# 11장. Software architecture for safety

## 장 계획

| 항목 | 내용 |
|---|---|
| Part | III. 안전한 소프트웨어 만들기 |
| 쓰는 단계 | 단계 1 (뼈대). 단계 2에서 깊게 고친다 |
| 상태 | 미착수 |

### 핵심 질문

일부가 고장 나도 안전한 구조는 어떻게 만드는가?

### 다룰 내용

- 설계 원칙: 단순함, 계층, 인터페이스 제한
- partitioning과 freedom from interference (timing, memory, 정보 교환)
- 등급이 다른 소프트웨어를 한 시스템에 섞기 (mixed criticality)
- 기능과 감시의 분리: monitor 구조, E-Gas 3단계 감시 구조
- redundancy와 diversity, voting (1oo2, 2oo3)
- safe state 진입, degradation, 상태 관리
- 아키텍처에 safety analysis를 다시 적용하기
- 로봇과 드론에서는 (단계 3에서 채운다)

### 검토에서 더한 항목 (2026-11-22)

괄호 안은 지적 번호이고, 검토 기록은 `reviews/2026-11-22-plan/`에 있다. 규격의 내용에 관한 항목은 쓰기 전에 확인한다 (RULES.md 5절).

- 응용, 감시, HAL의 3층 구조를 정적 view의 기본 예로 둔다 (E-12)
- 흔한 오해: thread를 나누면 partitioning이다 (F-05)
- model-based development: 모델이 설계인가 코드인가 (2쪽) (F-25)
- 아키텍처 수준의 safety analysis 1건을 예제에 적용한다 (F-30)
- 독립성 주장 목록과 sim이 보이는 것과 못 보이는 것 표 (F-05, E-15)
- 21장의 run-time assurance 구조와 잇는 상자 (F-23)

### 예제 산출물

software architecture (응용, 감시, HAL의 3층과 task table. 정적 view와 동적 view), partitioning 결정의 근거, 독립성 주장 목록

### 근거

ISO 26262-6 (Annex D 포함), -9; IEC 61508-3 (Annex F 포함); E-Gas monitoring concept

## 본문

아직 쓰지 않았다.
