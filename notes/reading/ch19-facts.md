# 19장 근거 문서에서 뽑은 사실 (읽기 기록)

대상: 19장 "Safety case" (plans/ch19-safety-case.md). 읽은 날: 2026-11-23.

- 쪽 칸은 PDF 파일의 몇 번째 쪽이다. 문서에 인쇄된 쪽 번호가 다르면 절 머리에 차이를 적는다.
- 인용은 줄바꿈을 합치고 따옴표와 줄표를 ASCII로 바꿨다. 인용 안의 작은따옴표는 원문의 따옴표를 그렇게 옮긴 것이다. 그 밖에는 원문 그대로다.
- 이 장의 규격 문서 (ISO 26262, UL 4600)는 받지 못했다. ISO 26262에 관한 말은 NHTSA 보고서가 옮긴 것 (2011 판 기준)과 AUTOSAR 문서의 부재 목록뿐이다. 이 파일의 NHTSA와 AUTOSAR 절은 규격 원문이 아니라 2차 자료다.
- `(기억)`은 문서에서 확인하지 못한 내용이다. 원고의 근거로 쓰지 않는다. 맨 끝의 "문서에서 찾지 못한 것" 절에만 있다.
- 원고에 쓰기 전에 그 쪽을 직접 열어 확인한다 (RULES.md 5.2절).
- GSN 문서는 문단 번호 (0:2.2, 1:2.1.4, 2:7.4.4.2 같은 것)를 쓴다. 비고 칸에 그 번호를 적었다.

## 1. gsn-standard-v3 (SCSC Assurance Case Working Group, GSN Community Standard Version 3, 2021년 5월. PDF 쪽 = 인쇄 쪽)

**1.1 개념: assurance case, argument, claim, evidence (Part 0)**

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| F19-001 | 10 | assurance case의 정의: 근거 묶음이 뒷받침하는, 이치에 맞고 설득력 있는 논증이다. 시스템, 서비스, 조직이 정해진 환경의 정해진 용도에서 뜻한 대로 동작한다는 것을 보인다. | "will operate as intended for a defined application in a defined environment" | 0:2.2. 정의 앞부분은 "A reasoned and compelling argument, supported by a body of evidence" |
| F19-002 | 10 | assurance case는 초점이 있다. safety case는 시스템이 주어진 맥락에서 받아들일 만큼 안전함을 보이고, security case는 시스템의 보안 성질을 정당화한다. | "a given system is acceptably safe in a given context" | 0:2.3. safety case를 assurance case의 한 종류로 둔 서술이다 |
| F19-003 | 10 | assurance case에서 argument는 전체 주장 (overall claim)을 세우려는 연결된 주장들의 열이다. 뒷받침하는 주장도 다시 뒷받침이 필요할 수 있다. | "a connected series of claims intended to establish an overall claim" | 0:3.1. 같은 문단은 주장이 결국 증거를 가리켜야 한다고 하고, 그 문장은 10쪽에서 11쪽으로 넘어간다 |
| F19-004 | 11 | GSN의 중심은 주장과 증거의 계층을 명시적으로 문서화하는 것이다. 맨 위의 goal이 저자가 내세우는 전체 주장이고, 충분히 뒷받침되는지 믿을지는 읽는 사람이 정한다. | "it is up to the reader to determine their belief that it is adequately supported" | 0:3.2 |
| F19-005 | 11 | 이 표준은 GSN으로 제시한 논증이 전체 주장을 뒷받침하기에 반드시 충분하다고 주장하지 않는다. GSN은 저자가 근거를 분명히 제시하게 하고 읽는 사람이 그 근거를 이해하고 따질 수 있게 해서, 주장에 대한 확신을 평가하게 한다. | "does not assert that an argument presented in GSN is necessarily sufficient" | 0:3.2 |
| F19-006 | 15 | GSN은 주장된 논증을 문서로 적는 수단일 뿐이며, GSN을 쓴다고 그 논증이 참이 되지는 않는다. | "The use of GSN itself does not establish the truth of that argument" | 0:4.12 |

