# 2차 검토: 임베디드 소프트웨어 엔지니어 (단계 2 묶음 3의 예제, 1차 지적의 반영)

검토자: 임베디드 소프트웨어 엔지니어 역할 (Sonnet 5.5). 날짜 2026-11-23. 기준 commit 8695c04 (코드는 60180fc, 예제 문서는 b37a945).
제품 폴더는 고치지 않았다. 모든 실행과 변이는 scratchpad의 복사본 (`review-emb-s2p3/r2` 등)에서 했다.

## 돌린 것

| 무엇 | 결과 |
|---|---|
| `make check` (복사본) | 통과. test 25, 31, 9, 2, 1, 2, 1개 (검사 5581, 520, 139, 15, 5, 18, 5), `TC-` 63개, 추적 문제 0, 구현 예정 5, coverage 11개 파일 100% (`flow.c` 30줄), 증명 14개 (`prove_flow` assert 13개) |
| `make proof-mutation` (복사본) | 9개 가운데 9개를 증명이 잡았다. 문서와 같다 |
| `make mutation` | 돌리지 않았다 (진행자가 돌렸고 218 = 217 + 1). 숫자는 `MUTANTS` 169개 + 상수 49개 = 218로 맞추어 보았다 |
| 1차의 변이 가운데 "test의 구멍" 일곱 | 모두 이제 잡는다 (아래) |
| fault를 모두 무효로 하고 test를 돌림 (1차와 같은 실험) | `TC-113`, `TC-208`이 이제 실패한다. `TC-209`도 실패한다 |
| 추가 변이 | 16개 (아래) |
| 문서의 숫자 | 아래 표. 어긋난 것은 없다 |

## 1차 지적의 반영

| 지적 | 판정 | 확인한 방법 |
|---|---|---|
| E-01 [A] 증명의 "배열 밖" | 닫힘 (조건이 하나 남는다. E-11) | 구조체 셋 (`flow_t`, `pedal_check_t`, `inverter_check_t`)에서 배열이 끝에 있다. `flow_mark`의 `<=` 변이를 `make proof-mutation`이 `prove_flow`로 잡는다. 같은 변이를 내 복사본에서 `cbmc`로 따로 돌려도 실패한다. 서술은 test-report 5절 (조건을 적음), 6절, harness.c 주석, flow.h/input.h/monitor.h 주석에서 바뀌었다. 1차에서 증명이 못 잡은 다른 하나 (채널 1을 뺀 뒤 `bad = false`)는 고치지 않았다. 문서가 그것을 증명했다고 하지 않으므로 서술의 어긋남은 아니고, `TC-022`가 잡는다 (변이로 확인) |
| E-02 [B] `ok \|\| !ok`가 동등하지 않다 | 닫힘 | 아래의 E-02 절 |
| E-03 [B] `TC-208`이 fault 없이 통과 | 닫힘 | 복사본에서 `hal_sim_set_fault`를 무효로 하면 `TC-208`이 실패한다. 선의 값 (`enable_wire`)을 `sample_t`에 더했고 `TC-128`, `TC-129`에도 넣었다 |
| E-04 [B] `TC-113`이 fault 없이 통과 | 닫힘 | 같은 실험에서 `TC-113`이 실패한다 (`over_ms >= 10`, 기준보다 30 ms 이상 늦게 내려감). 잰 값 99 ms / 59 ms와 맞는 판정이다 |
| E-05 [B] `SWR-24`가 일부만 말함 | 닫힘 | `requirements.yaml`에서 `SWR-24`의 문장과 `SWR-26` (alloc 기능)을 견주었다. 기능이 지킬 상한과 25 Nm 올림이 `SWR-26`에 있고 `app.c`, `app.h`에 ID가 달려 있다 (E-15에서 작은 것) |
| E-06 [C] 채널을 뺀 뒤의 test | 닫힘 | 내 변이 4개 (채널 1, 2의 `bad = r_a && r_b`, `single`에 `p > 0`)를 다시 넣으면 모두 `TC-022`가 잡는다. 변이 목록에도 넷이 들어 있다 |
| E-07 [C] 연결을 보는 test | 닫힘 | 변이 셋을 다시 넣어 모두 잡았다: `record(torque_req)` -> `TC-209`, `diag.inverter_out_cycles` 출처 -> `TC-123` (이제 `CHECK_EQ(worst, expected)`), `e2e_rx_init`의 `ok = true` -> `TC-018` |
| E-08 [C] task table과 상수 | 닫힘 | `vcu.c`의 `_Static_assert`. 상수를 1 올린 변이는 compile되지 않는다. 문장 ("task table과 같은지")은 코드와 맞는다 |
| E-09 [C] 서술 넷 | 닫힘 | `hal.h`의 `latched` 주석, hsi.md 3절의 -1050, `e2e.c` 주석, `TC-124`의 한계 (15, 76)를 읽어 확인했다. `e2e.c`의 새 주석은 "더하지 않아도 같다"를 함께 적어 정직하다 |
| E-10 [C] 변이 도구의 timeout | 닫힘 | `mutation_check.py`에 `timeout=300`과 `TimeoutExpired` 처리가 있다. 읽어서 확인했다. 시간 초과한 `make`가 남기는 자식 process (test 실행 파일)를 정리하지는 않는다 (1차에서 `timeout 60 make`를 겪을 때 남았다). 작다 |

