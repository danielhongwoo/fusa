# 소프트웨어 엔지니어를 위한 기능 안전 (Functional Safety) - 가제

책 개요, 초안 v0.2 (2026-11-21)

이 문서는 책의 뼈대이자 학습 계획이다. 장마다 "핵심 질문"에 답할 수 있게 되는 것이 학습 목표이고,
그 답을 자기 말로 쓴 것이 원고가 된다.

## 1. 이 책에 대하여

### 독자

- 소프트웨어 엔지니어. C 계열 언어를 읽을 수 있고 요구사항, 설계, 테스트, 코드 리뷰, CI 같은 개발 과정에 익숙하다.
- 가정하지 않는 것: 임베디드 개발 경험, 하드웨어 지식, 안전 규격 경험.

### 책이 답하려는 질문

1. Safety는 품질이나 reliability와 무엇이 다른가?
2. "이 소프트웨어는 충분히 안전하다"는 말은 무슨 뜻이고, 누가 어떻게 판단하는가?
3. Hazard에서 출발해 내 코드에 대한 요구사항까지 어떻게 내려오는가?
4. 안전을 위해 아키텍처, 코드, 테스트는 평소와 무엇이 달라지는가?
5. 규격은 무엇을 요구하고, 왜 그렇게 요구하는가?

### 읽고 나면 할 수 있는 것

- 안전 관련 프로젝트의 문서(HARA, safety concept, safety requirement)를 읽고 자기 작업과 연결한다.
- Software safety requirement를 쓰고, 그것을 만족하는 아키텍처와 safety mechanism을 설계한다.
- Integrity level에 맞는 verification 방법을 고르고 그 근거를 설명한다.
- 규격 조항을 직접 찾아 읽고, 평가자(assessor)의 질문에 근거를 들어 답한다.
- 자동차, 로봇, 드론이 같은 안전 문제를 어떻게 다르게 푸는지 설명한다.

### 다루지 않는 것

- 하드웨어 설계와 정량 분석의 상세 (읽는 법까지만 다룬다)
- 특정 상용 tool의 사용법
- 규격 원문의 대체. 이 책은 규격을 읽기 위한 안내서이고, 규격 문장과 표를 옮겨 싣지 않는다.

## 2. 기준과 가정

아래는 개요를 잡기 위해 둔 가정이다. 바꾸면 Part II 이후의 예제와 조항 대응이 달라진다.

| 항목 | 가정 | 이유 |
|---|---|---|
| 개념의 뿌리 | IEC 61508 | 분야 공통의 기본 규격이고 대부분의 분야별 규격이 여기서 갈라져 나왔다 |
| 주 분야 | 자동차, ISO 26262 | 소프트웨어 관련 요구가 구체적이고 공개 자료가 가장 많다 |
| 보조 분야 | 로봇 (20장), 드론 (21장) | 위험을 따지는 방식이 자동차와 달라, 비교하면 개념이 분명해진다 |
| 그 밖의 분야 | 22장에서 비교 | 항공, 철도, 의료기기, 공정 |
| 원고 언어 | 한국어, 기술 용어는 영어 그대로 | 규격과 국제 자료를 바로 찾을 수 있게 |
| 예제 코드 | C (필요한 곳에 Rust 비교) | 안전 분야의 현재 주 언어 |

### 세 분야를 함께 다루는 방식

Part I-IV는 자동차를 기준으로 쓴다. 로봇과 드론은 Part V에서 한 장씩 다루고,
앞 장들에는 차이가 큰 곳에만 "로봇과 드론에서는"이라는 짧은 항목을 둔다.

세 분야는 같은 문제를 서로 다른 방식으로 푼다. 이 차이가 책의 비교 축이다.

