/*
 * 책의 예제 코드다. 실제 제품에 쓸 수 없다.
 * 요구사항에 따른 unit test: 입력 검사, 감시, 출력 단계.
 * test마다 어느 요구사항을 보는지 "TC-번호: SWR-번호"로 적는다.
 *
 * 기댓값은 요구사항 (docs/requirements.yaml)의 숫자를 그대로 적는다.
 * 제품 코드의 상수 이름을 쓰지 않는다. 상수가 잘못 바뀌면 test가 실패해야 하기 때문이다.
 */
#include "app.h"
#include "e2e.h"
#include "input.h"
#include "monitor.h"
#include "reaction.h"
#include "test.h"

/* 센서가 정상일 때의 전압 */
static millivolt_t apps1(permille_t pedal) { return 500 + (4 * pedal); }
static millivolt_t apps2(permille_t pedal) { return 250 + (2 * pedal); }

static inputs_t inputs(millivolt_t a1, millivolt_t a2)
{
    inputs_t in = { a1, a2, false, false, GEAR_D };
    return in;
}

/* 검사를 통과하는 입력으로 켠 직후의 구간을 지난다 */
static void make_ready(pedal_check_t *st)
{
    inputs_t in = inputs(apps1(0), apps2(0));
    pedal_check_init(st);
    for (int i = 0; i < 3; i++) {
        (void)pedal_check_step(st, &in);
    }
}

/* 운전자의 입력 한 벌 */
typedef struct {
    permille_t pedal;
    bool brake;
    gear_t gear;
} drive_t;

/* 감시와 출력 단계를 한 주기 돌린다. 제품 (src/vcu/vcu.c의 task_monitor_output)이 부르는 것과 같은 함수다.
 * 그 주기의 허용 토크를 allowed에 적고, inverter로 보낼 토크를 돌려준다 */
static torque_t chain_step(output_stage_t *out, reaction_t *reaction, torque_t req, const drive_t *d,
                           torque_t *allowed)
{
    return monitor_output_cycle(out, reaction, req, d->pedal, d->brake, d->gear, allowed);
}

static bool is_cut(const reaction_t *reaction) { return reaction_state(reaction) == REACTION_CUT; }

static torque_t magnitude(torque_t v) { return (v < 0) ? -v : v; }

/* TC-001: SWR-01 두 채널의 전압을 같은 단위로 바꾼다 */
static void tc_001(void)
{
    pedal_check_t st;
    inputs_t in;

    make_ready(&st);
    in = inputs(apps1(0), apps2(0));
    CHECK_EQ(pedal_check_step(&st, &in), 0);
    in = inputs(apps1(500), apps2(500));
    CHECK_EQ(pedal_check_step(&st, &in), 500);
    in = inputs(apps1(1000), apps2(1000));
    CHECK_EQ(pedal_check_step(&st, &in), 1000);
    /* 센서 범위의 끝을 조금 넘는 전압은 0과 1000으로 자른다 */
    in = inputs(400, 200);
    CHECK_EQ(pedal_check_step(&st, &in), 0);
    in = inputs(4600, 2300);
    CHECK_EQ(pedal_check_step(&st, &in), 1000);
}

/* 같은 입력을 3번 넣은 뒤에 페달 고장인지 돌려준다 */
static bool faults_after_cycles(millivolt_t a1, millivolt_t a2)
{
    pedal_check_t st;
    inputs_t in = inputs(a1, a2);

    make_ready(&st);
    for (int i = 0; i < 3; i++) {
        (void)pedal_check_step(&st, &in);
    }
    return st.fault;
}

/* TC-002: SWR-02 채널마다 범위를 보고, 두 채널을 서로 견준다 */
static void tc_002(void)
{
    /* 정상 */
    CHECK(!faults_after_cycles(apps1(300), apps2(300)));
    /* 범위: 채널 1 */
    CHECK(!faults_after_cycles(250, apps2(0)));
    CHECK(faults_after_cycles(249, apps2(0)));
    CHECK(!faults_after_cycles(4750, apps2(1000)));
    CHECK(faults_after_cycles(4751, apps2(1000)));
    /* 범위: 채널 2 */
    CHECK(!faults_after_cycles(apps1(0), 125));
    CHECK(faults_after_cycles(apps1(0), 124));
    CHECK(!faults_after_cycles(apps1(1000), 2375));
    CHECK(faults_after_cycles(apps1(1000), 2376));
    /* 두 채널의 차이: 50까지는 받아들이고 51부터는 불일치다 */
    CHECK(!faults_after_cycles(apps1(350), apps2(300)));
    CHECK(faults_after_cycles(apps1(352), apps2(300)));
    CHECK(!faults_after_cycles(apps1(300), apps2(350)));
    CHECK(faults_after_cycles(apps1(300), apps2(351)));
}

/* TC-003: SWR-03 검사 실패가 3주기 이어지면 페달 고장으로 고정한다 */
static void tc_003(void)
{
    pedal_check_t st;
    inputs_t good = inputs(apps1(300), apps2(300));
    inputs_t bad = inputs(apps1(900), apps2(300));

    /* 2주기 실패한 뒤 통과하면 다시 센다 */
    make_ready(&st);
    (void)pedal_check_step(&st, &bad);
    (void)pedal_check_step(&st, &bad);
    CHECK(!st.fault);
    (void)pedal_check_step(&st, &good);
    (void)pedal_check_step(&st, &bad);
    (void)pedal_check_step(&st, &bad);
    CHECK(!st.fault);
    /* 3번째로 이어서 실패한 주기에 고장이 된다 */
    (void)pedal_check_step(&st, &bad);
    CHECK(st.fault);
    /* 그 뒤에 통과해도 고장은 유지된다 */
    for (int i = 0; i < 10; i++) {
        (void)pedal_check_step(&st, &good);
    }
    CHECK(st.fault);

    /* 실패와 통과가 번갈아 나오면 이어지는 횟수로는 판정되지 않는다.
     * 그런 간헐 고장은 SWR-14 (TC-014)가 맡는다. 여기서는 실패 10번까지 판정이 없다는 것만 본다 */
    make_ready(&st);
    for (int i = 0; i < 10; i++) {
        (void)pedal_check_step(&st, &bad);
        (void)pedal_check_step(&st, &good);
    }
    CHECK(!st.fault);
}

/* 실패하는 입력의 종류. 창은 어느 쪽의 실패든 세어야 한다 */
static bool fail_by_range; /* 참이면 채널 1이 전압 범위를 벗어난다. 거짓이면 두 채널이 어긋난다 */

/* 정해진 주기에만 검사에 실패하는 입력을 넣고, 처음 페달 고장이 된 주기를 돌려준다. 없으면 -1.
 * is_bad(i)가 참인 주기에 실패한다 */
static int first_fault_cycle(pedal_check_t *st, int cycles, bool (*is_bad)(int))
{
    /* 범위 실패는 페달을 끝까지 밟은 채 채널 1만 4800 mV로 둔다.
     * 페달 위치로 바꾸면 두 채널이 같으므로 (둘 다 1000) 불일치는 아니고 범위만 벗어난다 */
    inputs_t good = fail_by_range ? inputs(apps1(1000), apps2(1000)) : inputs(apps1(300), apps2(300));
    inputs_t bad = fail_by_range ? inputs(4800, apps2(1000)) : inputs(apps1(900), apps2(300));
    int first = -1;

    for (int i = 0; i < cycles; i++) {
        permille_t pedal = pedal_check_step(st, is_bad(i) ? &bad : &good);
        if (st->fault) {
            CHECK_EQ(pedal, 0);
            if (first < 0) {
                first = i;
            }
        }
    }
    return first;
}

static bool every_8th(int i) { return (i % 8) == 7; }
static bool every_10th(int i) { return (i % 10) == 9; }
static bool every_11th(int i) { return (i % 11) == 10; }
static bool every_2nd(int i) { return (i % 2) == 0; }
/* 처음 20주기 안에 한 주기 걸러 10번 실패하고, 그 뒤 99번째 주기 (0부터 세어)에 한 번 더 */
static bool ten_then_at_99(int i) { return ((i < 20) && ((i % 2) == 0)) || (i == 99); }
static bool ten_then_at_100(int i) { return ((i < 20) && ((i % 2) == 0)) || (i == 100); }
/* 76번째부터 96번째 주기까지 한 주기 걸러 11번 실패한다.
 * make_ready가 기록의 앞 세 자리를 썼으므로 96번째 주기의 결과는 기록의 마지막 자리 (99)에 적힌다 */
