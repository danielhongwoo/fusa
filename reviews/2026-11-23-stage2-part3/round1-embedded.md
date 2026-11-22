# 1차 검토: 임베디드 소프트웨어 엔지니어 (단계 2 묶음 3의 예제)

검토자: 임베디드 소프트웨어 엔지니어 역할 (Sonnet 5.5). 날짜 2026-11-23. 기준 commit 1e5aaf7 (`git log --oneline 75006f1..HEAD -- example/drive-torque`의 8개 commit). 다른 검토자의 의견은 보지 않았다.
대상: 묶음 3에서 예제에 더한 것 (메시지의 보호와 검사 `SWR-17`/`SWR-18`, 방향의 판정 `SWR-16`, inverter가 알린 토크의 검사 `SWR-19`, 실행의 확인 `SWR-20`, 되읽기 `SWR-21`, 줄여 감 `SWR-24`, sim, test, 증명 성질 4/6/10-14, 변이 목록, 문서).
저장소는 고치지 않았다. 모든 실험은 scratchpad의 복사본 (`review-emb-s2p3/`)에서 돌렸다.

## 읽은 것

- 지난 기록의 형식: `reviews/2026-11-23-stage2-part2/README.md`, `round1-embedded.md`.
- `docs/requirements.yaml`의 `SWR-16` - `SWR-25`와 `TSR-11` - `TSR-19`, `docs/test-report.md` 전부, `docs/technical-safety-concept.md` 9절 (9.1 - 9.5), `docs/hsi.md` 전부.
- 코드 전부: `src/com/e2e.c`, `src/input/gear_check.c`, `src/input/pedal_check.c`, `src/monitor/inverter_check.c`, `src/monitor/monitor.c`, `src/flow/flow.c`, `src/vcu/vcu.c`, `src/reaction/reaction.c`, `src/app/app.c`, 헤더들, `sim/hal_sim.c`, `sim/plant.c`, `sim/frame_sim.c`, `sim/scenario.c`, `test/proof/harness.c` 전부, `tools/mutation_check.py`.
- test는 TC-022 (unit), TC-113, TC-123, TC-124, TC-132, TC-208, NC-005를 읽었고, 나머지는 실행 결과와 변이로 보았다. 5장 이후의 장 (chapters/)은 읽지 않았다. 용어 하나 (ch13의 증명 서술)만 grep으로 보았다.

## 돌린 것과 결과

| 무엇 | 결과 |
|---|---|
| `make check` (복사본) | 통과. test 62 + 8개, 추적 문제 0, 정적 분석 지적 없음, coverage 11개 파일 100%, 증명 14개 성립 |
| `make mutation` (복사본, 약 15분) | 210개 가운데 210개를 잡음, 동등 2개. 문서와 같다 |
| `make check STRICT=1`의 추적 단계 | 종료 코드 2 (구현 예정 5개). 문서대로다 |
| `make intro` | 13.3 -> 31.1 km/h (naive), 11.6 km/h (예제). `notes/claims.md`의 C-01-019와 같다 |
| ASan + UBSan으로 `make test` | 7개 실행 파일 모두 실패 0, runtime error 0 |
| 변이를 더 넣음 (아래 표) | 90개 (compile되는 것) 가운데 65개 잡음, 25개 놓침 |
| 무작위 실험 (아래 표) | 모델과 어긋난 것 0. 단 어긋남을 찾는 과정에서 내 모델의 오류 둘을 고쳤다 (아래) |
| 증명의 점검 | assume이 비어 있지 않음 (14개 모두 끝에 `assert(0)`가 닿음). 제품 코드를 바꿔 본 28개 가운데 26개를 증명이 잡음, 2개는 못 잡음 (E-01) |
| fault를 빼고 test를 돌림 | 시나리오 test 31개 가운데 23개가 실패, 나머지는 fault가 없는 test이거나 운전자의 입력이 fault인 test. 단 TC-113와 TC-208은 fault가 없어도 통과 (E-03, E-04) |
| 문자 검사 | 이 범위에서 바뀐 57개 파일에 ASCII와 한글 밖의 문자는 없다 |

## 숫자의 대조

`docs/test-report.md`의 숫자를 출력과 하나씩 맞춰 보았다. 어긋난 숫자는 없다.

| 항목 | 문서 | 출력 | 일치 |
|---|---|---|---|
| `TC-` test | 62개 | 62개 (unit 22, 시나리오 31, fault를 넣는 test 8, 대조 파일의 TC-127 1) | 예 |
| `FT-`, `NC-` test | 8개 | FT 3, NC 5 | 예 |
| 구현 예정 | 5개 (SWR 2개) | 5개 (FSR-12, SWR-22, SWR-23, TSR-16, TSR-17) | 예 |
| coverage 줄 수 (statement) | app 28, e2e 48, flow 29, brake 23, gear 22, input 9, pedal 72, inverter 38, monitor 65, reaction 31, vcu 88 | 같다 | 예 |
| coverage branch, MC/DC | 26, 20, 20, 16, 18, 6, 62, 28, 44, 30, 24 | 같다 (11개 모두 100%) | 예 |
| 증명 | 14개 | 14개 (assert 4 - 15개씩) | 예 |
| 변이 | 210개 (손으로 161 + 상수 49), 동등 2 | 210 / 210, 동등 2 | 예 |
| 변이의 갈래 | 24 (메시지), 18 (방향), 20 (inverter), 19 (실행), 4 (되읽기), 4 (넘기는 값과 순서) | `MUTANTS`에서 파일과 항목으로 세어 맞다. 15 (줄여 감)도 맞다 | 예 |
| FI-01 | 29 ms, 88 ms | 29, 88 | 예 |
| FI-02 | 49 ms, 108 ms, 가속 0.08 | 49, 108, 0.08 | 예 |
| FI-07, FI-08 | 40 ms, 800 ms | 40, 800 | 예 |
| FI-11 | 190 ms | 190 | 예 |
| FI-13, FI-14 | 99 ms, 0.00 / 99 ms (없으면 59), 1.19, 18 ms | 같다 | 예 |
| FI-16 | 차단까지 140 ms | 140 | 예 |
| FI-17, FI-19 | 1.35 m/s, 1.81 / 966 ms | 같다 | 예 |
| FI-20 | 30 ms, 1.40, 17 ms / 70 ms, 128 ms, 1.32, 49 ms | 같다 | 예 |
| FI-21, FI-22 | 36 ms, 109 ms, 1.53, 24 ms / 1.81, 985 ms | 같다 | 예 |
| FI-23, FI-24, FI-25 | 15 ms, 73 ms / 6 ms / 16 ms | 같다 | 예 |
| FI-28, FI-30, FI-31 | 9 ms / 29 ms / 0.63 | 같다 | 예 |
| NC-001 .. NC-005 | 1.81, 984 / 1.81, 984 와 1.36, 974 / 1.81, 966 / 1.81, 985 / 1.36, 874 | 같다 | 예 |
| TC-123 표 (0 1 / 1 2 / 0 0) | 같다 | 같다. 시정수 25 ms에서 페달을 놓은 뒤 70 ms | 예 |
| 제품 코드 줄 수 | 944줄 | `src/*/*.c`의 `wc -l` 합이 944 (헤더는 뺀 수) | 예 |

