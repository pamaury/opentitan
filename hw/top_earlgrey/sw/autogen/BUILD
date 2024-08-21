# Copyright lowRISC contributors (OpenTitan project).
# Licensed under the Apache License, Version 2.0, see LICENSE for details.
# SPDX-License-Identifier: Apache-2.0
#
# ------------------- W A R N I N G: A U T O - G E N E R A T E D   C O D E !! -------------------#
# PLEASE DO NOT HAND-EDIT THIS FILE. IT HAS BEEN AUTO-GENERATED WITH THE FOLLOWING COMMAND:
#
# util/topgen.py -t hw/top_earlgrey/data/top_earlgrey.hjson \
#                -o hw/top_earlgrey/ \
#                --rnd_cnst_seed \
#                1017106219537032642877583828875051302543807092889754935647094601236425074047


load("//rules:cross_platform.bzl", "dual_cc_library", "dual_inputs")
load("//rules:linker.bzl", "ld_library")
load("//rules:opentitan.bzl", "OPENTITAN_CPU")

package(default_visibility = ["//visibility:public"])

dual_cc_library(
    name = "top_earlgrey",
    srcs = [
        "top_earlgrey.c",
    ],
    hdrs = [
        "top_earlgrey.h",
        "top_earlgrey_memory.h",
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
        ":top_earlgrey",
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
        "//hw/top_earlgrey/sw/autogen/devicetables:dt_api_ipgen",
        "//sw/device/lib/devicetables:dt_api_reggen",
    ],
)

ld_library(
    name = "top_earlgrey_memory",
    includes = ["top_earlgrey_memory.ld"],
)

filegroup(
    name = "all_files",
    srcs = glob(["**"]),
)