static bool eleven_ending_at_96(int i) { return (i >= 76) && (i <= 96) && ((i % 2) == 0); }
static bool first_ten_even(int i) { return (i < 20) && ((i % 2) == 0); }
static bool always(int i) { (void)i; return true; }

/* TC-014: SWR-14 최근 100주기 가운데 검사 실패가 10번을 넘으면 페달 고장으로 고정한다 */
static void tc_014(void)
{
    pedal_check_t st;

    fail_by_range = false;
    /* 8주기마다 한 번 실패한다 (FI-07, FI-08의 모양). 이어지는 횟수로는 판정되지 않는다.
     * 11번째 실패는 7 + 8 x 10 = 87번째 주기다. 그 주기에 고장이 된다 */
    make_ready(&st);
    CHECK_EQ(first_fault_cycle(&st, 400, every_8th), 87);
    CHECK(st.fault);

    /* 10주기마다 한 번 실패한다. 어느 100주기를 잡아도 실패가 10번이다. 넘지 않으므로 판정하지 않는다 */
    make_ready(&st);
    CHECK_EQ(first_fault_cycle(&st, 2000, every_10th), -1);
    CHECK(!st.fault);
    /* 11주기마다 한 번 실패한다. 실패가 기록의 자리를 옮겨 가며 적힌다.
     * 오래된 실패가 기록에서 지워지지 않으면 쌓여서 고장이 된다 (10주기마다의 경우는 같은 자리만 덮어써서 그것을 보지 못한다) */
    make_ready(&st);
    CHECK_EQ(first_fault_cycle(&st, 2000, every_11th), -1);
    CHECK(!st.fault);

    /* 돌아보는 길이는 정확히 100주기다.
     * 0 - 18번째 주기에 10번 실패한 뒤, 99번째 주기에 실패하면 0번째의 실패가 아직 기록에 있다: 11번 */
    make_ready(&st);
    CHECK_EQ(first_fault_cycle(&st, 300, ten_then_at_99), 99);
    /* 100번째 주기에 실패하면 0번째의 실패는 기록에서 밀려났다: 10번 */
    make_ready(&st);
    CHECK_EQ(first_fault_cycle(&st, 300, ten_then_at_100), -1);

    /* 기록의 마지막 자리 (99)도 적고 센다. 11번째 실패가 그 자리에 적히는 경우다 */
    make_ready(&st);
    CHECK_EQ(first_fault_cycle(&st, 300, eleven_ending_at_96), 96);

    /* 실패의 종류를 가리지 않는다. 채널 하나가 전압 범위를 벗어나는 실패도 센다
     * (위의 경우는 모두 두 채널이 어긋나는 실패였다) */
    fail_by_range = true;
    make_ready(&st);
    CHECK_EQ(first_fault_cycle(&st, 400, every_8th), 87);
    make_ready(&st);
    CHECK_EQ(first_fault_cycle(&st, 2000, every_11th), -1);
    fail_by_range = false;

    /* 켠 직후부터 한 주기 걸러 실패하면 검사를 3주기 이어서 통과하지 못한다.
     * 그동안에도 실패를 센다. 11번째 실패는 20번째 주기다 */
    pedal_check_init(&st);
    CHECK_EQ(first_fault_cycle(&st, 100, every_2nd), 20);
    CHECK(!st.ready);

    /* 적을 자리의 값이 범위를 벗어나 있어도 (memory의 값이 틀려도) 배열 밖을 쓰지 않는다 */
    make_ready(&st);
    st.window_pos = 100u;
    CHECK_EQ(first_fault_cycle(&st, 1, every_10th), -1);
    CHECK_EQ(st.window_pos, 1);
    st.window_pos = 255u;
    CHECK_EQ(first_fault_cycle(&st, 1, every_10th), -1);
    CHECK_EQ(st.window_pos, 1);
    /* 적을 자리가 범위를 하나 벗어난 채 실패가 들어오는 경우. 실패가 이미 10번 적혀 있다.
     * 자리를 처음으로 돌려 거기에 적어야 한다: 11번이 되어 고장이고, 다음 자리는 1이다.
     * 범위 검사가 하나 어긋나면 배열의 바로 뒤 (적을 자리를 담은 변수)를 덮어쓴다 */
    make_ready(&st);
    CHECK_EQ(first_fault_cycle(&st, 20, first_ten_even), -1);
    st.window_pos = 100u;
    CHECK_EQ(first_fault_cycle(&st, 1, always), 0);
    CHECK_EQ(st.window_pos, 1);
    /* 기록의 값이 틀려 실패가 11번 들어 있으면 다음 주기에 고장이 된다 (안전한 쪽) */
    make_ready(&st);
    for (int i = 10; i < 21; i++) {
        st.window[i] = true;
    }
    CHECK_EQ(first_fault_cycle(&st, 1, every_10th), 0);
}

/* TC-004: SWR-04 안전한 페달 값은 작은 쪽이고, 믿을 수 없으면 0이다 */
static void tc_004(void)
{
    pedal_check_t st;
    inputs_t in;
    inputs_t bad;

    /* 작은 쪽을 쓴다 */
    make_ready(&st);
    in = inputs(apps1(340), apps2(300));
    CHECK_EQ(pedal_check_step(&st, &in), 300);
    in = inputs(apps1(300), apps2(340));
    CHECK_EQ(pedal_check_step(&st, &in), 300);

    /* 판정 전에도 높은 쪽을 따라가지 않는다 */
    in = inputs(apps1(1000), apps2(300));
    CHECK_EQ(pedal_check_step(&st, &in), 300);
    CHECK_EQ(pedal_check_step(&st, &in), 300);
    /* 페달 고장이면 0이다 */
    CHECK_EQ(pedal_check_step(&st, &in), 0);
    CHECK(st.fault);

    /* 켠 뒤 검사를 3주기 이어서 통과하기 전에는 0이다 */
    pedal_check_init(&st);
    in = inputs(apps1(500), apps2(500));
    CHECK_EQ(pedal_check_step(&st, &in), 0);
    CHECK_EQ(pedal_check_step(&st, &in), 0);
    CHECK_EQ(pedal_check_step(&st, &in), 500);

    /* 3주기는 이어서 통과해야 한다. 사이에 실패가 끼면 다시 센다 */
    pedal_check_init(&st);
    bad = inputs(apps1(900), apps2(500));
    CHECK_EQ(pedal_check_step(&st, &in), 0);  /* 통과 1 */
    CHECK_EQ(pedal_check_step(&st, &in), 0);  /* 통과 2 */
    CHECK_EQ(pedal_check_step(&st, &bad), 0); /* 실패: 다시 센다 */
    CHECK_EQ(pedal_check_step(&st, &in), 0);  /* 통과 1 */
    CHECK_EQ(pedal_check_step(&st, &in), 0);  /* 통과 2 */
    CHECK_EQ(pedal_check_step(&st, &in), 500); /* 통과 3 */
}

/* TC-005: SWR-05 허용 토크가 0인 조건 */
static void tc_005(void)
{
    CHECK_EQ(monitor_allowed_torque(0, false, GEAR_D), 0);
    CHECK_EQ(monitor_allowed_torque(29, false, GEAR_D), 0);
    CHECK_EQ(monitor_allowed_torque(30, false, GEAR_D), 75 + 50); /* 3%의 7.5 Nm + 오차 5 Nm */
    CHECK_EQ(monitor_allowed_torque(500, true, GEAR_D), 0);
    CHECK_EQ(monitor_allowed_torque(500, false, GEAR_P), 0);
    CHECK_EQ(monitor_allowed_torque(500, false, GEAR_N), 0);
    CHECK(monitor_allowed_torque(500, false, GEAR_R) > 0);
    CHECK_EQ(monitor_allowed_torque(500, false, (gear_t)7), 0);
}

/* TC-006: SWR-06 허용 토크는 페달 위치에 비례하는 상한에 오차를 더한 값이다 */
static void tc_006(void)
{
    /* 토크의 단위는 0.1 Nm다. 오차 5 Nm는 50이다 */
    CHECK_EQ(monitor_allowed_torque(500, false, GEAR_D), 1250 + 50);
    CHECK_EQ(monitor_allowed_torque(100, false, GEAR_D), 250 + 50);
    CHECK_EQ(monitor_allowed_torque(100, false, GEAR_R), 100 + 50); /* 후진은 40% */
    CHECK_EQ(monitor_allowed_torque(1000, false, GEAR_R), 1000 + 50);
    /* 최대 토크 (250 Nm)를 넘지 않는다 */
    CHECK_EQ(monitor_allowed_torque(979, false, GEAR_D), 2447 + 50);
    CHECK_EQ(monitor_allowed_torque(981, false, GEAR_D), 2500);
    CHECK_EQ(monitor_allowed_torque(1000, false, GEAR_D), 2500);
    /* 범위 밖의 페달 값은 자른다 */
    CHECK_EQ(monitor_allowed_torque(5000, false, GEAR_D), 2500);
    CHECK_EQ(monitor_allowed_torque(-5, false, GEAR_D), 0);
}

