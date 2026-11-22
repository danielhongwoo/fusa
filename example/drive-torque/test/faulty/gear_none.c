/*
 * 책의 예제 코드다. 실제 제품에 쓸 수 없다.
 * 대조 test용: 방향의 판정을 하지 않는 입력 검사. 운전자가 고른 기어를 그대로 받아들인다.
 * test/test_no_gear_check.c가 src/input/gear_check.c 대신 이것을 link한다.
 */
#include "input.h"

void gear_check_init(gear_check_t *st)
{
    st->direction = GEAR_N;
    st->reject_cycles = 0u;
    st->caution = false;
}

gear_t gear_check_step(gear_check_t *st, gear_t selected, bool speed_valid, speed_t speed)
{
    (void)st;
    (void)speed_valid;
    (void)speed;
    return selected;
}