문서의 숫자는 모두 맞다. 다만 이 숫자 가운데 일부는 test가 값으로 확인하지 않고 찍기만 한다 (E-03, E-07).

## 지적

E-01 [A] 증명이 "배열 밖에 쓰지 않는다"고 말하는 것은 성질 14에서 틀리다.
- 파일: `docs/test-report.md` 197줄 (성질 14의 "표시를 남길 때 배열 밖을 쓰지 않는다"), 201줄 ("배열 밖의 접근이 없다는 것도 함께 증명했다"), 220줄 ("증명 (성질 14)은 배열 밖에 쓰지 않는다는 것을 모든 상태에서 본다"). `test/proof/harness.c` 691줄. `chapters/ch13-coding.md` 63줄, 171줄도 같은 말을 한다 (이 장은 범위 밖이라 읽지 않았고 grep으로만 보았다).
- 문제: `flow_mark`의 범위 검사를 `<`에서 `<=`로 바꿔 배열의 바로 뒤 (`marks[3]`)에 쓰게 해도 성질 14가 "증명됨"으로 나온다. CBMC 6.11의 `--bounds-check`는 구조체 안의 배열을 포인터로 접근할 때 (`f->marks[i]`) 그 배열의 크기를 넘지만 구조체 안에 머무는 접근을 잡지 않는다. 쓴 값이 이웃 변수 (`count`)에 겹치는 것을 모델이 흉내 내지도 않는다. 그래서 `assert(f.count == 4)`도 통과한다. 이 증명이 코드의 `marks[3]`을 잡지 못한다는 것은 `test-report.md` 220줄이 직접 설명하는 바로 그 변이다 (실제 기계에서는 `marks[3]`이 `count`다). 그 변이를 잡는 것은 증명이 아니라 unit test (`TC-021`)와 변이 목록의 70번째 항목이다. 성질 4와 13은 적을 자리 (`window_pos`, `pos`)가 한 주기 뒤에 범위 안이라는 assert가 따로 있어서 같은 변이를 잡는다 (아래의 증명 표).
- 확인: 복사본에서 `src/flow/flow.c`의 `if (f->count < FLOW_TASK_COUNT)`를 `<=`로 바꾸고 `cbmc ... --function prove_flow --bounds-check --signed-overflow-check --conversion-check --unwind 101 --unwinding-assertions`를 돌리면 `VERIFICATION SUCCESSFUL`이다 (`[flow_mark.array_bounds.1] ... SUCCESS`). 최소 예 (`mini/b.c`): 구조체 안의 `uint8_t marks[3]`에 `f.marks[i % 4]`로 쓰는 함수는 직접 접근이면 `array_bounds` FAILURE, 포인터를 거치면 SUCCESSFUL이다.
- 고칠 방법: (1) 세 곳의 서술을 "성질 14가 보는 것은 표시의 수와 값이다. 배열 바로 뒤에 쓰는 결함은 CBMC의 bounds 검사가 보지 못하고 unit test가 본다"로 고친다. (2) 가능하면 증명에서도 닫는다: `flow_mark`를 "자리 번호를 지역 변수에 받아 `if (idx < FLOW_TASK_COUNT)`로 쓰는" 꼴로 바꾸고 하네스에 같은 식을 `__CPROVER_assert`로 두거나, 하네스에서 `marks`를 구조체 밖의 배열로 따로 검사한다. 성질 4와 13의 "배열 밖" 서술은 index의 assert가 받치고 있다고 한 줄 적는다.

