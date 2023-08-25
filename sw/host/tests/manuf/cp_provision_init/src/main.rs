// Copyright lowRISC contributors.
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0

use std::time::Duration;

use anyhow::{Context, Result};
use arrayvec::ArrayVec;
use clap::Parser;

use opentitanlib::app::TransportWrapper;
use opentitanlib::dif::lc_ctrl::{DifLcCtrlState, DifLcCtrlToken, LcCtrlReg};
use opentitanlib::io::jtag::JtagTap;
use opentitanlib::test_utils::init::InitializeTest;
use opentitanlib::test_utils::lc_transition::trigger_lc_transition;
use opentitanlib::test_utils::load_sram_program::{
    ExecutionMode, ExecutionResult, SramProgramParams,
};
use opentitanlib::test_utils::rpc::UartSend;
use opentitanlib::uart::console::UartConsole;

mod provisioning_data;
use provisioning_data::ManufCpProvisioningData;

// Generated by the `lc_raw_unlock_token` Bazel rule from `//rules/lc.bzl`.
mod lc_raw_unlock_token;

#[derive(Debug, Parser)]
struct Opts {
    #[command(flatten)]
    init: InitializeTest,

    #[command(flatten)]
    sram_program: SramProgramParams,

    #[arg(
        long,
        value_parser = humantime::parse_duration,
        default_value = "600s",
        help = "Console receive timeout",
    )]
    timeout: Duration,
}

fn unlock_raw(opts: &Opts, transport: &TransportWrapper) -> Result<()> {
    // Set the TAP straps for the lifecycle controller and reset.
    transport
        .pin_strapping("PINMUX_TAP_LC")?
        .apply()
        .context("failed to apply LC TAP strapping")?;
    transport
        .reset_target(opts.init.bootstrap.options.reset_delay, true)
        .context("failed to reset")?;

    // Connect to the LC TAP via JTAG.
    let jtag = opts.init.jtag_params.create(transport)?;
    jtag.connect(JtagTap::LcTap)
        .context("failed to connect to LC TAP over JTAG")?;

    // Provide the `RAW_UNLOCK` token
    let token = DifLcCtrlToken::from(lc_raw_unlock_token::RND_CNST_RAW_UNLOCK_TOKEN.to_le_bytes());
    let token_words = token.into_register_values();

    // ROM execution is not enabled in the OTP so we can safely reconnect to the LC TAP after
    // the transition without risking the chip to be reset.
    trigger_lc_transition(
        transport,
        jtag.clone(),
        DifLcCtrlState::TestUnlocked0,
        Some(token_words),
        true,
        opts.init.bootstrap.options.reset_delay,
        Some(JtagTap::LcTap),
    )
    .context("failed to transition to TEST_UNLOCKED0")?;

    // Check that LC state is `TEST_UNLOCKED0`.
    let state = jtag.read_lc_ctrl_reg(&LcCtrlReg::LcState)?;
    assert_eq!(state, DifLcCtrlState::TestUnlocked0.redundant_encoding());
    jtag.disconnect()?;

    Ok(())
}

fn load_and_run_sram_program(opts: &Opts, transport: &TransportWrapper) -> Result<()> {
    // Set CPU TAP straps, reset, and connect to the JTAG interface.
    transport.pin_strapping("PINMUX_TAP_RISCV")?.apply()?;
    transport.reset_target(opts.init.bootstrap.options.reset_delay, true)?;
    let jtag = opts.init.jtag_params.create(transport)?;
    jtag.connect(JtagTap::RiscvTap)?;

    // Reset and halt the CPU to ensure we are in a known state, and clear out any ROM messages
    // printed over the console.
    jtag.reset(/*run=*/ false)?;
    let uart = transport.uart("console")?;
    uart.clear_rx_buffer()?;

    // Load and execute the SRAM program that contains the provisioning code.
    let result = opts
        .sram_program
        .load_and_execute(&jtag, ExecutionMode::Jump)?;
    match result {
        ExecutionResult::Executing => log::info!("SRAM program loaded and is executing."),
        _ => panic!("SRAM program load/execution failed: {:?}.", result),
    }

    // Get UART, set flow control, and wait for test to start running.
    let uart = transport.uart("console")?;
    uart.set_flow_control(true)?;
    let _ = UartConsole::wait_for(&*uart, r"CP provisioning start.", opts.timeout)?;

    // Inject provisioning data into the device.
    // TODO(#19453): update provisioning_data sent to the device.
    let provisioning_data = ManufCpProvisioningData {
        device_id: ArrayVec::from([0u32, 0u32, 0u32, 0u32]),
        manuf_state: ArrayVec::from([0u32, 0u32, 0u32, 0u32]),
        wafer_auth_secret: ArrayVec::from([0u32, 0u32, 0u32, 0u32]),
        test_unlock_token: ArrayVec::from([0u32, 0u32, 0u32, 0u32]),
        test_exit_token: ArrayVec::from([0u32, 0u32, 0u32, 0u32]),
    };
    provisioning_data.send(&*uart)?;

    // Once the SRAM program has printed a message over the console, we can continue with an LC
    // transition to mission mode, initiated on the host side.
    let _ = UartConsole::wait_for(&*uart, r"CP provisioning end.", opts.timeout)?;
    // TODO(#19453): transition to mission mode.

    Ok(())
}

fn main() -> Result<()> {
    let opts = Opts::parse();
    opts.init.init_logging();
    let transport = opts.init.init_target()?;

    unlock_raw(&opts, &transport)?;
    load_and_run_sram_program(&opts, &transport)?;

    Ok(())
}
