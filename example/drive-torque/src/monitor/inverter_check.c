/*
 * 책의 예제 코드다. 실제 제품에 쓸 수 없다.
 * 감시: inverter가 알린 토크를 VCU가 보낸 토크와 견준다.
 */
#include "monitor.h"

#include <stddef.h>

/* 배열이 구조체의 끝에 있고 그 뒤에 빈 자리도 없다는 것을 compile할 때 확인한다.
 * 증명 도구는 pointer로 받은 구조체의 끝만 본다. 배열 뒤에 필드가 생기면
 * 한 칸 넘는 쓰기를 증명도 test도 알리지 못한다 (docs/test-report.md 6절) */
_Static_assert((offsetof(inverter_check_t, sent) + sizeof(((inverter_check_t *)0)->sent)) == sizeof(inverter_check_t),
               "inverter_check_t: 배열은 구조체의 끝에 있어야 한다");

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

bool inverter_check_step(inverter_check_t *st, bool valid, bool fresh, torque_t reported)
{
    if (!valid) {
        /* SWR-19: 상태를 알 수 없는 주기를 센다. 범위를 벗어난 횟수는 그대로 둔다.
         * 지우면 벗어남과 무효가 번갈아 올 때 어느 쪽도 한계에 닿지 않는다 */
        if (st->invalid_cycles < INVERTER_INVALID_CYCLES) {
            st->invalid_cycles++;
        }
    } else if (!fresh) {
        /* SWR-19: 유효하지만 새 메시지가 없는 주기다. 받는 쪽의 검사 (SWR-18)는 새 메시지가 50 ms까지
         * 없어도 마지막 값을 유효로 넘긴다. 그 값은 지난 메시지의 것이어서 지금 보낸 토크와 견줄 수 없다.
         * 견주면 토크가 크게 내려가는 때에 고장 없는 inverter를 끊는다 (docs/change-impact.md).
         * 벗어난 횟수는 그대로 둔다. 올리면 벗어난 메시지 하나를 여러 번 세고,
         * 지우면 벗어난 메시지와 빈 주기가 번갈아 올 때 한계에 닿지 않는다 */
        st->invalid_cycles = 0u;
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
