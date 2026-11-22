#!/usr/bin/env python3
"""증명이 결함을 잡는지 본다: 제품 코드에 결함을 하나씩 넣고 그 성질의 증명을 돌린다.

    tools/proof_mutation.py

tools/mutation_check.py가 test에 하는 일을 증명에 한다. 예제 폴더를 임시 폴더에 복사하고,
복사본의 소스 한 곳을 바꾼 뒤 그 성질만 증명한다 (PROPS=... tools/prove.sh).
증명이 실패하면 그 결함을 잡은 것이다. 하나라도 놓치면 이 도구는 실패한다.

넣는 결함은 "증명이 본다"고 문서가 적은 것이다. 처음에는 이 도구가 없었고, 문서는
"배열 밖에 쓰지 않는다는 것을 증명이 본다"고 적었다. 검토자가 범위 검사를 한 칸 어긋나게 바꾸고
증명을 돌려, 그 말이 틀렸다는 것을 보였다 (docs/test-report.md 6절).

한계: 여기에 넣은 결함을 잡는다는 것만 보인다. 이 도구는 qualification되지 않았다.
"""
import os
import shutil
import subprocess
import sys
import tempfile

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

# (파일, 원래 코드, 바꾼 코드, 돌릴 성질, 설명)
MUTANTS = [
    ("src/flow/flow.c", "    if (f->count < FLOW_TASK_COUNT) {\n        f->marks[f->count] = mark;",
     "    if (f->count <= FLOW_TASK_COUNT) {\n        f->marks[f->count] = mark;", "prove_flow",
     "표시를 적을 자리의 범위 검사가 하나 어긋난다 (배열의 바로 뒤에 쓴다)"),
    ("src/input/pedal_check.c", "    if (st->window_pos >= PEDAL_WINDOW_CYCLES) {\n        st->window_pos = 0u;",
     "    if (st->window_pos > PEDAL_WINDOW_CYCLES) {\n        st->window_pos = 0u;", "prove_pedal_check",
     "기록을 적을 자리의 범위 검사가 하나 어긋난다"),
    ("src/monitor/inverter_check.c", "    if (st->pos >= INVERTER_HISTORY_CYCLES) {\n        st->pos = 0u;",
     "    if (st->pos > INVERTER_HISTORY_CYCLES) {\n        st->pos = 0u;", "prove_inverter_check",
     "보낸 토크를 적을 자리의 범위 검사가 하나 어긋난다"),
    ("src/flow/flow.c", "    answer = ((answer * 31u) + f->count) & 0xFFu;\n", "", "prove_flow",
     "답에 표시의 수를 넣지 않는다"),
    ("src/flow/flow.c", "        f->marks[i] = 0u;\n    }\n    f->count = 0u;\n    f->question = (uint8_t)",
     "    }\n    f->count = 0u;\n    f->question = (uint8_t)", "prove_flow",
     "주기를 닫을 때 표시의 값을 지우지 않는다"),
    ("src/com/e2e.c", "            st->ok = false;\n        } else {",
     "            st->ok = false;\n            st->last_counter = frame->counter;\n        } else {",
     "prove_message_change_detected", "CRC가 틀린 메시지가 counter의 기준을 바꾼다"),
    ("src/input/gear_check.c", "if (speed_valid && (speed >= 0) && (speed < GEAR_CHANGE_SPEED_MAX)) {",
     "if (speed_valid && (speed < GEAR_CHANGE_SPEED_MAX)) {", "prove_gear_check",
     "차량 속도가 음수인 것을 받아들인다"),
    ("src/reaction/reaction.h", "#define LIMP_APP_TORQUE ((torque_t)350)", "#define LIMP_APP_TORQUE ((torque_t)349)",
     "prove_normal_function_not_clamped", "줄여 감의 기능의 상한을 0.1 Nm 낮춘다 (감시와의 틈이 5 Nm를 넘는다)"),
    ("src/monitor/monitor.h", "#define ALLOWED_RISE_PER_CYCLE ((torque_t)250)", "#define ALLOWED_RISE_PER_CYCLE ((torque_t)251)",
     "prove_faulty_function_bounded", "감시가 허용하는 오르는 속도를 0.1 Nm 올린다"),
]


def main():
    missed = 0
    with tempfile.TemporaryDirectory() as work:
        for i, (path, old, new, prop, what) in enumerate(MUTANTS):
            copy = os.path.join(work, "p%02d" % i)
            shutil.copytree(ROOT, copy, ignore=shutil.ignore_patterns("build"))
            target = os.path.join(copy, path)
            text = open(target, encoding="utf-8").read()
            if text.count(old) != 1:
                print("오류  %s: 바꿀 곳을 찾지 못했다 (%s)" % (path, what))
                missed += 1
                continue
            open(target, "w", encoding="utf-8").write(text.replace(old, new))
            env = dict(os.environ, PROPS=prop)
            result = subprocess.run(["sh", "tools/prove.sh"], cwd=copy, capture_output=True, text=True, env=env)
            if result.returncode != 0 and ("실패    " + prop) in result.stdout:
                print("잡음  %s (%s)" % (what, prop))
            else:
                print("놓침  %s (%s)" % (what, prop))
                missed += 1
    print("증명의 변이: 결함 %d개 가운데 %d개를 증명이 잡았다" % (len(MUTANTS), len(MUTANTS) - missed))
    return 1 if missed else 0


if __name__ == "__main__":
    sys.exit(main())
