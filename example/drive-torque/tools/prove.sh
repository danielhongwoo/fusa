#!/bin/sh
# CBMC로 test/proof/harness.c의 성질을 하나씩 증명한다.
# 사용법: sh tools/prove.sh   (example/drive-torque 폴더에서)
#
# CBMC는 시작 함수에서 도달하지 않는 성질도 SUCCESS로 적는다.
# 그래서 성질마다 따로 돌리고, 그 성질의 assert가 결과에 실제로 있는지를 함께 본다.
# 반복문은 101번까지 펼친다 (가장 긴 반복이 100번이다). 그보다 길게 도는 반복이 있으면 실패한다.
# CBMC는 qualification되지 않았다.

INC="-Isrc/common -Isrc/hal -Isrc/input -Isrc/app -Isrc/monitor -Isrc/reaction -Isrc/com -Isrc/flow"
SRC="src/input/pedal_check.c src/input/brake_check.c src/input/gear_check.c src/monitor/monitor.c src/monitor/inverter_check.c src/reaction/reaction.c src/com/e2e.c src/flow/flow.c src/app/app.c test/proof/harness.c"
REPORT=build/reports/cbmc.txt
fail=0

mkdir -p build/reports
: > "$REPORT"

DEFAULT_PROPS="prove_allowed_torque prove_output_clamp prove_output_stage prove_pedal_check prove_limit_rise prove_normal_function_not_clamped prove_faulty_function_bounded prove_reaction prove_brake_check prove_message_rules prove_message_change_detected prove_gear_check prove_inverter_check prove_flow prove_inverter_check_bounded"
# PROPS를 주면 그 성질만 돌린다 (tools/proof_mutation.py가 쓴다)
PROPS="${PROPS:-$DEFAULT_PROPS}"
count=0

# 도구의 확인: 배열 경계 검사가 듣는가. 구조체의 끝에 있는 배열을 한 칸 넘는 쓰기는 잡아야 한다.
# 배열 뒤에 다른 필드가 있으면 이 도구는 잡지 못한다 (알려진 한계). 제품의 구조체는 그래서 배열을 끝에 둔다
tool_last=$(cbmc test/proof/tool_check.c --function canary_array_last --bounds-check --pointer-check 2>&1)
tool_inside=$(cbmc test/proof/tool_check.c --function canary_array_inside --bounds-check --pointer-check 2>&1)
if echo "$tool_last" | grep -q "VERIFICATION FAILED"; then
    echo "도구 확인: 구조체의 끝에 있는 배열을 한 칸 넘는 쓰기를 잡는다"
else
    echo "도구 확인: 실패. 배열 경계 검사가 듣지 않는다"
    fail=1
fi
if echo "$tool_inside" | grep -q "VERIFICATION SUCCESSFUL"; then
    echo "도구의 한계: 배열 뒤에 다른 필드가 있으면 한 칸 넘는 쓰기를 잡지 못한다 (제품의 구조체는 배열을 끝에 둔다)"
else
    echo "도구 확인: 이 판의 도구는 배열 뒤에 필드가 있어도 한 칸 넘는 쓰기를 잡는다"
fi

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
    elif echo "$out" | grep -q "VERIFICATION FAILED"; then
        echo "실패    $prop"
        echo "$out" | grep -E 'FAILURE|VERIFICATION|error' | head -10
        fail=1
    else
        # 증명이 실패한 것이 아니라 도구가 끝까지 돌지 못했다 (읽지 못하는 코드, 도달하지 않은 assert)
        echo "오류    $prop (도구가 판정을 내지 못했다)"
        echo "$out" | grep -iE 'error|VERIFICATION' | head -10
        fail=1
    fi
done

if [ "$fail" -ne 0 ]; then
    echo "증명: 실패한 성질이 있다 (보고서: $REPORT)"
    exit 1
fi
echo "증명: 성질 ${count}개가 모든 입력에서 성립한다 (보고서: $REPORT)"
