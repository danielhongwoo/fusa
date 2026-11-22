# 3장. Risk와 integrity level - 장 계획

원고: [chapters/ch03-risk-and-integrity-level.md](../chapters/ch03-risk-and-integrity-level.md)

| 항목 | 내용 |
|---|---|
| Part | I. 사고방식과 기본 개념 |
| 쓰는 단계 | 단계 1 (뼈대). 단계 2에서 깊게 고친다 |
| 상태 | 미착수 |

## 핵심 질문

얼마나 안전해야 충분한가? 그 답이 어떻게 개발 방법의 엄격함으로 바뀌는가?

## 다룰 내용

- risk는 severity와 발생 가능성의 조합
- tolerable risk, ALARP, risk reduction, safety function
- SIL, ASIL, PL, SAIL, DAL: 분야마다 다른 등급 체계
- 하드웨어에는 수치 목표를, 소프트웨어에는 방법과 엄격함을 요구하는 이유
- integrity level에 대한 흔한 오해
- 로봇과 드론에서는 (단계 3에서 채운다)

## 검토에서 더한 항목 (2026-11-22)

괄호 안은 지적 번호이고, 검토 기록은 `reviews/2026-11-22-plan/`에 있다. 규격의 내용에 관한 항목은 쓰기 전에 확인한다 (RULES.md 5절).

- demand mode (low demand, high demand, continuous)와 PFD, PFH가 둘인 이유 (F-13)
- 등급은 제품이 아니라 safety function과 요구사항의 속성이라는 점. QM의 뜻 (F-13)
- systematic capability (F-13)
- 흔한 오해: SAIL을 제품의 등급으로 읽는 것 (F-07)

## 예제 산출물

없음 (6장에서 실제 등급을 정한다)

## 근거

IEC 61508-1, -5; ISO 26262-3

받은 문서: iec-61508-overview-slides
