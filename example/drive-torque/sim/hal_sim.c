/*
 * 책의 예제 코드다. 실제 제품에 쓸 수 없다.
 * 시뮬레이션용 HAL 구현.
 */
#include "hal_sim.h"

#include <stddef.h>

#include "frame_sim.h"

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
    bool speed_fresh;
    speed_t speed_value;
    unsigned speed_counter;
    frame_t speed_frame;
    time_ms_t speed_rx_ms;
    bool inv_seen;
    bool inv_fresh;
    unsigned inv_counter;
    frame_t inv_frame;
    time_ms_t inv_rx_ms;
    /* 전송 중에 되풀이되는 토크 요구 메시지 (FAULT_TORQUE_MSG_REPEAT) */
    frame_t torque_frame_last;
    frame_t torque_frame_stuck;
    /* 내보낸 것 */
    torque_t torque_out;
    bool enable_out;
    uint8_t warning_out;
    hal_diag_t diag_out;
    /* 출력을 쓴 순서: 같은 순간 (1 ms) 안에서 구동 허용 신호를 쓰기 전에 토크 요구를 보낸 횟수 */
    bool enable_written_this_tick;
    uint32_t order_violations;
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
    /* 제동 제어기가 차량 속도를 보낸다. 값은 속도의 크기다 */
    if (sim.fault_on[FAULT_SPEED_MSG_REPEAT] && sim.speed_seen) {
        /* 같은 메시지가 다시 온다. counter도 그대로다 */
        sim.speed_fresh = true;
        sim.speed_rx_ms = sim.now_ms;
    } else if (!sim.fault_on[FAULT_SPEED_MSG_LOSS]) {
        double v = sim.plant->speed_mps;
        if (!sim.fault_on[FAULT_SPEED_MSG_FREEZE] || !sim.speed_seen) {
            sim.speed_value = (speed_t)(((v < 0.0) ? -v : v) * 100.0);
        }
        sim.speed_counter = (sim.speed_counter + 1u) & 15u;
        frame_sim_make(&sim.speed_frame, SIM_ID_SPEED, sim.speed_counter, sim.speed_value);
        if (sim.fault_on[FAULT_SPEED_MSG_CORRUPT]) {
            /* 전송 중에 값이 바뀐다. CRC는 그대로다 */
            sim.speed_frame.value += sim.fault_param[FAULT_SPEED_MSG_CORRUPT];
        }
        sim.speed_seen = true;
        sim.speed_fresh = true;
        sim.speed_rx_ms = sim.now_ms;
    } else {
        /* 메시지가 오지 않는다 */
    }
    /* inverter가 추정한 토크를 알린다 */
    if (!sim.fault_on[FAULT_INVERTER_MSG_LOSS]) {
        sim.inv_counter = (sim.inv_counter + 1u) & 15u;
        frame_sim_make(&sim.inv_frame, SIM_ID_INVERTER, sim.inv_counter,
                       (int32_t)(sim.plant->torque_act_nm * 10.0));
        sim.inv_seen = true;
        sim.inv_fresh = true;
        sim.inv_rx_ms = sim.now_ms;
    }
}

void hal_sim_init(plant_t *plant)
{
    sim.plant = plant;
    sim.now_ms = 0u;
    hal_sim_clear_faults();
    sim.speed_seen = false;
    sim.speed_fresh = false;
    sim.speed_value = 0;
    sim.speed_counter = 0u;
    sim.speed_frame = (frame_t){ 0, 0u, 0u };
    sim.speed_rx_ms = 0u;
    sim.inv_seen = false;
    sim.inv_fresh = false;
    sim.inv_counter = 0u;
    sim.inv_frame = (frame_t){ 0, 0u, 0u };
    sim.inv_rx_ms = 0u;
    sim.torque_frame_last = (frame_t){ 0, 0u, 0u };
    sim.torque_frame_stuck = (frame_t){ 0, 0u, 0u };
    sim.torque_out = 0;
    sim.enable_out = true; /* 켠 직후의 출력은 알 수 없다고 보고 나쁜 쪽으로 둔다 */
    sim.warning_out = 0u;
    sim.diag_out = (hal_diag_t){ 0, false, 0, 0, false, 0u, false, false, false, 0, false };
    sim.enable_written_this_tick = false;
    sim.order_violations = 0u;
    update_sensors();
}

