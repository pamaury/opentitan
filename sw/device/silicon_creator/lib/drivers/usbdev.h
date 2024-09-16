// Copyright lowRISC contributors (OpenTitan project).
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0

#ifndef OPENTITAN_SW_DEVICE_SILICON_CREATOR_LIB_DRIVERS_USB_H_
#define OPENTITAN_SW_DEVICE_SILICON_CREATOR_LIB_DRIVERS_USB_H_

#include <stddef.h>
#include <stdint.h>

#include "sw/device/lib/base/hardened.h"
#include "sw/device/silicon_creator/lib/error.h"
#include "sw/device/silicon_creator/lib/drivers/usb_def.h"

#ifdef __cplusplus
extern "C" {
#endif

// Number of endpoints used.
#define USB_DRIVER_ENDPOINT_COUNT 2

// Maximum packet size supported by the hardwared.
#define USBDEV_MAX_PACKET_SIZE 64

void usb_printf(const char *format, ...) __attribute__((format(printf, 1, 2)));

// Result status for IN/OUT transfer completion callbacks.
typedef enum {
  // Transfer succeeded.
  kUsbdevTransferSuccess,
  // Transfer failed due to an internal error.
  kUsbdevTransferError,
  // Transfer was cancelled by suspend or new SETUP (control only),
  // or endpoint was disabled by software.
  kUsbdevTransferCancelled,
  // Transfer was cancelled by USB link reset.
  kUsbdevTransferReset,
} usbdev_transfer_result_t;

typedef void (*usbdev_in_transfer_complete_fn_t)(void *userptr, usbdev_transfer_result_t result);
typedef void (*usbdev_out_transfer_complete_fn_t)(void *userptr, usbdev_transfer_result_t result, size_t size);

typedef struct {
  // For incoming transfers.
  uint8_t *out_buffer; // Pointer to the buffer.
  size_t out_remaining; // Remaining size to fill in the buffer.
  size_t out_received; // How many bytes we have already received.
  void *out_userptr;
  usbdev_out_transfer_complete_fn_t out_callback;
  // For outgoing transfers.
  uint8_t *in_buffer; // Pointer to the buffer.
  size_t in_remaining; // Size of the remaining data in the buffer.
  bool in_zlp; // Send a ZLP after transfering all the data.
  void *in_userptr;
  usbdev_in_transfer_complete_fn_t in_callback;
} usbdev_ep_context_t;

typedef bool (*usbdev_handle_setup_fn_t)(void *userptr, usb_setup_t *setup);
typedef void (*usbdev_handle_reset_fn_t)(void *userptr);

typedef struct {
  usbdev_handle_setup_fn_t handle_setup;
  usbdev_handle_reset_fn_t handle_reset;
} usbdev_vtable_t;

typedef struct usb_context {
  usbdev_ep_context_t ep[USB_DRIVER_ENDPOINT_COUNT];
  void *userptr;
  usbdev_vtable_t *vtable;
} usbdev_context_t;

/**
 * Check whether USB VBUS is present, indicating a host.
 *
 * This function requires the USB VBUS sense pin to be configured.
 *
 * @return kHardenedBoolTrue if USB VBUS is present.
 */
bool usbdev_is_vbus_present(void);

/**
 * Initialize the USB device and connect to the bus.
 */
void usbdev_init(usbdev_context_t *ctx);

/**
 * Stop the USB device and disconnect from the bus.
 */
void usbdev_finalize(usbdev_context_t *ctx);

void usbdev_set_vtable(usbdev_context_t *ctx, void *userptr, usbdev_vtable_t *vtable);

void usbdev_set_address(usbdev_context_t *ctx, uint8_t address);

/**
 * TODO document
 */
void usbdev_transfer_send(usbdev_context_t *ctx, size_t epnum, void *buffer, size_t size, bool zlp,
                         void *userptr, usbdev_in_transfer_complete_fn_t callback);

void usbdev_transfer_recv(usbdev_context_t *ctx, size_t epnum, void *buffer, size_t size,
                         void *userptr, usbdev_out_transfer_complete_fn_t callback);

/**
 * TODO document
 */
void usbdev_stall_endpoint_out(usbdev_context_t *ctx, size_t ep, bool stall_out);
void usbdev_stall_endpoint_in(usbdev_context_t *ctx, size_t ep, bool stall_in);

/**
 * Handle USB requests in a loop.
 */
void usbdev_handle_request(usbdev_context_t *ctx, uint32_t timeout_us);
void usbdev_handle_request_deadline(usbdev_context_t *ctx, uint64_t deadline_cycles);

void usb_try_send_log(void);

#ifdef __cplusplus
}
#endif

#endif  // OPENTITAN_SW_DEVICE_SILICON_CREATOR_LIB_DRIVERS_USB_H_

