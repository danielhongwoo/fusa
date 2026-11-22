# 7장. Safety concept: 요구사항을 아래로 내리기 - 장 계획

원고: [chapters/ch07-safety-concept.md](../chapters/ch07-safety-concept.md)

| 항목 | 내용 |
|---|---|
| Part | II. Hazard에서 소프트웨어 요구사항까지 |
| 쓰는 단계 | 단계 1 (뼈대). 단계 2에서 깊게 고친다 |
| 상태 | 미착수 |

## 핵심 질문

safety goal 한 문장이 어떻게 소프트웨어 요구사항 수십 개가 되는가?

## 다룰 내용

- functional safety concept와 technical safety concept
- 요구사항의 계층과 allocation
- hardware-software interface
- fault detection과 fault reaction에 주어진 시간 예산
- ASIL decomposition과 그 전제 조건 (독립성)
- warning과 degradation
- 로봇과 드론에서는 (단계 3에서 채운다)

## 검토에서 더한 항목 (2026-11-22)

괄호 안은 지적 번호이고, 검토 기록은 `reviews/2026-11-22-plan/`에 있다. 규격의 내용에 관한 항목은 쓰기 전에 확인한다 (RULES.md 5절).

- 시간 모델을 그림 하나로 정리한다: FTTI와 그것을 나눈 시간 구간 (fault detection, fault reaction 등) (F-12)
- ASIL decomposition의 조건과 흔한 오용. 나누면 싸진다는 오해 (F-14)
- E-Gas 구조에서 기능 쪽과 감시 쪽의 등급이 정해지는 방식. decomposition과 coexistence의 차이 (F-14)
- fault reaction과 warning, fault 기록 (E-10)

## 책의 성격에 따른 조정 (2026-11-22)

이 책은 ISO 26262:2018의 원문을 보지 않고 쓴다 (RULES.md 5.6절).

- decomposition의 조건, 시간 구간의 이름과 관계 같은 규격의 세부 규칙은 2차 자료로 확인한 범위에서만 쓴다. 용어의 정의는 ISO Online Browsing Platform에서 확인한다.

## 예제 산출물

functional safety concept, technical safety concept (3단계 감시 구조, 하드웨어 가정 목록, 시간 예산표, decomposition 또는 coexistence 판단)

## 관련 규격과 자료

ISO 26262-3, -4, -9

받은 문서: nhtsa-etc-ev-fsa (functional safety concept, safe state, 운전자 경고, functional safety requirement), autosar-safety-measures

## 근거 위치 (2026-11-22)

받은 문서에서 이 장을 뒷받침하는 곳이다. 쪽은 PDF 파일의 몇 번째 쪽인지다. 에이전트가 문서를 읽어 뽑은 것이므로, 원고에 쓰기 전에 그 쪽을 직접 읽어 확인한다 (RULES.md 5.2절).

| 문서 | 절 | 쪽 | 뒷받침하는 내용 |
|---|---|---|---|
| `nhtsa-etc-ev-fsa` | 8 Functional Safety Concept (8.1 Safety Strategies, 8.2 Example Safe States, 8.3 Driver Warning Strategies) | 66-69 | 안전 전략 12개 항목, safe state 후보, 운전자 경고 전략 |
| `nhtsa-etc-ev-fsa` | 9.1 Safety Goals / 9.2 Functional Safety Requirements (9.2.1-9.2.7) | 70-89 | safety goal에서 시스템, pedal, PCM 등 구성요소별 functional safety requirement로 allocation, fault detection time과 FTTI 서술 (예: p72, 74) |
| `nhtsa-etc-ev-fsa` | 9.3 Additional Safety Requirements beyond the Scope of the ISO 26262 Functional Safety Concept (9.3.1-9.3.7) | 89-100 | 하위 구성요소의 technical 수준 요구사항 예 (기술 safety concept 대응) |
| `nhtsa-etc-ev-fsa` | 9.2.3 EV Powertrain Control Module Functional Safety Requirements | 77-83 | ASIL decomposition과 safety mechanism 분류 언급 (p79, p82) |
| `autosar-safety-measures` | 3.7.2 E-Gas Monitoring Related Features (3.7.2.1-3.7.2.4) | 60-65 | E-Gas monitoring concept을 AUTOSAR에서 구현하는 방법 (2차 자료, 원문 아님) |
| `nhtsa-safety-standards-assessment` | 3.6.4 Software Risk Assessment | 29 | 소프트웨어 요구에 ASIL을 물려주는 방식 (ASIL decomposition, Part 9 Clause 5, 2011 판) |
| `nasa-toyota-ua-report` | 6.5 System Fail-Safe Architecture (6.5.1-6.5.3) | 64-83 | prime system + monitor + 다양한 safing 제어, limp home과 fuel cut 같은 단계적 degradation |
| `autosar-e2e-protocol` | 6.20.4 FTTI and E2E Parameters | 244-245 | FTTI = 고장 감지 시간 + 고장 반응 시간으로 나누고 E2E 상태 기계 parameter와 cycle time으로 감지 시간을 맞추는 계산 (시간 예산의 구체 예) |

### 받은 문서에 근거가 없는 항목

이 항목은 다른 공개 문서를 찾거나, `(2차 자료)`로 밝히거나, 쓰지 않는다.

- ASIL decomposition의 조건과 오용 - nhtsa-std p29, nhtsa-etc p79, 82에 언급뿐. 조건(독립성)의 설명이 없다
- E-Gas 3단계 감시 구조 원문과 기능/감시 쪽 등급 부여 - 원문 없음. autosar-safety-measures 3.7.2가 2차 자료
- hardware-software interface 명세 - 어느 문서에도 구체 서술이 없다
