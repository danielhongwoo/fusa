/*
 * 증명 도구 (CBMC)의 배열 경계 검사가 무엇을 보고 무엇을 보지 못하는지를 확인하는 작은 예.
 * 제품의 코드가 아니다. tools/prove.sh가 돌린다.
 *
 * 검토에서 찾은 것 (reviews/2026-11-23-stage2-part3/round1-embedded.md의 E-01):
 * pointer로 받은 구조체 안의 배열을 한 칸 넘어 쓰면, 쓰는 곳이 같은 구조체의 다음 필드일 때
 * 이 도구는 잡지 못한다. 구조체의 끝을 넘을 때에만 잡는다.
 * 그래서 제품의 구조체는 배열을 끝에 둔다 (flow_t, pedal_check_t, inverter_check_t).
 */
#include <stdint.h>

uint8_t nondet_uint8(void);

typedef struct {
    uint8_t before;
    uint8_t a[3];
} array_last_t;

typedef struct {
    uint8_t a[3];
    uint8_t after;
} array_inside_t;

static void write_last(array_last_t *s, uint8_t i)
{
    s->a[i] = 1u;
}

static void write_inside(array_inside_t *s, uint8_t i)
{
    s->a[i] = 1u;
}

/* 배열이 구조체의 끝에 있다. 한 칸 넘는 쓰기 (i가 3)를 도구가 잡아야 한다. 이 함수의 검증은 실패해야 한다 */
void canary_array_last(void)
{
    array_last_t s;
    uint8_t i = nondet_uint8();

    __CPROVER_assume(i <= 3);
    s.before = 0u;
    write_last(&s, i);
}

/* 배열 뒤에 다른 필드가 있다. 한 칸 넘는 쓰기가 그 필드에 떨어진다.
 * CBMC 6.11은 이것을 잡지 못한다 (알려진 한계). 잡는 판이 나오면 tools/prove.sh가 그렇게 알린다 */
void canary_array_inside(void)
{
    array_inside_t s;
    uint8_t i = nondet_uint8();

    __CPROVER_assume(i <= 3);
    s.after = 0u;
    write_inside(&s, i);
}
