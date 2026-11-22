# 6장. Hazard analysis and risk assessment - 장 계획

원고: [chapters/ch06-hara.md](../chapters/ch06-hara.md)

| 항목 | 내용 |
|---|---|
| Part | II. Hazard에서 소프트웨어 요구사항까지 |
| 쓰는 단계 | 단계 1 (뼈대). 단계 2에서 깊게 고친다 |
| 상태 | 깊게 고침 (2026-11-23). 검토 세 번, 통과 (`reviews/2026-11-23-stage2-part2/`) |

## 핵심 질문

무엇이 위험한지 어떻게 빠짐없이 찾고, 등급을 매기는가?

## 다룰 내용

- item definition
- 운전 상황과 hazardous event
- severity, exposure, controllability와 ASIL 결정
- safety goal과 safe state
- fault tolerant time interval
- 다른 분야의 방법과 비교: risk graph, risk matrix, 운용 위험 평가 (20, 21장에서 자세히)
- 로봇과 드론에서는 (단계 3에서 채운다)

## 검토에서 더한 항목 (2026-11-22)

괄호 안은 지적 번호이고, 검토 기록은 `reviews/2026-11-22-plan/`에 있다. 규격의 내용에 관한 항목은 쓰기 전에 확인한다 (RULES.md 5절).

- item의 경계와 가정 (assumption of use) (F-04)
- hazard 5개를 모두 HARA에 올린다: 의도하지 않은 가속, 감속 부족, 잘못된 방향으로 움직임, 구동력의 감소나 상실, 구동 부족 (F-04). 목록은 `example/drive-torque/docs/scope.md`가 원본이다. 2026-11-22에 미국 정부의 보고서와 견주어 고쳤다
- 정지 상태에서의 의도하지 않은 출발은 의도하지 않은 가속의 운전 상황 하나로 다룬다. 같은 hazard라도 기능이 동작하는 상황에 따라 등급이 달라지는 예로 쓴다
- 흔한 오해: 끄면 안전하다 (F-04)
- controllability의 가정을 표에 밝힌다 (F-04)
- FTTI는 hazard의 시간 성질로만 다룬다. 시간 구간을 나누는 것은 7장에서 한다 (F-12)
- ASIL을 정하는 표는 구조와 읽는 법만 설명한다 (F-03)

## 책의 성격에 따른 조정 (2026-11-22)

이 책은 ISO 26262:2018의 원문을 보지 않고 쓴다 (RULES.md 5.6절).

- severity, exposure, controllability의 등급 정의와 ASIL을 정하는 규칙은 2차 자료에 근거했음을 밝힌다.
- 예제의 판정은 방법을 보이기 위한 것이다. 규격의 요구사항을 만족하는지 확인한 것이 아니다.

## 예제 산출물

item definition (E/E 구성도와 item의 경계 포함), HARA 표, safety goal과 safe state, FTTI 가정값

## 관련 규격과 자료

ISO 26262-3; IEC 61508-5

받은 문서: nhtsa-etc-ev-fsa (전기차의 가속 제어 시스템에 대한 functional safety 평가. hazard 분석, ASIL 평가, safety goal)

## 근거 위치 (2026-11-22)

받은 문서에서 이 장을 뒷받침하는 곳이다. 쪽은 PDF 파일의 몇 번째 쪽인지다. 에이전트가 문서를 읽어 뽑은 것이므로, 원고에 쓰기 전에 그 쪽을 직접 읽어 확인한다 (RULES.md 5.2절).

| 문서 | 절 | 쪽 | 뒷받침하는 내용 |
|---|---|---|---|
| `nhtsa-etc-ev-fsa` | 3.1 System Analysis Scope / 3.2 Analysis Assumptions / 3.5.4 Brake Throttle Override | 27-30, 34 | item의 경계와 가정, 전기차 가속 제어 시스템 범위, 브레이크가 가속을 이기는 기능 |
| `nhtsa-etc-ev-fsa` | 4.1 Vehicle-Level Hazards / 4.2 HAZOP (4.2.1-4.2.3) | 37-42 | 7개 vehicle-level hazard (의도하지 않은 가속, 감속 부족, 잘못된 방향, 구동력 상실 등)와 HAZOP malfunction 도출 |
| `nhtsa-etc-ev-fsa` | 5.1 ASIL Assessment Steps (5.1.1 Operational Situations, 5.1.2) / 5.2 ASIL per Hazard | 52-57 | 운전 상황 변수 표와 S/E/C 평가, hazard별 최고 ASIL 선택 (ISO 26262:2011 기준) |
| `nhtsa-etc-ev-fsa` | 6 Vehicle-Level Safety Goals / 8.2 Example Safe States | 58, 67-68 | safety goal 표, safe state가 "완전 정지"가 아니라 정상, 성능 저하, 토크 0 중에서 고려됨 (끄면 안전하다는 오해) |
| `nhtsa-etc-ev-fsa` | 10.1-10.3 Observations | 101-103 | 분석자마다 ASIL이 달라지는 사례, controllability 판단의 객관 자료 부족 (controllability 가정을 밝히는 근거) |
| `nasa-gb-8719-13` | 2.3.1 Preliminary Hazard Analysis (PHA) / 6.5.4 Timing, Sizing and Throughput Considerations (Time to Criticality) | 27-28, 117 | fault에서 위험 상태까지 걸리는 시간(time to criticality)과 automatic safing 개념 (FTTI와 같은 시간 성질, 용어는 다름) |
| `nhtsa-safety-standards-assessment` | 3.4.2 Hazard and Safety Analysis in ISO 26262 / 3.6 Risk Assessment Approach | 23-29 | item 수준 hazard analysis 방법 나열과 risk assessment 방식 비교 (2011 판 기준) |
| `stpa-handbook` | Ch.2 Step 1 Defining the purpose of the analysis (losses, hazards, constraints) | 14-23 | loss, hazard, safety constraint 정의 방식 (HARA를 보완하는 다른 방법) |

### 받은 문서에 근거가 없는 항목

이 항목은 다른 공개 문서를 찾거나, `(2차 자료)`로 밝히거나, 쓰지 않는다.

- ASIL 결정표와 S, E, C 등급의 정의 - ISO 26262-3 원문이 없다. nhtsa-etc 54-55쪽이 규격의 표를 옮겨 싣고 있으나 2011년 판이고, 책에 옮기지 않는다. 등급의 뜻은 그 보고서의 설명과 예로 소개한다
- FTTI의 정의 원문 - nhtsa-etc에는 정의 문장이 없고 쓰임만 있다 (71-74쪽). autosar-e2e p244의 한 줄과 nasa-gb p117의 time to criticality로 설명한다
- risk graph, risk matrix(IEC 61508-5) - 슬라이드에 없다. nasa-gb의 risk matrix(p38-39)와 mil-std 범주만 있다
