# 1장. 소프트웨어가 사람을 다치게 할 때 - 장 계획

원고: [chapters/ch01-accidents.md](../chapters/ch01-accidents.md)

| 항목 | 내용 |
|---|---|
| Part | I. 사고방식과 기본 개념 |
| 쓰는 단계 | 단계 2 (살 붙이기) |
| 상태 | 미착수 |

## 핵심 질문

소프트웨어는 닳지도 부러지지도 않는데 어떻게 사고를 일으키는가?

## 다룰 내용

- 사례: Therac-25 방사선 치료기, Ariane 5 Flight 501, Toyota unintended acceleration, Boeing 737 MAX MCAS
- 사례에서 반복되는 패턴: 요구사항의 결함, 검증 없는 재사용, 단일 입력에 대한 의존, 사라진 hardware interlock, 조직 요인
- "버그 없는 코드"와 "안전한 시스템"이 다른 이유

## 검토에서 더한 항목 (2026-11-22)

괄호 안은 지적 번호이고, 검토 기록은 `reviews/2026-11-22-plan/`에 있다. 규격의 내용에 관한 항목은 쓰기 전에 확인한다 (RULES.md 5절).

- 사례의 깊이를 나눈다: Toyota와 737 MAX는 깊게, Therac-25와 Ariane 5는 짧게 (E-14)
- 사례마다 공식 조사의 결론과 다툼이 있는 부분을 나눠 적는다 (F-17)
- 장 끝에서 안전 장치가 없는 토크 제어기 (약 100줄)를 실행해, 센서 값이 고착되면 차가 계속 가속하는 그래프를 보인다 (E-04)

## 예제 산출물

관통 예제 소개

## 관련 규격과 자료

각 사고의 조사 보고서 원문

받은 문서: ariane-501-report, b737max-jatr, b737max-ntsb-asr1901, b737max-knkt-jt610, b737max-house-report, koopman-toyota-ua
