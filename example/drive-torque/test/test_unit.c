/*
 * 책의 예제 코드다. 실제 제품에 쓸 수 없다.
 * 요구사항에 따른 unit test: 입력 검사, 감시, 출력 단계.
 * test마다 어느 요구사항을 보는지 "TC-번호: SWR-번호"로 적는다.
 *
 * 기댓값은 요구사항 (docs/requirements.yaml)의 숫자를 그대로 적는다.
 * 제품 코드의 상수 이름을 쓰지 않는다. 상수가 잘못 바뀌면 test가 실패해야 하기 때문이다.
 */
#include "app.h"
#include "input.h"
#include "monitor.h"
#include "test.h"

/* 센서가 정상일 때의 전압 */
static millivolt_t apps1(permille_t pedal) { return 500 + (4 * pedal); }
static millivolt_t apps2(permille_t pedal) { return 250 + (2 * pedal); }

static inputs_t inputs(millivolt_t a1, millivolt_t a2)
{
    inputs_t in = { a1, a2, false, GEAR_D };
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

    /* 알려진 한계: 실패와 통과가 번갈아 나오는 간헐 고장은 판정되지 않는다 */
    make_ready(&st);
    for (int i = 0; i < 50; i++) {
        (void)pedal_check_step(&st, &bad);
        (void)pedal_check_step(&st, &good);
    }
    CHECK(!st.fault);
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
     * 토크 요구의 크기는 그 주기의 목표 (페달에 비례하는 값. 후진은 그 40%)를 넘지 않는다 */
    {
        app_t app;
        uint32_t seed = 12345u;
        permille_t pedal = 0;
        bool brake = false;
        gear_t gear = GEAR_D;
        int over_target = 0;

        clamped = 0;
        app_init(&app);
        for (int i = 0; i < 100000; i++) {
            seed = (seed * 1664525u) + 1013904223u;
            if (((seed >> 8) % 6u) == 0u) {
                pedal = (permille_t)((seed >> 12) % 1001u);
            }
            if (((seed >> 20) % 11u) == 0u) {
                brake = !brake;
            }
            if (((seed >> 24) % 13u) == 0u) {
                gear = gears[(seed >> 28) % 4u];
            }
            torque_t req = app_step(&app, pedal, brake, gear);
            torque_t allowed = monitor_allowed_torque(pedal, brake, gear);
            torque_t mag = (req < 0) ? -req : req;
            torque_t target = (pedal * 2500) / 1000;
            if (gear == GEAR_R) {
                target = (target * 40) / 100;
            }
            if (output_clamp(req, allowed, gear) != req) {
                clamped++;
            }
            if (mag > target) {
                over_target++;
            }
        }
        CHECK_EQ(clamped, 0);
        CHECK_EQ(over_target, 0);
    }
}

/* 운전자의 입력 한 벌 */
typedef struct {
    permille_t pedal;
    bool brake;
    gear_t gear;
} drive_t;

/*
 * TC-011: SWR-06 입력이 한 번 바뀐 뒤 기능이 토크를 올리는 동안에는 허용 토크와의 차이가
 * 55 Nm 이상일 수 있다. 그 시간은 SG-01의 시간 (200 ms)보다 짧아야 하고,
 * 그 뒤에는 차이가 5 Nm로 돌아와야 한다.
 * 기능이 감시가 모르는 상태를 가지면 이 test가 실패한다.
 * 예: 브레이크를 놓은 뒤에도 토크 0을 유지하는 기능 (처음의 예제가 그랬다).
 */
static void tc_011(void)
{
    /* 바뀌기 전의 입력, 바뀐 뒤의 입력, 차이가 55 Nm 이상인 주기의 수.
     * 주기의 수는 요구사항의 숫자 (주기마다 25 Nm, 오차 5 Nm)에서 계산한 값이다 */
    static const struct {
        drive_t before;
        drive_t after;
        int wide_cycles;
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
        int wide_cycles = 0;
        int clamped = 0;
        torque_t gap = 0;

        app_init(&app);
        for (int i = 0; i < 40; i++) {
            (void)app_step(&app, before->pedal, before->brake, before->gear);
        }
        for (int i = 0; i < 100; i++) {
            torque_t req = app_step(&app, after->pedal, after->brake, after->gear);
            torque_t allowed = monitor_allowed_torque(after->pedal, after->brake, after->gear);
            torque_t mag = (req < 0) ? -req : req;
            if (output_clamp(req, allowed, after->gear) != req) {
                clamped++;
            }
            gap = allowed - mag;
            if (gap >= 550) {
                wide_cycles++;
            }
        }
        CHECK_EQ(clamped, 0);
        CHECK((wide_cycles * 10) < 200);
        CHECK_EQ(wide_cycles, cases[c].wide_cycles);
        /* 다 올린 뒤에는 허용 오차 5 Nm뿐이다.
         * 페달을 끝까지 밟으면 허용 토크가 최대 토크에서 잘려 차이가 0이다 */
        CHECK_EQ(gap, (after->pedal == 1000 && after->gear == GEAR_D) ? 0 : 50);
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

    output_stage_init(&st);
    /* 4번 깎이고 한 번 정상이면 다시 센다 */
    for (int i = 0; i < 4; i++) {
        CHECK_EQ(output_stage_step(&st, 2000, 1000, GEAR_D), 1000);
    }
    CHECK(!st.latched);
    CHECK_EQ(output_stage_step(&st, 900, 1000, GEAR_D), 900);
    for (int i = 0; i < 4; i++) {
        (void)output_stage_step(&st, 2000, 1000, GEAR_D);
    }
    CHECK(!st.latched);
    /* 5번째로 이어서 깎인 주기에 고정한다 */
    (void)output_stage_step(&st, 2000, 1000, GEAR_D);
    CHECK(st.latched);
    CHECK_EQ(st.clamp_count, 9);
}

/* TC-010: SWR-09 고정된 뒤에는 토크 0을 보낸다 */
static void tc_010(void)
{
    output_stage_t st;

    output_stage_init(&st);
    for (int i = 0; i < 4; i++) {
        (void)output_stage_step(&st, 2000, 1000, GEAR_D);
    }
    /* 고정되는 바로 그 주기부터 0이다 */
    CHECK_EQ(output_stage_step(&st, 2000, 1000, GEAR_D), 0);
    /* 그 뒤에 요구가 정상이어도 0이고, 고정은 풀리지 않는다 */
    for (int i = 0; i < 10; i++) {
        CHECK_EQ(output_stage_step(&st, 500, 1000, GEAR_D), 0);
    }
    CHECK(st.latched);
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
        { "TC-011", "입력이 바뀐 뒤 토크를 올리는 동안의 차이는 200 ms보다 짧다", tc_011 },
        { "FT-001", "기능: 토크 요구의 계산", ft_001 },
        { "FT-002", "기능: 토크를 올리는 속도", ft_002 },
        { "FT-003", "기능: 제동 우선", ft_003 },
    };
    return (test_run_all(cases, (int)(sizeof(cases) / sizeof(cases[0]))) == 0) ? 0 : 1;
}
