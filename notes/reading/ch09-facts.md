# 9장 근거 문서에서 뽑은 사실

읽은 날: 2026-11-23. 쪽은 PDF 파일의 몇 번째 쪽인지다 (인쇄된 쪽 번호와 다를 수 있다). 인용은 그 쪽을 찾기 위한 표지다.
`(기억)`은 문서에 없고 읽는 이의 기억에서 나온 것이라 근거가 아니다. 이 파일에는 `(기억)` 항목을 넣지 않았다.
받은 문서는 ISO 26262 2018년 판 원문을 담지 않는다. 문서가 규격을 말하는 곳은 그 문서가 기준으로 삼은 판을 비고에 적었다.

## 1. autosar-safety-measures (AUTOSAR CP R25-11, 4장 Hardware Diagnostics 외)

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| F09-001 | 65 | 4장은 MCU가 안전 관련 시스템에서 요구하는 integrity를 이루려면 하드웨어와 소프트웨어 양쪽에 안전 기구와 수단이 필요하다고 시작한다 | "functional safety mechanisms and measures in hardware and software is required" | AUTOSAR의 설명서. 표는 ISO 26262-5 Annex D를 가리킨다 (72쪽 참고문헌에 2018년 판 표기) |
| F09-002 | 65 | Core Test의 목적은 처리 장치의 고장 중 틀린 결과를 내는 것을 소프트웨어 시험으로 찾는 것이다. MCU 시동과 실행 중에 쓴다 | "Core Test performs test by software of processing units during microcontroller start-up and runtime." | |
| F09-003 | 65 | 표 4.1은 처리 장치의 부분 (ALU data path, 레지스터와 내부 RAM, 주소 계산, 인터럽트 처리, 제어 논리, 설정 레지스터)을 ISO 26262 쪽 진단 범위 산정 대상으로 나열하고 Core Test 요구와 짝짓는다. 제어 논리와 설정 레지스터에는 짝이 없다 ("-") | "Memory Management/Protection Unit (MMU/MPU)" | 문서가 "preliminary mapping"이라고 쓴다. MPU 시험이 주소 계산 항목 아래에 있다 |
| F09-004 | 66 | Core Test Driver는 MCAL에 있고 중간 계층 없이 core에 직접 접근한다. 시험하는 기능 블록에 드라이버가 독점으로 접근할 수 있다고 가정한다 | "can be accessed by the Core Test Driver exclusively" | |
| F09-005 | 66 | 시험을 어떤 조합과 순서로 돌릴지는 드라이버를 쓰는 쪽이 정한다. 메모리와 bus 인터페이스, 인터럽트 컨트롤러의 오류는 DEM에 보고하지만 CPU 안의 오류는 믿을 수 있게 보고하지 못한다 | "Errors inside the CPU (e.g. ALU, Prefetch queue, registers) cannot be reliably reported to DEM" | |
| F09-006 | 66 | 한계 1: transient fault와 intermittent fault는 Core Test가 다루지 않고 믿을 만하게 찾지도 못한다. 정적 하드웨어 오류를 찾는 용도다 | "Transient faults are not covered by Core Test." | |
| F09-007 | 66 | 한계 2: 시험 중 core 자원을 독점해야 하는데 AUTOSAR 상위 계층에는 이를 관리하는 요소가 없어, 실행이 시동 때로 한정될 수 있다 | "Core Test implementations may be limited to execution during start-up/power-up." | |
| F09-008 | 67 | 한계 4: CPU 자체의 고장은 같은 고장 난 CPU가 처리하므로 믿을 수 있게 보고하지 못한다 | "as they are being processed by the same faulty CPU" | 한계 3은 시험 결과를 시험을 돌린 core만 볼 수 있다는 것 |
| F09-009 | 67 | RAM Test의 목적은 휘발성 메모리를 망가뜨릴 수 있는 permanent failure를 찾는 것이다 | "detect permanent failures which can cause corruption in the volatile memory" | |
| F09-010 | 68 | 휘발성 메모리 고장 모델별 coverage를 세 단계로 나눈다. Low 60% (stuck-at), Medium 90% (d.c. fault model과 bit cell의 soft error model), High 99% (같은 모델에 더 높은 coverage) | "High Coverage (99%):" | ISO 26262-5 Annex D Table D.1을 따른 표. 60/90/99는 이 표에서만 읽었다 |
| F09-011 | 68 | 어느 coverage가 필요한지는 ECU의 안전 분석이 정하고, 알고리즘은 compile 시점에 고르며 실행 시점에 그 가운데서 고를 수 있다 | "An ECU safety analysis must be performed to determine which RAM Test diagnostic coverage rate (Low, Medium or High) is required." | |
| F09-012 | 68 | RAM Test는 셀의 물리적 상태를 시험하며 내용을 시험하는 것이 아니다. 레지스터용 RAM도 시험한다. 알고리즘은 파괴형과 비파괴형, foreground와 background 시험이 있다 | "it is not intended to test the contents of the RAM" | |
| F09-013 | 69 | 비파괴 시험은 시험 구간의 내용을 저장했다가 되돌린다. 시험 중 다른 소프트웨어와 하드웨어 (NMI, DMA, 다른 core)가 그 구간을 바꾸면 안 되므로 시동, sleep, shutdown 단계로 한정될 수 있다 | "execution of RAM Test may be limited to the power-up/sleep/shutdown phase of a microcontroller" | |
| F09-014 | 69 | RAM Test도 transient와 intermittent fault는 다루지 않는다. 그런데 68쪽의 coverage 표에는 "Soft error model for bit cells"가 Medium과 High로 올라 있다 | "Transient faults and intermittent faults are not covered and cannot be reliably detected by RAM Test." | 두 쪽의 서술이 어떻게 맞물리는지 문서가 설명하지 않는다 |
| F09-015 | 18 | MPU로 memory partitioning을 한다. MPU 설정은 supervisor mode에서만 할 수 있다. core 안의 MPU는 그 core의 접근만 제어하고 DMA와 다른 core는 제어하지 않는다 | "Other Bus Masters, such as DMA controllers and additional Cores, are not controlled by this particular MPU instance." | |
| F09-016 | 63 | e-Gas monitoring 개념 안에서 감시 소프트웨어가 Complex Driver에서 A/D 변환기를 정상 취득을 방해하지 않고 시험하고, 안전 관련 actuator를 직접 시험할 수 있어야 한다는 coverage 기준이 있다. 근거는 ADC driver에 영향이 없어서 지원된다는 것이다 | "Testing and monitoring of I/O data and I/O HW" | ADC 시험 알고리즘이나 기준 전압 시험의 내용은 없다. 기준을 만족한다는 것을 보일 뿐이다 |
| F09-017 | 46 | AUTOSAR가 주지 않는 안전 수단 목록에 SEooC의 정의와 dependent failure analysis가 있다 | "The AUTOSAR specification does not define Safety Elements out of Context" | 목록은 "완전하다는 뜻이 아니다"라고 한다 |

