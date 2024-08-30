// Copyright lowRISC contributors.
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0
//
// Device table API auto-generated by `reggen`

#ifndef OPENTITAN_SW_DEVICE_LIB_DEVICETABLES_DT_HMAC_H_
#define OPENTITAN_SW_DEVICE_LIB_DEVICETABLES_DT_HMAC_H_

#include <stdint.h>

#include "sw/device/lib/devicetables/dt_api.h"

typedef enum {
  kDtHmacRegBlockCore = 0,
  kDtHmacRegBlockCount = 1,
} dt_hmac_reg_block_t;

typedef enum {
  kDtHmacIrqTypeHmacDone = 0,
  kDtHmacIrqTypeFifoEmpty = 1,
  kDtHmacIrqTypeHmacErr = 2,
  kDtHmacIrqTypeCount = 3,
} dt_hmac_irq_type_t;

typedef enum {
  kDtHmacClockClk = 0,
  kDtHmacClockCount = 1,
} dt_hmac_clock_t;

typedef struct dt_hmac {
  struct {
    dt_device_id_t device_id;
    uint32_t base_addrs[kDtHmacRegBlockCount];
    dt_irq_t irqs[kDtHmacIrqTypeCount];
    dt_clock_t clocks[kDtHmacClockCount];
  } __internal;
} dt_hmac_t;

/**
 * Get the device ID of an instance.
 *
 * @param dt Pointer to an instance of hmac.
 * @return The device ID of that instance.
 */
static inline dt_device_id_t dt_hmac_device_id(const dt_hmac_t *dt) {
  return dt->__internal.device_id;
}

/**
 * Get the register base address of an instance.
 *
 * @param dt Pointer to an instance of hmac.
 * @param reg_block The register block requested.
 * @return The register base address of the requested block.
 */
static inline uint32_t dt_hmac_reg_block(const dt_hmac_t *dt,
                                         dt_hmac_reg_block_t reg_block) {
  return dt->__internal.base_addrs[reg_block];
}

/**
 * Get the global IRQ ID of a local hmac IRQ type for a given instance.
 *
 * @param dt Pointer to an instance of hmac.
 * @param irq_type A local hmac IRQ type.
 * @return A global IRQ ID that corresponds to the local IRQ type of this
 * instance.
 */
static inline dt_irq_t dt_hmac_irq_id(const dt_hmac_t *dt,
                                      dt_hmac_irq_type_t irq_type) {
  return dt->__internal.irqs[irq_type];
}

/**
 * Convert a global IRQ ID to a local hmac IRQ type.
 *
 * @param dt Pointer to an instance of hmac.
 * @param irq A global IRQ ID that belongs to this instance.
 * @return The local hmac IRQ type, or `kDtHmacIrqTypeCount`.
 *
 * NOTE This function assumes that the global IRQ belongs to the instance
 * of hmac passed in parameter. In other words, it must be the case that
 * `dt->device_id == dt_irq_to_device(irq)`. Otherwise, this function will
 * return `kDtHmacIrqTypeCount`.
 */
static inline dt_hmac_irq_type_t dt_hmac_irq_type(const dt_hmac_t *dt,
                                                  dt_irq_t irq) {
  dt_hmac_irq_type_t count = kDtHmacIrqTypeCount;
  if (irq < dt->__internal.irqs[0] ||
      irq >= dt->__internal.irqs[0] + (dt_irq_t)count) {
    return count;
  }
  return irq - dt->__internal.irqs[0];
}

#endif  // OPENTITAN_SW_DEVICE_LIB_DEVICETABLES_DT_HMAC_H_
