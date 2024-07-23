// Copyright lowRISC contributors.
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0
//
// Device table API auto-generated by `reggen`

#ifndef OPENTITAN_SW_DEVICE_LIB_DEVICETABLES_DT_I2C_H_
#define OPENTITAN_SW_DEVICE_LIB_DEVICETABLES_DT_I2C_H_

#include <stdint.h>

#include "sw/device/lib/devicetables/dt.h"

typedef enum {
  kDtI2cRegBlockCore = 0,
  kDtI2cRegBlockCount = 1,
} dt_i2c_reg_block_t;

typedef enum {
  kDtI2cIrqTypeFmtThreshold = 0,
  kDtI2cIrqTypeRxThreshold = 1,
  kDtI2cIrqTypeAcqThreshold = 2,
  kDtI2cIrqTypeRxOverflow = 3,
  kDtI2cIrqTypeControllerHalt = 4,
  kDtI2cIrqTypeSclInterference = 5,
  kDtI2cIrqTypeSdaInterference = 6,
  kDtI2cIrqTypeStretchTimeout = 7,
  kDtI2cIrqTypeSdaUnstable = 8,
  kDtI2cIrqTypeCmdComplete = 9,
  kDtI2cIrqTypeTxStretch = 10,
  kDtI2cIrqTypeTxThreshold = 11,
  kDtI2cIrqTypeAcqStretch = 12,
  kDtI2cIrqTypeUnexpStop = 13,
  kDtI2cIrqTypeHostTimeout = 14,
  kDtI2cIrqTypeCount = 15,
} dt_i2c_irq_type_t;

typedef enum {
  kDtI2cClockClk = 0,
  kDtI2cClockCount = 1,
} dt_i2c_clock_t;

typedef enum {
  kDtI2cPinctrlInoutSda = 0,
  kDtI2cPinctrlInoutScl = 1,
  kDtI2cPinctrlInputCount = 2,
  kDtI2cPinctrlOutputCount = 2,
} dt_i2c_pinctrl_t;

typedef struct dt_i2c {
  dt_device_id_t device_id;
  uint32_t base_addrs[kDtI2cRegBlockCount];
  uint32_t irqs[kDtI2cIrqTypeCount];
  dt_clock_t clocks[kDtI2cClockCount];
} dt_i2c_t;

/**
 * Convert a global IRQ ID to a local i2c IRQ type.
 *
 * @param dt Pointer to an instance of i2c.
 * @param irq A global IRQ ID.
 * @return The local i2c IRQ type of this irq.
 *
 * IMPORTANT This function assumes that the global IRQ belongs to the instance
 * of i2c passed in parameter. In other words, it must be the case that
 * `dt->device_id == dt_irq_to_device(irq)`
 *
 * FIXME How should we handle errors (when the invariant above is violated)?
 */
static inline dt_i2c_irq_type_t dt_i2c_irq_type(const dt_i2c_t *dt,
                                                dt_irq_t irq) {
  // FIXME Should check that irq >= dt->irqs[0] and irq < dt->irqs[0] +
  // kDtI2cIrqTypeCount
  return irq - dt->irqs[0];
}

#endif  // OPENTITAN_SW_DEVICE_LIB_DEVICETABLES_DT_I2C_H_
