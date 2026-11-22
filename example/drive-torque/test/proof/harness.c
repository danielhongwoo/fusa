/*
 * 책의 예제 코드다. 실제 제품에 쓸 수 없다.
 * CBMC로 증명할 성질. 성질마다 함수 하나이고, tools/prove.sh가 하나씩 돌린다.
 *
 * 성질에는 요구사항의 숫자를 그대로 적는다 (토크의 단위는 0.1 Nm). 제품 코드의 상수 이름을 쓰지 않는다.
 *
 * 증명이 말해 주는 것: 이 C 코드는 가능한 모든 입력에서 아래 assert를 지킨다.
 * 말해 주지 않는 것: compiler가 만든 기계어, 실행 시간, 하드웨어의 고장, 주기를 놓치는 경우.
 */
#include <assert.h>

#include "app.h"
#include "input.h"
#include "monitor.h"

int32_t nondet_int32(void);
uint32_t nondet_uint32(void);
uint8_t nondet_uint8(void);
bool nondet_bool(void);

/* 성질 1 (SWR-05, SWR-06): 허용 토크는 0 이상 최대 토크 이하다. 0이어야 하는 조건에서는 0이다 */
void prove_allowed_torque(void)
{
    permille_t pedal = nondet_int32();
    bool brake = nondet_bool();
    gear_t gear = (gear_t)nondet_int32();
    torque_t allowed = monitor_allowed_torque(pedal, brake, gear);

    assert(allowed >= 0);
    assert(allowed <= 2500);
    if (brake || (pedal < 30) || ((gear != GEAR_D) && (gear != GEAR_R))) {
        assert(allowed == 0);
    }
    if (gear == GEAR_R) {
        assert(allowed <= 1000 + 50); /* 후진은 100 Nm에 오차 5 Nm까지 */
    }
}

/* 성질 2 (SWR-07): 깎은 토크는 허용 토크 안에 있고, 방향은 기어를 따른다 */
void prove_output_clamp(void)
{
    torque_t req = nondet_int32();
    torque_t allowed = nondet_int32();
    gear_t gear = (gear_t)nondet_int32();
    torque_t out;

    __CPROVER_assume((allowed >= 0) && (allowed <= 2500));
    out = output_clamp(req, allowed, gear);

    assert(out <= allowed);
    assert(out >= -allowed);
    if (gear == GEAR_D) {
        assert(out >= 0);
    } else if (gear == GEAR_R) {
        assert(out <= 0);
    } else {
        assert(out == 0);
    }
}

/* 성질 3 (SWR-08, SWR-09): 어떤 상태에서 시작해도 출력은 허용 토크 안에 있고, 고정은 풀리지 않으며, 고정되면 0이다 */
void prove_output_stage(void)
{
    output_stage_t st;
    torque_t req = nondet_int32();
    torque_t allowed = nondet_int32();
    gear_t gear = (gear_t)nondet_int32();
    bool was_latched;
    torque_t out;

    st.excess_cycles = nondet_uint8();
    st.clamp_count = nondet_uint32();
    st.latched = nondet_bool();
    __CPROVER_assume(st.excess_cycles <= 5);
    __CPROVER_assume((allowed >= 0) && (allowed <= 2500));
    was_latched = st.latched;

    out = output_stage_step(&st, req, allowed, gear);

    assert(out <= allowed);
    assert(out >= -allowed);
    if (was_latched) {
        assert(st.latched);
    }
    if (st.latched) {
        assert(out == 0);
    }
}

/* 성질 4 (SWR-01, SWR-03, SWR-04, SWR-14): 안전한 페달 값은 0-1000이고, 고장은 풀리지 않으며, 고장이면 0이다.
 * 최근 주기들의 기록과 적을 자리는 어떤 값이든 된다 (정하지 않은 변수를 CBMC는 모든 값으로 본다).
 * memory의 값이 틀려도 배열 밖을 쓰지 않아야 한다 */
void prove_pedal_check(void)
{
    pedal_check_t st;
    inputs_t in;
    bool was_fault;
    permille_t pedal;
    int bad_in_window = 0;

    st.bad_cycles = nondet_uint8();
    st.good_cycles = nondet_uint8();
    st.ready = nondet_bool();
    st.fault = nondet_bool();
    __CPROVER_assume(st.bad_cycles <= 3);
    __CPROVER_assume(st.good_cycles <= 3);
    in.apps1_mv = nondet_int32(); /* HAL이 어떤 값을 주더라도 */
    in.apps2_mv = nondet_int32();
    in.brake = nondet_bool();
    in.gear = GEAR_D;
    was_fault = st.fault;

    pedal = pedal_check_step(&st, &in);

    assert(pedal >= 0);
    assert(pedal <= 1000);
    if (was_fault) {
        assert(st.fault);
    }
    if (st.fault || !st.ready) {
        assert(pedal == 0);
    }
    /* 적을 자리는 한 주기 뒤에 범위 안에 있다 */
    assert((st.window_pos >= 1) && (st.window_pos <= 100));
    /* 기록에 실패가 10번을 넘게 남아 있으면 고장이다 */
    for (int i = 0; i < 100; i++) {
        if (st.window[i]) {
            bad_in_window++;
        }
    }
    if (bad_in_window > 10) {
        assert(st.fault);
    }
}