/*
 * TC-007: SWR-06 허용 토크와 정상인 기능의 토크 요구는 두 방향으로 맞물린다.
 *   1. 정상인 기능의 토크 요구는 허용 토크를 넘지 않는다 (한 번도 깎이지 않는다).
 *   2. 둘의 차이는 55 Nm보다 작다. 55 Nm는 SG-01의 가속 한계 (1.0 m/s^2)에 해당하는 토크다.
 * 정상인 기능을 입력의 격자에서 돌려 본다. 페달은 기능이 따라갈 수 있는 속도로 움직인다.
 */
static void tc_007(void)
{
    static const gear_t gears[] = { GEAR_P, GEAR_R, GEAR_N, GEAR_D };
    int clamped = 0;
    torque_t max_gap = 0;

    for (int g = 0; g < 4; g++) {
        for (int brake = 0; brake < 2; brake++) {
            app_t app;
            app_init(&app);
            /* 페달을 올렸다가 내린다. 기능에는 지난 주기의 상태가 있다 */
            for (permille_t p = 0; p <= 2000; p += 7) {
                permille_t pedal = (p <= 1000) ? p : (2000 - p);
                torque_t req = app_step(&app, pedal, brake != 0, gears[g]);
                torque_t allowed = monitor_allowed_torque(pedal, brake != 0, gears[g]);
                torque_t mag = (req < 0) ? -req : req;
                if (output_clamp(req, allowed, gears[g]) != req) {
                    clamped++;
                }
                if ((allowed - mag) > max_gap) {
                    max_gap = allowed - mag;
                }
            }
        }
    }
    CHECK_EQ(clamped, 0);
    CHECK(max_gap < 550);
    CHECK_EQ(max_gap, 50); /* 실제로는 허용 오차 5 Nm뿐이다 */

    /* 무작위 운전: 페달, 브레이크, 기어가 아무 때나 바뀌어도 정상인 기능은 깎이지 않고,
     * 토크 요구의 크기는 그 주기의 목표 (페달에 비례하는 값. 후진은 그 40%)를 넘지 않는다.
     * 허용 토크는 제품과 같은 순서로 구한다: 페달에서 나온 상한을 지난 출력 + 25 Nm로 한 번 더 누른다.
     * 그래도 정상인 기능은 깎이지 않아야 하고, 허용 토크와의 차이는 어느 주기에도 5 Nm를 넘지 않아야 한다 */
    {
        app_t app;
        output_stage_t out;
        reaction_t reaction;
        uint32_t seed = 12345u;
        drive_t d = { 0, false, GEAR_D };
        int over_target = 0;
        int rising = 0;
        torque_t prev_req = 0;

        max_gap = 0;
        app_init(&app);
        output_stage_init(&out);
        reaction_init(&reaction);
        for (int i = 0; i < 100000; i++) {
            torque_t allowed;
            seed = (seed * 1664525u) + 1013904223u;
            if (((seed >> 8) % 6u) == 0u) {
                d.pedal = (permille_t)((seed >> 12) % 1001u);
            }
            if (((seed >> 20) % 11u) == 0u) {
                d.brake = !d.brake;
            }
            if (((seed >> 24) % 13u) == 0u) {
                d.gear = gears[(seed >> 28) % 4u];
            }
            torque_t req = app_step(&app, d.pedal, d.brake, d.gear);
            torque_t sent = chain_step(&out, &reaction, req, &d, &allowed);
            torque_t target = (d.pedal * 2500) / 1000;
            if (d.gear == GEAR_R) {
                target = (target * 40) / 100;
            }
            if (magnitude(req) > target) {
                over_target++;
            }
            if ((allowed - magnitude(sent)) > max_gap) {
                max_gap = allowed - magnitude(sent);
            }
            if (magnitude(req) == (magnitude(prev_req) + 250)) {
                rising++; /* 올리는 속도의 제한에 걸린 주기 */
            }
            prev_req = req;
        }
        CHECK_EQ((int)out.clamp_count, 0);
        CHECK(!is_cut(&reaction));
        CHECK_EQ(over_target, 0);
        CHECK_EQ(max_gap, 50);
        CHECK(rising > 1000); /* 제한에 걸린 주기가 충분히 있어야 이 test가 뜻이 있다 */
    }
}

/*
 * TC-011: SWR-13 입력이 바뀌어 기능이 토크를 올리는 동안에도 허용 토크는 정상인 기능의 토크 요구를
 * 5 Nm 넘게 앞서지 않는다. 깎이는 주기도 없다.
 * 허용 토크가 페달에서 나온 상한뿐이던 때에는 이 차이가 55 Nm 이상인 주기가 경우마다 0-7번 있었다
 * (표의 마지막 숫자). 입력이 거듭 바뀌면 그 주기가 끝없이 이어졌다. 지금은 0이어야 한다.
 * 기능이 감시가 모르는 상태를 가지면 이 test가 실패한다.
 * 예: 브레이크를 놓은 뒤에도 토크 0을 유지하는 기능 (처음의 예제가 그랬다).
 */
static void tc_011(void)
{
    /* 바뀌기 전의 입력, 바뀐 뒤의 입력, 페달에서 나온 상한만 볼 때 차이가 55 Nm 이상인 주기의 수.
     * 주기의 수는 요구사항의 숫자 (주기마다 25 Nm, 오차 5 Nm)에서 계산한 값이다 */
    static const struct {
        drive_t before;
        drive_t after;
        int static_wide_cycles;
    } cases[] = {
        { { 0, false, GEAR_D }, { 1000, false, GEAR_D }, 7 },    /* 페달을 한 번에 끝까지 */
        { { 300, false, GEAR_D }, { 1000, false, GEAR_D }, 4 },  /* 밟은 채로 더 밟음 */
        { { 1000, true, GEAR_D }, { 1000, false, GEAR_D }, 7 },  /* 브레이크를 놓음. 페달은 그대로 */
        { { 800, true, GEAR_D }, { 800, false, GEAR_D }, 6 },
        { { 1000, false, GEAR_N }, { 1000, false, GEAR_D }, 7 }, /* 페달을 밟은 채 N에서 D로 */
        { { 1000, false, GEAR_P }, { 1000, false, GEAR_D }, 7 },
        { { 0, false, GEAR_R }, { 1000, false, GEAR_R }, 2 },    /* 후진 */
        { { 1000, true, GEAR_R }, { 1000, false, GEAR_R }, 2 },
        { { 1000, false, GEAR_D }, { 1000, false, GEAR_R }, 2 }, /* 페달을 밟은 채 D에서 R로 */
        { { 1000, false, GEAR_R }, { 1000, false, GEAR_D }, 7 },
        /* 방향이 바뀔 때 목표가 한 주기에 올릴 수 있는 양보다 작은 경우.
         * 기능은 목표를 넘는 토크를 내면 안 된다 */
        { { 199, false, GEAR_D }, { 199, false, GEAR_R }, 0 },
        { { 1000, false, GEAR_R }, { 40, false, GEAR_D }, 0 },
    };

    for (int c = 0; c < (int)(sizeof(cases) / sizeof(cases[0])); c++) {
        const drive_t *before = &cases[c].before;
        const drive_t *after = &cases[c].after;
        app_t app;
        output_stage_t out;
        reaction_t reaction;
        int static_wide_cycles = 0;
        torque_t max_gap = 0;
        torque_t gap = 0;
        torque_t allowed;

        app_init(&app);
        output_stage_init(&out);
        reaction_init(&reaction);
        for (int i = 0; i < 40; i++) {
            torque_t req = app_step(&app, before->pedal, before->brake, before->gear);
            (void)chain_step(&out, &reaction, req, before, &allowed);
        }
        for (int i = 0; i < 100; i++) {
            torque_t req = app_step(&app, after->pedal, after->brake, after->gear);
            torque_t ceiling = monitor_allowed_torque(after->pedal, after->brake, after->gear);
            torque_t sent = chain_step(&out, &reaction, req, after, &allowed);
            CHECK_EQ(sent, req);
            gap = allowed - magnitude(req);
            if (gap > max_gap) {
                max_gap = gap;
            }
            if ((ceiling - magnitude(req)) >= 550) {
                static_wide_cycles++;
            }
        }
        CHECK_EQ((int)out.clamp_count, 0);
        CHECK(max_gap <= 50);
        CHECK_EQ(static_wide_cycles, cases[c].static_wide_cycles);
        /* 다 올린 뒤에는 허용 오차 5 Nm뿐이다.
         * 페달을 끝까지 밟으면 허용 토크가 최대 토크에서 잘려 차이가 0이다 */
        CHECK_EQ(gap, (after->pedal == 1000 && after->gear == GEAR_D) ? 0 : 50);
    }
}