E-02 [B] 동등한 변이로 따로 둔 둘째 항목 (`if (ok || !ok)`)은 동등하지 않다. test-report 7절과 technical-safety-concept 9.1절 (M5의 첫째 줄)의 서술이 test의 구멍을 가린다.
- 파일: `tools/mutation_check.py` 398행 (`EQUIVALENT`), `docs/test-report.md` 242행, `docs/technical-safety-concept.md` M5 첫째 줄.
- 문제: 변이의 이유는 "틀린 표시가 우연히 옳은 답을 내는 조합이 있다 (답이 8 bit다)"이고, "엄밀하게는 동등하지 않다"고 적혀 있다. 그런데 그 조합은 우연한 것이 아니라 흔한 것이다. 한 task가 한 주기에 두 번 실행되면 (마지막 task에서 `marks`가 1, 2, 3, 3) `flow_mark`가 넷째 표시를 버리고 `count`만 4로 만든다. `marks[0..2]`는 1, 2, 3 그대로이므로 `flow_answer`는 옳은 답을 낸다. 확인 (`flow_check`)이 거짓인데도 답이 옳아서, 확인 줄이 유일한 보호가 된다. 문서의 말대로 그 줄이 필요하다면, 그 줄을 빼면 test가 실패해야 한다. 지금은 아무 test도 실패하지 않는다. sim에 "task가 두 번 실행됨"이라는 fault가 없기 때문이다. 8 bit의 답이 옳은 답과 같아지는 틀린 표시의 조합은, 표시를 0 - 255의 아무 값으로 보면 65535개이고 (내 계산), 실제로 닿는 값 (0 - 3)으로 좁히면 (0, 0, 2) 하나뿐이다. 이 하나는 `flow_mark`로 만들 수 없다. 문서가 말한 우연한 조합은 그러므로 닿지 않는 것이고, 닿는 것은 넷째 표시다.
- 확인: 복사본의 `sim/scenario.c`에서 t == 500 ms에 `vcu_task_table[2].run(&vcu)`를 한 번 더 부르게 하고 (`dbl/`), 1000 ms 시나리오를 돌렸다. 원본 `vcu.c`: watchdog이 506 ms에 끊고 구동 허용 신호가 꺼졌다. `if (ok || !ok)` 변이: 끊지 않았고 끝까지 토크가 나갔다 (구동 허용 1, 토크 124 Nm). 이 둘이 test에서 같아 보이는 것은 sim에 그 fault가 없어서일 뿐이다. 같은 방식으로 `if (ok || (count == 2))`는 놓침 (답이 틀려서 watchdog이 끊으므로 동등).
- 고칠 방법: sim에 `FAULT_TASK_REPEAT` (task 하나가 한 주기에 두 번 실행됨, `scenario.c`의 4번 단계)를 더하고 `TC-12x` 하나를 더한다. 그 변이를 `MUTANTS`로 옮기고 `EQUIVALENT`에서 뺀다. test-report 7절의 "(하나는) 보호가 겹쳐 test로 가릴 수 없다"는 문장은 "넷째 표시를 만드는 fault를 넣어 가릴 수 있게 되었다"로 바꾼다. 첫째 `EQUIVALENT` (`excess_cycles`를 멈추지 않음)는 이유가 옳다. 고정은 풀리지 않고 `excess_cycles`는 밖에 보이지 않는다 (진단 메시지에도 없다).

E-03 [B] `TC-208` (FI-29)은 sim의 fault를 빼도 통과한다. 선이 허용에 고착된 채 (숨은 고장) 구동을 막은 것이 토크 요구 0이었다는 말을 test가 보이지 않는다.
- 파일: `test/test_fault_app.c` (`tc_208`), `docs/test-report.md` 86행, 111행, 122행, `docs/technical-safety-concept.md` M6의 둘째 줄.
- 문제: `tc_208`이 확인하는 것은 토크 0, 구동 허용 차단 (VCU가 `enable`에 쓴 값), 경고, 가속의 차이 0이다. 선이 실제로 고착되어 있는지는 어디서도 보지 않는다. `sample_t.enable`은 VCU가 쓴 값 (`hal_sim_enable`)이지 inverter에 닿은 선의 값이 아니다. 그래서 "선은 끊기지 않았고, 구동을 막은 것은 토크 요구 0이었다"는 문장에 대응하는 assert가 없다. 문서의 의도 (끊는 길이 둘이어서 하나가 죽어도 `SG-01`이 지켜진다)는 선이 죽어 있어야 의미가 있다.
- 확인: 복사본에서 `hal_sim_set_fault`의 첫 줄에 `return;`을 넣으면 (fault 전부 무효) `build/test_fault_app`에서 `TC-208`이 통과한다 (`nf/`). 같은 실험에서 시나리오 test는 23개가 실패한다.
- 고칠 방법: `sample_t`에 plant의 `enable` (inverter에 닿은 값)을 한 칸 더하고, `TC-208`이 "끝에서 선은 허용이고 VCU는 끊으라고 썼다"를 `CHECK`한다. 또는 `hal_sim_enable_wire()`를 노출한다.

E-04 [B] `TC-113` (FI-14)도 fault가 없어도 통과한다. 문서가 쓴 "inverter가 되풀이를 알아채고 버렸다. 지난 토크가 50 ms 남았다가 내려갔다"를 test가 보이지 않는다.
- 파일: `test/test_scenario.c` `tc_113` (1000행대), `docs/test-report.md` 71행, 100행.
- 문제: 판정은 "페달을 놓은 주기에 0을 보낸다", "1.0 m/s^2를 넘은 시간 <= 200 ms", "모터의 토크가 5% 아래로 내려가는 데 110 ms 이하", "끝에 토크가 0"이다. 고장이 없을 때도 모두 참이다 (고장이 없으면 59 ms). 문서의 99 ms와 18 ms는 `printf`로만 나온다. fault가 되풀이를 만들지 못하는 sim의 결함이 생겨도 이 test는 통과한다.
- 확인: 위와 같은 실험 (fault 전부 무효)에서 `TC-113`이 통과한다.
- 고칠 방법: 참조 실행 (`log_ref`)과 견주는 assert를 하나 더한다. 예: `t_off - T_FAULT >= first_motor_off(ref) - T_FAULT + 30` (99와 59의 차이 40). 가속의 차이가 0보다 큰 때가 있다 (`over_ms > 0`)도 같은 구실을 한다.

