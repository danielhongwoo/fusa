/*
 * 책의 예제 코드다. 실제 제품에 쓸 수 없다.
 * 요구사항에 따른 unit test: 입력 검사, 감시, 출력 단계.
 * test마다 어느 요구사항을 보는지 "TC-번호: SWR-번호"로 적는다.
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
    inputs_t in = { a1, a2, false, GEAR_D, true, 0 };
    return in;
}

/* 검사를 통과하는 입력으로 켠 직후의 구간을 지난다 */
static void make_ready(pedal_check_t *st)
{
    inputs_t in = inputs(apps1(0), apps2(0));
    pedal_check_init(st);
    for (int i = 0; i < (int)PEDAL_READY_CYCLES; i++) {
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

/* 같은 입력을 PEDAL_FAULT_CYCLES번 넣은 뒤에 페달 고장인지 돌려준다 */
static bool faults_after_cycles(millivolt_t a1, millivolt_t a2)
{
    pedal_check_t st;
    inputs_t in = inputs(a1, a2);

    make_ready(&st);
    for (int i = 0; i < (int)PEDAL_FAULT_CYCLES; i++) {
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
}

/* TC-005: SWR-05 허용 토크가 0인 조건 */
static void tc_005(void)
{
    CHECK_EQ(monitor_allowed_torque(0, false, GEAR_D), 0);
    CHECK_EQ(monitor_allowed_torque(PEDAL_RELEASED - 1, false, GEAR_D), 0);
    CHECK(monitor_allowed_torque(PEDAL_RELEASED, false, GEAR_D) > 0);
    CHECK_EQ(monitor_allowed_torque(500, true, GEAR_D), 0);
    CHECK_EQ(monitor_allowed_torque(500, false, GEAR_P), 0);
    CHECK_EQ(monitor_allowed_torque(500, false, GEAR_N), 0);
    CHECK(monitor_allowed_torque(500, false, GEAR_R) > 0);
    CHECK_EQ(monitor_allowed_torque(500, false, (gear_t)7), 0);
}

/* TC-006: SWR-06 허용 토크는 페달 위치에 비례하는 상한에 오차를 더한 값이다 */
static void tc_006(void)
{
    CHECK_EQ(monitor_allowed_torque(500, false, GEAR_D), 1250 + TORQUE_TOLERANCE);
    CHECK_EQ(monitor_allowed_torque(100, false, GEAR_D), 250 + TORQUE_TOLERANCE);
    CHECK_EQ(monitor_allowed_torque(100, false, GEAR_R), 250 + TORQUE_TOLERANCE);
    /* 최대 토크를 넘지 않는다 */
    CHECK_EQ(monitor_allowed_torque(1000, false, GEAR_D), TORQUE_MAX);
    /* 범위 밖의 페달 값은 자른다 */
    CHECK_EQ(monitor_allowed_torque(5000, false, GEAR_D), TORQUE_MAX);
    CHECK_EQ(monitor_allowed_torque(-5, false, GEAR_D), 0);
}

/*
 * TC-007: SWR-06 허용 토크는 정상인 기능의 토크 요구보다 작지 않다.
 * 정상인 기능을 입력의 격자에서 돌려, 한 번도 깎이지 않는지 본다.
 */
static void tc_007(void)
{
    static const gear_t gears[] = { GEAR_P, GEAR_R, GEAR_N, GEAR_D };
    static const speed_t speeds[] = { -500, 0, 800, 1500, 3000, 6000 };
    int clamped = 0;

    for (int g = 0; g < 4; g++) {
        for (int s = 0; s < 6; s++) {
            for (int valid = 0; valid < 2; valid++) {
                for (int brake = 0; brake < 2; brake++) {
                    app_t app;
                    app_init(&app);
                    /* 페달을 올렸다가 내린다. 기능에는 지난 주기의 상태가 있다 */
                    for (permille_t p = 0; p <= 2000; p += 7) {
                        permille_t pedal = (p <= 1000) ? p : (2000 - p);
                        torque_t req = app_step(&app, pedal, brake != 0, gears[g], valid != 0,
                                                speeds[s]);
                        torque_t allowed = monitor_allowed_torque(pedal, brake != 0, gears[g]);
                        if (output_clamp(req, allowed, gears[g]) != req) {
                            clamped++;
                        }
                    }
                }
            }
        }
    }
    CHECK_EQ(clamped, 0);
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
static torque_t app_settle(app_t *app, permille_t pedal, bool brake, gear_t gear, bool speed_valid,
                           speed_t speed)
{
    torque_t req = 0;
    for (int i = 0; i < 40; i++) {
        req = app_step(app, pedal, brake, gear, speed_valid, speed);
    }
    return req;
}

/*
 * 아래 FT-는 기능의 test다. 기능에는 SG-01의 안전 요구사항이 없으므로 요구사항 추적에 넣지 않는다.
 * 그래도 기능의 코드에 같은 방법 (test와 coverage 측정)을 적용한다.
 */

/* FT-001: 토크 요구는 페달 위치에 비례하고, 높은 속도에서는 줄어든다 */
static void ft_001(void)
{
    app_t app;

    app_init(&app);
    CHECK_EQ(app_settle(&app, 500, false, GEAR_D, true, 0), 1250);
    CHECK_EQ(app_settle(&app, 1000, false, GEAR_D, true, 1500), 2500);
    CHECK_EQ(app_settle(&app, 1000, false, GEAR_D, true, 3000), 1250);  /* 속도가 2배면 절반 */
    CHECK_EQ(app_settle(&app, 1000, false, GEAR_D, true, 9000), 625);   /* 속도의 상한은 60 m/s */
    CHECK_EQ(app_settle(&app, 1000, false, GEAR_D, false, 0), 1250);    /* 속도를 모르면 절반 */
    CHECK_EQ(app_settle(&app, 1000, false, GEAR_D, true, -3000), 1250); /* 속도의 부호는 보지 않는다 */
    /* 범위 밖의 페달 값은 자른다 */
    CHECK_EQ(app_settle(&app, 1500, false, GEAR_D, true, 0), 2500);
    CHECK_EQ(app_settle(&app, -5, false, GEAR_D, true, 0), 0);
    /* P와 N에서는 0, R에서는 음수이고 40%까지 */
    CHECK_EQ(app_settle(&app, 500, false, GEAR_P, true, 0), 0);
    CHECK_EQ(app_settle(&app, 500, false, GEAR_N, true, 0), 0);
    CHECK_EQ(app_settle(&app, 500, false, GEAR_R, true, 0), -500);
}

/* FT-002: 토크는 한 주기에 10 Nm씩 올리고, 내릴 때는 바로 내린다 */
static void ft_002(void)
{
    app_t app;

    app_init(&app);
    CHECK_EQ(app_step(&app, 1000, false, GEAR_D, true, 0), 100);
    CHECK_EQ(app_step(&app, 1000, false, GEAR_D, true, 0), 200);
    CHECK_EQ(app_step(&app, 40, false, GEAR_D, true, 0), 100);
    CHECK_EQ(app_step(&app, 0, false, GEAR_D, true, 0), 0);
    CHECK_EQ(app_step(&app, 1000, false, GEAR_R, true, 0), -100);
    CHECK_EQ(app_step(&app, 1000, false, GEAR_R, true, 0), -200);
    CHECK_EQ(app_step(&app, 1000, false, GEAR_N, true, 0), 0);
}

/* FT-003: 제동 우선은 두 페달을 함께 밟으면 걸리고, 가속 페달을 놓아야 풀린다 */
static void ft_003(void)
{
    app_t app;

    app_init(&app);
    CHECK(app_settle(&app, 500, false, GEAR_D, true, 0) > 0);
    CHECK_EQ(app_step(&app, 500, true, GEAR_D, true, 0), 0);  /* 함께 밟음 */
    CHECK_EQ(app_step(&app, 500, false, GEAR_D, true, 0), 0); /* 브레이크만 놓음: 아직 0 */
    CHECK_EQ(app_step(&app, 0, false, GEAR_D, true, 0), 0);   /* 가속 페달을 놓음: 풀림 */
    CHECK(app_step(&app, 500, false, GEAR_D, true, 0) > 0);
    /* 가속 페달을 놓은 채 브레이크만 밟으면 걸리지 않는다 */
    CHECK_EQ(app_step(&app, 0, true, GEAR_D, true, 0), 0);
    CHECK(app_step(&app, 500, false, GEAR_D, true, 0) > 0);
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
        { "TC-007", "정상인 기능은 깎이지 않는다", tc_007 },
        { "TC-008", "출력은 기어의 방향과 허용 토크 안에 있다", tc_008 },
        { "TC-009", "깎인 주기가 5번 이어지면 고정한다", tc_009 },
        { "TC-010", "고정된 뒤에는 토크 0이다", tc_010 },
        { "FT-001", "기능: 토크 요구의 계산", ft_001 },
        { "FT-002", "기능: 토크를 올리는 속도", ft_002 },
        { "FT-003", "기능: 제동 우선", ft_003 },
    };
    return (test_run_all(cases, (int)(sizeof(cases) / sizeof(cases[0]))) == 0) ? 0 : 1;
}
