# 부록 A. 용어집

초안이다. 장을 쓰면서 용어를 더하고 풀이를 고친다. 단계 1에서 열두 개를 더했다. 단계 2의 1, 4, 5장에서 열두 개를 더했다.

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

### HARA (hazard analysis and risk assessment)

hazard를 찾고, hazard마다 운전 상황을 놓아 risk를 평가해 등급을 주고, safety goal을 정하는 일이다.

- 근거: `nhtsa-etc-ev-fsa` 21쪽, 52쪽

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

- 주의: 보고서는 약어만 풀고 뜻을 설명하지 않는다. 그래서 이 책은 "ASIL이 붙지 않는 결과"라는 뜻으로만 쓴다. "일반적인 품질 관리로 충분하다"는 풀이는 받은 문서로 확인하지 못했다 `(확인 필요)`.
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

고장이 난 뒤 위험한 상태가 되기 전까지의 시간이다. 이 안에 고장을 알아채고 (fault detection time) 대응을 끝내 (fault reaction time) safe state에 도달해야 한다. 재는 끝은 사고가 아니라 위험한 상태다.

- 주의: AUTOSAR의 문서는 보통 FTTI를 알아채는 시간과 대응하는 시간의 합으로 본다고 적는다. 통신의 timeout과 debounce 횟수는 이 시간 예산에서 나온다.
- 주의: 보고서에는 정의 문장이 없고, 값은 거의 모두 정해지지 않은 채로 남아 있다. NASA의 지침서는 고장이 난 때부터 위험한 상태에 이를 때까지의 시간을 time to criticality라고 부른다.
- 주의: 이 책은 규격의 정의를 확인하지 못했다. 예제에서는 이 이름을 쓰지 않는다.
- 근거: `nhtsa-etc-ev-fsa` 71-72쪽, 74쪽. `autosar-e2e-protocol` 244쪽 (ISO 26262:2018 기준). `nasa-gb-8719-13` 117쪽

### functional safety concept

safety goal에서 functional safety requirement를 이끌어 내고 시스템의 요소에 나눠 주는 일이다. 다루는 것은 고장의 검출과 완화, safe state로의 전환, 운전자 경고다. functional safety requirement는 구현 방법이 아니라 해야 할 일을 적는다.

- 근거: `nhtsa-etc-ev-fsa` 66-67쪽, 72-73쪽

### functional, technical, software safety requirement

safety goal에서 코드까지 요구사항을 내리는 세 단계다. functional safety requirement는 item이 무엇을 해야 하는지를, technical safety requirement는 그것을 어떤 구조와 값으로 하는지를, software safety requirement는 소프트웨어의 어느 부분이 무엇을 하는지를 적는다. 요구사항을 요소에 나눠 주는 것을 allocation이라고 한다.

- 주의: 세 단계의 풀이는 이 책의 것이다. 받은 문서에서 functional safety requirement는 쓰임을 확인했고, 아래 두 단계는 이름만 확인했다 `(확인 필요)`.
- 근거: `nhtsa-etc-ev-fsa` 66쪽, 72-73쪽

### technical safety concept

functional safety concept의 요구사항을 어떤 구조로 만들지를 정한 것이다. 구조, 한계값, 시간, 바깥 요소에 대한 가정을 담는다.

- 주의: 풀이는 이 책의 것이다. AUTOSAR의 문서는 이 말을 설명 없이 쓴다 `(확인 필요)`.
- 근거: `autosar-safety-measures` 8쪽, 47쪽

### ASIL decomposition

요구사항 하나를 서로 독립된 요소들이 나눠 맡을 때 각각의 등급을 낮추는 규칙이다. 미국 정부의 보고서는 구현 사이의 독립을 보일 수 있으면 다른 등급으로 구현할 수 있다고 적는다.

