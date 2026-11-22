# 규격 목록

책에서 다루는 규격의 정식 명칭, 기준으로 삼는 판, 상태를 적는다. 상태는 2026-11-21과 2026-11-22에 확인했다.

- 규격 원문은 거의 모두 유료다 (접근 등급 C). 받을 수 있는 문서와 볼 수만 있는 문서는 [README.md](README.md)에 있다.
- "확인" 열의 뜻
  - `검색`: 발행 기관이나 판매처의 목록에서 명칭과 판을 확인했다.
  - `받은 문서`: 받아 둔 문서 안에서 명칭을 확인했다.
  - `기억`: 아직 확인하지 않았다. 본문에 쓰기 전에 확인한다.
- ISO는 제목의 구분에 긴 줄표를 쓴다. 이 문서에서는 `-`로 적었다.
- 2026-11-22 검토에서 더한 문서는 대부분 `기억`이다.

## 1. 기준 규격

### ISO 26262:2018, Road vehicles - Functional safety

2판이다. 이 책은 2판을 기준으로 쓴다.

3판의 상태 (2026-11-22 확인): Part 1, 2, 3, 4, 6, 8, 9의 초안 (DIS)이 ISO store에 올라 있다. Part 3의 초안 투표가 2026-10에 시작되었다는 기록이 있다. 발행일은 정해지지 않았고 2027년 이후로 보인다. Part 6이 초안 단계에 있으므로 10-16장은 "새 판에서 달라지는 점"을 따로 살펴야 한다. 초안에서 Part 3의 제목이 바뀐 것으로 보인다는 보고가 있다 (`기억`으로 다룬다).

2018년 판은 2024년에 다시 확인되어 현행이다.

| Part | 제목 | 쓰는 장 | 확인 |
|---|---|---|---|
| 1 | Vocabulary | 2 | 검색 |
| 2 | Management of functional safety | 5, 19 | 검색 |
| 3 | Concept phase | 6, 7 | 검색 |
| 4 | Product development at the system level | 7 | 검색 |
| 5 | Product development at the hardware level | 9 | 검색 |
| 6 | Product development at the software level | 10-16 | 검색 |
| 7 | Production, operation, service and decommissioning | 18 | 검색 |
| 8 | Supporting processes | 5, 10, 17, 18 | 검색 |
| 9 | Automotive safety integrity level (ASIL)-oriented and safety-oriented analyses | 7, 8, 11 | 검색 |
| 10 | Guidelines on ISO 26262 | 4, 17 | 검색 |
| 11 | Guidelines on application of ISO 26262 to semiconductors | 9 | 검색 |
| 12 | Adaptation of ISO 26262 for motorcycles | 다루지 않음 | 검색 |

Part 1-9와 12가 규범 (normative) 문서이고, Part 10과 11은 해설 (guideline)이다. Part 1은 용어만 정의한다.

한국어 번역본 (KS R ISO 26262)이 옮긴 판

| Part | 옮긴 판 | 확인 |
|---|---|---|
| 1, 2, 3, 4, 6, 7, 8, 9 | ISO 26262:2011 | 검색 |
| 10 | ISO 26262-10:2012 | 검색 |
| 5, 11, 12 | ISO 26262:2018 | 검색 |

번역본의 대부분이 1판을 옮긴 것이다. 이 책의 근거로는 2018년 판의 영문 원문을 쓴다.

### IEC 61508:2010, Functional safety of electrical/electronic/programmable electronic safety-related systems

Edition 2이다. Edition 3은 최종 승인 단계이고 아직 발행 전이다. Part 3의 최종 투표가 2026-11에 끝났다는 기록이 있다. 발행은 2026년 말에서 2027년 사이로 예상된다.

| Part | 제목 | 쓰는 장 | 확인 |
|---|---|---|---|
| 1 | General requirements | 3, 4, 5, 9 | 검색 |
| 2 | Requirements for electrical/electronic/programmable electronic safety-related systems | 9 | 검색 |
| 3 | Software requirements | 10-17 | 검색 |
| 4 | Definitions and abbreviations | 2 | 검색 |
| 5 | Examples of methods for the determination of safety integrity levels | 3, 6 | 검색 |
| 6 | Guidelines on the application of IEC 61508-2 and IEC 61508-3 | 9 | 검색 |
| 7 | Overview of techniques and measures | 8, 12, 13, 15 | 검색 |

