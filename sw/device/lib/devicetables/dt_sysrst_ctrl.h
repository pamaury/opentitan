// Copyright lowRISC contributors.
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0
//
// Device table API auto-generated by `reggen`

#ifndef OPENTITAN_SW_DEVICE_LIB_DEVICETABLES_DT_SYSRST_CTRL_H_
#define OPENTITAN_SW_DEVICE_LIB_DEVICETABLES_DT_SYSRST_CTRL_H_

#include <stdint.h>

#include "sw/device/lib/devicetables/dt_api.h"

typedef enum {
  kDtSysrstCtrlRegBlockCore = 0,
  kDtSysrstCtrlRegBlockCount = 1,
} dt_sysrst_ctrl_reg_block_t;

typedef enum {
  kDtSysrstCtrlIrqTypeEventDetected = 0,
  kDtSysrstCtrlIrqTypeCount = 1,
} dt_sysrst_ctrl_irq_type_t;

typedef enum {
  kDtSysrstCtrlClockClk = 0,
  kDtSysrstCtrlClockAon = 1,
  kDtSysrstCtrlClockCount = 2,
} dt_sysrst_ctrl_clock_t;

typedef enum {
  kDtSysrstCtrlPinctrlInputAcPresent = 0,
  kDtSysrstCtrlPinctrlInputKey0In = 1,
  kDtSysrstCtrlPinctrlInputKey1In = 2,
  kDtSysrstCtrlPinctrlInputKey2In = 3,
  kDtSysrstCtrlPinctrlInputPwrbIn = 4,
  kDtSysrstCtrlPinctrlInputLidOpen = 5,
  kDtSysrstCtrlPinctrlInoutEcRstL = 6,
  kDtSysrstCtrlPinctrlInoutFlashWpL = 7,
  kDtSysrstCtrlPinctrlOutputBatDisable = 8,
  kDtSysrstCtrlPinctrlOutputKey0Out = 9,
  kDtSysrstCtrlPinctrlOutputKey1Out = 10,
  kDtSysrstCtrlPinctrlOutputKey2Out = 11,
  kDtSysrstCtrlPinctrlOutputPwrbOut = 12,
  kDtSysrstCtrlPinctrlOutputZ3Wakeup = 13,
  kDtSysrstCtrlPinctrlInputCount = 8,
  kDtSysrstCtrlPinctrlOutputCount = 14,
} dt_sysrst_ctrl_pinctrl_t;

typedef struct dt_sysrst_ctrl {
  dt_device_id_t device_id;
  uint32_t base_addrs[kDtSysrstCtrlRegBlockCount];
  uint32_t irqs[kDtSysrstCtrlIrqTypeCount];
  dt_clock_t clocks[kDtSysrstCtrlClockCount];
} dt_sysrst_ctrl_t;

/**
 * Convert a global IRQ ID to a local sysrst_ctrl IRQ type.
 *
 * @param dt Pointer to an instance of sysrst_ctrl.
 * @param irq A global IRQ ID.
 * @return The local sysrst_ctrl IRQ type of this irq.
 *
 * IMPORTANT This function assumes that the global IRQ belongs to the instance
 * of sysrst_ctrl passed in parameter. In other words, it must be the case that
 * `dt->device_id == dt_irq_to_device(irq)`
 *
 * FIXME How should we handle errors (when the invariant above is violated)?
 */
static inline dt_sysrst_ctrl_irq_type_t dt_sysrst_ctrl_irq_type(
    const dt_sysrst_ctrl_t *dt, dt_irq_t irq) {
  // FIXME Should check that irq >= dt->irqs[0] and irq < dt->irqs[0] +
  // kDtSysrstCtrlIrqTypeCount
  return irq - dt->irqs[0];
}

#endif  // OPENTITAN_SW_DEVICE_LIB_DEVICETABLES_DT_SYSRST_CTRL_H_
