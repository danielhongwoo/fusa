/*
 * 책의 예제 코드다. 실제 제품에 쓸 수 없다.
 * 시뮬레이션용 HAL 구현과 fault injection의 interface.
 * fault는 여기에서만 넣는다. src/의 코드에는 test용 코드가 없다.
 */
#ifndef HAL_SIM_H
#define HAL_SIM_H

#include "hal.h"
#include "plant.h"

typedef enum {
    FAULT_APPS1_STUCK = 0,   /* 채널 1이 지금 값에 고착 */
    FAULT_APPS1_FIXED_MV,    /* 채널 1이 param mV에 고착 */
    FAULT_APPS2_FIXED_MV,    /* 채널 2가 param mV에 고착 */
    FAULT_APPS_SUPPLY_SCALE, /* 공통 원인: 센서 전원이 param %로 바뀌어 두 채널이 같은 비율로 변함 */
    FAULT_SPEED_MSG_LOSS,    /* 차량 속도 메시지가 오지 않음 */
    FAULT_SPEED_MSG_FREEZE,  /* 차량 속도 메시지는 오지만 값이 멈춤 */
    FAULT_BRAKE1_STUCK,      /* 브레이크 접점 1이 고착: param이 1이면 "밟음" (선이 끊김), 0이면 "놓음" (접점이 붙음) */
    FAULT_BRAKE2_STUCK,      /* 브레이크 접점 2가 고착: param이 1이면 "밟음" (접점이 붙음), 0이면 "놓음" (선이 끊김) */
    FAULT_SPEED_MSG_CORRUPT, /* 차량 속도 메시지의 값이 전송 중에 param만큼 바뀜 */
    FAULT_SPEED_MSG_REPEAT,  /* 같은 차량 속도 메시지가 되풀이됨 */
    FAULT_INVERTER_MSG_LOSS, /* inverter의 상태 메시지가 오지 않음 */
    FAULT_INVERTER_TORQUE_OFFSET, /* inverter가 요구보다 param (0.1 Nm)만큼 더 냄 */
    FAULT_INVERTER_REPORT_OFFSET, /* inverter가 알리는 토크가 실제보다 param (0.1 Nm)만큼 큼 */
    FAULT_INVERTER_REPORT_STALE,  /* inverter가 알리는 토크가 한 주기 (10 ms) 전의 값임. 고장이 아니라 느린 경우다 */
    FAULT_ENABLE_STUCK_ON,   /* 구동 허용 신호의 선이 허용에 고착됨 (전원에 닿음) */
    FAULT_ENABLE_OPEN,       /* 구동 허용 신호의 선이 끊김. inverter는 끊긴 것으로 본다 */
    FAULT_TASK_SKIP,         /* task 하나가 실행되지 않음. param은 task table의 몇 번째인가 (0부터) */
    FAULT_TASK_STOP,         /* task가 하나도 실행되지 않음 (MCU가 멈춤) */
    FAULT_TASK_SLOW,         /* task의 주기가 두 배로 늘어남 (clock의 고장) */
    FAULT_TASK_TWICE,        /* task 하나가 한 주기에 두 번 실행됨. param은 task table의 몇 번째인가 (0부터) */
    FAULT_TORQUE_MSG_CORRUPT, /* 토크 요구 메시지의 값이 전송 중에 param만큼 바뀜 */
    FAULT_TORQUE_MSG_REPEAT, /* 지난 토크 요구 메시지가 되풀이됨 (새 메시지는 도착하지 않음) */
    FAULT_INVERTER_MSG_DROP, /* inverter의 상태 메시지가 bus에서 사라짐. 어느 것이 도착하는지를 되풀이되는 모양으로 준다:
                              * param은 SIM_DROP_PATTERN(길이, 표시)이고, 표시의 bit k가 1이면 그 모양의 k번째 메시지가 도착한다.
                              * 보낸 쪽의 counter는 오른다 (FAULT_INVERTER_MSG_LOSS는 보내지 않는 경우여서 오르지 않는다) */
    FAULT_INVERTER_MSG_CORRUPT, /* inverter의 상태 메시지의 값이 전송 중에 param만큼 바뀜 (test는 양수만 쓴다) */
    FAULT_COUNT
} fault_id_t;

