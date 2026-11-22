# 8장 근거 문서에서 뽑은 사실 (읽기 기록)

대상: 8장 "Safety analysis 기법" (plans/ch08-safety-analysis.md). 읽은 날: 2026-11-23.

- 쪽 칸은 PDF 파일의 몇 번째 쪽이다. 문서에 인쇄된 쪽 번호가 다르면 절 머리에 차이를 적는다.
- 인용은 줄바꿈을 합치고 따옴표와 줄표를 ASCII로 바꿨다. 그 밖에는 원문 그대로다.
- 이 장의 규격 문서 (ISO 26262, IEC 61508)는 받지 못했다. ISO 26262의 용어는 2차 자료가 적은 대로만 옮겼다.
- `(기억)`은 문서에서 확인하지 못한 내용이다. 원고의 근거로 쓰지 않는다. 이 파일에는 없다.
- 원고에 쓰기 전에 그 쪽을 직접 열어 확인한다 (RULES.md 5.2절).

## 1. nasa-fault-tree-handbook (NASA, Fault Tree Handbook with Aerospace Applications, Version 1.1, 2002. PDF 쪽 = 인쇄 쪽 + 13)

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| F08-001 | 15 | FTA는 시스템의 원치 않는 상태 (top event)를 먼저 정하고, 환경과 운영의 맥락에서 그것이 일어날 수 있는 현실적인 길을 찾는 기법이다. fault tree는 그 사건에 이르는 병렬/순차 결함 조합의 그림 모델이다. | "an undesired state of the system is specified" | 핸드북의 정의 |
| F08-002 | 15 | fault tree의 결함에는 하드웨어 고장, 사람의 오류, 소프트웨어 오류가 모두 들어갈 수 있다. | "hardware failures, human errors, software errors" | 소프트웨어를 기본 사건으로 넣는 것을 허용한다는 서술이다. 확률을 어떻게 얻는지는 이 쪽에 없다 |
| F08-003 | 15 | fault tree는 모든 고장의 모델이 아니다. top event 하나에 맞춘 것이며, 분석자가 현실적이라고 판단한 결함만 담는다. | "a fault tree is not a model of all possible system failures" | 완전성의 한계에 관한 핸드북의 서술 |
| F08-004 | 15 | fault tree 자체는 정성 모델이고, 정량 평가를 할 수 있을 뿐이다. | "It is a qualitative model that can be evaluated quantitatively" | 확률을 못 붙여도 구조 분석은 가능하다는 근거가 된다 |
| F08-005 | 16 | 정성 분석의 주된 결과는 minimal cut set (top event를 일으키는 기본 사건의 최소 조합)이다. 사건이 하나인 cut set은 그 하나만으로 top event를 일으키는 단일 고장이며, 개선 조치의 초점이다. | "A cut set is a combination of basic events that can cause the top event." | 단일 고장 서술은 같은 쪽: "These single failures are often weak links" |
| F08-006 | 16 | 같은 특성의 사건으로 이루어진 cut set은 implicit dependent failure, 곧 common cause에 약하다는 신호이며, 중복 (redundancy)을 무효로 만들 수 있다. 예는 같은 밸브들이 한 가지 제조 결함이나 환경 민감성으로 함께 고장나는 경우다. | "susceptibility to implicit dependent failure, or common cause, that can negate a redundancy" | 중복이 common cause에 약하다는 직접 근거 |
| F08-007 | 17 | 정량 평가는 cut set마다 확률을 구해 더하고, 큰 순서로 정렬해 지배적 cut set을 찾는다. importance로 조치의 우선순위를 정한다. | "Fault trees are typically quantified by calculating the probability of each minimal cut set" | |
| F08-008 | 24 | 연역 (deductive) 분석은 시스템이 특정 방식으로 고장났다고 가정하고, 어떤 시스템/부품의 행동이 그 고장에 기여하는지 거슬러 찾는다. FTA가 연역 기법이다. | "it is postulated that the system itself has failed in a certain way" | 핸드북은 이를 탐정의 추리에 비유한다 |
| F08-009 | 25 | 귀납 (inductive) 분석은 특정 결함이나 초기 사건을 가정하고 시스템에 미치는 영향을 따라간다. bottom-up 접근이라고도 부른다. FMEA와 parts count, event tree가 예로 나온다. | "Inductive approaches are also termed bottom-up approaches" | |
| F08-010 | 25 | 연역은 주어진 상태가 어떻게 일어나는지를 묻고, 귀납은 어떤 상태가 가능한지를 묻는다. 귀납은 사고 시나리오를 만들 때와 완전성을 확인할 때 쓴다. | "inductive methods can be applied to determine what system states (usually failed states) are possible" | |
| F08-011 | 26-27 | 핸드북의 FMEA 표는 부품, 고장 확률, 고장 모드, 모드별 비율, 시스템에 미치는 영향 (critical/non-critical)으로 이루어진다. 중복 증폭기 예에서 critical 모드만 더하면 2x10^-4, 모든 모드를 critical로 보는 parts count는 2x10^-3이다. | "the single failure causes system failure" | 숫자는 핸드북의 예시용 값이다 |
| F08-012 | 27 | FMEA는 영향이 non-critical인 부품 고장을 상당한 확신으로 가려내지만, 현실적으로 따질 수 있는 고장 모드의 수에 한계가 있다. 그래서 정하지 못한 모드와 불확실한 영향은 critical로 본다. | "the number of possible component failure modes that can realistically be considered is limited" | |
| F08-013 | 33 | FTA와 귀납 기법의 근본 차이는 분석의 방향이다. FTA는 원치 않는 사건에서 필요충분한 원인으로 거슬러 가고, 귀납은 시작 원인에서 결과로 따라간다. | "The basic difference between FTA and inductive methods is the direction of the analysis." | |
| F08-014 | 34 | 완전한 사고 시퀀스를 얻으려면 연역과 귀납을 모두 써야 한다. 연역은 원치 않는 사건에 분석을 집중시키고, 귀납은 분석이 모든 시나리오를 포괄하도록 돕는다. | "both deductive and inductive approaches must be employed to get a complete set of accident sequences" | 둘을 함께 쓰는 까닭의 직접 근거 |
| F08-015 | 33 | FTA만 한 것을 완전한 PRA의 대용으로 여기면 안 된다. | "performing an FTA alone should not be mistakenly perceived as an alternative to or substitute for a complete PRA" | 각주. PRA는 확률적 위험 평가 |
| F08-016 | 35 | FTA는 8단계로 한다: 목적, top event, 범위, 해상도 (resolution), 기본 규칙 (ground rules)을 정하고, tree를 만들고, 평가하고, 결과를 해석한다. | "Identify the objective for the FTA." | 앞 다섯 단계가 문제 설정이다 |
| F08-017 | 36 | 해상도는 보통 주요 부품 수준이다. 그러나 어떤 사건이 다른 사건과 독립임을 보일 수 없으면 (예: 구동 신호나 전원을 다른 시스템과 공유) 더 전개해야 한다. | "when an event cannot be shown to be independent of others in the analysis" | 독립성 주장과 FTA 깊이의 연결 |
| F08-018 | 45 | minimal cut set은 그 사건 가운데 하나라도 일어나지 않으면 top event가 일어나지 않는 최소 집합이다. 유한한 개수가 있고, top event가 일어나는 모든 서로 다른 길을 기본 사건으로 나타낸다. | "a smallest set of basic events, which if they all occur will result in the top event occurring" | 보수 개념은 path set (같은 쪽) |
| F08-019 | 67 | 핸드북은 FMEA 여러 개를 이어 붙여 fault tree를 만드는 것을 나쁜 관행이라고 못 박는다. FMEA는 정해진 논리 구조 없이 원인을 고르고 원인 사이의 관계를 보이지 않기 때문이다. | "This cannot be done and is bad practice." | 4.8절 |
| F08-020 | 67 | 반면 FMEA는 fault tree를 점검하는 데 쓸 수 있고, tree를 만들지 말지와 깊이를 정하는 첫 평가에도 쓸 수 있다. | "an FMEA can be used to check a fault tree" | 두 기법을 함께 쓰는 방법의 직접 근거 |
| F08-021 | 67 | 전원, 냉각 같은 지원 인터페이스를 보여야 하드웨어 배선이나 기능상의 의존이 드러난다. 사건 사이의 의존과 관계를 찾아낼 만큼은 tree를 깊게 만들어야 한다. | "developing a fault tree to the depth necessary to identify dependencies and relationships among events is essential" | 4.7절 |
| F08-022 | 70 | common cause failure (CCF)는 둘 이상의 부품이 동시에, 또는 짧은 간격으로 하나의 공통 원인 때문에 고장나는 것이다. "부품"은 밸브 같은 부품일 수도, 전원 같은 하위 시스템일 수도 있다. | "two or more component failures that occur at the same time or occur within a relatively short interval" | CCF의 정의로 쓸 수 있는 문장 |
| F08-023 | 70 | fault tree가 말하는 CCF는 명시적으로 모델링하지 않은 공통 원인이다. 전원이나 냉각처럼 tree에 이미 기능적 의존으로 그린 것은 포함하지 않는다. | "do not include a functional dependency of a component that is explicitly modeled" | |
| F08-024 | 71 | CCF를 무시하면 top event 확률을 크게 과소평가한다. CCF 예: 공통 설계/재료 결함, 공통 설치 오류, 공통 정비 오류, 공통의 가혹한 환경 (진동, 방사선, 습기, 오염). | "Neglecting these CCF contributions can result in a significant underestimate of the probability of the top event." | 네 가지 예는 71쪽 목록 |
| F08-025 | 71 | CCF는 같은 사양의 같은 부품으로 중복했을 때 중요하며, 능동 중복에서 더 크고 중복의 수가 늘수록 지배적이 된다. | "become more dominant contributors as the number of redundant components increases" | 중복이 CCF에 약하다는 서술 |
| F08-026 | 72 | 수치 예: 고장 확률 10^-3인 부품 셋이 모두 고장나야 하는 중복에서 독립이면 10^-9이다. 고장의 1%가 공통 원인이라고 가정하면 10^-5로, 독립일 때의 10,000배다. | "a factor of 10,000 greater than the independent failure probability" | 가정한 수치의 예시다. 조건부 확률 해석은 같은 쪽 |
| F08-027 | 72 | CCF는 tree에서 따로 모델링해야 한다. 각주는 CCF 모델로 beta-factor, Multiple Greek Letter, Alpha-factor를 든다. | "represents the fraction of the failure rate that is common to multiple susceptible components" | beta-factor의 설명. 앞 문장 "To include the CCF contribution in the fault tree, it must be separately modeled." |
| F08-028 | 160 | 핸드북의 가상 컴퓨터 시스템 예 (HECS)는 응용 소프트웨어 고장을 하드웨어 고장과 운영자 오류와 OR로 묶은 하나의 기본 사건으로 그린다. | "Thus an application (software (SW)) failure, GUI (hardware (HW)) failure or human operator error will lead to system failure." | 소프트웨어의 내부 구조는 전개하지 않는다 |
| F08-029 | 162 | 같은 예에서 응용 소프트웨어는 신뢰도 97%, 곧 고장 확률 0.03으로 "가정"한다. 이 쪽에 그 숫자를 얻은 방법은 없다. | "A similar quantification for the application software results in a software reliability of 97%." | 가상의 예 (hypothetical)이며 실제 소프트웨어 데이터가 아니다 |

