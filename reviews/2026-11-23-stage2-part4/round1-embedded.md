# 1차 검토: 임베디드 소프트웨어 엔지니어 (단계 2 묶음 4: 도구, 15 - 17장)

검토자: 임베디드 소프트웨어 엔지니어 역할 (Sonnet 5.5). 날짜 2026-11-23. 기준 commit 1a059b5. 다른 검토자의 의견은 보지 않았다.
저장소는 고치지 않았다. 모든 실험은 scratchpad (`p4/`)의 복사본에서 했다.

## 읽은 것

- `reviews/2026-11-23-stage2-part3/round3-integration.md`, 지난 묶음의 `round2-embedded.md`.
- `git diff 6146681..HEAD -- example/drive-torque`: `docs/tools.md` (전부), `tools/variants.sh`, `Makefile`의 `variants`와 `static`, `test/proof/harness.c`의 성질 7, `docs/test-report.md`의 바뀐 곳.
- 묶음 3의 2차 지적의 반영: `flow.c`, `pedal_check.c`, `inverter_check.c`의 `_Static_assert`, `tools/mutation_check.py`의 `BUILD_CAUGHT`, `tools/prove.sh`, `tools/proof_mutation.py`, `tools/coverage.sh`, `tools/coverage_summary.py`.
- 원고: `ch15-verification-strategy.md` (절 전부), `ch16-testing.md` (2절, 5절, 예제 절, sim 절), `ch17-tools-and-existing-software.md` (예제 절, sim 절). 외부 문서를 인용한 문장 (CPROVER Manual, tutorial의 쪽)은 확인하지 않았다. 예제와 도구의 동작을 말한 문장만 보았다.

## 돌린 것과 결과

| 무엇 | 결과 |
|---|---|
| `make check` (복사본) | 통과 (50초). test 25, 31, 9, 2, 1, 2, 1개 (검사 5598, 520, 139, 15, 5, 18, 5), `TC-` 63개, 변형 O2, Os, sanitizer 모두 "출력이 -O0과 한 줄도 다르지 않다", 추적 문제 0, cppcheck와 clang-tidy 지적 없음, coverage 100%, 증명 14개 |
| `make proof-mutation` | 9개 가운데 9개 |
| 전체 `make mutation` | 돌리지 않았다. `MUTANTS` 172개 + 상수 49개 = 221을 세어 맞추었고, build가 잡는 넷 (`FLOW_TASK_COUNT` 하나, 배열 뒤에 필드를 더한 셋)은 내 변이로 직접 compile 오류가 나는 것을 확인했다 |
| `make variants` 변형 | 최적화나 stack 배치에 따라 동작이 달라지는 결함 12개를 복사본에 넣어 돌림 (아래 1절) |
| `make static` 변형 | 5가지 (아래 2절) |
| CBMC의 가정을 하나씩 지움 | 17개 (아래 3절) |
| 원고의 코드 블록 둘 | 15장의 성질 7, 16장의 `TC-009`가 저장소의 코드와 글자 그대로 같다 (아래 4절) |
| CBMC의 펼침 한계 | 열 번 도는 반복: `--unwind 10`은 unwinding assertion 실패, `--unwind 11`은 증명됨. option을 주지 않아도 assertion이 켜져 있다. 100번 도는 반복: `prove_pedal_check`가 `--unwind 100`에서 실패, 101에서 성립. 원고와 같다 |

## 0. 묶음 3의 2차 지적 (E-11 - E-15)의 반영

