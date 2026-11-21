# 임베디드 소프트웨어 엔지니어 검토 (1차, 독립 검토)

검토자: 임베디드 소프트웨어 엔지니어 역할 에이전트 (sonnet), 2026-11-22

임베디드 엔지니어 검토 (독자와 실무 관점)

검토 범위: README, OUTLINE, PLAN, RULES, ch01-24 장 계획, 부록 4개(내용 없음), references/standards.md, figures/book-map.svg를 모두 읽었다. 파일은 고치지 않았다.
표시: "확인"은 웹에서 확인했다는 뜻이다. "경험에 의존, 미확인"은 웹에서 확인하지 못했다는 뜻이다. "FuSa 확인 필요"는 규격 해석이라 내 영역이 아닌 것이다.

## 1. 총평

- 계획의 뼈대는 탄탄하다. V-model 위에 장을 놓고, 관통 예제에 장마다 산출물을 쌓고, 확인하지 못한 것을 표시하는 규칙이 있다. 한계도 스스로 적어 두었다.
- 가장 큰 문제는 독자 가정이다. 책은 "임베디드 경험 없음"을 가정하는데, 임베디드 기초를 가르치는 장이 없다. interrupt, memory map, ADC, CAN, watchdog, MPU, 주기 task는 6-7장(시간 예산)과 12장(watchdog, MPU, stack, E2E)에서 처음 필요하다. 그런데 9장은 하드웨어 고장 지표(SPFM, LFM, PMHF)를 읽는 장이어서 MCU 기초를 채워 주지 않는다. 9장은 단계 2에 쓰는데, 12장은 단계 1에 쓴다.
- 실무자가 보면 순진한 곳이 있다. 핵심 안전 장치가 모두 사실은 하드웨어와 타이밍에 달려 있는데(독립 watchdog, 메모리 보호, 실행 시간, reset과 boot 후 상태), 계획에서는 그것을 PC 시뮬레이션에서 "흉내"만 낸다고 한다. 흉내로 보일 수 있는 것과 없는 것의 경계를 책이 독자에게 정직하게 보여 줘야 한다.
- 계획에 빠진 실무 주제가 많다. startup과 reset, NVM, interrupt와 공유 data, 실행 시간 측정, build 설정(최적화, linker, debug 대 양산), 진단(DTC), AUTOSAR Classic의 실제다. 반대로 22장(다른 분야), 23장(SOTIF, AI), 13장의 Ada/Rust, 14장의 Linux/hypervisor, 21장의 US/KR 제도는 이 독자에게 과하다.
- 일정은 낙관적이다. 단계 1은 "장마다 1주(6-8시간)"인데, 그 안에 자료 읽기, 2-3쪽 집필, 예제 산출물, 코드, test가 모두 들어 있다. PC 시뮬레이션 기반 구조 자체를 만드는 시간은 어느 단계에도 없다.
- 그림은 대체로 읽힌다. 다만 PLAN 9절의 sequence diagram에 `end`가 없어 렌더링 오류일 가능성이 높고, 의존 관계 그림은 단계 순서와 모순된다.
- 한 줄 요약: 방향은 맞다. "임베디드 기초"를 어디에 넣을지와 "시뮬레이션이 보여 주는 것의 한계"를 명시하면 훨씬 좋아진다.

## 2. 지적 목록

### E-01 (치명) 임베디드 기초를 가르치는 곳이 없다
- 위치: OUTLINE 1절 (독자), ch09, ch12, ch14, 목차 전체
- 지적: 독자는 "임베디드 경험 없음"인데 목차에 임베디드 입문이 없다. 처음 필요해지는 지점은 다음과 같다.
  - ch06-07: FTTI와 "fault detection/reaction 시간 예산"에서 주기 task, 응답 시간
  - ch07: hardware-software interface
  - ch09: MCU 구조, ADC, lockstep, ECC
  - ch12: watchdog window, MPU, stack 감시, E2E(CAN), 센서 plausibility
  - ch13: interrupt, volatile
  - ch14: scheduling, WCET
  - ch16: target, HIL
- 근거: 경험에 의존, 미확인
- 수정안: 아래 중 하나를 택한다. 1순위는 (a)다.
  - (a) Part II 앞(5장과 6장 사이)이나 Part I 끝에 새 장 "임베디드 시스템 최소 지식"(12-15쪽)을 둔다.
    - 내용: MCU 한 장 그림(CPU, flash, RAM, peripheral, clock, reset), memory map, 시작 순서, 주기 task와 interrupt, 센서 신호가 ADC 값이 되는 경로, PWM 출력, CAN frame과 CAN의 약점, hardware watchdog과 MPU의 역할, HAL이 무엇인가.
    - 규칙: 이 장은 규격과 무관하므로 `(확인 필요)` 부담이 없다.
  - (b) 부록 E("임베디드 용어와 구조 요약")로 두고, 장 안에서는 필요한 곳마다 2-3문단 설명과 부록 링크를 단다. 부록만으로는 독자가 건너뛰므로, 장 안에 최소 설명을 반드시 둔다.
  - 어느 쪽이든 관통 예제의 sim 구조와 같은 그림을 쓴다 (3절 참고).

### E-02 (치명) 단계 순서와 의존 관계가 모순된다
- 위치: PLAN 5절 (단계 1, 2), 7절 (의존 그림)
- 지적:
  - 의존 그림은 C9->C12, C15->C16, C11->C14를 "앞 장이 있어야 뒤 장을 쓴다"로 그린다. 그런데 단계 1은 12장과 16장을 쓰고, 9, 14, 15장은 단계 2에서 쓴다.
  - 12장의 watchdog, memory protection, stack 감시는 9장(MCU, 하드웨어 safety mechanism)과 14장(scheduling, timing)의 내용에 기댄다. 16장의 coverage와 정적 분석은 15장에 기댄다.
  - 단계 1의 "9개 장 1주씩"은 서로 필요한 개념을 미루는 구조다.
- 근거: PLAN 문서 자체의 모순
- 수정안:
  - 단계 1에서는 12장을 "watchdog 1개(논리적 시간 기반) + plausibility check + 센서 중복 비교"로 줄이고, 필요한 MCU 지식은 E-01의 입문 장 뼈대(3-4쪽)로 함께 쓴다.
  - 또는 단계 1에 9장(MCU 기초 부분만)을 끼운다.
  - 의존 그림을 고친다: C14->C12 (timing), C9->C7 (인터페이스)를 추가하고, 단계 1에서 미루는 것은 점선으로 표시한다.

### E-03 (중요) 9장이 MCU 기초와 정량 지표를 한 장에 섞는다
- 위치: ch09
- 지적:
  - 장의 핵심 질문은 "하드웨어는 어떻게 고장 나고 무엇이 소프트웨어의 일이 되는가"인데, 다룰 내용 1-3번째는 확률과 지표(failure rate, SPFM, LFM, PMHF, PFH, SFF)다.
  - 이 독자에게는 계산법이 아니라 "MCU safety manual을 열면 무엇을 찾는가"가 중요하다. 소프트웨어 엔지니어가 지표를 직접 계산할 일은 거의 없다.
  - 하드웨어 safety mechanism(lockstep, ECC)과 소프트웨어 진단(startup test, 주기 self-test)이 같은 장에 있어 난이도가 한꺼번에 오른다.
