/*
 * 책의 예제 코드다. 실제 제품에 쓸 수 없다.
 * 감시와 출력 단계의 구현. 계산은 모두 정수다.
 */
#include "monitor.h"

#include "input.h"

torque_t monitor_allowed_torque(permille_t pedal_safe, bool brake, gear_t gear)
{
    permille_t p = pedal_safe;
    torque_t allowed;

    /* 곱하기 전에 범위로 자른다 */
    if (p < 0) {
        p = 0;
    }
    if (p > PEDAL_FULL) {
        p = PEDAL_FULL;
    }

    /* SWR-05: 페달을 놓았거나, 브레이크를 밟았거나, 기어가 P나 N이면 허용 토크는 0이다 */
    if ((p < PEDAL_RELEASED) || brake || ((gear != GEAR_D) && (gear != GEAR_R))) {
        return 0;
    }

    /* SWR-06: 허용 토크는 페달 위치에 비례하는 상한에 오차를 더한 값이다.
     * 후진에서는 상한이 전진의 40%다 */
    allowed = (p * TORQUE_MAX) / PEDAL_FULL;
    if (gear == GEAR_R) {
        allowed = (allowed * ALLOWED_REVERSE_PCT) / 100;
    }
    allowed += TORQUE_TOLERANCE;
    if (allowed > TORQUE_MAX) {
        allowed = TORQUE_MAX;
    }
    return allowed;
}

torque_t monitor_limit_rise(torque_t allowed, torque_t last_out, gear_t gear)
{
    torque_t from = 0;
    torque_t limit;

    /* SWR-13: 허용 토크는 지난 주기에 보낸 토크의 크기에서 한 주기에 25 Nm까지만 오른다.
     * 지난 주기에 보낸 토크가 지금 기어의 방향과 반대이면 0에서 다시 센다.
     * 기준이 감시의 지난 허용값이 아니라 실제로 보낸 값이므로, 기능이 가진 상태를 베끼지 않는다 */
    if (gear == GEAR_D) {
        if (last_out > 0) {
            from = (last_out > TORQUE_MAX) ? TORQUE_MAX : last_out;
        }
    } else if (gear == GEAR_R) {
        if (last_out < 0) {
            from = (last_out < -TORQUE_MAX) ? TORQUE_MAX : -last_out;
        }
    } else {
        /* P와 N에서는 0에서 센다 */
    }
    limit = from + ALLOWED_RISE_PER_CYCLE;
    return (allowed < limit) ? allowed : limit;
}

torque_t output_clamp(torque_t torque_req, torque_t allowed, gear_t gear)
{
    torque_t lo = 0;
    torque_t hi = 0;

    /* SWR-07: 토크는 기어가 정한 방향으로만, 허용 토크까지만 나간다 */
    if (allowed > 0) {
        if (gear == GEAR_D) {
            hi = allowed;
        } else if (gear == GEAR_R) {
            lo = -allowed;
        } else {
            /* P와 N에서는 토크를 내지 않는다 */
        }
    }
    if (torque_req > hi) {
        return hi;
    }
    if (torque_req < lo) {
        return lo;
    }
    return torque_req;
}

void output_stage_init(output_stage_t *st)
{
    st->excess_cycles = 0u;
    st->clamp_count = 0u;
    st->latched = false;
    st->last_out = 0;
}

torque_t output_stage_step(output_stage_t *st, torque_t torque_req, torque_t allowed, gear_t gear)
{
    torque_t out = output_clamp(torque_req, allowed, gear);

    /* SWR-08: 토크 요구가 허용 범위를 벗어난 주기가 이어지면 기능의 고장으로 고정한다 */
    if (out != torque_req) {
        st->clamp_count++;
        if (st->excess_cycles < EXCESS_LATCH_CYCLES) {
            st->excess_cycles++;
        }
        if (st->excess_cycles >= EXCESS_LATCH_CYCLES) {
            st->latched = true;
        }
    } else {
        st->excess_cycles = 0u;
    }

    /* SWR-09: 고정된 뒤에는 토크 0을 보낸다 */
    if (st->latched) {
        out = 0;
    }
    st->last_out = out;
    return out;
}
