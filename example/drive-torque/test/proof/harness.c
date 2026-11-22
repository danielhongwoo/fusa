/*
 * 책의 예제 코드다. 실제 제품에 쓸 수 없다.
 * CBMC로 증명할 성질. 성질마다 함수 하나이고, tools/prove.sh가 하나씩 돌린다.
 *
 * 성질에는 요구사항의 숫자를 그대로 적는다 (토크의 단위는 0.1 Nm). 제품 코드의 상수 이름을 쓰지 않는다.
 *
 * 증명이 말해 주는 것: 이 C 코드는 가능한 모든 입력에서 아래 assert를 지킨다.
 * 말해 주지 않는 것: compiler가 만든 기계어, 실행 시간, 하드웨어의 고장, 주기를 놓치는 경우.
 *
 * 성질 6과 7은 기능, 감시, 출력 단계를 이어서 돌린다. 감시와 출력 단계를 잇는 것은 제품
 * (src/vcu/vcu.c의 task_monitor_output)이 부르는 것과 같은 함수 (monitor_output_cycle)다.
 * 처음에는 그 순서를 여기에 옮겨 적었고, 검토에서 지적을 받아 함수 하나로 묶었다.
 * 증명의 밖에 남는 것은 제품이 그 함수에 무엇을 넘기는가다 (기능의 토크 요구, 안전한 페달 값,
 * 브레이크, 기어). 그것은 시나리오 test와 변이 검사가 지킨다.
 */
#include <assert.h>

#include "app.h"
#include "e2e.h"
#include "flow.h"
#include "input.h"
#include "monitor.h"
#include "reaction.h"

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

/* 성질 3 (SWR-08, SWR-09): 어떤 상태에서 시작해도 출력은 허용 토크 안에 있다.
 * 고장 대응의 상태가 토크 0이나 구동 허용 차단이면 출력은 0이고, 그 상태는 이 걸음으로 풀리지 않는다.
 * 깎인 주기가 5번째로 이어진 주기에는 구동 허용 차단이 된다 */
void prove_output_stage(void)
{
    output_stage_t st;
    reaction_t reaction;
    torque_t req = nondet_int32();
    torque_t allowed = nondet_int32();
    gear_t gear = (gear_t)nondet_int32();
    reaction_state_t before;
    reaction_state_t after;
    uint8_t excess_before;
    torque_t out;

    st.excess_cycles = nondet_uint8();
    st.clamp_count = nondet_uint32();
    st.last_out = nondet_int32();
    reaction.state = (reaction_state_t)nondet_int32(); /* 망가진 값도 포함한다 */
    __CPROVER_assume(st.excess_cycles <= 5);
    __CPROVER_assume((allowed >= 0) && (allowed <= 2500));
    before = reaction_state(&reaction);
    excess_before = st.excess_cycles;

    out = output_stage_step(&st, &reaction, req, allowed, gear);
    after = reaction_state(&reaction);

    assert(out <= allowed);
    assert(out >= -allowed);
    assert(after >= before);
    if ((after == REACTION_ZERO) || (after == REACTION_CUT)) {
        assert(out == 0);
    }
    if ((excess_before == 4) && (output_clamp(req, allowed, gear) != req)) {
        assert(after == REACTION_CUT);
    }
    assert(st.last_out == out);
}

/* 성질 4 (SWR-01, SWR-03, SWR-04, SWR-14): 안전한 페달 값은 0-1000이고, 고장은 풀리지 않으며, 고장이면 0이다.
 * 최근 주기들의 기록과 적을 자리는 어떤 값이든 된다 (정하지 않은 변수를 CBMC는 모든 값으로 본다).
 * memory의 값이 틀려도 배열 밖을 쓰지 않아야 한다 */
