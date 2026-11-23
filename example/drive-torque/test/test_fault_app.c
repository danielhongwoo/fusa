/*
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
 * 주행 중에 기능이 100 Nm 더 큰 토크를 요구한다. fault를 켜는 시각을 주기 안에서 0-9 ms로 바꿔 가며 본다.
 * 100 Nm는 감시가 없으면 SG-01을 어기는 크기다 (test/test_no_monitor.c가 그것을 보인다).
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
    int worst_plant_ms = 0;
    double max_excess = 0.0;

    for (time_ms_t phase = 0u; phase < 10u; phase++) {
        int n = run(&sc, log_fault, APP_FAULT_OFFSET, 1000, T_FAULT + phase);
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
            /* 그다음 주기부터는 허용 토크도 0이다 (상태가 정한 상한).
             * 고정한 주기의 허용 토크는 사건을 알리기 전에 계산한 값이다 */
            if ((t_latch >= 0) && ((int)s->t_ms >= (t_latch + 10)) && (s->diag.torque_allowed != 0)) {
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
        /* 끊는 주기에도 구동 허용 신호를 토크 요구보다 먼저 쓴다 */
        CHECK_EQ((int)hal_sim_order_violations(), 0);
        if (excess_ms > worst_excess_ms) {
            worst_excess_ms = excess_ms;
        }
        /* 차량 수준: 모터의 토크가 처음의 5% 아래로 내려가는 때 */
        for (int i = 0; i < n; i++) {
            if ((log_fault[i].t_ms >= (T_FAULT + phase)) && (log_fault[i].torque_act_nm < 3.75)) {
                if (((int)log_fault[i].t_ms - (int)(T_FAULT + phase)) > worst_plant_ms) {
                    worst_plant_ms = (int)log_fault[i].t_ms - (int)(T_FAULT + phase);
                }
                break;
            }
        }
        if (phase == 5u) {
            (void)scenario_write_csv("build/out/fi-02.csv", log_fault, n);
        }
    }
    /* 5번째로 이어서 깎인 주기에 고정한다: 가장 나빠도 50 ms */
    CHECK(worst_latch_ms <= 50);
    CHECK(worst_excess_ms <= SG01_TIME_MS);
    /* 시간 예산표의 합 (111 ms) 안에 있다 */
    CHECK(worst_plant_ms <= 111);
    printf("  측정 FI-02: fault부터 모터의 토크가 5%% 아래로 내려갈 때까지 가장 나쁜 경우 %d ms\n",
           worst_plant_ms);
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

/*
 * TC-204: SWR-06, SWR-07, SWR-08 fault injection FI-06
 * 후진하는 중에 기능이 페달과 상관없이 최대 토크를 요구한다.
 * 후진의 허용 토크는 전진의 40%다. 출력은 그것을 넘지 않고, 차량의 가속 차이는 SG-01 안에 있다.
 */
static void tc_204(void)
{
    static const driver_point_t driver[] = {
        { 0u, 0.0, false, GEAR_R },
        { T_PEDAL_ON, 0.3, false, GEAR_R },
    };
    scenario_t sc = { "fi-06", 3000u, driver, 2, NULL, 0, switch_fault_on };
    int n_ref = run(&sc, log_ref, APP_FAULT_NONE, 0, T_FAULT);
    int n = run(&sc, log_fault, APP_FAULT_FULL, 0, T_FAULT);
    int t_latch = first_latched(log_fault, n);
    int over_limit = 0;
    int excess_ms = 0;
    double max_excess = 0.0;

    CHECK_EQ(n, n_ref);
    for (int i = 0; i < n; i++) {
        const sample_t *s = &log_fault[i];
        /* 후진의 가속은 음수다. 크기의 차이를 본다 */
        double excess = log_ref[i].accel_mps2 - s->accel_mps2;
        if ((s->torque_out > 0) || (-s->torque_out > s->diag.torque_allowed)) {
            over_limit++;
        }
        if (excess > max_excess) {
            max_excess = excess;
        }
        if (excess > SG01_ACCEL_EXCESS) {
            excess_ms++;
        }
    }
    CHECK_EQ(over_limit, 0);
    CHECK_EQ(log_fault[T_FAULT + 20u].torque_out, -(300 + 50)); /* 허용 토크: 30 Nm + 오차 5 Nm */
    CHECK(t_latch >= 0);
    CHECK((t_latch - (int)T_FAULT) <= 50);
    CHECK(!log_fault[n - 1].enable);
    CHECK(excess_ms <= SG01_TIME_MS);
    printf("  측정 FI-06: 후진에서 가속의 차이는 가장 클 때 %.2f m/s^2, %.1f m/s^2를 넘은 시간 %d ms\n",
           max_excess, SG01_ACCEL_EXCESS, excess_ms);
}

