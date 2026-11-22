# 6장. Hazard analysis and risk assessment - 장 계획

원고: [chapters/ch06-hara.md](../chapters/ch06-hara.md)

| 항목 | 내용 |
|---|---|
| Part | II. Hazard에서 소프트웨어 요구사항까지 |
| 쓰는 단계 | 단계 1 (뼈대). 단계 2에서 깊게 고친다 |
| 상태 | 미착수 |

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
- hazard 5개를 모두 HARA에 올린다: 의도하지 않은 가속, 의도하지 않은 감속, 잘못된 방향, 정지 상태에서의 출발, 구동력 상실 (F-04)
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
