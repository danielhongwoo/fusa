# 15장 근거 문서에서 뽑은 사실 (읽기 기록)

대상: 15장 "Verification 전략: review, 정적 분석, formal method" (plans/ch15-verification-strategy.md). 읽은 날: 2026-11-23.

- 쪽 칸은 PDF 파일의 몇 번째 쪽이다. 문서에 인쇄된 쪽 번호가 다르면 절 머리에 차이를 적는다.
- 인용은 줄바꿈을 합치고 따옴표와 줄표를 ASCII로 바꿨다. 그 밖에는 원문 그대로다.
- 이 장의 규격 문서 (ISO 26262, IEC 61508, DO-333)는 받지 못했다. DO-333의 내용은 이 파일에 없다. FAA AC 20-115D가 그 supplement을 인정한다는 사실만 있다.
- `(기억)`은 문서에서 확인하지 못한 내용이다. 원고의 근거로 쓰지 않는다. 맨 끝의 "문서에서 찾지 못한 것" 절에만 적는다.
- NASA 지침서의 benefit rating과 cost rating은 문서가 "subjective"라고 적은 값이다 (F15-014). 비고에 그 값을 옮길 때도 이 단서가 붙는다.
- 원고에 쓰기 전에 그 쪽을 직접 열어 확인한다 (RULES.md 5.2절).