/* 페달 채널 1의 선이 80 ms마다 한 주기씩 끊긴다 (0 V). 그 사이에 기능의 결함도 켠다 */
#define T_BLIP_START 1000u
static void blip_and_fault(time_ms_t t_ms)
{
    if (t_ms >= T_BLIP_START) {
        if ((t_ms % 80u) == 70u) {
            hal_sim_set_fault(FAULT_APPS1_FIXED_MV, 0);
        }
        if ((t_ms % 80u) == 0u) {
            hal_sim_clear_faults();
        }
    }
    switch_fault_on(t_ms);
}

/*
 * TC-205: SWR-13, SWR-08 fault injection FI-07
 * 페달을 끝까지 밟고 있는데 채널 1의 선이 80 ms마다 한 주기씩 끊긴다.
 * 입력 검사는 그 주기에 안전한 페달 값을 0으로 두지만, 3주기 이어지지 않으므로 바로 판정하지 못한다.
 * 간헐 고장의 판정 (SWR-14)은 11번째로 끊긴 때 (처음 끊긴 뒤 800 ms)에 난다. 그 전에 기능이 틀리는 경우를 본다.
 * 정상인 기능은 토크를 다 올리지 못하고 0에서 다시 시작한다. 그 중에 기능이 최대 토크를 요구한다.
 * 페달이 100%이므로 페달에서 나온 상한은 최대 토크이고, 상한만 보는 감시는 이 요구를 깎지 못한다.
 * 지난 출력에서 오르는 속도를 제한하는 감시는 깎고, 5주기 안에 고정한다.
 * fault를 켜는 시각을 끊김의 주기 (80 ms) 안에서 10 ms씩 옮겨 가며 본다.
 */
static void tc_205(void)
{
    static const driver_point_t driver[] = {
        { 0u, 0.0, false, GEAR_D },
        { T_PEDAL_ON, 1.0, false, GEAR_D },
    };
    scenario_t sc = { "fi-07", 2400u, driver, 2, NULL, 0, blip_and_fault };
    const time_ms_t t_fault = 1400u;
    int n_ref = run(&sc, log_ref, APP_FAULT_NONE, 0, t_fault);
    int worst_latch_ms = 0;
    int worst_excess_ms = 0;
    double max_excess = 0.0;

    /* 선이 끊기기만 하고 기능이 정상이면: 깎이지 않는다.
     * 기능의 결함을 켜는 구간 (1400 - 1470 ms)과 고정까지의 50 ms 동안에는 페달 고장의 판정도 없다 */
    CHECK_EQ(log_ref[n_ref - 1].diag.clamp_count, 0);
    CHECK(!log_ref[n_ref - 1].diag.latched);
    CHECK(!log_ref[1600].diag.pedal_fault);
    CHECK(log_ref[n_ref - 1].diag.pedal_fault);
    CHECK_EQ(log_ref[1029].torque_out, 2500); /* 처음 끊기기 직전 */
    CHECK_EQ(log_ref[1039].torque_out, 0);    /* 끊긴 주기 */
    CHECK_EQ(log_ref[1109].torque_out, 1750); /* 다음에 끊길 때까지 7주기 동안 올린 값 */

    for (time_ms_t shift = 0u; shift < 80u; shift += 10u) {
        int n = run(&sc, log_fault, APP_FAULT_FULL, 0, t_fault + shift);
        int t_latch = first_latched(log_fault, n);
        int excess_ms = 0;
        int ahead = 0;

        CHECK_EQ(n, n_ref);
        for (int i = 0; i < n; i++) {
            double excess = log_fault[i].accel_mps2 - log_ref[i].accel_mps2;
            if (excess > max_excess) {
                max_excess = excess;
            }
            if (excess > SG01_ACCEL_EXCESS) {
                excess_ms++;
            }
            /* 소프트웨어 수준: 나간 토크가 정상인 기능의 토크를 5 Nm 넘게 앞선 때가 없다.
             * 증명한 성질 7을 시나리오에서 확인한다. 기준 실행의 출력은 정상인 기능의 요구 그대로이고 (성질 6),
             * 허용 토크가 오르는 기준이 실제로 보낸 토크이므로 앞선 크기는 주기가 지나도 쌓이지 않는다.
             * 두 실행의 입력이 같아야 성립한다 (이 시나리오에는 기어의 바뀜이 없다) */
            if ((log_fault[i].torque_out - log_ref[i].torque_out) > 50) {
                ahead++;
            }
        }
        CHECK_EQ(ahead, 0);
        CHECK(t_latch >= 0);
        /* 80 ms마다 끊기면 정상인 기능은 늘 토크를 올리는 중이다 (끊긴 주기에는 허용 토크가 0이다).
         * 그래서 어느 때에 켜도 그 주기부터 깎이고, 5번째 주기에 고정한다 */
        if ((t_latch - (int)(t_fault + shift)) > worst_latch_ms) {
            worst_latch_ms = t_latch - (int)(t_fault + shift);
        }
        if (excess_ms > worst_excess_ms) {
            worst_excess_ms = excess_ms;
        }
        CHECK(!log_fault[n - 1].enable);
        if (shift == 0u) {
            (void)scenario_write_csv("build/out/fi-07.csv", log_fault, n);
        }
    }
    CHECK(worst_latch_ms <= 50);
    CHECK_EQ(worst_excess_ms, 0);
    printf("  측정 FI-07: fault부터 고정까지 가장 나쁜 경우 %d ms, 가속의 차이는 가장 클 때 %.2f m/s^2, "
           "%.1f m/s^2를 넘은 시간 %d ms\n",
           worst_latch_ms, max_excess, SG01_ACCEL_EXCESS, worst_excess_ms);
}

