# 4장 근거 문서에서 뽑은 사실

읽은 날: 2026-11-22. 쪽은 PDF 파일의 몇 번째 쪽인지다 (인쇄된 쪽 번호와 다를 수 있다). 인용은 그 쪽을 찾기 위한 표지다.
`(기억)`은 문서에 없고 읽는 이의 기억에서 나온 것이라 근거가 아니다. 웹 항목은 파일을 받지 않고 읽기만 했다.

## 1. iec-61508-overview-slides (IEC, 2022, 발표 자료)

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| F04-001 | 4 | IEC 61508의 목표 중 하나는 산업이 직접 쓸 수 있으면서 분야별 규격 (machinery, process plant)과 제품 규격 (power drive systems)의 개발도 돕는 범용 규격이 되는 것이다 | "Provide a generically-based standard that can be used directly by industry" | 슬라이드는 2010년 판이라고 적지 않았다 |
| F04-002 | 4 | 필요한 성능을 정하는 데 위험에 기초한 접근을 쓴다. 위험은 정량 또는 반정량으로 정할 수 있다 | "Provide risk based approach for determining the required performance of safety-related systems" | |
| F04-003 | 4 | 공통 원리에 기초한 요구로 공급망의 효율, 요구 사항 전달의 명확함, 분야 공통 기법의 개발, 필요하면 conformity assessment 서비스의 개발을 돕는다고 한다 | "The development of conformity assessment services if required." | |
| F04-004 | 2 | 규제 기관이 국제 규격을 "합리적인 것"(accepted good practice)의 기준으로 쓰는 경향이 늘고 있다고 한다 | "Safety Regulators using international standards as basis of what is reasonable" | 발표자의 시장 환경 설명이다 |
| F04-005 | 5 | 원칙적으로 E/E/PE (전기, 전자, 프로그래머블 전자) 안전 관련 시스템이면 복잡도와 무관하게 적용된다. 예시 15개에 medical devices, railway signalling, automotive systems가 있다 | "In principle, IEC 61508 is applicable to any system that uses Electrical, Electronic and Programmable" | 슬라이드는 이 목록을 sector/product specific applications라고 부른다 |
| F04-006 | 6 | 기본 (standalone) 규격 옆에 분야와 제품별 구현으로 IEC 62061 (machinery), IEC 61511 (process), IEC 61513 (nuclear), IEC 61800-5-2 (power drives)를 든다 | "Sector & product implementations" | ISO 26262, EN 50716, IEC 62304, DO-178C는 이 슬라이드에 없다 |
| F04-007 | 7 | IEC 61508의 요소 (elements)가 분야 규격과 제품 규격에 쓰이고, 그 덕에 61508에 맞는 범용 요소의 큰 시장이 생긴다는 그림이다 | "Large market for generic elements & conforming to IEC 61508" | 그림 설명이라 문장이 불완전하다 |
| F04-008 | 10, 14 | 안전 기능의 "무엇을 하는가"(functionality)는 hazard analysis에서, "얼마나 믿을 만한가"(safety integrity)는 risk assessment에서 정해진다. SIL은 안전 기능의 속성이다 | "SIL is a property of a safety function" (14쪽) | 규격이 정하는 틀과 프로젝트가 정하는 값의 구분에 쓸 수 있다 |
| F04-009 | 21 | 안전 lifecycle은 세 가지다: Overall, E/E/PE system, Software. 각 단계가 그 단계의 요구를 정하고 그것은 기술 요구에 관한 것이다 | "There are three Safety Lifecycles" | 그림은 단순화된 것이라고 슬라이드가 밝힌다 |
| F04-010 | 22 | 준수 (compliance)의 구성 요소 그림: Management of Functional Safety, Competence, Technical Requirements, Functional Safety Assurance Measures. 이 절들이 lifecycle의 관련 단계마다 적용된다 | "These clauses applied to each relevant phase" | 그림이라 설명이 짧다. 슬라이드는 Part 번호를 적지 않았다 |
| F04-011 | 12-13 | 고장을 무작위 하드웨어 고장과 systematic 고장 (명세 오류, 소프트웨어 오류, 사람의 실수 등)으로 나누고, SIL 개념이 나온 이유가 systematic 고장의 중요성이라고 한다 | "The driver for the concept of Safety Integrity Level (SIL)" | 규격 구성을 설명하는 쪽은 아니고 배경이다 |

## 2. nhtsa-safety-standards-assessment (NHTSA, DOT HS 812 285, 2016)

