# 규격 목록

책에서 다루는 규격의 정식 명칭, 기준으로 삼는 판, 상태를 적는다. 상태는 2026-11-21과 2026-11-22에 확인했다.

- 규격 원문은 거의 모두 유료다 (접근 등급 C). 받을 수 있는 문서와 볼 수만 있는 문서는 [README.md](README.md)에 있다.
- "확인" 열의 뜻: `검색`은 발행 기관이나 판매처의 목록에서 명칭과 판을 확인했다는 뜻이고, `기억`은 아직 확인하지 않았다는 뜻이다. `기억`으로 표시한 줄은 본문에 쓰기 전에 확인한다.
- ISO는 제목의 구분에 긴 줄표를 쓴다. 이 문서에서는 `-`로 적었다.

## 1. 기준 규격

### ISO 26262:2018, Road vehicles - Functional safety

2판이다. 3판은 초안 단계이고 2027년 전후 발행이 예상되나 확정된 일정은 없다.

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

Part 10과 11은 해설 (guideline)이고 나머지가 요구사항이다.

### IEC 61508:2010, Functional safety of electrical/electronic/programmable electronic safety-related systems

Edition 2이다. Edition 3은 최종 승인 단계이고 아직 발행 전이다. 2027년 발행이 예상된다.

| Part | 제목 | 쓰는 장 | 확인 |
|---|---|---|---|
| 1 | General requirements | 3, 4, 5 | 검색 |
| 2 | Requirements for electrical/electronic/programmable electronic safety-related systems | 9 | 검색 |
| 3 | Software requirements | 10-17 | 검색 |
| 4 | Definitions and abbreviations | 2 | 검색 |
| 5 | Examples of methods for the determination of safety integrity levels | 3, 6 | 검색 |
| 6 | Guidelines on the application of IEC 61508-2 and IEC 61508-3 | 9 | 검색 |
| 7 | Overview of techniques and measures | 8, 12, 13, 15 | 검색 |

## 2. 로봇 (20장)

| 규격 | 제목 | 상태 | 확인 |
|---|---|---|---|
| ISO 12100:2010 | Safety of machinery - General principles for design - Risk assessment and risk reduction | 현행 | 기억 |
| ISO 13849-1:2023 | Safety of machinery - Safety-related parts of control systems - Part 1: General principles for design | 4판, 현행 | 검색 |
| ISO 13849-2:2012 | Safety of machinery - Safety-related parts of control systems - Part 2: Validation | 현행 | 기억 |
| IEC 62061:2021 | Safety of machinery - Functional safety of safety-related control systems | 현행 | 검색 |
| ISO 10218-1:2025 | Robotics - Safety requirements - Part 1: Industrial robots | 3판, 현행 | 검색 |
| ISO 10218-2:2025 | Robotics - Safety requirements - Part 2: Industrial robot applications and robot cells | 2판, 현행 | 검색 |
| ISO/TS 15066:2016 | Robots and robotic devices - Collaborative robots | 내용이 ISO 10218-2:2025에 통합되었다는 2차 자료가 있다. 폐지 여부는 확인하지 못했다 | 기억 |
| ISO 13482:2014 | Robots and robotic devices - Safety requirements for personal care robots | 2판 (Robotics - Safety requirements for service robots)이 최종 초안 승인 단계다. 발행 여부는 확인하지 못했다 | 검색 |
| ISO 3691-4:2023 | Industrial trucks - Safety requirements and verification - Part 4: Driverless industrial trucks and their systems | 2판, 현행. 개정 초안 진행 중 | 검색 |

## 3. 드론 (21장)

드론에는 단일 규격이 없다. 규제 문서, 위험 평가 방법, 업계 규격을 함께 쓴다.

| 문서 | 제목 | 상태 | 확인 |
|---|---|---|---|
| JARUS SORA 2.5 | Specific Operations Risk Assessment | 2024년 발행. EASA가 2025-09에 EU 규정의 AMC와 GM으로 채택 (ED Decision 2025/018/R) | 검색 |
| EU 규정 2019/947 | 무인 항공기 운용에 관한 EU 규정 | 현행 | 기억 |
| EASA SC Light-UAS | Special Condition Light-UAS | 현행 | 검색 |
| ASTM F3201-26 | Standard Practice for Ensuring Dependability of Software Used in Unmanned Aircraft Systems (UAS) | 현행. 2026년 판에서 크게 개정된 것으로 보인다 | 검색 |
| ASTM F3269-21 | Standard Practice for Methods to Safely Bound Behavior of Aircraft Systems Containing Complex Functions Using Run-Time Assurance | 현행 | 검색 |
| EUROCAE ED-280 | Guidelines for UAS safety analysis for the Specific category | 현행 | 검색 |
| ISO 21384-2:2021 | Unmanned aircraft systems - Part 2: UAS components | 현행 | 검색 |

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

EN 50716:2023은 EN 50128과 EN 50657을 대체한다.

## 5. Functional safety의 경계 (23장)

| 규격 | 제목 | 확인 |
|---|---|---|
| ISO 21448:2022 | Road vehicles - Safety of the intended functionality | 기억 |
| ISO/SAE 21434:2021 | Road vehicles - Cybersecurity engineering | 기억 |
| ISO/PAS 8800:2024 | Road vehicles - Safety and artificial intelligence | 기억 |
| ISO/IEC TR 5469:2024 | Artificial intelligence - Functional safety and AI systems | 기억 |
| ISO/TS 5083:2025 | Road vehicles - Safety for automated driving systems - Design, verification and validation | 기억 |
| UL 4600 | Standard for Safety for the Evaluation of Autonomous Products | 기억 |

## 6. 코딩 규칙과 그 밖의 문서 (13, 14장)

| 문서 | 내용 | 확인 |
|---|---|---|
| MISRA C:2025 | C 언어의 coding guideline. 2025-03 발행 | 검색 |
| MISRA C++:2023 | C++ 언어의 coding guideline | 기억 |
| SEI CERT C Coding Standard | C 언어의 secure coding 규칙 | 기억 |
| AMC 20-193 | multicore processor를 쓰는 항공 시스템에 대한 EASA의 지침 | 기억 |
