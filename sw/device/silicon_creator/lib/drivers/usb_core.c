// Copyright lowRISC contributors (OpenTitan project).
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0

#include "sw/device/silicon_creator/lib/drivers/usb_core.h"

#include "sw/device/lib/base/bitfield.h"
#include "sw/device/lib/base/memory.h"
#include "sw/device/silicon_creator/lib/dbg_print.h"
#include "sw/device/silicon_creator/lib/drivers/ibex.h"
#include "sw/device/silicon_creator/lib/error.h"

static usb_device_descriptor_t usb_core_dev_desc = {
  .bLength            = sizeof(usb_device_descriptor_t),
  .bDescriptorType    = kUsbStdDescTypeDevice,
  .bcdUSB             = 0x0200,
  .bDeviceClass       = kUsbClassPerInterface,
  .bDeviceSubClass    = 0,
  .bDeviceProtocol    = 0,
  .bMaxPacketSize0    = USBDEV_MAX_PACKET_SIZE,
  .idVendor           = 0, // Filled at runtime.
  .idProduct          = 0, // Filled at runtime.
  .bcdDevice          = 0x0100,
  .iManufacturer      = 0, // Filled at runtime.
  .iProduct           = 0, // Filled at runtime.
  .iSerialNumber      = 0, // Filled at runtime.
  .bNumConfigurations = 1
};

static usb_device_qualifier_t usb_core_dev_qualifier = {
  .bLength            = sizeof(usb_device_qualifier_t),
  .bDescriptorType    = kUsbStdDescTypeDevQualifier,
  .bcdUSB             = 0x0200,
  .bDeviceClass       = kUsbClassPerInterface,
  .bDeviceSubClass    = 0,
  .bDeviceProtocol    = 0,
  .bMaxPacketSize0    = USBDEV_MAX_PACKET_SIZE,
  .bNumConfigurations = 1
};

static usb_device_config_t usb_core_dev_config = {
  .bLength             = sizeof(usb_device_config_t),
  .bDescriptorType     = kUsbStdDescTypeConfig,
  .wTotalLength        = 0, // Filled at runtime.
  .bNumInterfaces      = 0, // Filled at runtime.
  .bConfigurationValue = 1,
  .iConfiguration      = 0,
  .bmAttributes        = (1 << USB_DEV_CFG_ATTR_ONE_BIT) | (1 << USB_DEV_CFG_ATTR_SELF_POWERED_BIT),
  .bMaxPower           = (500 + 1) / 2, /* In 2mA units */
};

static void write_dev_desc(usb_core_context_t *core_ctx, usb_device_descriptor_t *desc) {
  memcpy(desc, &usb_core_dev_desc, sizeof(usb_core_dev_desc));
  desc->idVendor = 0xdead;
  desc->idProduct = 0xbeef;
}

static void write_dev_qualifier(usb_core_context_t *core_ctx, usb_device_qualifier_t *desc) {
  memcpy(desc, &usb_core_dev_qualifier, sizeof(usb_core_dev_qualifier));
}

static void write_config_desc(usb_core_context_t *core_ctx, usb_device_config_t *desc) {
  memcpy(desc, &usb_core_dev_config, sizeof(usb_core_dev_config));
}

usb_device_state_t usb_core_get_state(usb_core_context_t *ctx) {
  return ctx->state;
}

static void usb_core_set_state(usb_core_context_t *ctx, usb_device_state_t state) {
  usb_printf("state: %d -> %d\n", ctx->state, state);
  ctx->state = state;
}

static void usb_core_change_config(usb_core_context_t *core_ctx, uint8_t config_val) {
  // TODO deinit previous config
  core_ctx->config_val = config_val;
  usb_printf("usb core: set config=%d\n", config_val);
  usb_core_set_state(core_ctx, config_val == 0 ? kUsbDeviceAddressed : kUsbDeviceConfigured);
  // TODO init new config
}

static size_t usb_core_create_config_desc(usb_core_context_t *core_ctx, void *buffer, size_t bufsize) {
  size_t remsize = bufsize;
  usb_device_config_t *cfgdesc = buffer;
  write_config_desc(core_ctx, cfgdesc);
  remsize -= sizeof(usb_device_config_t);
  // TODO fill interface descriptors
  cfgdesc->wTotalLength = (uint16_t)(bufsize - remsize);
  return bufsize - remsize;
}

static void usb_core_notify_control_complete(usb_core_context_t *core_ctx, usbdev_transfer_result_t result) {
  void *userptr = core_ctx->control_xfer_userptr;
  usb_core_control_transfer_complete_fn_t cb = core_ctx->control_xfer_complete;
  core_ctx->control_xfer_userptr = NULL;
  core_ctx->control_xfer_complete = NULL;
  core_ctx->control_xfer_received = NULL;
  if (cb)
    cb(userptr, result);
}