기준 판: ISO 26262 1판 (2011년 11월 발행)의 최종 초안. 보고서는 최종 초안과 발행본의 기술 내용이 같다고 위원회 전문가가 확인했다고 적는다 (15쪽 각주 4).

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| F04-012 | 14 | 보고서가 본 6개 규격 중 ISO 26262가 가장 해당한다. 보고서가 말하는 ISO 26262는 E/E와 소프트웨어 요소로 된 자동차 시스템의 기능 안전을 다루는 첫 포괄적 자발적 업계 규격이다 | "first comprehensive and voluntary industry standard" | 6개: ISO 26262, MIL-STD-882E, DO-178C, FMVSS, AUTOSAR, MISRA C (13쪽) |
| F04-013 | 14 | ISO 26262는 IEC 61508을 도로 차량에 맞춘 (adaptation) 규격이다 | "an adaptation of the International Electrotechnical Commission 61508 standard" | |
| F04-014 | 14 | 1판은 10개 Part이고, Part 2-7이 핵심이며 Part 1, 8, 9, 10이 핵심 내용을 지원한다 | "Parts 2 through 7 are the core of the standard." | 2011년 판 기준. 2018년 판은 12개 Part (7.2절 참조). Part별 제목은 이 보고서에 없다 |
| F04-015 | 14-15 | 적용 범위는 최대 총중량 3.5톤의 양산 승용차에 설치되는 E/E 안전 관련 시스템이고, 오동작으로 생기는 hazard를 다룬다. 감전, 화재 등은 E/E의 오동작이 직접 원인일 때만 다룬다 | "installed in series production passenger cars with a maximum gross weight up to 3.5 tons" | 규격을 인용한 문장이다. 2018년 판의 범위는 다를 수 있다 |
| F04-016 | 15 | ISO 26262는 시스템 공학 과정을 정한다. 안전은 시스템 속성이라고 보고 안전 문화와 안전 관리를 강조한다 | "prescribes a systems engineering process for safety engineering" | |
| F04-017 | 16 | DO-178C는 항공 탑재 소프트웨어의 업계 합의 지침이다. FAA가 AC 20-115C (2013-07)로 이를 "유일하지는 않은 인정된 방법"의 하나로 인정했다. 소프트웨어 lifecycle data와 문서의 생성을 안내한다 | "acceptable means, but not the only means" | 요구가 아니라 guidance라고 보고서가 부른다 |
| F04-018 | 16 | DO-178C는 소프트웨어 개발을 전체 시스템 개발의 부분집합으로 보고, 안전 관련 요구는 상위 시스템 공학 활동에서 정해져 소프트웨어 개발 시작에 주어진다고 가정한다 | "subset of the overall system development process" | 항공 계보와 ISO 26262의 차이를 설명할 때 쓸 수 있다 |
| F04-019 | 16-17 | FMVSS는 법으로 지정된 성능 요구와 시험 조건을 정하고, 제조사가 자기 인증 (self-certify)한다. 시험으로 합격과 불합격을 가르는 방식이다 | "requires manufacturers to self-certify" | 17쪽. 보고서는 다른 자발적 과정 규격에는 이런 객관 척도가 없다고 쓴다 |
| F04-020 | 17 | AUTOSAR의 주 목적은 안전이 아니라 소프트웨어 아키텍처의 재사용이다. 그러나 ISO 26262를 돕는 아키텍처 개념을 제공하고, 둘은 상호 보완이다 | "AUTOSAR's main objective is not safety" | |
| F04-021 | 18 | ISO 26262는 소프트웨어 coding에 MISRA C를 따르라고 권고하며, MISRA C는 C 언어 사용을 제한하는 규칙 모음이다. 보고서는 이를 ISO 26262의 지원 규격으로 본다 | "ISO 26262 recommends following MISRA C" | 2011년 판 기준의 보고서 서술이다 |
| F04-022 | 19 | 비교한 11개 차원의 첫째가 규격의 유형이고, 6개 규격에서 안전 보증의 접근 네 가지를 찾았다: 과정 규정, 방법 나열, 성능 기반, 설계 규정 | "Four different approaches to safety assurance exist" | |
| F04-023 | 19 | 과정 규정 규격은 안전 공학의 과정을 정한다. ISO 26262, MIL-STD-882E, DO-178C가 여기에 든다. ISO 26262와 DO-178C는 안전 공학을 개발 과정의 일부로 넣고, MIL-STD-882E는 개발 과정과 나란한 별도 과정으로 둔다 | "prescribes a safety engineering process" | |
| F04-024 | 19-20 | MIL-STD-882E와 DO-178C는 과정만 정하고 각 단계의 방법은 정하지 않는다. 장점은 방법 선택의 자유와 새 기술에의 적용 용이이고, 단점은 고수준 지침뿐이라 달성되는 안전의 수준이 적용하는 사람에 따라 달라질 수 있다는 것이다 | "full freedom to select the most suitable safety engineering method" | 19쪽에서 시작해 20쪽에서 끝난다. 규격이 정하는 것과 맡기는 것을 보여 준다 |
| F04-025 | 20 | ISO 26262는 과정에 더해 FMEA, FTA, HAZOP 같은 분석 방법을 여러 Part에 나열하고 (보고서는 Part 9를 가리킨다) 하드웨어 무작위 고장 지표도 도입한다. 나열의 이점은 적절한 방법 선택에 도움이 되는 것이고, 비용은 목록을 계속 갱신해야 하는 것이다 | "lists a number of commonly known hazard analysis and safety analysis methods" | "methods listing"의 보고서식 정의 |
| F04-026 | 20 | 성능 기반 규격은 특정 시스템의 최소 성능을 정하고 해법에 중립이다 (FMVSS). 과정 규격은 완성품의 성능 목표를 정하지 않고 설계자가 설계 선택의 안전 영향을 따지게 하며, 성능 규격을 보완할 수 있다 | "generally solution neutral" | |
| F04-027 | 20-21 | 설계 규정 규격은 설계의 특정 측면 (AUTOSAR는 아키텍처, MISRA C는 coding)에 초점을 둔다. 안전 과정의 알맞은 단계에서 쓰면 강력하지만 전체 안전 규격으로는 충분히 일반적이지 않을 수 있다 | "focus on a specific aspect of the product design" | 21쪽에서 끝난다 |
| F04-028 | 21 | ISO 26262의 safety는 "unreasonable risk의 부재"이고 hazard는 item의 오동작이 일으키는 해악의 잠재 원인이다. 보고서는 "unreasonable"의 정의가 규격에 더 없다고 쓴다 | "Absence of unreasonable risk." | Table 1. 2011년 판 정의 |
| F04-029 | 33 | MIL-STD-882E는 안전 인증 (certification) 규격이 아니다. 정부의 검토와 감사를 지원하라고 하지만 세부는 프로그램 관리자와 계약자에게 맡긴다 | "is not a safety certification standard" | |
| F04-030 | 33 | DO-178C 10절은 용어를 구분한다. certification은 항공기, 엔진, 프로펠러에 적용되고, 인증 당국은 소프트웨어를 단독 제품으로 인증하지 않는다. 소프트웨어를 포함한 시스템과 장비는 "approved"되며 그 승인은 특정 인증의 맥락에서만 의미가 있다 | "do not certify the software as a unique, stand-alone product" | DO-178C 본문을 보고서가 인용한 것이다 (2차 인용) |
| F04-031 | 33 | 따라서 소프트웨어 승인은 규격이 정한 lifecycle 문서에 근거한다 | "software approval is based on the documents produced" | 보고서의 결론 문장 |
| F04-032 | 34 | ISO 26262는 DO-178C와 매우 비슷하게 시스템 안전 공학 과정의 모든 work product를 모아 "safety case"를 만들고, 그것으로 규격 과정을 따랐음을 보인다 | "build up a safety case" | 보고서는 이 용어가 안전 공학의 일반 의미와 달라 오해를 부른다고 지적한다 |
| F04-033 | 34 | ISO 26262 Part 2의 Table 1이 ASIL별로 confirmation review를 요구하며, 개발자, 프로젝트 관리, work product 저자로부터의 독립을 요구한다. 보고서는 현실에서 독립된 검토자를 구하기 어렵다고 비판한다 | "independence with regard to the developers of the item" | 규격 인용문이다. 비판은 보고서의 의견이다 |