## 1. nasa-gb-8719-13 (NASA, NASA-GB-8719.13 Software Safety Guidebook, 2004. PDF 쪽 = 인쇄 쪽 + 1)

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| F15-001 | 42 | 필요한 software safety effort (Full, Moderate, Minimum, None)는 software category와 hazard severity 수준의 표로 정한다. 예: category IA에 catastrophic이면 Full, category IV에 catastrophic이면 Minimum이다. | "Table 3-5 Required Software Safety Effort" | 표 3-5. 등급에 따라 방법을 고르는 NASA 쪽의 예다. 계획표의 쪽 밖이다 |
| F15-002 | 43 | 각 기법과 각 effort 수준마다 권장 코드가 붙는다 (Mandatory, Highly Recommended, Recommended, Not Recommended). Highly Recommended를 넣지 않으면 안전이 해쳐지지 않음을 보여야 한다. | "it should be shown that safety is not compromised" | "Not Recommended"는 기대 이익에 견줘 비싼 것이라고 같은 쪽 각주가 적는다 |
| F15-003 | 45 | verification은 한 단계의 산출물이 앞 단계에서 정한 요구를 만족하는지 보는 것이다. 방법으로 analysis, review, inspection, testing, auditing을 든다. | "Verification methods include analysis, review, inspection," | 인용 뒤에 "testing, and auditing"이 이어진다 |
| F15-004 | 45 | validation은 "right product"를 만들고 있는지 보는 것이며, 보통 주된 방법은 testing이다. | "Validation checks that the" | 인용 뒤에 `"right product" is being built`가 이어진다. verification은 "built right"라고 같은 쪽이 적는다 |
| F15-005 | 46 | 한 프로젝트 안에서도 부품마다 safety effort를 다르게 할 수 있다. 위험이 큰 안전 필수 부품에는 Full, 작은 것에는 Minimum을 적용할 수 있다. | "Safety-critical software components can have different levels of software safety effort applied to them." | 같은 쪽: safety-critical과 그렇지 않은 코드를 나누면 안전 노력을 그 부분에만 쓸 수 있다 |
| F15-006 | 67 | NASA Formal Methods Guidebook을 인용해 formal method를 수학적 모델링과 형식 논리에 바탕을 둔 기법과 도구의 집합이라고 정의한다. 요구와 설계를 명세하고 검증하는 데 쓴다. | "techniques and tools based on mathematical modeling and formal logic" | 같은 쪽: formal specification과 formal verification의 두 부분으로 이루어진다 |
| F15-007 | 68 | 요구를 사람이 읽는 말로 쓰면 모호해질 수 있다. 이를 피하려고 형식적인 수학 언어로 쓰는 것이 formal specification이고, FM 적용의 첫 단계다. | "This formal specification is the first step in applying FM." | |
| F15-008 | 68 | formal verification은 결과 (software)가 formal specification을 만족한다는 증명을 준다. 단계마다 새 산출물이 앞 산출물과 일치하는지 형식으로 검증하는 점진적 활동이다. | "Verification is a progressive activity." | 예: 상세 설계를 예비 설계에 대해, 예비 설계를 안전이나 보안 같은 성질에 대해 검증한다 |
| F15-009 | 68 | FM은 높은 수준의 assurance를 준다고 인정된다. 정해진 정량 신뢰도 수준을 보장하지는 않는다. NASA, 군, 상용의 safety-critical 시스템에 성공적으로 쓰인 바 있다. | "FM does not guarantee a precise quantifiable level of reliability." | "highest degree of assurance"라는 표현도 같은 쪽에 있다 |
| F15-010 | 68 | FM을 쓰는 세 방식: 개발을 마친 뒤에 보증하는 것, 개발과 나란히 보증하는 것, FM만으로 개발하는 것. 뒤에 하는 방식은 개발 활동이 둘이라 비용과 일정이 늘고, 늦게 찾은 문제는 고치는 데 비싸다. | "increasing cost and schedule" | 같은 쪽의 세 방식 서술 가운데 첫째에 대한 것이다 |
| F15-011 | 68 | 나란히 하는 방식은 개발 팀과 FM 팀이 따로 일한다. 비용은 들지만 더 빨리 개발할 수 있고 오류를 더 일찍 찾는다. 두 팀의 소통이 필수다. | "communication between the two teams is vital" | |
| F15-012 | 68 | FM만으로 개발하는 통합 방식은 세 방식 가운데 비용이 가장 적다. 개발자가 FM을 훈련받아야 한다. | "This method is the least costly of the three" | 설계를 코드 생성 전에 형식으로 검증한다고 같은 쪽이 적는다 |
| F15-013 | 68 | FM이 모든 산업에서 널리 받아들여지지 않은 것은 주로 형식 증명의 어려움 때문이다. 처음 쓰는 사람에게는 상당한 학습 곡선이 있고 비용이 든다. 일부 사용자는 코딩 전에 값비싼 결함을 많이 없애서 전체 수명주기 비용이 줄었다고 한다. | "mostly due to the difficulty of the formal proofs" | "some users find"라는 약한 서술이다 |
| F15-014 | 69 | 증명 없이 formal specification을 만드는 과정만으로도 가치가 있다. 명세의 모호함과 불확실성을 없애면 이후의 오류를 막는다. | "Removing ambiguity and uncertainty from the specification" | 68쪽 끝에서 이어진다. 원문은 "invaluable"이라고 쓴다 |
| F15-015 | 69 | Lutz와 Ampo의 사례: 요구 수준의 formal specification과 verification으로 요구에서 37개의 문제를 찾았다. 문서화되지 않은 가정, 부족한 비정상/경계 동작, 추적성, 불일치, 모호한 용어, 논리 오류를 포함한다. | "37 issues were found in the requirements" | 시험 대상 프로젝트는 객체 지향 개발을 따랐다 |
| F15-016 | 69 | SpecTRM은 "light" formal method의 새 접근이다. 사람이 읽을 수 있고 안전 중심 설계를 지원하며, 모델을 실행해 코드 전에 동작을 동적으로 분석할 수 있다. | "the models can be executed" | |
| F15-017 | 104 | 안전 분석 기법은 두 부류다: top down (위험이나 고장에서 원인을 따라 내려감)과 bottom up (설계 산출물에서 예상하지 못한 고장 모드를 찾음). 보통 둘 다 쓰되 프로젝트에 맞게 고른다. | "Typically, both types of analyses are used" | 부정적 결과 (위험 없음)도 올바른 길에 있다는 확신을 준다고 같은 쪽이 적는다 |
| F15-018 | 104 | 기법마다 benefit와 cost 등급이 주어지고 effort 수준별 조정이 X.3절에 있다. 등급은 주관적이며 기법을 고르는 하나의 고려일 뿐이다. | "The ratings are subjective and meant to be only one" | 인용 뒤에 "consideration when choosing analysis techniques"가 이어진다 |
| F15-019 | 118 | Formal Inspection은 개발 수명주기 산출물 (요구, 설계 노트, 시험 계획, 소스 코드)에 대한 구조화된 기술 review로, 결함을 찾아 없애려고 한다. Fagan Inspection이라고도 한다. | "conducted for the purpose of finding and eliminating defects" | 118쪽 맨 아래의 6.5.5절과 각주 |
| F15-020 | 119 | Formal Inspection은 informal review나 walkthrough와 달리 정해진 단계가 있고 검토자마다 역할이 정해진다. | "differ from informal reviews or walkthroughs" | |
| F15-021 | 119 | Formal Inspection은 formal method가 아니다. 앞은 결함을 찾는 구조화된 방법이고 뒤는 수학적으로 명세하고 검증하는 방법이다. 둘을 함께 쓰거나 따로 쓸 수 있다. | "Formal inspections are not formal methods!" | 책에서 두 용어를 구별해야 하는 근거다 |
| F15-022 | 119 | NASA는 Formal Inspection의 표준과 지침서를 냈다. 요구 명세, 설계, 코딩, 시험을 포함한 개발의 모든 주요 단계에서 수행해야 한다 (should). | "should be performed within every major step of the software development process" | 인용은 원문의 "FI's" 뒤에 이어진다 |
| F15-023 | 119 | Formal Inspection은 프로젝트 초기, 특히 요구 단계에 적용할 때 영향이 가장 크다. 결함을 일찍 찾아 고치기 싸기 때문이다. 연구는 안전에 관련된 것을 포함한 고장과 결함 대부분이 빠졌거나 잘못 이해된 요구에서 나온다고 한다. | "come from missing or misunderstood requirements" | "Studies have shown"이라고 쓰며 연구는 인용하지 않는다 |
| F15-024 | 119 | 요구의 inspection 팀에는 시스템 엔지니어링, 운영, 소프트웨어 설계와 코드, 품질 보증, 안전 대표가 들어간다. 검토자는 tester, programmer, designer, user, safety 같은 관점을 맡을 수 있다. 단계마다 검사 목록 (checklist)이 있으면 도움이 된다. | "inspection checklists for each phase of development" | 안전 대표는 inspection 결과 중 안전 후속이 필요한 것을 따로 옮겨 닫힐 때까지 추적한다 |
| F15-025 | 119 | Formal Inspection of software requirements의 등급은 benefit HIGH, cost MODERATE다. | "Cost Rating: MODERATE" | benefit와 cost는 같은 줄에 있다. F15-018의 단서가 붙는다 |
| F15-026 | 122 | 요구 분석과 flow-down에 formal method를 쓰는 것은 가장 엄격하고 가장 비싼 방법이다. 덜 엄격하고 싼 방법으로 checklist와 표준화된 구조적 접근을 든다. | "The most rigorous (and most expensive) method" | 같은 쪽의 등급: cost LOW to HIGH (Formal Methods) |
| F15-027 | 127 | formal method의 가장 성공적인 응용 가운데 하나가 formal specification이다. formal verification을 하지 않아도 명세를 만드는 행위가 오류를 자주 잡는다. 모호함, 빠뜨림, 문서화되지 않은 가정, 충돌하는 요구, 논리 오류를 드러낸다. | "Among the most successful applications of Formal Methods is Formal Specification." | 등급: benefit HIGH, cost MODERATE to HIGH |
| F15-028 | 128 | model checking은 finite-state 시스템을 검증하는 formal method의 한 형태다. 자동 방법이며 도구로 SPIN과 SMV를 든다. 문서는 FM 전체와 따로 쓰이게 되었다고 적는다. | "Model checking is a form of Formal Methods that verifies finite-state systems." | 등급: benefit HIGH, cost MODERATE |
| F15-029 | 128 | model checking은 상시 환경과 상호작용하는 reactive, embedded 시스템의 검증을 겨냥한다. 기존 소프트웨어 과정의 어느 단계에나 큰 혼란 없이 비교적 쉽게 적용할 수 있다고 한다. 유한 상태 밖의 일부 시스템과 real-time 시스템으로도 확장되었다. | "reactive, embedded systems" | "relatively easily"라는 문서의 말이다 |
| F15-030 | 128 | model checking이 검증하는 성질: 단순한 것은 reachability와 lack-of-deadlock, 복잡한 것은 safety (나쁜 일은 일어나지 않는다)와 liveness (좋은 일은 결국 일어난다). | "safety (nothing bad ever happens)" | |
| F15-031 | 128 | model checking의 과정: 시스템을 상태 기반의 형식으로 기술하고 (도구마다 언어가 다르다), 성질을 temporal logic으로 쓰고, 알고리즘이 모델을 훑으며 성질이 성립하는지 확인한다. 매우 큰 state space도 흔히 몇 분 안에 훑을 수 있다고 한다. | "can often be traversed in minutes" | "Very large state-spaces can often be traversed in minutes"라는 낙관적인 서술이다. 한계는 F15-034 |
| F15-032 | 128 | SPIN은 비동기 (asynchronous) 시스템의 검증에 특화된 on-the-fly model checker다. deadlock, busy cycle, assertion 위반, race condition을 찾는다. | "It will find deadlocks, busy cycles, conditions that violate assertions, and" | 인용 뒤에 "race conditions"가 이어진다 (129쪽 첫 줄) |
| F15-033 | 129 | SMV는 CTL로 성질을 쓰고, 유한 상태 기계를 기술하는 입력 언어를 가진다. 그래서 언어의 자료형이 Boolean, scalar, 고정 배열 같은 유한한 것뿐이다. | "the only data types in the language are finite ones" | |
| F15-034 | 129 | model checking의 주된 어려움은 state explosion이다. 모델의 상태 수가 너무 커서 model checker가 쓸 수 있는 메모리나 시간을 넘기기 쉽다. | "The main challenge in model checking is the state explosion problem" | |
| F15-035 | 129 | state explosion에 대응하는 기법: 상태 공간의 일부만 만들되 관심 있는 성질은 검사할 수 있게 하는 partial-order 기법과 abstraction 기법, 상태를 암묵적으로 표현하는 symbolic 기법 (BDD), 일부만 메모리에 두는 on-the-fly 기법. | "abstraction techniques" | BDD와 on-the-fly 서술은 130쪽에 이어진다. "Several techniques are used to cope with this problem."이 같은 쪽에 있다 |
| F15-036 | 130 | 동적으로 할당한 자료 구조는 배열과 문자열이 물리적 끝을 넘지 않는지 정적 분석으로 검증하기 어려운 경우가 많다. | "they often cannot be statically analyzed" | 6.6.6절의 동적 메모리 서술. 정적 분석이 놓치는 쪽의 한 예다 |
| F15-037 | 132 | SFTA와 SFMEA를 함께 쓰면 가능한 고장 모드를 찾는 데 매우 좋지만 시간이 많이 들어 비싸다. 작은 프로젝트는 보통 하나만 한다. | "On smaller projects, usually only one analysis is performed." | 같은 쪽: 분석의 질은 분석가의 경험에 달려 있다. SFTA는 top down, SFMEA는 bottom up이다 |
| F15-038 | 155 | 최종 코드에 계획한 분석은 모두 상세 설계의 코드와 비슷한 산출물에서 먼저 한 번 돌려 볼 것을 권한다. 오류를 최종 코드에 가기 전에 더 싸게 잡는다. | "undergo their first iteration" | 7.5절 앞부분. "it is recommended"라는 권고의 세기다 |
| F15-039 | 156 | 안전 필수 부품으로 찾은 것은 위험에 따라 순위를 매긴다. 모든 부품이 같은 깊이의 분석을 받을 필요는 없다. 요인으로 시스템 위험 지수, 소프트웨어가 위험을 제어하는 정도, 중복 제어의 양, 부품의 복잡도, 시간 임계성을 든다. | "nor do all warrant the same depth of analysis" | 7.5.1.2절 |
| F15-040 | 156 | 위험에 맞춰 inspection의 횟수를 조정한다: 위험이 큰 부품은 설계와 코딩의 모든 단계에서 inspection하고, 작은 부품은 코드 inspection만 할 수 있다. | "High risk components may be inspected at all stages of design and coding." | 같은 쪽: 안전 필수 설계나 코드의 Formal Inspection은 해야 한다 (should be performed) |
| F15-041 | 157 | 설계 안전 분석에서 설계 review를 하며 "what if" 질문을 다양한 검토자에게 던지면 소프트웨어의 약점이나 강점을 찾을 수 있다. Formal Inspection이나 design review로 이 과정을 보완한다. | "asking the "what if" questions with a diverse group of reviewers" | 같은 쪽의 설계 review는 설계가 요구를 만족하는지 확인하는 것이다 (PDR, CDR) |
| F15-042 | 158 | prototype이나 simulation으로 시간 제약 같은 것을 일찍 확인할 수 있다. 그 시험 결과는 prototype이나 simulation에 대한 것이므로 실제 소프트웨어와 다를 수 있다. | "The behavior of the real software" | 인용 뒤에 "may differ"가 이어진다 |
| F15-043 | 159 | 설계 단계의 Formal Inspection은 안전 필수 부품의 모듈화와 독립성에 초점을 둔다. 안전 필수 설계만 inspection하기로 선택할 수 있으나, 그러면 비필수 코드와 필수 코드의 뜻밖의 상호작용을 놓칠 수 있다. | "unexpected interactions between non-critical and critical code may not be detected" | 등급: benefit HIGH, cost LOW to MODERATE |
| F15-044 | 160 | Design Logic Analysis (DLA)의 가장 엄격한 형태는 formal method를 쓰는 것이다. 비용이 높고 대상의 비용이나 위험이 낮으면 FM이 적절하지 않으므로 더 단순한 DLA를 쓴다. 가장 덜 형식적인 것은 사람이 작은 분량의 중요한 산출물을 눈으로 따라가는 것이다. | "fully rigorous DLA uses the application of Formal Methods" | 같은 쪽: model checking은 설계가 요구 성질을 여전히 만족하는지 검증하는 데 쓸 수 있다 (7.5.5의 끝) |
| F15-045 | 160 | 상용 자동 소스 분석기는 이 활동을 보완하는 데 쓸 수 있으나, 결함과 오류가 있을 수 있으므로 절대적으로 믿어서는 안 된다 (should not). | "should not be relied upon absolutely" | COTS 도구 일반의 걱정이라고 문서가 덧붙인다 |
| F15-046 | 171 | 단위 시험에서 찾은 오류의 목록을 code review checklist에 되먹이면, 다음에는 시험이 아니라 review 단계에서 더 일찍 찾는다. | "Feed those errors back into the code review checklist" | 8.4.2절 |
| F15-047 | 172 | 안전 필수 코드를 refactoring하면 원래 코드에 한 inspection이 무효가 될 수 있다. refactoring을 하면 re-inspection이 필요하고, 가능하면 처음의 Formal Inspection 팀이 하는 것이 좋다. | "a re-inspection of the code is necessary" | "Refactoring safety-critical units should be avoided."도 같은 쪽 |
| F15-048 | 172 | static slicing은 소스 코드에서 관심 변수에 영향을 줄 수 있는 모든 문장을 보인다. dynamic slicing은 실행 중에 실제로 영향을 준 문장만 보인다. 안전 필수 data의 계통을 확인하고 비필수 코드가 상호작용하지 않음을 확인하는 데 쓸 수 있다. | "Static slicing shows every statement that may impact the variable of interest." | 등급: benefit MEDIUM, cost MODERATE |
| F15-049 | 173 | Code Logic Analysis는 사람이 하면 지루하고 자동 도구가 드물다. 설계에서 코드로 가는 구현 오류는 가능하지만 주된 문제의 원천은 아니며, Formal Inspection 같은 다른 방법이 같은 오류를 대개 많이 찾는다. | "usually find many of the same errors as this analysis" | 등급: benefit LOW, cost HIGH |
| F15-050 | 174 | 논리상 실행될 수 없는 코드 (unused code)는 큰 구현 오류의 징후일 수 있고, 복잡도와 메모리를 늘리고, 하드웨어 고장이나 SEU로 잘못 실행되면 위험할 수 있다. 이것을 찾는 특별한 분석 기법은 없다. | "There is no particular analysis technique for identifying unused code." | 다른 분석 중에 찾는다: Formal Inspection, Code Logic Analysis, coverage 도구를 쓴 단위 시험 |
| F15-051 | 176 | 안전 필수 소프트웨어 부품에는 Formal Inspection을 최소한으로 해야 하고 (should), 복잡하거나 중요한 다른 부품에도 고려한다. 코드 품질을 평가하는 최선의 방법론 가운데 하나라고 한다. | "Formal Inspections are one of the best methodologies" | 176쪽에서 시작해 177쪽의 benefit HIGH, cost MODERATE로 끝난다 |
| F15-052 | 176 | 코드 inspection의 checklist에 넣을 것: 검토할 부품의 요구와 설계 정보, 코딩 표준의 중요한 부분, 언어와 무관한 프로그래밍 오류, 언어별 프로그래밍 오류. | "language-independent programming errors" | 부록 H에 점검표 예가 있다고 177쪽이 적는다 |
| F15-053 | 177 | 코드가 생기면 복잡도 지표를 다시 계산한다. 복잡한 코드는 사람이 평가해야 한다. case 문처럼 지표가 복잡하다고 표시하는 구조가 실제로는 이해하기를 돕는 경우가 있다. | "may be flagged as complicated" | 지표의 false positive에 해당하는 서술이다 (문서는 이 말을 쓰지 않는다) |
| F15-054 | 236 | lint는 컴파일러가 놓칠 수 있는 코드의 문제를 찾는다. 모든 지적이 진짜 문제는 아니지만 평가해야 한다. "non standard"라면 오류로 취급하라고 한다. | "finds problems in the code that compilers might miss" | 11.2절의 도구 목록 |
| F15-055 | 312 | 용어집은 verification의 정의를 다섯 가지로 적는다. (1) 개발 단계의 산출물이 앞 단계 요구를 만족하는지 판정하는 과정, (2) 프로그램 정확성의 formal proof, (3) review, inspect, test, check, audit 등의 행위 등이다. | "Formal proof of program correctness." | 한 낱말에 (2)처럼 증명의 뜻이 들어 있다. 인용은 (2)번 항목 |
| F15-056 | 312 | 용어집은 validation의 정의를 네 가지로 적는다. (2) 개발의 끝에 소프트웨어가 요구에 맞는지 평가하는 과정, (4) 시스템이 올바르게 동작하고 올바른 기능을 수행하는지 판정하는 과정 등이다. | "The process of determining whether the system operates correctly" | 인용은 (4)번 항목. (1)번은 안전 요구가 완전하고 추적 가능한지 corroborate하는 평가 기법이라고 적는다 |

