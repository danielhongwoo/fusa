/*
 * 책의 예제 코드다. 실제 제품에 쓸 수 없다.
 * 기능의 구현.
 */
#include "app.h"

#include "input.h"

/* 후진은 전진 토크의 40%까지.
 * 감시의 ALLOWED_REVERSE_PCT와 값이 같아야 한다. 일부러 상수를 함께 쓰지 않았다.
 * 함께 쓰면 이 값을 바꿀 때 감시의 한계가 검토 없이 따라 바뀐다.
 * 따로 두면 두 값이 어긋날 때 TC-007이 실패한다 */
#define REVERSE_PERCENT     ((int32_t)40)
#define RISE_PER_CYCLE      ((torque_t)250)  /* 한 주기에 올릴 수 있는 토크: 25 Nm */

void app_init(app_t *st)
{
    st->prev = 0;
}

torque_t app_step(app_t *st, permille_t pedal, bool brake, gear_t gear)
{
    permille_t p = pedal;
    torque_t target;

    if (p < 0) {
        p = 0;
    }
    if (p > PEDAL_FULL) {
        p = PEDAL_FULL;
    }

    /* 제동 우선: 브레이크를 밟는 동안에는 토크를 요구하지 않는다.
     * 걸린 상태를 기억하지 않는다. 기억하면 감시가 모르는 상태가 생기고,
     * 그 상태에서는 허용 토크와 이 모듈의 토크 요구가 크게 벌어진다
     * (docs/technical-safety-concept.md 3절) */
    if ((p < PEDAL_RELEASED) || brake || ((gear != GEAR_D) && (gear != GEAR_R))) {
        target = 0;
    } else {
        target = (p * TORQUE_MAX) / PEDAL_FULL;
        if (gear == GEAR_R) {
            target = -((target * REVERSE_PERCENT) / 100);
        }
    }

    /* 토크는 천천히 올리고, 내릴 때는 바로 내린다.
     * 알려진 단순화: 주행 중에 기어가 D에서 R로 바뀌면 한 주기에 양수에서 음수로 넘어간다.
     * 차량 속도를 보고 막는 것은 하지 않았다 (docs/technical-safety-concept.md 6절) */
    if ((target > 0) && (target > (st->prev + RISE_PER_CYCLE))) {
        target = (st->prev > 0) ? (st->prev + RISE_PER_CYCLE) : RISE_PER_CYCLE;
    }
    if ((target < 0) && (target < (st->prev - RISE_PER_CYCLE))) {
        target = (st->prev < 0) ? (st->prev - RISE_PER_CYCLE) : -RISE_PER_CYCLE;
    }
    st->prev = target;
    return target;
}
