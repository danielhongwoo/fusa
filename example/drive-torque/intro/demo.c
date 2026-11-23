/*
 * 1장의 실행 예: 페달 센서의 채널 1이 고착된 뒤 운전자가 페달을 놓는다.
 *
 * 같은 시나리오를 두 제어기로 돌린다. 어느 제어기인지는 link할 때 정해진다.
 *   build/intro_naive  안전 장치가 없는 제어기 (intro/naive_vcu.c)
 *   build/intro_vcu    이 책의 예제 제어기 (src/)
 * 실행하면 기록을 CSV로 쓰고, 기대한 결과가 아니면 실패한다.
 *
 *   사용법: intro_xxx <naive|vcu> <CSV 경로>
 */
#include <stdio.h>
#include <string.h>

#include "scenario.h"

#define LOG_CAP 8000
static sample_t log_buf[LOG_CAP];

#define T_PEDAL_ON 1000u /* 운전자가 페달을 30% 밟는다 */
#define T_FAULT    3000u /* 채널 1이 그때의 값에 고착된다 */
#define T_RELEASE  4000u /* 운전자가 페달을 놓는다 */
#define T_END      8000u

/* 안전 장치가 없는 제어기에는 외부 watchdog도 없다 */
static void no_watchdog(time_ms_t t_ms)
{
    if (t_ms == 0u) {
        hal_sim_watchdog_present(false);
    }
}

int main(int argc, char **argv)
{
    static const driver_point_t driver[] = {
        { 0u, 0.0, false, GEAR_D },
        { T_PEDAL_ON, 0.3, false, GEAR_D },
        { T_RELEASE, 0.0, false, GEAR_D },
    };
    static const fault_event_t faults[] = {
        { T_FAULT, FAULT_APPS1_STUCK, 0 },
    };
    scenario_t sc = { "stuck-pedal", T_END, driver, 3, faults, 1, NULL };
    int naive;
    int n;
    double v_release;
    double v_end;
    int ok;

    if ((argc != 3) || ((strcmp(argv[1], "naive") != 0) && (strcmp(argv[1], "vcu") != 0))) {
        fprintf(stderr, "사용법: %s <naive|vcu> <CSV 경로>\n", argv[0]);
        return 2;
    }
    naive = (strcmp(argv[1], "naive") == 0);
    if (naive) {
        sc.on_tick = no_watchdog;
    }

    n = scenario_run(&sc, log_buf, LOG_CAP);
    if (scenario_write_csv(argv[2], log_buf, n) != 0) {
        fprintf(stderr, "CSV를 쓰지 못했다: %s\n", argv[2]);
        return 2;
    }

    v_release = log_buf[T_RELEASE].speed_mps;
    v_end = log_buf[n - 1].speed_mps;
    printf("%s: 페달을 놓을 때 %.1f km/h, 4초 뒤 %.1f km/h, 그때의 토크 요구 %.1f Nm\n",
           naive ? "안전 장치가 없는 제어기" : "예제의 제어기",
           v_release * 3.6, v_end * 3.6, (double)log_buf[n - 1].torque_out / 10.0);

    if (naive) {
        /* 페달을 놓았는데도 토크가 그대로이고 차가 계속 빨라진다 */
        ok = (log_buf[n - 1].torque_out == 750) && (v_end > (v_release + 3.0));
    } else {
        /* 페달을 놓은 뒤 50 ms 안에 토크 요구가 0이 되고 차는 더 빨라지지 않는다 */
        ok = (log_buf[T_RELEASE + 50u].torque_out == 0) && (log_buf[n - 1].torque_out == 0)
             && (v_end <= v_release + 0.1);
    }
    if (!ok) {
        fprintf(stderr, "기대한 결과가 아니다\n");
        return 1;
    }
    return 0;
}
