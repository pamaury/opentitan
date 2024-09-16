// Copyright lowRISC contributors (OpenTitan project).
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0

#include "sw/device/silicon_creator/lib/drivers/usbdev.h"
#include "sw/device/silicon_creator/lib/drivers/usb_def.h"
#include "sw/device/silicon_creator/lib/drivers/usb_core.h"

#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

#include "sw/device/lib/arch/device.h"
#include "sw/device/lib/base/abs_mmio.h"
#include "sw/device/lib/base/bitfield.h"
#include "sw/device/lib/base/memory.h"
#include "sw/device/lib/base/mmio.h"
#include "sw/device/silicon_creator/lib/dbg_print.h"
#include "sw/device/silicon_creator/lib/drivers/ibex.h"
#include "sw/device/silicon_creator/lib/drivers/uart.h"
#include "sw/device/silicon_creator/lib/error.h"

#include "hw/top_earlgrey/sw/autogen/top_earlgrey.h"
#include "usbdev_regs.h"  // Generated.

/* Buffer management.
 *
 * This driver does not try to be smart: we allocate the first N
 * buffers (0..N-1) for reception. Whenever a buffer is filled and given
 * to the software, the software will immediately copy (or read)
 * its content and push this buffer back into the available FIFO.
 * While not particularly efficient, this greatly simplifies the
 * management. We then allocate buffer N to EPiIN, ie EP1IN
 * will use buffer N. We do not do double buffering or anything
 * fancy.
 */

enum {
  // Number of buffers allocated for reception. Ideally should be
  // equal to the depth of the AVBUFFER.
  kUsbdevReceiveBufferCount = 4,
  // First buffer to send.
  kUsbdevSendBufferEp0 = kUsbdevReceiveBufferCount,
  // Size of buffers.
  kUsbdevBufferSize = 64,
  // Number of buffers supported by hardware.
  kUsbdevBufferCount = 32,
  // Usbdev register base.
  kUsbdevBase = TOP_EARLGREY_USBDEV_BASE_ADDR,
};

// Maximum number of supported endpoints.
#define USBDEV_NUM_ENDPOINTS USBDEV_PARAM_N_ENDPOINTS

_Static_assert(USB_DRIVER_ENDPOINT_COUNT <= USBDEV_NUM_ENDPOINTS, "too many endpoints used by driver");