- 근거: 경험에 의존, 미확인
- 수정안: 9장을 둘로 나눈다.
  - 9A: "하드웨어 고장과 소프트웨어의 몫"
    - 고장 종류(permanent, transient, latent)
    - 하드웨어가 이미 잡아 주는 것 vs 소프트웨어가 해야 하는 것
    - safety manual에서 찾는 항목(FIT 표, 진단 coverage, assumption of use)
    - 소프트웨어가 하는 startup test와 주기 test: RAM, flash CRC, ADC reference, clock 감시, watchdog 점검
  - 9B: SPFM, LFM, PMHF는 "읽는 법" 정도로 1쪽으로 축소하거나 부록으로 보낸다.
  - 지표 정의와 목표값의 정확성은 FuSa 확인 필요.

### E-04 (중요) 코드와 예제가 너무 늦게 나온다
- 위치: OUTLINE 4절, PLAN 8절의 산출물 표
- 지적:
  - 소프트웨어 엔지니어 독자가 처음 코드를 보는 곳은 10장이다. 1-9장은 사례, 용어, 등급, 규격 지도, lifecycle, HARA, 요구사항 분해, FTA/FMEA, 하드웨어이므로 약 100쪽 이상 코드가 없다.
  - 1장의 산출물이 "관통 예제 소개"뿐이다. 독자는 왜 이 모든 절차가 필요한지 직접 겪지 못한 채 규격 이야기를 듣는다.
- 근거: 경험에 의존, 미확인
- 수정안:
  - 1장 끝에서 "안전 장치가 없는 단순 토크 제어기" 약 100줄을 실행한다. 페달 센서 한 개가 한 값에 고착되면 차가 계속 가속하는 그래프를 보여 준다. 이 한 장면이 2-9장의 동기가 된다.
  - 6, 7장에서는 같은 코드에서 어느 변수가 safety goal에 관련되는지 표시한다.
  - 4장(규격 지도)은 건조하다. 1장 직후가 아니라 5장과 합치거나, 짧게 쓰고 부록 B로 보내는 것을 검토한다.

### E-05 (보통) 약어 충돌: SIL
- 위치: ch03, ch16, 부록 A
- 지적:
  - SIL은 "Safety Integrity Level"이다. 16장의 test 환경(MIL/SIL/PIL/HIL)에서는 "Software-in-the-Loop"다. HIL도 이 독자에게 처음이다.
  - 3장에서 SIL이 등급으로 나오고 16장에서 다른 뜻으로 나오면 독자가 혼란스러워한다.
- 근거: 경험에 의존, 미확인
- 수정안:
  - 용어집에 SIL을 두 개로 올리고, 3장에서 "이 책에서 test 환경을 말할 때는 SIL이라 쓰지 않고 'host 시뮬레이션'으로 쓴다"처럼 규칙을 정한다.
  - 16장에 MIL/SIL/PIL/HIL을 한 장짜리 표로 둔다. 관통 예제는 어디에 해당하는지도 표시한다.

### E-06 (중요) startup, reset, boot, bootloader, NVM이 빠져 있다
- 위치: ch09, ch12, ch18
- 지적:
  - 실무에서 사고와 결함이 가장 많은 곳 중 하나가 startup과 reset 이후의 상태다. 다음 질문이 책에 없다.
    - 전원이 들어오면 출력이 어떤 상태인가 (torque 출력 기본값, enable 신호).
    - startup self-test는 언제, 얼마나 오래 도는가.
    - reset 원인(watchdog, brown-out, software)을 기록하는가.
    - reset이 반복(boot loop)될 때 어떻게 하는가.
    - 시작 순서 중 "아직 검증되지 않은 센서 값"을 쓰지 않는가.
  - bootloader와 flashing: ch18은 OTA만 언급한다. 잘못된 image가 올라가는 것 방지(CRC, 서명, 버전), 갱신 중 전원 상실이 안전 문제다.
  - NVM(flash/EEPROM)의 data 무결성: 쓰는 도중 전원 상실, wear, 이중 저장, CRC와 counter. 12장의 "중요 데이터의 중복 저장" 한 줄이 전부다.
- 근거: 경험에 의존, 미확인
- 수정안:
  - ch12에 "startup과 reset 동작" 절을 둔다. 내용은 safe state 기본값, self-test 순서, reset 원인 처리, boot loop 방지다. 관통 예제에서도 구현한다.
  - ch12의 NVM 항목을 한 절로 확장한다. 이중 저장, CRC+version, 쓰는 도중 전원 상실을 다룬다.
  - ch18에 bootloader와 갱신 절을 둔다. 갱신 중 전원 상실, 호환 검사, rollback을 다룬다.
  - 구현 상세는 다루지 않고 "무엇을 질문해야 하는가" 수준으로 한다.

### E-07 (중요) interrupt와 공유 data, 동시성이 "제한" 한 줄로만 나온다
- 위치: ch13 ("interrupt, 동시성에 대한 제한"), ch14
- 지적:
  - 소프트웨어 엔지니어에게 동시성은 thread와 lock이다. 임베디드의 핵심 실수는 ISR과 main loop가 공유하는 변수(`volatile`로 충분하다는 오해), 다중 byte 변수의 비원자 갱신(32-bit MCU의 64-bit 값, 8/16-bit MCU의 32-bit 값), 우선순위 역전, ISR 안에서의 긴 처리다.
  - 이것이 safety에서 중요한 이유는 간헐적이고 재현이 어려워 test로 거의 못 잡기 때문이다.
  - "제한"만 쓰면 독자는 이유를 모르고 규칙만 외운다.
- 근거: 경험에 의존, 미확인
- 수정안: ch13에 "interrupt와 공유 data" 절을 둔다. 반드시 깨지는 짧은 예 하나(16-bit 값을 읽는 도중 ISR이 갱신)를 보이고, 대책(critical section, 이중 buffer, 단일 writer 원칙)을 설명한다. 관통 예제에서 이를 sim으로 완전히 재현하기는 어렵다 (E-15).

### E-08 (중요) stack과 실행 시간 측정을 다루는 방식이 비현실적이다
- 위치: ch14 ("worst-case execution time과 stack 사용량 분석"), ch12 ("stack 감시")
- 지적:
  - 정적 WCET 분석 도구(예: aiT)는 상용이고 cache, pipeline 모델이 필요하다. 실무 대부분은 측정 기반이다(타이머나 trace, GPIO 토글로 측정하고 여유를 둔다). stack은 painting(초기 패턴 채우고 high water mark 확인)과 MPU guard로 한다.
  - 계획은 분석 중심으로 쓰여 있고 이 현실이 빠져 있다. 정적 WCET 분석 도구의 상용 여부는 경험에 의존, 미확인.
  - PC sim은 실제 실행 시간을 줄 수 없다. 관통 예제의 "timing 예산"은 논리적 시간으로만 가능하다.
