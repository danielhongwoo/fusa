/*
 * 책의 예제 코드다. 실제 제품에 쓸 수 없다.
 * 시뮬레이션용 HAL 구현.
 */
#include "hal_sim.h"

#include <stddef.h>

#define MSG_PERIOD_MS 10u
#define ADC_MAX_MV    5000

static struct {
    plant_t *plant;
    time_ms_t now_ms;
    bool fault_on[FAULT_COUNT];
    int32_t fault_param[FAULT_COUNT];
    millivolt_t adc_mv[HAL_ADC_COUNT];
    millivolt_t apps1_stuck_mv;
    /* 받은 메시지 */
    bool speed_seen;
    speed_t speed_value;
    time_ms_t speed_rx_ms;
    bool inv_seen;
    hal_inverter_status_t inv_value;
    time_ms_t inv_rx_ms;
    /* 내보낸 것 */
    torque_t torque_out;
    bool enable_out;
    uint8_t warning_out;
    hal_diag_t diag_out;
} sim;

/* 두 채널은 특성이 다르다: 채널 1은 0.5 - 4.5 V, 채널 2는 0.25 - 2.25 V */
millivolt_t hal_sim_apps1_mv(permille_t pedal)
{
    return 500 + (4 * pedal);
}

millivolt_t hal_sim_apps2_mv(permille_t pedal)
{
    return 250 + (2 * pedal);
}

static millivolt_t clamp_mv(millivolt_t mv)
{
    return (mv < 0) ? 0 : ((mv > ADC_MAX_MV) ? ADC_MAX_MV : mv);
}

static void update_sensors(void)
{
    permille_t pedal = (permille_t)((sim.plant->pedal * 1000.0) + 0.5);
    millivolt_t a1 = hal_sim_apps1_mv(pedal);
    millivolt_t a2 = hal_sim_apps2_mv(pedal);

    if (sim.fault_on[FAULT_APPS_SUPPLY_SCALE]) {
        a1 = (a1 * sim.fault_param[FAULT_APPS_SUPPLY_SCALE]) / 100;
        a2 = (a2 * sim.fault_param[FAULT_APPS_SUPPLY_SCALE]) / 100;
    }
    if (sim.fault_on[FAULT_APPS1_STUCK]) {
        a1 = sim.apps1_stuck_mv;
    }
    if (sim.fault_on[FAULT_APPS1_FIXED_MV]) {
        a1 = sim.fault_param[FAULT_APPS1_FIXED_MV];
    }
    if (sim.fault_on[FAULT_APPS2_FIXED_MV]) {
        a2 = sim.fault_param[FAULT_APPS2_FIXED_MV];
    }
    sim.adc_mv[HAL_ADC_APPS1] = clamp_mv(a1);
    sim.adc_mv[HAL_ADC_APPS2] = clamp_mv(a2);
}

static void update_messages(void)
{
    if ((sim.now_ms % MSG_PERIOD_MS) != 0u) {
        return;
    }
    if (!sim.fault_on[FAULT_SPEED_MSG_LOSS]) {
        if (!sim.fault_on[FAULT_SPEED_MSG_FREEZE] || !sim.speed_seen) {
            sim.speed_value = (speed_t)(sim.plant->speed_mps * 100.0);
        }
        sim.speed_seen = true;
        sim.speed_rx_ms = sim.now_ms;
    }
    sim.inv_value.fault = false;
    sim.inv_value.torque_act = (torque_t)(sim.plant->torque_act_nm * 10.0);
    sim.inv_seen = true;
    sim.inv_rx_ms = sim.now_ms;
}

void hal_sim_init(plant_t *plant)
{
    sim.plant = plant;
    sim.now_ms = 0u;
    hal_sim_clear_faults();
    sim.speed_seen = false;
    sim.speed_value = 0;
    sim.speed_rx_ms = 0u;
    sim.inv_seen = false;
    sim.inv_value.fault = false;
    sim.inv_value.torque_act = 0;
    sim.inv_rx_ms = 0u;
    sim.torque_out = 0;
    sim.enable_out = false;
    sim.warning_out = 0u;
    sim.diag_out = (hal_diag_t){ 0, false, 0, 0, false, 0u };
    update_sensors();
}

void hal_sim_step(time_ms_t t_ms)
{
    sim.now_ms = t_ms;
    update_sensors();
    update_messages();
}

void hal_sim_set_fault(fault_id_t fault, int32_t param)
{
    if (fault == FAULT_APPS1_STUCK) {
        sim.apps1_stuck_mv = sim.adc_mv[HAL_ADC_APPS1];
    }
    sim.fault_on[fault] = true;
    sim.fault_param[fault] = param;
}

void hal_sim_clear_faults(void)
{
    for (int i = 0; i < (int)FAULT_COUNT; i++) {
        sim.fault_on[i] = false;
        sim.fault_param[i] = 0;
    }
}

torque_t hal_sim_last_torque(void) { return sim.torque_out; }
bool hal_sim_enable(void) { return sim.enable_out; }
uint8_t hal_sim_warning(void) { return sim.warning_out; }
const hal_diag_t *hal_sim_diag(void) { return &sim.diag_out; }

/* ---- HAL interface의 구현 ---- */

time_ms_t hal_time_ms(void)
{
    return sim.now_ms;
}

millivolt_t hal_adc_read_mv(hal_adc_ch_t ch)
{
    return sim.adc_mv[ch];
}

bool hal_brake_pressed(void)
{
    return sim.plant->brake;
}

gear_t hal_gear_read(void)
{
    return sim.plant->gear;
}

bool hal_can_rx_speed(speed_t *speed, time_ms_t *age_ms)
{
    if (!sim.speed_seen) {
        return false;
    }
    *speed = sim.speed_value;
    *age_ms = sim.now_ms - sim.speed_rx_ms;
    return true;
}

bool hal_can_rx_inverter(hal_inverter_status_t *status, time_ms_t *age_ms)
{
    if (!sim.inv_seen) {
        return false;
    }
    *status = sim.inv_value;
    *age_ms = sim.now_ms - sim.inv_rx_ms;
    return true;
}

void hal_can_tx_torque(torque_t torque)
{
    sim.torque_out = torque;
    plant_send_torque(sim.plant, (double)torque / 10.0);
}

void hal_can_tx_warning(uint8_t level)
{
    sim.warning_out = level;
}

void hal_enable_write(bool on)
{
    sim.enable_out = on;
    plant_send_enable(sim.plant, on);
}

void hal_can_tx_diag(const hal_diag_t *diag)
{
    sim.diag_out = *diag;
}
