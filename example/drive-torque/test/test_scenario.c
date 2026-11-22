/*
 * 책의 예제 코드다. 실제 제품에 쓸 수 없다.
 * 시나리오 test: VCU 전체를 plant model과 함께 돌린다. fault는 HAL의 뒤에서 넣는다.
 * test마다 어느 요구사항을 보는지 "TC-번호: SWR-번호"로 적는다.
 */
#include <stddef.h>
#include <string.h>

#include "scenario.h"
#include "vcu.h"
#include "test.h"

#define LOG_CAP 10000
static sample_t log_buf[LOG_CAP];
static sample_t log_ref[LOG_CAP]; /* 고장이 없는 실행. 차량 수준의 차이를 재는 기준이다 */

#define T_PEDAL_ON 200u
#define T_FAULT    2000u

/* 조건이 처음 참이 되는 시각을 찾는다. 없으면 -1 */
static int first_time(const sample_t *log, int n, time_ms_t from_ms, int (*pred)(const sample_t *))
{
    for (int i = 0; i < n; i++) {
        if ((log[i].t_ms >= from_ms) && pred(&log[i])) {
            return (int)log[i].t_ms;
        }
    }
    return -1;
}

static int is_latched(const sample_t *s) { return s->diag.latched; }

/* 구동 허용 차단이 된 뒤로 토크 0, 구동 허용 신호 차단, 경고가 유지되는가. 어긴 줄의 수를 돌려준다 */
static int bad_after_cut(const sample_t *log, int n, int t_cut)
{
    int bad = 0;

    for (int i = 0; i < n; i++) {
        if (((int)log[i].t_ms >= t_cut)
            && ((log[i].torque_out != 0) || log[i].enable || (log[i].warning != 2u))) {
            bad++;
        }
    }
    return bad;
}

static int is_pedal_fault_and_zero(const sample_t *s)
{
    return s->diag.pedal_fault && (s->torque_out == 0);
}

static int is_torque_zero(const sample_t *s) { return s->torque_out == 0; }

/* TC-101: SWR-10, SWR-11 고장이 없으면 구동을 막지 않고 경고도 요청하지 않는다 */
static void tc_101(void)
{
    static const driver_point_t driver[] = {
        { 0u, 0.0, false, GEAR_D },
        { T_PEDAL_ON, 0.3, false, GEAR_D },
        { 3000u, 0.0, false, GEAR_D },
        { 4000u, 0.0, true, GEAR_D },
    };
    scenario_t sc = { "nominal", 5000u, driver, 4, NULL, 0, NULL };
    int n = scenario_run(&sc, log_buf, LOG_CAP);
    int bad = 0;

    for (int i = 0; i < n; i++) {
        const sample_t *s = &log_buf[i];
        if (s->diag.pedal_fault || s->diag.latched || (s->warning != 0u) || s->watchdog_tripped
            || (s->diag.clamp_count != 0u) || ((s->t_ms >= 20u) && !s->enable)) {
            bad++;
        }
    }
    CHECK_EQ(bad, 0);
    /* 출력을 쓰는 순서: 주기마다 구동 허용 신호를 먼저 쓰고 토크 요구를 보낸다 (docs/hsi.md 4절) */
    CHECK_EQ((int)hal_sim_order_violations(), 0);
    CHECK_EQ(log_buf[2900].torque_out, 750);       /* 페달 30% -> 75 Nm */
    CHECK(log_buf[2900].speed_mps > 2.0);
    CHECK_EQ(log_buf[3020].torque_out, 0);         /* 페달을 놓으면 바로 0 */
    CHECK(log_buf[n - 1].speed_mps < 0.01);        /* 브레이크로 멈춘다 */
    (void)scenario_write_csv("build/out/nominal.csv", log_buf, n);
}

/*
 * TC-102: SWR-02, SWR-03, SWR-04, SWR-11 fault injection FI-01
 * 페달 채널 1이 높은 값에 고착된다. fault를 넣는 시각을 주기 안에서 0-9 ms로 바꿔 가며 본다.
 */
static void tc_102(void)
{
    static const driver_point_t driver[] = {
        { 0u, 0.0, false, GEAR_D },
        { T_PEDAL_ON, 0.3, false, GEAR_D },
    };
    const torque_t limit_true = 750 + 50; /* 실제 페달 위치 (30%)의 허용 토크: 75 Nm + 오차 5 Nm */
    int worst_ms = 0;
    int worst_plant_ms = 0;

    for (time_ms_t phase = 0u; phase < 10u; phase++) {
        fault_event_t fault = { T_FAULT + phase, FAULT_APPS1_FIXED_MV, 4500 };
        scenario_t sc = { "fi-01", 3000u, driver, 2, &fault, 1, NULL };
        int n = scenario_run(&sc, log_buf, LOG_CAP);
        int t_zero = first_time(log_buf, n, fault.t_ms, is_pedal_fault_and_zero);
        int excess = 0;
        int escalated = 0;

        CHECK(t_zero >= 0);
        if ((t_zero - (int)fault.t_ms) > worst_ms) {
            worst_ms = t_zero - (int)fault.t_ms;
        }
        for (int i = 0; i < n; i++) {
            const sample_t *s = &log_buf[i];
            /* 판정 전에도 출력은 낮은 채널을 따른다: 실제 페달 위치의 허용 토크를 넘지 않는다 */
            if (s->torque_out > limit_true) {
                excess++;
            }
            /* 페달 고장은 기능의 고장이 아니다: 고정하지 않고 구동 허용 신호도 끊지 않는다 */
            if (s->diag.latched || ((s->t_ms >= 20u) && !s->enable)) {
                escalated++;
            }
            /* 판정한 뒤로는 토크 0과 경고가 유지된다 */
            if ((t_zero >= 0) && ((int)s->t_ms >= t_zero)
                && ((s->torque_out != 0) || (s->warning != 2u))) {
                excess++;
            }
        }
        CHECK_EQ(excess, 0);
        CHECK_EQ(escalated, 0);
        /* 차량 수준: 모터의 토크가 처음의 5% 아래로 내려가는 때 */
        for (int i = 0; i < n; i++) {
            if ((log_buf[i].t_ms >= fault.t_ms) && (log_buf[i].torque_act_nm < 3.75)) {
                if (((int)log_buf[i].t_ms - (int)fault.t_ms) > worst_plant_ms) {
                    worst_plant_ms = (int)log_buf[i].t_ms - (int)fault.t_ms;
                }
                break;
            }
        }
        if (phase == 5u) {
            (void)scenario_write_csv("build/out/fi-01.csv", log_buf, n);
        }
    }
    /* 3번째로 이어서 실패를 본 주기에 반영한다: 가장 나빠도 30 ms */
    CHECK(worst_ms <= 30);
    /* 시간 예산표의 합 (92 ms)과 SG-01의 시간 (200 ms) 안에 있다 */
    CHECK(worst_plant_ms <= 92);
    printf("  측정 FI-01: fault부터 토크 요구 0까지 가장 나쁜 경우 %d ms\n", worst_ms);
    printf("  측정 FI-01: fault부터 모터의 토크가 5%% 아래로 내려갈 때까지 가장 나쁜 경우 %d ms\n",
           worst_plant_ms);
}

/*
 * TC-103: SWR-02 fault injection FI-03 (알려진 한계)
 * 센서의 전원이 올라가 두 채널이 같은 비율로 올라간다. 두 채널이 일치하므로 알아채지 못한다.
 */
static void tc_103(void)
{
    static const driver_point_t driver[] = {
        { 0u, 0.0, false, GEAR_D },
        { T_PEDAL_ON, 0.3, false, GEAR_D },
    };
    fault_event_t fault = { T_FAULT, FAULT_APPS_SUPPLY_SCALE, 120 };
    scenario_t sc = { "fi-03", 3000u, driver, 2, &fault, 1, NULL };
    int n = scenario_run(&sc, log_buf, LOG_CAP);
    const sample_t *last = &log_buf[n - 1];

    CHECK(!last->diag.pedal_fault);
    CHECK_EQ(last->warning, 0);
    CHECK_EQ(last->diag.pedal_safe, 385); /* 운전자는 30%를 밟았는데 38.5%로 읽는다 */
    CHECK(last->torque_out > 750);        /* 토크가 따라 올라간다 */
    (void)scenario_write_csv("build/out/fi-03.csv", log_buf, n);
}

/* TC-104: SWR-05 브레이크를 밟으면 다음 주기부터 토크 0이 나간다 */
static void tc_104(void)
{
    static const driver_point_t driver[] = {
        { 0u, 0.0, false, GEAR_D },
        { T_PEDAL_ON, 0.5, false, GEAR_D },
        { T_FAULT + 3u, 0.5, true, GEAR_D },
    };
    scenario_t sc = { "brake", 3000u, driver, 3, NULL, 0, NULL };
    int n = scenario_run(&sc, log_buf, LOG_CAP);
    int t_zero = first_time(log_buf, n, T_FAULT + 3u, is_torque_zero);

    CHECK(log_buf[T_FAULT].torque_out > 0);
    CHECK(t_zero >= 0);
    CHECK((t_zero - (int)(T_FAULT + 3u)) <= 10);
    CHECK_EQ(log_buf[n - 1].torque_out, 0);
    CHECK(!log_buf[n - 1].diag.latched);
    CHECK_EQ(log_buf[n - 1].diag.clamp_count, 0); /* 기능도 같은 주기에 0을 요구한다 */
}

/* TC-105: SWR-04 켠 직후에는 검사를 3주기 통과하기 전까지 토크를 내지 않는다 */
static void tc_105(void)
{
    static const driver_point_t driver[] = {
        { 0u, 0.5, false, GEAR_D },
    };
    scenario_t sc = { "startup", 500u, driver, 1, NULL, 0, NULL };
    int n = scenario_run(&sc, log_buf, LOG_CAP);

    CHECK(n == 500);
    for (int t = 0; t < 20; t++) {
        CHECK_EQ(log_buf[t].torque_out, 0);
    }
    CHECK(log_buf[30].torque_out > 0);
}

/* TC-108: SWR-12 켤 때 구동 허용 신호는 끊겨 있고, 입력 검사를 3주기 통과한 뒤에 허용한다 */
static void tc_108(void)
{
    static const driver_point_t driver[] = {
        { 0u, 0.0, false, GEAR_D },
    };
    scenario_t sc = { "startup-enable", 100u, driver, 1, NULL, 0, NULL };
    plant_t plant;
    vcu_t vcu;
    int n;

    /* 시뮬레이션의 HAL은 켠 직후의 출력을 "허용"으로 둔다. 초기화가 그것을 끊어야 한다 */
    plant_init(&plant);
    hal_sim_init(&plant);
    CHECK(hal_sim_enable());
    vcu_init(&vcu);
    CHECK(!hal_sim_enable());

    n = scenario_run(&sc, log_buf, LOG_CAP);
    CHECK(n == 100);
    for (int t = 0; t < 20; t++) {
        CHECK(!log_buf[t].enable);
    }
    CHECK(log_buf[20].enable);
    CHECK(log_buf[99].enable);
}

/* TC-106: SWR-07 후진 기어에서는 음수 토크만 나간다 */
static void tc_106(void)
{
    static const driver_point_t driver[] = {
        { 0u, 0.0, false, GEAR_R },
        { T_PEDAL_ON, 0.3, false, GEAR_R },
    };
    scenario_t sc = { "reverse", 3000u, driver, 2, NULL, 0, NULL };
    int n = scenario_run(&sc, log_buf, LOG_CAP);
    int positive = 0;

    for (int i = 0; i < n; i++) {
        if (log_buf[i].torque_out > 0) {
            positive++;
        }
    }
    CHECK_EQ(positive, 0);
    CHECK_EQ(log_buf[n - 1].torque_out, -300); /* 페달 30%, 후진은 40%: -30 Nm */
    CHECK_EQ(log_buf[n - 1].diag.torque_allowed, 300 + 50);
    CHECK(log_buf[n - 1].speed_mps < -0.5);
    CHECK_EQ(log_buf[n - 1].diag.clamp_count, 0);
}

/* TC-107: SWR-05 기어가 P, N이거나 알 수 없는 값이면 토크를 내지 않는다 */
static void tc_107(void)
{
    static const driver_point_t driver[] = {
        { 0u, 0.5, false, GEAR_P },
        { 500u, 0.5, false, GEAR_N },
        { 1000u, 0.5, false, (gear_t)9 },
    };
    scenario_t sc = { "gear", 1500u, driver, 3, NULL, 0, NULL };
    int n = scenario_run(&sc, log_buf, LOG_CAP);
    int nonzero = 0;

    for (int i = 0; i < n; i++) {
        if ((log_buf[i].torque_out != 0) || (log_buf[i].diag.torque_allowed != 0)) {
            nonzero++;
        }
    }
    CHECK_EQ(nonzero, 0);
    CHECK_EQ(log_buf[n - 1].diag.clamp_count, 0);
}

/* 페달 채널 1의 선이 80 ms마다 한 주기씩 끊긴다 (0 V) */
#define T_BLIP_START 1000u
static void blip_apps1(time_ms_t t_ms)
{
    if (t_ms >= T_BLIP_START) {
        if ((t_ms % 80u) == 70u) {
            hal_sim_set_fault(FAULT_APPS1_FIXED_MV, 0);
        }
        if ((t_ms % 80u) == 0u) {
            hal_sim_clear_faults();
        }
    }
}

static int is_pedal_fault(const sample_t *s) { return s->diag.pedal_fault; }

