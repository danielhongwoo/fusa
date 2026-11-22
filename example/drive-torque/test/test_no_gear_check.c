/*
 * 책의 예제 코드다. 실제 제품에 쓸 수 없다.
 * 대조 test: 방향의 판정을 뺀 VCU에 FI-17과 같은 입력을 넣는다.
 * 방향의 판정을 아무것도 하지 않는 모듈 (test/faulty/gear_none.c)로 바꿔 끼워 link한다.
 *
 * 이 test가 보이는 것: 달리는 중에 기어가 R로 바뀌는 것을 막지 않으면 SG-02의 첫째 구절을 어긴다.
 * 그래서 test_scenario.c의 TC-116이 "지켜졌다"고 한 것은 방향의 판정이 한 일이다.
 * 요구사항을 검증하는 test가 아니므로 추적에 넣지 않는다 (ID는 NC-로 시작한다).
 */
#include <stddef.h>

#include "scenario.h"
#include "test.h"

#define LOG_CAP 6000
static sample_t log_fault[LOG_CAP];
static sample_t log_ref[LOG_CAP];

#define T_PEDAL_ON 200u
#define T_CHANGE   3000u

/* NC-003: 방향의 판정이 없으면 달리는 차에 반대 방향의 토크가 걸리고, SG-02를 어긴다 */
static void nc_003(void)
{
    /* 기준: 같은 때에 가속 페달을 놓고 타력으로 간다 */
    static const driver_point_t coast[] = {
        { 0u, 0.0, false, GEAR_D },
        { T_PEDAL_ON, 1.0, false, GEAR_D },
        { T_CHANGE, 0.0, false, GEAR_D },
    };
    /* 가속 페달을 밟은 채 기어가 R로 바뀐다 */
    static const driver_point_t change[] = {
        { 0u, 0.0, false, GEAR_D },
        { T_PEDAL_ON, 1.0, false, GEAR_D },
        { T_CHANGE, 1.0, false, GEAR_R },
    };
    scenario_t sc_ref = { "no-gear-check-ref", 4000u, coast, 3, NULL, 0, NULL };
    scenario_t sc = { "no-gear-check", 4000u, change, 3, NULL, 0, NULL };
    int n_ref = scenario_run(&sc_ref, log_ref, LOG_CAP);
    int n = scenario_run(&sc, log_fault, LOG_CAP);
    int over_ms = 0;
    double max_decel = 0.0;

    CHECK_EQ(n, n_ref);
    for (int i = 0; i < n; i++) {
        /* 타력 주행보다 얼마나 더 감속하는가 */
        double decel = log_ref[i].accel_mps2 - log_fault[i].accel_mps2;
        if (decel > max_decel) {
            max_decel = decel;
        }
        if (decel > 1.0) {
            over_ms++;
        }
    }
    /* SG-02의 가정값: 1.0 m/s^2 넘는 감속이 200 ms 넘게 이어지면 안 된다. 여기서는 어긴다 */
    CHECK(log_fault[T_CHANGE - 1u].speed_mps > 5.0);
    CHECK(log_fault[n - 1].torque_out < 0);
    CHECK(max_decel > 1.0);
    CHECK(over_ms > 200);
    printf("  측정 대조 (방향의 판정 없음): 타력 주행과 견준 감속은 가장 클 때 %.2f m/s^2, 1.0 m/s^2를 넘은 시간 %d ms\n",
           max_decel, over_ms);
    (void)scenario_write_csv("build/out/no-gear-check.csv", log_fault, n);
}

int main(void)
{
    static const test_case_t cases[] = {
        { "NC-003", "대조: 방향의 판정이 없으면 SG-02를 어긴다", nc_003 },
    };
    return (test_run_all(cases, (int)(sizeof(cases) / sizeof(cases[0]))) == 0) ? 0 : 1;
}