- 주의: 이 책은 규칙의 조건을 원문으로 확인하지 못했다. 그래서 규칙을 설명하지 않고 예제에서도 쓰지 않는다 `(확인 필요)`.
- 근거: `nhtsa-etc-ev-fsa` 73쪽, 80쪽

### safety mechanism

고장을 알아채고 대응해 safety goal이 깨지지 않게 하는 수단이다. 입력의 검사, 감시, 통신의 보호, watchdog이 그 예다.

- 주의: 풀이는 이 책의 것이다. 받은 문서들은 이 말을 설명 없이 쓴다.
- 근거: `autosar-safety-measures` 9쪽, `nhtsa-etc-ev-fsa` 82쪽

### freedom from interference

ASIL이 낮은 소프트웨어가 ASIL이 높은 소프트웨어를 방해하지 않는 것이다. 방해의 원인은 메모리, timing, 실행, 정보 교환의 네 가지로 나눈다. AUTOSAR의 문서는 ISO 26262를 들어, 등급이 다른 소프트웨어를 함께 싣는다면 전체를 가장 높은 등급으로 개발하거나 방해가 없음을 보여야 한다고 적는다. 이 책은 이 내용을 이 문서 하나로만 확인했다.

- 주의: 이 책은 함수나 thread를 나눈 것만으로 방해가 없다고 쓰지 않는다. PC 시뮬레이션은 메모리 보호와 실행 시간 감시를 보이지 못하기 때문이다.
- 근거: `autosar-safety-measures` 9쪽 (ISO 26262:2018 기준)

## 구조와 고장

### fault containment region

안에서 난 fault가 밖으로 번지지 않고, 밖의 fault가 안으로 들어오지 않는 구역이다. 한 구역은 자기 안의 고장을 다 잡아내지 못한다. 그래서 고장을 잡으려면 서로 독립된 구역이 둘 넘게 있어야 한다.

- 주의: 근거 문서는 소송에서 원고 쪽 전문가였던 사람의 발표 자료다. 여기에서는 공학의 원칙을 설명한 부분만 쓴다.
- 근거: `koopman-toyota-ua` 31-32쪽

### single point of failure

그곳 하나가 고장 나면 다른 것이 막아 주지 못하고 그대로 시스템의 failure가 되는 곳이다. 하드웨어만이 아니다. 여러 요소가 함께 쓰는 입력이나, 여러 벌이 똑같이 도는 소프트웨어도 single point of failure가 될 수 있다.

- 근거: Leveson과 Turner (1993) 38쪽 (hardware interlock을 없앤 것이 소프트웨어를 single point of failure로 만들었다), `ariane-501-report` 9쪽 (두 장치가 같은 소프트웨어를 돌린다), `koopman-toyota-ua` 33-34쪽 (재판에서 원고 쪽 전문가였던 사람의 발표 자료)

### interlock

조건이 맞지 않으면 위험한 동작이 일어나지 못하게 막는 장치다. 제어하는 소프트웨어와 따로 동작하는 hardware interlock은 소프트웨어가 틀렸을 때의 마지막 보호가 된다.

- 근거: Leveson과 Turner (1993) 19-20쪽, 29쪽

### latent fault

평소에는 드러나지 않다가 다른 fault와 겹칠 때에야 드러나는 fault다. 감시 기능의 고장이 흔한 예다. 이 풀이는 이 책의 것이다.

- 주의: 미국 정부의 보고서는 주기적인 검사로 줄여야 하는 것으로 이 말을 쓴다. 규격의 정의는 확인하지 못했다 `(확인 필요)`.
- 근거: `nhtsa-etc-ev-fsa` 67쪽

### dependent failure

한 가지 원인이 여러 요소를 함께 틀리게 하거나, 한 요소의 고장이 다른 요소로 번지는 것이다. 기능과 감시가 같은 입력이나 같은 MCU에 기대면 여기에 해당한다. 이것을 따지는 분석을 dependent failure analysis라고 한다.

