/*
 * 책의 예제 코드다. 실제 제품에 쓸 수 없다.
 * VCU의 주기 실행.
 */
#include "vcu.h"

#include "hal.h"

void vcu_init(vcu_t *vcu)
{
    pedal_check_init(&vcu->pedal_check);
    brake_check_init(&vcu->brake_check);
    app_init(&vcu->app);
    output_stage_init(&vcu->output);
    reaction_init(&vcu->reaction);
    e2e_rx_init(&vcu->speed_rx);
    e2e_rx_init(&vcu->inverter_rx);
    e2e_tx_init(&vcu->torque_tx);
    vcu->speed_valid = false;
    vcu->speed = 0;
    vcu->inverter_valid = false;
    vcu->inverter_torque = 0;
    vcu->pedal_safe = 0;
    vcu->brake = true;
    vcu->torque_req = 0;
    vcu->torque_allowed = 0;
    vcu->torque_out = 0;
    vcu->enable = false;
    vcu->warning = WARNING_NONE;
    /* SWR-12: 켤 때 구동 허용 신호를 끊은 상태에서 시작한다.
     * reset 직후의 출력이 어떤 상태인지는 믿지 않는다 */
    hal_enable_write(false);
}

/* 입력을 한 번 읽고 검사한다 */
static void task_input(vcu_t *vcu)
{
    hal_rx_t rx;

    input_read(&vcu->in);
    /* SWR-18: 받은 메시지는 검사를 통과한 것만 쓴다. 무효이면 마지막 값을 쓰지 않는다 */
    hal_can_rx_speed(&rx);
    vcu->speed_valid = e2e_check(&vcu->speed_rx, E2E_ID_SPEED, &rx.frame, rx.seen, rx.fresh, rx.age_ms);
    vcu->speed = vcu->speed_valid ? rx.frame.value : 0;
    hal_can_rx_inverter(&rx);
    vcu->inverter_valid = e2e_check(&vcu->inverter_rx, E2E_ID_INVERTER, &rx.frame, rx.seen, rx.fresh,
                                    rx.age_ms);
    vcu->inverter_torque = vcu->inverter_valid ? rx.frame.value : 0;
    vcu->pedal_safe = pedal_check_step(&vcu->pedal_check, &vcu->in);
    /* SWR-11: 페달 고장은 토크 0의 사건이다 */
    if (vcu->pedal_check.fault) {
        reaction_raise(&vcu->reaction, REACTION_ZERO);
    }
    /* SWR-15: 브레이크는 여기 한 곳에서 판정해 기능과 감시에 같은 값을 준다.
     * 브레이크 신호의 고장도 토크 0의 사건이다 */
    vcu->brake = brake_check_step(&vcu->brake_check, &vcu->in);
    if (vcu->brake_check.fault) {
        reaction_raise(&vcu->reaction, REACTION_ZERO);
    }
}

/* 기능: 토크 요구를 만든다 */
static void task_app(vcu_t *vcu)
{
    vcu->torque_req = app_step(&vcu->app, vcu->pedal_safe, vcu->brake, vcu->in.gear);
}

/* 감시와 출력 단계 */
static void task_monitor_output(vcu_t *vcu)
{
    vcu->torque_out = monitor_output_cycle(&vcu->output, &vcu->reaction, vcu->torque_req,
                                           vcu->pedal_safe, vcu->brake, vcu->in.gear,
                                           &vcu->torque_allowed);

    /* 여기부터는 이 주기의 사건이 모두 반영된 상태를 쓴다 */
    reaction_state_t state = reaction_state(&vcu->reaction);

    /* SWR-10: 구동 허용 차단 상태이면 구동 허용 신호를 끊는다.
     * SWR-12: 켠 뒤 입력 검사를 충분히 통과하기 전에는 구동을 허용하지 않는다 */
    vcu->enable = vcu->pedal_check.ready && reaction_enable(state);

    /* SWR-11: 경고 요청은 상태에서 나온다 */
    vcu->warning = reaction_warning(state);

    /* 구동 허용 신호를 먼저 쓴다. 끊어야 하는 주기에 CAN의 송신이 늦어져도 끊는 일이 밀리지 않는다 */
    hal_enable_write(vcu->enable);
    /* SWR-17: 싣는 값은 출력 단계가 돌려준 토크다. 깎기 전의 요구가 아니다 */
    frame_t frame;
    e2e_protect(&vcu->torque_tx, E2E_ID_TORQUE, vcu->torque_out, &frame);
    hal_can_tx_torque_frame(&frame);
    hal_can_tx_warning(vcu->warning);

    hal_diag_t diag;
    diag.pedal_safe = vcu->pedal_safe;
    diag.pedal_fault = vcu->pedal_check.fault;
    diag.torque_req = vcu->torque_req;
    diag.torque_allowed = vcu->torque_allowed;
    diag.latched = (state == REACTION_CUT);
    diag.clamp_count = vcu->output.clamp_count;
    diag.brake = vcu->brake;
    diag.brake_fault = vcu->brake_check.fault;
    diag.speed_valid = vcu->speed_valid;
    diag.speed = vcu->speed;
    diag.inverter_valid = vcu->inverter_valid;
    hal_can_tx_diag(&diag);
}

const vcu_task_t vcu_task_table[] = {
    { "input", CYCLE_MS, task_input },
    { "app", CYCLE_MS, task_app },
    { "monitor_output", CYCLE_MS, task_monitor_output },
};

const int vcu_task_count = (int)(sizeof(vcu_task_table) / sizeof(vcu_task_table[0]));