## 2. nasa-gb-8719-13 (NASA Software Safety Guidebook, 2004)

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| F09-020 | 93 | 우주 방사선, EMI, 방전, 충격이 CPU를 손상시킬 수 있으므로 CPU self-test를 보통 boot 때 돌려 프로세서의 동작을 확인하고, 실패하면 safe state로 간다 | "A CPU self-test, usually run at boot time, can verify correct operations of the processor." | Doug Brown의 목록을 옮긴 것 (4.6절). 인쇄 쪽 92 |
| F09-021 | 93 | ROM, EEPROM, flash의 무결성은 실행 전에 확인하고 보통 CPU self-test 뒤에 한다. 스스로 프로그램을 바꾸는 시스템이면 주기적으로 한다 | "then the tests should be run periodically" | |
| F09-022 | 93-94 | watchdog timer는 보통 하드웨어이고, 제때 건드리지 않으면 CPU를 reset한다. 무한 loop에서는 loop마다 한 번 건드린다. interrupt로 건드리지 말라고 한다 | "Do NOT use an interrupt to tickle the watchdog." | 인용은 94쪽. 이유는 interrupt가 살아 있어도 실제 process가 막힐 수 있다는 것 |
| F09-023 | 94 | 중요한 변수는 서로 다른 저장 매체나 분리된 메모리에 여러 사본을 두고 쓸 때 비교한다. 셋 중 둘 투표, 일치가 없으면 기본값을 쓴다. 변수 묶음에 CRC를 쓸 수도 있다 | "critical variables can be grouped, and a CRC used to verify they are not corrupted" | |
| F09-024 | 93 | ROM이나 RAM의 안 쓰는 곳을 halt나 illegal instruction 패턴으로 채우고, trap vector가 safe state로 가게 하면 잘못 뛴 뒤 동작을 막을 수 있다 | "Filling ROM or RAM with a known pattern, particularly a halt or illegal instruction" | |
| F09-025 | 95 | 값을 메모리, 표시 장치, 하드웨어에 쓴 뒤 다른 함수가 다시 읽어 맞는지 확인하는 read-back을 권한다 | "Use read-backs to check values." | 인쇄 쪽 94 |
| F09-026 | 96 | 소프트웨어 요구에 없으면 소프트웨어에 영향을 주는 하드웨어 고장의 목록을 만들고, 하드웨어 엔지니어와 시스템 엔지니어가 검토하게 한다. 소프트웨어는 이 고장에 맞게 반응해야 한다 | "Create a list of possible hardware failures that may impact the software" | |
| F09-027 | 97 | 중요한 I/O 포트와 그렇지 않은 포트의 주소가 충분히 달라, 주소 bit 하나가 고장 나도 중요한 기능에 닿지 않게 하라고 한다 | "such that a single address bit failure does not allow access to critical functions or ports" | ISS의 SSP 50038에서 가져온 제안 |
| F09-028 | 98 | 하드웨어나 다른 소프트웨어의 값으로 판단하는 논리는 전부 1이나 전부 0이라는 값에 기대지 말고 특정한 bit 패턴을 쓰라고 한다 | "should not be based on values of all ones or all zeros" | |
| F09-029 | 118 | RAM 시험은 보통 전원을 켤 때 하고, single event upset이나 RAM 문제가 생기기 쉬운 환경에서는 주기적 확인이 필요할 수 있다 | "Periodic verification of memory functionality may be required" | 인쇄 쪽 117 |
| F09-030 | 22 | 위험의 원인이 processor 고장이면 위험 통제는 다른 processor에 있어야 한다. 고장 난 processor가 자기 소프트웨어의 대응 능력도 해치기 때문이다 | "the hazard control must be located on another processor" | |
| F09-031 | 22 | 컴퓨터 하나는 본래 고장 허용이 0이다. 컴퓨터가 안전하게 고장 난다고 믿는 것은 오해이고, NASA의 경험으로는 위험한 고장 모드도 있다 | "A single computer is inherently zero failure tolerant." | |
| F09-032 | 115 | NASA 우주 시스템은 주로 하드웨어로 failure tolerance를 얻지만, 소프트웨어 설계가 나쁘면 하드웨어의 failure tolerance를 무력화할 수 있다 | "improper software design can defeat the hardware failure tolerance and vice versa" | |
| F09-033 | 144 | 소프트웨어나 논리적 방벽은 하드웨어 고장이나 EMI와 방사선의 영향으로 무력해질 수 있어서 NASA에서는 hazard control이 아니라 mitigation으로 본다. FCR 사이의 독립은 별도 processor에 올려 얻는 것이 보통이다 | "can be defeated by hardware failures or EMI/Radiation effects" | 인쇄 쪽 143 |