/*
 * TC-109: SWR-14, SWR-04, SWR-11 fault injection FI-08
 * 페달을 30% 밟고 가는데 채널 1의 선이 80 ms마다 한 주기씩 끊긴다. 기능은 정상이다.
 * 끊긴 주기마다 토크가 0으로 떨어졌다가 다시 오른다. 운전자에게는 차가 울컥거리는 것으로 보인다.
 * 이어지는 횟수로는 판정되지 않는다. 11번째로 끊긴 주기에 페달 고장으로 판정하고 경고한다.
 */
static void tc_109(void)
{
    static const driver_point_t driver[] = {
        { 0u, 0.0, false, GEAR_D },
        { T_PEDAL_ON, 0.3, false, GEAR_D },
    };
    scenario_t sc = { "fi-08", 3000u, driver, 2, NULL, 0, blip_apps1 };
    int n = scenario_run(&sc, log_buf, LOG_CAP);
    int t_fault = first_time(log_buf, n, 0u, is_pedal_fault);
    const int t_first_blip = 1030;
    int dips = 0;
    int bad_before = 0;
    int bad_after = 0;

    /* 처음 끊긴 때는 1030 ms다. 11번째는 800 ms 뒤다 */
    CHECK_EQ(t_fault, t_first_blip + 800);
    for (int i = 1; i < n; i++) {
        const sample_t *s = &log_buf[i];
        if ((int)s->t_ms < t_fault) {
            /* 판정 전: 토크는 실제 페달 위치의 허용 토크를 넘지 않고, 경고와 고정이 없다 */
            if ((s->torque_out > (750 + 50)) || (s->warning != 0u) || s->diag.latched) {
                bad_before++;
            }
            if ((s->t_ms >= T_BLIP_START) && (s->torque_out == 0) && (log_buf[i - 1].torque_out != 0)) {
                dips++;
            }
        } else {
            /* 판정한 뒤: 토크 0과 경고가 유지된다. 기능의 고장이 아니므로 구동 허용 신호는 끊지 않는다 */
            if ((s->torque_out != 0) || (s->warning != 2u) || s->diag.latched || !s->enable) {
                bad_after++;
            }
        }
    }
    CHECK_EQ(bad_before, 0);
    CHECK_EQ(bad_after, 0);
    CHECK_EQ(dips, 10); /* 판정하기 전에 10번 떨어졌다. 11번째에 판정한다 */
    CHECK_EQ(log_buf[n - 1].diag.clamp_count, 0);
    (void)scenario_write_csv("build/out/fi-08.csv", log_buf, n);
    printf("  측정 FI-08: 처음 끊긴 때부터 페달 고장의 판정까지 %d ms\n", t_fault - t_first_blip);
}

static int is_brake_fault(const sample_t *s) { return s->diag.brake_fault; }

/*
 * TC-110: SWR-15, SWR-25 fault injection FI-10
 * 브레이크 접점 1이 "놓음"에 고착되어 있다 (접점이 붙었다). 접점이 하나뿐이면 제동 우선이 듣지 않는 고장이다.
 * 운전자가 가속 페달을 밟은 채 브레이크를 밟는다. 접점 2가 밟음을 알리므로 토크는 그 주기에 0이 된다.
 * 두 접점이 어긋난 채 200 ms가 지나면 브레이크 신호의 고장으로 판정하고 경고한다.
 * 이 고장은 브레이크를 밟기 전까지는 드러나지 않는다 (숨은 고장).
 */
static void tc_110(void)
{
    static const driver_point_t driver[] = {
        { 0u, 0.0, false, GEAR_D },
        { T_PEDAL_ON, 0.3, false, GEAR_D },
        { 2000u, 0.3, true, GEAR_D },
    };
    fault_event_t fault = { 1000u, FAULT_BRAKE1_STUCK, 0 };
    scenario_t sc = { "fi-10", 3000u, driver, 3, &fault, 1, NULL };
    int n = scenario_run(&sc, log_buf, LOG_CAP);
    int t_fault = first_time(log_buf, n, 0u, is_brake_fault);
    int bad = 0;

    /* 고착된 뒤에도 브레이크를 밟기 전까지는 아무것도 달라지지 않는다 */
    CHECK_EQ(log_buf[1999].torque_out, 750);
    CHECK_EQ(log_buf[1999].warning, 0);
    CHECK(!log_buf[1999].diag.brake_fault);
    /* 밟은 주기에 토크가 0이 된다 */
    CHECK_EQ(log_buf[2000].torque_out, 0);
    CHECK(log_buf[2000].diag.brake);
    /* 20번째로 어긋난 주기 (190 ms 뒤)에 고장으로 판정한다 */
    CHECK_EQ(t_fault, 2190);
    for (int i = 2000; i < n; i++) {
        const sample_t *s = &log_buf[i];
        uint8_t want_warning = ((int)s->t_ms >= t_fault) ? 2u : 0u;
        /* 토크는 나가지 않는다. 구동 허용 신호는 끊지 않는다 (VCU의 계산은 믿을 수 있다) */
        if ((s->torque_out != 0) || !s->enable || (s->warning != want_warning) || s->diag.latched) {
            bad++;
        }
    }
    CHECK_EQ(bad, 0);
    (void)scenario_write_csv("build/out/fi-10.csv", log_buf, n);
}

/*
 * TC-111: SWR-15, SWR-25 fault injection FI-11
 * 달리는 중에 브레이크 접점 1의 선이 끊긴다. 접점 1은 "밟음"으로 읽힌다.
 * 운전자는 브레이크를 밟지 않았는데 토크가 그 주기에 0이 된다 (구동력을 잃는다. SG-02 쪽의 대가).
 * 200 ms 동안은 경고가 없다. 그 뒤에 고장으로 판정하고 경고한다.
 */
static void tc_111(void)
{
    static const driver_point_t driver[] = {
        { 0u, 0.0, false, GEAR_D },
        { T_PEDAL_ON, 0.3, false, GEAR_D },
    };
    fault_event_t fault = { T_FAULT, FAULT_BRAKE1_STUCK, 1 };
    scenario_t sc = { "fi-11", 3000u, driver, 2, &fault, 1, NULL };
    int n = scenario_run(&sc, log_buf, LOG_CAP);
    int t_fault = first_time(log_buf, n, 0u, is_brake_fault);
    int bad = 0;

    CHECK_EQ(log_buf[T_FAULT - 1u].torque_out, 750);
    CHECK_EQ(log_buf[T_FAULT].torque_out, 0);
    CHECK_EQ(t_fault, (int)T_FAULT + 190);
    for (int i = (int)T_FAULT; i < n; i++) {
        const sample_t *s = &log_buf[i];
        uint8_t want_warning = ((int)s->t_ms >= t_fault) ? 2u : 0u;
        if ((s->torque_out != 0) || !s->enable || (s->warning != want_warning)) {
            bad++;
        }
    }
    CHECK_EQ(bad, 0);
    /* 운전자는 브레이크를 밟지 않았다. 차는 타력으로 간다 */
    CHECK(log_buf[n - 1].speed_mps > 1.0);
    printf("  측정 FI-11: 구동력을 잃은 때부터 경고까지 %d ms\n", t_fault - (int)T_FAULT);
}

/* 고장이 없는 실행과 견준 가속의 차이. 가장 큰 값을 돌려주고, 1.0 m/s^2를 넘은 시간을 over_ms에 적는다 */
static double accel_excess(const sample_t *log, const sample_t *ref, int n, int *over_ms)
{
    double max_excess = 0.0;

    *over_ms = 0;
    for (int i = 0; i < n; i++) {
        double excess = log[i].accel_mps2 - ref[i].accel_mps2;
        if (excess > max_excess) {
            max_excess = excess;
        }
        if (excess > 1.0) {
            (*over_ms)++;
        }
    }
    return max_excess;
}

/* 모터의 토크가 limit_nm 아래로 처음 내려가는 시각. 없으면 -1 */
static int first_motor_below(const sample_t *log, int n, time_ms_t from_ms, double limit_nm)
{
    for (int i = 0; i < n; i++) {
        if ((log[i].t_ms >= from_ms) && (log[i].torque_act_nm < limit_nm)) {
            return (int)log[i].t_ms;
        }
    }
    return -1;
}

/* 모터의 토크가 3.75 Nm (75 Nm의 5%) 아래로 처음 내려가는 시각. 없으면 -1 */
static int first_motor_off(const sample_t *log, int n, time_ms_t from_ms)
{
    return first_motor_below(log, n, from_ms, 3.75);
}

static void inverter_does_not_check(time_ms_t t_ms)
{
    if (t_ms == 0u) {
        hal_sim_inverter_check(false);
    }
}

/*
 * TC-112: SWR-17 fault injection FI-13
 * 토크 요구 메시지의 값이 전송 중에 100 Nm 커진다. VCU가 붙인 CRC가 값과 맞지 않으므로 inverter가 버린다.
 * 옳은 메시지가 50 ms 오지 않아 inverter는 토크를 내지 않는다 (가정 A-21).
 * VCU는 자기가 보낸 것이 바뀐 줄 모른다. 그래서 경고를 요청하지 않는다 (남은 것. docs/safety-case.md 3절의 H3.7).
 */
static void tc_112(void)
{
    static const driver_point_t driver[] = {
        { 0u, 0.0, false, GEAR_D },
        { T_PEDAL_ON, 0.3, false, GEAR_D },
    };
    fault_event_t fault = { T_FAULT, FAULT_TORQUE_MSG_CORRUPT, 1000 };
    scenario_t sc_ref = { "fi-13-ref", 3000u, driver, 2, NULL, 0, NULL };
    scenario_t sc = { "fi-13", 3000u, driver, 2, &fault, 1, NULL };
    int n_ref = scenario_run(&sc_ref, log_ref, LOG_CAP);
    int n = scenario_run(&sc, log_buf, LOG_CAP);
    int over_ms = 0;
    double max_excess = accel_excess(log_buf, log_ref, n, &over_ms);
    int t_off = first_motor_off(log_buf, n, T_FAULT);
    int vcu_changed = 0;

    CHECK_EQ(n, n_ref);
    /* 차량 수준: 바뀐 값은 한 번도 쓰이지 않는다. 가속이 고장 없는 실행보다 커지지 않는다 */
    CHECK(max_excess < 0.01);
    CHECK_EQ(over_ms, 0);
    /* 마지막 옳은 메시지에서 50 ms 뒤에 토크를 내리기 시작한다. 시정수 20 ms로 5% 아래까지 60 ms */
    CHECK(t_off >= 0);
    CHECK((t_off - (int)T_FAULT) <= 110);
    CHECK(log_buf[n - 1].torque_act_nm < 0.01);
    /* VCU 쪽에서는 아무것도 달라지지 않는다 */
    for (int i = (int)T_FAULT; i < n; i++) {
        const sample_t *s = &log_buf[i];
        if ((s->torque_out != 750) || !s->enable || (s->warning != 0u)) {
            vcu_changed++;
        }
    }
    CHECK_EQ(vcu_changed, 0);
    printf("  측정 FI-13: fault부터 모터의 토크가 5%% 아래로 내려갈 때까지 %d ms, 가속의 차이는 가장 클 때 %.2f m/s^2\n",
           t_off - (int)T_FAULT, max_excess);
    (void)scenario_write_csv("build/out/fi-13.csv", log_buf, n);
}

/*
 * TC-113: SWR-17 fault injection FI-14
 * 운전자가 페달을 놓기 직전부터 지난 토크 요구 메시지 (75 Nm)가 되풀이되고 새 메시지는 닿지 않는다.
 * 메시지의 CRC는 맞다. counter가 그대로이므로 inverter가 되풀이로 알아채고 버린다.
 * 50 ms 동안은 지난 토크가 유지된다. 그 시간이 SG-01의 200 ms 안에 있다.
 */
static void tc_113(void)
{
    static const driver_point_t driver[] = {
        { 0u, 0.0, false, GEAR_D },
        { T_PEDAL_ON, 0.3, false, GEAR_D },
        { T_FAULT, 0.0, false, GEAR_D },
    };
    fault_event_t fault = { T_FAULT - 5u, FAULT_TORQUE_MSG_REPEAT, 0 };
    scenario_t sc_ref = { "fi-14-ref", 3000u, driver, 3, NULL, 0, NULL };
    scenario_t sc = { "fi-14", 3000u, driver, 3, &fault, 1, NULL };
    int n_ref = scenario_run(&sc_ref, log_ref, LOG_CAP);
    int n = scenario_run(&sc, log_buf, LOG_CAP);
    int over_ms = 0;
    double max_excess = accel_excess(log_buf, log_ref, n, &over_ms);
    int t_off = first_motor_off(log_buf, n, T_FAULT);

    CHECK_EQ(n, n_ref);
    /* VCU는 페달을 놓은 주기에 0을 보낸다 */
    CHECK_EQ(log_buf[T_FAULT].torque_out, 0);
    /* 차량 수준: 지난 토크가 남는 시간이 SG-01의 시간 (200 ms) 안에 있다 */
    CHECK(over_ms <= 200);
    CHECK(t_off >= 0);
    CHECK((t_off - (int)T_FAULT) <= 110);
    CHECK(log_buf[n - 1].torque_act_nm < 0.01);
    /* 고장이 정말 들어갔는가: 지난 토크가 남아 있는 동안 가속이 고장 없는 실행보다 크고,
     * 모터의 토크가 내려가는 것이 inverter의 timeout (50 ms)만큼 늦다. fault를 빼면 이 둘이 실패한다 */
    CHECK(over_ms >= 10);
    CHECK((t_off - first_motor_off(log_ref, n_ref, T_FAULT)) >= 30);
    {
        /* VCU의 검사 (SWR-19)도 이 고장을 본다. inverter가 스스로 토크를 내리는 것이 더 빨라서,
         * 범위를 벗어난 주기가 3번 이어지기 전에 범위 안으로 돌아온다.
         * 끊어도 되는 경우이므로 끊었는지는 판정하지 않고 재기만 한다 */
        int worst = 0;
        for (int i = 0; i < n; i++) {
            if ((int)log_buf[i].diag.inverter_out_cycles > worst) {
                worst = (int)log_buf[i].diag.inverter_out_cycles;
            }
        }
        printf("  측정 FI-14: VCU의 검사가 범위를 벗어났다고 센 주기는 이어서 %d번, 구동 허용 차단 %s\n", worst,
               log_buf[n - 1].diag.latched ? "함" : "안 함");
    }
    printf("  측정 FI-14: 페달을 놓은 때부터 모터의 토크가 5%% 아래로 내려갈 때까지 %d ms (고장이 없으면 %d ms), "
           "가속의 차이는 가장 클 때 %.2f m/s^2, 1.0 m/s^2를 넘은 시간 %d ms\n",
           t_off - (int)T_FAULT, first_motor_off(log_ref, n_ref, T_FAULT) - (int)T_FAULT, max_excess, over_ms);
    (void)scenario_write_csv("build/out/fi-14.csv", log_buf, n);
}