한국어 번역본 (KS C IEC 61508-1 - -7)은 Edition 2를 옮긴 것이다 (`검색`).

어느 Part가 요구사항이고 어느 Part가 해설인지는 확인하지 못했다 (`기억`: Part 1-3이 요구사항, Part 4가 정의, Part 5-7이 해설).

관련 문서

| 문서 | 내용 | 확인 |
|---|---|---|
| IEC TS 61508-3-1:2016 | 기존 소프트웨어의 재사용. Edition 3에 합쳐진다는 기록이 있다 | 검색 |
| IEC TR 61508-3-3:2025 | 객체 지향 소프트웨어에 관한 해설 | 검색 |

## 2. 로봇 (20장)

| 규격 | 제목 | 상태 | 확인 |
|---|---|---|---|
| ISO 12100:2010 | Safety of machinery - General principles for design - Risk assessment and risk reduction | 현행. 개정 초안이 진행 중이다 | 검색 |
| ISO 13849-1:2023 | Safety of machinery - Safety-related parts of control systems - Part 1: General principles for design | 4판, 현행 | 검색 |
| ISO 13849-2:2012 | Safety of machinery - Safety-related parts of control systems - Part 2: Validation | 현행 | 기억 |
| IEC 62061:2021 | Safety of machinery - Functional safety of safety-related control systems | 현행 | 검색 |
| ISO 10218-1:2025 | Robotics - Safety requirements - Part 1: Industrial robots | 3판, 현행 | 검색 |
| ISO 10218-2:2025 | Robotics - Safety requirements - Part 2: Industrial robot applications and robot cells | 2판, 현행 | 검색 |
| ISO/TS 15066:2016 | Robots and robotic devices - Collaborative robots | 내용이 ISO 10218-2:2025에 통합되었다는 2차 자료가 있다. 폐지 여부는 확인하지 못했다 | 기억 |
| ISO 13482:2014 | Robots and robotic devices - Safety requirements for personal care robots | 2판 (Robotics - Safety requirements for service robots)이 최종 초안 승인 단계다. 발행 여부는 확인하지 못했다 | 검색 |
| ISO 3691-4:2023 | Industrial trucks - Safety requirements and verification - Part 4: Driverless industrial trucks and their systems | 2판, 현행. 개정 초안 진행 중 | 검색 |
| Regulation (EU) 2023/1230 | EU Machinery Regulation | 2027-01-20부터 적용된다 | 검색 |
| IEC 60204-1 | 기계의 전기 장비. 정지의 종류를 정한다 | - | 기억 |
| ISO 13850 | 비상 정지 | - | 기억 |
| IEC 61496-3 | 보호 장치 (laser scanner 등) | - | 기억 |
| ANSI/A3 R15.08 | 미국의 산업용 이동 로봇 규격 | - | 기억 |

## 3. 드론 (21장)

드론에는 단일 규격이 없다. 규제 문서, 위험 평가 방법, 업계 규격을 함께 쓴다.

| 문서 | 제목 | 상태 | 확인 |
|---|---|---|---|
| JARUS SORA 2.5 | Specific Operations Risk Assessment | 2024년 발행. EASA가 ED Decision 2025/018/R (2025-09)로 EU 규정의 AMC와 GM에 넣었다. SORA 2.0에 따른 기존 AMC도 효력이 있다 | 검색, 받은 문서 |
| Commission Implementing Regulation (EU) 2019/947 | 무인 항공기의 운용에 관한 규정 | 현행 | 받은 문서 |
| Commission Delegated Regulation (EU) 2019/945 | 무인 항공기 기체에 관한 규정 | 현행 | 받은 문서 |
| EASA SC Light-UAS Medium Risk | Special Condition Light-UAS, Issue 01 (2020) | 현행 | 받은 문서 |
| EASA MoC Light-UAS.2510-01 | SAIL IV용 means of compliance, Issue 1 (2024) | 현행 | 받은 문서 |
| EASA MoC Light-UAS High Risk.2510-01 | SAIL V와 VI용 means of compliance (2025) | 현행 | 받은 문서 |
| EASA AMC 20-115D | 항공 소프트웨어의 development assurance. DO-178C를 인정하는 문서 | 현행 | 받은 문서 |
| EUROCAE ED-79B / SAE ARP4754B | Guidelines for Development of Civil Aircraft and Systems | 현행 | 받은 문서 |
| EUROCAE ED-135 / SAE ARP4761A | 민간 항공기의 safety assessment 지침 | 현행 | 받은 문서 |
| EUROCAE ED-279 | Generic Functional Hazard Assessment (FHA) for UAS/RPAS | 현행 | 받은 문서 |
| EUROCAE ED-280 | Guidelines for UAS safety analysis for the Specific category | 현행 | 검색 |
| ASTM F3201-26 | Standard Practice for Ensuring Dependability of Software Used in Unmanned Aircraft Systems (UAS) | 현행. 2026년 판은 전면 개정판이다. 미국 FAA 규칙의 means of compliance로 쓰인다 | 검색 |
| ASTM F3269-21 | Standard Practice for Methods to Safely Bound Behavior of Aircraft Systems Containing Complex Functions Using Run-Time Assurance | 현행 | 검색 |
| ISO 21384-2:2021 | Unmanned aircraft systems - Part 2: UAS components | 현행 | 검색 |

