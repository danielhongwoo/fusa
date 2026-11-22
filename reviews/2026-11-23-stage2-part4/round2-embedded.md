# 2차 확인: 임베디드 소프트웨어 엔지니어 (단계 2 묶음 4, 1차 지적 E-01 - E-08의 반영)

검토자: 임베디드 소프트웨어 엔지니어 역할 (Sonnet 5.5). 날짜 2026-11-23. 기준 commit 213e3cd (`git archive`로 꺼낸 복사본에서만 돌렸다. 작업 폴더는 읽지도 고치지도 않았다).

## 돌린 것

| 무엇 | 결과 |
|---|---|
| `make check` (복사본) | 통과 (1분). test 26, 32, 9, 2, 1, 2, 1개 (검사 5672, 578, 139, 15, 5, 18, 5), `TC-` 65개, 변형 다섯 (O2, Os, gcc-O0, gcc-O2, sanitizer) 모두 출력이 -O0과 같다, coverage 100%, 증명 14개 |
| `make step-check` | 12가지 가운데 12가지 "알림" (46초) |
| `make proof-mutation` | 이번에는 돌리지 않았다 (증명의 변이 9개는 1차에 이미 확인했고 harness의 바뀐 곳은 가정 넷을 지운 것뿐이다). 대신 아래 4번의 가정 점검을 했다 |
| 전체 `make mutation` | 돌리지 않았다. `MUTANTS` 186 + 상수 49 = 235가 test-report와 맞다 |

## 1차 지적의 확인

| 지적 | 판정 | 확인한 방법 |
|---|---|---|
| E-01 [A] coverage 단계가 실패를 덮음 | 닫힘 | `vcu.c`의 `task_input`에 test가 닿지 않는 문장 (`if (vcu->speed == 7654321) {...}`)을 더한 복사본에서 `make coverage`와 `make check`가 모두 종료 코드 2로 끝난다 ("coverage: ... 100%에 못 미친다: src/vcu/vcu.c"). `coverage.sh`는 `|| status=$?`로 상태를 넘긴다. 이 단계가 `step-check`의 한 가지로 들어 있다 |
| E-02 [B] "여덟 가운데 넷" | 닫힘 | tools.md 3절의 표를 줄마다 센다: 검토자 7 (1, 4, 5, 6, 11, 12, 13), 만든 쪽 4 (2, 7, 8, 9), 원고를 쓰던 에이전트 1 (10), 도구 자신 1 (3). 합 13. 17장의 문단 (열셋, 만든 쪽 넷, 일곱, 하나, 하나)과 맞고, "나머지 아홉은 만든 쪽의 확인으로는 드러나지 않았다"도 표와 맞는다 |
| E-03 [B] 초기화를 빠뜨림 | 닫힘 (아래 3절) | 내가 고른 변이 26개가 모두 잡힌다. 0xA5와 0x00 둘로 못 잡는 필드는 찾지 못했다 |
| E-04 [C] 필요 없는 가정 넷 | 닫힘 | harness의 가정은 이제 13개다. 하나씩 지워 해당 성질을 CBMC로 다시 돌리면 13개 모두 실패한다 (지우면 안 된다). 필요 없는 것이 남아 있지 않다. `make check`의 증명 14개는 그대로 성립한다 |
| E-05 [C] clang-tidy가 말없이 죽음 | 닫힘 | `make static CLANG_TIDY=false` -> "clang-tidy: 경고 0 개"에 이어 "clang-tidy: 실패 (종료 상태 1)", 종료 코드 2. clang-tidy만 경고하는 코드도 실패한다 |
| E-06 [C] GCC로 도는 test | 닫힘 | `variants.sh`가 GCC의 `-O0`과 `-O2`를 `make test`의 일곱 실행 파일로 돌리고 출력을 Apple clang의 `-O0`과 견준다. `make check`에서 둘 다 "한 줄도 다르지 않다". GCC가 없으면 "건너뜀"을 `build/skipped`에 적는다 |
| E-07 [C] tools.md에 빠진 것 | 닫힘 | 1절, 2절에 빌드를 묶는 글이 들어 있다. 4절에 target의 정수 폭과 배치 (`int` 32 bit, `size_t` 64 bit, little endian)와 초기화하지 않은 변수를 보는 도구 (MemorySanitizer, valgrind)가 있다 |
| E-08 [C] 변형의 UBSan | 닫힘 | `variants.sh` 머리의 설명이 "배열 밖은 AddressSanitizer가 본다. 구조체의 끝에 있는 배열은 UBSan이 이 설정에서 알리지 않는다"로 고쳐졌다. option은 더하지 않았다 |

