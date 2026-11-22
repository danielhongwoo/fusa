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
import signal
import subprocess
import sys
import tempfile

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
TEST_TIMEOUT_S = 300  # 반복이 끝나지 않게 되는 변이가 도구를 멈추지 않게 한다

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
    ("src/vcu/vcu.c", "vcu->torque_req,\n                                           vcu->pedal_safe, vcu->brake, vcu->gear,\n", "vcu->torque_req,\n                                           vcu->pedal_safe, false, vcu->gear,\n",
     "감시에 브레이크를 넘기지 않는다"),
    ("src/vcu/vcu.c", "vcu->torque_req,\n                                           vcu->pedal_safe, vcu->brake, vcu->gear,\n", "vcu->torque_req,\n                                           vcu->pedal_safe, vcu->brake, GEAR_D,\n",
     "감시에 기어를 넘기지 않고 D로 둔다"),
    ("src/vcu/vcu.c", "vcu->torque_req,\n                                           vcu->pedal_safe, vcu->brake, vcu->gear,\n", "vcu->torque_req,\n                                           PEDAL_FULL, vcu->brake, vcu->gear,\n",
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
    ("src/vcu/vcu.c",
     "    hal_enable_write(vcu->enable);\n    /* SWR-17: 싣는 값은 출력 단계가 돌려준 토크다. 깎기 전의 요구가 아니다 */\n"
     "    frame_t frame;\n    e2e_protect(&vcu->torque_tx, E2E_ID_TORQUE, vcu->torque_out, &frame);\n"
     "    hal_can_tx_torque_frame(&frame);\n",
     "    frame_t frame;\n    e2e_protect(&vcu->torque_tx, E2E_ID_TORQUE, vcu->torque_out, &frame);\n"
     "    hal_can_tx_torque_frame(&frame);\n    hal_enable_write(vcu->enable);\n",
     "토크 요구를 구동 허용 신호보다 먼저 쓴다"),
    ("src/vcu/vcu.c", "e2e_protect(&vcu->torque_tx, E2E_ID_TORQUE, vcu->torque_out, &frame);",
     "e2e_protect(&vcu->torque_tx, E2E_ID_TORQUE, vcu->torque_req, &frame);",
     "메시지에 깎기 전의 토크 요구를 싣는다"),
    ("src/vcu/vcu.c", "e2e_protect(&vcu->torque_tx, E2E_ID_TORQUE, vcu->torque_out, &frame);",
     "e2e_protect(&vcu->torque_tx, E2E_ID_SPEED, vcu->torque_out, &frame);",
     "토크 요구에 다른 종류의 data ID를 붙인다"),
    ("src/vcu/vcu.c", "e2e_check(&vcu->speed_rx, E2E_ID_SPEED,", "e2e_check(&vcu->speed_rx, E2E_ID_INVERTER,",
     "차량 속도를 다른 종류의 data ID로 검사한다"),
    ("src/vcu/vcu.c", "e2e_check(&vcu->inverter_rx, E2E_ID_INVERTER,", "e2e_check(&vcu->inverter_rx, E2E_ID_SPEED,",
     "inverter의 상태를 다른 종류의 data ID로 검사한다"),
    ("src/vcu/vcu.c", "vcu->speed = vcu->speed_valid ? rx.frame.value : 0;", "vcu->speed = rx.frame.value;",
     "무효인 차량 속도의 값을 그대로 쓴다"),
    ("src/flow/flow.c", "    answer = ((answer * 31u) + f->count) & 0xFFu;\n", "", "답에 표시의 수를 넣지 않는다"),
    ("src/vcu/vcu.c", "inverter_check_record(&vcu->inverter_check, vcu->torque_out);",
     "inverter_check_record(&vcu->inverter_check, vcu->torque_req);",
     "inverter의 검사에 보낸 토크가 아니라 깎기 전의 요구를 기록한다"),
    ("src/vcu/vcu.c", "diag.inverter_out_cycles = vcu->inverter_check.out_cycles;",
     "diag.inverter_out_cycles = vcu->inverter_check.invalid_cycles;", "진단 메시지에 다른 횟수를 싣는다"),
    ("src/com/e2e.c", "    st->synced = false;\n    st->ok = false;\n}", "    st->synced = false;\n    st->ok = true;\n}",
     "받는 쪽의 처음 판정을 유효로 둔다"),
    ("src/input/pedal_check.c", "        bad = range2;\n", "        bad = range2 && range1;\n",
     "채널 1을 뺀 뒤 남은 채널의 실패를 뺀 채널도 벗어났을 때만 본다"),
    ("src/input/pedal_check.c", "        bad = range1;\n", "        bad = range1 && range2;\n",
     "채널 2를 뺀 뒤 남은 채널의 실패를 뺀 채널도 벗어났을 때만 본다"),
    ("src/input/pedal_check.c", "        if (range1 && !range2) {", "        if (range1 && !range2 && (p2 > 0)) {",
     "다른 채널이 페달을 놓은 값이면 채널 1의 단선을 한 채널의 고장으로 보지 않는다"),
    ("src/input/pedal_check.c", "        if (range2 && !range1) {", "        if (range2 && !range1 && (p1 > 0)) {",
     "다른 채널이 페달을 놓은 값이면 채널 2의 단선을 한 채널의 고장으로 보지 않는다"),
    ("src/input/pedal_check.c", "        bad = range2;\n", "        bad = range2 || range1;\n", "뺀 채널 1의 범위를 계속 본다"),
    ("src/input/pedal_check.c", "        bad = range1;\n", "        bad = range1 || range2;\n", "뺀 채널 2의 범위를 계속 본다"),
    ("src/input/pedal_check.c", "        if (range1 && !range2) {", "        if (range1) {",
     "채널 2도 범위를 벗어났는지를 보지 않는다"),
    ("src/input/pedal_check.c", "        if (range2 && !range1) {", "        if (range2) {",
     "채널 1도 범위를 벗어났는지를 보지 않는다"),
    ("src/input/pedal_check.c", "        if (st->bad_cycles == 0u) {\n            st->suspect = single;",
     "        if (st->bad_cycles == 0u) {\n            st->suspect = PEDAL_CH_NONE;",
     "이어진 실패의 첫 주기가 어느 채널이었는지를 기억하지 않는다"),
    ("src/input/pedal_check.c", "        } else if (st->suspect != single) {\n            st->suspect = PEDAL_CH_NONE;",
     "        } else if (st->suspect != single) {\n            st->suspect = single;",
     "실패의 모양이 주기마다 달라도 마지막 주기만 본다"),
    ("src/input/pedal_check.c", "                st->excluded = st->suspect;\n                st->bad_cycles = 0u;",
     "                st->bad_cycles = 0u;", "틀린 채널을 검사에서 빼지 않는다"),
    ("src/input/pedal_check.c", "                st->excluded = st->suspect;\n                st->bad_cycles = 0u;",
     "                st->excluded = st->suspect;", "채널을 뺀 뒤에 이어진 횟수를 지우지 않는다"),
    ("src/input/pedal_check.c", "    if (st->excluded == PEDAL_CH1) {\n        return p2;\n    }\n", "",
     "채널 1을 뺀 뒤에도 두 채널 가운데 작은 값을 낸다"),
    ("src/input/pedal_check.c", "    if (st->excluded == PEDAL_CH2) {\n        return p1;\n    }\n", "",
     "채널 2를 뺀 뒤에도 두 채널 가운데 작은 값을 낸다"),
    ("src/vcu/vcu.c", "    if (vcu->pedal_check.excluded != PEDAL_CH_NONE) {\n        reaction_raise(&vcu->reaction, REACTION_LIMP);\n    }\n", "",
     "채널을 빼도 줄여 감의 사건을 알리지 않는다"),
    ("src/vcu/vcu.c", "                               reaction_app_limit(reaction_state(&vcu->reaction)));",
     "                               TORQUE_MAX);", "줄여 감 상태에서도 기능에 상한을 주지 않는다"),
    ("src/reaction/reaction.c", "return (state == REACTION_LIMP) ? LIMP_APP_TORQUE : TORQUE_MAX;",
     "return (state == REACTION_LIMP) ? TORQUE_MAX : TORQUE_MAX;", "줄여 감 상태의 기능의 상한을 최대 토크로 한다"),
    ("src/app/app.c", "    if (target > limit) {\n        target = limit;\n    }\n", "", "기능이 전진 쪽의 상한을 지키지 않는다"),
    ("src/app/app.c", "    if (target < -limit) {\n        target = -limit;\n    }\n", "", "기능이 후진 쪽의 상한을 지키지 않는다"),
    ("src/vcu/vcu.c", "    if (hal_enable_readback() != vcu->enable) {\n        reaction_raise(&vcu->reaction, REACTION_CUT);\n    }\n", "",
     "구동 허용 신호를 되읽지 않는다"),
    ("src/vcu/vcu.c", "    if (hal_enable_readback() != vcu->enable) {\n        reaction_raise(&vcu->reaction, REACTION_CUT);",
     "    if (hal_enable_readback() != vcu->enable) {\n        reaction_raise(&vcu->reaction, REACTION_ZERO);",
     "되읽은 값이 어긋나도 구동 허용 차단으로 가지 않고 토크 0으로만 간다"),
    ("src/vcu/vcu.c", "    if (hal_enable_readback() != vcu->enable) {", "    if (hal_enable_readback() && !vcu->enable) {",
     "허용이라고 썼는데 끊김으로 읽히는 쪽을 보지 않는다"),
    ("src/vcu/vcu.c", "    if (hal_enable_readback() != vcu->enable) {", "    if (!hal_enable_readback() && vcu->enable) {",
     "끊으라고 썼는데 허용으로 읽히는 쪽을 보지 않는다"),
    ("src/flow/flow.c", "    if (f->count < FLOW_TASK_COUNT) {\n        f->marks[f->count] = mark;",
     "    if (f->count <= FLOW_TASK_COUNT) {\n        f->marks[f->count] = mark;",
     "표시를 적을 자리의 범위 검사가 하나 어긋난다 (배열의 바로 뒤에 쓴다)"),
    ("src/flow/flow.c", "    } else {\n        f->count = (uint8_t)(FLOW_TASK_COUNT + 1u);\n    }", "    }",
     "표시가 넘친 것을 남기지 않는다"),
    ("src/flow/flow.c", "return (f->count == FLOW_TASK_COUNT) && (f->marks[0] == FLOW_MARK_INPUT)",
     "return (f->marks[0] == FLOW_MARK_INPUT)", "표시의 수를 보지 않는다"),
    ("src/flow/flow.c", "return (f->count == FLOW_TASK_COUNT) && (f->marks[0] == FLOW_MARK_INPUT)",
     "return (f->count == FLOW_TASK_COUNT)", "첫째 표시를 보지 않는다"),
    ("src/flow/flow.c", "           && (f->marks[1] == FLOW_MARK_APP) && (f->marks[2] == FLOW_MARK_MONITOR);",
     "           && (f->marks[2] == FLOW_MARK_MONITOR);", "둘째 표시를 보지 않는다"),
    ("src/flow/flow.c", "           && (f->marks[1] == FLOW_MARK_APP) && (f->marks[2] == FLOW_MARK_MONITOR);",
     "           && (f->marks[1] == FLOW_MARK_APP);", "셋째 표시를 보지 않는다"),
    ("src/flow/flow.c", "    uint32_t answer = f->question;", "    uint32_t answer = (uint32_t)f->question & 0u;",
     "답에 질문의 번호를 넣지 않는다"),
    ("src/flow/flow.c", "answer = ((answer * 31u) + f->marks[i]) & 0xFFu;", "answer = ((answer * 31u) + (uint32_t)i + 1u) & 0xFFu;",
     "답을 남은 표시가 아니라 정해진 값에서 만든다"),
    ("src/flow/flow.c", "    if ((out > limit) || (out < -limit)) {\n        answer ^= 0xFFu;\n    }\n", "    (void)limit;\n    (void)out;\n",
     "보낸 토크가 허용 토크를 넘어도 답을 바꾸지 않는다"),
    ("src/flow/flow.c", "    if ((out > limit) || (out < -limit)) {", "    if (out > limit) {",
     "후진 쪽으로 넘는 토크를 보지 않는다"),
    ("src/flow/flow.c", "torque_t limit = (allowed < 0) ? 0 : allowed;", "torque_t limit = allowed;",
     "음수인 허용 토크를 0으로 자르지 않는다"),
    ("src/flow/flow.c", "    f->count = 0u;\n    f->question = (uint8_t)", "    f->question = (uint8_t)", "주기를 닫을 때 표시의 수를 지우지 않는다"),
    ("src/flow/flow.c", "    for (uint8_t i = 0u; i < FLOW_TASK_COUNT; i++) {\n        f->marks[i] = 0u;\n    }\n    f->count = 0u;\n    f->question = (uint8_t)",
     "    f->count = 0u;\n    f->question = (uint8_t)", "주기를 닫을 때 표시의 값을 지우지 않는다"),
    ("src/flow/flow.c", "    f->count = 0u;\n    f->question = (uint8_t)((f->question + 1u) & 0xFFu);\n", "    f->count = 0u;\n",
     "질문의 번호를 올리지 않는다"),
    ("src/vcu/vcu.c", "    flow_mark(&vcu->flow, FLOW_MARK_INPUT);\n", "", "입력의 task가 표시를 남기지 않는다"),
    ("src/vcu/vcu.c", "    flow_mark(&vcu->flow, FLOW_MARK_APP);\n", "    flow_mark(&vcu->flow, FLOW_MARK_APP);\n    flow_mark(&vcu->flow, FLOW_MARK_APP);\n",
     "기능의 task가 표시를 두 번 남긴다"),
    ("src/vcu/vcu.c", "hal_watchdog_write(flow_answer(&vcu->flow, vcu->torque_allowed, vcu->torque_out));",
     "hal_watchdog_write(flow_answer(&vcu->flow, vcu->torque_allowed, 0));",
     "답을 만들 때 보낸 토크 대신 0을 넘긴다"),
    ("src/vcu/vcu.c", "hal_watchdog_write(flow_answer(&vcu->flow, vcu->torque_allowed, vcu->torque_out));",
     "hal_watchdog_write(flow_answer(&vcu->flow, TORQUE_MAX, vcu->torque_out));",
     "답을 만들 때 허용 토크 대신 최대 토크를 넘긴다"),
    ("src/vcu/vcu.c", "    flow_next(&vcu->flow);\n", "", "주기를 닫지 않는다 (표시가 쌓인다)"),
    ("src/monitor/inverter_check.c", "        if (st->invalid_cycles < INVERTER_INVALID_CYCLES) {\n            st->invalid_cycles++;\n        }",
     "        st->invalid_cycles++;", "무효인 횟수를 한계에서 멈추지 않는다 (넘쳐서 0으로 돌아간다)"),
    ("src/monitor/inverter_check.c", "        st->invalid_cycles = 0u;\n", "", "유효한 주기가 끼어도 무효인 횟수를 지우지 않는다"),
    ("src/monitor/inverter_check.c", "            if (v < lo) {\n                lo = v;\n            }\n", "",
     "보낸 토크가 음수여도 범위의 아래쪽을 넓히지 않는다"),
    ("src/monitor/inverter_check.c", "            if (v > hi) {\n                hi = v;\n            }\n", "",
     "보낸 토크가 커도 범위의 위쪽을 넓히지 않는다"),
    ("src/monitor/inverter_check.c",
     "if ((reported < (lo - INVERTER_TORQUE_MARGIN)) || (reported > (hi + INVERTER_TORQUE_MARGIN))) {",
     "if (reported > (hi + INVERTER_TORQUE_MARGIN)) {", "범위의 아래쪽을 보지 않는다"),
    ("src/monitor/inverter_check.c",
     "if ((reported < (lo - INVERTER_TORQUE_MARGIN)) || (reported > (hi + INVERTER_TORQUE_MARGIN))) {",
     "if (reported < (lo - INVERTER_TORQUE_MARGIN)) {", "범위의 위쪽을 보지 않는다"),
    ("src/monitor/inverter_check.c", "            if (st->out_cycles < INVERTER_OUT_CYCLES) {\n                st->out_cycles++;\n            }",
     "            st->out_cycles++;", "벗어난 횟수를 한계에서 멈추지 않는다 (넘쳐서 0으로 돌아간다)"),
    ("src/monitor/inverter_check.c", "        } else {\n            st->out_cycles = 0u;\n        }", "        }",
     "범위 안으로 돌아와도 벗어난 횟수를 지우지 않는다"),
    ("src/monitor/inverter_check.c",
     "return (st->out_cycles >= INVERTER_OUT_CYCLES) || (st->invalid_cycles >= INVERTER_INVALID_CYCLES);",
     "return (st->out_cycles >= INVERTER_OUT_CYCLES);", "상태가 계속 무효여도 사건을 알리지 않는다"),
    ("src/monitor/inverter_check.c",
     "return (st->out_cycles >= INVERTER_OUT_CYCLES) || (st->invalid_cycles >= INVERTER_INVALID_CYCLES);",
     "return (st->invalid_cycles >= INVERTER_INVALID_CYCLES);", "범위를 계속 벗어나도 사건을 알리지 않는다"),
    ("src/monitor/inverter_check.c", "    if (r > TORQUE_MAX) {\n        r = TORQUE_MAX;\n    }\n", "",
     "기록의 값을 위쪽으로 자르지 않는다 (값이 틀리면 계산이 넘친다)"),
    ("src/monitor/inverter_check.c", "    if (r < -TORQUE_MAX) {\n        r = -TORQUE_MAX;\n    }\n", "",
     "기록의 값을 아래쪽으로 자르지 않는다"),
    ("src/monitor/inverter_check.c", "    if (st->pos >= INVERTER_HISTORY_CYCLES) {\n        st->pos = 0u;",
     "    if (st->pos > INVERTER_HISTORY_CYCLES) {\n        st->pos = 0u;",
     "기록할 자리의 범위 검사가 하나 어긋난다 (배열의 바로 뒤에 쓴다)"),
    ("src/monitor/inverter_check.c", "    st->sent[st->pos] = sent;\n    st->pos++;", "    st->sent[st->pos] = 0;\n    st->pos++;\n    (void)sent;",
     "보낸 토크 대신 0을 기록한다"),
    ("src/monitor/inverter_check.c", "    st->sent[st->pos] = sent;\n    st->pos++;", "    st->sent[st->pos] = sent;",
     "기록할 자리를 옮기지 않는다 (늘 같은 자리에 쓴다)"),
    ("src/vcu/vcu.c",
     "    if (inverter_check_step(&vcu->inverter_check, vcu->inverter_valid, vcu->inverter_torque)) {\n        reaction_raise(&vcu->reaction, REACTION_CUT);",
     "    if (inverter_check_step(&vcu->inverter_check, vcu->inverter_valid, vcu->inverter_torque)) {\n        reaction_raise(&vcu->reaction, REACTION_ZERO);",
     "inverter의 검사가 사건을 알려도 구동 허용을 끊지 않고 토크 0으로만 간다"),
    ("src/vcu/vcu.c", "inverter_check_step(&vcu->inverter_check, vcu->inverter_valid, vcu->inverter_torque)",
     "inverter_check_step(&vcu->inverter_check, true, vcu->inverter_torque)",
     "inverter의 검사에 상태가 유효한지를 넘기지 않는다"),
    ("src/vcu/vcu.c", "inverter_check_step(&vcu->inverter_check, vcu->inverter_valid, vcu->inverter_torque)",
     "inverter_check_step(&vcu->inverter_check, vcu->inverter_valid, vcu->torque_out)",
     "inverter가 알린 토크 대신 VCU가 보낸 토크를 견준다"),
    ("src/vcu/vcu.c", "    inverter_check_record(&vcu->inverter_check, vcu->torque_out);\n", "",
     "보낸 토크를 inverter의 검사에 기록하지 않는다"),
    ("src/vcu/vcu.c", "vcu->inverter_torque = vcu->inverter_valid ? rx.frame.value : 0;", "vcu->inverter_torque = 0;",
     "inverter가 알린 토크를 쓰지 않는다"),
    ("src/input/gear_check.c", "    st->direction = GEAR_N; /* 받아들인 방향이 아직 없다 */", "    st->direction = GEAR_D;",
     "켠 직후에 D를 받아들인 것으로 둔다"),
    ("src/input/gear_check.c", "if (speed_valid && (speed >= 0) && (speed < GEAR_CHANGE_SPEED_MAX)) {",
     "if ((speed_valid || !speed_valid) && (speed >= 0) && (speed < GEAR_CHANGE_SPEED_MAX)) {",
     "차량 속도가 유효한지를 보지 않는다"),
    ("src/input/gear_check.c", "if (speed_valid && (speed >= 0) && (speed < GEAR_CHANGE_SPEED_MAX)) {",
     "if (speed_valid && (speed < GEAR_CHANGE_SPEED_MAX)) {", "차량 속도가 음수인 것을 받아들인다"),
    ("src/input/gear_check.c", "if (speed_valid && (speed >= 0) && (speed < GEAR_CHANGE_SPEED_MAX)) {",
     "if (speed_valid && (speed >= 0)) {", "차량 속도가 높아도 방향의 바뀜을 받아들인다"),
    ("src/input/gear_check.c", "        if (selected != st->direction) {",
     "        if ((selected != st->direction) && (st->direction != GEAR_N)) {",
     "받아들인 방향이 없을 때에는 속도를 보지 않는다"),
    ("src/input/gear_check.c", "                st->direction = selected;\n", "", "받아들인 방향을 기억하지 않는다"),
    ("src/input/gear_check.c", "                accepted = GEAR_N;\n                rejected = true;",
     "                rejected = true;", "받아들이지 못한 방향을 그대로 낸다"),
    ("src/input/gear_check.c", "                accepted = GEAR_N;\n                rejected = true;",
     "                accepted = GEAR_N;", "받아들이지 못한 주기를 세지 않는다"),
    ("src/input/gear_check.c", "    } else if (selected != GEAR_P) {\n        accepted = GEAR_N; /* N이거나 알 수 없는 값 */\n",
     "    } else if (selected != GEAR_P) {\n", "알 수 없는 기어 값을 그대로 낸다"),
    ("src/input/gear_check.c", "        if (st->reject_cycles < GEAR_REJECT_WARN_CYCLES) {\n            st->reject_cycles++;\n        }",
     "        st->reject_cycles++;", "받아들이지 못한 횟수를 한계에서 멈추지 않는다 (넘쳐서 0으로 돌아간다)"),
    ("src/input/gear_check.c", "    } else {\n        st->reject_cycles = 0u;\n    }", "    }",
     "받아들인 뒤에도 세던 횟수를 지우지 않는다"),
    ("src/input/gear_check.c", "st->caution = (st->reject_cycles >= GEAR_REJECT_WARN_CYCLES);",
     "st->caution = (st->reject_cycles > GEAR_REJECT_WARN_CYCLES);", "주의를 요청하지 않는다"),
    ("src/vcu/vcu.c", "gear_check_step(&vcu->gear_check, vcu->in.gear, vcu->speed_valid, vcu->speed);",
     "gear_check_step(&vcu->gear_check, vcu->in.gear, true, vcu->speed);",
     "방향의 판정에 속도가 유효한지를 넘기지 않는다"),
    ("src/vcu/vcu.c", "gear_check_step(&vcu->gear_check, vcu->in.gear, vcu->speed_valid, vcu->speed);",
     "gear_check_step(&vcu->gear_check, vcu->in.gear, vcu->speed_valid, 0);",
     "방향의 판정에 속도 대신 0을 넘긴다"),
    ("src/vcu/vcu.c", "app_step(&vcu->app, vcu->pedal_safe, vcu->brake, vcu->gear,\n",
     "app_step(&vcu->app, vcu->pedal_safe, vcu->brake, vcu->in.gear,\n",
     "기능이 받아들인 기어가 아니라 운전자가 고른 기어를 쓴다"),
    ("src/vcu/vcu.c", "vcu->torque_req,\n                                           vcu->pedal_safe, vcu->brake, vcu->gear,\n", "vcu->torque_req,\n                                           vcu->pedal_safe, vcu->brake, vcu->in.gear,\n",
     "감시가 받아들인 기어가 아니라 운전자가 고른 기어를 쓴다"),
    ("src/vcu/vcu.c", "    if ((vcu->warning == WARNING_NONE) && vcu->gear_check.caution) {\n        vcu->warning = WARNING_AMBER;\n    }\n",
     "", "방향을 받아들이지 못해도 주의를 요청하지 않는다"),
    ("src/vcu/vcu.c", "    if ((vcu->warning == WARNING_NONE) && vcu->gear_check.caution) {",
     "    if (vcu->gear_check.caution) {", "주의가 고장의 경고를 덮는다"),
    ("src/com/e2e.c", "st->counter = (uint8_t)((counter + 1u) & E2E_COUNTER_MASK);", "st->counter = counter;",
     "보내는 counter를 올리지 않는다"),
    ("src/com/e2e.c", "frame->crc = frame_crc(data_id, counter, value);", "frame->crc = frame_crc((uint8_t)(data_id & 0u), counter, value);",
     "보내는 CRC에 data ID를 넣지 않는다"),
    ("src/com/e2e.c", "    bytes[1] = counter;", "    bytes[1] = (uint8_t)(counter & 0u);", "CRC에 counter를 넣지 않는다"),
    ("src/com/e2e.c", "    bytes[5] = (uint8_t)((v >> 24u) & 0xFFu);", "    bytes[5] = 0u;",
     "CRC에 값의 가장 높은 byte를 넣지 않는다"),
    ("src/com/e2e.c", "crc = ((crc << 1u) & 0xFFu) ^ 0x1Du;", "crc = ((crc << 1u) & 0xFFu) ^ 0x1Bu;",
     "CRC의 다항식이 다르다"),
    ("src/com/e2e.c", "    uint32_t crc = 0xFFu;", "    uint32_t crc = 0x00u;", "CRC의 처음 값이 다르다"),
    ("src/com/e2e.c", "    return (uint8_t)(crc ^ 0xFFu);", "    return (uint8_t)crc;", "CRC를 끝에 뒤집지 않는다"),
    ("src/com/e2e.c", "    return (value >= 0) ? (uint32_t)value : (0xFFFFFFFFu - (uint32_t)(-(value + 1)));",
     "    return (value >= 0) ? (uint32_t)value : (uint32_t)(-(value + 1));",
     "음수인 값을 전송하는 bit로 잘못 편다"),
    ("src/com/e2e.c", "    if (!seen || (age_ms > E2E_TIMEOUT_MS)) {", "    if (!seen || (age_ms > (E2E_TIMEOUT_MS * 1000u))) {",
     "받은 뒤로 흐른 시간의 한계를 1000배로 한다"),
    ("src/com/e2e.c", "    if (!seen || (age_ms > E2E_TIMEOUT_MS)) {", "    if ((!seen && (age_ms > 0u)) || (age_ms > E2E_TIMEOUT_MS)) {",
     "받은 적이 없어도 방금 받은 것처럼 보이면 검사한다"),
    ("src/com/e2e.c", "    if (!seen || (age_ms > E2E_TIMEOUT_MS)) {\n        st->ok = false;",
     "    if (!seen || (age_ms > E2E_TIMEOUT_MS)) {", "시간이 넘은 뒤에 지난 판정을 지우지 않는다"),
    ("src/com/e2e.c", "    if (fresh) {", "    if (fresh || !fresh) {", "새 메시지가 아니어도 다시 검사한다"),
    ("src/com/e2e.c", "        if (frame->crc != frame_crc(data_id, frame->counter, frame->value)) {",
     "        if ((frame->crc != frame_crc(data_id, frame->counter, frame->value)) && (frame->counter > 200u)) {",
     "CRC를 검사하지 않는다"),
    ("src/com/e2e.c", "st->ok = !st->synced || ((step >= 1u) && (step <= E2E_MAX_STEP));",
     "st->ok = (step >= 1u) && (step <= E2E_MAX_STEP);", "처음 받은 메시지도 counter를 견준다"),
    ("src/com/e2e.c", "st->ok = !st->synced || ((step >= 1u) && (step <= E2E_MAX_STEP));",
     "st->ok = !st->synced || (step <= E2E_MAX_STEP);", "같은 counter의 되풀이를 받아들인다"),
    ("src/com/e2e.c", "st->ok = !st->synced || ((step >= 1u) && (step <= E2E_MAX_STEP));",
     "st->ok = !st->synced || (step >= 1u);", "counter가 얼마나 건너뛰어도 받아들인다"),
    ("src/com/e2e.c", "            st->last_counter = frame->counter;\n", "", "counter의 기준을 갱신하지 않는다"),
    ("src/com/e2e.c", "            st->synced = true;\n", "", "처음 받았다는 표시를 남기지 않는다"),
    ("src/com/e2e.c", "            /* 값이나 counter가 바뀌었거나, 다른 종류의 메시지다 */\n            st->ok = false;",
     "            st->ok = false;\n            st->last_counter = frame->counter;",
     "CRC가 틀린 메시지가 counter의 기준을 바꾼다"),
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
    ("src/vcu/vcu.c", "vcu->torque_req,\n                                           vcu->pedal_safe, vcu->brake, vcu->gear,\n", "vcu->torque_req,\n                                           vcu->pedal_safe, vcu->in.brake1, vcu->gear,\n",
     "감시에 판정한 브레이크가 아니라 접점 1을 넘긴다"),
    ("src/vcu/vcu.c", "app_step(&vcu->app, vcu->pedal_safe, vcu->brake, vcu->gear,\n",
     "app_step(&vcu->app, vcu->pedal_safe, vcu->in.brake1, vcu->gear,\n",
     "기능에 판정한 브레이크가 아니라 접점 1을 넘긴다"),
    ("src/input/input.c", "in->gear = GEAR_N; /* 알 수 없는 값은 N으로 본다 */",
     "in->gear = GEAR_D;", "알 수 없는 기어 값을 D로 본다"),
    # 켠 직후의 상태를 정하는 줄을 뺀 변이. 다른 test는 stack에 남은 값 덕분에 통과하기 쉽다.
    # 쓰레기 값으로 채운 뒤에 init을 부르고 필드를 값으로 보는 test (TC-023, TC-133)가 잡아야 한다
    ("src/app/app.c", "    st->prev = 0;\n}", "    (void)st;\n}", "기능의 켠 직후 상태를 정하지 않는다"),
    ("src/vcu/vcu.c", "    vcu->brake = true;\n", "", "켠 직후의 브레이크 상태 (밟음)를 정하지 않는다"),
    ("src/vcu/vcu.c", "    vcu->gear = GEAR_N;\n", "", "켠 직후의 받아들인 기어 (N)를 정하지 않는다"),
    ("src/vcu/vcu.c", "    app_init(&vcu->app);\n", "", "켤 때 기능의 init을 부르지 않는다"),
    ("src/vcu/vcu.c", "    e2e_rx_init(&vcu->inverter_rx);\n", "", "켤 때 inverter 상태 메시지의 검사의 init을 부르지 않는다"),
    ("src/vcu/vcu.c", "    reaction_init(&vcu->reaction);\n", "", "켤 때 상태 기계의 init을 부르지 않는다"),
    ("src/input/gear_check.c", "    st->direction = GEAR_N; /* 받아들인 방향이 아직 없다 */\n", "",
     "켠 직후의 받아들인 방향 (없음)을 정하지 않는다"),
    ("src/monitor/inverter_check.c", "    st->pos = 0u;\n    st->out_cycles = 0u;\n", "    st->pos = 0u;\n",
     "inverter 검사의 벗어난 횟수를 켤 때 정하지 않는다"),
    ("src/reaction/reaction.c", "    r->state = REACTION_NORMAL;\n}", "    (void)r;\n}",
     "상태 기계의 켠 직후 상태를 정하지 않는다"),
    ("src/com/e2e.c", "    st->counter = 0u;\n}", "    (void)st;\n}", "보내는 counter를 켤 때 정하지 않는다"),
    ("src/input/brake_check.c", "    st->release_cycles = 0u;\n    st->mismatch_cycles = 0u;\n",
     "    st->release_cycles = 0u;\n", "브레이크 검사의 어긋난 횟수를 켤 때 정하지 않는다"),
    ("src/input/pedal_check.c", "    st->ready = false;\n    st->fault = false;\n", "    st->fault = false;\n",
     "켠 직후에 검사를 통과했는지를 정하지 않는다"),
    ("src/monitor/monitor.c", "    st->clamp_count = 0u;\n    st->last_out = 0;\n}", "    st->clamp_count = 0u;\n}",
     "출력 단계의 지난 출력을 켤 때 정하지 않는다"),
    ("src/flow/flow.c", "    f->count = 0u;\n    f->question = 0u;\n}", "    f->count = 0u;\n}",
     "질문의 번호를 켤 때 정하지 않는다"),
    # 배열을 구조체의 끝에 둔다는 약속을 깨는 변이. 증명 도구는 구조체의 끝만 보므로, 이 약속이 깨지면
    # 한 칸 넘는 쓰기를 증명도 test도 알리지 못한다. compile할 때의 확인 (_Static_assert)이 잡아야 한다
    ("src/flow/flow.h", "    uint8_t marks[FLOW_TASK_COUNT]; /* 이 주기에 task가 남긴 표시. 남긴 순서대로다 */\n",
     "    uint8_t marks[FLOW_TASK_COUNT]; /* 이 주기에 task가 남긴 표시. 남긴 순서대로다 */\n    uint8_t spare;\n",
     "실행 확인의 구조체에서 배열 뒤에 필드를 더한다"),
    ("src/input/input.h", "    bool window[PEDAL_WINDOW_CYCLES]; /* 최근 주기들의 검사 결과. true가 실패다 */\n",
     "    bool window[PEDAL_WINDOW_CYCLES]; /* 최근 주기들의 검사 결과. true가 실패다 */\n    uint8_t spare;\n",
     "페달 검사의 구조체에서 배열 뒤에 필드를 더한다"),
    ("src/monitor/monitor.h", "    torque_t sent[INVERTER_HISTORY_CYCLES]; /* 최근 주기들에 보낸 토크 */\n",
     "    torque_t sent[INVERTER_HISTORY_CYCLES]; /* 최근 주기들에 보낸 토크 */\n    torque_t spare;\n",
     "inverter 검사의 구조체에서 배열 뒤에 필드를 더한다"),
]

