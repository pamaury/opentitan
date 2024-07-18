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



#include "hw/top_earlgrey/sw/autogen/devicetables.h"
#include "hw/top_earlgrey/sw/autogen/top_earlgrey.h"
#include <stdint.h>

// Device tables for adc_ctrl
_Static_assert(kDtAdcCtrlRegBlockCount == 1, "Reg block count mismatch");
_Static_assert(kDtAdcCtrlClockCount == 2, "Clock count mismatch");
_Static_assert(kDtAdcCtrlIrqTypeCount == 1, "IRQ count mismatch");
_Static_assert(kDtAdcCtrlCount == 1, "Number of adc_ctrl modules mismatch");

const dt_adc_ctrl_t kDtAdcCtrlList[kDtAdcCtrlCount] = {
  // Properties for adc_ctrl_aon
  {
    .device = kDtDeviceIdAdcCtrlAon,
    .base_addrs = {
      0x40440000,
    },
    .clocks = {
      [kDtAdcCtrlClockClk] = kTopEarlgreyClockSrcIoDiv4,
      [kDtAdcCtrlClockAon] = kTopEarlgreyClockSrcAon,
    },
    .irqs = {
      kTopEarlgreyPlicIrqIdAdcCtrlAonMatchPending,
    },
  },
};
// Device tables for aes
_Static_assert(kDtAesRegBlockCount == 1, "Reg block count mismatch");
_Static_assert(kDtAesClockCount == 2, "Clock count mismatch");
_Static_assert(kDtAesCount == 1, "Number of aes modules mismatch");

const dt_aes_t kDtAesList[kDtAesCount] = {
  // Properties for aes
  {
    .device = kDtDeviceIdAes,
    .base_addrs = {
      0x41100000,
    },
    .clocks = {
      [kDtAesClockClk] = kTopEarlgreyClockSrcMain,
      [kDtAesClockEdn] = kTopEarlgreyClockSrcMain,
    },
  },
};
// Device tables for alert_handler
_Static_assert(kDtAlertHandlerRegBlockCount == 1, "Reg block count mismatch");
_Static_assert(kDtAlertHandlerClockCount == 2, "Clock count mismatch");
_Static_assert(kDtAlertHandlerIrqTypeCount == 4, "IRQ count mismatch");
_Static_assert(kDtAlertHandlerCount == 1, "Number of alert_handler modules mismatch");

const dt_alert_handler_t kDtAlertHandlerList[kDtAlertHandlerCount] = {
  // Properties for alert_handler
  {
    .device = kDtDeviceIdAlertHandler,
    .base_addrs = {
      0x40150000,
    },
    .clocks = {
      [kDtAlertHandlerClockClk] = kTopEarlgreyClockSrcIoDiv4,
      [kDtAlertHandlerClockEdn] = kTopEarlgreyClockSrcMain,
    },
    .irqs = {
      kTopEarlgreyPlicIrqIdAlertHandlerClassa,
      kTopEarlgreyPlicIrqIdAlertHandlerClassb,
      kTopEarlgreyPlicIrqIdAlertHandlerClassc,
      kTopEarlgreyPlicIrqIdAlertHandlerClassd,
    },
  },
};
// Device tables for aon_timer
_Static_assert(kDtAonTimerRegBlockCount == 1, "Reg block count mismatch");
_Static_assert(kDtAonTimerClockCount == 2, "Clock count mismatch");
_Static_assert(kDtAonTimerIrqTypeCount == 2, "IRQ count mismatch");
_Static_assert(kDtAonTimerCount == 1, "Number of aon_timer modules mismatch");

const dt_aon_timer_t kDtAonTimerList[kDtAonTimerCount] = {
  // Properties for aon_timer_aon
  {
    .device = kDtDeviceIdAonTimerAon,
    .base_addrs = {
      0x40470000,
    },
    .clocks = {
      [kDtAonTimerClockClk] = kTopEarlgreyClockSrcIoDiv4,
      [kDtAonTimerClockAon] = kTopEarlgreyClockSrcAon,
    },
    .irqs = {
      kTopEarlgreyPlicIrqIdAonTimerAonWkupTimerExpired,
      kTopEarlgreyPlicIrqIdAonTimerAonWdogTimerBark,
    },
  },
};
// Device tables for ast
_Static_assert(kDtAstRegBlockCount == 1, "Reg block count mismatch");
_Static_assert(kDtAstClockCount == 6, "Clock count mismatch");
_Static_assert(kDtAstCount == 1, "Number of ast modules mismatch");

const dt_ast_t kDtAstList[kDtAstCount] = {
  // Properties for ast
  {
    .device = kDtDeviceIdAst,
    .base_addrs = {
      0x40480000,
    },
    .clocks = {
      [kDtAstClockAstTlul] = kTopEarlgreyClockSrcIoDiv4,
      [kDtAstClockAstAdc] = kTopEarlgreyClockSrcAon,
      [kDtAstClockAstAlert] = kTopEarlgreyClockSrcIoDiv4,
      [kDtAstClockAstEs] = kTopEarlgreyClockSrcMain,
      [kDtAstClockAstRng] = kTopEarlgreyClockSrcMain,
      [kDtAstClockAstUsb] = kTopEarlgreyClockSrcUsb,
    },
  },
};
// Device tables for clkmgr
_Static_assert(kDtClkmgrRegBlockCount == 1, "Reg block count mismatch");
_Static_assert(kDtClkmgrClockCount == 5, "Clock count mismatch");
_Static_assert(kDtClkmgrCount == 1, "Number of clkmgr modules mismatch");

const dt_clkmgr_t kDtClkmgrList[kDtClkmgrCount] = {
  // Properties for clkmgr_aon
  {
    .device = kDtDeviceIdClkmgrAon,
    .base_addrs = {
      0x40420000,
    },
    .clocks = {
      [kDtClkmgrClockClk] = kTopEarlgreyClockSrcIoDiv4,
      [kDtClkmgrClockMain] = kTopEarlgreyClockSrcMain,
      [kDtClkmgrClockIo] = kTopEarlgreyClockSrcIo,
      [kDtClkmgrClockUsb] = kTopEarlgreyClockSrcUsb,
      [kDtClkmgrClockAon] = kTopEarlgreyClockSrcAon,
    },
  },
};
// Device tables for csrng
_Static_assert(kDtCsrngRegBlockCount == 1, "Reg block count mismatch");
_Static_assert(kDtCsrngClockCount == 1, "Clock count mismatch");
_Static_assert(kDtCsrngIrqTypeCount == 4, "IRQ count mismatch");
_Static_assert(kDtCsrngCount == 1, "Number of csrng modules mismatch");

const dt_csrng_t kDtCsrngList[kDtCsrngCount] = {
  // Properties for csrng
  {
    .device = kDtDeviceIdCsrng,
    .base_addrs = {
      0x41150000,
    },
    .clocks = {
      [kDtCsrngClockClk] = kTopEarlgreyClockSrcMain,
    },
    .irqs = {
      kTopEarlgreyPlicIrqIdCsrngCsCmdReqDone,
      kTopEarlgreyPlicIrqIdCsrngCsEntropyReq,
      kTopEarlgreyPlicIrqIdCsrngCsHwInstExc,
      kTopEarlgreyPlicIrqIdCsrngCsFatalErr,
    },
  },
};
// Device tables for edn
_Static_assert(kDtEdnRegBlockCount == 1, "Reg block count mismatch");
_Static_assert(kDtEdnClockCount == 1, "Clock count mismatch");
_Static_assert(kDtEdnIrqTypeCount == 2, "IRQ count mismatch");
_Static_assert(kDtEdnCount == 2, "Number of edn modules mismatch");

const dt_edn_t kDtEdnList[kDtEdnCount] = {
  // Properties for edn0
  {
    .device = kDtDeviceIdEdn0,
    .base_addrs = {
      0x41170000,
    },
    .clocks = {
      [kDtEdnClockClk] = kTopEarlgreyClockSrcMain,
    },
    .irqs = {
      kTopEarlgreyPlicIrqIdEdn0EdnCmdReqDone,
      kTopEarlgreyPlicIrqIdEdn0EdnFatalErr,
    },
  },
  // Properties for edn1
  {
    .device = kDtDeviceIdEdn1,
    .base_addrs = {
      0x41180000,
    },
    .clocks = {
      [kDtEdnClockClk] = kTopEarlgreyClockSrcMain,
    },
    .irqs = {
      kTopEarlgreyPlicIrqIdEdn1EdnCmdReqDone,
      kTopEarlgreyPlicIrqIdEdn1EdnFatalErr,
    },
  },
};
// Device tables for entropy_src
_Static_assert(kDtEntropySrcRegBlockCount == 1, "Reg block count mismatch");
_Static_assert(kDtEntropySrcClockCount == 1, "Clock count mismatch");
_Static_assert(kDtEntropySrcIrqTypeCount == 4, "IRQ count mismatch");
_Static_assert(kDtEntropySrcCount == 1, "Number of entropy_src modules mismatch");

const dt_entropy_src_t kDtEntropySrcList[kDtEntropySrcCount] = {
  // Properties for entropy_src
  {
    .device = kDtDeviceIdEntropySrc,
    .base_addrs = {
      0x41160000,
    },
    .clocks = {
      [kDtEntropySrcClockClk] = kTopEarlgreyClockSrcMain,
    },
    .irqs = {
      kTopEarlgreyPlicIrqIdEntropySrcEsEntropyValid,
      kTopEarlgreyPlicIrqIdEntropySrcEsHealthTestFailed,
      kTopEarlgreyPlicIrqIdEntropySrcEsObserveFifoReady,
      kTopEarlgreyPlicIrqIdEntropySrcEsFatalErr,
    },
  },
};
// Device tables for flash_ctrl
_Static_assert(kDtFlashCtrlRegBlockCount == 3, "Reg block count mismatch");
_Static_assert(kDtFlashCtrlClockCount == 2, "Clock count mismatch");
_Static_assert(kDtFlashCtrlIrqTypeCount == 6, "IRQ count mismatch");
_Static_assert(kDtFlashCtrlCount == 1, "Number of flash_ctrl modules mismatch");

const dt_flash_ctrl_t kDtFlashCtrlList[kDtFlashCtrlCount] = {
  // Properties for flash_ctrl
  {
    .device = kDtDeviceIdFlashCtrl,
    .base_addrs = {
      0x41000000,
      0x41008000,
      0x20000000,
    },
    .clocks = {
      [kDtFlashCtrlClockClk] = kTopEarlgreyClockSrcMain,
      [kDtFlashCtrlClockOtp] = kTopEarlgreyClockSrcIoDiv4,
    },
    .irqs = {
      kTopEarlgreyPlicIrqIdFlashCtrlProgEmpty,
      kTopEarlgreyPlicIrqIdFlashCtrlProgLvl,
      kTopEarlgreyPlicIrqIdFlashCtrlRdFull,
      kTopEarlgreyPlicIrqIdFlashCtrlRdLvl,
      kTopEarlgreyPlicIrqIdFlashCtrlOpDone,
      kTopEarlgreyPlicIrqIdFlashCtrlCorrErr,
    },
  },
};
// Device tables for gpio
_Static_assert(kDtGpioRegBlockCount == 1, "Reg block count mismatch");
_Static_assert(kDtGpioClockCount == 1, "Clock count mismatch");
_Static_assert(kDtGpioIrqTypeCount == 32, "IRQ count mismatch");
_Static_assert(kDtGpioCount == 1, "Number of gpio modules mismatch");