**1.2 요소와 관계, 쓰는 규칙 (Part 1)**

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| F19-007 | 17 | goal은 사각형으로 그리며 논증의 일부가 되는 주장 (claim)을 나타낸다. | "presents a claim forming part of the argument" | Table 1:2-1 |
| F19-008 | 17 | strategy는 평행사변형으로 그리며 goal과 그것을 뒷받침하는 goal 사이에 있는 추론 (inference)을 서술한다. | "describes the inference that exists between a goal and its supporting goal(s)" | Table 1:2-1 |
| F19-009 | 17 | solution은 원으로 그리며 증거 항목에 대한 참조를 나타낸다. | "presents a reference to an evidence item" | Table 1:2-1 |
| F19-010 | 17 | context는 맥락 산출물을 나타낸다. 맥락 정보에 대한 참조일 수도 있고 진술일 수도 있다. | "presents a contextual artefact" | Table 1:2-1 |
| F19-011 | 17 | assumption은 타원에 'A'를 붙여 그리며 의도적으로 입증하지 않은 진술을 나타낸다. | "presents an intentionally unsubstantiated statement" | Table 1:2-1 |
| F19-012 | 18 | justification은 타원에 'J'를 붙여 그리며 근거 이유 (rationale)의 진술을 나타낸다. | "presents a statement of rationale" | Table 1:2-1 |
| F19-013 | 18 | 아직 펼치지 않은 줄기는 element의 아래 가운데에 속이 빈 마름모를 붙여 표시한다. goal과 strategy에 쓸 수 있다. undeveloped goal은 의도적으로 논증을 펼치지 않은 주장이다. | "indicates that a line of argument has not been developed" | Table 1:2-1 |
| F19-014 | 18 | SupportedBy (실선, 속이 찬 화살촉)가 허용하는 연결은 goal에서 goal, goal에서 strategy, goal에서 solution, strategy에서 goal이다. | "goal-to-goal, goal-to-strategy, goal-to-solution, strategy to goal" | Table 1:2-2. solution에서 아래로 잇는 연결이 없다 |
| F19-015 | 18 | InContextOf (속이 빈 화살촉)가 허용하는 연결은 goal이나 strategy에서 context, assumption, justification으로 가는 것이다. | "strategy-to-context, strategy-to-assumption and strategy-to-justification" | Table 1:2-2 |
| F19-016 | 19 | goal structure는 방향이 있고 고리가 없는 그래프다. 한 요소가 부모와 자식을 여럿 가질 수 있지만, goal이 직접 또는 간접으로 자기 자신을 뒷받침하게 만들 수 없다. | "A GSN goal structure is a directed acyclic graph" | 1:2.2.2 |
| F19-017 | 19 | G1 아래 G2, G3을 두는 것은, G2와 G3이 참이면 G1이 참임을 세우기에 충분하다고 주장하는 것이다. 이 추론은 두 SupportedBy 관계가 나눌 수 없게 합쳐진 것이다. | "this is sufficient to establish that the claim in Goal G1 is true" | 1:2.2.4 |
| F19-018 | 20 | strategy를 여럿 두면 각 strategy 아래 goal 묶음이 각자 기여하고, 이 줄기들이 모두 있어야 부모 goal이 뒷받침된다. | "Both lines of argument are required to support goal G1" | 1:2.2.6 |
| F19-019 | 21 | goal 아래 solution을 두면, 그 solution이 가리키는 증거가 goal의 주장이 참임을 세우기에 충분하다고 주장하는 것이다. | "is sufficient to establish the truth of the claim made in the goal" | 1:2.2.8 |
| F19-020 | 22 | 주장은 정해진 context에서만 참이라고 내세울 수 있다. context는 주장의 범위를 정의하거나 제한한다. | "Claims can only be asserted to be true in a specified context" | 1:2.2.10, 1:2.2.11 |
| F19-021 | 22 | context는 context가 붙은 요소를 뒷받침하는 논증 전체에 이어진 것으로 본다. 그래서 아래 논증에서 다시 적지 않아도 된다. 또 아래 논증은 그 context와 모순되거나 그것을 훼손해서는 안 된다. | "nothing in the supporting argument for the goal" | 1:2.2.11. 인용 뒤에 "to which the context is applied should contradict or undermine"가 이어진다 |
| F19-022 | 23 | assumption은 입증하지 않은 진술이다. goal에 붙인 assumption은 관련된 논증 전체에 이어진 것으로 본다. | "An assumption is an unsubstantiated statement" | 1:2.2.13. goal에 붙인 assumption의 뜻은 1:2.2.12에서 주장이 그 assumption이 참인 맥락에서 내세워진다고 한다 |
| F19-023 | 23 | justification은 주장의 뜻을 바꾸지 않고 그 주장을 넣은 이유나 표현의 이유를 준다. assumption과 달리 아래 논증 전체에 이어지지 않고 붙은 요소에만 적용된다. 같은 이유가 다른 곳에 필요하면 다시 적거나 다시 이어야 한다. | "they are local to the element to which they are linked" | 1:2.2.14 |
| F19-024 | 25 | goal 하나는 명사구 + 동사구 문장의 명제 하나를 담는다. | "expressed as a proposition in the form of a noun-phrase + verb-phrase sentence" | 1:2.3.2. 문서는 이 규칙을 "shall"로 쓴다 |

