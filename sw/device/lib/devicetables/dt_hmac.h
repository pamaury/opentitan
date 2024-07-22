// Copyright lowRISC contributors.
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0
//
// Device table API auto-generated by `reggen`

#ifndef OPENTITAN_SW_DEVICE_LIB_DEVICETABLES_DT_HMAC_H_
#define OPENTITAN_SW_DEVICE_LIB_DEVICETABLES_DT_HMAC_H_

#include <stdint.h>

#include "sw/device/lib/devicetables/dt.h"

typedef enum {
  kDtHmacRegBlockCore = 0,
  kDtHmacRegBlockCount = 1,
} dt_hmac_reg_block_t;

typedef enum {
  kDtHmacIrqTypeHmacDone = 0,
  kDtHmacIrqTypeFifoEmpty = 1,
  kDtHmacIrqTypeHmacErr = 2,
  kDtHmacIrqTypeCount = 3,
} dt_hmac_irq_type_t;

typedef enum {
  kDtHmacClockClk = 0,
  kDtHmacClockCount = 1,
} dt_hmac_clock_t;

typedef enum {
  kDtHmacPinctrlInputCount = 0,
  kDtHmacPinctrlOutputCount = 0,
} dt_hmac_pinctrl_t;

typedef struct dt_hmac {
  dt_device_t device;
  uint32_t base_addrs[kDtHmacRegBlockCount];
  uint32_t irqs[kDtHmacIrqTypeCount];
  dt_clock_t clocks[kDtHmacClockCount];
} dt_hmac_t;

/**
 * Convert a global IRQ ID to a local hmac IRQ type.
 *
 * @param dt Pointer to an instance of hmac.
 * @param irq A global IRQ ID.
 * @return The local hmac IRQ type of this irq.
 *
 * IMPORTANT This function assumes that the global IRQ belongs to the instance
 * of hmac passed in parameter. In other words, it must the case that
 * `dt->device == dt_irq_to_device(irq)`
 *
 * FIXME How should we handle errors (when the invariant above is violated)?
 */
static inline dt_hmac_irq_type_t dt_hmac_irq_type(const dt_hmac_t *dt,
                                                  dt_irq_t irq) {
  // FIXME Should check that irq >= dt->irqs[0] and irq < dt->irqs[0] +
  // kDtHmacIrqTypeCount
  return irq - dt->irqs[0];
}

#endif  // OPENTITAN_SW_DEVICE_LIB_DEVICETABLES_DT_HMAC_H_