E-05 [B] 요구사항 `SWR-24`가 코드가 하는 것의 일부만 말한다.
- 파일: `docs/requirements.yaml` 276줄 (`SWR-24`), `src/reaction/reaction.c` 63줄과 `src/reaction/reaction.h`의 `LIMP_APP_TORQUE`, `src/app/app.c`.
- 문제: 코드의 주석은 `reaction_app_limit`을 `SWR-24`로 가리키고 (`reaction.c`), 증명 성질 6은 "줄여 감에서 나가는 토크는 35 Nm"를 단언하고, `TC-022`/`TC-130`이 350을 값으로 확인한다. 그러나 `SWR-24`의 문장에는 "기능은 35 Nm를 넘게 요구하지 않는다"가 없다. 그 문장은 `TSR-18`에만 있고, 그 할당은 "기능"인데 `SWR-24`의 `alloc`은 "입력 검사, 감시"다. 따라서 기능 모듈 (`app_step`의 `limit` 인자)을 받는 소프트웨어 요구사항이 없다. 같은 모양의 빠진 것: "기능은 상태가 바뀐 그 주기에 상태를 받는다" (`vcu.c`의 `task_input`에서 사건을 알리고 `task_app`이 받는다. `TSR-18`에는 있다), "다시 켤 때까지 정상으로 돌아가지 않는다" (`excluded`가 풀리지 않는 코드는 있다), "두 채널이 범위 안에서 어긋나면 토크 0 (페달 고장)으로 간다" (`SWR-02`/`SWR-03`이 받는다). 앞의 둘은 `TSR-18` 아래에서 어떤 `SWR`도 받지 않는다.
- 확인: `requirements.yaml`에서 `SWR-24`와 `TSR-18`의 `text`를 견준다. 변이 목록의 62, 63, 64, 65번 (줄여 감의 기능 상한)은 이 빠진 요구사항의 코드를 지킨다.
- 고칠 방법: `SWR-24`에 "기능은 줄여 감 상태에서 35 Nm를 넘게 요구하지 않는다. 기능은 상태가 바뀐 주기에 새 상한을 받는다"를 더하고 `alloc`에 "기능"을 넣는다. 줄여 감이 풀리지 않는다는 문장도 `SWR-25` 쪽에 적는다.

E-06 [C] 페달 채널 하나를 뺀 뒤의 test가 "뺀 채널이 정상으로 돌아온 경우"와 "다른 채널이 페달을 놓은 값인 경우"를 보지 않는다. 변이 넷이 test를 빠져나갔다 (채널 1과 2에 각각 둘).
- 파일: `test/test_unit.c` `tc_022` (1195행 이하), `src/input/pedal_check.c`.
- 문제: (a) 채널 1을 뺀 뒤의 `bad = range2;`를 `bad = range2 && range1;`로, 채널 2를 뺀 뒤의 `bad = range1;`을 `bad = range1 && range2;`로 바꿔도 test가 통과한다. "뺀 채널이 범위 안으로 돌아왔는데 남은 채널이 실패한다"를 보는 test가 없다 (`tc_022`는 뺀 채널도 계속 범위 밖인 입력만 쓴다). (b) 채널 하나의 범위 실패를 `single`로 세는 조건에 "다른 채널의 페달 값이 0보다 큼"을 더해도 통과한다 (`range1 && !range2 && (p2 > 0)`, 채널 2도 같다). 다른 채널이 페달을 놓은 값 (p = 0)일 때 한 채널이 단선되는 경우를 보는 test가 없다. 이때 실제 코드는 줄여 감으로 가지만 변이는 페달 고장으로 간다. 뺀 채널의 범위를 계속 본다 (`bad = range2 || range1`)와 두 채널이 모두 범위 밖일 때를 `single`로 세지 않는다는 쪽은 잡힌다 (변이 51 - 54번). 빼기만 하고 남은 채널을 보지 않는 변이 (`bad = false`)도 잡힌다.
- 확인: 내 변이 67번, 69번과 `mymut3.py`의 0번, 1번 (표 참조). `make test`가 통과한다.
- 고칠 방법: `tc_022`에 (a) 채널 1을 뺀 뒤 채널 1은 정상 범위로 돌아오고 채널 2가 2400 mV를 3번 (채널 2를 뺀 뒤도 같게), (b) 페달을 놓은 값 (apps1 500 mV, apps2 250 mV)에서 한 채널이 0 V를 3번 (채널 1, 2 모두)을 더한다.

E-07 [C] 연결 (wiring)을 보는 test가 모자란 곳 셋. 모두 놓친 변이다.
- (a) `vcu.c`의 `inverter_check_record(&vcu->inverter_check, vcu->torque_out)`을 `vcu->torque_req`로 바꿔도 통과한다 (변이 57번). 정상일 때는 요구와 보낸 값이 같다. 기능이 틀려 출력 단계가 깎는 주기에만 기록이 달라지고, 그때 inverter까지 틀려야 (fault 둘) 차이가 드러난다. 지난 묶음의 "감시에 브레이크를 넘기지 않는다"와 같은 종류다. 고침: 기능의 결함과 inverter가 더 내는 결함 (`FI-21`)을 함께 넣은 시나리오를 더하거나, 연결을 unit 수준에서 보는 test를 더한다.
- (b) `diag.inverter_out_cycles`의 출처를 `out_cycles`에서 `invalid_cycles`로 바꿔도 통과한다 (변이 54번). `TC-123`은 이 값의 최댓값을 `CHECK(worst < 3)`으로만 보고, 문서의 표 (0, 1, 2)는 `printf`로만 나온다. 문서에 적힌 숫자가 test의 판정이 아니다. 고침: 표의 가장 나쁜 경우 (+10 Nm, 한 주기 묵음)에 대해 `CHECK_EQ(worst, 2)`를 둔다.
- (c) `e2e_rx_init`의 `ok`를 `true`로 바꿔도 통과한다 (변이 19번). 제품의 연결에서는 첫 호출에서 `seen`이 거짓이라 같다. 그러나 `seen`이 참이고 `fresh`가 거짓인 첫 호출 (이론상의 경우)의 결과가 다르다. 성질 10의 "라" 와 "마"는 이것을 모든 상태에서 같은 규칙으로 말하지만 초기값은 보지 않는다. 고침: unit test에 "init 직후 `seen`, `!fresh`, `age 0`이면 거짓"을 한 줄 더한다.

