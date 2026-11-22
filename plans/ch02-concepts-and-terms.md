# 2장. 기본 개념과 용어 - 장 계획

원고: [chapters/ch02-concepts-and-terms.md](../chapters/ch02-concepts-and-terms.md)

| 항목 | 내용 |
|---|---|
| Part | I. 사고방식과 기본 개념 |
| 쓰는 단계 | 단계 1 (뼈대). 단계 2에서 깊게 고친다 |
| 상태 | 미착수 |

## 핵심 질문

safety, reliability, availability, security는 어떻게 다른가?

## 다룰 내용

- harm, hazard, hazardous event, risk
- fault -> error -> failure
- random hardware failure와 systematic failure. 소프트웨어 failure는 모두 systematic이라는 말의 뜻
- safe state, fail-safe, fail-operational
- functional safety의 정의와 범위: 기능이 올바르게 동작하는 것에 의존하는 안전

## 검토에서 더한 항목 (2026-11-22)

괄호 안은 지적 번호이고, 검토 기록은 `reviews/2026-11-22-plan/`에 있다. 규격의 내용에 관한 항목은 쓰기 전에 확인한다 (RULES.md 5절).

- 흔한 오해: 소프트웨어 failure는 모두 systematic이지만, memory의 bit 반전 같은 random hardware fault는 소프트웨어의 동작으로 나타난다 (F-13)

## 예제 산출물

예제 시스템에서 무엇이 hazard이고 무엇이 fault, failure인지 정리한 표

## 근거

IEC 61508-4, ISO 26262-1, Avizienis 외 (2004)

받은 문서: avizienis-2004-taxonomy (학술지 판이 아니라 기술 보고서 판)