## 3. gsn-standard-v3 (SCSC, 2021)

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| F04-034 | 9 | GSN Standard는 4부분이다. Part 0 개요와 개념은 informative, Part 1 GSN의 정의 (구문과 의미)는 normative, Part 2 사용과 평가의 지침은 informative이고, 웹 저장소가 informative 자료를 더한다 | "Part 1: Definition Of The Goal Structuring Notation (normative)" | normative와 informative를 Part 단위로 나눈 실제 예. 이 표기법 규격의 구조이고 안전 규격은 아니다 |

## 4. faa-ac-20-115d (FAA, 2017-07-21)

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| F04-035 | 1 | AC는 형식 인증 (type certification) 또는 TSO 승인에서 소프트웨어 측면의 감항 규정 준수를 보이는 "인정된 방법의 하나이고 유일한 방법은 아닌" 것을 설명한다. 의무가 아니고 규정이 아니다. 단 이 방법을 쓰면 해당되는 모든 점에서 따라야 한다 | "This AC is not mandatory and does not constitute a regulation." | |
| F04-036 | 1 | 이 AC가 인정하는 문서는 ED-12C/DO-178C, 도구 인정 ED-215/DO-330, 보충 문서 ED-218/DO-331 (model-based), ED-217/DO-332 (object-oriented), ED-216/DO-333 (formal methods)이다. ED-xxx와 DO-xxx는 동등하다 | "recognized as being equivalent" | |
| F04-037 | 2 | 지원 문서 ED-94C/DO-248C는 FAQ와 토의 자료로 DO-178C의 지침을 명확히 한다. 이 AC는 DO-178C 계열의 지침을 objectives, activities, 증거의 설명으로 구성된다고 설명한다 | "Objectives for software life cycle processes" | 2쪽 4.a항 |
| F04-038 | 3 | DO-178C를 쓰면 부여된 소프트웨어 level에 해당하는 모든 objective를 만족하고 Annex A 표의 lifecycle data를 만들어야 한다 (should). 활동은 계획하고 수행한다 | "ED-12C/DO-178C is an acceptable means of compliance" | 6.a항. should이지만 AC 1.a의 "따르라"와 함께 읽어야 한다 |
| F04-039 | 4 | 신청자는 lifecycle data를 해당 인증 사무소에 제출하고, 요청 시 그 밖의 data를 제공한다. 활동의 수행과 data의 생산은 신청자의 책임이다 | "It is your responsibility to perform the planned activities" | 6.b, 6.d항 |
| F04-040 | 4 | FAA가 특정 규정에 대해 소프트웨어 기반 시스템의 중요도와 소프트웨어 level의 관계를 정한 별도의 인정된 방법을 낼 수 있고, 그것이 DO-178C 2.3절보다 우선한다 | "will take precedence over the application of section 2.3" | 6.e항 |
| F04-041 | 4 | 보충 문서 (DO-331, 332, 333)는 단독 문서로 쓸 수 없다. 쓰는 경우 PSAC에 DO-178C와 함께 적용하는 방법을 적어야 한다 | "You cannot use supplements as stand-alone documents." | 8.a항 |
| F04-042 | 3 | 이전 DO-178B의 프로세스를 새 개발에 계속 쓸 수 있는 조건이 6개 있고, 맞지 않으면 DO-178C로 올려야 한다. 새 프로세스를 세우는 경우는 DO-178C를 따른다 | "should do so in accordance with ED-12C/DO-178C" | 5.b, 5.c항 |

