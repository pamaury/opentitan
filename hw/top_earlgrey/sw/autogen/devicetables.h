// Copyright lowRISC contributors.
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0
//
//
// ------------------- W A R N I N G: A U T O - G E N E R A T E D   C O D E !! -------------------//
// PLEASE DO NOT HAND-EDIT THIS FILE. IT HAS BEEN AUTO-GENERATED WITH THE FOLLOWING COMMAND:
//
// util/topgen.py -t hw/top_earlgrey/data/top_earlgrey.hjson \
//                -o hw/top_earlgrey/ \
//                --rnd_cnst_seed \
//                1017106219537032642877583828875051302543807092889754935647094601236425074047


#ifndef OPENTITAN_HW_TOP_EARLGREY_SW_AUTOGEN_DEVICETABLES_H_
#define OPENTITAN_HW_TOP_EARLGREY_SW_AUTOGEN_DEVICETABLES_H_

#include "sw/device/lib/devicetables/dt.h"

#include "hw/top_earlgrey/sw/autogen/devicetables/dt_alert_handler.h"
#include "hw/top_earlgrey/sw/autogen/devicetables/dt_ast.h"
#include "hw/top_earlgrey/sw/autogen/devicetables/dt_clkmgr.h"
#include "hw/top_earlgrey/sw/autogen/devicetables/dt_flash_ctrl.h"
#include "hw/top_earlgrey/sw/autogen/devicetables/dt_pinmux.h"
#include "hw/top_earlgrey/sw/autogen/devicetables/dt_pwrmgr.h"
#include "hw/top_earlgrey/sw/autogen/devicetables/dt_rstmgr.h"
#include "hw/top_earlgrey/sw/autogen/devicetables/dt_rv_plic.h"
#include "hw/top_earlgrey/sw/autogen/devicetables/dt_sensor_ctrl.h"
#include "sw/device/lib/devicetables/dt_adc_ctrl.h"
#include "sw/device/lib/devicetables/dt_aes.h"
#include "sw/device/lib/devicetables/dt_aon_timer.h"
#include "sw/device/lib/devicetables/dt_csrng.h"
#include "sw/device/lib/devicetables/dt_edn.h"
#include "sw/device/lib/devicetables/dt_entropy_src.h"
#include "sw/device/lib/devicetables/dt_gpio.h"
#include "sw/device/lib/devicetables/dt_hmac.h"
#include "sw/device/lib/devicetables/dt_i2c.h"
#include "sw/device/lib/devicetables/dt_keymgr.h"
#include "sw/device/lib/devicetables/dt_kmac.h"
#include "sw/device/lib/devicetables/dt_lc_ctrl.h"
#include "sw/device/lib/devicetables/dt_otbn.h"
#include "sw/device/lib/devicetables/dt_otp_ctrl.h"
#include "sw/device/lib/devicetables/dt_pattgen.h"
#include "sw/device/lib/devicetables/dt_pwm.h"
#include "sw/device/lib/devicetables/dt_rom_ctrl.h"
#include "sw/device/lib/devicetables/dt_rv_core_ibex.h"
#include "sw/device/lib/devicetables/dt_rv_dm.h"
#include "sw/device/lib/devicetables/dt_rv_timer.h"
#include "sw/device/lib/devicetables/dt_spi_device.h"
#include "sw/device/lib/devicetables/dt_spi_host.h"
#include "sw/device/lib/devicetables/dt_sram_ctrl.h"
#include "sw/device/lib/devicetables/dt_sysrst_ctrl.h"
#include "sw/device/lib/devicetables/dt_uart.h"
#include "sw/device/lib/devicetables/dt_usbdev.h"

enum {
  kDtAdcCtrlCount = 1,
  kDtAesCount = 1,
  kDtAlertHandlerCount = 1,
  kDtAonTimerCount = 1,
  kDtAstCount = 1,
  kDtClkmgrCount = 1,
  kDtCsrngCount = 1,
  kDtEdnCount = 2,
  kDtEntropySrcCount = 1,
  kDtFlashCtrlCount = 1,
  kDtGpioCount = 1,
  kDtHmacCount = 1,
  kDtI2cCount = 3,
  kDtKeymgrCount = 1,
  kDtKmacCount = 1,
  kDtLcCtrlCount = 1,
  kDtOtbnCount = 1,
  kDtOtpCtrlCount = 1,
  kDtPattgenCount = 1,
  kDtPinmuxCount = 1,
  kDtPwmCount = 1,
  kDtPwrmgrCount = 1,
  kDtRomCtrlCount = 1,
  kDtRstmgrCount = 1,
  kDtRvCoreIbexCount = 1,
  kDtRvDmCount = 1,
  kDtRvPlicCount = 1,
  kDtRvTimerCount = 1,
  kDtSensorCtrlCount = 1,
  kDtSpiDeviceCount = 1,
  kDtSpiHostCount = 2,
  kDtSramCtrlCount = 2,
  kDtSysrstCtrlCount = 1,
  kDtUartCount = 4,
  kDtUsbdevCount = 1,
};

