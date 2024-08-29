// Copyright lowRISC contributors.
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0
//
// Device table API auto-generated by `reggen`

#ifndef OPENTITAN_HW_TOP_EARLGREY_SW_AUTOGEN_DEVICETABLES_DT_RSTMGR_H_
#define OPENTITAN_HW_TOP_EARLGREY_SW_AUTOGEN_DEVICETABLES_DT_RSTMGR_H_

#include "sw/device/lib/devicetables/dt_api.h"
#include <stdint.h>

typedef enum {
  kDtRstmgrRegBlockCore = 0,
  kDtRstmgrRegBlockCount = 1,
} dt_rstmgr_reg_block_t;

typedef enum {
  kDtRstmgrClockClk = 0,
  kDtRstmgrClockAon = 1,
  kDtRstmgrClockIoDiv4 = 2,
  kDtRstmgrClockMain = 3,
  kDtRstmgrClockIo = 4,
  kDtRstmgrClockIoDiv2 = 5,
  kDtRstmgrClockUsb = 6,
  kDtRstmgrClockPor = 7,
  kDtRstmgrClockCount = 8,
} dt_rstmgr_clock_t;

typedef struct dt_rstmgr {
  dt_device_id_t device_id;
  uint32_t base_addrs[kDtRstmgrRegBlockCount];
  dt_clock_t clocks[kDtRstmgrClockCount];
} dt_rstmgr_t;

#endif  // OPENTITAN_HW_TOP_EARLGREY_SW_AUTOGEN_DEVICETABLES_DT_RSTMGR_H_