E-08 [C] `SWR-20`의 "task table과 같은지"는 table과 이어져 있지 않다.
- 파일: `src/flow/flow.h` (`FLOW_TASK_COUNT`, `FLOW_MARK_*`), `src/vcu/vcu.c` (`vcu_task_table`, 4개).
- 문제: 문장은 표시의 순서와 수가 "task table과 같은지" 확인한다고 하는데, 코드는 상수 3과 1, 2, 3을 따로 가진다. table에는 task가 넷이고 (표시를 남기지 않는 `flow`가 하나 더 있다) 그 "3 = 4 - 1"을 이어 주는 것이 없다. 누가 task를 더하고 table에만 넣으면 모든 주기에 표시가 모자라 watchdog이 끊는다 (안전한 쪽). 표시를 남기는 task를 더하고 table에만 넣지 않으면 반대다. test는 `vcu_task_count`를 어디서도 `FLOW_TASK_COUNT`와 견주지 않는다 (grep으로 확인).
- 고침: `vcu.c`에 `_Static_assert`가 안 되므로 (table이 `const` 배열) unit test에서 `vcu_task_count == FLOW_TASK_COUNT + 1`을 한 줄 `CHECK`한다. 또는 문장을 "task마다 정해진 표시 (1, 2, 3)"으로 고친다.

E-09 [C] 작은 서술의 어긋남 넷.
- `src/hal/hal.h`의 `hal_diag_t.latched`: 주석은 "기능의 고장으로 고정했는가"인데, `vcu.c`는 구동 허용 차단 상태 (`state == REACTION_CUT`)면 원인에 상관없이 참으로 쓴다 (되읽기, inverter의 검사, watchdog이 끊은 것도 포함). `TC-115`, `TC-120`, `TC-121`이 이 값으로 차단을 판정한다. 주석을 "구동 허용 차단 상태인가"로 고친다.
- `docs/hsi.md` 3절의 토크 요구의 범위 "-1000 - 2500": 감시의 상한은 후진에서 105 Nm (`SWR-06`, 성질 1)이므로 틀린 기능이 깎여 나가면 -1050까지 나간다. 정상인 기능은 -1000까지다. "받는 쪽이 검사할 범위"로 읽히면 안 맞는다. -1050 - 2500으로 고치거나 "정상 운전에서"를 붙인다.
- `src/com/e2e.c`의 "16을 먼저 더해 뺄셈이 음수가 되지 않게 한다": 식 전체가 부호 없는 형 (`+ 16u` 이후)이므로 `+ 16u`를 빼도 결과가 같다 (내 변이 21번이 이것을 확인했다). 무해하나 이유가 틀렸다. "부호 없는 계산이라 0 아래로 돌아도 mod 16이 같다"로 바꾸거나 `+ 16u`를 뺀다.
- `TC-124`의 한계 (`worst_trip_ms <= 16`, `worst_off_ms <= 77`)는 `technical-safety-concept.md` 9.4절의 예산 (창 15 ms, 합 76 ms)보다 1 ms 넉넉하다. 잰 값 (15, 73)은 예산 안이므로 지금은 문제가 없지만, test가 예산이 아니라 예산 + 1을 지킨다. 예산을 76으로 쓸 거면 test도 76.

E-10 [C] `tools/mutation_check.py`는 test가 끝나지 않으면 끝나지 않는다.
- 파일: `tools/mutation_check.py`의 `subprocess.run(["make", "-s", "test"], ...)` (timeout 없음).
- 문제: 반복문을 끝없이 돌게 하는 변이는 test를 멈추게 하고 도구도 멈춘다. 그 변이는 "잡았다"가 되어야 한다 (test가 끝나지 않는 것은 실패다).
- 확인: `flow_init`의 `for` 반복에서 `i++`를 뺀 (volatile로 compile 경고를 피한) 변이 하나를 `make test`로 돌리면 60초 뒤에도 끝나지 않는다 (`hang/`, `timeout 60`이 124를 냈다). 도구는 읽어서 확인했고 `mutation_check.py` 자체를 그 변이로 돌려 보지는 않았다.
- 고침: `subprocess.run(..., timeout=300)`과 `TimeoutExpired`를 "잡음 (끝나지 않음)"으로 센다.

찾지 못한 것 (확인했고 문제가 없었다)
- 요구사항 문장 `SWR-16`, `SWR-17`, `SWR-18`, `SWR-19`, `SWR-20`, `SWR-21`의 숫자 (50 ms, 1-3, 50주기, 30 Nm, 3번/10번, 5주기, 138/139)는 코드와 같다. 5 km/h는 138까지가 "아래"다 (139는 1.39 m/s로 5.004 km/h).
- `SWR-16`의 "크기가 5 km/h 아래"에서 코드는 음수 속도를 받아들이지 않는다 (`speed >= 0`). hal.h가 속도를 크기로 정의하므로 방어일 뿐이다. 성질 12가 이것을 단언한다 (E 항목 없음).
- sim 쪽의 CRC와 제품의 CRC가 400만 메시지에서 한 번도 다르지 않았다. 문서의 "따로 쓴 두 구현"이 같은 규칙으로 맞는다.
- 모든 test가 ASan/UBSan을 지난다. 제품 코드에 정수 변환의 넘침, 배열 경계의 위반, 초기화 누락은 찾지 못했다 (`scenario_run`의 `vcu_t vcu;`는 초기화 안 된 stack인데, `vcu_init` 하나를 빼는 변이 셋을 0xA5로 채운 stack으로도 돌려 보았고, 첫 주기에 상태가 덮이거나 값이 무관하게 되어 통과한다. 동등에 가깝다. E 항목으로 세지 않는다).

