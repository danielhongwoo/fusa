# 부록 A. 용어집

초안이다. 장을 쓰면서 용어를 더하고 풀이를 고친다.

## 읽는 법

- 풀이는 이 책의 말로 쓴 것이다. 규격의 정의 문장을 옮긴 것이 아니다.
- 근거는 받은 문서의 id와 쪽이다. 쪽은 PDF 파일의 몇 번째 쪽인지다. 문서의 목록은 [references/README.md](../references/README.md)에 있다.
- `(2차 자료)`는 규격의 원문이 아니라 규격을 설명한 문서로 확인했다는 뜻이다. 그 문서가 기준으로 삼은 판을 함께 적었다.
- 같은 말을 문서마다 다르게 쓰는 경우에는 이 책이 따르는 쪽을 밝혔다.

## 기본 개념

### fault

error를 일으켰거나 일으킬 수 있는 원인이다. 아직 error를 일으키지 않은 fault는 잠들어 있다 (dormant)고 한다.

- 주의: NASA의 지침서는 fault를 감지되는 비정상 상태에 가까운 뜻으로 쓴다. 이 책은 원인이라는 뜻으로 쓴다.
- 근거: `avizienis-2004-taxonomy` 5쪽, `nasa-gb-8719-13` 303쪽

### error

시스템의 상태 가운데 올바른 상태에서 벗어난 부분이다. failure로 이어질 수 있지만 모든 error가 failure가 되지는 않는다.

- 주의: NASA의 지침서는 error를 사람이 요구사항, 설계, 구현에서 저지른 실수라는 뜻으로 쓴다. 이 책은 시스템의 상태라는 뜻으로 쓴다.
- 근거: `avizienis-2004-taxonomy` 5쪽, `nasa-gb-8719-13` 302쪽

### failure

시스템이 내놓는 동작이 올바른 동작에서 벗어나는 사건이다. fault가 error를 만들고, error가 밖으로 드러나면 failure가 된다.

- 주의: 명세를 어긴 경우만이 아니다. 명세가 틀려서 생긴 것도 failure다.
- 근거: `avizienis-2004-taxonomy` 5쪽

### hazard

사고로 이어질 수 있는 시스템의 상태나 조건이다. STPA는 환경의 나쁜 조건과 겹치면 손실로 이어지는 시스템의 상태라고 풀이하고, 설계자가 다룰 수 있는 범위 안의 상태로 한정한다.

- 주의: 문서마다 범위가 다르다. 자동차에서는 차량 수준에서 운전자의 명령과 차량의 반응이 어긋나는 모습으로 적는다. 예: 운전자가 요구하지 않았는데 가속한다.
- 근거: `stpa-handbook` 17쪽, `nasa-gb-8719-13` 304쪽, `nhtsa-etc-ev-fsa` 37쪽

### risk

해로운 일이 일어날 가능성과 그 결과의 심각도를 합쳐서 본 것이다.

- 근거: `nasa-gb-8719-13` 308쪽, `iec-61508-overview-slides` 11쪽

### safety

받아들일 수 없는 risk가 없는 상태다.

- 주의: "받아들일 수 없는"을 무엇으로 정하는지는 분야마다 다르다. ISO 26262는 "불합리한 risk가 없는 것"이라고 하고 그 뜻을 더 풀지 않는다고 한다 `(2차 자료)`. 기준 판은 ISO 26262:2011이다.
- 근거: `iec-61508-overview-slides` 8쪽, `nhtsa-safety-standards-assessment` 21쪽

### functional safety

safety 가운데 시스템이 입력에 맞게 올바르게 동작하는 데 달려 있는 부분이다 `(2차 자료)`. 자동차에서는 전기, 전자 시스템의 오동작이 만드는 hazard 때문에 생기는 불합리한 risk가 없는 것을 가리킨다 `(2차 자료)`.

- 주의: 오동작이 없어도 위험한 경우 (성능의 한계, 사람의 오용)와 공격은 여기에 들지 않는다. 23장에서 경계를 다룬다.
- 근거: `iec-61508-overview-slides` 8쪽 (IEC 61508을 설명한 2022년 발표 자료), `nhtsa-safety-standards-assessment` 14쪽 (ISO 26262:2011 기준)

### safety function

hazard가 사고로 이어지지 않게 하려고 시스템이 해야 하는 일이다. 무엇을 하는가 (기능)와 얼마나 믿을 수 있어야 하는가 (safety integrity)의 두 면이 있다.

- 근거: `iec-61508-overview-slides` 10쪽 `(2차 자료)`, `ifa-report-2-2017e` 20쪽

### safety integrity

