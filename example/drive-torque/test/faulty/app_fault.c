/*
 * 결함이 있는 기능 모듈의 구현.
 * 정상인 기능 (src/app/app.c)은 소스를 고치지 않고 함수 이름만 바꿔 compile한 것을 부른다
 * (Makefile의 -Dapp_init=app_good_init -Dapp_step=app_good_step).
 */
#include "app_fault.h"

#include "app.h"

void app_good_init(app_t *st);
torque_t app_good_step(app_t *st, permille_t pedal, bool brake, gear_t gear, torque_t limit);

static app_fault_mode_t fault_mode = APP_FAULT_NONE;
static torque_t fault_offset = 0;

void app_fault_set(app_fault_mode_t mode, torque_t offset)
{
    fault_mode = mode;
    fault_offset = offset;
}

void app_init(app_t *st)
{
    app_good_init(st);
}

torque_t app_step(app_t *st, permille_t pedal, bool brake, gear_t gear, torque_t limit)
{
    torque_t good = app_good_step(st, pedal, brake, gear, limit);

    if (fault_mode == APP_FAULT_OFFSET) {
        return good + fault_offset;
    }
    if (fault_mode == APP_FAULT_HALF) {
        return good / 2;
    }
    if (fault_mode == APP_FAULT_FULL) {
        return (gear == GEAR_R) ? -TORQUE_MAX : TORQUE_MAX;
    }
    return good;
}
