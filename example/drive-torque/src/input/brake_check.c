/*
 * 책의 예제 코드다. 실제 제품에 쓸 수 없다.
 * 입력 검사: 브레이크의 두 접점에서 밟음 여부를 정한다.
 * 하드웨어를 부르지 않는다.
 *
 * 두 접점은 서로 반대로 움직인다. 접점 1은 밟으면 열리고, 접점 2는 밟으면 닫힌다.
 * 선이 끊기면 접점 1은 "밟음"으로, 접점 2는 "놓음"으로 읽힌다 (docs/hsi.md 5절).
 * 그래서 한 가지 원인 (connector가 빠짐)이 둘을 함께 끊어도 두 접점이 어긋나 보인다.
 */
#include "input.h"

void brake_check_init(brake_check_t *st)
{
    st->release_cycles = 0u;
    st->mismatch_cycles = 0u;
    /* 켠 직후에는 밟은 것으로 본다. 두 접점이 놓음을 가리키는 것을 확인한 뒤에 놓음으로 바꾼다 */
    st->pressed = true;
    st->fault = false;
}

bool brake_check_step(brake_check_t *st, const inputs_t *in)
{
    /* SWR-15: 어느 하나라도 밟음을 가리키면 그 주기부터 밟음이다.
     * 놓음은 두 접점이 모두 놓음을 가리키고 정해진 주기만큼 이어진 뒤에 받아들인다.
     * 밟음을 놓치는 쪽이 위험하고 (제동 우선이 듣지 않는다), 놓음을 늦게 아는 쪽은 토크가 잠깐 늦을 뿐이다 */
    if (in->brake1 || in->brake2) {
        st->release_cycles = 0u;
        st->pressed = true;
    } else {
        if (st->release_cycles < BRAKE_RELEASE_CYCLES) {
            st->release_cycles++;
        }
        if (st->release_cycles >= BRAKE_RELEASE_CYCLES) {
            st->pressed = false;
        }
    }

    /* SWR-15: 두 접점이 어긋난 채 이어지면 브레이크 신호의 고장이다.
     * 페달을 밟거나 놓는 동안에는 두 접점이 바뀌는 때가 조금 달라 잠깐 어긋날 수 있다 */
    if (in->brake1 != in->brake2) {
        if (st->mismatch_cycles < BRAKE_MISMATCH_CYCLES) {
            st->mismatch_cycles++;
        }
        if (st->mismatch_cycles >= BRAKE_MISMATCH_CYCLES) {
            st->fault = true;
        }
    } else {
        st->mismatch_cycles = 0u;
    }

    /* 고장으로 판정한 뒤에는 밟은 것으로 둔다. 어느 접점이 맞는지 알 수 없다 */
    if (st->fault) {
        st->pressed = true;
    }
    return st->pressed;
}