const dt_gpio_t kDtGpioList[kDtGpioCount] = {
  // Properties for gpio
  {
    .device = kDtDeviceIdGpio,
    .base_addrs = {
      0x40040000,
    },
    .clocks = {
      [kDtGpioClockClk] = kTopEarlgreyClockSrcIoDiv4,
    },
    .irqs = {
      kTopEarlgreyPlicIrqIdGpioGpio0,
      kTopEarlgreyPlicIrqIdGpioGpio1,
      kTopEarlgreyPlicIrqIdGpioGpio2,
      kTopEarlgreyPlicIrqIdGpioGpio3,
      kTopEarlgreyPlicIrqIdGpioGpio4,
      kTopEarlgreyPlicIrqIdGpioGpio5,
      kTopEarlgreyPlicIrqIdGpioGpio6,
      kTopEarlgreyPlicIrqIdGpioGpio7,
      kTopEarlgreyPlicIrqIdGpioGpio8,
      kTopEarlgreyPlicIrqIdGpioGpio9,
      kTopEarlgreyPlicIrqIdGpioGpio10,
      kTopEarlgreyPlicIrqIdGpioGpio11,
      kTopEarlgreyPlicIrqIdGpioGpio12,
      kTopEarlgreyPlicIrqIdGpioGpio13,
      kTopEarlgreyPlicIrqIdGpioGpio14,
      kTopEarlgreyPlicIrqIdGpioGpio15,
      kTopEarlgreyPlicIrqIdGpioGpio16,
      kTopEarlgreyPlicIrqIdGpioGpio17,
      kTopEarlgreyPlicIrqIdGpioGpio18,
      kTopEarlgreyPlicIrqIdGpioGpio19,
      kTopEarlgreyPlicIrqIdGpioGpio20,
      kTopEarlgreyPlicIrqIdGpioGpio21,
      kTopEarlgreyPlicIrqIdGpioGpio22,
      kTopEarlgreyPlicIrqIdGpioGpio23,
      kTopEarlgreyPlicIrqIdGpioGpio24,
      kTopEarlgreyPlicIrqIdGpioGpio25,
      kTopEarlgreyPlicIrqIdGpioGpio26,
      kTopEarlgreyPlicIrqIdGpioGpio27,
      kTopEarlgreyPlicIrqIdGpioGpio28,
      kTopEarlgreyPlicIrqIdGpioGpio29,
      kTopEarlgreyPlicIrqIdGpioGpio30,
      kTopEarlgreyPlicIrqIdGpioGpio31,
    },
  },
};
// Device tables for hmac
_Static_assert(kDtHmacRegBlockCount == 1, "Reg block count mismatch");
_Static_assert(kDtHmacClockCount == 1, "Clock count mismatch");
_Static_assert(kDtHmacIrqTypeCount == 3, "IRQ count mismatch");
_Static_assert(kDtHmacCount == 1, "Number of hmac modules mismatch");

const dt_hmac_t kDtHmacList[kDtHmacCount] = {
  // Properties for hmac
  {
    .device = kDtDeviceIdHmac,
    .base_addrs = {
      0x41110000,
    },
    .clocks = {
      [kDtHmacClockClk] = kTopEarlgreyClockSrcMain,
    },
    .irqs = {
      kTopEarlgreyPlicIrqIdHmacHmacDone,
      kTopEarlgreyPlicIrqIdHmacFifoEmpty,
      kTopEarlgreyPlicIrqIdHmacHmacErr,
    },
  },
};
// Device tables for i2c
_Static_assert(kDtI2cRegBlockCount == 1, "Reg block count mismatch");
_Static_assert(kDtI2cClockCount == 1, "Clock count mismatch");
_Static_assert(kDtI2cIrqTypeCount == 15, "IRQ count mismatch");
_Static_assert(kDtI2cCount == 3, "Number of i2c modules mismatch");

const dt_i2c_t kDtI2cList[kDtI2cCount] = {
  // Properties for i2c0
  {
    .device = kDtDeviceIdI2c0,
    .base_addrs = {
      0x40080000,
    },
    .clocks = {
      [kDtI2cClockClk] = kTopEarlgreyClockSrcIoDiv4,
    },
    .irqs = {
      kTopEarlgreyPlicIrqIdI2c0FmtThreshold,
      kTopEarlgreyPlicIrqIdI2c0RxThreshold,
      kTopEarlgreyPlicIrqIdI2c0AcqThreshold,
      kTopEarlgreyPlicIrqIdI2c0RxOverflow,
      kTopEarlgreyPlicIrqIdI2c0ControllerHalt,
      kTopEarlgreyPlicIrqIdI2c0SclInterference,
      kTopEarlgreyPlicIrqIdI2c0SdaInterference,
      kTopEarlgreyPlicIrqIdI2c0StretchTimeout,
      kTopEarlgreyPlicIrqIdI2c0SdaUnstable,
      kTopEarlgreyPlicIrqIdI2c0CmdComplete,
      kTopEarlgreyPlicIrqIdI2c0TxStretch,
      kTopEarlgreyPlicIrqIdI2c0TxThreshold,
      kTopEarlgreyPlicIrqIdI2c0AcqStretch,
      kTopEarlgreyPlicIrqIdI2c0UnexpStop,
      kTopEarlgreyPlicIrqIdI2c0HostTimeout,
    },
  },
  // Properties for i2c1
  {
    .device = kDtDeviceIdI2c1,
    .base_addrs = {
      0x40090000,
    },
    .clocks = {
      [kDtI2cClockClk] = kTopEarlgreyClockSrcIoDiv4,
    },
    .irqs = {
      kTopEarlgreyPlicIrqIdI2c1FmtThreshold,
      kTopEarlgreyPlicIrqIdI2c1RxThreshold,
      kTopEarlgreyPlicIrqIdI2c1AcqThreshold,
      kTopEarlgreyPlicIrqIdI2c1RxOverflow,
      kTopEarlgreyPlicIrqIdI2c1ControllerHalt,
      kTopEarlgreyPlicIrqIdI2c1SclInterference,
      kTopEarlgreyPlicIrqIdI2c1SdaInterference,
      kTopEarlgreyPlicIrqIdI2c1StretchTimeout,
      kTopEarlgreyPlicIrqIdI2c1SdaUnstable,
      kTopEarlgreyPlicIrqIdI2c1CmdComplete,
      kTopEarlgreyPlicIrqIdI2c1TxStretch,
      kTopEarlgreyPlicIrqIdI2c1TxThreshold,
      kTopEarlgreyPlicIrqIdI2c1AcqStretch,
      kTopEarlgreyPlicIrqIdI2c1UnexpStop,
      kTopEarlgreyPlicIrqIdI2c1HostTimeout,
    },
  },
  // Properties for i2c2
  {
    .device = kDtDeviceIdI2c2,
    .base_addrs = {
      0x400A0000,
    },
    .clocks = {
      [kDtI2cClockClk] = kTopEarlgreyClockSrcIoDiv4,
    },
    .irqs = {
      kTopEarlgreyPlicIrqIdI2c2FmtThreshold,
      kTopEarlgreyPlicIrqIdI2c2RxThreshold,
      kTopEarlgreyPlicIrqIdI2c2AcqThreshold,
      kTopEarlgreyPlicIrqIdI2c2RxOverflow,
      kTopEarlgreyPlicIrqIdI2c2ControllerHalt,
      kTopEarlgreyPlicIrqIdI2c2SclInterference,
      kTopEarlgreyPlicIrqIdI2c2SdaInterference,
      kTopEarlgreyPlicIrqIdI2c2StretchTimeout,
      kTopEarlgreyPlicIrqIdI2c2SdaUnstable,
      kTopEarlgreyPlicIrqIdI2c2CmdComplete,
      kTopEarlgreyPlicIrqIdI2c2TxStretch,
      kTopEarlgreyPlicIrqIdI2c2TxThreshold,
      kTopEarlgreyPlicIrqIdI2c2AcqStretch,
      kTopEarlgreyPlicIrqIdI2c2UnexpStop,
      kTopEarlgreyPlicIrqIdI2c2HostTimeout,
    },
  },
};
// Device tables for keymgr
_Static_assert(kDtKeymgrRegBlockCount == 1, "Reg block count mismatch");
_Static_assert(kDtKeymgrClockCount == 2, "Clock count mismatch");
_Static_assert(kDtKeymgrIrqTypeCount == 1, "IRQ count mismatch");
_Static_assert(kDtKeymgrCount == 1, "Number of keymgr modules mismatch");

const dt_keymgr_t kDtKeymgrList[kDtKeymgrCount] = {
  // Properties for keymgr
  {
    .device = kDtDeviceIdKeymgr,
    .base_addrs = {
      0x41140000,
    },
    .clocks = {
      [kDtKeymgrClockClk] = kTopEarlgreyClockSrcMain,
      [kDtKeymgrClockEdn] = kTopEarlgreyClockSrcMain,
    },
    .irqs = {
      kTopEarlgreyPlicIrqIdKeymgrOpDone,
    },
  },
};
// Device tables for kmac
_Static_assert(kDtKmacRegBlockCount == 1, "Reg block count mismatch");
_Static_assert(kDtKmacClockCount == 2, "Clock count mismatch");
_Static_assert(kDtKmacIrqTypeCount == 3, "IRQ count mismatch");
_Static_assert(kDtKmacCount == 1, "Number of kmac modules mismatch");

const dt_kmac_t kDtKmacList[kDtKmacCount] = {
  // Properties for kmac
  {
    .device = kDtDeviceIdKmac,
    .base_addrs = {
      0x41120000,
    },
    .clocks = {
      [kDtKmacClockClk] = kTopEarlgreyClockSrcMain,
      [kDtKmacClockEdn] = kTopEarlgreyClockSrcMain,
    },
    .irqs = {
      kTopEarlgreyPlicIrqIdKmacKmacDone,
      kTopEarlgreyPlicIrqIdKmacFifoEmpty,
      kTopEarlgreyPlicIrqIdKmacKmacErr,
    },
  },
};
// Device tables for lc_ctrl
_Static_assert(kDtLcCtrlRegBlockCount == 1, "Reg block count mismatch");
_Static_assert(kDtLcCtrlClockCount == 2, "Clock count mismatch");
_Static_assert(kDtLcCtrlCount == 1, "Number of lc_ctrl modules mismatch");

const dt_lc_ctrl_t kDtLcCtrlList[kDtLcCtrlCount] = {
  // Properties for lc_ctrl
  {
    .device = kDtDeviceIdLcCtrl,
    .base_addrs = {
      0x40140000,
    },
    .clocks = {
      [kDtLcCtrlClockClk] = kTopEarlgreyClockSrcIoDiv4,
      [kDtLcCtrlClockKmac] = kTopEarlgreyClockSrcMain,
    },
  },
};
// Device tables for otbn
_Static_assert(kDtOtbnRegBlockCount == 1, "Reg block count mismatch");
_Static_assert(kDtOtbnClockCount == 3, "Clock count mismatch");
_Static_assert(kDtOtbnIrqTypeCount == 1, "IRQ count mismatch");
_Static_assert(kDtOtbnCount == 1, "Number of otbn modules mismatch");

