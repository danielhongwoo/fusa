# FuSa 전문가 검토 (1차, 독립 검토)

검토자: FuSa 전문가 역할 에이전트 (opus), 주도 검토자, 2026-11-22

# 1차 검토 보고 (FuSa 주도 검토자)

대상: /Users/daniel/work/fusa 의 README.md, OUTLINE.md, PLAN.md, RULES.md, chapters/ 아래 장 계획 24개와 부록 4개, references/standards.md, figures/book-map.svg. 모두 읽었고, 파일은 고치지 않았다.
나도 규격 원문을 볼 수 없다. 웹에서 확인한 것에는 주소를 달았고, 나머지는 "기억에 의존, 미확인"이라고 적었다.

## 1. 총평

판정: **조건부 가능**.

뼈대는 좋다. 독자, 범위, 관통 예제, 단계 구분, 근거 등급이 한 체계로 묶여 있고, 확인하지 못한 것을 표시하는 원칙도 있다. 다만 단계 1 전에 반드시 고칠 것이 넷 있다.

- (a) RULES 5.3은 조항 번호까지 적으라고 하는데, 원문은 볼 수 없다(등급 C). 이 조건에서는 기억에서 나온 조항 번호가 원고에 들어가게 된다(F-01).
- (b) 단계 1의 "얇은 조각"에 safety analysis(DFA/FFI)와 하드웨어 가정이 빠져 있다. 이대로면 E-Gas 감시 구조를 PC 시뮬레이션의 thread 분리로 흉내 내고 "독립적"이라고 가르칠 위험이 크다(F-02, F-03).
- (c) OUTLINE 비교표의 드론 열(SAIL, 소프트웨어 요구의 출처, safe state)이 실제 EASA 체계와 다르다(F-05, F-06, F-07).
- (d) 전기 구동에서 "토크 0 = safe state"라는 함정을 예제 설계 단계에서 막아야 한다(F-04).

이 넷을 반영하고, 규격 원문 구입 여부(정해야 할 것 2번)를 단계 1 시작 전의 관문으로 정하면 시작해도 된다.

## 2. 지적 목록

### A. 근거와 규칙 (가장 먼저 고칠 것)