## 2. nasa-toyota-ua-report (NASA NESC, Technical Assessment Report: Toyota Unintended Acceleration Investigation, 2011. PDF 쪽 = 인쇄 쪽)

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| F15-057 | 148 | 조사 대상은 MY 2005 Camry L4의 ECM 소프트웨어다. 조사는 2010년 4월 중순부터 8월 중순까지였다. 잠재적 소프트웨어 원인을 코딩 결함, 알고리즘 결함, task 간섭, 부족한 fault protection의 네 부류로 나눴다. | "The study focused on the MY 2005 Camry L4" | 네 번째 부류는 149쪽에 있다 |
| F15-058 | 148 | 코딩 표준은 구현 기법을 제약하고 code inspection을 돕는 식으로 결함의 유입을 줄일 수 있다. 이 조사에서는 도구를 써서 소스를 분석하고 코딩 표준에 견줘 code inspection을 자동화했다. | "tools were used to automate the code inspections" | |
| F15-059 | 148 | 알고리즘 결함 (설계 논리)은 기능 모델을 만들어 분석했다. 모델은 팀 전체에 시스템 동작을 전달했고, 수동 분석과 자동 분석이 관심 영역을 찾고 조사의 우선순위를 정했다. | "produced areas of interest and prioritized the study efforts" | |
| F15-060 | 149 | 소스 코드의 정적 분석은 가능한 코딩 결함과 취약점을 찾는 데 먼저 집중했다. | "to find possible coding defects and potential" | 인용은 "source code analysis of the ECM source code to find possible coding defects and potential"의 일부다. 줄 앞부분은 "a thorough static" |
| F15-061 | 149 | Coverity는 큰 코드 기반에서 흔한 코딩 결함과 의심스러운 패턴을 비교적 짧은 시간에 찾는 데 뛰어나다. 사용자 정의 checker로 추가 코딩 규칙도 검사할 수 있다. 경고 수를 최소로 줄이려고 가장 중요한 문제를 골라내는 세심한 filtering을 한다. | "taking a relatively short amount of time" | 이 조사에서는 소수의 Extend checker를 썼다 |
| F15-062 | 149 | CodeSonar는 다른 기술로 상세한 절차 간 (inter-procedural) 분석을 한다. 비슷한 도구보다 완료에 보통 더 오래 걸리지만 더 깊은 경로 분석이 필요한 미묘한 결함을 찾을 수 있다. 이 조사에서는 JPL 코딩 표준의 checker를 더한 판을 썼다. | "typically takes longer to complete than comparable tools" | |
| F15-063 | 149 | Uno는 Bell Labs에서 나온 연구용 도구로, 더 단순하고 빠른 분석으로 초기화하지 않은 변수의 사용, nil pointer 역참조, 배열 범위 밖 첨자, 세 가지 흔한 결함을 주로 잡는다. | "the use of uninitialized variables" | 사용자 정의 검사로 확장할 수 있다 |
| F15-064 | 150 | SPIN은 분산 소프트웨어 시스템의 formal verification을 위한 오픈 소스 도구다. 시스템의 상위 수준 설계 모델의 철저한 (exhaustive) 검증과, 다중 task나 다중 thread 시스템의 구현 수준 코드의 상세한 탐색에 둘 다 쓸 수 있다. | "exhaustive verification of high level design models of a system" | 1991년부터 공개되었고 2002년 4월에 ACM System Software Award를 받았다고 적는다 |
| F15-065 | 150 | 보고서는 SPIN을 이 분야의 선도적인 도구라고 하며, 그 도구를 이 보고서의 저자 가운데 한 사람이 개발했다고 적는다. | "which was developed by one of the authors of this report" | 도구 개발자가 보고서 저자였다는 사실이다 |
| F15-066 | 150 | Swarm은 SPIN의 전처리 시스템이다. 큰 compute cloud나 한 서버의 모든 CPU 코어를 써서, 작은 검증 작업을 많이 내어 함께 탐색 공간을 덮는 방식으로 크고 복잡한 소프트웨어의 종합 분석을 하게 한다. | "swarm of small verification jobs" | |
| F15-067 | 150 | MATLAB 모델은 TMC 문서와 기술자와의 대화로 시작해 소스 분석으로 정확도를 높이고, Camry simulator와 실제 차량의 시험으로 정확도를 확인했다. 가능한 한 실제 소스 코드를 모델에 넣었다. | "high-fidelity models of the software functions and behaviors" | 모델은 소스를 노출하지 않고 소프트웨어를 팀에 전달하는 데도 쓰였다고 151쪽이 적는다 |
| F15-068 | 151 | 분석 도구 목록: MATLAB, Simulink, Stateflow, SystemTest (Simulink 모델의 black box 자동 시험), aiT. aiT는 실시간 시스템의 task의 최악 실행 시간 (WCET)의 tight한 상한을 정적으로 계산하며 binary 실행 파일을 직접 분석한다. | "statically computes tight bounds for the worst-case execution time" | WCET 분석도 정적 분석의 한 종류로 쓰인 예다 |
| F15-069 | 151 | 관찰 O-6: Camry 소스 코드를 검사하는 데 특수한 코드 검사 도구와 수동 검사가 필요했다. TMC가 독자적으로 만든 코딩 표준을 쓰고, 업계 표준의 정적 분석 도구는 업계 표준의 코드 구현에 따라 자동 검사를 하기 때문이다. | "The TMC software development process uses a proprietary developed coding standard." | 설계 취약점의 결과는 아니라고 같은 항목이 적는다. 173쪽에도 같은 서술이 있다 |
| F15-070 | 152 | 조사의 결론 F-10: 정적 분석, logic model testing, recursion testing, 최악 실행 시간 분석을 포함한 소프트웨어 시험과 분석을 했다. 이 조사에서 쓴 도구로는 UA를 단독으로 일으키는 소프트웨어 결함을 찾지 못했다. | "With the tools utilized during the course of this study" | 문서의 결론은 쓴 도구의 범위로 한정된다. 인용 뒤에 "software defects that unilaterally cause a UA were not found"가 이어진다 |