## 3. ifa-report-2-2017e (IFA Report 2/2017e, 기준 EN ISO 13849-1:2015, 기계 분야)

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| F09-040 | 39 | 안전 관련 제어 부품의 품질은 Performance Level (PL) 다섯 단계로 나타내고, 각 PL은 시간당 평균 위험측 고장 확률 PFHD의 범위에 대응한다. PFHD 외에도 systematic failure 대책이 있어야 그 PL이 된다 | "average probability of a dangerous failure per hour" | 기계 규격의 지표다. IEC 61508의 PFH와 같은 지표인지는 이 문서가 말하지 않는다 |
| F09-041 | 44 | random 부품 고장과 달리 systematic failure는 설계, 제조 공정, 운용 방법, 문서를 바꿔야만 원인을 없앨 수 있다. 명세나 설계의 오류, 수정 중에 생긴다 | "systematic failures have causes that can be eliminated only by" | |
| F09-042 | 46 | systematic failure를 피하는 수단과 다루는 수단의 목록 (그림 6.4)에 program sequence monitoring (소프트웨어), automatic tests, redundant 또는 diverse hardware가 있다 | "Program sequence monitoring (for software)" | EN ISO 13849-1 Annex G를 옮긴 그림 |
| F09-043 | 50 | Category 3는 단일 고장이 있어도 안전 기능이 수행되고, 일부 고장은 찾지만 모두 찾지는 못해 찾지 못한 고장이 쌓이면 안전 기능을 잃을 수 있다. Category 4는 이 쌓임도 견딘다 | "Accumulation of undetected faults can lead to the loss of the safety function." | 표 6.2 |
| F09-044 | 51 | Category 2는 안전 기능을 기계 시동 때와 위험 상황이 시작되기 전, 필요하면 운전 중 주기적으로 시험한다. 시험은 자동으로 시작할 수 있고, 고장이면 안전 상태로 가는 출력을 내야 한다 | "at start-up of the machine" | PLr c까지는 경고만 주는 것도 허용될 수 있다고 한다 |
| F09-045 | 52 | 시험 사이에 안전 기능이 알아채지 못하게 고장 날 수 있으므로 시험 간격은 중요한 변수다. 시험 장치 자체가 먼저 고장 날 수도 있다. 그래서 Category 2는 PL d까지로 제한된다 | "the interval between tests is a critical parameter" | |
| F09-046 | 52 | 시험 장치의 진단 결과를 평가하는 부분은 보통 기능 channel 밖에 (예: 별도의 watchdog) 두어야 한다. 분리 없는 on-chip watchdog이나, 소프트웨어가 de-energizing 신호로 출력을 직접 쓰는 시험 장치는 받아들일 수 없다 | "an on-chip watchdog without the separation described in IEC 61508-2, Annex E" | IEC 61508-2 Annex E를 가리킨다 |
| F09-047 | 53 | 단일 고장 허용이 꼭 두 channel을 뜻하지는 않는다. 그러나 단일 하드웨어 위에 소프트웨어를 중복하는 논리적 두 channel은 하드웨어 고장에 대한 단일 고장 허용을 보통 주지 못한다 | "will however not generally offer single-fault tolerance of hardware failures" | |
| F09-048 | 55 | 실제 시스템에서는 이론상 가능한 고장이 끝없으므로 관련 있는 고장만 평가한다. 고장 배제는 발생이 기술적으로 매우 희박하거나 일반적으로 인정된 경험이 있을 때 한다. 배제하면 그 부품의 MTTFD와 DC를 따지지 않는다 | "failure rates (MTTFD) and monitoring measures (DC) need not be considered for such components" | 고장 목록은 EN ISO 13849-2 |
| F09-049 | 55 | 원인이 서로 다른 두 개 이상의 고장이 동시에 나는 것은 극히 드물다고 보아 고려하지 않는다. 2차 고장은 처음 고장과 한 단일 고장으로, 공통 원인의 다중 고장도 같이 평가한다 | "need not therefore be taken into account" | |
| F09-050 | 55 | MTTFD는 부품이 위험측으로 고장 나기까지의 평균 시간이고 보통 년으로 쓴다. 상수 고장률에서 MTTFD = 1/lambda_D이고, 고장률의 단위는 FIT (10^-9/h)다 | "generally indicated in years" | 수식은 원문의 기호를 ASCII로 바꿨다 |
| F09-051 | 55 | 평균 값이므로 보장된 최소 수명이 아니다. 개별 부품의 기댓값은 같은 종류 부품 다수의 평균과 같다고 본다 | "The value is not therefore a guaranteed minimum lifetime" | |
| F09-052 | 56 | 부품의 고장 자료는 제조사의 데이터시트를 먼저 쓰고, 없으면 데이터베이스를 쓴다. 데이터베이스는 위험측과 안전측을 나누지 않으므로 평균 절반이 위험측이라고 가정한다. parts count 방법에서는 MTTFD를 MTTF의 두 배로 둔다 | "only half of all failures are dangerous" | 56쪽 |
| F09-053 | 57 | channel의 MTTFD를 Low (3-10년), Medium (10-30년), High (30-100년)로 나눈다. 평균 수명이 3년 아래는 안전 부품으로 합리적이지 않다고 본다. Category 4만 100년 넘는 값 (2,500년까지)을 허용한다 | "lifetime of less than three years is deemed not reasonable for safety engineering components" | |
| F09-054 | 57 | DC는 모든 위험측 고장 중 찾은 위험측 고장의 비율이다. 기준은 부품, 블록, 전체 SRP/CS일 수 있고 전체일 때는 평균 DCavg다 | "defined as the proportion of detected dangerous failures among all conceivable dangerous failures" | |
| F09-055 | 58 | DC를 FMEA로 정밀하게 계산하거나, 표준 시험 수단에 대해 거친 값 0%, 60%, 90%, 99% 네 개를 쓴다. 이 값들로 DC 네 단계 (None, Low, Medium, High)를 만든다 (60-90 Low, 90-99 Medium, 99 이상 High) | "a coarse system comprising four key values (0%, 60%, 90% and 99%)" | 단계 구분은 60쪽의 표 6.4 |
| F09-056 | 58 | 위험측 고장을 찾는 것은 시작일 뿐이고, 안전 상태가 제때 시작되어야 한다. Category 2에서는 정상 shut-off 요소의 고장을 시험이 찾았을 때 안전 상태를 만들고 유지할 두 번째 shut-off 요소가 필요하다 | "a safe state that presents no further hazard must be initiated in time" | |
| F09-057 | 58 | 시험 빈도가 부족하면 시험이 위험 사건보다 늦어 안전하다는 착각을 만든다. Category 2는 시험 빈도를 요구 빈도의 100배 이상 (예외적으로 25배)으로 하거나 요구 때 바로 시험하고 안전 상태에 도달하는 시간이 위험까지의 시간보다 짧아야 한다 | "may therefore create a false sense of safety" | 25배일 때 PFHD에 1.1을 곱한다는 말은 39쪽 |
| F09-058 | 58-59 | IEC 61800-5-2의 최소 시험 빈도 (중단 없이 시험할 수 없을 때): PL d Category 3은 1년에 한 번, PL e Category 3은 3개월에 한 번, PL e Category 4는 하루 한 번이다 | "one test per day for PL e in Category 4" | 원문은 이를 다른 방법이 없을 때의 최소 요구라고 한다 |
| F09-059 | 59 | 전자 시스템의 processor와 memory 시험은 부하가 적게 더 자주 돌릴 수 있다. 실무에서는 Category 3은 최소 shift당 한 번, Category 4는 시간당 한 번이 적당했다 | "testing at least once per shift for Category 3 has proved suitable" | 시간당 한 번은 이전 규격 EN 954 시절에 정했다고 한다 |
| F09-060 | 59 | 프로그래머블 논리에서 DC 60% 넘게 요구하면, 가변 메모리, 불변 메모리, 처리 장치 각각에 DC 60% 이상의 수단 하나 이상을 요구한다 | "at least one measure for variable memory" | |
| F09-061 | 60 | DCavg는 MTTFD로 가중한 평균이다. 신뢰도 높은 부품은 시험에 덜 의존하기 때문이다. bar chart에서는 DCavg를 단계의 아래 key 값 (0, 60, 90, 99)으로 내림해 쓴다 | "very reliable parts (with a high MTTFD) are less reliant upon effective tests" | |
| F09-062 | 60 | CCF는 공통 원인으로 생기는 관련 위험측 고장이다 (예: 중복 channel 둘 다). 규격은 여덟 대책의 점수 (물리적 분리 15, 다양성 20 등)를 주고 Category 2, 3, 4에 최소 65점을 요구한다 | "attributable to a common cause" | 점수 합계 100 |
| F09-063 | 60-61 | 65점은 beta factor 2%에 해당한다. 중복 구조의 이점은 beta가 10% 이상이면 거의 사라지고, 2% 이하면 CCF의 영향이 정당화할 수준으로 준다. IEC 61508-6 Annex D의 beta-factor 모델을 언급한다 | "a beta factor of no more than 2% reduces the relevance of common cause failures to a justifiable level" | |
| F09-064 | 61 | bar chart는 Category, DCavg 단계, channel의 MTTFD로 PL을 읽는 방법이다. 그림의 PFHD 눈금은 PL a가 10^-4 쪽에서 PL e가 10^-8 쪽까지다 | "PFHD Average probability of dangerous failure per hour" | 값은 그림의 눈금이다. 정밀한 PFHD는 Annex K나 SISTEMA를 쓰라고 한다 |
| F09-065 | 88 | IEC 61508-2의 Annex A Table A.1에 CPU, RAM, ROM, clock 고장의 상세가 있다고 이 보고서가 알려 준다 (이 책이 받은 문서에는 61508 원문이 없다) | "precise details of faults in CPU, RAM, ROM and clock" | |
| F09-066 | 88 | 집적도가 높은 부품 (microprocessor, DSP, ASIC, FPGA, SoC)의 fault model은 대체로 추상적이다. 표준 진단 요소로 CPU self-test (BGIA Report 7/2006), RAM self-test (Galpat, March, Checkerboard), 상용 watchdog과 감시 모듈을 쓰는 것이 낫다고 한다 | "generally somewhat abstract in its characterization" | |
| F09-067 | 285 | DC는 self-test와 감시 수단의 효과를 재는 값이다. 고장을 safe (S), dangerous detectable (DD), dangerous undetectable (DU)로 나누고 DC는 DD를 위험측 전체로 나눈 비율이다. 시험 장치가 아니라 시험 받는 블록의 값이다 | "DC is a measure of the effectiveness of a control system" | Annex E |
| F09-068 | 286 | DCavg를 key 값으로 내림한다 (예: 80%는 60%로). 시험을 하는 쪽이 자기 자신인지는 상관없으나, 시험하는 쪽과 받는 쪽 사이에 독립이 보장될 때만 시험이 유효하다. 고장을 찾아도 안전 상태가 되지 않으면 DC는 0%다 | "rounded down to the next lowest of the four key values" | 독립에 관한 말은 287쪽 첫머리 |
| F09-069 | 286 | 표 E.2의 예: cyclic test stimulus by dynamic change monitoring 90%, plausibility check/readback/cross-monitoring은 신호 변화의 빈도에 따라 0-99%, direct monitoring 99% | "Cyclic test stimulus by dynamic change" | |
| F09-070 | 288 | 표 E.2 (전자 부분): start-up self-test 90% (latent fault를 찾으며 기법에 따라 DC가 달라진다), program sequence monitoring (시간만 60%, 시간과 논리 90%), 불변 메모리 signature 한 word (8 bit) 90%와 double word (16 bit) 99% | "To detect latent faults, DC depends on the testing technique" | 이 책의 flash CRC 항목과 가장 가까운 서술. CRC라는 말은 이 문서에 없다 |
| F09-071 | 288 | 가변 메모리: 중복 데이터 비교 60%, 읽기와 쓰기 가능 확인 60%, 수정 Hamming code의 RAM 감시 또는 RAM self-test (galpat, Abraham) 99%. 처리 장치: 소프트웨어 self-test 60-90%, coded processing 90-99% | "RAM monitoring with modified Hamming code or RAM self-test" | |