const dt_otbn_t kDtOtbnList[kDtOtbnCount] = {
  // Properties for otbn
  {
    .device = kDtDeviceIdOtbn,
    .base_addrs = {
      0x41130000,
    },
    .clocks = {
      [kDtOtbnClockClk] = kTopEarlgreyClockSrcMain,
      [kDtOtbnClockEdn] = kTopEarlgreyClockSrcMain,
      [kDtOtbnClockOtp] = kTopEarlgreyClockSrcIoDiv4,
    },
    .irqs = {
      kTopEarlgreyPlicIrqIdOtbnDone,
    },
  },
};
// Device tables for otp_ctrl
_Static_assert(kDtOtpCtrlRegBlockCount == 2, "Reg block count mismatch");
_Static_assert(kDtOtpCtrlClockCount == 2, "Clock count mismatch");
_Static_assert(kDtOtpCtrlIrqTypeCount == 2, "IRQ count mismatch");
_Static_assert(kDtOtpCtrlCount == 1, "Number of otp_ctrl modules mismatch");

const dt_otp_ctrl_t kDtOtpCtrlList[kDtOtpCtrlCount] = {
  // Properties for otp_ctrl
  {
    .device = kDtDeviceIdOtpCtrl,
    .base_addrs = {
      0x40130000,
      0x40138000,
    },
    .clocks = {
      [kDtOtpCtrlClockClk] = kTopEarlgreyClockSrcIoDiv4,
      [kDtOtpCtrlClockEdn] = kTopEarlgreyClockSrcMain,
    },
    .irqs = {
      kTopEarlgreyPlicIrqIdOtpCtrlOtpOperationDone,
      kTopEarlgreyPlicIrqIdOtpCtrlOtpError,
    },
  },
};
// Device tables for pattgen
_Static_assert(kDtPattgenRegBlockCount == 1, "Reg block count mismatch");
_Static_assert(kDtPattgenClockCount == 1, "Clock count mismatch");
_Static_assert(kDtPattgenIrqTypeCount == 2, "IRQ count mismatch");
_Static_assert(kDtPattgenCount == 1, "Number of pattgen modules mismatch");

const dt_pattgen_t kDtPattgenList[kDtPattgenCount] = {
  // Properties for pattgen
  {
    .device = kDtDeviceIdPattgen,
    .base_addrs = {
      0x400E0000,
    },
    .clocks = {
      [kDtPattgenClockClk] = kTopEarlgreyClockSrcIoDiv4,
    },
    .irqs = {
      kTopEarlgreyPlicIrqIdPattgenDoneCh0,
      kTopEarlgreyPlicIrqIdPattgenDoneCh1,
    },
  },
};
// Device tables for pinmux
_Static_assert(kDtPinmuxRegBlockCount == 1, "Reg block count mismatch");
_Static_assert(kDtPinmuxClockCount == 2, "Clock count mismatch");
_Static_assert(kDtPinmuxCount == 1, "Number of pinmux modules mismatch");

const dt_pinmux_t kDtPinmuxList[kDtPinmuxCount] = {
  // Properties for pinmux_aon
  {
    .device = kDtDeviceIdPinmuxAon,
    .base_addrs = {
      0x40460000,
    },
    .clocks = {
      [kDtPinmuxClockClk] = kTopEarlgreyClockSrcIoDiv4,
      [kDtPinmuxClockAon] = kTopEarlgreyClockSrcAon,
    },
  },
};
// Device tables for pwm
_Static_assert(kDtPwmRegBlockCount == 1, "Reg block count mismatch");
_Static_assert(kDtPwmClockCount == 2, "Clock count mismatch");
_Static_assert(kDtPwmCount == 1, "Number of pwm modules mismatch");

const dt_pwm_t kDtPwmList[kDtPwmCount] = {
  // Properties for pwm_aon
  {
    .device = kDtDeviceIdPwmAon,
    .base_addrs = {
      0x40450000,
    },
    .clocks = {
      [kDtPwmClockClk] = kTopEarlgreyClockSrcIoDiv4,
      [kDtPwmClockCore] = kTopEarlgreyClockSrcAon,
    },
  },
};
// Device tables for pwrmgr
_Static_assert(kDtPwrmgrRegBlockCount == 1, "Reg block count mismatch");
_Static_assert(kDtPwrmgrClockCount == 4, "Clock count mismatch");
_Static_assert(kDtPwrmgrIrqTypeCount == 1, "IRQ count mismatch");
_Static_assert(kDtPwrmgrCount == 1, "Number of pwrmgr modules mismatch");

const dt_pwrmgr_t kDtPwrmgrList[kDtPwrmgrCount] = {
  // Properties for pwrmgr_aon
  {
    .device = kDtDeviceIdPwrmgrAon,
    .base_addrs = {
      0x40400000,
    },
    .clocks = {
      [kDtPwrmgrClockClk] = kTopEarlgreyClockSrcIoDiv4,
      [kDtPwrmgrClockSlow] = kTopEarlgreyClockSrcAon,
      [kDtPwrmgrClockLc] = kTopEarlgreyClockSrcIoDiv4,
      [kDtPwrmgrClockEsc] = kTopEarlgreyClockSrcIoDiv4,
    },
    .irqs = {
      kTopEarlgreyPlicIrqIdPwrmgrAonWakeup,
    },
  },
};
// Device tables for rom_ctrl
_Static_assert(kDtRomCtrlRegBlockCount == 2, "Reg block count mismatch");
_Static_assert(kDtRomCtrlClockCount == 1, "Clock count mismatch");
_Static_assert(kDtRomCtrlCount == 1, "Number of rom_ctrl modules mismatch");

const dt_rom_ctrl_t kDtRomCtrlList[kDtRomCtrlCount] = {
  // Properties for rom_ctrl
  {
    .device = kDtDeviceIdRomCtrl,
    .base_addrs = {
      0x00008000,
      0x411e0000,
    },
    .clocks = {
      [kDtRomCtrlClockClk] = kTopEarlgreyClockSrcMain,
    },
  },
};
// Device tables for rstmgr
_Static_assert(kDtRstmgrRegBlockCount == 1, "Reg block count mismatch");
_Static_assert(kDtRstmgrClockCount == 8, "Clock count mismatch");
_Static_assert(kDtRstmgrCount == 1, "Number of rstmgr modules mismatch");

const dt_rstmgr_t kDtRstmgrList[kDtRstmgrCount] = {
  // Properties for rstmgr_aon
  {
    .device = kDtDeviceIdRstmgrAon,
    .base_addrs = {
      0x40410000,
    },
    .clocks = {
      [kDtRstmgrClockClk] = kTopEarlgreyClockSrcIoDiv4,
      [kDtRstmgrClockPor] = kTopEarlgreyClockSrcIoDiv4,
      [kDtRstmgrClockAon] = kTopEarlgreyClockSrcAon,
      [kDtRstmgrClockMain] = kTopEarlgreyClockSrcMain,
      [kDtRstmgrClockIo] = kTopEarlgreyClockSrcIo,
      [kDtRstmgrClockUsb] = kTopEarlgreyClockSrcUsb,
      [kDtRstmgrClockIoDiv2] = kTopEarlgreyClockSrcIoDiv2,
      [kDtRstmgrClockIoDiv4] = kTopEarlgreyClockSrcIoDiv4,
    },
  },
};
// Device tables for rv_core_ibex
_Static_assert(kDtRvCoreIbexRegBlockCount == 1, "Reg block count mismatch");
_Static_assert(kDtRvCoreIbexClockCount == 4, "Clock count mismatch");
_Static_assert(kDtRvCoreIbexCount == 1, "Number of rv_core_ibex modules mismatch");

const dt_rv_core_ibex_t kDtRvCoreIbexList[kDtRvCoreIbexCount] = {
  // Properties for rv_core_ibex
  {
    .device = kDtDeviceIdRvCoreIbex,
    .base_addrs = {
      0x411F0000,
    },
    .clocks = {
      [kDtRvCoreIbexClockClk] = kTopEarlgreyClockSrcMain,
      [kDtRvCoreIbexClockEdn] = kTopEarlgreyClockSrcMain,
      [kDtRvCoreIbexClockEsc] = kTopEarlgreyClockSrcIoDiv4,
      [kDtRvCoreIbexClockOtp] = kTopEarlgreyClockSrcIoDiv4,
    },
  },
};
// Device tables for rv_dm
_Static_assert(kDtRvDmRegBlockCount == 2, "Reg block count mismatch");
_Static_assert(kDtRvDmClockCount == 2, "Clock count mismatch");
_Static_assert(kDtRvDmCount == 1, "Number of rv_dm modules mismatch");

const dt_rv_dm_t kDtRvDmList[kDtRvDmCount] = {
  // Properties for rv_dm
  {
    .device = kDtDeviceIdRvDm,
    .base_addrs = {
      0x00010000,
      0x41200000,
    },
    .clocks = {
      [kDtRvDmClockClk] = kTopEarlgreyClockSrcMain,
      [kDtRvDmClockLc] = kTopEarlgreyClockSrcMain,
    },
  },
};
// Device tables for rv_plic
_Static_assert(kDtRvPlicRegBlockCount == 1, "Reg block count mismatch");
_Static_assert(kDtRvPlicClockCount == 1, "Clock count mismatch");
_Static_assert(kDtRvPlicCount == 1, "Number of rv_plic modules mismatch");

const dt_rv_plic_t kDtRvPlicList[kDtRvPlicCount] = {
  // Properties for rv_plic
  {
    .device = kDtDeviceIdRvPlic,
    .base_addrs = {
      0x48000000,
    },
    .clocks = {
      [kDtRvPlicClockClk] = kTopEarlgreyClockSrcMain,
    },
  },
};
// Device tables for rv_timer
_Static_assert(kDtRvTimerRegBlockCount == 1, "Reg block count mismatch");
_Static_assert(kDtRvTimerClockCount == 1, "Clock count mismatch");
_Static_assert(kDtRvTimerIrqTypeCount == 1, "IRQ count mismatch");
_Static_assert(kDtRvTimerCount == 1, "Number of rv_timer modules mismatch");

const dt_rv_timer_t kDtRvTimerList[kDtRvTimerCount] = {
  // Properties for rv_timer
  {
    .device = kDtDeviceIdRvTimer,
    .base_addrs = {
      0x40100000,
    },
    .clocks = {
      [kDtRvTimerClockClk] = kTopEarlgreyClockSrcIoDiv4,
    },
    .irqs = {
      kTopEarlgreyPlicIrqIdRvTimerTimerExpiredHart0Timer0,
    },
  },
};
// Device tables for sensor_ctrl
_Static_assert(kDtSensorCtrlRegBlockCount == 1, "Reg block count mismatch");
_Static_assert(kDtSensorCtrlClockCount == 2, "Clock count mismatch");
_Static_assert(kDtSensorCtrlIrqTypeCount == 2, "IRQ count mismatch");
_Static_assert(kDtSensorCtrlCount == 1, "Number of sensor_ctrl modules mismatch");

const dt_sensor_ctrl_t kDtSensorCtrlList[kDtSensorCtrlCount] = {
  // Properties for sensor_ctrl_aon
  {
    .device = kDtDeviceIdSensorCtrlAon,
    .base_addrs = {
      0x40490000,
    },
    .clocks = {
      [kDtSensorCtrlClockClk] = kTopEarlgreyClockSrcIoDiv4,
      [kDtSensorCtrlClockAon] = kTopEarlgreyClockSrcAon,
    },
    .irqs = {
      kTopEarlgreyPlicIrqIdSensorCtrlAonIoStatusChange,
      kTopEarlgreyPlicIrqIdSensorCtrlAonInitStatusChange,
    },
  },
};
// Device tables for spi_device
_Static_assert(kDtSpiDeviceRegBlockCount == 1, "Reg block count mismatch");
_Static_assert(kDtSpiDeviceClockCount == 1, "Clock count mismatch");
_Static_assert(kDtSpiDeviceIrqTypeCount == 8, "IRQ count mismatch");
_Static_assert(kDtSpiDeviceCount == 1, "Number of spi_device modules mismatch");