- 주의: 풀이는 이 책의 것이다. 규격의 정의는 확인하지 못했다 `(확인 필요)`.
- 근거: `autosar-safety-measures` 21쪽, 46쪽

### debounce

이상을 한 번 보고 바로 고장으로 판정하지 않고, 이어지는지를 세어 판정하는 것이다. 세는 동안의 시간은 고장을 알아채는 시간에 들어간다.

- 근거: `autosar-e2e-protocol` 244쪽

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

### fault injection

고장을 일부러 넣고 시스템이 정한 대로 알아채고 대응하는지를 보는 test다.

- 주의: 이 책의 예제는 fault를 하드웨어 추상화 계층의 뒤에서 넣거나, 모듈 전체를 바꿔 끼워서 넣는다. 제품의 코드에는 test용 코드를 넣지 않는다.
- 근거: `nasa-gb-8719-13` 179쪽, 192쪽

### statement coverage, decision coverage

structural coverage의 기준이다. statement coverage는 모든 문장이 한 번은 실행되었는지를 본다. decision coverage는 모든 판단이 참과 거짓으로 한 번씩 갔는지를 본다.

- 근거: `nasa-mcdc-tutorial` 13-15쪽

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

### safety case

시스템이 정해진 환경과 쓰임에서 뜻한 대로 동작한다는 것을 근거로 뒷받침해 설득하는 논증이다. 주장, 논증, 근거로 이루어진다.

- 주의: ISO 26262에서는 개발하면서 만든 산출물을 모아 safety case를 이룬다고 한다 `(2차 자료)`. 기준 판은 ISO 26262:2011이다.
- 근거: `gsn-standard-v3` 10쪽, `nhtsa-safety-standards-assessment` 33쪽

### GSN (goal structuring notation)

safety case의 논증을 그림으로 적는 표기법이다. 주장 (goal), 주장을 나누는 방법 (strategy), 근거를 가리키는 것 (solution), 입증하지 않고 두는 전제 (assumption)를 나눠 적는다.

- 주의: 표기법은 논증이 충분하다는 것을 보장하지 않는다. 읽는 사람이 따져 볼 수 있게 할 뿐이다.
- 근거: `gsn-standard-v3` 11-13쪽

## 규격과 과정

### normative, informative

규격 문서의 요소를 둘로 나눈 것이다. normative는 규정을 담는 부분이고, informative는 이해를 돕거나 배경을 알려 주는 부분이다. 요구사항은 normative한 부분에만 있다.

- 근거: ISO/IEC Directives, Part 2 (2021) 3.2.1, 3.2.2 (웹에서 읽음, 2026-11-22). 예: `gsn-standard-v3` 9쪽

### shall, should, may, can

ISO와 IEC의 문서에서 쓰는 조동사다. shall은 요구사항, should는 권고, may는 허용, can은 가능성이나 능력을 나타낸다. 그 문서를 따랐다고 주장하려면 shall이 붙은 것에서 벗어날 수 없다.

- 주의: 다른 기관의 문서는 다르게 정의한다. SORA는 should를 강한 의무의 뜻으로 쓴다. 문서마다 정의를 먼저 찾는다.
- 근거: ISO/IEC Directives, Part 2 (2021) 3.3.3 - 3.3.7, 7절 (웹에서 읽음, 2026-11-22). `sora-2-5-main-body` 29쪽

### compliance, assessment, certification

이 책에서는 이렇게 구분한다. compliance는 만든 쪽이 규격의 요구사항을 만족한다고 주장하는 것이다. assessment는 만든 쪽에서 떨어진 누군가가 그 주장을 따져 보는 것이다. certification은 권한이 있는 기관이 결과를 공식으로 인정하는 것이다.