void prove_pedal_check(void)
{
    pedal_check_t st;
    inputs_t in;
    bool was_fault;
    uint8_t was_excluded;
    bool range1;
    bool range2;
    permille_t pedal;
    int bad_in_window = 0;

    st.suspect = nondet_uint8();
    st.excluded = nondet_uint8();
    st.bad_cycles = nondet_uint8();
    st.good_cycles = nondet_uint8();
    st.ready = nondet_bool();
    st.fault = nondet_bool();
    __CPROVER_assume(st.bad_cycles <= 3);
    __CPROVER_assume(st.good_cycles <= 3);
    in.apps1_mv = nondet_int32(); /* HAL이 어떤 값을 주더라도 */
    in.apps2_mv = nondet_int32();
    in.brake1 = nondet_bool();
    in.brake2 = nondet_bool();
    in.gear = GEAR_D;
    was_fault = st.fault;
    was_excluded = st.excluded;
    range1 = (in.apps1_mv < 250) || (in.apps1_mv > 4750);
    range2 = (in.apps2_mv < 125) || (in.apps2_mv > 2375);

    pedal = pedal_check_step(&st, &in);

    assert(pedal >= 0);
    assert(pedal <= 1000);
    if (was_fault) {
        assert(st.fault);
    }
    /* SWR-24: 뺀 채널은 다시 넣지 않고, 다른 채널로 바꾸지도 않는다 */
    if ((was_excluded == 1) || (was_excluded == 2)) {
        assert(st.excluded == was_excluded);
    }
    /* SWR-24: 채널을 새로 빼는 것은 그 채널만 범위를 벗어난 주기에만 한다 */
    if (st.excluded != was_excluded) {
        assert(((st.excluded == 1) && range1 && !range2) || ((st.excluded == 2) && range2 && !range1));
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
    /* SWR-24: 채널을 빼는 주기에 페달 고장도 함께 난다면, 그것은 기록에 쌓인 실패 (SWR-14) 때문이다.
     * 처음에는 "그 주기에 페달 고장으로 가지 않는다"고 적었고, 증명이 반례를 냈다 */
    if ((st.excluded != was_excluded) && st.fault && !was_fault) {
        assert(bad_in_window > 10);
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
 *                고장 대응의 상태가 정상이고, 이어서 깎인 주기가 없다.
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
    reaction_t reaction;
    permille_t pedal = nondet_int32();
    bool brake = nondet_bool();
    gear_t gear = (gear_t)nondet_int32();
    torque_t prev;
    uint32_t clamp_count;
    torque_t req;
    torque_t allowed;
    torque_t sent;
    bool limp = nondet_bool();

    /* 켠 직후의 상태는 맞물린 상태다 */
    app_init(&app);
    output_stage_init(&out);
    reaction_init(&reaction);
    assert(app.prev == out.last_out);
    assert(reaction_state(&reaction) == REACTION_NORMAL);
    assert(out.excess_cycles == 0);

    /* 맞물린 상태 가운데 아무것이나 */
    app.prev = nondet_int32();
    __CPROVER_assume((app.prev >= -2500) && (app.prev <= 2500));
    out.last_out = app.prev;
    /* 고장 대응의 상태는 정상이거나 줄여 감이다. 줄여 감에서는 기능에 주는 페달 값이 잘린다 */
    reaction.state = limp ? REACTION_LIMP : REACTION_NORMAL;
    out.excess_cycles = 0;
    out.clamp_count = nondet_uint32();
    prev = app.prev;
    clamp_count = out.clamp_count;

    /* 한 주기: 제품 (src/vcu/vcu.c)이 부르는 것과 같은 함수 */
    req = app_step(&app, pedal, brake, gear, reaction_app_limit(reaction_state(&reaction)));
    sent = monitor_output_cycle(&out, &reaction, req, pedal, brake, gear, &allowed);

    /* 그 주기의 토크 요구는 그대로 나간다 */
    assert(sent == req);
    assert(out.clamp_count == clamp_count);
    /* 한 주기 뒤에도 맞물린 상태다 */
    assert(app.prev == out.last_out);
    assert(reaction_state(&reaction) == (limp ? REACTION_LIMP : REACTION_NORMAL));
    assert(out.excess_cycles == 0);
    assert((app.prev >= -2500) && (app.prev <= 2500));
    /* 줄여 감에서 나가는 토크는 35 Nm를 넘지 않는다 */
    if (limp) {
        assert((sent <= 350) && (sent >= -350));
    }
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

/* 성질 8 (SWR-25): 고장 대응의 상태는 안전한 쪽으로만 바뀐다.
 * 상태를 담은 변수와 알린 값이 어떤 값이든 (망가진 값이든) 성립한다.
 * 알 수 없는 값은 구동 허용 차단으로 읽힌다 */
void prove_reaction(void)
{
    reaction_t reaction;
    reaction_state_t wanted = (reaction_state_t)nondet_int32();
    reaction_state_t before;
    reaction_state_t after;

    reaction.state = (reaction_state_t)nondet_int32();
    before = reaction_state(&reaction);
    assert((before == REACTION_NORMAL) || (before == REACTION_LIMP) || (before == REACTION_ZERO)
           || (before == REACTION_CUT));
    if ((reaction.state != REACTION_NORMAL) && (reaction.state != REACTION_LIMP)
        && (reaction.state != REACTION_ZERO)) {
        assert(before == REACTION_CUT);
    }

    reaction_raise(&reaction, wanted);
    after = reaction_state(&reaction);

    assert(after >= before);
    if ((wanted == REACTION_LIMP) || (wanted == REACTION_ZERO) || (wanted == REACTION_CUT)) {
        assert(after >= wanted);
    }
    if ((wanted != REACTION_NORMAL) && (wanted != REACTION_LIMP) && (wanted != REACTION_ZERO)) {
        assert(after == REACTION_CUT);
    }
    if (wanted == REACTION_NORMAL) {
        assert(after == before); /* "정상"을 알려서는 아무것도 풀리지 않는다 */
    }

    /* 상태에서 나오는 출력 */
    assert(reaction_torque_cap(after) >= 0);
    assert(reaction_torque_cap(after) <= 2500);
    if (after == REACTION_LIMP) {
        assert(reaction_torque_cap(after) == 400);
    }
    if ((after == REACTION_ZERO) || (after == REACTION_CUT)) {
        assert(reaction_torque_cap(after) == 0);
        assert(reaction_warning(after) == 2);
    }
    assert(reaction_enable(after) == (after != REACTION_CUT));
    if (after == REACTION_NORMAL) {
        assert(reaction_warning(after) == 0);
    }
    /* SWR-24: 기능이 요구할 수 있는 크기의 상한은 줄여 감에서 35 Nm, 그 밖에는 최대 토크다 */
    assert(reaction_app_limit(REACTION_LIMP) == 350);
    assert(reaction_app_limit(wanted) == ((wanted == REACTION_LIMP) ? 350 : 2500));
}

/* 방향 d (GEAR_D나 GEAR_R)로의 토크의 크기. 반대 방향이면 0 */
static torque_t toward(torque_t v, gear_t d)
{
    if (d == GEAR_D) {
        return (v > 0) ? v : 0;
    }
    return (v < 0) ? -v : 0;
}

/*
 * 성질 7 (SWR-06, SWR-13): 기능이 어떻게 틀려도, 나가는 토크는 정상인 기능의 토크 요구를
 * 5 Nm 넘게 앞서지 않는다. 입력이 어떻게 바뀌어도 그렇다.
 *
 * 두 궤적을 나란히 돌린다. 하나는 정상인 기능이 스스로 기억하는 지난 요구 (normal.prev)이고,
 * 다른 하나는 틀린 기능의 요구가 감시와 출력 단계를 거쳐 실제로 나간 토크 (out.last_out)다.
 * 둘은 같은 입력을 받는다.
 *   묶인 상태: 전진 쪽으로도 후진 쪽으로도, 지난 출력의 크기가 정상인 기능의 지난 요구의 크기를
 *              5 Nm 넘게 앞서지 않는다.
 * 묶인 상태에서 시작하면, 입력과 틀린 기능의 요구가 무엇이든 한 주기 뒤에도 묶인 상태다.
 * 켠 직후 (둘 다 0)는 묶인 상태다. 둘을 이으면 몇 주기를 돌아도 성립한다.
 *
 * 전제 (증명이 말해 주지 않는 것)
 *   - 감시와 출력 단계가 주기마다 실행되고, 감시가 받는 입력은 정상인 기능이 받았을 입력과 같다.
 *   - 출력 단계가 기억하는 지난 출력을 다른 코드가 바꾸지 않는다 (memory의 고장이 없다).
 *   - 정상인 기능은 src/app/app.c 그대로다. 견주는 대상이 이 코드이므로, 이 코드의 요구사항이 틀렸으면
 *     증명도 틀린 것을 기준으로 삼는다.
 *   - 입력이 옳다는 것은 이 증명이 말하지 않는다. 견주는 기준이 같은 입력을 받은 정상인 기능이므로,
 *     입력 검사가 틀려 안전한 페달 값이 실제보다 크면 기준도 함께 틀린다.
 * 고장 대응의 상태는 어떤 값이든 된다. 줄여 감의 상한이 걸려도, 토크 0이나 구동 허용 차단이어도 성립한다.
 * 줄여 감에 들어가는 길 (SWR-24)을 넣으면 기능이 그 상태를 받는 것과 함께 다시 본다.
 * 재는 것은 VCU가 보낸 토크 요구다. inverter가 낸 토크가 아니다.
 */
void prove_faulty_function_bounded(void)
{
    app_t normal;
    output_stage_t out;
    reaction_t reaction;
    permille_t pedal = nondet_int32();
    bool brake = nondet_bool();
    gear_t gear = (gear_t)nondet_int32();
    torque_t faulty_req = nondet_int32(); /* 틀린 기능은 무엇이든 요구할 수 있다 */
    torque_t normal_req;
    torque_t allowed;
    torque_t sent;

    /* 켠 직후의 상태는 묶인 상태다 */
    app_init(&normal);
    output_stage_init(&out);
    reaction_init(&reaction);
    assert(toward(out.last_out, GEAR_D) <= (toward(normal.prev, GEAR_D) + 50));
    assert(toward(out.last_out, GEAR_R) <= (toward(normal.prev, GEAR_R) + 50));

    /* 묶인 상태 가운데 아무것이나. 출력 단계의 나머지 상태는 어떤 값이든 된다 */
    normal.prev = nondet_int32();
    out.last_out = nondet_int32();
    out.excess_cycles = nondet_uint8();
    out.clamp_count = nondet_uint32();
    reaction.state = (reaction_state_t)nondet_int32(); /* 고장 대응의 상태도 어떤 값이든 된다 */
    __CPROVER_assume((normal.prev >= -2500) && (normal.prev <= 2500));
    __CPROVER_assume((out.last_out >= -2500) && (out.last_out <= 2500));
    __CPROVER_assume(out.excess_cycles <= 5);
    __CPROVER_assume(toward(out.last_out, GEAR_D) <= (toward(normal.prev, GEAR_D) + 50));
    __CPROVER_assume(toward(out.last_out, GEAR_R) <= (toward(normal.prev, GEAR_R) + 50));

    /* 한 주기: 정상인 기능은 견주려고 나란히 돌릴 뿐이고, 출력으로 가는 것은 틀린 기능의 요구다 */
    normal_req = app_step(&normal, pedal, brake, gear, 2500);
    sent = monitor_output_cycle(&out, &reaction, faulty_req, pedal, brake, gear, &allowed);

    /* 나간 토크는 정상인 기능의 토크 요구를 5 Nm 넘게 앞서지 않는다 */
    assert(toward(sent, GEAR_D) <= (toward(normal_req, GEAR_D) + 50));
    assert(toward(sent, GEAR_R) <= (toward(normal_req, GEAR_R) + 50));
    /* 한 주기 뒤에도 묶인 상태다 */
    assert(out.last_out == sent);
    assert(normal.prev == normal_req);
    assert((out.last_out >= -2500) && (out.last_out <= 2500));
    assert((normal.prev >= -2500) && (normal.prev <= 2500));
}

/* 성질 9 (SWR-15): 브레이크의 판정. 어느 접점이든 밟음을 가리키면 판정은 밟음이다.
 * 판정이 놓음이면 두 접점이 모두 놓음을 가리키고 있다. 고장은 풀리지 않고, 고장이면 밟음이다.
 * 세는 값이 어떤 값에서 시작해도 (memory의 값이 틀려도) 성립한다 */
void prove_brake_check(void)
{
    brake_check_t st;
    inputs_t in;
    bool was_fault;
    bool pressed;

    st.release_cycles = nondet_uint8();
    st.mismatch_cycles = nondet_uint8();
    st.pressed = nondet_bool();
    st.fault = nondet_bool();
    in.apps1_mv = 0;
    in.apps2_mv = 0;
    in.brake1 = nondet_bool();
    in.brake2 = nondet_bool();
    in.gear = GEAR_D;
    was_fault = st.fault;

    pressed = brake_check_step(&st, &in);

    assert(pressed == st.pressed);
    if (in.brake1 || in.brake2) {
        assert(pressed);
    }
    if (!pressed) {
        assert(!in.brake1 && !in.brake2);
        assert(!st.fault);
    }
    if (was_fault) {
        assert(st.fault);
    }
    if (st.fault) {
        assert(pressed);
    }
}

/* 부호 있는 값을 전송하는 32 bit로 편 것. 제품의 코드 (src/com/e2e.c)와 따로 적었다 */
static uint32_t wire(int32_t v)
{
    return (v >= 0) ? (uint32_t)v : (0xFFFFFFFFu - (uint32_t)(-(v + 1)));
}

/*
 * 성질 10 (SWR-17, SWR-18): 메시지의 보호와 검사의 규칙. 받는 쪽의 상태가 무엇이었든 아래가 성립한다.
 *   가. 보내는 쪽은 값을 그대로 싣고, counter는 0-15 안에서 1 오른다.
 *   나. 보낸 메시지를 그대로, 제때 받으면: 처음 받았거나 counter가 지난 것에서 1-3 앞섰을 때,
 *       그리고 그때에만 유효하다.
 *   다. 같은 메시지를 새 메시지로 한 번 더 받으면 무효다.
 *   라. 받은 적이 없거나 받은 뒤 50 ms가 넘었으면 무효다.
 *   마. 새 메시지가 없으면 판정이 바뀌지 않는다 (50 ms 안에서).
 */
void prove_message_rules(void)
{
    e2e_tx_t tx;
    e2e_rx_t rx0;
    e2e_rx_t rx;
    frame_t sent;
    uint8_t data_id = nondet_uint8();
    int32_t value = nondet_int32();
    uint32_t age_ok = nondet_uint32();
    uint32_t age_any = nondet_uint32();
    bool seen = nondet_bool();
    bool fresh = nondet_bool();
    uint8_t step;
    bool valid;

    /* 가. 보내는 쪽의 상태가 망가져 있었더라도 */
    tx.counter = nondet_uint8();
    e2e_protect(&tx, data_id, value, &sent);
    assert(sent.value == value);
    assert(sent.counter <= 15);
    assert(tx.counter == ((sent.counter + 1) % 16));

    rx0.last_counter = nondet_uint8();
    rx0.synced = nondet_bool();
    rx0.ok = nondet_bool();
    __CPROVER_assume(rx0.last_counter <= 15);
    __CPROVER_assume(age_ok <= 50u);
    step = (uint8_t)((sent.counter + 16 - rx0.last_counter) % 16);

    /* 나 */
    rx = rx0;
    valid = e2e_check(&rx, data_id, &sent, true, true, age_ok);
    assert(valid == (!rx0.synced || ((step >= 1) && (step <= 3))));
    /* 다 */
    valid = e2e_check(&rx, data_id, &sent, true, true, age_ok);
    assert(!valid);

    /* 라 */
    rx = rx0;
    valid = e2e_check(&rx, data_id, &sent, seen, fresh, age_any);
    if (!seen || (age_any > 50u)) {
        assert(!valid);
    }
    /* 마 */
    if (seen && !fresh && (age_any <= 50u)) {
        assert(valid == rx0.ok);
    }
}

/*
 * 성질 11 (SWR-18): 전송 중에 바뀐 메시지는 무효다. 받는 쪽의 상태가 무엇이었든, 제때 받았더라도 그렇다.
 *   가. 값의 bit 하나가 바뀌었다.
 *   나. counter의 bit 하나가 바뀌었다.
 *   다. CRC의 bit 하나가 바뀌었다.
 *   라. 다른 종류의 메시지다 (data ID가 다르다).
 * 그런 메시지는 counter의 기준도 바꾸지 않는다.
 * 말해 주지 않는 것: 값의 bit가 둘 넘게 바뀌는 경우. CRC가 8 bit이므로 잡지 못하는 조합이 있다
 * (아무렇게나 바뀐 메시지 256개 가운데 하나쯤은 CRC가 우연히 맞는다).
 * 보내는 쪽이 틀린 값을 옳은 counter와 CRC로 보내는 경우도 이 검사의 밖이다.
 *
 * 성질 10과 한 함수로 묶으면 증명이 10분 안에 끝나지 않았다. CRC는 XOR로 이루어진 계산이고,
 * 이 도구가 쓰는 풀이 방식 (SAT)은 XOR이 길게 이어진 식에 약하다. 나누니 몇 초에 끝난다.
 */
void prove_message_change_detected(void)
{
    e2e_tx_t tx;
    e2e_rx_t rx0;
    e2e_rx_t rx;
    frame_t sent;
    frame_t changed;
    uint8_t data_id = nondet_uint8();
    uint8_t check_id = data_id;
    uint8_t other_id = nondet_uint8();
    int32_t value = nondet_int32();
    int32_t other_value = nondet_int32();
    uint8_t which = nondet_uint8();
    uint8_t bit = nondet_uint8();
    uint32_t age_ok = nondet_uint32();
    bool valid;

    tx.counter = nondet_uint8();
    e2e_protect(&tx, data_id, value, &sent);
    rx0.last_counter = nondet_uint8();
    rx0.synced = nondet_bool();
    rx0.ok = nondet_bool();
    __CPROVER_assume(age_ok <= 50u);

    changed = sent;
    if ((which % 4u) == 0u) {
        /* 가. 전송하는 32 bit 가운데 하나만 다른 값 */
        __CPROVER_assume((wire(other_value) ^ wire(sent.value)) == ((uint32_t)1u << (bit % 32u)));
        changed.value = other_value;
    } else if ((which % 4u) == 1u) {
        changed.counter = (uint8_t)(changed.counter ^ (uint8_t)(1u << (bit % 8u)));
    } else if ((which % 4u) == 2u) {
        changed.crc = (uint8_t)(changed.crc ^ (uint8_t)(1u << (bit % 8u)));
    } else {
        __CPROVER_assume(other_id != data_id);
        check_id = other_id;
    }

    rx = rx0;
    valid = e2e_check(&rx, check_id, &changed, true, true, age_ok);
    assert(!valid);
    assert((rx.last_counter == rx0.last_counter) && (rx.synced == rx0.synced));
}

/*
 * 성질 12 (SWR-16): 받아들인 기어. 기억한 방향과 세는 값이 어떤 값에서 시작해도 (망가진 값이어도) 성립한다.
 *   가. 받아들인 기어는 P, N이거나 운전자가 고른 방향이다. 고르지 않은 방향은 나오지 않는다.
 *   나. 방향을 받아들였으면 그것이 기억한 방향이다.
 *   다. 받아들인 방향이 지난번에 기억한 방향과 다르면, 차량 속도가 유효하고 0 이상 1.38 m/s 이하였다.
 *   라. 기억한 방향은 받아들일 때에만 바뀐다.
 *   마. 주의는 받아들이지 못한 주기가 50번 이어진 때에만 요청하고, 받아들이거나 방향을 고르지 않으면 거둔다.
 * 말해 주지 않는 것: 차량 속도의 값이 옳은가, 차가 실제로 어느 쪽으로 가고 있는가.
 */
void prove_gear_check(void)
{
    gear_check_t st;
    gear_t selected = (gear_t)nondet_int32();
    bool speed_valid = nondet_bool();
    speed_t speed = nondet_int32();
    gear_t old_direction;
    uint8_t old_reject;
    gear_t accepted;

    st.direction = (gear_t)nondet_int32();
    st.reject_cycles = nondet_uint8();
    st.caution = nondet_bool();
    old_direction = st.direction;
    old_reject = st.reject_cycles;

    accepted = gear_check_step(&st, selected, speed_valid, speed);

    /* 가 */
    assert((accepted == GEAR_P) || (accepted == GEAR_N) || (accepted == GEAR_D) || (accepted == GEAR_R));
    if (accepted == GEAR_P) {
        assert(selected == GEAR_P);
    }
    if ((accepted == GEAR_D) || (accepted == GEAR_R)) {
        assert(accepted == selected);
        /* 나 */
        assert(st.direction == accepted);
        /* 다 */
        if (accepted != old_direction) {
            assert(speed_valid && (speed >= 0) && (speed <= 138));
        }
    }
    /* 라 */
    if (st.direction != old_direction) {
        assert((st.direction == accepted) && (accepted == selected));
    }
    /* 마 */
    assert(st.caution == (st.reject_cycles >= 50));
    if (st.caution) {
        assert(old_reject >= 49);
        assert(((selected == GEAR_D) || (selected == GEAR_R)) && (accepted == GEAR_N));
    }
    if ((accepted == GEAR_D) || (accepted == GEAR_R) || ((selected != GEAR_D) && (selected != GEAR_R))) {
        assert(st.reject_cycles == 0);
    }
}

/*
 * 성질 13 (SWR-19): inverter가 알린 토크의 검사. 기록, 적을 자리, 세는 값이 어떤 값에서 시작해도
 * (memory의 값이 틀려도) 성립한다.
 *   가. 사건은 범위를 벗어난 횟수가 3 이상이거나 무효인 횟수가 10 이상일 때, 그리고 그때에만 알린다.
 *   나. 유효하고, 알린 토크가 -280 - 280 Nm 밖이면 반드시 벗어난 것으로 센다 (기록이 무엇이든).
 *   다. 유효하고, 알린 토크가 -30 - 30 Nm 안이면 반드시 범위 안으로 본다 (기록이 무엇이든. 0은 늘 범위에 든다).
 *   라. 유효하고 범위 안이면 벗어난 횟수와 무효인 횟수가 0이 된다.
 *   마. 무효이면 알린 값을 보지 않고, 벗어난 횟수는 그대로다.
 *   바. 기록할 때 배열 밖을 쓰지 않는다.
 * 말해 주지 않는 것: 범위가 최근에 보낸 값에서 옳게 나오는가. 그것은 unit test (TC-020)가 값으로 본다.
 */
void prove_inverter_check(void)
{
    inverter_check_t st;
    bool valid = nondet_bool();
    torque_t reported = nondet_int32();
    torque_t sent = nondet_int32();
    uint8_t old_out;
    uint8_t old_invalid;
    bool event;

    for (int i = 0; i < 5; i++) {
        st.sent[i] = nondet_int32();
    }
    st.pos = nondet_uint8();
    st.out_cycles = nondet_uint8();
    st.invalid_cycles = nondet_uint8();
    old_out = st.out_cycles;
    old_invalid = st.invalid_cycles;

    event = inverter_check_step(&st, valid, reported);

    /* 가 */
    assert(event == ((st.out_cycles >= 3) || (st.invalid_cycles >= 10)));
    if (valid) {
        assert(st.invalid_cycles == 0);
        /* 나 */
        if ((reported > 2800) || (reported < -2800)) {
            assert((st.out_cycles == (old_out + 1)) || ((old_out >= 3) && (st.out_cycles == old_out)));
        }
        /* 다, 라 */
        if ((reported >= -300) && (reported <= 300)) {
            assert(st.out_cycles == 0);
            assert(!event);
        }
        assert((st.out_cycles == 0) || (st.out_cycles == (old_out + 1)) || (st.out_cycles == old_out));
    } else {
        /* 마 */
        assert(st.out_cycles == old_out);
        assert((st.invalid_cycles == (old_invalid + 1)) || ((old_invalid >= 10) && (st.invalid_cycles == old_invalid)));
    }

    /* 바 */
    inverter_check_record(&st, sent);
    assert((st.pos >= 1) && (st.pos <= 5));
    assert(st.sent[st.pos - 1] == sent);
}

/*
 * 성질 14 (SWR-20): 실행의 확인. 표시, 표시의 수, 질문의 번호가 어떤 값에서 시작해도 성립한다.
 *   가. 맞다고 하는 것은 표시가 셋이고 1, 2, 3의 순서일 때뿐이다.
 *   나. 그때 보낸 토크의 크기가 허용 토크 안이면, 답은 질문의 번호로 정해진 값 하나다.
 *       허용 토크를 넘으면 그 값이 아니다.
 *   다. 표시를 남길 때 배열 밖을 쓰지 않고, 표시의 수는 4를 넘지 않는다.
 *   라. 주기를 닫으면 표시가 없는 상태가 되고 (값도 남지 않는다), 질문의 번호가 1 오른다 (255 다음은 0).
 * 말해 주지 않는 것: 순서가 틀린 표시에서 나온 답이 옳은 답과 반드시 다른가. 답이 8 bit여서
 * 우연히 같은 조합이 있다. 그래서 답을 쓰기 전에 가.를 따로 확인한다.
 */
void prove_flow(void)
{
    flow_t f;
    flow_t before;
    torque_t allowed = nondet_int32();
    torque_t out = nondet_int32();
    uint8_t mark = nondet_uint8();
    uint32_t expected;
    uint8_t answer;
    bool ok;

    for (int i = 0; i < 3; i++) {
        f.marks[i] = nondet_uint8();
    }
    f.count = nondet_uint8();
    f.question = nondet_uint8();
    before = f;
    __CPROVER_assume(allowed >= 0);

    /* 가 */
    ok = flow_check(&f);
    assert(ok == ((f.count == 3) && (f.marks[0] == 1) && (f.marks[1] == 2) && (f.marks[2] == 3)));
    /* 나 */
    answer = flow_answer(&f, allowed, out);
    expected = (((uint32_t)f.question * 29791u) + 1026u) & 0xFFu;
    if (ok) {
        if ((out <= allowed) && (out >= -allowed)) {
            assert(answer == expected);
        } else {
            assert(answer != expected);
        }
    }
    /* 다 */
    flow_mark(&f, mark);
    assert(f.count <= 4);
    if (before.count < 3) {
        assert(f.count == (before.count + 1));
        assert(f.marks[before.count] == mark);
    } else {
        assert(f.count == 4);
    }
    assert(f.question == before.question);
    /* 라 */
    flow_next(&f);
    assert(f.count == 0);
    assert((f.marks[0] == 0) && (f.marks[1] == 0) && (f.marks[2] == 0));
    assert(!flow_check(&f));
    assert(f.question == ((before.question + 1) % 256));
}