## 3. misra-compliance-2020 (MISRA, MISRA Compliance:2020, 2020. PDF 쪽 = 인쇄 쪽 + 8)

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| F15-071 | 13 | 위반을 모두 찾고 false positive도 없는 이상적인 정적 분석 도구는 만들 수 없고 앞으로도 만들 수 없다. 그래서 가능한 한 많은 위반을 찾으면서 false positive를 줄이는 정도가 도구 선택의 요소다. | "it is not, and never will be, possible to produce a static" | 근거는 3.5절의 decidability다 |
| F15-072 | 13 | 도구의 실행 시간은 초에서 일 단위까지 이른다. 대체로 시간이 짧은 도구가 false positive를 낼 가능성이 더 높다. 분석 시간과 정밀도의 균형을 도구 선택에서 고려해야 한다. | "tools that consume less time are more likely to produce false positives" | "Broadly speaking"이라는 단서가 붙은 서술이다 |
| F15-073 | 13 | 도구마다 강조점이 다르다. 범용 도구도 있고 일부 문제의 철저한 분석에 집중한 도구도 있다. 점검할 문제의 범위를 넓히려면 도구를 둘 이상 쓸 필요가 있을 수 있다. | "it might be necessary to use more than one tool" | |
| F15-074 | 13 | 컴파일러와 정적 분석 도구는 출력을 믿고 쓰는 "trusted" 과정이다. 그 신뢰가 틀리지 않도록 조치해야 한다. 이상적으로는 도구 공급자가 검증 시험을 한다. | "this trust is not misplaced" | 인용은 "Measures must therefore be taken to ensure that this trust is not misplaced."의 일부다 |
| F15-075 | 13 | 공급자가 그 수준의 보증을 주지 못하면 도구의 품질을 확인할 책임은 개발자에게 있다. 방법: 문서화된 검증 시험, 공급자의 개발 과정 평가, 도구의 성능 이력 검토. | "Perform some form of documented validation testing;" | 컴파일러에 대해서는 형식적인 검증 제도가 발행 시점에 없다고 같은 쪽이 적는다 |
| F15-076 | 13 | 정적 분석 도구의 검증 시험은 guideline 하나씩의 위반을 담은 코드 파일을 써서, 도구가 그 위반을 찾는지 보는 것이다. 이런 시험은 한정적이지만 기본 성능을 보여 준다. | "each containing a violation of one guideline" | 인용 앞부분은 "a set of code files should be written,"다 |
| F15-077 | 14 | IEC 61508, ISO 26262, DO-178은 어떤 상황에서 컴파일러와 정적 분석 도구의 qualification을 요구한다. | "qualification of compilers and static analysis tools in some situations" | 쪽 위의 Note. 요구의 조건은 이 문서에 없다 |
| F15-078 | 15 | 정적 분석 도구는 보통 범용이고 컴파일러는 특정 프로세서용이다. 그래서 정적 분석 도구는 컴파일러의 구현 결정에 맞춰 설정해야 한다. 예로 정수 형의 크기를 든다. | "it is therefore important to configure each static analysis tool to" | 인용은 "It is therefore important to configure each static analysis tool to"의 일부다 |
| F15-079 | 16 | 정적 분석이 검사하는 것은 rule이다. rule은 코드만으로 판정되는 guideline이고, directive는 과정이나 문서나 기능 요구를 가리키므로 도구가 돕기만 할 수 있다. directive에서는 도구마다 비준수의 해석이 달라질 수 있다. | "different tools will therefore sometimes place" | 인용 뒤에 "different interpretations"가 이어진다 |
| F15-080 | 16 | rule의 분석 범위는 단일 translation unit이거나 시스템이다. 어떤 rule은 시스템 전체의 소스 코드를 분석해야 완전히 검사할 수 있다. 예: "An identifier with external linkage shall have exactly one external definition". | "Some rules can only be fully checked by analysing the source code in the entire system." | 단일 TU의 예: "Every switch statement shall have a default value" |
| F15-081 | 16 | guideline 대부분은 도구나 컴파일러로 검사하는 것이 가장 쉽고 믿을 만하고 비용 효율이 좋다. 도구가 완전히 검사하지 못하는 guideline에는 수동 review가 필요할 수 있다. | "A manual review process may be required where a guideline cannot be completely checked by a tool." | |
| F15-082 | 17 | guideline enforcement plan에 기록할 것: 도구의 version, 도구가 쓴 data와 설정 파일, 호출 option, 도구가 그 guideline의 위반을 찾을 수 있다는 증거, 수동 과정의 상세. | "Evidence proving that the tool is able to detect violations" | 요청이 있으면 acquirer에게 제공해야 한다 (shall) |
| F15-083 | 17 | 검사 과정이 내는 메시지는 네 부류다: (1) 위반의 올바른 진단, (2) 위반 가능성의 진단, (3) 위반의 잘못된 진단, (4) 위반은 아니지만 실제 문제인 것의 진단. | "Diagnosis of a genuine issue that is not a violation." | 부류 (1)은 코드를 고치는 것이 바람직한 해결이다 |
| F15-084 | 18 | (2), (3), (4) 부류의 메시지는 조사하고, 코드를 고치지 않으면 조사의 기록을 남긴다. (2)는 코드가 왜 준수인지, (3)은 도구의 진단이 왜 틀렸는지 (가능하면 도구 개발자의 동의), (4)는 왜 무시해도 되는지 적는다. 기록은 자격 있는 기술 책임자가 review하고 승인한다. | "reviewed and approved by an appropriately qualified" | 인용 뒤에 "technical authority"가 이어진다 |
| F15-085 | 18 | decidable rule은 준수 질문에 항상 yes나 no로 답할 수 있다. 도구가 맞게 설정되고 결함이 없으면 준수를 확실히 검증할 수 있다. | "it is always possible to verify compliance with certainty" | |
| F15-086 | 18 | undecidable rule은 도구가 모든 경우에 yes나 no로 답한다고 보장할 수 없는 rule이다. yes나 no가 가능한 경우도 있으나 "Possibly" (준수가 불확실)만 가능한 경우도 있다. | "Possibly" | 인용은 원문의 `"Possibly"`다 (8자 이상) |
| F15-087 | 18 | 위반 검출이 run-time 성질에 달려 있으면 undecidable일 가능성이 높다. 예로 객체가 가진 값, 제어가 프로그램의 특정 지점에 이르는지를 든다. | "Whether control reaches a particular point in the program." | 문서는 계산 이론의 설명이 범위 밖이라고 적는다 |
| F15-088 | 18 | 대부분의 undecidable rule은 시스템 전체로 검사해야 한다. 예: 자동 저장 기간의 객체를 값이 정해지기 전에 읽지 않는다는 rule에서, 지역 변수의 주소를 다른 translation unit의 함수에 넘기면 그 함수의 동작을 모르고는 준수를 검증할 수 없다. | "f might modify the object pointed to by its parameter" | 예제 코드의 주석이다. 결론은 19쪽 첫 문장에 있다 |
| F15-089 | 19 | undecidable rule에는 아무리 정교한 도구도 모든 경우에 확정적으로 답한다고 보장할 수 없다. 진단이 없는 것이 곧 준수 (Yes)를 뜻하지는 않는다. | "the absence of a diagnostic does not necessarily imply a response" | 인용 뒤에 "of Yes"가 이어진다. 놓침 (false negative)에 해당하는 서술이다 (문서는 이 부분에서 이 말을 쓰지 않는다) |
| F15-090 | 19 | 정적 분석만으로 undecidable rule의 준수를 검증하기는 흔히 불가능하다. 이론상 증명이 가능한 경우에도 분석이 매우 복잡하거나 감당할 수 없는 계산 자원이 필요할 수 있다. | "static analysis alone is often impossible" | |
| F15-091 | 19 | 도구마다 undecidable rule의 위반을 진단하는 능력이 크게 다르다. 중요한 것은 확정 위반과 가능한 위반을 구별해 보고하며 false positive와 false negative를 모두 피하는 정도다. | "avoid both false positives and false negatives" | |
| F15-092 | 19 | undecidable rule의 준수를 review하는 과정에 특별히 주의해야 한다. 도구가 가능한 위반을 믿을 만하게 알려 준다면, 보수적이고 방어적인 코딩 기법으로 그 불확실성을 없앨 수 있다. | "conservative and defensive coding techniques" | 정적 분석이 일반적으로는 준수를 보증하지 못해도 어떤 코드에 대해서는 보증할 수 있다고 같은 쪽이 적는다 |

