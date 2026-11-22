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
| CBMC 6.11.0 (Homebrew) | 저자가 설치함 | 감시 함수의 성질 두 개를 모든 32-bit 입력에 대해 증명했다. 일부러 넣은 결함 두 개를 반례와 함께 찾았다. 아래 "CBMC와 정적 분석" 절 |
| cppcheck 2.22.0 (Homebrew) | 저자가 설치함 | `--enable=all`과 `--addon=misra`로 돌렸다. 아래 "CBMC와 정적 분석" 절 |
| gcovr | 없음 | 보고서를 보기 좋게 만드는 도구. 없어도 측정은 된다 |

## 알게 된 것

- 부분 묶음은 줄 단위로는 100%를 덮었다. 그런데 MC/DC로는 GCC 기준 43%, LLVM 기준 20%였다. 16장에서 "줄을 다 지나가도 판단의 조건은 덜 시험되었을 수 있다"를 보이는 예로 쓸 수 있다.
- 두 compiler는 세는 단위가 다르다. GCC는 판단문 세 개의 조건 결과 14개를 세고, LLVM은 조건이 둘 이상인 판단문 하나의 조건 5개를 센다. 숫자를 그대로 견줄 수 없다.
- 측정은 최적화를 끈 빌드 (`-O0`)로 했다.

## 정한 것

- compiler: GCC 16과 LLVM 23을 함께 쓴다. 측정은 GCC로 하고 LLVM으로 견주어 본다.
- unit test: 바깥의 framework를 받지 않고, 예제 안에 작은 test 틀을 둔다. `make check`가 다른 것을 내려받지 않고 돌게 하기 위해서다. 필요해지면 다시 정한다.
- 이 도구들은 어느 것도 qualification되지 않았다. 17장의 tool 분류표에 그렇게 적는다.

## CBMC와 정적 분석

2026-11-22에 저자가 CBMC와 cppcheck를 설치한 뒤에 확인했다.

### CBMC

시제품에 토크 요구를 한도로 깎는 함수를 더하고, 증명할 성질을 assert로 적었다.

```c
/* 성질 1: 허용 토크는 어떤 페달 값에서도 0 이상, 최대 토크 이하다 */
void prove_allowed_range(void)
{
    int32_t pedal = nondet_int32();
    int32_t t = allowed_torque(pedal);
    assert(t >= 0);
    assert(t <= TORQUE_MAX);
}

/* 성질 2: 깎은 토크 요구는 어떤 입력에서도 감시를 통과하고 한도 이하다 */
void prove_limited_output(void)
{
    int32_t cmd = nondet_int32();
    int32_t pedal = nondet_int32();
    bool valid = nondet_bool();
    bool brake = nondet_bool();
    int32_t out = limit_torque(cmd, pedal, valid, brake);
    assert(!monitor_violation(out, pedal, valid, brake));
    assert(out <= TORQUE_MAX + TOLERANCE);
    if (!valid) { assert(out <= 0); }
    if (brake) { assert(out <= BRAKE_LIMIT); }
}
```

명령은 `cbmc monitor.c harness.c --function prove_limited_output --signed-overflow-check --div-by-zero-check --conversion-check`다.

| 확인한 것 | 결과 |
|---|---|
| 성질 1, 성질 2 | 둘 다 증명되었다. 0.4초쯤 걸렸다 |
| 계산 중의 signed overflow | 없다고 증명되었다. 페달 값을 범위 안으로 자른 뒤에 곱하기 때문이다 |
| 결함 1: 페달 값을 자르지 않고 곱한다 | 곱셈의 overflow와 성질 위반을 찾았다. 반례: 페달 값 1208352769 |
| 결함 2: 제동 때의 한도를 뺀다 | 성질 위반을 찾았다. 반례: 토크 요구 102, 페달 55, 브레이크 밟음 |

### cppcheck와 clang-tidy

| 도구 | 찾은 것 | 찾지 못한 것 |
|---|---|---|
| cppcheck `--enable=all` | 쓰이지 않는 함수, static으로 둘 수 있는 함수 | 결함 1의 overflow |
| cppcheck `--addon=misra` | 규칙 15.5 (함수의 출구가 둘), 규칙 17.8 (parameter를 고쳐 씀). 규칙 번호만 나온다 | - |
| clang-tidy (`bugprone-*`, `cert-*`, `clang-analyzer-*`) | 이름 없는 상수, 형이 같은 parameter가 나란히 있는 것 | 결함 1의 overflow |

## CBMC와 정적 분석에서 알게 된 것

- 세 도구가 찾는 것이 다르다. 결함 1의 overflow는 CBMC만 찾았다. 15장에서 도구마다 보는 것이 다르다는 예로 쓸 수 있다.
- CBMC는 시작 함수에서 닿지 않는 함수의 성질도 "SUCCESS"로 적는다. 성질 1만 돌렸을 때 성질 2의 assert가 모두 SUCCESS로 나왔다. 증명되었다는 표시만 보면 안 되고, 그 성질에 실제로 닿았는지를 봐야 한다.
- 증명이 빈 증명이 아닌지는 결함을 일부러 넣어 확인했다. 결함을 넣으면 실패해야 한다.
- cppcheck의 MISRA 검사는 규칙의 문장 없이 번호만 낸다. 문장을 보려면 MISRA 문서가 있어야 한다. 저자는 2026-11-22에 이 문서를 사지 않기로 정했다 (PLAN.md 12절).
- cppcheck의 MISRA 검사가 규칙 7.3을 여덟 곳에서 냈다. 그 줄에는 숫자의 접미사가 없으므로 거짓 경보로 보인다. 원인은 확인하지 않았다. 단계 0.5에서 본다.
- CBMC가 증명한 것은 C 코드의 성질이다. compiler가 만든 기계어, 실행 시간, 하드웨어의 동작은 증명하지 않는다.

## 예제를 만들면서 알게 된 것 (2026-11-22)

- CBMC가 실제 결함을 찾았다. 전압을 페달 위치로 바꾸는 함수가 `mv - min_mv`를 먼저 계산했다. HAL이 범위 밖의 값을 주면 이 뺄셈에서 signed overflow가 난다. unit test와 시나리오 test는 모두 통과하고 있었다. 빼기 전에 범위를 보도록 고쳤다. 15장과 16장의 예로 쓴다.
- coverage 측정이 빠진 test를 찾았다. 처음에는 입력 읽기 (`input.c`)의 MC/DC가 42%였다. 기어 값을 알 수 없는 경우와 속도 메시지가 끊긴 경우의 test가 없었다.
- test가 결함을 잡는지 변이로 확인했다. 제품 코드에 결함 10개를 하나씩 넣었고 test가 모두 잡았다 (`make mutation`).
- cppcheck 2.22의 MISRA 검사는 변수 이름 `pedal`을 규칙 7.3 (숫자의 접미사 `l`) 위반으로 낸다. `brake`나 `medal`은 내지 않는다. 거짓 경보다. 작은 파일로 확인했다. 17장에서 도구도 틀린다는 예로 쓸 수 있다.
- GCC의 gcov 옵션은 `--conditions`와 `--branch-probabilities`다. gcov는 compile한 폴더를 기준으로 소스를 찾으므로, coverage 빌드와 gcov를 같은 폴더에서 돌린다.

## 남은 것

- 깨끗한 container에서 `make check`를 돌려 보지 못했다. 이 컴퓨터에서 docker가 실행 중이 아니었다.
- gcovr는 설치하지 않았다. 보고서는 `gcov`의 출력을 `tools/coverage_summary.py`로 줄여서 만든다.