const dt_spi_device_t kDtSpiDeviceList[kDtSpiDeviceCount] = {
  // Properties for spi_device
  {
    .device = kDtDeviceIdSpiDevice,
    .base_addrs = {
      0x40050000,
    },
    .clocks = {
      [kDtSpiDeviceClockClk] = kTopEarlgreyClockSrcIoDiv4,
    },
    .irqs = {
      kTopEarlgreyPlicIrqIdSpiDeviceUploadCmdfifoNotEmpty,
      kTopEarlgreyPlicIrqIdSpiDeviceUploadPayloadNotEmpty,
      kTopEarlgreyPlicIrqIdSpiDeviceUploadPayloadOverflow,
      kTopEarlgreyPlicIrqIdSpiDeviceReadbufWatermark,
      kTopEarlgreyPlicIrqIdSpiDeviceReadbufFlip,
      kTopEarlgreyPlicIrqIdSpiDeviceTpmHeaderNotEmpty,
      kTopEarlgreyPlicIrqIdSpiDeviceTpmRdfifoCmdEnd,
      kTopEarlgreyPlicIrqIdSpiDeviceTpmRdfifoDrop,
    },
  },
};
// Device tables for spi_host
_Static_assert(kDtSpiHostRegBlockCount == 1, "Reg block count mismatch");
_Static_assert(kDtSpiHostClockCount == 1, "Clock count mismatch");
_Static_assert(kDtSpiHostIrqTypeCount == 2, "IRQ count mismatch");
_Static_assert(kDtSpiHostCount == 2, "Number of spi_host modules mismatch");

const dt_spi_host_t kDtSpiHostList[kDtSpiHostCount] = {
  // Properties for spi_host0
  {
    .device = kDtDeviceIdSpiHost0,
    .base_addrs = {
      0x40300000,
    },
    .clocks = {
      [kDtSpiHostClockClk] = kTopEarlgreyClockSrcIo,
    },
    .irqs = {
      kTopEarlgreyPlicIrqIdSpiHost0Error,
      kTopEarlgreyPlicIrqIdSpiHost0SpiEvent,
    },
  },
  // Properties for spi_host1
  {
    .device = kDtDeviceIdSpiHost1,
    .base_addrs = {
      0x40310000,
    },
    .clocks = {
      [kDtSpiHostClockClk] = kTopEarlgreyClockSrcIoDiv2,
    },
    .irqs = {
      kTopEarlgreyPlicIrqIdSpiHost1Error,
      kTopEarlgreyPlicIrqIdSpiHost1SpiEvent,
    },
  },
};
// Device tables for sram_ctrl
_Static_assert(kDtSramCtrlRegBlockCount == 2, "Reg block count mismatch");
_Static_assert(kDtSramCtrlClockCount == 2, "Clock count mismatch");
_Static_assert(kDtSramCtrlCount == 2, "Number of sram_ctrl modules mismatch");

const dt_sram_ctrl_t kDtSramCtrlList[kDtSramCtrlCount] = {
  // Properties for sram_ctrl_ret_aon
  {
    .device = kDtDeviceIdSramCtrlRetAon,
    .base_addrs = {
      0x40500000,
      0x40600000,
    },
    .clocks = {
      [kDtSramCtrlClockClk] = kTopEarlgreyClockSrcIoDiv4,
      [kDtSramCtrlClockOtp] = kTopEarlgreyClockSrcIoDiv4,
    },
  },
  // Properties for sram_ctrl_main
  {
    .device = kDtDeviceIdSramCtrlMain,
    .base_addrs = {
      0x411C0000,
      0x10000000,
    },
    .clocks = {
      [kDtSramCtrlClockClk] = kTopEarlgreyClockSrcMain,
      [kDtSramCtrlClockOtp] = kTopEarlgreyClockSrcIoDiv4,
    },
  },
};
// Device tables for sysrst_ctrl
_Static_assert(kDtSysrstCtrlRegBlockCount == 1, "Reg block count mismatch");
_Static_assert(kDtSysrstCtrlClockCount == 2, "Clock count mismatch");
_Static_assert(kDtSysrstCtrlIrqTypeCount == 1, "IRQ count mismatch");
_Static_assert(kDtSysrstCtrlCount == 1, "Number of sysrst_ctrl modules mismatch");

const dt_sysrst_ctrl_t kDtSysrstCtrlList[kDtSysrstCtrlCount] = {
  // Properties for sysrst_ctrl_aon
  {
    .device = kDtDeviceIdSysrstCtrlAon,
    .base_addrs = {
      0x40430000,
    },
    .clocks = {
      [kDtSysrstCtrlClockClk] = kTopEarlgreyClockSrcIoDiv4,
      [kDtSysrstCtrlClockAon] = kTopEarlgreyClockSrcAon,
    },
    .irqs = {
      kTopEarlgreyPlicIrqIdSysrstCtrlAonEventDetected,
    },
  },
};
// Device tables for uart
_Static_assert(kDtUartRegBlockCount == 1, "Reg block count mismatch");
_Static_assert(kDtUartClockCount == 1, "Clock count mismatch");
_Static_assert(kDtUartIrqTypeCount == 9, "IRQ count mismatch");
_Static_assert(kDtUartCount == 4, "Number of uart modules mismatch");

const dt_uart_t kDtUartList[kDtUartCount] = {
  // Properties for uart0
  {
    .device = kDtDeviceIdUart0,
    .base_addrs = {
      0x40000000,
    },
    .clocks = {
      [kDtUartClockClk] = kTopEarlgreyClockSrcIoDiv4,
    },
    .irqs = {
      kTopEarlgreyPlicIrqIdUart0TxWatermark,
      kTopEarlgreyPlicIrqIdUart0RxWatermark,
      kTopEarlgreyPlicIrqIdUart0TxDone,
      kTopEarlgreyPlicIrqIdUart0RxOverflow,
      kTopEarlgreyPlicIrqIdUart0RxFrameErr,
      kTopEarlgreyPlicIrqIdUart0RxBreakErr,
      kTopEarlgreyPlicIrqIdUart0RxTimeout,
      kTopEarlgreyPlicIrqIdUart0RxParityErr,
      kTopEarlgreyPlicIrqIdUart0TxEmpty,
    },
  },
  // Properties for uart1
  {
    .device = kDtDeviceIdUart1,
    .base_addrs = {
      0x40010000,
    },
    .clocks = {
      [kDtUartClockClk] = kTopEarlgreyClockSrcIoDiv4,
    },
    .irqs = {
      kTopEarlgreyPlicIrqIdUart1TxWatermark,
      kTopEarlgreyPlicIrqIdUart1RxWatermark,
      kTopEarlgreyPlicIrqIdUart1TxDone,
      kTopEarlgreyPlicIrqIdUart1RxOverflow,
      kTopEarlgreyPlicIrqIdUart1RxFrameErr,
      kTopEarlgreyPlicIrqIdUart1RxBreakErr,
      kTopEarlgreyPlicIrqIdUart1RxTimeout,
      kTopEarlgreyPlicIrqIdUart1RxParityErr,
      kTopEarlgreyPlicIrqIdUart1TxEmpty,
    },
  },
  // Properties for uart2
  {
    .device = kDtDeviceIdUart2,
    .base_addrs = {
      0x40020000,
    },
    .clocks = {
      [kDtUartClockClk] = kTopEarlgreyClockSrcIoDiv4,
    },
    .irqs = {
      kTopEarlgreyPlicIrqIdUart2TxWatermark,
      kTopEarlgreyPlicIrqIdUart2RxWatermark,
      kTopEarlgreyPlicIrqIdUart2TxDone,
      kTopEarlgreyPlicIrqIdUart2RxOverflow,
      kTopEarlgreyPlicIrqIdUart2RxFrameErr,
      kTopEarlgreyPlicIrqIdUart2RxBreakErr,
      kTopEarlgreyPlicIrqIdUart2RxTimeout,
      kTopEarlgreyPlicIrqIdUart2RxParityErr,
      kTopEarlgreyPlicIrqIdUart2TxEmpty,
    },
  },
  // Properties for uart3
  {
    .device = kDtDeviceIdUart3,
    .base_addrs = {
      0x40030000,
    },
    .clocks = {
      [kDtUartClockClk] = kTopEarlgreyClockSrcIoDiv4,
    },
    .irqs = {
      kTopEarlgreyPlicIrqIdUart3TxWatermark,
      kTopEarlgreyPlicIrqIdUart3RxWatermark,
      kTopEarlgreyPlicIrqIdUart3TxDone,
      kTopEarlgreyPlicIrqIdUart3RxOverflow,
      kTopEarlgreyPlicIrqIdUart3RxFrameErr,
      kTopEarlgreyPlicIrqIdUart3RxBreakErr,
      kTopEarlgreyPlicIrqIdUart3RxTimeout,
      kTopEarlgreyPlicIrqIdUart3RxParityErr,
      kTopEarlgreyPlicIrqIdUart3TxEmpty,
    },
  },
};
// Device tables for usbdev
_Static_assert(kDtUsbdevRegBlockCount == 1, "Reg block count mismatch");
_Static_assert(kDtUsbdevClockCount == 2, "Clock count mismatch");
_Static_assert(kDtUsbdevIrqTypeCount == 18, "IRQ count mismatch");
_Static_assert(kDtUsbdevCount == 1, "Number of usbdev modules mismatch");

const dt_usbdev_t kDtUsbdevList[kDtUsbdevCount] = {
  // Properties for usbdev
  {
    .device = kDtDeviceIdUsbdev,
    .base_addrs = {
      0x40320000,
    },
    .clocks = {
      [kDtUsbdevClockClk] = kTopEarlgreyClockSrcUsb,
      [kDtUsbdevClockAon] = kTopEarlgreyClockSrcAon,
    },
    .irqs = {
      kTopEarlgreyPlicIrqIdUsbdevPktReceived,
      kTopEarlgreyPlicIrqIdUsbdevPktSent,
      kTopEarlgreyPlicIrqIdUsbdevDisconnected,
      kTopEarlgreyPlicIrqIdUsbdevHostLost,
      kTopEarlgreyPlicIrqIdUsbdevLinkReset,
      kTopEarlgreyPlicIrqIdUsbdevLinkSuspend,
      kTopEarlgreyPlicIrqIdUsbdevLinkResume,
      kTopEarlgreyPlicIrqIdUsbdevAvOutEmpty,
      kTopEarlgreyPlicIrqIdUsbdevRxFull,
      kTopEarlgreyPlicIrqIdUsbdevAvOverflow,
      kTopEarlgreyPlicIrqIdUsbdevLinkInErr,
      kTopEarlgreyPlicIrqIdUsbdevRxCrcErr,
      kTopEarlgreyPlicIrqIdUsbdevRxPidErr,
      kTopEarlgreyPlicIrqIdUsbdevRxBitstuffErr,
      kTopEarlgreyPlicIrqIdUsbdevFrame,
      kTopEarlgreyPlicIrqIdUsbdevPowered,
      kTopEarlgreyPlicIrqIdUsbdevLinkOutErr,
      kTopEarlgreyPlicIrqIdUsbdevAvSetupEmpty,
    },
  },
};