| 비교 항목 | 자동차 | 로봇 | 드론 |
|---|---|---|---|
| 위험을 따지는 단위 | 제품의 기능 (item) | 기계와 작업 | 운용 (operation) |
| 위험 평가 방법 | HARA | ISO 12100 risk assessment | SORA |
| 등급 | ASIL A-D | PL a-e 또는 SIL 1-3 | SAIL I-VI (운용 단위의 등급) |
| 소프트웨어 요구의 출처 | ISO 26262-6 | ISO 13849-1, IEC 62061, IEC 61508-3 | ASTM F3201, 고위험 운용은 DO-178C |
| 대표적인 safe state | 기능 축소 또는 정지 | 정지 (protective stop) | 정지할 수 없음: 복귀, 착륙, 비행 종료 |

주의할 점
- 로봇에는 소프트웨어 개발 과정을 다루는 전용 규격이 없다. 로봇 규격은 필요한 safety function과 등급을 정하고, 만드는 방법은 기계류 제어 규격에 맡긴다.
- 드론에는 ISO 26262에 해당하는 단일 규격이 없다. 규제와 운용 위험 평가가 중심이고 나라마다 다르다. 이 책은 EU 체계 (SORA)를 기준으로 삼는다.
- 드론 쪽은 제도가 빠르게 바뀐다. 21장은 쓰는 시점에 다시 확인한다.

### 기준으로 삼는 판 (2026-11 확인)

| 규격 | 기준 판 | 다음 판 상태 |
|---|---|---|
| IEC 61508 | Edition 2 (2010) | Edition 3은 최종 승인 단계이고 아직 발행 전. 2027년 발행 예상 |
| ISO 26262 | 2판 (2018) | 3판은 초안 단계. 2027년 전후 발행 예상, 확정 일정 없음 |
| ISO 13849-1 | 4판 (2023) | - |
| ISO 10218-1, -2 | 2025 | - |
| ISO 13482 | 2014 | 2판은 최종 초안 승인 단계. 발행 여부 확인 필요 |
| ISO 3691-4 | 2판 (2023) | 개정 초안 진행 중 |
| SORA | 2.5 (JARUS 2024) | EASA가 2025-09에 EU 규정의 AMC와 GM으로 채택 |
| ASTM F3201 | F3201-26 | - |
| ASTM F3269 | F3269-21 | - |
| EN 50716 | 2023 | EN 50128과 EN 50657을 대체함 |
| MISRA C | MISRA C:2025 | - |

집필 중에 IEC 61508 Edition 3이 발행될 가능성이 높다. 본문은 Edition 2 기준으로 쓰고,
바뀌는 내용은 장마다 "Edition 3에서 달라지는 점" 항목으로 따로 모은다.

## 3. 관통 예제 (running example)

책 전체에서 시스템 하나를 hazard 분석부터 safety case까지 끌고 간다. 장마다 이 예제의 산출물이 하나씩 쌓인다.

- 제안: 구동 토크 제어 (drive torque control). 가속 페달 입력을 받아 구동 모터의 토크 명령을 만드는 소프트웨어.
- 대표 hazard: 의도하지 않은 가속 (unintended acceleration).
- 고른 이유
  - 위험이 직관적이어서 자동차 지식이 없어도 이해할 수 있다.
  - 공개된 감시 구조가 있다 (E-Gas monitoring concept: 엔진 제어기용으로 자동차 회사들이 공개한 3단계 감시 구조).
  - 1장의 실제 사례(Toyota unintended acceleration)와 이어진다.
  - 센서와 모터를 PC에서 시뮬레이션할 수 있어 개발 보드 없이 실습할 수 있다.

산출물의 흐름:

```
item definition -> HARA -> safety goal -> functional safety concept
  -> technical safety concept -> software safety requirements
  -> software architecture -> safety mechanism 구현 -> test -> safety case
```

### 보조 예제

20장과 21장에서는 작은 예제를 하나씩 따로 쓴다. 위험 평가에서 구조 설계까지만 가고, 관통 예제와 나란히 놓고 비교한다.

- 로봇: 자율 이동 로봇의 protective stop. 사람이 감지 영역에 들어오면 정지하는 기능.
- 드론: 소형 multicopter의 geofence와 조종 link 상실 대응. 정해진 공역을 벗어나지 않고, 통신이 끊기면 미리 정한 동작으로 넘어가는 기능.

