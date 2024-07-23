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
module_data = {}

def snake_to_constant_name(s):
    out = ""
    parts = s.split("_")
    for p in parts:
        # If we're about to join two parts which would introduce adjacent
        # numbers, put an underscore between them.
        if out[-1:].isnumeric() and p[:1].isnumeric():
            out += "_" + p
        else:
            out += p.capitalize()
    return out
%>\

#ifndef ${helper.header_macro_prefix}_DEVICETABLES_H_
#define ${helper.header_macro_prefix}_DEVICETABLES_H_

#include "sw/device/lib/devicetables/dt.h"

#include <stddef.h>

% for header_path in sorted(dt_headers):
#include "${header_path}"
% endfor

enum {
% for module_name in module_types:
<%
    modules = [m for m in top["module"] if m["type"] == module_name]
%>\
  kDt${snake_to_constant_name(module_name)}Count = ${len(modules)},
% endfor
};

typedef enum dt_device_type {
% for module_name in module_types:
  kDtDeviceType${snake_to_constant_name(module_name)},
% endfor
} dt_device_type_t;

/**
 * Get the device type of a device.
 *
 * For example the device type of `kDtUart0` is `kDtUartDevice`.
 *
 * @param dev A device ID.
 * @return The device type.
 */
static inline dt_device_type_t dt_device_type(dt_device_id_t dev) {
    return (dt_device_type_t)(dev >> 16);
}

/**
 * Get the device instance of a device.
 *
 * If a top instances several devices of the same type, this will
 * return the instance number. This function guarantees that the instance
 * number can be used to index into the correspond devicetable below.
 *
 * For example, the instance number of `kDtUart3` is 3. It is guaranteed
 * then that `kDtUart[3].device == kDtUart3`.
 *
 * @param dev A device ID.
 * @return The device instance number.
 */
static inline size_t dt_device_instance(dt_device_id_t dev) {
    return (dt_device_type_t)(dev & 0xffff);
}

/**
 * Return the device ID from a device type and instance.
 *
 * @param dev_type A device type (dt_device_type_t).
 * @param instance A device instance (size_t).
 * @return The corresponding device ID (dt_device_id_t).
 *
 * This is a macro so it can be used in `devicetables.c` to create constants.
 */
#define dt_get_device_id(dev_type, inst) \
  ((dt_device_id_t)((dev_type) << 16 | ((inst) & 0xffff)))

% for module_name in module_types:
// Device tables for ${module_name}
extern const dt_${module_name}_t kDt${snake_to_constant_name(module_name)}[kDt${snake_to_constant_name(module_name)}Count];

% endfor

#endif // ${helper.header_macro_prefix}_DEVICETABLES_H_