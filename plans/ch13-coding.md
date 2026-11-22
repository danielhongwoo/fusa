# 13장. Coding for safety - 장 계획

원고: [chapters/ch13-coding.md](../chapters/ch13-coding.md)

| 항목 | 내용 |
|---|---|
| Part | III. 안전한 소프트웨어 만들기 |
| 쓰는 단계 | 단계 2 (살 붙이기) |
| 상태 | 미착수 |

독자는 임베디드 개발 경험이 있다 (2026-11-22 결정). 이 장에서 임베디드의 기초는 다시 설명하지 않고, 같은 주제를 안전의 관점에서만 다룬다.

## 핵심 질문

언어와 코딩 습관은 안전에 얼마나 기여하는가?

## 다룰 내용

- language subset과 coding standard: MISRA C:2025, MISRA C++:2023, CERT C
- undefined behavior와 unspecified behavior
- defensive programming
- 동적 메모리, 재귀, interrupt, 동시성에 대한 제한
- 정수 overflow와 floating point
- 복잡도 관리
- Ada/SPARK와 Rust의 위치
- coding standard에서 벗어나는 경우 (deviation)의 관리

## 검토에서 더한 항목 (2026-11-22)

괄호 안은 지적 번호이고, 검토 기록은 `reviews/2026-11-22-plan/`에 있다. 규격의 내용에 관한 항목은 쓰기 전에 확인한다 (RULES.md 5절).

- interrupt와 공유 data: 반드시 깨지는 짧은 예 1개와 대책 (critical section, 이중 buffer, 쓰는 쪽을 하나로) (E-07)
- build 설정이 안전에 미치는 영향: warning 수준, 최적화, volatile, 정수의 크기 (E-09)
- MISRA를 준수한다는 주장과 일부 규칙을 검사한다는 것의 차이 (E-18)
- Ada와 SPARK는 한 문단, Rust는 1-2쪽으로 줄인다 (E-14)

## 책의 성격에 따른 조정 (2026-11-22)

이 책은 ISO 26262:2018의 원문을 보지 않고 쓴다 (RULES.md 5.6절).

- 등급에 따라 어떤 coding 규칙과 기법이 권장되는지를 표로 싣지 않는다. 근거는 받은 문서 (nasa-gb-8719-13, misra-compliance-2020)에서 든다.

## 예제 산출물

예제의 coding guideline, 정적 분석 설정, deviation 기록 예

## 관련 규격과 자료

ISO 26262-6; IEC 61508-3, -7; MISRA 문서

받은 문서: misra-compliance-2020, nasa-gb-8719-13

## 근거 위치 (2026-11-22)

받은 문서에서 이 장을 뒷받침하는 곳이다. 쪽은 PDF 파일의 몇 번째 쪽인지다. 에이전트가 문서를 읽어 뽑은 것이므로, 원고에 쓰기 전에 그 쪽을 직접 읽어 확인한다 (RULES.md 5.2절).

| 문서 | 절 | 쪽 | 뒷받침하는 내용 |
|---|---|---|---|
| `misra-compliance-2020` | 2 The software development process (2.4 Style guide, 2.6 Tool management) / 3 Fundamental elements of compliance (3.1-3.5 Decidability) | 10-19 | 지침 분류, 분석 범위, enforcement plan, 정적 분석 tool의 false positive와 undecidable 지침 |
| `misra-compliance-2020` | 4 Deviations (4.1-4.4) / 5 Guideline re-categorization / 6 Adopted code | 20-27 | deviation record와 permit, 정당화 방법, adopted code 처리 |
| `misra-compliance-2020` | 7 Claiming MISRA compliance (7.1-7.3) / Appendix A, B, C | 28-31, 33-39 | 준수 주장의 요건 (guideline compliance summary)과 준수한다는 주장 vs 일부 규칙 검사의 차이 |
| `nasa-gb-8719-13` | 4.6 Good Programming Practices / 7.4.5 Language Restrictions and Coding Standards / 7.4.6 Defensive Programming / 7.4.8 Complexity | 93-98, 146-152 | safe subset과 coding standard 개념, 방어적 프로그래밍, 복잡도 관리 |
| `nasa-gb-8719-13` | 11.1 Programming Languages (11.1.1 Safe Subsets, 11.1.2 Insecurities, 11.1.4 Languages, 11.1.6 Recommendations) | 208-233 | 언어별 안전 위험 (C, C++, Ada 등), 안전한 부분집합 (기준 시점은 2004년경, 최신 언어 아님) |
| `nasa-gb-8719-13` | 8.4.1 Coding Checklists and Standards / 8.5.4 Unused Code Analysis / 8.5.5 Interrupt Analysis | 169-174 | coding 점검표, 인터럽트 분석, 사용하지 않는 코드 |
| `koopman-toyota-ua` | slides 35-43 (MISRA C, Code Complexity, Global Variables, Concurrency, Recursion) | 35-43 | 전역 변수, race condition, 재귀, 복잡도에 대한 구체 사례 (원고 측 전문가 분석) |
| `ariane-501-report` | 2.1 / 2.2 보호되지 않은 정수 변환 | 8-10 | 정수 변환 overflow가 operand error로 이어진 사례 (OCR본) |

### 받은 문서에 근거가 없는 항목

이 항목은 다른 공개 문서를 찾거나, `(2차 자료)`로 밝히거나, 쓰지 않는다.

- MISRA C:2025, MISRA C++:2023, CERT C의 규칙 - misra-compliance-2020은 준수 절차 문서이고 규칙 본문이 아니다
- Ada/SPARK, Rust - nasa-gb 11.1 (2004년경)에 Ada 있음. Rust는 없다
- build 설정(최적화, volatile, 경고 수준)의 영향 - 직접 서술 없음
- interrupt와 공유 data의 깨지는 예 - nasa-gb p94-97 지침만, koopman 41-42 (race condition)로 간접