**1.3 만드는 순서: 위에서 아래로 여섯 단계 (2:3)**

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| F19-025 | 60 | 나머지 다섯 단계: goal을 서술하는 근거 (basis)를 정의한다, goal을 뒷받침할 strategy를 찾는다, strategy를 서술하는 근거를 정의한다, strategy를 펼친다 (새 goal이 나오면 1단계로 돌아간다), 기본 solution을 찾는다. | "Define the basis on which the goals are stated" | 2:3.1.1. 순서의 마지막은 "Identify the basic solution" |
| F19-026 | 61 | 1단계: 맨 위의 주장은 알맞은 수준의 구체성으로 적어야 한다. 더 근본적인 목적을 건너뛰어 주장하면 읽는 사람이 너무 낮은 수준에서 결론을 내리게 되고, 근본 목적에서 최상위 주장이 도출되는 과정을 보일 수 없다. | "jumps ahead of a more fundamental objective" | 2:3.2.1. 예는 "Press is acceptably safe to operate within CCC Whatford Plant" |
| F19-027 | 63 | 최상위 goal의 'safe'는 따로 정의하지 않아도 된다. 'safe'의 뜻은 그 goal을 뒷받침하려고 내놓는 논증이 정한다. 예는 "System X is safe"이고, 'System X'는 context로 가리킨다. | "defined by whatever argument is put forward in support of this top-level goal" | 2:3.3.5, 2:3.3.7 |
| F19-028 | 63 | 대표적인 strategy는 divide and conquer이다. 높은 수준의 goal을 더 작은 goal로 나누어, 그것들이 모두 만족되면 원래 goal을 뒷받침하기에 충분하게 한다. | "the satisfaction of all of which would be sufficient to support the original goal" | 2:3.4.2. 예는 "System is SAFE"를 서브시스템 A, B, C로 나누는 것 |
| F19-029 | 65 | 예의 최상위 주장 아래에 strategy가 둘 있다: 알려진 운전 위험을 모두 다루는 논증, 해당하는 모든 안전 규격과 규정을 준수한다는 논증. 규정 준수가 논증 줄기 하나로 나란히 놓인다. | "Argument of compliance with all applicable safety standards" | 2:3.4.5, Figure 2:3-7 |
| F19-030 | 67 | 예에서 "모든 규격과 규정을 준수한다"는 strategy는, 대상 규격의 목록을 context로 두고 규격마다 준수한다는 주장 (goal)을 내는 것으로 펼쳐진다. | "putting forward a claim of compliance for each identified standard" | 2:3.6.5. goal 하나가 다른 부모 goal의 논증에도 들 수 있다 (2:3.6.4) |
| F19-031 | 68 | 6단계: 주장이 충분히 기본적인 수준이 되어 더 펼치거나 설명할 필요가 없으면 solution으로 증거를 가리킨다. | "Eventually, claims will be expressed at a sufficiently basic level" | 2:3.7.1. 예는 "Motor / Clutch / Drive Belts surrounded with safety cage"를 inspection report로 닫는 것 |
| F19-032 | 70 | 위에서 아래로 펼치다 보면 닫으려는 주장의 증거가 없거나, 기존 증거가 바닥의 주장을 충분히 덮지 못하는 일이 자주 생긴다. | "the existing evidence does not 'cover' the lowest-level claim adequately" | 2:3.8.1. 문서는 덮지 못하는 쪽이 더 흔하다고 쓴다 |
| F19-033 | 70 | 증거를 더 찾아도 안 되면 논증을 고친다. 증거에서 말할 수 있는 주장으로 solution 바로 위의 주장을 다시 쓰고 (덜 구체적으로 또는 범위를 좁혀), 위로 올라가며 그 주장에 기댄 모든 상위 주장을 다시 본다. 다시 쓰는 것은 주장을 약하게 하는 것이다. | "Rephrasing of this kind implies a weakening of the claim made" | 2:3.8.1. 그 줄기 전체가 약해질 수 있다고 같은 문단이 쓴다 |

**1.4 흔한 오류: 말의 오류와 구조의 오류 (2:5, 2:6)**

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| F19-034 | 81 | 'essay in the box': goal, strategy, solution 하나에 논증의 요약을 길게 쓰는 경향이다. 그런 글에는 구조 안에서 뒷받침하거나 맥락을 붙이거나 펼칠 수 없는 주장이 여럿 들어 있다. | "the resulting 'essay in a box' will typically contain several claims" | 2:5.3.1 |
| F19-035 | 82 | goal에는 주장만, solution에는 증거에 대한 참조만, strategy에는 논증 접근의 요약만 쓴다. goal이 논증의 일을 하게 하지 말고, 상하 goal의 관계가 불분명하면 strategy를 끼운다. | "Goals should only contain claims, solutions should only refer to evidence" | 2:5.3.2. 인용 뒤에 "and strategies should only summarise the argument approach"가 이어진다 |
| F19-036 | 83 | 뜻이 정의되지 않으면 거의 의미 없는 말의 목록: 'abnormal', 'appropriate', 'approximate', 'effective', 'early', 'easy', 'envelope', 'flexible', 'friendly', 'generally', 'late', 'normal', 'often', 'timely'. 이런 말을 쓰면 정확한 뜻을 검증 가능한 말로 밝히는 context를 붙인다. | "a context should be added, specifying the precise meaning, in verifiable terms" | 2:5.5.1 |
| F19-037 | 84 | 'jumping ahead': 논증의 전체 목적이 아니라 그 목적을 뒷받침하는 주장을 최상위 주장으로 적는 것이다. 예: "위험 X가 줄었다" 대신 "기계에 interlock을 달았다". 그러면 완화 전략의 상위 정당화가 논증에서 빠진다. | "stating a claim which supports the overall objective of the argument" | 2:6.1.1. 문서의 판단: 위험이 줄었음을 읽는 사람이 아는 것이 어떻게 줄였는지보다 중요하다 |
| F19-038 | 85 | context 오용 (1): 주장의 타당성을 뒷받침하는 정보는 context가 아니라 증거이므로 solution으로 나타낸다. 예: 고장률 주장에 붙인 fault tree. | "should be represented using a GSN solution element" | 2:6.2.1, 2:6.2.2 |
| F19-039 | 86 | strategy 오용 (2): strategy가 하중을 받는 (load-bearing) 요소가 되어 실제 주장을 담는 것이다. strategy에 든 주장은 뒤따르는 goal structure로 뒷받침되지 못해 펼쳐지지 않은 채 인정받지 못하고 남는다. | "will therefore remain undeveloped, and unacknowledged, in the argument" | 2:6.3.2 |
| F19-040 | 86 | 'leaps of faith': 주장과 주장 사이, 또는 주장과 증거 사이의 귀납적 도약이 너무 크다. 읽는 사람이 흐름을 잃는다. 수학자가 증명에서 풀이 과정을 생략하는 것에 비긴다. | "too large an 'inductive leap' between claims" | 2:6.4.1, 2:6.4.2. 예는 "Press is acceptably safe"에서 "surrounded with safety cage"로 바로 가는 것 |
| F19-041 | 87 | 둘째 도약: goal을 증거로 너무 일찍 닫는 것이다. 예는 "Requirement 6.3 (Defence in Depth) has been met"를 "Plant design"이라는 solution에 바로 잇는 것이다. | "close out' a goal prematurely by direct reference to evidence" | 2:6.4.4. 원문은 'close out' 앞에 작은따옴표가 있다. 인용은 그 앞의 따옴표를 뺐다 |

