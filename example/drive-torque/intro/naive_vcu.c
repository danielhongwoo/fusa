/*
 * 1장에서 보이는 것: 안전 장치가 없는 토크 제어기.
 *
 * 이 제어기는 요구사항대로 동작한다. 요구사항은 "가속 페달 위치에 비례하는 토크를 요구한다"다.
 * 코드에 결함은 없다. 그런데 페달 센서의 값이 고착되면 운전자가 페달을 놓아도 차가 계속 가속한다.
 * 빠진 것은 코드가 아니라 요구사항이다: 센서가 틀렸을 때 어떻게 하는가.
 *
 * src/vcu/vcu.c 대신 이 파일을 link하면 같은 시뮬레이션에서 이 제어기가 돈다.
 */
#include "vcu.h"

#include "hal.h"

/* 채널 1의 전압 범위 (0%에서 500 mV, 100%에서 4500 mV) */
#define APPS1_MIN_MV  ((millivolt_t)500)
#define APPS1_SPAN_MV ((millivolt_t)4000)

void vcu_init(vcu_t *vcu)
{
    vcu->torque_out = 0;
    vcu->enable = true;
    /* 켜자마자 구동을 허용한다 */
    hal_enable_write(true);
}

/* 전압을 페달 위치 (0-1000)로 바꾼다 */
static permille_t pedal_from_mv(millivolt_t mv)
{
    if (mv <= APPS1_MIN_MV) {
        return 0;
    }
    if (mv >= (APPS1_MIN_MV + APPS1_SPAN_MV)) {
        return PEDAL_FULL;
    }
    return ((mv - APPS1_MIN_MV) * PEDAL_FULL) / APPS1_SPAN_MV;
}

/* 하나뿐인 task: 페달을 읽고, 토크를 계산하고, 보낸다 */
static void task_torque(vcu_t *vcu)
{
    /* 센서의 채널 하나만 읽는다. 값이 맞는지 확인할 방법이 없다 */
    permille_t pedal = pedal_from_mv(hal_adc_read_mv(HAL_ADC_APPS1));
    gear_t gear = hal_gear_read();
    torque_t torque = 0;

    if (gear == GEAR_D) {
        torque = (pedal * TORQUE_MAX) / PEDAL_FULL;
    }
    /* 브레이크를 보지 않는다. 계산한 토크를 검사하는 것도 없다 */
    vcu->torque_out = torque;
    hal_can_tx_torque(torque);
}

const vcu_task_t vcu_task_table[] = {
    { "torque", CYCLE_MS, task_torque },
};
const int vcu_task_count = (int)(sizeof(vcu_task_table) / sizeof(vcu_task_table[0]));
