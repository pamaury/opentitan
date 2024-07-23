// Copyright lowRISC contributors.
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0
//
// Device table API auto-generated by `reggen`

#ifndef OPENTITAN_SW_DEVICE_LIB_DEVICETABLES_DT_ENTROPY_SRC_H_
#define OPENTITAN_SW_DEVICE_LIB_DEVICETABLES_DT_ENTROPY_SRC_H_

#include <stdint.h>

#include "sw/device/lib/devicetables/dt.h"

typedef enum {
  kDtEntropySrcRegBlockCore = 0,
  kDtEntropySrcRegBlockCount = 1,
} dt_entropy_src_reg_block_t;

typedef enum {
  kDtEntropySrcIrqTypeEsEntropyValid = 0,
  kDtEntropySrcIrqTypeEsHealthTestFailed = 1,
  kDtEntropySrcIrqTypeEsObserveFifoReady = 2,
  kDtEntropySrcIrqTypeEsFatalErr = 3,
  kDtEntropySrcIrqTypeCount = 4,
} dt_entropy_src_irq_type_t;

typedef enum {
  kDtEntropySrcClockClk = 0,
  kDtEntropySrcClockCount = 1,
} dt_entropy_src_clock_t;

typedef enum {
  kDtEntropySrcPinctrlInputCount = 0,
  kDtEntropySrcPinctrlOutputCount = 0,
} dt_entropy_src_pinctrl_t;

typedef struct dt_entropy_src {
  dt_device_id_t device_id;
  uint32_t base_addrs[kDtEntropySrcRegBlockCount];
  uint32_t irqs[kDtEntropySrcIrqTypeCount];
  dt_clock_t clocks[kDtEntropySrcClockCount];
} dt_entropy_src_t;

/**
 * Convert a global IRQ ID to a local entropy_src IRQ type.
 *
 * @param dt Pointer to an instance of entropy_src.
 * @param irq A global IRQ ID.
 * @return The local entropy_src IRQ type of this irq.
 *
 * IMPORTANT This function assumes that the global IRQ belongs to the instance
 * of entropy_src passed in parameter. In other words, it must the case that
 * `dt->device == dt_irq_to_device(irq)`
 *
 * FIXME How should we handle errors (when the invariant above is violated)?
 */
static inline dt_entropy_src_irq_type_t dt_entropy_src_irq_type(
    const dt_entropy_src_t *dt, dt_irq_t irq) {
  // FIXME Should check that irq >= dt->irqs[0] and irq < dt->irqs[0] +
  // kDtEntropySrcIrqTypeCount
  return irq - dt->irqs[0];
}

#endif  // OPENTITAN_SW_DEVICE_LIB_DEVICETABLES_DT_ENTROPY_SRC_H_
