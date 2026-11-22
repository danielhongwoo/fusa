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
     "if (st->excess_cycles > EXCESS_LATCH_CYCLES) {", "기능의 고장을 알리지 않는다"),
    ("src/monitor/monitor.c", "reaction_raise(reaction, REACTION_CUT);",
     "reaction_raise(reaction, REACTION_ZERO);", "기능의 고장에 구동 허용을 끊지 않고 토크 0으로만 간다"),
    ("src/monitor/monitor.c", "+= TORQUE_TOLERANCE;", "+= (4 * TORQUE_TOLERANCE);",
     "허용 오차를 4배로 한다"),
    ("src/monitor/monitor.c", "+= TORQUE_TOLERANCE;", "+= 0;", "허용 오차를 0으로 한다"),
    ("src/monitor/monitor.c", "allowed = (allowed * ALLOWED_REVERSE_PCT) / 100;", "",
     "후진의 허용 토크를 전진과 같게 한다"),
    ("src/monitor/monitor.c", "lo = -allowed;", "lo = -allowed; hi = allowed;",
     "후진 기어에서 전진 토크를 허용한다"),
    ("src/monitor/monitor.c",
     "    if (reaction_torque_cap(reaction_state(reaction)) == 0) {\n        out = 0;\n    }\n", "",
     "토크 0이나 구동 허용 차단 상태에서도 토크를 보낸다"),
    ("src/monitor/monitor.c", "    return (allowed < cap) ? allowed : cap;", "    return (allowed < cap) ? allowed : allowed;",
     "상태가 정한 상한을 허용 토크에 걸지 않는다"),
    ("src/monitor/monitor.c", "    a = monitor_apply_cap(a, reaction_state(reaction));\n", "",
     "상태가 정한 상한을 걸지 않는다 (부르지 않는다)"),
    ("src/reaction/reaction.c", "    } else if (wanted > now) {\n        r->state = wanted;",
     "    } else if (wanted != now) {\n        r->state = wanted;", "상태가 덜 안전한 쪽으로 돌아갈 수 있다"),
    ("src/reaction/reaction.c", "    } else if (wanted > now) {", "    } else if (wanted > (now + 1)) {",
     "한 단계 위의 사건을 무시한다"),
    ("src/reaction/reaction.c",
     "    if ((r->state != REACTION_NORMAL) && (r->state != REACTION_LIMP) && (r->state != REACTION_ZERO)) {\n        return REACTION_CUT;\n    }\n",
     "", "알 수 없는 상태 값을 그대로 돌려준다"),
    ("src/reaction/reaction.c", "    if (state == REACTION_LIMP) {\n        return LIMP_TORQUE_CAP;\n    }\n    return 0;",
     "    if (state == REACTION_LIMP) {\n        return LIMP_TORQUE_CAP;\n    }\n    return TORQUE_MAX;",
     "토크 0과 구동 허용 차단 상태의 상한을 최대 토크로 한다"),
    ("src/reaction/reaction.c", "return (state == REACTION_NORMAL) || (state == REACTION_LIMP) || (state == REACTION_ZERO);",
     "return (state != REACTION_CUT);", "알 수 없는 상태에서 구동을 허용한다"),
    ("src/reaction/reaction.c", "    if (state == REACTION_LIMP) {\n        return WARNING_AMBER;\n    }\n    return WARNING_RED;",
     "    if (state == REACTION_LIMP) {\n        return WARNING_AMBER;\n    }\n    return WARNING_AMBER;",
     "토크 0과 구동 허용 차단에서 경고가 아니라 주의를 요청한다"),
    ("src/monitor/monitor.c", "    a = monitor_limit_rise(a, st->last_out, gear);\n",
     "", "허용 토크가 오르는 속도를 제한하지 않는다 (감시를 부르지 않는다)"),
    ("src/vcu/vcu.c", "vcu->pedal_safe, vcu->brake, vcu->in.gear,\n", "vcu->pedal_safe, false, vcu->in.gear,\n",
     "감시에 브레이크를 넘기지 않는다"),
    ("src/vcu/vcu.c", "vcu->pedal_safe, vcu->brake, vcu->in.gear,\n", "vcu->pedal_safe, vcu->brake, GEAR_D,\n",
     "감시에 기어를 넘기지 않고 D로 둔다"),
    ("src/vcu/vcu.c", "vcu->pedal_safe, vcu->brake, vcu->in.gear,\n", "PEDAL_FULL, vcu->brake, vcu->in.gear,\n",
     "감시에 안전한 페달 값 대신 끝까지 밟은 값을 넘긴다"),
    ("src/monitor/monitor.c", "return (allowed < limit) ? allowed : limit;", "return (allowed < limit) ? allowed : allowed;",
     "허용 토크가 오르는 속도를 제한하지 않는다"),
    ("src/monitor/monitor.c", "return (allowed < limit) ? allowed : limit;", "return (allowed < limit) ? limit : limit;",
     "페달에서 나온 상한을 버리고 오르는 속도의 제한만 쓴다"),
    ("src/monitor/monitor.c", "        if (last_out > 0) {\n", "        if (last_out != 0) {\n",
     "전진에서 지난 출력의 방향을 보지 않는다"),
    ("src/monitor/monitor.c", "        if (last_out < 0) {\n            from = (last_out < -TORQUE_MAX) ? TORQUE_MAX : -last_out;",
     "        if (last_out != 0) {\n            from = (last_out < 0) ? -last_out : last_out;",
     "후진에서 지난 출력의 방향을 보지 않고 크기만 쓴다"),
    ("src/monitor/monitor.c", "    st->last_out = out;\n    return out;", "    return out;",
     "보낸 토크를 기억하지 않는다"),
    ("src/monitor/monitor.c",
     "    if (reaction_torque_cap(reaction_state(reaction)) == 0) {\n        out = 0;\n    }\n    st->last_out = out;",
     "    st->last_out = out;\n    if (reaction_torque_cap(reaction_state(reaction)) == 0) {\n        out = 0;\n    }",
     "구동 허용 차단이 된 주기에 보내지 않은 토크를 기억한다"),
    ("src/monitor/monitor.c", "    } else if (gear == GEAR_R) {\n        if (last_out < 0) {",
     "    } else if (gear != GEAR_D) {\n        if (last_out < 0) {",
     "P와 N에서도 지난 출력에서 센다"),
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
    ("src/input/pedal_check.c", "if (window_bad_count(st) > PEDAL_WINDOW_MAX_BAD) {\n        st->fault = true;",
     "if (window_bad_count(st) > PEDAL_WINDOW_MAX_BAD) {\n        st->fault = st->fault;",
     "간헐 고장을 판정하지 않는다"),
    ("src/input/pedal_check.c", "if (window_bad_count(st) > PEDAL_WINDOW_MAX_BAD) {",
     "if (window_bad_count(st) >= PEDAL_WINDOW_MAX_BAD) {", "실패 10번에서 판정한다 (넘을 때가 아니라)"),
    ("src/input/pedal_check.c", "    st->window[st->window_pos] = bad;\n",
     "    if (bad) {\n        st->window[st->window_pos] = true;\n    }\n",
     "오래된 실패를 기록에서 지우지 않는다"),
    ("src/input/pedal_check.c", "    st->window_pos++;\n", "", "기록의 자리를 옮기지 않는다"),
    ("src/input/pedal_check.c", "    for (uint8_t i = 0u; i < PEDAL_WINDOW_CYCLES; i++) {\n        if (st->window[i]) {",
     "    for (uint8_t i = 0u; i < (PEDAL_WINDOW_CYCLES - 1u); i++) {\n        if (st->window[i]) {",
     "기록의 마지막 자리를 세지 않는다"),
    ("src/input/pedal_check.c", "    st->window[st->window_pos] = bad;\n",
     "    st->window[st->window_pos] = bad && (st->window_pos < 99u);\n",
     "기록의 마지막 자리에는 실패를 적지 않는다"),
    ("src/input/pedal_check.c", "    st->window[st->window_pos] = bad;\n",
     "    st->window[st->window_pos] = (diff > PEDAL_MISMATCH_MAX);\n",
     "기록에 불일치만 적고 범위의 실패는 적지 않는다"),
    ("src/input/pedal_check.c", "    if (st->window_pos >= PEDAL_WINDOW_CYCLES) {\n        st->window_pos = 0u;",
     "    if (st->window_pos > PEDAL_WINDOW_CYCLES) {\n        st->window_pos = 0u;",
     "적을 자리의 범위 검사가 하나 어긋난다 (배열의 바로 뒤에 쓴다)"),
    ("src/input/pedal_check.c", "    if (st->window_pos >= PEDAL_WINDOW_CYCLES) {\n        st->window_pos = 0u;\n    }\n",
     "    st->window_pos = (uint8_t)(st->window_pos % PEDAL_WINDOW_CYCLES);\n",
     "범위를 벗어난 자리를 처음으로 돌리지 않고 나머지로 접는다"),
    ("src/vcu/vcu.c", "vcu->enable = vcu->pedal_check.ready && reaction_enable(state);",
     "vcu->enable = vcu->pedal_check.ready;", "구동 허용 차단 상태에서도 구동 허용 신호를 끊지 않는다"),
    ("src/vcu/vcu.c", "vcu->enable = vcu->pedal_check.ready && reaction_enable(state);",
     "vcu->enable = reaction_enable(state);", "켠 직후에 구동을 허용한다"),
    ("src/vcu/vcu.c", "    hal_enable_write(false);\n}", "}",
     "켤 때 구동 허용 신호를 끊지 않는다"),
    ("src/vcu/vcu.c", "    hal_enable_write(vcu->enable);\n    hal_can_tx_torque(vcu->torque_out);\n",
     "    hal_can_tx_torque(vcu->torque_out);\n    hal_enable_write(vcu->enable);\n",
     "토크 요구를 구동 허용 신호보다 먼저 쓴다"),
    ("src/vcu/vcu.c", "    if (vcu->pedal_check.fault) {\n        reaction_raise(&vcu->reaction, REACTION_ZERO);\n    }\n",
     "", "페달 고장을 상태 기계에 알리지 않는다 (경고가 나가지 않는다)"),
    ("src/vcu/vcu.c", "    if (vcu->pedal_check.fault) {\n        reaction_raise(&vcu->reaction, REACTION_ZERO);",
     "    if (vcu->pedal_check.fault) {\n        reaction_raise(&vcu->reaction, REACTION_CUT);",
     "페달 고장에 구동 허용 신호까지 끊는다"),
    ("src/vcu/vcu.c", "    if (vcu->brake_check.fault) {\n        reaction_raise(&vcu->reaction, REACTION_ZERO);",
     "    if (vcu->brake_check.fault) {\n        reaction_raise(&vcu->reaction, REACTION_CUT);",
     "브레이크 신호의 고장에 구동 허용 신호까지 끊는다"),
    ("src/vcu/vcu.c", "    reaction_state_t state = reaction_state(&vcu->reaction);\n\n    /* SWR-10",
     "    reaction_state_t state = REACTION_NORMAL;\n\n    /* SWR-10",
     "구동 허용과 경고를 상태에서 가져오지 않는다"),
    ("src/input/brake_check.c", "    if (in->brake1 || in->brake2) {", "    if (in->brake1) {",
     "브레이크 접점 2를 보지 않는다"),
    ("src/input/brake_check.c", "    if (in->brake1 || in->brake2) {", "    if (in->brake2) {",
     "브레이크 접점 1을 보지 않는다"),
    ("src/input/brake_check.c", "    if (in->brake1 != in->brake2) {", "    if (in->brake1 && !in->brake2) {",
     "접점 2만 밟음인 어긋남을 세지 않는다"),
    ("src/input/brake_check.c", "    if (st->fault) {\n        st->pressed = true;\n    }\n", "",
     "브레이크 신호의 고장 뒤에도 접점을 따른다"),
    ("src/input/brake_check.c", "        st->release_cycles = 0u;\n        st->pressed = true;", "        st->pressed = true;",
     "놓음을 세는 중에 밟음이 와도 다시 세지 않는다"),
    ("src/input/brake_check.c", "    } else {\n        st->mismatch_cycles = 0u;\n    }", "    }",
     "어긋남을 이어서가 아니라 모두 합쳐 센다"),
    ("src/input/brake_check.c", "    st->pressed = true;\n    st->fault = false;", "    st->pressed = false;\n    st->fault = false;",
     "켠 직후에 브레이크를 놓은 것으로 본다"),
    ("src/vcu/vcu.c", "    if (vcu->brake_check.fault) {\n        reaction_raise(&vcu->reaction, REACTION_ZERO);\n    }\n", "",
     "브레이크 신호의 고장을 상태 기계에 알리지 않는다"),
    ("src/vcu/vcu.c", "vcu->pedal_safe, vcu->brake, vcu->in.gear,\n", "vcu->pedal_safe, vcu->in.brake1, vcu->in.gear,\n",
     "감시에 판정한 브레이크가 아니라 접점 1을 넘긴다"),
    ("src/vcu/vcu.c", "app_step(&vcu->app, vcu->pedal_safe, vcu->brake, vcu->in.gear);",
     "app_step(&vcu->app, vcu->pedal_safe, vcu->in.brake1, vcu->in.gear);",
     "기능에 판정한 브레이크가 아니라 접점 1을 넘긴다"),
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
                  "src/reaction/reaction.h", "src/common/types.h", "src/app/app.c"]
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
