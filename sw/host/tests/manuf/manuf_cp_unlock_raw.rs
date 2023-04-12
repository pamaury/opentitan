// Copyright lowRISC contributors.
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0
use std::cmp;
use std::iter;
use std::rc::Rc;
use std::thread;
use std::time::{Duration, Instant};

use anyhow::{bail, Context};
use structopt::StructOpt;

use opentitanlib::chip::boolean::MultiBitBool8;
use opentitanlib::dif::lc_ctrl::{
    DifLcCtrlState, DifLcCtrlToken, LcCtrlReg, LcCtrlStatusBit, LcCtrlTransitionCmdBit,
    LcCtrlTransitionCtrlBit,
};
use opentitanlib::io::jtag::{Jtag, JtagParams, JtagTap};
use opentitanlib::test_utils::init::InitializeTest;

#[derive(Debug, StructOpt)]
struct Opts {
    #[structopt(flatten)]
    init: InitializeTest,
    #[structopt(flatten)]
    jtag: JtagParams,
}

// Verify transition from `RAW` to `TEST_UNLOCKED` `lc_state`.
//
// - [ ] Pre-load OTP with `RAW` lc_state.
// - [x] Bring device out of reset selecting the Life Cycle (LC) TAP interface using strap pins.
//
// Perfom the following steps via LC TAP interface:
//
// - [x] Switch to external clock via `TRANSITION_CTRL.EXT_CLOCK_EN`.
// - [~] Provide `RAW_UNLOCK`.
// - [x] Poll for lc_ctrl `STATUS` register for `TRANSITION_SUCCESSFUL`. Check for errors or timeout.
// - [~] Perform reset by toggling the `POR` pin.
// - [x] Verify the `lc_state` is `TEST_UNLOCKED0`.
//
// The manufacturing environment is required to support test reruns whenever possible:
//
// - [ ] Verify that the `RAW_UNLOCK` process can be re-tried after failed or interrupted attempts.

