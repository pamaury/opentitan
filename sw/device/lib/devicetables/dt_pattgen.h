// Copyright lowRISC contributors.
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0
//
// Device table API auto-generated by `reggen`

#ifndef OPENTITAN_SW_DEVICE_LIB_DEVICETABLES_DT_PATTGEN_H_
#define OPENTITAN_SW_DEVICE_LIB_DEVICETABLES_DT_PATTGEN_H_

#include <stdint.h>

#include "sw/device/lib/devicetables/dt.h"

typedef enum {
  kDtPattgenRegBlockCore = 0,
  kDtPattgenRegBlockCount = 1,
} dt_pattgen_reg_block_t;

typedef enum {
  kDtPattgenIrqTypeDoneCh0 = 0,
  kDtPattgenIrqTypeDoneCh1 = 1,
  kDtPattgenIrqTypeCount = 2,
} dt_pattgen_irq_type_t;

typedef enum {
  kDtPattgenClockClk = 0,
  kDtPattgenClockCount = 1,
} dt_pattgen_clock_t;

typedef enum {
  kDtPattgenPinctrlOutputPda0Tx = 0,
  kDtPattgenPinctrlOutputPcl0Tx = 1,
  kDtPattgenPinctrlOutputPda1Tx = 2,
  kDtPattgenPinctrlOutputPcl1Tx = 3,
  kDtPattgenPinctrlInputCount = 0,
  kDtPattgenPinctrlOutputCount = 4,
} dt_pattgen_pinctrl_t;

typedef struct dt_pattgen {
  dt_device_t device;
  uint32_t base_addrs[kDtPattgenRegBlockCount];
  uint32_t irqs[kDtPattgenIrqTypeCount];
  dt_clock_t clocks[kDtPattgenClockCount];
} dt_pattgen_t;

#endif  // OPENTITAN_SW_DEVICE_LIB_DEVICETABLES_DT_PATTGEN_H_
