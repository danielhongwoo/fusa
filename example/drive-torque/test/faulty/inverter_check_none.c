/*
 * 책의 예제 코드다. 실제 제품에 쓸 수 없다.
 * 대조 test용: inverter가 알린 토크를 검사하지 않는 모듈.
 * test/test_no_inverter_check.c가 src/monitor/inverter_check.c 대신 이것을 link한다.
 */
#include "monitor.h"

void inverter_check_init(inverter_check_t *st)
{
    for (uint8_t i = 0u; i < INVERTER_HISTORY_CYCLES; i++) {
        st->sent[i] = 0;
    }
    st->pos = 0u;
    st->out_cycles = 0u;
    st->fresh_bits = 0u;
}

void inverter_check_record(inverter_check_t *st, torque_t sent)
{
    (void)st;
    (void)sent;
}

bool inverter_check_step(inverter_check_t *st, bool fresh, torque_t reported)
{
    (void)st;
    (void)fresh;
    (void)reported;
    return false;
}