## 놓친 변이

내가 고른 변이 (`tools/mymut.py`, `mymut2.py`, `mymut3.py`, 복사본에서 `make test`). 목록 (`MUTANTS`, 상수 +1)에 없는 것이다. 93개를 넣었고, compile되지 않은 2개 (`INVERTER_HISTORY_CYCLES`를 4로 하면 test의 고정 인덱스가 -Warray-bounds에 걸림, `!st->synced && !st->ok ||`의 괄호 경고)와 아무것도 바꾸지 않은 대조 1개를 빼면 90개다. 65개를 잡고 25개를 놓쳤다 (`mymut.py` 73개, `mymut2.py` 16개, `mymut3.py` 4개).

| 갈래 | 개수 |
|---|---|
| 잡음 | 65 |
| 놓침, 동등 (코드가 같은 일을 함) | 14 |
| 놓침, 첫 주기에 덮여 test로 보이지 않는 초기화 누락 (동등에 가깝다) | 3 |
| 놓침, 보호가 겹쳐서 (동등) | 1 |
| 놓침, test의 구멍 | 7 |

넣은 변이의 갈래 (대략): 상수를 1 내림 17개 (하나는 compile 안 됨) (`E2E_MAX_STEP`, `E2E_TIMEOUT_MS`, `INVERTER_*`, `GEAR_*`, `LIMP_*`, `PEDAL_*`, 센서 범위 4개)와 경계 (`>`/`>=`) 6개, 초기값 7개, 순서 바꾸기 4개, 조건 하나 빼기/더하기 30여 개, 넘침 처리 5개.

놓친 25개:

| 번호 | 파일, 변이 | 판정 | 까닭 |
|---|---|---|---|
| 19 | `e2e.c`: `e2e_rx_init`에서 `ok = true` | test의 구멍 (C) | E-07 (c) |
| 20 | `e2e.c`: `e2e_rx_init`에서 `last_counter = 7` | 동등 | `synced`가 거짓이면 쓰이지 않는다 |
| 21 | `e2e.c`: `+ 16u`를 `+ 0u`로 | 동등 | 부호 없는 계산이라 같다 (E-09) |
| 28 | `e2e.c`: `e2e_protect`에서 counter를 mask하지 않음 | 동등 (정상 상태에서) | `tx.counter`는 늘 0-15다. 망가진 상태에서는 다르고, 증명 (성질 10)이 이것을 잡는다 (증명 변이 3번, 실패) |
| 32 | `gear_check.c`: `caution = (>=50) && rejected` | 동등 | `reject_cycles >= 50`이면 이번 주기에도 받아들이지 못한 것이다 |
| 38 | `inverter_check.c`: `bounded`의 `r > MAX`를 `>=`로 | 동등 | 같은 값으로 자른다 |
| 39 | `inverter_check.c`: `pos++` 뒤에 바로 처음으로 돌림 | 동등 | 다음 호출의 검사와 같다 |
| 40 | `inverter_check.c`: init에서 `pos = 2` | 동등 | 기록이 모두 0이므로 시작 자리는 상관없다 |
| 41 | `flow.c`: 반복문 안의 `& 0xFFu`를 뺌 | 동등 | 부호 없는 32 bit 계산의 아래 8 bit는 같다 |
| 49 | `vcu.c`: `gear_check_init` 호출을 뺌 | 첫 주기에 덮임 | 시작 때 기어가 P라서 `reject_cycles`가 0으로 돌아간다 |
| 50 | `vcu.c`: `inverter_check_init` 호출을 뺌 | 첫 주기에 덮임 | 첫 주기에 상태 메시지가 유효하여 `out_cycles`가 지워진다 |
| 51 | `vcu.c`: `e2e_tx_init` 호출을 뺌 | 첫 주기에 덮임 | inverter가 처음 메시지는 counter를 견주지 않는다 |
| 54 | `vcu.c`: `diag.inverter_out_cycles`를 `invalid_cycles`로 | test의 구멍 (C) | E-07 (b) |
| 57 | `vcu.c`: `inverter_check_record`에 `torque_req`를 줌 | test의 구멍 (C) | E-07 (a) |
| 58 | `vcu.c`: 되읽기를 `input_read` 뒤로 옮김 | 동등 | 서로 다른 변수만 만진다 |
| 60 | `vcu.c`: `ok \|\| (count == 2)` | 동등 | 표시가 둘이면 답이 틀려 watchdog이 끊는다. 실제 구멍은 `ok \|\| !ok` (E-02) |
| 66 | `pedal_check.c`: `to_permille`의 `mv <= min`을 `<`로 | 동등 | 경계에서 0이다 |
| 67 | `pedal_check.c`: 채널 2를 뺀 뒤 `bad = range1 && range2` | test의 구멍 (C) | E-06 (a) |
| 69 | `pedal_check.c`: 채널 2의 `single`에 `(p1 > 0)`를 더함 | test의 구멍 (C) | E-06 (b) |
| c0 | `pedal_check.c`: 채널 1을 뺀 뒤 `bad = range2 && range1` | test의 구멍 (C) | E-06 (a) |
| c1 | `pedal_check.c`: 채널 1의 `single`에 `(p2 > 0)`를 더함 | test의 구멍 (C) | E-06 (b) |
| 70 | `app.c`: `target < -limit + 1`을 `-limit`로 자르는 조건에 | 동등 | 같은 값 |
| 71 | `monitor.c`: `allowed >= TORQUE_MAX` | 동등 | 같은 값 |
| b4 | `monitor.c`: `monitor_apply_cap`과 `monitor_limit_rise`의 순서 바꿈 | 동등 | 둘 다 `min`이라 교환된다 |
| b13 | `pedal_check.c`: 고장 뒤에는 기록에 쓰지 않음 | 동등 | 고장은 풀리지 않고 출력이 0이다 |