/* TC-012: SWR-13 허용 토크는 지난 주기에 보낸 토크의 크기에서 25 Nm까지만 오른다 */
static void tc_012(void)
{
    /* 전진 */
    CHECK_EQ(monitor_limit_rise(2500, 0, GEAR_D), 250);
    CHECK_EQ(monitor_limit_rise(2500, 1000, GEAR_D), 1250);
    CHECK_EQ(monitor_limit_rise(2500, 2249, GEAR_D), 2499);
    CHECK_EQ(monitor_limit_rise(2500, 2250, GEAR_D), 2500);
    CHECK_EQ(monitor_limit_rise(2500, 2500, GEAR_D), 2500);
    /* 페달에서 나온 상한이 더 작으면 그 값이다. 내릴 때는 제한이 없다 */
    CHECK_EQ(monitor_limit_rise(300, 2500, GEAR_D), 300);
    CHECK_EQ(monitor_limit_rise(0, 2500, GEAR_D), 0);
    CHECK_EQ(monitor_limit_rise(250, 0, GEAR_D), 250);
    CHECK_EQ(monitor_limit_rise(251, 0, GEAR_D), 250);
    CHECK_EQ(monitor_limit_rise(249, 0, GEAR_D), 249);
    /* 후진: 지난 출력이 음수일 때 그 크기에서 센다 */
    CHECK_EQ(monitor_limit_rise(1050, 0, GEAR_R), 250);
    CHECK_EQ(monitor_limit_rise(1050, -500, GEAR_R), 750);
    CHECK_EQ(monitor_limit_rise(1050, -1000, GEAR_R), 1050);
    CHECK_EQ(monitor_limit_rise(1050, -1, GEAR_R), 251);
    /* 지난 출력의 방향이 지금 기어와 반대이면 0에서 다시 센다 */
    CHECK_EQ(monitor_limit_rise(2500, -1000, GEAR_D), 250);
    CHECK_EQ(monitor_limit_rise(2500, -1, GEAR_D), 250);
    CHECK_EQ(monitor_limit_rise(2500, 1, GEAR_D), 251);
    CHECK_EQ(monitor_limit_rise(1050, 2000, GEAR_R), 250);
    CHECK_EQ(monitor_limit_rise(1050, 1, GEAR_R), 250);
    /* P와 N에서는 지난 출력을 보지 않는다 (허용 토크는 어차피 0이다) */
    CHECK_EQ(monitor_limit_rise(0, 2000, GEAR_N), 0);
    CHECK_EQ(monitor_limit_rise(2500, 2000, GEAR_N), 250);
    CHECK_EQ(monitor_limit_rise(2500, -2000, GEAR_P), 250);
    /* 지난 출력이 범위 밖이어도 (memory의 값이 틀려도) 계산이 넘치지 않는다 */
    CHECK_EQ(monitor_limit_rise(2500, 2501, GEAR_D), 2500);
    CHECK_EQ(monitor_limit_rise(2500, INT32_MAX, GEAR_D), 2500);
    CHECK_EQ(monitor_limit_rise(2500, INT32_MIN, GEAR_R), 2500);
    CHECK_EQ(monitor_limit_rise(2500, -2501, GEAR_R), 2500);
    CHECK_EQ(monitor_limit_rise(2500, INT32_MIN, GEAR_D), 250);

    /* 출력 단계는 보낸 토크를 기억한다. 고정된 뒤에는 0을 기억한다 */
    {
        output_stage_t out;
        reaction_t reaction;
        output_stage_init(&out);
        reaction_init(&reaction);
        CHECK_EQ(out.last_out, 0);
        CHECK_EQ(output_stage_step(&out, &reaction, 700, 1000, GEAR_D), 700);
        CHECK_EQ(out.last_out, 700);
        CHECK_EQ(output_stage_step(&out, &reaction, 1500, 1000, GEAR_D), 1000); /* 깎인 값을 기억한다 */
        CHECK_EQ(out.last_out, 1000);
        CHECK_EQ(output_stage_step(&out, &reaction, -300, 1000, GEAR_R), -300);
        CHECK_EQ(out.last_out, -300);
        for (int i = 0; i < 5; i++) {
            (void)output_stage_step(&out, &reaction, 2000, 1000, GEAR_D);
        }
        CHECK(is_cut(&reaction));
        CHECK_EQ(out.last_out, 0);
    }
}

/* TC-015: SWR-25 고장 대응의 상태는 안전한 쪽으로만 바뀌고, 출력은 상태에서 나온다 */
static void tc_015(void)
{
    reaction_t r;

    /* 켠 직후는 정상이다 */
    reaction_init(&r);
    CHECK_EQ(reaction_state(&r), REACTION_NORMAL);
    /* 안전한 쪽으로만 간다. 덜 안전한 쪽을 알려도 그대로다 */
    reaction_raise(&r, REACTION_LIMP);
    CHECK_EQ(reaction_state(&r), REACTION_LIMP);
    reaction_raise(&r, REACTION_NORMAL);
    CHECK_EQ(reaction_state(&r), REACTION_LIMP);
    reaction_raise(&r, REACTION_ZERO);
    CHECK_EQ(reaction_state(&r), REACTION_ZERO);
    reaction_raise(&r, REACTION_LIMP);
    CHECK_EQ(reaction_state(&r), REACTION_ZERO);
    reaction_raise(&r, REACTION_ZERO);
    CHECK_EQ(reaction_state(&r), REACTION_ZERO);
    reaction_raise(&r, REACTION_CUT);
    CHECK_EQ(reaction_state(&r), REACTION_CUT);
    reaction_raise(&r, REACTION_NORMAL);
    reaction_raise(&r, REACTION_LIMP);
    reaction_raise(&r, REACTION_ZERO);
    CHECK_EQ(reaction_state(&r), REACTION_CUT);
    /* 단계를 건너뛸 수 있다 */
    reaction_init(&r);
    reaction_raise(&r, REACTION_CUT);
    CHECK_EQ(reaction_state(&r), REACTION_CUT);

    /* 상태에서 나오는 출력: 토크의 상한, 구동 허용, 경고 */
    CHECK_EQ(reaction_torque_cap(REACTION_NORMAL), 2500);
    CHECK_EQ(reaction_torque_cap(REACTION_LIMP), 400);
    CHECK_EQ(reaction_torque_cap(REACTION_ZERO), 0);
    CHECK_EQ(reaction_torque_cap(REACTION_CUT), 0);
    CHECK(reaction_enable(REACTION_NORMAL));
    CHECK(reaction_enable(REACTION_LIMP));
    CHECK(reaction_enable(REACTION_ZERO));
    CHECK(!reaction_enable(REACTION_CUT));
    CHECK_EQ(reaction_warning(REACTION_NORMAL), 0);
    CHECK_EQ(reaction_warning(REACTION_LIMP), 1);
    CHECK_EQ(reaction_warning(REACTION_ZERO), 2);
    CHECK_EQ(reaction_warning(REACTION_CUT), 2);

    /* 상태를 담은 변수가 알 수 없는 값이면 (memory의 값이 틀리면) 구동 허용 차단으로 읽힌다 */
    reaction_init(&r);
    r.state = (reaction_state_t)7;
    CHECK_EQ(reaction_state(&r), REACTION_CUT);
    r.state = (reaction_state_t)-1;
    CHECK_EQ(reaction_state(&r), REACTION_CUT);
    /* 그 상태에서 사건을 알려도 풀리지 않는다 */
    reaction_raise(&r, REACTION_LIMP);
    CHECK_EQ(reaction_state(&r), REACTION_CUT);
    /* 알 수 없는 값을 사건으로 알리면 구동 허용 차단이 된다 */
    reaction_init(&r);
    reaction_raise(&r, (reaction_state_t)4);
    CHECK_EQ(reaction_state(&r), REACTION_CUT);
    /* 알 수 없는 값은 어느 출력에서도 "허용"이 되지 않는다 */
    CHECK_EQ(reaction_torque_cap((reaction_state_t)9), 0);
    CHECK(!reaction_enable((reaction_state_t)9));
    CHECK_EQ(reaction_warning((reaction_state_t)9), 2);

    /* 허용 토크에 상태의 상한이 걸린다 */
    CHECK_EQ(monitor_apply_cap(2500, REACTION_NORMAL), 2500);
    CHECK_EQ(monitor_apply_cap(2500, REACTION_LIMP), 400);
    CHECK_EQ(monitor_apply_cap(401, REACTION_LIMP), 400);
    CHECK_EQ(monitor_apply_cap(300, REACTION_LIMP), 300);
    CHECK_EQ(monitor_apply_cap(2500, REACTION_ZERO), 0);
    CHECK_EQ(monitor_apply_cap(2500, REACTION_CUT), 0);

    /* 줄여 감 상태에서 사슬을 돌린다: 페달을 끝까지 밟아도 40 Nm까지만 나간다.
     * 40 Nm를 넘게 요구하는 기능은 깎이고, 5주기 이어지면 구동 허용 차단이 된다 */
    {
        output_stage_t out;
        reaction_t reaction;
        drive_t d = { 1000, false, GEAR_D };
        torque_t allowed;

        output_stage_init(&out);
        reaction_init(&reaction);
        reaction_raise(&reaction, REACTION_LIMP);
        CHECK_EQ(chain_step(&out, &reaction, 250, &d, &allowed), 250);
        CHECK_EQ(chain_step(&out, &reaction, 350, &d, &allowed), 350);
        CHECK_EQ(allowed, 400);
        CHECK_EQ(chain_step(&out, &reaction, 350, &d, &allowed), 350);
        CHECK_EQ(reaction_state(&reaction), REACTION_LIMP);
        CHECK_EQ((int)out.clamp_count, 0);
        for (int i = 0; i < 4; i++) {
            CHECK_EQ(chain_step(&out, &reaction, 500, &d, &allowed), 400);
        }
        CHECK_EQ(reaction_state(&reaction), REACTION_LIMP);
        CHECK_EQ(chain_step(&out, &reaction, 500, &d, &allowed), 0);
        CHECK_EQ(reaction_state(&reaction), REACTION_CUT);
    }

    /* 토크 0 상태 (예: 페달 고장)에서는 허용 범위 안의 요구도 나가지 않는다 */
    {
        output_stage_t out;
        reaction_t reaction;

        output_stage_init(&out);
        reaction_init(&reaction);
        reaction_raise(&reaction, REACTION_ZERO);
        CHECK_EQ(output_stage_step(&out, &reaction, 500, 1000, GEAR_D), 0);
        CHECK_EQ(out.last_out, 0);
        CHECK_EQ(reaction_state(&reaction), REACTION_ZERO);
    }
}

