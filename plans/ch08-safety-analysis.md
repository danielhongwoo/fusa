# 8장. Safety analysis 기법 - 장 계획

원고: [chapters/ch08-safety-analysis.md](../chapters/ch08-safety-analysis.md)

| 항목 | 내용 |
|---|---|
| Part | II. Hazard에서 소프트웨어 요구사항까지 |
| 쓰는 단계 | 단계 2 (살 붙이기) |
| 상태 | 미착수 |

## 핵심 질문

설계가 safety goal을 위반할 수 있는 경로를 어떻게 찾는가?

## 다룰 내용

- 원인에서 결과로 (FMEA), 결과에서 원인으로 (FTA)
- HAZOP과 guide word
- STPA: 제어 구조 관점의 분석
- dependent failure analysis: common cause failure와 cascading failure
- 분석 기법을 소프트웨어 아키텍처에 적용하는 법과 한계

## 검토에서 더한 항목 (2026-11-22)

괄호 안은 지적 번호이고, 검토 기록은 `reviews/2026-11-22-plan/`에 있다. 규격의 내용에 관한 항목은 쓰기 전에 확인한다 (RULES.md 5절).

- FTA와 FMEA는 충분히, STPA는 2-3쪽, HAZOP은 소개만 한다 (E-14)
- dependent failure analysis를 11장의 freedom from interference 주장과 잇는다 (F-06)
- 단계 1에서는 이 장의 원고 없이 예제 산출물 (FTA 1개, 독립성 주장 목록)만 먼저 만든다 (F-06)

## 예제 산출물

FTA 1개, 소프트웨어 수준 FMEA 1개, STPA control structure

## 관련 규격과 자료

ISO 26262-9, ISO 26262-6 Annex E; IEC 61508-7; STPA Handbook

받은 문서: stpa-handbook

받은 문서 (추가): nhtsa-etc-ev-fsa (HAZOP, STPA, FMEA를 같은 시스템에 적용한 예)
