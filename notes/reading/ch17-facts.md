# 17장 근거 문서에서 뽑은 사실 (읽기 기록)

대상: 17장 "도구와 기존 소프트웨어" (plans/ch17-tools-and-existing-software.md). 읽은 날: 2026-11-23.

- 쪽 칸은 PDF 파일의 몇 번째 쪽이다. 문서에 인쇄된 쪽 번호가 다르면 절 머리에 차이를 적는다.
- 인용은 줄바꿈을 합치고 따옴표와 줄표를 ASCII로 바꿨다. 그 밖에는 원문 그대로다. 단 ariane-501-report는 스캔본이어서 쪽을 OCR로 읽었고, 인용은 OCR이 또렷하게 읽은 구절만 골랐다 (quotecheck는 이 문서를 건너뛴다).
- 이 장의 규격 문서 (ISO 26262, IEC 61508, DO-330)는 받지 못했다. FAA AC 20-115D는 DO-178C/DO-330을 가리키는 항공의 문서이고, 아래 항공 항목은 항공의 것이다. 자동차나 산업의 규격이 같게 요구한다고 읽으면 안 된다.
- NASA-GB-8719.13은 2004년경의 지침서다. 문서의 "should"와 "must", "may"의 세기는 사실 칸에 그대로 옮겼다.
- `(기억)`은 문서에서 확인하지 못한 내용이다. 원고의 근거로 쓰지 않는다. 맨 끝의 "문서에서 찾지 못한 것" 절에만 둔다.
- 원고에 쓰기 전에 그 쪽을 직접 열어 확인한다 (RULES.md 5.2절).

## 1. faa-ac-20-115d (FAA, AC 20-115D, Airborne Software Development Assurance Using EUROCAE ED-12() and RTCA DO-178(), 2017. PDF 쪽 = 인쇄 쪽)

항공 소프트웨어의 문서다. 아래의 "tool qualification"은 DO-330 (ED-215)과 DO-178C 12.2절을 가리키며, 이 문서는 그 규격들의 요지를 인용만 한다.

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| F17-001 | 5 | 이 AC에서 "legacy software"는 이전에 승인된 소프트웨어, 또는 legacy system에서 쓰던 소프트웨어를 이루는 component를 가리킨다. 9절은 legacy software를 고쳐 쓰거나 고치지 않고 쓸 때 인증의 소프트웨어 측면에서 적합함을 보이는 법을 설명한다. | "legacy software includes the previously approved software" | 항공의 인증 절차다 |
| F17-002 | 8 | legacy software를 고쳐 쓰거나 다시 쓰려면 이전 설치에서의 사용 이력을 평가한다. 제안한 설치에 안전 영향이 있을 수 있는 safety-related service difficulty, airworthiness directive, open problem report가 있으면, 관련한 모든 소프트웨어 결함을 해결할 계획을 세운다. | "Assess the legacy software to be modified or re-used for its usage history" | 항공의 것. 이 문서의 표현은 "establish plans to resolve all related software deficiencies"다 |
| F17-003 | 8 | 고쳐 쓰거나 다시 쓰기 전에, 감사나 검토에서 나왔거나 open problem report가 가리킨, DO-178B의 목표를 만족하지 못하게 한 개발 과정의 결함도 바로잡는다. 모든 과정 관련 problem report와 감사 지적의 해결과 종결의 증거를 요구받을 수 있다. | "correct any related development process deficiencies" | 항공의 것. 제품의 이력뿐 아니라 과정의 결함도 본다 |
| F17-004 | 8 | legacy software의 level이 새 설치에 배정된 소프트웨어 level을 만족하는지는 Table 1로 판정한다. 예: DO-178A Level 2로 개발한 legacy software는 B, C, D를 만족하는 것으로 볼 수 있으나, level A가 필요한 곳에는 받아들일 수 없다. | "would not be acceptable where software Level A is required" | 항공의 level 체계다 |
| F17-005 | 8-9 | legacy software의 level이 받아들일 수 없으면, 모든 과정과 절차 (tool qualification 과정 포함)를 DO-178C 12.1.4절과 DO-330으로 끌어올려야 한다 (DO-178B 기반이면 DO-178B 12.1.4절도 쓸 수 있다). | "(including tool qualification processes)" | 항공의 것. 8쪽의 (2)(a)와 9쪽의 (2)(b), (c)를 합쳤다 |
| F17-006 | 9 | 9.b(1)과 (2)의 기준을 만족하고 소프트웨어를 고칠 필요가 없으면, 원래의 승인을 새 설치의 승인 근거로 쓸 수 있다. | "The original approval may serve as the basis for the software" | 항공의 것 |
| F17-007 | 9 | 소프트웨어가 DO-178C와 동등하다고 선언하더라도, 고치지 않은 tool까지 DO-178C와 DO-330을 만족한 것과 동등하다고 선언할 수는 없다. 이후의 모든 소프트웨어와 tool 수정은 DO-178C와 DO-330을 만족하는 과정으로 한다. | "you cannot declare your unmodified tools as equivalent" | 항공의 것. 같은 문장이 9.b(3)(b), (6), (9)에 되풀이된다 |
| F17-008 | 9 | 소프트웨어를 고쳐야 하면 change impact analysis (CIA)를 하여 수정의 범위, 영향, 필요한 검증을 정하고, 그 결과를 PSAC나 SAS에 요약한다. | "conduct a software change impact analysis (CIA)" | 항공의 것 |
| F17-009 | 9 | 새 tool이나 tool의 수정이 필요하면 10절로 tool qualification의 요구를 정한다. | "If new software tools or modifications to tools are needed" | 항공의 것 |
| F17-010 | 10 | 기존 과정으로 옛 DO-178 판을 써서 legacy software를 고치려면 세 조건을 모두 만족해야 한다: (a) 모델 기반 개발, 객체지향, formal method를 쓰면 그 과정이 이전 인증 프로젝트에서 FAA의 평가를 받았을 것, (b) 계획, 과정, life cycle 환경을 유지하고 있고 아직 쓸 수 있을 것, (c) DO-178C 만족을 선언하지 않을 것. | "You have maintained, and can still use, the software plans, processes, and life" | 항공의 것. 인용은 (b)의 일부다 |
| F17-011 | 10 | 위 조건이 하나라도 안 맞으면 tool qualification 과정을 포함한 모든 과정과 절차를 DO-178C와 DO-330으로 고치고, 소프트웨어 수정은 12.1절로 한다. | "update all your" | 항공의 것. 인용은 9.b(9)의 첫 구절이다 |
| F17-012 | 10 | DO-178C의 12.2절과 DO-330은 tool qualification의 받아들일 수 있는 방법을 준다. DO-330은 tool qualification의 목표, 활동, life cycle data를 자체로 완비하여 담고 있다. | "provide an acceptable method for tool qualification" | 항공의 것 |
| F17-013 | 10-11 | DO-178 또는 DO-178A로 승인한 legacy software를 새 tool이나 고친 tool로 고칠 때는, DO-178C 12.2절의 기준으로 qualification이 필요한지 정한다. 필요하면 시스템 안전 평가가 배정한 소프트웨어 level로 tool qualification level (TQL)을 정하고 DO-330의 목표와 활동을 쓴다. | "use the software level assigned by the system safety assessment for" | 항공의 것. 인용은 11쪽 첫 줄이다 |
| F17-014 | 11 | DO-178C는 tool의 쓰임과 소프트웨어 life cycle 과정에 미치는 잠재적 영향에 따라 tool qualification을 다섯 level로 나눈다 (12.2.2절과 Table 12-1). | "establishes five levels of tool qualification" | 항공의 것. Table 12-1 자체는 이 문서에 없다 |
| F17-015 | 11 | DO-178C는 DO-178B의 기준으로 이미 qualification한 tool의 사용을 다루지 않는다. 그런 개발 tool이나 검증 tool은 Table 2로 DO-178B의 tool qualification type과 DO-178C의 tool criteria, TQL의 대응을 본다. | "does not address the use of tools previously" | 항공의 것 |
| F17-016 | 11 | Table 2의 대응 (개발 tool): software level A는 criteria 1, TQL-1. level B는 TQL-2, level C는 TQL-3, level D는 TQL-4. 모두 tool criteria 1이다. | "Development A 1 TQL-1" | 항공의 것. 표의 첫 행이다. 나머지 행의 인용은 F17-017 |
| F17-017 | 11 | Table 2의 대응 (검증 tool): level A, B는 criteria 2, TQL-4. level C, D는 criteria 2, TQL-5. 모든 level에서 criteria 3인 검증 tool은 TQL-5다. | "Verification A, B 2 TQL-4" | 항공의 것. criteria 1, 2, 3의 정의는 이 문서에 없다 |
| F17-018 | 11 | DO-178B로 승인한 legacy software를 DO-178C와 동등하다고 선언하지 않는다면, 새 tool이나 고친 tool의 qualification에 (1) DO-178B의 tool qualification 과정을 쓰거나, (2) 과정을 고쳐 DO-330으로 qualification하고 Table 2로 TQL을 정할 수 있다. | "Use your ED-12B/DO-178B tool qualification processes for qualifying new or" | 항공의 것 |
| F17-019 | 12 | DO-178B로 qualification한 개발 tool은, tool에 배정된 DO-178B level이 요구되는 TQL과 대응하거나 그것을 넘으면 DO-178B 과정을 계속 쓸 수 있다. tool이나 운용 환경이 바뀌면 DO-330의 절로 tool change impact analysis를 한다. 대응하지 않으면 DO-330으로 다시 qualification한다. | "correlates with or exceeds the required TQL" | 항공의 것 |
| F17-020 | 12 | DO-178B로 qualification한 검증 tool은, 요구되는 TQL이 TQL-5면 DO-178B 과정을 계속 쓸 수 있고, TQL-4면 DO-330으로 다시 qualification해야 한다. | "then you should requalify your" | 항공의 것. 인용은 TQL-4의 경우다 |