**F-01 / 치명 / RULES.md 5.2, 5.3**
- 지적: 5.3은 `ISO 26262-6:2018, 7.4.3`처럼 조항까지 적으라고 한다. 그런데 근거 문서는 등급 C라서 볼 수 없다. 이 둘이 부딪치면 Claude가 기억으로 쓴 조항 번호가 표시 없이 들어간다. 이런 책에서 가장 흔하고 가장 해로운 오류다. 또 "표시 없음 = 근거 문서를 직접 읽고 확인했다"에서 누가 읽었는지(저자인지 Claude인지)와 어떤 판을 읽었는지가 남지 않는다.
- 근거: RULES.md 5.3과 5.1의 등급 C 규칙. 사실 관계는 문서 안에서 확인된다.
- 수정안:
  1. 조항 번호는 셋 중 하나로 확인된 것만 쓴다: 원문, ISO OBP(https://www.iso.org/obp, 서문, 범위, 용어, 목차를 무료로 볼 수 있다), IEC webstore의 preview PDF. 이 둘은 등급 B로 쓸 수 있고, 조항 제목과 Annex 제목을 확인하기에 충분하다. 그 밖에는 Part 단위로만 쓴다.
  2. 표기 형식을 더한다: `ISO 26262-6:2018, Clause 9 (2차 자료: 저자, 연도, 쪽)`.
  3. 근거 기록을 본문 밖에 둔다. 예: `notes/claims.md`에 ID, 주장, 근거, 확인한 사람, 확인한 판, 날짜. 본문에는 각주나 HTML 주석으로 ID만 단다.
  4. "Claude 기억에서 나온 조항 번호는 어떤 표시로도 최종 원고에 남기지 않는다"를 명문화한다.

**F-02 / 중요 / RULES.md 5.2, PLAN.md 9절 (2차 자료의 판과 질)**
- 지적: 무료 2차 자료는 상당수가 ISO 26262:2011을 기준으로 쓰였고, 2018년 판에서 조항과 Annex 구성이 바뀌었다. 예를 들어 2011년 판 Part 6의 "verification of software safety requirements"가 2018년 판에서는 Clause 11 "testing of the embedded software"가 되었다. 근거는 기억에 의존, 미확인. 업체 백서는 해석이 섞여 있다. 그런데 현재 `(2차 자료)` 표시에는 판과 질에 대한 조건이 없다.
- 근거: 기억에 의존, 미확인(판별 조항 대응).
- 수정안: RULES 5.2에 규칙 두 개를 더한다.
  - "2차 자료는 그 자료가 기준으로 삼은 규격의 판을 함께 기록한다. 판을 알 수 없으면 조항 번호의 근거로 쓰지 않는다."
  - "규범적 주장(shall 수준)은 업체 블로그 하나만을 근거로 삼지 않는다. 2차 자료는 둘 이상, 또는 발행 기관이나 인증 기관의 자료로 확인한다."

**F-03 / 중요 / RULES.md 6절 (저작권)**
- 지적: "표를 옮기지 않는다"는 원칙은 맞다. 하지만 ASIL 결정표처럼 책마다 다시 싣는 표를 어떻게 다룰지 구체적인 방침이 없다.
  - 사실과 방법(S1-S3, E1-E4, C1-C3를 조합해 ASIL을 정한다)은 보호 대상이 아니라고 본다. 표의 표현 그대로를 옮기는 것은 복제다.
  - ISO의 저작권 정책은 일부라도 복제하려면 허락을 받도록 한다. 다른 책들은 허락을 받아 싣는 경우가 많다고 알고 있다.
  - 법적 판단이 아니고, 기억에 의존, 미확인이다.
  - MISRA 규칙 본문과 E-Gas 문서의 그림도 같은 문제다.
- 근거: 기억에 의존, 미확인.
- 수정안: 세 단계 방침을 RULES 6절에 적는다.
  1. 기본: 표의 구조(축, 등급, 읽는 법)만 설명하고 칸은 채우지 않는다. 예제에서는 자기 hazardous event 3-5개에 대한 판정 결과만 보인다.
  2. 출판할 경우: 꼭 필요한 표 1-2개는 국가 표준 기관을 통해 복제 허락을 받는다(한국은 KS 판매 기관 경유, 미확인).
  3. ASIL 결정 규칙을 "각 등급 번호의 합"처럼 다른 형식으로 다시 표현하는 방법도 있다. 이 방법은 원문과 대조한 뒤에만 쓰고, 출판 전 법률 검토 대상으로 표시한다.
  - 함께 정할 것: MISRA 규칙은 번호와 자기 말로 쓴 요지만 쓴다. 규격의 정의(Part 1)는 직접 인용하지 않고 풀어 쓴다(이미 그렇게 정함). 국내법상 정당한 인용(저작권법 제28조) 범위는 출판사와 확인한다.

**F-04 / 중요 / OUTLINE.md 3절, ch06, ch07, PLAN.md 8절 (전기 구동의 safe state 함정)**
- 지적: 관통 예제는 "토크를 끊으면 안전하다"는 직관 위에 있다. 그러나 영구자석 동기 모터 inverter의 safe state는 간단하지 않다(기억에 의존, 미확인).
  - 고속에서 모든 스위치를 끄는 freewheeling을 쓰면 역기전력 때문에 제어되지 않는 제동 토크가 생길 수 있다.
  - active short circuit은 저속에서 끌림 토크를 만든다.
  - 그래서 safe state는 속도에 따라 다른 전략을 쓴다.
  - 전기 구동에는 음의 토크(회생 제동)도 있다. 따라서 대표 hazard는 의도하지 않은 가속 하나가 아니다. 의도하지 않은 감속(저마찰 노면에서 차량이 불안정해짐), 잘못된 방향, 정지 상태에서의 의도하지 않은 출발이 함께 있다.
  - item 경계(VCU의 토크 요구만인지, inverter의 토크 실행까지인지)도 정해져 있지 않다.
- 근거: 기억에 의존, 미확인.
- 수정안:
  1. 단계 0에서 item 경계를 "VCU의 토크 요구 경로"로 정한다. inverter는 가정(assumption of use)으로 받는 외부 요소로 둔다(SEooC와 비슷한 모양).
  2. HARA 표에는 위 hazard 4-5개를 모두 올리고, 끌고 가는 것은 하나로 한다.
  3. safe state를 "토크 0"이 아니라 "토크 요구를 허용 범위로 제한하고, inverter에 안전한 전환을 요청한다"로 정의한다. inverter 쪽 전략은 가정 목록에 남긴다.
  4. 6장 "흔한 오해"에 "끄면 안전하다"를 넣는다.
  - 예제의 S, E, C 값과 ASIL은 "brake override가 있다" 같은 controllability 가정에 크게 좌우된다. 가정을 표에 명시하고, 실제 제품의 ASIL로 읽히지 않게 한다(PLAN 8절의 기존 한계 항목을 강화).

**F-05 / 치명 / OUTLINE.md 3절, ch11, PLAN.md 5절 단계 1과 8절 (E-Gas와 독립성)**
- 지적: E-Gas 3단계는 다음과 같다(기억에 의존, 미확인).
  - Level 1: 기능.
  - Level 2: 기능 감시. 중복 입력으로 허용 토크를 다르게 계산해 비교한다.
  - Level 3: 제어기 감시. 별도 하드웨어의 감시 모듈과 질의-응답을 주고받는다.
  - 전기 구동의 VCU에 이 구조를 쓰는 것은 실무에서 흔하고 타당하다고 본다.
  - 문제는 안전 논증의 핵심인 독립성이다. 이 구조는 보통 Level 1을 QM으로, Level 2를 높은 ASIL로 같은 core에 둔다. 그래서 FFI(memory partitioning, timing, 정보 교환)와 Level 3의 독립 하드웨어가 논증의 핵심이 된다.
  - PC 시뮬레이션에서는 이 셋이 모두 "흉내"다. 단계 1 예제에는 DFA/FFI 분석도, 하드웨어 가정도 없다. 그대로 가면 독자는 "감시 함수를 다른 thread에 두면 독립적이다"라고 배운다. 이 책이 막아야 할 가장 큰 오해다.
  - 또 E-Gas 공개 문서는 웹 검색으로 찾지 못했다. 공개 여부, 판, 재배포 조건을 확인하지 못했다. 버전 6.0(2015)은 기억에 의존, 미확인.
- 근거: 기억에 의존, 미확인. 문서 찾기 실패는 검색으로 확인.
- 수정안:
  1. 단계 1 예제에 "FFI와 독립성 주장 목록 한 쪽"과 "하드웨어 가정 5-10줄"을 넣는다. 예: MPU가 있다, 독립 watchdog이나 감시 모듈이 있다, 페달 센서 두 채널의 특성이 다르다.
  2. 각 주장 옆에 "시뮬레이션이 보여 주는 것과 보여 주지 못하는 것"을 적는다.
  3. 11장의 "흔한 오해"에 thread 분리와 partitioning의 차이를 넣는다.
  4. 단계 0에서 E-Gas 문서의 출처와 등급을 확정한다. 구할 수 없으면 OUTLINE의 "공개된 감시 구조"라는 문장을 고친다.

**F-06 / 중요 / PLAN.md 7절 의존 그래프와 단계 1 범위**
- 지적: 그래프는 단계 1 묶음 안의 장이 묶음 밖의 장에 의존하는 것으로 그려져 있다: 8->11, 9->12, 13->15->16, 5->19, 17->19, 18->19. 이 정의("앞 장이 있어야 뒤 장을 쓸 수 있다")대로라면 단계 1은 시작할 수 없다. 내용상으로도 그렇다. safety analysis 증거가 없는 한 쪽짜리 safety case는 19장이 비판하려는 "형식만 갖춘 safety case" 그 자체다.
- 근거: PLAN.md 7절과 5절.
- 수정안:
  1. 화살표를 두 종류로 나눈다. 실선은 "쓰기 전에 필요", 점선은 "깊게 고칠 때 필요".
  2. 단계 1 예제에 8장의 최소분(safety goal 하나에 대한 FTA 1개와 F-05의 DFA/FFI 한 쪽)과 9장의 최소분(하드웨어 가정 목록)을 넣는다. 장 원고는 단계 2에 써도 된다.
  3. 6장 앞에 5장의 최소분(lifecycle 그림 반 쪽, item definition의 자리)을 2장이나 6장 머리에 둔다.

### B. 사실 정확성: 세 분야 비교표

**F-07 / 중요 / OUTLINE.md 2절 비교표 "등급" 행, ch03, ch21**
- 지적: SAIL을 ASIL, PL, SIL과 나란히 "등급"으로 놓으면 같은 종류의 값처럼 읽힌다.
  - SAIL은 운용(operation)에 대한 값이다. OSO(operational safety objective)마다 요구하는 robustness(integrity와 assurance) 수준을 정한다. 운영자 절차, 훈련, 설계 요구가 섞여 있다.
  - 소프트웨어 개발의 엄격함은 SAIL에서 바로 나오지 않는다. EASA의 SAIL V/VI용 MoC Light-UAS.2510-01을 보면, failure condition 분류(Major, Hazardous, Catastrophic)마다 FDAL D/C/B를 배정한다. 즉 드론에서도 소프트웨어의 엄격함은 결국 "failure condition에서 DAL로" 가는 항공 경로로 정해진다. 그리고 그 최대값은 DAL A가 아니라 B다.
- 근거: EASA, Final MoC Light-UAS.2510-01 (SAIL V and VI), Table 1과 9절, https://www.easa.europa.eu/sites/default/files/dfu/final_moc_light-uas_2510-01_sail_v_and_vi.pdf
- 수정안: "등급" 행을 두 행으로 나눈다.
  - "위험 평가의 결과": ASIL(safety goal) / PLr 또는 SIL(safety function) / SAIL(운용).
  - "소프트웨어 엄격함을 정하는 값": ASIL(요구사항에 상속) / PL 또는 SIL / SAIL V-VI에서는 failure condition에 따른 FDAL/IDAL, 그 아래 SAIL은 OSO의 robustness 수준.
  - 3장에는 "SAIL은 제품의 등급이 아니다"를 흔한 오해로 넣는다.

**F-08 / 중요 / OUTLINE.md 비교표 "소프트웨어 요구의 출처", ch21, standards.md 3절**
- 지적: "ASTM F3201, 고위험 운용은 DO-178C"는 미국과 EU 경로를 섞고 있다.
  - ASTM F3201-26은 2026년에 완전히 새로 쓴 판이다. 범위 설명에 FAA의 BVLOS 규칙(Normalizing UAS BVLOS Operations)에 대한 means of compliance가 들어 있다. 즉 미국 쪽 맥락이 강하다.
  - 책이 기준으로 삼은 EU 체계의 고위험(SAIL V/VI) 경로는 SC Light-UAS의 MoC다. 이 MoC는 소프트웨어에 AMC 20-115( )(ED-12C/DO-178C)를, 시스템 수준에 ED-79B/ARP4754B와 ED-135/ARP4761A를 쓴다. COTS 소프트웨어에는 ED-109A/DO-278A 12.4절을 함께 인정한다.
  - SAIL III-IV의 design verification(DVR)에서 소프트웨어를 어떻게 다루는지는 확인하지 못했다.
- 근거:
  - https://store.astm.org/f3201-26.html
  - https://knowledge.bsigroup.com/products/standard-practice-for-ensuring-dependability-of-software-used-in-unmanned-aircraft-systems-uas-3
  - 위 EASA MoC PDF의 참고 문서 목록과 software development assurance 절
- 수정안: 비교표의 칸을 다음과 같이 바꾼다. "SORA의 OSO -> EASA SC Light-UAS와 그 MoC. 고위험(SAIL V-VI)은 ARP4754B/ARP4761A와 DO-178C(AMC 20-115) 경로. 미국에서는 ASTM F3201이 FAA 규칙의 means of compliance로 쓰인다."
  - standards.md에 다음을 더한다: AMC 20-115D, ED-12C, ED-79B/ARP4754B, ED-135/ARP4761A, ED-279, MoC Light-UAS.2510-01.

**F-09 / 중요 / OUTLINE.md 비교표 "대표적인 safe state", ch21 핵심 질문, ch23**
- 지적: "드론은 정지할 수 없다, 자동차는 정지할 수 있다"는 대비는 양쪽 모두 지나치게 단순하다.
  - 자동차: 조향, 제동, 자동 운전 기능은 꺼지는 것이 안전하지 않다. ISO 26262:2018에는 emergency operation과 그 시간(EOTI) 개념이 있다. 자동 운전에는 minimal risk condition이 있다. 기억에 의존, 미확인.
  - 드론: multicopter는 제자리 비행도 착륙도 할 수 있다. 정확한 문장은 "공중에서 동력을 끊는 것은 safe state가 아니다"이다. flight termination은 safe state라기보다 지상 위험을 정해진 영역 안에 가두는 containment 수단이다. EASA MoC도 운용 영역 안의 추락을 failure condition으로 분류해 다룬다.
  - 로봇: protective stop도 늘 안전하지는 않다. 중력이 걸린 축, 들고 있는 짐, AMR의 제동 거리와 경사가 있다. 정지 category 0/1/2(IEC 60204-1)도 구분해야 한다. 기억에 의존, 미확인.
- 근거: 위 EASA MoC 9절(운용 영역 안의 추락 분류). 나머지는 기억에 의존, 미확인.
- 수정안: 비교 축을 "safe state에 이르는 데 드는 시간과 에너지, 그리고 그동안 무엇이 기능을 유지해야 하는가"로 바꾼다.
  - 드론 칸: "공중에서 동력 차단은 safe state가 아님. 복귀, 착륙 등 기능을 유지하는 대응이 필요하고, 최후 수단(termination)은 containment."
  - 21장 핵심 질문의 "멈출 수 없는 기계"는 "동력을 끊는 것이 안전하지 않은 기계"로 고친다.

**F-10 / 보통 / OUTLINE.md 2절 "개념의 뿌리" 이유, ch04 다룰 내용**
- 지적: "대부분의 분야별 규격이 IEC 61508에서 갈라져 나왔다"와 4장의 목록을 함께 읽으면, ISO 13849와 IEC 62304도 61508에서 나온 규격으로 읽힌다(기억에 의존, 미확인).
  - ISO 13849-1은 EN 954-1에서 나왔다. 61508을 일부 참조할 뿐이다.
  - IEC 62304는 ISO 14971과 짝을 이루는 의료 소프트웨어 lifecycle 규격이다. 61508의 분야별 구현이 아니다.
  - 61508의 분야별 구현으로 볼 수 있는 것은 IEC 62061, IEC 61511, ISO 26262(adaptation), 철도 규격의 일부다.
- 근거: 기억에 의존, 미확인.
- 수정안: 4장 규격 지도를 세 묶음으로 그린다: "61508의 분야별 구현", "61508을 참조하는 규격", "독립 계보(DO-178C, IEC 62304/ISO 14971, ISO 13849)". OUTLINE의 문장은 "여러 분야별 규격의 공통 기반"으로 낮춘다.

### C. 사실 정확성: 장 계획의 용어와 근거

**F-11 / 확인 결과, 수정 불필요 / ch08, ch11, ch18의 ISO 26262-6 Annex 언급과 ch11의 IEC 61508-3 Annex F**
- 지적 없음. 내 기억과 맞는다(기억에 의존, 미확인).
  - 6 Annex C: software configuration. 18장의 configuration/calibration data에 맞다.
  - 6 Annex D: freedom from interference. 11장에 맞다.
  - 6 Annex E: 아키텍처 수준의 safety analysis와 dependent failure analysis. 8장에 맞다.
  - 61508-3 Annex F: 한 컴퓨터 안 software element 사이의 non-interference 기법. 11장에 맞다.
- 수정안: ISO OBP나 IEC preview로 Annex 제목을 확인한 뒤 확인 등급을 올린다. 61508-3의 Annex A/B는 F-13에서 다룬다.

**F-12 / 보통 / ch06, ch07, ch12, ch14 (시간 개념)**
- 지적: FTTI가 6장에만 한 줄 있다. 2018년 판은 시간 구간을 나눴다: FDTI, FRTI, FHTI(= FDTI + FRTI, FHTI <= FTTI), EOTI, 그리고 multiple-point fault detection interval(기억에 의존, 미확인, 용어 이름은 높은 확신). FTTI는 hazard 쪽의 성질이고, 소프트웨어 엔지니어가 직접 만지는 것은 FDTI와 FRTI의 예산이다. "FTTI = task 주기 또는 watchdog 주기"라는 오해가 흔하다.
- 근거: 기억에 의존, 미확인.
- 수정안:
  - 6장: "FTTI는 차량 동역학에서 정해지는 hazard의 성질"만 다룬다.
  - 7장: 시간 모델 전체를 그림 하나로 정리한다.
  - 12장, 14장: watchdog 주기와 task 주기를 FDTI 예산과 연결한다.
  - 예제 산출물에 "시간 예산표"를 7장 단계 1 항목으로 넣는다.

**F-13 / 보통 / ch03, ch09 (IEC 61508의 기본 개념)**
- 지적:
  1. demand mode(low demand, high demand, continuous)가 빠졌다. 이것이 없으면 PFD와 PFH가 왜 둘인지, SIL 표를 어떻게 읽는지 설명할 수 없다. 자동차 기능은 대부분 continuous나 high demand에 가깝다는 비교도 할 수 없다.
  2. PFD/PFH의 목표값은 61508-1에, 계산 예는 61508-6 Annex B에 있다. HFT와 SFF(Route 1H)는 -2에 있다. 9장의 근거에 -1과 -6이 없다.
  3. "integrity level은 제품이 아니라 safety function이나 safety requirement의 속성이고, element는 그것을 물려받는다"와 QM의 뜻이 3장 다룰 내용에 없다. "ASIL D 칩", "SIL 3 소프트웨어" 같은 말이 왜 부정확한지가 3장의 핵심 오해다.
  4. 61508-3을 읽는 열쇠인 Annex A/B(SIL별 기법 표, normative)와 systematic capability(SC 1-4)가 어느 장에도 없다.
- 근거: 기억에 의존, 미확인.
- 수정안:
  - 3장에 demand mode, "등급은 요구사항의 속성", QM, systematic capability를 넣는다.
  - 9장 근거를 "IEC 61508-1(목표값), -2, -6"으로 고친다.
  - 13, 15, 16장 근거에 "IEC 61508-3 Annex A, B"를 명시한다.
  - 2장에 "소프트웨어 failure는 모두 systematic이지만, memory bit flip 같은 random hardware fault는 소프트웨어 동작으로 나타난다"를 흔한 오해로 넣는다.

**F-14 / 중요 / ch07 (ASIL decomposition)**
- 지적: "전제 조건(독립성)"만으로는 흔한 오용을 막지 못한다. 다음이 빠졌다(기억에 의존, 미확인, Part 9 Clause 5와 7).
  1. decomposition은 각각 혼자서 safety goal을 지킬 수 있는 중복 요구사항에 대해서만 한다.
  2. 표기법은 ASIL B(D)처럼 원래 등급을 함께 적는다.
  3. random hardware failure 지표는 원래 ASIL로 평가한다.
  4. 독립성은 DFA로 보인다.
  5. E-Gas에서 Level 1이 QM인 것은 "Level 2가 혼자서 safety goal을 지킨다"는 전제 위의 QM(D) + D(D) 구조다. 감시 쪽 등급은 낮아지지 않는다. 얻는 것은 기능 쪽을 QM으로 개발할 수 있다는 것뿐이고, 그 대가가 FFI다.
- 근거: 기억에 의존, 미확인.
- 수정안: 7장 다룰 내용에 위 5개를 넣는다. 예제의 technical safety concept에 decomposition 판단과 그 근거를 한 줄씩 적는다. "D를 B+B로 나누면 싸진다"를 흔한 오해에 넣는다.

**F-15 / 보통 / ch17 (기존 소프트웨어와 tool)**
- 지적: 경로가 한 목록에 섞여 있다. 기억에 의존, 미확인으로 정리하면 다음과 같다.
  - ISO 26262의 길은 넷이다.
    - (a) SEooC로 개발: Part 10 Clause 9, 해설이며 informative.
    - (b) software component의 qualification: Part 8 Clause 12.
    - (c) proven in use: Part 8 Clause 14. 변경이 생기면 다시 따져야 해서 소프트웨어에는 거의 쓰이지 않는다.
    - (d) 등급 없이 쓰고 FFI로 격리.
  - IEC 61508 쪽에는 Route 1S/2S/3S와 tool 분류 T1/T2/T3가 있다. TCL(Part 8 Clause 11)과 비교하면 좋은 교재다.
  - IEC TS 61508-3-1:2016(기존 소프트웨어의 재사용)이 Ed3에 흡수된다는 기록이 있다. IEC TR 61508-3-3:2025(객체 지향 소프트웨어)는 이미 나왔다.
- 근거:
  - https://genorma.com/en/standards/iec-61508-3-ed3 (3-1 흡수, 3-3 발행)
  - 나머지는 기억에 의존, 미확인.
- 수정안:
  - 17장을 "네 갈래 길" 표로 구성한다. open source는 (b)나 (d)의 사례로 다룬다.
  - TCL과 T1-T3를 나란히 비교한다.
  - standards.md에 IEC TS 61508-3-1과 IEC TR 61508-3-3을 더한다.

**F-16 / 보통 / ch05, ch19 (confirmation measure)**
- 지적: 두 장에 같은 내용이 있고, 구분해야 할 것이 빠졌다.
  - verification review(작업물이 맞는지)와 confirmation review(규격을 따랐는지)의 차이.
  - ASIL에 따른 독립성 수준(I0-I3).
  - 기억에 의존, 미확인.
- 근거: 기억에 의존, 미확인.
- 수정안: 5장은 "무엇을, 언제, 누가(독립성)", 19장은 "평가자가 safety case에서 무엇을 보는가"로 나눈다.

**F-17 / 보통 / ch01 사례**
- 지적: Toyota 사례는 원인이 다투어진다.
  - NHTSA/NASA 2011년 조사는 전자 결함의 증거를 찾지 못했다.
  - 2013년 Bookout v. Toyota 재판에서 전문가 증언이 소프트웨어 결함(단일 실패 지점, stack overflow 가능성 등)을 지적했고, 배심은 Toyota의 책임을 인정했다.
  - 관통 예제가 이 사례와 이어지므로, 원인을 단정하면 책 전체의 신뢰가 흔들린다.
  - 737 MAX MCAS는 "코드 버그"가 아니라 시스템 수준의 가정 문제(단일 AoA 센서, 조종사 반응 가정)다. 이 점이 오히려 좋은 교재다.
  - 이상 기억에 의존, 미확인.
- 근거: 기억에 의존, 미확인.
- 수정안: 1장에 "사례마다 공식 조사의 결론과 다툼이 있는 부분을 나눠 적는다"는 규칙을 둔다. 근거는 NHTSA 보고서(등급 A 후보)와 법정 증언 기록(등급 B)을 함께 쓴다. OUTLINE 3절의 "Toyota 사례와 이어진다"는 "의도하지 않은 가속이라는 hazard를 다룬다는 점에서 이어진다"로 고친다.

### D. references/standards.md

**F-18 / 보통 / standards.md 1절, 4절 (상태 갱신)**
확인한 것과 고칠 것:
- ISO 12100:2010: 현행이다. ISO 페이지에 "Next version under development(ISO/DIS 12100)"라고 나온다. CEN 목록은 2027-04 발행을 예상한다. `기억`을 `검색`으로 바꾼다.
  - https://www.iso.org/standard/51528.html
  - https://standards.iteh.ai/catalog/standards/cen/e54d5a11-1d8b-42a4-a422-5cfe2d1790b5/pren-iso-12100
- IEC 61508 Ed3: Part 3 ED3 기록에 투표 종료와 proof 날짜가 2026-11-13으로 나온다. 아직 발행 전이다. "최종 승인 단계"는 맞다. 발행은 2026년 말에서 2027년 사이로 본다.
  - https://genorma.com/en/standards/iec-61508-3-ed3
- ISO 26262 3판: ISO 페이지 기준으로 Part 1, 2, 6, 7은 DIS이고 Part 3과 10은 WD다. 페이지에 날짜가 없어 시점은 불명확하다. 발행 예상은 2027(2차 자료). 특히 Part 6이 DIS라서 10-16장의 "새 판에서 달라지는 점"에 직접 영향을 준다. Part별 상태 열을 둔다.
  - https://www.iso.org/standard/90020.html
  - https://ul.com/sis/blog/what-to-expect-with-version-3-of-iso-26262
- SORA 2.5: ED Decision 2025/018/R은 2025-09-15 결정, 2025-09-29 공표로 확인했다. 부록의 개정 번호를 2025-12-12 정오표가 Amendment 3에서 4로 고쳤다. SORA 2.0의 AMC(Decision 2019/021/R)는 그대로 효력이 있다. 이 공존을 적는다.
  - https://www.easa.europa.eu/en/document-library/agency-decisions/ed-decision-2025018r
- ASTM F3201-26: 2026년 발행, 완전히 새로 쓴 판으로 확인했다. "크게 개정된 것으로 보인다"를 "완전히 새로 쓴 판(complete rewrite)"으로 고친다.
  - https://store.astm.org/f3201-26.html
- IEC 62304: 2판이 진행 중이다. 적용 범위가 health software로 넓어지고 A/B/C 등급이 바뀐다. 단계에 대해서는 자료끼리 어긋나고, 발행은 2027 전후로 보인다. 22장에 "달라지는 점"으로 넣는다.
  - https://www.vde.com/topics-en/health/expertise/iec-62304-edition-2-changes
- "Part 10과 11은 guideline이고 나머지가 요구사항이다": Part 1(용어)도 요구사항이 아니다. 이렇게 고친다: "Part 2-9, 12가 요구사항, 1은 용어, 10과 11은 해설."
- IEC 61508은 Part 1-3이 normative, 4가 정의, 5-7이 informative다(기억에 의존, 미확인). 4장에서 normative와 informative를 가르치려면 표에 이 열이 있어야 한다.
- 기억에 의존, 미확인이지만 거의 확실한 것:
  - DO-178C, DO-330, DO-333은 2011-12 발행이고, EUROCAE 짝은 ED-12C, ED-215, ED-216이다.
  - IEC 61511-1:2016에는 AMD1:2017이 있다.
  - UL 4600은 3판(2023)이다.
  - EU 2019/947의 정식 명칭은 Commission Implementing Regulation이다.

**F-19 / 중요 / standards.md (빠진 문서)**
- 지적: 장 계획에 필요한데 목록에 없는 문서가 있다.
  - 로봇:
    - EU Machinery Regulation (EU) 2023/1230. 2027-01-20부터 적용된다. software를 safety component로 명시하고, 기계 학습으로 스스로 바뀌는(self-evolving) 안전 부품은 notified body를 거치게 한다. 20장의 틀에 직접 영향을 준다.
    - IEC 60204-1(정지 category).
    - ISO 13850(비상 정지).
    - IEC 61496-1/-3(laser scanner 같은 보호 장치).
    - ANSI/A3 R15.08(미국의 산업용 이동 로봇).
  - 드론:
    - Delegated Regulation (EU) 2019/945(기체 요구와 class mark C0-C6).
    - Regulation (EU) 2018/1139(basic regulation).
    - F-08의 항공 문서들.
  - 자동차 18장: UN R155, UN R156, ISO 24089(software update).
  - 공통: IEC TS 61508-3-1, IEC TR 61508-3-3, 한국어 번역본(KS R ISO 26262 계열인지 확인 필요, 기억에 의존, 미확인).
- 근거:
  - https://www.pilz.com/en-SG/support/law-standards-norms/manufacturer-machine-operators/machinery-regulation
  - https://www.ul.com/resources/navigating-new-eu-machinery-regulation-eu-20231230
  - 나머지는 기억에 의존, 미확인.
- 수정안: 위 문서를 `기억` 상태로 표에 더하고, 쓰는 장을 적는다.

### E. 로봇 장(20장)

**F-20 / 중요 / ch20 (ISO 10218:2025)**
- 지적: 2025년 판의 변화가 다룰 내용에 없다. 그리고 "collaborative robot"을 전제로 한 표현이 남아 있다. 확인한 것은 다음과 같다.
  - 2025년 판에서 "collaborative robot"과 "collaborative operation"이라는 용어가 사라졌다. "collaborative application"을 쓴다.
  - ISO/TS 15066의 내용이 시리즈 안으로 들어왔다. 다만 ISO의 10218-2:2025 페이지는 아직 TS 15066을 보완 문서로 언급한다.
  - Part 1의 safety function이 20개가 넘게 늘었다.
  - cybersecurity 요구가 새로 생겼다.
  - 2차 자료에 따르면 Class I/II 로봇 구분이 생겼다(Class I은 저질량, 50 N, 250 mm/s 수준).
  - 2차 자료에 따르면 10218-2의 Annex C가 safety function을 required, optional, conditional로 나누고 PL/SIL을 요구한다.
  - 로봇 규격이 safety function에 기본 등급을 미리 정해 주는 것은 자동차와의 큰 차이다. 자동차는 항상 HARA로 정한다. 비교표에 들어갈 만하다.
- 근거:
  - https://universal-robots.com/blog/safer-clearer-and-more-explicit-iso-10218-gets-a-makeover
  - https://www.automate.org/robotics/industry-insights/ansi-a3-publish-revised-r15-06-industrial-robot-safety-standard
  - https://si-fa.mitsubishielectric.com/fa/news/blog/avoid-getting-into-trouble-with-safety
  - https://www.iso.org/standard/73934.html
- 수정안: 20장에 "2025년 판에서 달라진 점" 항목을 넣는다. speed and separation monitoring과 power and force limiting은 "collaborative application의 방법"으로 표기한다. 비교표에 "규격이 기본 등급을 정해 주는가" 행을 더한다.

**F-21 / 보통 / ch20 (ISO 13849-1:2023)**
- 지적: 2023년 판은 소프트웨어 요구를 Clause 7로 독립시켰다.
  - 7.3: safety-related embedded software(SRESW).
  - 7.4: safety-related application software(SRASW).
  - limited variability language와 full variability language의 구분과 선택 지침이 들어 있다.
  - 소프트웨어의 systematic failure 회피를 다루는 Annex N이 새로 생겼다.
  - safety PLC 프로그래밍(LVL)이 이 독자가 로봇 쪽에서 가장 먼저 만날 소프트웨어다. 장 계획의 "embedded와 application의 구분"은 맞지만, 이 용어들이 빠졌다.
  - "PL과 SIL의 관계"는 PFH 범위를 대응시킨 것이다. 같은 개념이 아니라는 점을 밝혀야 한다(기억에 의존, 미확인).
- 근거:
  - https://www.tuvsud.com/en-gb/press-and-media/2023/may/updated-iso-standard-13849-1-machinery-control-system-safety
  - https://www.din.de/de/mitwirken/normenausschuesse/nasg/veroeffentlichungen/wdc-beuth:din21:367982018/toc-3436636/download (DIN 목차)
- 수정안: 20장 다룰 내용을 "Clause 7: SRESW와 SRASW, LVL과 FVL, Annex N"으로 바꾸고, PLr을 정하는 risk graph(Annex A)를 명시한다.

**F-22 / 보통 / ch20 보조 예제, PLAN 12절 7번 (자율 이동 로봇)**
- 지적: ISO 3691-4를 기준으로 삼은 것은 타당하다. 다만 예제 이름과 용어가 문제다.
  - "protective stop"은 ISO 10218의 용어다. 3691-4는 사람 감지와 제동으로 서술한다(기억에 의존, 미확인).
  - 실제 AMR 안전 기능은 safety laser scanner(IEC 61496-3)와 safety controller가 수행한다. 소프트웨어 엔지니어의 일은 "속도에 따라 보호 영역(field set)을 전환하는 것"과 그 설정을 검증하는 것이다.
  - 정지에는 제동 거리, 짐, 경사가 걸린다. F-09의 좋은 사례가 된다.
  - mobile manipulator는 10218과 3691-4에 걸친다.
- 근거: 기억에 의존, 미확인.
- 수정안: 보조 예제를 "속도에 따른 보호 영역 전환과 정지"로 바꾼다. ROS 2와 안전 controller의 분리를 같은 예제에서 보인다.

### F. 드론 장(21장)

**F-23 / 보통 / ch21 (SORA 2.5 개념과 분량)**
- 지적:
  - 개념 목록은 대체로 맞다. ground risk와 air risk, SAIL, OSO, robustness(integrity와 assurance), containment가 있다.
  - 하지만 다음이 빠졌다(기억에 의존, 미확인): 인구 밀도로 iGRC를 정하는 방식, mitigation(M1, M2), ARC와 TMPR, SAIL에 따라 design verification이나 인증 수준의 설계 요구가 붙는 방식(SAIL V-VI는 SC Light-UAS High Risk, F-07).
  - 한 장에 들어가기에는 다음이 너무 많다: PX4/ArduPilot 코드 읽기, 미국과 한국 제도, RTA(F3269), DO-178C.
- 근거: EASA MoC(F-07 주소). 나머지는 기억에 의존, 미확인.
- 수정안: 21장의 중심을 "SORA -> OSO -> 설계 요구 -> 소프트웨어 보증" 사슬 하나로 정한다. 미국과 한국 제도는 한 문단으로 줄인다. PX4/ArduPilot은 "읽어 볼 곳" 상자로 옮긴다. RTA는 11장 monitor 구조의 비교로 두 쪽 이내로 쓴다.

### G. 빠진 주제와 무게 배분

**F-24 / 중요 / ch09 또는 ch07 (차량 E/E 기초)**
- 지적: 독자는 임베디드 경험이 없다고 가정했다. 그런데 ECU, 센서에서 actuator까지의 신호 경로, CAN/CAN FD/Ethernet, AUTOSAR 계층을 설명하는 곳이 없다. 이것 없이는 12장의 E2E 보호(왜 CRC, counter, timeout인가)와 7장의 HSI가 공중에 뜬다.
- 근거: 판단.
- 수정안: 9장을 "하드웨어와 차량 E/E 기초"로 넓혀 3-4쪽을 둔다. 관통 예제의 E/E 구성(페달 센서 2채널 -> VCU -> CAN -> inverter)을 단계 0의 item definition 초안에 그린다.

**F-25 / 중요 / ch11, ch13, ch17 (model-based development)**
- 지적: 자동차 소프트웨어에서는 모델 기반 개발과 자동 code 생성이 표준적이다(ISO 26262-6 Annex B, 기억에 의존, 미확인). 그런데 17장에 한 줄만 있다. 이 독자가 실무에서 가장 먼저 부딪히는 차이 중 하나다. 무엇이 "unit"이고, coverage를 모델에서 재는지 code에서 재는지, code generator를 어떻게 믿는지가 다 여기서 나온다.
- 근거: 기억에 의존, 미확인.
- 수정안: 11장에 "모델이 설계인가 코드인가" 2쪽, 16장에 back-to-back test와 연결, 17장에 code generator의 TCL을 둔다. 예제는 C로 손으로 쓰되, 이 차이를 본문에서 밝힌다.

**F-26 / 보통 / ch18 (OTA와 규제)**
- 지적: OTA를 말하면서 UN R156과 ISO 24089가 없고, safety와 security가 만나는 지점(UN R155, E2E와 SecOC)도 23장에만 있다.
- 근거: 기억에 의존, 미확인.
- 수정안: 18장 근거에 UN R156과 ISO 24089를 넣는다. 12장의 E2E 절에 "E2E는 safety, SecOC는 security"를 짧게 비교한다.

**F-27 / 보통 / 무게 배분 (과한 것)**
- 지적: 이 독자에게 과한 것들이 있다.
  - 9장의 PFD, HFT, SFF 계산: 20장의 PFH를 읽는 데 필요한 만큼만 쓴다.
  - 14장의 ELISA와 범용 Linux: 상자 하나로 충분하다.
  - 15장의 abstract interpretation 이론: 도구가 무엇을 보장하는지만 쓴다.
  - 23장의 UL 4600, TS 5083, PAS 8800: 지도 수준이면 된다.
  - 22장의 네 분야: 비교표 중심으로 쓴다.
  - 24장 "흔한 오해": 장마다 이미 있으므로 겹친다.
- 근거: 판단.
- 수정안: OUTLINE 4절에 장별 목표 쪽수를 적는다. 예: 9장 10쪽, 14장 12쪽, 22-23장 각 8쪽, 6, 7, 10, 11, 12, 16장 각 18-20쪽. 24장의 오해 항목은 장별 항목에 대한 색인으로 바꾼다.

### H. 구조와 그림

**F-28 / 중요 / figures/book-map.svg, PLAN.md 4절 (V-model의 짝)**
- 지적:
  1. 맨 위에서 19장(safety case와 assessment)이 6장(HARA, safety goal)의 짝으로 놓였다. ISO 26262에서 safety goal의 짝은 차량 수준의 safety validation이다(Part 4, 기억에 의존, 미확인). safety case와 functional safety assessment는 Part 2에 속하는, 전체에 걸친 활동이다. 5장과 같은 가로 막대가 맞다.
  2. technical safety concept, 곧 시스템 설계의 짝은 system/item integration과 test다. 지금 "시스템 통합과 test"가 7장과 짝을 이룬 것은 대략 맞다. 하지만 7장 하나가 functional safety concept와 technical safety concept를 함께 품고 있어서 짝이 흐려진다.
  3. 하드웨어 쪽 V(Part 5)가 없다. 소프트웨어가 시스템 V 안의 한 갈래라는 점, 그리고 HSI가 둘을 잇는다는 점이 이 독자에게 중요하다.
  4. 나머지 짝은 규격 구조와 맞다: 16장 embedded software test와 10장, integration test와 11장, unit verification과 12/13장.
- 근거: 기억에 의존, 미확인(Part 4의 integration과 validation 위치).
- 수정안:
  - 오른쪽 맨 위를 "safety validation(개요, 16장 또는 19장에서 짧게)"으로 바꾼다.
  - 19장을 5장처럼 아래쪽 가로 막대로 옮긴다.
  - 7장 상자 안에서 FSC와 TSC를 나눠 적는다.
  - 10-16장 부분을 시스템 V에서 갈라진 소프트웨어 V로 그리고, 옆에 하드웨어 V(9장)를 점선으로 그린다.

**F-29 / 제안 / OUTLINE 4절 Part IV**
- 지적: 18장(변경, 형상, 생산과 운영)은 "안전함을 보이기"가 아니라 "안전함을 유지하기"다.
- 근거: 판단.
- 수정안: Part IV 제목을 "안전함을 보이고 유지하기"로 바꾼다.

### I. 관통 예제와 산출물

**F-30 / 중요 / PLAN.md 8절 산출물 표**
- 지적: 빠진 산출물이 있다.
  - safety plan: 5장 계획에는 있는데 표에 없다.
  - hazard log(또는 HARA의 가정 목록).
  - 시간 예산(F-12).
  - HSI specification.
  - DFA/FFI 분석(F-05).
  - 아키텍처 수준의 software safety analysis: 11장 다룰 내용에는 있는데 산출물에 없다.
  - verification plan과 verification report.
  - safety validation의 개요.
  - confirmation review 기록이나 assessment checklist(19장).
  - 가정 목록(inverter, MCU).
  - 2장의 hazard/fault 표, 4장의 조항 대응표 틀.
  - 요구사항 ID 체계: 단계 0에서 정하지 않으면 단계 2에서 추적표를 다시 만들어야 한다.
- 근거: PLAN.md 8절과 장 계획을 대조한 결과.
- 수정안: 표에 위 줄을 더한다. 단계 1에는 시간 예산, DFA/FFI 한 쪽, 가정 목록, ID 체계를 넣는다(F-05, F-06과 함께).

**F-31 / 보통 / PLAN.md 8절 기술 선택**
- 지적: fault injection 목록(센서 값 고정, 값 튐, 통신 끊김, 실행 지연)에 빠진 것이 있다: memory 손상(bit flip), 잘못된 실행 순서(program flow), 멈춘 task, 감시 기능 자체의 고장(latent fault). 12장의 "safety mechanism 자체의 고장"을 시험하려면 마지막 것이 꼭 필요하다.
  - MC/DC는 GCC 14의 `-fcondition-coverage`와 Clang 18의 `-fcoverage-mcdc`로 잴 수 있다고 알고 있다(기억에 의존, 미확인).
  - PC와 실제 보드 사이의 중간 단계로 QEMU나 Renode 같은 Cortex-M 에뮬레이터를 쓰면 MPU와 watchdog을 어느 정도 보일 수 있다(기억에 의존, 미확인).
- 근거: 기억에 의존, 미확인.
- 수정안: 단계 0에서 HAL 경계를 두고 코드를 짜서 나중에 옮기기 쉽게 한다. fault 목록에 위 4개를 더한다. 단계 0의 tool 확인 항목에 MC/DC 지원 compiler 버전을 적는다.

### J. 계획(PLAN.md)

**F-32 / 중요 / PLAN.md 10절 일정**
- 지적: 45주에 주당 6-8시간이면 270-360시간이다. 350쪽이면 쪽당 약 1시간인데, 여기에 학습, 사실 검증, 예제 코드, 검토 반영이 모두 들어간다. 초고를 Claude가 쓰더라도 저자가 원문과 대조하고 다시 쓰는 시간을 생각하면 현실적이지 않다. 단계 1(9장, 9-10주)은 장마다 예제 코드와 test까지 포함하는데, 장마다 1주는 빠듯하다.
- 근거: PLAN.md 10절의 수치로 계산.
- 수정안:
  - 단계 1 뒤에 다시 계산한다는 원칙은 유지한다.
  - 처음 추정을 1.5-2배로 잡거나, 목표 분량을 250쪽 안팎으로 줄인다.
  - 예제의 골격(시뮬레이터, build, test harness)은 단계 0의 별도 항목으로 1-2주 잡는다.

**F-33 / 중요 / PLAN.md 5절, 9절, 12절 2번 (원문 확보와 사람 검토)**
- 지적:
  - 원문을 구할지가 "정해야 할 것"에 있지만, 단계 1의 6, 7, 10, 11장은 ISO 26262-3, -4, -6, -9 없이는 1차 완료 기준("근거 표기 또는 확인 필요")만 겨우 넘는다.
  - 사람 실무자의 검토가 단계 4에만 있다. 그러면 토대의 오류가 19개 장에 퍼진 뒤에야 발견된다.
  - 두 역할 에이전트는 같은 계열의 모델이라 오류가 서로 상관된다. 독립 검토로 볼 수 없다.
- 근거: 판단.
- 수정안:
  1. 단계 0의 완료 기준에 "ISO 26262-3, -6, -9(가능하면 -4, -8) 확보 방법 확정"을 넣는다. 번역본이 더 싸면 그것도 비교한다. ISO OBP로 Part 1 용어를 확인하는 것은 바로 시작한다.
  2. 단계 1 검토에 사람 FuSa 실무자 한 명의 검토(9장과 예제, 몇 시간 분량)를 넣는다.
  3. PLAN 9절에 "에이전트 검토는 서로 독립이 아니다"를 명시한다.

**F-34 / 보통 / PLAN.md 11절 위험**
- 지적: 빠진 위험이 있다.
  - (a) 예제 코드와 ASIL 값이 실제 제품에 재사용되는 책임 문제.
  - (b) Claude가 초고를 쓰면 저자의 학습 목표가 약해지는 문제. "먼저 답하기"가 있지만 완료 기준에 저자 자신의 이해를 확인하는 항목이 없다.
  - (c) 2차 자료가 2011년 판 기준인 문제(F-02).
  - (d) ISO 26262 3판이 원고 완성 전(2027 예상)에 나올 가능성. 2018년 판으로 쓸지, 3판을 기다릴지를 지금 정해야 한다.
  - (e) EU Machinery Regulation 적용(2027-01)으로 20장이 낡는 문제.
- 근거: F-18, F-19의 주소.
- 수정안: 위험 표에 다섯 줄을 더한다. 각 대응은 다음과 같다.
  - (a) 본문과 코드 license에 면책 문구.
  - (b) 1차 완료 기준에 "저자가 핵심 질문의 답을 자료 없이 다시 쓸 수 있다".
  - (c) F-02의 규칙.
  - (d) "2018년 판 기준, 3판은 장마다 '새 판에서 달라지는 점' 상자"로 확정.
  - (e) 20장을 쓰는 시점에 다시 확인.

### K. 규칙(RULES.md)의 나머지

**F-35 / 보통 / RULES.md 빠진 규칙**
- 지적: 다음 규칙이 없다.
  - 예제 코드의 license와 면책.
  - 상표(MISRA, AUTOSAR) 표기.
  - 한국어 용어의 기준: 용어집이 KS 번역본을 따른다고 했는데, 번역본이 없거나 용어가 어색할 때 어떻게 할지.
  - 검토 기록에 검토 에이전트의 모델과 날짜를 남기는 규칙.
- 근거: 판단.
- 수정안: RULES에 "9. 예제 코드", "10. 용어의 기준" 절을 더한다.

**F-36 / 제안 / RULES.md 3절 (ASCII 규칙에서 생기는 문제)**
- 지적: ASCII와 한글만 쓰는 규칙 때문에 표기법이 필요한 곳이 생긴다.
  - 고장률 기호(lambda), 지수(10^-8/h), FIT.
  - 저자 이름의 발음 구별 기호: Avizienis의 원래 철자에는 비ASCII 글자가 있다.
  - 출판할 때 조판 단계에서 문장 부호를 바꿀지 여부.
- 근거: 판단.
- 수정안: 표기법 표를 더한다. 예: `lambda`, `10^-8 /h`, `1 FIT = 10^-9 /h`, 인명은 영어 문헌의 ASCII 표기를 따름.

## 3. 잘된 점 (유지할 것)

1. 확인 상태를 문장 단위로 드러내는 원칙(`(확인 필요)`, `기억`과 `검색` 열), 그리고 "에이전트 검토 의견도 확인 필요"라는 규칙. 이 책의 신뢰를 지탱하는 핵심이다. F-01처럼 조항 번호 쪽만 보강하면 된다.
2. "얇게 끝까지 먼저" 가는 전략과, safety goal 하나를 safety case까지 추적하는 단계 1 완료 기준. F-06처럼 analysis 조각만 더하면 이 책에 맞는 학습 구조다.
3. 관통 예제의 선택. 위험이 직관적이고, 감시 구조가 공개되어 있고(출처 확인은 필요), PC로 실습할 수 있다. 전기 구동의 함정(F-04)은 오히려 좋은 교재가 된다.
4. 세 분야를 "같은 문제를 다르게 푸는 방식"으로 비교하는 축, 그리고 로봇과 드론을 한 장씩으로 제한한 범위 관리.
5. 장 계획의 형식(핵심 질문, 다룰 내용, 예제 산출물, 근거)과 "흔한 오해"와 "확인 문제"를 최종 완료 기준에 넣은 것.

## 4. 저자가 결정해야 할 것

1. 규격 원문을 확보할지, 어느 Part까지인지, 언어(영어 원문인지 한국어 번역본인지)와 예산. 단계 1 시작 전에 정해야 한다(F-33).
2. 기준 판: ISO 26262:2018로 끝까지 쓸지, 3판 발행(2027 예상)에 맞춰 옮길지. IEC 61508도 Ed3를 기준으로 할지(F-18, F-34).
3. 출판 형태. 이것으로 저작권 방침의 단계가 정해진다: 표 구조만 설명, 허락을 받아 수록, 법률 검토(F-03).
4. 관통 예제의 item 경계: VCU만으로 할지, inverter까지 넣을지. 그리고 E-Gas 문서를 구하지 못할 때의 대안(F-04, F-05).
5. 목표 분량과 일정 중 무엇을 줄일지: 350쪽과 45주 가운데 하나(F-32).
6. 로봇 보조 예제의 기능: 일반적인 protective stop인지, 속도에 따른 보호 영역 전환인지(F-22). 그리고 EU Machinery Regulation을 20장의 틀에 넣을지.
7. 드론 장에서 EU 경로(SORA, SC Light-UAS, DO-178C)와 미국 경로(ASTM F3201, FAA 규칙)를 둘 다 다룰지, EU만 다룰지(F-08).
8. 사람 실무자 검토를 어느 단계에서 받을지, 비용을 들일지(F-33).

## 참고: 웹에서 확인한 출처

- https://www.easa.europa.eu/sites/default/files/dfu/final_moc_light-uas_2510-01_sail_v_and_vi.pdf
- https://www.easa.europa.eu/en/document-library/agency-decisions/ed-decision-2025018r
- https://store.astm.org/f3201-26.html
- https://knowledge.bsigroup.com/products/standard-practice-for-ensuring-dependability-of-software-used-in-unmanned-aircraft-systems-uas-3
- https://www.iso.org/standard/51528.html
- https://standards.iteh.ai/catalog/standards/cen/e54d5a11-1d8b-42a4-a422-5cfe2d1790b5/pren-iso-12100
- https://genorma.com/en/standards/iec-61508-3-ed3
- https://www.iso.org/standard/90020.html
- https://ul.com/sis/blog/what-to-expect-with-version-3-of-iso-26262
- https://www.iso.org/standard/73934.html
- https://universal-robots.com/blog/safer-clearer-and-more-explicit-iso-10218-gets-a-makeover
- https://www.automate.org/robotics/industry-insights/ansi-a3-publish-revised-r15-06-industrial-robot-safety-standard
- https://si-fa.mitsubishielectric.com/fa/news/blog/avoid-getting-into-trouble-with-safety
- https://www.tuvsud.com/en-gb/press-and-media/2023/may/updated-iso-standard-13849-1-machinery-control-system-safety
- https://www.din.de/de/mitwirken/normenausschuesse/nasg/veroeffentlichungen/wdc-beuth:din21:367982018/toc-3436636/download
- https://www.pilz.com/en-SG/support/law-standards-norms/manufacturer-machine-operators/machinery-regulation
- https://www.ul.com/resources/navigating-new-eu-machinery-regulation-eu-20231230
- https://www.vde.com/topics-en/health/expertise/iec-62304-edition-2-changes

확인하지 못한 것: E-Gas 문서의 공개 여부와 판(검색에서 찾지 못함), SAIL III-IV design verification에서 소프트웨어를 다루는 방식, ISO 10218:2025의 PL 기본값, ISO 26262 각 Part의 현재 단계가 언제 기준인지.

2차 검토(임베디드 엔지니어 의견)의 판정 요청을 받을 준비가 되어 있다.