## 4. koopman-toyota-ua (Philip Koopman, Toyota Unintended Acceleration slides, 2014. PDF 쪽 = slide 번호)

원고 쪽 전문가의 발표 자료다. 숫자는 NASA 보고서의 부록 A (받지 못했음)를 인용한 것이다.

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| F15-093 | 35 | Toyota의 infotainment 소프트웨어 자료는 코딩 규칙 위반 30개마다 "major bug" 하나가 있을 것으로 기대한다고 한다 (Kawana 2004 인용). | "one "major bug" for every 30 coding rule violations" | 계획표의 쪽 밖이다. 출처는 슬라이드가 인용한 문헌 하나다 |
| F15-094 | 36 | Toyota는 자사 코딩 규칙이 MISRA C와 50% 겹친다고 주장했으나, Toyota의 코딩 규칙에 든 MISRA C 규칙은 11개뿐이라고 슬라이드가 적는다. | "But only 11 MISRA C rules out of MISRA C in the Toyota coding rules" | |
| F15-095 | 36 | Toyota가 자기 규칙을 항상 지키지는 않았다. 예: "switch" 343개 가운데 105개에 "default"가 없었다. | "105 out of 343" | 인용은 슬라이드의 `105 out of 343 "switch" keywords without "default"`의 일부다 (원문 쪽: NASA 부록 A 21-23쪽) |
| F15-096 | 36 | NASA의 도구가 쉽게 검사할 수 있는 MISRA C 규칙 35개 가운데 14개가 위반되었고 위반은 7,134건이었다. 대부분 매크로 사용과 #undef 사용이다. | "14 of 35 rules violated; 7,134 violations" | |
| F15-097 | 36 | Mike Barr의 팀은 MISRA C 위반 80,000건을 찾았다고 슬라이드가 적는다 (재판 증언 인용). | "Mike Barr's team found 80,000 violations of MISRA C" | 두 수 (7,134건과 80,000건)는 검사한 규칙의 수가 달라 같은 척도가 아니라고 읽을 수 있으나, 슬라이드는 그 점을 적지 않는다 |
| F15-098 | 37 | NASA는 여러 정적 분석 도구를 썼다. Toyota는 이 도구들에서 경고가 없는 상태를 주장하지 않았으나 결과는 참고가 된다고 슬라이드가 적는다. | "Toyota did not claim warning-free on these, but results informative" | |
| F15-099 | 37 | Coverity의 결과로 슬라이드가 든 것: 선언했으나 참조하지 않음 97건, 재귀를 포함함 5건. | "97 - declared but not referenced" | 건수만 있다. 각 경고가 실제 결함인지는 슬라이드가 적지 않는다 |
| F15-100 | 37 | CodeSonar의 결과로 든 것: 전역 변수를 다른 형으로 선언 2272건, cast가 값을 바꿈 333건, 조건에 부작용 99건, 전역의 다중 선언 64건, 초기화되지 않은 변수 22건. | "2272 - global variable declared with different types" | 도구마다 경고의 종류가 다르다는 점이 보인다 |
| F15-101 | 37 | Uno의 결과로 든 것: 초기화되지 않았을 수 있는 변수 89건, 16 byte 배열을 17 byte로 초기화 2건. | "Array of 16 bytes initialized with 17 bytes" | |
| F15-102 | 38 | Toyota ETCS 코드에는 McCabe cyclomatic complexity가 50을 넘는 함수가 67개 있었다. 슬라이드는 50을 넘으면 "untestable"로 본다고 적는다. | "67 functions with complexity over 50" | 계획표의 쪽 밖이다. 복잡도 지표의 사례로 덧붙였다 |

