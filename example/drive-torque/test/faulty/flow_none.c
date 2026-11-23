/*
 * 대조 test용: 실행의 순서를 보지 않고 늘 옳은 답을 내는 모듈.
 * 주기마다 정해진 값을 써 주기만 하면 되는 단순한 watchdog을 쓰는 것과 같다.
 * test/test_no_flow_check.c가 src/flow/flow.c 대신 이것을 link한다.
 */
#include "flow.h"

void flow_init(flow_t *f)
{
    for (uint8_t i = 0u; i < FLOW_TASK_COUNT; i++) {
        f->marks[i] = 0u;
    }
    f->count = 0u;
    f->question = 0u;
}

void flow_mark(flow_t *f, uint8_t mark)
{
    (void)f;
    (void)mark;
}

bool flow_check(const flow_t *f)
{
    (void)f;
    return true;
}

uint8_t flow_answer(const flow_t *f, torque_t allowed, torque_t out)
{
    /* 표시가 1, 2, 3으로 셋이고 토크가 허용 범위 안일 때의 답을 그대로 낸다 */
    uint32_t answer = f->question;

    (void)allowed;
    (void)out;
    answer = ((answer * 31u) + 1u) & 0xFFu;
    answer = ((answer * 31u) + 2u) & 0xFFu;
    answer = ((answer * 31u) + 3u) & 0xFFu;
    answer = ((answer * 31u) + 3u) & 0xFFu; /* 표시의 수 */
    return (uint8_t)answer;
}

void flow_next(flow_t *f)
{
    /* 표시의 값도 지운다. 남겨 두면 다음 주기에 task가 빠져도 지난 주기의 표시가 그 자리를 채워,
     * 답이 옳게 나온다 */
    for (uint8_t i = 0u; i < FLOW_TASK_COUNT; i++) {
        f->marks[i] = 0u;
    }
    f->count = 0u;
    f->question = (uint8_t)((f->question + 1u) & 0xFFu);
}
