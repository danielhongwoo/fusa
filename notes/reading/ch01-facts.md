# 1장 근거 문서에서 뽑은 사실 (읽기 기록)

작성일 2026-11-22. 대상: plans/ch01-accidents.md. 글이 아니라 "문서에 적힌 것"의 기록이다. 쪽은 PDF 파일의 몇 번째 쪽인지다 (Therac-25만 IEEE Computer 인쇄 쪽).
인용은 영어 원문이며, 곡선 따옴표는 ASCII로 바꿨고 그 밖의 변경은 비고에 적었다. `(기억)`은 문서에 없는 기억이다. 근거로 쓰지 않는다.

## 1. ariane-501-report (Inquiry Board report, 스캔본을 OCR로 읽음)

보고서 자체 쪽 = PDF 쪽 - 4. OCR 텍스트에서 `rn`을 `m`으로 읽은 글자 오류(예: "pattem")는 바로잡아 인용했다. 숫자는 OCR 결과이며 원본 이미지와 대조하지 않았다. "H0"는 OCR에서 "H," 로 나왔다.
공식 조사의 결론: 이 문서 전체. 다툼이 있는 부분: 읽은 쪽에는 없다.

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| F01-001 | 7 | Ariane 5의 SRI(관성 기준 장치)는 Ariane 4에서 쓰던 SRI와 설계, 특히 소프트웨어가 거의 같다. | "practically the same as that of an SRI which is presently used on Ariane 4" | 재사용 |
| F01-002 | 7 | SRI는 하드웨어와 소프트웨어가 같은 두 대가 병렬로 돈다. 하나가 active, 하나가 hot standby이고 OBC가 고장을 감지하면 전환한다. | "two SRIs operating in parallel, with identical hardware and software" | 같은 소프트웨어를 둔 이중화 |
| F01-003 | 7 | 파괴의 사슬: 발사체는 H0+39초쯤 공기역학 하중으로 분해되기 시작했다. 원인은 노즐 최대 편향이고, 이는 OBC가 active SRI(SRI 2)의 데이터로 지시한 것이다. 그 데이터 일부는 비행 데이터가 아니라 SRI 2의 진단 비트 패턴이었다. | "showed a diagnostic bit pattern of the computer of the SRI 2" | 쪽 7-8에 걸친 사슬 |
| F01-004 | 7-8 | 백업 SRI 1은 직전 데이터 주기(72 ms)에 같은 이유로 이미 멈춰 있어 OBC가 전환할 수 없었다. | "had already ceased to function during the previous data cycle (72 milliseconds period)" | 이 문장은 p7 끝에서 p8로 이어짐 |
| F01-005 | 8 | SRI 내부의 소프트웨어 예외는 64비트 부동소수점을 16비트 부호 정수로 변환하다가 값이 범위를 넘어 Operand Error가 난 것이다. 같은 곳의 비슷한 변수 변환은 보호되어 있었다. | "were not protected from causing an Operand Error" | 보호되지 않은 변환 |
| F01-006 | 8 | 오류가 난 곳은 정렬(alignment) 기능으로, 이륙 전에만 의미가 있다. 이 기능은 이륙 뒤에도 약 40초 계속 돈다. 이 시간 배치는 Ariane 4의 요구에 근거하며 Ariane 5에는 필요 없다. | "based on a requirement of Ariane 4 and is not required for Ariane 5" | 검증 없는 재사용의 핵심 |
| F01-007 | 8 | 변수 BH(수평 편향)가 기대보다 훨씬 컸다. Ariane 5의 초기 궤적이 Ariane 4와 달라 수평 속도가 훨씬 높기 때문이다. | "differs from that of Ariane 4" | 입력 범위 가정 |
| F01-008 | 8 | 위원회는 이 사슬이 기술적 원인이라는 것이 "합리적 의심의 여지 없이" 확립되었다고 쓴다. 근거: 시뮬레이션 재현, 두 SRI의 회수와 메모리 판독, 코드 검토. | "established beyond reasonable doubt" | 결론의 확신 수준 |
| F01-009 | 9 | 예외를 낼 수 있는 연산 중 변수 7개가 위험했고 4개에만 보호를 넣었다. 3개(BH 포함)는 보호하지 않았다. 이유로 SRI 컴퓨터의 최대 부하 목표 80%가 거론되었다. 이 결정의 근거는 소스 코드에서 찾지 못했다. | "three of the variables were left unprotected" | 80%는 "위원회에 진술되었다"(It has been stated to the Board)로 적힌 것 |
| F01-010 | 9 | 보호하지 않은 이유는 물리적으로 제한되거나 안전 여유가 크다는 추론이었고, BH의 경우 그 추론이 틀렸다. 이 결정은 계약 수준이 여러 개인 협력사들이 공동으로 내렸다. | "turned out to be faulty" | 조직 요인 |
| F01-011 | 9 | Ariane 5 궤적 데이터로 비보호 변수의 동작을 분석한 증거가 없고, 궤적 데이터를 SRI 요구와 사양에 넣지 않기로 공동으로 합의했다. | "jointly agreed not to include the Ariane 5 trajectory data in the SRI requirements and specification" | 요구사항의 결함 |
| F01-012 | 9 | 예외 처리의 사양: 실패를 버스에 알리고, 문맥을 EEPROM에 저장하고, SRI 프로세서를 정지시킨다. 위원회는 정지 결정이 결정적이었다고 쓴다. 재시작은 자세 재계산이 어려워 불가능했다. | "the decision to cease the processor operation which finally proved fatal" | 원문 어순은 "It was the decision to cease..." |
| F01-013 | 9 | 정지 사양의 배경은 무작위 하드웨어 고장만 다루는 Ariane 프로그램의 문화다. 그런 시각에서는 예외 처리를 백업 시스템이 맡는다. 그러나 이번 것은 체계적 소프트웨어 설계 오류였다. | "culture within the Ariane programme of only addressing random hardware failures" | 조직 요인 |
| F01-014 | 9 | 같은 소프트웨어가 두 SRI에서 돌므로 소프트웨어 기능을 잃으면 위험하다. 이번에는 아직 건강한 핵심 장비 둘이 꺼졌다. | "the same software runs in both SRI units" | 이중화가 체계적 오류를 막지 못함 |
| F01-015 | 9-10 | 정렬 기능이 이륙 뒤에도 도는 요구는 10년 이상 전 이전 모델의 카운트다운 중단 상황(예: -9초와 -5초 사이)에 대응해 들어왔다. 실제로는 1989년 Flight 33에서 한 번 쓰였다. Ariane 5에는 이 요구가 적용되지 않지만 유지되었다. | "maintained for commonality reasons" | "presumably"가 붙은 위원회의 추정 |
| F01-016 | 10 | 위원회: 소프트웨어는 기계 시스템처럼 고장 나지 않으며, 표현력이 높아 까다로운 요구를 부르고 그것이 평가하기 어려운 구현으로 이어진다. | "does not fail in the same sense as a mechanical system" | |
| F01-017 | 10 | SRI 공급자는 "예외가 감지되면 프로세서를 멈춰라"는 사양을 따랐을 뿐이다. 소프트웨어는 틀렸음이 드러날 때까지 옳다고 보는 시각이 있었고, 위원회는 반대 시각을 지지한다. | "software should be assumed to be faulty until applying the currently accepted best practice methods can demonstrate that it is correct" | 위원회 의견 |
| F01-018 | 11 | SRI를 Ariane 5의 카운트다운, 비행 시간 순서, 궤적 아래에서 시험한 일이 없다. 그런 시험을 했다면 실패 기전이 드러났을 것이라고 위원회는 쓴다. | "the failure mechanism would have been exposed" | 원문은 "Had such a test been performed ... the failure mechanism would have been exposed" |
| F01-019 | 11 | SRI 사양은 선택한 구현에서 나오는 운용 제한을 밝히지 않는다. 위원회는 이런 제한 선언이 모든 mission-critical 장비에 의무여야 한다고 쓴다. | "should be mandatory for every mission-critical device" | |
| F01-020 | 13 | 1992년에 시험 철학이 바뀌어 실제 SRI를 폐루프 시스템 시험에 넣지 않기로 했다 (SRI는 장비 수준에서 완전히 인증되었다고 간주 등 4가지 이유). 위원회는 이유들이 기술적으로 타당하지만 위험했다고 평가한다. | "a definite risk in assuming that critical equipment such as the SRI had been validated" | 원문은 "...validated by qualification on its own, or by previous use on Ariane 4" |
| F01-021 | 13 | 검토 과정에서 SRI 소프트웨어의 한계가 충분히 분석되지 않았고, 시험 범위가 이를 드러내기에 부족한 줄도 몰랐다. 위원회는 검토 과정을 기여 요인으로 본다. | "the review process was a contributory factor in the failure" | 문장 일부가 OCR 줄바꿈에 걸려 있음 |
| F01-022 | 17 | 권고: R1 이륙 직후 정렬 기능을 끄고, 필요 없는 소프트웨어 기능은 비행 중 돌리지 않는다. R3 어떤 센서도 best-effort 데이터 전송을 멈추게 하지 않는다. R5 구현이 장비 값에 두는 암묵적 가정을 모두 찾아 사용 제한과 대조한다. | "no software function should run during flight unless it is needed" | R2는 실제 장비를 넣은 폐루프 시스템 시험 |
| F01-023 | 18 | R8 핵심 부품의 정의를 소프트웨어 기원 고장(특히 single point failure)까지 넣어 다시 본다. R10 사양과 시험 요구에 궤적 데이터를 넣는다. R9는 검토가 "검증을 했는지 확인"이 아니라 논거의 실질을 다루도록 요구한다. | "single point failures" | |

