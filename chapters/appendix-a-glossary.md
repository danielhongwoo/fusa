# 부록 A. 용어집

초안이다. 장을 쓰면서 용어를 더하고 풀이를 고친다. 단계 1에서 열두 개를 더했다. 단계 2의 1, 4, 5장에서 열두 개를 더했다. 8장과 9장에서 일곱 개를 더했다. 10 - 14장과 부록 E에서 스물일곱 개를 더했다. 15 - 17장에서 스물아홉 개를 더했다.

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

- 주의: AUTOSAR의 문서는 보통 FTTI를 알아채는 시간과 대응하는 시간의 합으로 본다고 적는다. 이 책은 그 합이 FTTI 안에 들어야 하는 것으로 읽는다. FTTI는 위험 쪽에서 정해지는 상한이고, 알아채는 시간과 대응하는 시간은 설계가 쓰는 시간이다. 통신의 timeout과 debounce 횟수는 이 시간 예산에서 나온다.
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

- 주의: 자동차의 하드웨어 지표에 비슷한 이름의 말이 있다. 뜻이 같다고 보지 않는다. 9장에서 다룬다.
- 근거: Leveson과 Turner (1993) 38쪽 (hardware interlock을 없앤 것이 소프트웨어를 single point of failure로 만들었다), `ariane-501-report` 9쪽 (두 장치가 같은 소프트웨어를 돌린다), `koopman-toyota-ua` 33-34쪽 (재판에서 원고 쪽 전문가였던 사람의 발표 자료)

### interlock

조건이 맞지 않으면 위험한 동작이 아예 일어나지 못하게 묶어 두는 장치다. 우리말로는 연동 장치라고 한다. 문이 열려 있으면 켜지지 않는 전자레인지가 흔한 예다.

- 주의: 제어하는 소프트웨어와 따로 동작하는 hardware interlock은 소프트웨어가 틀렸을 때의 보호가 된다. (이 책의 풀이다.)
- 근거: Leveson과 Turner (1993) 19-20쪽, 29쪽

### permanent, transient, intermittent fault

하드웨어의 fault를 얼마나 오래 있는가로 나눈 것이다. permanent fault는 한 번 생기면 계속 있고, transient fault는 잠깐 있다가 사라진다. intermittent fault는 나타났다 사라졌다 한다.

- 주의: 방사선이나 잡음으로 bit가 뒤집히는 transient fault를 soft error라고도 한다. 켤 때의 시험은 permanent fault만 찾는다.
- 근거: `avizienis-2004-taxonomy` 9쪽, 25쪽. `nasa-toyota-ua-report` 169쪽. `autosar-safety-measures` 66쪽

### dormant fault

있기는 하지만 지금 error를 일으키고 있지 않은 fault다. 쓰이지 않는 memory cell이나 한 번도 동작한 적이 없는 차단 회로의 고장이 그 예다. 일부러 써 보는 시험으로 찾는다.

- 주의: latent fault와 가까운 말이다. 이 책은 분류의 말로는 dormant를, 안전 mechanism의 숨은 고장을 말할 때에는 latent를 쓴다.
- 근거: `avizienis-2004-taxonomy` 5쪽, 24쪽

### diagnostic coverage

위험한 쪽의 고장 가운데 진단이 알아채는 것의 비율이다. 정확히 구하기 어려워 몇 단계의 값 (기계 분야에서는 0%, 60%, 90%, 99%)으로 쓴다.

- 주의: 고장을 알아채도 safe state로 제때 가지 못하면 값은 0이다. 시험하는 쪽이 시험받는 쪽에서 독립이어야 한다.
- 근거: `ifa-report-2-2017e` 57-58쪽, 285-288쪽 `(2차 자료)` (EN ISO 13849-1:2015 기준). `autosar-safety-measures` 68쪽 `(2차 자료)` (ISO 26262:2018을 설명)

### latent fault

평소에는 드러나지 않다가 다른 fault와 겹칠 때에야 드러나는 fault다. 감시 기능의 고장이 흔한 예다. 이 풀이는 이 책의 것이다.

- 주의: 미국 정부의 보고서는 주기적인 검사로 줄여야 하는 것으로 이 말을 쓴다. 규격의 정의는 확인하지 못했다 `(확인 필요)`.
- 근거: `nhtsa-etc-ev-fsa` 67쪽

### dependent failure

한 가지 원인이 여러 요소를 함께 틀리게 하거나, 한 요소의 고장이 다른 요소로 번지는 것이다. 기능과 감시가 같은 입력이나 같은 MCU에 기대면 여기에 해당한다. 이것을 따지는 분석을 dependent failure analysis라고 한다.

- 주의: 풀이는 이 책의 것이다. 규격의 정의는 확인하지 못했다 `(확인 필요)`. 분석하는 방법은 8장에 있다.
- 근거: `autosar-safety-measures` 21쪽, 46쪽. `nasa-gb-8719-13` 158쪽 (independence analysis)

### debounce

이상을 한 번 보고 바로 고장으로 판정하지 않고, 이어지는지를 세어 판정하는 것이다. 세는 동안의 시간은 고장을 알아채는 시간에 들어간다.

- 근거: `autosar-e2e-protocol` 244쪽

### hazard의 mitigation과 control

NASA의 지침서가 쓰는 구분이다. control은 hazard를 막는 수단이고 mitigation은 줄이는 수단이다. 소프트웨어와 논리로만 만든 격리 (논리적인 firewall)는 하드웨어의 고장이나 전자파로 무너질 수 있어서 mitigation으로만 센다.

- 근거: `nasa-gb-8719-13` 144쪽

### partitioning

소프트웨어 요소를 서로 나누어, 한 요소가 다른 요소의 memory를 바꾸거나 실행 시간을 빼앗지 못하게 하는 것이다. memory의 나눔은 MPU 같은 하드웨어가 막고 OS가 그것을 설정한다. 시간의 나눔은 OS의 실행 시간 감시와 timer가 한다. memory만 나눈 것은 반쪽이다. 소스 코드를 파일이나 함수로 나눈 것은 partitioning이 아니다.