## 5. faa-ac-20-115d (FAA, Advisory Circular 20-115D, Airborne Software Development Assurance Using EUROCAE ED-12( ) and RTCA DO-178( ), 2017. PDF 쪽 = 인쇄 쪽)

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| F15-103 | 1 | AC는 DO-178C 외에 ED-216/DO-333 Formal Methods Supplement를 인정하는 문서로 나열한다. 같은 쪽에 DO-330 (tool qualification), DO-331 (model-based development and verification), DO-332 (object-oriented)도 나열한다. | "Formal Methods Supplement to ED-12C and ED-109A" | DO-333의 내용은 이 AC에 없다 |
| F15-104 | 1 | AC는 규정 준수를 보이는 수용 가능한 수단 중 하나를 설명하지만 유일한 수단은 아니다. 필수는 아니며 규정이 아니다. 그러나 그 수단을 쓰면 해당하는 모든 점에서 따라야 한다. | "acceptable means, but not the only means" | |
| F15-105 | 4 | 8.a: supplement가 다루는 소프트웨어 개발 기법을 쓰면 그 supplement의 지침을 적용해야 한다 (should). 여러 기법을 함께 쓰면 supplement가 둘 이상 적용된다. supplement는 단독 문서로 쓸 수 없다. | "supplements ED-218/DO-331, ED-217/DO-332, and ED-216/DO-333 when incorporating the" | 인용 앞은 "You should apply the guidance of"다 |
| F15-106 | 4 | supplement를 쓸 때 PSAC에는 DO-178C와 supplement를 어떻게 함께 적용하는지, 어느 목적이 어느 소프트웨어 부품에 적용되며 계획한 활동이 모든 해당 목적을 어떻게 만족하는지 기술해야 한다 (should). | "How you will apply ED-12C/DO-178C and the supplement(s) together." | |
| F15-107 | 5 | 모델을 소프트웨어 개발의 기초로 쓸 때 (DO-331), simulation만으로, 또는 review와 분석과 함께 만족하려는 목적을 밝히고, 각 목적에 대해 simulation 활동이 그 review와 분석의 목적을 어떻게 완전히 만족하는지 상세히 정당화해야 한다 (should). | "justify in detail, how the simulation activity" | 모델 기반 개발의 simulation에 대한 서술이며 formal method의 것이 아니다 |