/* 성질 5 (SWR-13): 오르는 속도를 제한한 허용 토크는 페달에서 나온 상한을 넘지 않고,
 * 지난 주기에 보낸 토크의 크기 (지금 기어의 방향일 때만)에서 25 Nm 넘게 오르지 않는다.
 * 지난 출력은 어떤 값이든 된다. memory의 값이 틀려도 계산이 넘치지 않아야 한다 */
void prove_limit_rise(void)
{
    torque_t allowed = nondet_int32();
    torque_t last_out = nondet_int32();
    gear_t gear = (gear_t)nondet_int32();
    torque_t limited;

    __CPROVER_assume((allowed >= 0) && (allowed <= 2500));
    limited = monitor_limit_rise(allowed, last_out, gear);

    assert(limited >= 0);
    assert(limited <= allowed);
    if ((gear == GEAR_D) && (last_out > 0)) {
        if (last_out <= 2500) {
            assert(limited <= (last_out + 250));
        }
    } else if ((gear == GEAR_R) && (last_out < 0)) {
        if (last_out >= -2500) {
            assert(limited <= (250 - last_out));
        }
    } else {
        assert(limited <= 250); /* 방향이 다르거나 P, N이면 0에서 센다 */
    }
}

/*
 * 성질 6 (SWR-06, SWR-13): 정상인 기능의 토크 요구는 깎이지 않는다.
 *
 * 한 주기의 걸음을 증명한다. 아래의 "맞물린 상태"에서 시작하면, 입력이 무엇이든
 * 한 주기 뒤에도 맞물린 상태이고 그 주기의 토크 요구는 그대로 나간다.
 *   맞물린 상태: 기능이 기억하는 지난 토크 요구와 출력 단계가 기억하는 지난 출력이 같고,
 *                고정되지 않았고, 이어서 깎인 주기가 없다.
 * 켠 직후의 상태가 맞물린 상태라는 것도 함께 증명한다. 둘을 이으면 몇 주기를 돌아도 성립한다.
 *
 * 전제 (증명이 말해 주지 않는 것)
 *   - 기능과 감시가 같은 주기에 같은 안전한 페달 값, 브레이크, 기어를 받는다.
 *   - 기능, 감시, 출력 단계가 주기마다 이 순서로 한 번씩 실행된다.
 *   - 기능과 출력 단계의 변수를 다른 코드가 바꾸지 않는다.
 * 기능이 틀리면 지난 요구와 지난 출력이 달라진다. 그때의 한계는 성질 5와 TC-013이 본다.
 */
void prove_normal_function_not_clamped(void)
{
    app_t app;
    output_stage_t out;
    permille_t pedal = nondet_int32();
    bool brake = nondet_bool();
    gear_t gear = (gear_t)nondet_int32();
    torque_t prev;
    uint32_t clamp_count;
    torque_t req;
    torque_t allowed;
    torque_t sent;

    /* 켠 직후의 상태는 맞물린 상태다 */
    app_init(&app);
    output_stage_init(&out);
    assert(app.prev == out.last_out);
    assert(!out.latched);
    assert(out.excess_cycles == 0);

    /* 맞물린 상태 가운데 아무것이나 */
    app.prev = nondet_int32();
    __CPROVER_assume((app.prev >= -2500) && (app.prev <= 2500));
    out.last_out = app.prev;
    out.latched = false;
    out.excess_cycles = 0;
    out.clamp_count = nondet_uint32();
    prev = app.prev;
    clamp_count = out.clamp_count;

    /* 한 주기: 제품 (src/vcu/vcu.c)과 같은 순서 */
    req = app_step(&app, pedal, brake, gear);
    allowed = monitor_allowed_torque(pedal, brake, gear);
    allowed = monitor_limit_rise(allowed, out.last_out, gear);
    sent = output_stage_step(&out, req, allowed, gear);

    /* 그 주기의 토크 요구는 그대로 나간다 */
    assert(sent == req);
    assert(out.clamp_count == clamp_count);
    /* 한 주기 뒤에도 맞물린 상태다 */
    assert(app.prev == out.last_out);
    assert(!out.latched);
    assert(out.excess_cycles == 0);
    assert((app.prev >= -2500) && (app.prev <= 2500));
    /* 기능의 토크 요구는 지난 요구에서 25 Nm 넘게 오르지 않는다. 방향이 바뀌면 0에서 센다 */
    if (req > 0) {
        assert(req <= (((prev > 0) ? prev : 0) + 250));
    }
    if (req < 0) {
        assert(req >= (((prev < 0) ? prev : 0) - 250));
    }
    /* 허용 토크는 토크 요구를 5 Nm 넘게 앞서지 않는다 */
    assert((allowed - ((req < 0) ? -req : req)) <= 50);
}
