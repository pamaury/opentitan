# Copyright lowRISC contributors.
# Licensed under the Apache License, Version 2.0, see LICENSE for details.
# SPDX-License-Identifier: Apache-2.0

load(
    "//rules:certificates.bzl",
    "certificate_template",
)

cc_library(
    name = "ot_certs",
    srcs = ["ot_certs.c"],
    hdrs = ["ot_certs.h"],
    deps = [
        "//sw/device/lib/base:status",
    ],
)

certificate_template(
    "generic_template",
    "generic.hjson",
)

certificate_template(
    "example_template",
    "example.hjson",
)

certificate_template(
    "uds_template",
    "uds.hjson",
)

certificate_template(
    "cdi_0_template",
    "cdi_0.hjson",
)

cc_library(
    name = "asn1",
    srcs = ["asn1.c"],
    hdrs = ["asn1.h"],
    deps = [
        "//sw/device/lib/base:memory",
        "//sw/device/lib/base:status",
    ],
)