(번호는 `mymut.py`의 순서다. b4와 b13은 `mymut2.py`의 4번과 13번, c0과 c1은 `mymut3.py`의 0번과 1번이다.)

잡은 것 가운데 눈에 띄는 것 (지난 묶음에서는 놓쳤을 만한 종류): `E2E_MAX_STEP`, `E2E_TIMEOUT_MS`, `GEAR_CHANGE_SPEED_MAX`, `INVERTER_TORQUE_MARGIN`을 1 내린 것 모두, 경계 (`<` -> `<=`, `>` -> `>=`) 모두, 센서 범위 4개를 1 내린 것 모두, `inverter_check_step`을 출력 단계 뒤로 옮긴 것, 받아들이지 못한 방향을 기억하는 것, 기억한 방향을 P나 N에서 지우는 것, 무효인 주기가 벗어난 횟수를 지우는 것, 유효한 주기가 무효 횟수를 1씩만 줄이는 것.

## 증명의 점검

| 점검 | 방법 | 결과 |
|---|---|---|
| assume이 성질을 비우지 않는가 | 14개 증명 함수 끝에 `assert(0 && "REACHED")`를 넣고 `cbmc`를 돌림 | 14개 모두 그 assert가 FAILURE (닿는다). 성질이 비어 있지 않다 |
| 주석이 말하는 것 | 성질 4, 6, 10 - 14의 assert를 주석과 견줌 | 주석과 assert가 맞는다. 단 성질 14의 "배열 밖" (E-01). 성질 12는 "주의는 50번 이어진 때에만"을 단언하고, "50번 이어지면 주의를 요청한다"는 반대쪽은 단언하지 않는다. 그 쪽은 test가 본다 (변이 116번 "받아들이지 못한 주기를 세지 않는다"는 증명이 아니라 test가 잡는다) |
| 제품 코드를 바꾸면 실패하는가 | 28개를 바꿔 해당 성질을 돌림 (`tools/pmut.py`) | 26개에서 실패. `MAX_STEP` 2/4, `TIMEOUT` 51, `tx counter unmasked`, CRC에서 counter/data ID를 뺌, CRC가 틀린 메시지가 기준을 바꿈, `GEAR` 140, `WARN` 51, 음수 속도 허용, `MARGIN` 299/301, `OUT_CYCLES` 4, `bounded`에서 위쪽 자르기 빼기, 유효한 주기가 `invalid`를 지우지 않음, `pos` 범위 한 칸 어긋남, 답의 곱셈 상수 33, 음수 쪽 초과를 안 봄, `flow_next`가 표시를 안 지움, `MAX_BAD` 11, `window_pos` 범위 한 칸 어긋남, 다른 채널을 뺌, `LIMP_APP` 349/400, `LIMP_CAP` 340, 줄여 감의 기능 상한을 뺌 |
| 못 잡은 둘 | 위와 같음 | (1) `flow_mark`의 범위 검사 `<=` (E-01). (2) 채널 1을 뺀 뒤 `bad = false` (성질 4는 이 경우의 "남은 채널의 실패가 고장으로 이어진다"를 말하지 않는다. test `TC-022`가 본다. 문서도 이것을 증명했다고 하지 않는다) |

`LIMP_APP` 349도 성질 6이 실패한다. 틈이 5 Nm보다 커져서다. 문서의 "상수가 어긋나면 실패한다" (test-report 207줄)가 줄여 감의 두 상수에도 맞는다.

## 무작위 실험

새 모듈마다 요구사항의 문장대로 따로 쓴 모델 (C, `rnd/rand.c`)과 제품 함수를 같은 입력으로 돌려 견주었다. `-fsanitize=address,undefined`로 compile했다. 시작값이 다른 7번 (40만 걸음 3번, 100만 걸음 4번)을 합친 횟수다.

| 대상 | 입력 | 걸음 수 | 어긋남 |
|---|---|---|---|
| `e2e_check` (data ID 66과 99 각각) | 옳은 메시지 (+1), 건너뜀 (+2 - +4), 되풀이, 임의의 counter, 값의 bit 반전 (32 bit 가운데 하나), CRC bit 반전, counter 바꿈, 다른 종류, 극단값 (INT_MIN, INT_MAX 근처), 새 메시지 없음, 받은 적 없음, 시간 초과 (50, 51 ms 경계 포함), 상태 초기화 | 각 520만 | 0 |
| `e2e_protect` + sim의 CRC | 무작위 data ID, 값 (극단값 포함), 중간 초기화 | 520만 | 0 |
| `gear_check_step` | 기어 (0 - 3, 7, -1), 속도 유효/무효, 속도 {-1, 0, 1, 50, 100, 137, 138, 139, 140, 141, 5000, INT_MIN, INT_MAX}. 50번 넘게 받아들이지 못하는 구간 포함 (주의 약 31만 주기) | 520만 | 0 |
| `inverter_check_step` + `record` | 보낸 토크 (-1050 .. 2500, 극단 구간), 알린 토크 (경계 +-300, 범위 밖, INT_MAX/MIN), 유효/무효 (무효 9번에 유효 1번 포함) | 520만 (판정 참 약 55만 주기) | 0 |
| `pedal_check_step` | 정상 페달 + 잡음, 채널 한쪽이 범위의 경계 (249/250, 124/125, 4749/4750, 2374/2375), 불일치, 채널 중 하나만 단선, 극단값 (INT_MAX, INT_MIN), 90주기마다 초기화 | 약 400만 (뒷 4번), 앞 3번은 초기화가 덜 잦았음 | 0 (모델을 고친 뒤) |
| `flow_*` | 표시 0 - 5개, 값을 무작위로 어긋남, 허용 토크와 보낸 토크 (극단값 포함) | 520만 | 0 |
| 닫힌 고리, 고장 없음 (`rnd/rand2.c`) | 운전자의 입력 (30 ms - 800 ms 간격, 또는 1 - 40 ms 간격), 기어 P/R/N/D 무작위, 15초 | 600번 (900만 ms) | 0. 위반한 불변식 없음: 토크 <= 허용 토크, watchdog 끊김 0, 고정 0, 깎음 0, 경고 0, 구동 허용 꺼짐 0 |
| 닫힌 고리, 고장 있음 | 고장 1 - 3개 (23종 가운데 무작위, 시각 200 ms - 12 s, 인자 무작위), 15초 | 1500번 (2250만 ms) | 0. 불변식: 토크 <= 허용 토크 (task 고장이 없을 때), 고정은 풀리지 않음, 고정이면 토크 0과 구동 허용 꺼짐, watchdog이 끊으면 25 ms 안에 고정 |