- 주의: 같은 영역 안의 부품끼리는 막지 않는다. DMA나 다른 core의 접근을 막지 못하는 구현이 있다.
- 근거: `autosar-safety-measures` 13쪽, 15쪽, 18쪽, 20쪽 `(2차 자료)` (ISO 26262:2018 기준). 시간의 나눔은 `faa-ac-20-193` 5쪽 (항공의 지침)

### mixed criticality

등급이 다른 소프트웨어를 한 제어기에 함께 싣는 것이다. 높은 쪽이 낮은 쪽에게서 방해받지 않음을 보이지 못하면 전체를 높은 등급으로 만든다.

- 근거: `autosar-safety-measures` 9쪽, 15쪽 `(2차 자료)` (ISO 26262:2018 기준). `nasa-gb-8719-13` 20쪽

### majority voting

홀수 개의 채널이 같은 일을 하고 다수의 결과를 따르는 것이다. 셋 가운데 둘이면 고장 하나를 견딘다.

- 근거: `nasa-gb-8719-13` 142쪽

### limp home

고장이 난 뒤에 출력을 줄여 계속 달리게 하는 동작이다. 이 책의 예제에서는 "줄여 감" 상태다.

- 근거: `nasa-toyota-ua-report` 49쪽, 67쪽

### time to criticality

고장이 난 때부터 시스템이 위험한 상태에 이를 때까지의 시간이다. 자동으로 대응할 때 쓸 수 있는 여유를 정한다.

- 주의: 자동차의 FTTI와 닮았지만 다른 문서의 말이다.
- 근거: `nasa-gb-8719-13` 117쪽

## 소프트웨어 기법

### E2E (end-to-end) protection

안전에 관련된 data를 보낼 때 보내는 쪽이 검사용 정보 (CRC, counter, ID)를 붙이고, 받는 쪽이 그것으로 data를 검사하는 방법이다. 통신 경로에서 생긴 손상, 유실, 반복, 순서 바뀜, 다른 메시지가 그 메시지로 둔갑하는 것 (masquerading)을 실행 중에 알아챈다.

- 주의: 알아챈 뒤에 무엇을 할지는 받는 쪽 응용이 정한다. 지연은 counter만으로는 드러나지 않고, 받는 쪽이 제때 검사하며 timeout을 따로 볼 때 드러난다 (12장).
- 근거: `autosar-e2e-protocol` 13-14쪽, 32-34쪽, 83쪽, 107쪽

### program flow monitoring

프로그램이 정해진 시간과 순서로 실행되는지 감시하는 것이다. 시간 쪽은 주기적으로 실행되는지 (alive supervision)와 두 지점 사이의 시간 (deadline supervision)을 본다. 논리 쪽은 checkpoint를 지나는 순서 (logical supervision)를 본다.

- 근거: `autosar-safety-measures` 22-23쪽

### watchdog

소프트웨어가 정해진 시간 안에 신호를 보내지 않으면 reset 같은 대응을 일으키는 감시 장치다. AUTOSAR에서는 실행 감시의 결과를 하드웨어 watchdog의 신호와 묶는다.

- 주의: alive supervision은 실행되는 횟수만 본다. 순서가 옳은지는 logical supervision으로 본다 (`autosar-safety-measures` 22-23쪽).
- 근거: `autosar-safety-measures` 26-27쪽

### read-back (되읽기)

쓴 출력을 다시 읽어 쓴 값과 견주는 검사다. 이 책의 예제는 구동 허용 신호를 되읽는다.

- 근거: `nasa-gb-8719-13` 95쪽

### quizzer (seed-and-key)

한 제어기가 다른 제어기에 정해 둔 문제를 주고, 정한 시간 안에 옳은 답이 오는지로 그 제어기의 건전성을 확인하는 방식이다. 이 책의 예제는 이보다 단순한 꼴이다. 외부 watchdog이 질문을 보내지 않고, 기다리는 답이 몇 번째 답인지만으로 정해진다 (12장).

- 근거: `nhtsa-etc-ev-fsa` 74쪽

### fault injection

고장을 일부러 넣고 시스템이 정한 대로 알아채고 대응하는지를 보는 test다.

- 주의: 이 책의 예제는 fault를 하드웨어 추상화 계층의 뒤에서 넣거나, 모듈 전체를 바꿔 끼워서 넣는다. 제품의 코드에는 test용 코드를 넣지 않는다.
- 근거: `nasa-gb-8719-13` 179쪽, 192쪽

### statement coverage, decision coverage

structural coverage의 기준이다. statement coverage는 모든 문장이 한 번은 실행되었는지를 본다. decision coverage는 모든 판단이 참과 거짓으로 한 번씩 갔는지를 본다. condition coverage는 판단 안의 조건마다 참과 거짓을 가졌는지를 본다. multiple condition coverage는 입력의 모든 조합을 해 보는 것이어서 입력이 n개면 2^n개의 test가 든다.

- 주의: 2^n의 n은 조건의 수가 아니라 입력의 수다. `(A and B) or (A and C)`는 입력이 셋이고 조건이 넷이다.
- 근거: `nasa-mcdc-tutorial` 13-15쪽

### MC/DC (modified condition/decision coverage)

structural coverage의 기준 가운데 하나다. decision 안의 condition마다 그 condition이 decision의 결과를 혼자서 바꿀 수 있음을 test로 보인다. 입력이 n개인 decision에는 보통 test가 적어도 n+1개 필요하다.

- 주의: 혼자서 바꿀 수 있음을 보이는 방식이 둘이다. unique-cause는 다른 condition을 모두 고정한다. masking은 다른 condition이 결과에 영향을 주지 못하는 것을 논리로 보인다.
- 주의: unique-cause는 판단의 논리를 분석하지 않아도 되지만 같은 condition이 되풀이되거나 강하게 묶인 판단에는 쓸 수 없다. masking은 논리 분석이 필요하고 그런 판단에도 쓸 수 있다. 연산자가 한 종류인 판단에서는 두 방식이 같다.
- 주의: structural coverage는 요구사항에 따라 만든 test가 코드를 얼마나 실행했는지 확인하는 수단이다. test를 만드는 방법이 아니다.
- 근거: `nasa-mcdc-tutorial` 10-12쪽, 15-17쪽, 19쪽, 79-82쪽

