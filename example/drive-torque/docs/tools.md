# 도구와 밖에서 온 소프트웨어

이 예제의 검증 결과는 모두 도구가 낸 것이다. 도구가 틀리면 결과도 틀린다. 도구마다 무엇에 쓰는지, 틀리면 어떻게 되는지, 그 틀림을 다른 무엇이 잡는지를 적는다.

- 어느 도구도 qualification되지 않았다. 이 문서는 qualification의 기록이 아니다. 도구를 얼마나 믿고 있는지를 드러내는 표다.
- 분류의 말 ("제품에 결함을 넣을 수 있다", "결함을 놓칠 수 있다")은 이 책의 말이다. 규격의 분류표를 옮긴 것이 아니다 (17장).
- 판은 2026-11-23에 `make check`를 돌린 컴퓨터 (macOS, arm64)의 것이다.

## 1. 도구의 목록

| 도구 | 판 | 쓰는 곳 | 설정이 있는 곳 |
|---|---|---|---|
| compiler (빌드와 test) | Apple clang 21.0.0 | 제품 코드, sim, test를 host의 실행 파일로 만든다 | `Makefile`의 `CFLAGS` (`-std=c11 -Wall -Wextra -Werror -pedantic -O0 -g`) |
| compiler (coverage) | GCC 16.2 | 같은 코드를 coverage를 재는 실행 파일로 만든다 | `tools/coverage.sh` (`--coverage -fcondition-coverage`) |
| sanitizer (AddressSanitizer, UndefinedBehaviorSanitizer) | Apple clang 21.0.0의 것 | test를 돌리는 동안 memory 오류와 정의되지 않은 동작을 본다 | `tools/variants.sh` |
| gcov | GCC 16.2의 것 | statement, branch, MC/DC를 센다 | `tools/coverage.sh`, `tools/coverage_summary.py` |
| cppcheck | 2.22 | 정적 분석 | `Makefile`의 `static` |
| clang-tidy | LLVM 23 | 정적 분석 (bugprone, cert, clang-analyzer 묶음) | `Makefile`의 `static` |
| CBMC | 6.11 | 성질 14개의 증명. overflow, 0으로 나누기, 값이 달라지는 변환, 배열 밖 접근 | `tools/prove.sh` |
| 추적 스크립트 | 이 저장소의 것 | 요구사항, 코드, test의 ID가 이어져 있는지 | `tools/trace.py` |
| 변이 검사 스크립트 | 이 저장소의 것 | 제품 코드에 결함을 넣고 test (또는 증명)가 실패하는지 | `tools/mutation_check.py`, `tools/proof_mutation.py` |
| test의 틀 | 이 저장소의 것 | test를 돌리고 통과와 실패를 센다 | `test/test.h`, `test/test_run.c` |
| sim | 이 저장소의 것 | HAL의 뒤 (센서, CAN, 선, 외부 watchdog), 차량과 inverter의 model, 시나리오 실행기 | `sim/` |
| make, python3, sh | GNU Make 3.81, Python 3 | 위의 것들을 부른다 | `Makefile` |

sim과 test의 틀도 도구로 센다. test의 결과는 sim이 fault를 정말 넣었는지와 틀이 실패를 정말 세는지에 달려 있다.

## 2. 틀리면 어떻게 되는가

도구가 틀리는 모양은 둘이다. 제품에 결함을 넣는 것과, 있는 결함을 놓치는 것이다.

| 도구 | 틀리는 모양 | 제품에 결함을 넣는가 | 결함을 놓치는가 | 그 틀림을 잡을 수 있는 것 |
|---|---|---|---|---|
| compiler | source와 다르게 동작하는 기계어를 만든다 | 넣는다 | - | 그 실행 파일로 돌린 test. 다른 compiler (GCC)로 만든 실행 파일에서도 같은 test가 통과한다. 최적화를 켠 build (`-O2`, `-Os`)에서도 test의 출력이 `-O0`과 한 줄도 다르지 않다 (`make variants`). 다만 모두 host의 compiler다. target의 compiler와 그 최적화는 아무것도 보지 않았다 |
| sanitizer | 있는 오류를 알리지 않는다 | 아니다 | 놓친다 | 알려진 결함을 넣어 보기. 한 칸 넘는 쓰기가 같은 stack 변수 안의 이웃 (test의 guard)에 떨어지면 AddressSanitizer는 알리지 않는다는 것을 확인했다. 그 경우는 test의 값 검사가 잡는다 |
| gcov | 실행한 줄이나 조건을 잘못 센다 | 아니다 | 놓친다 (덜 실행한 곳을 100%라고 한다) | 변이 검사. coverage가 100%인 곳에 넣은 결함을 test가 놓치면 드러난다 |
| cppcheck, clang-tidy | 결함을 지적하지 않는다. 결함이 아닌 것을 지적한다 | 아니다 | 놓친다 | 두 도구가 서로 다른 것을 본다. 증명과 test |
| CBMC | 성립하지 않는 성질을 증명됐다고 한다. 보는 범위가 생각보다 좁다 | 아니다 | 놓친다 | 증명의 변이 (`make proof-mutation`), 증명 전의 도구 확인, 같은 성질을 보는 test |
| 추적 스크립트 | 이어지지 않은 요구사항을 이어졌다고 한다 | 아니다 | 놓친다 | 검토 (사람이나 에이전트가 표를 읽는다) |
| 변이 검사 스크립트 | 잡지 못한 변이를 잡았다고 센다 | 아니다 | 놓친다 (test가 모자란 것을) | 검토자가 따로 넣어 보는 변이 |
| test의 틀 | 실패한 검사를 통과로 센다 | 아니다 | 놓친다 | 변이 검사 (결함을 넣었는데 실패가 없으면 드러난다) |
| sim | fault를 넣지 않는다. 차량의 model이 틀리다 | 아니다 | 놓친다 | fault를 빼고 돌려 test가 실패하는지 보기. 대조 test (`NC-`). model이 실제와 같은지는 아무것도 잡지 못한다 |

