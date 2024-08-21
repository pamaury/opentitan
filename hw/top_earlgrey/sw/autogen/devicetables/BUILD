# Copyright lowRISC contributors (OpenTitan project).
# Licensed under the Apache License, Version 2.0, see LICENSE for details.
# SPDX-License-Identifier: Apache-2.0
#
#
# ------------------- W A R N I N G: A U T O - G E N E R A T E D   C O D E !! -------------------#
# PLEASE DO NOT HAND-EDIT THIS FILE. IT HAS BEEN AUTO-GENERATED WITH THE FOLLOWING COMMAND:
#
# util/topgen.py -t hw/top_earlgrey/data/top_earlgrey.hjson \
#                -o hw/top_earlgrey/ \
#                --rnd_cnst_seed \
#                1017106219537032642877583828875051302543807092889754935647094601236425074047


package(default_visibility = ["//visibility:public"])

cc_library(
    name = "dt_api_ipgen",
    hdrs = [
        "dt_alert_handler.h",
        "dt_ast.h",
        "dt_clkmgr.h",
        "dt_flash_ctrl.h",
        "dt_pinmux.h",
        "dt_pwrmgr.h",
        "dt_rstmgr.h",
        "dt_rv_plic.h",
        "dt_sensor_ctrl.h",
    ],
    # We pretend that this header lives in sw/device/lib/devicetables
    include_prefix = "sw/device/lib/devicetables/",
    deps = ["//hw/top_earlgrey/sw/autogen:dt_api"],
)
