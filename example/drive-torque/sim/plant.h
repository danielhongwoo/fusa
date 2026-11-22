/*
 * 책의 예제 코드다. 실제 제품에 쓸 수 없다.
 * plant model: 운전자, 센서, inverter, 모터, 차량을 흉내 낸다.
 * item (VCU)의 밖에 있는 것들이다. 여기서는 부동소수점을 쓴다.
 */
#ifndef PLANT_H
#define PLANT_H

#include "types.h"

typedef struct {
    /* 운전자의 입력 */
    double pedal; /* 가속 페달, 0.0 - 1.0 */
    bool brake;
    gear_t gear;

    /* VCU가 보낸 것. 지연 뒤에 inverter에 닿는다 */
    double torque_sent_nm;
    time_ms_t torque_sent_wait_ms; /* 닿을 때까지 남은 시간. 0이면 보낸 것이 없다 */
    frame_t frame_sent;            /* 보호가 붙은 토크 요구 메시지 */
    time_ms_t frame_sent_wait_ms;

    double torque_offset_nm; /* inverter의 고장: 요구보다 이만큼 더 낸다. 평소에는 0 */
    double inverter_tau_ms;  /* inverter의 토크 응답의 시정수. 평소에는 PLANT_INVERTER_TAU_MS */

    /* inverter의 메시지 검사 (가정 A-21) */
    bool check_frames;       /* 거짓이면 받은 값을 검사 없이 쓴다 (대조 test) */
    bool rx_synced;
    unsigned rx_counter;
    bool enable_sent;
    time_ms_t enable_sent_wait_ms;

    /* inverter가 받은 것 */
    double torque_cmd_nm;    /* 마지막으로 받은 토크 요구 */
    time_ms_t cmd_age_ms;    /* 그 뒤로 흐른 시간 */
    bool enable;             /* 구동 허용 신호 */

    /* 상태 */
    double torque_act_nm;    /* 모터가 내는 토크 */
    double speed_mps;        /* 차량 속도. 양수는 전진 */
    double accel_mps2;       /* 차량 가속도 */
} plant_t;

/* 가정값. docs/technical-safety-concept.md의 시간 예산표와 맞춘다 */
#define PLANT_CMD_TIMEOUT_MS  50u  /* 토크 요구가 이 시간 넘게 오지 않으면 inverter는 토크를 내지 않는다 (A-06) */
#define PLANT_CAN_DELAY_MS    2u   /* 토크 요구가 inverter에 닿는 데 걸리는 시간 */
#define PLANT_ENABLE_DELAY_MS 1u   /* 구동 허용 신호의 변화가 inverter에 닿는 데 걸리는 시간 */
#define PLANT_INVERTER_TAU_MS 20u  /* inverter의 토크 응답의 시정수 (A-05) */
#define PLANT_MASS_KG         1600.0
#define PLANT_GEAR_RATIO      9.0
#define PLANT_WHEEL_RADIUS_M  0.31

void plant_init(plant_t *p);

/* VCU가 보호가 없는 토크 요구를 보냈다 (1장의 단순한 제어기). inverter는 검사 없이 쓴다 */
void plant_send_torque(plant_t *p, double torque_nm);

/* VCU가 보호가 붙은 토크 요구 메시지를 보냈다. inverter는 CRC와 counter를 검사하고 틀리면 버린다 */
void plant_send_frame(plant_t *p, const frame_t *frame);

/* VCU가 구동 허용 신호를 바꿨다 */
void plant_send_enable(plant_t *p, bool on);

/* 1 ms만큼 진행한다 */
void plant_step_1ms(plant_t *p);

#endif
