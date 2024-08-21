# Copyright lowRISC contributors (OpenTitan project).
# Licensed under the Apache License, Version 2.0, see LICENSE for details.
# SPDX-License-Identifier: Apache-2.0
#
${gencmd.replace("//", "#")}

<%
top_name = "top_" + top["name"]
%>\
package(default_visibility = ["//visibility:public"])

cc_library(
    name = "dt_api_ipgen",
    hdrs = [
% for header_name in sorted(dt_ipgen_headers):
        "${header_name}",
% endfor
    ],
    # We pretend that this header lives in sw/device/lib/devicetables
    include_prefix = "sw/device/lib/devicetables/",
    deps = ["//hw/${top_name}/sw/autogen:dt_api"],
)