## 2. stpa-handbook (MIT, STPA Handbook, Leveson와 Thomas. PDF 쪽 = 인쇄 쪽)

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| F08-030 | 4 | STPA는 부품 고장 외에, 고장나지 않은 구성요소 사이의 위험한 상호작용으로도 사고가 날 수 있다고 가정하는 hazard 분석 기법이다. | "accidents can also be caused by unsafe interactions of system components, none of which may have failed" | 1장 (Leveson)의 주장 |
| F08-031 | 4 | 저자들은 FTA, FMECA, ETA, HAZOP과 견준 여러 평가에서 STPA가 전통 기법이 찾은 시나리오를 모두 찾았고, 소프트웨어 관련과 비고장 시나리오를 더 찾았다고 적는다. | "STPA found all the causal scenarios found by the more traditional analyses" | 1장 (Leveson)의 주장. 평가 자료는 각주의 MIT 워크숍 발표이며 이 문서에 없다. 독립 검증이 아니다 |
| F08-032 | 6 | 전통적 hazard 분석은 시스템을 부품으로 나누고, 사고가 부품 고장에서 온다고 보고, 부품별 고장 확률을 따로 계산해 합친다. FMEA가 예다. | "assume that accidents are caused by component failure, calculate the probability of failure of each component separately" | 1장 (Leveson)의 서술 |
| F08-033 | 6 | 이 분해 접근이 맞으려면 각 구성요소가 독립으로 동작하고, 따로 볼 때와 전체 안에서 같게 동작하며, 되먹임이 없고, 상호작용을 둘씩 합칠 수 있어야 한다. | "Each component or subsystem operates independently." | 1장 (Leveson)의 서술 |
| F08-034 | 7 | 사건 사슬 접근이 FTA, ETA, HAZOP의 바탕이다. 확률을 쓰려면 사건이 확률적 (stochastic)이어야 하는데 소프트웨어와 사람은 이 가정을 만족하지 않는다고 적는다. | "Unfortunately, software and humans do not satisfy this assumption." | 1장 (Leveson)의 주장. 소프트웨어에 확률을 붙이는 문제에 관한 STPA 쪽의 입장 |
| F08-035 | 7 | 복잡한 시스템에서는 요구사항을 만족하는, 고장나지 않은 구성요소들의 상호작용으로 사고가 날 수 있다. 예로 Mars Polar Lander는 착륙 다리의 센서 잡음을 소프트웨어가 착륙으로 읽어 40 m 상공에서 엔진을 껐다. | "Accidents can occur due to unsafe interactions among components that have not failed" | 8쪽: "The software thought the spacecraft had landed" |
| F08-036 | 12 | STAMP는 안전을 고장 방지 문제가 아니라 동적 제어 문제로 본다. STPA는 STAMP 위에 세운 기법이고, FTA, ETA, HAZOP, FMECA는 chain-of-failure-events 모델 위에 있다고 적는다. | "safety is treated as a dynamic control problem rather than a failure prevention problem" | 1장 (Leveson)의 주장 |
| F08-037 | 14 | basic STPA는 네 단계다: 분석 목적 정의 (losses, hazards), 제어 구조 (control structure) 모델, unsafe control action (UCA) 식별, loss scenario 식별. | "The second step is to build a model of the system called a control structure." | 2장 (Thomas). 15쪽: 목적 정의는 losses, system-level hazards, system-level constraints, hazard 세분화 (선택)의 네 부분 |
| F08-038 | 17 | STPA의 hazard는 시스템 수준의 상태나 조건으로, 최악의 환경 조건과 함께 loss로 이어지는 것이다. 부품 수준의 원인 (예: 브레이크 고장)은 hazard가 아니다. | "A hazard is a system state or set of conditions that, together with a particular set of worst-case environmental conditions, will lead to a loss." | 2장 (Thomas). 19쪽에 "원인을 hazard로 쓰는" 실수의 설명 |
| F08-039 | 19 | STPA는 정해진 기능이 안전하고 옳다고 가정하지 않는다. 전통 기법이 기술적 기능의 이탈이나 부품 고장에서 시작하는 것과 구별한다. | "we cannot assume that the defined and specified functions are safe and correct" | 2장 (Thomas)의 주장 |
| F08-040 | 22 | control structure는 되먹임 제어 루프로 이루어진 계층 모델이다. controller는 control algorithm으로 control action을 정하고, process model (제어 대상에 관한 내부 믿음)을 가진다. | "A hierarchical control structure is a system model that is composed of feedback control loops." | 23쪽: process model 설명 |
| F08-041 | 25 | 제어 구조는 controller, control action, feedback, 그 밖의 입출력, controlled process로 이루어진다. 그림만 그려도 피드백 없이 control action을 내리는 구성요소나 충돌하는 명령 같은 결함이 드러날 수 있다고 한다. | "simply drawing a control structure diagram can make previously undiscovered flaws painfully obvious" | 2장 (Thomas)의 서술 |
| F08-042 | 31 | 제어 구조 모델은 기능적 관계를 강조하며, 물리적 근접이나 화재 전파 같은 순수한 물리/기하 관계는 보통 담지 않는다. | "does not typically capture purely physical or geometric relationships" | dependent failure 분석에서 STPA가 채우지 못하는 부분의 근거 |
| F08-043 | 35 | UCA는 특정 맥락과 최악의 환경에서 hazard로 이어지는 control action이다. | "An Unsafe Control Action (UCA) is a control action that, in a particular context and worst-case environment, will lead to a hazard." | 2장 (Thomas)의 정의 |
| F08-044 | 36 | UCA의 네 유형: (1) 제공하지 않아서 hazard, (2) 제공해서 hazard, (3) 너무 이르거나 늦거나 순서가 틀림, (4) 너무 오래 계속되거나 너무 일찍 멈춤 (연속 동작에만 해당). UCA는 맥락을 반드시 적는다. | "Providing a potentially safe control action but too early, too late, or in the wrong order" | 표 2.3. 37쪽: UCA의 다섯 부분은 source, type, control action, context, hazard 연결 |
| F08-045 | 37 | STPA는 최악의 경우 분석이다. 이미 안전장치 (중복, 백업)가 있어도 UCA를 빼지 않는다. 안전장치가 없을 때의 설계 결정을 돕는다. | "STPA is a worst-case analysis method not a best-case, average-case, or most-likely-case method." | 2장 (Thomas)의 서술 |
| F08-046 | 38 | 핸드북은 네 유형이 "provably complete"라고 적는다. 증명은 이 쪽에 없다. | "These four categories are provably complete" | 2장 (Thomas)의 주장. 증명을 확인하지 못했다 |
| F08-047 | 39 | control action에 매개변수 (예: 제동량, 토크 값)가 있으면 부족, 과다, 잘못된 방향의 경우를 따로 따진다. | "it is important to consider how the parameters may be insufficient, excessive, in a wrong direction, or otherwise unsafe" | 구동 토크 요구에 맞는 서술 |
| F08-048 | 40 | UCA의 맥락에는 controller가 믿는 상태가 아니라 실제 상태를 적는다. 믿음의 오류는 다음 단계 (loss scenario)에서 원인으로 다룬다. | "The UCA context should specify the actual (true) state or condition that would make the control action unsafe" | |
| F08-049 | 43 | loss scenario는 두 종류다: (a) UCA가 왜 일어나는가, (b) control action이 왜 잘못 실행되거나 실행되지 않는가. | "Why would Unsafe Control Actions occur?" | 2장 (Thomas) |
| F08-050 | 45 | controller가 안전하지 않은 control action을 내는 이유는 네 가지다: controller 자체의 고장, 부적절한 control algorithm, 다른 controller의 위험한 입력, 부적절한 process model. | "There are four general reasons why a controller might provide (or not provide) a control action that" | 이어지는 문장: "is unsafe" |
| F08-051 | 46 | 흔한 control algorithm 결함은 이전 control action이 제대로 실행되었다고 가정하는 것이다. 각주는 PID의 계수도 제어 대상의 동특성에 관한 process model의 믿음이라고 설명한다. | "the control algorithm assumes that previous control actions have been executed properly" | 각주 10: "Tuning-related issues in control theory can be captured here." |
| F08-052 | 51 | 시나리오가 아니라 개별 원인 요인의 목록을 만들면 요인의 조합을 놓친다. 그것은 단일 부품 고장만 보는 FMEA와 같아진다. | "Considering single factors essentially reduces to a FMEA where only single component failures are considered." | 2장 (Thomas)의 주장 |
| F08-053 | 52 | STPA의 출력은 요구사항, 설계 권고, 필요한 완화책, 시험 계획에 쓰이고, 설계가 끝난 뒤에는 기존 설계 결정의 빈틈을 찾는 데 쓴다. | "Evaluate existing design decisions and identify gaps and changes needed" | |
| F08-054 | 65 | STPA는 물리 설계를 가정하지 않고 필요한 기능 행동에서 출발해 그것이 위험해지는 조건을 찾는다. redundancy 같은 설계 해법은 그 뒤에 정한다. | "STPA starts without a specific design solution to potential problems." | 3장 (Leveson) |
| F08-055 | 105 | 중복을 쓸 때 부품이 독립이라고 가정하는 것은 흔한 설계상의 가정이며, 저자는 Macondo 방지기의 중복 장치들이 common cause failure 모드를 공유했고 Challenger의 O-ring도 같은 예라고 든다. | "the redundant units contained a common cause failure mode" | 6장 (Leveson)의 서술. 사고 사례의 해석은 저자의 것 |
| F08-056 | 105 | 기술 요인이 확인되었으나 확률이 충분히 낮다고 계산해 무시되었다가 사고가 난 경우가 흔하다고 적는다. | "ruled out because they were calculated to be sufficiently unlikely that they could be ignored" | 6장 (Leveson)의 주장. 확률로 위험 요인을 배제하는 데 대한 경고 |
| F08-057 | 107 | TCAS 개발에는 사람과 소프트웨어 행동을 포함한 매우 광범위한 FTA를 썼다. 정량화하지 못하는 사건도 제한하지 않았다. 저자는 STPA가 그 tree의 시나리오를 모두 만들고 더 만들었을 것이라고 주장한다. | "Because the goal was completeness over quantification" | 6장의 각주 24. Leveson의 주장. 확인된 비교가 아니다 |