## 6. nasa-std-8739-8b (NASA, NASA-STD-8739.8B Software Assurance and Software Safety Standard, 2022. PDF 쪽 = 인쇄 쪽, 각 쪽 아래에 "N of 65")

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| F15-108 | 13 | 용어 절: software validation은 제품이 의도한 사용을 충족한다는 확인이고 "you built the right thing"이다. software verification은 제품이 지정된 요구를 올바르게 반영한다는 확인이고 "you built it right"다 (출처: IEEE 1012). | "verification ensures that "you built it right."" | validation의 인용: `validation ensures that "you built the right thing."` |
| F15-109 | 49 | IV&V 제공자는 verification과 validation 두 활동을 하며, 각 활동이 시스템과 소프트웨어에 대해 다른 관점을 준다. verification은 요구에서 설계, 코드, 시험까지 걸쳐 제품이 build-to 요구와 설계 명세에 맞는지 객관적 증거를 평가한다. validation은 산출물의 내용이 시스템에 맞는 내용인지, 올바른 문제를 푸는지에 대한 객관적 증거를 만든다. | "Each of the activities provides a different perspective on the" | 4.4.1.4항. 인용 뒤에 "system/software"가 이어진다 |
| F15-110 | 36 | SWE-135: 프로젝트 관리자는 개발과 시험 단계에서 정적 분석 도구로 코드를 분석해야 한다 (shall). 최소한 결함, 소프트웨어 보안, 코드 coverage, 복잡도를 찾는다. 소프트웨어 보증 쪽은 도구가 보안과 코딩 오류를 찾는 checker와 함께 쓰이는지, 프로젝트가 그 결과를 다루는지 확인한다. | "The project manager shall use static analysis" | 요구 번호 4.4.4 |
| F15-111 | 44 | SWE-087: 프로젝트 관리자는 요구, 계획, 설계 항목, 코드, 시험 절차에 대해 peer review나 inspection을 하고 보고해야 한다 (shall). 코드 peer review에서는 안전 필수 부품의 cyclomatic complexity가 15 이하임을 확인하거나, 15를 넘으면 위험을 만든다. | "cyclomatic complexity value of 15 or lower" | 요구 번호 5.3.2. 인용은 오른쪽 열 (소프트웨어 보증 과제)의 글이다 |
| F15-112 | 32 | SWE-185: 프로젝트 관리자는 정적 분석 도구의 결과로 코드가 프로젝트의 secure coding 표준을 만족하는지 verify해야 한다 (shall). 소프트웨어 보증 쪽은 엔지니어링 data를 분석하거나 독립적인 정적 코드 분석을 한다. | "The project manager shall verify that the software" | 요구 번호 3.11.7. 인용 뒤에 "code meets the project's secure coding standard"가 이어진다 |

