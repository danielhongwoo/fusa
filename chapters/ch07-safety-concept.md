# 7장. Safety concept: 요구사항을 아래로 내리기

## 장 계획

| 항목 | 내용 |
|---|---|
| Part | II. Hazard에서 소프트웨어 요구사항까지 |
| 쓰는 단계 | 단계 1 (뼈대). 단계 2에서 깊게 고친다 |
| 목표 분량 | 16쪽 |
| 상태 | 미착수 |

### 핵심 질문

safety goal 한 문장이 어떻게 소프트웨어 요구사항 수십 개가 되는가?

### 다룰 내용

- functional safety concept와 technical safety concept
- 요구사항의 계층과 allocation
- hardware-software interface
- fault detection과 fault reaction에 주어진 시간 예산
- ASIL decomposition과 그 전제 조건 (독립성)
- warning과 degradation
- 로봇과 드론에서는 (단계 3에서 채운다)

### 검토에서 더한 항목 (2026-11-22)

괄호 안은 지적 번호이고, 검토 기록은 `reviews/2026-11-22-plan/`에 있다. 규격의 내용에 관한 항목은 쓰기 전에 확인한다 (RULES.md 5절).

- 시간 모델을 그림 하나로 정리한다: FTTI와 그것을 나눈 시간 구간 (fault detection, fault reaction 등) (F-12)
- ASIL decomposition의 조건과 흔한 오용. 나누면 싸진다는 오해 (F-14)
- E-Gas 구조에서 기능 쪽과 감시 쪽의 등급이 정해지는 방식. decomposition과 coexistence의 차이 (F-14)
- fault reaction과 warning, fault 기록 (E-10)

### 예제 산출물

functional safety concept, technical safety concept (3단계 감시 구조, 하드웨어 가정 목록, 시간 예산표, decomposition 또는 coexistence 판단)

### 근거

ISO 26262-3, -4, -9

## 본문

아직 쓰지 않았다.