## 2. nasa-gb-8719-13 (NASA, NASA-GB-8719.13 NASA Software Safety Guidebook, 2004. PDF 쪽 = 인쇄 쪽 + 1)

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| F17-021 | 233 | 개발자에게 필요한 최소한의 tool은 편집기, compiler (또는 cross-compiler), linker, debugger다. | "Compiler (or cross-compiler) to create object code with" | 11.2절 첫머리 |
| F17-022 | 234 | tool의 목표는 오류를 되도록 많이 일찍 찾는 것이다. 어떤 tool은 좋은 관행을 강제하고, 어떤 tool은 프로그래머를 귀찮게 하여 오히려 오류를 늘리거나 tool의 의도를 거스르게 만든다. | "Others make life difficult for the programmer and lead to additional" | |
| F17-023 | 234 | tool을 고를 때 볼 것: 배우기 쉬운가, 잘 통합되는가, 프로그래머가 알맞은 switch를 고르기를 기대하지 않고 기본값으로 표준을 강제하는가, 문서가 잘 되어 있는가 (사용법뿐 아니라 한계와 문제까지). tool이 못하는 것을 아는 것이 하는 것을 아는 것만큼 중요하다고 한다. | "Knowing what the tool cannot do is as important as what it can do." | |
| F17-024 | 235 | compiler를 고를 때 묻는 것: 경고를 오류로 다룰 수 있고 그것을 기본값으로 할 수 있는가. | "Can warnings (possible problems) be treated as errors?" | 11.2절의 목록 |
| F17-025 | 235 | compiler를 고를 때 묻는 것: compiler의 결함 목록이 있는가. 과거 결함과 그것을 고친 판이나 patch의 목록이 있는가. | "Is there a list of defects (bugs) in the compiler?" | |
| F17-026 | 235 | compiler를 고를 때 묻는 것: 크기와 속도 중 무엇을 우선할지, 또는 최적화를 하지 않을지 고르는 최적화 option이 있는가. 대상 processor에 맞게 최적화하는가. | "Does the compiler offer optimization options that allow you to choose size over speed" | 최적화 option의 선택을 요구 사항으로 둔 것이다. 최적화가 compiler의 결함을 드러낼 위험은 이 쪽에 없다 |
| F17-027 | 235 | compiler에 딸린 run-time library가 얼마나 최적화되어 있는지, 필요 없는 code를 stub으로 없앨 수 있는지, 필요 없는 code를 걷어 내거나 formal verification이나 inspection에 쓰도록 source가 있는지를 묻는다. | "How optimized is the run-time library that comes with the compiler?" | |
| F17-028 | 235 | compiler가 assembly language 출력을 낼 수 있는지, 그 출력이 어떤 assembler를 겨냥하는지를 묻는다. | "Can the compiler produce assembly language output?" | assembly 출력을 읽어 compiler의 변환을 확인할 길이 되는지는 문서가 말하지 않는다 |
| F17-029 | 235 | software debugger는 결함 있는 소프트웨어를 debugging 환경 안에서 돌린다. 문제가 memory 위반 (범위 밖 접근 등)일 때, debug 환경과 보통의 run-time 환경이 달라서 문제가 생길 수 있다. | "Software debuggers run the defective software within the debugging environment." | |
| F17-030 | 236 | 안전한 code를 만드는 데 쓸모 있는 tool: lint (compiler가 놓치는 문제를 찾음. 모든 지적이 진짜 문제는 아니지만 평가해야 하며, "non standard"이면 오류로 다룬다), profiler, memory check 프로그램, locator. | "finds problems in the code that compilers might miss" | |
| F17-031 | 237 | CASE tool은 code generator, 요구사항 추적, 정적 분석기, 시험 도구 등을 포함한다. 1980년대에는 질이 좋지 않았고 (개발 주기를 충분히 덮지 못하고, 통합이 안 되고, 비쌌음), 지금은 질, 신뢰성, 상호운용성이 많이 나아졌다고 한다. | "their quality, reliability, and interoperability have greatly" | Upper CASE, Lower CASE, I-CASE의 구분도 같은 쪽에 있다 |
| F17-032 | 237 | Lower CASE tool은 주로 설계 (Upper CASE tool의 출력)에서 code를 생성하는 tool이다. | "primarily those that generate code from the design" | |
| F17-033 | 237 | 자동 code 생성의 장점으로 문서가 드는 것: 소프트웨어를 더 높은 수준에서 설계하고 사람의 오류 없이 source code로 번역한다. 설계가 "source code"가 된다. | "translated, without human error, into source code." | 인용 뒤의 "사람의 오류 없이"는 번역 단계만을 말한다. F17-034가 이어서 단서를 단다 |
| F17-034 | 238 | 자동 code 생성의 단점: tool이 이제야 성숙해 가고 있다. 설계에서 code로의 번역에서 사람의 오류는 없어지지만 tool의 오류는 남는다. 안전 관련 소프트웨어에서는 올바른 번역을 검증해야 한다. | "tool error still exists" | |
| F17-035 | 238 | 환경에 따라 생성된 source code에 접근하지 못할 수 있고, 생성된 code의 최적화가 성능이나 크기의 기준에 영향을 줄 수 있다. | "Keep in mind that in some environments" | 인용은 "the source code may not be accessible"의 앞부분이다 |
| F17-036 | 238 | visual language (LabVIEW 등)의 안전 관련 응용에서의 문제: "code"를 inspect할 수 없고, 그림으로 만든 프로그램이 동작하기까지가 black box다. 형식을 갖춘 개발이 드물고, 명세가 없거나 부족하다. | "A problem with visual languages in safety-critical applications is the inability to inspect" | 같은 쪽의 "Formal specifications are usually lacking or non-existent."도 이 사실의 근거다 |
| F17-037 | 238-239 | visual language를 쓰는 곳에서는 configuration control이 고려되지 않는 일이 많고, configuration management tool이 시각적 표현을 다루기 어려울 수 있다. | "Configuration control is often" | 238쪽 끝과 239쪽 첫머리에 걸친다 |
| F17-038 | 239 | visual programming environment는 source code를 만들어 주므로 정식 inspection과 분석 tool을 쓸 수 있다. 그러나 개발자가 쓴 code가 아니어서 팀의 style이나 coding standard를 따르지 않을 수 있고, 읽기 어려울 수 있다. | "it may not follow the style" | |
| F17-039 | 239 | 모델 기반 code 생성은 추상화 수준을 높인다. assembly에서 고급 언어로 옮긴 것과 같은 한 걸음이지만, 각 걸음은 프로그램이 안전한지 검증하는 어려움도 가져온다. | "challenges in verifying that the program is safe!" | |
| F17-040 | 239 | 방법론과 tool을 고를 때 볼 것 가운데 하나: 번역기의 성숙도 (수년 쓰였는가, 어제 만들어졌는가. 번역기가 만든 소프트웨어를 검증하는 분석이 얼마나 되어 있는가). | "The maturity of translators for generating quality code." | |
| F17-041 | 240 | 이상적으로는 CASE tool이 어떤 표준에 맞게 인증되어 생성된 code가 compiler의 object code처럼 검토 없이 받아들여질 것이다. 그러나 compiler도 object code에서 오류를 낸다고 문서가 말한다. | "compilers produce errors in the object code." | |
| F17-042 | 240 | 자동 생성 code가 안전 관련이거나 안전 관련 code와 보호되지 않은 partition에 같이 있으면, 손으로 쓴 code와 같은 엄격한 inspection, 분석, test를 받아야 한다 ("should"). 이 문서는 자동 생성 code가 초기 단계라고 한다. | "subjected to the same rigorous inspection" | |
| F17-043 | 245 | 문서가 소개하는 RTEMS는 무료 open source 운영체제로, 원래 미 육군 미사일 사령부용으로 개발되었고, RTOS의 기본을 갖추고 source code를 구할 수 있다. Linux는 open source의 Unix이지만 보통은 real-time 운영체제가 아니라고 한다. | "RTEMS is a free, open source operating system." | open source에 관한 이 문서의 서술은 이 쪽의 소개뿐이다. 안전 관련 사용의 기준은 말하지 않는다 |
| F17-044 | 270 | NASA 정책 지침 NPD 2820.1은 COTS와 GOTS가 개발보다 이로운지 평가하라고 하며, 소프트웨어 공급자가 요구를 만족하는 제품을 낼 능력이 있다는 증거를 기대한다. | "It expects proof that software providers are capable of delivering products that" | |
| F17-045 | 270 | off-the-shelf (OTS)를 쓰는 결정은 가볍게 해서는 안 된다. 다른 project에서 소프트웨어를 다시 쓰는 것도 만병통치약이 아니며, 시스템이 다르면 미묘한 차이가 참담한 결과를 낼 수 있다. 이 문서는 OTS라는 말로 사 온 소프트웨어와 다시 쓰는 소프트웨어를 함께 가리킨다. | "Systems differ, and the subtle differences can lead to devastating results." | |
| F17-046 | 271 | OTS는 SOUP (Software of Uncertain Pedigree, 출신이 불확실한 소프트웨어)라고도 불린다. 이름이 문제를 앞에 내세워서 더 낫다고 한다. | "SOUP (Software of Uncertain Pedigree)" | |
| F17-047 | 271 | 구현이 깊어진 뒤에야 OTS의 군더더기 기능 하나가 안전 위험을 일으킬 수 있음을 알게 되지 않도록, 시스템 접근으로 영향을 미리 분석해야 한다. | "deep into implementation to find out that one of the extra functions in the OTS software" | |
| F17-048 | 271 | glueware가 OTS 소프트웨어의 크기에 맞먹을 만큼 크면 OTS를 쓰는 결정을 다시 생각하라고 한다 ("may want to"). 안전 관련 시스템에서는 추가 분석과 test의 비용이 OTS를 비싸게 만들 수도 있다. | "If the glueware is going to be a significant portion of the size of the OTS software" | |
| F17-049 | 271 | 안전 관련 시스템에서 OTS의 주된 문제 첫째: 문서가 부족하다. 흔히 사용자 설명서뿐이어서 모듈 사이와 외부와의 상호작용 (API)에 관한 정보가 모자란다. | "Inadequate documentation. Often only a user manual is provided" | |
| F17-050 | 271-272 | OTS의 주된 문제: source code에 접근하지 못해 일부 안전 분석이 막히고 실제로 어떻게 동작하는지 이해하기 어렵다. 개발 과정과 시험 과정을 모른다. 알려진 결함의 정보가 부족하고, 분석이 부족하거나 없다. | "Lack of access to source code, which precludes some safety analyses." | 271쪽의 앞 두 항목과 272쪽의 항목들을 합쳤다 |
| F17-051 | 272 | OTS에는 필요 없는 기능이 있을 수 있다. "turn off"할 수 있어도 OTS를 다시 compile하지 않으면 그 기능의 code는 시스템에 남는다. 나머지 시스템을 그 기능에서 보호하려면 wrapper가 필요할 수 있다. | "unless the OTS software is recompiled" | |
| F17-052 | 272 | JSC의 작업 지침 EA-WI-018은 기능의 중요도를 먼저 정하고, OTS 후보에 대한 검토의 양을 그 중요도에 따라 정하도록 한다. 생명을 위협하는 위험이 있는 project는 Appendix H의 OTS 점검표 (둘째 점검표)의 처음 세 항목을 해야 한다. | "The amount of scrutiny the candidate OTS software faces is based on the" | |
| F17-053 | 272-273 | 안전 관련 code와 같은 platform에 있는 모든 OTS 소프트웨어는 안전 관련 code에 영향을 줄 수 없음을 분석해야 한다. 문서는 COTS의 안전과 신뢰성을 시험하는 독립된 인증 기관이 없으므로, 추가 분석과 test를 모두 사용자가 해야 한다고 한다. | "Since there is no independent COTS certification authority" | |
| F17-054 | 273 | 안전과 관계없는 OTS 소프트웨어를 안전 관련 소프트웨어와 같은 platform에 두는 것은 권하지 않는다. 구매 전에 위험 분석을 갱신하거나 적어도 검토해야 한다 ("should"). | "Using non-safety-critical OTS software on the same platform as safety-critical software is" | |
| F17-055 | 273 | OTS를 고를 때 묻는 것: 그 운영 context가 새 시스템과 맞는가. 원래 시스템과의 차이점이 동작에 어떻게 영향을 주는가. | "Is its operational context compatible with the system under development?" | |
| F17-056 | 273 | 운영체제나 언어 library처럼 매우 잘 알려진 소프트웨어는 오류가 없다고 여겨지기 쉽다. 안전 관련 시스템에서는 오류가 없다고 가정하지 말라고 한다. | "you do not want to assume there are no errors" | |
| F17-057 | 273 | 사용자가 수천 명인 일반 library에서는 대부분의 결함이 찾아져 보고되리라 기대할 수 있다. 작은 프로그램은 그런 검증을 덜 받아 결함이 더 남아 있을 수 있다. 공급자가 그 정보를 보관하고 사용자에게 주는지 확인하라고 한다. | "What is the user base of the software?" | |
| F17-058 | 273 | 갱신판의 API가 크게 바뀌었는가, 갱신 때마다 glueware를 고쳐야 하는가, 공급자가 결함 patch를 알려 주는가, 오래된 판도 지원하는가를 묻는다. | "How compatible are upgrades to the software?" | 273쪽과 274쪽의 질문들이다 |
| F17-059 | 274 | 사용자가 OTS와 어떻게 상호작용하는지를 적은 잘 정의된 API나 ICD가 있는가, 문서에 없는 API 함수가 있는가, 입력의 범위를 함수가 점검하는가 사용자의 몫인가를 묻는다. | "Is there a well-defined API (Application Program Interface), ICD" | |
| F17-060 | 274 | 알려진 결함과 해결되지 않은 문제를 공급자 밖의 제품 지원 그룹, newsgroup, web site에서도 찾으라고 한다. 단 그 정보의 출처를 따져야 한다고 덧붙인다. | "Are there any known defects in the software?" | |
| F17-061 | 275 | OTS가 독립 실행 (운영체제 등)이면 API와 ICD가 주된 관심이고, 통합되는 것 (library 등)이면 더 많은 test나 분석이 필요할 수 있다. | "Will the OTS software be stand-alone or integrated into your system?" | |
| F17-062 | 275 | 버전 1.0은 오류와 문제의 위험이 더 높으므로 첫 bug-fix 갱신까지 기다리거나 다른 제품을 고르는 것을 생각하라고 한다 ("Consider"). | "Is the software version 1.0?" | |
| F17-063 | 275 | IEEE 1228이 말하는 것으로 문서가 전하는 조건: 다시 쓰는 소프트웨어와 산 소프트웨어는 충분히 시험되었고, 위험이 받아들일 만하며, 계획한 사용의 context에서 안전해야 한다. 이를 만족하지 못하거나 위험과 고장의 결과를 알 수 없으면 안전 관련 시스템에 쓰지 말아야 한다. | "should not be used in a safety-critical system" | IEEE 1228 자체는 받지 않았다. 이 문서가 전한 것이다 |
| F17-064 | 275-276 | IEEE 1228의 최소 승인 과정으로 문서가 전하는 것: 인터페이스와 기능을 정하고, 관련 문서와 그 상태를 확인하고, 공개된 명세와의 적합성을 정하고, 능력과 한계를 확인하고, 승인된 test 계획으로 안전 관련 기능을 프로젝트의 소프트웨어와 분리하여 그리고 함께 시험하고, 위험 평가를 한다. | "test the safety-critical features of the previously" | 275쪽의 목록이 276쪽의 위험 평가 항목으로 이어진다 |
| F17-065 | 276 | wrapper는 OTS code를 나머지에서 격리하는 encapsulation으로, 어떤 입력이 OTS에 닿지 못하게 막거나 OTS의 출력을 점검할 수 있다. 입력의 제한은 어떤 값이 OTS를 이상하게 동작시키거나 dormant code를 실행시킬 때 한다. | "Wrappers are an encapsulation mechanism, where the OTS code is isolated from the rest of the" | |
| F17-066 | 276 | 그런 입력을 찾기는, 특히 source code가 없고 문서가 겨우 충분할 때 어렵다. 문서는 OTS component의 해로운 출력과 그것을 일으키는 입력을 찾기 위해 software fault injection을 쓰는 것을 참고 문헌 (83)으로 든다. | "especially when the source code is unavailable and the documentation is" | |
| F17-067 | 276 | wrapper의 문제: OTS의 인터페이스를 잘 이해해야 하므로 충분한 문서가 필요하고, 문서화된 이해 밖의 출력은 wrapper를 빠져나갈 수 있다. wrapper가 OTS component의 크기에 가깝거나 넘을 만큼 복잡해질 수 있다. | "Outputs that are outside the documented understanding may slip through the wrapper." | |
| F17-068 | 277 | 복제와 다수결 (N-version programming 포함)은 같은 입력에 항상 같은 결함이 나는 소프트웨어에 쓸 수 있으나, 신뢰성이 논란이 되므로 권하지 않는다고 한다 ("not recommended"). | "(especially N-Version programming) has debatable" | |
| F17-069 | 277 | 시스템을 high-performance 부분과 high-assurance kernel (safety kernel)로 나누고, OTS는 high-performance 부분에 둘 수 있다. 그 부분이 고장 나면 시스템은 high-assurance kernel로 돌아가 안전 상태를 유지하며 성능을 낮춰 기능을 제공한다. | "Partitioning the system into a high-performance portion and a high-assurance kernel" | |
| F17-070 | 277 | 중복 구조도 wrapper처럼 복잡하고, 알려지지 않았거나 예기치 못한 기능을 효과적으로 다루지 못하므로 OTS의 만능 해결책이 아니라고 한다. | "Redundant architecture is no silver bullet for OTS." | |
| F17-071 | 278 | OTS가 다른 응용을 위해 쓰여서 갖게 되는 불필요한 기능의 code를 "dormant" code라고 부른다. dormant code를 찾으려면 source code가 필요하다. 없으면 공급자에게 쓰려는 함수 목록을 주어 정보를 구하거나 문서에서 쓰지 않을 함수를 찾는다. 쓰는 기능의 비율이 높을수록 dormant code가 적다. | "The higher the ratio of used functionality to total functionality in the OTS software" | |
| F17-072 | 278 | dormant code가 있으면 그것을 실행시키는 자극 (명령, 특정 루틴 호출, 상태나 매개변수에 따른 진입)을 찾고, 그 code가 쓰는 memory와 저장 공간도 본다. 이상적으로는 dormant code가 결코 실행되지 않음을 확인하지만 현실은 이상적이지 않으므로 위험 완화 계획이 필요하다. | "verify that it cannot ever be" | |
| F17-073 | 278 | dormant code가 실행되면 시스템이 안전하지 않은 상태로 가는지, 성능이 떨어지는지, 위험을 일으키거나 위험 통제를 방해하는지 살핀다. 안전 관련 기능을 OTS의 오동작에서 보호하려면 wrapper나 firewall이 필요하며, dormant code가 많을수록 우연히 실행될 가능성이 크다. | "The more dormant code there is in the OTS software, the more likely it is to" | |
| F17-074 | 278 | dormant code를 실수로 실행하지 않게 하는 절차적 방법은 최후의 수단으로만 고려한다. 사람의 실수가 문제를 일으킬 여지가 많기 때문이다. | "methods to avoid accidentally invoking the dormant code" | |
| F17-075 | 279 | 추가 test의 양은 dormant code의 양, code 내부를 아는 정도, 안전 문제에 따라 정한다. 소프트웨어 공학자와 안전 공학자가 project 관리의 의견을 들어 위험에 따라 정한다. source도 없고 개발과 test 정보도 거의 없는 OTS가 안전 통제를 방해할 수 있으면 추가 test가 필요하다. | "OTS software that could interfere with a safety control, with no source" | |
| F17-076 | 279 | 다시 쓰는 소프트웨어의 가장 큰 문제는 심리적인 것이라고 한다. 이전 시스템에서 잘 시험되었으니 추가 분석이 필요 없다는 생각은 틀렸고, 문서는 Ariane 5 팀이 Ariane 4 소프트웨어를 다시 쓸 때 그렇게 생각했다고 말한다. | "The greatest problem with reusing software created for a different project is psychological." | Ariane 5의 상세는 참고 문헌 (86)으로 넘긴다 |
| F17-077 | 279 | 시스템은 서로 같지 않다. 새 시스템은 더 빠른 processor에서 돌아 timing 문제가 드러나거나, 다시 쓴 code가 시스템을 오래 점유해 주기적으로 실행해야 할 핵심 task를 늦추거나, 입력 data가 달라 이전에 놓친 문제가 나올 수 있다. | "No two systems are alike." | |
| F17-078 | 279 | 다시 쓰는 code를 새 시스템의 용량, 능력, 요구에 비추어 분석해야 한다 ("very important"). 볼 것: timing, 시스템 독점, 변수 덮어쓰기, 같은 시스템 자원을 다른 목적에 쓰는 것. | "It is very important to analyze the reused code in light of the capacity, capability, and" | |
| F17-079 | 279 | 소프트웨어 재사용은 아직 초기 단계이고 모든 함정이 발견된 것은 아니라고 한다. | "software reuse is still in its infancy" | |
| F17-080 | 279 | 철저히 시험하고 분석한 OTS라도 새 시스템에서 어떻게 동작하는지 분석하고 시험해야 한다. | "Even the most thoroughly tested and analyzed OTS software must still be analyzed and" | |
| F17-081 | 280 | 안전 관련 OTS (COTS, GOTS, 다시 쓰는 소프트웨어)는 사용자가 분석하고 시험해야 한다 ("should"). 안전 관련 소프트웨어와 같은 platform에서 partition되지 않고 있는 것과 위험이 높은 OTS도 안전 관련으로 보며, 고쳤든 아니든 한다. | "Safety-critical Off-The-Shelf (COTS, GOTS, or reused) software should be analyzed" | |
| F17-082 | 280 | 문서는 Ariane 5가 잘 시험된 소프트웨어를 새 시스템 (영역)에 적용하면 큰 문제를 일으킬 수 있음을 보여 주었다고 쓴다. | "demonstrated that well tested software can cause significant" | |
| F17-083 | 280 | 먼저 이미 한 test를 확인한다. 정부가 공급했거나 정부 계약으로 개발한 소프트웨어는 위험 분석이 있을 수 있고, 상용 소프트웨어는 다른 안전 제도 (FAA, 의료, 자동차 등)를 위해 개발된 것이 아니면 있을 가능성이 낮다. | "it is less likely for commercial software unless developed for other safety regimes" | 인용 뒤의 괄호에 "FAA, medical, automobile"이 있다 |
| F17-084 | 280 | 안전 관련 시스템에 이미 쓴, 고치지 않은 소프트웨어의 기존 위험 분석과 test 결과를 새 시스템의 인증 근거로 쓸 수 있다 ("may"). 단 새 환경과의 차이에 비추어 그 적합성을 검토해야 한다. | "may be used as the basis for certification" | |
| F17-085 | 280 | OTS가 위험에 관여하면 완화를 다뤄야 한다. source가 있으면 고치고 같은 조건에서 다시 시험한다. source가 없으면 wrapper로 감싸거나, 자체 소프트웨어에 기능을 더하거나, 위험의 원인이나 통제에서 소프트웨어 제어를 빼거나, OTS를 쓰지 않기로 결정한다. | "or even deciding not to use the OTS software" | |
| F17-086 | 280 | 문서는 OTS 소프트웨어의 안전에 대한 확신을 주는 일이 아직 "black art"에 가깝다고 한다. | "something of a black art" | |
| F17-087 | 281 | OTS를 위험 분석에 포함하고 OTS가 안전 관련 code에 영향을 주는 길을 찾는다: 안전 관련 변수가 있는 memory를 덮어쓰기, 자원을 다 써서 안전 관련 code가 실행되지 못하게 하기, 메시지 queue를 막기. | "overwriting a memory location where a safety-critical variable is stored" | |
| F17-088 | 281 | source code가 없는 일이 많으므로 주된 test는 black box다. 입력의 범위를 시험하고 잘못된 입력으로 오류 처리를 시험한다. 예외, 무한 loop, 자원 과다 사용도 본다. software fault injection은 component 사이의 interface에서도 쓸 수 있어 source가 없어도 된다. | "the primary testing will be black box" | |
| F17-089 | 281-282 | 시스템에 이미 하는 분석 (timing, sizing, throughput, software fault tree, interdependence와 independence, design constraint, code interface, code data, interrupt, test coverage)에 OTS를 포함해 갱신해야 한다. fault tree에는 OTS의 결함과 dormant code도 넣는다. | "Software fault tree, to include faults and dormant code in the OTS software" | |

