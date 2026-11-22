/*
 * 책의 예제 코드다. 실제 제품에 쓸 수 없다.
 * 감시가 없는 것과 같은 모듈. test에서만 쓴다.
 * src/monitor/monitor.c 대신 link되어 같은 interface (monitor.h)를 구현한다.
 * 토크 요구를 깎지 않고, 고정하지도 않는다.
 * 쓰는 곳: 감시가 없으면 같은 fault가 safety goal을 어긴다는 것을 보이는 대조 test.
 *
 * monitor_none_keeps_limit이 참이면 허용 토크는 계산해서 알리되 깎지만 않는다.
 * 출력 단계가 깎지 않는 고장을 흉내 낸 것이다 (감시의 결함).
 */
#include "monitor.h"

bool monitor_none_keeps_limit = false;

torque_t monitor_allowed_torque(permille_t pedal_safe, bool brake, gear_t gear)
{
    (void)pedal_safe;
    (void)brake;
    (void)gear;
    return TORQUE_MAX;
}

torque_t monitor_limit_rise(torque_t allowed, torque_t last_out, gear_t gear)
{
    (void)last_out;
    (void)gear;
    return allowed;
}

torque_t monitor_apply_cap(torque_t allowed, reaction_state_t state)
{
    (void)state;
    return allowed;
}

torque_t output_clamp(torque_t torque_req, torque_t allowed, gear_t gear)
{
    (void)allowed;
    (void)gear;
    return torque_req;
}

torque_t monitor_output_cycle(output_stage_t *st, reaction_t *reaction, torque_t torque_req,
                              permille_t pedal_safe, bool brake, gear_t gear, torque_t *allowed)
{
    (void)st;
    (void)reaction;
    (void)brake;
    (void)gear;
    if (monitor_none_keeps_limit) {
        /* 허용 토크는 옳게 계산한다 (페달에 비례하는 값에 오차 5 Nm). 깎지만 않는다 */
        *allowed = ((pedal_safe * TORQUE_MAX) / PEDAL_FULL) + 50;
    } else {
        /* 감시가 없으므로 한계가 없다 */
        *allowed = TORQUE_MAX;
    }
    return torque_req;
}

void output_stage_init(output_stage_t *st)
{
    st->excess_cycles = 0u;
    st->clamp_count = 0u;
    st->last_out = 0;
}

torque_t output_stage_step(output_stage_t *st, reaction_t *reaction, torque_t torque_req,
                           torque_t allowed, gear_t gear)
{
    (void)st;
    (void)reaction;
    (void)allowed;
    (void)gear;
    return torque_req;
}