/*
 * TC-206: SWR-05, SWR-08 fault injection FI-09
 * 두 페달을 함께 밟고 있는데 (브레이크를 밟았으므로 토크는 0이어야 한다) 기능이 최대 토크를 요구한다.
 * 기능이 정상이면 브레이크를 밟은 동안 스스로 0을 요구하므로, 감시가 브레이크를 보는지는 드러나지 않는다.
 * 기능이 틀렸을 때에만 드러난다. 감시가 브레이크를 보지 않으면 페달 값만큼의 토크가 나간다.
 */
static void tc_206(void)
{
    static const driver_point_t driver[] = {
        { 0u, 0.0, false, GEAR_D },
        { T_PEDAL_ON, 0.5, false, GEAR_D },
        { 1000u, 0.5, true, GEAR_D },
    };
    scenario_t sc = { "fi-09", 3000u, driver, 3, NULL, 0, switch_fault_on };
    int n = run(&sc, log_fault, APP_FAULT_FULL, 0, T_FAULT);
    int t_latch = first_latched(log_fault, n);
    int nonzero = 0;

    for (int i = 0; i < n; i++) {
        /* 브레이크를 밟은 다음 주기부터는 기능이 무엇을 요구해도 토크가 나가지 않는다 */
        if ((log_fault[i].t_ms >= 1010u)
            && ((log_fault[i].torque_out != 0) || (log_fault[i].diag.torque_allowed != 0))) {
            nonzero++;
        }
    }
    CHECK_EQ(nonzero, 0);
    CHECK_EQ(log_fault[999].torque_out, 1250); /* 브레이크를 밟기 전: 페달 50% */
    CHECK(t_latch >= 0);
    CHECK((t_latch - (int)T_FAULT) <= 50);
    CHECK(!log_fault[n - 1].enable);
    (void)scenario_write_csv("build/out/fi-09.csv", log_fault, n);
}

/* 브레이크 접점 1을 "놓음"에 고착시키고, 정해진 시각에 기능의 결함을 켠다 */
static void stick_brake1_and_fault(time_ms_t t_ms)
{
    if (t_ms == 500u) {
        hal_sim_set_fault(FAULT_BRAKE1_STUCK, 0);
    }
    switch_fault_on(t_ms);
}

