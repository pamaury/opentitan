# Copyright lowRISC contributors (OpenTitan project).
# Licensed under the Apache License, Version 2.0, see LICENSE for details.
# SPDX-License-Identifier: Apache-2.0

TEMPLATE = """
// Copyright lowRISC contributors (OpenTitan project).
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0
//
#ifndef OPENTITAN_SW_HOST_OPENTITANLIB_BINDGEN_DIFS_H_
#define OPENTITAN_SW_HOST_OPENTITANLIB_BINDGEN_DIFS_H_

{}

#endif  // OPENTITAN_SW_HOST_OPENTITANLIB_BINDGEN_DIFS_H_
"""

def _generate_dif_header(ctx):
    include_list = ""
    for ip in ctx.attr.ips:
        include_list += "#include \"{}_regs.h\"\n".format(ip)
        include_list += "#include \"sw/device/lib/dif/dif_{}.h\"\n".format(ip)

    f = ctx.actions.declare_file("dif.h")
    ctx.actions.write(f, TEMPLATE.format(include_list))
    return [DefaultInfo(files = depset([f]))]

generate_dif_header = rule(
    implementation = _generate_dif_header,
    attrs = {
        "ips": attr.string_list(
            doc = "List of IPS for which to include the DIF."
        )
    }
)
