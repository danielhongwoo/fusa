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
    };
    return (test_run_all(cases, (int)(sizeof(cases) / sizeof(cases[0]))) == 0) ? 0 : 1;
}