## 3. misra-compliance-2020 (MISRA, MISRA Compliance:2020, 2020. PDF 쪽 = 인쇄 쪽 + 8)

규칙의 내용은 이 문서에 없다. 13장의 읽기 기록 (ch13-facts.md)이 이 문서의 같은 절을 다른 쪽에서 다뤘다 (F13-013 - F13-026).

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| F17-090 | 12 | 이 문서에서 "compiler"는 compiler 자체와 linker, library manager, 실행 파일 형식 변환 tool 같은 딸린 tool을 모두 가리킨다. | "as well as any associated tools such as a linker, library manager and" | |
| F17-091 | 12 | compiler 개발자에게서 정보를 얻기 어려우면 선택을 돕는 방법: 개발자가 알맞은 개발 과정을 따르는지 보기, 평가와 사용자 경험담 읽기, 사용자 수와 응용 종류 보기, 적합성 시험 묶음이나 기존 응용의 compile로 독립 검증 시험을 하고 기록하기. | "Performing and documenting independent validation testing" | |
| F17-092 | 13 | 임베디드 target용 compiler도 validation suite로 시험할 수는 있으나, 발행 시점에 정식 validation 제도는 없다. tool은 ISO 9001의 요구를 만족하는 품질 체계로 개발되어야 한다고 한다. | "no formal validation scheme exists at the time of publication" | ch13의 F13-020과 같은 쪽이다 |
| F17-093 | 13 | tool 공급자는 검증과 validation 활동의 기록, 통제된 개발을 보이는 변경 기록을 보여 줄 수 있어야 하고, 사용자가 보고한 결함의 기록, 기존 사용자에게 알려진 결함의 통지, 이후 판에서의 수정 체계를 갖춰야 한다 ("should"). | "Notifying existing users of known faults" | |
| F17-094 | 13 | 사용자 수와 지난 6-12개월의 보고된 결함을 보면 tool의 안정성을 가늠할 수 있다. 공급자에게서 이 수준의 확신을 얻기 어려운 일이 많고, 그때는 tool이 충분한 품질인지 확인할 책임이 개발자에게 있다. | "the onus is on the developer to ensure that the tools are of adequate quality" | |
| F17-095 | 13 | 개발자가 tool에 대한 확신을 얻는 방법: 문서로 남기는 validation test, 공급자의 개발 과정 평가, 지금까지의 tool 성능 검토. | "Review the performance of the tool to date." | |
| F17-096 | 13 | compiler의 validation test는 이전 응용의 문제없는 code로 할 수 있다. 같은 쪽에서, 이 test는 제품 code를 compile할 때와 같은 compiler option, linker option, source library 판으로 해야 한다고 한다 ("must"). | "validation testing of the compiler must be performed for the same set of" | |
| F17-097 | 14 | tool 공급자가 tool에 영향을 주는 알려진 결함의 목록과 우회법을 유지하면, 프로젝트를 시작하기 전에 그것을 아는 것이 유리하다. 공급자에게 없으면 결함이 발견될 때마다 자체 목록을 유지하고 공급자에게 보고한다. | "a local list should be maintained whenever a defect or suspected defect is discovered" | |
| F17-098 | 14 | IEC 61508, ISO 26262, DO-178은 어떤 상황에서 compiler와 정적 분석 tool의 qualification을 요구한다고 이 문서는 주석으로 적는다. | "qualification of compilers and static analysis tools in some situations" | 그 상황이 무엇인지는 이 문서에 없다 (ch13의 F13-022와 같다) |
| F17-099 | 14 | compiler option의 사용이나 불사용은 표준 적합성, 언어 확장과 조건부 기능의 사용 가능성, 자원 사용, compiler 결함이 드러날 가능성에 영향을 줄 수 있다. | "The likelihood that a defect in the compiler will be exposed" | |
| F17-100 | 14 | compiler의 최적화 option은 실행 속도와 code 크기의 균형을 보아 신중히 고르며, 더 공격적인 최적화는 compiler 결함이 드러날 위험을 높일 수 있다 ("may"). | "Using more aggressive optimizations may increase the risk of exposing defects in the compiler." | 최적화로 code의 동작이 바뀐 사례는 이 문서에 없다 |
| F17-101 | 14-15 | 정적 분석 tool은 compiler의 implementation-defined 동작에 맞춰 설정해야 한다. compiler는 보통 특정 processor용이지만 정적 분석 tool은 일반 목적이므로 정수 형의 크기 같은 것을 알려 주어야 한다. | "static analysers need to know the sizes of the integer types" | |
| F17-102 | 15 | 정적 분석 tool이 compiler의 언어 확장을 지원하게 설정할 수 없으면, 확장을 쓴 code의 적합성을 확인할 다른 절차를 마련해야 한다. | "an alternative procedure will need to be put in place" | |
| F17-103 | 25 | 프로젝트 밖에서 온 code는 고쳐서 준수시키기 어렵거나 불가능한 일이 많고 (source가 있어도), 이를 "adopted code"라 하며 프로젝트 안에서 개발한 "native code"와 구분한다. | "this type of code will be referred to as adopted code" | 6.1절 |
| F17-104 | 25 | adopted code의 출처로 문서가 드는 것: Standard Library, 반도체 제조사의 device driver, middleware (운영체제, protocol stack, 개발 tool), 제3자 library, modelling tool 등이 자동 생성한 code, legacy code. | "Automatically generated code" | 인용은 목록의 한 항목이다 |
| F17-105 | 25 | adopted code가 시스템의 integrity에 미치는 영향을 간과하거나 무해하다고 가정해서는 안 된다 ("must never"). 두 질문은 서로 같지 않다: 검증 가능한 안전과 보안의 수준으로 개발되었는가, MISRA 지침에 맞게 개발되었는가. | "The impact of adopted code on the integrity of a system must never be overlooked or assumed to be" | |
| F17-106 | 25 | MISRA 지침의 준수는 adopted code의 품질을 보장하는 데 필요한 조건도 충분한 조건도 아니다. | "neither a necessary nor a sufficient condition" | |
| F17-107 | 25 | adopted code가 native code와 정확히 같은 준수 기준으로 개발되지 않았으면 MISRA 준수의 주장은 필연적으로 손상된다. adopted code는 준수를 목표로 하지 않았을 수도, 지침의 다른 판이나 다른 준수 기준 (GRP)으로 썼을 수도 있다. | "claims of MISRA Compliance will inevitably be compromised" | |
| F17-108 | 25 | 일부 지침은 시스템 전체 분석 범위에서 적용되므로, 각각 준수하는 두 translation unit도 한 시스템에서 합치면 준수하지 못할 수 있다. adopted code가 끼면 고치기 어려워 deviation이 필요할 수 있다. | "may not be compliant when combined in the same system" | 6.2절 |
| F17-109 | 26 | adopted code가 binary로만 있는 일이 많고, 그러면 MISRA 준수뿐 아니라 code 자체의 품질을 검증하는 범위도 제한된다. 공급자가 준수 선언을 줄 수도, 협력 조직이 공통 절차와 tool을 쓰거나 source의 stub를 주고받을 수도 있다. source 전체가 없으면 시스템 수준 지침의 준수는 검증하지 못한다. | "adopted code will only be available in binary form" | 6.3절. 인용은 같은 문장의 앞부분이다 |
| F17-110 | 26 | adopted code의 source가 없을 때는 binary의 정적 분석이나 동적 분석 같은 다른 길을 찾아야 한다. 같은 쪽의 주석은 여러 조직의 개발 관리에 관해 ISO 26262 Part 8 Clause 5 "Interfaces in distributed development"를 든다. | "Interfaces in distributed development" | |
| F17-111 | 26 | adopted source code에 지침 위반이 있다고 반드시 품질이 나쁜 것은 아니지만, 위반은 무시할 수 없다. 모든 위반을 검토하여 integrity가 훼손되지 않았음과 승인된 deviation으로 덮임을 확인해야 한다. | "violations cannot simply be ignored" | 6.4절 |
| F17-112 | 26 | adopted code는 고칠 수 없으므로 덜 엄격한 GRP를 따로 둘 수 있다. adopted code의 GRP가 더 관대하다고 안전에 대한 헌신이 덜한 것은 아니며, 위반이 더 많이 검토 대상이 될 뿐이다. Mandatory 지침을 어긴 code는 결코 준수한 것으로 분류할 수 없다. | "can never be classified as compliant" | 같은 쪽의 "does not imply that the commitment ... is any less stringent"도 근거다 |
| F17-113 | 27 | code를 바꿀 수 없는 adopted code에서 GRP의 역할은 개발에 영향을 주는 것보다, 얼마나 준수하는지를 기록하고 모든 위반이 적절히 검토되었음을 보증하는 것이다. | "to document the extent to which the adopted code is compliant" | |
| F17-114 | 27 | adopted header file의 macro가 native code에 전개되면 위반이 adopted code 탓인데 native code 안에 나타날 수 있다. 문서의 예는 macro `NOT_NULL`이 0과 비교하여 규칙 11.9를 어기는 것이다. | "Sometimes a violation which is clearly attributable to the adopted code is actually located within the" | 6.5절 |
| F17-115 | 27 | Standard Library의 code는 compiler 구현의 일부이므로 MISRA 지침을 준수할 필요가 없다. 단 표준 header의 선언과 macro가 제공하는 interface에 의존하는 지침 (함수 인수와 반환값의 형 검사 등)은 여전히 적용된다. 프로젝트가 이롭다고 보면 Standard Library를 다른 adopted code처럼 다룰 수 있다. | "Standard Library code is not required to comply with MISRA Guidelines." | 6.6절 |