## 5. ifa-report-2-2017e (DGUV IFA, 2019-07)

기준 판: EN ISO 13849-1:2015 (3판), ISO 12100:2010. 보고서 자체는 규격의 대체가 아니라고 밝힌다 (9쪽).

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| F04-043 | 11 | EN ISO 12100은 Type A 규격으로, 기계 안전 설계의 기본 개념과 일반 원칙을 정하고 위험 식별과 risk assessment의 절차를 포함한다. EN ISO 13849-1 (과 -2)은 이를 바탕으로 제어 시스템의 안전 관련 부분 (SRP/CS)의 설계를 다룬다 | "EN ISO 12100 [3], a Type A standard" | |
| F04-044 | 11 | 13849-1의 방법은 응용과 기술에 중립이라 제품별 (대개 Type C) 안전 규격이 거의 다 참조한다. 설계에 전기, 전자, 유압, 공압, 기계를 가리지 않는다 | "referenced by virtually all product standards" | 같은 쪽 "(generally Type C standards)" |
| F04-045 | 86 | EN ISO 13849-1은 기계류 지침 아래에서 제어에 관한 Type B 규격으로 조화되었다 (harmonized) | "harmonized under the Machinery Directive as a Type B standard" | 7.1.1절. Type A, B, C의 정의문은 이 보고서에서 찾지 못했다 |
| F04-046 | 11 | 조화 규격 (harmonized standard)을 EU 관보에 올려 두면 그 규격을 따르는 것이 지침의 필수 요구를 만족한다는 추정 (presumption of conformity)을 준다 | "gives rise to a presumption of conformity" | |
| F04-047 | 25, 29 | 기계에 해당하는 제품별 조화 규격 (Type C)이 관보에 있고 설계가 그것을 따르면 필수 요구의 만족이 추정된다. 없거나 벗어나거나 덮지 못한 부분은 설계자가 위험 감소 전략을 직접 따른다. Type C에 규정이 없으면 안전 기능은 기계 설계자가 정한다 | "In the absence of relevant provisions in a Type C standard" | 29쪽의 인용. 25쪽의 설명과 합쳐 읽었다 |
| F04-048 | 15 | 기능 안전의 일반 규격은 IEC 61508 계열과 그 machinery 분야 규격 IEC 62061, 그리고 EN ISO 13849이다. 61508과 62061은 E/E/PE에 한정되고 13849는 유압, 공압, 기계도 다룬다 | "their sector standard IEC 62061 for the machinery industry" | 그림 3.1 |
| F04-049 | 16 | EN ISO 13849-1과 IEC 62061은 둘 다 Machinery Directive의 조화 규격이다. IEC 61508 Part 1-4는 IEC 시각에서 기본 안전 규격 (basic safety standard)이지만 유럽 규격이 되어도 이 지침에 조화될 수 없다 | "have the status of basic safety standards" | 보고서가 던지는 질문 중 하나가 "어느 규격을 적용할 것인가"다 |
| F04-050 | 17 | ISO/TR 23849 (2010)의 핵심: 두 규격의 방법은 다르지만 비슷한 위험 감소 수준에 이를 수 있고, 두 규격의 요구를 섞으면 안 된다는 데 널리 합의되어 있다. ISO/IEC 17305로 통합하는 작업은 2015-10에 중단되었다 | "requirements from the two standards should not be mixed" | |
| F04-051 | 17 | 기계 제조사와 사용자의 2012-2013년 설문에서 715명 중 90%가 EN ISO 13849-1을 쓴다고 답했다 | "EN ISO 13849-1 was used by 90%" | 현황이라 책에서 쓸 때 시기를 밝혀야 한다 |
| F04-052 | 19-20 | 13849의 설계 흐름: 안전 기능 식별, 필요한 PL (PLr) 결정, 구현, 달성 PL 평가, PL >= PLr 검증, validation. 위험 분석은 ISO 12100에서 오고 다시 돌아간다. PLr은 3개 질문 (상해의 가역성, 위험 구역에 있는 빈도, 회피 가능성)의 risk graph로 정한다 | "iterative process for the design of safety-related parts" | 19쪽 그림 4.1과 20쪽 |
| F04-053 | 20 | 규격은 PL을 계산하는 방법을 사용자에게 맡긴다 (Markov 모델링도 가능). 단순한 방법으로 지정 아키텍처와 막대 도표를 제시한다. 지정 아키텍처는 선택적 편의이다 | "places the methods by which the PL is calculated" | 16쪽에도 "optional facility" |
| F04-054 | 22 | 13849-1의 3판은 개정 1에서 나왔다. 2016년 개정 작업을 시작해 4판 가능성을 말한다 | "begin work on a revision of the standard" | 4판 (ISO 13849-1:2023)은 standards.md가 확인했고 이 문서는 2019년 7월 판이다 |