# (파일, 원래 코드, 바꾼 코드, 설명, 동등한 이유)
EQUIVALENT = [
    ("src/monitor/monitor.c",
     "        if (st->excess_cycles < EXCESS_LATCH_CYCLES) {\n            st->excess_cycles++;\n        }",
     "        st->excess_cycles++;",
     "이어진 횟수를 한계에서 멈추지 않는다",
     "횟수가 한계에 닿은 주기에 고정되고, 고정은 풀리지 않는다. 그 뒤에 횟수가 넘쳐 0으로 돌아가도 "
     "출력과 진단 메시지는 같다"),
    ("src/vcu/vcu.c", "    if (ok) {\n        hal_watchdog_write(", "    if (ok || !ok) {\n        hal_watchdog_write(",
     "task의 순서가 틀려도 외부 watchdog에 답을 쓴다",
     "보호가 겹쳐 있어서 밖에서 보이는 결과가 같다. 답은 그 주기에 남은 표시와 그 수에서 만들므로 (flow_answer), "
     "task가 빠지거나 더 실행되거나 순서가 틀리면 답도 틀리게 나오고 watchdog이 끊는다. task가 남길 수 있는 표시 "
     "(1, 2, 3의 열, 일곱 개까지)와 모든 질문의 번호에서 틀린 열이 옳은 답을 내는 경우가 없다는 것을 TC-021이 "
     "모두 세어 확인한다. 그래서 닿을 수 있는 상태에서는 동등하다. 표시가 다른 값이 되는 경우 (memory가 "
     "망가진 경우)에는 답이 우연히 같을 수 있고 (답이 8 bit다), 그때는 이 줄이 마지막 보호다. "
     "이 이유는 두 번 틀렸다. 처음에는 지난 주기의 표시가 남아 빈 자리를 채웠고 (변이 검사가 알렸다), 다음에는 "
     "task가 두 번 실행되어 넷째 표시가 버려지면 앞의 셋만으로 옳은 답이 나왔다 (검토자가 찾았다). "
     "두 경우 모두 답이 틀리게 나오도록 고쳤고, TC-021과 TC-125, 증명한 성질 14가 그것을 본다"),
]

