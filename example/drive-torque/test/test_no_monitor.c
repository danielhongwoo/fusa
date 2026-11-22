/*
 * 책의 예제 코드다. 실제 제품에 쓸 수 없다.
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

int main(void)
{
    static const test_case_t cases[] = {
        { "NC-001", "대조: 감시가 없으면 SG-01을 어긴다", nc_001 },
    };
    return (test_run_all(cases, (int)(sizeof(cases) / sizeof(cases[0]))) == 0) ? 0 : 1;
}