## 6. sora-2-5-main-body (JARUS, JAR-DEL-SRM-SORA-MB-2.5, 2024-05-13)

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| F04-055 | 2 | SORA는 특정 운용이 안전하게 수행될 수 있다는 충분한 신뢰를 세우는 위험 평가 방법을 권고한다. 운용을 6개 SAIL로 분류하고 SAIL별로 운용 안전 목표를 권고한다 | "recommends a risk assessment methodology" | 문서 분류는 Guidelines (1쪽) |
| F04-056 | 14 | 목적은 "specific" 범주의 UAS 운용이 허용 가능하게 안전하려면 필요한 증거와 보증을 위험에 비례해 정하는 것이다. 신청자와 소관 당국이 함께 쓴다. 목표 안전 수준 (TLOS)은 유인 항공의 수준에 맞춘다 | "risk-proportionate method to determine the required evidence" | |
| F04-057 | 18 | 처방적 요구가 아니라 위험에 맞춘 견고성 수준의 안전 목표를 담는다. 체크리스트로 쓰면 안 되고 안내서다 | "does not contain prescriptive requirements" | 문서 자체가 "shall not be used as a checklist"라고 쓴다 |
| F04-058 | 18-19 | 이 방법은 "인정된 평가 방법"으로 제안되며, 소관 당국은 방법을 바꾸거나 조치를 더 요구할 수 있다. 운용자는 SORA가 다루지 않는 다른 규제 요구도 지켜야 한다 | "proposed as an acceptable means to evaluate the safety risks" | 1.2(c), 1.2(f), 1.3(h)항 |
| F04-059 | 19 | 전통적 항공기 인증 (설계 승인, 감항 승인, 형식 인증)이 위험에 비례하지 않는 경우에 쓸 수 있다고 한다 | "traditional approach to aircraft certification" | 1.2(d)항 |
| F04-060 | 29 | 규격 문장 용어: "Should"는 강한 의무, "May"는 제공할 정보의 재량을 뜻한다. 권고 (R)는 지역에 따라 means of compliance라고 부른다. open 범주, 표준 시나리오, certified 범주는 SORA 대상이 아니다 | "'Should' indicates a strong obligation." | 3.1(e), (f)항과 각주 6. 이 문서가 정의한 용어 사용이며 ISO 방식이 아니다 |
| F04-061 | 30-31 | SORA는 Step #9 뒤에서 두 단계로 나뉜다. 1단계는 요구 도출과 means of compliance 제안, 2단계는 요구의 충족이고, 1단계 끝에 소관 당국과 사전 합의를 권고한다. 결과물은 Comprehensive Safety Portfolio이다 | "Phase 1 (Requirements derivation)" | 3.3절 |