| 지적 | 판정 | 확인한 방법 |
|---|---|---|
| E-11 [B] 배열을 끝에 두는 약속 | 닫힘 | 세 구조체에 `_Static_assert`가 있다. 배열 뒤에 필드를 더한 변이 셋과 `FLOW_TASK_COUNT` 4를 넣어 보니 모두 compile 오류이고, 메시지가 `BUILD_CAUGHT`의 글과 같다 |
| E-12 [C] 한 칸 넘는 쓰기를 값으로 잡는가 | 닫힘 | `flow_mark`의 `<=`, `window_pos`의 `>`, inverter의 `pos`의 `>`를 넣으면 모두 값으로 실패한다 (`TC-021`, `TC-014`와 `TC-022`, `TC-020`). 각각 2초 안에 끝난다. 페달의 변이에서 `test_unit`의 종료 코드는 1이고 `Abort trap` (134)이 아니다 |
| E-13 [C] 증명의 변이 도구가 도구의 실패를 "잡음"으로 셈 | 닫힘 | `answer = ...  /*oops*/`로 flow.c에 문법 오류를 넣으면 `prove.sh`가 "오류    prove_flow (도구가 판정을 내지 못했다)"와 "PARSING ERROR"를 내고 종료한다. `VERIFICATION FAILED`는 "실패"로 따로 센다 (읽어서 확인) |
| E-14 [C] "우연히 같은 조합" | 닫힘 | `TC-021`에 표시 1, 2, 3의 모든 열 (일곱 개까지)과 모든 질문의 번호를 센다. 내 계산 (같은 범위, 열 0개)과 같다 |
| E-15 [C] `SWR-26`의 `TC-011`, `FLOW_TASK_COUNT` | 닫힘 | `requirements.yaml`의 `verified_by: [TC-007, TC-011, TC-022]`. `flow.c`의 `_Static_assert(FLOW_TASK_COUNT == 3u)`. `flow_check`의 `marks[2]`를 틀리게 바꾸면 `TC-021`이 잡는다 |

묶음 3의 2차 때 내가 본 `ok || !ok`와 `TC-113`, `TC-208`의 상태는 그대로다 (fault를 모두 무효로 하는 실험은 이번에 다시 하지 않았다).

## 1. `make variants`

뜻이 있다. 다만 "있는 이유"는 추측이 아니라 실험으로 확인했다.

- 실패를 알린다. 복사본의 `monitor.h`에 `#ifdef __OPTIMIZE__`로 허용 오차를 바꾸면 (`-O0`에서는 test가 통과하고 `-O2`, `-Os`, sanitizer의 `-O1`에서는 실패) 세 변형이 모두 "test가 실패했다"를 내고 `make check`는 종료 코드 2로 끝난다. test는 통과하지만 출력만 다르게 하면 (`#ifdef __OPTIMIZE__`로 inverter의 시정수를 19 ms로) "test는 통과했지만 출력이 -O0과 다르다"를 내고 역시 `make check`가 실패한다. 출력의 비교가 잰 시간과 가속까지 보므로, 이런 종류의 차이를 단언이 없어도 잡는다.
- 건너뛰는 길이 맞다. `sanitizer` 옵션에 실패하는 compiler (옵션을 보면 1로 끝나는 wrapper)로 돌리면 "건너뜀: sanitizer (이 compiler에는 없다)"를 내고 `build/skipped`에 적고, `make skipped STRICT=1`이 실패한다. O2와 Os는 그 경우에도 돈다.
- 기준 (`-O0`)의 test가 실패하면 변형을 돌리지 않고 실패한다.

그러나 이것이 "최적화에 따라 달라지는 결함"을 잡는 정도는 test가 이미 잡는 정도를 거의 넘지 않는다. 내가 넣은 12개로 본 것이다.

| 넣은 결함 | `make test` (-O0) | `make variants` |
|---|---|---|
| 초기화하지 않은 local (`from`, `lo`, `count`) | compile 오류 (`-Werror`의 `-Wuninitialized`) | (도달하지 않음) |
| 같은 것을 pointer를 거쳐 읽음 | test 실패 13개 (stack의 쓰레기가 0이 아니다) | (도달하지 않음) |
| 배열 한 칸 넘는 읽기 (`i <= len`) | test 실패 | (도달하지 않음) |
| 극단값의 signed overflow, 한 칸 넘는 쓰기 | test 실패 | (도달하지 않음) |
| 감시와 기능의 pedal 값을 자르는 줄 둘을 뺌, `to_wire`의 `-INT_MIN` | test 통과 | 세 변형 모두 통과. 호출하는 test가 극단값을 주지 않기 때문이다 (증명이 맡는 쪽) |
| `vcu_init`에서 `app_init`, `vcu->brake = true`, `vcu->gear = GEAR_N` 초기화를 뺌 | test 통과 | 세 변형 모두 통과 (아래 E-03) |

