# Copyright lowRISC contributors (OpenTitan project).
# Licensed under the Apache License, Version 2.0, see LICENSE for details.
# SPDX-License-Identifier: Apache-2.0
#
${gencmd.replace("//", "#")}

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "dt_api_ipgen",
    hdrs = [
% for header_name in sorted(dt_ipgen_headers):
        "${header_name}",
% endfor
    ],
    includes = ["."],
    deps = ["//sw/device/lib/devicetables:dt_api"],
)
