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

## 예제 산출물

예제의 coding guideline, 정적 분석 설정, deviation 기록 예

## 근거

ISO 26262-6; IEC 61508-3, -7; MISRA 문서

받은 문서: misra-compliance-2020, nasa-gb-8719-13
