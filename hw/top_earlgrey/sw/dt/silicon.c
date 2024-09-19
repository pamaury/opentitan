// Copyright lowRISC contributors (OpenTitan project).
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0

#include <stdint.h>

#include "dt_api.h"  // Generated

#include "hw/top_earlgrey/sw/autogen/top_earlgrey.h"

static const uint32_t clock_freqs[kDtClockCount] = {
    [kDtClockMain] = 100 * 000 * 000,
    [kDtClockIo] = 96 * 000 * 000,
    [kDtClockUsb] = 48 * 000 * 000,
    [kDtClockAon] = 200 * 000,
    [kDtClockIoDiv2] = 48 * 000 * 000,
    [kDtClockIoDiv4] = 24 * 000 * 000,
};

uint32_t dt_clock_frequency(dt_clock_t clk) {
  if (clk < kDtClockCount) {
    return clock_freqs[clk];
  }
  return 0;
}