## 3. TC-023, TC-133과 초기화 변이

진행자의 변이 14개 밖에서 26개를 골랐다 (`im.py`): `vcu_init`의 줄 19개 (`speed_valid`, `speed`, `inverter_valid`, `inverter_torque`, `pedal_safe`, `torque_req`, `torque_allowed`, `torque_out`, `enable`, `warning`, `hal_enable_write`, `speed_rx`와 `torque_tx`의 init, `flow_init`, `output_stage_init`, `pedal_check_init`, `brake_check_init`, `gear_check_init`, `inverter_check_init`), 그리고 각 init 안의 줄 (브레이크의 `pressed`와 `fault`, 페달의 `bad_cycles`와 `good_cycles`, `window_pos`, `suspect`, `excluded`, 기록 비우기, 기어의 `reject_cycles`와 `caution`, inverter의 `sent` 비우기와 `invalid_cycles`, 출력 단계의 `excess_cycles`와 `clamp_count`, 표시 비우기, `e2e_rx`의 `last_counter`와 `synced`, `ok`). 모두 test가 값으로 실패를 찍었다 (대부분 `TC-133` 또는 `TC-023`, 몇은 `TC-101`이나 `TC-108`). 컴파일 오류는 둘 (init의 본문을 모두 지워 인자가 쓰이지 않는 것)이었고 변이로 세지 않았다.

- 0x00으로 채운 상태는 참이나 0이 아닌 값으로 정해야 하는 필드 (`brake.pressed`, `gear.direction`)를, 0xA5는 0으로 정해야 하는 필드를 드러낸다. 두 값을 모두 쓰므로 한 값에만 맞는 필드는 걸린다. 두 값으로 못 잡는 필드는 찾지 못했다.
- 한계 (지적으로 세지 않는다): `init_state_is_defined`는 필드를 손으로 하나씩 단언한다. 구조체에 필드를 더하고 init에도 test에도 쓰지 않으면 이 test는 알리지 않는다. 제안 하나: 두 쓰레기 값 (0xA5, 0x00)으로 채운 뒤 init한 결과가 byte 단위로 같은지를 본다 (padding은 비교에서 뺀다). 모든 필드가 정해졌는지를 필드 목록 없이 보게 된다. 내가 필드를 더해 본 실험은 그 필드가 동작에 쓰이는 경우여서 다른 test가 잡았고, 쓰이지 않는 필드로는 확인하지 못했다.

## 5. `make step-check`

12가지를 하나씩 복사본에서 손으로 돌려 실제 까닭을 읽었다. 모두 의도한 까닭으로 실패했다.

| 경우 | 실패한 까닭 |
|---|---|
| test: 알 수 없는 기어를 D로 | `TC-107` 실패 |
| variants: `__OPTIMIZE__`에만 드러나는 결함 | 변형 O2, Os, gcc-O2, sanitizer가 "test가 실패했다" |
| trace: 없는 ID | "문제  SWR-99: 코드에 있지만 요구사항 파일에 없다" |
| static: cppcheck | `knownConditionTrueFalse` 지적 |
| static: clang-tidy만 | "경고 1 개", app.c의 지적, "실패 (종료 상태 0)" |
| static: clang-tidy가 말없이 죽음 | "경고 0 개" 다음에 "실패 (종료 상태 1)" |
| coverage: 닿지 않는 문장 | "100%에 못 미친다: src/vcu/vcu.c" |
| prove: 배열 바로 뒤 | "실패    prove_flow", `VERIFICATION FAILED` |
| 도구가 없다 (cbmc, GCC, cppcheck, clang-tidy) | 각각의 "건너뜀"과 "건너뛴 단계가 있다", 종료 코드 2 (`skipped`가 실패) |

도구의 기준 (결함 없는 복사본에서 단계가 통과해야 한다)은 `test`, `trace`, `static`만 확인한다. 나머지 단계 (`variants`, `coverage`, `prove`, `skipped`)가 결함이 없을 때 통과하는지는 내가 따로 돌려 통과를 확인했다 (모두 종료 코드 0).

## 6. `mutation_check.py`의 timeout