## 2. nasa-toyota-ua-report (NASA NESC 보고서, 2011)

쪽 = PDF 쪽 = "of 177" 표기 쪽. 이 절은 NASA 보고서가 적은 것만 담는다.

### 2a. NASA 보고서가 적은 것 (공식 조사의 결론과 조사 범위)

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| F01-024 | 13 | NHTSA가 NESC에 요청한 것: Toyota ETCS-i에 UA를 일으킬 수 있는 설계, 구현의 취약점이 있는지, 있다면 소비자의 실제 사용에서 일어날 수 있는지. ETCS-i는 2002 MY Camry에서 기계식 연결을 대체했다. | "could realistically occur in consumers' use of these vehicles" | |
| F01-025 | 13 | 보고서의 전제: 전자 제어는 기계적 고장을 줄일 수 있지만 기계식에 없던 이상 모드를 도입할 수도 있다. | "can also potentially introduce anomalous modes not present with those mechanical systems" | |
| F01-026 | 14 | 사고 통계(VOQ): 2000-2010년 접수 426,911건 중 UA로 판정된 것 9,698건, Toyota 3,054건. ETCS-i 도입 시점에 보고가 늘지 않았고, 보도(publicity)와 함께 늘었다. | "an increase in UA VOQs coincident with publicity" | 이 쪽에는 사망자 수가 없음 |
| F01-027 | 14 | VOQ의 절반 넘게가 원인 불명의 큰(25도 초과) 스로틀 열림 UA였다. 많은 경우 브레이크가 듣지 않았다고 적혀 있으나, 사후에 ETCS-i나 브레이크의 고장 증거가 보통 발견되지 않았다. | "no evidence of a failure in either the ETCS-i or brake system typically was reported as having been found" | |
| F01-028 | 14 | NESC는 ETCS-i 설계, 도면, 소프트웨어 소스 코드, NHTSA가 확보한 VOQ 차량에 제한 없이 접근했다. | "Had unrestricted access to the ETCS-i design" | 조사의 한계를 가늠할 때 같이 볼 사실 |
| F01-029 | 15 | ETCS-i는 prime 시스템과 monitor 시스템의 단계적 fail-safe 구조다. fail-safe 모드 5가지, limp home(스로틀 상한 약 18도), fuel cut(페달이 놓이면 2500 rpm으로 제한)이 있다. | "tiered fail-safe approach with a prime system and a monitor system" | |
| F01-030 | 15 | DTC 없이 UA를 일으킬 수 있는 가설 시나리오 두 개: (1) 페달 위치 감지의 이중 고장, (2) monitor가 못 잡는 main CPU의 체계적 소프트웨어 오작동. | "a systematic software malfunction in the main central processor unit (CPU) that is not detected by the monitor system" | 둘 다 hypothetical로 적힘 |
| F01-031 | 16 | 코드 검토: 스로틀 제어 변수는 복사본 여러 개로 손상을 막고, 엔진 출력을 제어하는 병렬 기능 경로가 둘이다. 28만 줄이 넘는 코드에서 시나리오 (2)를 일으킬 경로는 찾지 못했다. | "none were identified" | 원문: "(more than 280,000 lines) for paths that might initiate such a UA, but none were identified" |
| F01-032 | 16 | 시나리오 (1)에 관해: 결함 페달 조립품에서 tin whisker가 저항성 부분 단락을 만들었다. 이 단락이 있으면 특정 두 번째 고장에서 이론상 UA가 가능하다. 그러나 보증 자료에서 페달 유발 DTC의 관측 가능한 흔적이 없고, 차량 6대의 전기 측정에서 필요한 저항 경로도 없었다. | "could theoretically lead to UA" | 원문: "may be vulnerable to a specific second fault condition that could theoretically lead to UA" |
| F01-033 | 17 | 전자기 간섭(EMI)을 인증 수준보다 훨씬 높게 가해도 UA는 나오지 않았고, 엔진이 느려지거나 꺼지는 경우가 있었다. | "did not produce any UAs" | |
| F01-034 | 17 | 결론 1: VOQ가 말하는 큰 스로틀 열림 UA를 ETCS-i가 일으켰다는 증거는 하드웨어, 소프트웨어 시험으로 찾지 못했다. 단일 고장으로 DTC 없이 스로틀이 15도까지 튈 수 있는 모드가 있으나 페달을 놓거나 브레이크로 해제된다. | "Proof for the hypothesis that the ETCS-i caused the large throttle opening UAs ... could not be found" | 인용은 중간 생략 |
| F01-035 | 17 | 결론 2 (조사의 한계를 스스로 적은 문장): 증거를 못 찾았다는 것이 일어날 수 없다는 뜻은 아니다. 다만 이 조사는 ETCS-i 전자장치를 큰 스로틀 열림의 가능성 높은 원인으로 보지 않았다. | "does not mean it could not occur" | 원문: "Because proof that the ETCS-i caused the reported UAs was not found does not mean it could not occur." |
| F01-036 | 17 | 같은 쪽: "did not find that ... a likely cause" 형태의 부정이며, 원인이 없다는 단정이 아니다. | "did not find that TMC ETCS-i electronics are a likely cause of large throttle openings" | 원문은 "...as described in the VOQs"로 이어짐 |
| F01-037 | 170 | 조사 범위: 공학적 분석의 대부분은 2005 MY Camry L4 ETCS-i에 한정되었다. EMC 시험은 VOQ 차량 2002, 2003, 2004, 2007 MY에서만 했다. | "limited to MY 2005 Camry, L4 ETCS-i" | 7.1 Findings 첫 문단 |
| F01-038 | 170 | F-1: 큰 스로틀 열림 UA를 자연스럽게 반복 재현하는 Toyota 차량은 찾지 못했다. F-2: 단일 고장과 일부 이중 고장에 대한 다중 독립 안전 기능이 있다. | "No TMC vehicle was identified that could naturally and repeatedly reproduce large throttle opening UA effects" | F-2 인용: "single and some double ETCS-i failures" |
| F01-039 | 170 | 메모리와 프로세서 보호: 메모리 EDAC, 핵심 변수 데이터 미러링, watchdog timer, 두 프로세서의 heartbeat 상호 점검이 있다고 적었다. | "Processor and memory protection against single event effects includes EDAC on memory" | Koopman은 2005 MY에 RAM EDAC가 없었다고 주장함 (3b 참조) |
| F01-040 | 171 | F-4: 페달 고장이 큰 스로틀 열림이 되려면 유효한 페달 신호를 흉내 내야 하고, 조건을 못 맞추면 DTC가 선다. 다만 Hall Effect 페달의 이중 고장 시나리오에서 첫 고장은 ECM이나 진단 자료로 못 볼 수 있다. | "might not be detectable by the ECM or via diagnostic data" | |
| F01-041 | 171 | F-6: 248 ohm 단락 시험에서 페달을 천천히 밟으면 차가 full throttle까지 갈 수 있고 brake override가 없다. 빨리 밟으면 limp home이 작동한다. 어느 경우든 페달을 놓으면 스로틀이 닫히고 브레이크는 정상이다. | "capable of full throttle without throttle brake override" | 원문 F-6a: 시동 전에 단락이 생긴 경우 |
| F01-042 | 172 | F-10: 정적 분석, logic model testing, recursion testing, 최악 실행 시간 분석을 거쳐 "단독으로 UA를 일으키는" 소프트웨어 결함은 찾지 못했다. "사용한 도구로는"이라는 단서가 붙는다. | "software defects that unilaterally cause a UA were not found" | 원문: "With the tools utilized during the course of this study" |
| F01-043 | 172-173 | O-1: UA의 해결은 운전자의 인지와 대응에 달려 있고 일부 운전자는 대응 수단을 모른다. O-9: 인적 요인 문헌상 pedal misapplication은 일부 UA의 원인으로 남아 있으나 빈도는 추정할 수 없다. | "pedal misapplication remains an identified cause of some UAs" | O-9는 173쪽 |
| F01-044 | 173 | O-3: ETC의 안전 임계 고장은 브레이크 고장과 달리 전용 경고등이 없고 일반 check engine light만 켜진다. O-4: 법정 DTC는 배출 제어용이며 안전 임계 고장을 포괄하도록 규정되지 않았다. | "only a generic, multi-purpose check engine light occurs for off-nominal ETC conditions" | |
| F01-045 | 173 | O-5: 활성 페달 센서 고장을 가진 채 운행하는 차는 두 번째 고장에 취약할 수 있다. NHTSA가 본 SMART 자료 188건에서는 두 번째 고장이 UA를 일으킨다는 증거를 못 찾았다. O-2: 브레이크로 스로틀을 닫는 limp home 동작은 광범위한 방어다. | "may be susceptible to the effects of second faults" | |
| F01-046 | 173 | O-6: 2005 Camry 소스 코드는 독자 코딩 표준 때문에 일반 도구 외의 검사 도구와 수작업 검토가 필요했다 (설계 취약점은 아님). O-7: UA 뒤에 사건 이전의 소프트웨어 상태를 남기는 방법이 차량에도 진단 도구에도 없다. | "no methods for capturing pre-event software state and performance following a UA event" | O-6, O-7은 151쪽에도 있음. 원문은 "There are no methods..." |
| F01-047 | 148-150 | 소프트웨어 연구 범위: 2005 Camry L4 ECM 소프트웨어, 2010년 4월 중순부터 8월 중순까지. 점검 4분류는 코딩 결함, 알고리즘 결함, task 간섭(race condition, 데이터 손상), 불충분한 fault protection. 도구는 Coverity, CodeSonar, Uno, Spin, MATLAB/Simulink/Stateflow, aiT. | "The study started mid April 2010 and ran through mid August 2010." | 4분류의 4번째는 149쪽 |
| F01-048 | 147 | 후보 선정 기준 중 하나: 내부 소프트웨어 데이터 손상은 시연되지 않았다. 외부 센서, 제어 고장은 폭넓게 시험했다. | "Internal software data corruption could not be demonstrated." | |

