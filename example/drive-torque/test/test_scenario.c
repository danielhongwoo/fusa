/*
 * 책의 예제 코드다. 실제 제품에 쓸 수 없다.
 * 시나리오 test: VCU 전체를 plant model과 함께 돌린다. fault는 HAL의 뒤에서 넣는다.
 * test마다 어느 요구사항을 보는지 "TC-번호: SWR-번호"로 적는다.
 */
#include <stddef.h>

#include "scenario.h"
#include "vcu.h"
#include "test.h"

#define LOG_CAP 8000
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
        if (s->diag.pedal_fault || s->diag.latched || (s->warning != 0u)
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

/* 모터의 토크가 3.75 Nm (75 Nm의 5%) 아래로 처음 내려가는 시각. 없으면 -1 */
static int first_motor_off(const sample_t *log, int n, time_ms_t from_ms)
{
    for (int i = 0; i < n; i++) {
        if ((log[i].t_ms >= from_ms) && (log[i].torque_act_nm < 3.75)) {
            return (int)log[i].t_ms;
        }
    }
    return -1;
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
 * VCU는 자기가 보낸 것이 바뀐 줄 모른다. 그래서 경고를 요청하지 않는다 (남은 것. docs/safety-case.md 5절).
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
 * TC-115: SWR-18 fault injection FI-16
 * inverter의 상태 메시지가 끊긴다. 마지막 메시지에서 50 ms가 지난 다음 주기부터 무효다.
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

    for (int i = 10; i < n; i++) {
        bool want = (i < ((int)T_FAULT + 50));
        if (log_buf[i].diag.inverter_valid != want) {
            wrong++;
        }
    }
    CHECK_EQ(wrong, 0);
}

/*
 * NC-002: 대조. inverter가 메시지를 검사하지 않으면 FI-13과 FI-14는 SG-01을 어긴다.
 * 그래서 TC-112와 TC-113의 "SG-01이 지켜졌다"는 메시지의 보호와 inverter의 검사 (가정 A-21)가 한 일이다.
 * 요구사항을 검증하는 test가 아니므로 추적에 넣지 않는다.
 */
static void nc_002(void)
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
    scenario_t sc_ref1 = { "nc-002-ref1", 3000u, hold, 2, NULL, 0, inverter_does_not_check };
    scenario_t sc1 = { "nc-002-corrupt", 3000u, hold, 2, &corrupt, 1, inverter_does_not_check };
    scenario_t sc_ref2 = { "nc-002-ref2", 3000u, release, 3, NULL, 0, inverter_does_not_check };
    scenario_t sc2 = { "nc-002-repeat", 3000u, release, 3, &repeat, 1, inverter_does_not_check };
    int over_ms = 0;
    double max_excess;
    int n;

    (void)scenario_run(&sc_ref1, log_ref, LOG_CAP);
    n = scenario_run(&sc1, log_buf, LOG_CAP);
    max_excess = accel_excess(log_buf, log_ref, n, &over_ms);
    CHECK(max_excess > 1.0);
    CHECK(over_ms > 200);
    printf("  측정 대조 (inverter가 검사하지 않음, 값이 바뀜): 가속의 차이는 가장 클 때 %.2f m/s^2, "
           "1.0 m/s^2를 넘은 시간 %d ms\n", max_excess, over_ms);

    (void)scenario_run(&sc_ref2, log_ref, LOG_CAP);
    n = scenario_run(&sc2, log_buf, LOG_CAP);
    max_excess = accel_excess(log_buf, log_ref, n, &over_ms);
    CHECK(max_excess > 1.0);
    CHECK(over_ms > 200);
    printf("  측정 대조 (inverter가 검사하지 않음, 되풀이): 가속의 차이는 가장 클 때 %.2f m/s^2, "
           "1.0 m/s^2를 넘은 시간 %d ms\n", max_excess, over_ms);
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
        { "NC-002", "대조: inverter가 메시지를 검사하지 않으면 SG-01을 어긴다", nc_002 },
    };
    return (test_run_all(cases, (int)(sizeof(cases) / sizeof(cases[0]))) == 0) ? 0 : 1;
}
