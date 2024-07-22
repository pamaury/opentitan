// Copyright lowRISC contributors.
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0
//
// Device table API auto-generated by `reggen`

#ifndef OPENTITAN_HW_TOP_EARLGREY_SW_AUTOGEN_DEVICETABLES_DT_FLASH_CTRL_H_
#define OPENTITAN_HW_TOP_EARLGREY_SW_AUTOGEN_DEVICETABLES_DT_FLASH_CTRL_H_

#include "sw/device/lib/devicetables/dt.h"
#include <stdint.h>

typedef enum {
  kDtFlashCtrlRegBlockCore = 0,
  kDtFlashCtrlRegBlockPrim = 1,
  kDtFlashCtrlRegBlockMem = 2,
  kDtFlashCtrlRegBlockCount = 3,
} dt_flash_ctrl_reg_block_t;

typedef enum {
  kDtFlashCtrlIrqTypeProgEmpty = 0,
  kDtFlashCtrlIrqTypeProgLvl = 1,
  kDtFlashCtrlIrqTypeRdFull = 2,
  kDtFlashCtrlIrqTypeRdLvl = 3,
  kDtFlashCtrlIrqTypeOpDone = 4,
  kDtFlashCtrlIrqTypeCorrErr = 5,
  kDtFlashCtrlIrqTypeCount = 6,
} dt_flash_ctrl_irq_type_t;

typedef enum {
  kDtFlashCtrlClockClk = 0,
  kDtFlashCtrlClockOtp = 1,
  kDtFlashCtrlClockCount = 2,
} dt_flash_ctrl_clock_t;

typedef enum {
  kDtFlashCtrlPinctrlInputTck = 0,
  kDtFlashCtrlPinctrlInputTms = 1,
  kDtFlashCtrlPinctrlInputTdi = 2,
  kDtFlashCtrlPinctrlOutputTdo = 3,
  kDtFlashCtrlPinctrlInputCount = 3,
  kDtFlashCtrlPinctrlOutputCount = 4,
} dt_flash_ctrl_pinctrl_t;

typedef struct dt_flash_ctrl {
  dt_device_t device;
  uint32_t base_addrs[kDtFlashCtrlRegBlockCount];
  uint32_t irqs[kDtFlashCtrlIrqTypeCount];
  dt_clock_t clocks[kDtFlashCtrlClockCount];
} dt_flash_ctrl_t;

/**
 * Convert a global IRQ ID to a local flash_ctrl IRQ type.
 *
 * @param dt Pointer to an instance of flash_ctrl.
 * @param irq A global IRQ ID.
 * @return The local flash_ctrl IRQ type of this irq.
 *
 * IMPORTANT This function assumes that the global IRQ belongs to the instance
 * of flash_ctrl passed in parameter. In other words, it must the case that
 * `dt->device == dt_irq_to_device(irq)`
 *
 * FIXME How should we handle errors (when the invariant above is violated)?
 */
static inline dt_flash_ctrl_irq_type_t dt_flash_ctrl_irq_type(
    dt_flash_ctrl_t *dt,
    dt_irq_t irq) {
  // FIXME Should check that irq >= dt->irqs[0] and irq < dt->irqs[0] + kDtFlashCtrlIrqTypeCount
  return irq - dt->irqs[0];
}

#endif  // OPENTITAN_HW_TOP_EARLGREY_SW_AUTOGEN_DEVICETABLES_DT_FLASH_CTRL_H_
