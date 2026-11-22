# 부록 E. 차량 E/E 최소 지식 - 장 계획

원고: [chapters/appendix-e-vehicle-ee-basics.md](../chapters/appendix-e-vehicle-ee-basics.md)

| 항목 | 내용 |
|---|---|
| 쓰는 단계 | 단계 1에서 뼈대 (1-2쪽). 단계 2에서 완성 |
| 상태 | 미착수 |

2026-11-22 검토에서 더했다 (E-01, F-24). 독자는 임베디드 개발 경험이 있으므로 MCU, interrupt, RTOS 같은 기초는 다루지 않는다. 자동차 분야를 모르는 임베디드 엔지니어가 관통 예제를 따라오는 데 필요한 차량의 전자 장치만 다룬다.

## 핵심 질문

관통 예제를 이해하려면 차량의 전자 장치에 대해 최소한 무엇을 알아야 하는가?

## 다룰 내용

- ECU와 차량 network: CAN frame과 CAN의 약점. CAN FD와 Ethernet은 한 문단
- 센서에서 actuator까지의 신호 경로: 가속 페달 센서, 차량 제어기, inverter, 모터
- AUTOSAR Classic의 층과 이 책의 예제 구조의 대응
- 관통 예제의 E/E 구성도: 페달 센서 2채널 -> 차량 제어기 -> CAN -> inverter

## 예제 산출물

관통 예제의 E/E 구성도 (6장의 item definition과 함께 쓴다)

## 근거

받은 문서: autosar-safety-measures, autosar-e2e-protocol
