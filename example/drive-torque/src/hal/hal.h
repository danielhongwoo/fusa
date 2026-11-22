/*
 * 책의 예제 코드다. 실제 제품에 쓸 수 없다.
 * 하드웨어 추상화 계층 (HAL)의 interface.
 * 기능과 감시의 코드는 하드웨어를 이 함수들로만 만난다.
 * 시뮬레이션에서는 sim/hal_sim.c가 구현하고, fault는 그 뒤에서만 넣는다.
 *
 * 신호마다의 단위, 켠 직후의 값, 고장일 때의 모습은 docs/hsi.md에 있다.
 */
#ifndef HAL_H
#define HAL_H

#include "types.h"

typedef enum {
    HAL_ADC_APPS1 = 0, /* 가속 페달 위치 센서 채널 1 */
    HAL_ADC_APPS2 = 1, /* 가속 페달 위치 센서 채널 2 */
    HAL_ADC_COUNT = 2
} hal_adc_ch_t;

/* 받은 메시지 */
typedef struct {
    frame_t frame;    /* 마지막으로 받은 메시지 */
    bool seen;        /* 한 번이라도 받았는가 */
    bool fresh;       /* 지난번에 읽은 뒤로 새 메시지를 받았는가 */
    time_ms_t age_ms; /* 마지막으로 받은 뒤로 흐른 시간 */
} hal_rx_t;

/* 켜진 뒤로 흐른 시간 */
time_ms_t hal_time_ms(void);

/* ADC 입력을 mV로 읽는다 (0 - 5000) */
millivolt_t hal_adc_read_mv(hal_adc_ch_t ch);

/* 브레이크 페달의 접점 둘. 참이면 그 접점이 "밟음"을 가리킨다.
 * 접점 1은 밟으면 열리고 접점 2는 밟으면 닫힌다. 선이 끊기면 접점 1은 참, 접점 2는 거짓으로 읽힌다 */
bool hal_brake1_pressed(void);
bool hal_brake2_pressed(void);

/* 운전자가 고른 기어 */
gear_t hal_gear_read(void);

/* 차량 속도 메시지 (제동 제어기가 CAN으로 보낸다). 값은 속도의 크기, 단위 0.01 m/s */
void hal_can_rx_speed(hal_rx_t *rx);

/* inverter의 상태 메시지. 값은 inverter가 추정한 실제 토크, 단위 0.1 Nm */
void hal_can_rx_inverter(hal_rx_t *rx);

/* 토크 요구 메시지를 inverter로 보낸다. 값은 토크, 단위 0.1 Nm */
void hal_can_tx_torque_frame(const frame_t *frame);

/* 경고 요청을 계기판으로 보낸다. 0은 없음, 1은 주의, 2는 경고 */
void hal_can_tx_warning(uint8_t level);

/* 구동 허용 신호 (CAN과 별개의 선). false면 inverter는 토크를 내지 않는다 */
void hal_enable_write(bool on);

/* 구동 허용 신호의 선을 되읽는다. 참이면 선이 허용 상태다. 외부 watchdog을 지난 뒤의 선을 읽는다 */
bool hal_enable_readback(void);

/* 외부 watchdog에 답을 쓴다. watchdog은 정해진 창 안에 옳은 답을 받지 못하면 구동 허용 신호를 끊는다.
 * 답의 규칙은 docs/hsi.md 3절에 있다 */
void hal_watchdog_write(uint8_t answer);

/* 진단 메시지. 정비와 시험에서 VCU의 판단을 보는 데 쓴다 */
typedef struct {
    permille_t pedal_safe;   /* 입력 검사를 거친 페달 값 */
    bool pedal_fault;        /* 페달 고장으로 판정했는가 */
    torque_t torque_req;     /* 기능이 낸 토크 요구 (깎기 전) */
    torque_t torque_allowed; /* 감시가 계산한 허용 토크 */
    bool latched;            /* 기능의 고장으로 고정했는가 */
    uint32_t clamp_count;    /* 출력 단계가 토크 요구를 깎은 횟수 */
    bool brake;              /* 판정한 브레이크 상태 */
    bool brake_fault;        /* 브레이크 신호의 고장으로 판정했는가 */
    bool speed_valid;        /* 차량 속도 메시지가 유효한가 */
    speed_t speed;           /* VCU가 쓰는 차량 속도. 메시지가 무효이면 0 */
    bool inverter_valid;     /* inverter의 상태 메시지가 유효한가 */
    gear_t gear;             /* 받아들인 기어 */
    uint8_t inverter_out_cycles; /* inverter가 알린 토크가 범위를 벗어난 주기가 몇 번 이어졌는가 */
} hal_diag_t;

void hal_can_tx_diag(const hal_diag_t *diag);

#endif