### 1. E-01 자세히

- 구조체: `flow_t`는 `count, question, marks[]`, `pedal_check_t`는 `window[]`가 끝, `inverter_check_t`는 `sent[]`가 끝이다.
- 도구 확인 (`tool_check.c`): 뜻이 있다. 확인이 늘 통과하는 꼴이 아니다. 둘 가운데 `canary_array_last`는 "VERIFICATION FAILED"여야 통과이고, 도구가 그 경계를 보지 않게 되면 `prove.sh`가 실패한다. 나는 prove.sh의 옵션 (`--bounds-check --signed-overflow-check --div-by-zero-check --conversion-check`)과 prove.sh가 쓰는 옵션 (`--bounds-check --pointer-check`) 둘로 모두 돌렸고 결과가 같았다 (끝: FAILED, 안: SUCCESSFUL). 한계 쪽 (`canary_array_inside`)은 어느 쪽이 나오든 통과이고 알림만 바꾼다. 그것은 의도한 것이다.
- 한 가지 빈틈: "배열이 끝에 있다"는 약속을 지키게 하는 것이 없다. E-11.
- `make proof-mutation` 변이 9개를 읽었다. 앞의 셋은 E-01의 세 배열 (`flow`, `pedal`, `inverter`)이고 뜻이 있다. 나머지는 증명이 이미 잡는다고 문서가 말하는 것들이다.
- 도구의 한 곳: `proof_mutation.py`는 "실패    <성질>"이 출력에 있으면 잡았다고 센다. `prove.sh`는 CBMC가 parse나 compile에서 실패해도 같은 줄을 낸다. 그래서 오타로 compile되지 않는 변이도 "잡음"으로 센다. 지금의 9개는 `count == 1`로 바꿀 곳을 찾는 검사를 거치므로 위험은 작다 (E-13).

### 2. E-02 자세히

