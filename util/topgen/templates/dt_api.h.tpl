// Copyright lowRISC contributors.
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0
//
${gencmd}
<%
from topgen.lib import Name, is_top_reggen, is_ipgen

module_types = {m["type"] for m in top["module"]}
module_types = sorted(module_types)
top_reggen_module_types = {m["type"] for m in top["module"] if is_top_reggen(m)}
ipgen_module_types = {m["type"] for m in top["module"] if is_ipgen(m)}
top_name = Name(["top", top["name"]])
irq_base_name = top_name + Name(["plic", "irq", "id"])
top_clock_prefix = top_name + Name(["clock", "src"])
module_data = {}

def snake_to_constant_name(s):
    out = ""
    parts = s.split("_")
    for p in parts:
        # If we're about to join two parts which would introduce adjacent
        # numbers, put an underscore between them.
        if out[-1:].isnumeric() and p[:1].isnumeric():
            out += "_" + p
        else:
            out += p.capitalize()
    return out
%>\

#ifndef ${helper.header_macro_prefix}_DT_API_H_
#define ${helper.header_macro_prefix}_DT_API_H_

#include <stddef.h>
#include <stdint.h>
#include "hw/top_${top["name"]}/sw/autogen/top_${top["name"]}.h"

enum {
% for module_name in module_types:
<%
    modules = [m for m in top["module"] if m["type"] == module_name]
%>\
  kDt${snake_to_constant_name(module_name)}Count = ${len(modules)},
% endfor
};

/** List of devices types. */
typedef enum dt_device_type {
% for module_name in module_types:
  kDtDeviceType${snake_to_constant_name(module_name)},
% endfor
  kDtDeviceTypeCount,
  kDtDeviceTypeUnknown = kDtDeviceTypeCount,
} dt_device_type_t;

/** List of devices IDs. */
typedef enum dt_device_id {
% for module_name in module_types:
<%
    modules = [m for m in top["module"] if m["type"] == module_name]
%>\
%   for (dev_index, m) in enumerate(modules):
  kDtDeviceId${snake_to_constant_name( m["name"])},
%   endfor
% endfor
  kDtDeviceIdCount,
  kDtDeviceIdUnknown = kDtDeviceIdCount,
} dt_device_id_t;

/**
 * Get the device type of a device.
 *
 * For example the device type of `kDtUart0` is `kDtUartDevice`.
 *
 * @param dev A device ID.
 * @return The device type, or kDtDeviceIdUnknown if the ID is not valid.
 */
dt_device_type_t dt_device_type(dt_device_id_t dev);

/**
 * Get the device instance number of a device.
 *
 * If a top instances several devices of the same type, this will
 * return the instance number. This function guarantees that the instance
 * number can be used to index into the correspond devicetable below.
 *
 * For example, the instance number of `kDtUart3` is 3. It is guaranteed
 * then that `kDtUart[3].device == kDtUart3`.
 *
 * @param dev A device ID.
 * @return The device instance number, or 0 if the ID is not valid.
 */
size_t dt_device_index(dt_device_id_t dev);

/** IRQ IDs. */
typedef ${top_name.as_snake_case()}_plic_irq_id_t dt_irq_t;
// This is a define so that kDtIrqUnknown has the type dt_irq_t
// and does not require casting.
#define kDtIrqUnknown ${top_name.as_c_enum()}PlicIrqIdNone

/**
 * Get the device ID for a given IRQ ID.
 *
 * The IRQ ID is the PLIC IRQ ID. For example, on earlgrey, the device ID
 * of `kTopEarlgreyPlicIrqIdUart0TxWatermark` is `kDtDeviceIdUart0`.
 * One can then use the type specific function to retrieve the local IRQ
 * type, for example `dt_uart_irq_type` for the UART.
 *
 * @param dev A device ID.
 * @return The device instance number, or kDtDeviceIdUnknown if the ID is not valid.
 */
dt_device_id_t dt_irq_to_device(dt_irq_t irq);

typedef ${top_name.as_snake_case()}_clock_src_t dt_clock_t;
/**
 * Get the frequency of a clock.
 *
 * @param dev A clock ID.
 * @return Clock frequency in Hz.
 */
uint32_t dt_clock_frequency(dt_clock_t clk);


/** Type of a pin. */
typedef enum dt_pin_type {
  /* This pin is connected to a MIO. */
  kDtPinTypeMio,
  /* This pin is connected to a direct IO. */
  kDtPinTypeDio,
  /* This pin is not connected to either a MIO or a DIO. */
  kDtPinTypeOther,
} dt_pin_type_t;

enum {
  kDtPinPeriphInputNone = k${top_name.as_camel_case()}PinmuxPeripheralInLast + 1,
  kDtPinOutselNone = k${top_name.as_camel_case()}PinmuxOutselLast + 1,
  kDtPinDirectPadsNone = k${top_name.as_camel_case()}DirectPadsLast + 1,
};

