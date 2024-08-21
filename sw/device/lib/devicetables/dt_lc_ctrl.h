// Copyright lowRISC contributors.
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0
//
// Device table API auto-generated by `reggen`

#ifndef OPENTITAN_SW_DEVICE_LIB_DEVICETABLES_DT_LC_CTRL_H_
#define OPENTITAN_SW_DEVICE_LIB_DEVICETABLES_DT_LC_CTRL_H_

#include <stdint.h>

#include "sw/device/lib/devicetables/dt_api.h"

typedef enum {
  kDtLcCtrlRegBlockCore = 0,
  kDtLcCtrlRegBlockCount = 1,
} dt_lc_ctrl_reg_block_t;

typedef enum {
  kDtLcCtrlClockClk = 0,
  kDtLcCtrlClockKmac = 1,
  kDtLcCtrlClockCount = 2,
} dt_lc_ctrl_clock_t;

typedef enum {
  kDtLcCtrlPinctrlInputCount = 0,
  kDtLcCtrlPinctrlOutputCount = 0,
} dt_lc_ctrl_pinctrl_t;

typedef struct dt_lc_ctrl {
  dt_device_id_t device_id;
  uint32_t base_addrs[kDtLcCtrlRegBlockCount];
  dt_clock_t clocks[kDtLcCtrlClockCount];
} dt_lc_ctrl_t;

#endif  // OPENTITAN_SW_DEVICE_LIB_DEVICETABLES_DT_LC_CTRL_H_