- `flow_answer`에 `answer = answer * 31 + count`가 들어갔다. sim의 기다리는 답은 `(q * 923521 + 31809) & 0xFF`다. 31^4 = 923521, ((1 * 31 + 2) * 31 + 3) * 31 + 3 = 31809로 직접 계산해 맞다. harness.c의 `expected`, hsi.md 3절의 식, unit test의 65 / 194 / 190 / 223도 같은 식에서 나온다 (직접 계산).
- `FAULT_TASK_TWICE`가 `scenario.c`에서 task를 한 번 더 부른다. `TC-125`는 여섯 경우 (기능, 감시와 출력의 두 번 실행)를 보고 경고가 있어야 하는 경우의 표 (`k == 1 || k == 3`이 0)를 고쳤다. 내 변이 `answer`에서 count를 뺀 것은 이제 `TC-125`가 잡는다.
- `ok || !ok`는 지금 정말 동등하다. 닿는 표시를 모두 세어 보았다 (표시를 1 - 3 가운데 아무 순서로 최대 일곱 개까지 남기는 모든 열, 질문의 번호를 바꿔 가며): 옳은 열 (1, 2, 3) 말고 옳은 답을 내는 열이 하나도 없다. 그래서 변이가 test를 빠져나가는 길은 없다. 내 변이 `ok || count == 4`와 `ok || count == 2`도 test가 놓치는데 같은 까닭이다 (동등).
- 남은 서술의 흠 (E-14): 따로 둔 변이의 이유가 "표시가 틀렸는데 답이 우연히 같은 조합이 있다 (엄밀하게는 동등하지 않다)"를 아직 적는다. 표시를 0 - 255의 아무 값으로 보면 그런 조합이 있지만 task가 남길 수 있는 표시로는 없다. 이 이유는 이미 두 번 틀렸고 (문서가 적었다), 세 번째가 "있다고 쓴 것이 없다"가 되지 않게 고쳐 두는 것이 낫다.
- 성질 14의 "나-2" (표시 셋이 옳고 수가 셋이 아니면 답이 옳은 답이 아니다)는 뜻이 있다. 증명의 변이 4번 (답에 수를 넣지 않음)을 증명이 잡는다.

### 3. 구조체 뒤의 값을 보는 검사 (`TC-021`)

- 뜻이 있다. 확인: 복사본에서 `flow_mark`의 `<`를 `<=`로 바꾸고 `make test`를 돌리면 `TC-021`만 실패한다. 검사를 지우면 그 변이는 통과한다 (이 검사가 없으면 test가 놓친다는 진행자의 말이 맞다).
- 약점: (1) 구조체를 감싸는 임시 구조체와 "바로 뒤"가 말 그대로 이어져 있다는 C의 규칙에 기댄다. 필드가 모두 `uint8_t`라서 padding이 없지만 그 가정은 test에 적혀 있지 않다. (2) 정의되지 않은 동작을 일부러 일으킨다. (3) 같은 방법이 `pedal_check_t`, `inverter_check_t`에는 없다 (E-12).
- 더 나은 방법: sanitizer로 test를 돌린다. 내가 1차에서 쓴 방법이다. 지금 구조에서 확인했다.
  - ASan (`make test CC="cc -fsanitize=address"`): `flow_mark`의 `<=` 변이를 `TC-021`에서 `stack-buffer-overflow`로 잡는다. 배열이 구조체의 끝에 와서 지역 변수 `flow_t`의 끝을 넘기 때문이다. 배열을 끝으로 옮긴 효과가 증명뿐 아니라 ASan에도 미친다.
  - UBSan (`-fsanitize=undefined`): 이 변이에서 runtime error가 나오지 않는다. clang은 구조체 끝의 배열을 가변 길이 배열처럼 보아 경계 검사를 하지 않는다. `-fstrict-flex-arrays=3`을 더해야 `index 3 out of bounds for type 'uint8_t[3]'`가 나온다. 1차에서 "ASan, UBSan이 깨끗하다"고 쓴 확인은 배열이 구조체의 안에 있을 때였다. 지금의 배열 위치에서 UBSan만으로는 약하다.
  - 권고: `make check`에 ASan 한 번 (`-fsanitize=address,undefined -fstrict-flex-arrays=3`)을 더하고, 지금의 guard 검사는 그대로 둔다. guard는 sanitizer가 없는 환경에서도 도는 마지막 보호다.

### 4. `BUILD_CAUGHT`