## 3. nhtsa-etc-ev-fsa (NHTSA/Volpe, 전기차 가속 제어/전자 스로틀 제어의 기능 안전 분석 보고서. PDF 쪽 = 인쇄 쪽 + 16. 기준 판: ISO 26262 Final Draft (FDIS) 2011)

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| F08-058 | 107 | 이 보고서가 기준으로 삼은 규격은 ISO 26262 Final Draft (FDIS) 2011이다. | "ISO 26262 Road Vehicles - Functional Safety, Final Draft (FDIS), 2011." | 참고문헌 [2]. 2018년 판이 아니다 |
| F08-059 | 21 | 분석 순서: HAZOP과 STPA로 차량 수준 hazard를 찾고, ASIL을 매기고, safety goal을 정한 뒤, 시스템 구성요소에 Functional FMEA와 STPA를 safety analysis로 적용한다. | "Perform safety analyses on the relevant system components and interactions" | hazard analysis와 safety analysis를 다른 단계로 나누는 구도 |
| F08-060 | 21 | 보고서는 ISO 26262가 hazard나 safety 분석의 특정 방법을 권하거나 승인하지 않는다고 적는다. 또 STPA는 HAZOP, Functional FMEA와 달리 표준 접근이 정해져 출판되지 않았다고 적는다. | "ISO 26262 does not recommend or endorse specific methods for hazard or safety analysis." | 각주 7과 8. 같은 규격의 Part 9가 방법을 열거한다는 서술은 nhtsa-safety-standards-assessment 절 참조. FDIS 2011 기준 |
| F08-061 | 22 | HAZOP은 시스템 범위를 정하고, 기능을 나열하고, 각 기능에 guide word를 적용해 설계 의도에서 벗어나는 방식을 서술하고, 그 이탈의 차량 수준 영향을 평가한다. | "Apply a set of guidewords to each of the identified functions" | 2.2.1절 |
| F08-062 | 22 | IEC 61882는 11개의 guide word를 제안하며 시스템에 맞게 고칠 수 있다고 한다. 이 보고서는 일곱 개를 썼다: Loss of function, More than intended, Less than intended, Intermittent, Incorrect direction, Not requested, Locked function. | "lists 11 suggested guidewords, but notes that the guidewords can be tailored" | guide word의 일반 정의는 이 쪽에 없다. 목록과 적용 예만 있다 |
| F08-063 | 41 | HAZOP 적용 예: 기능 "Provide the APP to the EV PCM"에 guide word를 적용해 표를 만든다. Loss of function이면 운전 모드마다 uncontrolled vehicle propulsion, 추진력 상실 같은 차량 수준 hazard가 나온다. | "Function: Provide the APP to the EV PCM." | 표 2. APP는 가속 페달 위치, PCM은 전동 파워트레인 제어 모듈 |
| F08-064 | 23 | Functional FMEA는 bottom-up이고 brainstorming에 의존한다. 기능 수준에서 고장 모드를 찾고, 그 영향이 차량 수준 hazard로 이어지는지 본다. | "The FMEA is a bottom-up reliability analysis method that relies on brainstorming" | SAE J1739의 7단계 중 이 보고서는 1-4단계 (기능 나열, 고장 모드, 영향과 심각도, 원인)만 했다 |
| F08-065 | 23 | 보고서는 concept phase에서 특정 설계 없이 분석했으므로 FMEA의 원인별 발생 가능성, 현행 통제, 검출 가능성 (5-7단계)을 뒷받침할 자료가 없었다고 적는다. | "there are not enough data to support Steps 5 through 7" | Functional FMEA의 한계에 관한 보고서의 서술 |
| F08-066 | 23 | 보고서의 STPA 설명: 시스템은 controller가 UCA를 내거나 안전에 필요한 control action을 내지 않을 때에만 위험 상태에 들어간다. | "a system will not enter a hazardous state unless an unsafe control action is issued by" | 이어지는 문장: "a controller, or a control action needed to maintain safety is not issued" |
| F08-067 | 25 | 보고서는 UCA를 찾을 때 context 변수의 조합을 모두 열거하고 control action마다 여섯 guide word (원문의 네 개를 확장)를 적용했고, Quine-McCluskey 알고리즘으로 UCA 진술의 수를 줄였다. | "This study uses a set of six guidewords for the identification of UCAs" | 25-26쪽. 4단계 설명 |
| F08-068 | 26 | 원인 요인 (causal factor) guide word는 STPA 문헌에 17개가 있고, 보고서는 26개로 늘려 썼다. | "This project used an expanded list of 26 guidewords for" | 이어지는 문장: "identifying CFs" |
| F08-069 | 13-14 | 결과의 수: HAZOP은 19개 기능에서 132개의 malfunction, STPA step 1은 13개 control action에서 95개 UCA, Functional FMEA는 30개 고장 모드와 90개 원인, STPA step 2는 1,048개 원인 요인을 냈다. 일곱 개의 차량 수준 hazard로 모았다. | "The STPA method identifies 1,048 causes that may lead to 95 UCAs" | 보고서는 이 수를 나란히 적을 뿐 두 기법의 우열을 평가하지 않는다. 단위 (고장 모드/원인 대 UCA/원인 요인)와 범위가 달라 직접 비교할 수 없다 |
| F08-070 | 60 | FMEA 표는 EV PCM의 고장 모드 "더 큰 토크를 지령한다"에 원인 20개를 든다. 이 FMEA는 다른 차량 시스템이 정상이라고 가정했으므로 그 시스템의 결함은 표에 넣지 않았다. | "other vehicle systems are assumed to be operating correctly" | 표 25. 시스템 경계를 넘는 고장 전파는 FMEA 범위 밖 |
| F08-071 | 61 | FMEA 예 (표 26)에서 "더 큰 토크를 지령한다"의 원인은 하드웨어 결함, 입출력 연결 결함, 토크 계산 알고리즘 결함, 소프트웨어 매개변수 훼손, arbitration 논리 결함 등이고, 현행 통제로 3단계 감시와 진단이 적힌다. | "Arbitration logic fault" | 소프트웨어 원인도 같은 표의 행으로 나열된다 |
| F08-072 | 63 | STPA step 2의 원인 요인 1,048개 가운데 외부 교란이 317개, "차량의 다른 구성요소와의 위험한 상호작용"이 301개, 소프트웨어 오류가 53개로 분류되었다. | "Hazardous interaction with other components in the rest of the vehicle" | 표 27. 한 요인이 여러 UCA에 걸칠 수 있어 분류 수의 합과 다르다 |
| F08-073 | 64 | STPA 원인 요인의 예: 전자기 간섭이 EV PCM에 영향을 주는 경우, BTO 모드 중 다른 시스템의 토크 증가 요청에 EV PCM이 응답하는 논리 설계 결함. 앞은 구성요소 사이의 상호작용이고 뒤는 소프트웨어 논리다. | "The EV PCM may respond to requests from other vehicle systems" | 표 28 |
| F08-074 | 74 | 보고서가 예시로 든 안전 요구사항: 중복 요소를 쓰면 common cause failure에 대해 검증한다 (ASIL C/D). 한 요소의 전원 고장이 다른 요소의 전원에, 한 요소의 통신 경로 고장이 다른 요소의 통신 경로에 영향을 주면 안 된다. | "If redundant elements are used, they are to be verified against common cause failures" | 13쪽 각주 1: 이 요구사항들은 예시이며 NHTSA의 공식 입장이 아니다. ISO 26262의 요구라고 보고서가 주장하는 것이 아니다 |

