// Copyright lowRISC contributors.
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0
//
// Device table API auto-generated by `reggen`

#ifndef OPENTITAN_SW_DEVICE_LIB_DEVICETABLES_DT_KMAC_H_
#define OPENTITAN_SW_DEVICE_LIB_DEVICETABLES_DT_KMAC_H_

#include <stdint.h>

#include "sw/device/lib/devicetables/dt_api.h"

typedef enum {
  kDtKmacRegBlockCore = 0,
  kDtKmacRegBlockCount = 1,
} dt_kmac_reg_block_t;

typedef enum {
  kDtKmacIrqTypeKmacDone = 0,
  kDtKmacIrqTypeFifoEmpty = 1,
  kDtKmacIrqTypeKmacErr = 2,
  kDtKmacIrqTypeCount = 3,
} dt_kmac_irq_type_t;

typedef enum {
  kDtKmacClockClk = 0,
  kDtKmacClockEdn = 1,
  kDtKmacClockCount = 2,
} dt_kmac_clock_t;

typedef struct dt_kmac {
  dt_device_id_t device_id;
  uint32_t base_addrs[kDtKmacRegBlockCount];
  uint32_t irqs[kDtKmacIrqTypeCount];
  dt_clock_t clocks[kDtKmacClockCount];
} dt_kmac_t;

/**
 * Convert a global IRQ ID to a local kmac IRQ type.
 *
 * @param dt Pointer to an instance of kmac.
 * @param irq A global IRQ ID.
 * @return The local kmac IRQ type of this irq.
 *
 * IMPORTANT This function assumes that the global IRQ belongs to the instance
 * of kmac passed in parameter. In other words, it must be the case that
 * `dt->device_id == dt_irq_to_device(irq)`
 *
 * FIXME How should we handle errors (when the invariant above is violated)?
 */
static inline dt_kmac_irq_type_t dt_kmac_irq_type(const dt_kmac_t *dt,
                                                  dt_irq_t irq) {
  // FIXME Should check that irq >= dt->irqs[0] and irq < dt->irqs[0] +
  // kDtKmacIrqTypeCount
  return irq - dt->irqs[0];
}

#endif  // OPENTITAN_SW_DEVICE_LIB_DEVICETABLES_DT_KMAC_H_