- 맞다. `FLOW_TASK_COUNT`를 1 올린 변이는 compile 출력에 "task table과 FLOW_TASK_COUNT가 맞지 않는다"가 있어야 build가 잡은 것으로 센다. 다른 이유로 compile되지 않거나 compile되면 "오류"로 세어 도구가 실패한다. 그래서 `_Static_assert`를 중화하면 도구가 알린다 (내 변이 `_Static_assert(1 || ...)`로는 test가 통과했다. 도구의 쪽은 `BUILD_CAUGHT`의 "compile되었다" 분기로 알린다. 그 분기는 읽어서 확인했고 돌려 보지는 않았다).
- 문서가 이것을 "test가 잡았다"에 넣지 않고 따로 센 것은 정직하다 (test-report 1절, 7절, 16장의 표).
- 작은 것: `flow_check`는 표시 셋을 상수 3으로 직접 본다 (`marks[0]`, `[1]`, `[2]`). `FLOW_TASK_COUNT`를 4로 올리고 `_Static_assert`를 맞추면 `flow_check`는 넷째 표시를 보지 않는다. 지금의 범위 밖이다.

### 5. 일곱 변이

| 1차의 변이 | 결과 |
|---|---|
| `e2e_rx_init`의 `ok = true` | 잡음 (`TC-018`) |
| `diag.inverter_out_cycles`를 `invalid_cycles`에서 | 잡음 (`TC-123`) |
| `inverter_check_record(torque_req)` | 잡음 (`TC-209`) |
| 채널 2를 뺀 뒤 `bad = range1 && range2` | 잡음 (`TC-022`) |
| 채널 2의 `single`에 `p1 > 0` | 잡음 (`TC-022`) |
| 채널 1을 뺀 뒤 `bad = range2 && range1` | 잡음 (`TC-022`) |
| 채널 1의 `single`에 `p2 > 0` | 잡음 (`TC-022`) |

`TC-209`는 새 test (FI-33)이다. 기능이 큰 토크를 요구하고 inverter도 더 내는 fault 둘이다. 판정이 구체적이다 (보낸 토크 800, 차단까지 30 ms, `inverter_out_cycles` 3). `record(torque_req)`가 깎기 전의 요구를 기록하면 범위가 넓어져 차단이 늦는다는 것을 보인다.

### 6. `SWR-26`, `SWR-20`의 `TC-101`

- `SWR-26` (기능): 부모가 `TSR-09`이고 `app.c`, `app.h`에 ID가 있다. `trace.py`가 코드 `src/app/app.c, app.h`, test `TC-007, TC-022`로 잇는다. 추적 문제 0. 뜻이 있다: 지금까지 기능을 받는 software safety requirement가 없었다 (FuSa의 F-04).
- 작은 것: `verified_by`가 `TC-007`, `TC-022`뿐이다. 기능이 입력이 바뀌는 열 가지에서 깎이지 않는다는 `TC-011`이 이 요구사항의 핵심 test인데 목록에 없다 (E-15).
- `SWR-20`의 `TC-101`: 고장이 없으면 watchdog이 끊지 않는다 (`s->watchdog_tripped`가 판정에 들어 있다). 뜻이 있다. `FSR-10`의 거짓 차단 쪽이다.

### 7. 문서의 숫자

| 항목 | 문서 | 실행 결과 | 일치 |
|---|---|---|---|
| `TC-` test | 63개 | 63개 | 예 |
| 추적 | 구현한 SWR 24개 | 24개, 구현 예정 5 | 예 |
| 변이 | 218 = 217 + 1 (169 + 49) | `MUTANTS`에서 169, 상수 49 (진행자의 전체 실행의 숫자는 믿었고 다시 돌리지 않았다) | 예 |
| 증명의 변이 | 9 | 9 / 9 | 예 |
| `flow.c` | 30줄 | 30 | 예 |
| 제품 코드 | 13장의 955줄 | `src/*/*.c`의 `wc -l` 합 955 | 예 |
| 증명 | 14개 | 14개 | 예 |
| hsi.md 3절의 watchdog의 답 | (n mod 256) x 923521 + 31809 | sim, harness, unit test와 같은 식 (직접 계산) | 예 |
| hsi.md 3절의 토크의 범위 | 정상 -1000 - 2500, 깎여 나가면 -1050 | `SWR-06`, 성질 1 (105 Nm)과 맞다 | 예 |
| 16장의 표 | test case 63, 변이 218 (217 + 1), fault 33 | 맞다 (FI-33까지) | 예 |

