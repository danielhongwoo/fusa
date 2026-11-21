# 부록 E. 임베디드 시스템과 차량 E/E 최소 지식

## 장 계획

| 항목 | 내용 |
|---|---|
| 쓰는 단계 | 단계 1에서 뼈대 (3-4쪽). 단계 2에서 완성 |
| 목표 분량 | 12-15쪽 |
| 상태 | 미착수 |

2026-11-22 검토에서 더했다 (E-01, F-24). 독자가 임베디드 경험이 없다는 가정이 확정되면 Part I 끝의 장으로 올린다. 그때까지는 부록으로 두고, 각 장의 "임베디드 상자"가 이 부록을 가리킨다.

### 핵심 질문

이 책의 예제와 safety mechanism을 이해하려면 MCU와 차량의 전자 장치에 대해 최소한 무엇을 알아야 하는가?

### 다룰 내용

- MCU 한 장 그림: CPU, flash, RAM, peripheral, clock, reset
- memory map과 시작 순서
- 주기 task와 interrupt
- 센서 신호가 ADC 값이 되는 경로, PWM 출력
- ECU와 차량 network: CAN frame과 CAN의 약점. CAN FD와 Ethernet은 한 문단
- hardware watchdog과 MPU의 역할
- 하드웨어 추상화 계층 (HAL)과 AUTOSAR Classic의 층
- 관통 예제의 E/E 구성도: 페달 센서 2채널 -> 차량 제어기 -> CAN -> inverter

### 예제 산출물

관통 예제의 E/E 구성도 (6장의 item definition과 함께 쓴다)

### 근거

받은 문서: autosar-safety-measures. 이 부록의 내용은 대부분 규격과 무관한 일반 지식이다.

## 본문

아직 쓰지 않았다.