/* TC-114가 쓰는 시간표: 차량 속도 메시지의 고장을 차례로 넣고 지운다 */
static void speed_message_faults(time_ms_t t_ms)
{
    if (t_ms == 1000u) {
        hal_sim_set_fault(FAULT_SPEED_MSG_CORRUPT, 100); /* 값이 1 m/s 커진다 */
    } else if (t_ms == 2000u) {
        hal_sim_set_fault(FAULT_SPEED_MSG_REPEAT, 0);
    } else if (t_ms == 3000u) {
        hal_sim_set_fault(FAULT_SPEED_MSG_LOSS, 0);
    } else if ((t_ms == 1200u) || (t_ms == 2200u) || (t_ms == 3200u)) {
        hal_sim_clear_faults();
    } else if (t_ms == 4000u) {
        hal_sim_set_fault(FAULT_SPEED_MSG_FREEZE, 0);
    } else {
        /* 그대로 둔다 */
    }
}

/* TC-114의 기댓값: 그 시각에 차량 속도가 유효한가 */
static bool speed_should_be_valid(time_ms_t t_ms)
{
    /* 값이 바뀐 동안 무효다. 그친 뒤의 첫 메시지 (1200 ms)는 counter가 지난 옳은 메시지에서
     * 5 앞서 있어 버리고 (그 사이의 20개는 CRC가 틀려 기준이 되지 못했다), 둘째부터 받아들인다 */
    if ((t_ms >= 1000u) && (t_ms < 1210u)) {
        return false;
    }
    /* 되풀이되는 동안 무효다. 그치면 counter가 1 앞선 메시지가 와서 바로 유효하다 */
    if ((t_ms >= 2000u) && (t_ms < 2200u)) {
        return false;
    }
    /* 끊기면 마지막 메시지 (2990 ms)에서 50 ms까지는 유효하고, 그다음 주기 (3050 ms)부터 무효다 */
    if ((t_ms >= 3050u) && (t_ms < 3200u)) {
        return false;
    }
    return true;
}

/*
 * TC-114: SWR-18 fault injection FI-15
 * 차량 속도 메시지의 값이 전송 중에 바뀌고, 같은 메시지가 되풀이되고, 메시지가 끊긴다.
 * 무효인 동안 VCU는 마지막 값을 쓰지 않는다 (0으로 둔다).
 * 마지막은 알려진 한계다: 보내는 쪽이 얼어붙은 값을 새 counter와 옳은 CRC로 보내면 이 검사는 알지 못한다.
 */
static void tc_114(void)
{
    static const driver_point_t driver[] = {
        { 0u, 0.0, false, GEAR_D },
        { T_PEDAL_ON, 0.3, false, GEAR_D },
    };
    scenario_t sc = { "fi-15", 5000u, driver, 2, NULL, 0, speed_message_faults };
    int n = scenario_run(&sc, log_buf, LOG_CAP);
    int wrong_validity = 0;
    int used_invalid = 0;
    int wrong_value = 0;

    for (int i = 10; i < n; i++) {
        const sample_t *s = &log_buf[i];
        /* VCU가 그 주기에 읽은 메시지는 주기의 처음 (10 ms의 배수)에 만들어졌다 */
        int t_msg = (i / 10) * 10;
        if (s->diag.speed_valid != speed_should_be_valid((time_ms_t)t_msg)) {
            wrong_validity++;
        }
        if (!s->diag.speed_valid && (s->diag.speed != 0)) {
            used_invalid++;
        }
        /* 유효한 동안의 값은 그 메시지를 만들 때의 차량 속도다 (0.01 m/s).
         * 끊긴 뒤의 50 ms와 얼어붙은 뒤는 따로 본다 */
        if (s->diag.speed_valid && ((t_msg < 3000) || ((t_msg >= 3200) && (t_msg < 4000)))
            && (s->diag.speed != (speed_t)(log_buf[t_msg - 1].speed_mps * 100.0))) {
            wrong_value++;
        }
    }
    CHECK_EQ(wrong_validity, 0);
    CHECK_EQ(used_invalid, 0);
    CHECK_EQ(wrong_value, 0);
    /* 끊긴 뒤 50 ms까지는 마지막 메시지 (2990 ms)의 값을 쓴다 */
    CHECK_EQ(log_buf[3045].diag.speed, (speed_t)(log_buf[2989].speed_mps * 100.0));
    /* 알려진 한계: 얼어붙은 값은 유효로 남는다. 차는 그 사이에 더 빨라졌다 */
    CHECK(log_buf[n - 1].diag.speed_valid);
    CHECK_EQ(log_buf[n - 1].diag.speed, log_buf[3995].diag.speed);
    CHECK(log_buf[n - 1].speed_mps > (log_buf[3995].speed_mps + 1.0));
    /* 이 묶음에서는 속도를 쓰는 곳이 아직 없다. 토크와 경고는 달라지지 않는다 */
    CHECK_EQ(log_buf[n - 1].torque_out, 750);
    CHECK_EQ(log_buf[n - 1].warning, 0);
}

/*
 * TC-115: SWR-18, SWR-19 fault injection FI-16
 * inverter의 상태 메시지가 끊긴다. 최근 5주기 가운데 새 메시지를 받은 주기가 3번보다 적어지는 주기
 * (셋째로 빈 주기)에 구동 허용 신호를 끊는다. inverter가 요구대로 내는지 확인할 수 없기 때문이다.
 * 받는 쪽의 검사는 마지막 메시지에서 50 ms가 지난 다음 주기부터 상태를 무효로 알린다 (끊은 뒤다).
 */
static void tc_115(void)
{
    static const driver_point_t driver[] = {
        { 0u, 0.0, false, GEAR_D },
        { T_PEDAL_ON, 0.3, false, GEAR_D },
    };
    fault_event_t fault = { T_FAULT, FAULT_INVERTER_MSG_LOSS, 0 };
    scenario_t sc = { "fi-16", 3000u, driver, 2, &fault, 1, NULL };
    int n = scenario_run(&sc, log_buf, LOG_CAP);
    int wrong = 0;
    int bad = 0;
    /* 새 메시지가 없는 주기: 2000, 2010, 2020 ms. 셋째에 끊는다 */
    const int t_cut = (int)T_FAULT + 20;

    for (int i = 10; i < n; i++) {
        const sample_t *s = &log_buf[i];
        bool want = (i < ((int)T_FAULT + 50));
        if (s->diag.inverter_valid != want) {
            wrong++;
        }
        if (i < t_cut) {
            /* 끊기 전에는 아무것도 달라지지 않는다 */
            if ((s->torque_out != ((i >= 300) ? 750 : s->torque_out)) || s->diag.latched || (s->warning != 0u)) {
                bad++;
            }
        } else if ((s->torque_out != 0) || s->enable || (s->warning != 2u) || !s->diag.latched) {
            bad++;
        } else {
            /* 끊은 뒤: 토크 0, 구동 허용 신호 차단, 경고 */
        }
    }
    CHECK_EQ(wrong, 0);
    CHECK_EQ(bad, 0);
    printf("  측정 FI-16: 메시지가 끊긴 때부터 구동 허용 차단까지 %d ms\n", t_cut - (int)T_FAULT);

    /* 메시지는 주기마다 닿는데 값이 전송 중에 바뀐다. 받는 쪽의 검사가 버리므로 (CRC가 맞지 않는다)
     * 검사를 통과한 새 메시지가 없다. 끊긴 것과 같이 셋째 주기에 끊는다. 바뀐 값은 한 번도 쓰지 않는다 */
    {
        fault_event_t corrupt = { T_FAULT, FAULT_INVERTER_MSG_CORRUPT, 5000 };
        scenario_t sc2 = { "fi-16-corrupt", 3000u, driver, 2, &corrupt, 1, NULL };
        int t_cut2;

        n = scenario_run(&sc2, log_buf, LOG_CAP);
        t_cut2 = first_time(log_buf, n, 0u, is_latched);
        CHECK_EQ(t_cut2, (int)T_FAULT + 20);
        CHECK_EQ(bad_after_cut(log_buf, n, t_cut2), 0);
        CHECK(!log_buf[T_FAULT + 5u].diag.inverter_valid);
        /* 메시지는 계속 닿았다 (잃은 것이 아니다) */
        CHECK_EQ((int)log_buf[n - 1].inverter_msgs, 300);
        /* 범위를 벗어난 횟수는 오르지 않았다: 바뀐 값 (500 Nm 큼)을 견주지 않았다 */
        CHECK_EQ(log_buf[n - 1].diag.inverter_out_cycles, 0);
        printf("  측정 FI-16 (값이 바뀜): 구동 허용 차단까지 %d ms\n", t_cut2 - (int)T_FAULT);
    }
}

static int is_gear_r(const sample_t *s) { return s->diag.gear == GEAR_R; }

/*
 * TC-116: SWR-16 fault injection FI-17
 * 가속 페달을 끝까지 밟고 달리는 중에 기어가 R로 바뀐다 (신호의 고장이든 운전자가 고른 것이든 VCU는 가릴 수 없다).
 * 받아들이지 않고 N으로 둔다. 토크는 0이고 차는 타력으로 간다. 500 ms 이어지면 주의를 요청한다.
 * D로 돌아오면 바로 받아들인다. 그 뒤에 브레이크를 밟고 R을 고르면, 속도가 5 km/h 아래로 내려간 뒤에 받아들인다.
 */
static void tc_116(void)
{
    /* 기준: 같은 때 (3000 ms)에 가속 페달을 놓고 타력으로 간다 */
    static const driver_point_t coast[] = {
        { 0u, 0.0, false, GEAR_D },
        { T_PEDAL_ON, 1.0, false, GEAR_D },
        { 3000u, 0.0, false, GEAR_D },
    };
    static const driver_point_t driver[] = {
        { 0u, 0.0, false, GEAR_D },
        { T_PEDAL_ON, 1.0, false, GEAR_D },
        { 3000u, 1.0, false, GEAR_R },
        { 4000u, 1.0, false, GEAR_D },
        { 5000u, 0.0, true, GEAR_R },
    };
    scenario_t sc_ref = { "fi-17-ref", 4000u, coast, 3, NULL, 0, NULL };
    scenario_t sc = { "fi-17", 8000u, driver, 5, NULL, 0, NULL };
    int n_ref = scenario_run(&sc_ref, log_ref, LOG_CAP);
    int n = scenario_run(&sc, log_buf, LOG_CAP);
    int bad = 0;
    int over_ms = 0;
    double max_decel = 0.0;
    int t_r;

    CHECK_EQ(n_ref, 4000);
    CHECK(log_buf[2999].speed_mps > 5.0); /* 18 km/h 넘게 달리고 있다 */
    CHECK_EQ(log_buf[2999].diag.gear, GEAR_D);
    for (int i = 3000; i < 4000; i++) {
        const sample_t *s = &log_buf[i];
        /* 500 ms (50번째로 받아들이지 못한 주기) 뒤에 주의 */
        uint8_t want_warning = (i >= 3490) ? 1u : 0u;
        /* 타력 주행보다 얼마나 더 감속하는가 (SG-02의 첫째 구절) */
        double decel = log_ref[i].accel_mps2 - s->accel_mps2;
        if (decel > max_decel) {
            max_decel = decel;
        }
        if (decel > 1.0) {
            over_ms++;
        }
        /* 받아들인 기어는 N, 토크와 허용 토크는 0. 고장이 아니므로 고정도 차단도 없다 */
        if ((s->diag.gear != GEAR_N) || (s->torque_out != 0) || (s->diag.torque_allowed != 0)
            || (s->warning != want_warning) || s->diag.latched || !s->enable) {
            bad++;
        }
    }
    CHECK_EQ(bad, 0);
    CHECK(max_decel < 0.05);
    CHECK_EQ(over_ms, 0);
    /* D로 돌아온 주기에 받아들이고 주의를 거둔다. 토크가 다시 오른다 */
    CHECK_EQ(log_buf[4000].diag.gear, GEAR_D);
    CHECK_EQ(log_buf[4000].warning, 0);
    CHECK_EQ(log_buf[4000].torque_out, 250);
    CHECK_EQ(log_buf[4990].torque_out, 2500);
    CHECK_EQ(log_buf[4990].diag.clamp_count, 0);
    /* 브레이크를 밟고 R을 고른다. 속도가 5 km/h (1.389 m/s) 아래로 내려간 뒤에야 받아들인다 */
    t_r = first_time(log_buf, n, 5000u, is_gear_r);
    CHECK(t_r > 5000);
    if (t_r > 5000) {
        CHECK(log_buf[t_r - 1].speed_mps < 1.39);
        CHECK(log_buf[t_r - 11].speed_mps >= 1.38);
        for (int i = 5000; i < t_r; i++) {
            if (log_buf[i].diag.gear != GEAR_N) {
                bad++;
            }
        }
        CHECK_EQ(bad, 0);
    }
    /* 처음부터 끝까지 반대 방향의 토크는 한 번도 나가지 않았다 (브레이크를 밟고 있다) */
    for (int i = 0; i < n; i++) {
        if (log_buf[i].torque_out < 0) {
            bad++;
        }
    }
    CHECK_EQ(bad, 0);
    printf("  측정 FI-17: 타력 주행과 견준 감속은 가장 클 때 %.2f m/s^2, R을 받아들인 때의 속도 %.2f m/s\n",
           max_decel, (t_r > 0) ? log_buf[t_r - 1].speed_mps : -1.0);
    (void)scenario_write_csv("build/out/fi-17.csv", log_buf, n);
}

