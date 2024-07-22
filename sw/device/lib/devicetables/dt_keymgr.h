// Copyright lowRISC contributors.
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0
//
// Device table API auto-generated by `reggen`

#ifndef OPENTITAN_SW_DEVICE_LIB_DEVICETABLES_DT_KEYMGR_H_
#define OPENTITAN_SW_DEVICE_LIB_DEVICETABLES_DT_KEYMGR_H_

#include <stdint.h>

#include "sw/device/lib/devicetables/dt.h"

typedef enum {
  kDtKeymgrRegBlockCore = 0,
  kDtKeymgrRegBlockCount = 1,
} dt_keymgr_reg_block_t;

typedef enum {
  kDtKeymgrIrqTypeOpDone = 0,
  kDtKeymgrIrqTypeCount = 1,
} dt_keymgr_irq_type_t;

typedef enum {
  kDtKeymgrClockClk = 0,
  kDtKeymgrClockEdn = 1,
  kDtKeymgrClockCount = 2,
} dt_keymgr_clock_t;

typedef enum {
  kDtKeymgrPinctrlInputCount = 0,
  kDtKeymgrPinctrlOutputCount = 0,
} dt_keymgr_pinctrl_t;

typedef struct dt_keymgr {
  dt_device_t device;
  uint32_t base_addrs[kDtKeymgrRegBlockCount];
  uint32_t irqs[kDtKeymgrIrqTypeCount];
  dt_clock_t clocks[kDtKeymgrClockCount];
} dt_keymgr_t;

/**
 * Convert a global IRQ ID to a local keymgr IRQ type.
 *
 * @param dt Pointer to an instance of keymgr.
 * @param irq A global IRQ ID.
 * @return The local keymgr IRQ type of this irq.
 *
 * IMPORTANT This function assumes that the global IRQ belongs to the instance
 * of keymgr passed in parameter. In other words, it must the case that
 * `dt->device == dt_irq_to_device(irq)`
 *
 * FIXME How should we handle errors (when the invariant above is violated)?
 */
static inline dt_keymgr_irq_type_t dt_keymgr_irq_type(const dt_keymgr_t *dt,
                                                      dt_irq_t irq) {
  // FIXME Should check that irq >= dt->irqs[0] and irq < dt->irqs[0] +
  // kDtKeymgrIrqTypeCount
  return irq - dt->irqs[0];
}

#endif  // OPENTITAN_SW_DEVICE_LIB_DEVICETABLES_DT_KEYMGR_H_