void hal_sim_init(plant_t *plant);

/* 시각을 t_ms로 맞추고, 센서 값과 주기 메시지를 갱신한다 */
void hal_sim_step(time_ms_t t_ms);

/* FAULT_INVERTER_MSG_DROP의 param. 길이는 1 - 16을 받는다 (test가 쓰는 것은 7까지다).
 * 예: SIM_DROP_PATTERN(3, 4)는 셋에 하나 (세 번째)만 도착한다. SIM_DROP_PATTERN(1, 0)은 모두 잃는다 */
#define SIM_DROP_PATTERN(period, mask) ((int32_t)(((uint32_t)(mask) << 8) | (uint32_t)(period)))

void hal_sim_set_fault(fault_id_t fault, int32_t param);
void hal_sim_clear_faults(void);

/* inverter가 받은 메시지를 검사하는지를 정한다. 기본은 검사한다. 거짓은 대조 test에 쓴다 */
void hal_sim_inverter_check(bool on);

/* 외부 watchdog의 model (가정 A-24). 답을 기다리는 창은 지난 답에서 5 - 15 ms다. 값은 임시다.
 * 첫 답을 받기 전과 끊은 뒤에는 구동 허용 신호가 inverter에 도착하지 않는다. 끊은 것은 다시 켤 때까지 풀리지 않는다 */
#define SIM_WD_WINDOW_MIN_MS 5u
#define SIM_WD_WINDOW_MAX_MS 15u

/* 외부 watchdog이 있는가. 기본은 있다. 1장의 단순한 제어기에는 없다 */
void hal_sim_watchdog_present(bool present);

/* inverter에 도착하는 구동 허용 신호의 선의 값. VCU가 쓴 값 (hal_sim_enable)과 다를 수 있다:
 * 외부 watchdog이 막거나 끊었을 때, 선이 고착되거나 끊겼을 때 */
bool hal_sim_enable_wire(void);

/* 외부 watchdog이 구동 허용 신호를 끊었는가 */
bool hal_sim_watchdog_tripped(void);

/* 넣은 fault를 본다. 시나리오 실행기가 task를 건너뛰는 데 쓴다 */
bool hal_sim_fault_on(fault_id_t fault);
int32_t hal_sim_fault_param(fault_id_t fault);

/* inverter의 토크 응답의 시정수를 바꾼다. 기본은 20 ms (가정 A-16). 가정보다 느린 inverter를 보는 test에 쓴다 */
void hal_sim_inverter_tau(double tau_ms);

/* 보호가 없는 토크 요구. 1장의 단순한 제어기 (intro/naive_vcu.c)만 쓴다.
 * 제품의 HAL (src/hal/hal.h)에는 없다. 제품은 hal_can_tx_torque_frame을 쓴다 */
void hal_can_tx_torque(torque_t torque);

/* VCU가 내보낸 것을 본다 */
torque_t hal_sim_last_torque(void);
bool hal_sim_enable(void);
/* 구동 허용 신호를 쓰기 전에 토크 요구를 보낸 횟수. 제품이 출력을 쓰는 순서를 test가 보는 데 쓴다 */
uint32_t hal_sim_order_violations(void);

/* inverter의 상태 메시지가 VCU에 도착한 횟수. test가 메시지를 정말 잃었는지 확인하는 데 쓴다 */
uint32_t hal_sim_inverter_msgs_arrived(void);
uint8_t hal_sim_warning(void);
const hal_diag_t *hal_sim_diag(void);

/* 센서가 정상일 때의 전압 (plant와 test가 함께 쓴다) */
millivolt_t hal_sim_apps1_mv(permille_t pedal);
millivolt_t hal_sim_apps2_mv(permille_t pedal);

#endif