즉, 이 단계가 새로 알리는 것은 `__OPTIMIZE__`처럼 최적화 수준에 직접 기대는 결함뿐이었다. 문서가 그렇게만 말하는지 보면, tools.md 2절과 4절, 16장은 "host의 compiler에 대해서만"과 "test가 지나간 길에서만"이라고 적는다. 과장은 없다.

tools.md 2절의 sanitizer 문장 ("한 칸 넘는 쓰기가 같은 stack 변수 안의 이웃 (test의 guard)에 떨어지면 AddressSanitizer는 알리지 않는다")은 맞다. 같은 구조체 안의 이웃은 같은 객체이므로 ASan의 red zone 밖이 아니다. 앞의 검토에서 확인한 것: 배열을 구조체의 끝에 둔 상태에서 `flow_t`를 지역 변수로 두면 ASan이 `stack-buffer-overflow`로 잡고, guard가 딸린 틀에 넣으면 알리지 않는다. 한 가지 더: 변형의 UBSan은 `-fsanitize=undefined`뿐이어서 clang이 구조체 끝의 배열을 가변 길이처럼 다루는 경계 검사를 하지 않는다 (`-fstrict-flex-arrays=3`을 더하면 `index 3 out of bounds`가 나온다). 이 변형이 배열 밖 쓰기를 잡는 것은 ASan에 기대고 있다. 변형이 그것을 알리지 않는다 (E-07).

## 2. `make static`

| 경우 | 결과 |
|---|---|
| clang-tidy만 경고하는 코드 (`#define BADMACRO(x) x * 2`) | 단계가 실패한다 (종료 코드 2). 경고 줄 둘을 찍는다. cppcheck는 지적하지 않았다 |
| `src/`에 선언하지 않은 함수를 부름 | cppcheck는 통과, clang-tidy의 `error:`가 센 줄 1개로 단계가 실패한다 |
| clang-tidy의 option이 틀림 (`-fbadflag`), 입력 파일이 없음 | `error:` 줄이 있어서 단계가 실패한다 |
| clang-tidy가 없음 (`CLANG_TIDY=`) | "건너뜀: clang-tidy가 없다"가 `build/skipped`에 적히고 `make skipped STRICT=1`이 실패한다 |
| clang-tidy가 출력 없이 실패 (`CLANG_TIDY=/usr/bin/false`) | "clang-tidy: 경고 0 개"를 찍고 단계가 통과한다 (E-05) |

## 3. 성질 7의 가정

`excess_cycles <= 5`를 지운 것은 맞다. `make check`가 통과하고, 나는 `harness.c`의 가정 17개를 하나씩 지워 해당 성질을 다시 돌렸다. 대부분은 필요하다 (지우면 실패한다). 필요하지 않은 것은 넷이다.

| 줄 | 성질 | 가정 | 지워도 |
|---|---|---|---|
| 89 | 3 (`prove_output_stage`) | `st.excess_cycles <= 5` | 증명됨 |
| 129 | 4 (`prove_pedal_check`) | `st.bad_cycles <= 3` | 증명됨 |
| 130 | 4 | `st.good_cycles <= 3` | 증명됨 |
| 549 | 11 (`prove_message_change_detected`) | `age_ok <= 50u` | 증명됨 |

