/*
 * 책의 예제 코드다. 실제 제품에 쓸 수 없다.
 * VCU의 주기 실행.
 */
#include "vcu.h"

#include <stddef.h>

#include "hal.h"

void vcu_init(vcu_t *vcu)
{
    pedal_check_init(&vcu->pedal_check);
    brake_check_init(&vcu->brake_check);
    gear_check_init(&vcu->gear_check);
    app_init(&vcu->app);
    output_stage_init(&vcu->output);
    reaction_init(&vcu->reaction);
    inverter_check_init(&vcu->inverter_check);
    flow_init(&vcu->flow);
    e2e_rx_init(&vcu->speed_rx);
    e2e_rx_init(&vcu->inverter_rx);
    e2e_tx_init(&vcu->torque_tx);
    vcu->speed_valid = false;
    vcu->speed = 0;
    vcu->inverter_valid = false;
    vcu->inverter_fresh = false;
    vcu->inverter_torque = 0;
    vcu->pedal_safe = 0;
    vcu->brake = true;
    vcu->gear = GEAR_N;
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

    /* SWR-21: 지난 주기에 쓴 구동 허용 신호를 되읽어 견준다. 쓴 대로 나가지 않았으면 구동 허용 차단의 사건이다.
     * 켠 뒤의 처음 주기들에는 끊으라고 쓴 것을 되읽는다. 끊기는 것을 확인하기 전에는 허용하지 않게 된다 */
    if (hal_enable_readback() != vcu->enable) {
        reaction_raise(&vcu->reaction, REACTION_CUT);
    }
    input_read(&vcu->in);
    /* SWR-18: 받은 메시지는 검사를 통과한 것만 쓴다. 무효이면 마지막 값을 쓰지 않는다 */
    hal_can_rx_speed(&rx);
    vcu->speed_valid = e2e_check(&vcu->speed_rx, E2E_ID_SPEED, &rx.frame, rx.seen, rx.fresh, rx.age_ms);
    vcu->speed = vcu->speed_valid ? rx.frame.value : 0;
    hal_can_rx_inverter(&rx);
    vcu->inverter_valid = e2e_check(&vcu->inverter_rx, E2E_ID_INVERTER, &rx.frame, rx.seen, rx.fresh,
                                    rx.age_ms);
    /* SWR-19: 새 메시지이고 검사를 통과한 것만 inverter의 검사가 견준다 */
    vcu->inverter_fresh = rx.fresh && vcu->inverter_valid;
    vcu->inverter_torque = vcu->inverter_valid ? rx.frame.value : 0;
    vcu->pedal_safe = pedal_check_step(&vcu->pedal_check, &vcu->in);
    /* SWR-24: 페달 채널 하나를 검사에서 뺐으면 줄여 감의 사건이다 */
    if (vcu->pedal_check.excluded != PEDAL_CH_NONE) {
        reaction_raise(&vcu->reaction, REACTION_LIMP);
    }
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
    /* SWR-16: 받아들인 기어도 여기 한 곳에서 정해 기능과 감시에 같은 값을 준다 */
    vcu->gear = gear_check_step(&vcu->gear_check, vcu->in.gear, vcu->speed_valid, vcu->speed);
    flow_mark(&vcu->flow, FLOW_MARK_INPUT);
}

/* 기능: 토크 요구를 만든다 */
static void task_app(vcu_t *vcu)
{
    /* SWR-24: 기능은 이 주기의 상태가 정한 상한을 받는다 */
    vcu->torque_req = app_step(&vcu->app, vcu->pedal_safe, vcu->brake, vcu->gear,
                               reaction_app_limit(reaction_state(&vcu->reaction)));
    flow_mark(&vcu->flow, FLOW_MARK_APP);
}

