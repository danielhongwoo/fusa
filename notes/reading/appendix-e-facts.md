# 부록 E 근거 문서에서 뽑은 사실 (읽기 기록)

대상: 부록 E "차량 E/E 최소 지식" (plans/appendix-e-vehicle-ee-basics.md). 읽은 날: 2026-11-23.

- 쪽 칸은 PDF 파일의 몇 번째 쪽이다. 문서에 인쇄된 쪽 번호가 다르면 절 머리에 차이를 적는다.
- 인용은 줄바꿈을 합치고 따옴표와 줄표를 ASCII로 바꿨다. 그 밖에는 원문 그대로다.
- 받은 문서 가운데 차량 전자 장치를 직접 서술하는 것은 nhtsa-etc-ev-fsa, nhtsa-etc-gasoline-fsa, nasa-toyota-ua-report 셋이다. AUTOSAR 두 문서는 소프트웨어 층과 통신 보호를 다루며, CAN 자체의 동작은 다루지 않는다. 그 빈자리는 끝의 "찾지 못한 것"에 적었다.
- 그림 (블록 그림)의 글자는 쪽에서 글자로 뽑히지 않는 것이 있다. 그런 줄은 쪽을 그림으로 그려 눈으로 읽었고, 인용 칸에는 그림의 제목만 넣었다.
- 이 파일의 사실은 "그 문서가 그렇게 서술한다"까지다. 예제의 설계 (전압 범위, 신호 이름)와 책 원고의 주장은 "비고"와 끝의 두 절에서 견준다.
- 원고에 쓰기 전에 그 쪽을 직접 열어 확인한다 (RULES.md 5.2절).

## 1. nhtsa-etc-ev-fsa (NHTSA/Volpe, Functional Safety Assessment of a Generic Accelerator Control System With Electronic Throttle Control in Electric Vehicles, DOT HS 812 656, 2020. PDF 쪽 = 인쇄 쪽 + 16)