/* 브레이크의 두 접점만 다른 입력을 만든다 */
static inputs_t contacts(bool brake1, bool brake2)
{
    inputs_t in = { 500, 250, brake1, brake2, GEAR_D };
    return in;
}

static bool brake_run(brake_check_t *st, bool brake1, bool brake2, int cycles)
{
    inputs_t in = contacts(brake1, brake2);
    bool pressed = st->pressed;

    for (int i = 0; i < cycles; i++) {
        pressed = brake_check_step(st, &in);
    }
    return pressed;
}

/* TC-016: SWR-15 브레이크는 두 접점 가운데 하나라도 밟음이면 밟음이고, 놓음은 3주기 뒤에 받아들인다.
 * 두 접점이 어긋난 채 20주기 이어지면 고장이다 */
static void tc_016(void)
{
    brake_check_t st;

    /* 켠 직후에는 밟은 것으로 본다. 두 접점이 놓음을 3주기 가리킨 뒤에 놓음이 된다 */
    brake_check_init(&st);
    CHECK(st.pressed);
    CHECK(brake_run(&st, false, false, 1));
    CHECK(brake_run(&st, false, false, 1));
    CHECK(!brake_run(&st, false, false, 1));
    CHECK(!st.fault);

    /* 밟음은 그 주기에 받아들인다. 두 접점이 함께여도, 어느 하나만이어도 */
    CHECK(brake_run(&st, true, true, 1));
    CHECK(!brake_run(&st, false, false, 3));
    CHECK(brake_run(&st, true, false, 1));
    CHECK(!brake_run(&st, false, false, 3));
    CHECK(brake_run(&st, false, true, 1));

    /* 놓음을 세는 중에 한 주기라도 밟음이 오면 다시 센다 */
    CHECK(brake_run(&st, false, false, 2));
    CHECK(brake_run(&st, false, true, 1));
    CHECK(brake_run(&st, false, false, 2));
    CHECK(!brake_run(&st, false, false, 1));

    /* 어긋난 채 19주기까지는 고장이 아니다. 그동안 밟음이다. 20번째 주기에 고장이 된다 */
    brake_check_init(&st);
    (void)brake_run(&st, false, false, 3);
    CHECK(brake_run(&st, true, false, 19));
    CHECK(!st.fault);
    CHECK(brake_run(&st, true, false, 1));
    CHECK(st.fault);
    /* 접점 2 쪽이 밟음인 어긋남도 같다 */
    brake_check_init(&st);
    (void)brake_run(&st, false, false, 3);
    CHECK(brake_run(&st, false, true, 19));
    CHECK(!st.fault);
    CHECK(brake_run(&st, false, true, 1));
    CHECK(st.fault);

    /* 어긋남이 이어지지 않으면 다시 센다. 페달을 밟는 동안 두 접점이 잠깐 어긋나는 것은 고장이 아니다 */
    brake_check_init(&st);
    (void)brake_run(&st, false, false, 3);
    for (int i = 0; i < 10; i++) {
        (void)brake_run(&st, true, false, 19);
        (void)brake_run(&st, true, true, 1);
    }
    CHECK(!st.fault);

    /* 고장으로 판정한 뒤에는 두 접점이 놓음을 가리켜도 밟음으로 둔다. 고장은 풀리지 않는다 */
    brake_check_init(&st);
    (void)brake_run(&st, true, false, 20);
    CHECK(st.fault);
    CHECK(brake_run(&st, false, false, 50));
    CHECK(st.fault);
}

/* 입력이 거듭 바뀌는 네 모양. 페달은 끝까지 밟고 있고, 80-90 ms마다 입력 하나가 잠깐 바뀐다.
 * 페달 한 채널이 가끔 끊기거나 브레이크와 기어의 신호가 튀면 이렇게 된다.
 * 정상인 기능은 토크를 다 올리기 전에 다시 0에서 시작한다 */
static drive_t bouncing_input(int shape, int i)
{
    drive_t d = { 1000, false, GEAR_D };

    if (shape == 0) {
        d.gear = ((i % 9) < 7) ? GEAR_D : GEAR_R;
    } else if (shape == 1) {
        d.pedal = ((i % 8) < 7) ? 1000 : 0;
    } else if (shape == 2) {
        d.brake = ((i % 8) == 7);
    } else {
        d.gear = ((i % 8) < 7) ? GEAR_D : GEAR_N;
    }
    return d;
}

/*
 * TC-013: SWR-13 기능이 틀려도, 입력이 거듭 바뀌는 동안 나가는 토크는 정상인 기능의 토크를
 * 55 Nm (SG-01의 가속 한계에 해당하는 토크) 넘게 앞서지 않는다.
 * 틀린 기능 둘을 본다. 정상인 기능을 같은 입력으로 나란히 돌려 견준다.
 */