제품에 결함을 넣을 수 있는 것은 compiler 하나다. 나머지는 모두 "없다고 말했는데 있다"로 틀린다. 그래서 이 표의 오른쪽 칸은 대부분 같은 꼴이다. 알려진 결함을 넣어 보고 도구가 그것을 알리는지를 본다.

## 3. 실제로 있었던 일

도구가 틀렸거나, 도구가 보는 범위를 잘못 알고 있었던 경우다. 자세한 것은 [test-report.md](test-report.md) 6절에 있다.

| 도구 | 무슨 일 | 어떻게 드러났는가 | 한 일 |
|---|---|---|---|
| CBMC | 구조체 안의 배열을 한 칸 넘는 쓰기를 잡지 못했다. pointer로 받은 구조체에서는 구조체의 끝만 본다. 문서는 "배열 밖을 쓰지 않는다는 것을 증명했다"고 적고 있었다 | 검토자가 그 결함을 넣었는데 증명이 통과했다 | 배열을 구조체의 끝으로 옮기고, 그 약속을 compile할 때 확인한다. 증명 전에 작은 예로 도구를 확인한다. 증명에 결함을 넣어 보는 검사를 더했다 |
| 변이 검사 스크립트 | compile되지 않는 변이를 "잡았다"고 셌다 | 숫자를 맞춰 보다가 | compile 실패를 따로 세게 고쳤다 |
| 변이 검사 스크립트 | "동등하다"고 따로 둔 변이의 이유가 두 번 틀렸다. 도구는 사람이 적은 이유를 확인하지 못한다 | 한 번은 도구가 (따로 둔 변이를 test가 잡았다), 한 번은 검토자가 | 제품 코드를 고쳤다 (답에 표시의 수) |
| sim과 test | fault를 빼도 통과하는 시나리오 test가 둘 있었다. test가 fault가 한 일을 보지 않았다 | 검토자가 fault를 빼고 돌렸다 | fault가 있어야만 성립하는 판정을 더했다 |
| cppcheck (MISRA 검사) | 변수 이름을 규칙 위반으로 냈다 (거짓 경보) | 지적을 읽다가 | 기록만 했다. 이 검사는 `make check`에서 쓰지 않는다 |
| gcov와 llvm-cov | 같은 코드의 MC/DC를 서로 다른 단위로 센다. 숫자를 그대로 견줄 수 없다 | 도구를 처음 확인할 때 | GCC의 것만 쓴다 |
| 추적 스크립트 | ID가 주석에 적혀 있기만 하면 통과한다 | 설계할 때부터 아는 한계 | 10장에 적었다 |

일곱 가운데 넷은 다른 사람 (검토자)이 결함을 넣거나 빼 보아서 드러났다. 도구를 만들거나 쓴 사람이 고른 확인만으로는 드러나지 않았다.

## 4. 하지 않은 것

| 하지 않은 것 | 그래서 못 하는 주장 |
|---|---|
| 도구의 qualification | 도구의 결과를 다른 확인 없이 믿어도 된다는 주장 |
| target의 compiler로 빌드하고 target에서 test하기 | 제품에 실릴 기계어가 source대로 동작한다는 주장. test한 것은 host의 실행 파일이다. 최적화를 켠 build의 test (`make variants`)도 host의 compiler에 대해서만 말해 준다 |
| 도구의 판을 고정하기 (container, 판을 적은 설정 파일) | 다른 컴퓨터에서 같은 결과가 나온다는 주장. `Makefile`은 설치된 GCC 가운데 하나를 고른다 |
| 도구의 알려진 결함 목록을 확인하기 | 쓰고 있는 판의 알려진 결함이 이 코드에 걸리지 않는다는 주장 |
| 도구의 설정을 검토하기 | 꺼 둔 검사가 꺼도 되는 것이라는 주장 (clang-tidy의 검사 하나를 껐다) |

## 5. 밖에서 온 소프트웨어

- 제품 코드 (`src/`)는 표준 헤더 셋 (`stdint.h`, `stdbool.h`, `stddef.h`)만 쓰고, library의 함수를 하나도 부르지 않는다. 동적 memory도 쓰지 않는다 (13장).
- 그래도 실행 파일에는 예제가 쓰지 않은 코드가 들어간다. compiler가 넣는 시작 코드와 runtime이다. target에 따라서는 compiler가 나눗셈이나 큰 정수의 계산을 runtime의 함수 호출로 바꾼다. source에는 보이지 않는 밖의 코드가 감시의 계산 안에서 실행되는 것이다. host에서는 이것을 볼 수 없다.
- sim과 test는 C library (`stdio`, `math`)를 쓴다. 제품에 실리지 않는다.
- 실제 제어기라면 여기에 더 있다: MCU 회사의 driver와 시작 코드, OS, 통신 stack, 메시지 보호의 library. 예제는 HAL의 뒤를 sim으로 바꿔서 이것들을 모두 범위 밖에 두었다. 그 선택의 대가는 [hsi.md](hsi.md)와 [hardware-assumptions.md](hardware-assumptions.md)의 가정으로 적혀 있다.