- 근거: 경험에 의존, 미확인
- 수정안:
  - 14장을 "측정 기반 + 여유 + 감시" 중심으로 쓴다. 측정, 최악 조건 유도, 여유, 런타임 감시(deadline 감시, stack high water mark)를 정리한다.
  - 정적 WCET 분석은 "있고 이런 때 쓴다" 수준으로 1문단.
  - 관통 예제에서는 task에 "실행 시간을 시뮬레이션 인자로 주입"하는 방식으로 deadline 감시 로직만 검증한다. 실제 시간은 보드나 emulator 선택 단계(E-20)에서 보인다.

### E-09 (중요) build 설정, compiler 최적화, linker script와 map file, debug 대 양산 build가 없다
- 위치: ch13, ch14, ch16, ch17
- 지적:
  - "test한 binary와 출하한 binary가 같은가"는 실무의 큰 질문이다. 다음이 책에 없다.
    - 최적화 수준에 따라 달라지는 동작(UB, volatile, 부동소수점 순서).
    - debug build와 양산 build의 차이(assert, 로그, 최적화).
    - linker script와 map file(RAM/ROM 배치, section, stack/heap 크기, MPU region 정렬).
    - 같은 source에서 같은 binary를 다시 만드는 재현 가능한 build.
  - 17장은 tool qualification만 말하고, compiler가 최적화로 감시 코드를 지우는 문제(예: 방어 코드가 "죽은 코드"로 제거)를 다루지 않는다.
- 근거: 경험에 의존, 미확인
- 수정안:
  - ch13에 "build 설정이 안전에 미치는 영향" 절을 둔다. warning 수준, 최적화 수준, volatile, 정수 크기를 다룬다.
  - ch14에 map file 읽는 법을 둔다. 메모리 배치, stack, partition 경계를 다룬다.
  - ch16에 "test한 build가 양산 build인가"를 체크 항목으로 넣는다.
  - ch17에 "compiler가 안전 코드를 바꿀 수 있다"는 사례 1개를 넣는다.

### E-10 (보통) 진단(DTC, UDS)과 calibration
- 위치: ch07 (warning, degradation), ch12 (fault reaction), ch18 (calibration)
- 지적:
  - 자동차 ECU에서 fault reaction은 hazard 대응(torque 제한)과 진단(DTC 저장, warning lamp)이 한 쌍이다. DTC debounce, fault memory, 서비스 단계의 읽기가 자동차 독자에게 필수 개념이다.
  - 하지만 UDS 프로토콜 전체는 이 책의 범위 밖이다.
  - calibration data는 ch18에 있어 좋다. 안전 관련 parameter의 범위 검사, CRC, 버전, 변조 방지로 잘 연결될 수 있다.
- 근거: 경험에 의존, 미확인. UDS는 ISO 14229 계열이라는 기억에 의존.
- 수정안:
  - ch12의 error handling 전략에 "fault 기록(DTC), debounce, 복구(healing) 조건"을 1절로 추가한다. UDS는 "있다"고 한 문단만 쓴다.
  - ch18의 calibration에 "calibration 값이 safety 요구사항(예: 최대 torque)을 깨뜨릴 수 있다"를 명시한다. 관통 예제의 torque 제한을 parameter로 두고 범위 검사 요구사항을 만든다.

### E-11 (중요) AUTOSAR의 실제와 14장의 비중
- 위치: ch14
- 지적:
  - 자동차 ECU 소프트웨어의 현실은 대부분 AUTOSAR Classic이다. 구성은 MCAL, BSW, RTE, OS(OSEK 계열)이고, safety 관련 모듈은 watchdog manager, E2E library, OS의 memory protection과 timing protection이다.
  - 독자가 "내 코드 아래"를 이해하려면 이 모듈들과 12장 mechanism의 대응표가 필요하다.
  - 계획은 Classic과 Adaptive를 같은 비중으로 쓰는데, Adaptive(POSIX 기반, 고성능 컴퓨팅)는 구동 토크 제어 같은 저수준 ECU 예제와 거리가 있다.
- 근거: 경험에 의존, 미확인
- 수정안:
  - ch14의 AUTOSAR는 Classic 중심으로 1절을 쓴다. 층 구조 그림 하나와 "12장 mechanism -> AUTOSAR 모듈" 대응표를 둔다.
  - Adaptive는 한 문단.
  - AUTOSAR 공개 문서가 접근 등급 A인지 B인지 references에서 확인한다.

### E-12 (보통) 하드웨어 추상화 계층(HAL)
- 위치: ch11, 예제 구조
- 지적:
  - HAL은 sim 설계의 핵심이기도 하다. 같은 응용 코드가 PC와 target에서 돌려면 입출력(ADC, PWM, CAN, timer, NVM)이 HAL 경계 뒤에 있어야 한다.
  - 이 경계가 곧 fault injection 지점이고 partitioning 경계다.
  - 지금 ch11은 partitioning과 freedom from interference만 말하고, 독자가 쓸 수 있는 구체적 소프트웨어 구조(layer와 HAL)는 빠져 있다.
- 근거: 경험에 의존, 미확인
- 수정안: ch11에 "응용, 감시, HAL의 3층 구조"를 정적 view의 기본 예로 보인다. 관통 예제의 폴더 구조와 일치시킨다 (3절).

### E-13 (중요) host에서의 coverage와 target의 차이, 임베디드 CI
- 위치: ch16
- 지적:
  - 16장은 "test 환경(host, target, HIL)과 그 차이"를 한 줄로 쓴다. 독자가 알아야 할 것은 다음과 같다.
    - host에서 측정한 coverage는 host compiler의 object code에 대한 것이다.
    - 정수 크기, endianness, 부동소수점, 정렬, 최적화가 다르다.
    - target에서 측정하려면 instrumentation 비용(memory, 시간)이나 trace가 필요하다.
    - 상용 tool(VectorCAST 등)은 이를 지원한다.
  - ISO 26262-6이 host 결과를 target으로 옮길 때 무엇을 요구하는지는 FuSa 확인 필요.
- 근거: 경험에 의존, 미확인
- 수정안:
  - ch16에 "host 결과가 target에 대해 말해 주는 것과 못 말해 주는 것" 표를 둔다.
  - 관통 예제 sim에서 `-m32`나 `stdint` 고정 폭 타입, UBSan으로 정수 차이의 일부를 줄이는 방법을 보인다.
  - 임베디드 CI는 18장에 "CI에서 host test, 정적 분석, coverage를 자동으로" 절로 둔다. target test는 nightly라고 쓴다.