// Device tables for adc_ctrl
extern const dt_adc_ctrl_t kDtAdcCtrlList[kDtAdcCtrlCount];

// Device tables for aes
extern const dt_aes_t kDtAesList[kDtAesCount];

// Device tables for alert_handler
extern const dt_alert_handler_t kDtAlertHandlerList[kDtAlertHandlerCount];

// Device tables for aon_timer
extern const dt_aon_timer_t kDtAonTimerList[kDtAonTimerCount];

// Device tables for ast
extern const dt_ast_t kDtAstList[kDtAstCount];

// Device tables for clkmgr
extern const dt_clkmgr_t kDtClkmgrList[kDtClkmgrCount];

// Device tables for csrng
extern const dt_csrng_t kDtCsrngList[kDtCsrngCount];

// Device tables for edn
extern const dt_edn_t kDtEdnList[kDtEdnCount];

// Device tables for entropy_src
extern const dt_entropy_src_t kDtEntropySrcList[kDtEntropySrcCount];

// Device tables for flash_ctrl
extern const dt_flash_ctrl_t kDtFlashCtrlList[kDtFlashCtrlCount];

// Device tables for gpio
extern const dt_gpio_t kDtGpioList[kDtGpioCount];

// Device tables for hmac
extern const dt_hmac_t kDtHmacList[kDtHmacCount];

// Device tables for i2c
extern const dt_i2c_t kDtI2cList[kDtI2cCount];

// Device tables for keymgr
extern const dt_keymgr_t kDtKeymgrList[kDtKeymgrCount];

// Device tables for kmac
extern const dt_kmac_t kDtKmacList[kDtKmacCount];

// Device tables for lc_ctrl
extern const dt_lc_ctrl_t kDtLcCtrlList[kDtLcCtrlCount];

// Device tables for otbn
extern const dt_otbn_t kDtOtbnList[kDtOtbnCount];

// Device tables for otp_ctrl
extern const dt_otp_ctrl_t kDtOtpCtrlList[kDtOtpCtrlCount];

// Device tables for pattgen
extern const dt_pattgen_t kDtPattgenList[kDtPattgenCount];

// Device tables for pinmux
extern const dt_pinmux_t kDtPinmuxList[kDtPinmuxCount];

// Device tables for pwm
extern const dt_pwm_t kDtPwmList[kDtPwmCount];

// Device tables for pwrmgr
extern const dt_pwrmgr_t kDtPwrmgrList[kDtPwrmgrCount];

// Device tables for rom_ctrl
extern const dt_rom_ctrl_t kDtRomCtrlList[kDtRomCtrlCount];

// Device tables for rstmgr
extern const dt_rstmgr_t kDtRstmgrList[kDtRstmgrCount];

// Device tables for rv_core_ibex
extern const dt_rv_core_ibex_t kDtRvCoreIbexList[kDtRvCoreIbexCount];

// Device tables for rv_dm
extern const dt_rv_dm_t kDtRvDmList[kDtRvDmCount];

// Device tables for rv_plic
extern const dt_rv_plic_t kDtRvPlicList[kDtRvPlicCount];

// Device tables for rv_timer
extern const dt_rv_timer_t kDtRvTimerList[kDtRvTimerCount];

// Device tables for sensor_ctrl
extern const dt_sensor_ctrl_t kDtSensorCtrlList[kDtSensorCtrlCount];

// Device tables for spi_device
extern const dt_spi_device_t kDtSpiDeviceList[kDtSpiDeviceCount];

// Device tables for spi_host
extern const dt_spi_host_t kDtSpiHostList[kDtSpiHostCount];

// Device tables for sram_ctrl
extern const dt_sram_ctrl_t kDtSramCtrlList[kDtSramCtrlCount];

// Device tables for sysrst_ctrl
extern const dt_sysrst_ctrl_t kDtSysrstCtrlList[kDtSysrstCtrlCount];

// Device tables for uart
extern const dt_uart_t kDtUartList[kDtUartCount];

// Device tables for usbdev
extern const dt_usbdev_t kDtUsbdevList[kDtUsbdevCount];


#endif // OPENTITAN_HW_TOP_EARLGREY_SW_AUTOGEN_DEVICETABLES_H_