/* TC-117이 쓰는 시간표: 서 있는 동안 차량 속도 메시지가 끊겼다가 돌아온다 */
static void speed_loss_at_standstill(time_ms_t t_ms)
{
    if (t_ms == 500u) {
        hal_sim_set_fault(FAULT_SPEED_MSG_LOSS, 0);
    } else if (t_ms == 2000u) {
        hal_sim_clear_faults();
    } else {
        /* 그대로 둔다 */
    }
}

/*
 * TC-117: SWR-16 fault injection FI-18
 * 서 있는 차에서 R을 고르는데 차량 속도 메시지가 끊겨 있다. 속도가 무효이므로 받아들이지 못한다.
 * 차는 출발하지 못하고 (구동력이 없다), 500 ms 뒤에 주의를 요청한다. 메시지가 돌아오면 받아들이고 주의를 거둔다.
 * 무효인 동안 VCU가 쓰는 속도 값은 0이다. 0은 "낮은 속도"로 읽히는 값이므로, 유효한지를 따로 보지 않으면
 * 이 경우에 방향을 받아들이게 된다.
 */
static void tc_117(void)
{
    static const driver_point_t driver[] = {
        { 0u, 0.0, false, GEAR_D },
        { 1000u, 0.3, false, GEAR_R },
    };
    scenario_t sc = { "fi-18", 3000u, driver, 2, NULL, 0, speed_loss_at_standstill };
    int n = scenario_run(&sc, log_buf, LOG_CAP);
    int bad = 0;

    CHECK_EQ(log_buf[999].diag.gear, GEAR_D);
    CHECK(!log_buf[999].diag.speed_valid);
    for (int i = 1000; i < 2000; i++) {
        const sample_t *s = &log_buf[i];
        uint8_t want_warning = (i >= 1490) ? 1u : 0u;
        if ((s->diag.gear != GEAR_N) || (s->torque_out != 0) || (s->warning != want_warning)
            || s->diag.latched || !s->enable) {
            bad++;
        }
    }
    CHECK_EQ(bad, 0);
    CHECK_EQ(log_buf[2000].diag.gear, GEAR_R);
    CHECK_EQ(log_buf[2000].warning, 0);
    CHECK_EQ(log_buf[n - 1].torque_out, -300);
    CHECK(log_buf[n - 1].speed_mps < -0.2);
}

/*
 * TC-118: SWR-16 fault injection FI-19 (알려진 한계)
 * 차량 속도의 값이 0에 얼어붙은 채 메시지는 계속 온다 (보내는 쪽의 고장). 달리는 중에 기어가 R로 바뀐다.
 * VCU가 아는 속도는 0이므로 받아들인다. 반대 방향의 토크가 나가고 SG-02의 첫째 구절을 어긴다.
 * 방향의 판정이 속도를 쓰면서 새로 생긴 길이다 (docs/safety-case.md 3절의 H2.2).
 */
static void tc_118(void)
{
    static const driver_point_t coast[] = {
        { 0u, 0.0, false, GEAR_D },
        { T_PEDAL_ON, 1.0, false, GEAR_D },
        { 3000u, 0.0, false, GEAR_D },
    };
    static const driver_point_t driver[] = {
        { 0u, 0.0, false, GEAR_D },
        { T_PEDAL_ON, 1.0, false, GEAR_D },
        { 3000u, 1.0, false, GEAR_R },
    };
    fault_event_t fault = { 100u, FAULT_SPEED_MSG_FREEZE, 0 };
    scenario_t sc_ref = { "fi-19-ref", 4000u, coast, 3, &fault, 1, NULL };
    scenario_t sc = { "fi-19", 4000u, driver, 3, &fault, 1, NULL };
    int n_ref = scenario_run(&sc_ref, log_ref, LOG_CAP);
    int n = scenario_run(&sc, log_buf, LOG_CAP);
    int over_ms = 0;
    double max_decel = 0.0;

    CHECK_EQ(n, n_ref);
    for (int i = 3000; i < n; i++) {
        double decel = log_ref[i].accel_mps2 - log_buf[i].accel_mps2;
        if (decel > max_decel) {
            max_decel = decel;
        }
        if (decel > 1.0) {
            over_ms++;
        }
    }
    CHECK(log_buf[2999].speed_mps > 5.0);
    CHECK(log_buf[2999].diag.speed_valid);
    CHECK_EQ(log_buf[2999].diag.speed, 0);
    /* 알아채지 못한다: R을 그 주기에 받아들이고, 경고도 없다 */
    CHECK_EQ(log_buf[3000].diag.gear, GEAR_R);
    CHECK(log_buf[n - 1].torque_out < 0);
    CHECK_EQ(log_buf[n - 1].warning, 0);
    CHECK(max_decel > 1.0);
    CHECK(over_ms > 200);
    printf("  측정 FI-19 (알려진 한계): 타력 주행과 견준 감속은 가장 클 때 %.2f m/s^2, 1.0 m/s^2를 넘은 시간 %d ms\n",
           max_decel, over_ms);
}

/*
 * TC-119: SWR-16, SWR-11 주의와 경고가 겹치면 경고가 나간다
 * 방향의 바뀜을 받아들이지 못해 주의가 나가 있는 중에 페달 채널 1이 범위 안의 다른 값에 고착된다.
 */
static void tc_119(void)
{
    static const driver_point_t driver[] = {
        { 0u, 0.0, false, GEAR_D },
        { T_PEDAL_ON, 1.0, false, GEAR_D },
        { 3000u, 1.0, false, GEAR_R },
    };
    fault_event_t fault = { 3700u, FAULT_APPS1_FIXED_MV, 2000 }; /* 범위 안의 값이다. 채널 2 (100%)와 어긋난다 */
    scenario_t sc = { "caution-and-warning", 4500u, driver, 3, &fault, 1, NULL };
    int n = scenario_run(&sc, log_buf, LOG_CAP);

    CHECK_EQ(log_buf[3600].warning, 1);
    CHECK(log_buf[n - 1].diag.pedal_fault);
    CHECK_EQ(log_buf[n - 1].warning, 2);
    CHECK_EQ(log_buf[n - 1].diag.gear, GEAR_N);
}



/*
 * TC-120: SWR-19 fault injection FI-20
 * FI-13, FI-14와 같은 전송 중의 고장인데, inverter가 메시지를 검사하지 않는다 (가정 A-21이 틀린 경우).
 * inverter는 바뀐 값이나 옛 값을 그대로 쓴다. inverter가 알린 토크가 VCU가 보낸 토크의 범위를 벗어나므로
 * VCU가 3주기 뒤에 구동 허용 신호를 끊는다. 가정 하나가 틀려도 다른 수단이 SG-01을 지킨다.
 */
static void tc_120(void)
{
    static const driver_point_t hold[] = {
        { 0u, 0.0, false, GEAR_D },
        { T_PEDAL_ON, 0.3, false, GEAR_D },
    };
    static const driver_point_t release[] = {
        { 0u, 0.0, false, GEAR_D },
        { T_PEDAL_ON, 0.3, false, GEAR_D },
        { T_FAULT, 0.0, false, GEAR_D },
    };
    fault_event_t corrupt = { T_FAULT, FAULT_TORQUE_MSG_CORRUPT, 1000 };
    fault_event_t repeat = { T_FAULT - 5u, FAULT_TORQUE_MSG_REPEAT, 0 };
    scenario_t sc_ref1 = { "fi-20-ref1", 3000u, hold, 2, NULL, 0, inverter_does_not_check };
    scenario_t sc1 = { "fi-20-corrupt", 3000u, hold, 2, &corrupt, 1, inverter_does_not_check };
    scenario_t sc_ref2 = { "fi-20-ref2", 3000u, release, 3, NULL, 0, inverter_does_not_check };
    scenario_t sc2 = { "fi-20-repeat", 3000u, release, 3, &repeat, 1, inverter_does_not_check };
    int over_ms = 0;
    double max_excess;
    int t_cut;
    int n;

    /* 값이 100 Nm 커진 채 inverter에 닿는다 */
    (void)scenario_run(&sc_ref1, log_ref, LOG_CAP);
    n = scenario_run(&sc1, log_buf, LOG_CAP);
    max_excess = accel_excess(log_buf, log_ref, n, &over_ms);
    t_cut = first_time(log_buf, n, 0u, is_latched);
    /* 3번째로 범위를 벗어난 주기 (30 ms 뒤)에 끊는다 */
    CHECK_EQ(t_cut, (int)T_FAULT + 30);
    CHECK_EQ(bad_after_cut(log_buf, n, t_cut), 0);
    CHECK(over_ms <= 200);
    CHECK(log_buf[n - 1].torque_act_nm < 0.01);
    printf("  측정 FI-20 (값이 바뀜, inverter가 검사하지 않음): 차단까지 %d ms, 가속의 차이는 가장 클 때 %.2f m/s^2, "
           "1.0 m/s^2를 넘은 시간 %d ms\n", t_cut - (int)T_FAULT, max_excess, over_ms);
    (void)scenario_write_csv("build/out/fi-20.csv", log_buf, n);

    /* 운전자가 페달을 놓았는데 옛 메시지 (75 Nm)가 되풀이된다.
     * 보낸 토크의 기록 (50 ms)에서 75 Nm가 빠진 뒤에야 범위를 벗어나므로, 판정은 50 ms 늦게 시작한다 */
    (void)scenario_run(&sc_ref2, log_ref, LOG_CAP);
    n = scenario_run(&sc2, log_buf, LOG_CAP);
    max_excess = accel_excess(log_buf, log_ref, n, &over_ms);
    t_cut = first_time(log_buf, n, 0u, is_latched);
    CHECK_EQ(t_cut, (int)T_FAULT + 70);
    CHECK_EQ(bad_after_cut(log_buf, n, t_cut), 0);
    CHECK(over_ms <= 200);
    CHECK(log_buf[n - 1].torque_act_nm < 0.01);
    /* 이 경우가 시간 예산표 (docs/technical-safety-concept.md 9.4절)의 M4 줄이다: 합 151 ms */
    CHECK((first_motor_off(log_buf, n, T_FAULT) - (int)T_FAULT) <= 151);
    printf("  측정 FI-20 (되풀이, inverter가 검사하지 않음): 차단까지 %d ms, 모터의 토크가 5%% 아래로 내려갈 때까지 %d ms, "
           "가속의 차이는 가장 클 때 %.2f m/s^2, 1.0 m/s^2를 넘은 시간 %d ms\n", t_cut - (int)T_FAULT,
           first_motor_off(log_buf, n, T_FAULT) - (int)T_FAULT, max_excess, over_ms);
}

/*
 * TC-121: SWR-19 fault injection FI-21
 * inverter가 요구보다 100 Nm 더 낸다 (inverter 안의 고장). 알리는 토크는 실제 토크다.
 * fault를 넣는 시각을 주기 안에서 0-9 ms로 바꿔 가며 본다.
 */
static void tc_121(void)
{
    static const driver_point_t driver[] = {
        { 0u, 0.0, false, GEAR_D },
        { T_PEDAL_ON, 0.3, false, GEAR_D },
    };
    scenario_t sc_ref = { "fi-21-ref", 3000u, driver, 2, NULL, 0, NULL };
    int n_ref = scenario_run(&sc_ref, log_ref, LOG_CAP);
    int worst_cut_ms = 0;
    int worst_over_ms = 0;
    int worst_off_ms = 0;
    double worst_excess = 0.0;

    for (time_ms_t phase = 0u; phase < 10u; phase++) {
        fault_event_t fault = { T_FAULT + phase, FAULT_INVERTER_TORQUE_OFFSET, 1000 };
        scenario_t sc = { "fi-21", 3000u, driver, 2, &fault, 1, NULL };
        int n = scenario_run(&sc, log_buf, LOG_CAP);
        int over_ms = 0;
        double max_excess = accel_excess(log_buf, log_ref, n, &over_ms);
        int t_cut = first_time(log_buf, n, 0u, is_latched);
        int t_off = first_motor_off(log_buf, n, fault.t_ms);

        CHECK_EQ(n, n_ref);
        CHECK(t_cut >= 0);
        CHECK(t_off >= 0);
        CHECK_EQ(bad_after_cut(log_buf, n, t_cut), 0);
        /* 끊기 전까지 VCU가 보낸 토크는 그대로다. 틀린 것은 inverter다 */
        CHECK_EQ(log_buf[t_cut - 1].torque_out, 750);
        if ((t_cut - (int)fault.t_ms) > worst_cut_ms) {
            worst_cut_ms = t_cut - (int)fault.t_ms;
        }
        if ((t_off - (int)fault.t_ms) > worst_off_ms) {
            worst_off_ms = t_off - (int)fault.t_ms;
        }
        if (over_ms > worst_over_ms) {
            worst_over_ms = over_ms;
        }
        if (max_excess > worst_excess) {
            worst_excess = max_excess;
        }
        if (phase == 5u) {
            (void)scenario_write_csv("build/out/fi-21.csv", log_buf, n);
        }
    }
    /* 시간 예산표 (docs/technical-safety-concept.md 9.4절)의 합 151 ms와 SG-01의 200 ms 안에 있다 */
    CHECK(worst_cut_ms <= 50);
    CHECK(worst_off_ms <= 151);
    CHECK(worst_over_ms <= 200);
    printf("  측정 FI-21: fault부터 차단까지 가장 나쁜 경우 %d ms, 모터의 토크가 5%% 아래로 내려갈 때까지 %d ms, "
           "가속의 차이는 가장 클 때 %.2f m/s^2, 1.0 m/s^2를 넘은 시간 %d ms\n",
           worst_cut_ms, worst_off_ms, worst_excess, worst_over_ms);
}