# build가 잡아야 하는 변이. 상수가 다른 곳의 값과 맞물려 있고, 그것을 _Static_assert가 compile할 때 견준다.
# 이 변이가 compile되면 그 견줌이 없어진 것이다.
# 설명 -> compile 출력에 있어야 하는 글
BUILD_CAUGHT = {
    "상수 FLOW_TASK_COUNT를 3에서 1 올린다": "FLOW_TASK_COUNT",
    "실행 확인의 구조체에서 배열 뒤에 필드를 더한다": "flow_t: 배열은 구조체의 끝에 있어야 한다",
    "페달 검사의 구조체에서 배열 뒤에 필드를 더한다": "pedal_check_t: 배열은 구조체의 끝에 있어야 한다",
    "inverter 검사의 구조체에서 배열 뒤에 필드를 더한다": "inverter_check_t: 배열은 구조체의 끝에 있어야 한다",
}

# 상수를 자동으로 바꿀 파일. 안전 요구사항을 받는 부분의 상수와,
# 감시의 한계와 맞물리는 기능의 상수 (올리는 속도, 후진의 비율)다
CONSTANT_FILES = ["src/input/input.h", "src/input/pedal_check.c", "src/monitor/monitor.h",
                  "src/reaction/reaction.h", "src/com/e2e.h", "src/flow/flow.h", "src/common/types.h", "src/app/app.c"]
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


