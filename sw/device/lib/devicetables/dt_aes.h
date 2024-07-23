// Copyright lowRISC contributors.
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0
//
// Device table API auto-generated by `reggen`

#ifndef OPENTITAN_SW_DEVICE_LIB_DEVICETABLES_DT_AES_H_
#define OPENTITAN_SW_DEVICE_LIB_DEVICETABLES_DT_AES_H_

#include <stdint.h>

#include "sw/device/lib/devicetables/dt.h"

typedef enum {
  kDtAesRegBlockCore = 0,
  kDtAesRegBlockCount = 1,
} dt_aes_reg_block_t;

typedef enum {
  kDtAesClockClk = 0,
  kDtAesClockEdn = 1,
  kDtAesClockCount = 2,
} dt_aes_clock_t;

typedef enum {
  kDtAesPinctrlInputCount = 0,
  kDtAesPinctrlOutputCount = 0,
} dt_aes_pinctrl_t;

typedef struct dt_aes {
  dt_device_id_t device_id;
  uint32_t base_addrs[kDtAesRegBlockCount];
  dt_clock_t clocks[kDtAesClockCount];
} dt_aes_t;

#endif  // OPENTITAN_SW_DEVICE_LIB_DEVICETABLES_DT_AES_H_