성질 7의 것과 같은 종류다 (상태의 한 변수를 좁히는 가정이 불변식의 일부가 아니다). 15장이 "가정은 증명이 보는 상태를 좁힌다"고 쓰므로 같은 점검을 이 넷에도 하는 것이 낫다. 단, 성질 3의 `excess_cycles`와 성질 4의 두 값은 주석이 말하는 "5번째 주기에 차단"이나 "고장이거나 켠 직후"가 이 가정에 기대는지 읽고 정해야 한다. 지우면 성립하므로 기댈 필요는 없다 (E-04).

## 4. 원고가 도구에 대해 말한 것

| 원고의 문장 | 확인 | 결과 |
|---|---|---|
| 15장: CBMC에서 열 번 도는 반복은 `--unwind 11`에서 증명, `--unwind 10`에서 unwinding assertion 실패. option 없이도 켜져 있다 | 위 | 맞다 |
| 15장: `prove.sh`가 `--unwind 101`을 쓰는 것은 가장 긴 반복이 100번이기 때문 | `prove_pedal_check`가 100에서 실패, 101에서 성립 | 맞다 |
| 15장의 코드 (성질 7), 16장의 코드 (`TC-009`) | 저장소의 `harness.c`와 `test_unit.c`와 대조 | 성질 7: 21줄이 모두 같고 순서가 같다 (뒤쪽의 한 구절 "켠 직후의 상태" 부분은 싣지 않았다). `TC-009`: 글자 그대로, 연속한 22줄이 같다 |
| 15장: clang-tidy만 경고하는 코드를 넣어 멈추는 것을 확인했다 | 위 2절 | 맞다 |
| 15장: 성질 7의 가정을 지워도 증명된다 | 위 3절 | 맞다 (다른 가정 넷도 같다. E-04) |
| 16장: `make check`는 안전 요구사항을 받는 파일의 coverage가 100%가 아니면 실패한다 | `vcu.c`에 test가 닿지 않는 분기를 더하고 `make check`를 돌림 | 틀리다 (E-01) |
| 16장: GCC가 재는 것은 masking MC/DC | GCC의 문서를 보지 않았다 | 확인하지 못했다. `gcov`가 센 조건 결과 수는 `coverage_summary.py`의 출력과 맞는다 |
| 16장: GCC 43%와 LLVM 20% | `notes/tool-check.md`의 14개 가운데 42.86%, 5개 가운데 1개 (20%) | 맞다 (반올림 43) |
| 16장: 변이 221개 (172 + 49), 217과 4 | `MUTANTS` 172, 상수 49. 4는 build | 맞다 |
| 16장: `FI-01` 29 ms (한계 30), 88 ms (예산 92), `FI-02` 49 ms (한계 50), 108 ms (예산 111) | 출력 | 맞다 |
| 16장: fault 33가지, 알아채지 못한다가 통과 조건인 것은 `FI-03, 05, 19, 22, 31`과 `FI-15`의 마지막 구간 | test-report와 test | 맞다 |
| 16장과 17장: 변이 검사가 "모두 잡음"인 뒤에 구멍이 네 번 | test-report 7절 | 맞다 (10개 -> 4, 54개 -> 7 가운데 4, 출력 순서와 브레이크, 90개 -> 7) |
| 17장과 tools.md: 도구가 틀린 일 여덟 가운데 넷은 검토자가 넣거나 빼 보아서 드러났다 | tools.md 3절의 표와 test-report 6절의 "누가 찾았는가" | 표에서 검토자가 찾은 줄은 셋이다 (CBMC, "동등" 변이의 이유 한 번, fault를 빼도 통과). 둘째 것은 도구와 검토자가 한 번씩이라 둘로 세어도 넷이 안 된다 (E-02) |
| 17장과 tools.md: 같은 test를 다른 compiler (GCC)로 만든 실행 파일에서도 돌린다 | `tools/coverage.sh` | 부분적으로만 맞다 (E-06) |

## 숫자의 대조

