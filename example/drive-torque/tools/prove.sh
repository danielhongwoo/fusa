#!/bin/sh
# 책의 예제다. 실제 제품에 쓸 수 없다.
# CBMC로 test/proof/harness.c의 성질을 하나씩 증명한다.
# 사용법: sh tools/prove.sh   (example/drive-torque 폴더에서)
#
# CBMC는 시작 함수에서 닿지 않는 성질도 SUCCESS로 적는다.
# 그래서 성질마다 따로 돌리고, 그 성질의 assert가 결과에 실제로 있는지를 함께 본다.
# 반복문은 101번까지 펼친다 (가장 긴 반복이 100번이다). 그보다 길게 도는 반복이 있으면 실패한다.
# CBMC는 qualification되지 않았다.

INC="-Isrc/common -Isrc/hal -Isrc/input -Isrc/app -Isrc/monitor -Isrc/reaction -Isrc/com"
SRC="src/input/pedal_check.c src/input/brake_check.c src/monitor/monitor.c src/reaction/reaction.c src/com/e2e.c src/app/app.c test/proof/harness.c"
REPORT=build/reports/cbmc.txt
fail=0

mkdir -p build/reports
: > "$REPORT"

PROPS="prove_allowed_torque prove_output_clamp prove_output_stage prove_pedal_check prove_limit_rise prove_normal_function_not_clamped prove_faulty_function_bounded prove_reaction prove_brake_check prove_message_rules prove_message_change_detected"
count=0

for prop in $PROPS; do
    count=$((count + 1))
    out=$(cbmc $INC $SRC --function "$prop" \
        --signed-overflow-check --div-by-zero-check --conversion-check --bounds-check \
        --unwind 101 --unwinding-assertions 2>&1)
    echo "==== $prop" >> "$REPORT"
    echo "$out" | grep -E '^\[|VERIFICATION' >> "$REPORT"
    reached=$(echo "$out" | grep -c "^\[$prop\.assertion\.[0-9]*\].*SUCCESS")
    if echo "$out" | grep -q "VERIFICATION SUCCESSFUL" && [ "$reached" -gt 0 ]; then
        echo "증명됨  $prop (assert $reached개)"
    else
        echo "실패    $prop"
        echo "$out" | grep -E 'FAILURE|VERIFICATION|error' | head -10
        fail=1
    fi
done

if [ "$fail" -ne 0 ]; then
    echo "증명: 실패한 성질이 있다 (보고서: $REPORT)"
    exit 1
fi
echo "증명: 성질 ${count}개가 모든 입력에서 성립한다 (보고서: $REPORT)"