약어: AP 가속 페달, APPS 가속 페달 위치 센서, EV PCM 전기차 powertrain 제어 모듈 (이 책의 차량 제어기에 해당), TICM 구동 inverter 제어 모듈, EPS 전동 powertrain 부분계 (TICM, gate drive, inverter, 센서), BPPS 브레이크 페달 위치 센서, RESS 고전압 배터리 계통, BTO 브레이크가 가속을 누르는 기능.

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| FE-001 | 27 | 분석 대상인 ACS는 운전자의 조작 장치에서 엔진 또는 모터의 throttle 또는 연료 조절 장치까지 이어진 부품의 사슬이다. | "extending from the driver-operated control to the throttling or fuel-metering device" | 원문은 이 정의를 2012 FMVSS 124 NPRM에서 따왔다고 적는다 |
| FE-002 | 27 | 범위에 든 부품: 가속 페달, 페달 위치 센서, EV PCM, 구동 inverter 제어 모듈, gate drive board, inverter/converter (power stage), 상 전류 센서, 모터 위치와 속도 센서, inverter 온도 센서. | "All components leading from the driver-operated control to the high voltage power supply connection" | 인용 뒤에 "to the traction motor"가 이어지고 부품 목록이 나온다 |
| FE-003 | 27 | 범위에는 부품 사이의 선 연결과, 차량 bus (예: controller area network)를 통한 통신이 모두 든다. | "Communication over the vehicle bus (e.g., controller area network)" | 보고서가 CAN을 말하는 곳은 "예"로 든 것뿐이다 |
| FE-004 | 28 | 범위에 든 interface 센서: 차량 속도, 브레이크 페달 위치 센서, 차량 방향 (전진 또는 후진 기어). | "Vehicle direction data (forward or reverse gear)" | 기어 선택을 "센서의 데이터"로 다룬다 |
| FE-005 | 28 | 범위 밖: 모터의 토크 발생과 그 뒤의 감속기 같은 전달, 운전자 오류, 점검 소홀, 다중 고장, 운전자에게 알리는 경고등 자체. | "Multiple point failures in the ACS/ETC system or interfacing systems" | 경고 표시를 범위 밖으로 둔 점이 중요하다. 부록이 계기판 경고를 설명할 때 보고서가 다루지 않은 부분임을 밝혀야 한다 |
| FE-006 | 29 | 차량 속도는 brake/stability 제어 모듈이 EV PCM에 준다고 가정한다. 다른 구조에서는 다른 부품이 줄 수 있다. | "Some system architectures may obtain the vehicle speed from other components." | 보고서의 가정이다. 모든 차가 그렇다는 서술이 아니다 |
| FE-007 | 30 | 내연기관은 연료의 통제된 연소로, 전기차는 전기 에너지를 traction motor의 토크로 바꾸어 구동력을 만든다. 운전자 조작 장치는 전기차에서 모터로 가는 전류를 조절한다. | "converting electrical energy to torque through the traction motor" | |
| FE-008 | 30 | 전기차는 모터 속도가 0이 되어도 시동이 꺼지지 않는다 (stall하지 않는다). 그러나 EPS가 갑자기 꺼지면 stall과 비슷한 상태가 생길 수 있다. | "the traction motor speed can be reduced to zero without causing the vehicle to stall" | 원고의 "멈춤" 항목의 근거다 |
| FE-009 | 30 | 전기차의 creep 속도나 idle 토크는 소프트웨어로 흉내 낸 것이다. | "is simulated in the software to create a behavior more like traditional ICEs" | 원고의 "느낌을 소프트웨어로 흉내 낸다"의 근거다 |
| FE-010 | 31 | 내연기관은 페달을 놓으면 엔진이 차를 더 감속시킨다. 전기차는 페달을 놓으면 차가 coast한다. 일부 전기차는 회생 제동으로 엔진 제동을 흉내 낸다. | "releasing the AP will cause the vehicle to coast" | 원고의 "페달을 놓았을 때" 항목과 "토크를 0으로 하면 타력으로 간다"의 근거다 |
| FE-011 | 31 | 내연기관은 엔진이 한 방향으로만 돌고 별도의 변속 장치가 방향을 바꾼다. 전기차의 모터는 두 방향으로 돌 수 있고, 토크의 방향은 모터에 주는 전류가 정한다. | "is determined by the current supply to the traction motor" | |
| FE-012 | 31 | 차의 진행 방향을 제어하는 책임은 EV ACS/ETC에 있다. | "The EV ACS/ETC is responsible for controlling the direction of vehicle motion." | 원고의 "구동 소프트웨어가 진행 방향까지 맡는다"의 근거다 |
| FE-013 | 31 | 블록 그림은 EV ACS/ETC의 경계를 점선으로 그리고, 경계 밖의 다른 차량 계통은 올바르게 동작한다고 가정한 black box로 다룬다. | "are treated as black boxes with respect to the EV ACS/ETC" | 예제의 "inverter부터는 가정으로 받는다"와 같은 방식이다 |
| FE-014 | 32 | Figure 5의 흐름: 운전자 -> 가속 페달 -> 페달 위치 센서 -> EV PCM. EV PCM은 12V 전원 (ignition key 위치)을 받고, 다른 차량 센서에서 선택된 기어와 충돌 신호를 받는다. EV PCM은 토크 요구를 traction inverter 제어 모듈에 보내고, 제어 모듈은 switch 신호를 gate drive board에 보낸다. EV PCM에서 gate drive board로 가는 "Disable Motor (Traction Controller Bypass)" 선이 따로 있다. | "Block Diagram of the ACS/ETC in Electric Vehicles" | 그림의 글자를 눈으로 읽었다. 쪽의 글자 층에는 그림 제목만 있다. 부록의 구성도는 이 그림을 줄인 것이다 |
| FE-015 | 33 | 페달 위치 센서는 페달의 각도 변위를 전압 신호로 바꾸어 EV PCM에 보낸다. 신호는 센서와 EV PCM 사이의 직접 연결이나 차량 통신 bus (예: CAN bus)로 간다. | "a direct connection between the APPS and EV PCM" | 같은 쪽: "The signal may be transmitted via a direct connection ... or over the vehicle communication bus". 센서 신호가 CAN으로도 간다는 서술이다 |
| FE-016 | 33 | EV PCM은 센서 전압을 원하는 모터 토크로 바꾸고, 운전자의 토크 요구를 브레이크/안정성 계통과 cruise control 같은 다른 계통의 토크 요구와 조정한다. | "reconciles the torque requested by the driver with torque requests from other vehicle systems" | |
| FE-017 | 33 | 운전자가 기어 선택기로 방향을 고르면 transmission range sensor가 그 위치를 EV PCM에 알리고, EV PCM은 그 방향으로 토크를 낸다. | "The transmission range sensor communicates the gear selector position to the EV PCM." | 원고의 "기어 선택"이 어떻게 들어오는가의 근거다 |
| FE-018 | 33 | EV PCM이 토크 명령을 TICM에 보내면, TICM이 모터에 필요한 전류를 계산한다. 전류가 토크의 방향과 크기를 정한다. | "The TICM computes the amount of electrical current required by the traction motor" | 원고 표의 "inverter의 제어부"가 TICM이다 |
| FE-019 | 33 | TICM은 switching 신호를 gate drive board에 보내 전류를 흐르게 한다. gate drive board는 전력 증폭기이고, TICM과 고전압 inverter를 전기적으로 격리할 수도 있다. | "The gate drive board serves as a power amplifier that switches the transistors" | |
| FE-020 | 34 | 교류 모터를 쓰는 전기차에서 inverter/converter는 배터리의 고전압 직류를 모터가 쓰는 교류로 바꾼다. 같은 장치가 보조 장치용 저전압 직류도 만든다. | "converts the HV DC from the RESS to the AC required by the traction motor" | 직류 모터인 구조도 있다고 같은 쪽 앞에 적는다 |
| FE-021 | 34 | 상 전류 센서가 모터로 가는 전류를 재서 TICM에 되먹인다. 모터의 위치와 속도는 모터에 붙은 센서 (예: resolver)가 재서 TICM이 스위칭 신호를 고치는 데 쓴다. | "allowing closed-loop control of the switching signal provided to the gate drive board" | 원고 그림의 "전류, 회전 위치" 되먹임의 근거다 |
| FE-022 | 34 | 운전자가 페달을 놓으면 페달 조립체의 기계 부품 (예: 스프링)이 페달을 원위치로 돌린다. 전기차에서는 이때 모터 토크를 0으로 줄일 수 있다. | "the traction motor torque output can be reduced to zero when the AP is released" | |
| FE-023 | 34 | 가속과 브레이크가 함께 눌리면 EV PCM이 운전자의 뜻을 판단하고, 멈추려는 것으로 보이면 BTO 기능으로 가속 요구를 무시한다. | "the EV PCM will override the torque request from the driver via the AP" | 판단에 차량 속도와 두 페달이 함께 눌린 시간을 쓸 수 있다고 같은 쪽이 적는다. 예제의 브레이크와 가속 충돌 처리의 배경이다 |
| FE-024 | 35 | 고장 감지: EV PCM이 구동 계통의 전자 부품을 감시한다. 고장을 찾으면 DTC (진단 고장 코드)를 기록하고 limp-home mode 같은 safe state로 보낼 수 있다. | "a diagnostic trouble code (DTC) and may force the EV ACS/ETC into a safe state" | 원고에 DTC 설명이 없다. 이 쪽이 DTC, limp-home, MIL의 근거다 |
| FE-025 | 35 | EV PCM은 계기판 (instrument display panel)의 고장 표시등 (malfunction indicator light)을 켜는 명령도 낸다. | "will also issue a command to turn on the malfunction indicator light" | 경고등을 켜는 주체가 EV PCM이라는 서술이다. 계기판이 CAN으로 받는지는 말하지 않는다 |
| FE-026 | 35 | 고장의 예: 페달 센서 전압이 교정 범위를 벗어남, TICM이나 inverter/converter의 고장, 고전압 공급의 고장, EV PCM 내부의 소프트웨어 또는 하드웨어 고장. | "APPS voltage signals exceeding the calibration range" | |
| FE-027 | 35 | TICM에 고장이 있으면 EV PCM이 TICM을 건너뛰고 gate drive board와 직접 통신해 모터의 전류를 끊을 수 있다. | "bypass the TICM and communicate directly with the gate drive board" | 원고의 "직결선" 문단의 근거다. 보고서는 "may be able to"라고 쓴다. 이것이 선 하나인지 network 메시지인지는 이 쪽에 없다 |
| FE-028 | 35 | 브레이크 페달 위치 센서는 브레이크 페달의 각도 변위를 재어 전기 신호로 바꾸어 EV PCM에 보낸다. | "the BPPS measures the angular displacement of the BP" | 이 보고서의 브레이크 입력은 각도를 재는 센서다. 예제의 "브레이크 스위치"(접점 둘)와 다르다 (끝의 어긋남 목록) |
| FE-029 | 35 | 회생 제동은 모터를 발전기로 쓰는 것이다. 회생만으로 모자라면 EV PCM이 마찰 브레이크를 요청할 수 있다. | "the traction motor is operated as a generator" | 회생 제동은 이 연구의 범위 밖이다 (36쪽) |
| FE-030 | 36 | 고전압 배터리 계통은 inverter에 고전압 직류를 주고, 이상이 있거나 충돌 센서 신호를 받으면 EV PCM에 고전압 bus를 방전하라는 신호를 보낼 수 있다. | "the RESS may send a signal to the EV PCM to discharge the HV bus" | 예제에는 없는 기능이다. 부록이 고전압 안전을 어디까지 말할지의 판단 재료다 |
| FE-031 | 39 | EV ACS/ETC는 12V 직류 전원, 고전압 전원, 통신 bus (예: CAN bus)에 연결된다. | "also connected to the 12-volt direct current power supply, the HV power supply" | 12V가 보조 전원이라는 서술은 이 쪽에 없다. 숫자와 연결만 있다 |
| FE-032 | 42 | STPA의 제어 구조 그림에는 12V 전원이 운전자가 ignition key를 돌린 결과로만 그려진다. 12V 전원이 계통에 미치는 영향은 STPA Step 2에서 자세히 다룬다. | "12-volt power supply is only shown on this diagram" | ignition은 이 보고서에서 "key 위치"로만 나온다. ignition의 상태 (off, accessory, on, start)는 말하지 않는다 |
| FE-033 | 67 | 전형적인 safety 전략 요소: 핵심 센서 입력의 유효성 확인 (redundant measurement path), 주 제어기의 건전성 확인 (보조 processor 사용), 잠복 고장을 주기적 검사로 잡기, 통신 신호의 유효성 확인, 위험이 보이면 safe state에 제때 도달, 위험이 보이면 운전자에게 경고. | "mitigate latent faults through periodic checks" | 원고의 "센서를 둘 달고 견준다", "경고"가 이 목록의 항목들이다 |
| FE-034 | 67 | safe state는 정상 동작, 줄인 동작 (degraded, 0 < 토크 < 최대), 꺼진 상태 (토크 0) 가운데 하나다. | "The safe states for the EV ACS/ETC are either full operation" | 줄인 동작에도 단계가 있다고 같은 쪽이 쓴다 |
| FE-035 | 68 | 예시한 safe state: 1 (ACC와 AEB 같은 다른 계통의 입력을 끊음), 2 (고장 직전의 토크로 상한을 제한), 3 (페달에 대한 토크의 변화율을 낮춤, 예: 페달 센서 고장 하나), 4 (페달 없이 토크, 속도 제한, 예: 페달 센서 고장 둘), 5 (페달 0의 토크 map 값으로 토크를 냄, 예: 페달 센서 둘과 BPPS의 고장), 6 (토크 0), 7 (고전압 bus 분리). | "Safe State 6: Zero torque output" | 번호는 이 보고서의 예시일 뿐 규격의 번호가 아니다 |
| FE-036 | 68 | safe state에 들어갈 때는 운전자가 줄인 동작 상태임을 알리고 조치할 수 있다. hazard가 그냥 나타날 때는 운전자에게 알려지지 않을 수 있다. | "the driver is informed that the vehicle is in a degraded operating state" | safe state와 hazard를 가르는 두 차이 가운데 하나다 |
| FE-037 | 68 | 운전자 경고 예: amber light (안전 목표를 어길 가능성이 있고 그 확률이 중간), red light (어길 가능성이 크거나 이미 어김), chime (red light 조건에서 소리). | "Red Light: Potential violation of a safety goal is detected" | "commonly seen in the automotive industry"의 예라고 보고서가 말한다. 규격의 요구가 아니다. 원고의 "계기판의 경고"의 근거다 |
| FE-038 | 74 | 중복 요소를 쓰면 한 요소의 전원 고장이 다른 요소의 전원에 영향을 주지 않아야 한다. 한 요소의 통신 경로 고장도 마찬가지다. | "are not to affect the power supply of the other element" | 원고의 "전원과 접지를 따로 준다"의 근거다. ASIL C/D 요구로 적혀 있다 |
| FE-039 | 74 | 중복 요소 하나가 고장나면 FTTI 안에 safe state 3으로 가고 amber 경고를 낸다. 둘 다 고장나거나 요소가 하나뿐인데 고장나면 safe state 4로 가고 red 경고를 낸다. | "transition into Safe State 3 within the FTTI of TBD seconds" | 시간은 TBD로 남아 있다 |
| FE-040 | 74 | 주 제어기의 건전성은 보조 제어기 (A)가 정해진 간격으로 입력 묶음을 주고 기대한 응답이 오는지 보는 방식 (quizzer, seed-and-key)으로 확인할 수 있다. | "One controller (A), at predefined time intervals, presents a set of inputs" | 각주 24의 정의다. 모니터가 별도의 processor에 있는 구조의 설명이다 |
| FE-041 | 76 | DTC는 안전 목표를 어길 수 있을 때마다 설정한다 (ASIL QM). | "DTCs are to be set every time a safety goal may be violated" | |
| FE-042 | 76 | 가속 페달 조립체의 요구: 센서의 건전성을 모든 운전 조건에서 감시하고 확인한다 (ASIL C/D). | "The health and sanity of the APPS is to be monitored and confirmed" | 쪽의 끝부분에서 다음 쪽의 5번 (plausibility and rationality)으로 이어진다 |
| FE-043 | 77 | 페달 센서에 고장이 있으면 센서가 EV PCM에 그 고장을 알려야 한다. 센서의 단일 고장은 FTTI 안에 검출하고 safe state로 간다. | "the APPS is to communicate the fault to the EV PCM" | 8번 요구는 "detected and mitigated within the FTTI"이다 |
| FE-044 | 83 | EV PCM의 진단은 전선과 connector의 단선과 단락, 그리고 CAN 메시지를 포함한 중요 메시지를 덮어야 한다. | "Critical messages including CAN messages" | ASIL QM/A/B 요구다 |
| FE-045 | 87 | 중요 통신 신호의 목록: 페달 센서 신호, 페달 진단 신호, 브레이크 페달 센서 신호, 차량 속도, 차량 방향, EV PCM이 EPS에 주는 토크 명령, 운전자 경고 신호, 저전압 전원 상실 신호 등. | "Command for torque from the EV PCM to the EPS" | 원고의 "토크 요구", "속도", "경고"가 모두 중요 통신 신호의 목록에 있다 |
| FE-046 | 87 | 모든 중요 통신 신호는 유효성과 정확성 (plausibility and rationality)을 확인해야 한다. 고장을 찾은 계통은 EV PCM에 알리고 완화 전략을 쓴다. | "All critical communication signals are to be qualified for validity and correctness" | |
| FE-047 | 88 | 통신 bus는 중요 신호의 전송 중 손상을 막아야 하고, bus나 bus 모듈이 이상하면 EV PCM에 알려야 한다. | "The communication bus is to prevent the corruption of the critical communication signals" | 어떤 수단으로 막는지는 적지 않는다 |
| FE-048 | 88 | 저전압 전원은 이중화해야 한다. 이중 전원은 TBD ms 안에 켜져 가장 긴 FTTI보다 오래 전원을 유지해야 한다. | "The ACS/ETC is to have a redundant low voltage power supply." | 원고에 전원 항목이 없다. 이 쪽이 12V 전원의 안전 요구의 근거다 |
| FE-049 | 88 | 저전압 전원 상실이나 이상이 있으면 safe state 6 (토크 0)으로 가고 운전자에게 red 경고를 낸다 (ASIL D). | "transition to Safe State 6 in case of the loss or malfunction" | |