## 4. nasa-mcdc-tutorial (Hayhurst, Veerhusen, Chilenski, Rierson, A Practical Tutorial on Modified Condition/Decision Coverage, NASA/TM-2001-210876, 2001. PDF 쪽 = 인쇄 쪽 + 6)

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| F17-116 | 56 | 문서는 coverage 분석 자동화에서 생기는 문제를 막기 위해 coverage tool의 작동과 고를 때 볼 요인을 설명한다. 이 요인이 tool을 쓸 때 고려할 모든 것은 아니라고 한다. 절의 처음에 "이해하지 못하는 것을 자동화하는 것은 위험하다"는 말 (참고 문헌 19)을 인용한다. | "important factors to consider in selecting and qualifying a structural coverage tool" | 항공의 MC/DC 맥락이다. 절 앞머리에 "[I]t's dangerous to automate something that we don't understand"라는 인용 (참고 문헌 19)이 있으나, 쪽의 글자 층에서 줄이 갈라져 인용 칸에는 쓰지 않았다 |
| F17-117 | 56 | coverage tool은 보통 code에 probe (hardware나 software), flag 같은 감시 장치를 넣어 (instrument) 어떤 부분이 실행되는지 본다. instrumentation이 code를 바꾸므로, 그것이 오류를 숨기거나 넣지 않음을 보이는 것이 필수다. 보통 원래 code와 instrument한 code에 같은 test를 돌려 결과를 견준다. | "demonstrating that the instrumentation does not conceal or introduce an error is essential" | |
| F17-118 | 56 | coverage tool은 instrument한 code가 MC/DC 기준을 만족함을 확인할 뿐이고, instrument하지 않은 code도 그렇다는 것은 가정이다. 그 가정이 맞는지는 instrumentation 방법과 compiler의 조합에 달렸다. | "The assumption is that the uninstrumented code does, too." | |
| F17-119 | 56 | tool을 고르거나 qualify할 때 이해해야 할 요인: 감시하는 statement의 종류, 감시하는 곳 (source냐 object code냐), 감시할 수 있는 condition과 decision의 최대 수, 독립된 효과를 정하는 algorithm, 관계 연산자의 처리, instrumentation의 효과. | "algorithms used for determining independent effect" | 4.1.2절. instrumentation 방식도 알아야 한다고 같은 쪽이 적는다 |
| F17-120 | 57 | 모든 tool이 MC/DC에 필요한 coverage point를 다 지원하지는 않는다. 예로 진입점과 출구점을 지원하지 않는 tool이 있고, 그러면 다른 방법으로 덮어야 한다. Boolean 형이 없는 언어에서는 tool이 어느 식이 Boolean인지 추정해야 해서 모든 Boolean 식을 감시하지 못할 수 있다. 문서는 C를 그런 언어의 예로 든다. | "Some tools do not support all of the coverage points required for MC/DC." | 쪽 아래 각주 17이 C를 가리킨다 |
| F17-121 | 57 | object code 수준에서 MC/DC를 얻는 것이 source code 수준에서 얻는 것과 반드시 같지는 않다. 문서는 object code 수준의 분석이 source 수준과 같음을 보이는 분석을 제공하면 object code 수준에서 MC/DC를 보일 수 있다는 인증 FAQ를 인용한다. | "MC/DC at the object code level is not necessarily" | 항공의 것. 인용한 FAQ는 참고 문헌 9의 #42다 |
| F17-122 | 58 | object code 수준의 coverage tool을 쓰려면 source 수준과의 동등성을 확인하는 분석이 필요하다. 이 분석은 보통 쉽지 않고 인증 기관이 프로젝트 초기에 검토해야 한다 ("should"). | "not typically trivial" | 항공의 것. 원문은 이 쪽의 OCR 텍스트에서 띄어쓰기가 붙어 있다 |
| F17-123 | 58 | 어떤 tool은 한 Boolean 식에서 감시할 수 있는 condition의 수나 전체 condition, decision, statement의 수에 제한이 있다. 큰 식을 완전히 무시하거나 일부만 감시할 수 있다. 제한은 명확히 알아야 하고, 영향이 있으면 완화 전략과 절차를 정해 문서로 남긴다. 식이 tool에 너무 크면 수동 분석이 필요할 가능성이 높다. | "In some cases, large expressions may be completely ignored" | |
| F17-124 | 58 | tool마다 condition의 독립된 효과를 정하는 algorithm이 다르다. 관계 연산자는 Boolean 연산자가 아니므로, 식에 관계 연산자가 있을 때 tool이 조건을 제대로 감시하는지 검토해야 한다. | "Different structural coverage analysis tools use different algorithms" | 관계 연산자의 예 `(x<y) and (x>z)`가 같은 쪽에 있다 |
| F17-125 | 59 | software probe는 memory와 CPU 시간의 부담을 더한다. throughput이나 memory가 빠듯한 component에서는 instrument한 소프트웨어가 제대로 동작하지 않을 수 있다. | "Software probes add overhead for memory and CPU cycles." | |
| F17-126 | 59 | hardware probe는 보통 instruction fetch를 감시하며, cache가 있는 현대의 hardware 구조에 속을 수 있다. instruction이 cache로 fetch되었다고 실행된 것은 아니다. | "Just because an instruction is fetched into cache" | |
| F17-127 | 59-60 | software probe를 넣으면 compiler가 다른 code를 만들 수 있다. 문서의 예: 식에서 함수 B가 함수 A의 부수 효과에 의존하는데, instrument하지 않은 code는 A를 먼저 부르도록 compile되지만 instrument한 code에서는 B를 먼저 부르는 code를 만든다. 그러면 instrument한 code가 시스템 맥락에서 잘못 동작한다. | "the presence of the probes may cause the compiler to generate code that" | 사례는 식의 평가 순서다. 항공의 coverage tool 맥락이며 최적화 설정과의 관계는 이 쪽에 없다 |
| F17-128 | 60 | coverage tool을 쓰면 instrument한 소프트웨어에 다른 compiler나 compiler switch, linker, target (emulator, simulator)가 필요할 수 있고, 이는 instrument한 code와 하지 않은 code의 실행 결과의 충실도에 영향을 준다. 충실도의 정도를 평가하여 tool의 역할을 정해야 한다. | "Each of these can affect the fidelity of the execution results" | |