/** Pin description.
 *
 * A `dt_pin_t` represents a HW IP block pin, which can be an input, output or both.
 * Importantly, this only represents how the block pin is wired to the pinmux, ie
 * whether it is a MIO or a direct IO, and the relevant information necessary to
 * configure it.
 *
 * NOTE The fields of this structure are internal, use the dt_pin_* functions instead.
 */
typedef struct dt_pin {
  struct {
    /** Pin type */
    uint16_t type : 2;
    /** For `kDtPinTypeMio` pins: peripheral input number. This is the index of the MIO_PERIPH_INSEL register
    * that controls this pin (or the input part of this pin). Set to `kDtPinPeriphInputNone`
    * if this pin is not an input.
    *
    * For `kDtPinTypeDio`:  direct IO pad number. This is the index of the various DIO_PAD_* registers
    * that control this pin.
    */
    uint16_t periph_input_or_direct_pad: 7;
    /** For `kDtPinTypeMio` pins: eripheral output number. This is the value to put in the MIO_OUTSEL registers
    * to connect an output to this pin. Set to `kDtPinPeriphOutputNone`
    * if this pin is not an input.
    *
    * For `kDtPinTypeDio`: unused.
    */
    uint16_t outsel: 7;
  } __internal;
} __attribute__((packed)) dt_pin_t;

typedef ${top_name.as_snake_case()}_pinmux_peripheral_in_t dt_pinmux_peripheral_in_t;
typedef ${top_name.as_snake_case()}_pinmux_insel_t dt_pinmux_insel_t;
typedef ${top_name.as_snake_case()}_pinmux_outsel_t dt_pinmux_outsel_t;
typedef ${top_name.as_snake_case()}_pinmux_mio_out_t dt_pinmux_mio_out_t;
typedef ${top_name.as_snake_case()}_direct_pads_t dt_pinmux_direct_pad_t;
typedef ${top_name.as_snake_case()}_muxed_pads_t  dt_pinmux_muxed_pad_t;

/** Tie constantly to zero
 *
 * This is a define so the type remains ${top_name.as_snake_case()}_pinmux_outsel_t. */
#define kDtPinmuxOutselConstantZero  kTopEarlgreyPinmuxOutselConstantZero
/** Tie constantly to one
 *
 * This is a define so the type remains ${top_name.as_snake_case()}_pinmux_outsel_t. */
#define kDtPinPinmuxOutselConstantOne  kTopEarlgreyPinmuxOutselConstantOne
/** Tie constantly to high-Z
 *
 * This is a define so the type remains ${top_name.as_snake_case()}_pinmux_outsel_t. */
#define kDtPinmuxOutselConstantHighZ  kTopEarlgreyPinmuxOutselConstantHighZ

/** Return the type of a `dt_pin_t`.
 *
 * @param dev A pin description.
 * @return The pin type (MIO, DIO, etc).
 */
static inline dt_pin_type_t dt_pin_type(dt_pin_t pin) {
  return pin.__internal.type;
}

/** Return the peripheral input for an MIO pin
 *
 * @param dev A pin of type `kDtPinTypeMio`.
 * @return The peripheral input number of the MIO that this pin is connected to,
 * or `kDtPinPeriphInputNone`.
 *
 * NOTE This function only makes sense for pins of type `kDtPinTypeMio` which are
 * either inputs or inouts. For any other pin, this function will return `kDtPinPeriphInputNone`.
 */
static inline dt_pinmux_peripheral_in_t dt_pin_mio_periph_input(dt_pin_t pin) {
  if (dt_pin_type(pin) != kDtPinTypeMio) {
    return kDtPinPeriphInputNone;
  }
  return pin.__internal.periph_input_or_direct_pad;
}

/** Return the outsel for an MIO pin
 *
 * @param dev A pin of type `kDtPinTypeMio`.
 * @return The outsel of the MIO that this pin is connected to,
 * or `kDtPinOutselNone`.
 *
 * NOTE This function only makes sense for pins of type `kDtPinTypeMio` which are
 * either outputs or inouts. For any other pin, this function will return `kDtPinPeriphInputNone`.
 */
static inline dt_pinmux_outsel_t dt_pin_mio_outsel(dt_pin_t pin) {
  if (dt_pin_type(pin) != kDtPinTypeMio) {
    return kDtPinPeriphInputNone;
  }
  return pin.__internal.outsel;
}

/** Return the direct pad number of a DIO pin
 *
 * @param dev A pin of type `kDtPinTypeDio`.
 * @return The direct pad number of the DID that this pin is connected to,
 * or `kDtPinDirectPadsNone`.
 *
 * NOTE This function only makes sense for pins of type `kDtPinTypeDio` which are
 * either outputs or inouts. For any other pin type, this function will return `kDtPinDirectPadsNone`.
 */
static inline dt_pinmux_direct_pad_t dt_pin_dio_pad(dt_pin_t pin) {
  if (dt_pin_type(pin) != kDtPinTypeDio) {
    return kDtPinDirectPadsNone;
  }
  return pin.__internal.periph_input_or_direct_pad;
}

#endif // ${helper.header_macro_prefix}_DT_API_H_