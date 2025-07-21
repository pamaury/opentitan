#!/usr/bin/env python3
# Copyright lowRISC contributors (OpenTitan project).
# Licensed under the Apache License, Version 2.0, see LICENSE for details.
# SPDX-License-Identifier: Apache-2.0
r"""Command-line tool to add the calling interpreter to fusesoc's PATH, so it
is used for generators. Also add some extra elements to the PATH.
"""


import os
import sys
from fusesoc.main import main

if __name__ == "__main__":
    # First, ensure the calling interpreter is on the PATH first, so any
    # generators asking /usr/bin/env for python3 will use the same version.
    path_env = os.environ.get("PATH", "")
    if path_env:
        path_env = ":" + path_env
    path_env = os.path.dirname(sys.executable) + path_env
    # Add every path in EXTRA_PATH to PATH, and resolve them to absolute
    # paths in the process since those come from bazel which only gives
    # relative paths.
    for path in reversed(os.environ.get("EXTRA_PATH","").split(":")):
        path = path.strip()
        if path:
            path_env = os.path.abspath(path) + ":" + path_env

    os.environ["PATH"] = path_env

    # Start fusesoc
    rc = main()
    sys.exit(rc)