## 5. ariane-501-report (ESA, Ariane 501 Inquiry Board Report, 1996. PDF 쪽 = 보고서 쪽 + 4. 스캔본이며 OCR로 읽었다)

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| F17-129 | 9 | SRI에서 변환을 보호하지 않은 변수 세 개를 두기로 한 이유는, 그것들이 물리적으로 제한되거나 안전 여유가 크다는 추론이었다. 변수 BH에서는 그 추론이 틀렸다고 한다. Ariane 5의 궤적 data를 SRI의 요구와 명세에 넣지 않기로 합의했다고 한다. | "it was jointly agreed not to include the Ariane 5 trajectory data" | 보고서 5쪽. 이 장에서는 다시 쓴 소프트웨어의 요구가 새 환경의 입력 범위를 담지 않은 사례다 |
| F17-130 | 10 | 정렬 (alignment) 기능을 이륙 후 50초까지 계속하게 한 요구는 Ariane 4의 이전 모델들을 위해 10년도 더 전에 정한 것이다 (count-down 중단 때 짧은 launch window를 쓰기 위한 것). 같은 요구가 Ariane 5에는 해당하지 않는다. | "The same requirement does not apply to Ariane 5" | 보고서 6쪽 |
| F17-131 | 10 | 그 요구가 Ariane 5에도 유지된 것은 공통성 때문이고, 아마 Ariane 4에서 잘 돌던 소프트웨어는 필요하다고 증명되지 않는 한 바꾸지 않는 것이 현명하다는 견해에 따른 것이라고 보고서는 쓴다 ("presumably"). | "it was maintained for commonality reasons" | 보고서 6쪽 |
| F17-132 | 10 | 위원회는 소프트웨어가 올바르다고 보고 오류가 드러날 때까지 두는 견해와 반대로, 현재 받아들여지는 best practice로 올바름을 보일 수 있을 때까지는 결함이 있다고 가정하는 견해를 지지한다고 쓴다. | "software should be assumed to be faulty until" | 보고서 6쪽 |
| F17-133 | 10 | 위원회는 임무가 위태로워질 정도로 중요한 소프트웨어를 매우 세부적인 수준까지 식별하고, 예외적 동작을 가두고, 소프트웨어 고장을 고려한 합리적인 back-up 정책이 필요하다고 쓴다. | "exceptional behaviour must be confined" | 보고서 6쪽 |
| F17-134 | 11 | SRI의 장비 수준 test는 환경 요인에 엄격했으나, Ariane 5의 count-down과 비행 순서와 궤적 아래에서 SRI가 올바르게 동작하는지를 확인하는 test는 하지 않았다. | "no test was performed to verify that the SRI would behave correctly" | 보고서 7쪽 |
| F17-135 | 11 | 그런 시험을 하지 않은 주된 이유는, SRI 명세 (SRI의 요구 문서)가 Ariane 5의 궤적 data를 기능 요구로 담고 있지 않아서였다. 지상에서 가속도 신호를 모의로 넣고 회전대를 쓰는 시험이 가능했고, 했다면 고장 기구가 드러났을 것이라고 보고서는 쓴다. | "does not contain the Ariane 5 trajectory data as a functional requirement" | 보고서 7쪽. 같은 쪽의 "the failure mechanism would have been exposed"도 근거다 |
| F17-136 | 11 | 시스템 명세는 선택한 구현에서 나오는 운용상의 제약을 밝히지 않았다. 위원회는 그런 한계의 선언이 모든 임무 중요 장치에 의무여야 한다고 쓴다. 그것이 있었다면 Ariane 5의 궤적과의 불일치를 식별했을 것이다. | "should be mandatory for every mission-critical device" | 보고서 7쪽 |