### E-14 (제안) 과하게 다루는 곳
- 위치: ch01, ch08, ch13, ch14, ch22, ch23, ch21
- 지적:
  - ch01: 사례 4건(Therac-25, Ariane 5, Toyota, MCAS)을 모두 깊게 쓰면 ch01이 가장 길어진다. 독자 동기에는 2건이면 충분하다. Toyota는 관통 예제와 직결되므로 유지하고, 나머지는 표 한 줄씩.
  - ch08: FMEA, FTA, HAZOP, STPA, DFA를 각각 예제까지 만든다. 단계 2 부담이 크다. FTA와 FMEA는 충분히, STPA는 한 쪽, HAZOP은 언급 정도로 낮춘다.
  - ch13: Ada/SPARK와 Rust는 "위치" 한 문단이면 충분하다.
  - ch14: Linux/ELISA, hypervisor, multicore를 모두 쓰면 분량이 커진다. 관통 예제와 무관하다.
  - ch22(항공, 철도, 의료, 공정), ch23(SOTIF, security, AI, 자율): 각각 6-8쪽의 개관으로 충분하다. 12-20쪽 목표는 과하다.
  - ch21: 미국과 한국 제도 개요는 OUTLINE에서도 미정이다. 한 장 안에 SORA + PX4 + RTA + 제도 비교는 넘친다 (E-23).
- 근거: 경험에 의존, 미확인
- 수정안: 위 장은 분량 목표를 낮추고, 줄인 만큼 E-01, E-06-E-12의 실무 주제를 넣는다.

### E-15 (중요) PC 시뮬레이션이 보여 주는 것과 잃는 것을 독자에게 정직하게 보여 줘야 한다
- 위치: PLAN 8절 "알고 있는 한계", ch12, ch14, ch16
- 지적:
  - 계획은 한계를 "memory protection, hardware watchdog, 실제 timing"이라고 적는다. 맞지만 부족하다.
  - 잃는 것: ISR 선점과 race, 실제 실행 시간과 jitter, stack overflow, MPU fault, hardware watchdog의 reset 동작, startup과 reset 이후의 상태, ADC 양자화와 잡음과 오프셋, CAN의 오류 frame과 bus-off, flash/NVM의 쓰기 중 전원 상실, 비트 반전, compiler와 정수 크기 차이.
  - 위험: sim에서 fault injection test가 모두 통과하면 독자가 "검증됐다"로 오해한다.
- 근거: 경험에 의존, 미확인
- 수정안:
  - 12장과 16장에 "sim으로 보이는 것 / 못 보이는 것 / 어디서 보이는가" 표를 둔다.
  - 각 mechanism에 "PC에서 검증한 것은 논리이고 하드웨어 동작은 아니다"라는 표지를 단다.
  - 최소한 stack overflow, MPU fault, hardware watchdog, startup은 E-20의 emulator/보드 선택 단계에서 보이도록 약속한다.

### E-16 (중요) E-Gas 3단계 감시의 3단계는 sim에서 독립성을 보일 수 없다
- 위치: OUTLINE 3절 (고른 이유), ch11
- 지적:
  - E-Gas의 3단계(기능, 기능 감시, controller 감시)에서 가장 중요한 점은 3단계가 독립 하드웨어(별도 monitoring module, 두 번째 core, question-answer watchdog)라는 것이다. 한 process 안의 한 thread로는 독립성을 보일 수 없다.
  - E-Gas 구조의 세부는 2차 자료로만 알고 있다. FuSa 확인 필요.
- 근거: 경험에 의존, 미확인
- 수정안:
  - sim에서는 1단계(기능)와 2단계(torque 감시)를 구현한다. 2단계는 1단계와 다른 알고리즘과 다른 입력 경로로 짠다.
  - 3단계는 "question-answer watchdog 프로토콜을 흉내 내는 상태 기계"로 구현하되, 책에 "여기서 독립성은 시뮬레이션되지 않는다"를 명시한다.
  - ASIL decomposition의 독립성 논의(ch07)와 연결해 이 한계를 교재로 쓴다.