## 4. iec-61508-overview-slides (IEC 61508 개요 발표, 2022)

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| F09-080 | 12 | 고장을 둘로 나눈다. A는 열화 기구에서 나오는 위험측 random hardware failure, B는 위험측 systematic failure다 | "Random Hardware Failures in a dangerous mode" | |
| F09-081 | 12 | systematic failure의 예에 잘못된 명세, 안전 요구의 누락, systematic hardware failure mechanism, 소프트웨어 오류, 사람의 실수, EMI, 유지보수와 수정이 있다. 하드웨어의 고장도 systematic일 수 있다 | "Systematic hardware failure mechanisms" | EMI를 systematic 쪽에 넣은 것은 발표자의 분류다 |
| F09-082 | 13 | 1970년대 설계는 random hardware failure에 집중했고, 복잡한 시스템에서는 systematic failure에 훨씬 더 신경 써야 했다. SIL 개념이 생긴 이유가 systematic failure의 중요성이라고 한다 | "much more attention had to be taken of Systematic Failures" | |
| F09-083 | 9 | safety integrity는 정해진 조건과 기간에 안전 관련 시스템이 안전 기능을 수행할 확률이다. random hardware failure와 소프트웨어 같은 systematic failure 둘의 위험측 고장을 포괄한다. 높은 integrity는 낮은 위험측 고장률이다 | "A high safety integrity means a low dangerous failure rate" | |
| F09-084 | 16 | SIL마다 정량 Target Failure Measure와 risk reduction 범위가 있다 (SIL 1은 10 초과 100 이하, SIL 4는 10,000 이상 100,000 이하). 슬라이드는 이 값을 PFD나 PFH라 부르지 않는다 | "there is a quantified Target Failure Measure" | 지표 이름 PFD, PFH, SFF, HFT는 이 슬라이드에 나오지 않는다 |
| F09-085 | 20 | HSE 연구에서 제어 시스템 고장의 원인은 명세 44%, 변경 20%, 설계와 구현 15%, 운용과 유지 15%, 설치 6%다. 60% 넘는 고장이 운전에 들어가기 전에 이미 시스템에 있었다 | "of failures were built into the safety-related systems" | 34개 사고, 화학과 기계 분야 연구 |

