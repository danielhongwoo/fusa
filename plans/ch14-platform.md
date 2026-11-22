# 14장. 플랫폼: RTOS, OS, multicore - 장 계획

원고: [chapters/ch14-platform.md](../chapters/ch14-platform.md)

| 항목 | 내용 |
|---|---|
| Part | III. 안전한 소프트웨어 만들기 |
| 쓰는 단계 | 단계 2 (살 붙이기) |
| 상태 | 초고 (2026-11-23, 단계 2의 묶음 3). 검토를 거쳤다 (`reviews/2026-11-23-stage2-part3/`) |

독자는 임베디드 개발 경험이 있다 (2026-11-22 결정). 이 장에서 임베디드의 기초는 다시 설명하지 않고, 같은 주제를 안전의 관점에서만 다룬다.

## 핵심 질문

내 코드 아래에 있는 소프트웨어와 프로세서는 믿을 수 있는가?

## 다룰 내용

- 실시간성과 scheduling
- worst-case execution time과 stack 사용량 분석
- 안전 인증을 받은 RTOS와 hypervisor가 제공하는 것과 제공하지 않는 것
- AUTOSAR Classic과 Adaptive의 safety 기능
- Linux 같은 범용 OS를 안전 시스템에 쓰는 문제 (ELISA project 등)
- multicore에서의 간섭
- 로봇과 드론에서는 (단계 3에서 채운다)

## 검토에서 더한 항목 (2026-11-22)

괄호 안은 지적 번호이고, 검토 기록은 `reviews/2026-11-22-plan/`에 있다. 규격의 내용에 관한 항목은 쓰기 전에 확인한다 (RULES.md 5절).

- AUTOSAR는 Classic을 중심으로 쓴다. 층 구조 그림 하나. Adaptive는 한 문단 (E-11)
- 실행 시간은 측정, 여유, 실행 중 감시를 중심으로 쓴다. 정적 분석은 1쪽 (E-08)
- stack 사용량: 초기 패턴을 채워 최대 사용량을 재는 방법과 MPU로 막는 방법 (E-08)
- map file 읽기: memory 배치, stack, partition의 경계 (E-09)
- 범용 OS와 hypervisor는 상자 하나로 줄인다 (F-27)

## 예제 산출물

task 설계와 timing 예산, 플랫폼 선택의 근거

## 관련 규격과 자료

ISO 26262-6; AMC 20-193 (multicore); AUTOSAR 공개 문서

받은 문서: faa-ac-20-193, autosar-safety-measures

## 근거 위치 (2026-11-22)

받은 문서에서 이 장을 뒷받침하는 곳이다. 쪽은 PDF 파일의 몇 번째 쪽인지다. 에이전트가 문서를 읽어 뽑은 것이므로, 원고에 쓰기 전에 그 쪽을 직접 읽어 확인한다 (RULES.md 5.2절).

| 문서 | 절 | 쪽 | 뒷받침하는 내용 |
|---|---|---|---|
| `autosar-safety-measures` | 2.2 Timing Monitoring (2.2.2.3 Timing Protection of the Operating System) / 2.1 Memory Partitioning | 22-28, 9-21 | OS의 실행 시간 budget 감시, 메모리 보호 (AUTOSAR Classic 기준) |
| `autosar-safety-measures` | 3.7.1 Timing Related Features | 48-60 | 동기화된 시간 기반, 시간 결정적 구현, timing violation 방어 기능 |
| `faa-ac-20-193` | 3 Background / 5.2-5.8 Multi-core processor guidance (objectives MCP_Planning, MCP_Resource_Usage, MCP_Software) | 3-13 | multicore의 간섭 채널과 robust resource partitioning 목표 (FAA AC 20-193이며 EASA AMC 20-193이 아님) |
| `nasa-gb-8719-13` | 11.4 Operating Systems (11.4.2 Do I need an RTOS?, 11.4.3 What to look for in an RTOS) | 241-245 | RTOS의 안전 관련 선택 기준 (기준 시점은 2004년경) |
| `koopman-toyota-ua` | slides 52-55 (Real Time Scheduling, RMA, Does ETCS Meet Deadlines?) | 52-55 | rate monotonic analysis와 deadline 분석 필요성 (원고 측 전문가 의견) |
| `nasa-gb-8719-13` | 6.6.6 Timing, Throughput And Sizing Analysis | 130 | 타이밍, 메모리 크기 분석 |
| `koopman-toyota-ua` | slide 43 (Toyota ETCS and Recursion) | 43 | 재귀와 stack 사용의 관계 |

### 받은 문서에 근거가 없는 항목

이 항목은 다른 공개 문서를 찾거나, `(2차 자료)`로 밝히거나, 쓰지 않는다.

- WCET 분석 - nasa-gb p368 한 줄. 측정/여유/감시 방법의 근거 없음
- AUTOSAR Adaptive, 인증 RTOS와 hypervisor, Linux(ELISA), EASA AMC 20-193 - 없음 (faa-ac-20-193은 FAA 문서, hypervisor 언급 5회)
- stack 사용량 측정(초기 패턴), map file - 없음