## 2. nhtsa-etc-gasoline-fsa (NHTSA/Volpe, Functional Safety Assessment of a Generic Accelerator Control System With Electronic Throttle Control in Gasoline-Fueled Vehicles, DOT HS 812 557, 2018. PDF 쪽 = 인쇄 쪽 + 18)

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| FE-050 | 31 | 가솔린 엔진은 흡입 공기량으로 출력을 조절한다. 옛 기계식은 cam과 cable로 throttle valve를 페달에 직접 이었고, 지금의 electronic throttle control에서는 ECM의 전기 신호를 받은 모터가 throttle valve를 움직인다. | "regulates the amount of air intake to control the engine power output" | 전기차와 다른 점을 말할 근거다. 전기차는 throttle이 없고 inverter가 모터 전류를 조절한다 (FE-007, FE-018) |
| FE-051 | 33 | 페달 위치 센서는 각도를 전압으로 바꾸어 ECM에 보내며, 신호는 직접 analog 입력이나 CAN bus 같은 통신 bus로 갈 수 있다. ECM이 교정 map으로 전압을 원하는 엔진 토크로 바꾼다. | "a direct analog input or a vehicle communication bus such as the CAN bus" | 전기차 보고서의 같은 서술 (FE-015)과 구조가 같다. 두 보고서는 같은 연구의 짝이다 |
| FE-052 | 33 | ECM은 PWM으로 throttle 모터를 구동하고, throttle에 붙은 센서 (TPS)의 되먹임으로 위치를 닫힌 고리로 맞춘다. | "uses pulse-width modulation to drive the throttle motor" | 전기차의 TICM과 gate drive에 해당하는 역할이 가솔린차에서는 ECM과 throttle 모터다 |
| FE-053 | 34 | 가솔린차는 페달을 놓으면 ECM이 throttle을 idle 위치로 보내고, 엔진 속도 센서의 되먹임으로 idle 속도를 맞춘다. | "continuously updates the throttle valve idle angular position calibration" | idle을 유지하는 기계 장치가 엔진이라는 점이 전기차와 다르다 |
| FE-054 | 34 | 고장을 찾으면 ECM이 DTC를 기록하고 limp-home mode 같은 safe state로 보내며, 고장 표시등을 켠다. | "The ECM will also turn on the malfunction indicator light" | 전기차 보고서의 FE-024, FE-025와 같다. DTC와 limp-home은 두 보고서가 같은 말을 쓴다 |
| FE-055 | 35 | 가솔린차의 고장 예: 페달 또는 throttle 센서 전압이 교정 범위를 벗어남, throttle 모터가 전류 한계를 넘음, ECM 내부 고장. | "Throttle motor exceeding the allowable electronic current limit" | |