### deviation

코딩 지침을 어기는 것을 정해진 절차로 승인하고 기록한 것이다. 어긴 지침, 어긴 곳, 이유, 위험에 대한 판단을 남긴다.

- 주의: 개발자의 편의는 이유가 되지 못한다.
- 근거: `misra-compliance-2020` 20-21쪽

### traceability (추적)

요구사항을 위로는 그것이 나온 곳에, 아래로는 구현한 코드와 확인한 test에 ID로 잇는 것이다. 이어져 있다는 것이 이어진 내용이 옳다는 뜻은 아니다.

- 근거: `nasa-gb-8719-13` 112-113쪽

### defensive programming

fault가 failure가 되지 않게 하려고 입력과 자기 상태를 의심하며 쓰는 방법의 모음이다. 입력의 범위 검사가 가장 단순한 예다.

- 근거: `nasa-gb-8719-13` 147쪽

### undefined behavior, implementation-defined behavior

undefined behavior는 틀린 구성이나 틀린 data에 대해 C 규격이 아무것도 요구하지 않는 동작이다. implementation-defined behavior는 compiler가 고르되 어떻게 골랐는지를 문서로 밝혀야 하는 동작이다.

- 근거: N1570 (C11의 공개된 최종 초안) 3.4.1절, 3.4.3절

### integer promotion

`int`보다 작은 정수형이 식 안에서 먼저 `int`로 넓어지는 것이다. 부호 없는 작은 형끼리 빼거나 밀어도 계산은 부호 있는 `int`로 한다.

- 근거: N1570 6.3.1.1절

### language subset, coding standard

언어의 구성 가운데 모호하거나 틀리기 쉬운 것을 쓰지 않기로 해서 만든 부분집합이고, 그것을 적은 문서가 coding standard다. 규칙으로 만든 부분집합은 compiler가 지키게 해 주지 않는다.

- 근거: `nasa-gb-8719-13` 208쪽

### rule, directive (MISRA)

MISRA의 지침은 둘로 나뉜다. rule은 source 코드만 보고 판정할 수 있는 요구이고, directive는 과정이나 문서에 걸쳐 있어 코드만으로는 판정되지 않는 요구다. 지침마다 mandatory (어길 수 없다), required (deviation이 있어야 어길 수 있다), advisory (할 수 있는 만큼 따른다)의 category가 있다.

- 근거: `misra-compliance-2020` 16쪽, 23쪽

### decidable, undecidable rule

decidable한 rule은 도구가 늘 예나 아니오로 답할 수 있는 rule이다. 실행 중의 값이나 흐름에 달린 rule은 undecidable해서, 도구가 진단을 내지 않았다는 것이 지켰다는 뜻이 되지 않는다.

- 근거: `misra-compliance-2020` 17-19쪽

### false positive (거짓 경보)

도구가 위반이 아닌 것을 위반으로 알리는 것이다. 모든 위반을 찾으면서 거짓 경보가 없는 정적 분석 도구는 만들 수 없다.

- 근거: `misra-compliance-2020` 12-13쪽

### cyclomatic complexity

함수 안의 판단의 수에서 나오는 값으로, 서로 독립인 경로의 수에 해당한다. 한계값은 문서마다 다르다.

- 근거: `nasa-gb-8719-13` 96쪽

### review, inspection (Formal Inspection)

review는 사람이 산출물 (요구사항, 설계, test 계획, 코드)을 읽어 결함이나 어긋남을 찾는 일을 두루 가리킨다. NASA의 지침서가 다루는 Formal Inspection은 정해진 단계와 검토자마다의 역할을 갖춘 구조화된 review로, 만든 사람의 이름을 따 Fagan Inspection이라고도 한다.

- 주의: Formal Inspection은 formal method가 아니다. 사람이 구조를 갖춰 읽는 방법이고, 수학으로 명세하고 증명하는 방법과 다르다.
- 주의: 읽은 사람이 떠올린 것만 찾으므로 빠짐없음은 보장하지 못한다. 앞의 풀이 가운데 review를 두루 가리키는 말은 이 책의 풀이다.
- 근거: `nasa-gb-8719-13` 118-119쪽, 176쪽

### 정적 분석 (static analysis)

코드를 실행하지 않고 읽어서 결함이나 규칙 위반을 찾는 방법과 그 도구다. 분석 시간과 정밀도는 맞바뀌고, 도구마다 보는 것이 다르다.

- 주의: 진단이 없다는 것은 그 도구가 검사하는 종류에서 그 도구가 보는 방식대로 지적하지 않았다는 뜻이다. 결함이 없다는 뜻이 아니다. false positive와 decidable, undecidable rule 항목도 본다.
- 근거: `misra-compliance-2020` 13쪽, 18-19쪽. `nasa-toyota-ua-report` 149쪽

### formal method (formal specification, formal verification)

수학으로 요구사항을 쓰고 그것이 지켜짐을 보이는 방법의 모음이다. 요구사항을 형식적인 수학 언어로 쓰는 것이 formal specification이고, 결과물이 그 명세를 만족한다는 증명을 주는 것이 formal verification이다.

- 주의: NASA의 지침서는 formal method가 높은 수준의 assurance를 준다고 인정되지만 정량적인 신뢰도를 보장하지는 않는다고 적는다. 증명 없이 명세를 쓰는 과정만으로도 요구사항의 문제를 찾은 사례가 있다.
- 근거: `nasa-gb-8719-13` 68-69쪽

### abstract interpretation, sound

실제 실행의 모든 경우를 덮는 더 큰 집합을 계산하고, 그 집합이 금지된 영역에 닿지 않으면 실제 실행도 닿지 않는다고 보는 정적 분석의 방법이다. 모든 경우를 덮는 분석을 sound하다고 하고, sound한 분석기가 경보를 내지 않았다면 검사한 종류의 오류가 없다는 증명이 된다. 대가는 일어날 수 없는 오류에도 경보가 나는 거짓 경보다.

