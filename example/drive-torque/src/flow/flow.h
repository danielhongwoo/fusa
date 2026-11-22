/*
 * 책의 예제 코드다. 실제 제품에 쓸 수 없다.
 * 실행의 확인: task가 정해진 순서로 한 번씩 실행되었는지를 보고, 외부 watchdog에 보낼 답을 만든다.
 * 하드웨어를 부르지 않는다.
 *
 * task는 끝날 때 자기 번호를 표시로 남긴다. 주기의 끝에서 표시가 1, 2, 3의 순서로 하나씩인지 본다.
 * 답은 질문의 번호 (주기마다 1 오른다), 남은 표시와 그 수, 그 주기의 허용 토크와 보낸 토크에서 만든다.
 * 그래서 task가 빠지거나, 더 실행되거나, 순서가 틀리거나, 보낸 토크가 허용 토크를 넘으면 옳은 답이 나오지 않는다.
 */
#ifndef FLOW_H
#define FLOW_H

#include "types.h"

#define FLOW_TASK_COUNT ((uint8_t)3) /* 표시를 남기는 task의 수 */
#define FLOW_MARK_INPUT   ((uint8_t)1)
#define FLOW_MARK_APP     ((uint8_t)2)
#define FLOW_MARK_MONITOR ((uint8_t)3)

/* 배열은 구조체의 끝에 둔다. 증명 도구 (CBMC)의 경계 검사는 pointer로 받은 구조체 안의 배열에 대해
 * 구조체의 끝만 본다. 배열 뒤에 다른 필드가 있으면 한 칸 넘는 쓰기가 그 필드에 떨어져도 잡지 못한다
 * (docs/test-report.md 6절. tools/prove.sh가 이 한계를 작은 예로 확인한다) */
typedef struct {
    uint8_t count;                  /* 남긴 표시의 수. 표시가 넘치면 FLOW_TASK_COUNT + 1에서 멈춘다 */
    uint8_t question;               /* 이 주기의 답의 번호 */
    uint8_t marks[FLOW_TASK_COUNT]; /* 이 주기에 task가 남긴 표시. 남긴 순서대로다 */
} flow_t;

void flow_init(flow_t *f);

/* task가 끝날 때 부른다 */
void flow_mark(flow_t *f, uint8_t mark);

/* 이 주기의 표시가 task table의 순서와 수 그대로인가 */
bool flow_check(const flow_t *f);

/* 외부 watchdog에 보낼 답 */
uint8_t flow_answer(const flow_t *f, torque_t allowed, torque_t out);

/* 주기를 닫는다: 표시를 지우고 질문의 번호를 올린다.
 * 답하지 않은 주기에도 올린다. 답이 한 번 빠지면 watchdog이 끊고 풀지 않으므로 그 뒤의 번호는 뜻이 없다 */
void flow_next(flow_t *f);

#endif
