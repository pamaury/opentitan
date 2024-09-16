// Copyright lowRISC contributors (OpenTitan project).
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0

#ifndef OPENTITAN_SW_DEVICE_SILICON_CREATOR_LIB_DRIVERS_USB_DEF_H_
#define OPENTITAN_SW_DEVICE_SILICON_CREATOR_LIB_DRIVERS_USB_DEF_H_

#include <stddef.h>
#include <stdint.h>

/** FIXME This header assumes that the target device is little-endian
 * so we don't need to swap bytes. Maybe introduce some functions to do
 * that that compile to NOP? */

#include "sw/device/lib/base/bitfield.h"

#ifdef __cplusplus
extern "C" {
#endif

// Device state (USB spec section 9.1)
typedef enum {
  kUsbDeviceAttached,
  kUsbDevicePowered,
  kUsbDeviceDefault,
  kUsbDeviceAddressed,
  kUsbDeviceConfigured,
  kUsbDeviceSuspended,
} usb_device_state_t;

typedef struct {
  uint8_t bmRequestType;
  uint8_t bRequest;
  uint16_t wValue;
  uint16_t wIndex;
  uint16_t wLength;
} __attribute__ ((packed)) usb_setup_t;

_Static_assert(sizeof(usb_setup_t) == 8, "usb_setup_t has the wrong size");

// bmRequestType fields.
#define USB_SETUP_REQTYPE_DIR_IN_BIT  7
#define USB_SETUP_REQTYPE_TYPE_MASK   (0x3 << 5)
#define USB_SETUP_REQTYPE_TYPE_OFFSET 5
#define USB_SETUP_REQTYPE_TYPE_FIELD \
  ((bitfield_field32_t) { .mask = USB_SETUP_REQTYPE_TYPE_MASK, .index = USB_SETUP_REQTYPE_TYPE_OFFSET })
#define USB_SETUP_REQTYPE_RECIP_MASK   (0x1f << 0)
#define USB_SETUP_REQTYPE_RECIP_OFFSET 0
#define USB_SETUP_REQTYPE_RECIP_FIELD \
  ((bitfield_field32_t) { .mask = USB_SETUP_REQTYPE_RECIP_MASK, .index = USB_SETUP_REQTYPE_RECIP_OFFSET })

// Values of USB_SETUP_REQTYPE_TYPE.
enum {
  kUsbSetupReqTypeStandard = 0,
  kUsbSetupReqTypeClass = 1,
  kUsbSetupReqTypeVendor = 2,
  kUsbSetupReqTypeReserved = 3,
};

// Values of USB_SETUP_REQTYPE_RECIP.
enum {
  kUsbSetupReqTypeDevice = 0,
  kUsbSetupReqTypeInterface = 1,
  kUsbSetupReqTypeEndpoint = 2,
  kUsbSetupReqTypeOther = 3,
};

// Standard requests.
enum {
  kUsbReqStdGetStatus = 0,
  kUsbReqStdClearFeature = 1,
  kUsbReqStdSetFeature = 3,
  kUsbReqStdSetAddress = 5,
  kUsbReqStdGetDescriptor = 6,
  kUsbReqStdSetDescriptor = 7,
  kUsbReqStdGetConfig = 8,
  kUsbReqStdSetConfig = 9,
  kUsbReqStdGetInterface = 10,
  kUsbReqStdSetInterface = 11,
};

// Standard descriptor types.
enum {
  kUsbStdDescTypeDevice = 1,
  kUsbStdDescTypeConfig = 2,
  kUsbStdDescTypeString = 3,
  kUsbStdDescTypeInterface = 4,
  kUsbStdDescTypeEndpoint = 5,
  kUsbStdDescTypeDevQualifier = 6,
};

// USB device descriptor.
typedef struct {
  uint8_t  bLength;
  uint8_t  bDescriptorType;
  uint16_t bcdUSB;
  uint8_t  bDeviceClass;
  uint8_t  bDeviceSubClass;
  uint8_t  bDeviceProtocol;
  uint8_t  bMaxPacketSize0;
  uint16_t idVendor;
  uint16_t idProduct;
  uint16_t bcdDevice;
  uint8_t  iManufacturer;
  uint8_t  iProduct;
  uint8_t  iSerialNumber;
  uint8_t  bNumConfigurations;
} __attribute__ ((packed)) usb_device_descriptor_t;

_Static_assert(sizeof(usb_device_descriptor_t) == 18, "usb_device_descriptor_t has the wrong size");

// Device and interface classes
enum {
  kUsbClassPerInterface = 0, // For device: class defined per interface.
  kUsbClassComm = 2,
  kUsbClassCdcData = 0xa,
};

// Device qualifier descriptor.
typedef struct {
  uint8_t  bLength;
  uint8_t  bDescriptorType;
  uint16_t bcdUSB;
  uint8_t  bDeviceClass;
  uint8_t  bDeviceSubClass;
  uint8_t  bDeviceProtocol;
  uint8_t  bMaxPacketSize0;
  uint8_t  bNumConfigurations;
  uint8_t  bReserved;
} __attribute__ ((packed)) usb_device_qualifier_t;

_Static_assert(sizeof(usb_device_qualifier_t) == 10, "usb_device_qualifier_t has the wrong size");

// Device configuration descriptor.
typedef struct {
  uint8_t  bLength;
  uint8_t  bDescriptorType;
  uint16_t wTotalLength;
  uint8_t  bNumInterfaces;
  uint8_t  bConfigurationValue;
  uint8_t  iConfiguration;
  uint8_t  bmAttributes;
  uint8_t  bMaxPower;
} __attribute__ ((packed)) usb_device_config_t;

_Static_assert(sizeof(usb_device_config_t) == 9, "usb_device_config_t has the wrong size");

// bmAttributes fields.
#define USB_DEV_CFG_ATTR_ONE_BIT          7
#define USB_DEV_CFG_ATTR_SELF_POWERED_BIT 6

// Interface descriptor.
typedef struct {
  uint8_t  bLength;
  uint8_t  bDescriptorType;
  uint8_t  bInterfaceNumber;
  uint8_t  bAlternateSetting;
  uint8_t  bNumEndpoints;
  uint8_t  bInterfaceClass;
  uint8_t  bInterfaceSubClass;
  uint8_t  bInterfaceProtocol;
  uint8_t  iInterface;
} __attribute__ ((packed)) usb_interface_descriptor_t;

#endif  // OPENTITAN_SW_DEVICE_SILICON_CREATOR_LIB_DRIVERS_USB_DEF_H_
