/*
 * 책의 예제 코드다. 실제 제품에 쓸 수 없다.
 * 기능의 고장을 넣는 test. 기능 모듈을 결함이 있는 것 (test/faulty/app_fault.c)으로 바꿔 끼워 link한다.
 * 제품의 소스에는 test용 코드가 없다.
 * test마다 어느 요구사항을 보는지 "TC-번호: SWR-번호"로 적는다.
 */
#include <stddef.h>

#include "app_fault.h"
#include "scenario.h"
#include "test.h"

#define LOG_CAP 4000
static sample_t log_fault[LOG_CAP];
static sample_t log_ref[LOG_CAP];

#define T_PEDAL_ON 200u
#define T_FAULT    2000u

/* SG-01의 가정값 */
#define SG01_ACCEL_EXCESS 1.0 /* m/s^2 */
#define SG01_TIME_MS      200

static time_ms_t fault_at_ms;
static app_fault_mode_t fault_mode;
static torque_t fault_offset;

/* 정해진 시각에 기능의 결함을 켠다 */
static void switch_fault_on(time_ms_t t_ms)
{
    if (t_ms == fault_at_ms) {
        app_fault_set(fault_mode, fault_offset);
    }
}

static int run(const scenario_t *sc, sample_t *log, app_fault_mode_t mode, torque_t offset,
               time_ms_t at_ms)
{
    app_fault_set(APP_FAULT_NONE, 0);
    fault_mode = mode;
    fault_offset = offset;
    fault_at_ms = at_ms;
    return scenario_run(sc, log, LOG_CAP);
}

static int first_latched(const sample_t *log, int n)
{
    for (int i = 0; i < n; i++) {
        if (log[i].diag.latched) {
            return (int)log[i].t_ms;
        }
    }
    return -1;
}

/*
 * TC-201: SWR-07, SWR-08, SWR-09, SWR-10, SWR-11 fault injection FI-02
 * 주행 중에 기능이 30 Nm 더 큰 토크를 요구한다. fault를 켜는 시각을 주기 안에서 0-9 ms로 바꿔 가며 본다.
 */
static void tc_201(void)
{
    static const driver_point_t driver[] = {
        { 0u, 0.0, false, GEAR_D },
        { T_PEDAL_ON, 0.3, false, GEAR_D },
    };
    scenario_t sc = { "fi-02", 3000u, driver, 2, NULL, 0, switch_fault_on };
    int n_ref = run(&sc, log_ref, APP_FAULT_NONE, 0, T_FAULT);
    int worst_latch_ms = 0;
    int worst_excess_ms = 0;
    double max_excess = 0.0;

    for (time_ms_t phase = 0u; phase < 10u; phase++) {
        int n = run(&sc, log_fault, APP_FAULT_OFFSET, 300, T_FAULT + phase);
        int t_latch = first_latched(log_fault, n);
        int over_limit = 0;
        int after_latch_bad = 0;
        int excess_ms = 0;

        CHECK_EQ(n, n_ref);
        CHECK(t_latch >= 0);
        if ((t_latch - (int)(T_FAULT + phase)) > worst_latch_ms) {
            worst_latch_ms = t_latch - (int)(T_FAULT + phase);
        }
        for (int i = 0; i < n; i++) {
            const sample_t *s = &log_fault[i];
            /* 소프트웨어 수준: 넘는 토크는 한 주기도 나가지 않는다 */
            if (s->torque_out > s->diag.torque_allowed) {
                over_limit++;
            }
            /* 고정한 주기부터 토크 0, 구동 허용 신호 차단, 경고 */
            if ((t_latch >= 0) && ((int)s->t_ms >= t_latch)
                && ((s->torque_out != 0) || s->enable || (s->warning != 2u))) {
                after_latch_bad++;
            }
            /* 차량 수준: 고장이 없을 때와 견준 가속의 차이 */
            double excess = s->accel_mps2 - log_ref[i].accel_mps2;
            if (excess > max_excess) {
                max_excess = excess;
            }
            if (excess > SG01_ACCEL_EXCESS) {
                excess_ms++;
            }
        }
        CHECK_EQ(over_limit, 0);
        CHECK_EQ(after_latch_bad, 0);
        if (excess_ms > worst_excess_ms) {
            worst_excess_ms = excess_ms;
        }
        if (phase == 5u) {
            (void)scenario_write_csv("build/out/fi-02.csv", log_fault, n);
        }
    }
    /* 5번째로 이어서 깎인 주기에 고정한다: 가장 나빠도 50 ms */
    CHECK(worst_latch_ms <= 50);
    CHECK(worst_excess_ms <= SG01_TIME_MS);
    printf("  측정 FI-02: fault부터 고정과 차단까지 가장 나쁜 경우 %d ms\n", worst_latch_ms);
    printf("  측정 FI-02: 가속의 차이는 가장 클 때 %.2f m/s^2, %.1f m/s^2를 넘은 시간 %d ms\n",
           max_excess, SG01_ACCEL_EXCESS, worst_excess_ms);
}

/*
 * TC-202: SWR-05, SWR-08 fault injection FI-04
 * 페달을 놓고 서 있는데 기능이 토크를 요구한다. 출력은 0이고 차는 움직이지 않는다.
 */
static void tc_202(void)
{
    static const driver_point_t driver[] = {
        { 0u, 0.0, false, GEAR_D },
    };
    scenario_t sc = { "fi-04", 2000u, driver, 1, NULL, 0, switch_fault_on };
    int n = run(&sc, log_fault, APP_FAULT_OFFSET, 300, 1000u);
    int t_latch = first_latched(log_fault, n);
    int moved = 0;

    for (int i = 0; i < n; i++) {
        if ((log_fault[i].torque_out != 0) || (log_fault[i].speed_mps != 0.0)) {
            moved++;
        }
    }
    CHECK_EQ(moved, 0);
    CHECK(t_latch >= 0);
    CHECK((t_latch - 1000) <= 50);
    CHECK(!log_fault[n - 1].enable);
}

/*
 * TC-203: SWR-07 fault injection FI-05 (SG-01의 범위 밖)
 * 기능이 토크를 절반만 낸다. 허용 범위 안이므로 그대로 나가고, 감시는 알아채지 못한다.
 */
static void tc_203(void)
{
    static const driver_point_t driver[] = {
        { 0u, 0.0, false, GEAR_D },
        { T_PEDAL_ON, 0.3, false, GEAR_D },
    };
    scenario_t sc = { "fi-05", 3000u, driver, 2, NULL, 0, switch_fault_on };
    int n_ref = run(&sc, log_ref, APP_FAULT_NONE, 0, T_FAULT);
    int n = run(&sc, log_fault, APP_FAULT_HALF, 0, T_FAULT);
    const sample_t *last = &log_fault[n - 1];

    CHECK_EQ(n, n_ref);
    CHECK(!last->diag.latched);
    CHECK_EQ(last->diag.clamp_count, 0);
    CHECK_EQ(last->warning, 0);
    CHECK_EQ(last->torque_out, log_ref[n - 1].torque_out / 2);
    (void)scenario_write_csv("build/out/fi-05.csv", log_fault, n);
}

int main(void)
{
    static const test_case_t cases[] = {
        { "TC-201", "FI-02 기능이 너무 큰 토크를 요구", tc_201 },
        { "TC-202", "FI-04 서 있는데 기능이 토크를 요구", tc_202 },
        { "TC-203", "FI-05 기능이 토크를 덜 냄 (SG-01의 범위 밖)", tc_203 },
    };
    return (test_run_all(cases, (int)(sizeof(cases) / sizeof(cases[0]))) == 0) ? 0 : 1;
}