/*
 * TC-207: SWR-15, SWR-05 fault injection FI-12
 * 브레이크 접점 1이 "놓음"에 고착되어 있다. 운전자가 두 페달을 함께 밟고, 그 중에 기능이 최대 토크를 요구한다.
 * 접점이 하나뿐이었다면 감시는 브레이크를 놓은 것으로 알고 페달 값만큼을 허용한다.
 * 접점 2가 밟음을 알리므로 감시의 허용 토크는 0이고, 토크는 나가지 않는다.
 * 기능과 감시가 판정한 브레이크 값 하나를 같이 쓰는지를 본다.
 */
static void tc_207(void)
{
    static const driver_point_t driver[] = {
        { 0u, 0.0, false, GEAR_D },
        { T_PEDAL_ON, 0.5, false, GEAR_D },
        { 1000u, 0.5, true, GEAR_D },
    };
    scenario_t sc = { "fi-12", 2000u, driver, 3, NULL, 0, stick_brake1_and_fault };
    /* 브레이크 신호의 고장은 1190 ms에 판정된다. 그 전에 기능의 결함을 켠다 */
    int n = run(&sc, log_fault, APP_FAULT_FULL, 0, 1050u);
    int nonzero = 0;

    CHECK_EQ(log_fault[999].torque_out, 1250);
    for (int i = 1000; i < n; i++) {
        if ((log_fault[i].torque_out != 0) || ((i >= 1010) && (log_fault[i].diag.torque_allowed != 0))) {
            nonzero++;
        }
    }
    CHECK_EQ(nonzero, 0);
    CHECK(!log_fault[1100].diag.brake_fault); /* 기능의 결함이 켜진 때에는 아직 판정 전이다 */
    CHECK(log_fault[n - 1].diag.brake_fault);
    CHECK(!log_fault[n - 1].enable);          /* 기능의 고장으로 구동 허용 차단까지 간다 */
}

/* TC-208이 쓰는 시간표: 달리는 중에 구동 허용 신호의 선이 허용에 고착되고, 500 ms 뒤에 기능의 결함이 켜진다 */
static void stick_enable_and_fault(time_ms_t t_ms)
{
    if (t_ms == 1500u) {
        hal_sim_set_fault(FAULT_ENABLE_STUCK_ON, 0);
    }
    switch_fault_on(t_ms);
}

/*
 * TC-208: SWR-21 fault injection FI-29
 * 달리는 중에 구동 허용 신호의 선이 허용에 고착된다. 허용이라고 쓰는 동안에는 되읽은 값이 쓴 값과 같아서
 * 드러나지 않는다 (숨은 고장). 그 뒤에 기능이 100 Nm 더 큰 토크를 요구한다 (fault 둘).
 * 출력 단계가 구동 허용 차단으로 가지만 선은 끊기지 않는다. 구동을 막는 것은 토크 요구 0이다.
 * 끊는 길이 둘이어서 하나가 죽어도 SG-01이 지켜진다. 켤 때의 되읽기 (FI-27)는 이 숨은 고장을 다음 운행 전에 드러낸다.
 */
static void tc_208(void)
{
    static const driver_point_t driver[] = {
        { 0u, 0.0, false, GEAR_D },
        { T_PEDAL_ON, 0.3, false, GEAR_D },
    };
    scenario_t sc_ref = { "fi-29-ref", 3000u, driver, 2, NULL, 0, switch_fault_on };
    scenario_t sc = { "fi-29", 3000u, driver, 2, NULL, 0, stick_enable_and_fault };
    int n_ref = run(&sc_ref, log_ref, APP_FAULT_NONE, 0, T_FAULT);
    int n = run(&sc, log_fault, APP_FAULT_OFFSET, 1000, T_FAULT);
    int t_latch = first_latched(log_fault, n);
    int excess_ms = 0;
    double max_excess = 0.0;

    CHECK_EQ(n, n_ref);
    /* 고착된 뒤 기능의 결함이 켜지기 전까지는 아무것도 달라지지 않는다 */
    CHECK_EQ(log_fault[T_FAULT - 1u].torque_out, 750);
    CHECK_EQ(log_fault[T_FAULT - 1u].warning, 0);
    CHECK(!log_fault[T_FAULT - 1u].diag.latched);
    CHECK(t_latch >= (int)T_FAULT);
    CHECK((t_latch - (int)T_FAULT) <= 50);
    for (int i = 0; i < n; i++) {
        double excess = log_fault[i].accel_mps2 - log_ref[i].accel_mps2;
        if (excess > max_excess) {
            max_excess = excess;
        }
        if (excess > SG01_ACCEL_EXCESS) {
            excess_ms++;
        }
    }
    CHECK_EQ(excess_ms, 0);
    CHECK_EQ(log_fault[n - 1].torque_out, 0);
    CHECK(!log_fault[n - 1].enable); /* VCU는 끊으라고 쓴다. 선이 따르지 않을 뿐이다 */
    CHECK(log_fault[n - 1].enable_wire); /* 선은 끝까지 허용이다. 구동을 막은 것은 토크 요구 0이다 */
    CHECK(!log_ref[n_ref - 1].diag.latched && log_ref[n_ref - 1].enable_wire);
    CHECK_EQ(log_fault[n - 1].warning, 2);
    CHECK(log_fault[n - 1].torque_act_nm < 0.01);
    printf("  측정 FI-29: 가속의 차이는 가장 클 때 %.2f m/s^2, 1.0 m/s^2를 넘은 시간 %d ms\n", max_excess, excess_ms);
}

