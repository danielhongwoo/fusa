/*
 * 책의 예제 코드다. 실제 제품에 쓸 수 없다.
 * 입력 검사: 가속 페달의 두 채널을 검사하고 안전한 페달 값을 낸다.
 * 하드웨어를 부르지 않는다. 그래서 unit test와 증명을 이 파일만으로 할 수 있다.
 */
#include "input.h"

/* 센서의 특성: 채널 1은 0.5 - 4.5 V, 채널 2는 0.25 - 2.25 V */
#define APPS1_MIN_MV    ((millivolt_t)500)
#define APPS1_SPAN_MV   ((millivolt_t)4000)
#define APPS2_MIN_MV    ((millivolt_t)250)
#define APPS2_SPAN_MV   ((millivolt_t)2000)
/* 이 범위를 벗어난 전압은 단선이나 단락으로 본다 */
#define APPS1_LOW_MV    ((millivolt_t)250)
#define APPS1_HIGH_MV   ((millivolt_t)4750)
#define APPS2_LOW_MV    ((millivolt_t)125)
#define APPS2_HIGH_MV   ((millivolt_t)2375)

/*
 * 전압을 페달 위치 (0 - 1000)로 바꾼다.
 * 빼거나 곱하기 전에 범위를 본다. HAL이 어떤 값을 주더라도 overflow가 나지 않게 하기 위해서다.
 */
static permille_t to_permille(millivolt_t mv, millivolt_t min_mv, millivolt_t span_mv)
{
    if (mv <= min_mv) {
        return 0;
    }
    if (mv >= (min_mv + span_mv)) {
        return PEDAL_FULL;
    }
    return ((mv - min_mv) * PEDAL_FULL) / span_mv;
}

static bool out_of_range(millivolt_t mv, millivolt_t low_mv, millivolt_t high_mv)
{
    return (mv < low_mv) || (mv > high_mv);
}

/* 최근 주기들의 기록에서 실패의 수를 센다.
 * 수를 따로 기억하지 않고 주기마다 다시 센다. 따로 기억하면 기록과 수가 어긋날 수 있다 */
static uint8_t window_bad_count(const pedal_check_t *st)
{
    uint8_t count = 0u;

    for (uint8_t i = 0u; i < PEDAL_WINDOW_CYCLES; i++) {
        if (st->window[i]) {
            count++;
        }
    }
    return count;
}

void pedal_check_init(pedal_check_t *st)
{
    st->bad_cycles = 0u;
    st->good_cycles = 0u;
    st->ready = false;
    st->fault = false;
    for (uint8_t i = 0u; i < PEDAL_WINDOW_CYCLES; i++) {
        st->window[i] = false;
    }
    st->window_pos = 0u;
}

permille_t pedal_check_step(pedal_check_t *st, const inputs_t *in)
{
    /* SWR-01: 두 채널을 같은 단위로 바꾼다 */
    permille_t p1 = to_permille(in->apps1_mv, APPS1_MIN_MV, APPS1_SPAN_MV);
    permille_t p2 = to_permille(in->apps2_mv, APPS2_MIN_MV, APPS2_SPAN_MV);
    permille_t diff = (p1 > p2) ? (p1 - p2) : (p2 - p1);

    /* SWR-02: 채널마다 범위를 보고, 두 채널을 서로 견준다 */
    bool bad = out_of_range(in->apps1_mv, APPS1_LOW_MV, APPS1_HIGH_MV)
               || out_of_range(in->apps2_mv, APPS2_LOW_MV, APPS2_HIGH_MV)
               || (diff > PEDAL_MISMATCH_MAX);

    /* SWR-03: 검사 실패가 정해진 주기만큼 이어지면 페달 고장으로 고정한다.
     * 한 주기라도 통과하면 다시 센다 */
    if (bad) {
        st->good_cycles = 0u;
        if (st->bad_cycles < PEDAL_FAULT_CYCLES) {
            st->bad_cycles++;
        }
        if (st->bad_cycles >= PEDAL_FAULT_CYCLES) {
            st->fault = true;
        }
    } else {
        st->bad_cycles = 0u;
        if (st->good_cycles < PEDAL_READY_CYCLES) {
            st->good_cycles++;
        }
        if (st->good_cycles >= PEDAL_READY_CYCLES) {
            st->ready = true;
        }
    }

    /* SWR-14: 최근 100주기 가운데 실패가 10번을 넘으면 페달 고장으로 고정한다.
     * 이어지지 않고 가끔 실패하는 간헐 고장을 잡는다. 가장 오래된 결과를 덮어쓴다.
     * 적을 자리가 범위를 벗어나 있으면 (memory의 값이 틀렸으면) 처음으로 돌린다 */
    if (st->window_pos >= PEDAL_WINDOW_CYCLES) {
        st->window_pos = 0u;
    }
    st->window[st->window_pos] = bad;
    st->window_pos++;
    if (window_bad_count(st) > PEDAL_WINDOW_MAX_BAD) {
        st->fault = true;
    }

    /* SWR-04: 안전한 페달 값은 작은 쪽이다.
     * 페달 고장이거나 켠 뒤 검사를 충분히 통과하기 전이면 0이다 */
    if (st->fault || !st->ready) {
        return 0;
    }
    return (p1 < p2) ? p1 : p2;
}
