#!/bin/sh
# GCC로 제품 코드의 coverage (statement, branch, MC/DC)를 잰다.
# 사용법: sh tools/coverage.sh <gcc> <gcov> "<cflags>"   (example/drive-torque 폴더에서)
#
# 재는 대상은 src/의 코드다. test 코드, 시뮬레이션, 결함 모듈은 재지 않는다.
# 세 test 실행 파일이 같은 object 파일을 쓰므로 결과가 합쳐진다.
# gcov는 qualification되지 않았다.
set -e

GCC=$1
GCOV=$2
CFLAGS=$3
R=../..
INC="-I$R/src/common -I$R/src/hal -I$R/src/input -I$R/src/app -I$R/src/monitor -I$R/src/reaction -I$R/src/com -I$R/src/flow -I$R/src/vcu -I$R/sim -I$R/test -I$R/test/faulty"
COV="--coverage -fcondition-coverage"

mkdir -p build/cov build/out build/reports
rm -f build/cov/*.gcda build/cov/*.gcno build/cov/*.gcov
cd build/cov

# 제품 코드: 재는 대상
for f in src/input/pedal_check.c src/input/brake_check.c src/input/gear_check.c src/input/input.c src/monitor/monitor.c src/monitor/inverter_check.c src/reaction/reaction.c src/com/e2e.c src/flow/flow.c src/vcu/vcu.c src/app/app.c; do
    $GCC $CFLAGS $COV $INC -c -o "$(basename "$f" .c).o" "$R/$f"
done
# 결함 모듈이 감싸는 기능: 이름만 바꿔 compile한다. 재지 않는다
$GCC $CFLAGS $INC -Dapp_init=app_good_init -Dapp_step=app_good_step -c -o app_good.o "$R/src/app/app.c"

SIM="$R/sim/plant.c $R/sim/frame_sim.c $R/sim/hal_sim.c $R/sim/scenario.c"
$GCC $CFLAGS $INC -o cov_unit \
    pedal_check.o brake_check.o gear_check.o monitor.o inverter_check.o reaction.o e2e.o flow.o app.o "$R/test/test_run.c" "$R/test/test_unit.c" -lgcov -lm
$GCC $CFLAGS $INC -o cov_scenario \
    pedal_check.o brake_check.o gear_check.o input.o monitor.o inverter_check.o reaction.o e2e.o flow.o vcu.o app.o \
    $SIM "$R/test/test_run.c" "$R/test/test_scenario.c" -lgcov -lm
$GCC $CFLAGS $INC -o cov_fault_app \
    pedal_check.o brake_check.o gear_check.o input.o monitor.o inverter_check.o reaction.o e2e.o flow.o vcu.o app_good.o \
    "$R/test/faulty/app_fault.c" $SIM "$R/test/test_run.c" "$R/test/test_fault_app.c" -lgcov -lm

# test는 예제 폴더에서 돌린다 (기록 파일의 경로 때문에)
(cd "$R" && build/cov/cov_unit > /dev/null && build/cov/cov_scenario > /dev/null \
    && build/cov/cov_fault_app > /dev/null)

$GCOV --conditions --branch-probabilities \
    pedal_check.gcda brake_check.gcda gear_check.gcda input.gcda monitor.gcda inverter_check.gcda reaction.gcda e2e.gcda flow.gcda vcu.gcda app.gcda > gcov.txt 2>&1

cd "$R"
# 요약 도구의 종료 상태를 그대로 넘긴다. 전에는 출력을 tee로 넘겨서 pipe의 끝 (tee)의 상태만 남았고,
# 100%에 못 미친다고 찍고도 이 단계가 통과했다 (docs/test-report.md 6절)
status=0
python3 tools/coverage_summary.py build/cov/gcov.txt > build/reports/coverage.txt || status=$?
cat build/reports/coverage.txt
exit "$status"