## 6. autosar-safety-measures (AUTOSAR, Overview of Functional Safety Measures in AUTOSAR, CP R25-11. PDF 쪽 = 문서의 "46 of 72")

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| F17-137 | 46 | AUTOSAR가 강제하지도 제공하지도 않는 기능 안전 조치의 예 (목록이 완전하다는 뜻은 아니라고 문서가 적는다): AUTOSAR 명세는 ISO 26262 Part 10의 SEooC를 정의하지 않는다. 전체 안전 개념, ASIL 식별, dependent failure analysis, AUTOSAR의 safety case, confirmation measure, 기능 안전 감사, conformance test가 없다. | "does not define Safety Elements out of Context" | SEooC의 정의 자체는 이 문서에 없다 |
| F17-138 | 46 | 같은 목록에는 software component의 구현 기법 (낮은 복잡도, 견고성, defensive programming, 규약, coding rule), AUTOSAR 기능의 component 구현 추적, software integration test, AUTOSAR 명세에 대한 V&V, 구현에 관한 결함 보고와 추적과 해결도 있다. | "Software integration testing" | 같은 쪽 위쪽의 문장은 안전 관련 응용의 개발자가 안전 개발 life cycle이 알맞은지 확인해야 한다고 한다 |

## 7. nasa-std-8739-8b (NASA, NASA-STD-8739.8B Software Assurance and Software Safety Standard, 2022. PDF 쪽 = 인쇄 쪽)

