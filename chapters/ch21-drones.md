# 21장. 드론: 운용 위험 기반의 방식

## 장 계획

| 항목 | 내용 |
|---|---|
| Part | V. 넓히기 |
| 쓰는 단계 | 단계 3 (넓히기) |
| 상태 | 미착수 |

### 핵심 질문

멈출 수 없는 기계는 어떻게 안전해지는가? 제품이 아니라 운용을 기준으로 위험을 따지면 무엇이 달라지는가?

### 다룰 내용

- 단일 규격이 없는 분야: 규제, 운용 위험 평가, 업계 규격의 조합
- 운용 범주: Open, Specific, Certified (EU 규정 2019/947)
- SORA: ground risk와 air risk, SAIL, operational safety objective, 요구 수준 (integrity와 assurance), containment
- 소프트웨어 보증의 단계: 저위험 운용은 ASTM F3201, 고위험 운용은 항공 규격 (DO-178C)
- 정지가 safe state가 아닌 시스템: 출발점 복귀, 제자리 비행, 강제 착륙, flight termination, parachute
- 드론의 safety mechanism: geofence, 조종 link 상실 대응, 위치 정보 상실 대응, battery 감시, 센서 중복과 상태 추정 감시
- run-time assurance 구조 (ASTM F3269): 복잡한 기능을 단순한 감시기와 대체 제어기로 감싸기. 11장의 monitor 구조와 연결
- 공개 autopilot (PX4, ArduPilot)의 failsafe 구현 읽기
- 미국과 한국의 제도 개요 (쓰는 시점에 조사)

### 예제 산출물

소형 multicopter 운용의 SORA 요약 (SAIL 결정), geofence와 link 상실 대응의 상태 기계 설계. 세 분야의 safe state 비교표

### 근거

JARUS SORA 2.5; EU 규정 2019/947과 EASA AMC, GM; EASA Special Condition Light-UAS; ASTM F3201; ASTM F3269; EUROCAE ED-280; DO-178C

## 본문

아직 쓰지 않았다.