**1.5 goal structure의 평가: 단계별 검토 (2:7)**

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| F19-042 | 89 | 위험을 줄이려면 프로젝트 수명 주기 내내 단계별로 검토하는 것이 좋다. 논증과 증거의 문제를 가능한 한 일찍 찾는다. 예: 논증의 strategy를 일찍 검토한다. | "staged review throughout the project lifecycle is desirable" | 2:7.2.1 |
| F19-043 | 90 | 검토는 적어도 네 단계다: 논증 이해 (comprehension), 형식 점검 (well-formedness), 표현의 충분성 점검 (expressive sufficiency), 논증의 비판과 반박 (criticism and defeat). | "Argument comprehension" | 2:7.4.2. 인용은 첫째 단계의 이름이다. 그림 2:7-1은 네 단계를 화살표로 잇는다 |
| F19-044 | 91 | 1단계 (이해): 핵심 주장, strategy, assumption, context, 증거를 가려낸다. GSN으로 적은 논증이면 표기가 Part 1의 규범대로인지 점검한다 (예: strategy 문구가 중간 주장이 아니라 논증 접근을 말하는가). 이 단계는 GSN으로 구성했으나 유효한 주장이나 논증이 없는 피상적 논증을 걸러낸다. | "weed out superficial arguments" | 2:7.4.1.1 |
| F19-045 | 91 | 2단계 (형식 점검): 구조의 오류를 찾는다. 순환 논증은 거의 받아들일 수 없다. 뒷받침하는 논증이나 증거가 없는 주장과, 논증에서 역할이 불분명한 증거도 찾는다. | "evidence whose role in the argument is unclear" | 2:7.4.2.1 |
| F19-046 | 92 | 4단계 (비판과 반박): 보증 논증은 대개 귀납적이다. 결론의 절대적 진리는 확실히 세울 수 없고, 전제의 개연적 진리가 결론으로 전해진다. 전제를 합친 것이 결론을 뒷받침하기에 충분한가를 본다. | "The absolute truth of the conclusion cannot be established with certainty" | 2:7.4.4.1 |
| F19-047 | 92 | 충분성의 속성 여섯: coverage (덮는 범위), dependency (의존), definition (정의), directness (직접성), relevance (관련성), robustness (견고함). | "Coverage - to what extent does the argument and/or evidence presented" | 2:7.4.4.2. 인용 뒤에 "cover the conclusion?"이 이어진다. 속성 이름은 첫 낱말이다 |
| F19-048 | 92 | coverage: 모든 hazard에 관한 결론을 내리면서 알려진 hazard의 일부에만 증거를 대면 coverage 문제가 있다. | "evidence only for a subset of the known hazards" | 2:7.4.4.2 |
| F19-049 | 92 | dependency: 여러 증거나 논증 줄기가 서로 독립이 아니면 확신이 기대만큼 높지 않다. 예: 증거 둘이 모두 같은 결함 있는 시스템 모델에서 출발한다. | "a common, flawed model of the system" | 2:7.4.4.2 |
| F19-050 | 93 | definition: 논증이나 증거를 지나치게 제한하거나 덜 제한하는 것은 좋지 않다. 예: 좁게 정한 운영 맥락에서만 안전하다 ("화요일에는 안전하다")는 논증은 운전의 승인에는 불충분할 수 있다. | "The system is safe on Tuesdays" | 2:7.4.4.2. 문장이 92쪽에서 93쪽으로 넘어간다 |
| F19-051 | 93 | directness: 특정한 제품 주장에 대해 과정 증거는 '간접적'으로 볼 수 있다. 간접 논증은 그것만으로는 설득력이 없다고 여겨지는 일이 많다. | "Indirect arguments are often considered unconvincing in isolation" | 2:7.4.4.2 |
| F19-052 | 93 | relevance: 증거나 논증이 결론과 관련이 있는가. 예: 앞선 버전의 시험 증거로 나중 버전이 요구를 충족한다고 주장하면 관련성 문제가 생길 수 있다. | "test evidence concerning a previous version" | 2:7.4.4.2 |
| F19-053 | 93 | robustness: 증거와 주장의 변화에 논증이 얼마나 민감한가. 목표를 겨우 충족한 논증보다 여유를 두고 넘긴 논증이 보증이 더 크다. 비관적인 평가로 요구를 (겨우) 충족한 것이 낙관적 평가의 큰 여유보다 설득력 있을 수 있다. | "an objective is considered to be 'just' satisfied" | 2:7.4.4.2 |
| F19-054 | 94 | 5단계 (증거의 감사): 논증이 가리킨 증거가 실제로 있고 주장을 실제로 뒷받침하는지 검토자가 확인한다. 예: "모든 hazard가 hazard log에서 닫혔다"는 주장은 hazard log를 보고 참임을 확인해야 한다. | "actually exist and that they actually support the claims of the case" | 2:7.4.5.1. 문서는 이 5단계를 4단계 뒤에 번호 5로 적는다 (앞의 "적어도 네 단계"와 달리) |
| F19-055 | 94 | 증거의 integrity를 보는 요소: 증거에 든 오류의 수 ('buggy-ness'), 능력 있는 인력이 만들고 검토했는가, 손으로 만든 증거라면 인력의 경험과 능력, 도구가 만든 증거라면 도구의 qualification. | "The more mistakes revealed in evidence during a review" | 2:7.4.5.3. 검토에서 드러난 오류가 많을수록 검토자의 확신이 줄어든다 |
| F19-056 | 94 | 좋은 assurance case는 논증과 증거를 선택해서 제시할 수 없다. 제시하지 않은 사실이 논증에 도전할 수 있으므로 그런 사실이 있는지 살필 준비를 해야 한다. | "cannot be selective in the arguments and evidence it presents" | 2:7.4.5.4 |
| F19-057 | 95 | rebuttal (반박)은 assurance case의 결론에 반하는 결론에 이를 증거가 있는 경우다. 예: "고장 모드 X는 일어난 적이 없다"는 주장에 대한 반박은 사고 보고서 같은 증거로 뒷받침한 "고장 모드 X가 일어났다"이다. | "evidence exists that allows you to reach a conclusion counter to one presented" | 2:7.4.5.6 |
| F19-058 | 95 | undercutting (밑동 끊기)은 논증의 추론에 도전하는 추가 논증이나 증거를 내는 경우다. 예: "차가 시속 80마일로 달린다"에서 "운전자가 속도 제한을 어긴다"로 가는 추론에 "사유지 도로다"라는 사실이 도전한다. 전제가 참인데 결론이 거짓인 상황이 있는지 검토 중에 따져 본다. | "additional arguments and evidence are introduced which challenge the reasoning" | 2:7.4.5.7 |

