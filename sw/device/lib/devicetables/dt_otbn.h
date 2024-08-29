// Copyright lowRISC contributors.
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0
//
// Device table API auto-generated by `reggen`

#ifndef OPENTITAN_SW_DEVICE_LIB_DEVICETABLES_DT_OTBN_H_
#define OPENTITAN_SW_DEVICE_LIB_DEVICETABLES_DT_OTBN_H_

#include <stdint.h>

#include "sw/device/lib/devicetables/dt_api.h"

typedef enum {
  kDtOtbnRegBlockCore = 0,
  kDtOtbnRegBlockCount = 1,
} dt_otbn_reg_block_t;

typedef enum {
  kDtOtbnIrqTypeDone = 0,
  kDtOtbnIrqTypeCount = 1,
} dt_otbn_irq_type_t;

typedef enum {
  kDtOtbnClockClk = 0,
  kDtOtbnClockEdn = 1,
  kDtOtbnClockOtp = 2,
  kDtOtbnClockCount = 3,
} dt_otbn_clock_t;

typedef struct dt_otbn {
  dt_device_id_t device_id;
  uint32_t base_addrs[kDtOtbnRegBlockCount];
  uint32_t irqs[kDtOtbnIrqTypeCount];
  dt_clock_t clocks[kDtOtbnClockCount];
} dt_otbn_t;

/**
 * Convert a global IRQ ID to a local otbn IRQ type.
 *
 * @param dt Pointer to an instance of otbn.
 * @param irq A global IRQ ID.
 * @return The local otbn IRQ type of this irq.
 *
 * IMPORTANT This function assumes that the global IRQ belongs to the instance
 * of otbn passed in parameter. In other words, it must be the case that
 * `dt->device_id == dt_irq_to_device(irq)`
 *
 * FIXME How should we handle errors (when the invariant above is violated)?
 */
static inline dt_otbn_irq_type_t dt_otbn_irq_type(const dt_otbn_t *dt,
                                                  dt_irq_t irq) {
  // FIXME Should check that irq >= dt->irqs[0] and irq < dt->irqs[0] +
  // kDtOtbnIrqTypeCount
  return irq - dt->irqs[0];
}

#endif  // OPENTITAN_SW_DEVICE_LIB_DEVICETABLES_DT_OTBN_H_
