// Copyright lowRISC contributors.
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0
//
// Device table API auto-generated by `reggen`

#ifndef OPENTITAN_SW_DEVICE_LIB_DEVICETABLES_DT_USBDEV_H_
#define OPENTITAN_SW_DEVICE_LIB_DEVICETABLES_DT_USBDEV_H_

#include <stdint.h>

#include "sw/device/lib/devicetables/dt.h"

typedef enum {
  kDtUsbdevRegBlockCore = 0,
  kDtUsbdevRegBlockCount = 1,
} dt_usbdev_reg_block_t;

typedef enum {
  kDtUsbdevIrqTypePktReceived = 0,
  kDtUsbdevIrqTypePktSent = 1,
  kDtUsbdevIrqTypeDisconnected = 2,
  kDtUsbdevIrqTypeHostLost = 3,
  kDtUsbdevIrqTypeLinkReset = 4,
  kDtUsbdevIrqTypeLinkSuspend = 5,
  kDtUsbdevIrqTypeLinkResume = 6,
  kDtUsbdevIrqTypeAvOutEmpty = 7,
  kDtUsbdevIrqTypeRxFull = 8,
  kDtUsbdevIrqTypeAvOverflow = 9,
  kDtUsbdevIrqTypeLinkInErr = 10,
  kDtUsbdevIrqTypeRxCrcErr = 11,
  kDtUsbdevIrqTypeRxPidErr = 12,
  kDtUsbdevIrqTypeRxBitstuffErr = 13,
  kDtUsbdevIrqTypeFrame = 14,
  kDtUsbdevIrqTypePowered = 15,
  kDtUsbdevIrqTypeLinkOutErr = 16,
  kDtUsbdevIrqTypeAvSetupEmpty = 17,
  kDtUsbdevIrqTypeCount = 18,
} dt_usbdev_irq_type_t;

typedef enum {
  kDtUsbdevClockClk = 0,
  kDtUsbdevClockAon = 1,
  kDtUsbdevClockCount = 2,
} dt_usbdev_clock_t;

typedef enum {
  kDtUsbdevPinctrlInputSense = 0,
  kDtUsbdevPinctrlInoutUsbDp = 1,
  kDtUsbdevPinctrlInoutUsbDn = 2,
  kDtUsbdevPinctrlInputCount = 3,
  kDtUsbdevPinctrlOutputCount = 3,
} dt_usbdev_pinctrl_t;

typedef struct dt_usbdev {
  dt_device_id_t device_id;
  uint32_t base_addrs[kDtUsbdevRegBlockCount];
  uint32_t irqs[kDtUsbdevIrqTypeCount];
  dt_clock_t clocks[kDtUsbdevClockCount];
} dt_usbdev_t;

/**
 * Convert a global IRQ ID to a local usbdev IRQ type.
 *
 * @param dt Pointer to an instance of usbdev.
 * @param irq A global IRQ ID.
 * @return The local usbdev IRQ type of this irq.
 *
 * IMPORTANT This function assumes that the global IRQ belongs to the instance
 * of usbdev passed in parameter. In other words, it must the case that
 * `dt->device == dt_irq_to_device(irq)`
 *
 * FIXME How should we handle errors (when the invariant above is violated)?
 */
static inline dt_usbdev_irq_type_t dt_usbdev_irq_type(const dt_usbdev_t *dt,
                                                      dt_irq_t irq) {
  // FIXME Should check that irq >= dt->irqs[0] and irq < dt->irqs[0] +
  // kDtUsbdevIrqTypeCount
  return irq - dt->irqs[0];
}

#endif  // OPENTITAN_SW_DEVICE_LIB_DEVICETABLES_DT_USBDEV_H_