## 4. 목차

장의 공통 구성: 핵심 질문 / 본문 / 관통 예제에 적용 / 규격 조항 대응 / 흔한 오해 / 확인 문제.
차이가 큰 장 (3, 6, 7, 11, 12, 14, 19장)에는 "로봇과 드론에서는" 항목을 더한다.

근거 표기는 Part 단위로 적었다. 조항(clause) 단위의 대응은 각 장을 쓰면서 원문으로 확인해 부록 B에 채운다.

### Part I. 사고방식과 기본 개념

#### 1장. 소프트웨어가 사람을 다치게 할 때

- 핵심 질문: 소프트웨어는 닳지도 부러지지도 않는데 어떻게 사고를 일으키는가?
- 내용
  - 사례: Therac-25 방사선 치료기, Ariane 5 Flight 501, Toyota unintended acceleration, Boeing 737 MAX MCAS
  - 사례에서 반복되는 패턴: 요구사항의 결함, 검증 없는 재사용, 단일 입력에 대한 의존, 사라진 hardware interlock, 조직 요인
  - "버그 없는 코드"와 "안전한 시스템"이 다른 이유
- 예제 산출물: 관통 예제 소개
- 근거: 각 사고의 조사 보고서 원문

#### 2장. 기본 개념과 용어

- 핵심 질문: safety, reliability, availability, security는 어떻게 다른가?
- 내용
  - harm, hazard, hazardous event, risk
  - fault -> error -> failure
  - random hardware failure와 systematic failure. 소프트웨어 failure는 모두 systematic이라는 말의 뜻
  - safe state, fail-safe, fail-operational
  - functional safety의 정의와 범위: 기능이 올바르게 동작하는 것에 의존하는 안전
- 예제 산출물: 예제 시스템에서 무엇이 hazard이고 무엇이 fault, failure인지 정리한 표
- 근거: IEC 61508-4, ISO 26262-1, Avizienis 외 (2004)

#### 3장. Risk와 integrity level

- 핵심 질문: 얼마나 안전해야 충분한가? 그 답이 어떻게 개발 방법의 엄격함으로 바뀌는가?
- 내용
  - risk는 severity와 발생 가능성의 조합
  - tolerable risk, ALARP, risk reduction, safety function
  - SIL, ASIL, PL, SAIL, DAL: 분야마다 다른 등급 체계
  - 하드웨어에는 수치 목표를, 소프트웨어에는 방법과 엄격함을 요구하는 이유
  - integrity level에 대한 흔한 오해
- 예제 산출물: 없음 (6장에서 실제 등급을 정한다)
- 근거: IEC 61508-1, -5; ISO 26262-3

#### 4장. 규격 지도와 규격 읽는 법

- 핵심 질문: 규격은 왜 이렇게 많고 서로 어떤 관계인가? 규격 문장은 어떻게 읽어야 하는가?
- 내용
  - IEC 61508과 분야별 규격: ISO 26262, IEC 61511, IEC 62061, ISO 13849, EN 50716, IEC 62304
  - 별도 계보인 항공: DO-178C
  - 로봇: 기계류 안전 규격 (ISO 12100, ISO 13849-1) 위에 로봇 규격이 얹히는 구조
  - 드론: 규격보다 규제와 운용 위험 평가 (SORA)가 중심인 구조
  - 규격의 구조: part, clause, normative와 informative, shall과 should, work product, 방법 표의 추천 등급
  - 규격이 정해 주는 것과 개발자 판단에 맡기는 것
  - compliance, assessment, certification의 차이
- 예제 산출물: 부록 B (규격 조항 대응표)의 틀
- 근거: IEC 61508-1; ISO 26262-1, -2, -10

### Part II. Hazard에서 소프트웨어 요구사항까지

#### 5장. Safety lifecycle과 safety management

- 핵심 질문: 안전은 왜 기술만이 아니라 프로세스와 조직의 문제인가?
- 내용
  - safety lifecycle과 V-model
  - safety plan, 역할과 책임, safety culture
  - confirmation measure (review, audit, assessment)와 independence
  - 공급망에서의 책임 분담 (development interface agreement)
  - tailoring
