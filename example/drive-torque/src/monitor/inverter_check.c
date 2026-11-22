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

/* 기록에서 쓰는 bit: 최근 INVERTER_FRESH_WINDOW 주기 */
#define FRESH_MASK ((uint8_t)((1u << INVERTER_FRESH_WINDOW) - 1u))

void inverter_check_init(inverter_check_t *st)
{
    for (uint8_t i = 0u; i < INVERTER_HISTORY_CYCLES; i++) {
        st->sent[i] = 0;
    }
    st->pos = 0u;
    st->out_cycles = 0u;
    /* 켠 직후에는 새 메시지를 받아 온 것으로 치고 시작한다. 그러지 않으면 첫 주기에 사건이 된다.
     * 메시지가 오지 않으면 3번째 주기에 사건이다 */
    st->fresh_bits = FRESH_MASK;
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

/* 기록에서 새 메시지를 받은 주기를 센다. 창 밖의 bit는 보지 않는다 (memory의 값이 틀려도) */
static uint8_t fresh_count(uint8_t bits)
{
    uint8_t n = 0u;

    for (uint8_t i = 0u; i < INVERTER_FRESH_WINDOW; i++) {
        /* 작은 정수형은 식 안에서 int로 넓어진다. 부호 없는 형으로 넓힌 뒤에 bit 연산을 한다 */
        if ((((uint32_t)bits >> i) & 1u) != 0u) {
            n++;
        }
    }
    return n;
}

bool inverter_check_step(inverter_check_t *st, bool fresh, torque_t reported)
{
    /* SWR-19: 이번 주기에 새 상태 메시지를 받았는지를 기록에 넣는다. 가장 오래된 주기는 밀려 나간다.
     * 넓힌 채로 밀고, 창의 bit만 남긴 뒤에 좁힌다. 좁힌 뒤에 자르면 기록의 값이 틀렸을 때 (위쪽 bit가 서 있을 때)
     * 좁히는 데서 값이 잘린다 (증명 도구가 알렸다) */
    st->fresh_bits = (uint8_t)(((uint32_t)st->fresh_bits << 1u) & (uint32_t)FRESH_MASK);
    if (fresh) {
        /* SWR-19: 최근에 보낸 토크와 0이 이루는 범위에 여유를 더한다.
         * inverter는 보낸 값을 늦게 따라가므로 그 사이의 값은 벗어난 것이 아니다 */
        torque_t lo = 0;
        torque_t hi = 0;

        st->fresh_bits |= 1u;
        for (uint8_t i = 0u; i < INVERTER_HISTORY_CYCLES; i++) {
            torque_t v = bounded(st->sent[i]);
            if (v < lo) {
                lo = v;
            }
            if (v > hi) {
                hi = v;
            }
        }
        if ((reported < (lo - INVERTER_TORQUE_MARGIN)) || (reported > (hi + INVERTER_TORQUE_MARGIN))) {
            if (st->out_cycles < INVERTER_OUT_CYCLES) {
                st->out_cycles++;
            }
        } else {
            st->out_cycles = 0u;
        }
    } else {
        /* SWR-19: 새 메시지가 없는 주기다. 손에 있는 값은 지난 메시지의 것이어서 지금 보낸 토크와 견줄 수 없다.
         * 견주면 토크가 크게 내려가는 때에 고장 없는 inverter를 끊는다 (docs/change-impact.md의 CR-001).
         * 벗어난 횟수는 그대로 둔다. 올리면 벗어난 메시지 하나를 여러 번 세고,
         * 지우면 벗어난 메시지와 빈 주기가 번갈아 올 때 한계에 닿지 않는다 */
    }
    /* SWR-19: 사건은 둘이다. 범위를 벗어난 새 메시지가 이어졌거나, 새 메시지가 너무 드물게 닿는다.
     * 뒤의 것이 없으면 받아들이는 손실의 모양에 끝이 없고, 판정에 걸리는 시간에도 끝이 없다 (CR-002).
     * 둘을 함께 두면, 알린 토크가 범위를 벗어난 채인 동안에는 메시지를 어떤 모양으로 잃든
     * INVERTER_FRESH_WINDOW 주기 안에 사건이 된다: 그 안에 새 메시지가 INVERTER_FRESH_MIN번 닿았으면
     * 앞의 것이, 닿지 않았으면 뒤의 것이 참이다 */
    return (st->out_cycles >= INVERTER_OUT_CYCLES) || (fresh_count(st->fresh_bits) < INVERTER_FRESH_MIN);
}