### E-17 (중요) MC/DC와 coverage tool의 사실, 환경 문제
- 위치: PLAN 8절 "test와 coverage", ch16
- 지적(확인된 사실):
  - GCC 14는 `-fcondition-coverage`로 MC/DC 측정을 지원한다. 사용법은 `gcc --coverage -fcondition-coverage`로 build하고 `gcov --conditions`로 본다. 구현은 masking MC/DC이다. GCC bug 115047는 GCC와 LLVM의 MC/DC 결과가 다르고 unique-cause MC/DC와도 다름을 보고한다.
    - 출처: https://arxiv.org/abs/2501.02133v1 , https://maskray.me/blog/2024-01-28-mc-dc-and-compiler-implementations , https://inbox.sourceware.org/gcc-bugs/bug-115047-4@http.gcc.gnu.org%2Fbugzilla%2F/T
    - GCC 14 changes 페이지(https://gcc.gnu.org/gcc-14/changes.html)에는 이 기능 언급이 없었다. 공식 문서(invoke.texi, gcov.texi)로 직접 확인하지는 못했다.
  - Clang/LLVM은 `-fcoverage-mcdc`를 `-fprofile-instr-generate -fcoverage-mapping`과 함께 쓰고 `llvm-cov show --show-mcdc`로 본다. 18.1.0에서 지원이 시작되었다 (Linux kernel patch 논의 인용, 2차 자료).
    - 조건 수 제한: `--show-mcdc` 부분 view는 식당 6개 조건까지다. 그 후 한도 설정 옵션이 생겼다 (PR #95887, LLVM 19로 추정, 내 추정).
    - 출처: https://clang.llvm.org/docs/SourceBasedCodeCoverage.html , https://prereleases.llvm.org/18.1.0/rc3/tools/clang/docs/SourceBasedCodeCoverage.html , https://lists.llvm.org/pipermail/cfe-commits/Week-of-Mon-20240617/589598.html
  - 이 coverage 도구는 모두 qualification되지 않은 무료 도구다.
- 경험에 의존, 미확인:
  - 저자의 환경은 macOS(Darwin)다. macOS의 `gcc` 명령은 보통 Apple clang이다. GCC 14와 LLVM 18 이상은 Homebrew나 Docker/Linux container로 맞춰야 한다. Apple clang의 `-fcoverage-mcdc` 지원 여부는 확인하지 못했다.
- 수정안:
  - 단계 0에서 "GCC 14 container에서 `gcov --conditions`가 우리 모니터 함수에 대해 동작하는지" 하루짜리 spike를 한다.
  - 기본 도구는 GCC >= 14, 교차 확인은 Clang >= 18 (또는 19)로 하고, 책에서는 두 도구의 MC/DC 정의가 다르다는 점(masking 대 unique-cause)을 알린다. 어느 variant가 규격에 맞는지는 FuSa 확인 필요.
  - 최적화가 켜진 build의 coverage는 의미가 흐려진다는 점도 쓴다: 측정은 `-O0`에서.
  - 17장의 tool 분류표에 "coverage tool, 정적 분석기, 무료 도구는 qualification하지 않았다"는 예를 넣는다.
  - docker, devcontainer를 단계 0의 산출물로 둔다.

### E-18 (중요) MISRA 검사의 현실
- 위치: ch13, PLAN 8절
- 지적:
  - 무료로 MISRA C 준수를 "검사했다"고 말하기는 어렵다.
  - Cppcheck의 `misra.py` add-on은 오픈소스지만 규칙 문구는 배포할 수 없어 사용자가 규칙 텍스트 파일을 따로 제공해야 한다. README는 MISRA C 2012 검증용이라고 쓴다. MISRA C:2025 지원은 확인하지 못했다.
    - 출처: https://sources.debian.org/src/cppcheck/2.18.0-2/addons/README.md , https://sources.debian.org/data/main/c/cppcheck/2.3-1/addons/misra.py
  - 상용 도구의 MISRA C:2025 지원 규칙 수는 90% 안팎으로 보고된다 (예: https://www.blackduck.com/?p=5288 ). 무료 도구는 이보다 낮다고 짐작하나 숫자는 확인하지 못했다.
  - MISRA 규칙 문서는 유료다 (https://misra.org.uk/ 에서 확인할 것).
- 수정안:
  - 13장에서 "MISRA 준수 주장"과 "일부 규칙 검사를 쓰는 것"을 구분한다.
  - 관통 예제는 `-Wall -Wextra -Wconversion -Werror`, cppcheck(+ misra add-on을 구입한 규칙 텍스트로), clang-tidy를 쓴다. 규칙 텍스트 파일은 RULES 7절에 따라 git에 넣지 않는다.
  - 예제에서 deviation 기록 1건을 실제로 만든다.
  - 무료 도구의 규칙 지원 범위는 쓰기 전에 직접 확인한다 (`(확인 필요)`).

### E-19 (보통) formal verification 도구 선택
- 위치: ch15, PLAN 8절
- 지적:
  - 독자에게 좋은 선택은 CBMC(bounded model checking)와 Frama-C(Eva는 abstract interpretation, WP는 contract 증명)다. 둘 다 무료이고 C를 직접 다룬다.
  - 감시 함수를 정수 연산으로 쓰면 증명이 쉬워진다. 부동소수점을 쓰면 어렵다.
  - macOS에서 Frama-C 설치는 번거롭다.
- 근거: 경험에 의존, 미확인
- 수정안:
  - 1순위 CBMC: torque 감시 함수에 비결정 입력 harness를 붙여 "출력이 한도를 넘지 않는다", "정수 overflow가 없다"를 증명한다.
  - 2순위 Frama-C Eva로 런타임 오류 부재를 확인한다.
  - 단계 0 spike에서 둘 중 하나가 동작함을 확인한 뒤에 15장 계획을 확정한다.
  - 감시 함수는 고정소수점 정수로 쓴다고 미리 결정한다 (3절).

### E-20 (제안) emulator나 보드로 옮겨야 하는가
- 위치: PLAN 8절 "알고 있는 한계", 12절 정할 것 10번
- 지적:
  - 기본은 PC sim으로 충분하다. 단, E-15에서 말한 항목(stack overflow, MPU fault, hardware watchdog, startup, 실제 실행 시간)은 PC에서 보일 수 없다.
  - emulator 선택지로 QEMU(Cortex-M 지원, 경험에 의존, 미확인)와 Renode가 있다. Renode는 MIT 라이선스이고 Cortex-M 지원과 Robot Framework 연동이 있다 (확인: https://github.com/renode/renode ). 둘 다 cycle 정확하지 않아 실행 시간 측정에는 부적합하다 (경험에 의존, 미확인).
  - 개발 보드(저가 Cortex-M 보드)는 실행 시간, stack 측정, 독립 watchdog, HardFault를 보여 줄 수 있다 (가격은 확인하지 못함).
- 수정안:
  - 기본값은 PC sim 유지.
  - 14장 쓸 때(단계 2) "선택 단계": 같은 응용 코드를 Cortex-M용으로 build해 Renode나 보드에서 4가지만 보인다 (HardFault 후 safe state, stack overflow 감지, 독립 watchdog reset, startup self-test).
  - 약 2주를 따로 예산에 넣는다. 못 하면 책에 "이 부분은 PC에서 보여 줄 수 없다"로 쓴다.

### E-21 (중요) 20장: 자율 이동 로봇의 protective stop에서 소프트웨어가 실제로 하는 일
- 위치: ch20, OUTLINE 3절 보조 예제
- 지적:
  - 실제 AMR/AGV에서 protective stop은 일반 소프트웨어(ROS 2 등)의 기능이 아니다. 안전 기능은 인증된 safety laser scanner(보호 영역 설정, OSSD 출력)가 safety controller(safety PLC나 safety 등급 controller)나 구동기의 STO(safe torque off)에 직접 연결되어 수행한다.
  - 일반 소프트웨어(navigation)는 "안전하지 않은 쪽"으로 취급한다. 소프트웨어 엔지니어가 하는 일:
    - 속도에 따른 scanner field 전환 요청의 논리와 stop distance 계산 근거,
    - 재시작 interlock(자동 재시작 조건),
    - scanner 설정의 확인과 변경 관리,
    - safety controller와 일반 소프트웨어의 인터페이스(상태 읽기, 정지 요청),
    - 정지 거리(응답 시간 + 제동)가 감지 거리 안에 들어오는지 계산.
  - 이것은 경험에 의존, 미확인. ISO 3691-4의 구체 요구는 FuSa 확인 필요.
  - 계획의 "사람이 감지 영역에 들어오면 정지하는 기능"을 C 코드로 설계하면 오해를 준다: 이 기능의 안전 부분은 코드가 아니라 하드웨어와 구성이다.
- 수정안:
  - 보조 예제는 "안전 기능 정의, PL 결정, 구조(Category), stop distance 예산 계산, 일반 소프트웨어와 safety controller의 경계 그림"으로 쓴다. 소프트웨어 요구사항은 safety controller가 실행하는 소규모 응용 논리(field 전환, 재시작)로 한정한다.
  - 한 장의 가장 좋은 교재 가치는 "소프트웨어가 안전 기능에서 하지 않는 일"을 보이는 데 있다. 이를 관통 예제와의 비교표 맨 위에 둔다.
  - ROS 2는 "안전 장치가 아니다"를 명시한다.

### E-22 (보통) 20장의 분량
- 위치: ch20 다룰 내용
- 지적:
  - 8개 항목 중 speed and separation monitoring, power and force limiting, 산업용 로봇 팔(ISO 10218)은 AMR 예제와 거리가 있다. 한 장에 모두 쓰면 얕아진다.
  - ISO 10218 2025 판의 내용은 standards.md에서도 "기억"이거나 확인 불가가 섞여 있다.
- 수정안: AMR(ISO 3691-4)을 중심으로 하고 협동 로봇은 표 한 칸으로 줄인다. ISO 13849-1의 Category와 PL 설명은 "읽는 법"까지만.

### E-23 (중요) 21장: 드론 계획의 현실성
- 위치: ch21
- 지적(확인된 사실):
  - PX4 failsafe는 RC 상실, data link 상실, geofence, 배터리, 위치 상실, GNSS 점검, offboard 상실로 나뉘고, 동작은 None, Warning, Hold, Return, Land, Disarm, Flight termination이다. 여러 failsafe가 동시에 걸리면 가장 심각한 동작이 실행된다. 대부분은 먼저 Hold로 들어가 조종자가 개입할 시간을 준다. 위치 상실 시 multicopter는 Return/Land에서 Descend로 내려간다. geofence는 위반 "후"에 작동하므로 엄격한 금지 구역에는 Hold와 여유 거리를 쓰라고 한다.
    - 출처: https://docs.px4.io/main/en/config/safety.html
  - ArduPilot Copter failsafe 목록: Radio, Battery, GCS, EKF, Dead Reckoning, Vibration, Terrain Data Loss, Crash Check, Parachute, Independent Watchdog.
    - 출처: https://ardupilot.org/copter/docs/failsafe-landing-page.html
- 평가:
  - 계획이 말한 "failsafe 구현 읽기"는 현실적이고 가치가 있다. 특히 "safe state가 메뉴이고 심각도 중재로 고른다"는 점, "geofence는 위반 후 작동한다"는 점은 좋은 교재다.
  - 다만 소스 코드 읽기(C++, uORB, RTOS)는 이 독자에게 무겁다. 문서와 상태 기계 그림으로 읽게 한다.
  - 계획의 "geofence와 link 상실" 예제는 위치 추정(EKF, GNSS)에 의존한다. 가장 어려운 문제는 위치 상실 시 fallback 순서다. 이것을 예제에 포함해야 한다.
  - 독립 하드웨어(별도 failsafe co-processor, flight termination 장치)가 있다는 점은 경험에 의존, 미확인이지만 11장과 연결할 가치가 있다.
  - 한 장 분량에서: SORA 요약 + SAIL 결정 + 상태 기계 + RTA(ASTM F3269) + 소스 읽기 + US/KR 제도는 넘친다.
- 수정안:
  - 21장은 (1) 규제는 SAIL 결정 한 예제로만, (2) 상태 기계 설계(link 상실, geofence, 위치 상실 3개)를 PX4 failsafe 표와 대응해 비교, (3) RTA는 한 절로 한다.
  - US/KR 제도 개요는 본문에서 빼고 "쓰는 시점에 확인" 표로 부록 이동한다.
  - 드론의 safe state에 대해 OUTLINE 표의 "정지할 수 없음"이라는 문구는 multicopter 착륙을 생각하면 과장이다. "제자리 정지가 안전하지 않다"로 정확히 쓴다.

### E-24 (중요) 일정의 현실성
- 위치: PLAN 10절
- 지적:
  - 주 6-8시간이면 총 45주는 270-360시간이다. 장 24개 + 부록 + 예제 + 보조 예제 2개 + 350쪽이므로 쪽당 1시간 안팎이다. 장마다 자료 읽기, 학습(저자가 배우는 책이다), 집필, 예제, 그림, 검토 반영을 모두 포함한다.
  - 단계 1: 장마다 1주 = 6-8시간. 이 안에 규격을 읽고 이해하고, 2-3쪽을 쓰고, 예제 산출물(HARA, 요구사항, 코드, test, 안전 사례)을 만든다. Claude가 초고를 쓰더라도 저자의 이해와 검증 시간은 줄지 않는다.
  - 단계 2: 새 장 10개와 보강 9개를 20주(약 140시간)에 한다. 장당 7시간 정도로, 12-20쪽 목표와 맞지 않는다.
  - 각 단계 검토에 걸리는 시간(에이전트 검토, 사실 확인, 반영)이 일정에 없다.
- 근거: 경험에 의존, 미확인
- 수정안:
  - 단계 1은 장당 2주(총 18-20주)로 늘리거나 범위를 줄인다 (E-25).
  - 전체는 70-80주로 보고, 단계 1 후 실제 속도로 다시 계산한다는 규칙(이미 있음)을 유지하되, "속도 측정 지표"(장당 시간, 쪽당 시간)를 단계 1에서 기록한다.
  - 줄일 수 있는 것: 분량 목표 350쪽을 250쪽으로, 20-24장의 분량 축소 (E-14).

### E-25 (중요) 단계 1 범위와 예제 구현 노력
- 위치: PLAN 5절 (단계 1), 8절
- 지적:
  - 단계 1의 "예제" 요구는 vertical slice 전체다: hazard 하나에서 safety goal, 요구사항 5-10개, 감시 구현과 test, 1쪽 safety case. 코드 기반 구조(build, plant 모델, HAL, test harness, CI, 고장 주입)가 먼저 필요한데 어느 단계에도 없다.
  - 대략 sim 골격과 test 환경에 15-25시간, 감시 구현과 test에 10시간 정도로 짐작한다 (경험에 의존, 미확인). 9장짜리 단계 1과 합치면 한 단계에 수십 시간이 더 든다.
  - 모든 장을 한 번씩 얇게 쓰는 방식(얇게 끝까지)은 좋지만, 단계 1에서 9개 장 + vertical slice를 동시에 하면 피로가 쌓인다.
- 수정안:
  - "단계 0.5: 예제 골격" 신설: 2-3주. 내용은 devcontainer, build, plant, HAL, 고장 주입 API, unit test, CI, 단계 0의 tool spike(E-17, E-19) 결과 확정이다. 완료 기준은 "깨끗한 container에서 `make test`가 통과하고 coverage와 정적 분석 보고서가 생성된다"이다.
  - 단계 1의 장은 6, 7, 10, 11, 12, 16 (+ 2, 3, 19의 아주 짧은 뼈대)로 시작해도 vertical slice는 충분하다.

### E-26 (보통) 완료 기준과 폴더 구조
- 위치: PLAN 6절, README, RULES 7절
- 지적:
  - 1차 완료 기준에 "예제 코드가 build되고 test가 통과한다", "요구사항 ID에서 test까지의 traceability가 자동으로 확인된다"가 없다. 예제가 책의 핵심 산출물인데 코드 품질 기준이 없다.
  - README는 `reviews/`, `references/README.md`를 안내하는데 현재 없다 (`references/`에는 standards.md만 있다). `notes/`, `example/`도 아직 없다.
  - chapters/ 안에 "장 계획"과 "본문"이 한 파일에 있다. 본문이 커지면 계획 부분이 독자용 원고에 섞이므로, book build(예: mdBook, pandoc)에서 제외하는 방법이 필요하다.
  - Mermaid와 SVG가 "제대로 그려지는지"를 확인하는 방법이 정해져 있지 않다.
- 수정안:
  - 완료 기준에 추가: "example/에서 `make check`가 통과한다", "요구사항 ID가 YAML에 있고 test와 코드에서 ID를 찾아 누락을 보고하는 스크립트가 통과한다".
  - 폴더 제안:
    ```
    example/
      docs/      (item.md, hara.md, goals, requirements.yaml, ...)
      src/app, src/monitor, src/hal
      sim/       (plant, driver profile, fault injection)
      test/
      tools/     (trace check, report scripts)
      Makefile or CMakeLists.txt
    ```
  - README의 안내와 실제 폴더를 맞춘다.
  - 장 계획을 front matter나 별도 파일로 분리하는 것을 검토한다.
  - Mermaid는 mermaid-cli로 파싱하는 단계를 CI에 넣는다 (E-28의 오류를 잡았을 것이다).

### E-27 (보통) RULES.md를 지키기 쉬운가
- 위치: RULES 2, 3, 5절, PLAN 6절
- 지적:
  - 규칙은 대체로 명확하다. 그러나 사람이 매번 확인하기에는 항목이 많다: 12개 구성 요소, 1차 7개와 최종 5개 완료 기준, ASCII+한글만 사용, 근거 표시, 조항 형식.
  - 최종 완료 기준은 `(확인 필요)`가 0개여야 하는데, 규격 원문을 구하지 못하면 대부분 삭제하거나 `(2차 자료)`로 바꿔야 한다. 지키기 어렵다기보다 책 내용이 얇아질 수 있다는 위험이다 (FuSa 확인 필요).
  - 기계로 확인 가능한 것은 자동화해야 한다.
- 수정안:
  - `tools/lint`: 비ASCII 문자(한글 제외) 검사, `(확인 필요)` 개수 세기, 장 파일의 필수 제목 존재 확인, Mermaid 파싱, 링크 깨짐 확인. pre-commit hook이나 CI에 둔다.
  - 장 구성은 "필수 / 해당될 때만"으로 나눈다. 예를 들어 "로봇과 드론에서는"은 단계 3에서 채우는 것이 이미 규칙이다.

### E-28 (중요) Mermaid 다이어그램의 구문과 가독성
- 위치: PLAN 9절 sequence diagram, 7절 의존 그림, 5절 단계 그림
- 지적:
  - 9절 sequence diagram: `par 독립 검토 ... and ... ` 블록에 닫는 `end`가 없다. Mermaid에서 `par`는 `end`로 닫아야 하므로 렌더링 오류로 보인다. 렌더러로 실행해 보지는 못했다. 경험에 의존, 미확인.
  - 의존 그림(7절):
    - 22개 node와 교차 화살표로 읽기 어렵다.
    - "앞 장이 있어야 쓸 수 있다"와 "읽는 순서"가 섞여 있다 (C1->C2는 의존이 아니라 읽는 순서).
    - 단계 1/2 구분이 subgraph 하나뿐이어서 E-02의 모순이 눈에 안 띈다.
    - 누락: C14->C12, C9->C7 (E-02).
  - 단계 그림(5절)은 명확하다. 유지.
- 수정안:
  - `end`를 추가하고 mermaid-cli로 렌더링을 확인한다.
  - 의존 그림은 Part별 subgraph로 나누고, 단계 1에서 쓰는 장을 색으로 표시하고, 일정에 영향을 주는 의존만 남긴다.

### E-29 (보통) 책 지도 SVG (figures/book-map.svg)
- 위치: figures/book-map.svg, PLAN 4절
- 지적:
  - V 모양은 직관적이고 좋다. 점선으로 "오른쪽 활동이 왼쪽 산출물을 검증한다"는 짝을 보인다. 선과 상자가 겹치는 곳은 코드로 보아 없었다. 렌더링을 직접 보지는 못했다.
  - 문제:
    1. 색이 Part를 뜻한다. 독자는 색이 "단계"나 "난이도"를 뜻한다고 오해할 수 있다. 단계 1/2/3 구분이 없어 작성 순서 용도로도 못 쓴다.
    2. 14장(플랫폼)과 9장(하드웨어)을 "V 전체에 입력을 주는 장"에 둔 것은 어색하다. 플랫폼은 구조와 구현에 영향을 주는 입력이다. 이 독자에게는 "내 코드 아래 층"으로 별도 띠가 더 명확하다.
    3. 가장 위의 짝(6장 safety goal <-> 19장 safety case)은 의미상 정확한지 FuSa 확인 필요. safety case는 검증 활동이 아니라 논거 정리다.
    4. 1000x676에 글자 11-13px는 책 지면 크기에서 읽기 어렵다.
    5. 15장과 16장이 한 상자에 있다. 15장은 정적 분석과 formal이라 test와 다르다.
    6. "시스템 통합과 test (개요만 다룸)"은 좋은 정직함이다.
- 수정안: 범례에 "단계 1에서 쓰는 장" 표시를 추가하고, 임베디드 입문 장(E-01)과 "내 코드 아래 층" 띠를 넣는다. 글자 크기를 키우거나 가로 폭을 줄여 책 폭에 맞게 한다.

## 3. 관통 예제의 최소 설계안과 toolchain 제안

### 3.1 구조 (모두 C, 하나의 build)

1. 가상 시간과 주기 실행
   - 하나의 process, 단일 thread, "가상 시계"(1 ms tick)를 쓴다. 실제 sleep이나 thread 선점을 쓰지 않는다. 그래야 결과가 결정적이고 test가 재현된다.
   - 주기: 1 ms(입력, 출력), 5 ms(기능), 10 ms(감시)처럼 task를 정적 table에 등록해 tick마다 호출한다.
   - 실행 시간은 task별 "소비 시간"을 sim이 주입하는 변수로 둔다. deadline 감시 로직을 검증하는 용도다. 실제 시간은 보이지 않는다고 명시한다 (E-08).
2. HAL 경계 (E-12)
   - `hal_adc_read(ch)` (12-bit 원시 count), `hal_pwm_set()` 또는 torque 출력 + enable 신호, `hal_can_rx/tx`, `hal_time_us()`, `hal_nvm_read/write`, `hal_wdg_kick()`, `hal_reset_reason()`.
   - HAL 구현을 두 개 둔다: sim 용과 (선택 단계) target 용.
   - 모든 고장 주입은 HAL 뒤쪽에서 한다.
3. Plant model
   - 1차원 종방향 차량(질량, 구름 저항, 공기 저항, 경사)과 모터 torque의 1차 지연, 속도에 따른 최대 torque 곡선, torque 증가율 제한.
   - 운전자 모델은 페달 프로파일(CSV)과 "T초 뒤 제동" (controllability 논의, ch06). 값은 설명용 가정이다.
4. 이중 페달 센서
   - 센서 1과 2는 서로 다른 특성(예: 센서 2는 기울기가 절반이고 offset이 다름)과 별도 ADC 채널로 둔다. 같은 전원을 공유하는 공통 원인 고장을 한 케이스로 넣는다 (ch08의 dependent failure 예).
   - 원시 count -> 정규화 -> plausibility(두 센서의 관계가 허용 오차 안인가) -> 선택 규칙.
   - 정수(고정소수점) 연산을 쓴다: 양자화와 overflow가 보이고 formal 검증이 쉽다 (E-19).
5. 기능 계층(1단계)
   - 페달 -> 요구 torque (맵, rate limit) -> 속도와 한계에 따른 제한 -> torque 명령.
6. 감시 계층(2단계, E-Gas 풍)
   - 1단계와 다른 입력 경로와 다른 알고리즘. 요구: "명령 torque <= f(페달, 속도) + 허용 오차".
   - 모터 전류 feedback으로 추정한 실제 torque와의 비교.
   - 위반이 debounce 시간(예: 20 ms) 계속되면 safe state(torque 0, enable 해제)로 래치한다.
   - fault 기록(DTC 단순판)과 warning 출력 (E-10).
7. 3단계(controller 감시)
   - question-answer watchdog 상태 기계와 window watchdog을 가상 시간으로 구현한다. 독립성은 시뮬레이션되지 않음을 책에서 밝힌다 (E-16).
8. 고장 주입 지점 (PLAN 8절의 항목을 구체화)
   - 센서: 값 고착, 값 튐(spike), offset, 단선(범위 밖 count), 둘이 동시에 같은 방향으로 이동(공통 원인).
   - 통신(CAN): 메시지 소실, 오래된 값(counter 정지), 값 손상(CRC 불일치), 지연.
   - 실행: task 건너뜀(실행 지연), 무한 루프 흉내(tick 소비), 지연 초과.
   - 메모리: 선택한 RAM 변수의 비트 반전(test 훅으로).
   - NVM: 쓰기 중 중단, CRC 불일치.
   - 시작: reset 후 센서가 아직 안정되지 않은 구간.
9. 측정 지표
   - fault 주입 시각부터 torque가 안전 한도 이하가 된 시각까지를 측정해 FTTI(가정값, 예: 200 ms)와 비교하는 assertion을 둔다.
   - 가속 hazard의 척도: 위험 상황에서 최대 가속도와 도달 속도.
10. 로그와 그림
   - 시나리오마다 CSV 로그를 남기고, 스크립트로 그래프(페달, torque, 속도, fault 상태)를 만든다. 독자는 그래프로 고장의 영향을 본다.

### 3.2 sim으로 보일 수 있는 것과 없는 것
- 보임: 요구사항 기반 test, plausibility와 감시 논리, 상태 기계와 safe state 전이, fault 반응 시간(논리적), coverage (MC/DC 포함), 정적 분석, formal (E-19), back-to-back (참조 모델 대 구현).
- 못 보임: E-15의 목록 전체. 특히 독립성(E-16), 실제 실행 시간(E-08), 하드웨어 watchdog과 MPU의 동작.

### 3.3 Toolchain

| 용도 | 제안 | 비고 |
|---|---|---|
| 환경 | Docker 또는 devcontainer (Linux, GCC 14, LLVM 18+) | macOS 기본 `gcc`는 Apple clang이므로 필요 (E-17). 경험에 의존, 미확인 |
| compiler | GCC >= 14 (주), Clang >= 18 (교차 확인) | MC/DC는 두 compiler 모두 지원 (E-17, 확인) |
| build | CMake + Ninja, 또는 단순 Makefile | 경험에 의존, 미확인 |
| unit test | Unity (+ 필요하면 CMock/Ceedling) 또는 CMocka | 라이선스와 최신 상태는 경험에 의존, 미확인 |
| coverage | `gcc --coverage -fcondition-coverage` + `gcov --conditions`, 보고서는 gcovr. 교차 확인은 `clang -fcoverage-mcdc` + `llvm-cov --show-mcdc` | masking MC/DC. 6개 조건 제한 (LLVM 18). gcovr의 MC/DC 지원 여부는 확인하지 못함 |
| 경고 | `-Wall -Wextra -Wconversion -Wshadow -Werror` | 경험에 의존, 미확인 |
| 동적 검사 | ASan, UBSan (test 실행 때) | 경험에 의존, 미확인 |
| 정적 분석 | cppcheck(+ misra add-on), clang-tidy (bugprone, cert-*, clang-analyzer), GCC `-fanalyzer` | MISRA 규칙 텍스트는 직접 구해야 함 (E-18, 확인) |
| formal | CBMC (1순위), Frama-C Eva/WP (2순위) | 감시 함수를 정수로 쓰면 쉬움 (E-19) |
| traceability | 요구사항 YAML + 약 100줄 스크립트 (ID가 코드 주석과 test에 있는지 확인) | 도구 학습 비용을 피한다. 경험에 의존, 미확인 |
| CI | GitHub Actions 등 | 경험에 의존, 미확인 |
| 선택 단계 | Renode (MIT, Cortex-M 지원, Robot Framework 연동. 확인), QEMU (Cortex-M. 미확인), 저가 Cortex-M 보드 | E-20 |

주의: 위 도구는 모두 qualification되지 않았다. 17장의 tool 분류표에서 "이 책의 증거는 도구의 한계 안에서 얻었다"고 밝혀야 한다.

### 3.4 emulator나 보드로 옮겨야 하는가
- 필요한가: 책의 학습 목표(요구사항에서 test까지의 흐름)에는 필요 없다. E-15의 항목을 "실제로 본다"는 목표에는 필요하다.
- 언제: 단계 2의 14장을 쓸 때(단계 2 후반)가 적절하다. 그 전에는 오히려 방해다.
- 어떻게: HAL을 target용으로 하나 더 쓴다. 응용과 감시 코드는 바뀌지 않는다. 이 점이 HAL 설계(E-12)의 검증이 된다.

## 4. 잘된 점 (유지할 것)

1. 얇게 끝까지 먼저 가는 접근(PLAN 2절)과 vertical slice 목표. 모든 장을 깊게 쓰기 전에 흐름을 한 번 겪는다.
2. 장 계획에 "핵심 질문 / 다룰 내용 / 예제 산출물 / 근거"를 갖춘 구조. 독자에게도 저자에게도 목표가 분명하다.
3. 한계를 숨기지 않는 규칙: `(확인 필요)`와 `(2차 자료)`, 예제의 수치는 가정이라는 명시, PC sim의 한계를 적은 문장.
4. 세 분야 비교표(자동차, 로봇, 드론)와 "safe state가 다르다"는 비교 축. 독자가 개념을 분명히 이해하게 해 준다.
5. 단계 검토에서 두 검토자를 독립적으로 돌리고 판정을 FuSa 전문가가 하는 절차, 그리고 에이전트 검토가 사람 전문가를 대신하지 못한다는 인정.
6. book-map.svg의 V 모양과 "시스템 통합과 test는 개요만 다룬다"는 정직한 표시.