enum {
  kDtIrqIdCount = 186,
};

static const dt_device_t device_from_irq[kDtIrqIdCount] = {
    [kTopEarlgreyPlicIrqIdNone] = kDtDeviceIdUnknown,
    [kTopEarlgreyPlicIrqIdUart0TxWatermark] = kDtDeviceIdUart0,
    [kTopEarlgreyPlicIrqIdUart0RxWatermark] = kDtDeviceIdUart0,
    [kTopEarlgreyPlicIrqIdUart0TxDone] = kDtDeviceIdUart0,
    [kTopEarlgreyPlicIrqIdUart0RxOverflow] = kDtDeviceIdUart0,
    [kTopEarlgreyPlicIrqIdUart0RxFrameErr] = kDtDeviceIdUart0,
    [kTopEarlgreyPlicIrqIdUart0RxBreakErr] = kDtDeviceIdUart0,
    [kTopEarlgreyPlicIrqIdUart0RxTimeout] = kDtDeviceIdUart0,
    [kTopEarlgreyPlicIrqIdUart0RxParityErr] = kDtDeviceIdUart0,
    [kTopEarlgreyPlicIrqIdUart0TxEmpty] = kDtDeviceIdUart0,
    [kTopEarlgreyPlicIrqIdUart1TxWatermark] = kDtDeviceIdUart1,
    [kTopEarlgreyPlicIrqIdUart1RxWatermark] = kDtDeviceIdUart1,
    [kTopEarlgreyPlicIrqIdUart1TxDone] = kDtDeviceIdUart1,
    [kTopEarlgreyPlicIrqIdUart1RxOverflow] = kDtDeviceIdUart1,
    [kTopEarlgreyPlicIrqIdUart1RxFrameErr] = kDtDeviceIdUart1,
    [kTopEarlgreyPlicIrqIdUart1RxBreakErr] = kDtDeviceIdUart1,
    [kTopEarlgreyPlicIrqIdUart1RxTimeout] = kDtDeviceIdUart1,
    [kTopEarlgreyPlicIrqIdUart1RxParityErr] = kDtDeviceIdUart1,
    [kTopEarlgreyPlicIrqIdUart1TxEmpty] = kDtDeviceIdUart1,
    [kTopEarlgreyPlicIrqIdUart2TxWatermark] = kDtDeviceIdUart2,
    [kTopEarlgreyPlicIrqIdUart2RxWatermark] = kDtDeviceIdUart2,
    [kTopEarlgreyPlicIrqIdUart2TxDone] = kDtDeviceIdUart2,
    [kTopEarlgreyPlicIrqIdUart2RxOverflow] = kDtDeviceIdUart2,
    [kTopEarlgreyPlicIrqIdUart2RxFrameErr] = kDtDeviceIdUart2,
    [kTopEarlgreyPlicIrqIdUart2RxBreakErr] = kDtDeviceIdUart2,
    [kTopEarlgreyPlicIrqIdUart2RxTimeout] = kDtDeviceIdUart2,
    [kTopEarlgreyPlicIrqIdUart2RxParityErr] = kDtDeviceIdUart2,
    [kTopEarlgreyPlicIrqIdUart2TxEmpty] = kDtDeviceIdUart2,
    [kTopEarlgreyPlicIrqIdUart3TxWatermark] = kDtDeviceIdUart3,
    [kTopEarlgreyPlicIrqIdUart3RxWatermark] = kDtDeviceIdUart3,
    [kTopEarlgreyPlicIrqIdUart3TxDone] = kDtDeviceIdUart3,
    [kTopEarlgreyPlicIrqIdUart3RxOverflow] = kDtDeviceIdUart3,
    [kTopEarlgreyPlicIrqIdUart3RxFrameErr] = kDtDeviceIdUart3,
    [kTopEarlgreyPlicIrqIdUart3RxBreakErr] = kDtDeviceIdUart3,
    [kTopEarlgreyPlicIrqIdUart3RxTimeout] = kDtDeviceIdUart3,
    [kTopEarlgreyPlicIrqIdUart3RxParityErr] = kDtDeviceIdUart3,
    [kTopEarlgreyPlicIrqIdUart3TxEmpty] = kDtDeviceIdUart3,
    [kTopEarlgreyPlicIrqIdGpioGpio0] = kDtDeviceIdGpio,
    [kTopEarlgreyPlicIrqIdGpioGpio1] = kDtDeviceIdGpio,
    [kTopEarlgreyPlicIrqIdGpioGpio2] = kDtDeviceIdGpio,
    [kTopEarlgreyPlicIrqIdGpioGpio3] = kDtDeviceIdGpio,
    [kTopEarlgreyPlicIrqIdGpioGpio4] = kDtDeviceIdGpio,
    [kTopEarlgreyPlicIrqIdGpioGpio5] = kDtDeviceIdGpio,
    [kTopEarlgreyPlicIrqIdGpioGpio6] = kDtDeviceIdGpio,
    [kTopEarlgreyPlicIrqIdGpioGpio7] = kDtDeviceIdGpio,
    [kTopEarlgreyPlicIrqIdGpioGpio8] = kDtDeviceIdGpio,
    [kTopEarlgreyPlicIrqIdGpioGpio9] = kDtDeviceIdGpio,
    [kTopEarlgreyPlicIrqIdGpioGpio10] = kDtDeviceIdGpio,
    [kTopEarlgreyPlicIrqIdGpioGpio11] = kDtDeviceIdGpio,
    [kTopEarlgreyPlicIrqIdGpioGpio12] = kDtDeviceIdGpio,
    [kTopEarlgreyPlicIrqIdGpioGpio13] = kDtDeviceIdGpio,
    [kTopEarlgreyPlicIrqIdGpioGpio14] = kDtDeviceIdGpio,
    [kTopEarlgreyPlicIrqIdGpioGpio15] = kDtDeviceIdGpio,
    [kTopEarlgreyPlicIrqIdGpioGpio16] = kDtDeviceIdGpio,
    [kTopEarlgreyPlicIrqIdGpioGpio17] = kDtDeviceIdGpio,
    [kTopEarlgreyPlicIrqIdGpioGpio18] = kDtDeviceIdGpio,
    [kTopEarlgreyPlicIrqIdGpioGpio19] = kDtDeviceIdGpio,
    [kTopEarlgreyPlicIrqIdGpioGpio20] = kDtDeviceIdGpio,
    [kTopEarlgreyPlicIrqIdGpioGpio21] = kDtDeviceIdGpio,
    [kTopEarlgreyPlicIrqIdGpioGpio22] = kDtDeviceIdGpio,
    [kTopEarlgreyPlicIrqIdGpioGpio23] = kDtDeviceIdGpio,
    [kTopEarlgreyPlicIrqIdGpioGpio24] = kDtDeviceIdGpio,
    [kTopEarlgreyPlicIrqIdGpioGpio25] = kDtDeviceIdGpio,
    [kTopEarlgreyPlicIrqIdGpioGpio26] = kDtDeviceIdGpio,
    [kTopEarlgreyPlicIrqIdGpioGpio27] = kDtDeviceIdGpio,
    [kTopEarlgreyPlicIrqIdGpioGpio28] = kDtDeviceIdGpio,
    [kTopEarlgreyPlicIrqIdGpioGpio29] = kDtDeviceIdGpio,
    [kTopEarlgreyPlicIrqIdGpioGpio30] = kDtDeviceIdGpio,
    [kTopEarlgreyPlicIrqIdGpioGpio31] = kDtDeviceIdGpio,
    [kTopEarlgreyPlicIrqIdSpiDeviceUploadCmdfifoNotEmpty] = kDtDeviceIdSpiDevice,
    [kTopEarlgreyPlicIrqIdSpiDeviceUploadPayloadNotEmpty] = kDtDeviceIdSpiDevice,
    [kTopEarlgreyPlicIrqIdSpiDeviceUploadPayloadOverflow] = kDtDeviceIdSpiDevice,
    [kTopEarlgreyPlicIrqIdSpiDeviceReadbufWatermark] = kDtDeviceIdSpiDevice,
    [kTopEarlgreyPlicIrqIdSpiDeviceReadbufFlip] = kDtDeviceIdSpiDevice,
    [kTopEarlgreyPlicIrqIdSpiDeviceTpmHeaderNotEmpty] = kDtDeviceIdSpiDevice,
    [kTopEarlgreyPlicIrqIdSpiDeviceTpmRdfifoCmdEnd] = kDtDeviceIdSpiDevice,
    [kTopEarlgreyPlicIrqIdSpiDeviceTpmRdfifoDrop] = kDtDeviceIdSpiDevice,
    [kTopEarlgreyPlicIrqIdI2c0FmtThreshold] = kDtDeviceIdI2c0,
    [kTopEarlgreyPlicIrqIdI2c0RxThreshold] = kDtDeviceIdI2c0,
    [kTopEarlgreyPlicIrqIdI2c0AcqThreshold] = kDtDeviceIdI2c0,
    [kTopEarlgreyPlicIrqIdI2c0RxOverflow] = kDtDeviceIdI2c0,
    [kTopEarlgreyPlicIrqIdI2c0ControllerHalt] = kDtDeviceIdI2c0,
    [kTopEarlgreyPlicIrqIdI2c0SclInterference] = kDtDeviceIdI2c0,
    [kTopEarlgreyPlicIrqIdI2c0SdaInterference] = kDtDeviceIdI2c0,
    [kTopEarlgreyPlicIrqIdI2c0StretchTimeout] = kDtDeviceIdI2c0,
    [kTopEarlgreyPlicIrqIdI2c0SdaUnstable] = kDtDeviceIdI2c0,
    [kTopEarlgreyPlicIrqIdI2c0CmdComplete] = kDtDeviceIdI2c0,
    [kTopEarlgreyPlicIrqIdI2c0TxStretch] = kDtDeviceIdI2c0,
    [kTopEarlgreyPlicIrqIdI2c0TxThreshold] = kDtDeviceIdI2c0,
    [kTopEarlgreyPlicIrqIdI2c0AcqStretch] = kDtDeviceIdI2c0,
    [kTopEarlgreyPlicIrqIdI2c0UnexpStop] = kDtDeviceIdI2c0,
    [kTopEarlgreyPlicIrqIdI2c0HostTimeout] = kDtDeviceIdI2c0,
    [kTopEarlgreyPlicIrqIdI2c1FmtThreshold] = kDtDeviceIdI2c1,
    [kTopEarlgreyPlicIrqIdI2c1RxThreshold] = kDtDeviceIdI2c1,
    [kTopEarlgreyPlicIrqIdI2c1AcqThreshold] = kDtDeviceIdI2c1,
    [kTopEarlgreyPlicIrqIdI2c1RxOverflow] = kDtDeviceIdI2c1,
    [kTopEarlgreyPlicIrqIdI2c1ControllerHalt] = kDtDeviceIdI2c1,
    [kTopEarlgreyPlicIrqIdI2c1SclInterference] = kDtDeviceIdI2c1,
    [kTopEarlgreyPlicIrqIdI2c1SdaInterference] = kDtDeviceIdI2c1,
    [kTopEarlgreyPlicIrqIdI2c1StretchTimeout] = kDtDeviceIdI2c1,
    [kTopEarlgreyPlicIrqIdI2c1SdaUnstable] = kDtDeviceIdI2c1,
    [kTopEarlgreyPlicIrqIdI2c1CmdComplete] = kDtDeviceIdI2c1,
    [kTopEarlgreyPlicIrqIdI2c1TxStretch] = kDtDeviceIdI2c1,
    [kTopEarlgreyPlicIrqIdI2c1TxThreshold] = kDtDeviceIdI2c1,
    [kTopEarlgreyPlicIrqIdI2c1AcqStretch] = kDtDeviceIdI2c1,
    [kTopEarlgreyPlicIrqIdI2c1UnexpStop] = kDtDeviceIdI2c1,
    [kTopEarlgreyPlicIrqIdI2c1HostTimeout] = kDtDeviceIdI2c1,
    [kTopEarlgreyPlicIrqIdI2c2FmtThreshold] = kDtDeviceIdI2c2,
    [kTopEarlgreyPlicIrqIdI2c2RxThreshold] = kDtDeviceIdI2c2,
    [kTopEarlgreyPlicIrqIdI2c2AcqThreshold] = kDtDeviceIdI2c2,
    [kTopEarlgreyPlicIrqIdI2c2RxOverflow] = kDtDeviceIdI2c2,
    [kTopEarlgreyPlicIrqIdI2c2ControllerHalt] = kDtDeviceIdI2c2,
    [kTopEarlgreyPlicIrqIdI2c2SclInterference] = kDtDeviceIdI2c2,
    [kTopEarlgreyPlicIrqIdI2c2SdaInterference] = kDtDeviceIdI2c2,
    [kTopEarlgreyPlicIrqIdI2c2StretchTimeout] = kDtDeviceIdI2c2,
    [kTopEarlgreyPlicIrqIdI2c2SdaUnstable] = kDtDeviceIdI2c2,
    [kTopEarlgreyPlicIrqIdI2c2CmdComplete] = kDtDeviceIdI2c2,
    [kTopEarlgreyPlicIrqIdI2c2TxStretch] = kDtDeviceIdI2c2,
    [kTopEarlgreyPlicIrqIdI2c2TxThreshold] = kDtDeviceIdI2c2,
    [kTopEarlgreyPlicIrqIdI2c2AcqStretch] = kDtDeviceIdI2c2,
    [kTopEarlgreyPlicIrqIdI2c2UnexpStop] = kDtDeviceIdI2c2,
    [kTopEarlgreyPlicIrqIdI2c2HostTimeout] = kDtDeviceIdI2c2,
    [kTopEarlgreyPlicIrqIdPattgenDoneCh0] = kDtDeviceIdPattgen,
    [kTopEarlgreyPlicIrqIdPattgenDoneCh1] = kDtDeviceIdPattgen,
    [kTopEarlgreyPlicIrqIdRvTimerTimerExpiredHart0Timer0] = kDtDeviceIdRvTimer,
    [kTopEarlgreyPlicIrqIdOtpCtrlOtpOperationDone] = kDtDeviceIdOtpCtrl,
    [kTopEarlgreyPlicIrqIdOtpCtrlOtpError] = kDtDeviceIdOtpCtrl,
    [kTopEarlgreyPlicIrqIdAlertHandlerClassa] = kDtDeviceIdAlertHandler,
    [kTopEarlgreyPlicIrqIdAlertHandlerClassb] = kDtDeviceIdAlertHandler,
    [kTopEarlgreyPlicIrqIdAlertHandlerClassc] = kDtDeviceIdAlertHandler,
    [kTopEarlgreyPlicIrqIdAlertHandlerClassd] = kDtDeviceIdAlertHandler,
    [kTopEarlgreyPlicIrqIdSpiHost0Error] = kDtDeviceIdSpiHost0,
    [kTopEarlgreyPlicIrqIdSpiHost0SpiEvent] = kDtDeviceIdSpiHost0,
    [kTopEarlgreyPlicIrqIdSpiHost1Error] = kDtDeviceIdSpiHost1,
    [kTopEarlgreyPlicIrqIdSpiHost1SpiEvent] = kDtDeviceIdSpiHost1,
    [kTopEarlgreyPlicIrqIdUsbdevPktReceived] = kDtDeviceIdUsbdev,
    [kTopEarlgreyPlicIrqIdUsbdevPktSent] = kDtDeviceIdUsbdev,
    [kTopEarlgreyPlicIrqIdUsbdevDisconnected] = kDtDeviceIdUsbdev,
    [kTopEarlgreyPlicIrqIdUsbdevHostLost] = kDtDeviceIdUsbdev,
    [kTopEarlgreyPlicIrqIdUsbdevLinkReset] = kDtDeviceIdUsbdev,
    [kTopEarlgreyPlicIrqIdUsbdevLinkSuspend] = kDtDeviceIdUsbdev,
    [kTopEarlgreyPlicIrqIdUsbdevLinkResume] = kDtDeviceIdUsbdev,
    [kTopEarlgreyPlicIrqIdUsbdevAvOutEmpty] = kDtDeviceIdUsbdev,
    [kTopEarlgreyPlicIrqIdUsbdevRxFull] = kDtDeviceIdUsbdev,
    [kTopEarlgreyPlicIrqIdUsbdevAvOverflow] = kDtDeviceIdUsbdev,
    [kTopEarlgreyPlicIrqIdUsbdevLinkInErr] = kDtDeviceIdUsbdev,
    [kTopEarlgreyPlicIrqIdUsbdevRxCrcErr] = kDtDeviceIdUsbdev,
    [kTopEarlgreyPlicIrqIdUsbdevRxPidErr] = kDtDeviceIdUsbdev,
    [kTopEarlgreyPlicIrqIdUsbdevRxBitstuffErr] = kDtDeviceIdUsbdev,
    [kTopEarlgreyPlicIrqIdUsbdevFrame] = kDtDeviceIdUsbdev,
    [kTopEarlgreyPlicIrqIdUsbdevPowered] = kDtDeviceIdUsbdev,
    [kTopEarlgreyPlicIrqIdUsbdevLinkOutErr] = kDtDeviceIdUsbdev,
    [kTopEarlgreyPlicIrqIdUsbdevAvSetupEmpty] = kDtDeviceIdUsbdev,
    [kTopEarlgreyPlicIrqIdPwrmgrAonWakeup] = kDtDeviceIdPwrmgrAon,
    [kTopEarlgreyPlicIrqIdSysrstCtrlAonEventDetected] = kDtDeviceIdSysrstCtrlAon,
    [kTopEarlgreyPlicIrqIdAdcCtrlAonMatchPending] = kDtDeviceIdAdcCtrlAon,
    [kTopEarlgreyPlicIrqIdAonTimerAonWkupTimerExpired] = kDtDeviceIdAonTimerAon,
    [kTopEarlgreyPlicIrqIdAonTimerAonWdogTimerBark] = kDtDeviceIdAonTimerAon,
    [kTopEarlgreyPlicIrqIdSensorCtrlAonIoStatusChange] = kDtDeviceIdSensorCtrlAon,
    [kTopEarlgreyPlicIrqIdSensorCtrlAonInitStatusChange] = kDtDeviceIdSensorCtrlAon,
    [kTopEarlgreyPlicIrqIdFlashCtrlProgEmpty] = kDtDeviceIdFlashCtrl,
    [kTopEarlgreyPlicIrqIdFlashCtrlProgLvl] = kDtDeviceIdFlashCtrl,
    [kTopEarlgreyPlicIrqIdFlashCtrlRdFull] = kDtDeviceIdFlashCtrl,
    [kTopEarlgreyPlicIrqIdFlashCtrlRdLvl] = kDtDeviceIdFlashCtrl,
    [kTopEarlgreyPlicIrqIdFlashCtrlOpDone] = kDtDeviceIdFlashCtrl,
    [kTopEarlgreyPlicIrqIdFlashCtrlCorrErr] = kDtDeviceIdFlashCtrl,
    [kTopEarlgreyPlicIrqIdHmacHmacDone] = kDtDeviceIdHmac,
    [kTopEarlgreyPlicIrqIdHmacFifoEmpty] = kDtDeviceIdHmac,
    [kTopEarlgreyPlicIrqIdHmacHmacErr] = kDtDeviceIdHmac,
    [kTopEarlgreyPlicIrqIdKmacKmacDone] = kDtDeviceIdKmac,
    [kTopEarlgreyPlicIrqIdKmacFifoEmpty] = kDtDeviceIdKmac,
    [kTopEarlgreyPlicIrqIdKmacKmacErr] = kDtDeviceIdKmac,
    [kTopEarlgreyPlicIrqIdOtbnDone] = kDtDeviceIdOtbn,
    [kTopEarlgreyPlicIrqIdKeymgrOpDone] = kDtDeviceIdKeymgr,
    [kTopEarlgreyPlicIrqIdCsrngCsCmdReqDone] = kDtDeviceIdCsrng,
    [kTopEarlgreyPlicIrqIdCsrngCsEntropyReq] = kDtDeviceIdCsrng,
    [kTopEarlgreyPlicIrqIdCsrngCsHwInstExc] = kDtDeviceIdCsrng,
    [kTopEarlgreyPlicIrqIdCsrngCsFatalErr] = kDtDeviceIdCsrng,
    [kTopEarlgreyPlicIrqIdEntropySrcEsEntropyValid] = kDtDeviceIdEntropySrc,
    [kTopEarlgreyPlicIrqIdEntropySrcEsHealthTestFailed] = kDtDeviceIdEntropySrc,
    [kTopEarlgreyPlicIrqIdEntropySrcEsObserveFifoReady] = kDtDeviceIdEntropySrc,
    [kTopEarlgreyPlicIrqIdEntropySrcEsFatalErr] = kDtDeviceIdEntropySrc,
    [kTopEarlgreyPlicIrqIdEdn0EdnCmdReqDone] = kDtDeviceIdEdn0,
    [kTopEarlgreyPlicIrqIdEdn0EdnFatalErr] = kDtDeviceIdEdn0,
    [kTopEarlgreyPlicIrqIdEdn1EdnCmdReqDone] = kDtDeviceIdEdn1,
    [kTopEarlgreyPlicIrqIdEdn1EdnFatalErr] = kDtDeviceIdEdn1,
};

