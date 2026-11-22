/*
 * 책의 예제 코드다. 실제 제품에 쓸 수 없다.
 * 고장 대응의 상태 기계.
 * 고장을 알아챈 모듈은 사건만 알린다 (reaction_raise). 토크의 상한, 구동 허용 신호, 경고 요청은
 * 이 모듈의 상태에서 나온다. 대응이 여러 곳에 흩어져 서로 다투지 않게 하려는 것이다.
 *
 * 상태는 안전한 쪽으로만 바뀐다: 정상 -> 줄여 감 -> 토크 0 -> 구동 허용 차단.
 * 다시 켤 때까지 돌아가지 않는다.
 *
 * 브레이크를 밟은 동안의 토크 0처럼 조건이 풀리면 돌아오는 것은 고장이 아니라 조건이다.
 * 그런 것은 이 기계에 알리지 않는다.
 */
#ifndef REACTION_H
#define REACTION_H

#include "types.h"

typedef enum {
    REACTION_NORMAL = 0, /* 정상 */
    REACTION_LIMP = 1,   /* 줄여 감: 허용 토크에 상한을 건다 */
    REACTION_ZERO = 2,   /* 토크 0. 구동 허용 신호는 유지한다 */
    REACTION_CUT = 3     /* 구동 허용 차단 */
} reaction_state_t;

/* 줄여 감 상태의 토크 상한: 40 Nm.
 * 남은 페달 채널이 틀려도 넘는 토크가 이 값과 inverter의 오차 (10 Nm)의 합이고,
 * SG-01의 한계 (55 Nm)보다 작다 (docs/technical-safety-concept.md 9.3절) */
#define LIMP_TORQUE_CAP ((torque_t)400)

#define WARNING_NONE  ((uint8_t)0)
#define WARNING_AMBER ((uint8_t)1) /* 주의 */
#define WARNING_RED   ((uint8_t)2) /* 경고 */

typedef struct {
    reaction_state_t state;
} reaction_t;

void reaction_init(reaction_t *r);

/* 사건을 알린다. 상태를 wanted보다 안전한 쪽이거나 같게 한다. 덜 안전한 쪽으로는 가지 않는다 */
void reaction_raise(reaction_t *r, reaction_state_t wanted);

/* 지금의 상태. 알 수 없는 값이 들어 있으면 구동 허용 차단으로 본다 */
reaction_state_t reaction_state(const reaction_t *r);

/* 상태에서 나오는 출력 */
torque_t reaction_torque_cap(reaction_state_t state); /* 허용 토크의 상한 */
bool reaction_enable(reaction_state_t state);         /* 구동을 허용하는가 */
uint8_t reaction_warning(reaction_state_t state);     /* 경고 요청 */

#endif
