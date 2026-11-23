/*
 * 감시와 출력 단계.
 * 감시는 기능을 다시 계산하지 않는다. 운전자의 입력에서 토크의 상한만 따로 계산한다.
 * 출력 단계는 토크 요구를 그 상한으로 깎고, 기능이 계속 틀리면 그 사건을 고장 대응의 상태 기계에 알린다.
 *
 * 주의: 감시가 기능과 다른 함수에 있다고 해서 독립적인 것은 아니다.
 * 같은 MCU, 같은 메모리, 같은 입력을 쓴다 (docs/technical-safety-concept.md).
 */
#ifndef MONITOR_H
#define MONITOR_H

#include "reaction.h"
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
 * 감시와 출력 단계의 한 주기: 허용 토크를 구하고 (페달에서 나온 상한, 오르는 속도의 상한, 상태가 정한 상한),
 * 토크 요구를 그 안으로 깎고, 보낸 값을 기억한다.
 * 제품 (src/vcu/vcu.c), unit test, 증명이 모두 이 함수 하나를 부른다. 잇는 순서를 따로 옮겨 적지 않으려는 것이다.
 * allowed에 그 주기의 허용 토크를 적고, inverter로 보낼 토크를 돌려준다.
 */
torque_t monitor_output_cycle(output_stage_t *st, reaction_t *reaction, torque_t torque_req,
                              permille_t pedal_safe, bool brake, gear_t gear, torque_t *allowed);

/* 고장 대응의 상태가 정한 상한을 허용 토크에 건다 */
torque_t monitor_apply_cap(torque_t allowed, reaction_state_t state);

/*
 * 한 주기의 출력을 정한다: 깎고, 초과가 이어지는지 세고, 이어지면 기능의 고장이라는 사건을 알린다.
 * 돌려주는 값은 inverter로 보낼 토크다. 고장 대응의 상태가 토크 0이나 구동 허용 차단이면 0이다.
 */
torque_t output_stage_step(output_stage_t *st, reaction_t *reaction, torque_t torque_req,
                           torque_t allowed, gear_t gear);

/* inverter가 알린 토크의 검사. 값은 임시다 */
#define INVERTER_HISTORY_CYCLES  ((uint8_t)5)    /* 보낸 토크를 이만큼 (50 ms) 기억한다 */
#define INVERTER_TORQUE_MARGIN   ((torque_t)300) /* 범위에 더하는 여유: 30.0 Nm */
#define INVERTER_OUT_CYCLES      ((uint8_t)3)    /* 범위를 벗어난 새 메시지가 이만큼 이어지면 구동 허용 차단 */
#define INVERTER_FRESH_WINDOW    ((uint8_t)5)    /* 최근 이만큼의 주기 (50 ms) 가운데 */
#define INVERTER_FRESH_MIN       ((uint8_t)3)    /* 새 상태 메시지를 받은 주기가 이만큼보다 적으면 구동 허용 차단 */

/* 값 셋이 맞물려 있다. 창 안에서 받아야 하는 새 메시지의 수가 판정에 필요한 수보다 적으면,
 * 받아들이는 손실의 모양 가운데 판정이 창보다 오래 걸리는 것이 생긴다. 그러면 "알린 토크가 범위를
 * 벗어난 채이면 창 안에 사건을 알린다"가 깨지고, 시간의 예산 (docs/technical-safety-concept.md 9.4절)이
 * 맞지 않게 된다 (docs/change-impact.md) */
_Static_assert(INVERTER_FRESH_MIN >= INVERTER_OUT_CYCLES,
               "창 안에서 받아야 하는 새 메시지의 수는 판정에 필요한 수보다 적으면 안 된다");
_Static_assert((INVERTER_FRESH_WINDOW >= INVERTER_FRESH_MIN) && (INVERTER_FRESH_WINDOW <= 8u),
               "창은 받아야 하는 수보다 짧을 수 없고, 기록은 8 bit에 담는다");

/* 배열은 구조체의 끝에 둔다. 증명 도구 (CBMC)의 경계 검사는 pointer로 받은 구조체 안의 배열에 대해
 * 구조체의 끝만 본다. 배열 뒤에 다른 필드가 있으면 한 칸 넘는 쓰기가 그 필드에 떨어져도 잡지 못한다
 * (docs/test-report.md 6절. tools/prove.sh가 이 한계를 작은 예로 확인한다) */
typedef struct {
    uint8_t pos;            /* 다음에 적을 자리 */
    uint8_t out_cycles;     /* 알린 토크가 범위를 벗어난 새 메시지가 몇 번 이어졌는가 */
    uint8_t fresh_bits;     /* 최근 주기들에 새 상태 메시지를 받았는가. bit 0이 이번 주기, bit 1이 지난 주기 */
    torque_t sent[INVERTER_HISTORY_CYCLES]; /* 최근 주기들에 보낸 토크 */
} inverter_check_t;

void inverter_check_init(inverter_check_t *st);

/* 이번 주기에 보낸 토크를 기록한다 */
void inverter_check_record(inverter_check_t *st, torque_t sent);

/*
 * inverter가 알린 토크를 지난 주기들에 보낸 토크와 견준다. 구동 허용 차단의 사건이면 참이다.
 *   fresh  이번 주기에 검사를 통과한 새 상태 메시지를 받았는가. 거짓이면 reported를 보지 않는다
 *          (새 메시지가 없으면 reported는 지난 메시지의 값이거나 쓸 수 없는 값이다).
 *          그 주기에는 견주지 않고, 벗어난 횟수를 올리지도 지우지도 않는다
 * 사건은 둘이다: 범위를 벗어난 새 메시지가 이어진다, 새 메시지가 너무 드물게 도착한다.
 */
bool inverter_check_step(inverter_check_t *st, bool fresh, torque_t reported);

#endif