| 항목 | 문서 | 실행 결과 | 일치 |
|---|---|---|---|
| `TC-` test | 63개 | 63개 | 예 |
| 변이 | 221 (test 217 + build 4), 손으로 172 + 상수 49 | 172 + 49 | 예 (전체는 돌리지 않음) |
| 증명 | 14개, 증명의 변이 9 | 14, 9 / 9 | 예 |
| coverage | 11개 파일의 줄 수와 branch, MC/DC 개수 | `test-report.md`의 표 10줄과 출력이 모두 같다 (`flow.c` 30줄) | 예 |
| 변형 | O2, Os, sanitizer 모두 출력이 같다 | 같다 | 예 |
| tools.md 1절의 판 | Apple clang 21.0.0, GCC 16.2, cppcheck 2.22, LLVM 23, CBMC 6.11, GNU Make 3.81 | 같다 | 예 |
| 16장의 표, 13장 | 앞 묶음과 같다 | 같다 | 예 |

## 지적

E-01 [A] `make check`는 coverage가 100%에 못 미쳐도 실패하지 않는다. 16장과 도구의 주석이 말하는 것과 다르다.
- 파일: `tools/coverage.sh` 47줄 (`python3 tools/coverage_summary.py build/cov/gcov.txt | tee build/reports/coverage.txt`), `chapters/ch16-testing.md` 195줄 ("`make check`는 안전 요구사항을 받는 파일의 coverage가 100%가 아니면 실패한다"), `tools/coverage_summary.py` 7줄의 주석.
- 문제: `coverage_summary.py`는 100%에 못 미치면 종료 코드 1을 내지만, pipe의 끝이 `tee`라서 `sh`는 `tee`의 종료 코드 (0)를 돌려준다. `coverage.sh`의 `set -e`도 pipe의 마지막 명령만 본다. 그래서 "coverage: 안전 요구사항을 받는 파일이 100%에 못 미친다"를 찍고도 단계는 통과한다. 이 묶음에서 15장이 `static`의 같은 종류의 틀림 (명령의 실패를 덮는 구절)을 찾아 고쳤는데, 같은 파일 묶음의 다른 곳에 같은 모양이 남아 있었다. 15장이 쓴 교훈 ("검사 단계가 있다는 것과 그 단계가 실패를 알린다는 것은 다른 일이다")이 그대로 이 단계에 해당하고, tools.md 3절의 "실제로 있었던 일"에도 없다.
- 확인: 복사본의 `src/vcu/vcu.c`의 `task_flow`에 `if (vcu->torque_out == 1234567) { ok = false; }`를 더하고 (test가 닿지 않는 문장) `make check`를 돌렸다. 출력: "coverage: 안전 요구사항을 받는 파일이 100%에 못 미친다: src/vcu/vcu.c". `make check`의 종료 코드는 0이고 마지막 줄은 "make check: 끝"이다. `make coverage`만 돌려도 종료 코드 0이다. (`flow.c`에 더했을 때에는 증명이 먼저 실패해 보이지 않았다. 증명이 없는 `vcu.c`에서 재현했다.)
- 고칠 방법: `python3 tools/coverage_summary.py build/cov/gcov.txt > build/reports/coverage.txt; status=$?; cat build/reports/coverage.txt; exit $status`로 쓴다. `static`을 고쳤을 때 한 것처럼 test 하나를 더한다: 닿지 않는 문장을 넣은 복사본에서 `make coverage`가 실패하는지를 도구 쪽의 확인 (또는 tools.md의 3절의 한 줄)으로 남긴다. 고친 뒤 16장의 문장은 그대로 맞다.

