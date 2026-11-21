# 14장. 플랫폼: RTOS, OS, multicore

## 장 계획

| 항목 | 내용 |
|---|---|
| Part | III. 안전한 소프트웨어 만들기 |
| 쓰는 단계 | 단계 2 (살 붙이기) |
| 목표 분량 | 12쪽 |
| 상태 | 미착수 |

### 핵심 질문

내 코드 아래에 있는 소프트웨어와 프로세서는 믿을 수 있는가?

### 다룰 내용

- 실시간성과 scheduling
- worst-case execution time과 stack 사용량 분석
- 안전 인증을 받은 RTOS와 hypervisor가 제공하는 것과 제공하지 않는 것
- AUTOSAR Classic과 Adaptive의 safety 기능
- Linux 같은 범용 OS를 안전 시스템에 쓰는 문제 (ELISA project 등)
- multicore에서의 간섭
- 로봇과 드론에서는 (단계 3에서 채운다)

### 검토에서 더한 항목 (2026-11-22)

괄호 안은 지적 번호이고, 검토 기록은 `reviews/2026-11-22-plan/`에 있다. 규격의 내용에 관한 항목은 쓰기 전에 확인한다 (RULES.md 5절).

- AUTOSAR는 Classic을 중심으로 쓴다. 층 구조 그림 하나. Adaptive는 한 문단 (E-11)
- 실행 시간은 측정, 여유, 실행 중 감시를 중심으로 쓴다. 정적 분석은 1쪽 (E-08)
- stack 사용량: 초기 패턴을 채워 최대 사용량을 재는 방법과 MPU로 막는 방법 (E-08)
- map file 읽기: memory 배치, stack, partition의 경계 (E-09)
- 범용 OS와 hypervisor는 상자 하나로 줄인다 (F-27)

### 예제 산출물

task 설계와 timing 예산, 플랫폼 선택의 근거

### 근거

ISO 26262-6; AMC 20-193 (multicore); AUTOSAR 공개 문서

받은 문서: faa-ac-20-193, autosar-safety-measures

## 본문

아직 쓰지 않았다.