## 7. 웹 (읽은 날 2026-11-22)

### 7.1 ISO 26262 3판의 진행 상태 (iso.org, 브라우저로 읽음)

| 번호 | 주소 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| F04-062 | https://www.iso.org/standard/90022.html | ISO/DIS 26262-3은 "Product development at the item level"이고 Edition 3이다. 상태는 under development, 단계 40.20 (DIS ballot initiated: 12 weeks)이며 ISO 26262-3:2018을 대체할 예정이다 | "in the enquiry phase with ISO members" | 쪽에 날짜는 없다. 2018년 판의 제목은 "Concept phase" |
| F04-063 | https://www.iso.org/standard/90020.html 부터 90031.html (12개 쪽) | Part 1-12의 DIS 쪽이 모두 단계 40.20, Edition 3이다. Part 1-12 전부가 같은 단계다. 제목: 1 Vocabulary, 2 Management of functional safety, 3 Product development at the item level, 4 ...system level, 5 ...hardware level, 6 ...software level, 7 Production, operation, service and decommissioning, 8 Supporting processes, 9 ASIL-oriented and safety-oriented analyses, 10 Guidelines on ISO 26262, 11 Guidelines on application of ISO 26262 to semiconductors, 12 Adaptation of ISO 26262 for motorcycles | "DIS ballot initiated: 12 weeks" | references/standards.md는 일부 Part만 DIS라고 적었는데 이 쪽들은 12개 전부를 DIS로 보인다. 확인 필요. 쪽마다 발행 예정일은 없다 |
| F04-064 | https://www.iso.org/standard/90022.html | DIS Part 3의 abstract는 이 규격이 기능 안전의 틀 (framework)이고, 일부 요구는 기술에 초점이 있고 일부는 조직의 역량을 보이는 과정 요구라고 말한다. Annex A가 objectives, prerequisites, work products를 개관한다고 적는다 | "can therefore be seen as process requirements" | DIS의 abstract이고 2018년 판의 abstract와 거의 같아 보이나 대조하지 않았다 |
| F04-065 | https://www.iso.org/standard/68388.html | ISO 26262-6:2018은 Edition 2, 발행 2018-12이고 2024년에 재검토되어 유지가 확인되었다 (fetch로 읽은 문구: "last reviewed and confirmed in 2024"). 다른 Part의 2018 쪽 (68383-68392)은 Edition 2, 2018-12이다 | "last reviewed and confirmed in 2024" | Part 6 쪽에서만 재검토 문구가 보였다 |

### 7.2 ISO 26262 2018년 판의 Part 목록 (C)

| 번호 | 주소 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| F04-066 | https://www.iso.org/publication/PUB200262.html | ISO가 묶음으로 파는 ISO 26262:2018은 Part 1-10이고 제목은 standards.md의 표와 같다 (1 Vocabulary ... 10 Guidelines on ISO 26262). 묶음에 Part 11, 12는 없다 | "This package includes 10 essential parts of ISO 26262" | Part 11, 12는 references/standards.md의 기록을 따른다 (`검색`, 2018년 판). 이 세션에서 다시 읽지 않았다 |
| F04-067 | https://www.iso.org/publication/PUB200262.html | 묶음 설명이 Part 3을 concept phase (hazard analysis and risk assessment 포함), Part 8을 supporting processes (configuration management, change control 등)로 소개한다 | "Supporting processes" | 판매 설명문이라 일반론이다 |