## 4. nasa-gb-8719-13 (NASA Software Safety Guidebook, 2004-03-31. PDF 쪽 = 인쇄 쪽 + 1)

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| F08-075 | 131 | 시스템이 정해진 요구의 올바른 상태를 만족하면서도 안전하지 않을 수 있다. 소프트웨어 FTA (SFTA)는 하드웨어 FTA를 소프트웨어로 넓힌 것이다. | "It is possible for a system to meet requirements for a correct state and still be unsafe." | 6.6.7절 |
| F08-076 | 131 | SFTA는 요구 단계에서 예비로 하는 top-down 분석이며, tree의 꼭대기 (hazard)를 미리 알고 있어야 한다. hazard의 출처는 PHA나 소프트웨어 하위 시스템 hazard 분석이다. | "The requirements phase is the time to perform a preliminary software fault tree analysis (SFTA)." | |
| F08-077 | 132 | 분석 결과는 hazard에 기여하는 원인 (또는 그 조합)의 목록이고 일부는 소프트웨어에 있다. 분석의 질은 분석자의 경험에 달려 있고, 소프트웨어는 부분 시스템이라기보다 전체와 함께 동작하므로 소프트웨어만 따로 떼기는 어렵다. | "The quality of the analysis depends on the analyst's experience and capability." | 소프트웨어 분리의 서술은 같은 쪽: "difficult, if not impossible" |
| F08-078 | 132 | SFTA (top-down)와 SFMEA (bottom-up)를 함께 하면 가능한 고장 모드를 찾는 데 매우 좋으나 시간과 비용이 든다. 작은 프로젝트는 하나만 한다. 분석자가 익숙한 것을 고르거나 일부러 낯선 것을 골라 새 관점을 얻기도 한다. | "these two analyses are very good at finding all the possible failure modes or areas of concern" | 133쪽에 같은 문장이 되풀이된다 |
| F08-079 | 132-133 | 소프트웨어 FMEA는 표준 (하드웨어) FMEA의 방법에서 부품을 소프트웨어 구성요소로 바꾼 것이다. 널리 쓰는 MIL-STD-1629 절차는 여덟 단계다: 시스템 정의, 기능 블록도, 항목과 인터페이스의 고장 모드, 최악의 결과 평가, 검출 방법과 보상 조치, 시정 설계, 시정의 영향, 문서화. | "A Software FMEA uses the methods of a standard (hardware) FMEA" | |
| F08-080 | 133 | 양방향 분석은 소프트웨어 설계를 체계적으로 검토했다는 제한적이지만 필수적인 보증을 줄 수 있다고 적는다. | "This bi-directional analysis can provide limited but essential assurances" | 참고문헌 [90]을 인용한 문장 |
| F08-081 | 28 | 소프트웨어 hazard의 발생 가능성은 특히 소프트웨어에서 하드 넘버가 아니라 공학적 판단에 기대는 경우가 많다. | "based on engineering judgment and not on hard numbers, especially where software is concerned" | 2장 위험 지수의 likelihood 설명 |
| F08-082 | 315 | SFTA는 소프트웨어 고장이 일으킬 수 있는 hazard의 원인을 찾는 체계이며, hazard 자체를 찾는 것이 아니다. 소프트웨어는 하드웨어와의 상호작용을 통해서만 hazard를 일으키므로 소프트웨어 tree에 하드웨어 요소가 자주 들어간다. | "Software can only cause the hazard through its interactions with the hardware." | 부록 C. Leveson 등의 글을 바탕으로 했다고 적는다 |
| F08-083 | 315 | 소프트웨어는 여러 모드와 상태에서 동작하므로 소프트웨어 tree에는 inhibit과 conditioning event가 더 많이 들어갈 수 있다. | "There may be a lot more of inhibits and conditioning events when mapping a Software Fault Tree." | |
| F08-084 | 316 | SFTA의 목표는 설계나 구현 (실제 코드)의 논리가 hazard를 만들지 않음을 보이는 것이다. 위험한 상태가 비교적 적은 시스템에서 가장 실용적이다. | "SFTAs are most practical to use when we know that the system has relatively few states that are hazardous" | |
| F08-085 | 316 | SFTA는 소프트웨어의 신뢰도에 관해 아무 주장도 하지 않는다. 신뢰도가 높은 소프트웨어가 안전하다는 것은 반드시 참이 아니며 안전과 신뢰도는 때로 서로 어긋난다. 통합과 시험을 대체하지도 않는다. | "The SFTA makes no claim as to the reliability of the software." | 같은 쪽: "SFTA is not a substitute for the integration and test procedures". 316쪽 (인쇄 315쪽) |
| F08-086 | 317 | 절차는 hazard가 일어났다고 가정하고 가능한 원인의 집합을 구하는 것이다. 확장은 모든 잎이 계산 가능한 확률의 사건이 되거나 더 분석할 수 없을 때까지, 또는 소프트웨어와 무관한 하드웨어 오작동에서 멈춘다. 시작점이 "시스템이 고장난다"처럼 지나치게 일반적이면 쓸모없다. | "The expansion continues until all leaves describe events of computable probability or the event cannot be analyzed further." | 소프트웨어 잎에 확률을 붙이는 방법은 이 부록에 없다 |
| F08-087 | 317 | SFTA는 일관된 결과를 보장한다고 주장하지 않는다. 언제 멈출지와 어떤 hazard를 분석할지는 분석자의 판단에 달려 있다. 복잡한 시스템의 모든 hazard를 미리 정할 수 없다는 서술이 앞에 있다. | "It is dependent on the judgment of the individual as to when to stop the process" | |
| F08-088 | 318 | 코드 수준 SFTA는 while, if 같은 구문을 템플릿으로 바꿔 hazard의 전제 조건 (weakest precondition)을 구하고, 그 조건을 assertion으로 검사하게 한다. 캐나다 원전 정지 소프트웨어를 3 work-month에 검토했으나 이 수치는 규모가 커지면 그대로 늘려 쓰기 어려울 것이라고 적는다. | "3 work months for 6K lines of code" | 가이드북의 사례. 이 사례의 범위는 소프트웨어 6천 줄 |
| F08-089 | 322 | SFMEA는 bottom-up 분석이다. 각 구성요소를 보고 고장 나는 모든 방식을 나열하고, 그것이 시스템에 미치는 영향과 hazard로 이어지는지를 따라간다. 소프트웨어는 닳지 않으며, 동작하거나 이미 고장나 있다. | "Each component in the system is examined, and all the ways it can fail are listed." | 같은 쪽 소프트웨어 고장 모드 예: "value of data out of limits (software), and garbled data (software)" |
| F08-090 | 323 | SFMEA가 찾을 수 있다고 적힌 것: 숨은 고장 모드, 시스템 상호작용, 의존성, 예상하지 못한 고장 모드, 명시되지 않은 가정, 요구와 설계의 불일치. 또한 SFMEA는 만병통치약이 아니라고 적는다. | "Hidden failure modes, system interactions, and dependencies" | D.2절. 좋은 방어적 설계에서는 많은 오류를 오류 처리가 이미 관리한다는 서술이 같은 쪽 |
| F08-091 | 323-324 | SFMEA의 문제점으로 시간이 걸리고, 지루하고, 수작업이고, 분석자의 지식과 문서의 정확도에 달려 있고, 고장 모드 목록이 불완전하면 이득이 의문스럽고, 한 번에 하나의 고장만 본다는 점을 든다. | "Only considers a single failure at one time (not multiple concurrent failures)" | D.3절. 324쪽에 있는 인용문 |
| F08-092 | 328 | SFMEA의 고장은 기능 고장 (PHA 등에서 도출), 나쁜 입력이나 고장난 하드웨어에 대한 바람직하지 않은 반응, 인터페이스 고장으로 나눈다. 소프트웨어 대 소프트웨어, 소프트웨어 대 하드웨어, 하드웨어 대 소프트웨어 인터페이스를 다루고 하드웨어끼리는 시스템 FMEA가 맡는다. | "There are more problems identified with interfaces, according to some researchers, than any other aspect of software development." | D.4.3절 |
| F08-093 | 336-337 | SFMEA의 데이터 고장 유형은 범위 밖, 누락, 순서 이상, 덮어쓰기, 잘못된 값이다. 사건 고장 유형은 halt, omission, 틀린 논리, timing/order다. | "halt (abnormal termination), omission (failure of the event to occur), incorrect logic/event, or timing/order" | 337쪽 인용. 데이터 유형은 336쪽 |
| F08-094 | 141 | fault propagation은 소프트웨어 (또는 하드웨어, 사람)의 오류가 한 구성요소에서 다른 구성요소로 번지는 것 (cascading)이다. 이를 막으려면 safety-critical 구성요소가 non-critical 구성요소와 완전히 독립이어야 하고, 자신의 오류를 감지해 넘기지 않아야 한다. | "Fault Propagation is a cascading of a software (or hardware or human) error from one component to another." | 7.4.2절. cascading의 정의로 쓸 수 있는 문장 |
| F08-095 | 141 | must work function은 독립 병렬 중복으로 고장 허용을 얻는다. 병렬이 독립이려면 서로 다른 소프트웨어가 있어야 하고, N-Version으로 얻을 수 있어도 진정한 독립은 매우 어렵다. 두 병렬 경로가 독립이려면 단일 고장 하나가 둘 다 멈추게 해서는 안 된다. | "though true independence is very difficult to achieve" | |
| F08-096 | 143 | 같은 운영체제를 도는 두 프로세서는 N-Version으로 쓴 정도와 상관없이 서로 독립이 아니고 서로의 고장을 견디지도 못한다고 NSTS 1700.7B의 규정을 인용한다. | "two processors running the same operating system are neither independent nor failure-tolerant of each other" | 규정의 서술이다. 인용 출처는 같은 쪽 |
| F08-097 | 144 | 별도 팀이 소프트웨어를 개발해도 진정으로 독립이 아닌 경우가 흔하다는 연구가 있다. | "Even if separate teams develop the software, studies have shown that the software is still often not truly independent." | N-Version의 한계 서술 |
| F08-098 | 144 | fault containment region (FCR)은 non-critical에서 critical로, 중복 단위 사이에서, safety-critical 구성요소 사이에서 소프트웨어 결함이 전파하는 것을 막는다. 하드웨어로 나누는 것이 가장 좋다. | "FCRs are best partitioned or firewalled by hardware." | 7.4.2.2절 |
| F08-099 | 144 | 논리적 방화벽은 방어적 프로그래밍과 소프트웨어 중복으로 일부 만들 수 있으나, NASA 안에서는 hazard 완화로 보고 hazard 통제로 보지 않는다. 하드웨어 고장이나 EMI/방사선으로 무력해질 수 있기 때문이다. | "within NASA this is normally regarded as hazard mitigation, but not hazard control" | |
| F08-100 | 144 | 독립 FCR을 같은 프로세서에 두어도 되는 경우가 있다. 예: 별도의 메모리 칩에 있고 같은 CPU에서 동시에 멀티태스킹하지 않는 경우. | "Sometimes it is acceptable to have independent FCRs hosted on the same processor" | |
| F08-101 | 158 | independence analysis는 safety-critical 구성요소가 non-critical과 독립인지 검증한다. safety-critical 구성요소의 출력에 영향을 주는 구성요소는 그 자체로 safety-critical이 된다. 입출력, 전역/공유 변수, 부작용을 본다. | "Those CSCs that are found to affect the output of safety-critical CSCs are designated as safety-critical themselves." | 7.5.3절 |
| F08-102 | 159 | 절차형 개발에서는 호출 구조와 전역/공유 데이터 접근이 의존을 정하고, 객체지향에서는 상속, 조합, 메서드 호출, 공유 데이터가 정한다. | "Dependence is determined by the calling structure (what module calls what module) and by access to global or shared data." | |
| F08-103 | 157 | 설계 단계에서는 요구 단계의 예비 소프트웨어 fault tree와 SFMEA를 구성요소 수준으로 보강한다. safety-critical에 영향을 줄 수 있는 non-critical 구성요소는 그 자체로 safety-critical이 된다. | "A non-critical component that can influence the safety-critical components becomes safety-critical itself." | 7.5.1.3절 |