static void tc_013(void)
{
    for (int shape = 0; shape < 4; shape++) {
        /* 1. 감시가 허용하는 만큼을 요구하는 기능. 깎이지 않으므로 고정되지 않는다.
         *    그래도 나가는 토크는 정상인 기능보다 5 Nm 넘게 크지 않다.
         *    허용 토크가 페달에서 나온 상한뿐이면 그 차이가 55 Nm 이상인 주기가 대부분이다 */
        {
            app_t ref;
            output_stage_t out;
            reaction_t reaction;
            int wide = 0;
            int static_wide = 0;
            torque_t max_ahead = 0;

            app_init(&ref);
            output_stage_init(&out);
            reaction_init(&reaction);
            for (int i = 0; i < 400; i++) {
                drive_t d = bouncing_input(shape, i);
                torque_t allowed;
                torque_t normal = app_step(&ref, d.pedal, d.brake, d.gear);
                torque_t ceiling = monitor_allowed_torque(d.pedal, d.brake, d.gear);
                torque_t sign = (d.gear == GEAR_R) ? -1 : 1;
                torque_t limit = monitor_limit_rise(ceiling, out.last_out, d.gear);
                torque_t sent = chain_step(&out, &reaction, sign * limit, &d, &allowed);
                torque_t ahead = magnitude(sent) - magnitude(normal);

                CHECK_EQ(sent, sign * limit);
                if (ahead > max_ahead) {
                    max_ahead = ahead;
                }
                if (ahead >= 550) {
                    wide++;
                }
                if ((ceiling - magnitude(normal)) >= 550) {
                    static_wide++;
                }
            }
            CHECK(!is_cut(&reaction));
            CHECK_EQ((int)out.clamp_count, 0);
            CHECK_EQ(wide, 0);
            CHECK(max_ahead <= 50);
            /* 상한만으로는 400주기 가운데 이만큼 열려 있었다 */
            CHECK_EQ(static_wide, (shape == 0) ? 400 : 350);
        }

        /* 2. 올리는 속도의 제한을 잃은 기능 (목표를 바로 요구한다).
         *    토크를 올리는 동안 깎이고, 5주기 안에 고정된다. 그때까지 나간 토크는 정상인 기능과 같다 */
        {
            app_t ref;
            output_stage_t out;
            reaction_t reaction;
            int latched_at = -1;
            torque_t max_ahead = 0;

            app_init(&ref);
            output_stage_init(&out);
            reaction_init(&reaction);
            for (int i = 0; i < 400; i++) {
                drive_t d = bouncing_input(shape, i);
                torque_t allowed;
                torque_t normal = app_step(&ref, d.pedal, d.brake, d.gear);
                torque_t target = (d.pedal * 2500) / 1000;
                torque_t sent;

                if (d.brake || (d.gear == GEAR_N)) {
                    target = 0;
                }
                if (d.gear == GEAR_R) {
                    target = -((target * 40) / 100);
                }
                sent = chain_step(&out, &reaction, target, &d, &allowed);
                if ((magnitude(sent) - magnitude(normal)) > max_ahead) {
                    max_ahead = magnitude(sent) - magnitude(normal);
                }
                if (is_cut(&reaction) && (latched_at < 0)) {
                    latched_at = i;
                }
            }
            CHECK_EQ(max_ahead, 0);
            CHECK_EQ(latched_at, 4); /* 처음 다섯 주기가 모두 깎인다 */
        }
    }
}

/* TC-008: SWR-07 토크는 기어가 정한 방향으로만, 허용 토크까지만 나간다 */
static void tc_008(void)
{
    /* D: 0 이상, 허용 토크 이하 */
    CHECK_EQ(output_clamp(800, 1000, GEAR_D), 800);
    CHECK_EQ(output_clamp(1000, 1000, GEAR_D), 1000);
    CHECK_EQ(output_clamp(1001, 1000, GEAR_D), 1000);
    CHECK_EQ(output_clamp(-300, 1000, GEAR_D), 0);
    /* R: 허용 토크의 음수 이상, 0 이하 */
    CHECK_EQ(output_clamp(-800, 1000, GEAR_R), -800);
    CHECK_EQ(output_clamp(-1001, 1000, GEAR_R), -1000);
    CHECK_EQ(output_clamp(300, 1000, GEAR_R), 0);
    /* P, N, 알 수 없는 값: 0만 나간다 */
    CHECK_EQ(output_clamp(300, 1000, GEAR_P), 0);
    CHECK_EQ(output_clamp(-300, 1000, GEAR_N), 0);
    CHECK_EQ(output_clamp(300, 1000, (gear_t)7), 0);
    /* 허용 토크가 0이면 0만 나간다 */
    CHECK_EQ(output_clamp(1, 0, GEAR_D), 0);
    CHECK_EQ(output_clamp(-1, 0, GEAR_R), 0);
}

/* TC-009: SWR-08 깎인 주기가 5번 이어지면 기능의 고장으로 고정한다 */
static void tc_009(void)
{
    output_stage_t st;
    reaction_t reaction;

    output_stage_init(&st);

    reaction_init(&reaction);
    /* 4번 깎이고 한 번 정상이면 다시 센다 */
    for (int i = 0; i < 4; i++) {
        CHECK_EQ(output_stage_step(&st, &reaction, 2000, 1000, GEAR_D), 1000);
    }
    CHECK(!is_cut(&reaction));
    CHECK_EQ(output_stage_step(&st, &reaction, 900, 1000, GEAR_D), 900);
    for (int i = 0; i < 4; i++) {
        (void)output_stage_step(&st, &reaction, 2000, 1000, GEAR_D);
    }
    CHECK(!is_cut(&reaction));
    /* 5번째로 이어서 깎인 주기에 고정한다 */
    (void)output_stage_step(&st, &reaction, 2000, 1000, GEAR_D);
    CHECK(is_cut(&reaction));
    CHECK_EQ(st.clamp_count, 9);
}

/* TC-010: SWR-09 고정된 뒤에는 토크 0을 보낸다 */
static void tc_010(void)
{
    output_stage_t st;
    reaction_t reaction;

    output_stage_init(&st);

    reaction_init(&reaction);
    for (int i = 0; i < 4; i++) {
        (void)output_stage_step(&st, &reaction, 2000, 1000, GEAR_D);
    }
    /* 고정되는 바로 그 주기부터 0이다 */
    CHECK_EQ(output_stage_step(&st, &reaction, 2000, 1000, GEAR_D), 0);
    /* 그 뒤에 요구가 정상이어도 0이고, 고정은 풀리지 않는다 */
    for (int i = 0; i < 10; i++) {
        CHECK_EQ(output_stage_step(&st, &reaction, 500, 1000, GEAR_D), 0);
    }
    CHECK(is_cut(&reaction));
}

/* 기능을 같은 입력으로 여러 주기 돌린 뒤의 토크 요구 */
static torque_t app_settle(app_t *app, permille_t pedal, bool brake, gear_t gear)
{
    torque_t req = 0;
    for (int i = 0; i < 40; i++) {
        req = app_step(app, pedal, brake, gear);
    }
    return req;
}

/*
 * 아래 FT-는 기능의 test다. 기능에는 SG-01의 안전 요구사항이 없으므로 요구사항 추적에 넣지 않는다.
 * 그래도 기능의 코드에 같은 방법 (test와 coverage 측정)을 적용한다.
 */

/* FT-001: 토크 요구는 페달 위치에 비례한다. 후진은 그 40%다 */
static void ft_001(void)
{
    app_t app;

    app_init(&app);
    CHECK_EQ(app_settle(&app, 500, false, GEAR_D), 1250);
    CHECK_EQ(app_settle(&app, 1000, false, GEAR_D), 2500);
    CHECK_EQ(app_settle(&app, 29, false, GEAR_D), 0);  /* 놓음 구간 */
    CHECK_EQ(app_settle(&app, 30, false, GEAR_D), 75);
    /* 범위 밖의 페달 값은 자른다 */
    CHECK_EQ(app_settle(&app, 1500, false, GEAR_D), 2500);
    CHECK_EQ(app_settle(&app, -5, false, GEAR_D), 0);
    /* P와 N에서는 0, R에서는 음수이고 40%까지 */
    CHECK_EQ(app_settle(&app, 500, false, GEAR_P), 0);
    CHECK_EQ(app_settle(&app, 500, false, GEAR_N), 0);
    CHECK_EQ(app_settle(&app, 500, false, GEAR_R), -500);
    CHECK_EQ(app_settle(&app, 1000, false, GEAR_R), -1000);
}

/* FT-002: 토크는 한 주기에 25 Nm씩 올리고, 내릴 때는 바로 내린다 */
static void ft_002(void)
{
    app_t app;

    app_init(&app);
    CHECK_EQ(app_step(&app, 1000, false, GEAR_D), 250);
    CHECK_EQ(app_step(&app, 1000, false, GEAR_D), 500);
    CHECK_EQ(app_step(&app, 40, false, GEAR_D), 100);
    CHECK_EQ(app_step(&app, 0, false, GEAR_D), 0);
    CHECK_EQ(app_step(&app, 1000, false, GEAR_R), -250);
    CHECK_EQ(app_step(&app, 1000, false, GEAR_R), -500);
    CHECK_EQ(app_step(&app, 1000, false, GEAR_N), 0);

    /* 알려진 단순화: 전진 토크를 내다가 기어가 R로 바뀌면 다음 주기에 바로 음수가 된다 */
    app_init(&app);
    (void)app_step(&app, 1000, false, GEAR_D);
    CHECK_EQ(app_step(&app, 1000, false, GEAR_D), 500);
    CHECK_EQ(app_step(&app, 1000, false, GEAR_R), -250);
}

