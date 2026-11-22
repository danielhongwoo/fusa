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
    bool brake1; /* 브레이크 접점 1 (밟으면 열린다)이 밟음을 가리키는가 */
    bool brake2; /* 브레이크 접점 2 (밟으면 닫힌다)가 밟음을 가리키는가 */
    gear_t gear;
} inputs_t;

#define PEDAL_RELEASED      ((permille_t)30) /* 이 값 아래는 페달을 놓은 것으로 본다 */
#define PEDAL_MISMATCH_MAX  ((permille_t)50) /* 두 채널의 차이가 이 값을 넘으면 불일치 */
#define PEDAL_FAULT_CYCLES  ((uint8_t)3)     /* 검사 실패가 이만큼 이어지면 페달 고장 */
#define PEDAL_READY_CYCLES  ((uint8_t)3)     /* 켠 뒤 이만큼 이어서 통과해야 페달 값을 쓴다 */
/* 간헐 고장의 판정: 최근 100주기 (1초) 가운데 실패가 10번을 넘으면 페달 고장. 두 값은 임시다 */
#define PEDAL_WINDOW_CYCLES  ((uint8_t)100)
#define PEDAL_WINDOW_MAX_BAD ((uint8_t)10)

/* 페달 검사의 상태 */
typedef struct {
    uint8_t bad_cycles;  /* 검사에 실패한 주기가 몇 번 이어졌는가 */
    uint8_t good_cycles; /* 켠 뒤로 검사를 통과한 주기가 몇 번 이어졌는가 */
    bool ready;          /* 켠 뒤로 검사를 충분히 통과했는가 */
    bool fault;          /* 페달 고장으로 판정했는가. 다시 켤 때까지 유지한다 */
    bool window[PEDAL_WINDOW_CYCLES]; /* 최근 주기들의 검사 결과. true가 실패다 */
    uint8_t window_pos;  /* 다음 결과를 적을 자리 */
} pedal_check_t;

/* 브레이크 검사: 놓음은 두 접점이 맞고 3주기 이어진 뒤에, 어긋난 채 20주기 (200 ms) 이어지면 고장. 두 값은 임시다 */
#define BRAKE_RELEASE_CYCLES  ((uint8_t)3)
#define BRAKE_MISMATCH_CYCLES ((uint8_t)20)

/* 브레이크 검사의 상태 */
typedef struct {
    uint8_t release_cycles;  /* 두 접점이 모두 놓음을 가리킨 주기가 몇 번 이어졌는가 */
    uint8_t mismatch_cycles; /* 두 접점이 어긋난 주기가 몇 번 이어졌는가 */
    bool pressed;            /* 판정한 브레이크 상태. 기능과 감시가 이 값 하나를 같이 쓴다 */
    bool fault;              /* 브레이크 신호의 고장으로 판정했는가 */
} brake_check_t;

void input_read(inputs_t *in);

void brake_check_init(brake_check_t *st);

/*
 * 두 접점에서 브레이크를 밟았는지를 정해 돌려준다.
 * 어느 하나라도 밟음이면 밟음이다. 고장으로 판정한 뒤에는 늘 밟음이다.
 */
bool brake_check_step(brake_check_t *st, const inputs_t *in);

void pedal_check_init(pedal_check_t *st);

/*
 * 두 채널을 검사하고 안전한 페달 값을 돌려준다.
 * 안전한 페달 값은 두 채널 가운데 작은 값이다.
 * 페달 고장이거나, 켠 뒤 검사를 아직 충분히 통과하지 못했으면 0이다.
 */
permille_t pedal_check_step(pedal_check_t *st, const inputs_t *in);

#endif