표는 NPR 7150.2의 요구와 그에 대한 소프트웨어 보증과 안전의 task를 짝지은 것이다. 아래에서는 NPR 7150.2의 요구 (project manager가 "shall"한다)를 적는다. 번호 SWE-nnn은 문서가 쓴 번호다.

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| F17-139 | 9 | 용어 정의: "accredit"는 소프트웨어 개발 tool, 모델, 모의 (관련 data 포함)를 특정 목적에 쓰도록 공식으로 받아들이는 것이다. | "The official acceptance of a software development tool, model, or simulation" | 3.2절 |
| F17-140 | 13 | 이 문서의 "software" 정의는 NASA가 개발한 것, NASA를 위해 개발한 것, NASA가 유지하는 것 외에 COTS, GOTS, MOTS, OSS, 다시 쓰는 component, 자동 생성 code, legacy, heritage, freeware, shareware, 시험판, open source component도 포함한다. | "auto-generated code, embedded software" | NPR 7150.2의 정의를 옮긴 것이다 |
| F17-141 | 20-21 | COTS, GOTS, MOTS, OSS, 다시 쓰는 소프트웨어 component를 얻거나 쓸 때 project manager가 만족해야 하는 조건 (SWE-027): (a) component가 만족할 요구를 식별, (b) 의도한 목적에 필요한 문서 (사용 설명서 등)가 포함, (c) 소유권, 사용권, 보증, license, 양도 권리, 사용 조건 (GNU GPL 같은 license의 재배포 조건 포함)이 다루어짐, (d) 이후의 지원이 계획되고 충분함, (e) 비슷하게 개발한 component를 받아들일 때와 같은 수준으로 검증하고 validation함, (f) 공급자가 보고한 결함을 주기적으로 평가할 계획. | "Open Source Software (OSS), or reused software component is" | NASA의 요구다. 인용은 20쪽의 조건 머리말이다 |
| F17-142 | 21 | 위 (e)의 요구는 사 온 component를 직접 개발한 component와 같은 수준으로 검증하고 validation하라는 것이다. (f)는 공급자가 보고한 결함이 선택한 component에 영향을 주지 않는지 주기적으로 평가할 계획을 요구한다. | "periodic assessments of vendor reported defects" | NASA의 요구다 |
| F17-143 | 29 | 자동 code 생성의 접근을 project manager가 정하도록 하는 요구 (SWE-146): 자동 생성 tool의 V&V, tool과 data의 configuration management, 자동 생성 소프트웨어의 사용 범위와 한계의 기술, 생성된 source code의 V&V를 손으로 쓴 code와 같은 표준과 과정으로 함, 실제 사용을 계획과 견주어 감시, 생성된 source code의 수동 변경에 관한 정책과 절차, 생성 tool의 입력, 출력, 출력에 한 수정의 configuration management. | "Verification and validation of auto-generated source code using the same software standards" | NASA의 요구다 |
| F17-144 | 29 | 외부에 맡기는 개발자와 custom 소프트웨어 공급자는 NASA에 자동 생성의 입력으로 쓰는 모델, 모의, 관련 data에 전자 접근을 주어야 한다 (SWE-206). | "provide NASA with electronic access to the" | NASA의 요구다 |
| F17-145 | 37 | project manager는 소프트웨어를 개발하거나 유지하는 데 필요한 소프트웨어 tool을 validation하고 accredit해야 한다 (SWE-136). 소프트웨어 보증 task는 그 tool이 validation되고 accredit되었는지 확인하는 것이다. | "validate and accredit" | NASA의 요구다 |
| F17-146 | 39 | project manager는 비행 소프트웨어나 비행 장비의 qualification에 필요한 모델, 모의, 분석 tool에 validation되고 accredit된 것을 써야 한다 (SWE-070). | "shall use validated and accredited software models, simulations, and" | NASA의 요구다 |
| F17-147 | 40 | project manager는 내장된 COTS, GOTS, MOTS, OSS, 다시 쓰는 component를 직접 개발한 소프트웨어를 받아들일 때와 같은 수준으로 시험해야 한다 (SWE-211). | "shall test embedded COTS" | NASA의 요구다 |
| F17-148 | 47 | project manager는 모든 COTS, GOTS, MOTS, OSS, 다시 쓰는 component에서 보고된 non-conformance의 평가를 의무로 해야 하고 (SWE-203), 보증 task는 그 영향을 소프트웨어의 안전, 품질, 신뢰성에 대해 평가하는 것이다. | "implement mandatory assessments of reported non-conformances" | NASA의 요구다 |
| F17-149 | 54 | IV&V 제공자는 off-the-shelf 소프트웨어의 알맞은 사용을 검증하고 validation해야 한다. 프로젝트가 쓴 open source 소프트웨어를 모두 식별했는지, open source 사용의 보안 위험이 식별되고 완화되었는지도 확인한다. | "has identified all open-source software used" | NASA의 IV&V 요구다 (4.4.2.34) |
| F17-150 | 61 | 소프트웨어의 원인으로 고려할 목록에 "Auto-Coding errors as a cause"와 "Untested COTS, MOTS, or reused code"가 있다. | "Untested COTS, MOTS, or reused code" | 61쪽의 coding, logic, algorithm 실패 항목이다. 두 항목이 같은 쪽에 있다 |
| F17-151 | 63 | 같은 목록의 다른 쪽에는 "Inadequate testing of reused or heritage software", COTS의 결함과 사용 가능한 bug fix와 갱신을 평가하지 않음, "Unverified COTS software", "Auto-Coding tool faults and defects"가 있다. | "Auto-Coding tool faults and defects" | 63쪽 |
| F17-152 | 65 | "Unknown/Unknowns" 항목에 COTS의 알려지지 않은 한계 (운용, 환경, 부하), COTS의 추가 기능, COTS 구성 요소의 불완전한 안전 분석, "Compiler behavior errors or undefined compiler behavior"가 있다. | "Compiler behavior errors or undefined compiler behavior" | 65쪽 |

