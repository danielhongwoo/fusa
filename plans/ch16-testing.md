# 16장. Testing - 장 계획

원고: [chapters/ch16-testing.md](../chapters/ch16-testing.md)

| 항목 | 내용 |
|---|---|
| Part | IV. 안전함을 보이고 유지하기 |
| 쓰는 단계 | 단계 1 (뼈대). 단계 2에서 깊게 고친다 |
| 상태 | 뼈대의 초고 (2026-11-22). 단계 2에서 깊게 고친다 |

독자는 임베디드 개발 경험이 있다 (2026-11-22 결정). 이 장에서 임베디드의 기초는 다시 설명하지 않고, 같은 주제를 안전의 관점에서만 다룬다.

## 핵심 질문

언제 "충분히 테스트했다"고 말할 수 있는가?

## 다룰 내용

- requirements-based testing
- equivalence class와 boundary value
- structural coverage (statement, branch, MC/DC)의 의미와 오용
- unit, integration, embedded software 수준의 test
- fault injection
- back-to-back test
- test 환경 (host, target, hardware-in-the-loop)과 그 차이

## 검토에서 더한 항목 (2026-11-22)

괄호 안은 지적 번호이고, 검토 기록은 `reviews/2026-11-22-plan/`에 있다. 규격의 내용에 관한 항목은 쓰기 전에 확인한다 (RULES.md 5절).

- test 환경 표: model, software, processor, hardware 수준의 in-the-loop test. 이 책에서는 test 환경을 SIL로 줄여 쓰지 않는다 (E-05)
- host에서 얻은 결과가 target에 대해 말해 주는 것과 말해 주지 못하는 것 (E-13)
- 점검 항목: test한 build가 양산 build인가 (E-09)
- MC/DC의 변형 (masking, unique-cause)과 도구마다 결과가 다를 수 있다는 점 (E-17)
- back-to-back test와 model-based development의 연결 (F-25)
- safety validation은 한 문단으로 소개한다 (F-28)

## 책의 성격에 따른 조정 (2026-11-22)

이 책은 ISO 26262:2018의 원문을 보지 않고 쓴다 (RULES.md 5.6절).

- 등급에 따라 어떤 test 방법과 coverage가 권장되는지는 2차 자료에 근거했음을 밝힌다. coverage의 의미와 한계에 무게를 둔다.

## 예제 산출물

test specification, coverage 보고서, fault injection test 3건 이상 (센서 고착, 통신 값 정지, task 지연), 반응 시간 측정

## 관련 규격과 자료

ISO 26262-6; IEC 61508-3; NASA MC/DC tutorial

받은 문서: nasa-mcdc-tutorial, nasa-gb-8719-13

## 근거 위치 (2026-11-22)

받은 문서에서 이 장을 뒷받침하는 곳이다. 쪽은 PDF 파일의 몇 번째 쪽인지다. 에이전트가 문서를 읽어 뽑은 것이므로, 원고에 쓰기 전에 그 쪽을 직접 읽어 확인한다 (RULES.md 5.2절).

| 문서 | 절 | 쪽 | 뒷받침하는 내용 |
|---|---|---|---|
| `nasa-mcdc-tutorial` | 2 MC/DC Apologia (2.1 Verification Process, 2.2 Role of Coverage, 2.3 Types of Structural Coverage) | 9-17 | requirements-based와 structural coverage의 역할, statement, decision, condition, MC/DC 비교 |
| `nasa-mcdc-tutorial` | 2.5 More Details about MC/DC / 3 MC/DC Approach / Appendix B | 16-54, 78-83 | unique-cause와 masking MC/DC의 차이 (p19, 38), 단락 평가와 비트 연산에서의 MC/DC (p48-53) |
| `nasa-mcdc-tutorial` | 4 MC/DC Admonitions (4.1 Automation Problems, 4.2 Process Problems) / 5 Assessment Process | 55-68 | coverage tool의 한계와 qualification 요소, coverage 오용 |
| `nasa-gb-8719-13` | 9.4 Testing Techniques (9.4.1, 9.4.2 Test Environment, 9.4.7 Safety Testing, 9.4.9 Computer Models) / 9.5.1 Test Coverage Analysis | 184-198 | 테스트 기법, 환경, 안전 테스트, 모델을 이용한 검증, coverage 해석 |
| `nasa-gb-8719-13` | 8.5.6 Test Coverage Analysis / 9.4.3 Integration Testing | 175, 190 | unit, integration 수준 테스트, software fault injection (p179, 192, 281) |
| `ariane-501-report` | 2.3 The testing and qualification procedures | 11-13 | system test에 실제 장비를 넣지 않은 결정과 그 결과 (OCR본) |
| `koopman-toyota-ua` | slides 19-20 (Didn't Vehicle Testing Make It Safe?, Testing Is Not Enough) | 19-20 | 테스트만으로 안전을 보일 수 없다는 주장 (35백만 마일 테스트 등 수치, 원고 측 전문가 발표) |

### 받은 문서에 근거가 없는 항목

이 항목은 다른 공개 문서를 찾거나, `(2차 자료)`로 밝히거나, 쓰지 않는다.

- back-to-back test, HIL 구분, model/software/processor 수준 in-the-loop 정의 - 없음
- safety validation - 없음