/* TC-122가 쓰는 시간표: inverter가 100 Nm 더 내면서, 알리는 값에서는 그만큼을 뺀다 */
static void hidden_inverter_fault(time_ms_t t_ms)
{
    if (t_ms == T_FAULT) {
        hal_sim_set_fault(FAULT_INVERTER_TORQUE_OFFSET, 1000);
        hal_sim_set_fault(FAULT_INVERTER_REPORT_OFFSET, -1000);
    }
}

/*
 * TC-122: SWR-19 fault injection FI-22 (알려진 한계)
 * inverter가 요구보다 100 Nm 더 내는데, 알리는 토크도 같은 원인으로 틀려서 요구한 값과 같게 보인다.
 * VCU는 알아채지 못하고 SG-01을 어긴다. 가정 A-23 (알리는 값은 토크 요구를 쓰는 길과 따로 구한다)이 틀린 경우다.
 */
static void tc_122(void)
{
    static const driver_point_t driver[] = {
        { 0u, 0.0, false, GEAR_D },
        { T_PEDAL_ON, 0.3, false, GEAR_D },
    };
    scenario_t sc_ref = { "fi-22-ref", 3000u, driver, 2, NULL, 0, NULL };
    scenario_t sc = { "fi-22", 3000u, driver, 2, NULL, 0, hidden_inverter_fault };
    int n_ref = scenario_run(&sc_ref, log_ref, LOG_CAP);
    int n = scenario_run(&sc, log_buf, LOG_CAP);
    int over_ms = 0;
    double max_excess = accel_excess(log_buf, log_ref, n, &over_ms);

    CHECK_EQ(n, n_ref);
    CHECK(!log_buf[n - 1].diag.latched);
    CHECK(log_buf[n - 1].enable);
    CHECK_EQ(log_buf[n - 1].warning, 0);
    CHECK(max_excess > 1.0);
    CHECK(over_ms > 200);
    printf("  측정 FI-22 (알려진 한계): 가속의 차이는 가장 클 때 %.2f m/s^2, 1.0 m/s^2를 넘은 시간 %d ms\n",
           max_excess, over_ms);
}

/* TC-123이 쓰는 것: 알리는 값의 오차와 묵은 정도 */
static int32_t report_offset;
static bool report_stale;
static double inverter_tau_ms = 20.0;

static void slow_inaccurate_report(time_ms_t t_ms)
{
    if (t_ms == 0u) {
        hal_sim_inverter_tau(inverter_tau_ms);
        if (report_offset != 0) {
            hal_sim_set_fault(FAULT_INVERTER_REPORT_OFFSET, report_offset);
        }
        if (report_stale) {
            hal_sim_set_fault(FAULT_INVERTER_REPORT_STALE, 0);
        }
    }
}

/*
 * TC-123: SWR-19 고장이 없으면 끊지 않는다 (SG-02 쪽)
 * 토크가 가장 크게 바뀌는 운전을 한다: 끝까지 밟았다 놓기, 끝까지 밟은 채 브레이크, 페달을 빠르게 밟았다 놓기,
 * 서서 D와 R을 오가기. inverter가 알리는 값이 가정 (A-23)의 끝에 있는 경우도 본다: 10 Nm 크거나 작고, 한 주기 묵었다.
 * 범위를 벗어난 주기가 이어진 가장 큰 횟수를 잰다. 3이면 끊는다.
 */
static void tc_123(void)
{
    static const driver_point_t driver[] = {
        { 0u, 0.0, false, GEAR_D },
        { 200u, 1.0, false, GEAR_D },   /* 끝까지 밟는다 */
        { 1500u, 0.0, false, GEAR_D },  /* 놓는다: 250 Nm에서 한 주기에 0 */
        { 2000u, 1.0, false, GEAR_D },
        { 3000u, 1.0, true, GEAR_D },   /* 밟은 채 브레이크 */
        { 3500u, 1.0, false, GEAR_D },
        { 3530u, 0.0, false, GEAR_D },  /* 30 ms마다 밟았다 놓는다 */
        { 3560u, 1.0, false, GEAR_D },
        { 3590u, 0.0, false, GEAR_D },
        { 3620u, 1.0, false, GEAR_D },
        { 3650u, 0.0, false, GEAR_D },
        { 3700u, 0.0, true, GEAR_D },   /* 세운다 */
        { 7000u, 1.0, false, GEAR_R },  /* 서서 R로, 끝까지 밟는다 */
        { 7300u, 0.0, true, GEAR_R },
        { 8000u, 1.0, false, GEAR_D },  /* 다시 D로 */
    };
    static const int32_t offsets[] = { 0, 100, -100 };
    /* 범위를 벗어난 주기가 이어진 가장 큰 횟수. 줄은 묵지 않음과 한 주기 묵음, 칸은 오차 0, +10, -10 Nm */
    static const int expected_worst[2][3] = { { 0, 1, 0 }, { 1, 2, 0 } };
    int worst_all = 0;

    for (int stale = 0; stale < 2; stale++) {
        for (int k = 0; k < 3; k++) {
            scenario_t sc = { "no-false-cut", 8500u, driver, 15, NULL, 0, slow_inaccurate_report };
            int worst = 0;
            int bad = 0;
            int n;

            report_offset = offsets[k];
            report_stale = (stale != 0);
            n = scenario_run(&sc, log_buf, LOG_CAP);
            for (int i = 0; i < n; i++) {
                const sample_t *s = &log_buf[i];
                if ((int)s->diag.inverter_out_cycles > worst) {
                    worst = (int)s->diag.inverter_out_cycles;
                }
                if (s->diag.latched || (s->warning != 0u) || ((s->t_ms >= 20u) && !s->enable)
                    || (s->diag.clamp_count != 0u)) {
                    bad++;
                }
            }
            CHECK_EQ(bad, 0);
            CHECK(worst < 3);
            CHECK_EQ(worst, expected_worst[stale][k]);
            /* 운전이 뜻한 대로 되었는지: 서 있다가 R을 받아들였고, 끝에는 D로 달린다 */
            CHECK_EQ(log_buf[7200].diag.gear, GEAR_R);
            CHECK_EQ(log_buf[n - 1].diag.gear, GEAR_D);
            printf("  측정 거짓 차단의 여유: 알리는 값의 오차 %+d Nm, %s: 범위를 벗어난 주기가 이어진 횟수는 가장 클 때 %d (3이면 끊는다)\n",
                   (int)(offsets[k] / 10), report_stale ? "한 주기 묵음" : "묵지 않음", worst);
            if (worst > worst_all) {
                worst_all = worst;
            }
        }
    }
    CHECK(worst_all < 3);

    /* 알려진 한계: 판정의 값은 inverter의 응답이 가정 (A-16: 시정수 20 ms)대로일 때에만 맞다.
     * 시정수가 25 ms이고 알리는 값이 10 Nm 크고 한 주기 묵으면, 고장이 없는데 250 Nm에서 0으로 내리는 한 번에 끊는다 */
    {
        scenario_t sc = { "false-cut", 8500u, driver, 15, NULL, 0, slow_inaccurate_report };
        int n;
        int t_cut;

        report_offset = 100;
        report_stale = true;
        inverter_tau_ms = 25.0;
        n = scenario_run(&sc, log_buf, LOG_CAP);
        t_cut = first_time(log_buf, n, 0u, is_latched);
        CHECK(t_cut > 1500);
        CHECK(t_cut < 1600);
        printf("  측정 거짓 차단 (알려진 한계): inverter의 시정수 25 ms, 오차 +10 Nm, 한 주기 묵음: 페달을 놓은 뒤 %d ms에 끊었다\n",
               t_cut - 1500);
    }
    report_offset = 0;
    report_stale = false;
    inverter_tau_ms = 20.0;
}

static int is_watchdog_tripped(const sample_t *s) { return s->watchdog_tripped; }

static int is_limp(const sample_t *s) { return s->warning == 1u; }

/*
 * TC-130: SWR-24 fault injection FI-30
 * 달리는 중에 페달 채널 1의 선이 끊긴다 (0 V). 채널 2는 범위 안이다.
 * 판정 전의 두 주기에는 안전한 페달 값이 0이어서 토크가 끊긴다. 3번째 주기에 채널 1을 빼고 채널 2로 간다.
 * 그 뒤로는 줄여 간다: 주의를 요청하고, 기능은 35 Nm까지, 감시의 허용 토크는 40 Nm까지다.
 * 토크 0이나 구동 허용 차단으로 가지 않는다. fault를 넣는 시각을 주기 안에서 0-9 ms로 바꿔 가며 본다.
 */
static void tc_130(void)
{
    static const driver_point_t driver[] = {
        { 0u, 0.0, false, GEAR_D },
        { T_PEDAL_ON, 0.5, false, GEAR_D },
    };
    int worst_limp_ms = 0;

    for (time_ms_t phase = 0u; phase < 10u; phase++) {
        fault_event_t fault = { T_FAULT + phase, FAULT_APPS1_FIXED_MV, 0 };
        scenario_t sc = { "fi-30", 3000u, driver, 2, &fault, 1, NULL };
        int n = scenario_run(&sc, log_buf, LOG_CAP);
        int t_limp = first_time(log_buf, n, 0u, is_limp);
        int bad = 0;

        CHECK_EQ(log_buf[T_FAULT - 1u].torque_out, 1250);
        CHECK(t_limp >= (int)fault.t_ms);
        for (int i = t_limp; i < n; i++) {
            const sample_t *s = &log_buf[i];
            /* 줄여 감: 주의, 구동 허용은 유지, 페달 고장도 고정도 아니다. 토크는 35 Nm를 넘지 않는다 */
            if ((s->warning != 1u) || !s->enable || s->diag.pedal_fault || s->diag.latched
                || (s->torque_out > 350) || (s->diag.torque_allowed > 400) || (s->diag.clamp_count != 0u)) {
                bad++;
            }
        }
        CHECK_EQ(bad, 0);
        /* 채널 2가 가리키는 50%는 14%에서 잘려 35 Nm가 된다. 감시의 허용 토크는 40 Nm다 */
        CHECK_EQ(log_buf[n - 1].torque_out, 350);
        CHECK_EQ(log_buf[n - 1].diag.torque_allowed, 400);
        CHECK_EQ(log_buf[n - 1].diag.pedal_safe, 500);
        CHECK(log_buf[n - 1].torque_act_nm > 34.0);
        if ((t_limp - (int)fault.t_ms) > worst_limp_ms) {
            worst_limp_ms = t_limp - (int)fault.t_ms;
        }
        if (phase == 5u) {
            (void)scenario_write_csv("build/out/fi-30.csv", log_buf, n);
        }
    }
    CHECK(worst_limp_ms <= 30);
    printf("  측정 FI-30: fault부터 줄여 감까지 가장 나쁜 경우 %d ms (그동안 토크 요구는 0이다)\n", worst_limp_ms);
}

/* TC-131이 쓰는 시간표: 채널 1의 선이 끊기고, 1초 뒤에 남은 채널 2가 100%의 값에 고착된다 */
static bool second_fault_on;
static void open_ch1_then_stick_ch2(time_ms_t t_ms)
{
    if (t_ms == 1000u) {
        hal_sim_set_fault(FAULT_APPS1_FIXED_MV, 0);
    }
    if (second_fault_on && (t_ms == T_FAULT)) {
        hal_sim_set_fault(FAULT_APPS2_FIXED_MV, 2250);
    }
}

/*
 * TC-131: SWR-24 fault injection FI-31
 * 줄여 가는 중에 남은 채널 2가 범위 안의 높은 값 (100%)에 고착된다 (fault 둘). 견줄 채널이 없어 알아챌 수 없다.
 * 100 ms 뒤에 운전자가 페달을 놓지만 VCU는 100%로 읽는다.
 * 토크는 줄여 감의 상한을 넘지 못하므로, 넘는 토크는 35 Nm이고 SG-01의 한계 (55 Nm, 1.0 m/s^2) 아래다.
 * 줄여 감의 상한을 그 크기로 정한 까닭이 이 경우다.
 */
static void tc_131(void)
{
    static const driver_point_t driver[] = {
        { 0u, 0.0, false, GEAR_D },
        { T_PEDAL_ON, 0.5, false, GEAR_D },
        { T_FAULT + 100u, 0.0, false, GEAR_D },
    };
    scenario_t sc = { "fi-31", 4000u, driver, 3, NULL, 0, open_ch1_then_stick_ch2 };
    int n_ref;
    int n;
    int over_ms = 0;
    double max_excess;

    second_fault_on = false;
    n_ref = scenario_run(&sc, log_ref, LOG_CAP);
    second_fault_on = true;
    n = scenario_run(&sc, log_buf, LOG_CAP);
    second_fault_on = false;
    max_excess = accel_excess(log_buf, log_ref, n, &over_ms);

    CHECK_EQ(n, n_ref);
    /* 기준 실행에서는 페달을 놓으면 토크가 0이 된다. 고착된 실행에서는 35 Nm가 남는다 */
    CHECK_EQ(log_ref[n_ref - 1].torque_out, 0);
    CHECK_EQ(log_buf[n - 1].torque_out, 350);
    CHECK_EQ(log_buf[n - 1].warning, 1);
    CHECK(!log_buf[n - 1].diag.pedal_fault);
    /* 알아채지 못하지만 SG-01은 지켜진다 */
    CHECK(max_excess > 0.5);
    CHECK(max_excess < 1.0);
    CHECK_EQ(over_ms, 0);
    printf("  측정 FI-31: 가속의 차이는 가장 클 때 %.2f m/s^2, 1.0 m/s^2를 넘은 시간 %d ms\n", max_excess, over_ms);
}