## 3. nasa-toyota-ua-report (NASA NESC, Technical Support to NHTSA on the Reported Toyota Motor Corporation Unintended Acceleration Investigation, 2011. PDF 쪽 = 인쇄 쪽 + 0)

약어: ETCS-i 이 차의 electronic throttle control 계통, ECM 엔진 제어 모듈, VPA1과 VPA2 두 페달 센서의 신호, VTA1과 VTA2 두 throttle 센서의 신호, MIL 고장 표시등, DTC 진단 고장 코드.

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| FE-056 | 15 | ETCS-i는 주 계통 (prime)과 감시 계통 (monitor)을 둔 단계적 fail-safe 구조다. 한 번 고장에서 제한된 페달 제어부터 엔진 정지까지 다섯 fail-safe mode가 있다. | "tiered fail-safe approach with a prime system and a monitor system" | 원문 같은 쪽: "five fail-safe modes that range from limited pedal control to complete engine shutdown" |
| FE-057 | 15 | 두 페달 센서 가운데 하나가 고장나면 limp home mode가 throttle의 최대 열림을 약 18도로 제한한다. | "limits maximum throttle opening to approximately 18 degrees" | 다른 쪽 (67, 80)은 10-15도와 약 15도라고 적는다. 엔진 형식에 따라 다르다 |
| FE-058 | 15 | 두 페달 센서 가운데 하나라도 가속하지 않음을 가리키면 throttle 위치와 무관하게 fuel cut이 엔진 속도를 2500 rpm 이하로 제한한다. | "the engine speed will be limited to a maximum of 2500 rpm" | 센서 둘의 신호를 "하나라도"의 논리로 쓰는 예다 |
| FE-059 | 49 | ETCS-i의 limp home은 고장 뒤에 낮은 속도로 계속 달리게 한다. 부품 이상이 있으면 MIL ("check engine light")이 운전자에게 알리고 고장은 DTC로 저장된다. | "is intended to alert the driver with the malfunction stored as a DTC" | 원고에 없는 MIL과 DTC의 정의에 해당한다 |
| FE-060 | 49 | 페달 신호 하나가 고장나면 ECM은 다른 페달 신호로 제한된 throttle 제어를 한다. | "the ECM will use the other pedal signal to provide limited throttle control" | 원고의 "어느 쪽이 맞는지는 모른다"와 견주어야 한다 (끝의 어긋남 목록) |
| FE-061 | 53 | ECM에는 CPU가 둘 있고, 엔진이 돌려면 둘이 함께 정상이라고 동의해야 한다. 어느 한 CPU의 고장은 엔진을 멈춘다. | "To operate the vehicle both CPUs must agree that the engine is operating properly." | main CPU와 sub-CPU의 구조다 |
| FE-062 | 54 | main CPU의 Pedal Command Function이 두 페달 센서 입력을 원하는 throttle 각도 명령으로 바꾼다. 같은 함수가 페달 센서 고장 때의 limp home 논리도 담는다. | "converts two accelerator pedal position sensors inputs into a desired throttle angle command" | 원고의 "차량 제어기는 전압을 토크로 바꾼다"에 해당하는 구조다 |
| FE-063 | 56 | sub-CPU는 main CPU와 같은 논리를 되풀이해 견주지 않는다. main CPU와 throttle 모터의 성능에 관한 진단만 한다. 두 CPU는 직렬 interface로 data를 나누고 서로 견준다. | "The Sub-CPU does not run duplicate logic and compare with the Main CPU" | monitor가 main과 같은 계산을 하는 구조가 아님을 보인다. 같은 쪽에서 sub-CPU가 서로의 입력 data를 검사한다고도 적는다 |
| FE-064 | 56 | main CPU와 sub-CPU 사이에 heartbeat/watchdog 교환이 있어 큰 CPU 고장을 찾고 CPU를 reset할 수 있다. sub-CPU가 치명적 고장 코드를 내면 throttle 모터의 전원 공급을 끊어 limp home을 일으킨다. | "A heartbeat/watchdog exchange between the Main-CPU and Sub-CPU detects major CPU failures" | |
| FE-065 | 58 | 페달 센서 하나는 두 출력 (VPA1, VPA2)을 낸다. VPA2는 같은 기울기에 0.8V 높게 시작한다. ECM은 두 전압을 견주어 센서 문제를 찾는다. | "the ECM can compare the voltages and detect sensor problems" | 원고 예제의 "두 채널의 전압 범위를 다르게 한다"에 가장 가까운 실제 사례다. 이 차는 범위를 다르게 하지 않고 전압을 0.8V 옮겼다 |
| FE-066 | 96 | 이 차의 페달 위치 센서는 센서마다 전용의 전원선과 return선을 가진다. | "each position sensor has dedicated power and return lines" | 원고의 "전원과 접지를 따로 준다"와 맞는다. 같은 쪽에서 VPA1은 0-5V 범위, VPA2는 0.8V 오프셋이라고 적는다 |
| FE-067 | 96 | VPA1은 주 제어에 쓰고 VPA2는 VPA1이 옳은지 검사하는 데 쓴다. | "VPA2 is used to check the validity of VPA1" | 두 채널이 대칭이 아니다. 원고의 예제 설계가 어떤 쪽이 주인지는 이 보고서와 별개다 |
| FE-068 | 52 | throttle 위치 센서 (페달 센서가 아님)는 +5V 공급 한 선과 접지 한 선을 공유하며, 이 센서 둘도 같은 방식으로 견주어 고장을 찾는다. | "one +5V supply circuit (VC) and one ground circuit shared" | 센서 둘이 전원을 공유하는 실제 사례다. 원고의 "함께 쓰면 두 채널을 함께 틀리게 한다"의 반대편 사례이며, 같은 차의 페달 센서는 전용선이다 (FE-066) |
| FE-069 | 77 | 고장 모드 표에 throttle 위치 센서 둘의 "전원 또는 접지가 둘 모두 이상"이 원인으로 올라 있다. | "Compromised power feed or ground to both sensors." | 표의 한 칸이다. 원고의 공통 원인 고장 설명을 뒷받침하는 서술은 아니고, 같은 부류의 고장이 표에 오른 것만 보인다 |
| FE-070 | 67 | 센서 둘과 CPU 둘은 throttle을 열 때 "직렬"이다. 두 페달 센서가 모두 가속을 가리켜야 열리고, 어느 하나가 고장을 선언하면 닫는다. | "both pedal sensors are needed to indicate off idle in order to open the throttle" | 닫는 쪽으로는 이중화이고 여는 쪽으로는 아니라고 같은 쪽이 쓴다 |
| FE-071 | 67 | 페달 센서 하나의 고장이 선언되면 limp home mode로 들어가고 남은 센서로 제한된 범위 (10-15도)를 제어한다. 센서 둘 가운데 하나를 가려내 계속 달리는 데는 이중화가 있다고 보고서가 적는다. | "the limp home mode is entered and the other sensor is used" | 고장난 센서를 가려내는 방법은 DTC 표 (FE-076)의 범위 검사 등이다 |
| FE-072 | 72 | 두 센서를 서로 견주는 것은 고장이 두 센서를 모두 유효한 전압으로 망가뜨리지 않는 한 지켜 준다. VPA1과 VPA2를 오프셋으로 고른 것은 두 센서를 함께 유효한 신호처럼 만드는 공통 원인 고장을 막기 위해서다. | "Comparing two sensors against each other can protect against failures" | 원고의 "센서가 둘이면" 오해 항목과 직접 관련된다. 오프셋의 이유가 공통 원인 고장이라는 서술이다 |
| FE-073 | 16 | 페달 센서의 출력 사이에 저항성 단락 (tin whisker)이 있으면, 이후 ignition key를 돌릴 때마다 limp home mode의 동작과 MIL, DTC 표시에 영향이 있을 수 있었다. | "may compromise nominal limp home mode fail-safe operation on subsequent ignition key cycles" | 센서 둘을 견주는 방식도 두 출력 사이의 저항성 단락에서는 약했다는 실제 사례다 |
| FE-074 | 81 | 그 저항성 단락 상태에서 DTC 2121이 나오고 MIL이 켜졌지만, DTC를 지우고 MIL을 끄면 (OBD II clear code 명령이나 배터리 분리) 다시 나타나지 않았다. 동작은 그대로였다. | "cleared and the MIL is turned off via an OBD II clear code command" | DTC와 MIL이 고장의 표시일 뿐 고장 자체가 아니라는 사례다. OBD II는 진단 도구가 쓰는 통신이다 (FE-077) |
| FE-075 | 80 | limp home mode에서 브레이크를 밟으면 ETCS-i가 throttle을 자동으로 닫는다. 페달 센서 하나가 고장난 상태에서 나머지가 여는 쪽으로 틀리는 경우를 막기 위해서다. | "automatically closes the throttle when the brake is pressed" | 80쪽 끝에서 81쪽으로 이어진다. 예제의 브레이크와 가속 충돌 처리의 실제 사례다. 같은 차의 표 (78쪽)에는 브레이크 switch의 두 접점이 서로 맞지 않을 때 DTC를 내는 줄이 있다 |
| FE-076 | 63 | DTC 표는 페달 센서 하나하나의 문제 (chattering, 낮은 전압, 높은 전압)와, 둘 사이의 관계 (correlation, rationality)를 별개의 코드로 둔다. 예: P2138 (VPA1-VPA2 상관), P2121 (rationality). | "VPA1-VPA2 Correlation" | 어느 센서가 틀렸는가를 가리는 근거는 센서마다의 범위 검사 코드다. 둘의 견줌만으로는 가리지 못한다 |
| FE-077 | 62 | OBD의 역사: 1975년의 간단한 OBD, 1988년 SAE가 표준 진단 connector와 시험 신호를 권고, 1994년 법이 대시보드 경고등과 고장 코드 저장을 요구하고, 1996년에 미국이 OBD-II를 모든 차에 의무화했다. | "that the government mandated for all vehicles sold in the United States" | 미국 법의 역사다. OBD-II의 통신 방식은 이 쪽에 없다. 벤더 전용 코드 자리가 있다는 서술은 같은 쪽 |
| FE-078 | 64 | 고장 때 차를 꺼 버리면 길 위에 서 버려 (stranding) 새 위험이 생길 수 있으므로, 응답은 움직일 수 있음과 서 버림 사이의 균형을 본다. | "stranding the vehicle might introduce a new hazard" | 원고의 "구동이 갑자기 꺼지면 구동력을 잃는다"와 같은 뜻의 서술이다 |

