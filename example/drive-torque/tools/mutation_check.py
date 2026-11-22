#!/usr/bin/env python3
"""test가 결함을 잡는지 본다: 제품 코드에 결함을 하나씩 넣고 test를 돌린다.

    tools/mutation_check.py

예제 폴더를 임시 폴더에 복사하고, 복사본의 소스 한 곳을 바꾼 뒤 `make test`를 돌린다.
test가 실패하면 그 결함을 잡은 것이다. 하나라도 놓치면 이 도구는 실패한다.
원본은 건드리지 않는다.

넣는 결함은 두 가지다.
  1. 손으로 고른 것: 조건을 빼거나 뒤집는다 (MUTANTS)
  2. 자동으로 만든 것: 상수를 하나씩 1 올린다 (CONSTANT_FILES).
     안전 요구사항을 받는 파일과, 감시의 한계와 맞물리는 기능의 상수다

동등한 변이: 코드를 바꿔도 밖에서 보이는 동작이 같으면 어떤 test도 잡을 수 없다.
그런 변이는 EQUIVALENT에 이유와 함께 적는다. 돌려 보고 결과를 "동등"으로 내며, 놓친 것으로 세지 않는다.
이유를 적지 않고 여기에 옮기면 안 된다. 놓친 변이를 숨기는 길이 되기 때문이다.
동등한 변이를 test가 잡으면 이유가 틀린 것이므로 도구가 실패한다.

한계: 여기에 넣은 결함을 잡는다는 것만 보인다. 다른 결함도 잡는다는 뜻이 아니다.
상수는 1 올리는 것만 넣는다. 이 도구는 qualification되지 않았다.
"""
import os
import re
import shutil
import subprocess
import sys
import tempfile

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

# (파일, 원래 코드, 바꾼 코드, 설명)
MUTANTS = [
    ("src/monitor/monitor.c", "if ((p < PEDAL_RELEASED) || brake ||",
     "if ((p < PEDAL_RELEASED) || (brake && (p < 0)) ||", "허용 토크에서 브레이크 조건을 없앤다"),
    ("src/monitor/monitor.c", "if (torque_req > hi) {\n        return hi;",
     "if (torque_req > hi) {\n        return torque_req;", "넘는 토크를 깎지 않고 보낸다"),
    ("src/monitor/monitor.c", "if (st->excess_cycles >= EXCESS_LATCH_CYCLES) {",
     "if (st->excess_cycles > EXCESS_LATCH_CYCLES) {", "기능의 고장을 고정하지 않는다"),
    ("src/monitor/monitor.c", "+= TORQUE_TOLERANCE;", "+= (4 * TORQUE_TOLERANCE);",
     "허용 오차를 4배로 한다"),
    ("src/monitor/monitor.c", "+= TORQUE_TOLERANCE;", "+= 0;", "허용 오차를 0으로 한다"),
    ("src/monitor/monitor.c", "allowed = (allowed * ALLOWED_REVERSE_PCT) / 100;", "",
     "후진의 허용 토크를 전진과 같게 한다"),
    ("src/monitor/monitor.c", "lo = -allowed;", "lo = -allowed; hi = allowed;",
     "후진 기어에서 전진 토크를 허용한다"),
    ("src/monitor/monitor.c", "    if (st->latched) {\n        return 0;\n    }\n", "",
     "고정된 뒤에도 토크를 보낸다"),
    ("src/input/pedal_check.c", "return (p1 < p2) ? p1 : p2;", "return (p1 > p2) ? p1 : p2;",
     "두 채널 가운데 큰 값을 고른다"),
    ("src/input/pedal_check.c", "|| (diff > PEDAL_MISMATCH_MAX);",
     "|| (diff > (2 * PEDAL_MISMATCH_MAX));", "불일치의 한계를 2배로 한다"),
    ("src/input/pedal_check.c", "if (st->fault || !st->ready) {", "if (st->fault) {",
     "켠 직후의 대기를 뺀다"),
    ("src/input/pedal_check.c", "    if (bad) {\n        st->good_cycles = 0u;", "    if (bad) {",
     "켠 직후의 통과를 이어서가 아니라 모두 합쳐 센다"),
    ("src/input/pedal_check.c", "    } else {\n        st->bad_cycles = 0u;", "    } else {",
     "실패를 이어서가 아니라 모두 합쳐 센다"),
    ("src/vcu/vcu.c", "vcu->enable = vcu->pedal_check.ready && !vcu->output.latched;",
     "vcu->enable = vcu->pedal_check.ready;", "고정되어도 구동 허용 신호를 끊지 않는다"),
    ("src/vcu/vcu.c", "vcu->enable = vcu->pedal_check.ready && !vcu->output.latched;",
     "vcu->enable = !vcu->output.latched;", "켠 직후에 구동을 허용한다"),
    ("src/vcu/vcu.c", "    hal_enable_write(false);\n}", "}",
     "켤 때 구동 허용 신호를 끊지 않는다"),
    ("src/vcu/vcu.c", "(vcu->pedal_check.fault || vcu->output.latched) ? WARNING_RED",
     "(vcu->output.latched) ? WARNING_RED", "페달 고장에 경고를 요청하지 않는다"),
    ("src/input/input.c", "in->gear = GEAR_N; /* 알 수 없는 값은 N으로 본다 */",
     "in->gear = GEAR_D;", "알 수 없는 기어 값을 D로 본다"),
]