### 2b. 원고 쪽 전문가 (Koopman)의 주장 (koopman-toyota-ua, 2014년 발표 슬라이드)

쪽 = 슬라이드 번호 = PDF 쪽. 발표자는 Bookout 재판에서 원고 쪽 소프트웨어 전문가로 증언한 사람이다 (슬라이드 12). 자료의 숫자와 주장은 슬라이드에 적힌 것이며, 많은 항목이 재판 증언(Bookout 날짜와 쪽)과 NASA 보고서 부록 A 쪽을 출처로 단다. 부록 A는 내가 읽지 않았다 (확인하지 못함).

| 번호 | 쪽 | 사실 (누구의 주장인지) | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| F01-049 | 9 | Koopman: NASA는 "smoking gun"을 찾지 못했으나, 일정이 빠듯하고 정보가 제한되었으며 시스템을 무죄로 만들지는 않았다. 이를 재판 증언으로 뒷받침한다고 단다. 교통부 장관은 "전자 기반 원인이 없다"고 말했다. | "Did not exonerate system" | 장관 발언 인용은 슬라이드 9에 있음 (NHTSA 보도 자료 링크) |
| F01-050 | 10 | Koopman: ESP-B2 monitor 칩에도 소프트웨어가 있는데 NASA는 main CPU 소프트웨어만 분석했다. NASA가 2005 MY의 RAM ECC를 인정했으나 증언상 RAM EDAC는 실제로 없었다. | "analysis is limited to Main CPU software" | 쟁점. NASA 쪽 문장은 F01-039 |
| F01-051 | 11 | 사실(소송): 2002-2010 MY 대상 집단소송을 Toyota가 2012년 12월 16억 달러에 합의했고, Toyota는 청구를 부인한다. 일부 최근 모델에 brake override 펌웨어 갱신이 있다. | "Toyota denies claims; settled for $1.6 Billion in Dec. 2012" | 경제적 손실 소송이며 사고 인과 판단이 아님 |
| F01-052 | 12 | Bookout/Schwarz 재판(2013년 10월, Oklahoma): 2007년 2005 Camry 치명 사고. Toyota는 운전자 오류를 주장했고, 원고는 ETCS를 탓했다. 원고 쪽 증인이 소프트웨어 결함과 결함 있는 안전 구조를 증언했고 150피트 스키드 마크가 브레이크 중 스로틀 열림을 시사한다고 주장했다. | "Toyota blamed driver error for crash" | 양쪽 주장이 나란히 적힘 |
| F01-053 | 15 | 재판 결과: 배심은 300만 달러를 배상으로 인정했다. 핵심 쟁점은 ETCS 설계 결함이 치명 사고를 일으켰는가였다. Toyota는 징벌적 배상 판단 전에 합의했다. Toyota는 지금도 ETCS 결함을 부인한다. | "Toyota disputes that their ETCS is flawed" | 이 슬라이드는 "ETCS software/safety case로 실제 재판까지 간 유일한 사건"이라고도 적음 |
| F01-054 | 16 | 사실(형사): 2014-03-19 미 법무부 합의 12억 달러. 대상은 floor mat과 sticky pedal 두 문제뿐이다. 전자 스로틀 소프트웨어와는 관련이 없다고 슬라이드가 밝힌다. | "Related to floor mats & sticky throttle pedals only" | UA의 소프트웨어 원인에 대한 판단이 아님 |
| F01-055 | 17 | Koopman: NASA가 찾은 기술적으로 의심스러운 것이 많았다. 배심은 ETCS 결함이 사망을 일으켰다고 판단했으나 비전문가다. 증거 기준은 "more likely than not"(민사)이다. | "Standard of evidence is "more likely than not"" | 형사의 "합리적 의심"과 다름 |
| F01-056 | 19-20 | Koopman: 차량 수준 시험으로는 모든 조건과 타이밍을 못 덮는다. Toyota는 시스템 수준 약 3,500만 마일, 모듈 수준 소프트웨어 1,100만 시간을 시험했으나, 출하 차량당 1-2시간 수준이라 현장 노출의 수천 분의 1이다. | "Testing Is Not Enough To Establish Safety" | 수치의 출처는 NASA 보고서 p.20으로 슬라이드가 표시, 미확인 |
| F01-057 | 26-27 | Koopman: 미국 차량에는 인증 요구가 없고 FMVSS는 소프트웨어 안전을 다루지 않는다. Toyota는 MISRA를 따랐다고 주장하지 않으며, NASA는 감사 가능한 소프트웨어 프로세스 계획이나 문서화된 안전 논거를 공개하지 않았다. | "Toyota does not claim to have followed MISRA Guidelines" | Toyota 쪽 전문가의 의견은 같은 슬라이드: 현실적 ETCS 고장이 없고 fail-safe가 막는다 |
| F01-058 | 31-32 | Koopman: 한 fault containment region(FCR)은 자기 고장을 다 스스로 감시할 수 없다. 핵심 시스템은 독립 FCR 여럿이 필요하고, 입력도 독립적으로 관측해야 한다. 자기 시험(self-test)만으로는 부족하다. | "Self-test isn't enough for safety" | 설계 원칙에 대한 전문가 의견 |
| F01-059 | 33-34 | Koopman: Toyota ETCS의 monitor chip과 main CPU는 센서 입력을 공유한다 (VPA1, VPA2가 같은 칩의 같은 입력 블록을 통과). 그래서 공유 입력이 single point of failure이고 잘못된 데이터가 main CPU에 도달할 수 있다. | "This is a Single Point of Failure" | 증언 출처 [Bookout 2013-10-11AM 63:21-64:14]. NASA는 이중 센서와 monitor가 있다고 적음 (F01-029) |
| F01-060 | 36 | Koopman: Toyota 코딩 규칙은 MISRA C와 겹침이 11개 규칙뿐이다. Toyota는 자기 규칙도 늘 지키지 않았다 (switch 343개 중 105개에 default 없음). NASA 도구로 쉽게 점검되는 MISRA 규칙 35개 중 14개를 어겼고 위반 7,134건이다. 원고 쪽 증인팀은 MISRA 위반 80,000건을 셌다. | "Toyota did not always follow its own coding rules" | 출처 NASA App. A pp.21-29, Bookout 증언. App. A는 미확인 |
| F01-061 | 37-38 | Koopman: NASA의 정적 분석 도구 결과를 표로 보인다 (CodeSonar의 "전역 변수가 서로 다른 타입으로 선언됨" 2,272건, 초기화 안 된 변수 22건 등). McCabe 복잡도 50 초과 함수가 67개, 스로틀 각도 함수 복잡도 146, 1,300줄, 단위 시험 계획 없음. | "67 functions with complexity over 50" | Toyota는 이 도구들에 경고 0건을 주장하지 않았다고 슬라이드가 밝힘 |
| F01-062 | 40 | Koopman: 읽기/쓰기 전역 변수 11,253개, 전체 데이터 객체의 82%가 모든 task가 접근할 수 있는 범위다. 슬라이드는 "이상적인 쓰기 가능 전역 변수 수는 0"이라고 쓴다. | "a majority of all data objects (82%) is declared with unlimited scope" | NASA App. A p.33을 인용한다고 표시. 개수는 도구마다 다르다는 각주 있음 |
| F01-063 | 42-43 | Koopman: NASA가 구체적 동시성 결함을 하나 식별했다. 공유 전역이 모두 volatile이 아니고 인터럽트 마스크 없이 접근된다. ETCS는 재귀를 쓰고 스택이 94% 찼으며 오버플로 대책이 없다. | "Toyota ETCS uses recursion" | 출처 NASA App. A pp.33-34, 129-130과 증언. 미확인 |
| F01-064 | 44-45 | Koopman: watchdog은 하드웨어 타이머 서비스 루틴이 kick하고, throttle 각도 계산과 대부분의 fail-safe, 대부분의 DTC 설정을 맡은 "Task X"가 죽어도 감지하지 못한다. | "Watchdog does not detect death of major tasks" | 증언 출처 [Bookout 2013-10-14PM 70:10-72:23 등] |
| F01-065 | 46-47 | Koopman: "안전 문화" 증거로, 일부 개발 단계에 "Toyota에 지식이 없음", UA 조사 담당자의 "fail-safe가 있어서 소프트웨어 이상은 UA와 무관" 발언, 2007년 사내 이메일 ("fail-safe는 엔지니어링 부서의 DNA가 아님"), 비공식 검토, 형상 관리, 버그 추적, 정식 사양이 없다는 증언. | "failsafe is not part of the Toyota's engineering division's DNA" | 원문은 "In truth technology such as failsafe is not part of..."이다. 모두 재판 증언 출처로 표시됨 |