/* TC-132가 쓰는 시간표: 채널 1의 선이 끊기고, 1초 뒤에 남은 채널 2의 선도 끊긴다 */
static void open_ch1_then_open_ch2(time_ms_t t_ms)
{
    if (t_ms == 1000u) {
        hal_sim_set_fault(FAULT_APPS1_FIXED_MV, 0);
    }
    if (t_ms == T_FAULT) {
        hal_sim_set_fault(FAULT_APPS2_FIXED_MV, 0);
    }
}

/*
 * TC-132: SWR-24 fault injection FI-32
 * 줄여 가는 중에 남은 채널 2도 범위를 벗어난다 (fault 둘). 3주기 뒤에 페달 고장으로 판정하고 토크 0, 경고.
 */
static void tc_132(void)
{
    static const driver_point_t driver[] = {
        { 0u, 0.0, false, GEAR_D },
        { T_PEDAL_ON, 0.5, false, GEAR_D },
    };
    scenario_t sc = { "fi-32", 3000u, driver, 2, NULL, 0, open_ch1_then_open_ch2 };
    int n = scenario_run(&sc, log_buf, LOG_CAP);
    int t_zero = first_time(log_buf, n, T_FAULT, is_pedal_fault_and_zero);
    int bad = 0;

    CHECK_EQ(log_buf[T_FAULT - 1u].warning, 1);
    CHECK_EQ(log_buf[T_FAULT - 1u].torque_out, 350);
    /* 남은 채널이 0 V이면 안전한 페달 값이 그 주기부터 0이다. 판정은 3번째 주기다 */
    CHECK_EQ(log_buf[T_FAULT].torque_out, 0);
    CHECK_EQ(t_zero, (int)T_FAULT + 20);
    for (int i = t_zero; i < n; i++) {
        const sample_t *s = &log_buf[i];
        if ((s->torque_out != 0) || (s->warning != 2u) || !s->enable || s->diag.latched) {
            bad++;
        }
    }
    CHECK_EQ(bad, 0);
}

/*
 * TC-128: SWR-21 fault injection FI-27
 * 켜기 전부터 구동 허용 신호의 선이 허용 쪽에 고착되어 있다 (전원에 닿았다). 달리는 동안에는 드러나지 않는 고장이다.
 * VCU는 켤 때 끊으라고 쓰고, 첫 주기에 되읽는다. 허용으로 읽히므로 구동 허용 차단으로 가고 경고한다.
 * 끊는 길이 죽은 채로는 출발하지 않는다.
 */
static void tc_128(void)
{
    static const driver_point_t driver[] = {
        { 0u, 0.0, false, GEAR_D },
        { T_PEDAL_ON, 0.3, false, GEAR_D },
    };
    fault_event_t fault = { 0u, FAULT_ENABLE_STUCK_ON, 0 };
    scenario_t sc = { "fi-27", 2000u, driver, 2, &fault, 1, NULL };
    int n = scenario_run(&sc, log_buf, LOG_CAP);
    int bad = 0;

    for (int i = 0; i < n; i++) {
        const sample_t *s = &log_buf[i];
        /* 첫 주기부터 구동 허용 차단이다: 토크 0, 경고. VCU는 끝까지 허용을 쓰지 않는다 */
        if (!s->diag.latched || (s->torque_out != 0) || s->enable || (s->warning != 2u)) {
            bad++;
        }
    }
    CHECK_EQ(bad, 0);
    /* 선은 허용에 고착되어 있다. VCU가 쓴 값과 선의 값이 다르다 */
    CHECK(log_buf[n - 1].enable_wire);
    CHECK(log_buf[n - 1].speed_mps < 0.01);
}

/*
 * TC-129: SWR-21 fault injection FI-28
 * 달리는 중에 구동 허용 신호의 선이 끊긴다. inverter는 끊긴 것으로 보고 토크를 내지 않는다 (구동력을 잃는다).
 * VCU는 허용이라고 썼는데 다음 주기에 끊김으로 읽는다. 구동 허용 차단으로 가고 경고한다.
 * 구동력을 잃은 것을 운전자가 경고로 알게 된다 (SG-02의 둘째 구절).
 */
static void tc_129(void)
{
    static const driver_point_t driver[] = {
        { 0u, 0.0, false, GEAR_D },
        { T_PEDAL_ON, 0.3, false, GEAR_D },
    };
    int worst_warn_ms = 0;

    for (time_ms_t phase = 0u; phase < 10u; phase++) {
        fault_event_t fault = { T_FAULT + phase, FAULT_ENABLE_OPEN, 0 };
        scenario_t sc = { "fi-28", 3000u, driver, 2, &fault, 1, NULL };
        int n = scenario_run(&sc, log_buf, LOG_CAP);
        int t_cut = first_time(log_buf, n, 0u, is_latched);

        CHECK(t_cut >= (int)fault.t_ms);
        CHECK_EQ(bad_after_cut(log_buf, n, t_cut), 0);
        CHECK_EQ(log_buf[t_cut - 1].warning, 0);
        CHECK(log_buf[n - 1].torque_act_nm < 0.01);
        /* 끊긴 때의 선은 끊김이고, 그 주기에 VCU는 아직 허용이라고 쓰고 있었다 */
        CHECK(!log_buf[fault.t_ms].enable_wire);
        CHECK(log_buf[fault.t_ms].enable || (t_cut == (int)fault.t_ms));
        if ((t_cut - (int)fault.t_ms) > worst_warn_ms) {
            worst_warn_ms = t_cut - (int)fault.t_ms;
        }
    }
    /* 다음 주기의 되읽기에서 드러난다: 가장 나빠도 10 ms */
    CHECK(worst_warn_ms <= 10);
    printf("  측정 FI-28: 선이 끊긴 때부터 구동 허용 차단과 경고까지 가장 나쁜 경우 %d ms\n", worst_warn_ms);
}

/*
 * TC-124: SWR-20 fault injection FI-23
 * 달리는 중에 입력을 읽는 task가 실행되지 않게 된다. 기능과 감시는 지난 입력으로 계속 돈다.
 * 100 ms 뒤에 운전자가 페달을 놓지만 VCU는 그것을 읽지 못한다.
 * task의 표시가 하나 모자라므로 VCU는 외부 watchdog에 답하지 않고, watchdog이 창이 닫힐 때 구동 허용 신호를 끊는다.
 * fault를 넣는 시각을 주기 안에서 0-9 ms로 바꿔 가며 본다.
 */
static void tc_124(void)
{
    static const driver_point_t driver[] = {
        { 0u, 0.0, false, GEAR_D },
        { T_PEDAL_ON, 0.3, false, GEAR_D },
        { T_FAULT + 100u, 0.0, false, GEAR_D },
    };
    scenario_t sc_ref = { "fi-23-ref", 3000u, driver, 3, NULL, 0, NULL };
    int n_ref = scenario_run(&sc_ref, log_ref, LOG_CAP);
    int worst_trip_ms = 0;
    int worst_off_ms = 0;
    int worst_over_ms = 0;

    for (time_ms_t phase = 0u; phase < 10u; phase++) {
        fault_event_t fault = { T_FAULT + phase, FAULT_TASK_SKIP, 0 };
        scenario_t sc = { "fi-23", 3000u, driver, 3, &fault, 1, NULL };
        int n = scenario_run(&sc, log_buf, LOG_CAP);
        int over_ms = 0;
        double max_excess = accel_excess(log_buf, log_ref, n, &over_ms);
        int t_trip = first_time(log_buf, n, 0u, is_watchdog_tripped);
        int t_off = first_motor_off(log_buf, n, fault.t_ms);

        CHECK_EQ(n, n_ref);
        CHECK(t_trip >= (int)fault.t_ms);
        CHECK(t_off >= 0);
        /* VCU는 지난 입력으로 75 Nm를 계속 보낸다. 구동을 막은 것은 watchdog이다 */
        CHECK_EQ(log_buf[n - 1].torque_out, 750);
        CHECK(log_buf[n - 1].torque_act_nm < 0.01);
        CHECK(max_excess < 0.01);
        if ((t_trip - (int)fault.t_ms) > worst_trip_ms) {
            worst_trip_ms = t_trip - (int)fault.t_ms;
        }
        if ((t_off - (int)fault.t_ms) > worst_off_ms) {
            worst_off_ms = t_off - (int)fault.t_ms;
        }
        if (over_ms > worst_over_ms) {
            worst_over_ms = over_ms;
        }
        if (phase == 5u) {
            (void)scenario_write_csv("build/out/fi-23.csv", log_buf, n);
        }
    }
    /* 시간 예산표 (docs/technical-safety-concept.md 9.4절): 창 15 ms + 전달 1 ms + inverter의 응답 60 ms */
    CHECK(worst_trip_ms <= 15);
    CHECK(worst_off_ms <= 76);
    CHECK_EQ(worst_over_ms, 0);
    printf("  측정 FI-23: fault부터 watchdog이 끊을 때까지 가장 나쁜 경우 %d ms, 모터의 토크가 5%% 아래로 내려갈 때까지 %d ms\n",
           worst_trip_ms, worst_off_ms);
}

/*
 * TC-125: SWR-20 fault injection FI-24
 * 실행의 다른 고장 여섯: 기능의 task가 빠짐, 감시와 출력의 task가 빠짐, 실행을 확인하는 task가 빠짐,
 * task가 하나도 실행되지 않음 (MCU가 멈춤), 기능의 task가 한 주기에 두 번 실행됨, 감시와 출력의 task가 두 번 실행됨.
 * 어느 것이든 옳은 답이 나가지 않아 watchdog이 끊는다.
 */
static void tc_125(void)
{
    static const driver_point_t driver[] = {
        { 0u, 0.0, false, GEAR_D },
        { T_PEDAL_ON, 0.3, false, GEAR_D },
    };
    static const fault_event_t faults[] = {
        { T_FAULT, FAULT_TASK_SKIP, 1 },
        { T_FAULT, FAULT_TASK_SKIP, 2 },
        { T_FAULT, FAULT_TASK_SKIP, 3 },
        { T_FAULT, FAULT_TASK_STOP, 0 },
        { T_FAULT, FAULT_TASK_TWICE, 1 },
        { T_FAULT, FAULT_TASK_TWICE, 2 },
    };
    int worst_trip_ms = 0;

    for (int k = 0; k < 6; k++) {
        scenario_t sc = { "fi-24", 3000u, driver, 2, &faults[k], 1, NULL };
        int n = scenario_run(&sc, log_buf, LOG_CAP);
        int t_trip = first_time(log_buf, n, 0u, is_watchdog_tripped);

        CHECK(t_trip >= (int)T_FAULT);
        CHECK((t_trip - (int)T_FAULT) <= 16);
        CHECK(log_buf[n - 1].torque_act_nm < 0.01);
        /* watchdog이 끊은 것을 VCU가 아는가 (SWR-21). 입력의 task와 출력의 task가 살아 있으면
         * 다음 주기의 되읽기에서 드러나 구동 허용 차단과 경고가 된다. 출력의 task가 죽었으면 경고를 쓰지 못한다 */
        CHECK_EQ(log_buf[n - 1].warning, ((k == 1) || (k == 3)) ? 0 : 2);
        if ((t_trip - (int)T_FAULT) > worst_trip_ms) {
            worst_trip_ms = t_trip - (int)T_FAULT;
        }
    }
    printf("  측정 FI-24: fault부터 watchdog이 끊을 때까지 가장 나쁜 경우 %d ms\n", worst_trip_ms);
}

/*
 * TC-126: SWR-20 fault injection FI-25
 * task의 주기가 두 배로 늘어난다 (clock의 고장). 소프트웨어가 주기로 세는 시간이 모두 두 배가 된다.
 * 소프트웨어는 자기 clock이 틀린 것을 알 수 없다. 답이 창보다 늦게 가므로 watchdog이 끊는다.
 */
static void tc_126(void)
{
    static const driver_point_t driver[] = {
        { 0u, 0.0, false, GEAR_D },
        { T_PEDAL_ON, 0.3, false, GEAR_D },
    };
    fault_event_t fault = { T_FAULT, FAULT_TASK_SLOW, 0 };
    scenario_t sc = { "fi-25", 3000u, driver, 2, &fault, 1, NULL };
    int n = scenario_run(&sc, log_buf, LOG_CAP);
    int t_trip = first_time(log_buf, n, 0u, is_watchdog_tripped);

    CHECK(t_trip >= (int)T_FAULT);
    CHECK((t_trip - (int)T_FAULT) <= 26);
    CHECK(log_buf[n - 1].torque_act_nm < 0.01);
    printf("  측정 FI-25: fault부터 watchdog이 끊을 때까지 %d ms\n", t_trip - (int)T_FAULT);
}

/* TC-133: SWR-12 켠 직후의 VCU의 상태는 memory에 남아 있던 값과 상관없이 정해진 값이다.
 * 상태를 쓰레기 값으로 채운 뒤에 vcu_init을 부르고 필드를 값으로 본다.
 * 요소마다의 init을 부르는 줄이 하나 빠져도, 주기 실행부의 값 하나를 정하지 않아도 여기에서 드러난다 */
