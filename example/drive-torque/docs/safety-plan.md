# safety plan

예제 프로젝트에서 안전을 위해 무엇을, 어떤 순서로, 누가 하고, 누가 확인하는지를 적는다. 다른 산출물은 모두 이 계획에서 가리킨다.

- 이것은 책의 예제다. 실제 프로젝트의 계획이 아니고, 규격의 요구사항을 만족하는지 확인한 것이 아니다.
- 이 예제에는 사람의 조직이 없다. 아래의 "역할"은 이 책을 만드는 과정에서 실제로 그 일을 한 주체다. 실제 프로젝트라면 사람의 이름과 조직이 들어갈 자리다.
- 이 계획은 개발을 한 뒤에 정리한 것이다 (2026-11-22). 실제 프로젝트에서는 계획이 먼저 있고 그것을 다른 사람이 검토한다 (5장).

## 1. 범위

| 항목 | 내용 |
|---|---|
| item | 전기차의 차량 제어기 (VCU)의 구동 토크 제어 ([item-definition.md](item-definition.md)) |
| 다루는 safety goal | `SG-01` 하나 (의도하지 않은 가속). 등급은 ASIL D로 가정했다 |
| 다루지 않는 것 | 나머지 hazard 넷의 safety goal, 하드웨어의 개발, 생산과 운용 ([scope.md](scope.md)) |
| 환경 | PC 시뮬레이션. 보드로 옮기지 않는다 |

## 2. 활동과 산출물

| 단계 | 활동 | 산출물 | 상태 |
|---|---|---|---|
| concept | item을 정한다 | [item-definition.md](item-definition.md), [scope.md](scope.md) | 했다 |
| concept | hazard를 찾고 등급을 매긴다 | [hara.md](hara.md) | `H-01`만 |
| concept | functional safety concept | [functional-safety-concept.md](functional-safety-concept.md) | `SG-01`만 |
| system | technical safety concept, 가정 목록, 시간 예산 | [technical-safety-concept.md](technical-safety-concept.md) | `SG-01`만 |
| system | safety analysis | [fta.md](fta.md) | FTA만. FMEA와 dependent failure analysis는 하지 않았다 |
| software | software safety requirement | [requirements.yaml](requirements.yaml) | 12개 |
| software | 구조 설계 | [architecture.md](architecture.md) | 했다 |
| software | 구현 | `src/` | 했다 |
| software | 검증: test, 정적 분석, coverage, 증명 | [test-report.md](test-report.md) | 했다. PC 시뮬레이션에서만 |
| 전체 | safety case | [safety-case.md](safety-case.md) | 닫히지 않았다. 열린 가지 넷 |
| 전체 | 형상과 변경의 관리 | git의 이력 | 절차를 따로 적지 않았다 |

## 3. 역할

| 역할 | 하는 일 | 이 예제에서 |
|---|---|---|
| 안전 책임자 | 이 계획을 만들고 지키게 한다. 산출물이 빠지지 않았는지 본다 | 진행자 (Claude 주 세션) |
| 만드는 사람 | 요구사항, 설계, 코드, test를 만든다 | 진행자 |
| 검토자 | 산출물을 만든 사람이 아닌 눈으로 본다 | 두 역할의 에이전트 (FuSa 전문가, 임베디드 엔지니어) |
| 결정하는 사람 | 범위와 쟁점을 정한다 | 저자 |

이 표의 약한 곳은 스스로 보인다. 안전 책임자와 만드는 사람이 같다. 검토자는 만든 쪽과 같은 계열의 모델이다. 5장에서 이것이 왜 문제인지 다룬다.

## 4. 확인

| 무엇을 | 언제 | 누가 | 만든 쪽에서 떨어진 정도 | 기록 |
|---|---|---|---|---|
| 예제의 설계 | 코드를 쓰기 전 | 두 검토자 | 다른 에이전트. 같은 계열의 모델 | `reviews/2026-11-22-example-design/` |
| 예제의 산출물과 코드, 장의 원고 | 단계가 끝날 때 | 두 검토자 | 위와 같다 | `reviews/2026-11-22-stage1/` |
| 코드가 요구사항대로인가 | 바꿀 때마다 | 도구 (`make check`) | 사람이 아니다 | `build/reports/` |
| 과정을 계획대로 했는가 (audit) | - | - | - | 하지 않았다 |
| 전체가 안전한가 (assessment) | - | - | - | 하지 않았다. 사람 실무자의 검토를 받지 않았다 |

## 5. 줄인 것 (tailoring)

하지 않은 활동과 그 이유다. 실제 프로젝트에서는 이유마다 누군가의 승인이 붙는다.

| 줄인 것 | 이유 | 그래서 못 하는 주장 |
|---|---|---|
| safety goal 하나만 다룬다 | 책의 예제를 작게 유지한다 | item이 안전하다는 주장. `SG-01`에 대한 주장만 할 수 있다 |
| 하드웨어의 개발과 지표 계산을 하지 않는다 | 소프트웨어의 책이다 | 하드웨어의 고장에 대한 주장. 가정으로 받는다 |
| target에서 검증하지 않는다 | 보드로 옮기지 않기로 했다 | 실행 시간, 메모리 보호, watchdog에 대한 주장 |
| 도구를 qualification하지 않는다 | 예제의 범위 밖이다 | 도구의 결과를 믿어도 된다는 주장 |
| FMEA와 dependent failure analysis를 하지 않았다 | 단계 2로 미뤘다 | 감시가 기능에서 독립적이라는 주장. 기능과 감시를 함께 틀리게 하는 원인이 없다는 주장 |
| 나머지 hazard 넷은 등급을 매기지 않았다 | 예제를 작게 유지한다 | 고장 대응 (토크를 끊는 것)이 다른 hazard를 받아들일 수 없게 키우지 않는다는 주장 |
| 형상과 변경을 관리하는 절차를 적지 않았다 | git의 이력만 있다 | 검증한 것과 내보내는 것이 같은 판이라는 것을 절차로 보였다는 주장 |
| 차량에서의 validation을 하지 않는다 | 차량이 없다 | 실제 차량에서 `SG-01`이 지켜진다는 주장 |
| audit, assessment, 독립된 사람의 검토를 하지 않는다 | 사람의 조직이 없다 | 과정을 지켰다는 것과 전체가 안전하다는 것을 독립된 눈이 확인했다는 주장 |

줄인 이유를 승인한 사람도 없다. 이 표는 진행자가 적었고 두 검토자가 읽었을 뿐이다.

줄인 것마다 "그래서 못 하는 주장"을 적는다. 줄이는 것은 일을 덜 하는 것이 아니라 주장을 덜 하는 것이다.

## 6. 도구

| 도구 | 쓰는 곳 | 틀리면 |
|---|---|---|
| compiler (Apple clang, GCC 16) | 빌드, coverage | 틀린 실행 파일. test가 일부를 잡는다 |
| cppcheck, clang-tidy | 정적 분석 | 결함을 놓친다. 거짓 경보를 낸다 (한 번 있었다) |
| CBMC | 증명 | 성립하지 않는 성질을 증명됐다고 한다 |
| 추적 스크립트, 변이 검사 스크립트 | 추적, test의 평가 | 빠진 것을 놓친다 (한 번 있었다) |

어느 도구도 qualification되지 않았다. 17장에서 다룬다.