E-02 [B] 17장과 tools.md의 "여덟 가운데 넷은 검토자가 ... 드러났다"가 표와 맞지 않는다. 그 아래의 일반화가 표의 절반에 틀리다.
- 파일: `docs/tools.md` 3절의 끝 문단, `chapters/ch17-tools-and-existing-software.md`의 3절 설명 (예제 절).
- 문제: 표의 여덟 줄에서 검토자가 찾은 것으로 읽히는 줄은 셋이다 (CBMC, 변이의 "동등" 이유가 틀린 것의 둘째, fault를 빼도 통과). 나머지 다섯은 숫자를 맞추다가, 지적을 읽다가, 도구를 처음 확인할 때, 설계할 때부터 아는 한계, 15장을 쓰다가다. 이어지는 "도구를 만들거나 쓴 사람이 고른 확인만으로는 드러나지 않았다"는 그 다섯 가운데 넷 (숫자를 맞춤, 지적을 읽음, 처음 확인, 설계할 때부터)이 만든 사람이 찾은 것이라 틀리다. 문장의 주어가 "검토자가 아닌 다른 일을 하던 사람"이라면 맞지만, 앞 문장이 하나만 말하므로 독자는 여덟 줄에 대한 일반화로 읽는다.
- 확인: 표를 줄마다 "어떻게 드러났는가" 칸으로 센 것.
- 고칠 방법: 표에 "찾은 사람" 칸을 더하고 (진행자, 검토자, 쓰던 에이전트, 도구 자신) 문단은 그 칸을 센 수로 쓴다. 검토자가 찾은 것은 셋이고, 나머지를 합친 것이 이 책의 주장에 쓸모 있는 수 (도구를 쓴 쪽이 찾지 못한 것의 수)다. 일반화를 하려면 이쪽의 수 (셋이고 모두 도구가 보는 범위를 잘못 알고 있었다는 종류)로 한정한다.

E-03 [B] 초기화를 빠뜨리는 결함을 test도, 변형도, sanitizer도 알리지 않는다. 문서와 원고가 이 한계를 말하지 않는다.
- 파일: `docs/tools.md` 2절의 sanitizer 줄과 4절, `chapters/ch16-testing.md` "같은 test를 다른 build로", `tools/variants.sh` 머리의 설명 ("실행 중의 memory 오류와 정의되지 않은 동작이 없는가"), `sim/scenario.c`의 `vcu_t vcu;` (초기화하지 않은 stack).
- 문제: ASan과 UBSan은 초기화하지 않은 변수의 읽기를 알리지 않는다 (MSan, valgrind가 하는 일이고, 이 컴퓨터 (macOS arm64)에는 둘 다 없다). 이 예제에서는 의미가 있다. 시나리오 실행기의 `vcu_t`는 초기화하지 않은 stack이고 `vcu_init`이 채운다. 그 초기화를 하나 빠뜨려도 test는 통과한다. 위 1절의 표: `app_init` (`app.prev`), `vcu->brake = true`, `vcu->gear = GEAR_N`을 빼도 `make test`와 세 변형이 모두 통과한다. stack을 0xA5로 채우는 것도 부족하다 (`app_init`을 뺀 채 0xA5로 채워도 통과했다. 지난 묶음의 같은 실험에서 `gear_check`, `inverter_check`, `e2e_tx`의 초기화도 같았다). 변이 목록에도 초기화를 빼는 변이가 없다. 문서는 "memory 오류"를 본다고 적고, 초기화는 한 줄도 말하지 않는다. 13장은 "상태 변수가 망가져 있어도"를 말하는데, 이것은 켠 직후에 값이 정해져 있다는 것과는 다른 일이다.
- 확인: `vcu.c`에서 해당 줄을 지운 복사본에서 `make variants`. 지난 묶음의 복사본에서 `scenario_run`에 `memset(&vcu, 0xA5, sizeof vcu)`를 더해도 `app_init`을 뺀 코드가 통과했다.
- 고칠 방법: (1) tools.md 4절에 "초기화하지 않은 변수의 읽기를 알리는 도구 (MSan, valgrind)를 쓰지 않았다. 초기화를 빠뜨리는 결함은 test도 변형도 알리지 않는다"를 적고, 16장과 `variants.sh`의 머리 설명에도 한 구절 더한다. (2) 값으로 보는 방법: 각 `*_init` 직후의 상태를 stack을 쓰레기 값 (0xA5)으로 채운 뒤에 단언하는 unit test를 둔다. 변이 목록에 초기화를 빼는 변이를 넣는다.

