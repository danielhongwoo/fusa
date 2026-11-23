/*
 * 실행의 확인의 구현.
 */
#include "flow.h"

#include <stddef.h>

/* 배열이 구조체의 끝에 있고 그 뒤에 빈 자리도 없다는 것을 compile할 때 확인한다.
 * 증명 도구는 pointer로 받은 구조체의 끝만 본다. 배열 뒤에 필드가 생기면
 * 한 칸 넘는 쓰기를 증명도 test도 알리지 못한다 (docs/test-report.md 6절) */
_Static_assert((offsetof(flow_t, marks) + sizeof(((flow_t *)0)->marks)) == sizeof(flow_t),
               "flow_t: 배열은 구조체의 끝에 있어야 한다");
/* flow_check는 표시 셋을 하나씩 직접 본다. task의 수를 바꾸면 flow_check도 함께 고쳐야 한다 */
_Static_assert(FLOW_TASK_COUNT == 3u, "flow_check는 FLOW_TASK_COUNT가 3이라고 보고 쓴 것이다");

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
    /* SWR-20: task마다 표시를 남긴다. 자리가 없으면 적지 않고, 넘쳤다는 것만 남긴다 */
    if (f->count < FLOW_TASK_COUNT) {
        f->marks[f->count] = mark;
        f->count++;
    } else {
        f->count = (uint8_t)(FLOW_TASK_COUNT + 1u);
    }
}

bool flow_check(const flow_t *f)
{
    /* SWR-20: 표시의 수와 순서가 task table과 같아야 한다 */
    return (f->count == FLOW_TASK_COUNT) && (f->marks[0] == FLOW_MARK_INPUT)
           && (f->marks[1] == FLOW_MARK_APP) && (f->marks[2] == FLOW_MARK_MONITOR);
}

uint8_t flow_answer(const flow_t *f, torque_t allowed, torque_t out)
{
    uint32_t answer = f->question;

    for (uint8_t i = 0u; i < FLOW_TASK_COUNT; i++) {
        answer = ((answer * 31u) + f->marks[i]) & 0xFFu;
    }
    /* 표시의 수도 넣는다. 넣지 않으면 task가 한 번 더 실행되어 넷째 표시가 버려진 주기에도
     * 앞의 세 표시만으로 옳은 답이 나온다 */
    answer = ((answer * 31u) + f->count) & 0xFFu;
    /* SWR-20: 보낸 토크의 크기가 허용 토크를 넘었으면 답이 틀리게 나온다.
     * 허용 토크가 음수로 틀려 있어도 부호를 뒤집는 계산이 넘치지 않게 0에서 자른다 */
    torque_t limit = (allowed < 0) ? 0 : allowed;

    if ((out > limit) || (out < -limit)) {
        answer ^= 0xFFu;
    }
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
