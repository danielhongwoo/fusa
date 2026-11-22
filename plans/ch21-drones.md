# 21장. 드론: 운용 위험 기반의 방식 - 장 계획

원고: [chapters/ch21-drones.md](../chapters/ch21-drones.md)

| 항목 | 내용 |
|---|---|
| Part | V. 넓히기 |
| 쓰는 단계 | 단계 3 (넓히기) |
| 상태 | 미착수 |

## 핵심 질문

동력을 끊는 것이 안전하지 않은 기계는 어떻게 안전해지는가? 제품이 아니라 운용을 기준으로 위험을 따지면 무엇이 달라지는가?

## 다룰 내용

- 단일 규격이 없는 분야: 규제, 운용 위험 평가, 업계 규격의 조합
- 운용 범주: Open, Specific, Certified (EU 규정 2019/947)
- SORA: ground risk와 air risk, SAIL, operational safety objective, 요구 수준 (integrity와 assurance), containment
- 동력을 끊는 것이 safe state가 아닌 시스템: 제자리 비행, 출발점 복귀, 착륙, flight termination, parachute
- 드론의 safety mechanism: geofence, 조종 link 상실 대응, 위치 정보 상실 대응, battery 감시, 센서 중복과 상태 추정 감시
- run-time assurance 구조 (ASTM F3269): 복잡한 기능을 단순한 감시기와 대체 제어기로 감싸기. 11장의 monitor 구조와 연결
- 공개 autopilot (PX4, ArduPilot)의 failsafe 문서 읽기

## 검토에서 더한 항목 (2026-11-22)

괄호 안은 지적 번호이고, 검토 기록은 `reviews/2026-11-22-plan/`에 있다. 규격의 내용에 관한 항목은 쓰기 전에 확인한다 (RULES.md 5절).

- 장의 중심 사슬: SORA -> SAIL -> OSO -> Special Condition Light-UAS -> 소프트웨어 보증 (F-23)
- 소프트웨어 보증의 경로를 EU와 미국으로 나눠 적는다. EU: SAIL IV는 DAL C 수준, SAIL V와 VI는 failure condition에 따른 DAL B-D. 미국: ASTM F3201 (F-07, F-08)
- 상태 기계: link 상실, geofence 이탈, 위치 상실. 공개 autopilot의 failsafe 표와 대응시킨다 (E-23)
- geofence는 벗어난 뒤에 작동한다는 점, 고장이 겹치면 가장 심각한 대응이 선택된다는 점 (E-23)
- flight termination은 safe state가 아니라 지상의 위험을 가두는 수단이다 (F-09)
- 공개 autopilot의 소스 코드는 읽지 않는다. 문서와 상태 기계 그림으로 대신한다 (E-23)
- 미국과 한국의 제도는 쓰는 시점에 확인하는 상자로 줄인다 (F-23)

## 예제 산출물

소형 multicopter 운용 하나의 SAIL 결정, link 상실과 geofence 이탈과 위치 상실에 대한 상태 기계 설계. 세 분야의 safe state 비교표

## 관련 규격과 자료

JARUS SORA 2.5; EU 규정 2019/947과 EASA AMC, GM; EASA Special Condition Light-UAS; ASTM F3201; ASTM F3269; EUROCAE ED-280; DO-178C

받은 문서: sora-2-5-main-body, easa-ed-2025-018-r-annex, easa-ear-uas, easa-sc-light-uas-medium-risk, easa-moc-light-uas-2510, easa-moc-light-uas-high-risk-2510, faa-ac-20-115d