**1.6 dialectic, defeater, confidence argument, module (확장)**

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| F19-059 | 115 | dialectic 논증은 논증의 어느 부분에든 'defeater'를 적용해 도전하는 것이다. rebuttal은 논증의 일부나 전부에 도전하는 뒷받침된 논증이고, undercutting은 도전하는 추가 사실이다. | "Such challenges to the argument are achieved by applying 'defeaters'" | 2:11.2.3. 쓰임이 95쪽의 정의와 다르다 (95쪽 각주 4가 이를 인정한다) |
| F19-060 | 46 | Assurance Claim Point (ACP)는 위험 논증 (risk argument)의 단언에 confidence argument (확신을 뒷받침하는 논증)가 딸려 있음을 나타내는 표시다. ACP마다 그에 대응하는 confidence argument가 있어야 한다. | "For each ACP there should exist a corresponding confidence argument" | 1:5.1.1 |
| F19-061 | 112 | insulin pump 예에서 confidence argument는 남은 assurance deficit (보증의 부족)를 들고, 부족마다 반증 (counter evidence)과 민감도 (sensitivity)를 따진다. 신뢰성 (trustworthiness)은 산출물의 성질이고 적절성 (appropriateness)은 context와 goal 사이 관계의 성질이다. | "For each deficit, counter evidence and sensitivity are considered" | 2:10.2.3. 적절성은 113쪽 2:10.2.4. 예는 단순화한 가상의 사례라고 밝힌다 |

## 2. nhtsa-safety-standards-assessment (Volpe 국가 교통 시스템 센터, Assessment of Safety Standards for Automotive Electronic Control Systems, DOT HS 812 285, 2016년 6월. PDF 쪽 = 인쇄 쪽 + 10. 비교한 ISO 26262는 2011년 11월의 첫 판 (14쪽, 참고 문헌 [7] 36쪽에는 FDIS 2011))

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| F19-062 | 34 | 보고서는 ISO 26262의 접근이 DO-178C와 매우 비슷하다고 쓴다. 이 규격은 표준이 정한 시스템 안전 공학 과정의 모든 work product를 모아 'safety case'를 이루게 하고, 이 safety case로 ISO 26262 과정을 따랐음을 보인다. | "ISO 26262's approach is very similar to DO-178C" | 3.11. 이 보고서가 본 판은 2011 판이다 |
| F19-063 | 34 | 보고서의 비판: ISO 26262가 정의한 'safety case'는 그 맥락에서는 알맞지만, 이 용어를 넓은 뜻으로 쓰면 오해를 부를 수 있다. 시스템 안전 공학에서 safety case는 흔히 시스템이 주어진 운영 맥락에서 받아들일 만큼 안전하다는 정량적 논증 (quantitative argument)을 가리킨다. | "can lead to misunderstandings" | 3.11. 원문은 'quantitative'라고 쓴다. 다른 문서는 그렇게 한정하지 않는다 (F19-002). 출처는 Kelly 1998 [43]이다 |
| F19-064 | 34 | 보고서에 따르면 ISO 26262 Part 2 Table 1은 ASIL에 따라 confirmation review를 요구하며, 항목 개발자, 프로젝트 관리, work product의 저자로부터의 독립성을 요구한다. | "independence with regard to the developers of the item" | 3.11. 요구의 내용은 보고서가 옮긴 것이다. 규격 원문은 없다 |
| F19-065 | 34 | 개발 팀은 보통 안전 목표를 달성했다는 강한 증거를 제시한다 (확증 편향은 인간의 본성). 그 증거 앞에서 기술에 깊이 파묻히지 않은 독립 검토자는 'unknown-unknowns'를 찾지 못할 수 있다. | "truly independent reviewers may not be able to" | 3.11. 인용 뒤에 "find the unknown-unknowns"가 이어진다 |