/**
 * Return device ID for a given peripheral.
 */
dt_device_t dt_irq_to_device(uint32_t irq) {
  if (irq < kDtIrqIdCount) {
    return device_from_irq[irq];
  }
  return kDtDeviceUnknown;
}

static const dt_device_t device_irq_type_from_irq[kDtIrqIdCount] = {
    [kTopEarlgreyPlicIrqIdNone] = kTopEarlgreyPlicIrqIdNone,
    [kTopEarlgreyPlicIrqIdUart0TxWatermark] = kDtUartIrqTypeTxWatermark,
    [kTopEarlgreyPlicIrqIdUart0RxWatermark] = kDtUartIrqTypeRxWatermark,
    [kTopEarlgreyPlicIrqIdUart0TxDone] = kDtUartIrqTypeTxDone,
    [kTopEarlgreyPlicIrqIdUart0RxOverflow] = kDtUartIrqTypeRxOverflow,
    [kTopEarlgreyPlicIrqIdUart0RxFrameErr] = kDtUartIrqTypeRxFrameErr,
    [kTopEarlgreyPlicIrqIdUart0RxBreakErr] = kDtUartIrqTypeRxBreakErr,
    [kTopEarlgreyPlicIrqIdUart0RxTimeout] = kDtUartIrqTypeRxTimeout,
    [kTopEarlgreyPlicIrqIdUart0RxParityErr] = kDtUartIrqTypeRxParityErr,
    [kTopEarlgreyPlicIrqIdUart0TxEmpty] = kDtUartIrqTypeTxEmpty,
    [kTopEarlgreyPlicIrqIdUart1TxWatermark] = kDtUartIrqTypeTxWatermark,
    [kTopEarlgreyPlicIrqIdUart1RxWatermark] = kDtUartIrqTypeRxWatermark,
    [kTopEarlgreyPlicIrqIdUart1TxDone] = kDtUartIrqTypeTxDone,
    [kTopEarlgreyPlicIrqIdUart1RxOverflow] = kDtUartIrqTypeRxOverflow,
    [kTopEarlgreyPlicIrqIdUart1RxFrameErr] = kDtUartIrqTypeRxFrameErr,
    [kTopEarlgreyPlicIrqIdUart1RxBreakErr] = kDtUartIrqTypeRxBreakErr,
    [kTopEarlgreyPlicIrqIdUart1RxTimeout] = kDtUartIrqTypeRxTimeout,
    [kTopEarlgreyPlicIrqIdUart1RxParityErr] = kDtUartIrqTypeRxParityErr,
    [kTopEarlgreyPlicIrqIdUart1TxEmpty] = kDtUartIrqTypeTxEmpty,
    [kTopEarlgreyPlicIrqIdUart2TxWatermark] = kDtUartIrqTypeTxWatermark,
    [kTopEarlgreyPlicIrqIdUart2RxWatermark] = kDtUartIrqTypeRxWatermark,
    [kTopEarlgreyPlicIrqIdUart2TxDone] = kDtUartIrqTypeTxDone,
    [kTopEarlgreyPlicIrqIdUart2RxOverflow] = kDtUartIrqTypeRxOverflow,
    [kTopEarlgreyPlicIrqIdUart2RxFrameErr] = kDtUartIrqTypeRxFrameErr,
    [kTopEarlgreyPlicIrqIdUart2RxBreakErr] = kDtUartIrqTypeRxBreakErr,
    [kTopEarlgreyPlicIrqIdUart2RxTimeout] = kDtUartIrqTypeRxTimeout,
    [kTopEarlgreyPlicIrqIdUart2RxParityErr] = kDtUartIrqTypeRxParityErr,
    [kTopEarlgreyPlicIrqIdUart2TxEmpty] = kDtUartIrqTypeTxEmpty,
    [kTopEarlgreyPlicIrqIdUart3TxWatermark] = kDtUartIrqTypeTxWatermark,
    [kTopEarlgreyPlicIrqIdUart3RxWatermark] = kDtUartIrqTypeRxWatermark,
    [kTopEarlgreyPlicIrqIdUart3TxDone] = kDtUartIrqTypeTxDone,
    [kTopEarlgreyPlicIrqIdUart3RxOverflow] = kDtUartIrqTypeRxOverflow,
    [kTopEarlgreyPlicIrqIdUart3RxFrameErr] = kDtUartIrqTypeRxFrameErr,
    [kTopEarlgreyPlicIrqIdUart3RxBreakErr] = kDtUartIrqTypeRxBreakErr,
    [kTopEarlgreyPlicIrqIdUart3RxTimeout] = kDtUartIrqTypeRxTimeout,
    [kTopEarlgreyPlicIrqIdUart3RxParityErr] = kDtUartIrqTypeRxParityErr,
    [kTopEarlgreyPlicIrqIdUart3TxEmpty] = kDtUartIrqTypeTxEmpty,
    [kTopEarlgreyPlicIrqIdGpioGpio0] = kDtGpioIrqTypeGpio0,
    [kTopEarlgreyPlicIrqIdGpioGpio1] = kDtGpioIrqTypeGpio1,
    [kTopEarlgreyPlicIrqIdGpioGpio2] = kDtGpioIrqTypeGpio2,
    [kTopEarlgreyPlicIrqIdGpioGpio3] = kDtGpioIrqTypeGpio3,
    [kTopEarlgreyPlicIrqIdGpioGpio4] = kDtGpioIrqTypeGpio4,
    [kTopEarlgreyPlicIrqIdGpioGpio5] = kDtGpioIrqTypeGpio5,
    [kTopEarlgreyPlicIrqIdGpioGpio6] = kDtGpioIrqTypeGpio6,
    [kTopEarlgreyPlicIrqIdGpioGpio7] = kDtGpioIrqTypeGpio7,
    [kTopEarlgreyPlicIrqIdGpioGpio8] = kDtGpioIrqTypeGpio8,
    [kTopEarlgreyPlicIrqIdGpioGpio9] = kDtGpioIrqTypeGpio9,
    [kTopEarlgreyPlicIrqIdGpioGpio10] = kDtGpioIrqTypeGpio10,
    [kTopEarlgreyPlicIrqIdGpioGpio11] = kDtGpioIrqTypeGpio11,
    [kTopEarlgreyPlicIrqIdGpioGpio12] = kDtGpioIrqTypeGpio12,
    [kTopEarlgreyPlicIrqIdGpioGpio13] = kDtGpioIrqTypeGpio13,
    [kTopEarlgreyPlicIrqIdGpioGpio14] = kDtGpioIrqTypeGpio14,
    [kTopEarlgreyPlicIrqIdGpioGpio15] = kDtGpioIrqTypeGpio15,
    [kTopEarlgreyPlicIrqIdGpioGpio16] = kDtGpioIrqTypeGpio16,
    [kTopEarlgreyPlicIrqIdGpioGpio17] = kDtGpioIrqTypeGpio17,
    [kTopEarlgreyPlicIrqIdGpioGpio18] = kDtGpioIrqTypeGpio18,
    [kTopEarlgreyPlicIrqIdGpioGpio19] = kDtGpioIrqTypeGpio19,
    [kTopEarlgreyPlicIrqIdGpioGpio20] = kDtGpioIrqTypeGpio20,
    [kTopEarlgreyPlicIrqIdGpioGpio21] = kDtGpioIrqTypeGpio21,
    [kTopEarlgreyPlicIrqIdGpioGpio22] = kDtGpioIrqTypeGpio22,
    [kTopEarlgreyPlicIrqIdGpioGpio23] = kDtGpioIrqTypeGpio23,
    [kTopEarlgreyPlicIrqIdGpioGpio24] = kDtGpioIrqTypeGpio24,
    [kTopEarlgreyPlicIrqIdGpioGpio25] = kDtGpioIrqTypeGpio25,
    [kTopEarlgreyPlicIrqIdGpioGpio26] = kDtGpioIrqTypeGpio26,
    [kTopEarlgreyPlicIrqIdGpioGpio27] = kDtGpioIrqTypeGpio27,
    [kTopEarlgreyPlicIrqIdGpioGpio28] = kDtGpioIrqTypeGpio28,
    [kTopEarlgreyPlicIrqIdGpioGpio29] = kDtGpioIrqTypeGpio29,
    [kTopEarlgreyPlicIrqIdGpioGpio30] = kDtGpioIrqTypeGpio30,
    [kTopEarlgreyPlicIrqIdGpioGpio31] = kDtGpioIrqTypeGpio31,
    [kTopEarlgreyPlicIrqIdSpiDeviceUploadCmdfifoNotEmpty] = kDtSpiDeviceIrqTypeUploadCmdfifoNotEmpty,
    [kTopEarlgreyPlicIrqIdSpiDeviceUploadPayloadNotEmpty] = kDtSpiDeviceIrqTypeUploadPayloadNotEmpty,
    [kTopEarlgreyPlicIrqIdSpiDeviceUploadPayloadOverflow] = kDtSpiDeviceIrqTypeUploadPayloadOverflow,
    [kTopEarlgreyPlicIrqIdSpiDeviceReadbufWatermark] = kDtSpiDeviceIrqTypeReadbufWatermark,
    [kTopEarlgreyPlicIrqIdSpiDeviceReadbufFlip] = kDtSpiDeviceIrqTypeReadbufFlip,
    [kTopEarlgreyPlicIrqIdSpiDeviceTpmHeaderNotEmpty] = kDtSpiDeviceIrqTypeTpmHeaderNotEmpty,
    [kTopEarlgreyPlicIrqIdSpiDeviceTpmRdfifoCmdEnd] = kDtSpiDeviceIrqTypeTpmRdfifoCmdEnd,
    [kTopEarlgreyPlicIrqIdSpiDeviceTpmRdfifoDrop] = kDtSpiDeviceIrqTypeTpmRdfifoDrop,
    [kTopEarlgreyPlicIrqIdI2c0FmtThreshold] = kDtI2cIrqTypeFmtThreshold,
    [kTopEarlgreyPlicIrqIdI2c0RxThreshold] = kDtI2cIrqTypeRxThreshold,
    [kTopEarlgreyPlicIrqIdI2c0AcqThreshold] = kDtI2cIrqTypeAcqThreshold,
    [kTopEarlgreyPlicIrqIdI2c0RxOverflow] = kDtI2cIrqTypeRxOverflow,
    [kTopEarlgreyPlicIrqIdI2c0ControllerHalt] = kDtI2cIrqTypeControllerHalt,
    [kTopEarlgreyPlicIrqIdI2c0SclInterference] = kDtI2cIrqTypeSclInterference,
    [kTopEarlgreyPlicIrqIdI2c0SdaInterference] = kDtI2cIrqTypeSdaInterference,
    [kTopEarlgreyPlicIrqIdI2c0StretchTimeout] = kDtI2cIrqTypeStretchTimeout,
    [kTopEarlgreyPlicIrqIdI2c0SdaUnstable] = kDtI2cIrqTypeSdaUnstable,
    [kTopEarlgreyPlicIrqIdI2c0CmdComplete] = kDtI2cIrqTypeCmdComplete,
    [kTopEarlgreyPlicIrqIdI2c0TxStretch] = kDtI2cIrqTypeTxStretch,
    [kTopEarlgreyPlicIrqIdI2c0TxThreshold] = kDtI2cIrqTypeTxThreshold,
    [kTopEarlgreyPlicIrqIdI2c0AcqStretch] = kDtI2cIrqTypeAcqStretch,
    [kTopEarlgreyPlicIrqIdI2c0UnexpStop] = kDtI2cIrqTypeUnexpStop,
    [kTopEarlgreyPlicIrqIdI2c0HostTimeout] = kDtI2cIrqTypeHostTimeout,
    [kTopEarlgreyPlicIrqIdI2c1FmtThreshold] = kDtI2cIrqTypeFmtThreshold,
    [kTopEarlgreyPlicIrqIdI2c1RxThreshold] = kDtI2cIrqTypeRxThreshold,
    [kTopEarlgreyPlicIrqIdI2c1AcqThreshold] = kDtI2cIrqTypeAcqThreshold,
    [kTopEarlgreyPlicIrqIdI2c1RxOverflow] = kDtI2cIrqTypeRxOverflow,
    [kTopEarlgreyPlicIrqIdI2c1ControllerHalt] = kDtI2cIrqTypeControllerHalt,
    [kTopEarlgreyPlicIrqIdI2c1SclInterference] = kDtI2cIrqTypeSclInterference,
    [kTopEarlgreyPlicIrqIdI2c1SdaInterference] = kDtI2cIrqTypeSdaInterference,
    [kTopEarlgreyPlicIrqIdI2c1StretchTimeout] = kDtI2cIrqTypeStretchTimeout,
    [kTopEarlgreyPlicIrqIdI2c1SdaUnstable] = kDtI2cIrqTypeSdaUnstable,
    [kTopEarlgreyPlicIrqIdI2c1CmdComplete] = kDtI2cIrqTypeCmdComplete,
    [kTopEarlgreyPlicIrqIdI2c1TxStretch] = kDtI2cIrqTypeTxStretch,
    [kTopEarlgreyPlicIrqIdI2c1TxThreshold] = kDtI2cIrqTypeTxThreshold,
    [kTopEarlgreyPlicIrqIdI2c1AcqStretch] = kDtI2cIrqTypeAcqStretch,
    [kTopEarlgreyPlicIrqIdI2c1UnexpStop] = kDtI2cIrqTypeUnexpStop,
    [kTopEarlgreyPlicIrqIdI2c1HostTimeout] = kDtI2cIrqTypeHostTimeout,
    [kTopEarlgreyPlicIrqIdI2c2FmtThreshold] = kDtI2cIrqTypeFmtThreshold,
    [kTopEarlgreyPlicIrqIdI2c2RxThreshold] = kDtI2cIrqTypeRxThreshold,
    [kTopEarlgreyPlicIrqIdI2c2AcqThreshold] = kDtI2cIrqTypeAcqThreshold,
    [kTopEarlgreyPlicIrqIdI2c2RxOverflow] = kDtI2cIrqTypeRxOverflow,
    [kTopEarlgreyPlicIrqIdI2c2ControllerHalt] = kDtI2cIrqTypeControllerHalt,
    [kTopEarlgreyPlicIrqIdI2c2SclInterference] = kDtI2cIrqTypeSclInterference,
    [kTopEarlgreyPlicIrqIdI2c2SdaInterference] = kDtI2cIrqTypeSdaInterference,
    [kTopEarlgreyPlicIrqIdI2c2StretchTimeout] = kDtI2cIrqTypeStretchTimeout,
    [kTopEarlgreyPlicIrqIdI2c2SdaUnstable] = kDtI2cIrqTypeSdaUnstable,
    [kTopEarlgreyPlicIrqIdI2c2CmdComplete] = kDtI2cIrqTypeCmdComplete,
    [kTopEarlgreyPlicIrqIdI2c2TxStretch] = kDtI2cIrqTypeTxStretch,
    [kTopEarlgreyPlicIrqIdI2c2TxThreshold] = kDtI2cIrqTypeTxThreshold,
    [kTopEarlgreyPlicIrqIdI2c2AcqStretch] = kDtI2cIrqTypeAcqStretch,
    [kTopEarlgreyPlicIrqIdI2c2UnexpStop] = kDtI2cIrqTypeUnexpStop,
    [kTopEarlgreyPlicIrqIdI2c2HostTimeout] = kDtI2cIrqTypeHostTimeout,
    [kTopEarlgreyPlicIrqIdPattgenDoneCh0] = kDtPattgenIrqTypeDoneCh0,
    [kTopEarlgreyPlicIrqIdPattgenDoneCh1] = kDtPattgenIrqTypeDoneCh1,
    [kTopEarlgreyPlicIrqIdRvTimerTimerExpiredHart0Timer0] = kDtRvTimerIrqTypeTimerExpiredHart0Timer0,
    [kTopEarlgreyPlicIrqIdOtpCtrlOtpOperationDone] = kDtOtpCtrlIrqTypeOtpOperationDone,
    [kTopEarlgreyPlicIrqIdOtpCtrlOtpError] = kDtOtpCtrlIrqTypeOtpError,
    [kTopEarlgreyPlicIrqIdAlertHandlerClassa] = kDtAlertHandlerIrqTypeClassa,
    [kTopEarlgreyPlicIrqIdAlertHandlerClassb] = kDtAlertHandlerIrqTypeClassb,
    [kTopEarlgreyPlicIrqIdAlertHandlerClassc] = kDtAlertHandlerIrqTypeClassc,
    [kTopEarlgreyPlicIrqIdAlertHandlerClassd] = kDtAlertHandlerIrqTypeClassd,
    [kTopEarlgreyPlicIrqIdSpiHost0Error] = kDtSpiHostIrqTypeError,
    [kTopEarlgreyPlicIrqIdSpiHost0SpiEvent] = kDtSpiHostIrqTypeSpiEvent,
    [kTopEarlgreyPlicIrqIdSpiHost1Error] = kDtSpiHostIrqTypeError,
    [kTopEarlgreyPlicIrqIdSpiHost1SpiEvent] = kDtSpiHostIrqTypeSpiEvent,
    [kTopEarlgreyPlicIrqIdUsbdevPktReceived] = kDtUsbdevIrqTypePktReceived,
    [kTopEarlgreyPlicIrqIdUsbdevPktSent] = kDtUsbdevIrqTypePktSent,
    [kTopEarlgreyPlicIrqIdUsbdevDisconnected] = kDtUsbdevIrqTypeDisconnected,
    [kTopEarlgreyPlicIrqIdUsbdevHostLost] = kDtUsbdevIrqTypeHostLost,
    [kTopEarlgreyPlicIrqIdUsbdevLinkReset] = kDtUsbdevIrqTypeLinkReset,
    [kTopEarlgreyPlicIrqIdUsbdevLinkSuspend] = kDtUsbdevIrqTypeLinkSuspend,
    [kTopEarlgreyPlicIrqIdUsbdevLinkResume] = kDtUsbdevIrqTypeLinkResume,
    [kTopEarlgreyPlicIrqIdUsbdevAvOutEmpty] = kDtUsbdevIrqTypeAvOutEmpty,
    [kTopEarlgreyPlicIrqIdUsbdevRxFull] = kDtUsbdevIrqTypeRxFull,
    [kTopEarlgreyPlicIrqIdUsbdevAvOverflow] = kDtUsbdevIrqTypeAvOverflow,
    [kTopEarlgreyPlicIrqIdUsbdevLinkInErr] = kDtUsbdevIrqTypeLinkInErr,
    [kTopEarlgreyPlicIrqIdUsbdevRxCrcErr] = kDtUsbdevIrqTypeRxCrcErr,
    [kTopEarlgreyPlicIrqIdUsbdevRxPidErr] = kDtUsbdevIrqTypeRxPidErr,
    [kTopEarlgreyPlicIrqIdUsbdevRxBitstuffErr] = kDtUsbdevIrqTypeRxBitstuffErr,
    [kTopEarlgreyPlicIrqIdUsbdevFrame] = kDtUsbdevIrqTypeFrame,
    [kTopEarlgreyPlicIrqIdUsbdevPowered] = kDtUsbdevIrqTypePowered,
    [kTopEarlgreyPlicIrqIdUsbdevLinkOutErr] = kDtUsbdevIrqTypeLinkOutErr,
    [kTopEarlgreyPlicIrqIdUsbdevAvSetupEmpty] = kDtUsbdevIrqTypeAvSetupEmpty,
    [kTopEarlgreyPlicIrqIdPwrmgrAonWakeup] = kDtPwrmgrIrqTypeWakeup,
    [kTopEarlgreyPlicIrqIdSysrstCtrlAonEventDetected] = kDtSysrstCtrlIrqTypeEventDetected,
    [kTopEarlgreyPlicIrqIdAdcCtrlAonMatchPending] = kDtAdcCtrlIrqTypeMatchPending,
    [kTopEarlgreyPlicIrqIdAonTimerAonWkupTimerExpired] = kDtAonTimerIrqTypeWkupTimerExpired,
    [kTopEarlgreyPlicIrqIdAonTimerAonWdogTimerBark] = kDtAonTimerIrqTypeWdogTimerBark,
    [kTopEarlgreyPlicIrqIdSensorCtrlAonIoStatusChange] = kDtSensorCtrlIrqTypeIoStatusChange,
    [kTopEarlgreyPlicIrqIdSensorCtrlAonInitStatusChange] = kDtSensorCtrlIrqTypeInitStatusChange,
    [kTopEarlgreyPlicIrqIdFlashCtrlProgEmpty] = kDtFlashCtrlIrqTypeProgEmpty,
    [kTopEarlgreyPlicIrqIdFlashCtrlProgLvl] = kDtFlashCtrlIrqTypeProgLvl,
    [kTopEarlgreyPlicIrqIdFlashCtrlRdFull] = kDtFlashCtrlIrqTypeRdFull,
    [kTopEarlgreyPlicIrqIdFlashCtrlRdLvl] = kDtFlashCtrlIrqTypeRdLvl,
    [kTopEarlgreyPlicIrqIdFlashCtrlOpDone] = kDtFlashCtrlIrqTypeOpDone,
    [kTopEarlgreyPlicIrqIdFlashCtrlCorrErr] = kDtFlashCtrlIrqTypeCorrErr,
    [kTopEarlgreyPlicIrqIdHmacHmacDone] = kDtHmacIrqTypeHmacDone,
    [kTopEarlgreyPlicIrqIdHmacFifoEmpty] = kDtHmacIrqTypeFifoEmpty,
    [kTopEarlgreyPlicIrqIdHmacHmacErr] = kDtHmacIrqTypeHmacErr,
    [kTopEarlgreyPlicIrqIdKmacKmacDone] = kDtKmacIrqTypeKmacDone,
    [kTopEarlgreyPlicIrqIdKmacFifoEmpty] = kDtKmacIrqTypeFifoEmpty,
    [kTopEarlgreyPlicIrqIdKmacKmacErr] = kDtKmacIrqTypeKmacErr,
    [kTopEarlgreyPlicIrqIdOtbnDone] = kDtOtbnIrqTypeDone,
    [kTopEarlgreyPlicIrqIdKeymgrOpDone] = kDtKeymgrIrqTypeOpDone,
    [kTopEarlgreyPlicIrqIdCsrngCsCmdReqDone] = kDtCsrngIrqTypeCsCmdReqDone,
    [kTopEarlgreyPlicIrqIdCsrngCsEntropyReq] = kDtCsrngIrqTypeCsEntropyReq,
    [kTopEarlgreyPlicIrqIdCsrngCsHwInstExc] = kDtCsrngIrqTypeCsHwInstExc,
    [kTopEarlgreyPlicIrqIdCsrngCsFatalErr] = kDtCsrngIrqTypeCsFatalErr,
    [kTopEarlgreyPlicIrqIdEntropySrcEsEntropyValid] = kDtEntropySrcIrqTypeEsEntropyValid,
    [kTopEarlgreyPlicIrqIdEntropySrcEsHealthTestFailed] = kDtEntropySrcIrqTypeEsHealthTestFailed,
    [kTopEarlgreyPlicIrqIdEntropySrcEsObserveFifoReady] = kDtEntropySrcIrqTypeEsObserveFifoReady,
    [kTopEarlgreyPlicIrqIdEntropySrcEsFatalErr] = kDtEntropySrcIrqTypeEsFatalErr,
    [kTopEarlgreyPlicIrqIdEdn0EdnCmdReqDone] = kDtEdnIrqTypeEdnCmdReqDone,
    [kTopEarlgreyPlicIrqIdEdn0EdnFatalErr] = kDtEdnIrqTypeEdnFatalErr,
    [kTopEarlgreyPlicIrqIdEdn1EdnCmdReqDone] = kDtEdnIrqTypeEdnCmdReqDone,
    [kTopEarlgreyPlicIrqIdEdn1EdnFatalErr] = kDtEdnIrqTypeEdnFatalErr,
};

/**
 * Return local IRQ type for a global IRQ ID.
 */
uint32_t dt_irq_to_device_irq(uint32_t irq) {
  if (irq < kDtIrqIdCount) {
    return device_irq_type_from_irq[irq];
  }
  return kDtDeviceUnknown;
}
