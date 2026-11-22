# 20장. 로봇: 기계류 안전의 방식 - 장 계획

원고: [chapters/ch20-robots.md](../chapters/ch20-robots.md)

| 항목 | 내용 |
|---|---|
| Part | V. 넓히기 |
| 쓰는 단계 | 단계 3 (넓히기) |
| 상태 | 미착수 |

## 핵심 질문

사람 옆에서 움직이는 기계의 안전은 자동차와 무엇이 같고 무엇이 다른가?

## 다룰 내용

- 기계류 안전의 틀: ISO 12100 risk assessment와 3단계 위험 감소 (본질적 안전 설계, 보호 장치, 사용 정보)
- safety function과 required performance level. PL과 SIL의 관계
- ISO 13849-1의 구조 요구: Category, 부품 신뢰도, diagnostic coverage, common cause failure
- ISO 13849-1의 소프트웨어 요구: embedded software와 application software의 구분, ISO 26262-6과의 깊이 차이
- 로봇 규격이 정하는 safety function: protective stop, emergency stop, 속도와 위치 제한, speed and separation monitoring, power and force limiting
- 로봇 종류별 규격: 산업용 로봇 (ISO 10218-1, -2), 서비스 로봇 (ISO 13482), 이동 로봇 (ISO 3691-4)
- 흔한 구조: 안전 등급을 받은 controller와 일반 소프트웨어 (예: ROS 2)의 분리
- 정지가 safe state인 시스템의 설계와 그 한계

## 검토에서 더한 항목 (2026-11-22)

괄호 안은 지적 번호이고, 검토 기록은 `reviews/2026-11-22-plan/`에 있다. 규격의 내용에 관한 항목은 쓰기 전에 확인한다 (RULES.md 5절).

- 안전 기능은 인증된 보호 장치 (safety laser scanner)와 safety controller가 수행한다. 일반 소프트웨어 (예: ROS 2)는 안전 장치가 아니다 (E-21)
- ISO 13849-1:2023의 소프트웨어 요구: embedded software와 application software, 제한된 언어와 범용 언어의 구분 (F-21)
- risk graph로 요구 등급을 정하는 법 (F-21)
- ISO 10218:2025에서 달라진 점은 1쪽 상자로 쓴다. 협동 작업은 표 한 칸으로 줄인다 (F-20, E-22)
- EU Machinery Regulation 2023/1230 (2027-01-20 적용) (F-19)
- 정지에도 거리, 시간, 짐, 경사가 걸린다는 점 (F-09)

## 예제 산출물

자율 이동 로봇의 속도에 따른 보호 영역 전환과 정지: 안전 기능의 정의, risk graph로 정한 요구 등급, Category 구조, 정지 거리 예산 (응답 시간 + 제동 거리 <= 감지 거리), 일반 소프트웨어와 safety controller의 경계 그림. 관통 예제와의 비교표

## 관련 규격과 자료

ISO 12100; ISO 13849-1, -2; IEC 62061; ISO 10218-1, -2; ISO 13482; ISO 3691-4

받은 문서: ifa-report-2-2017e (ISO 13849-1의 2015년 판 기준)

## 근거 위치 (2026-11-22)

받은 문서에서 이 장을 뒷받침하는 곳이다. 쪽은 PDF 파일의 몇 번째 쪽인지다. 에이전트가 문서를 읽어 뽑은 것이므로, 원고에 쓰기 전에 그 쪽을 직접 읽어 확인한다 (RULES.md 5.2절).

