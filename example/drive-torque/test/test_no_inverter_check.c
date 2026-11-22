/*
 * 책의 예제 코드다. 실제 제품에 쓸 수 없다.
 * 대조 test: inverter가 알린 토크의 검사 (SWR-19)를 뺀 VCU.
 * 그 검사를 아무것도 하지 않는 모듈 (test/faulty/inverter_check_none.c)로 바꿔 끼워 link한다.
 *
 * 이 test가 보이는 것
 *   NC-002: inverter가 메시지를 검사하지 않고 (가정 A-21이 틀리고) VCU의 검사도 없으면,
 *           전송 중에 바뀐 토크 요구와 되풀이된 옛 토크 요구가 SG-01을 어긴다.
 *   NC-004: inverter가 요구보다 크게 내는 고장은 VCU의 검사가 없으면 SG-01을 어긴다.
 * 그래서 test_scenario.c의 TC-112, TC-113, TC-120, TC-121이 "SG-01이 지켜졌다"고 한 것은
 * 메시지의 보호와 inverter의 검사, 그리고 VCU의 검사가 한 일이다.
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

static const driver_point_t hold[] = {
    { 0u, 0.0, false, GEAR_D },
    { T_PEDAL_ON, 0.3, false, GEAR_D },
};
static const driver_point_t release[] = {
    { 0u, 0.0, false, GEAR_D },
    { T_PEDAL_ON, 0.3, false, GEAR_D },
    { T_FAULT, 0.0, false, GEAR_D },
};

static void inverter_does_not_check(time_ms_t t_ms)
{
    if (t_ms == 0u) {
        hal_sim_inverter_check(false);
    }
}

/* 고장이 없는 실행과 견준 가속의 차이. 가장 큰 값을 돌려주고, 1.0 m/s^2를 넘은 시간을 over_ms에 적는다 */
static double accel_excess(const scenario_t *sc_ref, const scenario_t *sc, int *over_ms)
{
    int n_ref = scenario_run(sc_ref, log_ref, LOG_CAP);
    int n = scenario_run(sc, log_fault, LOG_CAP);
    double max_excess = 0.0;

    CHECK_EQ(n, n_ref);
    *over_ms = 0;
    for (int i = 0; i < n; i++) {
        double excess = log_fault[i].accel_mps2 - log_ref[i].accel_mps2;
        if (excess > max_excess) {
            max_excess = excess;
        }
        if (excess > 1.0) {
            (*over_ms)++;
        }
    }
    /* VCU는 끝까지 아무것도 알지 못한다 */
    CHECK(!log_fault[n - 1].diag.latched);
    CHECK(log_fault[n - 1].enable);
    CHECK_EQ(log_fault[n - 1].warning, 0);
    return max_excess;
}

/* NC-002: inverter도 VCU도 검사하지 않으면 전송 중의 고장이 SG-01을 어긴다 */
static void nc_002(void)
{
    fault_event_t corrupt = { T_FAULT, FAULT_TORQUE_MSG_CORRUPT, 1000 };
    fault_event_t repeat = { T_FAULT - 5u, FAULT_TORQUE_MSG_REPEAT, 0 };
    scenario_t sc_ref1 = { "nc-002-ref1", 3000u, hold, 2, NULL, 0, inverter_does_not_check };
    scenario_t sc1 = { "nc-002-corrupt", 3000u, hold, 2, &corrupt, 1, inverter_does_not_check };
    scenario_t sc_ref2 = { "nc-002-ref2", 3000u, release, 3, NULL, 0, inverter_does_not_check };
    scenario_t sc2 = { "nc-002-repeat", 3000u, release, 3, &repeat, 1, inverter_does_not_check };
    int over_ms = 0;
    double max_excess;

    max_excess = accel_excess(&sc_ref1, &sc1, &over_ms);
    CHECK(max_excess > 1.0);
    CHECK(over_ms > 200);
    printf("  측정 대조 (검사가 어디에도 없음, 값이 바뀜): 가속의 차이는 가장 클 때 %.2f m/s^2, "
           "1.0 m/s^2를 넘은 시간 %d ms\n", max_excess, over_ms);

    max_excess = accel_excess(&sc_ref2, &sc2, &over_ms);
    CHECK(max_excess > 1.0);
    CHECK(over_ms > 200);
    printf("  측정 대조 (검사가 어디에도 없음, 되풀이): 가속의 차이는 가장 클 때 %.2f m/s^2, "
           "1.0 m/s^2를 넘은 시간 %d ms\n", max_excess, over_ms);
}

/* NC-004: VCU의 검사가 없으면 inverter가 요구보다 크게 내는 고장이 SG-01을 어긴다 */
static void nc_004(void)
{
    fault_event_t offset = { T_FAULT, FAULT_INVERTER_TORQUE_OFFSET, 1000 };
    scenario_t sc_ref = { "nc-004-ref", 3000u, hold, 2, NULL, 0, NULL };
    scenario_t sc = { "nc-004", 3000u, hold, 2, &offset, 1, NULL };
    int over_ms = 0;
    double max_excess = accel_excess(&sc_ref, &sc, &over_ms);

    CHECK(max_excess > 1.0);
    CHECK(over_ms > 200);
    printf("  측정 대조 (VCU의 검사 없음, inverter가 100 Nm 더 냄): 가속의 차이는 가장 클 때 %.2f m/s^2, "
           "1.0 m/s^2를 넘은 시간 %d ms\n", max_excess, over_ms);
}

int main(void)
{
    static const test_case_t cases[] = {
        { "NC-002", "대조: 메시지를 검사하는 곳이 없으면 SG-01을 어긴다", nc_002 },
        { "NC-004", "대조: inverter가 알린 토크를 검사하지 않으면 SG-01을 어긴다", nc_004 },
    };
    return (test_run_all(cases, (int)(sizeof(cases) / sizeof(cases[0]))) == 0) ? 0 : 1;
}