## 문서에서 찾지 못한 것

- abstract interpretation: 받은 문서에 없다. 계획이 "도구가 무엇을 보장하는가까지만" 쓰라고 한 부분은 MISRA Compliance의 decidability 서술 (F15-085 - F15-092)이 가장 가깝다. sound한 분석, 과대 근사 같은 말은 어느 문서에도 없다. (기억) 정의와 sound/complete의 구별은 외부 자료가 필요하다.
- CBMC와 bounded model checking: 없다. 계획의 "CBMC로 감시 함수 1개를 증명"은 문서 근거가 없다. 받은 문서의 model checker는 SPIN, SMV (NASA 지침서 6.6.5)이고, 실제 코드에 쓴 사례는 Toyota 보고서의 SPIN뿐이다 (F15-064 - F15-066).
- 정리 증명 (theorem proving)의 설명: NASA 지침서 69쪽은 theorem prover의 이름 목록만 준다. 방법과 비용은 없다.
- contract 기반 검증 (Design by Contract, Frama-C 등): 없다.
- SPIN을 Toyota 코드에 적용한 결과와 한계: 이 PDF (본문 177쪽)에는 도구 소개 (150쪽)와 결론 F-10 (152쪽)뿐이다. 모델링한 부분, 찾은 것, 상태 수의 한계는 부록 A에 있고 받지 못했다. 본문 쪽에서 SPIN을 어디에 썼는지의 서술이 150쪽 밖에 없다.
- 정적 분석 경고의 true positive 비율: Koopman slide 37은 건수만 적고 어느 것이 실제 결함인지 적지 않는다. NASA 보고서 본문도 건수나 판정을 적지 않는다.
- 정적 분석과 review의 결함 발견율, 비용 효과의 정량 자료: 받은 문서에 없다. NASA 지침서의 benefit와 cost는 주관적 등급이다 (F15-018). Fagan inspection의 효과를 수치로 적은 곳은 없다.
- DO-333의 내용 (formal method의 정의, 목적, 검증의 soundness 요구): FAA AC는 인정한다는 사실만 적는다 (F15-103).
- ISO 26262-6, -8과 IEC 61508-3, -7이 등급별로 권장하는 verification 방법: 받지 못했다. 책의 방침상 표로 싣지 않는다. 등급에 따라 방법을 고르는 예로는 NASA 지침서의 effort 수준 (F15-001, F15-002, F15-005)과 부품별 inspection 조정 (F15-040)이 있다.
- "verification and validation"의 ISO 26262 용어 정의: 받지 못했다. 받은 문서의 정의는 NASA 두 문서뿐이다 (F15-003, F15-004, F15-055, F15-056, F15-108, F15-109).
- false positive와 false negative의 일반 정의: MISRA Compliance가 false positive를 12쪽에서 풀이하고 (이 파일 밖의 F13-014), 19쪽에서 false negative를 쓰되 따로 정의하지 않는다 (F15-091).

## 계획의 "근거 위치" 표와 어긋난 쪽

- `nasa-gb-8719-13`의 8.5.7 Formal Inspections of Source Code는 계획표대로 176쪽이다. 그러나 benefit와 cost 등급은 177쪽 맨 위에 있다. 계획표의 "118-119, 159, 176"은 맞다.
- 계획표의 "67-69, 127-130"은 모두 formal method 서술이 맞다. 6.6.5 Model Checking (128-130쪽)은 6.6.4 뒤의 별도 절이다. 계획표의 "6.6.4 Formal Methods - Specification Development"는 127쪽 하나이고, model checking 절 제목이 계획표에 없다.
- "104, 122-134, 155-162, 172-177"은 맞다. 그러나 이 쪽들의 내용은 도구가 아니라 분석 기법 (criticality, SFTA, SFMEA, DLA, interrupt 분석 등)이고, 정적 분석 도구 서술은 거의 없다. 정적 분석 도구는 236-237쪽 (lint, CASE 목록)에만 짧게 있다. 계획표에 이 쪽을 더하는 것이 좋다. 그리고 verification과 validation의 구별은 45쪽, 용어집은 312쪽이고 계획표에 없다. 등급별 선택의 표는 42-43쪽이다.
- `nasa-toyota-ua-report` 149-150쪽은 계획표의 서술대로다. 단, 6.7.3.4 MATLAB Models는 150-151쪽, 도구 표와 결과 O-6은 151쪽, 결론 F-10은 152쪽이다. SPIN 절은 도구 소개뿐이고 모델링의 내용이나 결과가 없다. 계획의 "실제 대형 코드에 적용한 ... SPIN model checking" 가운데 "적용한 결과"는 이 PDF에서 확인되지 않는다 (SPIN 도구 소개와 F-10뿐).
- `misra-compliance-2020`의 13-19쪽은 계획표대로다. 3.4절은 17-18쪽, 3.5절은 18-19쪽이다. 2.6.2-2.6.5는 12-15쪽에 걸친다.
- `koopman-toyota-ua`의 slides 36-37은 "정적 분석 경고 수의 해석"이라고 계획표가 적었으나, 슬라이드는 경고의 건수를 나열할 뿐 해석 (진짜 결함의 수나 우선순위)을 담지 않는다. 36쪽은 MISRA C 위반 건수, 37쪽은 도구별 경고 건수다. 해석에 해당하는 문장은 37쪽의 "results informative" 하나다 (F15-098).
- `faa-ac-20-115d` 1쪽, 4-5쪽은 계획표대로다. 8.a는 4쪽에 있다.