## 4. autosar-safety-measures (AUTOSAR, Overview of Functional Safety Measures in AUTOSAR, AUTOSAR CP R25-11, 2025. PDF 쪽 = 인쇄 쪽 + 0)

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| FE-079 | 7 | AUTOSAR는 safety 수단을 제공하지만 완전한 safe 해법이 아니다. AUTOSAR를 쓴다고 ISO 26262 준수가 되지 않으며, 그것으로도 안전하지 않은 계통을 만들 수 있다. | "AUTOSAR is not a complete safe solution" | 같은 쪽: "possible to build unsafe systems using the AUTOSAR safety measures and mechanisms" |
| FE-080 | 11 | 응용 소프트웨어는 RTE 위에 있고, 서로 이어진 AUTOSAR software component (SW-C)로 이루어진다. SW-C는 hardware에 독립이다. | "Application Software is located above the RTE" | 원고 표의 응용 소프트웨어 줄의 근거다 |
| FE-081 | 11 | SW-C는 ECU 안과 ECU 사이의 정보 교환을 모두 RTE를 통해서만 한다. | "AUTOSAR Software Components communicate exclusively over the RTE" | 원고의 "RTE는 응용 사이, 응용과 아래 층 사이의 값을 나른다"는 이 서술에서 줄인 것이다. "아래 층"과의 교환이 포함되는지는 이 쪽만으로 확정되지 않는다 |
| FE-082 | 12 | SW-C 안의 C 함수를 runnable이라 부른다. runnable은 혼자 실행되지 못하고 OS의 실행 단위인 task에 넣어서 주기적이나 사건으로 실행한다. | "they must be assigned to executable entities of the operating system" | 원고의 "task의 실행"이 OS 쪽 일이라는 근거다 |
| FE-083 | 10 | OS-Application들은 서로 보호된 다른 메모리 영역 (partition)에 있다. 한 partition의 코드는 다른 partition의 메모리를 고칠 수 없다. | "OS-Applications reside in different memory areas (partitions) that are protected from each other" | 원고의 "메모리 보호는 아래 층이 준다"의 근거다. 쓰려면 hardware의 memory protection 기능이 필요하다는 점은 이 쪽에 없다 |
| FE-084 | 9 | ASIL이 다른 소프트웨어 component가 섞여 있으면, 전체를 가장 높은 ASIL로 개발하거나, 높은 ASIL 쪽이 낮은 쪽에서 간섭받지 않음 (freedom from interference)을 보장해야 한다. | "either the entire software must be developed according to the highest ASIL" | 간섭의 종류는 메모리, 타이밍, 실행, 정보 교환 넷이다 (같은 쪽) |
| FE-085 | 23 | Watchdog Manager는 AUTOSAR의 basic software module이며, 소프트웨어 실행의 감시를 watchdog hardware의 trigger와 연결한다. | "The Watchdog Manager is a basic software module of the AUTOSAR Architecture." | 원고의 "감시"가 basic software 쪽이라는 근거다 |
| FE-086 | 60 | complex driver (CDD)는 입출력에 직접 닿을 수 있다. 문서가 소개하는 설계에서는 감시 소프트웨어를 CDD에 둔다. | "A CDD allows a direct access to the related inputs and outputs." | 원고 표의 complex driver 줄의 근거다 |
| FE-087 | 60 | E-Gas Monitoring Concept는 디젤과 가솔린 엔진 제어에 적용하는 safety concept이고, AKEGAS 작업반이 표준화했으며 AUTOSAR 표준에 속하지 않는다. | "applicable e.g. for diesel and gasoline engine management" | 같은 쪽: "not part of the AUTOSAR standard". 문서의 3.7.2절이 이 개념을 AUTOSAR 위에 얹는 방법을 다룬다. 전기차 구동에는 이 개념이 그대로 적용된다고 적지 않는다 |
| FE-088 | 62 | 문서는 송신 ECU에서 수신 ECU의 BSW driver까지 데이터의 손실과 손상을 찾는 일이 CAN이나 FlexRay 같은 통신망의 보호 기구 (CRC, checksum, counter)로 보장된다고 정당화한다. | "protection mechanisms available with CAN or FlexRay communication networks" | CAN의 CRC가 어떤 오류를 잡는지는 이 문서가 설명하지 않는다. 그 구간에서 BSW driver 이후는 별개 (CC02)로 다룬다 |
| FE-089 | 33 | E2E 보호가 가정하는 통신 오류 목록: 되풀이 (repetition), 손실, 지연, 삽입, 사칭이나 잘못된 주소, 잘못된 순서, 손상, 송신자 하나에서 수신자 여럿으로 가는 정보가 서로 다름, 일부 수신자만 받음, 통신 채널 접근 막힘. | "Loss of information; Delay of information; Insertion of information;" | 원고의 "손상, 사라짐, 되풀이, 늦음, 뒤바뀜"이 이 목록의 일부다. 목록의 첫 항목 (repetition)은 같은 쪽 앞머리에 있다 |
| FE-090 | 33 | 통신 오류의 원인 예: 통신 transceiver의 register 손상 같은 무작위 hardware 고장, EMC 같은 간섭, 송수신 ECU와 gateway의 소프트웨어 (RTE, COM, network stack)의 체계적 고장. | "corrupt registers of a CAN transceiver" | 오류의 원인에 선 위의 손상만이 아니라 송수신 쪽 소프트웨어의 체계적 고장도 든다는 서술이다 |
| FE-091 | 34 | 송신 쪽이 응용 data에 End-2-End header (보통 checksum, counter 등)를 붙이고, 수신 쪽이 검사한다. 오류 처리는 수신 쪽이 한다. | "extended on the sender side with additional control information, the End-2-End header" | 35쪽: "The error handling is performed at the receiver." 원고의 "보내는 쪽이 검사 정보를 붙이고 받는 쪽이 검사한다"의 근거다 |
| FE-092 | 35 | E2E profile이 쓰는 보호 수단: CRC, 송신 요청마다 늘어나는 sequence counter (수신 쪽이 올바르게 늘었는지 검사), alive counter (바뀌는지만 검사), data ID. | "Sequence Counter incremented at every transmission request" | 한 profile은 이 가운데 일부만 쓴다 |
| FE-093 | 36 | E2E Profile 1은 4비트 counter, 8비트 CRC, 16비트 data ID를 쓰며 data ID는 CRC 계산에만 넣고 보내지 않는다. 수신 쪽은 counter가 늘었는지로 시간 초과를 안다. | "A CRC Checksum (8-Bit) calculation is performed over all data elements" | 8비트 CRC와 16비트 ID 때문에 서로 다른 ID가 같은 CRC를 만들 수 있다고 같은 쪽이 적는다 |
| FE-094 | 42 | E2E 보호는 data의 최신성 (actuality)을 보장하지 않는다. profile이 시간 기록을 담지 않기 때문이다. | "The End-2-End Protection does not guarantee data actuality" | 원고의 "메시지가 오래된 것"을 이 보호가 잡지 못한다는 근거가 될 수 있다. 다만 counter가 늘지 않는 것은 잡는다 (FE-092) |
| FE-095 | 42 | E2E 라이브러리를 쓰는 것만으로 안전한 통신이 되지 않는다. 선택한 profile이 그 망에서 충분히 오류를 찾는다는 것을 사용자가 보여야 한다. | "Solely the user is responsible to demonstrate that the selected profile provides sufficient error detection" | 근거로 hardware 고장률, bit error rate, 노드 수, 메시지 반복률, gateway 사용을 든다 |
| FE-096 | 45 | AUTOSAR가 주지 않는 safety 수단이 있다고 문서가 밝힌다. 46쪽의 목록: 전체 safety concept, ASIL 식별, 종속 고장 분석, safety case, 확인 조치, safety 감사, HARA와 HAZOP, 소프트웨어 component의 구현 기법 (낮은 복잡도, 방어적 코딩 등). | "Not all functional safety measures, which may be required for the development of safety-relevant applications" | 쪽 끝의 문장이다. 목록은 46쪽 앞부분. 원고의 "AUTOSAR를 쓰지 않는다"와 별개로, 층을 소개할 때 "AUTOSAR가 있으면 안전"으로 읽히지 않게 할 근거다 |

