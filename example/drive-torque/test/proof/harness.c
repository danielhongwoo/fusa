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

/* 성질 4 (SWR-01, SWR-03, SWR-04): 안전한 페달 값은 0-1000이고, 고장은 풀리지 않으며, 고장이면 0이다 */
void prove_pedal_check(void)
{
    pedal_check_t st;
    inputs_t in;
    bool was_fault;
    permille_t pedal;

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
}