safety function이 정해진 조건과 기간에 제대로 수행될 가능성이다 `(2차 자료)`.

- 주의: reliability와 같은 말이 아니다. 하드웨어의 우연한 고장만이 아니라 소프트웨어 같은 systematic failure까지 함께 다루려고 만든 개념이다.
- 근거: `iec-61508-overview-slides` 9쪽

### SIL (safety integrity level)

safety function에 요구되는 safety integrity의 등급이다. SIL 1부터 SIL 4까지 있고 SIL 4가 가장 높다 `(2차 자료)`.

- 주의: SIL은 safety function의 속성이다. 부품이나 소프트웨어 하나의 속성이 아니다.
- 주의: 이 책은 SIL을 이 뜻으로만 쓴다. test 환경인 software-in-the-loop는 줄여 쓰지 않는다.
- 근거: `iec-61508-overview-slides` 14-16쪽

### systematic failure, random hardware failure

위험한 failure를 원인으로 나눈 두 갈래다. random hardware failure는 하드웨어의 열화에서 생긴다. systematic failure는 명세의 오류, 빠진 요구사항, 소프트웨어의 오류, 사람의 실수, 변경 같은 원인에서 생긴다 `(2차 자료)`.

- 주의: 소프트웨어의 failure는 모두 systematic failure다. 그래서 소프트웨어의 안전은 고장률 계산이 아니라 개발 방법과 구조로 다룬다.
- 근거: `iec-61508-overview-slides` 12-13쪽, `nhtsa-safety-standards-assessment` 23쪽

## 자동차

이 절의 풀이는 대부분 미국 정부의 보고서 (`nhtsa-etc-ev-fsa`)가 ISO 26262를 적용한 방식을 근거로 한다. 그 보고서가 따른 판은 ISO 26262의 2011년 최종 초안이다. 그래서 이 절의 항목은 모두 `(2차 자료)`다.

### item

분석의 대상이 되는 시스템이다. 차량 수준의 기능을 구현한다. 이 책의 관통 예제에서는 차량 제어기 (VCU) 하나다.

- 주의: 보고서에는 정의 문장이 없고 쓰임만 있다.
- 근거: `nhtsa-etc-ev-fsa` 19쪽, 27-28쪽

### operational situation

차가 겪을 수 있는 운전 상황이다. 속도, 교통량, 노면, 운전 동작 같은 것으로 적는다. ASIL은 hazard와 운전 상황의 짝마다 평가한다.

- 근거: `nhtsa-etc-ev-fsa` 52-53쪽

### severity, exposure, controllability

ASIL을 정하는 세 가지 평가다.

- severity (S): 사람이 입을 수 있는 피해의 정도
- exposure (E): 고장과 겹치면 위험해지는 운전 상황에 놓여 있는 정도
- controllability (C): 운전자나 주변 사람이 제때 반응해 피해를 피할 수 있는 정도

- 주의: 보고서는 객관적인 자료가 없어서 분석자마다 평가가 달랐다고 적는다.
- 근거: `nhtsa-etc-ev-fsa` 54-56쪽, 57쪽

### ASIL (automotive safety integrity level)

hazard가 요구하는 엄격함의 등급이다. 운전 상황마다 severity, exposure, controllability를 평가해 등급을 찾고, 그 가운데 가장 나쁜 것을 hazard에 준다. A부터 D까지 있고 D가 가장 엄격하다.

- 주의: hazard의 ASIL은 safety goal로 넘어가고, 거기에서 나온 요구사항에 붙는다.
- 근거: `nhtsa-etc-ev-fsa` 21쪽, 52쪽, 55쪽

### QM (quality management)

ASIL을 정하는 표에서 A보다 낮게 나온 결과다. ASIL이 붙지 않는다.

- 주의: 보고서는 약어만 풀고 뜻을 설명하지 않는다. "일반적인 품질 관리로 충분하다"는 풀이는 아직 받은 문서로 확인하지 못했다 `(확인 필요)`.
- 근거: `nhtsa-etc-ev-fsa` 12쪽, 55쪽

### safety goal

hazard 분석에서 나온 차량 수준의 가장 위에 있는 안전 요구사항이다. hazard마다 만들고 그 hazard의 ASIL을 붙인다.

- 근거: `nhtsa-etc-ev-fsa` 21쪽, 58쪽

### safe state

고장이 났을 때 시스템이 옮겨 가는 상태다. 꺼진 상태만이 아니라 정상 동작이나 성능을 낮춘 동작도 될 수 있다. 고장마다 맞는 상태를 고른다.