static void usb_core_control_status_out(void *userptr, usbdev_transfer_result_t result, size_t sz) {
  usb_core_context_t *core_ctx = userptr;
  usb_printf("usb: control status: result=%d\n", result);
  usb_core_notify_control_complete(core_ctx, result);
}

static void usb_core_control_send_done(void *userptr, usbdev_transfer_result_t result) {
  usb_core_context_t *core_ctx = userptr;
  usb_printf("usb: control sent: result=%d\n", result);
  if (result == kUsbdevTransferSuccess) {
    // Status stage: receive a ZLP.
    usbdev_transfer_recv(core_ctx->usb_ctx, 0, /*buffer=*/NULL, /*size*/0, /*userptr=*/core_ctx, &usb_core_control_status_out);
  } else {
    usb_core_notify_control_complete(core_ctx, result);
  }
}

static void usb_core_control_send(usb_core_context_t *core_ctx, usb_setup_t *setup, void *buffer, size_t size,
                                  void *userptr, usb_core_control_transfer_complete_fn_t transfer_done_fn) {
  usb_printf("control send: wLength=%d, size=%d\n", setup->wLength, size);
  core_ctx->control_xfer_userptr = userptr;
  core_ctx->control_xfer_complete = transfer_done_fn;
  if (size > setup->wLength) {
    size = setup->wLength;
  }
  bool zlp = (size < setup->wLength && (size % USBDEV_MAX_PACKET_SIZE) == 0);
  usbdev_transfer_send(core_ctx->usb_ctx, 0, buffer, size, zlp, /*userptr=*/core_ctx, &usb_core_control_send_done);
}

static void usb_core_control_ack_done(void *userptr, usbdev_transfer_result_t result) {
  usb_core_context_t *core_ctx = userptr;
  usb_printf("usb: control acked: result=%d\n", result);
  usb_core_notify_control_complete(core_ctx, result);
}

static void usb_core_control_ack(usb_core_context_t *core_ctx, void *userptr, usb_core_control_transfer_complete_fn_t transfer_done_fn) {
  core_ctx->control_xfer_userptr = userptr;
  core_ctx->control_xfer_complete = transfer_done_fn;
  usbdev_transfer_send(core_ctx->usb_ctx, 0, /*buffer=*/NULL, /*size=*/0, false, /*userptr=*/core_ctx, &usb_core_control_ack_done);
}

static bool usb_core_get_dev_desc(usb_core_context_t *core_ctx, usb_setup_t *setup) {
  // The descriptor type is stored in the upper 8-bits of wValue and the lower
  // are for the index.
  uint8_t desc_type = setup->wValue >> 8;
  uint8_t desc_index = setup->wIndex & 0xff;

  switch (desc_type) {
    case kUsbStdDescTypeDevice:
      usb_printf("sending dev desc\n");
      if (desc_index != 0) {
        return false;
      }
      write_dev_desc(core_ctx, (void *)core_ctx->desc_buffer);
      usb_core_control_send(core_ctx, setup, core_ctx->desc_buffer, sizeof(usb_device_descriptor_t), /*userptr=*/NULL, /*callback*/NULL);
      return true;
    case kUsbStdDescTypeDevQualifier:
      usb_printf("sending dev qualifier\n");
      if (desc_index != 0) {
        return false;
      }
      write_dev_qualifier(core_ctx, (void *)core_ctx->desc_buffer);
      usb_core_control_send(core_ctx, setup, core_ctx->desc_buffer, sizeof(usb_device_qualifier_t), /*userptr=*/NULL, /*callback*/NULL);
      return true;
    case kUsbStdDescTypeConfig:
      usb_printf("sending dev cfg\n");
      if (desc_index != 0) {
        return false;
      }
      size_t size = usb_core_create_config_desc(core_ctx, core_ctx->desc_buffer, USB_CORE_DESCRIPTOR_BUFFER_SIZE);
      usb_core_control_send(core_ctx, setup, core_ctx->desc_buffer, size, /*userptr=*/NULL, /*callback*/NULL);
      return true;
    default:
      usb_printf("usb: unhandled std dev desc %d\n", desc_type);
      return false;
  }
}

static void usb_core_set_address_status(void *userptr, usbdev_transfer_result_t result) {
  usb_core_context_t *core_ctx = userptr;
  if (result == kUsbdevTransferSuccess) {
    usb_printf("usb: set address=%d\n", core_ctx->new_address);
    usbdev_set_address(core_ctx->usb_ctx, core_ctx->new_address);
    usb_core_set_state(core_ctx, core_ctx->new_address == 0 ? kUsbDeviceDefault : kUsbDeviceAddressed);
  }
  else {
    usb_printf("usb: set address ack failed\n");
  }
}