### 7.3 IEC 61508 Edition 3의 진행 상태

| 번호 | 주소 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| F04-068 | https://webstore.iec.ch/en/publication/5515 (Part 1), /5517 (Part 3) | IEC webstore의 Lifecycle 칸에 Part 1과 Part 3의 Edition 3.0이 "Under development", 단계 PRVC (Preparation of RVC), 예상 발행일 2026-10-22로 나온다. Edition 2 (2010-04-30)는 Valid이고 안정 기한 (stability date)은 2027이다 | "Stage code: PRVC" | 예상일 2026-10-22는 읽은 날 (2026-11-22)보다 앞이다. 발행되지 않았다. Part 2, 4-7은 읽지 못했다 |
| F04-069 | https://webstore.iec.ch/en/publication/5515 | 관련 문서에 IEC TS 61508-3-2:2024와 IEC TR 61508-3-3:2025가 보인다 | "IEC TR 61508-3-3:2025" | standards.md의 3-3 기록과 같다. 3-2는 standards.md에 없다 |
| F04-070 | https://61508.org/knowledge/standards-development/ | 61508 Association의 쪽이 Edition 2가 현행이고 CD가 나와 의견을 받았으며 CDV가 2026년 초 예정이고 Edition 3은 2027년 초 예상이라고 적는다. 바뀌는 점은 적지 않았다 | "A 'Committee Draft for Vote' (CDV) for Edition 3 is due in early 2026." | 날짜도 저자도 없는 쪽이라 시점이 오래되었을 수 있다 (읽은 쪽의 문구로는 2023 copyright). F04-068과 어긋나 보인다 |
| F04-071 | 검색 결과로 얻은 IEC 문서 65A/1169/CDV의 공개 미리보기 (iteh.ai) | Part 3의 CDV 문서가 2025-02-21에 회람되었고 투표 마감은 2025-05-16, 제안 안정 기한은 2028이다. 목차에는 Annex H (오프라인 지원 도구 신뢰), Annex I (model-based), Annex J (data driven systems)가 있다. 문서가 "reference로 쓰지 말라"고 적는다 | "This document is still under study and subject to change." | 14쪽짜리 미리보기를 읽었다. 목차만 읽었고 본문의 변경 요약은 없다. 표지의 단계는 CDV다 |
| F04-072 | 위와 같음 (검색 결과 요약, 직접 읽지 못함) | 검색 요약에 따르면 CDV의 서문은 TS 61508-3-1의 요구가 Clause 7에 들어가고 formal methods 요구가 명확해진다고 하고 보안은 IEC 62443을 가리킨다고 한다 | (직접 읽지 못해 인용 없음) | 검색 엔진의 요약이다. 원문을 열지 못했으니 책에는 쓰지 말고 다시 확인한다 |

### 7.4 무엇이 달라지는지에 관한 공개 자료

| 번호 | 주소 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| F04-073 | 검색 결과 요약 (kuglermaag.com의 "What to Expect with Version 3 of ISO 26262", UL의 블로그, HORIBA MIRA의 발표 자료, Omnex 블로그 2026-07-02) | 업체와 컨설팅의 글이 ISO 26262 3판에서 AI/ML 정렬 (ISO/TS 5083, PAS 8800), 소프트웨어 요구 갱신, zonal 아키텍처에서 item 개념의 부담을 예상한다. 발행 시기 추정은 글마다 다르다 (Q4 2027, 2028 Q2 등) | (직접 읽지 못해 인용 없음) | 모두 업체 또는 컨설팅의 글이고 ISO나 위원회의 발표가 아니다. kuglermaag.com은 인증서 오류로 열리지 않았고 나머지는 열지 못했다 |
| F04-074 | 위와 같음 | Part 6 DIS에 관한 ISO의 공개 쪽은 abstract (configurable software 요구 포함이라는 검색 요약)뿐이고 변경 목록은 찾지 못했다 | (인용 없음) | ISO/TC 22/SC 32 또는 IEC SC 65A의 공식 변경 요약은 찾지 못했다 |

### 7.5 ISO/IEC Directives, Part 2 (https://www.iso.org/sites/directives/current/part2/index.xhtml)

기준 판: 제9판 (2021)이 8판 (2018)을 대체한다. 같은 쪽의 현행판이다.

