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

## 관련 규격과 자료

IEC 61508-4, ISO 26262-1, Avizienis 외 (2004)

받은 문서: avizienis-2004-taxonomy (학술지 판이 아니라 기술 보고서 판)

## 근거 위치 (2026-11-22)

받은 문서에서 이 장을 뒷받침하는 곳이다. 쪽은 PDF 파일의 몇 번째 쪽인지다. 에이전트가 문서를 읽어 뽑은 것이므로, 원고에 쓰기 전에 그 쪽을 직접 읽어 확인한다 (RULES.md 5.2절).

| 문서 | 절 | 쪽 | 뒷받침하는 내용 |
|---|---|---|---|
| `avizienis-2004-taxonomy` | 2.2 The Threats to Dependability and Security: Failures, Errors, Faults | 5-6 | failure, error, fault의 정의와 dormant/active fault, partial failure와 degraded mode |
| `avizienis-2004-taxonomy` | 2.3 Dependability, Security, and their Attributes / 4.3 The attributes | 6-7, 22-23 | safety, reliability, availability, integrity, security를 dependability 속성으로 구분하고 safety를 "치명적 결과가 없음"으로 정의 |
| `avizienis-2004-taxonomy` | 3.2 Faults (3.2.1 A Taxonomy of Faults, 3.2.2 On Natural Faults, 3.2.3 Human-Made Faults) | 8-12 | fault 분류 (natural/human-made, 개발/운용, 영구/일시), 재현 가능한 fault와 그렇지 않은 fault |
| `avizienis-2004-taxonomy` | 3.3.1 Service Failures | 13-16 | failure mode와 severity, fail-stop과 fail-passive 같은 failure 모습, safety 관점의 failure 등급 |
| `iec-61508-overview-slides` | slides 8-9 (What is Functional Safety? / Safety Integrity), slides 12-13 (Failure Categories) | 8-9, 12-13 | functional safety의 정의 (시스템이 입력에 올바로 동작하는 데 의존하는 안전), random hardware failure와 systematic failure 분류 |
| `nasa-gb-8719-13` | 2.1 Hazardous and Safety-critical Software (2.1.1-2.1.7) | 18-23 | hazard의 정의, 소프트웨어가 hazard가 되는 경로, hardware control과 software control의 관계, fault/failure tolerance |
| `koopman-toyota-ua` | slides 29-32 (Random HW Faults & Safe Systems, Fault Containment Regions) | 29-32 | 방사선 등에 의한 random hardware fault가 소프트웨어 동작(bit flip으로 task 사망)으로 나타남 (2장의 흔한 오해 항목) |
| `stpa-handbook` | Ch.1 Introduction (Analytical Decomposition, System Theory) | 4-11 | 부품 고장 없이도 상호작용으로 사고가 난다는 관점 (safety와 reliability가 다른 이유) |

### 받은 문서에 근거가 없는 항목

이 항목은 다른 공개 문서를 찾거나, `(2차 자료)`로 밝히거나, 쓰지 않는다.

- fail-safe, fail-operational의 정의 - avizienis는 fail-stop/fail-passive만 다루고 fail-operational 정의가 없다
- harm, hazardous event, safe state의 규격 정의 - ISO 26262-1, IEC 61508-4 원문이 없다 (nhtsa-etc p67이 safe state를 ISO 26262 Part 1을 인용해 간접 설명)
