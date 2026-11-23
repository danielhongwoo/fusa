/*
 * 대조 test: 감시를 뺀 VCU에 FI-02와 같은 fault를 넣는다.
 * 감시와 출력 단계를 아무것도 하지 않는 모듈 (test/faulty/monitor_none.c)로 바꿔 끼워 link한다.
 *
 * 이 test가 보이는 것: 이 fault는 막지 않으면 SG-01을 어긴다.
 * 그래서 test_fault_app.c의 "SG-01이 지켜졌다"는 감시가 한 일이다.
 * 요구사항을 검증하는 test가 아니므로 추적에 넣지 않는다 (ID는 NC-로 시작한다).
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

static bool fault_enabled;

static void switch_fault_on(time_ms_t t_ms)
{
    if (fault_enabled && (t_ms == T_FAULT)) {
        app_fault_set(APP_FAULT_OFFSET, 1000); /* 100 Nm */
    }
}

/* NC-001: 감시가 없으면 기능의 큰 토크 요구가 그대로 나가고, SG-01을 어긴다 */
static void nc_001(void)
{
    static const driver_point_t driver[] = {
        { 0u, 0.0, false, GEAR_D },
        { T_PEDAL_ON, 0.3, false, GEAR_D },
    };
    scenario_t sc = { "no-monitor", 3000u, driver, 2, NULL, 0, switch_fault_on };
    int n_ref;
    int n;
    int excess_ms = 0;
    double max_excess = 0.0;

    app_fault_set(APP_FAULT_NONE, 0);
    fault_enabled = false;
    n_ref = scenario_run(&sc, log_ref, LOG_CAP);
    fault_enabled = true;
    n = scenario_run(&sc, log_fault, LOG_CAP);
    app_fault_set(APP_FAULT_NONE, 0);

    CHECK_EQ(n, n_ref);
    for (int i = 0; i < n; i++) {
        double excess = log_fault[i].accel_mps2 - log_ref[i].accel_mps2;
        if (excess > max_excess) {
            max_excess = excess;
        }
        if (excess > 1.0) {
            excess_ms++;
        }
    }
    /* SG-01의 가정값: 1.0 m/s^2 넘는 차이가 200 ms 넘게 이어지면 안 된다. 여기서는 어긴다 */
    CHECK(max_excess > 1.0);
    CHECK(excess_ms > 200);
    CHECK_EQ(log_fault[n - 1].torque_out, 750 + 1000);
    printf("  측정 대조 (감시 없음): 가속의 차이는 가장 클 때 %.2f m/s^2, 1.0 m/s^2를 넘은 시간 %d ms\n",
           max_excess, excess_ms);
    (void)scenario_write_csv("build/out/no-monitor.csv", log_fault, n);
}

extern bool monitor_none_keeps_limit;

/*
 * TC-127: SWR-20 fault injection FI-26
 * 출력 단계가 토크 요구를 깎지 않는다 (감시의 결함). 그 상태에서 기능이 100 Nm 더 큰 토크를 요구한다 (fault 둘).
 * 감시는 허용 토크를 옳게 계산했으므로, 주기의 끝에서 보낸 토크가 허용 토크를 넘은 것이 드러난다.
 * 외부 watchdog에 가는 답이 틀리게 나오고, watchdog이 구동 허용 신호를 끊는다.
 * 기능의 고장만 있을 때 (FI-02)와 달리 넘는 토크 요구가 inverter에 간다. 구동 허용 신호가 1 ms 뒤에 끊겨서
 * 모터의 토크는 거의 오르지 못한다.
 */
static void tc_127(void)
{
    static const driver_point_t driver[] = {
        { 0u, 0.0, false, GEAR_D },
        { T_PEDAL_ON, 0.3, false, GEAR_D },
    };
    scenario_t sc = { "fi-26", 3000u, driver, 2, NULL, 0, switch_fault_on };
    int n_ref;
    int n;
    int excess_ms = 0;
    int t_trip = -1;
    double max_excess = 0.0;

    monitor_none_keeps_limit = true;
    app_fault_set(APP_FAULT_NONE, 0);
    fault_enabled = false;
    n_ref = scenario_run(&sc, log_ref, LOG_CAP);
    /* 기능이 정상이면 깎을 것이 없으므로 이 결함은 드러나지 않는다 (숨은 고장) */
    CHECK(!log_ref[n_ref - 1].watchdog_tripped);
    CHECK_EQ(log_ref[n_ref - 1].torque_out, 750);
    fault_enabled = true;
    n = scenario_run(&sc, log_fault, LOG_CAP);
    app_fault_set(APP_FAULT_NONE, 0);
    monitor_none_keeps_limit = false;

    CHECK_EQ(n, n_ref);
    for (int i = 0; i < n; i++) {
        double excess = log_fault[i].accel_mps2 - log_ref[i].accel_mps2;
        if (excess > max_excess) {
            max_excess = excess;
        }
        if (excess > 1.0) {
            excess_ms++;
        }
        if ((t_trip < 0) && log_fault[i].watchdog_tripped) {
            t_trip = (int)log_fault[i].t_ms;
        }
    }
    /* 넘는 토크를 보낸 바로 그 주기에 답이 틀리게 나가고 watchdog이 끊는다 */
    CHECK_EQ(t_trip, (int)T_FAULT);
    CHECK_EQ(log_fault[T_FAULT].torque_out, 750 + 1000); /* 깎이지 않은 토크가 그 주기에 나갔다 */
    CHECK(log_fault[n - 1].torque_act_nm < 0.01);
    CHECK(max_excess < 1.0);
    CHECK_EQ(excess_ms, 0);
    /* watchdog이 끊은 것은 다음 주기의 되읽기 (SWR-21)에서 드러난다: 허용이라고 썼는데 끊김으로 읽힌다 */
    CHECK_EQ(log_fault[T_FAULT + 9u].warning, 0);
    CHECK_EQ(log_fault[T_FAULT + 10u].warning, 2);
    CHECK(log_fault[T_FAULT + 10u].diag.latched);
    printf("  측정 FI-26: fault부터 watchdog이 끊을 때까지 %d ms, 가속의 차이는 가장 클 때 %.2f m/s^2, "
           "1.0 m/s^2를 넘은 시간 %d ms\n", t_trip - (int)T_FAULT, max_excess, excess_ms);
}

int main(void)
{
    static const test_case_t cases[] = {
        { "NC-001", "대조: 감시가 없으면 SG-01을 어긴다", nc_001 },
        { "TC-127", "FI-26 출력 단계가 깎지 않고 기능이 큰 토크를 요구함 (fault 둘)", tc_127 },
    };
    return (test_run_all(cases, (int)(sizeof(cases) / sizeof(cases[0]))) == 0) ? 0 : 1;
}