static void vcu_init_state_is_defined(int fill)
{
    plant_t plant;
    vcu_t vcu;

    plant_init(&plant);
    hal_sim_init(&plant);
    memset(&vcu, fill, sizeof(vcu));
    vcu_init(&vcu);

    CHECK(!vcu.speed_valid);
    CHECK_EQ(vcu.speed, 0);
    CHECK(!vcu.inverter_valid);
    CHECK(!vcu.inverter_fresh);
    CHECK_EQ(vcu.inverter_torque, 0);
    CHECK_EQ(vcu.pedal_safe, 0);
    CHECK(vcu.brake);           /* 켠 직후에는 밟은 것으로 본다 */
    CHECK_EQ(vcu.gear, GEAR_N); /* 받아들인 기어가 아직 없다 */
    CHECK_EQ(vcu.torque_req, 0);
    CHECK_EQ(vcu.torque_allowed, 0);
    CHECK_EQ(vcu.torque_out, 0);
    CHECK(!vcu.enable);
    CHECK_EQ(vcu.warning, 0);
    /* 요소마다의 상태도 정해져 있다 (자세한 것은 TC-023이 본다) */
    CHECK(!vcu.pedal_check.ready);
    CHECK(!vcu.pedal_check.fault);
    CHECK(vcu.brake_check.pressed);
    CHECK_EQ(vcu.gear_check.direction, GEAR_N);
    CHECK_EQ(vcu.app.prev, 0);
    CHECK_EQ(vcu.output.last_out, 0);
    CHECK_EQ(vcu.output.excess_cycles, 0);
    CHECK_EQ(vcu.reaction.state, REACTION_NORMAL);
    CHECK_EQ(vcu.inverter_check.pos, 0);
    CHECK_EQ(vcu.inverter_check.out_cycles, 0);
    CHECK_EQ(vcu.flow.count, 0);
    CHECK(!vcu.speed_rx.ok);
    CHECK(!vcu.speed_rx.synced);
    CHECK(!vcu.inverter_rx.ok);
    CHECK(!vcu.inverter_rx.synced);
    CHECK_EQ(vcu.torque_tx.counter, 0);
    /* 켤 때 구동 허용 신호를 끊는 쪽으로 쓴다 */
    CHECK(!hal_sim_enable_wire());
}

static void tc_133(void)
{
    /* 0이 아닌 쓰레기 값과 0을 모두 넣어 본다 (TC-023의 설명) */
    vcu_init_state_is_defined(0xA5);
    vcu_init_state_is_defined(0x00);
}

/* TC-134와 TC-135가 쓰는 것: 정해진 동안 inverter의 상태 메시지를 잃는다 */
static fault_id_t loss_fault;
static int32_t loss_param;
static time_ms_t loss_on_ms;
static time_ms_t loss_off_ms;
static int32_t loss_report_offset;
static bool loss_report_stale;
static int32_t loss_torque_offset;
static time_ms_t loss_torque_ms;
static bool loss_inverter_no_check; /* inverter가 토크 요구 메시지를 검사하지 않는다 (A-21이 틀린 경우) */

static void status_message_loss(time_ms_t t_ms)
{
    if (t_ms == loss_off_ms) {
        hal_sim_clear_faults();
    }
    if ((t_ms == 0u) && loss_inverter_no_check) {
        hal_sim_inverter_check(false);
    }
    if ((t_ms == 0u) || (t_ms == loss_off_ms)) {
        if (loss_report_offset != 0) {
            hal_sim_set_fault(FAULT_INVERTER_REPORT_OFFSET, loss_report_offset);
        }
        if (loss_report_stale) {
            hal_sim_set_fault(FAULT_INVERTER_REPORT_STALE, 0);
        }
    }
    if ((t_ms == loss_on_ms) && (loss_on_ms != loss_off_ms)) {
        hal_sim_set_fault(loss_fault, loss_param);
    }
    if ((loss_torque_offset != 0) && (t_ms == loss_torque_ms)) {
        hal_sim_set_fault(FAULT_INVERTER_TORQUE_OFFSET, loss_torque_offset);
    }
}

static void loss_reset(void)
{
    loss_fault = FAULT_INVERTER_MSG_DROP;
    loss_param = 0;
    loss_on_ms = 0u;
    loss_off_ms = 0u;
    loss_report_offset = 0;
    loss_report_stale = false;
    loss_torque_offset = 0;
    loss_torque_ms = 0u;
    loss_inverter_no_check = false;
}

/* 되풀이되는 모양 (길이 period, bit k가 1이면 k번째 메시지가 닿는다)이 SWR-19가 받아들이는 것인가:
 * 어느 5주기를 잡아도 닿는 메시지가 3개 이상인가. 제품의 코드와 따로 적은 셈이다 */
static bool pattern_accepted(unsigned period, unsigned mask)
{
    for (unsigned start = 0u; start < period; start++) {
        unsigned ones = 0u;
        for (unsigned k = 0u; k < 5u; k++) {
            ones += (mask >> ((start + k) % period)) & 1u;
        }
        if (ones < 3u) {
            return false;
        }
    }
    return true;
}

static int count_bad_normal(const sample_t *log, int n)
{
    int bad = 0;

    for (int i = 0; i < n; i++) {
        const sample_t *s = &log[i];
        if (s->diag.latched || (s->warning != 0u) || ((s->t_ms >= 20u) && !s->enable)) {
            bad++;
        }
    }
    return bad;
}

static int count_invalid(const sample_t *log, int n, time_ms_t from_ms)
{
    int invalid = 0;

    for (int i = 0; i < n; i++) {
        if ((log[i].t_ms >= from_ms) && !log[i].diag.inverter_valid) {
            invalid++;
        }
    }
    return invalid;
}

/*
 * TC-134: SWR-19 상태 메시지를 잃을 때 (SG-02 쪽. 변경 요청 CR-001과 CR-002)
 * 받는 쪽의 검사 (SWR-18)는 새 메시지가 50 ms까지 없어도 마지막 값을 유효로 넘긴다.
 * 그 묵은 값을 보낸 토크의 범위와 견주면, 토크가 크게 내려가는 때에 고장 없는 inverter를 끊는다
 * (docs/fmea.md의 FM-29). 새 메시지가 없는 주기에는 견주지 않아야 한다 (CR-001).
 * 그리고 새 메시지가 너무 드물게 닿으면 (최근 5주기 가운데 3번보다 적으면) 그것으로 끊고 경고한다 (CR-002).
 * 받아들이는 손실 (이어서 둘까지, 어느 5주기에서도 3번 이상 닿음)에서는 끊지 않는다는 것과,
 * 그보다 많이 잃으면 끊는다는 것을 함께 본다.
 * 잃는 모양은 둘이다: inverter가 보내지 않는 경우와, 보냈는데 bus에서 사라지는 경우 (counter가 건너뛴다).
 * 알리는 값이 가정 (A-23)의 끝에 있는 경우 (10 Nm 크고 한 주기 묵음)도 본다.
 */
static void tc_134(void)
{
    static const driver_point_t driver[] = {
        { 0u, 0.0, false, GEAR_D },
        { 200u, 1.0, false, GEAR_D },
        { 1500u, 0.0, false, GEAR_D },  /* 놓는다: 250 Nm에서 한 주기에 0 */
    };
    static const fault_id_t models[] = { FAULT_INVERTER_MSG_LOSS, FAULT_INVERTER_MSG_DROP };
    static const char *const model_names[] = { "보내지 않음", "bus에서 사라짐" };
    scenario_t sc_ref = { "status-ref", 2000u, driver, 3, NULL, 0, NULL };
    int n_ref = scenario_run(&sc_ref, log_buf, LOG_CAP);
    uint32_t msgs_ref = log_buf[n_ref - 1].inverter_msgs;

    CHECK_EQ(count_bad_normal(log_buf, n_ref), 0);
    CHECK_EQ((int)msgs_ref, 200);

    /* 1. 페달을 놓는 때의 앞뒤로, 메시지를 1 - 5개 이어서 잃는 구간을 1 ms씩 옮긴다 */
    for (int m = 0; m < 2; m++) {
        for (int edge = 0; edge < 2; edge++) {
            int worst = 0;
            int kept = 0;         /* 둘까지 잃었을 때 끊지 않은 횟수 */
            int kept_runs = 0;
            int cut = 0;          /* 셋 넘게 잃었을 때 끊고 경고한 횟수 */
            int cut_runs = 0;
            int worst_cut_ms = 0;
            int wrong_msgs = 0;
            int wrong_valid = 0;

            for (int lost = 1; lost <= 5; lost++) {
                for (time_ms_t start = 1450u; start <= 1560u; start++) {
                    scenario_t sc = { "status-loss", 2000u, driver, 3, NULL, 0, status_message_loss };
                    int n;
                    int invalid;

                    loss_reset();
                    loss_fault = models[m];
                    loss_param = SIM_DROP_PATTERN(1, 0); /* 구간 안에서는 모두 잃는다 */
                    loss_on_ms = start;
                    loss_off_ms = start + (time_ms_t)(lost * 10);
                    loss_report_offset = (edge != 0) ? 100 : 0;
                    loss_report_stale = (edge != 0);
                    n = scenario_run(&sc, log_buf, LOG_CAP);
                    /* 메시지를 정말 그만큼 잃었는가 (fault가 들지 않으면 이 test는 아무것도 보지 않는다) */
                    if (log_buf[n - 1].inverter_msgs != (msgs_ref - (uint32_t)lost)) {
                        wrong_msgs++;
                    }
                    /* 잃는 모양이 적은 대로인가. bus에서 사라지면 counter가 건너뛴다: 셋 넘게 잃은 뒤에 닿은
                     * 메시지는 받는 쪽의 검사가 버린다 (무효인 주기가 생긴다). 둘까지는 받아들인다.
                     * 보내지 않는 경우에는 counter가 이어지므로 무효인 주기가 없다 (50 ms를 넘기 전까지) */
                    invalid = count_invalid(log_buf, n, 100u);
                    if ((m == 1) && (lost >= 3) && (invalid == 0)) {
                        wrong_valid++;
                    }
                    if (((m == 1) && (lost <= 2) && (invalid != 0)) || ((m == 0) && (lost <= 3) && (invalid != 0))) {
                        wrong_valid++;
                    }
                    if (lost <= 2) {
                        kept_runs++;
                        if (count_bad_normal(log_buf, n) == 0) {
                            kept++;
                        }
                        for (int i = 0; i < n; i++) {
                            if ((int)log_buf[i].diag.inverter_out_cycles > worst) {
                                worst = (int)log_buf[i].diag.inverter_out_cycles;
                            }
                        }
                    } else {
                        int t_cut = first_time(log_buf, n, 0u, is_latched);
                        cut_runs++;
                        if ((t_cut >= (int)start) && (bad_after_cut(log_buf, n, t_cut) == 0)) {
                            cut++;
                            if ((t_cut - (int)start) > worst_cut_ms) {
                                worst_cut_ms = t_cut - (int)start;
                            }
                        }
                    }
                }
            }
            CHECK_EQ(wrong_msgs, 0);
            CHECK_EQ(wrong_valid, 0);
            CHECK_EQ(kept, kept_runs);
            CHECK(worst < 3);
            CHECK_EQ(cut, cut_runs);
            CHECK(worst_cut_ms <= 40);
            printf("  측정 상태 메시지를 잃음 (%s, %s): 둘까지 잃은 %d번 가운데 끊은 것 %d번 (범위를 벗어난 새 메시지가 "
                   "이어진 횟수는 가장 클 때 %d), 셋 넘게 잃은 %d번은 모두 끊고 경고했다 (잃기 시작한 때부터 가장 늦어도 %d ms)\n",
                   model_names[m], (edge != 0) ? "오차 +10 Nm, 한 주기 묵음" : "오차 없음",
                   kept_runs, kept_runs - kept, worst, cut_runs, worst_cut_ms);
        }
    }

    /* 2. 손실이 되풀이되는 모양. 길이 1 - 5의 모든 모양 (62가지)을, 토크가 가장 크게 바뀌는 운전 (TC-123의 것)
     * 내내 넣는다. 어느 5주기에서도 3번 이상 닿는 모양에서는 끊지 않고, 나머지에서는 끊고 경고한다 */
    {
        static const driver_point_t hard[] = {
            { 0u, 0.0, false, GEAR_D },
            { 200u, 1.0, false, GEAR_D },
            { 1500u, 0.0, false, GEAR_D },
            { 2000u, 1.0, false, GEAR_D },
            { 3000u, 1.0, true, GEAR_D },
            { 3500u, 1.0, false, GEAR_D },
            { 3530u, 0.0, false, GEAR_D },
            { 3560u, 1.0, false, GEAR_D },
            { 3590u, 0.0, false, GEAR_D },
            { 3620u, 1.0, false, GEAR_D },
            { 3650u, 0.0, false, GEAR_D },
            { 3700u, 0.0, true, GEAR_D },
        };
        int accepted = 0;
        int accepted_kept = 0;
        int rejected = 0;
        int rejected_cut = 0;
        int worst_cut_ms = 0;
        int no_loss_seen = 0;

        for (unsigned period = 1u; period <= 5u; period++) {
            for (unsigned mask = 0u; mask < (1u << period); mask++) {
                for (time_ms_t start = 100u; start < 150u; start += 10u) {
                    scenario_t sc = { "status-pattern", 4500u, hard, 12, NULL, 0, status_message_loss };
                    int n;

                    loss_reset();
                    loss_fault = FAULT_INVERTER_MSG_DROP;
                    loss_param = SIM_DROP_PATTERN(period, mask);
                    loss_on_ms = start;
                    loss_off_ms = 100000u; /* 끝까지 */
                    loss_report_offset = 100;
                    loss_report_stale = true;
                    n = scenario_run(&sc, log_buf, LOG_CAP);
                    if (log_buf[n - 1].inverter_msgs == 450u) {
                        no_loss_seen++;
                    }
                    if (pattern_accepted(period, mask)) {
                        accepted++;
                        if (count_bad_normal(log_buf, n) == 0) {
                            accepted_kept++;
                        }
                    } else {
                        int t_cut = first_time(log_buf, n, 0u, is_latched);
                        rejected++;
                        if ((t_cut >= (int)start) && (bad_after_cut(log_buf, n, t_cut) == 0)) {
                            rejected_cut++;
                            if ((t_cut - (int)start) > worst_cut_ms) {
                                worst_cut_ms = t_cut - (int)start;
                            }
                        }
                    }
                }
            }
        }
        CHECK_EQ(accepted_kept, accepted);
        CHECK_EQ(rejected_cut, rejected);
        /* 하나도 잃지 않는 모양은 다섯 (길이마다 하나)이고 시작을 다섯 번 옮겼다. 그 밖에서는 메시지가 줄어야 한다 */
        CHECK_EQ(no_loss_seen, 25);
        CHECK(accepted > 25);
        CHECK(worst_cut_ms <= 110);
        printf("  측정 손실이 되풀이됨: 받아들이는 모양으로 돌린 %d번은 끊지 않았다. 그보다 드문 모양으로 돌린 %d번은 "
               "모두 끊고 경고했다 (잃기 시작한 때부터 가장 늦어도 %d ms)\n", accepted, rejected, worst_cut_ms);
    }

    /* 3. bus에서 모두 사라지는 채로 이어진다. 끊고, 받은 뒤로 50 ms가 지난 뒤에는 상태가 무효다 */
    {
        scenario_t sc = { "status-gone", 2000u, driver, 3, NULL, 0, status_message_loss };
        int n;
        int t_cut;

        loss_reset();
        loss_fault = FAULT_INVERTER_MSG_DROP;
        loss_param = SIM_DROP_PATTERN(1, 0);
        loss_on_ms = 1000u;
        loss_off_ms = 100000u;
        n = scenario_run(&sc, log_buf, LOG_CAP);
        t_cut = first_time(log_buf, n, 0u, is_latched);
        CHECK(t_cut >= 1000);
        CHECK(t_cut <= 1040);
        CHECK_EQ(bad_after_cut(log_buf, n, t_cut), 0);
        CHECK_EQ((int)log_buf[n - 1].inverter_msgs, 100);
        CHECK(log_buf[1040].diag.inverter_valid);
        CHECK_EQ(count_invalid(log_buf, n, 1070u), n - 1070);
    }
    loss_reset();
}