/* FT-003: 제동 우선은 브레이크를 밟는 동안 듣는다. 걸린 상태를 기억하지 않는다 */
static void ft_003(void)
{
    app_t app;

    app_init(&app);
    CHECK_EQ(app_settle(&app, 500, false, GEAR_D), 1250);
    CHECK_EQ(app_step(&app, 500, true, GEAR_D), 0);    /* 두 페달을 함께 밟음 */
    CHECK_EQ(app_step(&app, 500, true, GEAR_D), 0);
    CHECK_EQ(app_step(&app, 500, false, GEAR_D), 250); /* 브레이크를 놓음: 다시 올린다 */
    CHECK_EQ(app_settle(&app, 500, false, GEAR_D), 1250);
    /* 가속 페달을 놓은 채 브레이크만 밟았다 놓아도 같다 */
    CHECK_EQ(app_step(&app, 0, true, GEAR_D), 0);
    CHECK_EQ(app_step(&app, 500, false, GEAR_D), 250);
    /* 후진에서도 같다 */
    CHECK_EQ(app_step(&app, 500, true, GEAR_R), 0);
    CHECK_EQ(app_step(&app, 500, false, GEAR_R), -250);
}

/* 보내는 쪽의 counter가 주어진 값일 때 만든 메시지.
 * TC-018은 메시지를 이것으로 만든다. 이것이 붙이는 CRC가 옳다는 것은 TC-017이 따로 계산한 값으로 본다 */
static frame_t frame_of(uint8_t data_id, uint8_t counter, int32_t value)
{
    e2e_tx_t tx;
    frame_t frame;

    e2e_tx_init(&tx);
    tx.counter = counter;
    e2e_protect(&tx, data_id, value, &frame);
    return frame;
}

/* TC-017: SWR-17 보내는 메시지에 counter와 CRC를 붙인다 */
static void tc_017(void)
{
    static const uint8_t check_input[9] = { '1', '2', '3', '4', '5', '6', '7', '8', '9' };
    e2e_tx_t tx;
    frame_t frame;

    /* CRC의 계산. 이 방식 (다항식 0x1D, 처음 값 0xFF, 끝에 뒤집음)에 널리 쓰는 확인값이다 */
    CHECK_EQ(e2e_crc8(check_input, 9u), 0x4B);

    /* counter는 0에서 시작해 메시지마다 1 오르고 15 다음에 0으로 돈다. 값은 받은 그대로 싣는다 */
    e2e_tx_init(&tx);
    for (int i = 0; i < 40; i++) {
        e2e_protect(&tx, 33u, 750 + i, &frame);
        CHECK_EQ(frame.counter, i % 16);
        CHECK_EQ(frame.value, 750 + i);
    }

    /* CRC는 data ID, counter, 값에 걸친다. 기댓값은 제품의 코드와 따로 계산했다 */
    CHECK_EQ(frame_of(33u, 0u, 0).crc, 0x98);
    CHECK_EQ(frame_of(33u, 1u, 750).crc, 0xEF);
    CHECK_EQ(frame_of(33u, 15u, 2500).crc, 0x88);
    CHECK_EQ(frame_of(33u, 3u, -1000).crc, 0x98);
    /* data ID가 다르면 값과 counter가 같아도 CRC가 다르다 */
    CHECK_EQ(frame_of(66u, 1u, 750).crc, 0x5D);
    CHECK_EQ(frame_of(99u, 7u, 1234).crc, 0xEA);
}

/* 받는 쪽의 검사를 한 번 부른다. 새 메시지가 방금 닿은 경우다 */
static bool receive(e2e_rx_t *rx, uint8_t data_id, frame_t frame)
{
    return e2e_check(rx, data_id, &frame, true, true, 0u);
}

/* TC-018: SWR-18 받은 메시지의 CRC, data ID, counter, 시간을 검사한다 */
static void tc_018(void)
{
    e2e_rx_t rx;
    frame_t f = frame_of(66u, 0u, 0);

    /* 받은 적이 없으면 무효다 */
    e2e_rx_init(&rx);
    CHECK(!e2e_check(&rx, 66u, &f, false, false, 0u));
    /* 받은 적이 없다고 알려 오면 넘겨받은 메시지의 내용이 옳아 보여도 쓰지 않는다 */
    CHECK(!e2e_check(&rx, 66u, &f, false, true, 0u));
    /* 처음 받은 메시지는 견줄 것이 없으므로 counter가 무엇이든 받아들인다 */
    CHECK(receive(&rx, 66u, frame_of(66u, 7u, 500)));
    /* counter가 1 앞서면 유효하다 */
    CHECK(receive(&rx, 66u, frame_of(66u, 8u, 510)));
    /* 메시지를 둘까지 잃어도 (counter가 2, 3 앞섬) 유효하다 */
    CHECK(receive(&rx, 66u, frame_of(66u, 10u, 520)));
    CHECK(receive(&rx, 66u, frame_of(66u, 13u, 530)));
    /* 15 다음은 0이다. 그 사이를 건너뛰어도 같다 */
    CHECK(receive(&rx, 66u, frame_of(66u, 15u, 540)));
    CHECK(receive(&rx, 66u, frame_of(66u, 0u, 550)));
    CHECK(receive(&rx, 66u, frame_of(66u, 3u, 560)));
    CHECK(receive(&rx, 66u, frame_of(66u, 14u, 560)) == false); /* 11 앞섬 */
    CHECK(receive(&rx, 66u, frame_of(66u, 1u, 570)));           /* 14 -> 1은 3 앞섬 */
    /* 셋을 잃으면 (4 앞섬) 무효다. 그다음 메시지부터 다시 유효하다 */
    CHECK(!receive(&rx, 66u, frame_of(66u, 5u, 580)));
    CHECK(receive(&rx, 66u, frame_of(66u, 6u, 590)));
    /* 같은 counter가 다시 오면 (되풀이) 무효다. 값이 달라도 같다 */
    CHECK(!receive(&rx, 66u, frame_of(66u, 6u, 590)));
    CHECK(!receive(&rx, 66u, frame_of(66u, 6u, 600)));
    CHECK(receive(&rx, 66u, frame_of(66u, 7u, 610)));
    /* counter가 뒤로 가면 무효다 */
    CHECK(!receive(&rx, 66u, frame_of(66u, 6u, 620)));
    CHECK(receive(&rx, 66u, frame_of(66u, 7u, 630)));

    /* 전송 중에 값이 바뀌면 무효다 */
    f = frame_of(66u, 8u, 640);
    f.value += 1;
    CHECK(!receive(&rx, 66u, f));
    /* counter가 바뀌어도 무효다 */
    f = frame_of(66u, 8u, 640);
    f.counter = 9u;
    CHECK(!receive(&rx, 66u, f));
    /* CRC가 바뀌어도 무효다 */
    f = frame_of(66u, 8u, 640);
    f.crc ^= 1u;
    CHECK(!receive(&rx, 66u, f));
    /* 다른 종류의 메시지 (data ID가 다름)는 무효다 */
    CHECK(!receive(&rx, 66u, frame_of(99u, 8u, 640)));
    /* 틀린 메시지는 counter의 기준을 바꾸지 않는다. 지난 옳은 메시지 (7)에서 1 앞선 것이 유효하다 */
    CHECK(receive(&rx, 66u, frame_of(66u, 8u, 640)));

    /* 새 메시지가 없으면 지난 판정이 그대로다. 유효였으면 받은 뒤 50 ms까지 유효하다 */
    f = frame_of(66u, 8u, 640);
    CHECK(e2e_check(&rx, 66u, &f, true, false, 10u));
    CHECK(e2e_check(&rx, 66u, &f, true, false, 50u));
    /* 50 ms를 넘으면 무효다 */
    CHECK(!e2e_check(&rx, 66u, &f, true, false, 51u));
    /* 한 번 무효가 되면 새 메시지가 와야 유효해진다 */
    CHECK(!e2e_check(&rx, 66u, &f, true, false, 10u));
    CHECK(receive(&rx, 66u, frame_of(66u, 9u, 650)));
    /* 무효인 판정도 새 메시지가 없으면 그대로다 */
    f = frame_of(66u, 10u, 660);
    f.value += 1;
    CHECK(!receive(&rx, 66u, f));
    CHECK(!e2e_check(&rx, 66u, &f, true, false, 5u));
    /* 새 메시지가 옳아도 받은 지 50 ms가 넘은 뒤에 읽었으면 무효다 */
    f = frame_of(66u, 10u, 660);
    CHECK(!e2e_check(&rx, 66u, &f, true, true, 51u));
}