## 3. b737max-jatr (Joint Authorities Technical Review, Boeing 737 MAX Flight Control System: Observations, Findings, and Recommendations, 2019년 10월. PDF 쪽 = 인쇄 쪽 + 20)

이 문서는 'safety case'라는 말을 이 쪽들에서 쓰지 않는다. 아래는 규정 준수 중심의 개발과 증명이 안전 논증을 놓친 것에 관한 서술이다.

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| F19-066 | 50 | R6: JATR은 FAA가 안전한 제품을 만드는 데 주된 초점을 두는 안전 문화를 촉진하고, 그런 제품이 결과로 인증 요구를 충족하게 하라고 권고한다. | "primary focus on the creation of safe products" | R6 |
| F19-067 | 50 | R6.1: FAA는 신청자가 준수만을 위해 설계하지 말고 안전을 위한 기본 원칙을 따르도록 권장해야 한다. 여기에 hazard의 제거와 설계 기능, 경고, 절차의 사용이 들어간다. | "not to design only for compliance" | R6.1 |
| F19-068 | 51 | F6.1-B: 조종사 조치를 hazard 제거나 설계 기능, 경고를 따져 보기 전에 주된 완화 수단으로 쓴 것은 Boeing 자신의 안전 설계 절차 지침에도 맞지 않는다. | "is not in accordance with Boeing's process instructions for safe design" | F6.1-B |
| F19-069 | 52 | F6.5-A: MCAS를 하나의 완전한 기능으로 보는 통합된 SSA (system safety assessment)를 하지 않았다. 분석이 여러 문서로 쪼개졌고 B737 NG의 SSA 일부를 충분한 평가 없이 MAX에 다시 썼다. | "reused in the B737 MAX without sufficient evaluation" | F6.5-A |
| F19-070 | 52 | F6.6-A: FHA 보고서가 설계를 이끄는 것이 아니라 이미 정해진 설계를 문서로 적는 데 쓰였다는 인식이 있다. 설계에 의한 완화를 경고나 훈련과 절차보다 우선해야 하는데, 현재 구성을 기록하면서 훈련과 절차로 충분하다고 결론지었다. | "they are used to document the design as already defined" | F6.6-A. 원문은 "there is a perception that"로 시작하는 서술이다 |
| F19-071 | 52 | R6.7: FAA는 신청자가 설계 조직에서 독립한 시스템 안전 기능을 두도록 권장해야 한다. 그 기능은 항공기 안전을 독립적으로 평가하고 설계 세부에 영향을 줄 권한이 있어야 한다. | "independent from the design organization" | R6.7. R6의 요약에도 같은 말이 있다 |
| F19-072 | 53 | O6.7-A: JATR은 Boeing에 시스템 안전 분석을 조정하는 독립 안전 그룹이 있는지 확인하지 못했다. 시스템 팀이 설계와 안전 평가를 모두 한다. | "Each system team conducts both the design and related safety assessments" | O6.7-A |
| F19-073 | 55 | R6.12: FAA는 신청자가 한 가정의 타당성을 묻고, 모든 그런 가정에 실질적인 뒷받침을 요구하는 관행을 만들어야 한다. | "require substantive support for all such assumptions" | R6.12 |
| F19-074 | 55 | F6.12-A: Boeing이 NG와의 유사성을 근거로 예외를 구한 이유는 MAX가 NG의 대체이고 조종사가 NG 경험자라는 가정에서 나왔다. 이 가정은 근거가 없었다. F6.12-B: 훈련받은 승무원의 대응에 관한 기본 가정이 사고 두 건에서 성립하지 않은 것으로 보인다 (예비 정보 기준). | "These assumptions were not warranted" | F6.12-A. F6.12-B의 문장은 "did not appear to hold in the two accident cases" |

## 4. nasa-gb-8719-13 (NASA, NASA Software Safety Guidebook, NASA-GB-8719.13, 2004. PDF 쪽 = 인쇄 쪽 + 1)

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| F19-075 | 109 | 6.4절은 요구사항 관리를 설명하며, 그 이점의 하나로 규정이나 계약의 준수를 든다. 요구사항을 관리하면 규제 기관에 'safety case'를 제시해야 할 때도 도움이 된다. | "you must present a 'safety case' to a regulatory body" | 6.4. 문장은 이 지침서가 요구사항 관리의 이점 목록에서 든 것이다 |
| F19-076 | 109 | 이 지침서가 괄호로 준 safety case의 정의: 시스템이 수명 동안 주어진 응용과 환경에서 적절히 안전하다는 입증 가능하고 타당한 논증을 주는, 문서화된 증거의 묶음. 'Safety cases are required by the FAA'라고 쓴다. | "a documented body of evidence that provides a demonstrable and valid argument" | 6.4. 정의의 나머지: "adequately safe for a given application and environment over its lifetime" |

## 5. nasa-system-safety-handbook-v1 (NASA, NASA System Safety Handbook Volume 1, NASA/SP-2010-580, 2011. PDF 쪽 = 인쇄 쪽 + 16)