- 주의: 보장하는 것은 검사한 종류의 오류 (예: 실행 중 오류)가 없다는 것까지다. 요구사항대로 동작한다는 뜻이 아니다.
- 주의: 이 책의 예제는 이런 도구를 쓰지 않았다. 풀이는 도구 개발 쪽의 공개된 설명 세 곳에 기댄다.
- 근거: Cousot, "Abstract Interpretation in a Nutshell" 7절, 9절, 11절, 13절 (웹에서 읽음, 2026-11-23). Brat 외, "IKOS" (NASA Ames, 2014) 1쪽. Astree 연구 팀 (ENS, INRIA)의 소개 쪽 (웹에서 읽음, 2026-11-23)

### model checking, state explosion

유한한 상태의 시스템을 자동으로 검증하는 formal method다. 시스템을 상태의 모델로, 성질을 temporal logic으로 적으면 도구가 상태 공간을 훑어 성질이 성립하는지 본다. 상태의 수가 memory나 시간을 넘기 쉬운 문제를 state explosion이라 하고, 이것이 주된 어려움이다.

- 주의: 모델에 대한 검증이다. 코드가 모델과 같다는 것은 따로 보여야 한다.
- 근거: `nasa-gb-8719-13` 128-129쪽. `nasa-toyota-ua-report` 150쪽, 152쪽

### bounded model checking, unwinding (unwinding assertion)

프로그램의 실행을 정해진 단계 수까지만 모델로 만들어 검증하는 방법이다. 반복문을 정한 횟수만큼 펼치는 것 (unwinding)으로 구현한다. 펼친 횟수가 모자라면 더 깊은 경로의 결함을 놓칠 수 있어서, 마지막 복사본에서 반복 조건이 거짓인지를 단언하는 unwinding assertion을 넣고, 그것이 모두 성립하면 준 한계가 그 프로그램에 충분하다. 이 책의 예제가 쓰는 CBMC가 이 방법의 도구다.

- 주의: 한계를 세는 법이 문서마다 다르게 읽힌다. 이 책은 CBMC 6.11에서 열 번 도는 반복문이 `--unwind 11`에서 증명되고 `--unwind 10`에서 unwinding assertion이 실패함을 직접 확인했다.
- 주의: 한계가 충분한지 보이지 않았다면 실행의 앞부분만 본 것이어서 증명이 아니다.
- 근거: CPROVER Manual, "Understanding Loop Unwinding". CBMC training, "Loop unwinding". Cousot 6절 (모두 웹에서 읽음, 2026-11-23). 이 책의 확인 (cbmc 6.11.0, 2026-11-23, `notes/claims.md`의 C-15-025)

### 불변식 (invariant)

프로그램이 시작할 때 성립하고 한 단계를 돌 때마다 유지되어, 어느 단계에서나 성립하는 상태의 조건이다. 이 책의 예제에서 성질 7은 한 주기를 돌기 전의 조건이 한 주기 뒤에도 성립함을 보이고, 켠 직후가 그 조건을 지킴을 따로 보여, 이 둘을 이어 불변식으로 쓴다. 한 주기의 증분이 아니므로 여러 주기에 쌓이지 않는다.

- 주의: 풀이는 이 책의 것이고, 받은 문서는 이 말을 설명하지 않는다. 이 예제의 성질 7을 한 주기의 증분으로 잘못 읽은 일이 있었다 (15장).
- 근거: `example/drive-torque/test/proof/harness.c` 성질 7 (`prove_faulty_function_bounded`), `reviews/2026-11-23-stage2-part3/README.md`

### requirements-based test

요구사항에서 출발해 만든 test다. 기댓값을 코드가 아니라 요구사항에서 정하므로 구현되지 않은 요구사항을 찾을 수 있고, 코드의 출력을 기댓값으로 여기는 치우침이 없다. 이 책은 기댓값을 요구사항의 숫자로 적는다.

- 주의: 코드를 보고 만든 test는 코드가 하는 일을 확인할 뿐이고 해야 하는 일을 확인하지 못한다. structural coverage는 이 test가 코드를 얼마나 실행했는지를 재는 수단이지 test를 만드는 방법이 아니다.
- 근거: `nasa-mcdc-tutorial` 10-12쪽, 16쪽 (DO-248A를 인용한 부분은 `(2차 자료)`)

### equivalence class, boundary value

equivalence class는 같은 방식으로 처리될 입력을 묶은 갈래이고, boundary value는 갈래가 바뀌는 경계의 값이다. 요구사항 하나에서 test를 뽑을 때 갈래마다 하나를 고르고 경계에서는 한계의 값, 그 아래, 그 위를 고른다.

- 주의: 받은 문서에서 이 둘은 test 계획 항목에 이름으로만 나온다. 풀이는 이 책의 것이다. 경계와 성능의 요구사항을 한계에서, 아래에서, 위에서 test하라는 말은 NASA의 지침서에 있다.
- 근거: `nasa-gb-8719-13` 179쪽, 187쪽. `nasa-mcdc-tutorial` 24-25쪽

### 단락 평가 (short-circuit evaluation)

C의 `&&`와 `||`에서 왼쪽만으로 결과가 정해지면 오른쪽을 평가하지 않는 것이다. MC/DC에서는 평가하지 않는 피연산자를 "상관없음"으로 두어 최소 test를 줄일 수 있다.

- 주의: 그렇게 줄인 최소 test는 compiler가 최적화할 때에도 옳게 동작할 때에만 유효하다. 앞의 풀이 가운데 단락 평가의 뜻은 이 책의 풀이다.
- 근거: `nasa-mcdc-tutorial` 49-51쪽

### dead code, deactivated code

coverage가 100%에 못 미칠 때 실행되지 않은 코드의 출처로 드는 두 가지다. 이 책의 말로 풀면 dead code는 어떤 요구사항에도 쓰이지 않는 코드이고, deactivated code는 일부러 넣었지만 이 설정이나 이 쓰임에서는 실행되지 않게 해 둔 코드다.

