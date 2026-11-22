# 21장. 드론: 운용 위험 기반의 방식 - 장 계획

원고: [chapters/ch21-drones.md](../chapters/ch21-drones.md)

| 항목 | 내용 |
|---|---|
| Part | V. 넓히기 |
| 쓰는 단계 | 단계 3 (넓히기) |
| 상태 | 미착수 |

## 핵심 질문

동력을 끊는 것이 안전하지 않은 기계는 어떻게 안전해지는가? 제품이 아니라 운용을 기준으로 위험을 따지면 무엇이 달라지는가?

## 다룰 내용

- 단일 규격이 없는 분야: 규제, 운용 위험 평가, 업계 규격의 조합
- 운용 범주: Open, Specific, Certified (EU 규정 2019/947)
- SORA: ground risk와 air risk, SAIL, operational safety objective, 요구 수준 (integrity와 assurance), containment
- 동력을 끊는 것이 safe state가 아닌 시스템: 제자리 비행, 출발점 복귀, 착륙, flight termination, parachute
- 드론의 safety mechanism: geofence, 조종 link 상실 대응, 위치 정보 상실 대응, battery 감시, 센서 중복과 상태 추정 감시
- run-time assurance 구조 (ASTM F3269): 복잡한 기능을 단순한 감시기와 대체 제어기로 감싸기. 11장의 monitor 구조와 연결
- 공개 autopilot (PX4, ArduPilot)의 failsafe 문서 읽기

## 검토에서 더한 항목 (2026-11-22)

괄호 안은 지적 번호이고, 검토 기록은 `reviews/2026-11-22-plan/`에 있다. 규격의 내용에 관한 항목은 쓰기 전에 확인한다 (RULES.md 5절).

- 장의 중심 사슬: SORA -> SAIL -> OSO -> Special Condition Light-UAS -> 소프트웨어 보증 (F-23)
- 소프트웨어 보증의 경로를 EU와 미국으로 나눠 적는다. EU: SAIL IV는 DAL C 수준, SAIL V와 VI는 failure condition에 따른 DAL B-D. 미국: ASTM F3201 (F-07, F-08)
- 상태 기계: link 상실, geofence 이탈, 위치 상실. 공개 autopilot의 failsafe 표와 대응시킨다 (E-23)
- geofence는 벗어난 뒤에 작동한다는 점, 고장이 겹치면 가장 심각한 대응이 선택된다는 점 (E-23)
- flight termination은 safe state가 아니라 지상의 위험을 가두는 수단이다 (F-09)
- 공개 autopilot의 소스 코드는 읽지 않는다. 문서와 상태 기계 그림으로 대신한다 (E-23)
- 미국과 한국의 제도는 쓰는 시점에 확인하는 상자로 줄인다 (F-23)
- 저자의 결정 (2026-11-22, PLAN.md 12절): EU의 제도를 중심으로 쓰고 미국의 제도는 한 문단으로 둔다. 미국의 UAS 제도는 받은 문서에 없으므로, 쓰기 전에 직접 읽을 수 있는 공개 문서를 찾는다. 찾지 못하면 그 문단은 `(확인 필요)`로 두거나 쓰지 않는다

## 예제 산출물

소형 multicopter 운용 하나의 SAIL 결정, link 상실과 geofence 이탈과 위치 상실에 대한 상태 기계 설계. 세 분야의 safe state 비교표

## 관련 규격과 자료

JARUS SORA 2.5; EU 규정 2019/947과 EASA AMC, GM; EASA Special Condition Light-UAS; ASTM F3201; ASTM F3269; EUROCAE ED-280; DO-178C

받은 문서: sora-2-5-main-body, easa-ed-2025-018-r-annex, easa-ear-uas, easa-sc-light-uas-medium-risk, easa-moc-light-uas-2510, easa-moc-light-uas-high-risk-2510, faa-ac-20-115d

## 근거 위치 (2026-11-22)

받은 문서에서 이 장을 뒷받침하는 곳이다. 쪽은 PDF 파일의 몇 번째 쪽인지다. 에이전트가 문서를 읽어 뽑은 것이므로, 원고에 쓰기 전에 그 쪽을 직접 읽어 확인한다 (RULES.md 5.2절).