## 5. nhtsa-etc-ev-fsa (NHTSA, 전기차 ETC 기능안전 평가, 기준 ISO 26262 FDIS 2011)

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| F09-090 | 73 | 일반 요구 1: 제어기는 power-on 시험, 주기적 시험 또는 연속 감시로 안전에 중요한 변수의 올바름과 핵심 요소의 무결성을 확인해야 한다 (ASIL B/C/D) | "perform power-on tests, periodic tests, or continuous monitoring tests" | 원문 쪽 번호 57. 요구에 TBD 값이 많다. 예시 요구이지 규격의 요구가 아니다 |
| F09-091 | 74 | 토크 명령 전에 EV PCM과 TICM의 건강 확인이 필요하다. 건강 확인에는 RAM, ROM, EEPROM 시험, ADC 시험, shutdown 시험이 들 수 있다 | "Random-access memory/read-only memory/electrically erasable programmable read only memory tests" | |
| F09-092 | 74 | 주기적 시험의 빈도는 FTTI와 fault reaction time interval로 정한다. 주기적 self-test가 실패하면 TBD ms 안에 safe state로 간다 | "The frequency of the periodic tests is to be selected based on the FTTI" | |
| F09-093 | 74 | 한 제어기가 다른 제어기에 정해진 입력을 주고 정해진 시간 안에 맞는 답이 오는지 보는 quizzer (seed-and-key)를 microcontroller의 건강 확인으로 설명한다. 보통 ASIL C나 D의 redundancy 기법이라 한다 | "confirm the sanity (health) of a microcontroller" | 각주 24 |
| F09-094 | 74 | 하드웨어 architectural single-point fault와 latent fault 지표 목표를 안전 목표마다 보여야 한다 (ASIL B/C/D). 중복 요소는 공통 원인 고장에 대해 확인하고 전원과 통신 경로가 서로 영향을 주지 않아야 한다 (ASIL C/D) | "single-point fault and latent fault metrics targets per ISO" | SPFM, LFM이라는 이름은 이 문서에 없다 |
| F09-095 | 76 | 구성 요소와 연결의 진단은 안전 목표의 ASIL에 맞는 coverage (low, medium, high)로 하고, 하드웨어 architectural metrics 목표를 따른다 | "ISO 26262 diagnostics coverage guidelines for low, medium, and high" | |
| F09-096 | 67 | 안전 전략 요소: main controller의 건강을 보조 processor로 확인하고, latent fault는 주기적 점검으로 줄이고, 낮은 전압 전원이 safe state까지 이어지게 한다 | "mitigate latent faults through periodic checks" | |
| F09-097 | 67 | 통신 신호의 오류 검출 기법을 quality factor라 부르고 checksum, parity, CRC, error correcting code를 든다 | "checksums, parity bits, cyclic redundancy checks, error correcting codes, etc." | 각주 22 |
| F09-098 | 73 | 제어기의 하드웨어 고장이 나면 첫째 완화 전략은 이상을 알아채고 safe state로 가는 것이다. limp-home이면 운전자에게 알린다 | "detect the abnormality and transition the system to a safe state" | |
| F09-099 | 84 | 토크 전류를 정하는 look-up table의 내용을 시작할 때마다 올바른지 검사한다 (ASIL B/C/D) | "of the tables are to be checked for correctness every time the ACS/ETC is started" | |
| F09-100 | 93 | EV PCM은 clock이나 내부 timing 신호가 맞는지 확인해야 한다 (ASIL B/C/D). 방법은 쓰지 않았다 | "verify the correctness of all clock or internal EV PCM timing signals" | |
| F09-101 | 95 | TICM도 같은 요구다 | "verify the correctness of all clock or internal timing signals" | |
| F09-102 | 88 | 저전압 전원은 중복이어야 하고 가장 긴 FTTI보다 길게 공급해야 한다. 전압과 전류는 최소, 최대, ripple, transient, overshoot의 품질 변수를 만족해야 한다 | "The ACS/ETC is to have a redundant low voltage power supply." | 전압 감시 회로의 서술은 없다 |

