# Copyright lowRISC contributors.
# Licensed under the Apache License, Version 2.0, see LICENSE for details.
# SPDX-License-Identifier: Apache-2.0

load("//rules:opentitan.bzl", "OPENTITAN_CPU")

package(default_visibility = ["//visibility:public"])

# This library gets depended upon by each top-specific
# `devicetables`.
cc_library(
    name = "dt_api_reggen",
    srcs = [],
    hdrs = [
        "dt_adc_ctrl.h",
        "dt_aes.h",
        "dt_alert_handler.h",
        "dt_aon_timer.h",
        "dt_clkmgr.h",
        "dt_csrng.h",
        "dt_edn.h",
        "dt_entropy_src.h",
        "dt_flash_ctrl.h",
        "dt_gpio.h",
        "dt_hmac.h",
        "dt_i2c.h",
        "dt_keymgr.h",
        "dt_kmac.h",
        "dt_lc_ctrl.h",
        "dt_otbn.h",
        "dt_otp_ctrl.h",
        "dt_pattgen.h",
        "dt_pwm.h",
        "dt_pwrmgr.h",
        "dt_rom_ctrl.h",
        "dt_rv_core_ibex.h",
        "dt_rv_dm.h",
        "dt_rv_timer.h",
        "dt_spi_device.h",
        "dt_spi_host.h",
        "dt_sram_ctrl.h",
        "dt_sysrst_ctrl.h",
        "dt_uart.h",
        "dt_usbdev.h",
    ],
    deps = [
        "//hw/top_earlgrey/sw/autogen:dt_api",
    ],
)

cc_library(
    name = "devicetables",
    srcs = [],
    deps = [
        # The following cc_library sets `include_prefix` to this directory so that
        # one can include top-specific DT headers without knowing the top name.
        "//hw/top_earlgrey/sw/autogen:devicetables",
    ],
)
