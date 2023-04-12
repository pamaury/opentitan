# Copyright lowRISC contributors.
# Licensed under the Apache License, Version 2.0, see LICENSE for details.
# SPDX-License-Identifier: Apache-2.0

load("@rules_rust//rust:defs.bzl", "rust_binary")
load("//rules:opentitan_test.bzl",
     "cw310_params", "opentitan_functest",
     "OPENTITANTOOL_OPENOCD_DATA_DEPS",
     "OPENTITANTOOL_OPENOCD_TEST_CMDS")

package(default_visibility = ["//visibility:public"])

rust_binary(
    name = "manuf_cp_unlock_raw_harness",
    srcs = [
        "manuf_cp_unlock_raw.rs",
    ],
    deps = [
        "//sw/host/opentitanlib",
        "@crate_index//:anyhow",
        "@crate_index//:structopt",
    ],
)

opentitan_functest(
    name = "manuf_cp_unlock_raw",
    srcs = ["//sw/device/silicon_creator/rom/e2e:empty_test.c"],
    cw310 = cw310_params(
        bitstream = ":bitstream_otp_raw",
        tags = [
            "jtag",
            "vivado",
        ],
        test_cmds = OPENTITANTOOL_OPENOCD_TEST_CMDS,
    ),
    data = OPENTITANTOOL_OPENOCD_DATA_DEPS,
    targets = ["cw310_rom"],
    test_harness = ":manuf_cp_unlock_raw_harness",
    deps = [
        "//hw/ip/otp_ctrl/data:otp_ctrl_regs",
        "//sw/device/lib/testing/test_framework:ottf_main",
        "//sw/device/silicon_creator/lib/drivers:lifecycle",
        "//sw/device/silicon_creator/lib/drivers:otp",
    ],
)