- 주의: 풀이는 이 책의 것이고 받은 문서는 두 말의 정의를 싣지 않는다. 같은 문서가 dead code는 지우는 것이 좋고 deactivated code는 설명하고 다루는 것이 좋다고 둘을 나눠 적는다.
- 주의: 17장의 dormant code와 다른 말이다.
- 근거: `nasa-mcdc-tutorial` 53쪽 `(2차 자료)` (DO-178B를 설명), 67-68쪽

### instrumentation

coverage 도구가 실행된 곳을 알려고 코드에 probe나 flag를 넣는 일이다. 코드를 바꾸므로 오류를 숨기거나 만들지 않음을 보여야 하고, 보통 원래 코드와 probe를 넣은 코드에 같은 test를 돌려 견준다.

- 주의: 도구가 확인하는 것은 probe를 넣은 코드이고, 넣지 않은 코드도 그렇다는 것은 가정이다. probe를 넣자 compiler가 함수의 호출 순서를 바꾼 예가 있다.
- 근거: `nasa-mcdc-tutorial` 56쪽, 59-60쪽

### mutation testing (변이 검사), equivalent mutant

프로그램에 작은 구문의 변화를 하나씩 넣은 변이 (mutant)를 만들고, test 묶음이 원래 프로그램과 다른 결과를 내어 그 변이를 가려내는지 보는 방법이다. 가려낸 변이의 비율이 test 묶음의 질을 나타낸다. 구문만 다르고 기능이 같아 어떤 test로도 가려낼 수 없는 변이를 equivalent mutant라 한다.

- 주의: 프로그램이 같은지는 판정할 수 없는 문제여서 equivalent mutant를 모두 자동으로 찾을 수는 없다. 그래서 "동등하다"는 이유를 사람이 적고, 그 이유가 틀릴 수 있다.
- 주의: "모두 잡음"은 넣어 본 변이를 모두 잡았다는 뜻이다. 이 책의 예제에서는 다른 사람이 넣은 변이가 네 번 구멍을 찾았다.
- 근거: Jia와 Harman, "An Analysis and Survey of the Development of Mutation Testing" (저자 원고, 2010) 1쪽, 3쪽, 4쪽 (웹에서 읽음, 2026-11-23). `example/drive-torque/docs/test-report.md`

### 대조 test

이 예제의 용어다. 안전 수단을 뺀 채 같은 fault를 넣어 보아, 수단이 없으면 safety goal이 깨짐을 보이는 test다 (예제의 ID는 `NC-`). 수단이 있을 때 통과하는 test가 정말 수단을 시험하는지 확인한다.

- 주의: 다른 수단이 같은 fault를 막기 시작하면 대조는 더는 대조가 아니게 된다. 수단을 더할 때마다 대조를 다시 본다.
- 근거: `example/drive-torque/docs/test-report.md` 3절, 6절

### model-in-the-loop, software-in-the-loop, processor-in-the-loop, hardware-in-the-loop

test를 돌리는 환경을 나눈 말이다. 회사의 설명에 따르면 software-in-the-loop는 개발 컴퓨터에서 compile한 source를 실행하고, processor-in-the-loop는 cross-compile한 코드를 target processor에서 실행하며, hardware-in-the-loop는 제어기의 하드웨어와 소프트웨어 같은 실물 부품을 모의 환경과 짝지어 쓴다 `(2차 자료)`. model-in-the-loop는 C 코드를 만드는 model을 돌리는 것으로 구분한 논문이 있다.

- 주의: 이 책은 이 말들을 줄여 쓰지 않는다. SIL이 safety integrity level과 헷갈리기 때문이다.
- 주의: 받은 문서에는 이 구분이 없어서 회사의 설명 둘과 논문 하나로 확인했다. 환경마다 보이는 것과 못 보이는 것은 이 책의 정리다.
- 근거: MathWorks, "Model Development Processes" (설명서). Synopsys (2025) 2쪽 (백서). Jordan 외 (2018) 5쪽 (모두 웹에서 읽음, 2026-11-23)

### back-to-back test

model에서 생성한 코드가 model의 시뮬레이션과 같은 결과를 내는지 견주는 test다. equivalence test라고도 한다 `(2차 자료)`.

- 주의: 이 책은 이 설명을 한 회사의 문서로만 확인했다. 규격이 이 test를 권하는지는 확인하지 못했다.
- 근거: MathWorks, "Back-to-Back Equivalence Testing" (설명서, 웹에서 읽음, 2026-11-23)

### negative test

소프트웨어가 의도한 기능만 하고 그 밖의 기능은 하지 않는다는 것을 보이는 test다. 예를 들어 고장이 없을 때 대응이 일어나지 않음을 본다.

- 근거: `nasa-gb-8719-13` 194쪽

### sanitizer

이 책의 예제가 쓰는 뜻으로는, 검사를 끼워 넣은 build (AddressSanitizer와 UndefinedBehaviorSanitizer)로 test를 돌려 test가 지나간 길의 memory 오류와 정의되지 않은 동작을 알리는 도구다.

- 주의: test가 지나간 길에서만 본다. 이 예제에서 한 칸 넘는 쓰기가 같은 stack 변수 안의 이웃에 떨어졌을 때 AddressSanitizer는 알리지 않았다. 도구가 알리지 않았다는 것은 그 도구가 보는 범위에서 알리지 않았다는 뜻이다.
- 근거: `example/drive-torque/docs/tools.md` 2절, `example/drive-torque/tools/variants.sh`

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

### safety analysis

설계의 어디가 어떻게 틀리면 safety goal이 깨지는지를 찾는 분석이다. hazard를 찾는 분석 (HARA)의 뒤에, 설계가 생긴 다음에 한다. FTA, FMEA, STPA가 여기에 쓰인다.

- 근거: `nhtsa-etc-ev-fsa` 21쪽, `nhtsa-safety-standards-assessment` 23쪽 `(2차 자료)` (ISO 26262의 2011년 최종 초안 기준)

### FTA (fault tree analysis), minimal cut set

일어나면 안 되는 사건 하나 (top event)에서 시작해 그것을 만드는 원인을 거슬러 찾는 분석이다. 원인은 AND와 OR로 묶인다. minimal cut set은 함께 일어나면 top event를 일으키는 사건의 가장 작은 묶음이다. 사건이 하나인 cut set은 single point of failure다.

