// Copyright lowRISC contributors.
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0

#ifndef OPENTITAN_SW_DEVICE_LIB_DEVICETABLES_DT_H_
#define OPENTITAN_SW_DEVICE_LIB_DEVICETABLES_DT_H_

#include <stdbool.h>
#include <stdint.h>

// An ID representing a particular device, with `kDtDeviceUnknown` reserved for "unknown."
typedef uint32_t dt_device_t;
// An ID representing a clock, with `kDtClockUnknown` reserved for "unknown."
typedef uint32_t dt_clock_t;

enum {
  kDtDeviceUnknown = 0,
  kDtClockUnknown = 0,
  kDtIrqUnknown = 0,
};

/**
 * Get the requesting device corresponding to the given global IRQ ID.
 */
extern dt_device_t dt_irq_to_device(uint32_t irq);

/**
 * Convert a global IRQ ID to a device-specific IRQ type that can be casted
 * to a `dt_<block>_irq_type_t`.
 *
 * For example, `kTopEarlgreyPlicIrqIdUart0TxWatermark` will be converted to
 * `kDtUartIrqTypeTxWatermark` that can be casted to a `dt_uart_irq_type_t`.
 */
extern uint32_t dt_irq_to_device_irq(uint32_t irq);

/**
 * Returns the clock frequency of the specified clock in Hz.
 */
extern uint32_t dt_clock_frequency(dt_clock_t clk);

#endif  // OPENTITAN_SW_DEVICE_LIB_DEVICETABLES_DT_H_
