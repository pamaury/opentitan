// Copyright lowRISC contributors.
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0
//
// Device table API auto-generated by `reggen`
<%
    from topgen.lib import Name

    def snake_to_enum(s):
        return Name.from_snake_case(s).as_c_enum()
    device_name = block.name

    inouts, inputs, outputs = block.xputs
    device_pins = {"in": [], "inout": [], "out": []}
    for sig in inputs:
        if sig.bits.width() > 1:
            for bit in range(sig.bits.width()):
                device_pins["in"].append(sig.name + str(bit))
        else:
            device_pins["in"].append(sig.name)
    for sig in inouts:
        if sig.bits.width() > 1:
            for bit in range(sig.bits.width()):
                device_pins["inout"].append(sig.name + str(bit))
        else:
            device_pins["inout"].append(sig.name)
    for sig in outputs:
        if sig.bits.width() > 1:
            for bit in range(sig.bits.width()):
                device_pins["out"].append(sig.name + str(bit))
        else:
            device_pins["out"].append(sig.name)
    input_count = len(device_pins["in"])
    inout_count = len(device_pins["inout"])
    output_count = len(device_pins["out"])

    device_irqs = []
    for sig in block.interrupts:
        if sig.bits.width() > 1:
            for bit in range(sig.bits.width()):
                device_irqs.append(sig.name + str(bit))
        else:
            device_irqs.append(sig.name)

    device_reg_blocks = []
    for rb in block.reg_blocks.keys():
        if rb is None:
            device_reg_blocks.append("core")
        else:
            device_reg_blocks.append(rb)

    device_clocks = []
    for clk in block.clocking.items:
        if clk.internal or clk.clock is None:
            continue
        if clk.clock_base_name == "":
            if clk.clock != "scan_clk_i":
                device_clocks.append("clk")
        else:
            device_clocks.append(clk.clock_base_name)
%>\

#ifndef ${include_guard}
#define ${include_guard}

#include "sw/device/lib/devicetables/dt_api.h"
#include <stdint.h>

## List of register blocks.
typedef enum {
% for idx, rb in enumerate(device_reg_blocks):
  ${snake_to_enum(f"dt_{device_name}_reg_block_{rb}")} = ${str(idx)},
% endfor
  ${snake_to_enum(f"dt_{device_name}_reg_block_count")} = ${str(len(device_reg_blocks))},
} dt_${device_name}_reg_block_t;

## List of IRQs.
% if len(device_irqs) > 0:
typedef enum {
%   for idx, irq in enumerate(device_irqs):
  ${snake_to_enum(f"dt_{device_name}_irq_type_{irq}")} = ${str(idx)},
%   endfor
  ${snake_to_enum(f"dt_{device_name}_irq_type_count")} = ${str(len(device_irqs))},
} dt_${device_name}_irq_type_t;

% endif
## List of clocks.
% if len(device_clocks) > 0:
typedef enum {
% for idx, clk in enumerate(device_clocks):
  ${snake_to_enum(f"dt_{device_name}_clock_{clk}")} = ${str(idx)},
% endfor
  ${snake_to_enum(f"dt_{device_name}_clock_count")} = ${str(len(device_clocks))},
} dt_${device_name}_clock_t;

% endif
## List of pins.
typedef enum {
% for idx, pin in enumerate(device_pins["in"]):
  ${snake_to_enum(f"dt_{device_name}_pinctrl_input_{pin}")} = ${str(idx)},
% endfor
% for idx, pin in enumerate(device_pins["inout"]):
  ${snake_to_enum(f"dt_{device_name}_pinctrl_inout_{pin}")} = ${str(idx + input_count)},
% endfor
% for idx, pin in enumerate(device_pins["out"]):
  ${snake_to_enum(f"dt_{device_name}_pinctrl_output_{pin}")} = ${str(idx + input_count + inout_count)},
% endfor
  ${snake_to_enum(f"dt_{device_name}_pinctrl_input_count")} = ${str(input_count + inout_count)},
  ${snake_to_enum(f"dt_{device_name}_pinctrl_output_count")} = ${str(input_count + inout_count + output_count)},
} dt_${device_name}_pinctrl_t;

## DT structure.
typedef struct dt_${device_name} {
  dt_device_id_t device_id;
  uint32_t base_addrs[${snake_to_enum(f"dt_{device_name}_reg_block_count")}];
% if len(device_irqs) > 0:
  uint32_t irqs[${snake_to_enum(f"dt_{device_name}_irq_type_count")}];
% endif
  dt_clock_t clocks[${snake_to_enum(f"dt_{device_name}_clock_count")}];
} dt_${device_name}_t;

% if len(device_irqs) > 0:
/**
 * Convert a global IRQ ID to a local ${device_name} IRQ type.
 *
 * @param dt Pointer to an instance of ${device_name}.
 * @param irq A global IRQ ID.
 * @return The local ${device_name} IRQ type of this irq.
 *
 * IMPORTANT This function assumes that the global IRQ belongs to the instance
 * of ${device_name} passed in parameter. In other words, it must be the case that
 * `dt->device_id == dt_irq_to_device(irq)`
 *
 * FIXME How should we handle errors (when the invariant above is violated)?
 */
static inline dt_${device_name}_irq_type_t dt_${device_name}_irq_type(
    const dt_${device_name}_t *dt,
    dt_irq_t irq) {
  // FIXME Should check that irq >= dt->irqs[0] and irq < dt->irqs[0] + ${snake_to_enum(f"dt_{device_name}_irq_type_count")}
  return irq - dt->irqs[0];
}

%endif
#endif  // ${include_guard}