- 예제 산출물: 예제 프로젝트의 간단한 safety plan
- 근거: ISO 26262-2, -8; IEC 61508-1

#### 6장. Hazard analysis and risk assessment

- 핵심 질문: 무엇이 위험한지 어떻게 빠짐없이 찾고, 등급을 매기는가?
- 내용
  - item definition
  - 운전 상황과 hazardous event
  - severity, exposure, controllability와 ASIL 결정
  - safety goal과 safe state
  - fault tolerant time interval
  - 다른 분야의 방법과 비교: risk graph, risk matrix, 운용 위험 평가 (20, 21장에서 자세히)
- 예제 산출물: item definition, HARA 표, safety goal
- 근거: ISO 26262-3; IEC 61508-5

#### 7장. Safety concept: 요구사항을 아래로 내리기

- 핵심 질문: safety goal 한 문장이 어떻게 소프트웨어 요구사항 수십 개가 되는가?
- 내용
  - functional safety concept와 technical safety concept
  - 요구사항의 계층과 allocation
  - hardware-software interface
  - fault detection과 fault reaction에 주어진 시간 예산
  - ASIL decomposition과 그 전제 조건 (독립성)
  - warning과 degradation
- 예제 산출물: functional safety concept, technical safety concept
- 근거: ISO 26262-3, -4, -9

#### 8장. Safety analysis 기법

- 핵심 질문: 설계가 safety goal을 위반할 수 있는 경로를 어떻게 찾는가?
- 내용
  - 원인에서 결과로 (FMEA), 결과에서 원인으로 (FTA)
  - HAZOP과 guide word
  - STPA: 제어 구조 관점의 분석
  - dependent failure analysis: common cause failure와 cascading failure
  - 분석 기법을 소프트웨어 아키텍처에 적용하는 법과 한계
- 예제 산출물: FTA 1개, 소프트웨어 수준 FMEA 1개, STPA control structure
- 근거: ISO 26262-9, ISO 26262-6 Annex E; IEC 61508-7; STPA Handbook

#### 9장. 소프트웨어 엔지니어가 알아야 할 하드웨어

- 핵심 질문: 하드웨어는 어떻게 고장 나고, 그중 무엇이 소프트웨어의 일이 되는가?
- 내용
  - random hardware failure, failure rate, failure mode
  - single-point fault, latent fault, multiple-point fault
  - diagnostic coverage
  - 하드웨어 지표 읽는 법: SPFM, LFM, PMHF (ISO 26262), HFT, SFF, PFD, PFH (IEC 61508)
  - 하드웨어 safety mechanism: lockstep core, ECC, 전압과 clock 감시
  - 소프트웨어가 맡는 진단: startup test, 주기적 self test
  - MCU safety manual 읽는 법
- 예제 산출물: 예제 MCU에 대한 가정 목록, 소프트웨어가 수행할 진단 목록
- 근거: ISO 26262-5, -11; IEC 61508-2

### Part III. 안전한 소프트웨어 만들기

#### 10장. Software safety requirements

- 핵심 질문: 검증할 수 있는 안전 요구사항은 어떻게 쓰는가?
- 내용
  - 좋은 요구사항의 속성: 명확성, 검증 가능성, 추적 가능성
  - 요구사항 표기법 (예: EARS)
  - 시간, 값의 범위, 고장 시 동작을 빠뜨리지 않는 법
  - 양방향 traceability
  - safety 요구사항과 그렇지 않은 요구사항의 공존
- 예제 산출물: software safety requirements, traceability 표
- 근거: ISO 26262-6, -8; IEC 61508-3

#### 11장. Software architecture for safety

- 핵심 질문: 일부가 고장 나도 안전한 구조는 어떻게 만드는가?
- 내용
  - 설계 원칙: 단순함, 계층, 인터페이스 제한
  - partitioning과 freedom from interference (timing, memory, 정보 교환)
  - 등급이 다른 소프트웨어를 한 시스템에 섞기 (mixed criticality)
  - 기능과 감시의 분리: monitor 구조, E-Gas 3단계 감시 구조
  - redundancy와 diversity, voting (1oo2, 2oo3)
  - safe state 진입, degradation, 상태 관리
  - 아키텍처에 safety analysis를 다시 적용하기