"받은 문서"로 표시한 항공 문서 (AMC 20-115D, ED-79B, ED-135, ED-279)는 받은 EASA 문서가 참고 문서로 든 이름을 확인한 것이다. 그 문서 자체는 유료다.

## 4. 그 밖의 분야 (22장)

| 분야 | 규격 | 제목 | 확인 |
|---|---|---|---|
| 항공 | RTCA DO-178C | Software Considerations in Airborne Systems and Equipment Certification | 기억 |
| 항공 | RTCA DO-330 | Software Tool Qualification Considerations | 기억 |
| 항공 | RTCA DO-333 | Formal Methods Supplement to DO-178C and DO-278A | 기억 |
| 철도 | EN 50716:2023 | Railway Applications - Requirements for software development | 검색 |
| 철도 | EN 50126-1:2017 | Railway Applications - The Specification and Demonstration of Reliability, Availability, Maintainability and Safety (RAMS) - Part 1: Generic RAMS Process | 기억 |
| 철도 | EN 50129:2018 | Railway applications - Communication, signalling and processing systems - Safety related electronic systems for signalling | 기억 |
| 의료기기 | IEC 62304:2006+AMD1:2015 | Medical device software - Software life cycle processes | 기억 |
| 의료기기 | ISO 14971:2019 | Medical devices - Application of risk management to medical devices | 기억 |
| 공정 | IEC 61511-1:2016 | Functional safety - Safety instrumented systems for the process industry sector - Part 1 | 기억 |

- EN 50716:2023은 EN 50128과 EN 50657을 대체한다.
- IEC 62304는 2판이 진행 중이다. 적용 범위와 등급 체계가 바뀐다고 한다 (`검색`, 2차 자료).

## 5. Functional safety의 경계 (23장)

| 규격 | 제목 | 확인 |
|---|---|---|
| ISO 21448:2022 | Road vehicles - Safety of the intended functionality | 기억 |
| ISO/SAE 21434:2021 | Road vehicles - Cybersecurity engineering | 기억 |
| ISO/PAS 8800:2024 | Road vehicles - Safety and artificial intelligence | 기억 |
| ISO/IEC TR 5469:2024 | Artificial intelligence - Functional safety and AI systems | 기억 |
| ISO/TS 5083:2025 | Road vehicles - Safety for automated driving systems - Design, verification and validation | 기억 |
| UL 4600 | Standard for Safety for the Evaluation of Autonomous Products | 기억 |

## 6. 코딩 규칙과 그 밖의 문서 (13, 14, 18장)

| 문서 | 내용 | 확인 |
|---|---|---|
| MISRA C:2025 | C 언어의 coding guideline. 2025-03 발행 | 검색 |
| MISRA C++:2023 | C++ 언어의 coding guideline | 기억 |
| MISRA Compliance:2020 | MISRA 준수를 주장하는 방법 | 받은 문서 |
| SEI CERT C Coding Standard | C 언어의 secure coding 규칙 | 기억 |
| FAA AC 20-193 | multicore processor를 쓰는 항공 시스템에 대한 지침 | 받은 문서 |
| EASA AMC 20-193 | 위와 짝이 되는 EASA의 지침 | 기억 |
| UN R155 | 차량의 cybersecurity에 관한 UN 규정 | 기억 |
| UN R156 | 차량의 software update에 관한 UN 규정 | 기억 |
| ISO 24089 | Road vehicles - Software update engineering | 기억 |
