// Copyright lowRISC contributors (OpenTitan project).
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0

// THIS FILE HAS BEEN GENERATED, DO NOT EDIT MANUALLY. COMMAND:
// util/autogen_testutils.py

#include "sw/device/lib/testing/autogen/isr_testutils.h"

#include "sw/device/lib/dif/dif_aon_timer.h"
#include "sw/device/lib/dif/dif_base.h"
#include "sw/device/lib/dif/dif_rv_plic.h"
#include "sw/device/lib/testing/test_framework/check.h"

#include "hw/top_earlgrey/sw/autogen/top_earlgrey.h"  // Generated.

void isr_testutils_aon_timer_isr(
    plic_isr_ctx_t plic_ctx, aon_timer_isr_ctx_t aon_timer_ctx,
    top_earlgrey_plic_peripheral_t *peripheral_serviced,
    dif_aon_timer_irq_t *irq_serviced) {
  // Claim the IRQ at the PLIC.
  dif_rv_plic_irq_id_t plic_irq_id;
  CHECK_DIF_OK(
      dif_rv_plic_irq_claim(plic_ctx.rv_plic, plic_ctx.hart_id, &plic_irq_id));

  // Get the peripheral the IRQ belongs to.
  *peripheral_serviced = (top_earlgrey_plic_peripheral_t)
      top_earlgrey_plic_interrupt_for_peripheral[plic_irq_id];

  // Get the IRQ that was fired from the PLIC IRQ ID.
  dif_aon_timer_irq_t irq =
      (dif_aon_timer_irq_t)(plic_irq_id -
                            aon_timer_ctx.plic_aon_timer_start_irq_id);
  *irq_serviced = irq;

  // Check if it is supposed to be the only IRQ fired.
  if (aon_timer_ctx.is_only_irq) {
    dif_aon_timer_irq_state_snapshot_t snapshot;
    CHECK_DIF_OK(
        dif_aon_timer_irq_get_state(aon_timer_ctx.aon_timer, &snapshot));
    CHECK(snapshot == (dif_aon_timer_irq_state_snapshot_t)(1 << irq),
          "Only aon_timer IRQ %d expected to fire. Actual IRQ state = %x", irq,
          snapshot);
  }

  // Acknowledge the IRQ at the peripheral if IRQ is of the event type.
  dif_irq_type_t type;
  CHECK_DIF_OK(dif_aon_timer_irq_get_type(aon_timer_ctx.aon_timer, irq, &type));
  if (type == kDifIrqTypeEvent) {
    CHECK_DIF_OK(dif_aon_timer_irq_acknowledge(aon_timer_ctx.aon_timer, irq));
  }

  // Complete the IRQ at the PLIC.
  CHECK_DIF_OK(dif_rv_plic_irq_complete(plic_ctx.rv_plic, plic_ctx.hart_id,
                                        plic_irq_id));
}