- 예제 산출물: software architecture (정적 view와 동적 view), partitioning 결정의 근거
- 근거: ISO 26262-6 (Annex D 포함), -9; IEC 61508-3 (Annex F 포함); E-Gas monitoring concept

#### 12장. Software safety mechanism

- 핵심 질문: 고장을 제때 감지하고 반응하는 구체적 수단은 무엇인가?
- 내용
  - watchdog (window 방식, 질의-응답 방식)과 program flow monitoring
  - end-to-end 통신 보호: CRC, sequence counter, timeout
  - memory protection과 stack 감시
  - 입력 타당성 검사: range check, plausibility check, 센서 간 비교
  - 중요 데이터의 중복 저장
  - error handling 전략과 fault reaction
  - safety mechanism 자체의 고장과 그 검사
- 예제 산출물: safety mechanism 구현, mechanism마다 덮는 fault 목록
- 근거: ISO 26262-6; IEC 61508-7; AUTOSAR 공개 문서

#### 13장. Coding for safety

- 핵심 질문: 언어와 코딩 습관은 안전에 얼마나 기여하는가?
- 내용
  - language subset과 coding standard: MISRA C:2025, MISRA C++:2023, CERT C
  - undefined behavior와 unspecified behavior
  - defensive programming
  - 동적 메모리, 재귀, interrupt, 동시성에 대한 제한
  - 정수 overflow와 floating point
  - 복잡도 관리
  - Ada/SPARK와 Rust의 위치
  - coding standard에서 벗어나는 경우 (deviation)의 관리
- 예제 산출물: 예제의 coding guideline, 정적 분석 설정, deviation 기록 예
- 근거: ISO 26262-6; IEC 61508-3, -7; MISRA 문서

#### 14장. 플랫폼: RTOS, OS, multicore

- 핵심 질문: 내 코드 아래에 있는 소프트웨어와 프로세서는 믿을 수 있는가?
- 내용
  - 실시간성과 scheduling
  - worst-case execution time과 stack 사용량 분석
  - 안전 인증을 받은 RTOS와 hypervisor가 제공하는 것과 제공하지 않는 것
  - AUTOSAR Classic과 Adaptive의 safety 기능
  - Linux 같은 범용 OS를 안전 시스템에 쓰는 문제 (ELISA project 등)
  - multicore에서의 간섭
- 예제 산출물: task 설계와 timing 예산, 플랫폼 선택의 근거
- 근거: ISO 26262-6; AMC 20-193 (multicore); AUTOSAR 공개 문서

### Part IV. 안전함을 보이기

#### 15장. Verification 전략: review, 정적 분석, formal method

- 핵심 질문: 테스트만으로 부족한 것은 무엇이고, 무엇으로 메우는가?
- 내용
  - verification과 validation
  - review와 inspection
  - 정적 분석의 종류와 한계 (잘못된 경고, 놓치는 결함)
  - abstract interpretation
  - formal verification 개관: model checking, 정리 증명, contract 기반 검증
  - integrity level에 따른 방법 선택
- 예제 산출물: unit 하나에 대한 정적 분석 결과, 간단한 formal verification 시도
- 근거: ISO 26262-6, -8; IEC 61508-3, -7; DO-333

#### 16장. Testing

- 핵심 질문: 언제 "충분히 테스트했다"고 말할 수 있는가?
- 내용
  - requirements-based testing
  - equivalence class와 boundary value
  - structural coverage (statement, branch, MC/DC)의 의미와 오용
  - unit, integration, embedded software 수준의 test
  - fault injection
  - back-to-back test
  - test 환경 (host, target, hardware-in-the-loop)과 그 차이
- 예제 산출물: test specification, coverage 보고서, fault injection test
- 근거: ISO 26262-6; IEC 61508-3; NASA MC/DC tutorial

