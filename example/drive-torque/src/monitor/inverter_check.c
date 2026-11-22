/*
 * 책의 예제 코드다. 실제 제품에 쓸 수 없다.
 * 감시: inverter가 알린 토크를 VCU가 보낸 토크와 견준다.
 */
#include "monitor.h"

void inverter_check_init(inverter_check_t *st)
{
    for (uint8_t i = 0u; i < INVERTER_HISTORY_CYCLES; i++) {
        st->sent[i] = 0;
    }
    st->pos = 0u;
    st->out_cycles = 0u;
    st->invalid_cycles = 0u;
}

/* 기록의 값을 토크의 범위 안으로 자른다. memory의 값이 틀려도 아래의 덧셈과 뺄셈이 넘치지 않는다 */
static torque_t bounded(torque_t v)
{
    torque_t r = v;

    if (r > TORQUE_MAX) {
        r = TORQUE_MAX;
    }
    if (r < -TORQUE_MAX) {
        r = -TORQUE_MAX;
    }
    return r;
}

void inverter_check_record(inverter_check_t *st, torque_t sent)
{
    if (st->pos >= INVERTER_HISTORY_CYCLES) {
        st->pos = 0u;
    }
    st->sent[st->pos] = sent;
    st->pos++;
}

bool inverter_check_step(inverter_check_t *st, bool valid, torque_t reported)
{
    if (!valid) {
        /* SWR-19: 상태를 알 수 없는 주기를 센다. 범위를 벗어난 횟수는 그대로 둔다.
         * 지우면 벗어남과 무효가 번갈아 올 때 어느 쪽도 한계에 닿지 않는다 */
        if (st->invalid_cycles < INVERTER_INVALID_CYCLES) {
            st->invalid_cycles++;
        }
    } else {
        /* SWR-19: 최근에 보낸 토크와 0이 이루는 범위에 여유를 더한다.
         * inverter는 보낸 값을 늦게 따라가므로 그 사이의 값은 벗어난 것이 아니다 */
        torque_t lo = 0;
        torque_t hi = 0;

        for (uint8_t i = 0u; i < INVERTER_HISTORY_CYCLES; i++) {
            torque_t v = bounded(st->sent[i]);
            if (v < lo) {
                lo = v;
            }
            if (v > hi) {
                hi = v;
            }
        }
        st->invalid_cycles = 0u;
        if ((reported < (lo - INVERTER_TORQUE_MARGIN)) || (reported > (hi + INVERTER_TORQUE_MARGIN))) {
            if (st->out_cycles < INVERTER_OUT_CYCLES) {
                st->out_cycles++;
            }
        } else {
            st->out_cycles = 0u;
        }
    }
    return (st->out_cycles >= INVERTER_OUT_CYCLES) || (st->invalid_cycles >= INVERTER_INVALID_CYCLES);
}