| 번호 | 조항 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| F04-075 | 3.2.1 | normative element는 문서의 범위를 서술하거나 provision (규정)을 정하는 요소다 | "sets out provisions" | |
| F04-076 | 3.2.2 | informative element는 문서의 이해와 사용을 돕거나 내용의 배경, 다른 문서와의 관계에 관한 맥락 정보를 주는 요소다 | "intended to assist the understanding or use of the document" | |
| F04-077 | 3.3.3, 7.2 | requirement는 객관적으로 검증 가능한 기준이고, 적합성 (conformance)을 주장하려면 벗어날 수 없다. 표현은 shall (과 shall not)이다. "must"를 shall 대신 쓰지 않는다 | "no deviation is permitted if conformance with the document is to be claimed" | |
| F04-078 | 3.3.4, 7.3 | recommendation은 다른 것을 반드시 언급하거나 배제하지 않고 특히 알맞다고 보는 선택이나 행동을 제안한다. 표현은 should (과 should not)이다. should not은 선호하지 않지만 금지는 아니라는 뜻이다 | "suggested possible choice or course of action deemed to be particularly suitable" | 3.3.4 Note 2 |
| F04-079 | 3.3.5, 7.4 | permission은 허용이나 자유를 나타내고 표현은 may다. "can"을 may 대신 쓰지 않는다. may는 문서가 주는 허가이고 can은 사용자의 능력이나 가능성이다 | "\"May\" signifies a permission expressed by the document" | |
| F04-080 | 3.3.6, 3.3.7, 7.5 | possibility와 capability는 can (과 cannot)으로 표현한다. 가능한 결과 또는 능력을 말하고 요구가 아니다 | "ability, fitness, or quality necessary to do or achieve a specified thing" | 3.3.7 |
| F04-081 | 7.1 | 사용자는 적합성을 주장하려고 따라야 하는 요구를 다른 provision과 구별할 수 있어야 한다. 표에 정의되지 않은 동사 형태는 provision 표현에 쓰지 않는다 | "shall be able to identify the requirements he/she is obliged to satisfy" | |
| F04-082 | 3.3.8, 7.6 | external constraint (법칙, 지역 조건 같은 사용자에게 부과되는 제약)는 must로 가리키며 그 문서의 요구가 아니다 | "does not imply that the external constraint referred to is a requirement" | 3.3.8 Note 2 |

## 장 계획이 기대했지만 문서에 없던 것

- ISO 26262 2018년 판의 Part별 normative와 informative 구분: 문서에 없다. ISO 쪽은 Part 10 제목이 "Guidelines"라는 것과 DIS Part 3 abstract (F04-064)뿐이다. standards.md의 "Part 1-9와 12가 규범, 10과 11이 해설"은 문서의 근거를 확인하지 못했다.
- IEC 61508의 Part별 normative 구분과 Part 제목: 슬라이드에 Part 목록이 없다 (Part 제목은 standards.md의 검색 기록).
- IEC 62061, IEC 61511 같은 분야 규격의 내부 구조, EN 50716, IEC 62304, ISO 13849의 요구 구조: 슬라이드는 이름만 든다 (F04-006). ISO 26262와 EN 50716이 61508의 분야 규격이라는 말은 슬라이드에 없다.
- ISO 26262가 IEC 61508에서 나왔다는 서술은 NHTSA 보고서 (F04-013)에만 있고 ISO 쪽에는 없다.
- Type A, B, C 규격의 정의문: IFA 보고서가 예를 들 뿐 정의하지 않는다 (F04-043, 045, 047).
- DO-178C 자체의 구조 (objective 표, 소프트웨어 level): AC와 NHTSA 보고서의 간접 서술뿐이다. 소프트웨어 level의 이름과 수는 이 두 문서에서 읽지 못했다 (A-D 중 level D가 언급됨, AC 4쪽).
- 방법 표의 추천 등급 (++, +, o): 읽은 문서에 없다 (IEC 61508-3과 ISO 26262-6 원문이 필요).
- ISO 26262의 work product 정의와 compliance, assessment의 정의: NHTSA 보고서는 safety case, confirmation review, DO-178C의 approval만 다룬다. 규격이 정하는 "functional safety assessment"의 정의는 없다 (IEC 61508-3 CDV 목차에 clause 8 "Functional safety assessment"가 보일 뿐이다).
- IEC 61508 Edition 3, ISO 26262 3판의 변경 내용을 발행 기관이 말한 공개 자료: 찾지 못했다 (F04-072 - 074). 발행 예정일도 ISO 쪽에는 없다.
- ISO 26262 3판의 DIS 투표 날짜: ISO 쪽에는 단계 코드만 있고 날짜가 없다. standards.md의 "Part 3 투표가 2026-10에 시작" 기록은 이번에 확인하지 못했다.
