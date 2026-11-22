# 도구 확인 기록

단계 0의 "도구를 확인한다"의 결과다. 2026-11-22에 이 컴퓨터 (macOS, arm64)에서 확인했다.

## 방법

토크 감시 함수의 시제품을 만들어 재 보았다. 조건 다섯 개가 한 판단문에 들어 있는 함수다.
test를 두 묶음으로 돌렸다: 정상 경우 두 개만 있는 "부분" 묶음과, 조건을 하나씩 뒤집는 경우를 더한 "전체" 묶음.

## 결과

| 도구 | 상태 | 확인한 것 |
|---|---|---|
| GCC 16.2.0 (Homebrew) | 설치되어 있음 | `--coverage -fcondition-coverage`로 빌드하고 `gcov --conditions`로 본다. 부분 묶음은 조건 결과의 42.86% (14개 가운데), 전체 묶음은 100% |
| LLVM 23.1.5 (Homebrew) | 설치되어 있음 | `-fprofile-instr-generate -fcoverage-mapping -fcoverage-mcdc`로 빌드하고 `llvm-cov report --show-mcdc-summary`로 본다. 부분 묶음은 조건 5개 가운데 1개 (20%), 전체 묶음은 5개 (100%) |
| Apple clang 21.0.0 | 설치되어 있음 | `-fcoverage-mcdc`로 빌드된다. 보고서는 확인하지 않았다 |
| clang-tidy | 설치되어 있음 | Homebrew의 LLVM에 들어 있다. 실행은 아직 하지 않았다 |
| cmake, ninja, make, docker | 설치되어 있음 | - |
| CBMC | 없음 | 설치해야 확인할 수 있다 |
| cppcheck | 없음 | 설치해야 확인할 수 있다 |
| gcovr | 없음 | 보고서를 보기 좋게 만드는 도구. 없어도 측정은 된다 |

## 알게 된 것

- 부분 묶음은 줄 단위로는 100%를 덮었다. 그런데 MC/DC로는 GCC 기준 43%, LLVM 기준 20%였다. 16장에서 "줄을 다 지나가도 판단의 조건은 덜 시험되었을 수 있다"를 보이는 예로 쓸 수 있다.
- 두 compiler는 세는 단위가 다르다. GCC는 판단문 세 개의 조건 결과 14개를 세고, LLVM은 조건이 둘 이상인 판단문 하나의 조건 5개를 센다. 숫자를 그대로 견줄 수 없다.
- 측정은 최적화를 끈 빌드 (`-O0`)로 했다.

## 정한 것

- compiler: GCC 16과 LLVM 23을 함께 쓴다. 측정은 GCC로 하고 LLVM으로 견주어 본다.
- unit test: 바깥의 framework를 받지 않고, 예제 안에 작은 test 틀을 둔다. `make check`가 다른 것을 내려받지 않고 돌게 하기 위해서다. 필요해지면 다시 정한다.
- 이 도구들은 어느 것도 qualification되지 않았다. 17장의 tool 분류표에 그렇게 적는다.

## 남은 것

- CBMC와 cppcheck는 설치해야 확인할 수 있다. 설치는 저자의 허락을 받은 뒤에 한다.
