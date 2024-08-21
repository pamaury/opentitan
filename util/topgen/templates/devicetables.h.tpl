// Copyright lowRISC contributors.
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0
//
${gencmd}
<%
from topgen.lib import Name, is_top_reggen, is_ipgen

module_types = {m["type"] for m in top["module"]}
module_types = sorted(module_types)

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

#include "sw/device/lib/devicetables/dt_api.h"

% for header_path in sorted(dt_headers):
#include "${header_path}"
% endfor

% for module_name in module_types:
// Device tables for ${module_name}
extern const dt_${module_name}_t kDt${snake_to_constant_name(module_name)}[kDt${snake_to_constant_name(module_name)}Count];

% endfor

#endif // ${helper.header_macro_prefix}_DEVICETABLES_H_