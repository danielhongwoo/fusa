# 18장. 변경, 형상, 릴리스 이후 - 장 계획

원고: [chapters/ch18-change-and-configuration.md](../chapters/ch18-change-and-configuration.md)

| 항목 | 내용 |
|---|---|
| Part | IV. 안전함을 보이고 유지하기 |
| 쓰는 단계 | 단계 2 (살 붙이기) |
| 상태 | 미착수 |

## 핵심 질문

한 번 안전하다고 보인 소프트웨어를 바꿀 때 무엇을 다시 해야 하는가?

## 다룰 내용

- configuration management와 baseline
- change management와 impact analysis
- configuration data와 calibration data의 안전
- 생산, 운영, 서비스, 폐기 단계의 안전
- field monitoring, over-the-air update
- 반복적 개발 (agile, CI)과 safety lifecycle을 함께 쓰는 법

## 검토에서 더한 항목 (2026-11-22)

괄호 안은 지적 번호이고, 검토 기록은 `reviews/2026-11-22-plan/`에 있다. 규격의 내용에 관한 항목은 쓰기 전에 확인한다 (RULES.md 5절).

- bootloader와 software update: 갱신 중의 전원 상실, 호환 검사, 되돌리기 (E-06)
- calibration 값이 안전 요구사항을 깨뜨릴 수 있다는 점. 예제의 최대 토크 parameter와 범위 검사 (E-10)
- CI: host test, 정적 분석, coverage를 자동으로 돌린다 (E-13)
- software update에 관한 규제와 규격: UN R156, ISO 24089 (F-26)

## 예제 산출물

변경 요청 1건에 대한 impact analysis

## 관련 규격과 자료

ISO 26262-2, -6 (Annex C), -7, -8; IEC 61508-1, -3

더할 근거: UN R156, ISO 24089

## 근거 위치 (2026-11-22)

받은 문서에서 이 장을 뒷받침하는 곳이다. 쪽은 PDF 파일의 몇 번째 쪽인지다. 에이전트가 문서를 읽어 뽑은 것이므로, 원고에 쓰기 전에 그 쪽을 직접 읽어 확인한다 (RULES.md 5.2절).

| 문서 | 절 | 쪽 | 뒷받침하는 내용 |
|---|---|---|---|
| `nasa-gb-8719-13` | 4.5 Software Configuration Management (4.5.1 Change Control, 4.5.2 Versioning, 4.5.3 Status Accounting, 4.5.4 Defect Tracking) | 88-92 | 형상 관리, 변경 관리, 버전 관리, 결함 추적 |
| `nasa-gb-8719-13` | 10.5 Software Operations and Maintenance (10.5.2 Software Change Impact Analysis) | 201-205 | 변경 영향 분석 |
| `nasa-gb-8719-13` | 6.4.3 Requirements Change Management | 113 | 요구사항 변경의 관리 |
| `b737max-jatr` | R4 Changes during the certification process / R12 Post-certification activities | 43-45, 69-71 | 설계 변경이 safety analysis와 가정에 반영되지 않은 사례, 인증 이후 활동 |
| `ariane-501-report` | 4 Recommendations (R4 Configuration Controlled Item) | 17-18 | 핵심 소프트웨어를 형상 관리 항목으로 둘 것 (OCR본) |
| `nasa-gb-8719-13` | 4.2.1 Software Lifecycles (incremental, evolutionary) / 4.2.1.6 | 53-61 | 반복적 개발과 안전 노력의 관계 (agile은 이 문서가 권장하지 않음, p88) |
| `nhtsa-etc-ev-fsa` | 9.2.6 / 9.3.1 (calibration 요구 문장) | 90, 95 | 안전 관련 sensor, actuator, parameter의 calibration을 검증해야 한다는 요구사항 예 (ASIL B/C/D) |
| `b737max-knkt-jt610` | 3.2 Contributing Factors (6, 7번: 교체 AOA 센서의 mis-calibration) | 217-218 | 정비 중 calibration 오류가 감지되지 않은 사례 (하드웨어 calibration이며 소프트웨어 parameter는 아님) |

### 받은 문서에 근거가 없는 항목

이 항목은 다른 공개 문서를 찾거나, `(2차 자료)`로 밝히거나, 쓰지 않는다.

- UN R156, ISO 24089, OTA 갱신 - 없음
- bootloader 갱신 중 전원 상실, CI 자동화 - 없음
- 생산, 폐기 단계의 안전 - nasa-gb 10장은 운영/유지보수만
