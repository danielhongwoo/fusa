# 5장. Safety lifecycle과 safety management - 장 계획

원고: [chapters/ch05-safety-lifecycle.md](../chapters/ch05-safety-lifecycle.md)

| 항목 | 내용 |
|---|---|
| Part | II. Hazard에서 소프트웨어 요구사항까지 |
| 쓰는 단계 | 단계 2 (살 붙이기) |
| 상태 | 초고 (2026-11-22). 읽기 메모는 `notes/reading/`에 있다 |

## 핵심 질문

안전은 왜 기술만이 아니라 프로세스와 조직의 문제인가?

## 다룰 내용

- safety lifecycle과 V-model
- safety plan, 역할과 책임, safety culture
- confirmation measure (review, audit, assessment)와 independence
- 공급망에서의 책임 분담 (development interface agreement)
- tailoring

## 검토에서 더한 항목 (2026-11-22)

괄호 안은 지적 번호이고, 검토 기록은 `reviews/2026-11-22-plan/`에 있다. 규격의 내용에 관한 항목은 쓰기 전에 확인한다 (RULES.md 5절).

- confirmation measure를 무엇을, 언제, 누가 하는가로 정리한다. 누가에는 독립성의 수준이 들어간다 (F-16)
- verification review (작업물이 맞는가)와 confirmation review (규격을 따랐는가)를 구분한다 (F-16)
- 평가자가 보는 것은 19장으로 넘긴다 (F-16)

## 책의 성격에 따른 조정 (2026-11-22)

이 책은 ISO 26262:2018의 원문을 보지 않고 쓴다 (RULES.md 5.6절).

- ISO 26262가 정한 역할, 독립성의 수준, confirmation measure의 세부는 2차 자료에 근거했음을 밝히고 짧게 다룬다. 왜 그런 장치가 필요한지에 무게를 둔다.

## 예제 산출물

예제 프로젝트의 간단한 safety plan

## 관련 규격과 자료

ISO 26262-2, -8; IEC 61508-1

## 근거 위치 (2026-11-22)

받은 문서에서 이 장을 뒷받침하는 곳이다. 쪽은 PDF 파일의 몇 번째 쪽인지다. 에이전트가 문서를 읽어 뽑은 것이므로, 원고에 쓰기 전에 그 쪽을 직접 읽어 확인한다 (RULES.md 5.2절).

| 문서 | 절 | 쪽 | 뒷받침하는 내용 |
|---|---|---|---|
| `iec-61508-overview-slides` | slides 19-22 (HSE Out of control, Primary cause of control system failure, Safety Lifecycle, Compliance) | 19-22 | 제어 시스템 고장의 원인 대부분이 명세 단계에서 만들어짐 (lifecycle 필요성), 3개 safety lifecycle, 기능 안전 관리와 competence |
| `nasa-gb-8719-13` | Chapter 3 Software Safety Planning (3.1, 3.2 Tailoring) | 33-46 | safety 노력의 범위 결정, tailoring, 혼합 수준 프로젝트 |
| `nasa-gb-8719-13` | 4.2.1 Software Lifecycles / 4.4 Tailoring your process / 5.4 Independent Verification and Validation | 53-61, 87, 103 | lifecycle 모델 (waterfall 등), 프로세스 tailoring, IV&V에 의한 독립성 |
| `nasa-gb-8719-13` | 12.2 Contractor-developed Software (12.2.1-12.2.4) | 282-287 | 계약자 선정, 계약에 포함할 항목, 공정 감시 (공급망 책임 분담의 NASA식 예) |
| `nhtsa-safety-standards-assessment` | 3.9 System Lifecycle Consideration / 3.11 Review, Audit, and Certification | 32-34 | 규격별 lifecycle 범위와 review/audit 요구 비교 (ISO 26262:2011 기준) |
| `b737max-jatr` | R6.7 independent system safety function / Recommendation R6 | 50-53 | 설계 조직과 독립된 system safety 기능과 safety management system 권고 |
| `koopman-toyota-ua` | slides 26-27, 46 (Required Level of Rigor, Toyota Level of Rigor, Safety Culture) | 26-27, 46 | 규격을 따르지 않은 개발 수준과 V 과정 일부에 대한 지식 부재 지적 (safety culture 사례, 원고 측 주장) |
| `autosar-safety-measures` | 3.4 Functional Safety Measures not delivered by AUTOSAR | 45-46 | 공급자(AUTOSAR)가 제공하는 범위와 사용자에게 남는 범위의 분담 |

### 받은 문서에 근거가 없는 항목

이 항목은 다른 공개 문서를 찾거나, `(2차 자료)`로 밝히거나, 쓰지 않는다.

- ISO 26262의 역할, 독립성 수준, confirmation measure, development interface agreement - 받은 문서에 규격 내용이 없다 (autosar p46 목록과 jatr R6.7의 독립 safety 기능이 간접 근거)
- safety plan의 항목, safety culture 정의 - nasa-gb 3장 외에 자동차 규격 근거가 없다