## 5. nasa-system-safety-handbook-v1 (NASA/SP-2010-580 Version 1.0, 2011-11. PDF 쪽 = 인쇄 쪽 + 16)

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| F08-104 | 77 | 중복은 하드웨어뿐 아니라 소프트웨어와 사람의 작업에도 쓸 수 있다. 중복 시스템의 고장 확률은 구성요소의 확률에서 수학적으로 정하되, 공통의 원천이나 기전으로 고장나는 비슷한 구성요소가 있으면 공식이 common-cause failure를 반영해야 한다. | "the mathematical formulation must account for these common-cause failure possibilities" | 4.4절 |
| F08-105 | 77 | 위험에 기반한 확률 배분은 fault tree나 reliability block diagram 같은 논리 모델에서 시작하며, 가장 낮은 수준의 사건은 하드웨어, 소프트웨어, 사람 구성요소의 고장이거나 그 인터페이스의 고장이다. | "the lowest level events are failures of the hardware, software, and human components" | 소프트웨어 고장 확률을 어떻게 구하는지는 이 쪽에 없다 |
| F08-106 | 84 | 설계 일반 통제의 예로 가능한 곳마다 기능적 중복을 두는 것과, 단일 고장점과 common cause failure를 적절히 다루는 것을 든다. | "Controls to ensure single points of failure and common cause failures are adequately addressed" | 이 문서에 common cause failure의 정의는 없다 |

