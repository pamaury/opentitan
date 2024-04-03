#!/bin/sh
# Copyright lowRISC contributors (OpenTitan project).
# Licensed under the Apache License, Version 2.0, see LICENSE for details.
# SPDX-License-Identifier: Apache-2.0

# TEMPORARY example of how to build serial port-based Bulk Transfer testing without libusb dependence.
# This is NOT intended to be merged into the repository.
g++ -std=c++14 -Wall -Werror -g -O2 -o serial_test stream_test.cc usbdev_serial.cc usbdev_stream.cc usbdev_utils.cc usb_device.cc