| 문서 | 절 | 쪽 | 뒷받침하는 내용 |
|---|---|---|---|
| `ifa-report-2-2017e` | 3 Generic standards concerning the functional safety of machinery control systems | 15-16 | 기계류에서 IEC 61508/IEC 62061의 SIL(1-3, 기계류에서 SIL 4는 다루지 않음)과 ISO 13849-1의 PL(a-e)이 PFHD 구간으로 대응되는 관계. PL a는 SIL과 대응 없음, b와 c는 SIL 1, d는 SIL 2, e는 SIL 3. low demand(PFDavg)와 high demand/continuous(PFHD) 구분 |
| `ifa-report-2-2017e` | 4.1 Identification of safety functions and their properties | 19-20 | ISO 12100 risk assessment에서 출발해 safety function을 정하고 PLr을 정하는 반복 과정(Fig 4.1). 본질적 안전 설계 -> 보호 장치(안전 제어 포함) 순서. 같은 하드웨어도 safety function마다 요구 PL이 다를 수 있음 |
| `ifa-report-2-2017e` | 5.2 Risk reduction strategy (5.2.1 Risk estimation, 5.2.2 Risk evaluation) | 25-27 | ISO 12100 3단계 위험 감소(본질적 안전 설계, safeguard, 사용 정보)를 도식(Fig 5.1)으로 보임. 위험 추정의 요소(피해의 심각도, 노출, 위험 사건의 발생, 회피 가능성). 위험 평가의 판단 기준 |
| `ifa-report-2-2017e` | 5.3 Identification of the required safety functions and their properties | 28-29 | 본질적 안전 설계가 우선이고, 사용 정보(조직적 조치)는 경제적으로 타당한 기술적 보호가 불가능한 예외에만 허용된다는 서술. 안전 제어는 sensor-logic-actuator로 safety function을 수행(Fig 5.4) |
| `ifa-report-2-2017e` | 5.3.1 Definition of safety functions | 29-30 | safety function 예시(정지와 정지 유지, 사람이 위험 구역에 들어오면 로봇이 피하는 기능 등). Table 5.1(ISO 13849-1의 safety function: 보호 장치로 시작하는 정지, 비상 정지, hold-to-run, enabling, muting 등)과 Table 5.2(IEC 61800-5-2의 STO, SS1, SS2, SOS, SLS, SLT, SLP 등). 정의할 때 정할 특성(응답 시간, 우선순위, 고장 검출 시 응답 등) |
| `ifa-report-2-2017e` | 5.3.2 Examples in which the definition of the safety function has an influence upon subsequent calculation of the PFHD | 30-32 | safety function을 어떻게 나누느냐가 PFHD 합산과 달성 PL을 좌우한다는 설명(국소적 접근, 비상 정지의 worst case) |
| `ifa-report-2-2017e` | 5.4 Determining of the required Performance Level PLr, 5.4.1 Risk graph | 32-34 | risk graph(S1/S2, F1/F2, P1/P2)로 PLr a-e를 정하는 법. 다른 독립 보호 조치는 PLr 결정에서 효과가 있다고 가정 가능. F2 판정 기준(15분마다 이상 개입 등), 위험 사건 발생 확률이 낮으면 PLr을 한 단계 낮출 수 있으나 PL a 아래로는 못 내림(3판에서 추가) |
| `ifa-report-2-2017e` | 4.4 Changes arising from the third edition of the standard published in 2015 | 22 | 2015년 3판의 주요 변경(위험 사건 발생 확률의 반영, 출력부 PL의 간이 결정법, 표준 부품 사용 시 SRESW 요구의 취급) |
| `ifa-report-2-2017e` | 4.5 Future development of EN ISO 13849-1 | 22 | 3판 출간 직후 개정 착수가 결정되었고 소프트웨어 요구의 전면 개정이 과제로 꼽혔다는 서술 (2023년 판의 내용은 없음) |
| `ifa-report-2-2017e` | 4.2 Design and technical implementation of the safety functions | 20-21 | Category가 PL 결정의 기초이고 MTTFD, DCavg, CCF가 보완. Table 4.1(Category B, 1, 2, 3, 4별 특성). 체계적 고장과 소프트웨어는 PL에 따라 단계화된 조치로 다룸 |
| `ifa-report-2-2017e` | 6.2.2 Categories ... 6.2.7 Category 4 (Table 6.2) | 49-53 | Category B, 1, 2, 3, 4의 구조와 고장 시 동작 요약(Table 6.2, p50-51). Category 2는 검사 주기(수요의 100배 이상 또는 수요 시 즉시 검사)와 위험 도달 시간 조건, Category 3은 단일 고장 허용, Category 4는 고장 누적까지 고려 |
| `ifa-report-2-2017e` | 6.2.10 Fault consideration and fault exclusion | 55 | 고려할 고장의 범위와 고장 배제의 조건(기술적 불가능성, 일반 기술 경험 등)과 근거 기록 요구 |
| `ifa-report-2-2017e` | 6.2.11 Mean time to dangerous failure - MTTFD | 55-57 | MTTFD의 뜻(평균, 시간, dangerous)과 채널별 등급(low 3-10년, medium 10-30년, high 30-100년), 100년 상한(Category 4는 2,500년) |
| `ifa-report-2-2017e` | 6.2.14 Diagnostic coverage of test and monitoring measures - DC | 57-60 | DC의 정의식과 4단계(0, 60, 90, 99%), DCavg 가중 평균 공식. 검출만으로는 부족하고 제때 safe state에 들어가야 한다는 조건 |
| `ifa-report-2-2017e` | 6.2.15 Measures against common cause failure (CCF) | 60-61 | CCF 대책 8개 항목의 점수제(Category 2, 3, 4에서 65점/100점 이상), beta factor 2%와의 대응 |
| `ifa-report-2-2017e` | 6.2.16 Simplified determining of the PL by means of the bar chart | 61-62 | Category, DCavg, MTTFD로 PL을 읽는 bar chart 방법과 가정(임무 시간 20년). Category B는 최대 PL b |
| `ifa-report-2-2017e` | 6.3 Development of safety-related software (intro, 6.3.1) | 64-65 | ISO 13849-1에서 소프트웨어 요구가 2판에서 처음 생겼다는 점. SRESW(펌웨어, 안전 부품용)와 SRASW(응용 프로그램)의 구분, 언어 구분 FVL/LVL. SRASW를 FVL(예: C)로 쓰면 SRESW 요구를 적용하고, PL e는 IEC 61508-3:1998을 참조 |
| `ifa-report-2-2017e` | 6.3.2-6.3.5 (software specification, design, programming, tests) | 66-67 | 단순화한 V 모델, 소프트웨어 사양, 방어적 프로그래밍, 정적 분석(PL d, e는 data/control flow 검사), 낮은 PL의 신호가 높은 PL의 신호를 덮어쓰는 지점 점검, PL d, e의 확장 기능 시험 |
| `ifa-report-2-2017e` | 6.3.6 Structure of the normative requirements | 67-68 | 요구가 PLr에 따라 커지는 구조(PL a-b 기본 조치, c-e 추가 조치, Fig 6.12). 한 소프트웨어가 PLr이 다른 여러 safety function을 구현하면 가장 높은 PLr 기준 |
| `ifa-report-2-2017e` | 6.3.10 Requirements for the software of standard components in SRP/CS | 70-72 | 안전용이 아닌 표준 부품(PLC, 인버터)의 SRESW 요구를 PL, Category, 이종 두 채널 조건에 따라 면제하는 규칙(Table 6.6) |
| `ifa-report-2-2017e` | 6.1 Introduction (Fig 6.2) | 39-41 | 제어 시스템을 safety-related 부분(SRP/CS)과 일반 기능 제어로 나눈 구조. 에너지가 없는 상태에서 위험이 생기지 않으면 (de-energization, closed-circuit 원리) 구동부는 SRP/CS로 보지 않으나 외력(수직축)이 있으면 보강 필요(p40) |
| `ifa-report-2-2017e` | 6.1.1 Design and development process (Box 6.1) | 43-44 | safety requirements specification에 safe state, 에너지 상실 시 거동, 응답 시간, overrun 거리 등을 적는 항목 |
| `ifa-report-2-2017e` | 5.7.1 Definition of the limits of the machine | 35 | 부품 마모로 정지 시간이 길어질 수 있어 overrun 초과를 검출해 정지시켜야 한다는 예 |
| `ifa-report-2-2017e` | 7.3 Validation of the safety function | 90-91 | overrun과 안전 거리의 치수 검증이 기계 전체 통합 평가에 속한다는 서술 |
| `ifa-report-2-2017e` | 8.2.15 Protective device and hydraulics controlled by PLC - Category 3 - PL d (Example 15) | 148-149 | safety laser scanner(F1)와 safety PLC(K1)가 시험된 안전 부품이고 Category 3, PL d, 재시작 인터록과 PFHD 합산(1.4E-7/h)을 보인 예 |

