// Copyright lowRISC contributors (OpenTitan project).
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0

#ifndef OPENTITAN_SW_DEVICE_SILICON_CREATOR_LIB_DRIVERS_USB_CORE_H_
#define OPENTITAN_SW_DEVICE_SILICON_CREATOR_LIB_DRIVERS_USB_CORE_H_

#include <stddef.h>
#include <stdint.h>

#include "sw/device/lib/base/hardened.h"
#include "sw/device/silicon_creator/lib/error.h"

#include "sw/device/silicon_creator/lib/drivers/usb_def.h"
#include "sw/device/silicon_creator/lib/drivers/usbdev.h"

#ifdef __cplusplus
extern "C" {
#endif

// Size of the buffer used to construct descriptors. It should be large enough
// to accomodate the largest possible descriptor.
#define USB_CORE_DESCRIPTOR_BUFFER_SIZE   1024

// Maximum number of string descriptors supported.
#define USB_CORE_MAX_STRING_DESC_COUNT    5

typedef void (*usb_core_control_transfer_complete_fn_t)(void *userptr, usbdev_transfer_result_t result);
typedef bool (*usb_core_control_out_transfer_received_fn_t)(void *userptr);

typedef struct {
  struct usb_context *usb_ctx;
  // Device state.
  usb_device_state_t state;
  // Buffer used to construct descriptors.
  uint8_t desc_buffer[USB_CORE_DESCRIPTOR_BUFFER_SIZE];
  // String descriptors.
  const char *strings[USB_CORE_MAX_STRING_DESC_COUNT];
  size_t string_count;
  // User pointer and callback for control transfers.
  void *control_xfer_userptr;
  usb_core_control_transfer_complete_fn_t control_xfer_complete;
  usb_core_control_out_transfer_received_fn_t control_xfer_received;
  // Current configuration.
  uint8_t config_val;
  // New configuration.
  uint8_t new_config_val;
  // New address.
  uint8_t new_address;
} usb_core_context_t;

// Public
usb_device_state_t usb_core_get_state(usb_core_context_t *ctx);

/**
 * Wait until USB device is in the configured state.
 *
 * @param timeout_us Maximum time to wait.
 * @return kHardenedBoolTrue if device was configured before the timeout.
 */
bool usb_core_wait_until_configured(usb_core_context_t *ctx, uint32_t timeout_us);

void usb_core_init(usb_core_context_t *core_ctx, struct usb_context *ctx);

void usb_core_reset(usb_core_context_t *core_ctx);

void usb_core_finalize(usb_core_context_t *core_ctx);

#ifdef __cplusplus
}
#endif

#endif  // OPENTITAN_SW_DEVICE_SILICON_CREATOR_LIB_DRIVERS_USB_CORE_H_

