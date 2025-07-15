// Copyright lowRISC contributors (OpenTitan project).
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0

#include "sw/device/lib/arch/device.h"
#include "sw/device/lib/base/memory.h"
#include "sw/device/lib/dif/dif_sensor_ctrl.h"
#include "sw/device/lib/runtime/log.h"
#include "sw/device/lib/testing/aon_timer_testutils.h"
#include "sw/device/lib/testing/clkmgr_testutils.h"
#include "sw/device/lib/testing/pwrmgr_testutils.h"
#include "sw/device/lib/testing/sensor_ctrl_testutils.h"
#include "sw/device/lib/testing/test_framework/check.h"
#include "sw/device/lib/testing/test_framework/ottf_main.h"

#include "hw/top_earlgrey/sw/autogen/top_earlgrey.h"

OTTF_DEFINE_TEST_CONFIG();


enum {
  kMeasurementsPerRound = 100,
  kMeasurementsRetry = 100,
};

static dif_clkmgr_t clkmgr;
static dif_pwrmgr_t pwrmgr;

// TODO explain
static uint32_t clkmgr_aon_sync_delay;

// Upper bound (with safe margin) on the maximal jitter expected for
// any clock.
const size_t kMaxJitterPercent = 5;

// Number of bins in the jitter for one side. For example a value of a 10
// means we want to have statistics for the following bins:
// 100%, 90%, 80%, ..., 0%
// This is "one-sided" because we will want to measure on both side of the
// expected frequency: there will be a 90% bin below the average frequency
// and one above.
#define JITTER_STATS_BINS 10

// All frequencies here are expressed in terms of clkmgr measurements, i.e.
  // number of ticks during one AON tick.
typedef struct jitter_statistics {
  // Average frequency of this clock (i.e. the 100% pass rate).
  uint32_t average;
  // Frequencies to obtain a specified pass rate. Concretely, the i-th entry
  // (i=0,...,JITTER_STATS_BINS) is the frequency f_i (encoded as specified
  // above) such that in p_i percent of the runs, the frequency was below f_i,
  // where p_i = i / JITTER_STATS_BINS * 100.
  uint32_t negative_bins[JITTER_STATS_BINS + 1];
  // Same as above but replace "the frequency was below" by "the frequency was above".
  uint32_t positive_bins[JITTER_STATS_BINS + 1];
} jitter_statistics_t;

// Measure clock jitter for a particular clock.
static void measure_clock_frequencies_jitter(
  jitter_statistics_t *out_stats,
  uint32_t delay_micros,
  dif_clkmgr_measure_clock_t clock,
  uint64_t freq,
  const char *clkname) {

  // The clkmgr measurements are based on the AON clock.
  const uint32_t kClockCount = (uint32_t)udiv64_slow(freq, kClockFreqAonHz, /*rem_out=*/NULL);
  const uint32_t kClockMaxVariability = (kClockCount * kMaxJitterPercent + 99) / 100;
  const uint32_t kClockMinCount = kClockCount - kClockMaxVariability;
  const uint32_t kClockMaxCount = kClockCount + kClockMaxVariability;

  LOG_INFO("%s: min=%u, avg=%u, max=%u", clkname, kClockMinCount, kClockCount, kClockMaxCount);

  // We start from the minimum cycle count and increase, noting percentages of success
  // as we go.
  LOG_INFO("pass below:");
  for (uint32_t cycles = kClockMinCount; cycles <= kClockCount; cycles++) {
    size_t pass_cout = 0;
    for (size_t try = 0; try < kMeasurementsRetry; try++) {
      CHECK_DIF_OK(dif_clkmgr_recov_err_code_clear_codes(&clkmgr, ~0u));
      CHECK_DIF_OK(dif_clkmgr_enable_measure_counts(&clkmgr, clock, 1, cycles));
      busy_spin_micros(delay_micros);
      CHECK_DIF_OK(dif_clkmgr_disable_measure_counts(&clkmgr, clock));
      busy_spin_micros(clkmgr_aon_sync_delay);
      dif_clkmgr_recov_err_codes_t err_codes;
      CHECK_DIF_OK(dif_clkmgr_recov_err_code_get_codes(&clkmgr, &err_codes));
      if (err_codes == 0) {
        pass_cout++;
      }
      // Without this delay, I get random results.
      busy_spin_micros(clkmgr_aon_sync_delay);
    }
    LOG_INFO("%d: pass=%u%%", cycles, pass_cout * 100 / kMeasurementsRetry);
  }
  LOG_INFO("pass above:");
  for (uint32_t cycles = kClockCount; cycles <= kClockMaxCount; cycles++) {
    size_t pass_cout = 0;
    for (size_t try = 0; try < kMeasurementsRetry; try++) {
      CHECK_DIF_OK(dif_clkmgr_recov_err_code_clear_codes(&clkmgr, ~0u));
      CHECK_DIF_OK(dif_clkmgr_enable_measure_counts(&clkmgr, clock, cycles, kClockMaxCount));
      busy_spin_micros(delay_micros);
      CHECK_DIF_OK(dif_clkmgr_disable_measure_counts(&clkmgr, clock));
      dif_clkmgr_recov_err_codes_t err_codes;
      CHECK_DIF_OK(dif_clkmgr_recov_err_code_get_codes(&clkmgr, &err_codes));
      if (err_codes == 0) {
        pass_cout++;
      }
      // Without this delay, I get random results, probably the clkmgr needs some time to sync
      // some changes to the registers.
      busy_spin_micros(clkmgr_aon_sync_delay);
    }
    LOG_INFO("%d: pass=%u%%", cycles, pass_cout * 100 / kMeasurementsRetry);
  }
}

static void analyze_clock_frequencies_jitter(
  dif_clkmgr_measure_clock_t clock,
  uint64_t freq) {

  uint32_t delay_micros = 0;
  CHECK_STATUS_OK(aon_timer_testutils_get_us_from_aon_cycles(
      kMeasurementsPerRound, &delay_micros));
  jitter_statistics_t stats;
  measure_clock_frequencies_jitter(&stats, delay_micros, clock, freq, clkmgr_testutils_measurement_name(clock));
}

bool test_main(void) {
  dif_sensor_ctrl_t sensor_ctrl;

  CHECK_DIF_OK(dif_clkmgr_init(
      mmio_region_from_addr(TOP_EARLGREY_CLKMGR_AON_BASE_ADDR), &clkmgr));
  CHECK_DIF_OK(dif_sensor_ctrl_init(
      mmio_region_from_addr(TOP_EARLGREY_SENSOR_CTRL_AON_BASE_ADDR),
      &sensor_ctrl));
  CHECK_DIF_OK(dif_pwrmgr_init(
      mmio_region_from_addr(TOP_EARLGREY_PWRMGR_AON_BASE_ADDR), &pwrmgr));

  CHECK_STATUS_OK(aon_timer_testutils_get_us_from_aon_cycles(
      1, &clkmgr_aon_sync_delay));

  LOG_INFO("TEST: wait for ast init");
  IBEX_SPIN_FOR(sensor_ctrl_ast_init_done(&sensor_ctrl), 1000);
  LOG_INFO("TEST: done ast init");

  CHECK(UNWRAP(pwrmgr_testutils_is_wakeup_reason(&pwrmgr, 0)) == true);

  // CHECK_DIF_OK(dif_clkmgr_jitter_set_enabled(&clkmgr));
  analyze_clock_frequencies_jitter(kDifClkmgrMeasureClockMain, kClockFreqCpuHz);
  return true;
}