맞다. `start_new_session=True`로 process group을 만들고, 시간이 지나면 `os.killpg(..., SIGKILL)`로 `make`와 그 아래의 test 실행 파일을 함께 끝낸다. 확인: `flow_init`에 끝나지 않는 반복을 넣은 복사본에서 `run_tests`를 25초 시간 한계로 돌렸다. 결과 (종료 상태 1, 끝나지 않음 True, 25초). 그 뒤 해당 복사본의 build 아래의 프로세스가 하나도 남지 않았다 (1차의 stack에 남은 프로세스가 없다). 잡은 방식의 구분 (`^실패  ` 줄이 있으면 값, 시간이 지났으면 "끝나지 않음", 줄이 없으면 "죽음")도 읽어서 확인했다. 시간이 지난 것을 먼저 가르므로 "값으로 실패를 찍은 뒤 끝나지 않는" 경우도 "끝나지 않음"으로 센다 (1차에서 우려한 stack 덮어쓰기). 실패를 찍은 뒤 죽는 경우는 "값"으로 센다. 값이 이미 잡았으므로 문제는 아니다.

## 숫자의 대조

| 항목 | 문서 | 실행 결과 | 일치 |
|---|---|---|---|
| `TC-` test | 65개 | 65개 | 예 |
| 변이 | 235 (손으로 186 + 상수 49), test 231 + build 4 | 186 + 49 (실행하지 않음) | 예 |
| 단계의 확인 | 12가지 모두 알림 | 12 / 12 | 예 |
| 변형 | 다섯 모두 출력이 같다 | 같다 | 예 |
| 13장, 16장, 17장 표의 수 | 16장 235 = 231 + 4, 17장 열셋 | 맞다 | 예 |

## 새 지적

E-09 [C] `step_check.py`는 단계가 실패한 까닭을 보지 않는다. 지금의 12가지는 의도한 까닭으로 실패하지만 (위 5절), 도구가 그것을 보증하지는 않는다.
- 파일: `tools/step_check.py`의 `run`과 `main`.
- 문제: (1) 종료 코드가 0이 아니면 무엇이든 "알림"이다. 바뀐 곳을 찾았더라도 compile 오류나 도구의 설정 오류로 실패하면 같은 판정이다. 출력은 `DEVNULL`로 버려서 나중에 까닭을 볼 수도 없다. (2) 시간 한계에 걸리면 `run`이 1을 돌려주어 "알림"이 된다. 끝나지 않는 단계가 "실패를 알렸다"로 센다. (3) 결함이 없는 복사본에서 단계가 통과하는지 보는 기준이 `test`, `trace`, `static` 셋뿐이다. `variants`, `coverage`, `prove`, `skipped`가 원래 실패하는 컴퓨터에서는 그 경우들이 결함과 무관하게 "알림"이 된다 (예: cppcheck가 없는 컴퓨터에서는 "도구가 없다: cbmc"도 cppcheck의 건너뜀 때문에 실패한다).
- 1차에서 이 묶음의 주제 ("단계가 있다는 것과 실패를 알린다는 것은 다른 일")를 이 도구 자신에게 한 단계 더 적용한 것이다. 지금은 사람이 읽어 확인했다.
- 고칠 방법: 경우마다 기대하는 글 한 줄 (예: "100%에 못 미친다", "SWR-99")을 적어 두고 출력에 그 글이 있을 때만 "알림"으로 센다. 시간 한계는 따로 "끝나지 않음"으로 센다. 기준은 단계 전부에 한 번씩 돌린다.

## 판정

판정: 통과.

까닭: 1차의 지적 여덟은 모두 닫혔다. 가장 무거운 E-01은 닿지 않는 문장을 넣어 직접 실패하는 것을 확인했고 (두 파일 묶음에서 같은 모양이 다시 나오지 않는다. `step-check`가 그것을 지킨다), E-02는 표와 17장의 수가 맞고, E-03은 내가 고른 초기화 변이 26개를 모두 잡는다. 새 지적은 C 하나이고 도구의 확인을 더 엄밀하게 하자는 것이어서 통과에 영향이 없다. 새로 만든 `step-check`는 열두 경우 모두에서 의도한 까닭으로 실패하는 것을 확인했다. 확인하지 못한 것: 전체 `make mutation`과 `make proof-mutation` (이번에는 다시 돌리지 않았다), 원고가 인용한 외부 문서.