#### 17장. Tool과 기존 소프트웨어

- 핵심 질문: 내가 만들지 않은 것 (compiler, code generator, library, open source)을 어떻게 믿는가?
- 내용
  - tool이 안전에 미치는 영향, tool confidence level, tool qualification
  - compiler와 code generator, model-based development
  - 기존 software component의 qualification, proven in use
  - 맥락 없이 개발된 요소 (SEooC: safety element out of context)와 가정의 검증
  - open source 사용
- 예제 산출물: 예제 toolchain의 tool 분류표, 외부 component 하나의 사용 근거
- 근거: ISO 26262-8, -10; IEC 61508-3; DO-330

#### 18장. 변경, 형상, 릴리스 이후

- 핵심 질문: 한 번 안전하다고 보인 소프트웨어를 바꿀 때 무엇을 다시 해야 하는가?
- 내용
  - configuration management와 baseline
  - change management와 impact analysis
  - configuration data와 calibration data의 안전
  - 생산, 운영, 서비스, 폐기 단계의 안전
  - field monitoring, over-the-air update
  - 반복적 개발 (agile, CI)과 safety lifecycle을 함께 쓰는 법
- 예제 산출물: 변경 요청 1건에 대한 impact analysis
- 근거: ISO 26262-2, -6 (Annex C), -7, -8; IEC 61508-1, -3

#### 19장. Safety case와 assessment

- 핵심 질문: 흩어진 산출물이 어떻게 "안전하다"는 하나의 주장이 되는가?
- 내용
  - claim, argument, evidence
  - Goal Structuring Notation (GSN)
  - work product와 safety case의 관계
  - confirmation review, functional safety audit, functional safety assessment
  - 형식만 갖춘 safety case의 문제
- 예제 산출물: 예제 전체의 safety case
- 근거: ISO 26262-2; GSN Community Standard; UL 4600

### Part V. 넓히기

#### 20장. 로봇: 기계류 안전의 방식

- 핵심 질문: 사람 옆에서 움직이는 기계의 안전은 자동차와 무엇이 같고 무엇이 다른가?
- 내용
  - 기계류 안전의 틀: ISO 12100 risk assessment와 3단계 위험 감소 (본질적 안전 설계, 보호 장치, 사용 정보)
  - safety function과 required performance level. PL과 SIL의 관계
  - ISO 13849-1의 구조 요구: Category, 부품 신뢰도, diagnostic coverage, common cause failure
  - ISO 13849-1의 소프트웨어 요구: embedded software와 application software의 구분, ISO 26262-6과의 깊이 차이
  - 로봇 규격이 정하는 safety function: protective stop, emergency stop, 속도와 위치 제한, speed and separation monitoring, power and force limiting
  - 로봇 종류별 규격: 산업용 로봇 (ISO 10218-1, -2), 서비스 로봇 (ISO 13482), 이동 로봇 (ISO 3691-4)
  - 흔한 구조: 안전 등급을 받은 controller와 일반 소프트웨어 (예: ROS 2)의 분리
  - 정지가 safe state인 시스템의 설계
- 예제 산출물: 자율 이동 로봇의 protective stop에 대한 risk assessment, required performance level 결정, 구조 설계. 관통 예제와의 비교표
- 근거: ISO 12100; ISO 13849-1, -2; IEC 62061; ISO 10218-1, -2; ISO 13482; ISO 3691-4

#### 21장. 드론: 운용 위험 기반의 방식

