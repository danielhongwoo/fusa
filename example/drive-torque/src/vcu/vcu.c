/*
 * 책의 예제 코드다. 실제 제품에 쓸 수 없다.
 * VCU의 주기 실행.
 */
#include "vcu.h"

#include "hal.h"

#define WARNING_NONE ((uint8_t)0)
#define WARNING_RED  ((uint8_t)2)

void vcu_init(vcu_t *vcu)
{
    pedal_check_init(&vcu->pedal_check);
    app_init(&vcu->app);
    output_stage_init(&vcu->output);
    vcu->pedal_safe = 0;
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
    input_read(&vcu->in);
    vcu->pedal_safe = pedal_check_step(&vcu->pedal_check, &vcu->in);
}

/* 기능: 토크 요구를 만든다 */
static void task_app(vcu_t *vcu)
{
    vcu->torque_req = app_step(&vcu->app, vcu->pedal_safe, vcu->in.brake, vcu->in.gear);
}

/* 감시와 출력 단계 */
static void task_monitor_output(vcu_t *vcu)
{
    vcu->torque_allowed = monitor_allowed_torque(vcu->pedal_safe, vcu->in.brake, vcu->in.gear);
    vcu->torque_allowed = monitor_limit_rise(vcu->torque_allowed, vcu->output.last_out, vcu->in.gear);
    vcu->torque_out = output_stage_step(&vcu->output, vcu->torque_req, vcu->torque_allowed,
                                        vcu->in.gear);

    /* SWR-10: 기능의 고장으로 고정되면 구동 허용 신호를 끊는다.
     * SWR-12: 켠 뒤 입력 검사를 충분히 통과하기 전에는 구동을 허용하지 않는다 */
    vcu->enable = vcu->pedal_check.ready && !vcu->output.latched;

    /* SWR-11: 페달 고장이나 기능의 고장을 알아채면 경고를 요청한다 */
    vcu->warning = (vcu->pedal_check.fault || vcu->output.latched) ? WARNING_RED : WARNING_NONE;

    /* 구동 허용 신호를 먼저 쓴다. 끊어야 하는 주기에 CAN의 송신이 늦어져도 끊는 일이 밀리지 않는다 */
    hal_enable_write(vcu->enable);
    hal_can_tx_torque(vcu->torque_out);
    hal_can_tx_warning(vcu->warning);

    hal_diag_t diag;
    diag.pedal_safe = vcu->pedal_safe;
    diag.pedal_fault = vcu->pedal_check.fault;
    diag.torque_req = vcu->torque_req;
    diag.torque_allowed = vcu->torque_allowed;
    diag.latched = vcu->output.latched;
    diag.clamp_count = vcu->output.clamp_count;
    hal_can_tx_diag(&diag);
}

const vcu_task_t vcu_task_table[] = {
    { "input", CYCLE_MS, task_input },
    { "app", CYCLE_MS, task_app },
    { "monitor_output", CYCLE_MS, task_monitor_output },
};

const int vcu_task_count = (int)(sizeof(vcu_task_table) / sizeof(vcu_task_table[0]));
