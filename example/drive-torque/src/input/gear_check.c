/*
 * 책의 예제 코드다. 실제 제품에 쓸 수 없다.
 * 입력 검사: 운전자가 고른 기어에서 받아들인 기어를 정한다.
 */
#include "input.h"

void gear_check_init(gear_check_t *st)
{
    st->direction = GEAR_N; /* 받아들인 방향이 아직 없다 */
    st->reject_cycles = 0u;
    st->caution = false;
}

gear_t gear_check_step(gear_check_t *st, gear_t selected, bool speed_valid, speed_t speed)
{
    gear_t accepted = selected;
    bool rejected = false;

    if ((selected == GEAR_D) || (selected == GEAR_R)) {
        /* SWR-16: 마지막으로 받아들인 방향과 같으면 속도를 보지 않는다.
         * 받아들인 방향이 없거나 반대이면, 차량 속도가 유효하고 5 km/h 아래일 때만 받아들인다 */
        if (selected != st->direction) {
            if (speed_valid && (speed >= 0) && (speed < GEAR_CHANGE_SPEED_MAX)) {
                st->direction = selected;
            } else {
                accepted = GEAR_N;
                rejected = true;
            }
        }
    } else if (selected != GEAR_P) {
        accepted = GEAR_N; /* N이거나 알 수 없는 값 */
    } else {
        /* P는 그대로다 */
    }

    /* 받아들이지 못한 채 이어지면 주의를 요청한다. 고장으로 판정하지 않으므로 조건이 풀리면 거둔다 */
    if (rejected) {
        if (st->reject_cycles < GEAR_REJECT_WARN_CYCLES) {
            st->reject_cycles++;
        }
    } else {
        st->reject_cycles = 0u;
    }
    st->caution = (st->reject_cycles >= GEAR_REJECT_WARN_CYCLES);
    return accepted;
}