## 문서에서 찾지 못한 것

받은 문서에서 다음은 확인하지 못했다. 아래는 기억으로 아는 것이며 원고의 근거가 아니다. 원고에 쓰려면 다른 자료를 찾아 쪽을 직접 읽는다.

- `(기억)` ISO 26262의 tool confidence level (TCL)은 tool impact (TI)와 tool error detection (TD)로 정해진다. 받은 문서에는 없다 (MISRA와 NASA 문서는 규격이 qualification을 요구한다고만 적는다).
- `(기억)` IEC 61508-3의 tool 분류 (T1, T2, T3)와 ISO 26262-8의 tool qualification 방법 (사용 경험, 개발 과정 평가, validation 등)은 받은 문서에 없다. DO-178C의 tool criteria 1, 2, 3의 정의와 Table 12-1도 이 문서들에 없다 (FAA AC는 criteria와 TQL의 대응만 준다).
- `(기억)` SEooC의 정의와 가정의 검증 (ISO 26262-10)은 받은 문서에 없다. AUTOSAR의 문서는 AUTOSAR가 SEooC를 정의하지 않는다고만 말한다 (F17-137).
- `(기억)` ISO 26262-8의 proven in use와 component qualification의 기준은 받은 문서에 없다. FAA AC가 말하는 사용 이력은 service difficulty, airworthiness directive, open problem report의 평가이며 (F17-002), 항공의 것이다.
- compiler가 안전 관련 code를 바꾸어 오동작시킨 실제 사례는 받은 문서에 없다. MISRA는 공격적 최적화가 compiler 결함이 드러날 위험을 높일 수 있다고만 쓰고 (F17-100), NASA-GB는 compiler도 object code에서 오류를 낸다고만 쓴다 (F17-041). 가까운 것은 MC/DC 튜토리얼의 instrument한 code에서 compiler가 함수 호출 순서를 바꾸는 예다 (F17-127).
- code generator의 tool confidence level과 model-based development에서의 tool qualification의 세부는 받은 문서에 없다. 있는 것은 NASA-GB의 일반 서술 (F17-033 - F17-042)과 NASA-STD의 자동 생성 접근 요구 (F17-143)뿐이다.
- open source 사용에 관해서는 NASA-GB의 RTEMS와 Linux 소개 (F17-043), NASA-STD의 OSS를 COTS와 함께 다루는 요구 (F17-141)와 IV&V의 open source 식별 요구 (F17-149)뿐이다. open source의 안전 관련 사용 기준을 다룬 문서는 없다.
- Ariane 5의 상세한 사건 경과 (Ariane 4 소프트웨어의 어떤 값이 변환 오류를 냈는지 등)는 이 읽기 기록이 PDF 9-11쪽만 읽었으므로 여기 없다. 이 장은 재사용의 맥락만 쓴다.
