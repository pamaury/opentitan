# Copyright lowRISC contributors (OpenTitan project).
# Licensed under the Apache License, Version 2.0, see LICENSE for details.
# SPDX-License-Identifier: Apache-2.0

load("//rules/opentitan:util.bzl", "flatten")
load("//rules:autogen.bzl", "opentitan_autogen_dif")
load("//hw/top:defs.bzl", "ALL_IP_NAMES", "opentitan_if_ip", "opentitan_require_ip")

package(default_visibility = ["//visibility:public"])

[
    opentitan_autogen_dif(
        name = ip,
        ip = ip,
        target_compatible_with = opentitan_require_ip(ip),
        top = "//hw/top:top_desc",
        deps = [
            "//hw/top:dt_{}".format(ip),
            "//hw/top:{}_c_regs".format(ip),
            "//sw/device/lib/base:mmio",
            "//sw/device/lib/dif:base",
        ],
    )
    for ip in ALL_IP_NAMES
]

cc_library(
    name = "all_difs",
    deps = flatten([
        opentitan_if_ip(
            ip,
            [":{}".format(ip)],
            [],
        )
        for ip in ALL_IP_NAMES
    ])
)