# 12장. Software safety mechanism - 장 계획

원고: [chapters/ch12-safety-mechanisms.md](../chapters/ch12-safety-mechanisms.md)

| 항목 | 내용 |
|---|---|
| Part | III. 안전한 소프트웨어 만들기 |
| 쓰는 단계 | 단계 1 (뼈대). 단계 2에서 깊게 고친다 |
| 상태 | 미착수 |

독자는 임베디드 개발 경험이 있다 (2026-11-22 결정). 이 장에서 임베디드의 기초는 다시 설명하지 않고, 같은 주제를 안전의 관점에서만 다룬다.

## 핵심 질문

고장을 제때 감지하고 반응하는 구체적 수단은 무엇인가?

## 다룰 내용

- watchdog (window 방식, 질의-응답 방식)과 program flow monitoring
- end-to-end 통신 보호: CRC, sequence counter, timeout
- memory protection과 stack 감시
- 입력 타당성 검사: range check, plausibility check, 센서 간 비교
- 중요 데이터의 중복 저장
- error handling 전략과 fault reaction
- safety mechanism 자체의 고장과 그 검사
- 로봇과 드론에서는 (단계 3에서 채운다)

## 검토에서 더한 항목 (2026-11-22)

괄호 안은 지적 번호이고, 검토 기록은 `reviews/2026-11-22-plan/`에 있다. 규격의 내용에 관한 항목은 쓰기 전에 확인한다 (RULES.md 5절).

- startup과 reset 동작: 출력의 기본값, self test의 순서, reset 원인의 처리, reset이 반복될 때 (E-06)
- 비휘발성 memory의 data 무결성: 이중 저장, CRC와 version, 쓰는 도중의 전원 상실 (E-06)
- fault 기록: 진단 코드 (DTC), debounce, 해제 조건 (E-10)
- 이 장의 mechanism과 AUTOSAR 모듈의 대응표 (E-11)
- E2E 보호 (safety)와 SecOC (security)의 차이 한 문단 (F-26)
- watchdog 주기와 task 주기를 7장의 시간 예산과 잇는다 (F-12)
- sim이 보이는 것과 못 보이는 것 표 (E-15)

## 예제 산출물

safety mechanism 구현, mechanism마다 덮는 fault 목록

## 근거

ISO 26262-6; IEC 61508-7; AUTOSAR 공개 문서

받은 문서: autosar-e2e-protocol, autosar-safety-measures