## 6. koopman-toyota-ua (Koopman 발표, 2014, 원고 쪽 전문가의 주장)

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| F09-110 | 29 | 방사선에 맞아 bit가 뒤집히는 soft error는 메모리, 제어 논리, CPU 레지스터 등 chip 위 어디에나 생긴다. 소프트웨어 결함도 메모리를 망가뜨릴 수 있고 그 결과는 충돌이 아니라 틀린 출력일 수 있다 | "bits flip values due to radiation strikes" | Koopman의 주장. 인용 자료 [Mariani 2003]에 기댄다 |
| F09-111 | 30 | chip당 10,000-100,000 시간에 한 번 하드웨어 고장이 나고 그중 약 2%가 위험하다고 어림한다. 유리한 값은 100만 시간당 0.2회이고 Camry 한 해 생산분은 연 31회라고 계산한다 | "HW faults every 10,000 to 100,000 hours per chip" | 어림값이다. 출처 [Obermaisser]. 슬라이드가 "Approximate numbers"라고 쓴다 |
| F09-112 | 31 | 하드웨어 bit 하나가 뒤집혀 task 하나가 죽을 수 있다. 하나의 Fault Containment Region은 자기 고장 모드를 모두 스스로 감시할 수 없고 감시가 고장에 같이 손상될 수 있다 | "A single FCR can't self-police all of its own failure modes" | |
| F09-113 | 44 | watchdog은 count-down timer가 0이 되면 CPU를 reset하고 CPU가 주기적으로 kick한다. timer tick interrupt에서 kick하면 나쁜 신호이고, task 하나라도 죽으면 kick을 막아야 한다 | "Any single task death must inhibit watchdog kick" | |
| F09-114 | 45 | Toyota ETCS에서는 watchdog을 하드웨어 timer 서비스 루틴이 kick하고 1 ms task의 죽음만 감지한다고 주장한다. throttle 각도 계산과 대부분의 failsafe가 있는 Task X는 감지하지 못한다 | "Watchdog kicked by a hardware timer service routine" | NASA 보고서의 서술 (F09-132)과 다르다. 법정 증언 자료에 기댄 주장 |
| F09-115 | 10 | NASA가 2005년식에 RAM의 error correcting code를 인정했으나, 실제로는 RAM에 EDAC가 없었다고 주장한다. Exponent 보고서는 SEC만 주장하고 SECMED는 아니라고 한다 | "But, actually no EDAC on RAM for 2005MY vehicle" | 원고 쪽 증인 증언을 인용한 주장이다. NASA 보고서 146쪽은 EDAC가 있다고 쓴다 |

