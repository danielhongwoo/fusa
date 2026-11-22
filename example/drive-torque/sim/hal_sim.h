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
    FAULT_COUNT
} fault_id_t;

void hal_sim_init(plant_t *plant);

/* 시각을 t_ms로 맞추고, 센서 값과 주기 메시지를 갱신한다 */
void hal_sim_step(time_ms_t t_ms);

void hal_sim_set_fault(fault_id_t fault, int32_t param);
void hal_sim_clear_faults(void);

/* VCU가 내보낸 것을 본다 */
torque_t hal_sim_last_torque(void);
bool hal_sim_enable(void);
/* 구동 허용 신호를 쓰기 전에 토크 요구를 보낸 횟수. 제품이 출력을 쓰는 순서를 test가 보는 데 쓴다 */
uint32_t hal_sim_order_violations(void);
uint8_t hal_sim_warning(void);
const hal_diag_t *hal_sim_diag(void);

/* 센서가 정상일 때의 전압 (plant와 test가 함께 쓴다) */
millivolt_t hal_sim_apps1_mv(permille_t pedal);
millivolt_t hal_sim_apps2_mv(permille_t pedal);

#endif