## 5. autosar-e2e-protocol (AUTOSAR, E2E Protocol Specification, AUTOSAR FO R25-11, 2025. PDF 쪽 = 인쇄 쪽 + 0)

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| FE-097 | 13 | E2E 통신 보호는 safety 관련 data 교환을 통신 선로의 고장에서 보호한다. ASIL D까지의 요구를 가진 통신에 쓸 수 있다고 한다. | "adequate for safety-related communication having requirements up to ASIL D" | |
| FE-098 | 14 | 어떤 E2E profile이 충분한지는 사용자가 보여야 하고, 고장을 찾은 뒤의 반응 (반복 메시지의 폐기, 시간 초과 판정, 손상 메시지에 대한 safety 반응)도 사용자가 정해야 한다. | "requires the user to demonstrate that the selected profile provides sufficient error detection capabilities" | FE-095와 같은 취지다 |
| FE-099 | 16 | 용어 정의: 되풀이는 같은 메시지가 두 번 이상 받아진 것, 손실은 메시지가 받아지지 않은 것, 지연은 기대보다 늦게 받아진 것이다. | "The same message was received more than once" | 같은 표에 삽입, 사칭, 잘못된 주소 지정, 손상 등의 정의도 있다. 원고의 다섯 가지 오류 (손상, 사라짐, 되풀이, 늦음, 뒤바뀜)와 일대일로 대응하지 않는 항목이 있다 |
| FE-100 | 18 | 이 보호는 주기적이거나 준주기적인 data를 가정한다. 보호 함수를 주기적으로 부르지 않으면 손실과 지연 같은 일부 오류를 못 찾을 수 있다. | "some communication failure modes (loss, delay) may not be detected" | 안전 신호를 주기 송신으로 하는 이유의 근거다 |
| FE-101 | 18 | 하위 계층 (Ethernet FCS, IP header checksum 등)이 찾은 통신 오류는 그 메시지를 버리게 하므로 응용에 아예 닿지 않을 수 있다. | "will lead to discarding the related message" | CAN의 하위 계층 검사가 같은 방식인지는 이 쪽에 없다 |
| FE-102 | 20 | E2E 감독은 차량 안의 여러 ECU에 나뉜 SW-C 사이의 안전 관련 통신에 쓰이며, ECU 안의 통신 (memory partition, 코어, microcontroller 사이)에도 쓸 수 있다. | "The Supervision may also be used for intra-ECU communication" | |
| FE-103 | 27 | 송신자는 CRC나 counter 같은 제어 필드를 data에 더하고, 수신자는 그 필드를 계산해 받은 값과 견준다. | "Sender: addition of control fields like CRC or counter to the transmitted data" | |
| FE-104 | 28 | E2E profile들은 CAN, CAN FD, FlexRay, LIN, Ethernet 같은 통신 환경을 위해 정해졌다. 한 profile이 쓰는 수단 가운데 timeout 검출 (수신 쪽 시간 초과, 송신 쪽 응답 시간 초과)이 있다. | "such as CAN, CAN FD, FlexRay, LIN, Ethernet" | 이 목록이 이 책이 받은 문서에서 CAN FD와 Ethernet을 언급하는 거의 유일한 곳이다. 두 망의 특성은 설명하지 않는다 |

