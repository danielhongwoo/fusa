# 15장. Verification 전략: review, 정적 분석, formal method - 장 계획

원고: [chapters/ch15-verification-strategy.md](../chapters/ch15-verification-strategy.md)

| 항목 | 내용 |
|---|---|
| Part | IV. 안전함을 보이고 유지하기 |
| 쓰는 단계 | 단계 2 (살 붙이기) |
| 상태 | 초고 (2026-11-23, 단계 2의 묶음 4). 검토 전이다 |

## 핵심 질문

테스트만으로 부족한 것은 무엇이고, 무엇으로 메우는가?

## 다룰 내용

- verification과 validation
- review와 inspection
- 정적 분석의 종류와 한계 (잘못된 경고, 놓치는 결함)
- abstract interpretation
- formal verification 개관: model checking, 정리 증명, contract 기반 검증
- integrity level에 따른 방법 선택

## 검토에서 더한 항목 (2026-11-22)

괄호 안은 지적 번호이고, 검토 기록은 `reviews/2026-11-22-plan/`에 있다. 규격의 내용에 관한 항목은 쓰기 전에 확인한다 (RULES.md 5절).

- formal verification은 CBMC로 감시 함수 1개를 증명하는 것으로 보인다 (E-19)
- abstract interpretation은 도구가 무엇을 보장하는가까지만 쓴다 (F-27)

## 책의 성격에 따른 조정 (2026-11-22)

이 책은 ISO 26262:2018의 원문을 보지 않고 쓴다 (RULES.md 5.6절).

- 등급에 따라 어떤 verification 방법이 권장되는지를 표로 싣지 않는다. 방법마다 무엇을 보장하고 무엇을 보장하지 못하는지를 다룬다.

## 예제 산출물

unit 하나에 대한 정적 분석 결과, 간단한 formal verification 시도

## 관련 규격과 자료

ISO 26262-6, -8; IEC 61508-3, -7; DO-333

## 근거 위치 (2026-11-22)

받은 문서에서 이 장을 뒷받침하는 곳이다. 쪽은 PDF 파일의 몇 번째 쪽인지다. 에이전트가 문서를 읽어 뽑은 것이므로, 원고에 쓰기 전에 그 쪽을 직접 읽어 확인한다 (RULES.md 5.2절).

| 문서 | 절 | 쪽 | 뒷받침하는 내용 |
|---|---|---|---|
| `nasa-gb-8719-13` | 6.5.5 Formal Inspections of Software Requirements / 7.5.4 Formal Inspections of Design Products / 8.5.7 Formal Inspections of Source Code | 118-119, 159, 176 | review와 inspection의 방법과 효과 |
| `nasa-gb-8719-13` | 4.2.2.3 Formal Methods (FM) / 6.6.4 Formal Methods - Specification Development | 67-69, 127-130 | formal method의 종류와 적용 수준, 한계 |
| `nasa-toyota-ua-report` | 6.7.3.2 Static Source Code Tools / 6.7.3.3 Logic Model Checking Using SPIN / 6.7.3.4 MATLAB Models | 149-150 | 실제 대형 코드에 적용한 Coverity, CodeSonar, Uno 정적 분석과 SPIN model checking (UA 조사 사례) |
| `misra-compliance-2020` | 3.4 Investigating messages / 3.5 Decidability / 2.6.2-2.6.5 | 13-19 | 정적 분석의 false positive, 놓침, undecidability, tool 검증 |
| `koopman-toyota-ua` | slides 36-37 NASA ETCS Static Analysis Results | 36-37 | 정적 분석 경고 수의 해석 (원고 측 전문가 의견) |
| `nasa-gb-8719-13` | 5.5 Safety Analyses / 6.6 Software Requirements Analyses (6.6.2, 6.6.4, 6.6.6, 6.6.7) / 7.5 Design Analyses (7.5.1-7.5.9) / 8.5 Code Analyses (8.5.2-8.5.7, 8.5.10) | 104, 122-134, 155-162, 172-177 | 단계별 분석 기법 목록과 integrity에 따른 선택 |
| `faa-ac-20-115d` | 1. Purpose (DO-333 Formal Methods Supplement), 8. a Use of Supplements | 1, 4-5 | DO-333 supplement을 규제가 인정한다는 사실 (내용은 없음) |

### 받은 문서에 근거가 없는 항목

이 항목은 다른 공개 문서를 찾거나, `(2차 자료)`로 밝히거나, 쓰지 않는다.

- abstract interpretation, CBMC 등 model checker 일반, contract 기반 검증 - 없음 (SPIN은 nasa-toyota 6.7.3.3만)
- 등급별 verification 방법 권장 - ISO 26262-6, IEC 61508-7 원문 없음 (책 방침상 싣지 않음)