받은 문서에 'safety case'를 따로 설명하는 절이 있다 (2.3.3과 5장). 이 책은 이를 risk-informed safety case (RISC)라 부른다. 'defeater'라는 낱말은 이 문서에 없다. 5.5절의 평가는 아래 F19-090 이하에 있다.

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| F19-077 | 29 | RISC는 시스템의 안전 목표가 충족됨을 주요 단계 (KDP 같은 milestone)에서 의사결정자에게 보이고 전달하는 수단이다. 근거 묶음이 뒷받침하는 구조화된 논증이다. | "a structured argument, supported by a body of evidence" | 2.3.3. 정의는 [15]를 옮긴 것이라고 각주 8이 쓴다 |
| F19-078 | 29 | 핵심 개념은 '사례 (case)'다. 특정 안전 주장에 대해 설득력 있는 논증과 증거로 이루어진다. 반대로 완화 계획으로 다룬 '위험'의 임시 목록은 safety case가 아니다. | "that have been addressed through a mitigation plan is not a safety case" | 2.3.3 |
| F19-079 | 29 | Holloway의 말을 옮긴다: 증거를 뒷받침하는 논증이 부족한 논증은 설득력이 없고, 논증 없는 증거 묶음은 설명되지 않는다. | "A body of evidence without an argument is unexplained" | 2.3.3 |
| F19-080 | 29 | RISC의 요소는 셋이다: 시스템에 관한 명시적 안전 주장 (claim), 주장을 뒷받침하는 증거, 주장과 증거를 잇고 논리적으로 타당한 추론 규칙을 쓰는 구조화된 안전 논증. | "Structured safety arguments that link claims to evidence" | 2.3.3 |
| F19-081 | 30 | RISC의 평가는 감독 기관이 시스템의 적절한 안전에 대한 합리적 보증을 얻는 수단이다. 법적 사건처럼 '증명 책임'은 RISC를 만든 쪽에 있고, 비판적이고 회의적인 승인 기관에 안전의 사례를 내세운다. | "the 'burden of proof' is on the RISC developer to make the case for safety" | 2.3.3 |
| F19-082 | 85 | RISC의 타당성은 정해진 환경의 정해진 응용에 조건부다. RISC는 시스템이 안전하다고 주장하는 운영 범위 (operational envelope)를 분명히 정의해야 하고, 그 범위를 벗어나면 주장이 더는 유효하지 않을 수 있다. | "the RISC must clearly define the operational envelope" | 5.1 |
| F19-083 | 85 | RISC는 그것을 만든 결정의 맥락 (예: milestone 검토)에 한정된다. 시스템은 수명 중 RISC를 여럿 가질 수 있다. | "The RISC is specific to the decision context" | 5.1 |
| F19-084 | 86 | RISC를 만드는 일은 넷이다: 명시적 주장, 주장을 뒷받침하는 증거, 주장과 증거를 잇는 안전 논증, 논증의 밑에 있는 가정과 판단을 분명히 하는 것. | "Making clear the assumptions and judgments underlying the arguments" | 5.1 |
| F19-085 | 87 | 증거는 사실 (과학 원리, 경험 자료), 명시적 가정, 하위 주장 (sub-claim)일 수 있다. 각 하위 주장은 그 자체로 주장이고 논증으로 더 펼친다. | "explicit assumptions, or sub-claims" | 5.2 |
| F19-086 | 87 | 같은 주장을 독립인 논증 둘이 뒷받침하게 하면 주장이 견고해진다. 논증 하나의 결함을 견딜 수 있다. | "it can tolerate flaws in a single argument" | 5.2, Figure 5-2 |
| F19-087 | 89 | 안전 논증의 종류는 결정론적, 확률적, 정성적이다. 정성적 논증은 바라는 속성과 간접적으로 이어지는 규칙의 준수 (예: 산업 표준의 준수, 인력의 기술과 경험의 인정)이다. 신뢰도 같은 주장은 통계 논증을, 유지보수성 같은 주장은 정성적 논증을 쓸 수 있다. | "Compliance with rules that have an indirect link to the desired attributes" | 5.2.2. 결정론적 논증의 예에 "demonstration of compliance to a specification or safety requirement"가 있다 |
| F19-088 | 89 | 역할로 나누면 직접 (demonstrative) 논증은 증거로 특정 목표가 달성되었음을 보인다 ("증거가 주어지면 목표가 달성되었다"). | "Given the evidence, the objective has been met" | 5.2.2 |
| F19-089 | 90 | 간접 (indirect, backing, validating) 논증은 직접 논증에 쓴 증거가 믿을 만함을 보인다. 증거의 질, 적용 가능성, 실무자의 능력 같은 문제를 다룬다. | "shows that the evidence used in a direct argument is trustworthy" | 5.2.2 |
| F19-090 | 102 | RISC 평가: 의사결정자는 RISC를 받는 것으로 끝이 아니라 주장을 받아들이거나 거절해야 한다. 주장마다 의사결정자의 일은 (1) 뒷받침하는 기술적 근거 (증거)를 이해하고, (2) 그 근거의 타당성을 따져 묻고, (3) 주장의 적절성을 판단하는 것이다. | "Understand the technical basis" | 5.5. 인용은 1번 항목의 첫머리다 |
| F19-091 | 102 | 평가자의 점검표는 RISC의 구조를 흉내 내지 않고 RISC와 따로 짜야 한다. 그래야 RISC 제공자의 선입견과 가정에 얽매이지 않는다. 독립된 점검표는 일반적으로 쓸 수 있는 반면 RISC는 응용에 따라 다르다. | "The checklist should not mimic the structure of the RISC" | 5.5 |