# (파일, 원래 코드, 바꾼 코드, 설명, 동등한 이유)
EQUIVALENT = [
    ("src/monitor/monitor.c",
     "        if (st->excess_cycles < EXCESS_LATCH_CYCLES) {\n            st->excess_cycles++;\n        }",
     "        st->excess_cycles++;",
     "이어진 횟수를 한계에서 멈추지 않는다",
     "횟수가 한계에 닿은 주기에 고정되고, 고정은 풀리지 않는다. 그 뒤에 횟수가 넘쳐 0으로 돌아가도 "
     "출력과 진단 메시지는 같다"),
]

# 상수를 자동으로 바꿀 파일. 안전 요구사항을 받는 부분의 상수와,
# 감시의 한계와 맞물리는 기능의 상수 (올리는 속도, 후진의 비율)다
CONSTANT_FILES = ["src/input/input.h", "src/input/pedal_check.c", "src/monitor/monitor.h",
                  "src/common/types.h", "src/app/app.c"]
DEFINE = re.compile(r"^(#define\s+(\w+)\s+\(\((\w+)\)(\d+)u?\))", re.M)


def constant_mutants():
    found = []
    for path in CONSTANT_FILES:
        text = open(os.path.join(ROOT, path), encoding="utf-8").read()
        for m in DEFINE.finditer(text):
            old = m.group(1)
            new = old.replace(")" + m.group(4), ")" + str(int(m.group(4)) + 1), 1)
            found.append((path, old, new, "상수 %s를 %s에서 1 올린다" % (m.group(2), m.group(4))))
    return found


def main():
    mutants = [m + (None,) for m in MUTANTS + constant_mutants()] + EQUIVALENT
    count = len(mutants) - len(EQUIVALENT)
    work = tempfile.mkdtemp(prefix="mutation-")
    missed = 0
    try:
        for i, (path, old, new, what, why_equivalent) in enumerate(mutants):
            copy = os.path.join(work, "m%02d" % i)
            shutil.copytree(ROOT, copy, ignore=shutil.ignore_patterns("build"))
            target = os.path.join(copy, path)
            text = open(target, encoding="utf-8").read()
            if text.count(old) != 1:
                print("오류  %s: 바꿀 곳을 찾지 못했다 (%s)" % (path, what))
                missed += 1
                continue
            open(target, "w", encoding="utf-8").write(text.replace(old, new))
            result = subprocess.run(["make", "-s", "test"], cwd=copy, capture_output=True, text=True)
            output = result.stdout + result.stderr
            if "error:" in output:
                # compile이 안 되는 변이는 test가 잡은 것이 아니다
                print("오류  compile되지 않는 변이다 (%s)" % what)
                missed += 1
                continue
            caught = result.returncode != 0
            if why_equivalent is not None:
                if caught:
                    print("오류  동등하다고 적은 변이를 test가 잡았다 (%s)" % what)
                    missed += 1
                else:
                    print("동등  %s: %s" % (what, why_equivalent))
                continue
            if not caught:
                missed += 1
            print("%s  %s" % ("잡음" if caught else "놓침", what))
    finally:
        shutil.rmtree(work, ignore_errors=True)
    print("결함 %d개 가운데 %d개를 test가 잡았다. 동등한 변이 %d개는 세지 않았다"
          % (count, count - missed, len(EQUIVALENT)))
    return 1 if missed else 0


if __name__ == "__main__":
    sys.exit(main())
