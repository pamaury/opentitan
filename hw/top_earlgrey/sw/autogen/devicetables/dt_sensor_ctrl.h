// Copyright lowRISC contributors.
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0
//
// Device table API auto-generated by `reggen`

#ifndef OPENTITAN_HW_TOP_EARLGREY_SW_AUTOGEN_DEVICETABLES_DT_SENSOR_CTRL_H_
#define OPENTITAN_HW_TOP_EARLGREY_SW_AUTOGEN_DEVICETABLES_DT_SENSOR_CTRL_H_

#include "sw/device/lib/devicetables/dt.h"
#include <stdint.h>

typedef enum {
  kDtSensorCtrlRegBlockCore = 0,
  kDtSensorCtrlRegBlockCount = 1,
} dt_sensor_ctrl_reg_block_t;

typedef enum {
  kDtSensorCtrlIrqTypeIoStatusChange = 0,
  kDtSensorCtrlIrqTypeInitStatusChange = 1,
  kDtSensorCtrlIrqTypeCount = 2,
} dt_sensor_ctrl_irq_type_t;

typedef enum {
  kDtSensorCtrlClockClk = 0,
  kDtSensorCtrlClockAon = 1,
  kDtSensorCtrlClockCount = 2,
} dt_sensor_ctrl_clock_t;

typedef enum {
  kDtSensorCtrlPinctrlOutputAstDebugOut0 = 0,
  kDtSensorCtrlPinctrlOutputAstDebugOut1 = 1,
  kDtSensorCtrlPinctrlOutputAstDebugOut2 = 2,
  kDtSensorCtrlPinctrlOutputAstDebugOut3 = 3,
  kDtSensorCtrlPinctrlOutputAstDebugOut4 = 4,
  kDtSensorCtrlPinctrlOutputAstDebugOut5 = 5,
  kDtSensorCtrlPinctrlOutputAstDebugOut6 = 6,
  kDtSensorCtrlPinctrlOutputAstDebugOut7 = 7,
  kDtSensorCtrlPinctrlOutputAstDebugOut8 = 8,
  kDtSensorCtrlPinctrlInputCount = 0,
  kDtSensorCtrlPinctrlOutputCount = 9,
} dt_sensor_ctrl_pinctrl_t;

typedef struct dt_sensor_ctrl {
  dt_device_t device;
  uint32_t base_addrs[kDtSensorCtrlRegBlockCount];
  uint32_t irqs[kDtSensorCtrlIrqTypeCount];
  dt_clock_t clocks[kDtSensorCtrlClockCount];
} dt_sensor_ctrl_t;

#endif  // OPENTITAN_HW_TOP_EARLGREY_SW_AUTOGEN_DEVICETABLES_DT_SENSOR_CTRL_H_
