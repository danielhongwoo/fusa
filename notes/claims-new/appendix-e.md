# 부록 E 근거 기록 (새 줄)

`notes/claims.md`의 표에 옮길 줄이다. 형식은 그 파일의 "적는 법"을 따른다. 쪽은 PDF 파일의 쪽이다. 모두 진행 에이전트가 쪽을 직접 열어 확인했다.

| ID | 주장 | 근거 | 종류 | 확인한 날 |
|---|---|---|---|---|
| C-E-004 | 페달 위치 센서는 각도를 전압으로 바꾸어 제어기에 보내며, 신호는 직결선이나 차량 bus (예: CAN)로 간다. 제어기는 전압을 토크로 바꾸고 다른 계통의 토크 요구와 조정한다 | nhtsa-etc-ev-fsa, 33쪽 | 1차 | 2026-11-23 |
| C-E-005 | inverter 제어부, gate drive, inverter/converter, 상 전류 센서와 모터 위치 센서의 역할 | nhtsa-etc-ev-fsa, 33-34쪽 | 1차 | 2026-11-23 |
| C-E-006 | 블록 그림: 제동/안정성 제어기가 브레이크 페달 위치와 차량 속도를, 다른 차량 센서가 선택된 기어를 EV PCM에 준다. EV PCM에서 gate drive board로 "Disable Motor (Traction Controller Bypass)" 선이 있다 | nhtsa-etc-ev-fsa, 32쪽 (그림 5. 쪽을 그림으로 그려 눈으로 읽었다) | 1차 | 2026-11-23 |
| C-E-007 | 차량 속도는 제동/안정성 제어 모듈이 준다고 보고서가 가정한다 | nhtsa-etc-ev-fsa, 29쪽 | 1차 | 2026-11-23 |
| C-E-008 | 기어 선택기의 위치를 transmission range sensor가 알린다 | nhtsa-etc-ev-fsa, 33쪽 | 1차 | 2026-11-23 |
| C-E-009 | 보고서의 브레이크 입력은 페달의 각도를 재는 센서 (BPPS)다 | nhtsa-etc-ev-fsa, 35쪽 | 1차 | 2026-11-23 |
| C-E-010 | 제어기는 고장을 찾으면 DTC를 기록하고 limp-home 같은 safe state로 보낼 수 있으며 계기판의 고장 표시등을 켜라고 명령한다. inverter 제어부가 고장이면 그것을 건너뛰고 gate drive와 직접 통신해 전류를 끊을 수 있다 | nhtsa-etc-ev-fsa, 35쪽. nhtsa-etc-gasoline-fsa, 34쪽 | 1차 | 2026-11-23 |
| C-E-011 | 전기차와 내연기관 차의 차이: 방향은 전류가 정하고 구동 계통이 방향을 맡는다, 페달을 놓으면 coast한다, creep은 소프트웨어로 흉내 낸다, 모터는 속도 0에서 stall하지 않지만 EPS가 갑자기 꺼지면 비슷한 상태가 된다 | nhtsa-etc-ev-fsa, 30-31쪽 | 1차 | 2026-11-23 |
| C-E-012 | 가솔린차는 흡입 공기량으로 출력을 조절하고, ECM이 PWM으로 throttle 모터를 구동한다 | nhtsa-etc-gasoline-fsa, 31쪽, 33쪽 | 1차 | 2026-11-23 |
| C-E-013 | 고장 표시등 같은 운전자 알림은 보고서의 범위 밖이다. 범위에는 차량 bus (예: CAN)의 통신이 든다 | nhtsa-etc-ev-fsa, 27-28쪽 | 1차 | 2026-11-23 |
| C-E-014 | 업계에서 흔한 경고의 예: amber (어길 확률 중간), red (높거나 이미 어김), chime | nhtsa-etc-ev-fsa, 68쪽 | 1차 | 2026-11-23 |
| C-E-015 | 그 차의 페달 센서는 VPA1, VPA2를 내고 VPA2는 같은 기울기에 0.8 V 높게 시작한다. 제어기는 두 전압을 견주어 문제를 찾는다 | nasa-toyota-ua-report, 58쪽, 96쪽 | 1차 | 2026-11-23 |
| C-E-016 | 두 센서의 견줌은 고장이 둘을 함께 유효한 전압으로 만들지 않는 한 지켜 주고, offset은 공통 원인 고장을 막으려는 것이다 | nasa-toyota-ua-report, 72쪽 | 1차 | 2026-11-23 |
| C-E-017 | 페달 센서마다 전용의 전원선과 귀선이 있다 | nasa-toyota-ua-report, 96쪽 | 1차 | 2026-11-23 |
| C-E-018 | DTC 표는 센서마다의 낮은/높은 전압과 두 센서의 상관, rationality를 별개 코드로 둔다 | nasa-toyota-ua-report, 63쪽 | 1차 | 2026-11-23 |
| C-E-019 | 페달 센서 하나가 고장으로 판정되면 limp home으로 들어가 남은 센서로 제한된 범위에서 throttle을 제어한다. limp home은 고장 뒤 낮은 속도로 계속 달리게 한다. MIL이 알리고 DTC로 저장한다 | nasa-toyota-ua-report, 49쪽, 67쪽 | 1차 | 2026-11-23 |
| C-E-020 | 고장 모드 표에 "DTC when both Brake Switch poles do not agree"라는 칸이 있다 (cruise control의 줄) | nasa-toyota-ua-report, 78쪽 (쪽을 그림으로 그려 확인) | 1차 | 2026-11-23 |
| C-E-021 | 저항성 단락 상태에서 DTC를 지우고 MIL을 끄면 다시 켜지지 않았지만 동작은 그대로였다 | nasa-toyota-ua-report, 81쪽 | 1차 | 2026-11-23 |
| C-E-022 | CAN CC의 frame: 11 또는 29 bit identifier, 값이 작을수록 높은 우선순위 (bit-wise arbitration), 0-8 byte data, CRC, ACK, 오류 검출 다섯 가지, error frame과 재전송, bus-off | CAN in Automation, "CAN CC", https://www.can-cia.org/can-knowledge/can-cc (2026-11-23에 봄. 날짜 없는 웹 페이지. scratchpad에 받아 글을 대조했다) | 1차 (표준 단체의 설명 페이지) | 2026-11-23 |
| C-E-023 | E2E가 가정하는 통신 고장 목록과, 그 원인에 transceiver 고장, EMC, ECU와 gateway 안 통신 소프트웨어 (RTE, COM, network stack)의 체계적 고장이 든다 | autosar-safety-measures, 33-34쪽 | 1차 | 2026-11-23 |
| C-E-024 | SW-C는 RTE 위에 있고 하드웨어에 독립이며 정보를 RTE로만 주고받는다. runnable은 OS task에 넣어 실행한다. partition 사이 메모리 보호. Watchdog Manager는 basic software module이다. CDD는 입출력에 직접 닿고, 감시 소프트웨어를 CDD에 두는 설계가 있다 | autosar-safety-measures, 10쪽, 11쪽, 12쪽, 23쪽, 60쪽 | 1차 | 2026-11-23 |
| C-E-025 | AUTOSAR는 완전한 safe 해법이 아니며 그것으로도 안전하지 않은 계통을 만들 수 있다 | autosar-safety-measures, 7쪽 | 1차 | 2026-11-23 |