- 주의: tree는 시스템의 모든 고장을 담지 않는다. 분석하는 사람이 떠올린 원인만 담긴다. 소프트웨어의 사건에는 확률을 붙이지 않는다.
- 근거: `nasa-fault-tree-handbook` 15-16쪽, 45쪽. `nasa-gb-8719-13` 316쪽

### common cause failure, cascading failure

둘 이상의 요소가 함께 고장 나는 두 가지 길이다. common cause failure는 한 가지 원인이 여럿을 같은 때에 고장 내는 것이다. cascading failure는 한 요소의 고장이 다른 요소로 번지는 것이다. 둘을 묶어 dependent failure라고 한다.

- 주의: 중복은 둘이 따로 고장 날 때에만 값을 한다. 같은 소프트웨어 두 벌은 늘 common cause를 가진다.
- 근거: `nasa-fault-tree-handbook` 70-72쪽. `nasa-gb-8719-13` 141쪽 (fault propagation)

### control structure, unsafe control action

STPA의 말이다. control structure는 누가 무엇을 제어하고 무엇을 되돌려 받는지를 그린 그림이다. unsafe control action은 어떤 상황에서 hazard로 이어지는 명령이고, 네 가지로 묻는다: 내리지 않아서, 내려서, 때나 순서가 틀려서, 너무 길거나 짧아서.

- 주의: 상황은 controller가 믿는 상태가 아니라 실제의 상태로 적는다. controller가 가진 믿음 (process model)이 틀린 것은 원인으로 따로 다룬다.
- 근거: `stpa-handbook` 22-25쪽, 35-40쪽

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

### compliance, 인증서, 승인

이 책에서는 이렇게 구분한다. compliance (conformance)는 만든 쪽이 규격의 요구사항을 만족한다고 주장하는 것이다. 인증서는 제삼자 기관이 평가한 결과를 낸 문서다. 승인은 규제 당국이 법이 정한 절차로 인정하는 것이다.

- 주의: 이 구분은 저자의 정리이고 규격의 정의가 아니다. "평가받았다"는 말은 무엇을 평가했는지를 함께 물어야 한다 (verification, audit, functional safety assessment 항목). 항공에서는 소프트웨어를 따로 인증하지 않고, 소프트웨어가 든 시스템을 특정한 인증의 맥락에서 승인한다 `(2차 자료)`.
- 근거: `nhtsa-safety-standards-assessment` 33-34쪽 (DO-178C와 ISO 26262:2011을 설명), `faa-ac-20-115d` 1쪽

### safety lifecycle

안전에 관한 일을 처음 구상할 때부터 폐기할 때까지 단계로 나눈 것이다. 단계마다 입력, 목적, 활동, 산출물이 있고, 모든 단계에 걸쳐 verification과 assessment가 있다.

- 주의: waterfall이 아니다. 단계는 일의 종류이고 순서의 강제가 아니다.
- 근거: `hse-hsg238` 37-38쪽. `iec-61508-overview-slides` 21쪽 `(2차 자료)`

### safety plan

lifecycle의 활동을 이 프로젝트에서 누가, 언제, 무엇으로 하고 누가 확인하는지를 적은 계획이다.

- 근거: `nasa-gb-8719-13` 23쪽, 101쪽. `nasa-std-8739-8b` 6쪽

### verification, validation, audit, functional safety assessment

만든 것을 확인하는 네 가지 일이다. verification은 산출물이 그 단계의 입력을 만족하는지를 본다. validation은 만든 것이 정해진 쓰임에서 요구사항을 만족하는지를 본다. audit은 정한 과정을 따랐는지를 본다. functional safety assessment는 만든 쪽에서 독립된 사람이 증거를 바탕으로 functional safety가 달성되었는지를 판단한다.

- 주의: 넷은 서로를 대신하지 못한다. audit과 functional safety assessment를 섞지 않는다. 앞의 것은 과정을, 뒤의 것은 결과를 본다. 16장의 test는 verification의 한 수단이다. validation의 뜻은 문서마다 조금 다르다. 요구사항의 명세 자체가 옳은지를 validation에 넣는 문서도 있고, HSE는 그것을 functional safety assessment에 넣는다.
- 근거: `hse-hsg238` 43쪽, 52쪽. `nasa-std-8739-8b` 10쪽

### independence (독립)

확인하는 사람이 만든 사람에게서 떨어져 있는 정도다. NASA는 독립된 검증 조직에 대해 기술의 독립 (개발에 참여하지 않았다), 관리의 독립 (다른 조직이고 스스로 정한다), 재정의 독립 (예산을 개발 조직이 쥐지 않는다)의 셋을 든다.

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

## 도구와 밖에서 온 소프트웨어

이 절의 풀이는 대부분 공개된 웹 자료와 NASA, MISRA의 문서에 기댄다. 규격의 용어는 모두 `(2차 자료)`다.

### tool qualification

이 책에서는 도구나 소프트웨어를 쓰기 전에, 그것이 정한 목적에 맞게 동작한다는 근거를 갖추는 일을 뜻한다. 이 풀이는 이 책의 것이다.

- 주의: 필요한 경우와 방법은 규격마다 다르다. 항공의 지침은 도구의 출력을 다른 verification 활동이 확인하면 qualification이 필요하지 않다고 읽힌다. MISRA Compliance:2020은 어떤 과정 표준이 어떤 경우 compiler와 정적 분석 도구의 qualification을 요구한다고만 적고, 그 경우가 무엇인지는 적지 않는다.
- 근거: `misra-compliance-2020` 14쪽 `(2차 자료)` (판을 밝히지 않음). FAA Order 8110.49 (2003년 판의 9장, Chg 2는 2017) PDF 37-38쪽 `(2차 자료)` (DO-178B 기준)

### development tool, verification tool

항공의 옛 규격 DO-178B에서 쓰던 도구의 두 분류다. development tool은 오류를 시스템에 직접 넣을 수 있는 도구이고, verification tool은 이미 있는 오류를 놓칠 수만 있는 도구다 `(2차 자료)`. 오류가 제품에 남으려면 개발과 verification 두 과정이 함께 모자라야 하므로 두 종류에 다른 엄격함을 요구한다.

