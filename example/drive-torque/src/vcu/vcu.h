/*
 * 책의 예제 코드다. 실제 제품에 쓸 수 없다.
 * VCU의 주기 실행: 입력, 기능, 감시와 출력을 task table로 묶는다.
 */
#ifndef VCU_H
#define VCU_H

#include "app.h"
#include "e2e.h"
#include "input.h"
#include "monitor.h"
#include "reaction.h"

typedef struct {
    inputs_t in;
    pedal_check_t pedal_check;
    permille_t pedal_safe;
    brake_check_t brake_check;
    bool brake;              /* 판정한 브레이크 상태. 기능과 감시가 같이 쓴다 */
    app_t app;
    torque_t torque_req;     /* 기능이 낸 토크 요구 (깎기 전) */
    torque_t torque_allowed; /* 감시가 계산한 허용 토크 */
    output_stage_t output;
    reaction_t reaction;     /* 고장 대응의 상태 */
    e2e_rx_t speed_rx;       /* 차량 속도 메시지의 검사 */
    bool speed_valid;
    speed_t speed;           /* 유효할 때만 쓴다 */
    e2e_rx_t inverter_rx;    /* inverter의 상태 메시지의 검사 */
    bool inverter_valid;
    torque_t inverter_torque; /* 유효할 때만 쓴다 */
    e2e_tx_t torque_tx;      /* 토크 요구 메시지의 보호 */
    torque_t torque_out;     /* inverter로 보낸 토크 */
    bool enable;             /* 구동 허용 신호 */
    uint8_t warning;         /* 경고 요청: 0 없음, 1 주의, 2 경고 */
} vcu_t;

typedef struct {
    const char *name;
    time_ms_t period_ms;
    void (*run)(vcu_t *vcu);
} vcu_task_t;

/* 정적 task table. scheduler는 주기가 된 task를 표의 순서대로 부른다 */
extern const vcu_task_t vcu_task_table[];
extern const int vcu_task_count;

void vcu_init(vcu_t *vcu);

#endif