### 받은 문서에 근거가 없는 항목

이 항목은 다른 공개 문서를 찾거나, `(2차 자료)`로 밝히거나, 쓰지 않는다.

- ISO 12100 원문의 위험 평가 절차 - IFA가 ISO 12100과 ISO 13849-1:2015를 설명한 것(2차 자료, 기준 판은 EN ISO 13849-1:2015, ISO 12100:2010)만 있다. 원문은 받은 문서가 아니다
- ISO 13849-1:2023의 소프트웨어 요구 (F-21) - IFA는 2015년 3판 기준이다. 2023년 판의 내용은 없고, 소프트웨어 요구의 전면 개정이 예고되었다는 서술(p22)만 있다. embedded와 application software, 제한된 언어와 범용 언어의 구분은 2015판 기준으로만 확인된다(p64-68)
- ISO 10218-1, -2 (산업용 로봇)와 ISO 10218:2025의 변경점 - 받은 문서에 없다. IFA는 로봇을 예로 한 줄(p29, p315)만 언급한다
- 협동 작업, speed and separation monitoring, power and force limiting - 받은 문서에 설명이 없다. IFA Table 5.2의 SSM(safe speed monitor)과 SLT(safely-limited torque)는 구동 장치 수준의 기능이고 로봇 협동 작업의 같은 이름 개념과 다르다
- protective stop의 로봇 규격상 정의 - 받은 문서에 없다. 보호 장치로 시작하는 정지(safety-related stop function)와 STO, SS1, SS2는 IFA p29-30에 있다
- ISO 13482 (서비스 로봇), ISO 3691-4 (이동 로봇) - 받은 문서에 없다
- EU Machinery Regulation 2023/1230 (2027-01-20 적용) - 받은 문서에 없다. IFA는 기계류 지침(Machinery Directive)을 다룬다(p25)
- ROS 2 같은 일반 소프트웨어와 safety controller의 분리 - ROS 2에 관한 문서가 없다. 표준 부품(PLC, 인버터)의 소프트웨어를 안전 기능에 쓸 때의 조건(IFA p70-72)과 시험된 안전 부품(laser scanner, safety PLC)을 쓰는 예(p148-149)만 근거가 된다. "일반 소프트웨어는 안전 장치가 아니다"를 문서가 그대로 말하지는 않는다. IFA는 조건을 달아 표준 부품의 사용을 허용한다
- 자율 이동 로봇의 속도에 따른 보호 영역 전환 - IFA의 laser scanner 예(Example 15, p148-149)는 고정된 감지 영역과 재시작 인터록이다. 영역 전환을 다루는 문서가 없다
- 정지 거리 예산 (응답 시간 + 제동 거리 <= 감지 거리)의 식 - IFA는 ISO 13855를 참조만 하고(p52, p125-126, p133) 식은 싣지 않는다. 검사와 정지에 걸리는 시간이 위험에 이르는 시간보다 짧아야 한다는 조건(p52)과 overrun이 마모로 늘 수 있다는 점(p35)만 있다
- 정지에 짐과 경사가 걸린다는 점 - 거리와 시간은 확인된다(p35, p52, p91, p133). 외력이 있는 축(수직축)에 보강이 필요하다는 서술(p40)이 가장 가깝고, 짐과 경사를 직접 말한 곳은 없다
- 로봇 규격이 safety function과 요구 등급을 정해 둔다는 서술 - IFA p25(각주 1)와 p29는 Type C 규격이 있으면 그것을 따르고 없으면 설계자가 safety function을 정한다고만 말한다. 로봇 규격이 무엇을 정하는지는 문서가 없다
- IEC 62061의 소프트웨어 요구 - IFA는 IEC 62061과 IEC 61508의 관계만 설명한다(p15-16)