- 핵심 질문: 멈출 수 없는 기계는 어떻게 안전해지는가? 제품이 아니라 운용을 기준으로 위험을 따지면 무엇이 달라지는가?
- 내용
  - 단일 규격이 없는 분야: 규제, 운용 위험 평가, 업계 규격의 조합
  - 운용 범주: Open, Specific, Certified (EU 규정 2019/947)
  - SORA: ground risk와 air risk, SAIL, operational safety objective, 요구 수준 (integrity와 assurance), containment
  - 소프트웨어 보증의 단계: 저위험 운용은 ASTM F3201, 고위험 운용은 항공 규격 (DO-178C)
  - 정지가 safe state가 아닌 시스템: 출발점 복귀, 제자리 비행, 강제 착륙, flight termination, parachute
  - 드론의 safety mechanism: geofence, 조종 link 상실 대응, 위치 정보 상실 대응, battery 감시, 센서 중복과 상태 추정 감시
  - run-time assurance 구조 (ASTM F3269): 복잡한 기능을 단순한 감시기와 대체 제어기로 감싸기. 11장의 monitor 구조와 연결
  - 공개 autopilot (PX4, ArduPilot)의 failsafe 구현 읽기
  - 미국과 한국의 제도 개요 (쓰는 시점에 조사)
- 예제 산출물: 소형 multicopter 운용의 SORA 요약 (SAIL 결정), geofence와 link 상실 대응의 상태 기계 설계. 세 분야의 safe state 비교표
- 근거: JARUS SORA 2.5; EU 규정 2019/947과 EASA AMC, GM; EASA Special Condition Light-UAS; ASTM F3201; ASTM F3269; EUROCAE ED-280; DO-178C

#### 22장. 그 밖의 분야의 소프트웨어 안전 규격

- 핵심 질문: 같은 문제를 다른 분야는 어떻게 다르게 푸는가?
- 내용
  - 항공: DO-178C (objective 기반, DAL)
  - 철도: EN 50716
  - 의료기기: IEC 62304, ISO 14971
  - 공정: IEC 61511
  - 비교 관점: 등급을 정하는 법, 방법 지정 대 목표 제시, independence 요구, tool qualification
- 예제 산출물: 자동차, 로봇, 드론을 포함한 분야별 비교표

#### 23장. Functional safety의 경계

- 핵심 질문: 고장이 없어도 위험할 수 있다면, functional safety는 어디까지 책임지는가?
- 내용
  - 의도한 기능의 한계에서 오는 위험: SOTIF (ISO 21448)
  - cybersecurity와의 상호작용: ISO/SAE 21434
  - machine learning을 쓰는 기능의 안전: ISO/PAS 8800, ISO/IEC TR 5469
  - 자율 시스템: UL 4600, ISO/TS 5083
  - 멈출 수 없는 시스템: fail-operational 요구

#### 24장. 실무에 적용하기

- 내용
  - 흔한 오해와 잘못된 관행
  - 기존 프로젝트에 safety를 도입하는 순서
  - 소프트웨어 엔지니어의 역할
  - 더 읽을 자료

### 부록

- A. 용어집 (영어 - 한국어). 한국어 용어는 KS 번역본의 용어를 확인해 맞춘다.
- B. 규격 조항 대응표 (책의 장 <-> ISO 26262, IEC 61508 조항)
- C. 관통 예제의 산출물 전체
- D. 참고 문헌과 무료 자료

## 5. 집필하며 공부하는 방법

### 장마다 도는 순서

1. 먼저 쓰기: 핵심 질문에 지금 아는 만큼 답을 쓴다. 모르는 부분이 드러난다.
2. 읽기: 해당 규격 조항과 아래 자료를 읽는다.
3. 적용: 관통 예제의 산출물을 직접 만든다. 이해했는지는 여기서 판가름 난다.
4. 초고: 자기 말로 다시 쓴다. 규격 문장을 옮기지 않는다.
5. 검증: 규격 원문과 대조하고, 풀리지 않은 것은 미해결 질문 목록에 남긴다.

### 쓰는 순서 (읽는 순서와 다르다)

- 1차, 뼈대: 2, 3, 6, 7, 10, 11, 12, 16, 19장을 장마다 2-3쪽으로 쓴다.
  관통 예제를 hazard에서 safety case까지 얇게 한 번 끝까지 가 보는 것이 목표다.
  전체 흐름을 먼저 겪어야 각 장의 깊이를 정할 수 있다.