void hal_sim_step(time_ms_t t_ms)
{
    sim.now_ms = t_ms;
    sim.enable_written_this_tick = false;
    update_sensors();
    update_messages();
}

void hal_sim_set_fault(fault_id_t fault, int32_t param)
{
    if (fault == FAULT_APPS1_STUCK) {
        sim.apps1_stuck_mv = sim.adc_mv[HAL_ADC_APPS1];
    }
    if (fault == FAULT_TORQUE_MSG_REPEAT) {
        sim.torque_frame_stuck = sim.torque_frame_last;
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

void hal_sim_inverter_check(bool on) { sim.plant->check_frames = on; }
torque_t hal_sim_last_torque(void) { return sim.torque_out; }
bool hal_sim_enable(void) { return sim.enable_out; }
uint32_t hal_sim_order_violations(void) { return sim.order_violations; }
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

bool hal_brake1_pressed(void)
{
    if (sim.fault_on[FAULT_BRAKE1_STUCK]) {
        return sim.fault_param[FAULT_BRAKE1_STUCK] != 0;
    }
    return sim.plant->brake;
}

bool hal_brake2_pressed(void)
{
    if (sim.fault_on[FAULT_BRAKE2_STUCK]) {
        return sim.fault_param[FAULT_BRAKE2_STUCK] != 0;
    }
    return sim.plant->brake;
}

gear_t hal_gear_read(void)
{
    return sim.plant->gear;
}

void hal_can_rx_speed(hal_rx_t *rx)
{
    rx->frame = sim.speed_frame;
    rx->seen = sim.speed_seen;
    rx->fresh = sim.speed_fresh;
    rx->age_ms = sim.now_ms - sim.speed_rx_ms;
    sim.speed_fresh = false;
}

void hal_can_rx_inverter(hal_rx_t *rx)
{
    rx->frame = sim.inv_frame;
    rx->seen = sim.inv_seen;
    rx->fresh = sim.inv_fresh;
    rx->age_ms = sim.now_ms - sim.inv_rx_ms;
    sim.inv_fresh = false;
}

/* 출력을 쓰는 순서를 센다. 제품은 구동 허용 신호를 먼저 쓰고 토크 요구를 보내야 한다 (docs/hsi.md 4절).
 * sim에는 CAN의 지연이 없어 순서가 결과에 나타나지 않으므로, 순서 자체를 센다 */
static void count_order(void)
{
    if (!sim.enable_written_this_tick) {
        sim.order_violations++;
    }
}

void hal_can_tx_torque_frame(const frame_t *frame)
{
    frame_t on_bus = *frame;

    count_order();
    sim.torque_out = frame->value;
    sim.torque_frame_last = *frame;
    /* 전송 중의 고장 */
    if (sim.fault_on[FAULT_TORQUE_MSG_REPEAT]) {
        on_bus = sim.torque_frame_stuck; /* 지난 메시지가 되풀이된다 */
    }
    if (sim.fault_on[FAULT_TORQUE_MSG_CORRUPT]) {
        on_bus.value += sim.fault_param[FAULT_TORQUE_MSG_CORRUPT]; /* 값이 바뀐다. CRC는 그대로다 */
    }
    plant_send_frame(sim.plant, &on_bus);
}

void hal_can_tx_torque(torque_t torque)
{
    count_order();
    sim.torque_out = torque;
    plant_send_torque(sim.plant, (double)torque / 10.0);
}

void hal_can_tx_warning(uint8_t level)
{
    sim.warning_out = level;
}

void hal_enable_write(bool on)
{
    sim.enable_written_this_tick = true;
    sim.enable_out = on;
    plant_send_enable(sim.plant, on);
}

void hal_can_tx_diag(const hal_diag_t *diag)
{
    sim.diag_out = *diag;
}