/* 감시와 출력 단계 */
static void task_monitor_output(vcu_t *vcu)
{
    /* SWR-19: inverter가 알린 토크가 지난 주기들에 보낸 토크의 범위를 계속 벗어나거나,
     * 새 상태 메시지가 너무 드물게 닿으면 구동 허용 차단의 사건이다.
     * 새 메시지가 없는 주기의 값은 지난 메시지의 것이어서 견주지 않는다 */
    if (inverter_check_step(&vcu->inverter_check, vcu->inverter_fresh, vcu->inverter_torque)) {
        reaction_raise(&vcu->reaction, REACTION_CUT);
    }
    vcu->torque_out = monitor_output_cycle(&vcu->output, &vcu->reaction, vcu->torque_req,
                                           vcu->pedal_safe, vcu->brake, vcu->gear,
                                           &vcu->torque_allowed);

    /* 여기부터는 이 주기의 사건이 모두 반영된 상태를 쓴다 */
    reaction_state_t state = reaction_state(&vcu->reaction);

    /* SWR-10: 구동 허용 차단 상태이면 구동 허용 신호를 끊는다.
     * SWR-12: 켠 뒤 입력 검사를 충분히 통과하기 전에는 구동을 허용하지 않는다 */
    vcu->enable = vcu->pedal_check.ready && reaction_enable(state);

    /* SWR-11: 경고 요청은 상태에서 나온다 */
    vcu->warning = reaction_warning(state);
    /* SWR-16: 방향의 바뀜을 받아들이지 못한 채 이어지면 주의를 요청한다. 고장의 경고가 있으면 그쪽이 앞선다 */
    if ((vcu->warning == WARNING_NONE) && vcu->gear_check.caution) {
        vcu->warning = WARNING_AMBER;
    }

    /* 구동 허용 신호를 먼저 쓴다. 끊어야 하는 주기에 CAN의 송신이 늦어져도 끊는 일이 밀리지 않는다 */
    hal_enable_write(vcu->enable);
    /* SWR-17: 싣는 값은 출력 단계가 돌려준 토크다. 깎기 전의 요구가 아니다 */
    frame_t frame;
    e2e_protect(&vcu->torque_tx, E2E_ID_TORQUE, vcu->torque_out, &frame);
    hal_can_tx_torque_frame(&frame);
    inverter_check_record(&vcu->inverter_check, vcu->torque_out);
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
    diag.gear = vcu->gear;
    diag.inverter_out_cycles = vcu->inverter_check.out_cycles;
    hal_can_tx_diag(&diag);
    flow_mark(&vcu->flow, FLOW_MARK_MONITOR);
}

/* 실행의 확인: 이 주기에 task가 정해진 순서로 한 번씩 실행되었으면 외부 watchdog에 답한다 */
static void task_flow(vcu_t *vcu)
{
    /* SWR-20: 순서나 횟수가 틀렸으면 답하지 않는다. 그러면 watchdog이 구동 허용 신호를 끊는다 */
    bool ok = flow_check(&vcu->flow);

    if (ok) {
        hal_watchdog_write(flow_answer(&vcu->flow, vcu->torque_allowed, vcu->torque_out));
    }
    flow_next(&vcu->flow);
}

const vcu_task_t vcu_task_table[] = {
    { "input", CYCLE_MS, task_input },
    { "app", CYCLE_MS, task_app },
    { "monitor_output", CYCLE_MS, task_monitor_output },
    { "flow", CYCLE_MS, task_flow },
};

const int vcu_task_count = (int)(sizeof(vcu_task_table) / sizeof(vcu_task_table[0]));

/* SWR-20: 표시를 남기는 task의 수는 표의 task에서 실행을 확인하는 task 하나를 뺀 것이다.
 * 표에 task를 더하고 표시를 정하지 않으면 여기에서 compile이 멈춘다 */
_Static_assert((sizeof(vcu_task_table) / sizeof(vcu_task_table[0])) == ((size_t)FLOW_TASK_COUNT + 1u),
               "task table과 FLOW_TASK_COUNT가 맞지 않는다");