### 2c. 둘이 갈리는 점 (원 문서가 적은 것을 나란히 둔 것. 내 판정은 없다)

| 번호 | 쪽 | NASA 보고서 | Koopman | 비고 |
|---|---|---|---|---|
| F01-066 | NASA 17, 170 / K 9 | 전자장치가 "likely cause"라는 것을 찾지 못했다. 증거 없음이 불가능의 증명은 아니라고 스스로 적었다. | 장관이 "no electronic-based cause"라고 발표했다. NASA는 "smoking gun"을 못 찾았을 뿐 시스템을 무죄로 한 것이 아니다. | 요약 문구와 보고서 본문의 강도가 다르다는 주장 (K 슬라이드 9) |
| F01-067 | NASA 170 / K 10 | 메모리 EDAC가 있다고 적음 (F01-039). | 2005 MY에 RAM EDAC가 없다 (증언). NASA가 Toyota의 말을 듣고 인정했다고 추정. 분석은 main CPU만, monitor 칩 소프트웨어는 분석 안 함. | 사실 관계의 충돌. 어느 쪽이 맞는지는 읽은 쪽만으로 판정 불가 |
| F01-068 | NASA 15, 170 / K 31-34 | 다중 독립 안전 기능이 단일 및 일부 이중 고장을 막는다 (F-2). | 같은 FCR 안의 fail-safe는 같은 고장에 당할 수 있고, 입력 공유가 single point of failure다. | 설계 철학의 차이. K는 "Toyota 전문가 쪽도 같은 FCR fail-safe를 논거로 쓴다"고 적음 (27) |
| F01-069 | NASA 172 (F-10) / K 36-47 | 사용한 도구로 단독 UA 결함을 못 찾았다. | 같은 NASA 자료의 정적 분석 수치 등을 들어 코드 품질과 안전 문화가 낮다고 주장한다. | K는 "NASA가 찾은 기술적 의심스러운 점이 많다"고 요약 (17). 내용은 부록 A 미확인 |
| F01-070 | NASA 150, 17 / K 9, 19-20 | 4개월(2010-04 중순~08 중순) 소프트웨어 연구. 단위 시험과 분석으로 후보 경로를 점검. | "tight timeline & limited information". 차량 시험으로는 모든 경우를 못 본다. | K는 증언을 출처로 달았다. NASA는 이 비판의 쟁점을 보고서 이 쪽들에서 직접 다루지 않는다 |
| F01-071 | NASA 172-173 (O-1, O-9) / K 12 | 일부 UA는 운전자의 대응 지식과 pedal misapplication에 관련될 수 있다고 적음. | Toyota는 운전자 오류를 주장했고 원고는 ETCS 결함을 주장했다. 배심은 ETCS 결함이 사망을 일으켰다고 판단했다. | 배심 판단은 민사, 비전문가라고 K도 단서를 단다 (17) |
| F01-072 | NASA 전체 / K 16 | 형사 합의는 NASA 보고서의 대상이 아님. | 형사 합의는 floor mat과 sticky pedal에 한정된다. | 소프트웨어 원인이 형사에서 인정된 것이 아님 |

## 3. b737max-knkt-jt610 (KNKT 최종 보고서, Lion Air 610)

