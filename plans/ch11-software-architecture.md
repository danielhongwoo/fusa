# 11장. Software architecture for safety - 장 계획

원고: [chapters/ch11-software-architecture.md](../chapters/ch11-software-architecture.md)

| 항목 | 내용 |
|---|---|
| Part | III. 안전한 소프트웨어 만들기 |
| 쓰는 단계 | 단계 1 (뼈대). 단계 2에서 깊게 고친다 |
| 상태 | 미착수 |

## 핵심 질문

일부가 고장 나도 안전한 구조는 어떻게 만드는가?

## 다룰 내용

- 설계 원칙: 단순함, 계층, 인터페이스 제한
- partitioning과 freedom from interference (timing, memory, 정보 교환)
- 등급이 다른 소프트웨어를 한 시스템에 섞기 (mixed criticality)
- 기능과 감시의 분리: monitor 구조, E-Gas 3단계 감시 구조
- redundancy와 diversity, voting (1oo2, 2oo3)
- safe state 진입, degradation, 상태 관리
- 아키텍처에 safety analysis를 다시 적용하기
- 로봇과 드론에서는 (단계 3에서 채운다)

## 검토에서 더한 항목 (2026-11-22)

괄호 안은 지적 번호이고, 검토 기록은 `reviews/2026-11-22-plan/`에 있다. 규격의 내용에 관한 항목은 쓰기 전에 확인한다 (RULES.md 5절).

- 응용, 감시, HAL의 3층 구조를 정적 view의 기본 예로 둔다 (E-12)
- 흔한 오해: thread를 나누면 partitioning이다 (F-05)
- model-based development: 모델이 설계인가 코드인가 (2쪽) (F-25)
- 아키텍처 수준의 safety analysis 1건을 예제에 적용한다 (F-30)
- 독립성 주장 목록과 sim이 보이는 것과 못 보이는 것 표 (F-05, E-15)
- 21장의 run-time assurance 구조와 잇는 상자 (F-23)

## 예제 산출물

software architecture (응용, 감시, HAL의 3층과 task table. 정적 view와 동적 view), partitioning 결정의 근거, 독립성 주장 목록

## 관련 규격과 자료

ISO 26262-6 (Annex D 포함), -9; IEC 61508-3 (Annex F 포함); E-Gas monitoring concept

## 근거 위치 (2026-11-22)

받은 문서에서 이 장을 뒷받침하는 곳이다. 쪽은 PDF 파일의 몇 번째 쪽인지다. 에이전트가 문서를 읽어 뽑은 것이므로, 원고에 쓰기 전에 그 쪽을 직접 읽어 확인한다 (RULES.md 5.2절).

| 문서 | 절 | 쪽 | 뒷받침하는 내용 |
|---|---|---|---|
| `nasa-gb-8719-13` | 7.4.1 Designing for Safety / 7.4.2 Designing around Faults and Failures (7.4.2.1 N-Version, 7.4.2.2 Fault Containment Regions, 7.4.2.3 Redundant Architecture) | 138-146 | 단순함, 계층, 인터페이스 제한, 독립 병렬 redundancy와 직렬 inhibit의 독립 조건, fault propagation 방지, N-version 한계 |
| `nasa-gb-8719-13` | 7.5.2 Design Safety Analysis / 7.5.3 Independence Analysis | 157-159 | 아키텍처에 safety analysis를 다시 적용, 안전 부품의 분리 확인 |
| `autosar-safety-measures` | 2.1 Memory Partitioning (2.1.2.1-2.1.2.6, 2.1.3, 2.1.4) / 2.2 Timing Monitoring | 9-28 | freedom from interference의 memory와 timing 수단, 등급이 다른 SW-C 혼합 조건, 한계 |
| `autosar-safety-measures` | 3.7.2 E-Gas Monitoring Related Features | 60-65 | E-Gas 3단계 감시 구조의 AUTOSAR 구현 설명 (2차 자료) |
| `nasa-toyota-ua-report` | 6.5 System Fail-Safe Architecture (6.5.1 Redundancy, 6.5.3 Failure Mitigation) | 64-83 | main + monitor 구조, 다양성이 있는 safing 제어, 단계적 fail-safe 모드 |
| `koopman-toyota-ua` | slides 7, 18, 31-34, 43, 47 (ETCS two CPUs, Fault Containment, Split Inputs, Recursion, Poor Isolation) | 7, 18, 31-34, 43, 47 | 2 CPU 감시 구조의 약점과 task 분리 부족 (원고 측 전문가 의견) |
| `faa-ac-20-193` | 5.4 Interference channels and resource usage / 5.5 Software verification / 5.6 Error detection and handling, and safety nets | 8-12 | multicore의 interference channel과 robust partitioning 개념 (항공, FAA AC) |
| `b737max-jatr` | R6.1-R6.3 (fail-safe design, fault tolerance, sensor voting) | 50-52 | 단일 센서 의존과 voting/health monitoring 부재 사례 |

### 받은 문서에 근거가 없는 항목

이 항목은 다른 공개 문서를 찾거나, `(2차 자료)`로 밝히거나, 쓰지 않는다.

- partitioning의 규격 조건(ISO 26262-6 Annex D), mixed criticality - autosar p9, 14의 인용 문장만. Annex 원문 없음
- model-based development 2쪽 - nasa-gb 4.2.2.4 (p70)와 autosar p45 한 문단 수준
- 21장 run-time assurance 구조 - 대상 문서에 없다