static bool usb_core_set_address(usb_core_context_t *core_ctx, usb_setup_t *setup) {
  usb_device_state_t state = usb_core_get_state(core_ctx);
  if (state != kUsbDeviceDefault && state != kUsbDeviceAddressed) {
    usb_printf("unexpected set_address is state %d", state);
    return false;
  }
  core_ctx->new_address = setup->wValue & 0xff;
  usb_core_control_ack(core_ctx, /*userptr=*/core_ctx, /*callback*/usb_core_set_address_status);
  return true;
}

static void usb_core_set_config_status(void *userptr, usbdev_transfer_result_t result) {
  usb_core_context_t *core_ctx = userptr;
  if (result == kUsbdevTransferSuccess) {
    usb_core_change_config(core_ctx, core_ctx->new_config_val);
  }
  else {
    usb_printf("usb: set config ack failed\n");
  }
}

static bool usb_core_set_config(usb_core_context_t *core_ctx, usb_setup_t *setup) {
  usb_device_state_t state = usb_core_get_state(core_ctx);
  if (state != kUsbDeviceAddressed && state != kUsbDeviceConfigured) {
    usb_printf("unexpected set_config is state %d", state);
    return false;
  }
  core_ctx->new_config_val = setup->wValue & 0xff;
  // TODO check value valid.
  usb_core_control_ack(core_ctx, /*userptr=*/core_ctx, /*callback*/usb_core_set_config_status);
  return true;
}

static bool usb_core_handle_std_dev_req(usb_core_context_t *core_ctx, usb_setup_t *setup) {
  switch (setup->bRequest) {
    case kUsbReqStdGetDescriptor:
      return usb_core_get_dev_desc(core_ctx, setup);
    case kUsbReqStdSetAddress:
      return usb_core_set_address(core_ctx, setup);
    case kUsbReqStdSetConfig:
      return usb_core_set_config(core_ctx, setup);
    default:
      usb_printf("usb: unhandled std dev req %d\n", setup->bRequest);
      return false;
  }
}

static bool usb_core_handle_std_req(usb_core_context_t *core_ctx, usb_setup_t *setup) {
  uint32_t recip = bitfield_field32_read(setup->bmRequestType, USB_SETUP_REQTYPE_RECIP_FIELD);
  switch (recip) {
    case kUsbSetupReqTypeDevice:
      return usb_core_handle_std_dev_req(core_ctx, setup);
    default:
      usb_printf("usb: unhandled std req recip %d\n", recip);
      return false;
  }
}

static bool usb_core_handle_setup(usb_core_context_t *core_ctx, usb_setup_t *setup) {
  uint32_t reqtype = bitfield_field32_read(setup->bmRequestType, USB_SETUP_REQTYPE_TYPE_FIELD);
  switch (reqtype) {
    case kUsbSetupReqTypeStandard:
      return usb_core_handle_std_req(core_ctx, setup);
    default:
      usb_printf("usb: unhandled req type %d\n", reqtype);
      return false;
  }
}

static void usb_core_handle_reset(usb_core_context_t *core_ctx) {
  usb_printf("usb_core: reset\n");
  // Move back to default state.
  usb_core_set_state(core_ctx, kUsbDeviceDefault);
}

static bool _usb_core_handle_setup(void *user, usb_setup_t *setup) {
  return usb_core_handle_setup(user, setup);
}

static void _usb_core_handle_reset(void *user) {
  usb_core_handle_reset(user);
}

static usbdev_vtable_t usb_core_vtable = {
  .handle_setup = _usb_core_handle_setup,
  .handle_reset = _usb_core_handle_reset,
};

void usb_core_init(usb_core_context_t *core_ctx, struct usb_context *usb_ctx) {
  memset(core_ctx, 0, sizeof(usb_core_context_t));
  core_ctx->usb_ctx = usb_ctx;
  // We are in the default state.
  core_ctx->state = kUsbDeviceDefault;
  // Set callbacks.
  usbdev_set_vtable(usb_ctx, core_ctx, &usb_core_vtable);
}

void usb_core_reset(usb_core_context_t *core_ctx) {

}

void usb_core_finalize(usb_core_context_t *core_ctx) {

}

bool usb_core_wait_until_configured(usb_core_context_t *ctx, uint32_t timeout_us) {
  usb_printf("wait until configured\n");
  uint64_t deadline = ibex_mcycle() + ibex_time_to_cycles(timeout_us);
  while (usb_core_get_state(ctx) != kUsbDeviceConfigured && ibex_mcycle() < deadline) {
    usbdev_handle_request_deadline(ctx->usb_ctx, deadline);
  }
  return usb_core_get_state(ctx) == kUsbDeviceConfigured;
}