쪽 = PDF 쪽 (보고서 자체 쪽 = PDF 쪽 - 2). 이 문서는 인도네시아 KNKT의 사고 조사 결과다.

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| F01-073 | 191 | MCAS는 737-8(MAX)이 737-800의 파생형이라 추가되었다. 큰 LEAP-1B 엔진이 stick force per g 특성에 영향을 줄 것으로 보였고, 공기역학 변경과 함께 MCAS를 STS의 확장으로 넣었다. 목적에는 NG와 비슷한 특성을 줘서 시뮬레이터 훈련을 피하는 것이 포함된다. | "so similar to the NG versions that no simulator training was needed" | 원문은 "MCAS was needed in order to make ... handling characteristics so similar to the NG versions that no simulator training was needed for type rating" |
| F01-074 | 191 | 개발이 진행되며 MCAS 기능은 낮은 Mach 수까지 확장되었다. | "the MCAS function was expanded to low Mach numbers" | JATR O6.9-C, D와 같이 읽을 것 |
| F01-075 | 50-51 | MCAS는 STS의 기능으로 FCC 안의 제어 법칙이다. 각 FCC에 하나씩 있고 비행마다 master가 좌우로 번갈아 바뀌며 master FCC에서만 활성이다. 입력은 Air/Ground, flap 위치, AOA, pitch rate, 진대기속도, Mach. | "MCAS is only active in the master FCC for that flight" | 번갈아 쓰는 구조가 단일 입력 의존의 배경 |
| F01-076 | 51 | 각 ADIRU는 자기 쪽 AOA 센서의 resolver 하나에서 AOA를 받는다 (왼쪽 ADIRU는 왼쪽 vane). 같은 센서의 다른 resolver 값은 SMYD(실속 경고)로 간다. | "Each ADIRU receives AOA information from one of the two resolvers" | 원문: "...contained within the associated AOA sensor" |
| F01-077 | 51 | 출하 시 MCAS는 수동 비행, flap up에서 AOA가 Mach 기반 문턱을 넘으면 고속률 자동 trim 명령을 내렸다. 조종사가 yoke의 전기 trim 스위치로 멈추거나 되돌릴 수 있으나, 그 스위치가 시스템을 5초 뒤 reset한다. 높은 AOA가 계속되면 5초 뒤 다시 nose-down trim을 명령한다. | "if the original elevated AOA condition persists for more than 5 seconds following an MCAS flight control law reset" | 반복 활성화의 기전. 이 reset 논리는 조종사가 trim을 완전히 중립으로 돌린다는 가정에 근거한다고 적혀 있음 |
| F01-078 | 51 | 설계 가정: 조종사는 trim 스위치로 항공기를 완전히 중립 trim으로 되돌린다. | "based on the assumption that flight crews use the trim switches to completely return the aircraft to neutral trim" | |
| F01-079 | 52 | MCAS 때문에 첫 부조종사 쪽 column cutout 스위칭 모듈의 aft cutout을 MCAS 활성 중에는 억제하도록 수정했다. 즉 기존의 기둥-trim 반대 방향 차단이 MCAS 동안 풀린다. | "modified to inhibit the aft column cutout switch while MCAS is active" | 기존 안전 장치의 변경 |
| F01-080 | 191-192 | FHA: Boeing은 MCAS의 uncommanded 활성을 "major"로 분류했고, 그래서 FMEA, FTA는 요구되지 않았다 (Hazardous나 Catastrophic에만 요구). 따라서 uncommanded MCAS에 대한 fault tree를 하지 않았다. | "Boeing did not perform a specific fault tree analysis for an uncommanded MCAS hazard" | 192쪽에 FMEA, FTA가 필요 없었다는 문장도 있음 |
| F01-081 | 192 | FHA 시뮬레이터 시험에서 stabilizer 이동을 유도했을 뿐, 높은 AOA 입력 같은 고장 원인은 시뮬레이션하지 않았다. 저속 최대 한도 2.5도는 시험하지 않고 고속 0.6도까지만 했다. 반복 오작동은 고려하지 않았다. | "was not simulated as part of these functional hazard assessment validation tests" | 원문은 "erroneous high AOA input ... was not simulated" |
| F01-082 | 192 | 반복 활성화가 단일 활성화보다 나쁘지 않다고 본 근거는 조종사가 uncommanded trim 입력을 trim으로 상쇄할 것이라는 가정이었다. | "it was assumed that the pilots would trim out uncommanded trim inputs" | KNKT: 조종사가 충분히 반응하지 않으면 부하가 늘어 재고했어야 했다 |
| F01-083 | 193 | 조종사 응답 가정(FHA): 불시 stabilizer 이동은 쉽게 인지된다, 조종사는 즉시 조치한다, 훈련된 기억 항목 절차에 의존해도 된다. Boeing은 FAA 지침에 따라 3초 안에 반응한다고 가정했다. | "the flight crew would respond within 3 seconds to any changes in flight condition" | KNKT는 기억 항목에 의존한다는 가정이 "inappropriate"라고 평가 |
| F01-084 | 193-194 | 실제 사고기: 첫 활성화에 기장은 2초 안에 column으로 반응했으나 MCAS는 10초간 stabilizer를 움직였다. 둘째 활성화에는 8초 뒤에 전기 trim을 썼다. 승무원은 기둥 힘을 일관되게 trim으로 없애지 않았다. 직전 LNI043편 승무원은 문제를 이해하는 데 3분 40초가 걸렸다. | "they did not consistently trim out the resulting column forces as had been assumed" | 194쪽. 3분 40초는 195쪽 |
| F01-085 | 195 | 사고 중 다중 경고와 지시가 승무원의 부하를 늘려 문제를 가렸고, 승무원은 runaway stabilizer 절차로 가지 못했다. 사고편에서 uncommanded stabilizer 이동이 runaway stabilizer로 인식되지 않아 비정상 절차가 실행되지 않았다. | "multiple alerts and indications occurred which increased flight crew's workload" | |
| F01-086 | 196 | KNKT의 판단: stabilizer cutout은 가능하지만 필수는 아니라는 Boeing의 논리는 "incorrect"다. FHA에서 반복 MCAS 활성화의 영향을 충분히 평가하지 않았다. | "Boeing reasoning that the stabilizer cutout is available but not required is incorrect" | |
| F01-087 | 196 | 단일, 다중 고장 분석: 항공 자료 시스템의 최악 시나리오(좌우 AOA 오류)는 극히 개연성이 낮다고 평가했다. 그러나 MCAS가 AOA 센서 하나에 의존해 단일 AOA 오작동에 취약했다. 이 사고는 AOA 센서의 높은 편향 하나로 시작했다. | "the design of MCAS relying on input from a single AOA sensor, made this Flight Control System susceptible to a single failure" | |
| F01-088 | 196 | 737 선단에서 17년간 이륙 중이나 직후 stick shaker 작동이 25건 있었다. 이 때문에 AOA 센서 고장을 예견하고 평가했어야 했다고 KNKT는 쓴다. | "Boeing should have foreseen and assessed AOA sensor failures" | 원문: "Over the last 17 years in the Boeing 737 fleet alone, there were 25 events of stick shaker activation" |
| F01-089 | 217 | 기여 요인 1-3: 설계, 인증 중 조종사 반응에 관한 가정이 산업 지침과 일치했으나 틀렸다. 이 틀린 가정과 다중 flight deck effect의 불완전한 검토 때문에 MCAS의 단일 센서 의존이 적절하다고 판단되어 인증 요구를 모두 만족했다. MCAS는 AOA 센서 하나에 의존하도록 설계되었다. | "MCAS was designed to rely on a single AOA sensor, making it vulnerable to erroneous input from that sensor." | 기여 요인은 연대순이며 기여도 순서가 아니다 (원문 명시) |
| F01-090 | 217 | 기여 요인 4-9 (요약): 비행 매뉴얼과 훈련에 MCAS 안내가 없음, AOA DISAGREE 경고가 개발 중 제대로 활성화되지 않음, 교체 AOA 센서가 이전 수리에서 잘못 교정됨, 그 검출 실패, 정비 기록 문서화 부족, 다중 경고와 반복 활성화 속에서의 승무원 관리 실패. | "The AOA DISAGREE alert was not correctly enabled during Boeing 737-8 (MAX) development." | 항목 5. 4-9번은 한 줄로 합쳤고 정비, 승무원 요인이 섞여 있음 |

## 4. b737max-jatr (Joint Authorities Technical Review, 2019-10)

