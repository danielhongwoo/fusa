/*
 * 책의 예제 코드다. 실제 제품에 쓸 수 없다.
 * 감시가 없는 것과 같은 모듈. test에서만 쓴다.
 * src/monitor/monitor.c 대신 link되어 같은 interface (monitor.h)를 구현한다.
 * 토크 요구를 깎지 않고, 고정하지도 않는다.
 * 쓰는 곳: 감시가 없으면 같은 fault가 safety goal을 어긴다는 것을 보이는 대조 test.
 */
#include "monitor.h"

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

torque_t output_clamp(torque_t torque_req, torque_t allowed, gear_t gear)
{
    (void)allowed;
    (void)gear;
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
    (void)st;
    (void)allowed;
    (void)gear;
    return torque_req;
}