## 새 지적

E-11 [B] "배열은 구조체의 끝에 둔다"는 약속을 지키게 하는 것이 없다. 약속이 깨지면 증명과 test가 조용히 눈이 먼다.
- 파일: `src/flow/flow.h`, `src/input/input.h`, `src/monitor/monitor.h` (주석만 있다), `tools/prove.sh`, `test/proof/tool_check.c`.
- 문제: E-01의 반영은 도구가 구조체의 끝만 본다는 한계 위에 서 있다. 그래서 배열이 끝에 있어야 한다. 그런데 이것을 검사하는 것이 주석뿐이다. 누가 이 구조체에 필드 하나를 더하면 (나중에 `flow_t`에 진단용 변수를 하나 더하는 일은 흔하다) 증명도 test도 알리지 않고 눈이 먼다.
- 확인: 복사본에서 `flow_t`의 `marks[]` 뒤에 `uint8_t spare;`를 더하고 `flow_mark`를 `<=`로 바꾸었다. `PROPS=prove_flow sh tools/prove.sh`는 "증명됨"이고 `make test`는 실패 0개다 (`TC-021`의 guard도 통과한다. 넘는 쓰기가 `spare`에 떨어지기 때문이다).
- 고칠 방법: 세 구조체에 대해 compile할 때 견준다. 예: `_Static_assert(offsetof(flow_t, marks) + sizeof(((flow_t *)0)->marks) == sizeof(flow_t), "...")`를 `flow.c`에, 같은 꼴을 `pedal_check.c`와 `inverter_check.c`에 둔다. 변이 도구의 `BUILD_CAUGHT`에 "배열 뒤에 필드를 더함"을 하나 더하면 그 줄이 지켜진다.

E-12 [C] `pedal_check_t`와 `inverter_check_t`의 한 칸 넘는 쓰기를 test가 결정적으로 잡지 않는다. 지금은 우연에 기댄다.
- 파일: `test/test_unit.c` (`flow`만 guard가 있다), `src/input/pedal_check.c`, `src/monitor/inverter_check.c`.
- 문제: 배열을 끝으로 옮기자 `window_pos`를 `>`로 바꾼 변이 (넘는 쓰기가 `window[100]`)는 이제 구조체 바깥을 쓴다. 복사본에서 `make test`를 하면 `test_unit`이 `Abort trap: 6` (rc 134)으로 죽는다. "실패 N개"가 아니라 stack의 보호 기능이 죽인 것이다. 이 도구 모음에서는 잡은 것으로 세지만 (종료 코드가 0이 아니다), stack 보호가 없는 compiler나 다른 배치에서는 조용히 통과할 수 있다. 1차의 상태에서는 test의 값 검사가 결정적으로 잡았다.
- 확인: 복사본에서 `pedal_check.c`의 `window_pos >= PEDAL_WINDOW_CYCLES`를 `>`로 바꾸어 `make test`. 위 3절의 ASan 확인과 같은 꼴이다.
- 고칠 방법: `TC-021`의 guard 꼴을 두 구조체에도 두거나 (더 나은 것은), `make check`에 ASan을 넣는다 (3절). 뒤의 것이 세 구조체와 앞으로 더할 것을 한꺼번에 덮는다.