- 2차, 살 붙이기: 1, 4, 5, 8, 9, 13, 14, 15, 17, 18장을 쓰고 1차 장들을 깊게 고친다.
- 3차, 넓히기: 20-24장과 부록. 로봇과 드론 장을 쓴 뒤에 앞 장들의 "로봇과 드론에서는" 항목을 채운다.
  용어를 통일하고 조항 대응표를 완성한다.

### 원칙

- 규격은 저작권이 있는 유료 문서다. 문장과 표를 옮기지 않고, 조항 번호를 밝혀 자기 말로 설명한다.
- 사실 주장에는 근거 (규격 조항, 보고서, 논문)를 단다.
- "왜 이 요구가 있는가"를 장마다 한 번은 사고 사례나 failure mode로 설명한다.

## 6. 자료

### 규격 (유료, 장별로 필요한 Part만 구한다)

- IEC 61508 Part 1-7. 소프트웨어는 Part 3, 기법 설명은 Part 7
- ISO 26262 Part 1-12. 소프트웨어는 Part 6, 지원 프로세스는 Part 8, 분석은 Part 9, 해설은 Part 10
- ISO Online Browsing Platform에서 용어 정의 부분은 무료로 볼 수 있다

### 무료로 읽을 수 있는 자료

- Leveson, Engineering a Safer World (MIT Press, open access)
- Leveson, Thomas, STPA Handbook (2018)
- Leveson, Turner, An Investigation of the Therac-25 Accidents (1993)
- Ariane 501 Inquiry Board Report (1996)
- Boeing 737 MAX 관련 공식 조사 보고서
- Koopman, A Case Study of Toyota Unintended Acceleration and Software Safety
- EGAS Workgroup, Standardized E-Gas Monitoring Concept
- Avizienis, Laprie, Randell, Landwehr, Basic Concepts and Taxonomy of Dependable and Secure Computing (2004)
- NASA Software Safety Guidebook (NASA-GB-8719.13)
- Hayhurst 외, A Practical Tutorial on Modified Condition/Decision Coverage (NASA/TM-2001-210876)
- MIL-STD-882E
- GSN Community Standard
- AUTOSAR 공개 문서: E2E protocol 규격, functional safety measures 개요
- ELISA project 문서

### 로봇과 드론 자료

- 로봇 규격 (유료): ISO 12100, ISO 13849-1, ISO 13849-2, IEC 62061, ISO 10218-1, ISO 10218-2, ISO 13482, ISO 3691-4
- 로봇 (무료): DGUV IFA, Functional safety of machine controls - Application of EN ISO 13849
- 드론 (무료): JARUS SORA 2.5, EASA Easy Access Rules for Unmanned Aircraft Systems, EASA Special Condition Light-UAS와 그 means of compliance
- 드론 (유료): ASTM F3201, ASTM F3269, EUROCAE ED-280, RTCA DO-178C
- 공개 autopilot의 failsafe 문서와 코드: PX4, ArduPilot

### 책

- Hobbs, Embedded Software Development for Safety-Critical Systems
- Smith, Simpson, The Safety Critical Systems Handbook
- Rierson, Developing Safety-Critical Software (항공, DO-178C)
- Koopman, Better Embedded System Software
- Koopman, How Safe Is Safe Enough?

## 7. 정해야 할 것

정한 것 (2026-11-21): 주 분야는 자동차 (ISO 26262), 보조 분야는 로봇과 드론.

1. 관통 예제: 구동 토크 제어로 가정했다.
2. 로봇의 중심: 자율 이동 로봇 (ISO 3691-4)으로 가정했다. 산업용 로봇 팔 (ISO 10218)이나 서비스 로봇 (ISO 13482)으로 바꿀 수 있다.
3. 드론의 중심: 소형 드론의 Specific category 운용 (EU 체계, SORA)으로 가정했다. 한국과 미국 제도를 얼마나 다룰지는 정하지 않았다.
4. 규격 원문 접근: ISO 26262와 IEC 61508 원문을 볼 수 있는지에 따라 조항 대응표의 깊이가 달라진다.
5. 독자의 임베디드 경험: 없다고 가정했다. 있다고 보면 9장과 14장을 줄일 수 있다.