| 문서 | 절 | 쪽 | 뒷받침하는 내용 |
|---|---|---|---|
| `easa-ear-uas` | Article 3 Categories of UAS operations, GM1 Article 3 | 31 | open, specific, certified 세 범주와 각 범주의 승인 방식(open은 사전 승인 없음, specific은 운용 승인, certified는 UAS 인증과 운영자 인증). specific과 certified의 경계 |
| `easa-ear-uas` | Article 4 'Open' category of UAS operations | 32 | open 범주의 조건(25 kg 미만, VLOS, 120 m 이하 등) |
| `easa-ear-uas` | Article 5 'Specific' category of UAS operations | 32-33 | open 조건을 못 맞추면 위험 평가(Article 11)와 운용 승인이 필요하다는 규정 |
| `easa-ear-uas` | Article 6 'Certified' category of UAS operations, GM1 Article 6 | 34 | certified 범주 조건(사람 위 비행 등)과 위험 평가에서 완화가 불가능하다고 판단될 때 certified가 된다는 규정 |
| `easa-ear-uas` | Article 40 of Regulation (EU) 2019/945 (certified and specific categories) | 586 | UAS의 설계, 생산, 정비를 인증해야 하는 조건 |
| `easa-ear-uas` | Article 11 Rules for conducting an operational risk assessment | 37-38 | 운용 위험 평가가 운용 특성 기술, 안전 목표 제안, 지상과 공중 위험 식별, 완화와 robustness 수준 결정을 포함해야 한다는 규정. 목표 안전 수준은 유인 항공과 동등 |
| `easa-sc-light-uas-medium-risk` | Introductory note (Identification of issue) | 1-2 | 단일 규격이 없어 유인기 CS에 special condition을 붙이거나 JARUS 문서에 기반한 special condition으로 인증 기반을 정해 왔고, 객체 기반 (objective-based) special condition을 새로 만든 배경. high risk는 SAIL V, VI |
| `easa-sc-light-uas-medium-risk` | Applicability / An objective-based, operation centric and proportional approach | 3-4 | 적용 범위(SAIL III, IV, MTOM 600 kg 이하), 운용 중심 접근, 설계 관련 OSO와 mitigation means와의 관계(SORA의 SAIL -> OSO -> special condition 사슬) |
| `easa-sc-light-uas-medium-risk` | Light-UAS.2010 Accepted Means of Compliance | 9 | EASA의 AMC나 합의 표준(EASA가 수용한 경우)으로 special condition을 충족한다는 규정 (means of compliance 항목) |
| `easa-sc-light-uas-medium-risk` | Light-UAS.2510 Equipment, Systems and Installation | 17-18 | 개연적 고장에서 위험 최소화, 단일 고장이 catastrophic을 일으키지 않을 것, SAIL IV는 고장의 검출 경보 관리 수단 |
| `easa-sc-light-uas-medium-risk` | Light-UAS.2511 Containment | 18-19 | 운용 체적 밖으로 나가는 고장의 제한, 지상 위험 buffer 밖으로의 단일 고장 금지, 이를 일으킬 수 있는 소프트웨어와 전자 하드웨어는 EASA가 수용한 표준이나 방법으로 개발 |
| `easa-sc-light-uas-medium-risk` | Light-UAS.2512 Mitigation Means linked with Design | 19 | parachute, frangible 설계 같은 설계 연계 완화 수단의 성능 입증 |
| `easa-sc-light-uas-medium-risk` | Light-UAS.2529 UAS Navigation Function | 20 | UA가 공간 제한 또는 의도한 경로 안에 머물게 하는 기능 (geofence 항목의 근거. 'geofence'라는 단어는 없음) |
| `easa-sc-light-uas-medium-risk` | Light-UAS.2575 Command, Control and Communication Contingency | 21 | C2 기능 상실이나 열화 시 UAS가 적절한 contingency 절차를 시작하고 비행 매뉴얼에 규정 (조종 link 상실 대응 항목) |
| `easa-sc-light-uas-medium-risk` | Subpart H C2 Link: Light-UAS.2715, 2720, 2730 | 25 | C2 link 성능의 적절성, 지속적 성능 감시, 보안 |
| `easa-sc-light-uas-medium-risk` | Light-UAS.2430 Energy storage and distribution systems | 16 | 에너지 저장 장치가 안전 기능에 충분한 에너지를 공급하고 정상, 열화 상태와 남은 에너지를 원격 승무원에게 알리도록 요구 (battery 감시 항목) |
| `easa-sc-light-uas-medium-risk` | Light-UAS.2350 Forced landing or a crash | 14 | 비상 절차에 강제 착륙이나 추락이 포함되면 파편, 화재가 구역 밖으로 번지지 않도록 하는 자체 격리 설계 |
| `easa-sc-light-uas-medium-risk` | Light-UAS.2000 Applicability and Definitions, (b)(4) | 8 | 'continued safe flight and landing'의 정의 (가능하면 비상 절차를 써서 계속 제어 비행과 착륙) |
| `easa-moc-light-uas-2510` | Safety Objectives; Compliance with Light-UAS.2510(a)(1) | 6-7 | SAIL IV의 안전 목표(LOC 고장 조건은 probable이 아님, 단일 고장이 catastrophic을 못 일으킴, 직접 LOC를 일으키는 개발 오류에 적절한 엄격함). LOC 사례 목록(FTS, parachute의 오작동 활성화와 운용 체적 이탈 포함). 허용 LOC 확률 10^-4/FH 수준과 기술 원인 10^-5/FH 수준 |
| `easa-moc-light-uas-2510` | Compliance with Light-UAS.2510(a)(1) (emergency systems) | 8 | FTS 같은 M2와 containment 수단은 제어를 이미 잃은 뒤에 위험을 줄이는 비상 장치이고 오작동(잘못된 활성화)이 LOC가 되어 DAL을 좌우할 수 있다는 서술 (flight termination 항목) |
| `easa-moc-light-uas-2510` | 7.1 Development Assurance | 9 | 소프트웨어가 포함된 시스템은 simple이 아니고, ED-79B, AMC 20-115D, AMC 20-152A의 DAL C 목표를 수용 가능한 means of compliance로 쓸 수 있다는 서술 (SAIL IV와 DAL C 수준) |
| `easa-moc-light-uas-2510` | Compliance with Light-UAS.2510(a)(2), (a)(3) | 9-11 | 단일 고장과 공통 원인 고장(공통 하드웨어, 소프트웨어, 전원, GNSS 같은 외부 자원) 검토, 고장 검출과 경보 수단을 UAS 기능으로 다루고 그 오작동도 평가 |
| `easa-moc-light-uas-high-risk-2510` | Failure Condition classification | 8 | no safety effect, minor, major, hazardous, catastrophic 정의 |
| `easa-moc-light-uas-high-risk-2510` | 8.1 Safety Objectives per SAIL and failure condition classification (Table 1) | 9-10 | SAIL V, VI의 failure condition별 확률 목표와 FDAL(major D, hazardous C, catastrophic B), 아키텍처에 의한 FDAL/IDAL 배정 원칙 |
| `easa-moc-light-uas-high-risk-2510` | 9.1.1 Relationship with Light-UAS.2511, 9.1.2 Relationship with Light-UAS.2512 | 11-12 | 운용 체적 안에서 FTS가 잘못 활성화되면 catastrophic으로 보고, FTS, parachute 같은 수단을 쓸 때 그 손실과 오작동을 평가하며 완화 효과 상실을 catastrophic으로 보는 서술 |
| `easa-moc-light-uas-high-risk-2510` | 9.3 Development Assurance (9.3.1-9.3.4) | 13-14 | DAL 배정, UAS 단계 보증은 ED-79B/ARP4754B, 소프트웨어는 AMC 20-115, 하드웨어는 AMC 20-152를 수용 (SAIL V, VI의 항공 규격 경로) |
| `easa-moc-light-uas-high-risk-2510` | Definitions (k) FDAL, (m) IDAL and Principles of Fail-Safe design concept | 5-7 | FDAL과 IDAL의 정의, fail-safe 설계 개념 |
| `faa-ac-20-115d` | 1. Purpose, 6. Using EUROCAE ED-12C and RTCA DO-178C | 1, 3-4 | FAA가 DO-178C(ED-12C)를 소프트웨어 개발 보증의 수용 가능한 방법으로 인정하고, 배정된 소프트웨어 level의 목표를 모두 충족해야 한다는 서술 (미국 경로의 일부. UAS 전용 문서는 아님) |
| `faa-ac-20-115d` | 9. Modifying and Re-using Software ..., (b)(2) | 8 | system safety process가 failure condition 심각도로 소프트웨어 개발 보증 level을 정하고 Table 1이 구 level과의 대응을 보임 |
| `sora-2-5-main-body` | The SORA methodology (Steps #1-#10) | 15-17 | SORA 열 단계의 개관과 SAIL I-VI, 17개 OSO, containment 3 수준 |
| `sora-2-5-main-body` | 1.1 Preface, 1.2 Purpose of the document | 18-19 | SORA가 처방적 요구가 아니라 위험에 비례한 robustness의 safety objective를 제시하고 specific 범주 승인용이라는 서술 |
| `sora-2-5-main-body` | 2.2 Semantic model (2.2.1-2.2.4) | 22-23 | flight geography, contingency volume, operational volume, ground risk buffer의 정의. contingency volume 진입은 이상 상황 |
| `sora-2-5-main-body` | 2.3 States of the Operation (2.3.1, 2.3.2) | 24-25 | in control(정상, 이상 상황과 contingency 절차)과 loss of control(emergency 절차, FTS, ERP, containment)의 구분. 계획에 없던 flight termination은 loss of control |
| `sora-2-5-main-body` | 2.4 Robustness (Table 1) | 25-26 | integrity와 assurance가 합쳐진 robustness, low, medium, high와 Table 1의 최솟값 규칙 |
| `sora-2-5-main-body` | 4.2 Step #2 iGRC (Table 2) | 33-34 | UA 크기, 속도, 인구 밀도로 iGRC 결정 |
| `sora-2-5-main-body` | 4.3 Step #3 Final GRC (Table 5) | 38-40 | M1(A), M1(B), M1(C), M2 완화의 GRC 감소량과 GRC 7 초과는 SORA 밖 |
| `sora-2-5-main-body` | 4.4 Step #4 initial ARC - 4.6 Step #6 TMPR (Table 6) | 40-46 | initial ARC, 전략적 완화로 잔여 ARC, 전술적 완화 성능 요구(TMPR) |
| `sora-2-5-main-body` | 4.7 Step #7 SAIL determination (Table 7) | 47-48 | 최종 GRC와 잔여 ARC로 SAIL I-VI 결정 |
| `sora-2-5-main-body` | 4.8 Step #8 Containment requirements (Tables 8-13) | 48-53 | adjacent area, 인구 밀도, UA 크기, SAIL로 containment robustness 결정 |
| `sora-2-5-main-body` | 4.9 Step #9 Operational Safety Objectives (Table 14) | 53-55 | SAIL별 OSO robustness 표(OSO#05 UAS 설계의 시스템 안전과 신뢰성, OSO#06 C3 link 등) |
| `easa-ed-2025-018-r-annex` | S.0 Executive summary (AMC1 Article 11, SORA 2.5 EASA 판) | 3-4 | 목표 안전 수준(지상 10^-6 사망/FH, 공중 충돌)과 SAIL이 허용 loss-of-control 비율을 운용, 설계 등의 통제에 대응시킨다는 서술 |
| `easa-ed-2025-018-r-annex` | Annex A (A.5.2.3 Computation of the contingency volume) | 74-77 | 반응 시간, multirotor 정지(hover)까지의 거리, parachute 개방 시간으로 contingency volume을 계산하는 예. 자동 시스템(예: geofence)은 반응 시간이 짧을 수 있다는 언급 (geofence는 경계에 도달한 뒤 작동하는 대응이라는 항목의 근거) |
| `easa-ed-2025-018-r-annex` | Annex B, B.5 M2 Effects of UA impact dynamics are reduced | 91-95 | M2(예: parachute) 완화의 integrity, assurance 기준. M2 효과를 해치는 단일 고장 금지 |
| `easa-ed-2025-018-r-annex` | Annex E, E.2 OSO #05 - The UAS is designed considering system safety and reliability | 107-110 | OSO #05의 SAIL별 integrity, assurance(SAIL III, IV, V와 VI), SW와 AEH를 산업 표준이나 EASA 수용 방법으로 개발, MoC Light-UAS.2510으로 충족 가능 |
| `easa-ed-2025-018-r-annex` | Annex E, OSO #06 C3 link characteristics | 111-114 | C2 link를 포함하는 C3 link의 성능 요구, 감시, 면허 대역 사용(SAIL IV 이상)과 비행 매뉴얼 기재 |
| `easa-ed-2025-018-r-annex` | Annex E, E.4 Containment requirements | 149-152 | containment의 integrity 기준(운용 체적 containment, 비행 종료, ground risk buffer 정의와 containment, FTS나 독립 비상 비행 제어나 tether 예) |
| `easa-ed-2025-018-r-annex` | Annex I (glossary): I.54 Emergency recovery, I.55 Emergency procedures, I.63 Flight termination system, I.64 Fly-away, I.66-I.68 Geo-awareness, Geo-caging, Geo-fencing, I.86 Lost C2 link | 162-165 | return-to-home 같은 비상 복구, 비행 종료, fly-away, geo-awareness, geo-caging, geo-fencing, lost C2 link의 용어 정의 |
| `easa-ed-2025-018-r-annex` | GM1 UAS.SPEC.030(3)(e) (operations manual contents), item 6 Emergency procedures | 195 | 비상 절차의 예: 즉시 착륙, FTS로 비행 종료, 통제된 추락 |

### 받은 문서에 근거가 없는 항목

이 항목은 다른 공개 문서를 찾거나, `(2차 자료)`로 밝히거나, 쓰지 않는다.

- ASTM F3201 (미국의 소프트웨어 보증 경로) - 받은 문서에 없다. faa-ac-20-115d는 DO-178C를 인정하는 항공기 일반 문서이고 UAS 전용이 아니다
- ASTM F3269 run-time assurance와 11장 monitor 구조와의 연결 - 받은 문서에 없다
- 공개 autopilot (PX4, ArduPilot)의 failsafe 문서와 상태 기계 대응 (E-23) - 받은 문서에 없다. 고장이 겹치면 가장 심각한 대응이 선택된다는 점도 같은 이유로 근거가 없다
- geofence는 벗어난 뒤에 작동한다는 점 - 정의(geo-fencing은 UA가 정해진 체적에 들어가는 것을 막는 자동 기능, ED Annex I.68, p163)와 contingency volume 계산(p74-77, p23 SORA)에서 유추할 뿐, 같은 취지를 직접 말한 문장은 없다
- 위치 정보 상실 대응, 센서 중복과 상태 추정 감시 - 위치 정보 상실에 대응하라는 요구문은 없다. UAS가 공간 제한 안에 머무는 기능(SC Light-UAS.2529, p20)과 GNSS를 공통 자원으로 보고 공통 원인 고장을 검토하라는 서술(MoC 2510 p10)만 있다
- "공중에서 동력을 끊는 것은 safe state가 아니다"라는 문장 - 받은 문서에 이 문장은 없다. 가까운 근거는 비행 종료가 loss of control에 해당한다는 규정(SORA p25)과 FTS가 제어를 잃은 뒤의 비상 장치라는 서술(MoC 2510 p8)이다
- 제자리 비행, 출발점 복귀, 착륙의 상태 기계 설계 - 설계 지침은 없고, 용어(emergency recovery의 예로 return-to-home, ED Annex I.54, p162)와 비상 절차의 예(즉시 착륙, FTS, 통제된 추락, ED p195), 정지까지의 거리 계산(hover, p76)만 있다
- SAIL V와 VI용 Special Condition 본문 (SC Light-UAS High Risk) - 받은 문서는 medium risk (SAIL III, IV)의 special condition과 두 MoC뿐이다. 고위험 SC가 있다는 것은 MoC high risk p1-2에서 확인된다
- EUROCAE ED-280, ED-79B/ARP4754B, DO-178C 본문 - 받은 문서는 이것들을 가리키기만 한다(MoC p3, MoC high risk p3, FAA AC p1). 내용은 확인할 수 없다
- JARUS SORA의 Annex 본문 (Annex B, C, D, E, F) - sora-2-5-main-body는 본문만이다. 같은 내용의 EASA 판은 easa-ed-2025-018-r-annex (SORA 2.5, 2025년 9월 판)에서 읽을 수 있다
- 미국과 한국의 UAS 제도 - 받은 문서에 없다 (faa-ac-20-115d는 소프트웨어 개발 보증 문서)
- 소프트웨어 보증의 SAIL IV와 DAL C - MoC 2510 p9는 DAL C 목표를 "수용 가능한 방법으로 쓸 수 있고 더 느슨한 목표도 수용될 수 있다"고 쓴다. 규격이 DAL C를 요구한다는 문장으로 쓰면 안 된다