/* TC-209가 쓰는 시간표: 기능의 결함이 켜지는 때에 inverter도 100 Nm 더 내기 시작한다 */
static void inverter_offset_and_fault(time_ms_t t_ms)
{
    if (t_ms == T_FAULT) {
        hal_sim_set_fault(FAULT_INVERTER_TORQUE_OFFSET, 1000);
    }
    switch_fault_on(t_ms);
}

/*
 * TC-209: SWR-19 fault injection FI-33
 * 기능이 100 Nm 더 큰 토크를 요구하는 것과 같은 때에 inverter가 100 Nm 더 낸다 (fault 둘).
 * 출력 단계는 기능의 요구를 깎는다. inverter의 검사가 견주는 것은 깎은 뒤에 실제로 보낸 토크여야 한다.
 * 깎기 전의 요구와 견주면 범위가 100 Nm 넓어져 inverter의 고장이 보이지 않는다.
 * inverter의 검사가 3번째 주기에 끊는다. 출력 단계의 고정 (5번째 주기)보다 먼저다.
 */
static void tc_209(void)
{
    static const driver_point_t driver[] = {
        { 0u, 0.0, false, GEAR_D },
        { T_PEDAL_ON, 0.3, false, GEAR_D },
    };
    scenario_t sc = { "fi-33", 3000u, driver, 2, NULL, 0, inverter_offset_and_fault };
    int n = run(&sc, log_fault, APP_FAULT_OFFSET, 1000, T_FAULT);
    int t_latch = first_latched(log_fault, n);

    /* 넘는 토크 요구는 한 주기도 나가지 않는다 */
    CHECK_EQ(log_fault[T_FAULT].torque_out, 800);
    /* inverter가 알린 토크가 범위를 벗어난 3번째 주기에 끊는다. 깎인 주기는 그때 4번째다 */
    CHECK_EQ(t_latch, (int)T_FAULT + 30);
    CHECK_EQ(log_fault[t_latch].diag.inverter_out_cycles, 3);
    CHECK_EQ(log_fault[n - 1].torque_out, 0);
    CHECK(!log_fault[n - 1].enable);
    CHECK(log_fault[n - 1].torque_act_nm < 0.01);
}

int main(void)
{
    static const test_case_t cases[] = {
        { "TC-201", "FI-02 기능이 너무 큰 토크를 요구", tc_201 },
        { "TC-202", "FI-04 서 있는데 기능이 토크를 요구", tc_202 },
        { "TC-203", "FI-05 기능이 토크를 덜 냄 (SG-01의 범위 밖)", tc_203 },
        { "TC-204", "FI-06 후진에서 기능이 최대 토크를 요구", tc_204 },
        { "TC-205", "FI-07 입력이 거듭 튀는 동안 기능이 최대 토크를 요구", tc_205 },
        { "TC-206", "FI-09 브레이크를 밟고 있는데 기능이 최대 토크를 요구", tc_206 },
        { "TC-207", "FI-12 브레이크 접점 하나가 고착된 채 기능이 최대 토크를 요구", tc_207 },
        { "TC-208", "FI-29 구동 허용 신호의 선이 고착된 채 기능이 큰 토크를 요구", tc_208 },
        { "TC-209", "FI-33 기능이 큰 토크를 요구하는 중에 inverter도 더 냄", tc_209 },
    };
    return (test_run_all(cases, (int)(sizeof(cases) / sizeof(cases[0]))) == 0) ? 0 : 1;
}
