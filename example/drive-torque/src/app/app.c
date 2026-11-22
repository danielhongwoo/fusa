/*
 * 책의 예제 코드다. 실제 제품에 쓸 수 없다.
 * 기능의 구현.
 */
#include "app.h"

#include "input.h"

#define REVERSE_PERCENT     ((int32_t)40)    /* 후진은 전진 토크의 40%까지 */
#define RISE_PER_CYCLE      ((torque_t)250)  /* 한 주기에 올릴 수 있는 토크: 25 Nm */

void app_init(app_t *st)
{
    st->prev = 0;
    st->brake_override = false;
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

    /* 제동 우선: 두 페달을 함께 밟으면 걸리고, 가속 페달을 놓아야 풀린다 */
    if (brake && (p >= PEDAL_RELEASED)) {
        st->brake_override = true;
    }
    if (p < PEDAL_RELEASED) {
        st->brake_override = false;
    }

    if ((p < PEDAL_RELEASED) || brake || st->brake_override
        || ((gear != GEAR_D) && (gear != GEAR_R))) {
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
