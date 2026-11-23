/*
 * plant model의 구현. 수치는 설명을 위한 가정이다.
 */
#include "plant.h"

#include <math.h>

#include "frame_sim.h"

#define DT_S            0.001
#define DRAG_CDA_M2     0.65
#define AIR_DENSITY     1.2
#define ROLL_COEFF      0.012
#define GRAVITY         9.81
#define BRAKE_DECEL     6.0    /* 브레이크를 밟았을 때의 감속도, m/s^2 */
#define MOTOR_MAX_NM    250.0

void plant_init(plant_t *p)
{
    p->pedal = 0.0;
    p->brake = false;
    p->gear = GEAR_P;
    p->torque_sent_nm = 0.0;
    p->torque_sent_wait_ms = 0u;
    p->frame_sent = (frame_t){ 0, 0u, 0u };
    p->frame_sent_wait_ms = 0u;
    p->check_frames = true;
    p->torque_offset_nm = 0.0;
    p->inverter_tau_ms = (double)PLANT_INVERTER_TAU_MS;
    p->rx_synced = false;
    p->rx_counter = 0u;
    p->enable_sent = false;
    p->enable_sent_wait_ms = 0u;
    p->torque_cmd_nm = 0.0;
    p->cmd_age_ms = PLANT_CMD_TIMEOUT_MS;
    p->enable = false;
    p->torque_act_nm = 0.0;
    p->speed_mps = 0.0;
    p->accel_mps2 = 0.0;
}

void plant_send_torque(plant_t *p, double torque_nm)
{
    p->torque_sent_nm = torque_nm;
    p->torque_sent_wait_ms = PLANT_CAN_DELAY_MS;
}

void plant_send_frame(plant_t *p, const frame_t *frame)
{
    p->frame_sent = *frame;
    p->frame_sent_wait_ms = PLANT_CAN_DELAY_MS;
}

/* inverter가 받은 메시지를 검사한다. 통과하면 참 */
static bool inverter_accepts(plant_t *p, const frame_t *frame)
{
    unsigned step;
    bool ok;

    if (!p->check_frames) {
        return true;
    }
    if (!frame_sim_crc_ok(frame, SIM_ID_TORQUE)) {
        return false;
    }
    step = ((unsigned)frame->counter - p->rx_counter) & 15u;
    ok = !p->rx_synced || ((step >= 1u) && (step <= 3u));
    p->rx_counter = frame->counter;
    p->rx_synced = true;
    return ok;
}

void plant_send_enable(plant_t *p, bool on)
{
    if (on != p->enable_sent) {
        p->enable_sent = on;
        p->enable_sent_wait_ms = PLANT_ENABLE_DELAY_MS;
    }
}

static double clamp(double x, double lo, double hi)
{
    return (x < lo) ? lo : ((x > hi) ? hi : x);
}

void plant_step_1ms(plant_t *p)
{
    /* 보낸 것이 지연 뒤에 inverter에 도착한다 */
    if (p->torque_sent_wait_ms > 0u) {
        p->torque_sent_wait_ms--;
        if (p->torque_sent_wait_ms == 0u) {
            p->torque_cmd_nm = p->torque_sent_nm;
            p->cmd_age_ms = 0u;
        }
    }
    if (p->frame_sent_wait_ms > 0u) {
        p->frame_sent_wait_ms--;
        if (p->frame_sent_wait_ms == 0u) {
            if (inverter_accepts(p, &p->frame_sent)) {
                p->torque_cmd_nm = (double)p->frame_sent.value / 10.0;
                p->cmd_age_ms = 0u;
            }
            /* 틀린 메시지는 버린다. 옳은 메시지가 오지 않으면 시간이 지나 토크를 내지 않게 된다 */
        }
    }
    if (p->enable_sent_wait_ms > 0u) {
        p->enable_sent_wait_ms--;
        if (p->enable_sent_wait_ms == 0u) {
            p->enable = p->enable_sent;
        }
    }

    /* inverter: 허용 신호가 없거나 토크 요구가 끊기면 목표는 0이다 */
    double target = 0.0;
    if (p->enable && (p->cmd_age_ms < PLANT_CMD_TIMEOUT_MS)) {
        target = clamp(p->torque_cmd_nm + p->torque_offset_nm, -MOTOR_MAX_NM, MOTOR_MAX_NM);
    }
    p->torque_act_nm += (target - p->torque_act_nm) * (1.0 / p->inverter_tau_ms);
    if (p->cmd_age_ms < 100000u) {
        p->cmd_age_ms++;
    }

    /* 차량: 구동력에서 저항을 뺀다. 저항은 움직임의 반대 방향이다 */
    double drive_n = p->torque_act_nm * PLANT_GEAR_RATIO / PLANT_WHEEL_RADIUS_M;
    double v = p->speed_mps;
    double resist_n = (ROLL_COEFF * PLANT_MASS_KG * GRAVITY)
                      + (0.5 * AIR_DENSITY * DRAG_CDA_M2 * v * v)
                      + (p->brake ? (BRAKE_DECEL * PLANT_MASS_KG) : 0.0);
    double net_n;
    if (fabs(v) < 1e-6) {
        /* 서 있다: 구동력이 저항보다 커야 움직인다 */
        if (fabs(drive_n) > resist_n) {
            net_n = drive_n - ((drive_n > 0.0) ? resist_n : -resist_n);
        } else {
            net_n = 0.0;
        }
    } else {
        net_n = drive_n - ((v > 0.0) ? resist_n : -resist_n);
    }
    double v_new = v + ((net_n / PLANT_MASS_KG) * DT_S);
    if (((v > 0.0) && (v_new < 0.0)) || ((v < 0.0) && (v_new > 0.0))) {
        v_new = 0.0; /* 저항은 차를 멈추게 할 뿐 반대로 밀지 않는다 */
    }
    p->accel_mps2 = (v_new - v) / DT_S;
    p->speed_mps = v_new;
}
