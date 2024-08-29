// Copyright lowRISC contributors.
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0
//
// Device table API auto-generated by `reggen`

#ifndef OPENTITAN_SW_DEVICE_LIB_DEVICETABLES_DT_SPI_DEVICE_H_
#define OPENTITAN_SW_DEVICE_LIB_DEVICETABLES_DT_SPI_DEVICE_H_

#include <stdint.h>

#include "sw/device/lib/devicetables/dt_api.h"

typedef enum {
  kDtSpiDeviceRegBlockCore = 0,
  kDtSpiDeviceRegBlockCount = 1,
} dt_spi_device_reg_block_t;

typedef enum {
  kDtSpiDeviceIrqTypeUploadCmdfifoNotEmpty = 0,
  kDtSpiDeviceIrqTypeUploadPayloadNotEmpty = 1,
  kDtSpiDeviceIrqTypeUploadPayloadOverflow = 2,
  kDtSpiDeviceIrqTypeReadbufWatermark = 3,
  kDtSpiDeviceIrqTypeReadbufFlip = 4,
  kDtSpiDeviceIrqTypeTpmHeaderNotEmpty = 5,
  kDtSpiDeviceIrqTypeTpmRdfifoCmdEnd = 6,
  kDtSpiDeviceIrqTypeTpmRdfifoDrop = 7,
  kDtSpiDeviceIrqTypeCount = 8,
} dt_spi_device_irq_type_t;

typedef enum {
  kDtSpiDeviceClockClk = 0,
  kDtSpiDeviceClockCount = 1,
} dt_spi_device_clock_t;

typedef enum {
  kDtSpiDevicePinSck = 0,
  kDtSpiDevicePinCsb = 1,
  kDtSpiDevicePinTpmCsb = 2,
  kDtSpiDevicePinSd0 = 3,
  kDtSpiDevicePinSd1 = 4,
  kDtSpiDevicePinSd2 = 5,
  kDtSpiDevicePinSd3 = 6,
  kDtSpiDevicePinCount = 7,
} dt_spi_device_pinctrl_t;

typedef struct dt_spi_device {
  dt_device_id_t device_id;
  uint32_t base_addrs[kDtSpiDeviceRegBlockCount];
  uint32_t irqs[kDtSpiDeviceIrqTypeCount];
  dt_clock_t clocks[kDtSpiDeviceClockCount];
  dt_pin_t pins[kDtSpiDevicePinCount];
} dt_spi_device_t;

/**
 * Convert a global IRQ ID to a local spi_device IRQ type.
 *
 * @param dt Pointer to an instance of spi_device.
 * @param irq A global IRQ ID.
 * @return The local spi_device IRQ type of this irq.
 *
 * IMPORTANT This function assumes that the global IRQ belongs to the instance
 * of spi_device passed in parameter. In other words, it must be the case that
 * `dt->device_id == dt_irq_to_device(irq)`
 *
 * FIXME How should we handle errors (when the invariant above is violated)?
 */
static inline dt_spi_device_irq_type_t dt_spi_device_irq_type(
    const dt_spi_device_t *dt, dt_irq_t irq) {
  // FIXME Should check that irq >= dt->irqs[0] and irq < dt->irqs[0] +
  // kDtSpiDeviceIrqTypeCount
  return irq - dt->irqs[0];
}

#endif  // OPENTITAN_SW_DEVICE_LIB_DEVICETABLES_DT_SPI_DEVICE_H_