## 6. hse-hsg238 (HSE, Out of control, 2판. PDF 쪽 = 인쇄 쪽)

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| F08-107 | 41 | 설계의 두 핵심 기법은 fault avoidance와 fault tolerance다. 복잡할수록 내장된 (체계적) 고장에 취약하고, 소프트웨어 개발에서 큰 문제라고 적는다. | "The more complex the design, the more prone the system will be to systematic faults" | 22항 |
| F08-108 | 41 | 고장 허용에는 중복, 다양성 (diversity), 다수결 같은 기법을 쓴다. | "Techniques such as redundancy, diversity, majority voting etc are used to provide fault tolerance." | 이 문서에 common cause failure나 dependent failure를 다룬 서술은 없었다 |

## 7. autosar-safety-measures (AUTOSAR CP R25-11, Overview of Functional Safety Measures in AUTOSAR, 2차 자료. 참고문헌 [1]이 ISO 26262:2018을 가리킨다. 아래 조항 번호는 문서가 적은 것이다)

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| F08-109 | 9 | AUTOSAR 문서는 ISO 26262-6 7.4.8 (Coexistence)을 들어, 한 소프트웨어에 ASIL이 다른 구성요소가 섞이면 전체를 가장 높은 ASIL로 개발하거나, 높은 ASIL 구성요소를 낮은 ASIL 요소의 간섭으로부터 freedom from interference로 지켜야 한다고 설명한다. | "freedom from interference shall be ensured for software components with a higher ASIL rating from elements with a lower ASIL rating" | 2차 자료의 요약. 규격 원문이 아니다 |
| F08-110 | 9 | 같은 문서는 ISO 26262-6 Annex D가 소프트웨어 구성요소 사이의 간섭을 일으키는 fault의 예를 Memory, Timing, Execution, Exchange of Information의 넷으로 묶는다고 적는다. | "provides examples for faults, which cause interference between software components" | 2차 자료의 요약 |
| F08-111 | 10 | 메모리 관련 fault의 예 (Annex D.2.3): 내용 손상, 다른 소프트웨어 요소에 할당된 메모리의 읽기/쓰기, 일관되지 않은 데이터, 스택 오버플로/언더플로. | "Read or write access to memory allocated to another software element." | 2차 자료의 요약 |
| F08-112 | 14 | AUTOSAR OS는 OS-Application을 서로 다른 메모리 영역에 두어 메모리 관련 fault에 대한 freedom from interference를 제공한다. | "provides freedom from interference for memory-related faults by placing OS-Applications into separate memory regions" | |
| F08-113 | 15 | ASIL이 다른 소프트웨어 구성요소를 같은 OS-Application에 두면 안 된다. 메모리 파티셔닝은 같은 OS-Application 안의 구성요소 사이에는 freedom from interference를 주지 못한다. | "Software Components with different ASIL ratings should not be assigned to the same OS-Application." | 구조 (아키텍처) 수준에서 독립성 주장을 하는 방법의 예 |
| F08-114 | 16 | 한 구성요소 안의 runnable이 ASIL이 다르면 OS-Application 수준 파티셔닝으로 부족하고 task 수준이 필요하다. 그러나 task 수준 파티셔닝은 AUTOSAR OS에서 선택 사항이다. | "an implementation of Task-level partitioning is optional for the AUTOSAR OS" | 16쪽. 21쪽에도 같은 취지의 한계 서술 |
| F08-115 | 21 | 메모리 파티셔닝에 관련된 ISO 26262 참조 목록에 Part 6 [7.4.9] Partitioning, [7.4.11] Dependent failure analysis, Annex D, Part 9 [6.2], [6.4.3], [6.4.4]가 있다. 이 문서는 dependent failure analysis의 내용을 설명하지 않는다. | "Part 6: [7.4.11] Dependent failure analysis" | 표 2.4. 조항 번호는 문서가 적은 대로 |
| F08-116 | 46 | AUTOSAR가 제공하지 않는 것의 목록에 "No dependent failure analysis is performed."가 있다. HARA, HAZOP 같은 위험 분석 기법도 AUTOSAR 규격이 정하지 않는다고 적는다. | "No dependent failure analysis is performed." | 이 분석은 AUTOSAR를 쓰는 쪽이 해야 한다는 뜻으로 읽힌다 (문서가 그렇게 명시하지는 않는다) |
| F08-117 | 47 | AUTOSAR의 Safety Use Case는 AUTOSAR 방법론 위의 safety analysis를 위한 지침을 제공하는 것을 목표로 든다. | "Provide a guideline for safety analyses on top of AUTOSAR methodology" | 3.6절 |