## 6. nhtsa-safety-standards-assessment (NHTSA/Volpe, Assessment of Safety Standards for Automotive Electronic Control Systems, DOT HS 812 285, 2016. PDF 쪽 = 인쇄 쪽 + 10)

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| FE-105 | 17 | 보고서는 AUTOSAR를 자동차 제조사, 공급업체, tool과 semiconductor 업체의 협력체가 만드는 ECU용 개방형 표준 소프트웨어 구조로 소개한다. | "open, standardized software architecture for automotive electronic control units" | AUTOSAR 사이트의 글을 인용한 것이다 (보고서의 [11]) |
| FE-106 | 17 | AUTOSAR의 주된 목적은 safety가 아니지만, 메모리 partition, 시간 결정성, 프로그램 흐름 감시, 통신 stack 기능 같은 구조적 개념으로 ISO 26262를 돕는다. 이런 기능만으로 계통 안전을 보장하지 못한다. | "Such design features alone cannot guarantee system safety" | 앞 문장의 인용 칸에 넣을 만한 구절은 "main objective is not safety"이다. 원고의 AUTOSAR 소개에 이 단서를 넣을 근거다 |

## 찾지 못한 것

아래는 받은 문서에서 근거가 되는 서술을 찾지 못한 주제다. 원고에 쓰려면 근거 문서를 더 받아야 하고, 못 받으면 쓰지 않거나 `(확인 필요)`를 단다.

- CAN frame의 구조 (identifier, data 길이, CRC, ACK)와 한 frame에 실을 수 있는 data의 크기. 받은 문서에는 "CAN"이라는 이름이 예로만 나온다 (FE-003, FE-015, FE-031, FE-051, FE-088, FE-090, FE-104).
- CAN의 우선순위와 중재 (arbitration), 오류 검출 (CRC, bit stuffing, ACK 오류), 오류 계수기와 bus-off. 전기차와 가솔린차 보고서에서 "arbitration"은 토크 요구의 조정 논리를 가리킨다 (예: FE-016). EV 보고서 83쪽의 "bus arbitration"은 EV PCM 내부의 on-chip 통신 진단 항목 이름으로만 나온다. 두 AUTOSAR 문서와 NASA 보고서에는 bus-off 이야기가 없다 (글자 검색으로 확인).
- CAN FD와 Ethernet의 특성 (속도, frame 크기, 용도). 이름만 FE-104에 있다.
- "CAN의 CRC가 선 위의 손상을 잡는다"는 서술. FE-088은 CAN이나 FlexRay의 보호 기구가 손실과 손상 검출을 맡는다고 정당화하는 한 줄뿐이다. 어떤 오류를 어느 확률로 잡는가는 어떤 문서에도 없다.
- 12V 계통의 전압 범위, battery의 상태, 시동 때의 전압 저하, 전원 모드 (ignition off, accessory, on, start), wake-up과 sleep. FE-014, FE-031, FE-032는 "12V 전원"과 "ignition key 위치"만 말한다. NASA 보고서는 ignition key 한 번 돌림 (key cycle)을 고장 기억의 경계로 쓴다 (FE-073, FE-074).
- DTC의 형식 (P0xxx 같은 코드의 구조)과 OBD-II의 통신 방식, 진단 도구가 읽는 방법. NASA 보고서가 코드 번호를 예로 적고 (FE-076) OBD의 역사를 적지만 (FE-077), 형식은 정의하지 않는다. UDS 같은 진단 규격은 받은 문서에 없다.
- AUTOSAR Classic의 층 이름 가운데 services, ECU abstraction, microcontroller abstraction (MCAL)과 그림 전체. 받은 문서에는 SW-C, RTE, OS, basic software module, complex driver가 흩어져 나오지만 층의 완전한 목록과 그림은 없다 (layered software architecture 문서는 받지 않았다).
- gateway의 역할 설명. 두 AUTOSAR 문서가 gateway를 오류 원천으로 한 번 언급할 뿐이다 (FE-090, FE-095).
- 계기판이 경고를 받는 경로 (CAN 메시지인지 직결선인지). FE-025는 EV PCM이 표시등 명령을 낸다고만 적는다. 경고 표시는 보고서의 범위 밖이다 (FE-005).
- 브레이크 스위치의 구조 (접점 둘). EV 보고서는 각도를 재는 센서를 쓰고 (FE-028), NASA 보고서는 brake switch의 두 접점이 서로 맞지 않으면 DTC를 낸다고 표에 적는다 (78쪽). 후자는 표의 칸이라 인용 칸에 넣지 못했고, 원고에 쓰려면 78쪽을 직접 열어 확인한다.
- inverter의 동작 원리 (PWM, field-oriented control 등)와 모터 종류. FE-020, FE-021이 부품의 역할만 적는다.

## 지금 원고에서 근거가 서 있는 문장과 없는 문장

원고에는 `(2차 자료)`나 `(확인 필요)` 표시가 하나도 없다. 아래는 문장마다 이 파일의 사실로 확인되는지를 가린 것이다.

근거가 있다 (원고의 문장 - 사실 번호)

- 부품 표의 여섯 줄 (페달 센서, 차량 제어기, inverter 제어부, gate drive, 전력 스위치, 구동 모터) - FE-015, FE-016, FE-018, FE-019, FE-020, FE-011
- 방향, 페달을 놓았을 때, creep을 소프트웨어로 흉내, 회생 제동, 구동 계통이 꺼지면 구동력을 잃음 - FE-011, FE-012, FE-010, FE-009, FE-029, FE-008
- 센서를 둘 달고 서로 견준다 - FE-065, FE-070, FE-072
- 전원과 접지를 따로 주는 것 - FE-066, FE-038 (실제 차에서 페달 센서는 전용선)
- 메시지가 손상, 사라짐, 되풀이, 늦음, 뒤바뀜을 겪는다 - FE-089, FE-099
- 보내는 쪽이 검사 정보를 붙이고 받는 쪽이 검사한다 - FE-091, FE-103
- 제어기가 TICM을 거치지 않고 gate drive에 직접 닿는 길이 보고서의 구성도에 있다 - FE-014, FE-027
- AUTOSAR의 응용 소프트웨어 (SW-C)가 RTE 위에 있고 OS와 basic software가 아래라는 것 - FE-080, FE-081, FE-082, FE-085, FE-086
- 보고서가 분석 범위를 페달부터 inverter와 그 센서까지로 잡는다 - FE-001, FE-002
- 구동 토크가 0이면 타력으로 간다 - FE-010

