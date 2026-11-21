# 16장. Testing

## 장 계획

| 항목 | 내용 |
|---|---|
| Part | IV. 안전함을 보이고 유지하기 |
| 쓰는 단계 | 단계 1 (뼈대). 단계 2에서 깊게 고친다 |
| 목표 분량 | 18쪽 |
| 상태 | 미착수 |

### 핵심 질문

언제 "충분히 테스트했다"고 말할 수 있는가?

### 다룰 내용

- requirements-based testing
- equivalence class와 boundary value
- structural coverage (statement, branch, MC/DC)의 의미와 오용
- unit, integration, embedded software 수준의 test
- fault injection
- back-to-back test
- test 환경 (host, target, hardware-in-the-loop)과 그 차이

### 검토에서 더한 항목 (2026-11-22)

괄호 안은 지적 번호이고, 검토 기록은 `reviews/2026-11-22-plan/`에 있다. 규격의 내용에 관한 항목은 쓰기 전에 확인한다 (RULES.md 5절).

- test 환경 표: model, software, processor, hardware 수준의 in-the-loop test. 이 책에서는 test 환경을 SIL로 줄여 쓰지 않는다 (E-05)
- host에서 얻은 결과가 target에 대해 말해 주는 것과 말해 주지 못하는 것 (E-13)
- 점검 항목: test한 build가 양산 build인가 (E-09)
- MC/DC의 변형 (masking, unique-cause)과 도구마다 결과가 다를 수 있다는 점 (E-17)
- back-to-back test와 model-based development의 연결 (F-25)
- safety validation은 한 문단으로 소개한다 (F-28)

### 예제 산출물

test specification, coverage 보고서, fault injection test 3건 이상 (센서 고착, 통신 값 정지, task 지연), 반응 시간 측정

### 근거

ISO 26262-6; IEC 61508-3; NASA MC/DC tutorial

받은 문서: nasa-mcdc-tutorial, nasa-gb-8719-13

## 본문

아직 쓰지 않았다.