E-04 [C] 성질 7과 같은 필요 없는 가정이 넷 남아 있다 (위 3절). 15장의 서술 ("이제 이 성질은 그 횟수가 어떤 값이어도 성립한다")은 성질 7에는 맞고, 일반화한 "가정은 증명을 약하게 한다"는 이 넷에도 해당한다.
- 확인: `asm.py` (복사본에서 가정을 하나씩 지우고 그 성질만 CBMC로 돌림). 줄 89, 129, 130, 549.
- 고칠 방법: 지운다. 단, 성질 4의 `bad_cycles <= 3`, `good_cycles <= 3`은 "한 주기 전의 실제로 닿는 상태"를 적은 것이어서 지우면 읽는 사람의 이해가 줄 수 있다. 지우거나, 이유를 한 줄 적고 둔다 (이유가 "도달하는 상태"라면 불변식의 일부로 단언하는 것이 맞다).

E-05 [C] clang-tidy가 `warning:`과 `error:`가 없는 채 죽으면 `make static`은 "경고 0 개"로 통과한다.
- 파일: `Makefile`의 `static` (143, 144줄).
- 문제: `... > clang-tidy.txt 2>&1 || true`로 종료 코드를 버리고 출력의 `warning:`과 `error:`만 센다. 도구가 시작하지 못하거나 (종료 코드 1, 출력 없음) 중간에 죽으면 센 수가 0이다. option이 틀리거나 파일이 없는 흔한 경우는 `error:` 줄이 있어 걸린다 (위 2절).
- 확인: `make static CLANG_TIDY=/usr/bin/false` -> "clang-tidy: 경고 0 개", 종료 코드 0.
- 고칠 방법: 종료 코드를 `status`로 받아 두고 센 수가 0이어도 status가 0이 아니면 실패하게 한다. clang-tidy는 경고만 있을 때에도 0이 아닌 코드를 낼 수 있으므로 (`WarningsAsErrors`가 없으면 0) 판정은 "수 > 0 또는 status != 0"이다.

E-06 [C] "다른 compiler (GCC)로 만든 실행 파일에서도 같은 test가 통과한다"는 부분적으로만 맞다.
- 파일: `docs/tools.md` 2절 compiler 줄, `chapters/ch16-testing.md`와 `ch17`의 sim 표와 예제 절, `tools/coverage.sh`.
- 문제: GCC로 만드는 실행 파일은 `coverage.sh`의 셋 (`cov_unit`, `cov_scenario`, `cov_fault_app`)이다. 대조 test 넷 (`NC-`와 `TC-127`을 가진 실행 파일)은 GCC로 돌지 않는다. 그리고 출력은 `> /dev/null`로 버려서 `-O0`과 견주는 일도 없다 (종료 코드만 본다). GCC의 최적화도 켜지 않는다 (`CFLAGS`에 `-O0`). 그래서 "GCC로 만든 것에서도 최적화를 켠 build처럼 출력이 같다"로 읽히지 않게 적는 것이 낫다.
- 고칠 방법: tools.md의 문장을 "coverage를 재는 세 test 실행 파일은 GCC (-O0)로도 만들어 돌리고, 종료 코드만 본다"로 쓴다. 또는 `variants.sh`에 GCC 변형 하나를 더한다 (`-O0`, `-O2`).