E-13 [C] `tools/proof_mutation.py`가 "증명이 실패했다"와 "도구가 실패했다"를 가르지 않는다.
- 파일: `tools/proof_mutation.py`, `tools/prove.sh`.
- 문제: 잡은 것의 판정이 "종료 코드가 0이 아니고 `실패    <성질>`이 출력에 있다"이다. CBMC가 변이된 코드를 parse하지 못해도 (또는 시간이 다해도) `prove.sh`는 같은 줄을 낸다. 오타로 compile되지 않는 증명의 변이가 "잡음"으로 센다. 읽어서 확인했고 돌려 보지는 않았다.
- 고칠 방법: `prove.sh`가 `VERIFICATION FAILED`와 그 밖의 실패를 다른 줄로 내거나, `proof_mutation.py`가 CBMC의 출력에서 `VERIFICATION FAILED`와 `FAILURE`가 있는지 본다.

E-14 [C] 따로 둔 변이의 이유가 "우연히 같은 조합이 있다"를 아직 적는다 (`tools/mutation_check.py`의 `EQUIVALENT`, test-report 7절, TSC 9.1절 M5).
- 문제: 위 2절의 계산으로, task가 남길 수 있는 표시 (1 - 3의 아무 열, 일곱 개까지)와 질문의 번호의 어느 것에서도 옳은 답과 같아지는 틀린 열이 없다. 표시를 아무 byte로 보면 있지만 닿지 않는다. 이 이유가 두 번 틀렸다고 문서가 스스로 적은 만큼, 지금의 사실로 적는 것이 낫다.
- 고칠 방법: "표시가 닿을 수 있는 값 (1 - 3, 일곱 개까지)에서는 틀린 열이 옳은 답을 내지 않는다는 것을 모두 세어 확인했다. 그래서 동등하다. 표시가 다른 값이 될 수 있는 경우 (memory가 망가진 경우)는 이 줄이 마지막 보호다"로 바꾼다. 세어 보는 것을 unit test나 작은 도구로 남기면 더 낫다.

E-15 [C] 작은 것 둘.
- `SWR-26`의 `verified_by`에 `TC-011`이 없다 (기능이 입력이 바뀌는 열 가지 경우에 깎이지 않는다). 가장 가까운 test다 (`requirements.yaml`).
- `flow_check`가 표시를 `marks[0..2]`로 직접 본다 (E-08에서 본 상수와 이어져 있지 않다). `_Static_assert`가 `FLOW_TASK_COUNT`의 크기는 지키지만, 그 수를 바꾸면 `flow_check`의 본문은 따라 바뀌지 않는다. 지금은 문제가 아니다.

## 확인하지 못한 것

- 전체 `make mutation` (진행자의 숫자를 믿었다). `BUILD_CAUGHT`의 "compile되었다" 분기와 E-10의 timeout 분기, `proof_mutation.py`의 compile 오류 처리는 읽어서만 확인했다.
- 원고 (`chapters/`)는 13장의 줄 수와 16장의 표만 보았다.
- FuSa 쪽의 지적 (F-01 - F-28)과 그 반영은 보지 않았다.
- 실제 MCU, CBMC의 다른 판.

## 판정

판정: 조건부 통과.

까닭: 1차의 열 개는 모두 닫혔다. A (증명의 서술)는 구조와 도구 확인과 증명의 변이로 닫혔고, 같은 변이를 증명이 잡는 것도 확인했다. test의 구멍 일곱과 "fault를 빼도 통과하는 test" 둘이 닫혔고, `ok || !ok`는 이제 정말 동등하다. 숫자는 모두 맞다. 새 지적은 A 0, B 1, C 4다. 조건은 E-11 하나다: 이 반영이 "배열은 끝에 둔다"에 기대는데 그 약속을 compile이 지키지 않으면, 다음에 필드를 하나 더할 때 증명과 test가 같이 눈이 먼다 (재현함). `_Static_assert` 세 줄이면 닫힌다. 나머지는 C이고 반영하지 않아도 통과에 영향이 없다.