## 8. nhtsa-safety-standards-assessment (Van Eikema Hommes, NHTSA DOT HS 812 285, 2016-06. 2차 자료. PDF 쪽 = 인쇄 쪽 + 10. 기준 판: ISO 26262 Final Draft (FDIS) 2011)

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| F08-118 | 15 | 평가는 ISO 26262의 final draft에 기반한다. 규격 위원회 전문가들이 그 기술 내용이 출판판과 동일하다고 확인했다고 적는다. 참고문헌 [7]은 2011년 FDIS다. | "the technical content of the final draft version is identical to the published edition" | 각주 4. 2011년 1판이며 2018년 판이 아니다 |
| F08-119 | 20 | ISO 26262는 안전 공학 프로세스를 정하는 데 더해 여러 부에서 hazard 분석과 safety 분석 방법 (FMEA, FTA, HAZOP 등)을 열거한다. | "ISO 26262 also lists a number of commonly known hazard analysis and safety analysis methods" | 3.1.2절. 열거는 Part 9로 안내한다 |
| F08-120 | 23 | 보고서에 따르면 ISO 26262는 item 수준에서 hazard 분석을 하고, 그 아래 수준에서 safety analysis (Part 9 Clause 8; FMEA, FTA, ETA, HAZOP 등)를 쓴다. | "At lower level of the system decomposition, ISO 26262 employs safety analysis" | 3.4.2절. 조항 번호는 FDIS 2011 기준으로 이 문서가 적은 것 |
| F08-121 | 23 | 저자는 FMEA, FTA, ETA가 기계 시스템과 랜덤 하드웨어 고장이 주된 원인이던 50-60년 전에 개발되었고, 현대 차량은 소프트웨어 오류와 위험한 시스템 상호작용으로도 안전하지 않은 상태에 들어갈 수 있다고 적는다. | "FMEA, FTA, and ETA methods were developed 50 to 60 years ago" | 저자 (Hommes)의 주장. 근거로 Leveson [4]를 든다 |
| F08-122 | 23 | 이 기법들은 랜덤 하드웨어 고장을 정성과 정량으로 잘 다루지만, 위험한 시스템 상호작용의 원인을 찾는 지침이 충분하지 않고, 소프트웨어는 하드웨어처럼 랜덤하게 고장나지 않아 바로 적용되지 않는다고 적는다. | "these methods are not immediately applicable to software because software does not have random failures like hardware" | 저자의 주장 |
| F08-123 | 23 | FMEA, FTA, ETA는 단순한 선형 사건 사슬 사고 모델에 기반한다고 비판한다. 체계적인 문제와 상호작용 문제는 사슬로 모델링하면 놓치기 쉽다는 것이다. | "simple linear chain-of-event accident causality models" | 저자의 주장 ([4] 인용) |
| F08-124 | 23 | FMEA는 bottom-up 귀납 방법이라 복잡한 시스템에서 모든 구성요소 고장과 조합을 찾기가 힘들고, 부품이 고장나지 않은 상태의 조합이 위험을 만드는 경우를 예견하기는 더 어렵다고 적는다. | "FMEA is a bottom-up inductive method." | 저자의 서술 |
| F08-125 | 24 | FTA는 top-down이라 부품 고장의 모든 조합을 찾는 부담을 덜지만, 하위 사건을 만드는 지침은 적고, fault tree는 보통 brainstorming이나 전문가 의견의 기록이라고 적는다. | "Fault trees are typically records of the results of brainstorming or expert opinion" | 저자의 서술. 근거는 Leveson 1995 [23] |
| F08-126 | 24 | 정량 FTA는 하위 사건의 확률을 위로 합쳐 top event의 확률을 얻는다. 단, 부품 고장이 서로 독립임을 증명할 수 있어야 한다. | "if component failures can be proven to be independent of one another" | 3.4.2절. 독립성이 정량 분석의 전제라는 서술 |
| F08-127 | 24 | 하위 사건의 확률 자료가 없는 경우가 많고 (신기술, 소프트웨어, 사람과의 상호작용), 소프트웨어 고장 자료는 확률적이지 않아 확률 계산에 쓸 수 없을 수 있다고 적는다. | "Software failure data may not be probabilistic in nature, and therefore cannot be used for probability math" | 저자의 주장. 근거로 [24] [25] 인용 |
| F08-128 | 24 | 이 방식은 어떤 부품도 고장나지 않았는데 상호작용이 위험을 만드는 상황을 제대로 다루지 못한다. | "inadequately handling situations when none of the components fails" | 저자의 서술 |
| F08-129 | 24 | HAZOP은 공정 산업에서 나왔고 대체로 정성적이다. guide word와 실제 프로세스의 모델링이 부품 고장과 상호작용을 함께 보게 도우나, 자동차에 적용하려면 수정과 시험이 필요하며 ISO 26262는 적용 지침을 주지 않는다. | "ISO 26262 does not provide guidance on how to apply this method to automotive systems." | 저자의 서술. FDIS 2011 기준 |
| F08-130 | 24 | 규격은 이 기법들을 소프트웨어 개발에도 적용할 수 있다고 하지만, 소프트웨어 관련 사고의 다수는 코딩 오류가 아니라 요구사항의 결함에서 오고, 소프트웨어는 랜덤하게 고장나지 않아 이 기법들이 소프트웨어 hazard 분석에 늘 충분한 것은 아니라고 적는다. | "the majority of software-related accidents is due to requirements flaws" | 저자의 주장 ([4] 인용). 이어지는 문장: "not coding errors" |
| F08-131 | 25 | STPA는 안전을 제어 문제로 보는 체계적 과정이고, 안전에 중요한 부품 고장과 위험한 시스템 상호작용을 함께 찾도록 안내하며, 초기 개념 단계에도 쓸 수 있다고 적는다. 자동차 적용 사례는 아직 적다. | "applications to motor vehicles are still limited in numbers" | 저자의 서술. 효과는 분석자의 지식과 전문성에 달려 있다고도 적는다 |
| F08-132 | 22 | ISO 26262의 hazard 정의가 item의 오동작 (설계 의도를 충족하지 못함)에 한정되어, 어느 부품도 고장나지 않았는데 시스템 사이의 위험한 상호작용으로 생기는 안전 문제를 다루지 못할 수 있다고 적는다. | "may not address safety issues arising from unsafe interactions between systems" | 저자의 서술 |
| F08-133 | 29 | MIL-STD-882E를 인용해 단일 소프트웨어 기능의 고장 확률은 판정하기 어렵고 과거 자료에 기댈 수 없으므로 소프트웨어 고장 확률 개념을 쓰지 않는다고 적는다. | "determining the probability of failure of a single software function is difficult at best" | 3.6.4절. MIL-STD-882E의 문장을 보고서가 인용한 것 |
| F08-134 | 29 | DO-178C를 인용해 소프트웨어에 오류가 있을 가능성은 랜덤 하드웨어 고장과 같은 방식으로 정량화할 수 없다고 적는다. | "the likelihood that the software contains an error cannot be quantified in the same way as for random hardware failures" | DO-178C의 문장을 보고서가 인용한 것 |
| F08-135 | 29 | 중복 fault-tolerant 소프트웨어는 정말 독립인지 검증이 필요하고, 위험 평가를 하는 개발 초기에는 이를 하기가 매우 어려울 수 있다. | "Redundant fault tolerant software also needs verification that they are truly independent." | 저자의 서술 |

## 9. nasa-toyota-ua-report (NASA NESC, Toyota Unintended Acceleration Investigation, TI-10-00618. PDF 쪽 = 인쇄 쪽)

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| F08-136 | 68 | 높은 엔진 속도나 출력으로 이어지는 시스템 고장을 High Level Functional Fault Tree로 정리했다. 하위의 센서와 구동기 fail-safe 검출은 상세 tree에 따로 표시했다. | "System failures resulting in high engine speed or power are captured in the High Level" | 6.5.2절 |
| F08-137 | 68 | 유효한 페달 신호처럼 보이는 고장 (tree의 왼쪽 가지)은 하위 수준에서도 시스템 수준에서도 찾아 완화하기 어렵다. 스로틀이 크게 열릴 경로로 둘을 든다: 페달 신호 VPA1, VPA2 두 경로의 고장, 또는 검출되지 않는 Main CPU 소프트웨어 오동작. | "Failures on the left branch appear as valid pedal signals" | NESC의 서술. 소프트웨어 경로는 "requires an undetected software malfunction" |
| F08-138 | 71 | 보고서는 fishbone (원인 분류)과 fault tree를 구분한다. fishbone은 기능 계층을 따라 원인을 정리하지만 의도치 않은 가속을 만들 조합 논리는 없다. fault tree가 그 조합을 보인다. | "The fishbone organizes failure causes along a functional hierarchy, but without the combinatorial logic necessary to create a UA." | NESC의 서술. 원인 목록과 조합 논리의 차이 |
| F08-139 | 71 | tree의 AND 게이트는 검출을 빠져나간 큰 스로틀 명령과 작동하지 않는 idle speed fuel cut fail-safe를 묶어 엔진 속도 2500 rpm 초과를 만든다. 보고서는 다양한 (diverse) 센서와 구동기가 설계 분석이나 하위 검출을 빠져나간 고장에 대한 방어를 줄 수 있다고 적는다. | "a large anomalous throttle command that escaped detection with the non functioning idle speed fuel cut fail-safe" | 인용 뒤에 "in order to create an event" 가 이어진다 |
| F08-140 | 72 | 두 센서를 서로 비교하면 두 센서가 모두 유효한 전압으로 오염되지 않는 한 고장을 막는다. VPA1과 VPA2에 오프셋을 둔 것은 두 센서가 함께 유효한 신호를 흉내 내게 하는 common mode failure 원인에 대한 보호다. | "Comparing two sensors against each other can protect against failures as long as the failures do not corrupt both the sensors with valid voltages." | 오프셋 서술은 같은 쪽: "potential common mode failure causes" |
| F08-141 | 78 | 고장 표에서 Main CPU 소프트웨어가 가속 페달을 놓았는데 단독으로 스로틀을 여는 고장은 "이론적" 고장으로 분류되고, 현실에서 발견되지 않았으며 시험을 만들 수 없다고 적힌다. 한 메모리/변수 훼손이 의도치 않은 가속을 만드는 곳을 소프트웨어에서 찾지 못했다고 한다. | "Cannot engineer a test." | 표 6.5.2.2-1. NESC의 서술. 소프트웨어 안전성의 증명이 아니다 |