- 주의: 기능을 끄는 것이 언제나 안전한 것은 아니다. 주행 중에 구동 토크를 끊으면 그것이 다른 hazard가 된다.
- 주의: safe state로 가는 변화는 제어된 변화이고 운전자에게 알려진다. 이 점이 hazard와 다르다.
- 근거: `nhtsa-etc-ev-fsa` 67-68쪽

### FTTI (fault tolerant time interval)

고장이 난 때부터 safe state에 도달해야 하는 때까지의 시간 한계다. 이 안에 고장을 알아채고 (fault detection time) 대응을 끝내야 (fault reaction time) 한다.

- 주의: AUTOSAR의 문서는 보통 FTTI를 알아채는 시간과 대응하는 시간의 합으로 본다고 적는다. 통신의 timeout과 debounce 횟수는 이 시간 예산에서 나온다.
- 주의: 보고서에는 정의 문장이 없고, 값은 거의 모두 정해지지 않은 채로 남아 있다.
- 근거: `nhtsa-etc-ev-fsa` 71-72쪽, 74쪽. `autosar-e2e-protocol` 244쪽 (ISO 26262:2018 기준)

### functional safety concept

safety goal에서 functional safety requirement를 이끌어 내고 시스템의 요소에 나눠 주는 일이다. 다루는 것은 고장의 검출과 완화, safe state로의 전환, 운전자 경고다. functional safety requirement는 구현 방법이 아니라 해야 할 일을 적는다.

- 근거: `nhtsa-etc-ev-fsa` 66-67쪽, 72-73쪽

### freedom from interference

ASIL이 낮은 소프트웨어가 ASIL이 높은 소프트웨어를 방해하지 않는 것이다. 방해의 원인은 메모리, timing, 실행, 정보 교환의 네 가지로 나눈다. 등급이 다른 소프트웨어를 함께 싣는다면 전체를 가장 높은 등급으로 개발하거나, 방해가 없음을 보여야 한다.

- 주의: 이 책은 함수나 thread를 나눈 것만으로 방해가 없다고 쓰지 않는다. PC 시뮬레이션은 메모리 보호와 실행 시간 감시를 보이지 못하기 때문이다.
- 근거: `autosar-safety-measures` 9쪽 (ISO 26262:2018 기준)

## 소프트웨어 기법

### E2E (end-to-end) protection

안전에 관련된 data를 보낼 때 보내는 쪽이 검사용 정보 (CRC, counter, ID)를 붙이고, 받는 쪽이 그것으로 data를 검사하는 방법이다. 통신 경로에서 생긴 손상, 유실, 반복, 순서 바뀜, 지연을 실행 중에 알아챈다.

- 주의: 알아챈 뒤에 무엇을 할지는 받는 쪽 응용이 정한다.
- 근거: `autosar-e2e-protocol` 13-14쪽, 32-34쪽

### program flow monitoring

프로그램이 정해진 시간과 순서로 실행되는지 감시하는 것이다. 시간 쪽은 주기적으로 실행되는지 (alive supervision)와 두 지점 사이의 시간 (deadline supervision)을 본다. 논리 쪽은 checkpoint를 지나는 순서 (logical supervision)를 본다.

- 근거: `autosar-safety-measures` 22-23쪽

### watchdog

소프트웨어가 정해진 시간 안에 신호를 보내지 않으면 reset 같은 대응을 일으키는 감시 장치다. AUTOSAR에서는 실행 감시의 결과를 하드웨어 watchdog의 신호와 묶는다.

- 주의: alive supervision은 실행되는 횟수만 본다. 순서가 옳은지는 logical supervision으로 본다 (`autosar-safety-measures` 22-23쪽).
- 근거: `autosar-safety-measures` 26-27쪽

### MC/DC (modified condition/decision coverage)

structural coverage의 기준 가운데 하나다. decision 안의 condition마다 그 condition이 decision의 결과를 혼자서 바꿀 수 있음을 test로 보인다. 입력이 n개인 decision에는 보통 test가 적어도 n+1개 필요하다.

- 주의: 혼자서 바꿀 수 있음을 보이는 방식이 둘이다. unique-cause는 다른 condition을 모두 고정한다. masking은 다른 condition이 결과에 영향을 주지 못하는 것을 논리로 보인다.
- 주의: structural coverage는 요구사항에 따라 만든 test가 코드를 얼마나 실행했는지 확인하는 수단이다. test를 만드는 방법이 아니다.
- 근거: `nasa-mcdc-tutorial` 10-12쪽, 15-17쪽, 19쪽, 79-82쪽

### deviation

코딩 지침을 어기는 것을 정해진 절차로 승인하고 기록한 것이다. 어긴 지침, 어긴 곳, 이유, 위험에 대한 판단을 남긴다.