/* TC-019: SWR-16 방향의 바뀜은 차량 속도가 유효하고 5 km/h 아래일 때만 받아들인다 */
static void tc_019(void)
{
    gear_check_t st;

    /* 켠 직후에는 받아들인 방향이 없다. 처음 고른 방향도 속도를 본다 */
    gear_check_init(&st);
    CHECK_EQ(gear_check_step(&st, GEAR_D, false, 0), GEAR_N);  /* 속도가 무효다 */
    CHECK_EQ(gear_check_step(&st, GEAR_D, true, 139), GEAR_N); /* 1.39 m/s: 5 km/h (1.389 m/s)를 넘는다 */
    CHECK_EQ(gear_check_step(&st, GEAR_D, true, -1), GEAR_N);  /* 크기가 음수다: 믿을 수 없는 값 */
    CHECK_EQ(gear_check_step(&st, GEAR_D, true, 138), GEAR_D); /* 1.38 m/s: 5 km/h 아래 */
    /* 받아들인 방향과 같으면 속도를 보지 않는다. 속도가 무효여도 그대로다 */
    CHECK_EQ(gear_check_step(&st, GEAR_D, true, 3000), GEAR_D);
    CHECK_EQ(gear_check_step(&st, GEAR_D, false, 0), GEAR_D);
    /* N과 P는 그대로 받아들인다. 알 수 없는 값은 N이다 */
    CHECK_EQ(gear_check_step(&st, GEAR_N, true, 3000), GEAR_N);
    CHECK_EQ(gear_check_step(&st, GEAR_P, true, 3000), GEAR_P);
    CHECK_EQ(gear_check_step(&st, (gear_t)9, true, 0), GEAR_N);
    /* N이나 P를 거쳐 같은 방향으로 돌아오면 속도를 보지 않는다 */
    CHECK_EQ(gear_check_step(&st, GEAR_D, true, 3000), GEAR_D);
    /* 반대 방향은 속도가 높거나 무효이면 받아들이지 않고 N을 낸다 */
    CHECK_EQ(gear_check_step(&st, GEAR_R, true, 139), GEAR_N);
    CHECK_EQ(gear_check_step(&st, GEAR_R, false, 0), GEAR_N);
    /* 가던 방향으로 돌아가면 바로 받아들인다 */
    CHECK_EQ(gear_check_step(&st, GEAR_D, true, 3000), GEAR_D);
    /* N이나 P를 거쳐도 반대 방향은 속도를 본다 */
    CHECK_EQ(gear_check_step(&st, GEAR_N, true, 3000), GEAR_N);
    CHECK_EQ(gear_check_step(&st, GEAR_R, true, 3000), GEAR_N);
    CHECK_EQ(gear_check_step(&st, GEAR_P, true, 3000), GEAR_P);
    CHECK_EQ(gear_check_step(&st, GEAR_R, true, 3000), GEAR_N);
    /* 속도가 낮아지면 받아들인다. 이제 받아들인 방향은 R이고, D가 반대 방향이다 */
    CHECK_EQ(gear_check_step(&st, GEAR_R, true, 138), GEAR_R);
    CHECK_EQ(gear_check_step(&st, GEAR_R, true, 3000), GEAR_R);
    CHECK_EQ(gear_check_step(&st, GEAR_D, true, 3000), GEAR_N);
    CHECK_EQ(gear_check_step(&st, GEAR_D, true, 0), GEAR_D);

    /* 받아들이지 못한 채 50주기 이어지면 주의를 요청한다 */
    gear_check_init(&st);
    CHECK_EQ(gear_check_step(&st, GEAR_D, true, 0), GEAR_D);
    for (int i = 0; i < 49; i++) {
        CHECK_EQ(gear_check_step(&st, GEAR_R, true, 2000), GEAR_N);
        CHECK(!st.caution);
    }
    CHECK_EQ(gear_check_step(&st, GEAR_R, true, 2000), GEAR_N);
    CHECK(st.caution);
    /* 오래 이어져도 주의는 그대로다 (세는 값이 넘쳐 0으로 돌아가지 않는다) */
    for (int i = 0; i < 300; i++) {
        (void)gear_check_step(&st, GEAR_R, true, 2000);
        CHECK(st.caution);
    }
    /* 조건이 풀리면 (속도가 낮아져 받아들이면) 주의를 거둔다 */
    CHECK_EQ(gear_check_step(&st, GEAR_R, true, 100), GEAR_R);
    CHECK(!st.caution);

    /* 중간에 N을 고르면 세던 것을 지운다 */
    gear_check_init(&st);
    CHECK_EQ(gear_check_step(&st, GEAR_D, true, 0), GEAR_D);
    for (int i = 0; i < 49; i++) {
        (void)gear_check_step(&st, GEAR_R, true, 2000);
    }
    CHECK_EQ(gear_check_step(&st, GEAR_N, true, 2000), GEAR_N);
    for (int i = 0; i < 49; i++) {
        (void)gear_check_step(&st, GEAR_R, true, 2000);
    }
    CHECK(!st.caution);
    (void)gear_check_step(&st, GEAR_R, true, 2000);
    CHECK(st.caution);
    /* 가던 방향을 다시 고르면 주의를 거둔다 */
    CHECK_EQ(gear_check_step(&st, GEAR_D, true, 2000), GEAR_D);
    CHECK(!st.caution);

    /* 기억한 방향이 알 수 없는 값이 되어도 (memory의 값이 틀려도) 속도를 본다 */
    st.direction = (gear_t)7;
    CHECK_EQ(gear_check_step(&st, GEAR_D, true, 3000), GEAR_N);
    CHECK_EQ(gear_check_step(&st, GEAR_D, true, 0), GEAR_D);
}

int main(void)
{
    static const test_case_t cases[] = {
        { "TC-001", "전압을 페달 위치로 바꾼다", tc_001 },
        { "TC-002", "페달 채널의 범위와 불일치를 검사한다", tc_002 },
        { "TC-003", "검사 실패가 3주기 이어지면 페달 고장이다", tc_003 },
        { "TC-004", "안전한 페달 값은 작은 쪽이고, 믿을 수 없으면 0이다", tc_004 },
        { "TC-005", "허용 토크가 0인 조건", tc_005 },
        { "TC-006", "허용 토크의 계산", tc_006 },
        { "TC-007", "허용 토크와 정상인 기능의 토크 요구가 맞물린다", tc_007 },
        { "TC-008", "출력은 기어의 방향과 허용 토크 안에 있다", tc_008 },
        { "TC-009", "깎인 주기가 5번 이어지면 고정한다", tc_009 },
        { "TC-010", "고정된 뒤에는 토크 0이다", tc_010 },
        { "TC-011", "입력이 바뀌어 토크를 올리는 동안에도 허용 토크가 앞서지 않는다", tc_011 },
        { "TC-012", "허용 토크는 지난 출력에서 25 Nm까지만 오른다", tc_012 },
        { "TC-013", "입력이 거듭 바뀌어도 틀린 기능의 토크는 55 Nm 넘게 앞서지 않는다", tc_013 },
        { "TC-014", "최근 100주기 가운데 실패가 10번을 넘으면 페달 고장이다", tc_014 },
        { "TC-015", "고장 대응의 상태는 안전한 쪽으로만 바뀐다", tc_015 },
        { "TC-016", "브레이크는 두 접점으로 판정한다", tc_016 },
        { "TC-017", "보내는 메시지에 counter와 CRC를 붙인다", tc_017 },
        { "TC-018", "받은 메시지의 CRC, data ID, counter, 시간을 검사한다", tc_018 },
        { "TC-019", "방향의 바뀜은 속도가 유효하고 낮을 때만 받아들인다", tc_019 },
        { "FT-001", "기능: 토크 요구의 계산", ft_001 },
        { "FT-002", "기능: 토크를 올리는 속도", ft_002 },
        { "FT-003", "기능: 제동 우선", ft_003 },
    };
    return (test_run_all(cases, (int)(sizeof(cases) / sizeof(cases[0]))) == 0) ? 0 : 1;
}
