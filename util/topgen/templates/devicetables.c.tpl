// Copyright lowRISC contributors.
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0
//
${gencmd}
<%
from topgen.lib import Name, is_top_reggen, is_ipgen

module_types = {m["type"] for m in top["module"]}
module_types = sorted(module_types)
top_reggen_module_types = {m["type"] for m in top["module"] if is_top_reggen(m)}
ipgen_module_types = {m["type"] for m in top["module"] if is_ipgen(m)}
top_name = Name(["top", top["name"]])
irq_base_name = top_name + Name(["plic", "irq", "id"])
top_clock_prefix = top_name + Name(["clock", "src"])

def snake_to_constant_name(s):
    return Name.from_snake_case(s).as_c_enum()
%>\


#include "hw/top_${top["name"]}/sw/autogen/devicetables.h"
#include "hw/top_${top["name"]}/sw/autogen/top_${top["name"]}.h"
#include <stdint.h>

% for module_name in module_types:
// Device tables for ${module_name}
<%
    modules = [m for m in top["module"] if m["type"] == module_name]
    block = name_to_block[module_name]
    reg_count_enum = Name.from_snake_case(
        "dt_{}_reg_block_count".format(module_name)
    ).as_c_enum()
    clk_count_enum = Name.from_snake_case(
        "dt_{}_clock_count".format(module_name)
    ).as_c_enum()
    irq_count_enum = Name.from_snake_case(
        "dt_{}_irq_type_count".format(module_name)
    ).as_c_enum()
    reg_count = len(block.reg_blocks)
    irq_count = 0
    for irq in block.interrupts:
      irq_count += irq.bits.width()
    irqs = {}
    for m in modules:
      irqs_packed = [irq
        for irq in top["interrupt"] if irq["module_name"] == m["name"]]
      irqs[m["name"]] = []
      for irq in irqs_packed:
        irq_name = irq_base_name + Name.from_snake_case(irq["name"])
        irq_width = int(irq["width"])
        if irq_width > 1:
          for i in range(irq_width):
            irqs[m["name"]].append(irq_name + Name([str(i)]))
        else:
          irqs[m["name"]].append(irq_name)
    block_clock_prefix = Name.from_snake_case(f"dt_{module_name}_clock")
    block_clocks = {}
    for clock in block.clocking.items:
        if clock.internal or clock.clock == None or clock.clock == "scan_clk_i":
            continue
        if clock.clock_base_name == "":
            block_clock = block_clock_prefix + Name(["clk"])
        else:
            block_clock = (block_clock_prefix +
                           Name.from_snake_case(clock.clock_base_name))
        block_clocks[clock.clock] = block_clock
    clk_count = len(block_clocks.keys())
%>\
%   if reg_count > 0:
_Static_assert(${reg_count_enum} == ${str(reg_count)}, "Reg block count mismatch");
%   endif
%   if clk_count > 0:
_Static_assert(${clk_count_enum} == ${str(clk_count)}, "Clock count mismatch");
%   endif
%   if irq_count > 0:
_Static_assert(${irq_count_enum} == ${str(irq_count)}, "IRQ count mismatch");
%   endif
_Static_assert(${snake_to_constant_name("dt_" + module_name)}Count == ${len(modules)}, "Number of ${module_name} modules mismatch");

const dt_${module_name}_t ${snake_to_constant_name("dt_" + module_name)}[${snake_to_constant_name("dt_" + module_name)}Count] = {
%   for (dev_index, m) in enumerate(modules):
  // Properties for ${m["name"]}
  {
    .device_id = ${snake_to_constant_name("dt_device_id_" + m["name"])},
    .base_addrs = {
%     for addr in m["base_addrs"].values():
      ${addr},
%     endfor
    },
    .clocks = {
%     for port, clock in m["clock_srcs"].items():
%       if port in block_clocks:
<%
        if type(clock) is str:
            clock_id = top_clock_prefix + Name.from_snake_case(clock)
        else:
            clock_id = top_clock_prefix + Name.from_snake_case(clock["clock"])
        block_clock_enum = block_clocks[port].as_c_enum()
%>\
      [${block_clock_enum}] = ${clock_id.as_c_enum()},
%       endif
%     endfor
    },
%   if len(block.interrupts) > 0:
    .irqs = {
%     for irq in irqs[m["name"]]:
      ${irq.as_c_enum()},
%     endfor
    },
%   endif
  },
%   endfor
};
% endfor

<%
    dev_prefix = Name(["dt", "device", "id"])
    irq_prefix = Name(["top", top["name"], "plic", "irq", "id"])
    none_irq_name = irq_prefix + Name(["None"])
    unknown_peripheral_name = dev_prefix + Name(["unknown"])
    irq_table = {none_irq_name: unknown_peripheral_name}
    for module_name, irqs in helper.device_irqs.items():
        dev_name = Name.from_snake_case(module_name)
        module_type = [m for m in top["module"] if m["name"] == module_name]
        assert len(module_type) == 1
        for irq in irqs:
            irq_name = irq_prefix + Name.from_snake_case(irq)
            irq_table[irq_name] = dev_prefix + dev_name
%>\

enum {
  kDtIrqIdCount = ${str(len(irq_table.keys()))},
};

static const dt_device_id_t device_from_irq[kDtIrqIdCount] = {
% for irq, device_id in irq_table.items():
    [${irq.as_c_enum()}] = ${device_id.as_c_enum()},
% endfor
};

dt_device_id_t dt_irq_to_device(dt_irq_t irq) {
  if (irq < (dt_irq_t)kDtIrqIdCount) {
    return device_from_irq[irq];
  }
  return kDtDeviceIdUnknown;
}

static const dt_device_type_t device_type[kDtDeviceIdCount] = {
% for module_name in module_types:
<%
    modules = [m for m in top["module"] if m["type"] == module_name]
%>\
%   for (dev_index, m) in enumerate(modules):
  [${snake_to_constant_name("dt_device_id_" + m["name"])}] = ${snake_to_constant_name("dt_device_type_" + m["type"])},
%   endfor
% endfor
};

static const dt_device_type_t device_index[kDtDeviceIdCount] = {
% for module_name in module_types:
<%
    modules = [m for m in top["module"] if m["type"] == module_name]
%>\
%   for (dev_index, m) in enumerate(modules):
  [${snake_to_constant_name("dt_device_id_" + m["name"])}] = ${dev_index},
%   endfor
% endfor
};

dt_device_type_t dt_device_type(dt_device_id_t dev) {
  if (dev < kDtDeviceIdCount) {
    return device_type[dev];
  }
  return kDtDeviceTypeUnknown;
}

size_t dt_device_index(dt_device_id_t dev) {
  if (dev < kDtDeviceIdCount) {
    return device_index[dev];
  }
  return 0;
}
