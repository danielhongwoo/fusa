# 18장. 변경, 형상, 릴리스 이후

## 장 계획

| 항목 | 내용 |
|---|---|
| Part | IV. 안전함을 보이고 유지하기 |
| 쓰는 단계 | 단계 2 (살 붙이기) |
| 상태 | 미착수 |

### 핵심 질문

한 번 안전하다고 보인 소프트웨어를 바꿀 때 무엇을 다시 해야 하는가?

### 다룰 내용

- configuration management와 baseline
- change management와 impact analysis
- configuration data와 calibration data의 안전
- 생산, 운영, 서비스, 폐기 단계의 안전
- field monitoring, over-the-air update
- 반복적 개발 (agile, CI)과 safety lifecycle을 함께 쓰는 법

### 검토에서 더한 항목 (2026-11-22)

괄호 안은 지적 번호이고, 검토 기록은 `reviews/2026-11-22-plan/`에 있다. 규격의 내용에 관한 항목은 쓰기 전에 확인한다 (RULES.md 5절).

- bootloader와 software update: 갱신 중의 전원 상실, 호환 검사, 되돌리기 (E-06)
- calibration 값이 안전 요구사항을 깨뜨릴 수 있다는 점. 예제의 최대 토크 parameter와 범위 검사 (E-10)
- CI: host test, 정적 분석, coverage를 자동으로 돌린다 (E-13)
- software update에 관한 규제와 규격: UN R156, ISO 24089 (F-26)

### 예제 산출물

변경 요청 1건에 대한 impact analysis

### 근거

ISO 26262-2, -6 (Annex C), -7, -8; IEC 61508-1, -3

더할 근거: UN R156, ISO 24089

## 본문

아직 쓰지 않았다.