## 6. autosar-safety-measures (AUTOSAR, Overview of Functional Safety Measures in AUTOSAR, AUTOSAR CP R25-11. PDF 쪽 = 인쇄 쪽)

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| F19-092 | 46 | AUTOSAR가 강제하지도 제공하지도 않는 기능안전 조치의 목록에 'No AUTOSAR safety case', 'No confirmation measures', 'No functional safety audits'가 있다. 같은 목록에 'No overall safety concept', 'No ASIL identification', 'No dependent failure analysis'도 있다. | "No AUTOSAR safety case" | 3.4절. 목록이 완전하다는 뜻은 아니라고 문서가 밝힌다 ("This list does not imply completeness") |

## 7. hse-hsg238 (HSE, Out of control: Why control systems go wrong and how to prevent failure, HSG238, 2003판. PDF 쪽 = 인쇄 쪽)

'safety case'라는 말은 이 문서에서 찾지 못했다. functional safety assessment에 관한 짧은 서술만 있다.

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| F19-093 | 43 | functional safety assessment는 프로젝트 팀에서 독립한 인력이 하는 기술 평가이며, 증거에 근거해 기능안전이 달성되었는지 결정한다. | "carried out by personnel who are independent of the project team" | 부록 2 문단 33 |
| F19-094 | 50 | 용어집의 정의: functional safety assessment는 하나 이상의 안전 관련 시스템이 달성한 기능안전을 판단하는, 증거에 근거한 조사다. | "Investigation, based on evidence, to judge the" | 인용 뒤에 "functional safety achieved"가 이어진다 |

## 8. ifa-report-2-2017e (IFA, Functional safety of machine controls, IFA Report 2/2017e. PDF 쪽 = 인쇄 쪽)

'safety case'라는 말과 독립된 평가를 따로 다룬 절은 찾지 못했다. 7.1.1절에 verification과 validation의 독립성에 관한 두 문장이 있다.

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| F19-095 | 86 | verification과 validation을 맡은 인력은 가능하면 안전 관련 부분의 설계 과정에 참여하지 않아야 한다. 설계 부서 아래에 있지 않은 다른 사람, 부서, 기관이 맡을 수 있다. | "able to act independently of the design and development process" | 7.1.1. 이 문서의 대상은 EN ISO 13849-1 (기계 제어)이다 |
| F19-096 | 86 | 독립성의 수준은 위험, 곧 요구되는 Performance Level (PLr)에 맞춘다. | "The level of independence should be commensurate with the risk" | 7.1.1 |

## 문서에서 찾지 못한 것

받은 문서에서 확인하지 못한 항목이다. 아래의 `(기억)`은 원고의 근거가 아니다. 원고에 쓰려면 다른 공개 문서를 찾거나 `(2차 자료)`로 밝히거나 쓰지 않는다.

- ISO 26262:2018의 confirmation review, functional safety audit, functional safety assessment의 요구와 각각의 독립성 수준 (I0 - I3 같은 구분). NHTSA 보고서 (F19-064)는 2011 판의 Part 2 Table 1이 ASIL에 따라 confirmation review의 독립성을 요구한다고만 옮긴다. 어느 ASIL에서 어떤 수준인지는 보고서에 없다 (기억: 2018 판은 confirmation measure를 세 가지로 나누고, 독립성 수준을 I0 - I3으로 표기한다).
- ISO 26262의 safety case 요구의 내용. NHTSA (F19-062)는 work product를 모아 safety case를 이룬다고만 한다. 2018 판에서 safety case가 어떤 구성 (논증, 근거, 독립 평가의 판정)으로 정의되는지는 확인하지 못했다 (기억).
- UL 4600. 자율주행 시스템의 safety case를 요구하는 규격이며 GSN과 같은 구조를 쓸 수 있다고 알려져 있으나 (기억), 받은 문서에 없다. 이 장이 UL 4600을 들면 `(2차 자료)`로 밝히거나 쓰지 않는다.
- 자동차 안전 논증의 GSN 예. GSN 표준의 예는 가상의 press 공장 (2:3)과 insulin pump (2:10)이다. 자동차 예는 없다. 계획이 적은 insulin pump 예의 쪽 (111 - 113)은 이 파일에서 112쪽의 확신 논증 서술만 옮겼다.
- 'defeater'를 NASA 문서에서 쓰는지. 받은 NASA System Safety Handbook Volume 1에는 이 낱말이 없다 (rebuttal, undercutting, defeater는 GSN 표준에만 있다). 이 handbook이 예고한 2권 (safety case 예제)은 받지 못했다.
- JATR의 R6 - R7 쪽은 safety case라는 말을 쓰지 않는다. 규정 준수만으로 안전하다고 보지 않는 서술은 F19-066 - F19-074에 있으나, 이를 'safety case의 실패'라고 부르는 것은 책의 해석이지 이 문서의 말이 아니다.
- HSE와 IFA 문서는 safety case라는 말을 쓰지 않는다 (F19-093 - F19-096의 서술이 전부).
- GSN 표준의 safety case를 만드는 시점 (처음부터 vs 마지막)에 관한 직접 서술. 2:7.2.1은 검토를 일찍 하라고 하고 (F19-042), 2:3.8.1은 위에서 아래로 만들다가 증거가 모자라면 주장을 약하게 고친다고 한다 (F19-032, F19-033). 'safety case는 마지막에 쓰는 보고서가 아니다'라는 문장 자체는 문서에 없다. GSN 2:4의 아래에서 위로 만드는 방법 (bottom-up)은 이번에 읽지 않았다.