어긋남은 제품과 문서에서 찾지 못했다. 처음의 어긋남 둘은 내 모델의 오류였다. (1) 페달의 모델이 고장 뒤에도 연속 실패를 따라가서 고장 뒤에 채널을 빼는 것으로 보았다. 고장이 이미 걸렸으므로 의미가 없고 모델을 고쳤다. (2) 극단값을 만들 때 내 코드의 signed overflow (UBSan이 잡음).

## 결과의 해석과 확인하지 못한 것

- 변이 검사와 test는 이 묶음에서 지난 번보다 눈에 띄게 단단하다. 내가 넣은 90개 가운데 진짜 구멍은 일곱 (모두 C)이고, 반드시 고칠 것으로 볼 만한 것은 증명 서술 하나다 (E-01).
- 이 검토에서 확인하지 못한 것: (1) 실제 MCU의 동작, 실행 시간, stack. (2) `hsi.md`와 `hardware-assumptions.md`의 하드웨어 칸 (회로가 없어 확인할 수 없다). (3) 5장 이후의 장. (4) CBMC의 다른 버전에서 E-01의 한계가 같은지 (6.11.0만 썼다). (5) `fmea.md`, `stpa.md`, `dfa.md`, `fta.md`의 바뀐 부분. (6) 시나리오 test 전부를 한 줄씩 읽지는 않았다. 읽은 것은 위에 적은 것뿐이고, 나머지는 fault를 빼는 실험과 변이로 보았다. (7) `make check STRICT=1` 전체 (추적 단계만).
- sim이 제품에 유리한 곳. 이 가운데 문서에 이미 적힌 것 ("하지 않은 것" 8절)을 빼고 내가 확인한 것: 메시지가 주기마다 정확히 하나 (`fresh`가 늘 참), 지연 없이 같은 ms에 닿고 (`age = 0`), watchdog에 답하는 시각이 늘 10 ms 간격이다. 그래서 `e2e_check`의 "새 메시지 없음" 경로, 창의 아래쪽 (5 ms), 두 메시지가 한 주기에 오는 경우는 fault로만 만든다. 이것으로 test가 틀린 판정을 낸 곳은 찾지 못했다 (무작위 실험은 이 경로를 모델과 견주어 맞았다).
- 구동 허용 신호의 선 (`hal_sim.c`의 `enable_wire`)과 watchdog의 model (`hal_sim.c`)은 `hsi.md`와 TSC 9.5절 (`A-14` 2 ms, `A-15` 1 ms, `A-17` 50 ms, `A-24` 5 - 15 ms)이 적은 대로다. 첫 답 전에 선을 막는 것, 끊은 뒤 풀지 않는 것, 창의 아래와 위, 답의 식 (`q * 29791 + 1026`)이 모두 그렇다. 되읽기는 sim에서 지연 없이 (`enable_wire()`) 읽는다. `hsi.md`는 "지난 주기에 쓴 값이 닿아 있다 (A-15: 1 ms)"라고 적었으므로 10 ms 간격에서는 같은 결과다.
- 대조 test (NC-001 - NC-005): 같은 시나리오로 대응하는 요구사항의 test (FI-02, FI-17, FI-13/14, FI-21, FI-23)와 입력이 같다 (NC-005와 TC-124를 소스에서 견주었다). 수단을 뺀 모듈로 바꿔 끼워 어김을 보인다. NC-002, NC-004, NC-005는 fault를 빼면 실패한다 (fault가 판정에 쓰인다). NC-001과 NC-003은 fault가 모듈이나 운전자의 입력이어서 sim의 fault를 빼도 같다 (의도한 대로다).

## 판정

판정: 조건부 통과.

까닭: 숫자와 요구사항의 숫자는 모두 맞고, 무작위 실험과 변이 90개와 sanitizer가 제품 코드에서 틀린 결과를 찾지 못했다. 반드시 고칠 것은 서술 하나다 (E-01: 증명이 "배열 밖에 쓰지 않는다"고 말한다. 성질 14에서는 사실이 아니고, 변이로 재현된다). 고치는 것이 좋은 것은 넷이다. 둘은 test가 fault 없이도 통과하는 것 (E-03, E-04), 하나는 동등하다고 따로 둔 변이가 실제로는 구멍인 것 (E-02), 하나는 `SWR-24`가 코드의 35 Nm 상한을 말하지 않는 것 (E-05). 나머지는 C다. A 하나를 고치고 B 넷을 반영하거나 이유를 적어 받지 않으면 통과로 본다.
