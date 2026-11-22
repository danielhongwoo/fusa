# 부록 B. 규격 구조 대응표

책의 장이 규격의 어느 Part에 해당하는지를 보인다. 4장에서 설명한 것을 책 전체로 넓힌 표다.

## 읽는 법

- 이 표는 제목 수준의 대응이다. Part의 제목을 보고 이 책이 정했다. 장의 내용이 그 Part의 요구사항을 설명한다는 뜻이 아니다. 이 책은 ISO 26262와 IEC 61508의 원문을 보지 않고 쓴다.
- Part의 제목은 발행 기관의 목록에서 확인했다. 조항 번호는 적지 않는다.
- 기준 판은 ISO 26262:2018과 IEC 61508:2010이다. 다음 판에서 Part의 제목이 바뀌는 것이 있다 (4장).
- "상태"가 "쓰기 전"인 장은 계획의 대응이다. 장을 쓰면서 고친다.

## 장에서 규격으로

| 장 | 제목 | ISO 26262 | IEC 61508 | 그 밖의 문서 | 상태 |
|---|---|---|---|---|---|
| 1 | 소프트웨어가 사람을 다치게 할 때 | - | - | 사고 조사 보고서 | 초고 |
| 2 | 기본 개념과 용어 | 1 | 4 | | 뼈대 |
| 3 | Risk와 integrity level | 3, 9 | 1, 5 | ISO 13849-1, SORA | 뼈대 |
| 4 | 규격 지도와 규격 읽는 법 | 1, 10 | 1 | ISO/IEC Directives Part 2 | 초고 |
| 5 | Safety lifecycle과 safety management | 2, 8 | 1 | | 초고 |
| 6 | Hazard analysis and risk assessment | 3 | 5 | | 뼈대 |
| 7 | Safety concept | 3, 4, 9 | 1, 2 | | 뼈대 |
| 8 | Safety analysis 기법 | 9 | 7 | | 쓰기 전 |
| 9 | 소프트웨어 엔지니어가 알아야 할 하드웨어 | 5, 11 | 2, 6 | | 쓰기 전 |
| 10 | Software safety requirements | 6, 8 | 3 | | 뼈대 |
| 11 | Software architecture for safety | 6, 9 | 3 | | 뼈대 |
| 12 | Software safety mechanism | 6 | 3, 7 | AUTOSAR의 공개 문서 | 뼈대 |
| 13 | Coding for safety | 6 | 3, 7 | MISRA Compliance, SEI CERT C | 쓰기 전 |
| 14 | 플랫폼: RTOS, OS, multicore | 6 | 3 | | 쓰기 전 |
| 15 | Verification 전략 | 6 | 3, 7 | | 쓰기 전 |
| 16 | Testing | 6 | 3 | | 뼈대 |
| 17 | Tool과 기존 소프트웨어 | 8, 10 | 3 | | 쓰기 전 |
| 18 | 변경, 형상, 릴리스 이후 | 7, 8 | 1 | | 쓰기 전 |
| 19 | Safety case와 assessment | 2 | 1 | GSN Community Standard | 뼈대 |
| 20 | 로봇 | - | - | ISO 12100, ISO 13849-1, IEC 62061 | 쓰기 전 |
| 21 | 드론 | - | - | SORA, EASA의 문서 | 쓰기 전 |
| 22 | 그 밖의 분야 | - | - | DO-178C, EN 50716, IEC 62304 | 쓰기 전 |
| 23 | Functional safety의 경계 | - | - | | 쓰기 전 |
| 24 | 실무에 적용하기 | - | - | | 쓰기 전 |

## 규격에서 장으로: ISO 26262:2018

| Part | 제목 | 이 책의 장 |
|---|---|---|
| 1 | Vocabulary | 2, 4 |
| 2 | Management of functional safety | 5, 19 |
| 3 | Concept phase | 3, 6, 7 |
| 4 | Product development at the system level | 7 |
| 5 | Product development at the hardware level | 9 |
| 6 | Product development at the software level | 10-16 |
| 7 | Production, operation, service and decommissioning | 18 |
| 8 | Supporting processes | 5, 10, 17, 18 |
| 9 | Automotive safety integrity level (ASIL)-oriented and safety-oriented analyses | 3, 7, 8, 11 |
| 10 | Guidelines on ISO 26262 | 4, 17 |
| 11 | Guidelines on application of ISO 26262 to semiconductors | 9 |
| 12 | Adaptation of ISO 26262 for motorcycles | 다루지 않는다 |

## 규격에서 장으로: IEC 61508:2010

| Part | 제목 | 이 책의 장 |
|---|---|---|
| 1 | General requirements | 3, 4, 5, 7, 18, 19 |
| 2 | Requirements for electrical/electronic/programmable electronic safety-related systems | 7, 9 |
| 3 | Software requirements | 10-17 |
| 4 | Definitions and abbreviations | 2 |
| 5 | Examples of methods for the determination of safety integrity levels | 3, 6 |
| 6 | Guidelines on the application of IEC 61508-2 and IEC 61508-3 | 9 |
| 7 | Overview of techniques and measures | 8, 12, 13, 15 |

## 예제의 산출물

예제의 산출물이 어느 Part에 해당하는지는 4장의 "관통 예제에 적용"에 있다. 예제의 산출물 전체의 목록은 부록 C에 둔다.
