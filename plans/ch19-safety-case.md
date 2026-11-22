# 19장. Safety case와 assessment - 장 계획

원고: [chapters/ch19-safety-case.md](../chapters/ch19-safety-case.md)

| 항목 | 내용 |
|---|---|
| Part | IV. 안전함을 보이고 유지하기 |
| 쓰는 단계 | 단계 1 (뼈대). 단계 2에서 깊게 고친다 |
| 상태 | 뼈대의 초고 (2026-11-22). 단계 2에서 깊게 고친다 |

## 핵심 질문

흩어진 산출물이 어떻게 "안전하다"는 하나의 주장이 되는가?

## 다룰 내용

- claim, argument, evidence
- Goal Structuring Notation (GSN)
- work product와 safety case의 관계
- confirmation review, functional safety audit, functional safety assessment
- 형식만 갖춘 safety case의 문제
- 로봇과 드론에서는 (단계 3에서 채운다)

## 검토에서 더한 항목 (2026-11-22)

괄호 안은 지적 번호이고, 검토 기록은 `reviews/2026-11-22-plan/`에 있다. 규격의 내용에 관한 항목은 쓰기 전에 확인한다 (RULES.md 5절).

- 한 쪽짜리 safety case가 FTA, 독립성 분석, test를 증거로 가리키게 한다 (F-06)
- 5장과 겹치지 않게, 평가자가 safety case에서 무엇을 보는가에 집중한다 (F-16)

## 책의 성격에 따른 조정 (2026-11-22)

이 책은 ISO 26262:2018의 원문을 보지 않고 쓴다 (RULES.md 5.6절).

- confirmation review, audit, assessment에 관한 규격의 세부 요구는 개념 수준으로 다룬다 (2차 자료). safety case를 만드는 법은 받은 GSN 문서를 근거로 삼는다.

## 예제 산출물

예제 전체의 safety case

## 관련 규격과 자료

ISO 26262-2; GSN Community Standard; UL 4600

받은 문서: gsn-standard-v3

## 근거 위치 (2026-11-22)

받은 문서에서 이 장을 뒷받침하는 곳이다. 쪽은 PDF 파일의 몇 번째 쪽인지다. 에이전트가 문서를 읽어 뽑은 것이므로, 원고에 쓰기 전에 그 쪽을 직접 읽어 확인한다 (RULES.md 5.2절).

| 문서 | 절 | 쪽 | 뒷받침하는 내용 |
|---|---|---|---|
| `gsn-standard-v3` | Part 0: 0:2 Use of Arguments in Assurance Cases / 0:3 What is an Argument? / 0:4 GSN | 10-15 | assurance case, claim, argument, evidence의 정의와 GSN 개요 |
| `gsn-standard-v3` | 1:2 Core GSN (1:2.1 Notation, 1:2.2 Interpretation) | 16-25 | goal, strategy, context, solution 요소와 SupportedBy/InContextOf |
| `gsn-standard-v3` | 2:3 Developing Goal Structures Top-Down: The GSN Six-Step Method | 59-70 | goal 식별부터 solution까지 6단계 |
| `gsn-standard-v3` | 2:5 Common Errors Language / 2:6 Common Errors Structural (Jumping Ahead, Leaps of Faith) | 80-87 | 형식만 갖춘 safety case의 문제 유형 |
| `gsn-standard-v3` | 2:7 Evaluating Goal Structures: A Step-by-Step Approach (2:7.4 Staged Argument Review) | 88-95 | 평가자가 argument를 검토하는 단계 |
| `nhtsa-safety-standards-assessment` | 3.11 Review, Audit, and Certification | 33-34 | ISO 26262가 work product로 safety case를 구성한다는 설명과 비판 (2011 판 기준) |
| `b737max-jatr` | R6 / R7 (human factors) / R6.12 | 50-56 | 규정 준수 중심 증명이 안전 논증을 놓치는 사례 |
| `nasa-gb-8719-13` | 6.4 Requirements Management (safety case 정의 한 문단) | 109 | 규제 기관에 낼 safety case 개념 한 문단 |

### 받은 문서에 근거가 없는 항목

이 항목은 다른 공개 문서를 찾거나, `(2차 자료)`로 밝히거나, 쓰지 않는다.

- UL 4600, ISO 26262-2 confirmation review/audit/assessment 요구 - 규격 원문 없음 (autosar p46의 부재 목록과 nhtsa-std 3.11이 간접)
- 한 쪽짜리 safety case 예제 - GSN 표준에 insulin pump 예(p111-113)는 있으나 자동차 예제는 없다