/*
 * TC-135: SWR-19 fault injection FI-34 (SG-01 쪽. 변경 요청 CR-002)
 * inverter가 틀린 토크를 내는 것과 같은 때에 상태 메시지를 잃는다. 손실의 모양은 길이 1 - 5의 모든 모양이다.
 * 새 메시지가 없는 주기에는 견주지 않으므로 판정은 새 메시지가 닿아야 나아간다. 그 대신 새 메시지가 너무 드물면
 * 그것으로 끊는다. 그래서 손실의 모양이 무엇이든, 알린 토크가 범위를 벗어난 때부터 5주기 안에 끊는다.
 * inverter의 고장은 셋이다: 100 Nm 더 낸다 (FI-21의 것), 페달을 놓았는데 옛 토크를 계속 낸다 (FI-20의 되풀이.
 * 시간 예산표의 M4 줄을 정한 경우), 같은 것을 끝까지 밟은 데서 (250 Nm) 놓는다.
 */
static void tc_135(void)
{
    static const driver_point_t hold[] = {
        { 0u, 0.0, false, GEAR_D },
        { T_PEDAL_ON, 0.3, false, GEAR_D },
    };
    static const driver_point_t release[] = {
        { 0u, 0.0, false, GEAR_D },
        { T_PEDAL_ON, 0.3, false, GEAR_D },
        { T_FAULT, 0.0, false, GEAR_D },
    };
    static const driver_point_t release_full[] = {
        { 0u, 0.0, false, GEAR_D },
        { T_PEDAL_ON, 1.0, false, GEAR_D },
        { T_FAULT, 0.0, false, GEAR_D },
    };
    static const char *const kind_names[] = { "100 Nm 더 냄", "75 Nm에서 놓았는데 옛 토크를 계속 냄",
                                              "250 Nm에서 놓았는데 옛 토크를 계속 냄" };
    /* 시작: 오래전부터 (받아들이는 모양만), 고장의 조금 앞, 같은 때, 조금 뒤 */
    static const time_ms_t starts[] = { 1000u, T_FAULT - 20u, T_FAULT, T_FAULT + 20u };
    /* 차단까지의 한계: 범위를 벗어나기까지 (더 내는 경우 한두 주기, 옛 토크는 기록에서 빠지는 50 ms) + 5주기 + 다음 주기 */
    static const int cut_limit_ms[] = { 70, 110, 110 };
    /* 잰 값. 상태 메시지가 주기마다 닿으면 36, 70, 70 ms다 (TC-121, TC-120). 손실 때문에 20 ms까지 늦어진다.
     * 값으로 고정해 둔다. 바뀌면 시간의 예산을 다시 보아야 한다 */
    static const int cut_measured_ms[] = { 56, 90, 90 };
    /* "5% 아래"의 기준: 고장 전에 내던 토크 (75 Nm, 75 Nm, 250 Nm)의 5% */
    static const double off_limit_nm[] = { 3.75, 3.75, 12.5 };

    for (int kind = 0; kind < 3; kind++) {
        const driver_point_t *driver = (kind == 0) ? hold : ((kind == 1) ? release : release_full);
        const int driver_count = (kind == 0) ? 2 : 3;
        scenario_t sc_ref = { "fi-34-ref", 2600u, driver, driver_count, NULL, 0, NULL };
        int worst_cut_ms = 0;
        int worst_off_ms = 0;
        int worst_over_ms = 0;
        double worst_excess = 0.0;
        int runs = 0;
        int not_cut = 0;

        (void)scenario_run(&sc_ref, log_ref, LOG_CAP);
        for (unsigned period = 1u; period <= 5u; period++) {
            for (unsigned mask = 0u; mask < (1u << period); mask++) {
                for (int si = 0; si < 4; si++) {
                    const time_ms_t phase_count = (kind == 0) ? 3u : 1u;

                    if ((si == 0) && !pattern_accepted(period, mask)) {
                        continue; /* 고장보다 먼저 끊는다 (TC-134) */
                    }
                    for (time_ms_t pi = 0u; pi < phase_count; pi++) {
                        const time_ms_t t_fault = T_FAULT + ((kind == 0) ? (pi * 4u) : 0u);
                        fault_event_t repeat = { T_FAULT - 5u, FAULT_TORQUE_MSG_REPEAT, 0 };
                        scenario_t sc = { "fi-34", 2600u, driver, driver_count,
                                          (kind == 0) ? NULL : &repeat, (kind == 0) ? 0 : 1, status_message_loss };
                        int n;
                        int over_ms = 0;
                        double max_excess;
                        int t_cut;
                        int t_off;

                        loss_reset();
                        loss_fault = FAULT_INVERTER_MSG_DROP;
                        loss_param = SIM_DROP_PATTERN(period, mask);
                        loss_on_ms = starts[si];
                        loss_off_ms = 100000u;
                        if (kind == 0) {
                            loss_torque_offset = 1000;
                            loss_torque_ms = t_fault;
                        } else {
                            loss_inverter_no_check = true;
                        }
                        n = scenario_run(&sc, log_buf, LOG_CAP);
                        max_excess = accel_excess(log_buf, log_ref, n, &over_ms);
                        t_cut = first_time(log_buf, n, 0u, is_latched);
                        t_off = first_motor_below(log_buf, n, t_fault, off_limit_nm[kind]);
                        runs++;
                        if ((t_cut < 0) || (t_off < 0) || (bad_after_cut(log_buf, n, t_cut) != 0)) {
                            not_cut++;
                            continue;
                        }
                        if ((t_cut - (int)t_fault) > worst_cut_ms) {
                            worst_cut_ms = t_cut - (int)t_fault;
                        }
                        if ((t_off - (int)t_fault) > worst_off_ms) {
                            worst_off_ms = t_off - (int)t_fault;
                        }
                        if (over_ms > worst_over_ms) {
                            worst_over_ms = over_ms;
                        }
                        if (max_excess > worst_excess) {
                            worst_excess = max_excess;
                        }
                    }
                }
            }
        }
        CHECK_EQ(not_cut, 0);
        CHECK(worst_cut_ms <= cut_limit_ms[kind]);
        CHECK_EQ(worst_cut_ms, cut_measured_ms[kind]);
        /* 시간 예산표 (docs/technical-safety-concept.md 9.4절)의 M4 줄: 손실의 모양이 무엇이든 합 171 ms 안 */
        CHECK(worst_off_ms <= 171);
        CHECK(worst_over_ms <= 200);
        printf("  측정 FI-34 (%s + 상태 메시지 손실의 모든 모양, %d번): 고장부터 차단까지 가장 나쁜 경우 %d ms, "
               "모터의 토크가 5%% 아래로 내려갈 때까지 %d ms, 가속의 차이는 가장 클 때 %.2f m/s^2, 1.0 m/s^2를 넘은 시간 %d ms\n",
               kind_names[kind], runs, worst_cut_ms, worst_off_ms, worst_excess, worst_over_ms);
    }
    loss_reset();
}

int main(void)
{
    static const test_case_t cases[] = {
        { "TC-101", "고장이 없는 주행", tc_101 },
        { "TC-102", "FI-01 페달 채널 1이 높은 값에 고착", tc_102 },
        { "TC-103", "FI-03 두 채널이 함께 올라감 (알려진 한계)", tc_103 },
        { "TC-104", "브레이크를 밟으면 토크 0", tc_104 },
        { "TC-105", "켠 직후에는 토크를 내지 않는다", tc_105 },
        { "TC-106", "후진 기어의 방향", tc_106 },
        { "TC-107", "기어가 P, N, 알 수 없는 값이면 토크 0", tc_107 },
        { "TC-108", "켤 때 구동 허용 신호는 끊겨 있다", tc_108 },
        { "TC-109", "FI-08 페달 채널 1이 가끔 끊김 (간헐 고장)", tc_109 },
        { "TC-110", "FI-10 브레이크 접점 1이 놓음에 고착 (숨은 고장)", tc_110 },
        { "TC-111", "FI-11 브레이크 접점 1의 선이 끊김 (구동력을 잃는다)", tc_111 },
        { "TC-112", "FI-13 토크 요구 메시지의 값이 전송 중에 바뀜", tc_112 },
        { "TC-113", "FI-14 지난 토크 요구 메시지가 되풀이됨", tc_113 },
        { "TC-114", "FI-15 차량 속도 메시지가 바뀜, 되풀이됨, 끊김, 얼어붙음", tc_114 },
        { "TC-115", "FI-16 inverter의 상태 메시지가 끊김", tc_115 },
        { "TC-116", "FI-17 달리는 중에 기어가 R로 바뀜", tc_116 },
        { "TC-117", "FI-18 서서 R을 고르는데 차량 속도가 무효", tc_117 },
        { "TC-118", "FI-19 차량 속도가 0에 얼어붙은 채 기어가 R로 바뀜 (알려진 한계)", tc_118 },
        { "TC-119", "주의와 경고가 겹치면 경고가 나간다", tc_119 },
        { "TC-120", "FI-20 전송 중의 고장인데 inverter가 메시지를 검사하지 않음", tc_120 },
        { "TC-121", "FI-21 inverter가 요구보다 100 Nm 더 냄", tc_121 },
        { "TC-122", "FI-22 inverter가 더 내면서 알리는 값도 틀림 (알려진 한계)", tc_122 },
        { "TC-123", "고장이 없으면 inverter의 검사가 끊지 않는다", tc_123 },
        { "TC-124", "FI-23 입력을 읽는 task가 실행되지 않음", tc_124 },
        { "TC-125", "FI-24 task가 빠지거나 모두 멈춤", tc_125 },
        { "TC-126", "FI-25 task의 주기가 두 배로 늘어남", tc_126 },
        { "TC-128", "FI-27 켜기 전부터 구동 허용 신호의 선이 허용에 고착", tc_128 },
        { "TC-129", "FI-28 달리는 중에 구동 허용 신호의 선이 끊김", tc_129 },
        { "TC-130", "FI-30 페달 채널 1의 선이 끊김 (줄여 간다)", tc_130 },
        { "TC-131", "FI-31 줄여 가는 중에 남은 채널이 높은 값에 고착 (알아채지 못하지만 SG-01은 지킨다)", tc_131 },
        { "TC-132", "FI-32 줄여 가는 중에 남은 채널도 범위를 벗어남", tc_132 },
        { "TC-133", "켠 직후의 VCU의 상태는 memory에 남아 있던 값과 상관없이 정해져 있다", tc_133 },
        { "TC-134", "상태 메시지를 받아들이는 만큼 잃으면 끊지 않고, 그보다 드물게 닿으면 끊고 경고한다", tc_134 },
        { "TC-135", "FI-34 inverter의 고장과 상태 메시지의 손실이 겹쳐도 정한 시간 안에 끊는다", tc_135 },
    };
    return (test_run_all(cases, (int)(sizeof(cases) / sizeof(cases[0]))) == 0) ? 0 : 1;
}
