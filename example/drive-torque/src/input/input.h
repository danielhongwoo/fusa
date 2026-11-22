/*
 * 책의 예제 코드다. 실제 제품에 쓸 수 없다.
 * 입력 읽기와 입력 검사.
 * 기능과 감시가 함께 기대는 부분이라 safety goal SG-01의 요구사항을 받는다.
 */
#ifndef INPUT_H
#define INPUT_H

#include "types.h"

/* 한 주기의 입력. 주기마다 한 번만 읽는다 */
typedef struct {
    millivolt_t apps1_mv;
    millivolt_t apps2_mv;
    bool brake;
    gear_t gear;
} inputs_t;

/* 페달 검사의 상태 */
typedef struct {
    uint8_t bad_cycles;  /* 검사에 실패한 주기가 몇 번 이어졌는가 */
    uint8_t good_cycles; /* 켠 뒤로 검사를 통과한 주기가 몇 번 이어졌는가 */
    bool ready;          /* 켠 뒤로 검사를 충분히 통과했는가 */
    bool fault;          /* 페달 고장으로 판정했는가. 다시 켤 때까지 유지한다 */
} pedal_check_t;

#define PEDAL_RELEASED      ((permille_t)30) /* 이 값 아래는 페달을 놓은 것으로 본다 */
#define PEDAL_MISMATCH_MAX  ((permille_t)50) /* 두 채널의 차이가 이 값을 넘으면 불일치 */
#define PEDAL_FAULT_CYCLES  ((uint8_t)3)     /* 검사 실패가 이만큼 이어지면 페달 고장 */
#define PEDAL_READY_CYCLES  ((uint8_t)3)     /* 켠 뒤 이만큼 이어서 통과해야 페달 값을 쓴다 */

void input_read(inputs_t *in);

void pedal_check_init(pedal_check_t *st);

/*
 * 두 채널을 검사하고 안전한 페달 값을 돌려준다.
 * 안전한 페달 값은 두 채널 가운데 작은 값이다.
 * 페달 고장이거나, 켠 뒤 검사를 아직 충분히 통과하지 못했으면 0이다.
 */
permille_t pedal_check_step(pedal_check_t *st, const inputs_t *in);

#endif
