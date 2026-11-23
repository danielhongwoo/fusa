/*
 * 대조 test: 실행의 확인 (SWR-20)을 뺀 VCU.
 * 실행의 순서를 보지 않고 늘 옳은 답을 내는 모듈 (test/faulty/flow_none.c)로 바꿔 끼워 link한다.
 * 주기마다 정해진 값을 써 주기만 하면 되는 단순한 watchdog을 쓰는 것과 같다.
 *
 * 이 test가 보이는 것: 입력을 읽는 task가 실행되지 않는데 답이 계속 나가면, watchdog은 끊지 않고
 * VCU는 지난 입력으로 토크를 계속 낸다. 운전자가 페달을 놓아도 토크가 그대로여서 SG-01을 어긴다.
 * 그래서 test_scenario.c의 TC-124가 "SG-01이 지켜졌다"고 한 것은 실행의 확인과 watchdog이 한 일이다.
 * 요구사항을 검증하는 test가 아니므로 추적에 넣지 않는다 (ID는 NC-로 시작한다).
 */
#include <stddef.h>

#include "scenario.h"
#include "test.h"

#define LOG_CAP 4000
static sample_t log_fault[LOG_CAP];
static sample_t log_ref[LOG_CAP];

#define T_PEDAL_ON 200u
#define T_FAULT    2000u
#define T_RELEASE  2100u

/* NC-005: 실행의 순서를 보지 않으면 입력 task가 멈춘 것을 아무도 알지 못한다 */
static void nc_005(void)
{
    static const driver_point_t driver[] = {
        { 0u, 0.0, false, GEAR_D },
        { T_PEDAL_ON, 0.3, false, GEAR_D },
        { T_RELEASE, 0.0, false, GEAR_D },
    };
    fault_event_t fault = { T_FAULT, FAULT_TASK_SKIP, 0 };
    scenario_t sc_ref = { "no-flow-check-ref", 3000u, driver, 3, NULL, 0, NULL };
    scenario_t sc = { "no-flow-check", 3000u, driver, 3, &fault, 1, NULL };
    int n_ref = scenario_run(&sc_ref, log_ref, LOG_CAP);
    int n = scenario_run(&sc, log_fault, LOG_CAP);
    int over_ms = 0;
    double max_excess = 0.0;

    CHECK_EQ(n, n_ref);
    for (int i = 0; i < n; i++) {
        double excess = log_fault[i].accel_mps2 - log_ref[i].accel_mps2;
        if (excess > max_excess) {
            max_excess = excess;
        }
        if (excess > 1.0) {
            over_ms++;
        }
    }
    /* watchdog은 끊지 않았고, 페달을 놓은 뒤에도 토크가 그대로 나간다 */
    CHECK(!log_fault[n - 1].watchdog_tripped);
    CHECK_EQ(log_fault[n - 1].torque_out, 750);
    CHECK(max_excess > 1.0);
    CHECK(over_ms > 200);
    printf("  측정 대조 (실행의 확인 없음, 입력 task가 멈춤): 가속의 차이는 가장 클 때 %.2f m/s^2, "
           "1.0 m/s^2를 넘은 시간 %d ms\n", max_excess, over_ms);
    (void)scenario_write_csv("build/out/no-flow-check.csv", log_fault, n);
}

int main(void)
{
    static const test_case_t cases[] = {
        { "NC-005", "대조: 실행의 순서를 보지 않으면 SG-01을 어긴다", nc_005 },
    };
    return (test_run_all(cases, (int)(sizeof(cases) / sizeof(cases[0]))) == 0) ? 0 : 1;
}
