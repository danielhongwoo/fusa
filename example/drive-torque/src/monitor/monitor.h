/*
 * 책의 예제 코드다. 실제 제품에 쓸 수 없다.
 * 감시와 출력 단계.
 * 감시는 기능을 다시 계산하지 않는다. 운전자의 입력에서 토크의 상한만 따로 계산한다.
 * 출력 단계는 토크 요구를 그 상한으로 깎고, 기능이 계속 틀리면 구동을 막는다.
 *
 * 주의: 감시가 기능과 다른 함수에 있다고 해서 독립적인 것은 아니다.
 * 같은 MCU, 같은 메모리, 같은 입력을 쓴다 (docs/technical-safety-concept.md).
 */
#ifndef MONITOR_H
#define MONITOR_H

#include "types.h"

#define TORQUE_TOLERANCE    ((torque_t)50)  /* 허용 오차: 5 Nm */
#define ALLOWED_REVERSE_PCT ((int32_t)40)   /* 후진의 허용 토크는 전진의 40%. 기능의 값과 따로 둔다 */
#define EXCESS_LATCH_CYCLES ((uint8_t)5)    /* 초과가 이만큼 이어지면 기능의 고장으로 고정 */
/* 허용 토크가 한 주기에 오를 수 있는 양: 25 Nm.
 * 기능이 토크를 올리는 속도와 같아야 한다. 더 크면 그 차이만큼 틈이 주기마다 쌓이고,
 * 더 작으면 정상인 기능이 깎인다. 기능의 값과 따로 둔다 (TC-012, TC-013이 어긋남을 잡는다) */
#define ALLOWED_RISE_PER_CYCLE ((torque_t)250)

/* 출력 단계의 상태 */
typedef struct {
    uint8_t excess_cycles; /* 토크 요구가 허용 범위를 벗어난 주기가 몇 번 이어졌는가 */
    uint32_t clamp_count;  /* 깎은 횟수 (진단용) */
    bool latched;          /* 기능의 고장으로 고정했는가. 다시 켤 때까지 유지한다 */
    torque_t last_out;     /* 지난 주기에 inverter로 보낸 토크 */
} output_stage_t;

/* 허용 토크의 크기 (0 이상) */
torque_t monitor_allowed_torque(permille_t pedal_safe, bool brake, gear_t gear);

/* 허용 토크가 오르는 속도를 제한한다. last_out은 지난 주기에 보낸 토크다 */
torque_t monitor_limit_rise(torque_t allowed, torque_t last_out, gear_t gear);

/* 토크 요구를 허용 범위 안으로 깎는다. 방향은 기어가 정한다 */
torque_t output_clamp(torque_t torque_req, torque_t allowed, gear_t gear);

void output_stage_init(output_stage_t *st);

/*
 * 한 주기의 출력을 정한다: 깎고, 초과가 이어지는지 세고, 고정 여부를 정한다.
 * 돌려주는 값은 inverter로 보낼 토크다. 고정된 뒤에는 0이다.
 */
torque_t output_stage_step(output_stage_t *st, torque_t torque_req, torque_t allowed, gear_t gear);

#endif