- 주의: 개발자의 편의는 이유가 되지 못한다.
- 근거: `misra-compliance-2020` 20-21쪽

## 분석과 논증

### HAZOP (hazard and operability study)

기능마다 guide word (예: 기능 상실, 의도보다 많이, 의도보다 적게, 반대 방향)를 대어 보며 어긋난 동작을 찾는 분석이다.

- 근거: `nhtsa-etc-ev-fsa` 22쪽

### FMEA (failure mode and effects analysis)

구성 요소의 고장 모드에서 시작해 그 영향을 위로 따라가는 분석이다.

- 근거: `nhtsa-etc-ev-fsa` 23쪽

### STPA (system-theoretic process analysis)

시스템을 제어 구조로 그리고, 제어 명령이 위험해지는 경우 (UCA, unsafe control action)를 찾는 분석이다. 부품의 고장만이 아니라 틀린 feedback, 모자란 요구사항, 설계의 오류도 원인으로 본다.

- 근거: `stpa-handbook` 16-17쪽, `nhtsa-etc-ev-fsa` 24-25쪽

### GSN (goal structuring notation)

safety case의 논증을 그림으로 적는 표기법이다. 주장 (goal), 주장을 나누는 방법 (strategy), 근거를 가리키는 것 (solution), 입증하지 않고 두는 전제 (assumption)를 나눠 적는다.

- 주의: 표기법은 논증이 충분하다는 것을 보장하지 않는다. 읽는 사람이 따져 볼 수 있게 할 뿐이다.
- 근거: `gsn-standard-v3` 11-13쪽

## 로봇과 기계

### PL (performance level)

기계의 안전 제어가 위험을 얼마나 믿을 수 있게 줄이는지를 a부터 e까지로 나타낸 등급이다. 위험 평가에서 정한 목표는 PLr (required performance level)이라고 한다.

- 주의: 근거 문서는 ISO 13849-1의 2015년 판을 기준으로 한다. 현행은 2023년 판이다.
- 근거: `ifa-report-2-2017e` 16쪽, 20쪽

### SRESW, SRASW

ISO 13849-1이 소프트웨어를 나누는 두 갈래다. SRESW (safety-related embedded software)는 안전 부품에 들어가는 firmware다. SRASW (safety-related application software)는 기계를 만드는 쪽이 safety PLC 같은 부품 위에 짜는 응용 프로그램이다.

- 근거: `ifa-report-2-2017e` 64-65쪽 (ISO 13849-1:2015 기준)

## 드론

### SORA (specific operations risk assessment)

드론의 운용 하나를 승인받기 위한 위험 평가 방법이다. 지상의 위험과 공중의 위험을 따져 SAIL을 정하고, 거기에서 만족해야 할 목표를 얻는다.

- 주의: 제품이 아니라 운용을 평가한다.
- 근거: `sora-2-5-main-body` 15-18쪽

### SAIL (specific assurance and integrity level)

SORA가 운용에 주는 등급이다. I부터 VI까지 있다. 운용이 통제 아래에 있을 것이라는 믿음의 수준을 나타낸다.

- 주의: 이름이 SIL, ASIL과 비슷하지만 붙는 곳이 다르다. SAIL은 운용에 붙는다. 정량적인 값도 아니다.
- 근거: `sora-2-5-main-body` 47-48쪽

### OSO (operational safety objective)

SORA에서 운용자가 만족해야 하는 안전 목표다. SAIL에 따라 목표마다 요구되는 robustness가 정해진다.

- 근거: `sora-2-5-main-body` 53-55쪽

### robustness

SORA에서 대책이 얼마나 든든한지를 나타내는 수준이다. 위험을 얼마나 잘 줄이는가 (integrity)와 그것이 달성되었다고 얼마나 확신할 수 있는가 (assurance)를 함께 본다.

- 근거: `sora-2-5-main-body` 25-26쪽

### DAL (development assurance level)

항공에서 개발 오류를 줄이는 활동의 엄격함을 나타내는 등급이다. 기능이 관여하는 failure condition의 심각도에 따라 정한다. 기능에 주는 것을 FDAL, 소프트웨어나 전자 하드웨어 같은 item에 주는 것을 IDAL이라고 한다.

- 주의: 드론에서는 SAIL이 높은 운용에서 쓰인다. EASA의 문서는 SAIL IV에서 DAL C의 목표를 쓸 수 있는 방법 가운데 하나로 든다.
- 근거: `easa-moc-light-uas-2510` 5쪽, 9쪽. `easa-moc-light-uas-high-risk-2510` 5-6쪽, 9쪽
