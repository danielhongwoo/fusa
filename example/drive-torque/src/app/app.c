/*
 * 책의 예제 코드다. 실제 제품에 쓸 수 없다.
 * 기능의 구현.
 */
#include "app.h"

#include "input.h"

#define BASE_SPEED          ((speed_t)1500)  /* 15 m/s. 이 속도 위에서는 토크를 줄인다 */
#define SPEED_MAX           ((speed_t)6000)  /* 계산에 쓰는 속도의 상한 */
#define REVERSE_PERCENT     ((int32_t)40)    /* 후진은 전진 토크의 40%까지 */
#define RISE_PER_CYCLE      ((torque_t)100)  /* 한 주기에 올릴 수 있는 토크: 10 Nm */

void app_init(app_t *st)
{
    st->prev = 0;
    st->brake_override = false;
}

/* 지금 속도에서 낼 수 있는 최대 토크. 높은 속도에서는 출력이 일정하도록 줄인다 */
static torque_t max_torque_at(bool speed_valid, speed_t speed)
{
    speed_t s = (speed < 0) ? -speed : speed;
    if (!speed_valid) {
        return TORQUE_MAX / 2; /* 속도를 모르면 절반만 쓴다 */
    }
    if (s > SPEED_MAX) {
        s = SPEED_MAX;
    }
    if (s <= BASE_SPEED) {
        return TORQUE_MAX;
    }
    return (TORQUE_MAX * BASE_SPEED) / s;
}

torque_t app_step(app_t *st, permille_t pedal, bool brake, gear_t gear,
                  bool speed_valid, speed_t speed)
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
        target = (p * max_torque_at(speed_valid, speed)) / PEDAL_FULL;
        if (gear == GEAR_R) {
            target = -((target * REVERSE_PERCENT) / 100);
        }
    }

    /* 토크는 천천히 올리고, 내릴 때는 바로 내린다 */
    if ((target > 0) && (target > (st->prev + RISE_PER_CYCLE))) {
        target = (st->prev > 0) ? (st->prev + RISE_PER_CYCLE) : RISE_PER_CYCLE;
    }
    if ((target < 0) && (target < (st->prev - RISE_PER_CYCLE))) {
        target = (st->prev < 0) ? (st->prev - RISE_PER_CYCLE) : -RISE_PER_CYCLE;
    }
    st->prev = target;
    return target;
}