E-07 [C] tools.md의 두 표에 빠진 것.
- 파일: `docs/tools.md` 1절, 2절, 4절.
- (a) 1절과 2절에 "build를 묶는 글 (`Makefile`, `tools/*.sh`)"이 없다. 이 묶음에서 두 번 틀렸다 (`static`의 `|| true`, 그리고 위 E-01의 `| tee`). 틀리는 모양은 "실패를 덮는다"이고 잡는 길은 "알려진 결함을 넣어 단계가 실패하는지 본다"이다 (15장이 `static`에 한 것). 이것이 가장 쓸모 있는 도구 행이다.
- (b) 4절에 host와 target의 정수와 배치의 차이가 없다. 이 test는 LP64의 arm64에서 돈다 (`int` 32 bit, `size_t` 64 bit, little endian). `_Static_assert (offsetof ... == sizeof)`, guard를 두는 틀 (`flow_t`가 `uint8_t`만 있어서 padding이 없다는 가정), `uint8_t`가 식 안에서 `int`로 넓어지는 CRC 계산은 모두 이 배치에 기댄다. 16비트 `int`의 target에서는 같은 source가 다른 동작을 할 수 있다. 4절의 둘째 줄 ("target의 compiler로 빌드하고 target에서 test하기")이 이것을 덮는다고 읽을 수 있으나, 정수 폭과 배치는 compiler를 바꾸지 않아도 달라지는 별개의 일이다.
- (c) 4절에 "초기화하지 않은 변수를 보는 도구" (E-03).
- 고칠 방법: (a)는 표에 한 행, (b)와 (c)는 4절에 한 줄씩.

E-08 [C] 변형의 sanitizer는 구조체 끝의 배열 경계를 보지 않는다 (`-fsanitize=undefined`의 `bounds`는 clang에서 구조체 끝 배열을 가변 길이처럼 다룬다).
- 파일: `tools/variants.sh`의 `SAN`.
- 문제: 지난 묶음에서 배열을 구조체 끝에 두자 ASan이 `flow_mark`의 변이를 잡았지만 UBSan은 못 잡았다 (`-fstrict-flex-arrays=3`을 더하면 잡는다). 지금 변형은 ASan에 기대고 있다. 괜찮지만 `variants.sh`의 머리의 설명은 "배열 밖의 접근 등"을 UBSan과 ASan이 함께 본다고 읽힌다.
- 고칠 방법: `SAN`에 `-fstrict-flex-arrays=3`을 더하거나 (clang 전용 option이므로 GCC에서는 빼는 분기), 머리의 설명에 "배열 밖은 ASan이 본다"를 적는다.

## 판정

판정: 조건부 통과.

까닭: 묶음 3의 2차 지적 다섯은 모두 실제로 닫혔다 (값으로 실패하고 `Abort trap`이 없다). `make variants`는 뜻이 있고 실패를 `make check`까지 올리며 건너뛰는 길도 맞다. 새 `make static`은 clang-tidy만 경고하는 코드에서 실패한다. 숫자와 15장의 CBMC 설명, 코드를 실은 두 곳은 모두 맞다. 그러나 15장이 "검사 단계가 있다는 것과 그 단계가 실패를 알린다는 것은 다른 일"이라고 가르친 바로 그 틀림이 `coverage` 단계에 남아 있다 (E-01). 16장은 이것을 "make check가 실패한다"고 적고 있어서 이 책의 한 문장이 사실과 다르다. 고치는 것은 두 줄이고, 고친 뒤 문장은 그대로 맞다. 다음으로 무거운 것은 17장과 tools.md의 "여덟 가운데 넷"이 표와 맞지 않는 것 (E-02), 그리고 초기화를 빠뜨리는 결함이 어떤 단계에도 걸리지 않는데 문서가 말하지 않는 것 (E-03)이다. 지적은 A 1, B 2, C 5다. A를 고치고 B 둘을 반영하거나 이유를 적어 받지 않으면 통과로 본다.

## 확인하지 못한 것

- 전체 `make mutation` (진행자의 숫자를 믿었다).
- 원고가 인용한 외부 문서 (CPROVER Manual, MC/DC tutorial, JATR 등)의 쪽과 문장. 예제와 도구의 동작을 말한 문장만 보았다.
- "GCC가 재는 것은 masking MC/DC" (GCC의 문서를 보지 않았다).
- clang-tidy의 비정상 종료 (E-05)는 `/usr/bin/false`로 흉내 냈고 실제 crash는 만들지 못했다.
- FuSa 쪽, 요구사항, 안전 논증과의 관계.
