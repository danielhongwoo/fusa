# 12장. Software safety mechanism - 장 계획

원고: [chapters/ch12-safety-mechanisms.md](../chapters/ch12-safety-mechanisms.md)

| 항목 | 내용 |
|---|---|
| Part | III. 안전한 소프트웨어 만들기 |
| 쓰는 단계 | 단계 1 (뼈대). 단계 2에서 깊게 고친다 |
| 상태 | 초고 (2026-11-23, 단계 2의 묶음 3). 검토를 거쳤다 (`reviews/2026-11-23-stage2-part3/`) |

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

## 관련 규격과 자료

ISO 26262-6; IEC 61508-7; AUTOSAR 공개 문서

받은 문서: autosar-e2e-protocol, autosar-safety-measures

## 근거 위치 (2026-11-22)

받은 문서에서 이 장을 뒷받침하는 곳이다. 쪽은 PDF 파일의 몇 번째 쪽인지다. 에이전트가 문서를 읽어 뽑은 것이므로, 원고에 쓰기 전에 그 쪽을 직접 읽어 확인한다 (RULES.md 5.2절).

| 문서 | 절 | 쪽 | 뒷받침하는 내용 |
|---|---|---|---|
| `autosar-safety-measures` | 2.2 Timing Monitoring (Watchdog Manager, supervised entities) / 2.3 Logical Supervision | 22-32 | alive, deadline, logical supervision 기반 watchdog과 program flow monitoring |
| `autosar-e2e-protocol` | 1 Introduction / 6.1-6.2 Overview of E2E / 6.3 Generalized Part (Counter, Data ID, CRC, Timeout; Table 6.1) | 13-15, 27-47 | E2E 보호의 fault model (반복, 손실, 지연, 삽입, masquerade)과 방어 수단 (counter, data ID, CRC, timeout) |
| `autosar-e2e-protocol` | 6.5 Profile 1 / 6.6 Profile 2 (Header Layout, Creation, Evaluation) | 82-128 | CRC와 counter 기반 profile의 실제 구성과 수신측 평가 |
| `autosar-safety-measures` | 2.4 End-2-End Protection / 2.1 Memory Partitioning / 4 Hardware Diagnostics / 3.7 Use of AUTOSAR features | 32-43, 9-21, 65-69, 47-65 | AUTOSAR 모듈과 mechanism 대응표의 재료 (각 mechanism의 fault model, 감지와 반응, 한계) |
| `nasa-gb-8719-13` | 4.6 Good Programming Practices for Safety / 7.4.6 Defensive Programming | 93-98, 147-148 | watchdog, 메모리 검사, 입력 검사, 초기화 방어 기법 |
| `nasa-toyota-ua-report` | 6.7.2 System Integrity and Fail Safe Modes (6.7.2.1 Power On - Reset .. 6.7.2.6 Software Data Checks) / 6.4.4 The Role of Diagnostic Trouble Codes | 62-63, 144-147 | 실제 ECU의 power-on reset, heartbeat, watchdog, data mirroring, DTC 설정의 역할 |
| `nhtsa-etc-ev-fsa` | 8.1 Safety Strategies / 9.2.3 EV PCM Functional Safety Requirements | 66-67, 74-83 | 센서 타당성, main controller 감시(quizzer, seed-and-key), 통신 quality factor, periodic check 요구 문장 |
| `autosar-e2e-protocol` | 6.20.4 FTTI and E2E Parameters | 244-245 | E2E 감지 시간(debounce 창)을 task/통신 주기와 FTTI에 잇는 방법 |

### 받은 문서에 근거가 없는 항목

이 항목은 다른 공개 문서를 찾거나, `(2차 자료)`로 밝히거나, 쓰지 않는다.

- NVM data 무결성(이중 저장, 전원 상실), 반복 reset 처리, DTC debounce 해제 조건 - 깊은 서술 없음 (nasa-gb p93 ROM 검사, nasa-toyota 6.4.4 DTC 개요만)
- SecOC와 E2E의 차이 - 받은 문서에 SecOC가 없다
