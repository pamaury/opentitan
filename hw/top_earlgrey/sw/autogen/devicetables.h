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

#include <stddef.h>

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

typedef enum dt_device_id_type {
  kDtDeviceTypeAdcCtrl,
  kDtDeviceTypeAes,
  kDtDeviceTypeAlertHandler,
  kDtDeviceTypeAonTimer,
  kDtDeviceTypeAst,
  kDtDeviceTypeClkmgr,
  kDtDeviceTypeCsrng,
  kDtDeviceTypeEdn,
  kDtDeviceTypeEntropySrc,
  kDtDeviceTypeFlashCtrl,
  kDtDeviceTypeGpio,
  kDtDeviceTypeHmac,
  kDtDeviceTypeI2c,
  kDtDeviceTypeKeymgr,
  kDtDeviceTypeKmac,
  kDtDeviceTypeLcCtrl,
  kDtDeviceTypeOtbn,
  kDtDeviceTypeOtpCtrl,
  kDtDeviceTypePattgen,
  kDtDeviceTypePinmux,
  kDtDeviceTypePwm,
  kDtDeviceTypePwrmgr,
  kDtDeviceTypeRomCtrl,
  kDtDeviceTypeRstmgr,
  kDtDeviceTypeRvCoreIbex,
  kDtDeviceTypeRvDm,
  kDtDeviceTypeRvPlic,
  kDtDeviceTypeRvTimer,
  kDtDeviceTypeSensorCtrl,
  kDtDeviceTypeSpiDevice,
  kDtDeviceTypeSpiHost,
  kDtDeviceTypeSramCtrl,
  kDtDeviceTypeSysrstCtrl,
  kDtDeviceTypeUart,
  kDtDeviceTypeUsbdev,
} dt_device_type_t;

/**
 * Get the device type of a device.
 *
 * For example the device type of `kDtUart0` is `kDtUartDevice`.
 *
 * @param dev A device ID.
 * @return The device type.
 */
static inline dt_device_type_t dt_device_id_type(dt_device_id_t dev) {
    return (dt_device_type_t)(dev >> 16);
}

/**
 * Get the device instance of a device.
 *
 * If a top instances several devices of the same type, this will
 * return the instance number. This function guarantees that the instance
 * number can be used to index into the correspond devicetable below.
 *
 * For example, the instance number of `kDtUart3` is 3. It is guaranteed
 * then that `kDtUart[3].device == kDtUart3`.
 *
 * @param dev A device ID.
 * @return The device instance number.
 */
static inline size_t dt_device_instance(dt_device_id_t dev) {
    return (dt_device_type_t)(dev & 0xffff);
}

/**
 * Return the device ID from a device type and instance.
 *
 * @param dev_type A device type (dt_device_type_t).
 * @param instance A device instance (size_t).
 * @return The corresponding device ID (dt_device_id_t).
 *
 * This is a macro so it can be used in `devicetables.c` to create constants.
 */
#define dt_get_device_id(dev_type, inst)   ((dt_device_id_t)((dev_type) << 16 | ((inst) & 0xffff)))

// Device tables for adc_ctrl
extern const dt_adc_ctrl_t kDtAdcCtrl[kDtAdcCtrlCount];

// Device tables for aes
extern const dt_aes_t kDtAes[kDtAesCount];

// Device tables for alert_handler
extern const dt_alert_handler_t kDtAlertHandler[kDtAlertHandlerCount];

// Device tables for aon_timer
extern const dt_aon_timer_t kDtAonTimer[kDtAonTimerCount];

// Device tables for ast
extern const dt_ast_t kDtAst[kDtAstCount];

// Device tables for clkmgr
extern const dt_clkmgr_t kDtClkmgr[kDtClkmgrCount];

// Device tables for csrng
extern const dt_csrng_t kDtCsrng[kDtCsrngCount];

// Device tables for edn
extern const dt_edn_t kDtEdn[kDtEdnCount];

// Device tables for entropy_src
extern const dt_entropy_src_t kDtEntropySrc[kDtEntropySrcCount];

// Device tables for flash_ctrl
extern const dt_flash_ctrl_t kDtFlashCtrl[kDtFlashCtrlCount];

// Device tables for gpio
extern const dt_gpio_t kDtGpio[kDtGpioCount];

// Device tables for hmac
extern const dt_hmac_t kDtHmac[kDtHmacCount];

// Device tables for i2c
extern const dt_i2c_t kDtI2c[kDtI2cCount];

// Device tables for keymgr
extern const dt_keymgr_t kDtKeymgr[kDtKeymgrCount];

// Device tables for kmac
extern const dt_kmac_t kDtKmac[kDtKmacCount];

// Device tables for lc_ctrl
extern const dt_lc_ctrl_t kDtLcCtrl[kDtLcCtrlCount];

// Device tables for otbn
extern const dt_otbn_t kDtOtbn[kDtOtbnCount];

// Device tables for otp_ctrl
extern const dt_otp_ctrl_t kDtOtpCtrl[kDtOtpCtrlCount];

// Device tables for pattgen
extern const dt_pattgen_t kDtPattgen[kDtPattgenCount];

// Device tables for pinmux
extern const dt_pinmux_t kDtPinmux[kDtPinmuxCount];

// Device tables for pwm
extern const dt_pwm_t kDtPwm[kDtPwmCount];

// Device tables for pwrmgr
extern const dt_pwrmgr_t kDtPwrmgr[kDtPwrmgrCount];

// Device tables for rom_ctrl
extern const dt_rom_ctrl_t kDtRomCtrl[kDtRomCtrlCount];

// Device tables for rstmgr
extern const dt_rstmgr_t kDtRstmgr[kDtRstmgrCount];

// Device tables for rv_core_ibex
extern const dt_rv_core_ibex_t kDtRvCoreIbex[kDtRvCoreIbexCount];

// Device tables for rv_dm
extern const dt_rv_dm_t kDtRvDm[kDtRvDmCount];

// Device tables for rv_plic
extern const dt_rv_plic_t kDtRvPlic[kDtRvPlicCount];

// Device tables for rv_timer
extern const dt_rv_timer_t kDtRvTimer[kDtRvTimerCount];

// Device tables for sensor_ctrl
extern const dt_sensor_ctrl_t kDtSensorCtrl[kDtSensorCtrlCount];

// Device tables for spi_device
extern const dt_spi_device_t kDtSpiDevice[kDtSpiDeviceCount];

// Device tables for spi_host
extern const dt_spi_host_t kDtSpiHost[kDtSpiHostCount];

// Device tables for sram_ctrl
extern const dt_sram_ctrl_t kDtSramCtrl[kDtSramCtrlCount];

// Device tables for sysrst_ctrl
extern const dt_sysrst_ctrl_t kDtSysrstCtrl[kDtSysrstCtrlCount];

// Device tables for uart
extern const dt_uart_t kDtUart[kDtUartCount];

// Device tables for usbdev
extern const dt_usbdev_t kDtUsbdev[kDtUsbdevCount];


#endif // OPENTITAN_HW_TOP_EARLGREY_SW_AUTOGEN_DEVICETABLES_H_