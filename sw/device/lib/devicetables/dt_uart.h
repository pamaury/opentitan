// Copyright lowRISC contributors.
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0
//
// Device table API auto-generated by `reggen`

#ifndef OPENTITAN_SW_DEVICE_LIB_DEVICETABLES_DT_UART_H_
#define OPENTITAN_SW_DEVICE_LIB_DEVICETABLES_DT_UART_H_

#include <stdint.h>

#include "sw/device/lib/devicetables/dt_api.h"

typedef enum {
  kDtUartRegBlockCore = 0,
  kDtUartRegBlockCount = 1,
} dt_uart_reg_block_t;

typedef enum {
  kDtUartIrqTypeTxWatermark = 0,
  kDtUartIrqTypeRxWatermark = 1,
  kDtUartIrqTypeTxDone = 2,
  kDtUartIrqTypeRxOverflow = 3,
  kDtUartIrqTypeRxFrameErr = 4,
  kDtUartIrqTypeRxBreakErr = 5,
  kDtUartIrqTypeRxTimeout = 6,
  kDtUartIrqTypeRxParityErr = 7,
  kDtUartIrqTypeTxEmpty = 8,
  kDtUartIrqTypeCount = 9,
} dt_uart_irq_type_t;

typedef enum {
  kDtUartClockClk = 0,
  kDtUartClockCount = 1,
} dt_uart_clock_t;

typedef enum {
  kDtUartPinRx = 0,
  kDtUartPinTx = 1,
  kDtUartPinCount = 2,
} dt_uart_pinctrl_t;

typedef struct dt_uart {
  dt_device_id_t device_id;
  uint32_t base_addrs[kDtUartRegBlockCount];
  uint32_t irqs[kDtUartIrqTypeCount];
  dt_clock_t clocks[kDtUartClockCount];
  dt_pin_t pins[kDtUartPinCount];
} dt_uart_t;

/**
 * Convert a global IRQ ID to a local uart IRQ type.
 *
 * @param dt Pointer to an instance of uart.
 * @param irq A global IRQ ID.
 * @return The local uart IRQ type of this irq.
 *
 * IMPORTANT This function assumes that the global IRQ belongs to the instance
 * of uart passed in parameter. In other words, it must be the case that
 * `dt->device_id == dt_irq_to_device(irq)`
 *
 * FIXME How should we handle errors (when the invariant above is violated)?
 */
static inline dt_uart_irq_type_t dt_uart_irq_type(const dt_uart_t *dt,
                                                  dt_irq_t irq) {
  // FIXME Should check that irq >= dt->irqs[0] and irq < dt->irqs[0] +
  // kDtUartIrqTypeCount
  return irq - dt->irqs[0];
}

#endif  // OPENTITAN_SW_DEVICE_LIB_DEVICETABLES_DT_UART_H_