## 7. nasa-toyota-ua-report (NASA NESC, Toyota 급가속 조사, 2011)

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| F09-130 | 144 | throttle motor를 구동하는 H-Bridge는 Main CPU와 Sub CPU의 출력이 모두 있어야 동작하고, CPU reset 중에는 출력이 low로 끌려 모터 구동이 꺼진다. Sub CPU가 과전류에서 자기 입력을 거둘 수 있다 | "able to power the throttle motor only when both CPUs outputs are available" | |
| F09-131 | 145 | 전원 ASIC이 전압 threshold를 감시해 전압이 충분해질 때까지 두 CPU를 reset 상태로 잡는다. 두 CPU 사이 heartbeat 오류나 낮은 전압이 reset을 일으킨다. heartbeat는 소프트웨어가 만들고 CPU 하드웨어와 소프트웨어가 정상이라는 외부 표시다 (146쪽) | (원문이 이미지라 인용 없음) | 이 쪽은 글자 층이 없다. OCR로 읽었고 quotecheck로 대조할 수 없다 |
| F09-132 | 146 | Main CPU와 Sub CPU에 각각 하드웨어 watchdog이 있다. 소프트웨어가 다시 시작하지 않으면 CPU 하드웨어가 reset하고, 이를 시작하는 함수는 가장 낮은 우선순위 task에서 돈다. 그 task가 안 돌면 처리나 timing이 비정상이라는 뜻이다 | "If a watchdog timer expires without being re-initiated by software, the CPU hardware is reset and restarts." | |
| F09-133 | 146 | 하드웨어 EDAC 논리가 메모리의 1 bit 오류는 소프트웨어 실행에 영향 없이 감지하고 고치며, 2 bit 오류는 감지만 하고 고치지 못한다. 소프트웨어 오류는 다루지 않는다 | "error detection and correction (EDAC) logic can detect and correct a hardware error in a memory location for single bit errors" | NASA 보고서의 서술. Koopman 발표 (F09-115)는 이 EDAC의 존재를 부정한다 |
| F09-134 | 146 | 소프트웨어가 중요한 데이터의 일부를 mirroring한다. 쓸 때 둘째 위치에 보수 (complement)를 쓰고 읽을 때 대조해 실패하면 기본값을 쓴다. 두 CPU 사이 직렬 통신에는 data check와 retry가 없다 | "a second location is written with the complement of the data" | |
| F09-135 | 147 | 보고서의 정리: 큰 CPU와 소프트웨어 고장은 Sub-CPU와 Main CPU의 점검, watchdog, heartbeat, 전압 감시로 막고, 데이터 손상은 EDAC와 소프트웨어 data mirroring으로 막는다. 내부 소프트웨어 데이터 손상은 시험에서 재현하지 못했다 | "watchdog, heartbeat, and voltage monitoring" | |
| F09-136 | 169 | single event upset은 soft error이고 파괴하지 않으며 논리의 일시 펄스나 메모리 cell과 레지스터의 bit flip으로 나타난다. 파괴적인 hard error에는 single event latchup, MOSFET 소손, gate rupture, frozen bit가 있고 latchup은 보통 전원 reset으로 풀린다 | "Single Event Upsets (SEUs) are soft errors, and non-destructive" | 6.9 External Theories의 6번 이론 |
| F09-137 | 170 | processor와 메모리를 single event effect로부터 지키는 수단은 메모리의 EDAC, 중요 변수의 data mirroring, watchdog, 두 processor가 서로 점검하는 heartbeat다. throttle 전자부는 SOI 기술의 ASIC과 보호 논리로 지킨다 | "Processor and memory protection against single event effects includes EDAC on memory" | |

## 8. nhtsa-safety-standards-assessment (NHTSA/Volpe, 기준 ISO 26262 FDIS 2011)

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| F09-150 | 15 | 이 평가는 ISO 26262의 final draft에 근거한다. JASPAR의 마이크로컨트롤러용 기능안전 handbook이 ISO 26262-5의 하드웨어 architectural metrics 계산을 개선하는 권고를 준다고 알리지만 비교 연구에서는 다루지 않는다 | "metrics calculation in ISO 26262 Part 5 for microcontrollers" | 보고서가 handbook의 내용을 쓰지 않는다 |
| F09-151 | 20 | ISO 26262는 하드웨어 random failure 지표를 비롯한 신뢰성 공학의 개념을 도입했다고 쓴다. 지표의 이름과 정의는 없다 | "ISO 26262 also introduces hardware random failure metrics and other reliability engineering concepts." | |
| F09-152 | 23 | FMEA, FTA, ETA는 random hardware failure에는 정성과 정량으로 잘 맞지만 소프트웨어에는 random failure가 없어 곧바로 적용되지 않는다 | "software does not have random failures like hardware" | 보고서의 주장. 24쪽에도 비슷한 말이 있다 |
| F09-153 | 30 | ISO 26262의 safety measure는 systematic failure를 피하거나 통제하고 random hardware failure를 찾거나 통제하거나 영향을 줄이는 활동이나 기술적 해법이다. safety mechanism의 예로 센서 고장을 감시하는 진단 구성 요소를 든다 | "to detect random hardware failures or control random hardware failures" | 규격 정의의 인용을 보고서가 옮긴 것 |