쪽 = PDF 쪽 (R6 쪽의 인쇄 쪽은 PDF 쪽 - 20). JATR는 여러 규제 기관의 합동 검토다.

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| F01-091 | 4 | 의장 서한: 규정 준수 중심의 과정이 안전을 보장하는지 재검토해야 한다. 시스템이 복잡해지면 규정이 모든 시나리오를 다루지 못한다. | "compliance with every applicable regulation and standard does not necessarily ensure safety" | "코드에 버그가 없다 vs 시스템이 안전하다"와 닿는 문장 |
| F01-092 | 4 | 의장 서한: 조종사 조치를 주된 위험 완화책으로 삼는 것을 최소화하고 fail-safe 원칙을 우선하라고 권고한다. | "minimizing reliance on pilot action as primary means of risk mitigation" | |
| F01-093 | 4 | 의장 서한: 한 시나리오(고속 windup turn)를 위해 만든 소프트웨어를 다른 시나리오(저속, 높은 AOA)용으로 고칠 때 생기는 의도하지 않은 결과, 그리고 MCAS가 "상대적으로 온순한 시스템"에서 훨씬 공격적인 시스템으로 변한 일이 다루어졌는가 하는 질문을 적었다. | "designing software for one scenario" | 서한은 이를 질문(query)으로 제기하며 결론으로 쓰지 않음 |
| F01-094 | 4 | 의장 서한: 조종사가 문제를 인지하고 대응하는 데 필요한 시간에 관한 FAA 기준을 복잡한 통합 시스템에 대해 재검토하라. 연쇄 고장과 다중 경고, startle effect를 인증이 얼마나 반영하는지가 쟁점이다. | "startle effect" | |
| F01-095 | 50 | R6: 항공기 기능은 증분적, 단편적으로 평가하지 말고 항공기 수준에서 전체적으로 평가하고, 가정을 도전하며, 안전 분석을 개발 보증 과정과 통합해 모든 안전 요구와 가정이 올바르고 완전하며 검증되었는지 확인하라. 설계 조직에서 독립한 시스템 안전 기능을 권고한다. | "associated assumptions should be challenged" | |
| F01-096 | 50 | O6.1-A: 올바른 조종사 조치가 MCAS 오작동 같은 위험에 대해 적절한 완화로 간주되었다. F6.1-A: MCAS는 단일 채널 STS의 일부로서 sensor voting이나 권한 한계 같은 fault tolerant 기능이 없었고, 이는 위험 분류에 맞는 고장 영향 제한이 아니었다. | "did not include fault tolerant features, such as sensors voting or limits of authority" | 원문 앞에 "As part of the single-channel speed trim system" |
| F01-097 | 51 | F6.1-B: 위험을 제거하거나 설계 기능이나 경고로 완화하기 전에 조종사 조치를 주된 완화책으로 쓴 것은 MCAS 구상 시 Boeing 자신의 안전 설계 process 지침에 맞지 않는다. | "is not in accordance with Boeing's process instructions for safe design" | |
| F01-098 | 51 | F6.4-A: 모든 flight deck effect를 고려하면 MCAS 도입이 특정 조건의 AOA 오류에 대한 조종사 반응 가정을 무효로 만들었다. 완전한 workload 평가를 하지 않았고, 이전 프로그램의 같은 가정이 공식 검증 없이 이월되었다. | "carried over from previous programs without formal validation" | 검증 없는 재사용 |
| F01-099 | 52 | F6.5-A: MCAS를 하나의 완전한 기능으로 본 통합 SSA를 수행하지 않았다. 안전 분석이 여러 문서에 흩어졌고 737 NG의 SSA 일부가 충분한 평가 없이 MAX에 재사용되었다. | "reused in the B737 MAX without sufficient evaluation" | |
| F01-100 | 52 | F6.6-A: FHA 보고서가 설계를 이끄는 도구가 아니라 이미 정해진 설계를 문서화하는 데 쓰인다는 인식이 있다. STS와 FCC의 FHA는 737 NG 보고서의 갱신본이어서 MCAS의 새 위험을 찾는 도구로 보이지 않는다. Boeing은 현 구성을 문서화해 훈련과 절차로 충분하다고 결론 지었다. | "mitigation by design should be prioritized over warnings and training/procedures" | |
| F01-101 | 53 | O6.7-A: 독립 안전 그룹이 시스템 안전 분석을 조율하는지 JATR가 확인하지 못했다. 시스템 팀이 설계와 안전 평가를 모두 한다. F6.7-A: 오작동 분석이 동시에 일어날 다른 일(AOA 고장의 flight deck effect로 인한 주의 분산)을 충분히 반영하지 않았다. | "Each system team conducts both the design and related safety assessments" | 조직 요인 |
| F01-102 | 53 | O6.9-A: 단일, 다중 고장 분석(S&MF)이 AOA에 대해서는 단일 최악 시나리오(한쪽 AOA 상실 + 반대쪽 오류)만 평가했고, 그것이 이미 catastrophic이라는 이유로 MCAS 도입 뒤 갱신하지 않았다. F6.9-A: 그 최악 시나리오 평가로는 단일 AOA 고장의 위험한 영향을 못 찾는다. | "limited to a single worst-case scenario" | 원문 표현: "was limited to a single worst-case scenario: loss of AOA on one side plus erroneous AOA on the other side" |
| F01-103 | 54 | O6.9-B~H: MCAS는 군용 B767 급유기에서 이미 운용되어 Boeing 엔지니어가 "new or novel"로 보지 않았다. STS 요구사항 Rev C(고속 값만)에 S&MF를 했고, 비행 시험 중 Rev D에서 저속 값을 추가했으며, 인증은 Rev E로 받았다. SSA는 Rev C 이후 갱신되지 않았고, 문서화된 위험, 고장, 안전 분석이 없다. | "no documented risk, failure, or safety analyses conducted on the MCAS software beyond Revision C" | 재사용과 요구 변경의 분석 누락 |
| F01-104 | 54 | O6.9-H: Boeing은 반복 오작동이 단일 오작동보다 나쁘지 않다고 결론 지었다. 조종사가 매번 trim 상태로 되돌린다는 가정(AC 25-7C)에 근거한다. | "multiple erroneous MCAS activations were not worse than a single erroneous activation" | KNKT F01-082와 같은 가정 |

## 5. b737max-ntsb-asr1901 (NTSB 안전 권고 보고서, ASR-19-01)

쪽 = PDF 쪽. Lion Air 610과 Ethiopian 302 두 사고에 관한 미국 NTSB의 권고다.

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| F01-105 | 1-2 | NTSB의 우려: 사고 조종사의 반응이 Boeing이 FAA 지침에 근거해 기능 위험 평가에 쓴 조종사 인지, 대응 가정과 일치하지 않았다. 사망자: Lion Air 189명 전원, Ethiopian 157명 전원. | "were not consistent with the underlying assumptions about pilot recognition and response" | 인원은 2, 3쪽 |
| F01-106 | 2 | Lion Air 사고기 기록: 좌측 AOA 센서가 우측보다 약 20도 높았고 비행 내내 유지되었다. 이륙 후 flap을 넣자 10초 자동 nose-down trim이 나왔고, 약 6분 동안 20회 넘게 나왔다. 승무원은 매번 전기 trim으로 상쇄했고 마지막 몇 번은 완전히 상쇄하지 못했다. | "automatic AND stabilizer trim inputs occurred more than 20 times over the next 6 minutes" | 직전 비행에서는 승무원이 STAB TRIM CUTOUT으로 문제를 멈췄다 (3쪽) |
| F01-107 | 5 | Boeing FHA는 "uncommanded MCAS" 두 위험을 "major"로 분류했고 시뮬레이터 시험은 stabilizer 이동 입력을 유도해 했다. 높은 AOA 같은 고장 원인은 시뮬레이션하지 않아 IAS DISAGREE, ALT DISAGREE, stick shaker 같은 동반 효과는 평가에 없었다. | "were not simulated and were not in the stabilizer trim safety assessment report reviewed by the NTSB" | |
| F01-108 | 6 | FHA에 쓴 네 가정: 불시 입력은 쉽게 인지되고 flight control을 정상 방향으로 움직여 상쇄된다, 상쇄에 특별한 기량이나 힘이 필요하지 않다, 조종사는 즉시 re-trim 한다, 훈련된 기억 절차를 따른다. 이 가정은 Boeing의 모든 기종 비행 제어 FHA에 쓰인다고 Boeing이 말했다. | "the pilot will take immediate action to reduce or eliminate increased control forces" | |
| F01-109 | 7 | 세 비행(Lion Air 직전 비행, 사고 비행, Ethiopian) 모두 조종사 반응이 서로 다르고 Boeing이 위험 분류에 쓴 가정과 맞지 않았다. 같은 AOA 오류가 stick shaker, IAS DISAGREE, ALT DISAGREE 등을 함께 일으켰다. | "did not match the assumptions of pilot responses to unintended MCAS operation" | |
| F01-110 | 8 | NTSB 결론: Boeing의 FHA 가정은 다중 flight deck 경고와 지시가 조종사 반응에 미치는 영향을 충분히 고려하지 않았다. 같은 가정이 다른 기종의 안전 평가에도 쓰였을 수 있다고 걱정한다. | "did not adequately consider and account for the impact that multiple flight deck alerts and indications could have" | 권고 대상은 FAA |
| F01-111 | 9 | 2002년 FAA, 산업 연구가 인적 오류 확률을 평가하는 방법이 없고 정성적 방법도 만족스럽지 않다고 했다. NTSB는 AC 25.1309-1A(1988)가 나온 뒤 연구가 진전되었을 것이므로 검증된 방법이 필요하다고 본다. | "no methods available to evaluate the probability of human error" | |

## 6. b737max-house-report (미 하원 교통인프라위원회 다수당 직원 최종 보고서, 2020-09)