- 주의: verification 중에 쓰는 도구가 모두 verification tool은 아니다. 감시 코드를 넣었다 걷어 내는 도구는 제품을 바꿀 수 있다. 분류는 최종 제품에 미치는 영향으로 정한다.
- 근거: FAA Order 8110.49 PDF 37-38쪽 (DO-178B 기준, 발행 기관의 문서를 통한 `(2차 자료)`). `faa-ac-20-115d` 11쪽

### TCL (tool confidence level), TI, TD

자동차의 ISO 26262에서 도구를 쓰는 데 대한 확신을 나눈 분류를 어느 자료가 이렇게 설명한다 `(2차 자료)`. TI (tool impact)는 도구가 오류를 넣거나 놓칠 수 있는가이고, TD (tool error detection)는 도구의 오동작을 막거나 찾아낼 것이라는 확신의 높이다. 둘을 맞대어 TCL이 정해지고, TCL1은 더 qualification할 필요가 없는 경우다.

- 주의: TCL은 도구가 따내는 등급이 아니라 그 프로젝트에서 그 도구를 쓰는 방식에 대한 분류다. 판정의 책임은 쓰는 쪽에 있어서, 공급자가 미리 정한 TCL도 쓰는 쪽이 자기 쓰임에 맞는지 확인해야 한다고 Synopsys의 글이 적는다.
- 근거: Synopsys, "Understanding How to Assess Tool Confidence Levels for ISO 26262" (2017) 1-5쪽 `(2차 자료)` (ISO 26262:2011 기준). Siemens (2022) `(2차 자료)` (ISO 26262:2018 기준)

### TQL (tool qualification level)

항공의 DO-330과 DO-178C에서 도구의 qualification 엄격함을 나타내는 등급이다. 도구의 쓰임을 기준 셋 (출력이 소프트웨어가 되어 오류를 넣는 것, verification을 자동화해 다른 과정을 줄이는 근거가 되는 것, 의도한 범위에서 오류를 놓치는 것)으로 나누고 소프트웨어의 level과 맞대어 정한다. 번호가 낮을수록 엄격하다고 회사 셋이 같게 설명한다 `(2차 자료)`.

- 주의: 이름이 TCL과 비슷하지만 항공의 것이고 자동차의 TCL과 같은 분류가 아니다. FAA의 문서 (AC 20-115D)는 DO-178B로 qualification한 도구를 새 기준에 대응시키는 표만 준다.
- 근거: AFuzion (연도 미표기). LDRA (2021) 3쪽. Rapita Systems (연도 미표기) `(2차 자료)` (모두 DO-330을 설명한 글). `faa-ac-20-115d` 11쪽

### T1, T2, T3 (IEC 61508의 도구 부류)

IEC 61508이 off-line 지원 도구를 나눈 세 부류를 어느 자료가 이렇게 설명한다 `(2차 자료)`. T1은 실행 코드에 기여하지 않는 도구 (편집기), T2는 test와 verification을 돕고 그 오류가 결함을 못 찾게 할 수 있는 도구 (coverage 측정, 정적 분석), T3은 실행 코드에 기여하는 출력을 내는 도구 (최적화 compiler)다. T3에는 도구가 자기 명세에 맞는다는 증거가 필요하고 도구의 새 판마다 qualification한다고 설명한다.

- 주의: 근거 세 곳 가운데 둘은 부류의 정의를 거의 같은 문장으로 적어서 서로 독립한 근거로는 약하다. 기준 판이 자료마다 다르다.
- 근거: Conrad 외 (2010경) 3쪽 (IEC 61508 2판 초안 기준). El-Sayed (UL, 2024) 10-11쪽 (2판 기준). AbsInt (연도 미표기, 판을 밝히지 않음)

### OTS, COTS, SOUP

NASA의 지침서는 사 온 것 (COTS, commercial off-the-shelf)과 다른 프로젝트에서 다시 쓰는 것을 함께 OTS (off-the-shelf)라 부르고, SOUP (software of uncertain pedigree, 출신이 불확실한 소프트웨어)는 문제를 앞에 내세워서 낫다고 적는다. 문서가 모자라고 source가 없으면 어떤 안전 분석은 할 수 없고, 잘 알려진 소프트웨어도 오류가 없다고 가정하지 말라고 한다.

- 주의: 같은 지침서가 OTS의 안전에 확신을 주는 일이 아직 "black art"에 가깝다고 적는다.
- 근거: `nasa-gb-8719-13` 271-273쪽, 280쪽

### dormant code

필요 없는 기능이 들어 있는 소프트웨어에서, 그 기능을 꺼도 다시 compile하지 않으면 남아 있는 코드다. NASA의 지침서는 이런 코드를 찾으려면 source가 필요하다고 적는다.

- 주의: dormant fault와 다른 말이다. dormant fault는 지금 error를 일으키고 있지 않은 fault의 상태를 가리키고, dormant code는 제품에 들어 있지만 쓰이지 않는 코드를 가리킨다.
- 근거: `nasa-gb-8719-13` 272쪽, 278쪽

### wrapper

OTS를 나머지에서 격리해 어떤 입력이 닿지 못하게 하거나 출력을 검사하는 것이다. NASA의 지침서가 OTS를 다루는 수단으로 든다.

- 주의: 문서가 말하지 않은 출력은 wrapper를 빠져나갈 수 있고, wrapper가 OTS만큼 커질 수도 있다.
- 근거: `nasa-gb-8719-13` 276쪽

### adopted code

MISRA Compliance:2020에서 프로젝트 밖에서 온 코드를 가리키는 말이다. 표준 library, driver, 제3자 library, 자동 생성 코드, legacy 코드가 든다.

- 주의: 그 문서는 adopted code가 시스템의 integrity에 미치는 영향을 간과하거나 무해하다고 가정해서는 안 된다고 한다. MISRA 지침의 준수는 adopted code의 품질에 필요조건도 충분조건도 아니라고 적는다.
- 근거: `misra-compliance-2020` 25-26쪽

### SEooC (safety element out of context)