## 9. avizienis-2004-taxonomy (Avizienis, Laprie, Randell, Landwehr, 2004)

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| F09-160 | 9 | fault를 지속성으로 나눈다. permanent fault는 존재가 시간상 계속된다고 가정하고, transient fault는 존재가 시간상 한정된다 | "presence is bounded in time" | 여덟 관점 중 persistence. 인쇄 쪽 8 |
| F09-161 | 5 | fault는 error를 일으키면 active, 아니면 dormant다. error는 서비스 실패로 이어질 수 있는 상태의 부분이다 | "A fault is active when it causes an error, otherwise it is dormant." | 인쇄 쪽 4 |
| F09-162 | 10-11 | 자연적 hardware fault는 운용 중 내부 (물리적 열화)이거나 외부 (시스템 경계 밖의 자연 현상이 하드웨어 경계로 파고드는 방사선 등)다 | "penetrating the hardware boundary of the system (radiation, etc.)" | 11쪽의 인용. 10쪽은 "natural processes that cause physical deterioration" |
| F09-163 | 24 | 오류 검출에는 정상 서비스 중에 하는 concurrent detection과, 서비스를 멈추고 latent error와 dormant fault를 점검하는 preemptive detection이 있다 | "checks the system for latent errors and dormant faults" | 그림 5.1. 인쇄 쪽 23 |
| F09-164 | 25 | 보상 (compensation)으로 오류를 가리는 masking은 보호 redundancy의 점진적이고 결국 치명적인 손실을 숨길 수 있어서 실제 구현은 오류 검출을 함께 쓴다 | "will conceal a possibly progressive and eventually fatal loss of protective redundancy" | |
| F09-165 | 25 | intermittent fault는 isolation이나 reconfiguration이 필요 없고, 오류가 되풀이되는지로 intermittent인지 알 수 있다 | "intermittent faults do not necessitate isolation or reconfiguration" | |
| F09-166 | 25 | 물리 고장을 견디려고 같은 설계의 channel을 여럿 쓰는 것은 하드웨어 부품이 서로 독립적으로 고장 난다는 가정에 기댄다 | "based on the assumption that hardware components fail independently" | 같은 설계의 channel이 development fault에는 맞지 않는다고 이어진다 |
| F09-167 | 26 | 독립인 줄 알았는데 common-mode 고장이 나면 failure independence coverage가 부족한 것이다. fault tolerance 기구 자체도 고장으로부터 보호되어야 한다 (재귀적이다) | "the occurrence of common-mode failures when independent ones are assumed" | |

## 장 계획이 기대했지만 문서에 없던 것

- SPFM, LFM, PMHF: 받은 문서에 이름이 나오지 않는다. NHTSA EV 보고서 74쪽이 "single-point fault and latent fault metrics targets"라고 풀어 쓸 뿐이고 (F09-094), NHTSA 평가는 "hardware random failure metrics"라고만 한다 (F09-151). 수치 목표와 정의는 없다.
- HFT, SFF, PFD, PFH (IEC 61508): IEC 슬라이드에 나오지 않는다 (F09-084). 비슷한 개념은 IFA 보고서의 Category와 단일 고장 허용 (F09-043, 047), DC (F09-054), PFHD (F09-040)뿐이며 기준은 ISO 13849-1:2015다. 이름을 61508의 것으로 옮기지 말 것.
- lockstep core: 받은 문서에 나오지 않는다. 비슷한 것은 두 processor의 상호 점검 (NASA Toyota 보고서 170쪽)과 보조 processor, quizzer (EV 보고서 67, 74쪽)다.
- MCU safety manual, assumption of use: 받은 문서에 없다. safety element out of context는 AUTOSAR가 정의하지 않는다는 말뿐이다 (F09-017). JASPAR의 마이크로컨트롤러 handbook은 존재만 언급된다 (F09-150).
- 전압 감시와 clock 감시의 방법: EV 보고서가 요구 문장으로 clock 올바름 확인과 전원 품질을 요구할 뿐 (F09-100, 102), 방법이 없다. 전원 ASIC의 전압 감시는 NASA Toyota 보고서의 서술이다 (F09-131, 135). ADC 기준 전압 self-test의 서술은 없고, ADC 시험은 EV 74쪽과 AUTOSAR 63쪽에 이름만 있다.
- flash의 CRC 시험: "CRC"라는 말로는 NASA GB (F09-023, 변수 묶음)와 EV 보고서의 통신 항목 (F09-097)에만 나온다. 불변 메모리의 signature 시험이 DC 90%와 99% (IFA 288쪽)이다. flash 시험의 주기와 시간 예산은 문서에 없다.
- 하드웨어 고장률의 값 (FIT)과 MCU의 DC 표: Koopman의 어림 (F09-111)과 IFA의 FIT 단위 정의 (F09-050)뿐이다. ISO 26262-5 Annex D의 RAM coverage 세 단계는 AUTOSAR의 표에서만 읽었다 (F09-010).
- latent fault의 정의와 숨은 고장을 찾는 주기: IFA의 start-up self-test (F09-070)와 시험 빈도 (F09-057-059), Avizienis의 preemptive detection (F09-163), NASA GB의 ROM 주기 시험 (F09-021)에 흩어져 있다. 지표의 latent 항목 정의는 없다.
- ECC의 구성 (SEC-DED 등): NASA Toyota 보고서가 1 bit 정정, 2 bit 감지를 쓴다 (F09-133). 그 이상은 없다.
