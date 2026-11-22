# 10장. Software safety requirements - 장 계획

원고: [chapters/ch10-software-safety-requirements.md](../chapters/ch10-software-safety-requirements.md)

| 항목 | 내용 |
|---|---|
| Part | III. 안전한 소프트웨어 만들기 |
| 쓰는 단계 | 단계 1 (뼈대). 단계 2에서 깊게 고친다 |
| 상태 | 초고 (2026-11-23, 단계 2의 묶음 3). 검토를 거쳤다 (`reviews/2026-11-23-stage2-part3/`) |

## 핵심 질문

검증할 수 있는 안전 요구사항은 어떻게 쓰는가?

## 다룰 내용

- 좋은 요구사항의 속성: 명확성, 검증 가능성, 추적 가능성
- 요구사항 표기법 (예: EARS)
- 시간, 값의 범위, 고장 시 동작을 빠뜨리지 않는 법
- 양방향 traceability
- safety 요구사항과 그렇지 않은 요구사항의 공존

## 검토에서 더한 항목 (2026-11-22)

괄호 안은 지적 번호이고, 검토 기록은 `reviews/2026-11-22-plan/`에 있다. 규격의 내용에 관한 항목은 쓰기 전에 확인한다 (RULES.md 5절).

- 요구사항 ID 체계와 요구사항을 YAML 파일로 관리하는 방법 (E-26)
- 빠뜨리기 쉬운 항목에 startup과 reset 직후의 동작을 더한다 (E-06)

## 책의 성격에 따른 조정 (2026-11-22)

이 책은 ISO 26262:2018의 원문을 보지 않고 쓴다 (RULES.md 5.6절).

- 규격이 요구하는 요구사항의 속성 목록을 옮기지 않는다. 좋은 요구사항의 속성을 일반적인 근거로 설명한다.

## 예제 산출물

software safety requirements, traceability 표

## 관련 규격과 자료

ISO 26262-6, -8; IEC 61508-3

## 근거 위치 (2026-11-22)

받은 문서에서 이 장을 뒷받침하는 곳이다. 쪽은 PDF 파일의 몇 번째 쪽인지다. 에이전트가 문서를 읽어 뽑은 것이므로, 원고에 쓰기 전에 그 쪽을 직접 읽어 확인한다 (RULES.md 5.2절).

| 문서 | 절 | 쪽 | 뒷받침하는 내용 |
|---|---|---|---|
| `nasa-gb-8719-13` | 6.4 Requirements Management (6.4.1 Specification, 6.4.2 Traceability and Verification, 6.4.3 Change Management) | 109-114 | 요구사항 명세, 추적성, 변경 관리의 일반 지침 |
| `nasa-gb-8719-13` | 6.5 Development of Software Safety Requirements (6.5.1 Generic, 6.5.2 Fault and Failure Tolerance, 6.5.3 Hazardous Commands, 6.5.4 Timing/Sizing) | 114-120 | 빠뜨리기 쉬운 항목 (시간, 값의 범위, 동적 메모리, 초기화, 위험 명령) |
| `nasa-gb-8719-13` | 6.5.5 Formal Inspections / 6.5.7 Checklists and cross references / App.E Requirements State Machines (E.7 Degraded Mode) | 118-121, 338-345 | 요구사항 검토와 state machine 기반 완전성 점검 |
| `nhtsa-etc-ev-fsa` | 9.2 Functional Safety Requirements / 9.3 Additional Safety Requirements | 72-100 | 실제 문장 형태의 자동차 safety requirement 예 202개 중 대표 (시간 제한, 고장 시 safe state 진입 등) |
| `ariane-501-report` | 4 Recommendations (R5: 구현이 가정하는 값 범위 식별) | 17-18 | 요구사항에 변수 범위와 사용 제한이 명시되지 않아 사고 (OCR본) |
| `b737max-jatr` | R6.12 questioning assumptions / R2.8 pilot recognition times | 34-36, 55 | 요구와 가정의 타당성을 근거로 검토해야 한다는 사례 |
| `stpa-handbook` | Ch.2 Step 3 UCA -> safety constraints; Ch.3 requirements generation | 34-41, 54-71 | 분석 결과에서 요구사항을 만드는 흐름 (traceability) |

### 받은 문서에 근거가 없는 항목

이 항목은 다른 공개 문서를 찾거나, `(2차 자료)`로 밝히거나, 쓰지 않는다.

- EARS 등 요구사항 표기법, YAML 관리 - 받은 문서에 없다 (저자 영역)
- 규격이 요구하는 요구사항 속성 - ISO 26262-8, 6 원문 없음 (일반 지침은 nasa-gb 6.4로 대체)