쪽 = PDF 쪽 (인쇄 쪽 = PDF 쪽 - 7). 이 문서는 "Majority Staff" 보고서로 정치적 기구의 조사이며 사고 조사 기관의 보고서가 아니다. 사실 주장 중 상당수가 Boeing 내부 이메일, 청문회 기록, 면담을 출처로 단다.

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| F01-112 | 114 | MCAS는 한 번에 AOA 센서 하나의 데이터만 쓰도록 설계되었고, 비행마다 좌우를 번갈아 썼다. 그 센서가 높은 AOA를 잘못 알리면 MCAS가 반복 활성화한다. | "MCAS was designed to rely on data from only one AOA sensor at a time" | 비교로 KC-46 급유기의 MCAS는 AOA 센서 둘을 쓴다고 적음 (USAF 자료 인용) |
| F01-113 | 114 | Boeing의 FHA는 이 시스템을 다중 AOA 센서 같은 중복 기능이 필요할 만큼 위험하다고 평가하지 않았다. | "did not rate the system as being hazardous enough to require redundant features" | |
| F01-114 | 115 | 2015-12-17 Boeing 내부 이메일에서 AR인 엔지니어가 "MCAS 구현이 단일 AOA 센서 고장에 취약한가, 아니면 점검이 있는가"라고 물었다. 위원회는 이 우려가 예언적이었다고 쓴다. | "Are we vulnerable to single AOA sensor failures with the MCAS implementation" | 위원회의 해석이 섞임. 본문은 이 이메일이 FAA 인증(2017-03) 15개월 전이라고 적음 |
| F01-115 | 118 | 2016-06-22 MCAS 검토 회의록: 높은 AOA나 높은 Mach 고장이 MCAS 동작을 일으킨다는 논의에서, 다른 시스템도 반응할 것이므로 MCAS는 작고 재설계가 필요 없다고 결론 지었다. | "No need to redesign to address this." | 위원회가 인용한 회의록 |
| F01-116 | 118 | Boeing 자체 시험에서 조종사가 uncommanded MCAS에 10초 넘게 걸려 반응했고 이를 "catastrophic"이라 평가했다. Boeing은 이 상황이 runaway stabilizer처럼 보여 4초 안에 대응하리라고 가정했으나, 실제로는 AOA 센서 고장에서 동시에 오는 여러 경고가 따른다. | "Boeing assumed that pilots would respond to an unexpected MCAS activation" | 원문 계속: "as it if were a runaway stabilizer trim event, within four seconds" |
| F01-117 | 122 | Boeing의 coordination sheet에는 느린 반응(10초 초과)이 catastrophic이라는 문장이 2015-2018년 계속 같은 표현으로 남았다. 위원회는 이 정보가 FAA에 공유된 기록을 찾지 못했다. | "A slow reaction time scenario (>10 seconds) found the failure to be catastrophic" | 위원회의 확인: "unable to find any indication" |
| F01-118 | 124 | 737 MAX 책임 엔지니어(Teal)는 MCAS를 승인할 때 단일 AOA 센서 의존, 반복 활성화 가능성, 10초 반응 문제를 몰랐다고 면담에서 인정했다. 또 이 직책에서 직접 보고하는 엔지니어가 없는 구조를 설명했다. | "That is correct." | 면담 질문에 대한 답. 위원회는 조직 구조가 감독과 책임을 약화시킨 것 같다고 평가 (의견) |
| F01-119 | 126-127 | Boeing 설계 요구에 "MCAS shall not have any objectionable interaction with the piloting of the airplane"과 "shall not interfere with dive recovery"가 있다. 위원회는 두 사고에서 이 요구를 만족하지 못했다고 쓰고, Boeing 수석 엔지니어가 청문회에서 최소 하나를 인정했다고 적는다. | "MCAS shall not interfere with dive recovery." | 126쪽은 2016-03-30 MCAS를 FCOM에서 삭제해도 된다는 이메일 서술 |
| F01-120 | 192 | 2016년 11월 Boeing 내부 설문(ODA 구성원 520명 이상): AR 응답자의 39%가 부당한 압력을 경험했다고 믿었다. 그중 80%는 한 번 넘게 겪었다. | "39 percent of the Boeing ARs that responded believed they had experienced undue pressure" | 내부 문서를 내부 고발자가 제공 |

## 7. Therac-25 (Leveson and Turner, "An Investigation of the Therac-25 Accidents", IEEE Computer 26(7), 1993-07, pp.18-41)