## 10. koopman-toyota-ua (Philip Koopman, 슬라이드 2014, CC BY 4.0. PDF 쪽 = 슬라이드 번호)

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| F08-142 | 31 | fault containment region (FCR)은 결함의 방화벽이다. 하드웨어/소프트웨어 결함은 널리 영향을 줄 수 있다 (비트 하나가 task 전체를, 잘못된 포인터가 무관해 보이는 함수를 망가뜨림). 한 FCR이 자신의 모든 고장 모드를 스스로 감시할 수는 없다. | "A wild pointer can corrupt a seemingly unrelated function" | Koopman의 주장 |
| F08-143 | 32 | 중요한 시스템은 서로 독립인 FCR 여러 개가 필요하다. 공유 자원은 위험한 단일 고장점이고, 자가 시험만으로는 안전하지 않다. 대표 패턴은 multi-channel과 monitor/actuator다. | "Shared resources are a dangerous single point of failure" | Koopman의 주장 |
| F08-144 | 33 | 슬라이드는 Toyota ETCS에서 감시 칩과 main CPU가 입력을 공유하면 검출되지 않은 잘못된 데이터가 main CPU에 도달한다고 보이고, 별도 A/D 입력으로 교차 검사하는 대안을 그린다. | "Sharing of inputs permits undetected faulty data to reach main CPU" | 슬라이드의 설계 주장. 슬라이드 그림에 근거한 요약 |
| F08-145 | 34 | 슬라이드는 안전한 구조에 단일 고장점이 없어야 한다고 적고, 두 페달 신호 VPA1과 VPA2가 같은 칩의 같은 입력 블록을 지나는 것을 단일 고장점의 예로 든다. | "This is a Single Point of Failure" | 슬라이드가 인용한 증언 (Bookout 2013-10-11) 근거. Koopman의 해석 |

## 11. b737max-jatr (Joint Authorities Technical Review, Boeing 737 MAX Flight Control System, 2019-10. PDF 쪽 = 인쇄 쪽 + 20)

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| F08-146 | 53 | JATR는 FAA가 single and multiple failure (S&MF) 분석을 인증 제출물로 요구해, 시스템 수준 통합과 항공기 수준의 cascading hazard의 영향을 보이게 할 것을 권고한다 (R6.8). Boeing은 이를 내부 문서로만 썼다. | "demonstrate system-level integration and the effects of cascading hazards at the aircraft level" | JATR 팀의 권고. 관찰 O6.8-A |
| F08-147 | 53 | JATR는 단일 worst-case 시나리오 분석을 모든 고장 모드를 덮는 것으로 받아들이지 말고, 신호 입력마다 고장 모드를 모든 예상 가능한 시나리오와 비행 단계의 연쇄 영향에서 분석하게 하라고 권고한다 (R6.9). | "all foreseeable scenarios and the multiple possible outcomes for each flight phase" | JATR 팀의 권고 |
| F08-148 | 53 | 관찰: AOA 고장의 S&MF 분석이 한쪽 AOA 상실과 다른 쪽 오류라는 단일 worst-case에 한정되었고, 이미 catastrophic이라 MCAS 도입 뒤 갱신되지 않았다. JATR는 이것이 단일 AOA 고장의 위험한 영향을 찾는 데 적절하지 않았다고 판단한다. | "the S&MF analysis was limited to a single worst-case scenario" | 관찰 O6.9-A, 발견 F6.9-A |
| F08-149 | 53 | 발견: MCAS의 오작동 분석이 동시에 일어날 수 있는 다른 일, 예컨대 AOA 고장의 flight deck 효과가 승무원의 주의를 분산시킬 가능성을 충분히 고려하지 않았다. | "did not adequately take into account what else might be happening at the same time" | 발견 F6.7-A. JATR 팀의 판단 |
| F08-150 | 54 | 관찰: 시스템 안전 평가 (SSA)는 MCAS 소프트웨어 요구사항 Revision C 이후로 갱신되지 않았다. 그 뒤 소프트웨어에 대한 위험, 고장, 안전 분석 문서를 JATR는 찾지 못했다. 설계가 바뀌어도 분석을 다시 하지 않은 사례다. | "The SSA was not updated beyond Revision C of the STS requirements for MCAS." | 관찰 O6.9-F |
| F08-151 | 54 | 관찰: Boeing은 MCAS가 여러 번 잘못 작동하는 것이 한 번 잘못 작동하는 것보다 나쁘지 않다고 결론 지었고, 근거는 승무원이 매번 trim을 되돌린다는 가정이었다. | "multiple erroneous MCAS activations were not worse than a single erroneous activation" | 관찰 O6.9-H. JATR의 관찰 서술 |

## 장 계획이 기대했지만 문서에 없던 것

- ISO 26262가 정의한 dependent failure, common cause failure, cascading failure의 규격 문장은 받은 문서 어디에도 없다. AUTOSAR 문서는 용어 "dependent failure analysis"를 참조 표 (21쪽)와 "하지 않는다" 목록 (46쪽)에만 쓰고 설명하지 않는다. NHTSA 두 보고서에는 이 용어가 나오지 않는다. cascading failure는 NASA GB-8719.13 141쪽의 fault propagation 정의와 JATR의 cascading hazards/effects 서술이 가장 가깝다.
- freedom from interference는 AUTOSAR 9, 14, 15쪽의 2차 설명뿐이고, ISO 26262의 정의 문장이 아니다. 규격 번호도 AUTOSAR가 적은 것이다.
- safety analysis, dependent failure analysis를 ISO 26262 Part 9가 어떻게 요구하는지 (ASIL별 필요 여부 등)는 문서에 없다. NHTSA 평가 보고서 23쪽이 Part 9 Clause 8을 언급하는 것이 전부이며, FDIS 2011 기준이다.
- HAZOP guide word의 일반 정의는 없고, nhtsa-etc-ev-fsa의 22쪽에 보고서가 쓴 일곱 개의 목록과 IEC 61882가 11개를 제안한다는 서술만 있다. 소프트웨어 구조에 HAZOP을 적용하는 방법은 어느 문서에도 없다.
- 소프트웨어 기본 사건에 확률을 붙이는 방법은 NASA FTH에 없다 (HECS의 0.03은 가정). GB-8719.13은 SFTA의 확장이 "computable probability"에서 멈춘다고만 적는다. 정량 분석에서 소프트웨어를 빼야 한다는 직접 서술은 NHTSA 평가 보고서 24, 29쪽 (저자와 MIL-STD-882E, DO-178C 인용)뿐이다.
- FMEA의 일반 절차 (심각도, 발생도, 검출도, RPN)는 NHTSA ETC 23쪽의 SAE J1739 7단계 요약이 전부다. 소프트웨어 FMEA의 구조 수준 적용은 GB-8719.13 부록 D가 가장 자세하다.
- 중복이 common cause에 약하다는 서술은 NASA FTH 16, 71, 72쪽과 STPA 핸드북 105쪽에 있다. 소프트웨어의 다양성 (dissimilar software)이 효과적인지는 GB-8719.13 141, 143, 144쪽이 부정적이다. 이를 뒤집는 문서는 받지 못했다.
- HSE hsg238에는 common cause나 dependent failure를 다룬 서술이 없다. NASA System Safety Handbook v1에는 77쪽과 84쪽의 짧은 서술뿐이다.
- STPA와 FTA를 함께 쓰는 방법, 예제 fta.md의 E2 (두 채널이 함께 틀림)나 E6/E7 (기능과 감시가 같은 MCU)처럼 소프트웨어 구조에서 독립성 가정을 점검하는 절차는 어느 문서에도 단계별로 적혀 있지 않다. 가장 가까운 것은 NASA GB-8719.13 7.5.3절 (independence analysis)이다.
- STPA를 ISO 26262에 맞춘 절차는 nhtsa-etc-ev-fsa가 한 예다 (사용한 변형: context 변수, 여섯 guide word). 핸드북 쪽 절차와 다르므로 두 쪽을 구별해 인용한다.
