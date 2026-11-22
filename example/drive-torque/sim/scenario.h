/*
 * 책의 예제 코드다. 실제 제품에 쓸 수 없다.
 * 시나리오 실행기: 운전자의 입력과 fault를 시간표대로 넣고, VCU와 plant를 함께 돌린다.
 *
 * 시간 모델 (1 ms마다 아래 순서)
 *   1. 운전자의 입력을 적용한다
 *   2. fault를 적용한다
 *   3. 센서 값과 주기 메시지를 갱신한다
 *   4. 주기가 된 task를 task table의 순서대로 부른다
 *   5. plant를 1 ms 진행한다
 *   6. 기록한다
 * task의 실행 시간은 0이다. jitter와 마감 초과는 흉내 내지 않는다.
 * task가 실행되지 않거나 주기가 늘어지는 고장은 4에서 넣는다 (FAULT_TASK_SKIP, FAULT_TASK_STOP, FAULT_TASK_SLOW).
 */
#ifndef SCENARIO_H
#define SCENARIO_H

#include "hal_sim.h"

/* 운전자의 입력. 다음 점이 나올 때까지 유지된다 */
typedef struct {
    time_ms_t t_ms;
    double pedal; /* 0.0 - 1.0 */
    bool brake;
    gear_t gear;
} driver_point_t;

typedef struct {
    time_ms_t t_ms;
    fault_id_t fault;
    int32_t param;
} fault_event_t;

typedef struct {
    const char *name;
    time_ms_t duration_ms;
    const driver_point_t *driver;
    int driver_count;
    const fault_event_t *faults;
    int fault_count;
    void (*on_tick)(time_ms_t t_ms); /* 없으면 NULL. 모듈을 바꿔 끼운 test가 결함을 켜는 데 쓴다 */
} scenario_t;

/* 1 ms마다의 기록. VCU의 값은 HAL로 나온 것만 적는다 */
typedef struct {
    time_ms_t t_ms;
    double pedal;
    bool brake;
    gear_t gear;
    millivolt_t apps1_mv;
    millivolt_t apps2_mv;
    torque_t torque_out;
    bool enable;
    uint8_t warning;
    hal_diag_t diag;
    bool watchdog_tripped; /* 외부 watchdog이 구동 허용 신호를 끊었는가 */
    double torque_act_nm;
    double speed_mps;
    double accel_mps2;
} sample_t;

/* 시나리오를 돌리고 기록한 줄의 수를 돌려준다. log_cap이 모자라면 앞부분만 기록한다 */
int scenario_run(const scenario_t *sc, sample_t *log, int log_cap);

/* 기록을 CSV로 쓴다. 성공하면 0 */
int scenario_write_csv(const char *path, const sample_t *log, int count);

#endif