def run_tests(copy):
    """복사본에서 test를 돌린다. 돌려주는 것: (종료 상태, 출력, 끝나지 않았는가).

    끝나지 않으면 make와 그 아래의 프로세스를 모두 끝내고 실패로 돌려준다. make만 끝내면 test 실행 파일이
    남아 계속 돈다 (그렇게 남은 프로세스가 한 시간 넘게 돌고 있던 것을 찾았다. docs/test-report.md 6절)."""
    proc = subprocess.Popen(["make", "-s", "test"], cwd=copy, stdout=subprocess.PIPE, stderr=subprocess.STDOUT,
                            text=True, start_new_session=True)
    try:
        output, _ = proc.communicate(timeout=TEST_TIMEOUT_S)
        return proc.returncode, output, False
    except subprocess.TimeoutExpired:
        os.killpg(proc.pid, signal.SIGKILL)
        output, _ = proc.communicate()
        return 1, output, True


def main():
    mutants = [m + (None,) for m in MUTANTS + constant_mutants()] + EQUIVALENT
    count = len(mutants) - len(EQUIVALENT)
    work = tempfile.mkdtemp(prefix="mutation-")
    missed = 0
    by_build = 0
    not_by_value = 0
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
            # 끝나지 않는 test는 실패한 test다
            returncode, output, timed_out = run_tests(copy)
            if what in BUILD_CAUGHT:
                if ("error:" in output) and (BUILD_CAUGHT[what] in output):
                    by_build += 1
                    print("build  %s" % what)
                else:
                    print("오류  build가 잡아야 하는 변이가 compile되었다 (%s)" % what)
                    missed += 1
                continue
            if "error:" in output:
                # compile이 안 되는 변이는 test가 잡은 것이 아니다
                print("오류  compile되지 않는 변이다 (%s)" % what)
                missed += 1
                continue
            caught = returncode != 0
            if why_equivalent is not None:
                if caught:
                    print("오류  동등하다고 적은 변이를 test가 잡았다 (%s)" % what)
                    missed += 1
                else:
                    print("동등  %s: %s" % (what, why_equivalent))
                continue
            if not caught:
                missed += 1
                print("놓침  %s" % what)
                continue
            # 어떻게 잡았는가. test가 값을 견주어 실패를 찍은 것과, 끝나지 않거나 죽은 것을 가른다.
            # 뒤의 것은 compiler와 memory의 배치에 달린 일이어서 잡았다고 믿기 어렵다
            if timed_out:
                not_by_value += 1
                print("잡음 (끝나지 않음)  %s" % what)
            elif re.search(r"^실패  ", output, re.M) is None:
                not_by_value += 1
                print("잡음 (실패를 찍지 않고 죽음)  %s" % what)
            else:
                print("잡음  %s" % what)
    finally:
        shutil.rmtree(work, ignore_errors=True)
    print("결함 %d개 가운데 %d개를 test가, %d개를 build (_Static_assert)가 잡았다. 동등한 변이 %d개는 세지 않았다"
          % (count, count - missed - by_build, by_build, len(EQUIVALENT)))
    if not_by_value:
        print("test가 잡은 것 가운데 %d개는 값의 검사가 아니라 끝나지 않거나 죽어서 잡혔다. 값으로 잡히게 test를 고친다"
              % not_by_value)
    return 1 if (missed or not_by_value) else 0


if __name__ == "__main__":
    sys.exit(main())
