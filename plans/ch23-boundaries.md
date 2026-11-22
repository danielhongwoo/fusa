# 23장. Functional safety의 경계 - 장 계획

원고: [chapters/ch23-boundaries.md](../chapters/ch23-boundaries.md)

| 항목 | 내용 |
|---|---|
| Part | V. 넓히기 |
| 쓰는 단계 | 단계 3 (넓히기) |
| 상태 | 미착수 |

## 핵심 질문

고장이 없어도 위험할 수 있다면, functional safety는 어디까지 책임지는가?

## 다룰 내용

- 의도한 기능의 한계에서 오는 위험: SOTIF (ISO 21448)
- cybersecurity와의 상호작용: ISO/SAE 21434
- machine learning을 쓰는 기능의 안전: ISO/PAS 8800, ISO/IEC TR 5469
- 자율 시스템: UL 4600, ISO/TS 5083
- 멈출 수 없는 시스템: fail-operational 요구

## 검토에서 더한 항목 (2026-11-22)

괄호 안은 지적 번호이고, 검토 기록은 `reviews/2026-11-22-plan/`에 있다. 규격의 내용에 관한 항목은 쓰기 전에 확인한다 (RULES.md 5절).

- 지도 수준으로 쓴다 (E-14, F-27)

## 예제 산출물

없음

## 관련 규격과 자료

쓰는 시점에 정한다

## 근거 위치 (2026-11-22)

받은 문서에서 이 장을 뒷받침하는 곳이다. 쪽은 PDF 파일의 몇 번째 쪽인지다. 에이전트가 문서를 읽어 뽑은 것이므로, 원고에 쓰기 전에 그 쪽을 직접 읽어 확인한다 (RULES.md 5.2절).

| 문서 | 절 | 쪽 | 뒷받침하는 내용 |
|---|---|---|---|
| `stpa-handbook` | Ch.1 Introduction (unsafe interactions without component failures) / Appendix E | 4-11, 167-168 | 고장이 없어도 요구사항이 만족된 채 사고가 나는 사례 (기능 안전의 경계를 보이는 일반 근거) |
| `b737max-jatr` | Letter to FAA / Executive summary (compliance does not necessarily ensure safety) | 3-4 | 규정 준수가 곧 안전은 아니라는 지적 (항공) |
| `nasa-toyota-ua-report` | 6.3 Human Factors on UA Events and Current Trends in Automotive Technologies (6.3.1-6.3.5) | 41-47 | 운전자 인식, shared control authority 등 인간 요인 (고장 없는 위험) |
| `nasa-gb-8719-13` | 11.8 AI and Autonomous Systems (11.8.1-11.8.3) / 11.9 Human Factors in Software Safety | 254-269 | 자율 시스템과 인간 요인의 안전 문제 (2004년경 자료, 최신 ML 아님) |
| `nhtsa-safety-standards-assessment` | 3.10 Human Factors Consideration | 32-33 | 규격들이 인간 요인을 다루는 정도 비교 |
| `avizienis-2004-taxonomy` | 2.3 / 4.4 Dependability, high confidence, survivability, trustworthiness | 6-7, 23 | safety와 security가 같은 dependability 틀 안에서 속성으로 나뉜다는 정리 |
| `easa-sc-light-uas-medium-risk` | Applicability / SUBPART A - Light-UAS.2000 note | 3, 8 | 자율 운용(autonomous operation) 등 새로운 기술에는 추가 special condition이 필요할 수 있다는 서술 (자율 시스템 항목) |
| `easa-moc-light-uas-2510` | Applicability | 2 | Artificial Intelligence 기술은 이 MoC의 범위 밖이고 별도 compliance 입증이 필요할 수 있다는 서술 (machine learning 항목) |
| `easa-moc-light-uas-high-risk-2510` | Applicability | 2-3 | AI/ML 기법은 이 MoC의 범위 밖이고 EASA와 조기 협의를 권고한다는 서술 (machine learning 항목) |
| `easa-sc-light-uas-medium-risk` | Light-UAS.2500 (note), Light-UAS.2730 C2 Link Security | 17, 25 | 안전 기능의 오동작 원인으로 의도적 무단 전자 간섭(cybersecurity)을 고려하고 C2 link 보안을 요구하는 서술 (cybersecurity와의 상호작용 항목) |
| `easa-moc-light-uas-2510` | Applicability | 2 | safety 평가와 cybersecurity 평가가 서로 입력을 주고받는다(failure condition 분류가 cybersecurity 평가의 입력)는 서술 |
| `sora-2-5-main-body` | 1.3 Applicability, (f) | 19 | cyber security는 SORA의 별도 Cyber Safety Extension에서 다룬다는 서술 |
| `easa-moc-light-uas-high-risk-2510` | Principles of Fail-Safe design concept | 7 | 단일 고장이 catastrophic이 되면 안 된다는 fail-safe 설계 개념 (fail-operational 항목은 직접 근거 없음. 아래 gaps 참조) |

### 받은 문서에 근거가 없는 항목

이 항목은 다른 공개 문서를 찾거나, `(2차 자료)`로 밝히거나, 쓰지 않는다.

- SOTIF (ISO 21448), ISO/SAE 21434, ISO/PAS 8800, ISO/IEC TR 5469, UL 4600, ISO/TS 5083 - 받은 문서에 전혀 없다
- ML 기반 기능의 안전, fail-operational 요구 - 없음 (nasa-gb 11.8은 2004년경 자율 시스템)
- SOTIF(ISO 21448), ISO/SAE 21434, ISO/PAS 8800, ISO/IEC TR 5469, UL 4600, ISO/TS 5083 - 받은 문서에 없다
- fail-operational 요구 - 직접 근거가 없다. 단일 고장이 catastrophic이 되면 안 된다는 fail-safe 설계 개념(MoC high risk p7)만 있다