- 주의: 이 구분은 저자의 정리이고 규격의 정의가 아니다. 항공에서는 소프트웨어를 따로 인증하지 않고, 소프트웨어가 든 시스템을 특정한 인증의 맥락에서 승인한다 `(2차 자료)`.
- 근거: `nhtsa-safety-standards-assessment` 33-34쪽 (DO-178C와 ISO 26262:2011을 설명), `faa-ac-20-115d` 1쪽

### safety lifecycle

안전에 관한 일을 처음 구상할 때부터 폐기할 때까지 단계로 나눈 것이다. 단계마다 입력, 목적, 활동, 산출물이 있고, 모든 단계에 걸쳐 verification과 assessment가 있다.

- 주의: waterfall이 아니다. 단계는 일의 종류이고 순서의 강제가 아니다.
- 근거: `hse-hsg238` 37-38쪽. `iec-61508-overview-slides` 21쪽 `(2차 자료)`

### safety plan

lifecycle의 활동을 이 프로젝트에서 누가, 언제, 무엇으로 하고 누가 확인하는지를 적은 계획이다.

- 근거: `nasa-gb-8719-13` 23쪽, 101쪽. `nasa-std-8739-8b` 6쪽

### verification, audit, assessment

만든 것을 확인하는 세 가지 일이다. verification은 산출물이 그 단계의 입력을 만족하는지를 본다. audit은 정한 과정을 따랐는지를 본다. assessment는 증거를 바탕으로 functional safety가 달성되었는지를 판단한다.

- 주의: 셋은 서로를 대신하지 못한다. 16장의 test는 verification의 한 수단이다.
- 근거: `hse-hsg238` 43쪽, 52쪽. `nasa-std-8739-8b` 10쪽

### independence (독립)

확인하는 사람이 만든 사람에게서 떨어져 있는 정도다. 기술의 독립 (개발에 참여하지 않았다), 관리의 독립 (다른 조직이고 스스로 정한다), 재정의 독립 (예산을 개발 조직이 쥐지 않는다)으로 나눌 수 있다.

- 주의: ISO 26262가 등급에 따라 요구하는 독립의 정도는 이 책이 확인하지 못했다. 소프트웨어 요소 사이의 독립 (freedom from interference)과는 다른 말이다.
- 근거: `nasa-std-8739-8b` 48쪽. `nhtsa-safety-standards-assessment` 34쪽 `(2차 자료)` (ISO 26262:2011 기준)

### confirmation measure, confirmation review

ISO 26262에서 산출물과 과정을 확인하는 활동을 가리키는 말이다 `(2차 자료)`. confirmation review는 등급에 따라 요구되고, 검토자가 개발자, 프로젝트 관리, 산출물의 작성자로부터 독립적이기를 요구한다고 한다 `(2차 자료)`.

- 주의: 종류와 등급별 요구는 이 책이 확인하지 못했다.
- 근거: `autosar-safety-measures` 46쪽 (ISO 26262:2018을 참조하는 문서. 용어만 나온다), `nhtsa-safety-standards-assessment` 34쪽 (ISO 26262:2011 기준)

### tailoring

과정을 이 프로젝트의 위험과 복잡도에 맞게 줄이거나 늘리는 것이다. 줄일 수 없는 바닥이 있고, 줄일 때에는 이유를 대고 개발 조직이 아닌 쪽의 승인을 받는다.

- 근거: `nasa-gb-8719-13` 43-46쪽, 87쪽. `nasa-std-8739-8b` 56-57쪽. `hse-hsg238` 33쪽, 38쪽

### safety culture

과정이 종이에 있는 것으로 그치지 않고 실제로 지켜지게 하는 조직의 성질을 가리키는 말이다. 받은 문서에 정의는 없고, 그것이 없을 때의 모습 (일정의 압박, 규칙을 무시하라는 압박, 소통의 실패, 안전이 우선순위를 받지 못함)이 적혀 있다.

- 근거: `hse-hsg238` 7쪽, 32쪽. `nasa-gb-8719-13` 265쪽. `b737max-jatr` 50쪽

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