읽은 주소 (2026-11-22): https://www.se.rit.edu/~swen-342/resources/Leveson,%20Turner%20-%20An%20Investigation%20of%20the%20Therac-25%20Accidents%20-%20IEEE%20Computer%20v26n7%20-%201993-07.pdf (RIT 강의 사이트의 사본, 24쪽 PDF). 요청받은 sunnyday.mit.edu 주소는 연결이 거부되어 읽지 못했다. 파일은 저장소에 두지 않았고 도구의 임시 폴더에서 읽기만 했다.
쪽은 인쇄 쪽 번호다. 텍스트 추출 잡음(예: relics -> relies, thc -> the)은 바로잡아 인용했다. 소프트웨어 개발 이력 사이드바의 세부는 저자들이 "문서에서 끌어낸 추정"이라고 밝힌 부분이 많다.
공식 조사의 결론이 아니라 두 연구자가 공개 자료(소송, 규제 기관 문서)로 재구성한 기록이다.

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| F01-121 | 18 | 1985-06부터 1987-01 사이에 Therac-25의 대량 과조사 사고가 6건 알려져 있고, 사망과 중상을 냈다. 저자들은 단일 원인을 붙이는 것이 보통 심각한 실수라고 쓴다. | "six known accidents involved massive overdoses by the Therac-25" | 원문은 "Most accidents are system accidents" (18) |
| F01-122 | 18-19 | 저자들의 한계: 제조사의 소프트웨어 개발, 관리, 품질 관리의 상세는 구할 수 없어 대부분을 서신 등으로 추정했다. | "detailed information about the manufacturer's software development, management, and quality control was unavailable" | 원문 19쪽 |
| F01-123 | 19-20 | Therac-6과 Therac-20은 컴퓨터가 이미 단독으로 서던 기계에 편의를 더한 것이고 업계 표준 하드웨어 안전 장치와 interlock이 유지되었다. Therac-25는 처음부터 컴퓨터 제어로 설계되었다. | "Industry-standard hardware safety features and interlocks in the underlying machines were retained." | 19쪽. 20쪽에 Therac-25 설계 서술 |
| F01-124 | 20 | AECL은 Therac-25에서 기존 하드웨어 안전 장치와 interlock을 모두 복제하지 않기로 했다. Therac-20에는 전자빔 주사를 감시하는 독립 보호 회로와 기계식 interlock이 있었는데 Therac-25는 소프트웨어에 더 의존한다. | "decided not to duplicate all the existing hardware safety mechanisms and interlocks" | 저자들은 이런 접근이 업계에서 흔해지고 있다고 덧붙임 |
| F01-125 | 20 | 소프트웨어 재사용: 품질 보증 관리자는 Therac-25 소프트웨어가 Therac-6 패키지에서 시작했고 Therac-20과는 같은 기반에서 따로 만들었다고 썼다. 그러나 그는 일부 Therac-20 루틴이 Therac-25에도 쓰인 것을 몰랐다가, Therac-25 사고와 관련된 버그가 Therac-20 소프트웨어에서도 발견되고서 알게 되었다. | "The same Therac-6 package was used by the AECL software people when they started the Therac-25 software." | 20쪽. 같은 쪽 사이드바: 개발 문서가 거의 없었고 단위 시험이 최소였다는 추정 |
| F01-126 | 21 | 1983-03 안전 분석(fault tree)은 소프트웨어를 사실상 제외했다. 가정: 잔여 소프트웨어 오류는 분석에 넣지 않고, 소프트웨어는 마모되지 않으며, 컴퓨터 실행 오류는 하드웨어 부품 고장과 무작위 오류에서 온다. 결과로 "Computer selects wrong energy"에 10^-11 같은 확률이 붙었으나 근거가 없다. | "Any residual software errors are not included in the analysis." | 확률 값은 텍스트 추출이 "1 0-11"로 나와 불확실. 나중에 한 FMEA, FTA의 소프트웨어 고장률 10^-?/hour 설정은 36쪽 |
| F01-127 | 21 | 소프트웨어는 공유 변수로 동시에 접근되며 실질적 동기화가 없고, 공유 변수의 test와 set이 분할 불가가 아니다. 이 구현의 race condition이 사고에서 중요한 역할을 했다. | "no real synchronization aside from data stored in shared variables" | 쪽 21 사이드바 |
| F01-128 | 21 | 사고 이력: Therac-25 11대 설치(미국 5, 캐나다 6), 6건 과조사, 1987년 소프트웨어 오류에 대비한 하드웨어 안전 장치를 포함한 대폭 설계 변경으로 회수했다. Therac-20에서도 관련 문제가 있었으나 하드웨어 interlock 덕에 부상이 없었다. | "Related problems were found in the Therac-20 software." | 원문: "These were not recognized until after the Therac-25 accidents because the Therac-20 included hardware safety interlocks" |
| F01-129 | 23-33 | 개별 사고 (저자 기술): Marietta의 Kennestone(1985-06 경), Hamilton Ontario(1985-07-26), Yakima(1985, 날짜 미확인), Tyler Texas(1986-03과 1986-04), Yakima(1987-01-17). Tyler의 환자 둘은 과조사 합병증으로 사망했다 (한 명은 약 3주, 한 명은 약 5개월 뒤). Yakima 1987에서는 86 rad 처방에 약 8,000-10,000 rad가 들어갔을 수 있다. | "Details of this accident in Marietta, Georgia, are sketchy since it was never carefully investigated." | 날짜별 목록은 일부만 확인한 요약. 치사율 판단은 원문 사망 서술 참고. 선량은 28쪽, 33쪽 |
| F01-130 | 29 | Tyler 사고와 같은 버그가 Therac-20에도 있었다. 시카고대학 물리학자가 새 학생이 쓸 때 퓨즈와 차단기가 떨어지는 현상을 편집 순서와 연결해 같은 버그로 확인했다. Therac-20에서는 독립 하드웨어 보호 회로가 빔 켜짐을 막아 불편에 그쳤다. | "While the Therac-20 relies on mechanical interlocks for monitoring the machine, the Therac-25 relies largely on software." | 하드웨어 interlock이 같은 소프트웨어 결함의 결과를 바꾼 사례 |
| F01-131 | 29 | 저자들의 판단: 특정 버그에 집중하는 것은 안전한 시스템을 만드는 길이 아니다. 근본 문제는 열악한 소프트웨어 공학과 소프트웨어에 안전을 의존하는 기계를 만든 것이다. | "focusing on particular software bugs is not the way to make a safe system" | |
| F01-132 | 29-31 | Tyler 결함: 데이터 입력 서브루틴 Datent가 키보드 처리 task와 공유 변수로 통신한다. "데이터 입력 완료" 변수는 커서가 명령줄까지 내려갔음을 나타낼 뿐 아직 거기 있는지는 나타내지 않는다. 자기장 설정에 약 8초가 걸리는 동안 편집한 값은 Ptime이 첫 실행에서 플래그를 지워 인식되지 않는다. AECL의 설명은 일부 질문이 남는다고 저자들이 적는다. | "only indicates that the cursor has been down to the command line, not that it is still there" | 31쪽. 30쪽에 Magnet, Ptime 서술 |
| F01-133 | 34 | Yakima 결함: setup test를 통과할 때마다 1바이트 공유 변수 Class3을 1씩 증가시키므로 256번째 통과마다 0으로 돌아가 상부 collimator 검사를 건너뛴다. 오퍼레이터가 정확히 그 순간 set을 눌러 전자빔이 target과 주사 없이 25 MeV로 켜졌다. | "Since the Class3 variable is 1 byte, it can only contain a maximum value of 255 decimal." | 수정은 증가 대신 0이 아닌 고정값 대입. 원문 마침표 표기는 "1 byte. it" |
| F01-134 | 36 | AECL의 안전 분석 결론은 하드웨어 변경 10가지이며, 그중 가장 중요한 것은 전자빔 주사와 에너지 선택의 소프트웨어 제어를 뒷받침하는 interlock이다. 그러나 소프트웨어 검사는 일부 기능에서 "높은 수준의 신뢰"를 줄 수 없다고 적었다. | "interlocks to back up software control of both electron scanning and beam energy selection" | 36쪽. 소프트웨어 고장률 10^-?/hour 한 값 설정은 저자들이 정당화 곤란하다고 평가 (숫자는 추출 불확실) |
| F01-135 | 38 | 저자들의 교훈: 사고는 단순하지 않다. 사고 원인을 확정했다고 믿는 경향과, 현재 소프트웨어 버그만 고치면 재발을 막는다는 가정이 실수였다. "항상 또 다른 소프트웨어 버그가 있다." 기여 요인에 "소프트웨어에 대한 과신과 hardware interlock의 제거 (소프트웨어를 single point of failure로 만듦)"가 있다. | "overconfidence in the software and removal of hardware interlocks" | 38쪽. 원문은 "making the software into a single point of failure" |
| F01-136 | 39 | 교훈: 소프트웨어에 안전의 전적인 책임을 맡기지 말고 단일 소프트웨어 오류가 파국이 되게 설계하지 말라. 첫 안전 분석이 소프트웨어를 포함하지 않았다. 소프트웨어가 오퍼레이터에게 "거짓말"을 했고 기계는 대량 과조사를 감지하지 못했다 (이온 챔버 포화). | "Software should not be assigned sole responsibility for safety" | 원문은 "software needs to be treated as a single component"와 이어짐 |
| F01-137 | 39 | 교훈: 컴퓨터 관련 사고 대부분은 코딩 오류가 아니라 요구사항의 오류(누락, 환경 조건과 시스템 상태의 잘못된 처리)에서 나왔다. Therac-25는 코딩 오류가 관여한 드문 경우다. | "most computer-related accidents have not involved coding errors but rather errors in the software requirements" | 이 장의 "요구사항의 결함" 패턴에 대한 저자 의견 |
| F01-138 | 39 | 교훈 (재사용): 소프트웨어를 재사용하면 새 시스템의 안전이 보장되지 않고, 때로 어색하고 위험한 설계가 나온다. 안전은 소프트웨어 자체가 아니라 소프트웨어가 쓰이는 시스템의 성질이다. | "Safety is a quality of the system in which the software is used" | 원문 이어서: "it is not a quality of the software itself" |
| F01-139 | 39 | 교훈 (수치에 대한 경계): 안전 분석의 수치 출력에 지나치게 의존하지 말라. Hamilton 사고 뒤 microswitch 수정으로 안전이 5자릿수 높아졌다는 주장은 정당화하기 어렵다. | "overreliance on the numerical output of safety analyses is unwise" | 원문은 "Finally, overreliance on..." |

## 8. 장 계획이 기대했지만 문서에 없던 것

- Toyota: 2005 Camry 소프트웨어에서 UA를 일으킨 결함이라고 NASA가 확정한 것. NASA는 시나리오 둘을 가설로만 적고 소프트웨어 경로는 찾지 못했다고 적는다. 원인이 확정되지 않은 사례다.
- Toyota: 사망자 수. 읽은 NASA 쪽은 VOQ 건수만 있고 사망자 수가 없다. Koopman 슬라이드는 Bookout 사건의 사망 한 건만 언급한다.
- Toyota: Koopman이 인용한 NASA 부록 A(코드 품질 수치, 전역 변수, 재귀, watchdog)의 원문은 내가 읽지 않았다. 슬라이드의 수치가 NASA 보고서와 일치하는지 미확인이다. 원고에 쓰려면 부록 A 해당 쪽을 열어 확인해야 한다.
- Toyota: 재판의 판결문이나 법정 기록. Koopman 슬라이드의 요약뿐이다.
- Ariane 501: 사고의 금전 피해, 탑재물, 날짜, 무인 여부. 읽은 쪽 7-13, 17-18에 없다 ((기억): 1996년 6월, 무인 발사였고 Cluster 위성을 실었다. 근거로 쓰지 않는다).
- Ariane 501: 이 사례에 대한 다툼은 읽은 쪽에 없다 (위원회가 기술 원인을 "합리적 의심 없이" 확립했다고 적음).
- 737 MAX: KNKT 50-52쪽 서술은 MCAS가 해당 쪽의 기능 서술일 뿐이고, "단일 센서 의존"이라는 평가는 196쪽과 217쪽에 있다 (50-52쪽은 설명만).
- 737 MAX: 두 사고의 최종 조사 보고서 중 Ethiopian 302(ET302)의 공식 보고서는 받은 문서에 없다. ET302의 사실은 NTSB ASR1901과 House 보고서의 간접 서술뿐이다.
- 737 MAX: House 보고서는 위원회 다수당 직원의 보고서다. Boeing의 반론이나 FAA의 같은 사안에 대한 반박은 이 문서 안에 거의 없다. "다툼이 있는 부분"으로 쓰려면 Boeing과 FAA의 공식 입장 문서가 필요하다.
- Therac-25: MIT 저자 페이지(sunnyday.mit.edu)는 연결이 거부되어 읽지 못했고, RIT 사본으로 대신했다. 사고 6건의 날짜, 장소, 사망 한 건씩의 정확한 대응(어느 환자가 언제 죽었는가)은 내가 일부만 확인했다. 원고에 쓰려면 23-33쪽을 직접 읽어야 한다.
- Therac-25: 저자들 자신이 제조사 내부 문서와 소프트웨어 개발 이력은 얻지 못했다고 적는다. 즉 개발 과정의 서술은 추정이다.
