# Copyright lowRISC contributors (OpenTitan project).
# Licensed under the Apache License, Version 2.0, see LICENSE for details.
# SPDX-License-Identifier: Apache-2.0
${gencmd.replace("//", "#")}

<%
top_name = "top_" + top["name"]
%>\
load("//rules:cross_platform.bzl", "dual_cc_library", "dual_inputs")
load("//rules:linker.bzl", "ld_library")
load("//rules:opentitan.bzl", "OPENTITAN_CPU")

package(default_visibility = ["//visibility:public"])

dual_cc_library(
    name = "${top_name}",
    srcs = [
        "${top_name}.c",
    ],
    hdrs = [
        "${top_name}.h",
        "${top_name}_memory.h",
    ],
    copts = dual_inputs(
        device = ["-flto=full"],
    ),
    target_compatible_with = dual_inputs(device = [OPENTITAN_CPU]),
)

cc_library(
    name = "dt_api",
    hdrs = ["dt_api.h"],
    # We pretend that this header lives in sw/device/lib/devicetables
    include_prefix = "sw/device/lib/devicetables/",
    deps = [
        ":${top_name}",
    ],
)

dual_cc_library(
    name = "devicetables",
    srcs = ["devicetables.c"],
    hdrs = ["devicetables.h"],
    # We pretend that this header lives in sw/device/lib/devicetables
    include_prefix = "sw/device/lib/devicetables/",
    copts = dual_inputs(
        device = ["-flto=full"],
    ),
    deps = [
        ":dt_api",
        "//hw/${top_name}/sw/autogen/devicetables:dt_api_ipgen",
        "//sw/device/lib/devicetables:dt_api_reggen",
    ],
)

ld_library(
    name = "${top_name}_memory",
    includes = ["${top_name}_memory.ld"],
)

filegroup(
    name = "all_files",
    srcs = glob(["**"]),
)