#define ASSERT_VALUE(bitname, pos) \
  _Static_assert(bitname == pos, "This expects "#bitname " to be " #pos);

#define ASSERT_CONTIGUOUS(bitname) \
  ASSERT_VALUE(bitname##_0_BIT, 0) \
  ASSERT_VALUE(bitname##_1_BIT, 1) \

ASSERT_CONTIGUOUS(USBDEV_EP_OUT_ENABLE_ENABLE)
ASSERT_CONTIGUOUS(USBDEV_EP_IN_ENABLE_ENABLE)
ASSERT_CONTIGUOUS(USBDEV_RXENABLE_SETUP_SETUP)
ASSERT_CONTIGUOUS(USBDEV_RXENABLE_OUT_OUT)
ASSERT_CONTIGUOUS(USBDEV_SET_NAK_OUT_ENABLE)
ASSERT_CONTIGUOUS(USBDEV_IN_STALL_ENDPOINT)
ASSERT_CONTIGUOUS(USBDEV_OUT_STALL_ENDPOINT)
ASSERT_CONTIGUOUS(USBDEV_IN_SENT_SENT)

#define _ASSERT_REG_OFFSET(macro_val, expected) \
  _Static_assert(macro_val == expected, "Wrong register offset");

#define ASSERT_REG_OFFSET(macro_val, expected) \
  _ASSERT_REG_OFFSET(macro_val, expected)

#define ASSERT_REG_RANGE(macro, regname) \
  ASSERT_REG_OFFSET(macro(0), regname##_0##_REG_OFFSET) \
  ASSERT_REG_OFFSET(macro(1), regname##_1##_REG_OFFSET)

#define USBDEV_CONFIGIN_x_REG_OFFSET(x) \
  (USBDEV_CONFIGIN_0_REG_OFFSET + (x) * 4)

ASSERT_REG_RANGE(USBDEV_CONFIGIN_x_REG_OFFSET, USBDEV_CONFIGIN)

#define usb_set_ep_bit(ep, reg, field, val) \
  ({ \
    uint32_t regval = abs_mmio_read32(kUsbdevBase + USBDEV_##reg##_REG_OFFSET); \
    regval = bitfield_bit32_write(regval, USBDEV_##reg##_##field##_0_BIT + ep, (val) ? 1 : 0); \
    abs_mmio_write32(kUsbdevBase + USBDEV_##reg##_REG_OFFSET, regval); \
  })

static void usbdev_notify_in_complete(usbdev_context_t *ctx, size_t epnum, usbdev_transfer_result_t result) {
  usbdev_ep_context_t *ep = &ctx->ep[epnum];
  ep->in_buffer = NULL;
  ep->in_remaining = 0;
  ep->in_zlp = false;
  usbdev_in_transfer_complete_fn_t cb = ep->in_callback;
  void *userptr = ep->in_userptr;
  ep->in_callback = NULL;
  ep->in_userptr = NULL;
  if (cb)
    cb(userptr, result);
}

static void usbdev_notify_out_complete(usbdev_context_t *ctx, size_t epnum, usbdev_transfer_result_t result) {
  usbdev_ep_context_t *ep = &ctx->ep[epnum];
  ep->out_buffer = NULL;
  ep->out_remaining = 0;
  size_t received = ep->out_received;
  ep->out_received = 0;
  usbdev_out_transfer_complete_fn_t cb = ep->out_callback;
  void *userptr = ep->out_userptr;
  ep->out_callback = NULL;
  ep->out_userptr = NULL;
  if (cb)
    cb(userptr, result, received);
}

void usbdev_cancel_transfer_in(usbdev_context_t *ctx, size_t epnum, usbdev_transfer_result_t res) {
  usbdev_ep_context_t *ep = &ctx->ep[epnum];
  if (ep->in_remaining >0 || ep->in_zlp) {
    usbdev_notify_in_complete(ctx, epnum, res);
  }
}

void usbdev_cancel_transfer_out(usbdev_context_t *ctx, size_t epnum, usbdev_transfer_result_t res) {
  usbdev_ep_context_t *ep = &ctx->ep[epnum];
  if (ep->out_remaining > 0) {
    usbdev_notify_out_complete(ctx, epnum, res);
  }
}

bool usbdev_is_vbus_present(void) {
  uint32_t reg = abs_mmio_read32(kUsbdevBase + USBDEV_PHY_PINS_SENSE_REG_OFFSET);
  return bitfield_bit32_read(reg, USBDEV_PHY_PINS_SENSE_PWR_SENSE_BIT);
}

static void usbdev_configure_endpoint(size_t ep, bool en_in, bool en_out, bool en_rx_setup, bool en_rx, bool set_nak_out) {
  usb_set_ep_bit(ep, EP_OUT_ENABLE, ENABLE, en_out);
  usb_set_ep_bit(ep, EP_IN_ENABLE, ENABLE, en_in);
  usb_set_ep_bit(ep, RXENABLE_OUT, OUT, en_rx);
  usb_set_ep_bit(ep, RXENABLE_SETUP, SETUP, en_rx_setup);
  usb_set_ep_bit(ep, SET_NAK_OUT, ENABLE, set_nak_out);
}

static void usbdev_endpoint_enable_rx(usbdev_context_t *ctx, size_t ep, bool en_rx) {
  usb_set_ep_bit(ep, RXENABLE_OUT, OUT, en_rx);
}

static void usbdev_reset_endpoints(usbdev_context_t *ctx) {
  // This function may be called after a link reset and must therefore
  // clean-up everything to a good state. After this function is called:
  // all FIFOs are empty and all endpoints are disabled.

  // TODO: reset FIFOs (not available on ES?)

  // Disable all endpoints.
  abs_mmio_write32(kUsbdevBase + USBDEV_EP_OUT_ENABLE_REG_OFFSET, 0);
  abs_mmio_write32(kUsbdevBase + USBDEV_EP_IN_ENABLE_REG_OFFSET, 0);
  abs_mmio_write32(kUsbdevBase + USBDEV_RXENABLE_SETUP_REG_OFFSET, 0);

  // Clear all state.
  for (size_t i = 0; i < USB_DRIVER_ENDPOINT_COUNT; i++) {
    usbdev_cancel_transfer_in(ctx, i, kUsbdevTransferReset);
    usbdev_cancel_transfer_out(ctx, i, kUsbdevTransferReset);
    memset(&ctx->ep[i], 0, sizeof(usbdev_ep_context_t));
  }
}

static void usbdev_fifo_add_buffer(size_t buffer_id) {
  // NOTE If the FIFO is full, the write will be ignored, so this should always be called when it's not full.
  uint32_t reg_val = bitfield_field32_write(0, USBDEV_AVBUFFER_BUFFER_FIELD, buffer_id);
  abs_mmio_write32(kUsbdevBase + USBDEV_AVBUFFER_REG_OFFSET, reg_val);
}

static uint32_t usbdev_stat_av_depth(void) {
  uint32_t reg_val = abs_mmio_read32(kUsbdevBase + USBDEV_USBSTAT_REG_OFFSET);
  return bitfield_field32_read(reg_val, USBDEV_USBSTAT_AV_DEPTH_FIELD);
}

static bool usbdev_stat_av_full(void) {
  uint32_t reg_val = abs_mmio_read32(kUsbdevBase + USBDEV_USBSTAT_REG_OFFSET);
  return bitfield_bit32_read(reg_val, USBDEV_USBSTAT_AV_FULL_BIT);
}

static void usbdev_connect(bool connect) {
  uint32_t reg_val = abs_mmio_read32(kUsbdevBase + USBDEV_USBCTRL_REG_OFFSET);
  reg_val = bitfield_bit32_write(reg_val, USBDEV_USBCTRL_ENABLE_BIT, connect ? 1 : 0);
  abs_mmio_write32(kUsbdevBase + USBDEV_USBCTRL_REG_OFFSET, reg_val);
}

static void usbdev_init_control_ep(usbdev_context_t *ctx) {
  // Setup EP0: enable IN and OUT directions, allow SETUP reception, NAK OUT packets, automatically
  // NAK after receiving OUT packet.
  usbdev_configure_endpoint(/*ep=*/0, /*en_in=*/true, /*en_out*/true, /*en_rx_setup*/true, /*en_rx*/false, /*set_nak_out=*/true);
}

static void usbdev_read_buffer(usbdev_context_t *ctx, size_t buffer_id, void *dest, size_t len) {
  uint32_t bufaddr = USBDEV_BUFFER_REG_OFFSET + (buffer_id * kUsbdevBufferSize);
  // FIXME Unfortunately, there is no absolute function for that, we have to go through the mmio_region dance.
  mmio_region_t region = mmio_region_from_addr(kUsbdevBase);
  mmio_region_memcpy_from_mmio32(region, bufaddr, dest, len);
}

static void usb_write_buffer(usbdev_context_t *ctx, size_t buffer_id, void *dest, size_t len) {
  uint32_t bufaddr = USBDEV_BUFFER_REG_OFFSET + (buffer_id * kUsbdevBufferSize);
  // FIXME Unfortunately, there is no absolute function for that, we have to go through the mmio_region dance.
  mmio_region_t region = mmio_region_from_addr(kUsbdevBase);
  mmio_region_memcpy_to_mmio32(region, bufaddr, dest, len);
}

static void usbdev_init_buffers(usbdev_context_t *ctx) {
  if (usbdev_stat_av_depth() != 0) {
    // FIXME On the ES, we cannot drain the FIFOs on reset so we are stuck with the old
    // buffers that were previously pushed into the FIFO. Fortunately, we use a fixed assignment
    // for the buffers so it won't cause any harm. On A1, the FIFO is reset in usbdev_reset_endpoints()
    // so this case won't happen. If the FIFO is not empty, we don't know what was pushed so to avoid
    // tracking it, we don't do anything.
    usb_printf("usb: fifo not drained (%d remains)\n", usbdev_stat_av_depth());
    return;
  }

  // See buffer management.
  for (size_t i = 0; i < kUsbdevReceiveBufferCount; i++) {
    if(usbdev_stat_av_full()) {
      usb_printf("usb: av_full while still pushing buffer, kUsbdevReceiveBufferCount is too large\n");
    }
    usbdev_fifo_add_buffer(i);
  }
}

void usbdev_stall_endpoint_out(usbdev_context_t *ctx, size_t ep, bool stall_out) {
  usb_printf("stall EP%d OUT: %d\n", ep, stall_out);
  uint32_t regval = abs_mmio_read32(kUsbdevBase + USBDEV_OUT_STALL_REG_OFFSET);
  regval = bitfield_bit32_write(regval, ep, stall_out);
  abs_mmio_write32(kUsbdevBase + USBDEV_OUT_STALL_REG_OFFSET, regval);
}

void usbdev_stall_endpoint_in(usbdev_context_t *ctx, size_t ep, bool stall_in) {
  usb_printf("stall EP%d IN: %d\n", ep, stall_in);
  uint32_t regval = abs_mmio_read32(kUsbdevBase + USBDEV_IN_STALL_REG_OFFSET);
  regval = bitfield_bit32_write(regval, ep, stall_in);
  abs_mmio_write32(kUsbdevBase + USBDEV_IN_STALL_REG_OFFSET, regval);
}

void usbdev_send_buffer(usbdev_context_t *ctx, size_t epnum, size_t buffer_id, size_t sz) {
  uint32_t config_in = bitfield_field32_write(0, USBDEV_CONFIGIN_0_BUFFER_0_FIELD, buffer_id);
  config_in = bitfield_field32_write(config_in, USBDEV_CONFIGIN_0_SIZE_0_FIELD, sz);
  config_in = bitfield_bit32_write(config_in, USBDEV_CONFIGIN_0_RDY_0_BIT, true);
  abs_mmio_write32(kUsbdevBase + USBDEV_CONFIGIN_x_REG_OFFSET(epnum), config_in);
}

void usbdev_set_address(usbdev_context_t *ctx, uint8_t address) {
  uint32_t reg_val = abs_mmio_read32(kUsbdevBase + USBDEV_USBCTRL_REG_OFFSET);
  reg_val = bitfield_field32_write(reg_val, USBDEV_USBCTRL_DEVICE_ADDRESS_FIELD, address);
  abs_mmio_write32(kUsbdevBase + USBDEV_USBCTRL_REG_OFFSET, reg_val);
}

static void usbdev_transfer_continue_send(usbdev_context_t *ctx, size_t epnum) {
  // See buffer management.
  size_t buf_id = kUsbdevSendBufferEp0 + epnum;

  usbdev_ep_context_t *ep = &ctx->ep[epnum];
  if (ep->in_remaining != 0) {
    size_t sz = ep->in_remaining;
    if (sz > USBDEV_MAX_PACKET_SIZE) {
      sz = USBDEV_MAX_PACKET_SIZE;
    }
    usb_printf("usb ep%d: sending %d bytes\n", epnum, sz);
    usb_write_buffer(ctx, buf_id, ep->in_buffer, sz);
    ep->in_remaining -= sz;
    ep->in_buffer += sz;
    usbdev_send_buffer(ctx, epnum, buf_id, sz);
  } else if(ep->in_zlp) {
    usb_printf("usb ep%d: sending ZLP\n", epnum);
    usbdev_send_buffer(ctx, epnum, buf_id, 0);
    ep->in_zlp = false;
  } else {
    usb_printf("usb ep%d: transfer done\n", epnum);
    // Transfer complete.
    usbdev_notify_in_complete(ctx, epnum, kUsbdevTransferSuccess);
  }
}

void usbdev_transfer_send(usbdev_context_t *ctx, size_t epnum, void *buffer, size_t size, bool zlp,
                       void *userptr, usbdev_in_transfer_complete_fn_t callback) {
  // TODO check that no transfer is already pending.

  // If the size is 0, we turn it into a ZLP, otherwise usb_transfer_continue_send won't work.
  if (size == 0)
    zlp = true;

  usb_printf("transfer send: ep=%d, size=%d, zlp=%d\n", epnum, size, zlp);
  usbdev_ep_context_t *ep = &ctx->ep[epnum];
  ep->in_buffer = buffer;
  ep->in_remaining = size;
  ep->in_zlp = zlp;
  ep->in_userptr = userptr;
  ep->in_callback = callback;
  usbdev_transfer_continue_send(ctx, epnum);
}

void usbdev_transfer_recv(usbdev_context_t *ctx, size_t epnum, void *buffer, size_t size,
                       void *userptr, usbdev_out_transfer_complete_fn_t callback) {
  // TODO check that no transfer is already pending.
  usb_printf("transfer prepare recv: ep=%d, size=%d\n", epnum, size);
  usbdev_ep_context_t *ep = &ctx->ep[epnum];
  ep->out_buffer = buffer;
  ep->out_remaining = size;
  ep->out_received = 0;
  ep->out_userptr = userptr;
  ep->out_callback = callback;
  // Enable RX (we use auto NAK out).
  usbdev_endpoint_enable_rx(ctx, epnum, true);
}

static void usbdev_handle_recv(usbdev_context_t *ctx, size_t epnum, size_t buffer_id, size_t size) {
  usb_printf("handle recv: ep=%d, size=%d\n", epnum, size);
  usbdev_ep_context_t *ep = &ctx->ep[epnum];
  if (size > ep->out_remaining) {
    // Size too large, halt endpoint.
    usbdev_stall_endpoint_out(ctx, epnum, true);
    usbdev_notify_out_complete(ctx, epnum, kUsbdevTransferError);

  }
  else {
    // Write to buffer.
    if (size > 0) {
      usbdev_read_buffer(ctx, buffer_id, ep->out_buffer, size);
    }
    ep->out_buffer += size;
    ep->out_received += size;
    ep->out_remaining -= size;
    // Anything remaining?
    if (ep->out_remaining > 0) {
      // Enable RX (we use auto NAK out).
      usbdev_endpoint_enable_rx(ctx, epnum, true);
    }
    else {
      usbdev_notify_out_complete(ctx, epnum, kUsbdevTransferSuccess);
    }
  }
}

static void usbdev_handle_setup(usbdev_context_t *ctx, size_t ep, size_t buffer_id, size_t size) {
  bool stall_ep = true;

  // If there is a transfer in progress, cancel it.
  usbdev_cancel_transfer_in(ctx, ep, kUsbdevTransferCancelled);
  usbdev_cancel_transfer_out(ctx, ep, kUsbdevTransferCancelled);

  // Simply ignore invalid SETUP packets.
  if (ep != 0 || size != sizeof(usb_setup_t)) {
    usb_printf("usb: something is very wrong with SETUP packet (ep=%d, size=%d) ?!\n", ep, size);
  }
  else {
    // Read SETUP packet from buffer and extract the various fields.
    usb_setup_t setup;
    usbdev_read_buffer(ctx, buffer_id, &setup, sizeof(setup));
    if (ctx->vtable && ctx->vtable->handle_setup) {
      stall_ep = !ctx->vtable->handle_setup(ctx->userptr, &setup);
    }
  }
  // If SETUP was not handle, stall EP0 (will be cleared by HW on next SETUP).
  if (stall_ep) {
    usb_printf("setup not handled: stalling\n");
    usbdev_stall_endpoint_in(ctx, 0, true);
    usbdev_stall_endpoint_out(ctx, 0, true);
  }
}

void usbdev_handle_request_deadline(usbdev_context_t *ctx, uint64_t deadline) {
  usb_printf("usb_handle_request\n");
  while (ibex_mcycle() < deadline) {
    usb_try_send_log();
    // Is there anything to do?
    uint32_t intr_state = abs_mmio_read32(kUsbdevBase + USBDEV_INTR_STATE_REG_OFFSET);

    uint32_t ign_intr = bitfield_bit32_write(0, USBDEV_INTR_STATE_FRAME_BIT, 1);
    if ((intr_state & ~ign_intr) != 0) {
      usb_printf("usb: intr=%x\n", intr_state);
      // usb_printf("avbuffer depth: %d\n", usbdev_stat_av_depth());
    }

    // Packet sent.
    if (bitfield_bit32_read(intr_state, USBDEV_INTR_STATE_PKT_SENT_BIT)) {
      uint32_t in_sent = abs_mmio_read32(kUsbdevBase + USBDEV_IN_SENT_REG_OFFSET);
      for (size_t epnum = 0; epnum < USB_DRIVER_ENDPOINT_COUNT; epnum++) {
        if ((in_sent >> epnum) & 1) {
          // Notify completion.
          usbdev_transfer_continue_send(ctx, epnum);
        }
      }
      // Clear register.
      abs_mmio_write32(kUsbdevBase + USBDEV_IN_SENT_REG_OFFSET, in_sent);
    }

    // Packet received.
    if (bitfield_bit32_read(intr_state, USBDEV_INTR_STATE_PKT_RECEIVED_BIT)) {
      // Go through all received packets.
      while (true) {
        uint32_t usbstat = abs_mmio_read32(kUsbdevBase + USBDEV_USBSTAT_REG_OFFSET);
        if (bitfield_bit32_read(usbstat, USBDEV_USBSTAT_RX_EMPTY_BIT)) {
          break;
        }
        // Read packet description.
        uint32_t rxpkt = abs_mmio_read32(kUsbdevBase + USBDEV_RXFIFO_REG_OFFSET);
        uint8_t ep = (uint8_t)bitfield_field32_read(rxpkt, USBDEV_RXFIFO_EP_FIELD);
        uint8_t buffer_id = (uint8_t)bitfield_field32_read(rxpkt, USBDEV_RXFIFO_BUFFER_FIELD);
        uint16_t size = (uint16_t)bitfield_field32_read(rxpkt, USBDEV_RXFIFO_SIZE_FIELD);
        bool is_setup = bitfield_bit32_read(rxpkt, USBDEV_RXFIFO_SETUP_BIT);

        usb_printf("usb: pkt recv (ep=%d, stp=%d, bufid=%d, sz=%d)\n", ep, is_setup, buffer_id, size);
        // We will never use control endpoints other than EP0 so special case SETUP packets here.
        if (is_setup) {
          usbdev_handle_setup(ctx, ep, buffer_id, size);
        }
        else {
          usbdev_handle_recv(ctx, ep, buffer_id, size);
        }
        // As described in the buffer management, we always put the buffer back in the pool.
        usbdev_fifo_add_buffer(buffer_id);
      }
    }

    // Link reset.
    if (bitfield_bit32_read(intr_state, USBDEV_INTR_STATE_LINK_RESET_BIT)) {
      usb_printf("usb: reset\n");
      // Reset endpoints and buffers.
      usbdev_reset_endpoints(ctx);
      usbdev_init_control_ep(ctx);
      usbdev_init_buffers(ctx);
      if (ctx->vtable && ctx->vtable->handle_reset) {
        ctx->vtable->handle_reset(ctx->userptr);
      }
    }

    // Clear interrupts.
    abs_mmio_write32(kUsbdevBase + USBDEV_INTR_STATE_REG_OFFSET, intr_state);
  }
}

void usbdev_handle_request(usbdev_context_t *ctx, uint32_t timeout_us) {
  uint64_t deadline = ibex_mcycle() + ibex_time_to_cycles(timeout_us);
  usbdev_handle_request_deadline(ctx, deadline);
}

void usbdev_set_vtable(usbdev_context_t *ctx, void *userptr, usbdev_vtable_t *vtable) {
  ctx->userptr = userptr;
  ctx->vtable = vtable;
}

void usbdev_init(usbdev_context_t *ctx) {
  memset(ctx, 0, sizeof(usbdev_context_t));
  // Configure the PHY: enable differential receiver.
  uint32_t phy_config = 0;
  phy_config = bitfield_bit32_write(phy_config, USBDEV_PHY_CONFIG_USE_DIFF_RCVR_BIT, 1);
  abs_mmio_write32(kUsbdevBase + USBDEV_PHY_CONFIG_REG_OFFSET, phy_config);

  // Configure the endpoints.
  usbdev_reset_endpoints(ctx);
  usbdev_init_control_ep(ctx);
  usbdev_init_buffers(ctx);

  // Clear all interrupts so we don't get stale ones.
  uint32_t intr_state = abs_mmio_read32(kUsbdevBase + USBDEV_INTR_STATE_REG_OFFSET);
  abs_mmio_write32(kUsbdevBase + USBDEV_INTR_STATE_REG_OFFSET, intr_state);

  // Connect the USB interface.
  usbdev_connect(true);

  usb_printf("usb_init done\n");
}

void usbdev_finalize(usbdev_context_t *ctx) {
  usbdev_connect(false);
  usb_printf("usb_finalize\n");
}


// HACK
#define USB_LOG_BUFFER_SIZE   4000
static char usb_log_buffer[USB_LOG_BUFFER_SIZE];
static size_t usb_log_buffer_read = 0;
static size_t usb_log_buffer_write = 0;

static void usb_putchar(char c) {
  size_t next = usb_log_buffer_write + 1;
  if (next == USB_LOG_BUFFER_SIZE) {
    next = 0;
  }
  if (next != usb_log_buffer_read) {
    usb_log_buffer[usb_log_buffer_write] = c;
    usb_log_buffer_write = next;
  }
  else {
    // Ignore write.
  }
}

void usb_try_send_log(void) {
  while (usb_log_buffer_read != usb_log_buffer_write) {
    char c = usb_log_buffer[usb_log_buffer_read];
    if (!uart_try_putchar(c))
      return;
    usb_log_buffer_read++;
    if (usb_log_buffer_read == USB_LOG_BUFFER_SIZE)
      usb_log_buffer_read = 0;
  }
}

static const char kHexTable[16] = "0123456789abcdef";

static void print_integer(unsigned value, bool is_signed) {
  char buf[12];
  char *b = buf + sizeof(buf);
  if (is_signed && (int)value < 0) {
    usb_putchar('-');
    value = (unsigned)(-(int)value);
  }
  *--b = '\0';
  do {
    *--b = '0' + value % 10;
    value /= 10;
  } while (value);
  while (*b) {
    usb_putchar(*b++);
  }
}

void usb_printf(const char *format, ...) {
  va_list args;
  va_start(args, format);

  usb_putchar('[');
  print_integer((uint32_t)(ibex_mcycle() & 0xffffffff), false);
  usb_putchar(']');

  for (; *format != '\0'; ++format) {
    if (*format != '%') {
      usb_putchar(*format);
      continue;
    }

    ++format;  // Skip over the '%'.
    switch (*format) {
      case '%':
        usb_putchar(*format);
        break;
      case 'c': {
        int ch = va_arg(args, int);
        usb_putchar((char)ch);
        break;
      }
      case 'C': {
        uint32_t val = va_arg(args, uint32_t);
        for (size_t i = 0; i < sizeof(uint32_t); ++i, val >>= 8) {
          uint8_t ch = (uint8_t)val;
          if (ch >= 32 && ch < 127) {
            usb_putchar((char)ch);
          } else {
            usb_putchar('\\');
            usb_putchar('x');
            usb_putchar(kHexTable[ch >> 4]);
            usb_putchar(kHexTable[ch & 15]);
          }
        }
        break;
      }
      case 's': {
        // Print a null-terminated string.
        const char *str = va_arg(args, const char *);
        while (*str != '\0') {
          usb_putchar(*str++);
        }
        break;
      }
      case 'd':
        // `print_integer` will handle the sign bit of the value.
        print_integer(va_arg(args, unsigned), true);
        break;
      case 'u':
        print_integer(va_arg(args, unsigned), false);
        break;
      case 'p':
        OT_FALLTHROUGH_INTENDED;
      case 'x': {
        // Print an `unsigned int` in hexadecimal.
        unsigned int v = va_arg(args, unsigned int);
        for (int i = 0; i < sizeof(v) * 2; ++i) {
          int shift = sizeof(v) * 8 - 4;
          usb_putchar(kHexTable[v >> shift]);
          v <<= 4;
        }
        break;
      }
      default:
        // For an invalid format specifier, back up one char and allow the
        // output via the normal mechanism.
        usb_putchar('%');
        --format;
    }
  }
  va_end(args);
}