특정 차량이나 item을 모른 채, 쓰일 맥락을 가정해 개발한 요소다. 두 회사의 글이 이렇게 설명한다 `(2차 자료)`. 통합할 때 가정이 맞는지 확인하고, 맞지 않으면 영향 분석을 해서 item 쪽이나 SEooC 쪽을 바꾼다.

- 주의: 쓰는 쪽에서 보면 안전하다고 끝난 부품이 아니라 "이 가정이 맞으면"이라는 조건이 딸린 근거다. AUTOSAR의 문서는 자기 명세가 SEooC를 정의하지 않는다고 적는다.
- 근거: Embitel (2019, 판을 밝히지 않음). Guo (Renesas, 2021) `(2차 자료)` (ISO 26262:2018 기준). `autosar-safety-measures` 46쪽

### proven in use

사용 이력으로 믿음을 얻는 논증이다. 사용 이력이 있는 제품을 원래와 다른 환경에서 쓰려 할 때 필요하다고 Schabe와 Braband가 적고, 환경, 비교하는 부품, 고장과 사용 시간의 기록이 갖춰져야 한다고 한다.

- 주의: 환경이 바뀌면 이력에 기댄 논증은 무효가 된다 (두 저자의 해석이고 Ariane 501 조사 보고서의 결론은 아니다). IEC 61508의 proven in use는 하드웨어의 무작위 고장률을 위한 것이고 체계적 능력의 요구를 대신하지 않는다고 시험 인증 회사 Intertek의 글이 설명한다 `(2차 자료)` (판을 밝히지 않음. 한 회사의 글 하나).
- 근거: Schabe와 Braband, "Basic requirements for proven-in-use arguments" (arXiv:1511.01839, 2015) 1쪽, 6-7쪽 (웹에서 읽음, 2026-11-23). Intertek (2026)

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

## 플랫폼

### hardware-software interface

소프트웨어와 하드웨어가 만나는 신호를 하나씩 적은 명세다. 신호마다 단위와 범위, 켠 직후의 값, 고장이 났을 때 소프트웨어에 어떻게 보이는가, 누가 진단하는가를 적는다. 소프트웨어의 요구사항이 뜻으로 적은 것 (브레이크를 밟았으면)과 코드가 읽는 것 (pin의 전압) 사이를 잇는다.

- 주의: ISO 26262가 이 문서에 무엇을 요구하는지는 이 책이 확인하지 못했다 `(확인 필요)`. 여기의 풀이는 예제의 문서 (`example/drive-torque/docs/hsi.md`)가 담은 것이다.

### lockstep

두 core가 같은 소프트웨어를 나란히 실행하고, 같은 입력에서 나온 출력을 견주는 방식이다. processor의 고장으로 계산이 틀리는 것을 알아채는 데 쓴다.

- 주의: 풀이는 항공의 multicore 지침에서 가져왔다. 자동차용 MCU가 이 방식을 어떻게 쓰는지는 확인하지 못했다.
- 근거: `easa-amc-20-193` 2쪽

### OS-Application

AUTOSAR의 OS가 보호를 나누는 단위다. task와 interrupt 처리 루틴 등을 묶은 것이다. trusted로 둔 것에는 memory 보호와 감시를 끌 수 있다.

- 근거: `autosar-safety-measures` 13쪽

### priority inversion

낮은 우선순위의 task가 자원을 쥔 채 중간 우선순위의 task에 밀리는 동안, 그 자원을 기다리는 높은 우선순위의 task도 함께 멈추는 문제다.

- 근거: `nasa-gb-8719-13` 243쪽

### WCET (worst-case execution time)

가장 나쁜 경우의 실행 시간이다. multicore에서는 다른 core의 소프트웨어 때문에 크게 늘 수 있다.

- 근거: `faa-ac-20-193` 7쪽, 10-11쪽

### interference channel

multicore 프로세서에서, 함께 쓰는 자원 (cache, memory, interconnect) 때문에 소프트웨어 사이에 간섭이 생길 수 있게 하는 플랫폼의 성질이다. 항공의 지침이 쓰는 말이다.

- 근거: `faa-ac-20-193` 4쪽

### safety net

오동작의 원인과 상관없이 동작하는, 프로세서 바깥의 완화 수단이다. 이 책의 예제에서는 외부 watchdog이 이 자리에 있다.

- 근거: `faa-ac-20-193` 5쪽

## 차량의 전자 장치

### ECU (electronic control unit)

차량의 제어기다. 이 책의 예제에서 구동 토크를 정하는 제어기는 VCU (vehicle control unit)라고 부른다. 미국 정부의 보고서는 같은 자리의 제어기를 EV PCM이라고 부른다.

- 근거: `nhtsa-etc-ev-fsa` 33쪽

### inverter

배터리의 직류를 모터가 쓰는 교류로 바꾸고 모터의 전류를 제어하는 장치다. 이 책의 예제에서는 item 밖에 있다.

- 근거: `nhtsa-etc-ev-fsa` 33-34쪽

### CAN, bus-off

CAN은 차량의 제어기를 잇는 bus다. frame은 identifier를 싣고, identifier의 값이 작을수록 우선순위가 높다. 오류를 되풀이하는 노드가 스스로 bus에서 물러나는 것을 bus-off라고 한다.

- 근거: CAN in Automation의 공개 페이지 "CAN CC" (https://www.can-cia.org/can-knowledge/can-cc, 2026-11-23에 봄)

### DTC (diagnostic trouble code), MIL

DTC는 제어기가 고장을 찾았을 때 남기는 고장 코드다. MIL (malfunction indicator light)은 계기판의 고장 표시등이다. 둘은 고장의 기록이고 고장 자체가 아니다.

- 근거: `nhtsa-etc-ev-fsa` 35쪽. `nasa-toyota-ua-report` 81쪽

### SW-C, RTE, complex driver

AUTOSAR Classic의 말이다. SW-C는 하드웨어에 독립인 응용의 부품이고, RTE는 부품 사이로 값을 옮기는 층이며, complex driver는 입출력에 직접 닿는 부분이다.

- 근거: `autosar-safety-measures` 11쪽, 60쪽
