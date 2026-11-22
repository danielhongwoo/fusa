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

/* 페달의 채널을 가리키는 값 */
#define PEDAL_CH_NONE ((uint8_t)0)
#define PEDAL_CH1     ((uint8_t)1)
#define PEDAL_CH2     ((uint8_t)2)

/* 페달 검사의 상태 */
typedef struct {
    uint8_t bad_cycles;  /* 검사에 실패한 주기가 몇 번 이어졌는가 */
    uint8_t good_cycles; /* 켠 뒤로 검사를 통과한 주기가 몇 번 이어졌는가 */
    bool ready;          /* 켠 뒤로 검사를 충분히 통과했는가 */
    bool fault;          /* 페달 고장으로 판정했는가. 다시 켤 때까지 유지한다 */
    bool window[PEDAL_WINDOW_CYCLES]; /* 최근 주기들의 검사 결과. true가 실패다 */
    uint8_t window_pos;  /* 다음 결과를 적을 자리 */
    uint8_t suspect;     /* 이어지고 있는 실패가 모두 한 채널만의 범위 실패이면 그 채널. 아니면 없음 */
    uint8_t excluded;    /* 검사에서 뺀 채널. 없음이 아니면 줄여 감이다. 다시 켤 때까지 유지한다 */
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

/* 방향의 판정: 받아들인 방향이 없거나 반대인 방향은 차량 속도가 유효하고 5 km/h 아래일 때만 받아들인다.
 * 5 km/h는 1.389 m/s다. 속도의 단위가 0.01 m/s이므로 138까지가 "아래"다. 두 값은 임시다 */
#define GEAR_CHANGE_SPEED_MAX   ((speed_t)139)
#define GEAR_REJECT_WARN_CYCLES ((uint8_t)50) /* 받아들이지 못한 채 이만큼 (500 ms) 이어지면 주의 */

/* 방향 판정의 상태 */
typedef struct {
    gear_t direction;      /* 마지막으로 받아들인 방향 (GEAR_D 또는 GEAR_R). 아직 없으면 GEAR_N */
    uint8_t reject_cycles; /* 고른 방향을 받아들이지 못한 주기가 몇 번 이어졌는가 */
    bool caution;          /* 운전자에게 주의를 요청하는가. 조건이 풀리면 거둔다 */
} gear_check_t;

void input_read(inputs_t *in);

void gear_check_init(gear_check_t *st);

/*
 * 운전자가 고른 기어에서 받아들인 기어를 정해 돌려준다. 기능과 감시가 이 값 하나를 같이 쓴다.
 * 받아들이지 못한 방향은 N으로 낸다. 고장으로 판정하지 않는다.
 * speed는 차량 속도의 크기 (0.01 m/s), speed_valid는 그 값을 믿을 수 있는가다.
 */
gear_t gear_check_step(gear_check_t *st, gear_t selected, bool speed_valid, speed_t speed);

void brake_check_init(brake_check_t *st);

/*
 * 두 접점에서 브레이크를 밟았는지를 정해 돌려준다.
 * 어느 하나라도 밟음이면 밟음이다. 고장으로 판정한 뒤에는 늘 밟음이다.
 */
bool brake_check_step(brake_check_t *st, const inputs_t *in);

void pedal_check_init(pedal_check_t *st);

/*
 * 두 채널을 검사하고 안전한 페달 값을 돌려준다.
 * 안전한 페달 값은 두 채널 가운데 작은 값이다. 채널 하나를 검사에서 뺐으면 남은 채널의 값이다.
 * 페달 고장이거나, 켠 뒤 검사를 아직 충분히 통과하지 못했으면 0이다.
 */
permille_t pedal_check_step(pedal_check_t *st, const inputs_t *in);

#endif