fn main() -> anyhow::Result<()> {
    let opts = Opts::from_args();
    opts.init.init_target()?;

    let transport = opts
        .init
        .init_target()
        .context("failed to initialise target")?;

    // Set the TAP straps for the lifecycle controller and reset.
    transport
        .pin_strapping("PINMUX_TAP_LC")
        .context(format!("failed to find strapping PINMUX_TAP_LC"))?
        .apply()
        .context("failed to apply LC TAP strapping")?;
    transport
        .reset_target(opts.init.bootstrap.options.reset_delay, true)
        .context("failed to reset")?;

    // Connect to the LC TAP via JTAG.
    let jtag = transport
        .jtag(&opts.jtag)
        .context("failed to get JTAG interface")?;
    jtag.connect(JtagTap::LcTap)
        .context("failed to connect to LC TAP over JTAG")?;

    wait_until_ready(&jtag, Duration::from_secs(1)).context("failed to wait for LC to be ready")?;

    // Try to claim the transitions mutex.
    poll_until(Duration::from_secs(1), || {
        jtag.write_lc_ctrl_reg(
            &LcCtrlReg::ClaimTransitionIf,
            u8::from(MultiBitBool8::True) as u32,
        )
        .context("failed to write to CLAIM_TRANSITION_IF register")?;

        // Check we acquired the lock
        let got_lock = jtag
            .read_lc_ctrl_reg(&LcCtrlReg::ClaimTransitionIf)
            .context("failed to read CLAIM_TRANSITION_IF register")?;

        Ok(got_lock == 0x01)
    })
    .context("failed to claim transition mutex")?;

    // Check we're currently in the `RAW` lifecycle state.
    let state = jtag
        .read_lc_ctrl_reg(&LcCtrlReg::LcState)
        .context("failed to read LC_STATE register")?;
    assert_eq!(state, u32::from(DifLcCtrlState::Raw));

    // Enable the external clock.
    jtag.write_lc_ctrl_reg(
        &LcCtrlReg::TransitionCtrl,
        0x01 << LcCtrlTransitionCtrlBit::ExtClockEn as u32,
    )
    .context("failed to set TRANSITION_CTRL.EXT_CLOCK_EN bit")?;

    // Check that transitions are writable (we hold the mutex, so they should be).
    let transitions_enabled = jtag
        .read_lc_ctrl_reg(&LcCtrlReg::TransitionRegwen)
        .context("failed to read TRANSITION_REGWEN register")?;
    assert_eq!(transitions_enabled, 0x01);

    // Provide the `RAW_UNLOCK` token.

    let token_regs = [
        &LcCtrlReg::TransitionToken0,
        &LcCtrlReg::TransitionToken1,
        &LcCtrlReg::TransitionToken2,
        &LcCtrlReg::TransitionToken3,
    ];
    // FIXME: fill this out with the correct value.
    let token = DifLcCtrlToken::from([
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, //
        0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
    ]);
    let token_words = token.into_register_values();

    for (reg, value) in iter::zip(token_regs, token_words) {
        jtag.write_lc_ctrl_reg(reg, value)
            .context("failed to write word to TRANSITION_TOKEN register")?;
    }

    // Set the transition target to `TEST_UNLOCKED0`.
    jtag.write_lc_ctrl_reg(
        &LcCtrlReg::TransitionTarget,
        u32::from(DifLcCtrlState::TestUnlocked0),
    )
    .context("failed to write to TRANSITION_TARGET register")?;

    // Initiate the transition.
    jtag.write_lc_ctrl_reg(
        &LcCtrlReg::TransitionCmd,
        0x01 << LcCtrlTransitionCmdBit::Start as u32,
    )
    .context("failed to write to TRANSITION_CMD register")?;

    // Poll until the transition succeeds
    poll_until(Duration::from_secs(1), || {
        let status = jtag
            .read_lc_ctrl_reg(&LcCtrlReg::Status)
            .context("failed to read STATUS register")?;

        if status & LcCtrlStatusBit::errors() != 0 {
            bail!("lifecycle controller has error status: 0b{status:#b}");
        }

        Ok(status >> LcCtrlStatusBit::TransitionSuccessful as u32 & 0x01 == 0x01)
    })
    .context("did not read TRANSITION_SUCCESSFUL status from lifecycle controller")?;

    // Reset OpenTitan.
    // FIXME: Testplan specifies toggling the POR pin - does this do that?
    transport
        .reset_target(opts.init.bootstrap.options.reset_delay, false)
        .context("failed to reset")?;

    wait_until_ready(&jtag, Duration::from_secs(1)).context("failed to wait for LC to be ready")?;

    // Check that LC state is `TEST_UNLOCKED0`.
    let state = jtag
        .read_lc_ctrl_reg(&LcCtrlReg::TransitionTarget)
        .context("failed to write to TRANSITION_TARGET register")?;
    assert_eq!(state, u32::from(DifLcCtrlState::TestUnlocked0));

    Ok(())
}

/// Waits for the lifecycle controller to enter the `READY` state.
///
/// Will return an error if the lifecycle controller is in an error state, or
/// does not enter `READY` within the given timeout.
fn wait_until_ready(jtag: &Rc<dyn Jtag>, timeout: Duration) -> anyhow::Result<()> {
    // Wait for LC controller to be ready.
    poll_until(timeout, || {
        let status = jtag
            .read_lc_ctrl_reg(&LcCtrlReg::Status)
            .context("failed to read STATUS register")?;

        // Check for any error bits set.
        if status & LcCtrlStatusBit::errors() != 0 {
            bail!("lifecycle controller has error status: 0b{status:#b}");
        }

        Ok(status >> LcCtrlStatusBit::Ready as u32 & 0x01 == 0x01)
    })
    .context("did not read READY status from lifecycle controller")
}

/// Repeat a given operation until it succeeds or a timeout is hit.
///
/// `f` should return `Ok(true)` on success, and `Ok(false)` to poll again.
/// Errors are propagated.
fn poll_until<F: Fn() -> anyhow::Result<bool>>(timeout: Duration, f: F) -> anyhow::Result<()> {
    const POLL_DELAY: Duration = Duration::from_millis(5);
    let start = Instant::now();

    // Check the provided function until it succeeds or times out.
    loop {
        if start.elapsed() > timeout {
            bail!("timed out");
        }

        // Run the provided function, stopping if successful.
        if f()? {
            break;
        }

        // Delay between polls to prevent thrashing.
        let remaining = timeout.saturating_sub(start.elapsed());
        thread::sleep(cmp::max(POLL_DELAY, remaining));
    }

    Ok(())
}