근거가 없거나 약하다 (원고의 문장 - 이유)

- "전기차에서 운전자의 발과 바퀴 사이에는 기계적인 연결이 없다." - 보고서가 이렇게 쓰지 않는다. FE-007, FE-011이 같은 뜻을 간접으로 보인다. 페달에 스프링이 있어 원위치로 돌아가는 기계 부분은 있다 (FE-022). 문장을 "페달과 모터 사이는 센서와 제어기의 신호로 이어진다"처럼 보고서의 서술에 맞게 고칠 수 있다.
- "network와 별개로 직결선을 쓰기도 한다. ... network나 그것을 다루는 소프트웨어가 틀려도 구동을 막을 수 있는 길을 따로 두는 것이다." - 보고서는 TICM을 건너뛰어 gate drive에 직접 가는 경로가 "있을 수 있다"고만 쓴다 (FE-027). 그 목적이 network 고장 대비라는 설명은 보고서에 없다 (저자의 해석이다). 책의 표현을 해석이라고 밝히거나 NASA의 monitor 경로 (FE-063, FE-064: sub-CPU가 throttle 모터 전원을 끊음)를 같은 설계 발상의 사례로 드는 편이 낫다.
- "CAN에는 CRC가 있으니 값이 옳다. network의 CRC는 선 위의 손상을 잡는다." - CAN의 CRC 동작을 설명한 문서가 없다 (FE-088이 한 줄 언급). 나머지 (보내는 제어기 안의 오류, 오래된 메시지, 오지 않은 메시지를 CRC가 못 잡는다)는 E2E 문서의 오류 목록 (FE-089, FE-090)과 최신성 한계 (FE-094)로 뒷받침되지만, "CAN의 CRC"에 대한 말로는 근거가 없다.
- "예제의 구동 허용 신호가 그렇다." (구동 허용 신호를 직결선으로 둠) - 예제의 설계다. 외부 문서의 근거가 필요한 주장이 아니다.
- "예제에서는 0.5-4.5 V와 0.25-2.25 V다. 두 선이 서로 붙으면 두 값이 맞지 않게 된다." - 예제의 설계다. 외부 근거로는 실제 차가 0.8V 오프셋을 쓰고 오프셋의 목적이 공통 원인 고장 방지라는 것 (FE-065, FE-072)이 있다.
- "쓰는 전압의 범위를 전원의 끝에서 띄운다. 0 V나 전원 전압이 읽히면 선이 끊겼거나 붙은 것이다." - 받은 문서에 이 이유를 설명한 곳이 없다. NASA 보고서는 페달 센서의 low voltage와 high voltage (open, ground short, short to +V)를 별개 DTC로 둔다 (FE-076). 이는 같은 방식의 범위 검사를 쓴다는 뜻이지만, "띄운다"는 설계 선택의 이유는 아니다. VPA1이 3.0V 이상에서 throttle이 최대라는 서술은 97쪽에 있다.
- "페달의 위치는 운전자의 뜻을 전하는 하나뿐인 신호다." - 보고서는 운전자의 뜻이 가속 페달과 브레이크 페달 둘로 전해진다고 가정한다 (nhtsa-etc-ev-fsa 29쪽, 인쇄 13쪽). "하나뿐"은 가속 요구에 한정해야 맞다. 이 가정의 인용은 사실 표에 넣지 않았다.
- "예제의 차량 제어기는 제동 제어기에서 차량 속도를 받고" - 예제의 설계다. 보고서의 가정 (FE-006)과 같다.
- "실제 제어기에서 메모리 보호, 실행 시간의 감시, 통신의 보호는 아래 층이 준다." - 메모리 보호는 FE-083, 감시는 FE-085, 통신 보호는 E2E 라이브러리 (FE-091, 지금 AUTOSAR 판에서는 RTE의 data transformer 등에서 호출한다고 문서가 소개)로 확인된다. 다만 "실행 시간의 감시" 가운데 OS의 timing protection은 60쪽의 표에 요구의 이름만 있고 서술이 짧다. 필요하면 23-27쪽을 읽고 추가한다.
- "RTE ... 응용과 아래 층 사이의 값을 나른다" - FE-081은 SW-C 사이의 교환을 RTE가 맡는다고 한다. "아래 층과의 값"은 이 쪽만으로 확정되지 않는다 (지금 표현을 "SW-C가 서로 값을 주고받는 통로"로 줄이면 맞는다).
- "complex driver: 층을 거치지 않고 입출력에 직접 닿는 부분" - FE-086은 직접 접근을 말한다. 다만 "층을 거치지 않는다"는 표현은 받은 문서의 말이 아니다.
- "(Becker 외, 2020)"과 "(AUTOSAR, 2025)" 두 인용은 쪽이 없다 - RULES.md 5.4에 따라 쪽이나 절을 적어야 한다. 각각 이 파일의 해당 쪽 (FE-xxx)을 쓰면 된다.

## 지금 원고와 받은 문서가 어긋나 보이는 곳

- "센서가 둘이면 고장 하나는 견딘다. 견주는 것은 틀린 것을 알아챌 뿐이다. 어느 쪽이 맞는지는 모른다. 견디려면 셋이 있거나, 다른 정보가 있어야 한다." - nasa-toyota-ua-report 49쪽과 67쪽은 페달 센서 하나가 고장나면 limp home으로 들어가 남은 센서로 제한된 범위 (10-15도)를 제어한다고 쓰고, 이를 "redundant to continuing to operate the vehicle albeit with reduced power"로 평가한다 (FE-060, FE-071). 어느 쪽이 틀렸는지는 센서마다의 범위 검사 DTC로 가린다 (63쪽, FE-076). 그러므로 "견주기만으로는 어느 쪽이 맞는지 모른다"는 맞지만 "고장 하나를 견디지 못한다"는 일반 진술은 이 차의 설계와 어긋난다. 정확히는 "견주기만 하면 알아채기만 하고, 계속 달리려면 범위 검사 같은 다른 정보와 줄인 동작이 필요하다"이다. (이 차는 줄인 동작으로 견딘다.)
- "전압 범위를 다르게 해도 소용없다. 전원이 올라가면 두 채널이 같은 비율로 올라가 서로 맞는다." - 이 문장은 전원을 공유할 때의 이야기이고 문서와 직접 충돌하지 않는다. 다만 nasa-toyota-ua-report 72쪽은 두 신호를 오프셋으로 고른 목적이 공통 원인 고장 방지라고 쓴다 (FE-072). 책의 예제가 전원을 따로 주는 이유와 NASA의 오프셋의 이유가 겹친다. "오프셋만으로는 부족하고 전원과 접지도 따로" 식으로 두 근거를 함께 쓰면 문서와 맞는다.
- 원고는 부품 설명의 근거를 이 보고서로 밝혔다 (Becker 외, 2020). 그러나 보고서의 브레이크 입력은 각도를 재는 센서 (BPPS, nhtsa-etc-ev-fsa 35쪽)이고, 이 책의 예제는 브레이크 스위치다. 브레이크 입력을 설명할 때는 보고서의 서술과 예제의 설계를 따로 밝혀야 한다. 지금 원고의 본문은 브레이크 입력을 거의 설명하지 않는다.
- 어긋나는 것은 위의 첫 항목 외에는 찾지 못했다. ("내연기관은 변속기가 방향을 바꾼다"는 보고서의 "separate transmission system" 서술 (31쪽)과 맞는다.)
