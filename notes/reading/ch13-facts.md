# 13장 근거 문서에서 뽑은 사실 (읽기 기록)

대상: 13장 "Coding for safety" (plans/ch13-coding.md). 읽은 날: 2026-11-23.

- 쪽 칸은 PDF 파일의 몇 번째 쪽이다. 문서에 인쇄된 쪽 번호가 다르면 절 머리에 차이를 적는다.
- 인용은 줄바꿈을 합치고 따옴표와 줄표를 ASCII로 바꿨다. 그 밖에는 원문 그대로다.
- 이 장의 규격 문서 (ISO 26262, IEC 61508)와 MISRA C의 규칙 문서는 받지 못했다. MISRA Compliance:2020은 준수 절차 문서이며, 규칙의 내용은 이 파일에 없다. 예시로 든 규칙 번호는 문서가 쓴 대로만 옮겼다.
- `(기억)`은 문서에서 확인하지 못한 내용이다. 원고의 근거로 쓰지 않는다. 이 파일에는 거의 없다.
- 원고에 쓰기 전에 그 쪽을 직접 열어 확인한다 (RULES.md 5.2절).

## 1. misra-compliance-2020 (MISRA, MISRA Compliance:2020, 2020. PDF 쪽 = 인쇄 쪽 + 8)

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| F13-001 | 9 | "MISRA를 준수한다"는 주장이 뜻을 가지려면 다섯 가지를 밝혀야 한다: 규율 있는 개발 과정, 어떤 guideline을 적용하는가, 강제 방법의 효과, deviation의 범위, 프로젝트 밖에서 개발된 부품의 상태. | "The extent of any deviations from the guidelines" | 다섯 항목 중 하나를 인용했다. 문서 전체가 이 다섯 항목을 풀어 쓴 것이다 |
| F13-002 | 9 | 어떤 상황에서는 guideline을 지키는 것이 비합리적이거나 불가능하므로 벗어나야 한다고 인정한다. 벗어날 자유는 준수 주장을 반드시 해치지는 않지만 큰 책임이 따른다. | "it does carry with it great responsibility" | 규율 없는 과정에서는 그 자유가 남용되기 쉽다고 같은 쪽이 쓴다 |
| F13-003 | 9 | 신뢰할 만한 준수 주장은 이 문서의 원칙을 만족하는 과정에서 개발된 코드에만 할 수 있다. 이 문서는 이전 MISRA 문서들이 실었던 준수, deviation, 과정 요건을 대체한다. | "supersedes the compliance, deviation and process" | 인용 뒤에 "requirements published previously"가 이어진다 |
| F13-004 | 5 | 서문은 앞으로 나오는 모든 MISRA guideline 문서가 MISRA Compliance의 사용을 의무로 한다고 적는다. | "all future releases of MISRA Guidelines will mandate the use of MISRA Compliance" | 2016년의 첫 판에 이은 2020년 개정이라는 설명도 같은 쪽에 있다 |
| F13-005 | 4 | 면책 문구: 이 문서의 요건을 지키는 것만으로 오류 없는 견고한 소프트웨어가 보장되지 않고, 법적 의무에서 면제되지도 않는다. | "does not of itself confer immunity from legal obligations" | 준수가 곧 안전은 아니라는 근거로 쓸 수 있다 |
| F13-006 | 10 | MISRA guideline은 문서화된 개발 과정의 틀 안에서 쓰도록 만들어졌다. 그 틀은 요구사항의 완전성, 설계의 정확성, 컴파일러가 만든 object의 동작, 시험 같은 전제를 둔다. | "documented software development process" | 코딩 규칙만으로 안전이 되지 않는다는 서술이다 |
| F13-007 | 10 | 준수는 코드를 검토나 unit test에 올리기 전에 만족해야 하는 개발 단계의 일부여야 한다. 인도 직전에 "체크 항목 채우기"로 검사하면 재작업이 오히려 결함을 만든다. | "Code shall be checked for compliance as it is developed" | 따옴표 안의 tick-box 표현은 원문이 굽은 따옴표로 쓴 것이다 |
| F13-008 | 10 | 이미 실적이 있는 코드를 준수시키려고 고치는 이익은 결함이 들어갈 위험에 밀릴 수 있다. 그 경우 순이익을 보고 판단한다. | "may be outweighed by the risks of introducing a defect" | 기존 코드의 준수 문제 (adopted code, 6절)와 이어진다 |
| F13-009 | 10 | 준수를 주장하려면 개발 과정에 반드시 넣어야 하는 활동은 다섯이다: 교육, style guide, metrics, tool management, run-time behaviour. 모든 결정과 그 이유를 문서로 남긴다. | "process activities that must be included in order to demonstrate" | 부록 A에 같은 항목의 점검표가 있다 (F13-075) |
| F13-010 | 11 | style guide는 코드의 정확성에 직접 영향이 없는 외형 규칙이다: 배치와 들여쓰기, 괄호 모양, 이름 규칙, 주석, 파일 머리말. 이런 규칙은 주관적이라고 한다. | "These issues are subjective and typically include" | style guide의 집행은 이 문서의 범위 밖이라고 적는다. 안전 규칙과 style의 구분은 NASA 지침서도 같다 (F13-125) |
| F13-011 | 11 | metrics는 검토와 시험이 더 필요한 코드를 가려내고 다루기 힘든 코드를 막는 데 쓴다. 지표와 한계값은 산업, 조직, 프로젝트가 정하므로 이 문서는 지침을 주지 않는다. | "does not offer any guidance on software metrics" | 한계값을 문서가 정하지 않는다는 점이 중요하다 |
| F13-012 | 12 | 코드 크기와 cyclomatic complexity의 균형을 계획적으로 맞추는 노력은, 시험에서 높은 statement coverage를 얻는 시간을 줄여서 상쇄되고도 남을 수 있다. | "reduction in the time required to achieve high statement coverage during testing" | 쪽 위의 Note. 복잡도를 낮추면 시험이 쉬워진다는 서술이다 |
| F13-013 | 12 | 컴파일러는 선택한 언어 판에 대해 적합한 free-standing 구현이어야 한다. 컴파일러 개발자가 적합성 시험 결과를 내는 것이 이상적이고, 어려우면 사용자 평가, 사용자 수, 독립 검증 시험으로 대신한다. | "meet the requirements of a conforming free-standing implementation" | 컴파일러가 선택한 언어 판을 구현한다는 근거가 어디까지인가를 묻는 대목이다 |
| F13-014 | 12 | 이상적인 정적 분석 도구는 모든 위반을 찾고 false positive (위반이 아닌 것이나 위반일 가능성만 있는 것을 보고하는 것)가 없는 도구다. | "Detect all violations of The Guidelines" | 이 이상은 불가능하다고 다음 쪽이 말한다 |
| F13-015 | 12 | 눈으로 검사해서 준수를 확인하는 것은 이론상 가능하지만 매우 시간이 들고 오류가 나기 쉽다. 현실적인 과정에는 정적 분석 도구가 적어도 하나 들어간다. | "extremely time-consuming and error prone" | 도구의 설정과 검증이 준수 주장의 일부가 되는 이유다 |
| F13-016 | 12 | 도구는 whole program을 가로질러 검사할 수 있어야 한다. 한 파일만 보는 도구는 쓸 수 없다고 한다. | "performing checks across the whole program" | 쪽 아래의 도구 선택 서술이다. 원문은 "essential"이라는 말을 쓴다 |
| F13-017 | 13 | 이상적인 정적 분석 도구는 지금도 앞으로도 만들 수 없다. 그래서 가능한 한 많은 위반을 찾으면서 false positive를 줄이는 정도가 도구 선택의 요소다. | "it is not, and never will be, possible to produce a static analysis tool" | 근거는 3.5절의 decidability다 (F13-038) |
| F13-018 | 13 | 분석 시간이 짧은 도구일수록 false positive가 많은 경향이 있다. 도구의 실행 시간은 초에서 일 단위까지다. 분석 시간과 정밀도의 균형을 보아야 한다. | "tools that consume less time are more likely to produce false positives" | NASA의 Toyota 조사에서 쓴 도구의 차이 (F13-302)와 같은 맥락이다 |
| F13-019 | 13 | 도구마다 강조점이 다르므로 점검 범위를 넓히려면 도구를 둘 이상 써야 할 수도 있다. | "it might be necessary to use more than one tool" | 도구 하나로 모든 규칙을 검사할 수 없다는 근거다 |
| F13-020 | 13 | 컴파일러와 정적 분석 도구는 결과를 믿고 쓰는 "신뢰하는 과정"이다. 그 신뢰가 틀리지 않도록 조치해야 하며, 도구 공급자의 검증 시험, ISO 9001 수준의 품질 체계가 이상적이다. | "Measures must therefore be taken to ensure that this trust is not misplaced" | 공급자가 못 주면 개발자가 도구의 품질을 확인할 책임을 진다고 같은 쪽이 쓴다 |
| F13-021 | 13 | 정적 분석 도구의 검증 시험 방법: guideline 하나씩의 위반을 담은 코드 파일을 만들어 도구가 그것을 찾는지 본다. 시험은 한정적이지만 기본 성능을 보여 준다. | "each containing a violation of one guideline" | 컴파일러에 대해서는 정식 검증 제도가 발행 시점에 없다고 같은 쪽이 쓴다 |
| F13-022 | 14 | IEC 61508, ISO 26262, DO-178은 어떤 상황에서 컴파일러와 정적 분석 도구의 qualification을 요구한다. | "qualification of compilers and static analysis tools in some situations" | 쪽 위의 Note. 도구 신뢰와 qualification의 연결이다 |
| F13-023 | 14 | 컴파일러 option은 표준 적합성, 언어 확장의 사용 가능 여부, 자원 사용, 컴파일러 결함이 드러날 가능성에 영향을 준다. option의 효과를 이해하고 언어 판과 target을 맞게 설정해야 한다. | "might affect" | 인용 뒤에 다섯 항목이 이어진다. "likelihood that a defect in the compiler will be exposed"가 그중 하나다 |
| F13-024 | 14 | 공격적인 최적화는 컴파일러 결함이 드러날 위험을 높일 수 있다. 최적화는 실행 속도와 코드 크기의 균형을 보아 신중하게 고른다. | "may increase the risk of exposing defects in the compiler" | 최적화가 안전에 미치는 영향의 직접 근거다. 최적화로 동작이 바뀌는 경우는 이 문서에 없다 |
| F13-025 | 14 | implementation-defined 동작을 컴파일러가 어떻게 구현하는지 이해해야 한다. 컴파일러 경고를 내는 수준을 고를 수 있으면 검토하고 알맞은 수준을 고른다. | "these should be reviewed and an appropriate level selected" | 컴파일러가 규칙 검사에 쓰이지 않아도 경고에 결함의 징후가 있을 수 있다고 같은 쪽이 쓴다 |
| F13-026 | 14 | 정적 분석 도구는 컴파일러의 implementation-defined 동작에 맞춰 설정해야 한다. 예로 정수 형의 크기를 든다. | "e.g. sizes of the integer types" | 도구의 설정이 맞지 않으면 판정이 틀린다는 함의가 있다 (기억) |
| F13-027 | 15 | 정적 분석 도구는 보통 범용이어서 컴파일러가 정한 구현 결정을 따로 알려 줘야 한다. 예: 정수 형의 크기. 컴파일러가 확장한 언어 기능을 도구가 못 받아들이면 다른 방법으로 검사해야 한다. | "static analysers need to know the sizes of the integer types" | 도구가 규칙 이상의 검사를 지원하면 그것도 켜라고 권한다 (같은 쪽) |
| F13-028 | 15 | 개발 과정에는 run-time 오류를 피하는 단계를 적어야 한다: 실행 환경이 처리 시간과 stack 공간을 충분히 주는가, 산술 overflow 같은 run-time 오류가 없는가 (예: 계산 입력의 범위를 검사하는 코드). | "Run-time errors, such as arithmetic overflow, are absent from areas of the program" | 이 서술은 정수 overflow와 stack을 코딩 규칙이 아니라 과정의 증명 대상으로 본다 |
| F13-029 | 16 | guideline은 rule과 directive로 나뉜다. rule은 코드만으로 판정되는 완전하고 객관적이고 모호하지 않은 요구다. 도구가 검사할 수 있다 (3.5절의 한계 안에서). | "complete, objective, unambiguous and independent of any process, design-documentation or functional requirement" | 규칙 대부분이 rule이다 |
| F13-030 | 16 | directive는 코드만으로 정의되지 않는 guideline이다. 과정, 문서, 기능 요구를 가리키고 주관적 판단이 들어가므로 도구마다 해석이 달라질 수 있다. | "different tools will therefore sometimes place different interpretations" | 부록 D의 정의: rule은 완전하고 모호하지 않은 명세가 있고 directive는 없다 (F13-084) |
| F13-031 | 16 | rule의 분석 범위는 Single Translation Unit과 System으로 나뉜다. 예: 모든 switch에 default가 있는가는 translation unit 하나로 검사되고, 외부 연결 식별자의 정의가 하나인가는 전체를 봐야 한다. | "can only be verified with certainty by analysis of the entire body of source code" | 두 예의 규칙 문장은 문서가 든 것이다. 규칙 번호는 이 쪽에 없다 |
| F13-032 | 16 | 위반 검출은 도구, 컴파일러, 둘의 조합이 가장 쉽고 믿을 만하고 비용이 적다. 도구가 완전히 검사하지 못하는 guideline은 사람의 검토를 쓴다. | "where a guideline cannot be completely checked by a tool" | |
| F13-033 | 16 | guideline enforcement plan (GEP)은 모든 guideline마다 준수를 어떻게 검사하는지 적은 표이며, 공급자가 만들어 발주자에게 보여 준다. | "shall be produced to indicate how compliance with the guidelines is to be checked" | 예시 표는 17쪽. 열은 컴파일러 A/B, 분석 도구 A/B, 수동 검토다 |
| F13-034 | 17 | GEP를 뒷받침하는 기록: 도구의 버전, 도구가 쓴 설정 파일, 실행 option, 도구가 해당 guideline의 위반을 실제로 찾는다는 증거, 수동 절차의 상세. 발주자가 요청하면 제공한다. | "Evidence proving that the tool is able to detect violations" | 2.6.3의 검증 시험과 이어진다 |
| F13-035 | 17 | 검사 과정이나 번역 과정이 낸 메시지는 네 가지로 나뉜다: 위반의 올바른 진단, 위반 가능성의 진단, 위반의 잘못된 진단, 위반은 아니지만 진짜 문제인 것의 진단. | "Diagnosis of a possible violation" | 네 범주가 false positive 등의 분류에 해당한다 |
| F13-036 | 17 | 올바른 진단 (1)에는 코드를 고쳐 준수시키는 것이 바람직한 조치다. 고칠 수 없으면 4절의 절차로 deviation을 승인받는다. | "is to correct the source code in order to make it compliant" | |
| F13-037 | 18 | 나머지 범주의 메시지는 조사하고 기록한다: (2) 가능성 진단은 코드가 왜 준수인지 설명, (3) 잘못된 진단은 설명하고 가능하면 도구 개발자의 동의를 얻음, (4) 진짜 문제는 무시해도 되는 이유를 정당화. 기록은 자격이 있는 기술 책임자가 검토하고 승인한다. | "reviewed and approved by an appropriately qualified technical authority" | 쪽 위의 서술이다. 도구 경보를 지우는 과정의 근거가 된다 |
| F13-038 | 18 | rule은 decidable과 undecidable로 나뉜다. decidable rule은 언제나 예 아니면 아니오로 답할 수 있어서, 도구가 올바르게 설정되고 결함이 없으면 준수를 확실히 검증한다. | "always possible to answer the compliance question" | 원문 3.5절의 정의다 |
| F13-039 | 18 | undecidable rule에서는 도구가 모든 상황에서 예나 아니오로 답한다고 보장할 수 없고, "가능성이 있다"라는 답만 낼 때가 있다. 위반 검출이 object의 값, 제어가 어느 지점에 도달하는가 같은 run-time 성질에 달려 있으면 undecidable일 가능성이 크다. | "Whether control reaches a particular point in the program" | 대부분의 undecidable rule은 system 범위로 검사해야 한다 |
| F13-040 | 19 | 예: 초기화되지 않은 값을 읽는 것을 금하는 rule은, 지역 변수의 주소를 함수 f에 넘기는 코드에서 f가 다른 translation unit에 있으면 f를 보지 않고는 판정할 수 없다. | "function f, which may be defined in another translation unit." | 쪽 위의 문장이다. 코드 예는 18쪽 아래에서 시작한다 |
| F13-041 | 19 | undecidable rule에서는 아무리 정교한 도구도 모든 상황에서 단정적으로 답할 수 없다. 진단이 없다는 것이 "준수"라는 답은 아니다. | "absence of a diagnostic does not necessarily imply a response of" | 도구의 침묵을 합격으로 읽으면 안 된다는 근거다 |
| F13-042 | 19 | 이론상 증명할 수 있는 경우에도 필요한 분석이 매우 복잡하거나 감당할 수 없는 계산 자원을 요구할 수 있다. 도구는 확실한 위반과 가능성만 있는 위반을 구별해 보고하는 정도로 평가하며, false positive와 false negative를 모두 피해야 한다. | "avoid both false positives and false negatives" | 같은 쪽의 두 문장을 합쳤다. 계산 자원은 "may require computing resources which are unmanageable" |
| F13-043 | 19 | undecidable rule의 준수 검토 과정에는 특별한 주의가 필요하다. 도구가 가능한 위반을 믿을 만하게 찾아 준다면, 개발 단계에서 보수적이고 방어적인 코딩 기법을 써서 불확실성을 없앨 수 있다. | "adopting conservative and defensive coding techniques at the development stage" | 정적 분석이 못 푸는 규칙을 코드 쓰는 방식으로 푸는 방법이다 |
| F13-044 | 20 | 준수는 조직이 아니라 프로젝트에 대해서만 주장할 수 있다. 위반은 정해진 절차로 승인되고 deviation record로 뒷받침될 때만 주장이 의미를 갖는다. | "Compliance cannot be claimed for an organization, only for a project" | |
| F13-045 | 20 | deviation record가 담을 것: (1) 위반하는 guideline, (2) 위반이 허용되는 상황의 간결한 서술, (3) deviation이 필요한 이유, (4) 맥락과 언어 문제의 배경, (5) 위험 평가 절차와 지켜야 할 주의 사항을 포함한 요구 사항. | "A concise description of the circumstances in which a violation is acceptable" | 예는 부록 B (F13-076) |
| F13-046 | 20 | deviation이 적용되는 위치를 알아야 한다. 비슷한 위반 여럿에 한 record를 공통 문서로 두고 적용 위치의 목록 (파일과 줄, 매크로, 식별자 tag)을 붙일 수 있다. 위반의 모든 사례를 찾을 수 있어야 한다. | "a register of locations where the deviation is being applied" | 한 위반이 코드의 둘 이상의 위치와 연결되는 경우도 있다고 같은 쪽이 적는다 |
| F13-047 | 20 | deviation permit는 널리 쓰이는 사용 사례 (use case)를 미리 승인해 둔 것이다. deviation record가 아니고, record에 필요한 내용과 과정 요건의 많은 부분을 준다. | "A deviation permit is not the same as a deviation record" | 부록 C의 예 (F13-081) |
| F13-048 | 21 | permit 저장소를 코드 개발 전에 만들어 두면 새 deviation의 통제, 개발 중의 혼란, 작성과 검토의 노력이 줄고, 공급자와 발주자가 일찍 합의할 수 있다. 출처는 MISRA의 공개 permit, 발주자의 permit, 공급자의 permit이다. | "Public deviation permits, published by MISRA" | MISRA가 공개 permit를 guideline 판마다 따로 낸다. 이 파일에는 내용이 없다 |
| F13-049 | 21 | MISRA가 공개한 permit라도 특정 프로젝트에서 받아들일 수 있다는 뜻은 아니며, 같은 균형과 조치를 거쳐야 한다. | "does not imply that they are acceptable within a particular project" | 쪽 아래의 Note다 |
| F13-050 | 21 | deviation을 허용하면 안 되는 경우: 개발자의 편의만을 위해, 합리적인 다른 코딩 방법이 있는데, 다른 guideline에 미치는 영향을 따지지 않고, 적절한 과정의 뒷받침 없이, 지정된 기술 책임자의 동의 없이. | "Simply to satisfy the convenience of the developer" | 정당하지 않은 이유의 목록이다. 정당한 이유 넷은 F13-051 이하 |
| F13-051 | 22 | 정당한 이유 1은 code quality다. 안전과 보안을 지킨다는 조건에서, 기준을 지키는 것이 다른 품질 특성 (유지보수성, 이식성, 성능)을 해치는 경우 위반이 더 나은 전체 품질을 낳는다면 허용될 수 있다. | "only if safety and security are maintained" | ISO/IEC 25010의 품질 모델 표가 같은 쪽에 있다 |
| F13-052 | 22 | 방어적 코딩 (fault tolerance 특성)을 하려 해도, 불변인 식과 도달할 수 없는 코드를 금하는 guideline을 지키면서는 방어 조치를 못 쓸 수 있다. | "it can be impossible to implement some defensive coding measures" | 방어적 프로그래밍과 코딩 규칙이 충돌하는 사례의 직접 근거다. 어떤 rule인지는 이 쪽에 번호가 없다 |
| F13-053 | 22 | 정당한 이유 2는 하드웨어 접근이다. 표준 문법으로 못 닿는 저수준 하드웨어 기능에는 컴파일러별 확장이 필요하다. 구현 정의 동작이 있는 코드는 가능한 한 캡슐화하고 격리한다. | "Compiler-specific extensions to the language are often necessary" | |
| F13-054 | 22 | 정당한 이유 3은 adopted code의 통합이다. 두 translation unit이 각각 준수여도 합치면 위반이 생길 수 있다. 정당한 이유 4는 준수를 의도하지 않은 adopted code로, 위반이 안전과 보안을 해치지 않는다는 것을 보이는 것으로 정당화한다. | "Non-compliant adopted code" | 네 번째 이유의 제목이다. 3번과 4번이 adopted code와 이어진다 (F13-059) |
| F13-055 | 23 | guideline의 category는 세 가지다. Mandatory는 위반이 허용되지 않는다. Required는 제한, 요구, 주의를 담은 deviation이 있을 때만 위반할 수 있다. Advisory는 현실적으로 가능한 한 따르는 권고이며 deviation 없이 위반을 식별만 한다. | "Guidelines for which violation is never permitted" | 이전 판은 Required와 Advisory만 두었고 MISRA C:2012가 Mandatory를 더했다 |
| F13-056 | 23 | 발주자와 공급자는 프로젝트 시작 때 guideline re-categorization plan (GRP)에 합의한다. GRP는 category를 더 엄하게 바꾼 것을 정한다. 일부 Advisory를 아예 무시하는 "Disapplied" category가 추가되며, 그 이유를 GRP에 적어야 한다. | "At the outset of a development project, the acquirer and supplier shall agree" | 원문은 "re-categorization"이 줄 끝에서 나뉘어 있다 |
| F13-057 | 23 | Required 중 deviation의 정당한 이유가 생기는 것은 소수이므로 대다수를 Mandatory로 다룰 수 있다. 이것은 경험과 조사를 거친 뒤에만 도입할 수 있으며, 위반의 증식을 막는 데 쓴다. | "treat a high proportion of the Required guidelines as Mandatory" | |
| F13-058 | 23 | 허용되는 변경: Required -> Mandatory, Advisory -> Mandatory, Required, Disapplied. Mandatory는 어떤 식으로도 바꿀 수 없고, Required를 Advisory나 Disapplied로 낮출 수 없다. | "A Mandatory guideline may not be re-categorized in any way" | 쪽 아래의 표와 Note 1, 2. 24쪽에서 Advisory의 위반은 deviation 없이 식별만 하고 Disapplied는 무시한다고 이어진다 |
| F13-059 | 25 | adopted code는 프로젝트 밖에서 온 코드다: 표준 library, 장치 구동 코드, middleware, 제3자 library, 자동 생성 코드, legacy code. 안전과 보안이 검증된 수준인가와 MISRA 준수인가는 별개의 질문이다. | "is neither a necessary nor a sufficient condition" | 전체 문장: MISRA 준수는 adopted code 품질의 필요조건도 충분조건도 아니다 |
| F13-060 | 25 | adopted code의 영향은 무시하거나 무해하다고 가정해서는 안 된다. adopted code가 native code와 정확히 같은 준수 기준으로 개발되지 않았으면 준수 주장은 훼손된다. | "must never be overlooked or assumed to be benign" | |
| F13-061 | 25 | system 범위로 적용하는 guideline 때문에, 따로 보면 준수인 두 translation unit이 합쳐지면 위반이 생길 수 있다. 둘 다 native이면 코드를 고치고, adopted가 끼면 deviation을 낼 수 있다. | "may not be compliant when combined in the same system" | |
| F13-062 | 26 | adopted code가 binary뿐이면 준수와 코드 품질의 검증이 제한된다. 협력 조직끼리 공통 절차와 도구에 합의하거나 stub 소스를 주고받을 수 있다. 소스가 없으면 binary의 정적 또는 동적 분석 같은 다른 방법을 찾는다. | "static or dynamic analysis of the binary code" | system 범위 guideline은 전체 소스 없이는 검증이 제한된다고 같은 쪽이 쓴다 |
| F13-063 | 26 | adopted source code의 위반은 코드가 나쁘다는 뜻이 아닐 수 있지만 무시할 수 없다. 모든 위반을 검토해서 무결성이 해쳐지지 않았는지, 승인된 deviation이 덮는지 본다. | "violations cannot simply be ignored" | |
| F13-064 | 26 | adopted code는 고칠 수 없으므로 덜 엄한 GRP를 따로 둘 수 있다 (native용과 adopted용). 더 관대한 GRP가 adopted code에 대한 안전 약속이 덜하다는 뜻은 아니고, 검토할 위반이 더 많다는 뜻이다. | "is any less stringent for adopted code" | 원문 문장은 "The fact that an adopted code GRP is more permissive ... does not imply"로 이어진다 |
| F13-065 | 26 | 원래 MISRA에서 Mandatory였던 guideline을 위반한 코드는 어떤 GRP를 쓰든 준수라고 분류할 수 없다. | "can never be classified as compliant" | adopted code의 GRP로도 Mandatory 위반은 덮을 수 없다는 뜻이다 |
| F13-066 | 27 | adopted header의 위반은 header 안이 아니라 native code에서 나타날 수 있다. 예: header의 매크로는 준수인데 포인터 인자로 불러 확장하면 native code가 위반이 된다. 해결은 매크로의 정의를 고치는 것이다. | "are not always located within the header file itself" | 문서의 예는 NULL을 쓰지 않고 0과 비교하는 매크로다. 규칙 번호를 문서가 적었으나 이 파일은 번호를 옮기지 않는다 |
| F13-067 | 27 | 표준 library 코드는 컴파일러 구현의 일부이므로 MISRA guideline을 지킬 필요가 없다. 다만 표준 header의 선언과 매크로의 인터페이스에 의존하는 guideline (인자와 반환값의 형 검사)은 그대로 적용된다. | "Standard Library code is not required to comply with MISRA Guidelines" | 프로젝트가 원하면 표준 library도 adopted code처럼 다룰 수 있다 |
| F13-068 | 28 | 프로젝트는 이 문서의 과정과 원칙에 따라 개발되지 않았으면 "MISRA 준수"라고 부를 수 없다. | "unless development has been conducted in accordance with the process and principles" | 인용 앞은 "A project cannot be described as MISRA Compliant"다 (원문은 굽은 따옴표) |
| F13-069 | 28 | 준수 주장을 하려면 guideline과 언어 문제를 이해하는 교육받은 사람이 필요하다. 공급자는 능력 기록을 유지하고, deviation을 승인하는 사람은 특히 숙련되어야 한다. guideline끼리 서로 의존하므로 B를 어길 때 A의 보호가 깨질 수 있다. | "The supplier shall maintain staff competence records" | A와 B의 예는 같은 쪽 위쪽이다 |
| F13-070 | 28 | 계약으로 deviation의 자유를 제한하는 방법: Required를 Mandatory로, Advisory를 Mandatory나 Required로 올리기, 특정 guideline의 deviation을 승인된 permit의 use case로만 허용하기. | "Restricting deviations on specific guidelines to use cases defined in approved permits" | 29쪽의 두 예: (1) 공급자가 자기 deviation과 GRP를 만들고 발주자가 중간에 검토, (2) 계약이 엄한 GRP와 사전 합의된 permit를 강제 |
| F13-071 | 29 | guideline compliance summary (GCS)는 프로젝트 끝에 낸다. 모든 guideline마다 주장하는 준수 수준을 적는다: Compliant (위반 없음), Deviations (위반이 모두 deviation으로 뒷받침됨), Violations (deviation 없는 위반), Disapplied (검사하지 않음). | "No checks have been made for compliance with the guideline" | Disapplied의 정의다. 네 수준은 29쪽 아래에 있다 |
| F13-072 | 30 | category마다 주장할 수 있는 수준이 다르다. Mandatory는 Compliant만, Required는 Compliant나 Deviations, Advisory는 네 수준 모두다. GCS는 GRP가 허용한 최악의 집행 수준을 반영한다. | "capturing the worst-case enforcement permitted by the GRPs that have been applied" | 예: native에서 Mandatory로 올린 Required를 adopted에서 Required로 두면 GCS는 Deviations를 주장한다 |
| F13-073 | 30 | 프로젝트를 인도할 때 공급자가 발주자에게 내는 것: GEP (요청 시 3.3절의 문서, 도구 검사의 증거, 위반의 증거 포함), GCS, 승인된 permit의 상세, Required로 재분류된 guideline의 모든 위반을 덮는 deviation record. | "make the following artefacts available to the acquirer" | 준수 주장의 요건 목록이다. 31쪽에 나머지 항목이 이어진다 |
| F13-074 | 31 | 위의 문서는 처음엔 발주자에게 제공하지만, 개발된 코드를 나중에 쓰는 다른 당사자에게 증거로 줄 수도 있다. | "Deviation records covering all violations of guidelines re-categorized as Required" | 쪽의 목록 마지막 항목이다 |
| F13-075 | 33 | 부록 A의 점검표는 준수 주장을 위해 따라야 할 과정과 도구 항목이다. 교육, style guide와 metrics의 과정, 컴파일러와 분석 도구의 결함 처리, 언어 판 선택, 경고 수준과 최적화 수준의 설정, 분석 도구의 구현 설정 (정수 크기), 자원 충분성, run-time 오류 부재의 증명, GEP, 메시지 조사, undecidability 관리, deviation 과정, GRP, GCS. | "There is a process to manage undecidability issues" | 항목마다 본문의 절을 가리킨다. 점검표라서 "준수 주장의 요건"을 한눈에 보여 준다 |
| F13-076 | 34 | 부록 B는 deviation record의 예다. 항목: 프로젝트, deviation ID와 상태 (Approved), 근거 permit, 대상 rule, use case, 이유 (Code Quality, Time behaviour), 범위, tracing tag, 작성자와 승인자의 서명, 직책, 날짜. | "D_00102_1 to D_00102_10" | 예의 작성은 2015-03-14, 승인은 2015-04-12다. 작성자는 소프트웨어 팀장, 승인자는 엔지니어링 이사다 |
| F13-077 | 34 | 예의 사정: 16비트 두 값을 곱해 32비트 결과를 얻는 integrator에서, 규칙을 지키려 형 변환을 명시하면 이 컴파일러가 느린 곱셈 library 호출을 만들어 timing 요구를 못 맞춘다. 같은 문서가 이 문제가 vehicle의 배출 목표를 위협한다고 쓴다. | "the code generated for these integrators was far in excess of the budget" | 규칙 번호는 문서가 적었으나 이 파일은 옮기지 않는다. 작성 쪽 서술에는 worst-case execution time 분석 도구를 쓴 것도 있다 |
| F13-078 | 35 | 명시적 형 변환 없이 암묵 변환을 쓰면 컴파일러가 단일 곱셈 명령을 고른다. C 표준상 두 방식의 동작은 같고 결과도 같지만 library 호출은 최악 100 cycle이 든다. 컴파일러 공급자가 이 동작이 예상된 것임을 문서로 확인했다. | "independent of whether the conversion is implicit or explicit" | 컴파일러의 코드 생성이 코딩 규칙의 준수 비용을 바꾸는 사례다 |
| F13-079 | 35 | 정당화 (B.3): 25 MHz에서 평균 100 microsecond마다 실행되는 integrator가 10 microsecond 안에 결과를 내야 하고, 못 맞추면 $10m 넘는 상업적 영향이 있다. 검토한 대안과 기각 이유: 클럭을 올림 (최대 100 MHz), 프로세서 교체 (약 $250,000과 일정 영향), 컴파일러 교체 (대안 없음), library를 고침 (공급자가 지원하지 않는다고 함). | "there is no other commercially recognized compiler for this processor" | 정당하지 않은 이유 (F13-050)와 대비되는, 대안을 따져 보인 정당화의 예다 |
| F13-080 | 36 | 보고 통제의 조치 (B.7): 도구가 식 안에서 진단을 억제하는 기능이 있으므로, 매크로로 곱셈을 구현하고 주석으로 deviation을 가리키며 진단을 억제한다. 함수로는 호출의 부담이 과해서 매크로를 택하고, 그 때문에 다른 directive를 어기게 된다고 문서가 적는다. | "a diagnostic message can be suppressed within an expression" | deviation이 도구 설정의 억제와 코드의 표지로 이어지는 구체적 방법이다 |
| F13-081 | 37 | 부록 C는 deviation permit의 예다. 구성: permit ID, rule, use case, 이유, 배경, 요구 사항. 이 예의 요구 사항은 다섯이다: 넓은 형이 32비트 (int의 크기), 피연산자의 형이 16비트, 식의 피연산자가 정확히 둘, 곱셈만 포함, 넓은 형에서 평가하려는 의도. | "The composite expression shall have exactly two operands" | permit는 use case의 조건을 좁게 규정해서 deviation record를 간단하게 만든다 |
| F13-082 | 38 | 용어: deviation은 "공식적으로 받아들여지고 승인된 위반"이다. deviation record는 위반의 존재를 정당화하는 문서다. deviation permit는 use case와 deviation을 정당화할 요구의 명세다. | "A violation which has been formally accepted and approved." | 부록 D의 용어 정의다 |
| F13-083 | 38 | 용어: guideline은 language subset의 일부를 구현하는 language restriction을 정의하는 directive나 rule이다. "The Guidelines"는 language subset을 강제하는 데 쓰는 MISRA 문서를 뜻한다. | "that is used to enforce a language subset" | 이 문서는 MISRA guideline을 language subset이라고 부른다. 왜 subset인지는 서술하지 않는다 |
| F13-084 | 38 | 용어: rule은 완전하고 모호하지 않은 명세가 있는 guideline이고, directive는 그런 명세가 없는 guideline이다. GEP는 guideline마다 강제 방법의 기록이고, GRP는 category를 더 엄하게 대체하는 합의된 정책이다. | "A guideline lacking a complete, unambiguous specification." | directive의 정의다. 같은 쪽에 GEP와 GRP의 정의가 있다 |
| F13-085 | 39 | 용어: violation은 guideline이 정한 제한에 맞지 않는 코드다. native code는 프로젝트 안에서 적용된 guideline을 지키도록 개발된 코드다. | "Code which does not conform to the restrictions specified by a guideline" | |

## 2. nasa-gb-8719-13 (NASA, Software Safety Guidebook NASA-GB-8719.13, 2004. PDF 쪽 = 인쇄 쪽 + 1)

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| F13-100 | 93 | 4.6절은 좋은 개발 과정 위에 설계와 구현에 넣을 수 있는 여러 실천을 모은 것이다. 출처는 Doug Brown, David Stewart, Bill Wood, SSP 50038 등이고 부록 H에 점검표가 있다. | "there are many practices that can be incorporated into the design or implementation" | 이 절의 항목 상당수는 실천의 나열이다. 어느 것이 효과 있는지의 측정은 없다 (기억) |
| F13-101 | 93 | 소프트웨어가 자신을 점검하는 실천: 부팅 때 CPU 자체 시험, 알려진 패턴 (halt나 illegal instruction)으로 ROM과 RAM의 빈 곳 채우기, 실행 전 ROM 시험, watchdog timer. | "Filling ROM or RAM with a known pattern" | 4.6절의 첫 항목들이다 |
| F13-102 | 94 | watchdog는 interrupt에서 먹이를 주면 안 된다. interrupt가 살아 있는 동안 진짜 process가 모두 막혀 있을 수 있어서 watchdog의 목적이 사라진다. | "Do NOT use an interrupt to tickle the watchdog" | Koopman의 Toyota 분석이 같은 취지를 든다 (F13-214) |
| F13-103 | 94 | 중요한 변수를 여러 복사본으로 (다른 저장 매체에) 저장해서 쓸 때 비교하고, 불일치하면 3중 중 2 투표하거나 기본값을 쓴다. 변수 묶음에 CRC를 쓴다. stack을 알려진 패턴으로 채우고 남은 공간을 감시한다. | "Storing multiple copies of critical variables" | 방어적 프로그래밍의 변수 보호 항목이다 |
| F13-104 | 94 | Stewart의 함정 목록: 빈 loop로 구현한 지연은 더 빠른 기계나 최적화 컴파일러로 다시 컴파일하면 문제가 된다. | "recompiled with a newer, optimizing compiler" | 컴파일러 최적화가 안전과 연결되는 사례다 |
| F13-105 | 95 | 오류 검출과 처리를 나중에 시행착오로 붙이는 것은 함정이다. 처음부터 설계에 넣되, 모든 곳이 아니라 데이터가 맞아야 하는 중요한 곳, 나쁜 입출력에 약한 곳에 둔다. | "Design in the error detection and handling mechanisms from the start" | |
| F13-106 | 95 | interrupt를 가리지 않고 쓰면 실시간 시스템에서 priority inversion이 생기고 시간 제약 위반으로 이어질 수 있다. | "Indiscriminate use of interrupts" | 항목 제목이다. 본문은 priority inversion의 서술이다 |
| F13-107 | 95 | Bill Wood의 항목: 변수를 쓰기 전에 합리성 검사, 실행 기록을 독립적으로 점검, 중요 구성요소가 올바른 호출자에게 불렸는지 확인 (come-from 검사), 부하에서 메모리 누수 시험, 쓴 값을 다시 읽어 확인 (read-back). | "Check variables for reasonableness before use" | 범위를 벗어난 값은 메모리 손상, 계산 오류, 하드웨어 문제의 징후라고 본문이 설명한다 |
| F13-108 | 96 | 복잡도를 낮추라는 실천: McCabe cyclomatic complexity는 결정의 수를 모두 더하고 1을 빼서 구한다 (if는 1, case가 셋인 switch는 2). 10을 넘으면 그 routine의 단순화를 검토한다. | "If the complexity is over 10, look at simplifying the routine." | 10이라는 값의 출처는 150쪽의 McCabe 권고 (F13-136)와 같다 |
| F13-109 | 96 | 컴파일러 최적화는 신중히 고른다. 최적화한 코드는 debugger와 잘 맞지 않고 source와 object의 대응이 어렵다. 최적화는 프로그래머의 기대와 동작을 바꿀 수 있고, 쓰이지 않는 것으로 보이지만 실제로는 쓰이는 기능을 없앨 수 있다. | "Optimization may change the way the programmer expected the code to operate" | volatile이라는 말은 이 쪽에 없다 |
| F13-110 | 96 | 다중 thread 프로그램은 개발이 어렵고, 오류가 scheduler와 환경의 비결정성에 달려 있어 재현이 어렵다. | "Developing multi-threaded programs is notoriously difficult" | 4.6절 안의 짧은 경고다 |
| F13-111 | 97 | 국제 우주 정거장 요건 SSP 50038에서 온 항목: 쓰지 않는 모든 interrupt는 return으로 초기화한다. 쓰지 않는 메모리를 실행되면 안전 상태로 가게 하는 패턴으로 채운다. 위험한 동작을 시작하는 데 별도의 승인과 제어를 둔다. | "All interrupts should be initialized to a return, if not used by the software" | 같은 목록에 critical 입출력 port와 비critical port를 섞지 않는다는 항목도 있다 |
| F13-112 | 97 | 같은 목록: 이상을 감지하면 순서 있는 shutdown이나 알려진 안전 상태로 간다. critical routine에 실수로 들어가는 것을 막고 감지한다. | "Prevent inadvertent entry into a critical routine" | |
| F13-113 | 98 | 안전에 중요한 입력은 합리성 검사를 한다. 소프트웨어를 알려진 안전 상태로 초기화하고, 변수가 reset 전 값이 아니라 초기값을 갖도록 한다. flag는 한 가지 목적만 갖는다. | "Perform reasonableness checks on all safety-critical inputs" | |
| F13-114 | 98 | 하드웨어나 다른 구성요소의 데이터에 바탕을 둔 결정 논리는 모두 1이나 모두 0의 값에 기대면 안 된다. 오작동하는 하드웨어가 조건을 만족시킬 가능성을 줄이려고 특정 비트 패턴을 쓴다. | "should not be based on values of all ones or all zeros" | |
| F13-115 | 98 | 안전에 중요한 구성요소는 진입점과 출구점이 하나여야 한다는 항목이 있다. | "Safety-critical components should have only one entry and one exit point" | 부록 H.5는 이를 큰 routine에 적용하고 작은 subprogram에서는 다중 출구를 허용한다 (F13-181) |
| F13-116 | 118 | 6.5.4절 (요구사항 단계): 동적 메모리 할당이 성공할지는 RAM, 가상 메모리, 정적 사용량 등에 달려 있으므로 최악의 값으로 따져야 한다. 할당 실패를 소프트웨어가 어떻게 처리할지는 명세해야 한다. | "How the software will deal with failed dynamic allocation should be specified" | 실패했을 때 되풀이하거나 중단하는 기본값을 쓰는 것은 아주 나쁜 생각이라고 같은 쪽이 쓴다 |
| F13-117 | 118 | 중요한 메모리 블록을 우발적인 손상이나 삭제에서 보호하는 것을 요구 사항으로 해야 한다. RAM 시험은 전원을 켤 때 하고, 단일 사건 영향이 있는 환경에서는 주기적으로도 한다. | "Protecting critical memory blocks from inadvertent corruption or deletion" | |
| F13-118 | 139 | 7.4.1 설계: 위험이 큰 시스템에서는 interrupt가 안전 제어를 방해할 수 있으므로 피해야 한다. 쓰는 interrupt는 우선순위 기반으로 한다. | "interrupts should be avoided as they may interfere with software safety controls" | 같은 쪽의 항목: 안전에 중요한 data를 다른 data와 분리하고 비critical 구성요소가 접근하지 못하게 한다 |
| F13-119 | 146 | 7.4.5절: 안전이 중요한 소프트웨어에서는 언어의 어떤 면을 피해야 한다. 표준이 정하지 않아서 컴파일러마다 다른 것, 하는 일이 해로운 것 (interrupt를 너무 오래 막는 것), 그저 나쁜 관행인 것. | "These aspects may be undefined by the standard" | |
| F13-120 | 146 | 설계를 코드로 옮기기 전에, 언어 선택 때 이런 문제를 조사해야 한다. 이미 습관이 된 뒤에 구성 요소를 고치는 것보다 일찍 좋은 관행을 두는 것이 쉽다. | "It is important that the chosen language is surveyed for such potential problems" | |
| F13-121 | 146 | coding standard는 그런 언어 제한을 실행하는 한 방법이다. 쓸 수 있는 구성과 쓰면 안 되는 구성을 정하고, 결과가 사실상 언어의 안전한 부분집합이 된다. | "A Coding Standard is one way to implement such language restrictions" | 다음 쪽 첫머리에 "produces, in practice, a safe subset"가 이어진다 (원문은 safe에 굽은 따옴표) |
| F13-122 | 147 | coding standard는 설계자가 시스템에 맞춰 만들거나 어떤 언어의 더 안전한 판을 위한 일반 표준을 쓸 수 있다. | "Coding standards may be developed by the software designer" | |
| F13-123 | 147 | 동적 메모리 할당의 구현 방법은 대부분의 언어 명세에 없고 컴파일러마다 다르다. 할당된 위치도 예측하기 어렵다. 전역 항목의 초기화 순서도 같다. 표준으로 어떤 전역 항목도 다른 전역 항목이 먼저 초기화되었다고 가정하지 않게 할 수 있다. | "is not part of most language specifications" | |
| F13-124 | 147 | 표준은 프로젝트의 모든 층이 합의하고 집행되어야 한다. 프로그래머가 동의하지 않으면 우회할 길을 찾는다. 안전은 모두의 협조가 필요하다. | "Safety requires the cooperation of everyone" | |
| F13-125 | 147 | 들여쓰기와 주석 모양 같은 style 요구는 coding standard와 별도의 coding style 문서로 나누는 것이 최선이다. 표준이 style 때문에 선반에 올려지는 것을 막고, style은 읽기와 검사를 쉽게 한다. | "This avoids the problem of developers shelving the coding standards" | 11.1.1 절 (F13-153)과 같은 권고가 되풀이된다 |
| F13-126 | 147 | 합의한 표준에서 검사표를 만들어 형식 검사와 비형식 검토에 쓴다. 표준 집행은 개발 도구로도 할 수 있다. 이 절의 평가는 benefit HIGH, cost LOW다. | "Coding standards can be enforced some development tools" | 원문의 오탈자 (enforced 뒤에 by 없음)를 그대로 옮겼다 |
| F13-127 | 147 | 방어적 프로그래밍은 결함이 failure가 되지 않게 하는 방법과 기법과 알고리즘의 모음이다. 결함의 출처: 자기 소프트웨어의 논리 오류, 다른 프로그램의 잘못된 메시지, 하드웨어 결함 (sensor의 나쁜 값), 운영자 오류. | "prevent faults from becoming failures" | 시스템을 어떤 입력이든 던지는 적대적 환경으로 보라고 같은 쪽이 쓴다 |
| F13-128 | 148 | 방어적 프로그래밍의 가장 간단한 예는 입력 변수의 범위 검사다 (1에서 10이어야 하면 쓰기 전에 검사). 범위를 벗어나면 함수를 중단하고 오류 코드를 반환하거나, 미리 정한 기본값으로 바꾸거나, 예외를 던진다. | "If the input variable is outside that range, the software needs to do something" | 무엇을 할지는 전체 전략의 일부여야 한다 |
| F13-129 | 148 | 그냥 계속 진행해서 잘못된 입력이 결국 failure로 이어지게 두는 것은 권하지 않는다. | "This approach is not recommended" | |
| F13-130 | 148 | come-from 검사: 중요한 routine이 지금 실행되어야 하는지 점검하고, 아니면 실행하지 않고 오류를 낸다. 선행 process가 비트 flag를 세워서 구현할 수 있다. | "Critical routines test whether they should be executing at some particular instant" | |
| F13-131 | 148 | 오류 처리 전략 (각 함수가 입력을 검사하는가, 호출 전에 검사하는가, 오류를 상위로 올리는가)을 일찍 정한다. 선택과 상관없이 일관성이 중요하고, 모든 함수가 같은 전략을 쓴다. | "Regardless of the strategy chosen, consistency is important" | |
| F13-132 | 148 | 방어적 프로그래밍은 결함 허용 전략의 하위 수준이며 언어마다 다르다. 설계에 계획해서 넣어야 하고 나중에 붙이는 것이 아니다. 8.4.1절이 방어적 프로그래밍 점검표를 요구한다. 평가: benefit HIGH, cost LOW. | "planned into the software design, not tacked-on later" | assert 문은 이 절에 나오지 않는다 (F13-185) |
| F13-133 | 149 | 7.4.8절: 복잡한 구성요소와 인터페이스는 이해와 신뢰와 유지보수에 영향을 준다. 복잡한 data와 명령 구조는 철저히 시험하기 어렵고 모든 경로를 생각하거나 시험할 수 없다. | "Highly complex data and command structures are difficult, if not impossible, to test thoroughly" | |
| F13-134 | 149 | 복잡도 지표는 언어적 (줄 수, 연산자 수, Halstead)과 구조적 (제어와 data 흐름, 호출 수, 중첩 깊이, McCabe cyclomatic complexity)으로 나뉜다. | "McCabe's Cyclomatic Complexity metric is the most well-known and used metric" | 객체지향용 지표 목록도 같은 쪽에 있다 |
| F13-135 | 150 | 복잡도 지표를 액면대로 받지 말라고 경고한다. 복잡하다고 나오는 case 문이 실제로는 더 단순하고 직접적인 방법일 수 있다. | "Do not take the numbers at face value" | |
| F13-136 | 150 | 한계: McCabe는 cyclomatic complexity 10을 권하고 15까지 쓴 사례가 있다. 10을 넘기는 선택은 경험, 형식 설계, 현대 언어, 구조적 프로그래밍, 검토, 포괄적 시험이 있어 정보에 근거할 때만이고 추가 시험을 감수해야 한다. | "a development group can pick a complexity limit greater than 10" | 지침서는 이 인용을 참고 문헌 [93]에서 가져왔다 |
| F13-137 | 150 | 복잡도는 모듈만이 아니라 인터페이스에도 있다. 모듈 복잡도를 제한해서 모듈 수가 늘면 인터페이스가 늘어난다. 전역 data는 소프트웨어의 어느 부분이나 서로 영향을 줄 수 있게 해서 복잡도를 크게 늘린다. | "virtually any part of the software can interact with any other part" | 한 영역의 복잡도를 줄이면 다른 영역이 늘 수 있어서 균형이 필요하다는 서술이 이어진다. 평가: benefit HIGH, cost LOW |
| F13-138 | 169 | 8.4.1절: 코딩에는 검사표를 쓰며 요구 단계부터 갱신한다. coding standard는 피해야 할 안전하지 않은 함수나 절차를 알리는 데 가장 좋다. style, 이름, 주석 형식도 담을 수 있다. | "best used to identify unsafe functions or procedures" | 표준은 설계 단계나 그 전에 정하고 구현 내내 쓴다고 같은 쪽이 쓴다 |
| F13-139 | 169 | 방어적 프로그래밍 점검표는 선택한 기법을 일반과 언어별로 적는다. 항목은 긍정형 (C++ 소멸자는 virtual)이나 부정형 (memcpy를 쓰지 않는다)이다. 다른 프로젝트의 교훈도 담는다. | "Do not use the memcpy library routine" | 부록 H.5 - H.12가 시작점이라고 한다 |
| F13-140 | 170 | 표준의 집행을 돕는 자동 도구: style 검사기, 문맥 편집기, lint, profiler. 11.2절에서 논한다. | "Automated tools that aid in enforcing coding standards" | |
| F13-141 | 174 | 8.5.4절 쓰이지 않는 코드의 분석: 논리적으로 실행에서 제외된 코드는 실제로 흔한 오류다. 세 가지 이유로 나쁘다: 설계 구현의 큰 오류의 징후일 수 있고, 불필요한 복잡도와 메모리를 쓰고, 하드웨어 고장이나 SEU로 실수로 실행되면 위험한 routine이 들어 있을 수 있다. | "logically excluded from execution" | 앞 문장은 "A common real world coding error"로 시작한다. 평가: benefit MEDIUM, cost MODERATE (같은 쪽) |
| F13-142 | 174 | 쓰이지 않는 코드를 찾는 별도의 분석 기법은 없다. 다른 분석, 곧 형식 검사 (Formal Inspection), 코드 논리 분석, coverage 도구를 쓴 unit test를 하다가 발견된다. 모든 부분이 언젠가 모든 운용 mode에서 시험되도록 한다. | "There is no particular analysis technique for identifying unused code" | 8.5.4절의 평가 등급은 F13-141의 비고 |
| F13-143 | 174 | 8.5.5절 interrupt 분석은 interrupt가 프로그램 흐름과 data 손상에 미치는 영향을 본다. 질문: priority inversion이 생기는가, interrupt를 막은 동안 들어오는 interrupt를 쌓아 둘 수 있는가, 낮은 우선순위가 높은 것을 끊고 중요한 data를 바꿀 수 있는가. | "Can a low-priority process interrupt a high-priority process and change critical data?" | |
| F13-144 | 174 | interrupt 분석에서 볼 곳: interrupt를 막는 구간 (막는 시간, 쌓아 둘 수 있는가, 예상과 최대 발생률 필요, 무한 loop), 재진입 가능한 코드 (중단 후 상태 복원), 끊기면 안 되는 구간. | "Look at how long the interrupts are inhibited" | |
| F13-145 | 174 | 재진입 코드는 상태 정보를 잃지 않고 중단될 수 있게 만든 코드다. 재진입이어야 하는 구성요소가 실제로 그렇게 구현되었는지 확인한다. | "Re-entrant code is designed to be interrupted without loss of state information" | |
| F13-146 | 175 | interrupt 분석의 나머지 항목: 실시간 task의 우선순위, 시간 제약 사건이 반드시 실행되는가, 정의되지 않은 interrupt를 받으면 무시할지 오류를 처리할지. 평가: benefit HIGH, cost LOW. | "What happens when an undefined interrupt is received?" | |
| F13-147 | 160 | 7.5.7절 설계 data 분석: interrupt와 그것이 data에 미치는 영향은 안전 중요 영역에서 특별히 주의해야 한다. interrupt 처리 routine이 다른 routine이 쓰는 중요한 data를 바꾸지 않는지 검증한다. | "do not alter critical data items used by other routines" | 같은 쪽: 공유 메모리와 동적 메모리 할당이 data 무결성에 영향을 줄 수 있다. 공유 data의 대책 (critical section, 이중 buffer)은 이 쪽에 없다 |
| F13-148 | 160 | 설계 논리 분석 (7.5.6)에서 상용 자동 source 분석기는 보완용으로 쓸 수 있지만 결함과 오류가 있을 수 있어 전적으로 믿으면 안 된다. | "should not be relied upon absolutely" | 상용 도구 일반에 대한 서술이다 |
| F13-149 | 208 | 11.1.1절 안전한 부분집합: 오류 나기 쉽거나 정의가 모호한 기능을 제한한 언어의 부분집합이다. 업체나 사용자 공동체가 만들기도 하지만, 표준 부분집합이 없을 때 coding standard로 부분집합을 만든다. | "Using coding standards means that the compiler will not enforce the subset" | coding standard로 만든 부분집합은 컴파일러가 집행하지 않는다는 점이 중요하다 |
| F13-150 | 208 | 언어를 부분집합으로 제한하는 이유는 둘이다: (1) 어떤 기능이 모호하게 정의되어 있다, (2) 어떤 기능이 지나치게 복잡하거나 오류가 나기 쉽다. 지나친 복잡도는 일부 언어 기능을 검증하기 거의 불가능하게 만든다. | "some features are excessively complex or error-prone" | 인용 앞은 "1) some features are defined in an ambiguous manner"다 |
| F13-151 | 208 | 안전이 중요한 용도에 적합한 언어는 필요한 기능이 있고, 정의가 정확하고, 논리적으로 일관되고, 크기와 복잡도가 관리할 만해야 한다. | "has a precise definition, is logically coherent, and has a manageable size" | |
| F13-152 | 208 | 더 안전한 부분집합은 엄밀한 연구와 검증을 거쳐 사용자 공동체의 승인을 받고, 컴파일러가 소스에서 object로의 올바른 번역을 인증하는 경우가 많다. | "undergoes vigorous study and verification before it is accepted by the user community" | |
| F13-153 | 208 | 안전 전용 coding standard는 안전 코드의 주석 요구를 정하고 안전을 해치는 언어 기능을 금한다. 표준에 style 요구를 넣지 말고 별도 문서에 두라고 한다. style 논쟁 때문에 일부 프로그래머가 문서 전체를 무시할 수 있다. | "Avoid including programming style requirements in a coding standard" | 다음 쪽 첫머리의 문장이 이유를 적는다 (F13-154) |
| F13-154 | 209 | style과 표준이 섞이면 일부 프로그래머가 문서 전체를 무시한다. | "programmers ignoring the whole document, if style and standards are mixed" | 앞 쪽 11.1.1 끝에서 이어지는 문장이다. 7.4.5절의 같은 취지는 F13-125 |
| F13-155 | 209 | 11.1.2절 모든 언어의 약점: 초기화되지 않은 변수는 거의 모든 언어에서 가장 흔한 오류다. 시험이 의도적으로 설계되지 않으면 잡지 못한다. 새 언어와 표준 개정은 약점을 고치면서 새 약점을 더하기도 한다. | "Uninitialized variables are the most common error in practically all programming languages" | |
| F13-156 | 209 | 메모리 관리: 해제는 포인터만이 아니라 구조가 쓴 메모리를 해제해야 하고, 같은 블록은 한 번만 해제한다. 해제하지 않으면 누수와 결국 시스템 붕괴로 이어질 수 있다. | "memory that is not deallocated when no longer used will lead to a memory leak" | 메모리 관리의 우려 항목이다 |
| F13-157 | 209 | 컴파일러의 unspecified 동작: 피연산자의 평가 순서는 언어 표준이 정하지 않고 컴파일러 공급자에게 맡긴다. 부작용의 순서에 기대는 것은 나쁜 관행이다. 전역과 정적 변수의 초기화 순서도 같다. | "The order in which operands are evaluated is often not defined by the language standard" | 컴파일러 판이나 공급자가 달라지면 결과가 바뀔 수 있다고 같은 쪽이 쓴다 |
| F13-158 | 209 | 11.1.3절: 모든 언어에서 더 안전한 소프트웨어를 쓸 수 있다. coding standard는 그 방법을 정한다. 인간은 실수하고 서두르고 표준을 안 지킬 수 있으므로, 더 안전한 언어는 표준을 집행하고 공통 오류를 가능한 한 일찍 검사하는 언어다. | "and that do so as early as possible" | 앞 문장은 "that enforce the standards, that check for common errors"다 (원문은 safer에 굽은 따옴표) |
| F13-159 | 210 | 언어 평가 질문 (최소): 임의의 위치로 점프하지 않음을 보일 수 있는가, 임의 메모리 덮어쓰기를 막는 기능이 있는가, 의미가 정적 분석이 가능할 만큼 정의되어 있는가, 정수와 부동 소수점 산술의 엄밀한 모델이 있는가, 실행 중 메모리 부족을 막는 기능이 있는가, 안전한 부분집합이 있는가. | "Is there a rigorous model of both integer and floating point arithmetic within the standard?" | 목록은 열 개의 질문이다. 인용은 그중 하나다 |
| F13-160 | 211 | 11.1.4.1절: Ada는 안전과 신뢰를 목표로 설계되었고 가능한 한 일찍 오류를 가장 많이 검출하는 것이 목표다. Ada는 국제 우주 정거장의 주 언어다. 미국 국방부는 1997년까지 무기와 임무 필수 프로그램에 Ada를 의무로 했다. | "Ada is also the primary language of the International Space Station" | Ada83, Ada95 시기의 서술이다 |
| F13-161 | 211 | SPARK는 Ada의 부분집합으로, 정확한 의미가 Ada 컴파일러 선택에 영향받지 않고 결코 erroneous가 될 수 없다. task, exception, generic, access type, goto 등을 제외한다. | "excludes tasks, exceptions, generic units, access types, use clauses" | 서술은 2004년경의 SPARK 지침이다. 오늘의 SPARK 2014 이후와 다르다 (기억) |
| F13-162 | 211-212 | Ada는 강한 타입이다. 정수를 부동 소수점 자리에 명시 변환 없이 쓸 수 없다. 강제된 변환은 프로그래머가 이유를 생각하게 한다. 212쪽에서 범위 검사: 배열 등의 범위 검사가 언어에 포함되고 null 참조도 검사한다. | "Ada enforces data typing" | |
| F13-163 | 233 | 11.1.6절 권고: 가장 안전한 언어는 Ada95와 Ada83과 SPARK 부분집합이다. Ada 프로그래머를 찾고 유지하기 어렵다는 점이 다른 언어를 고르는 이유 중 하나다. 새 언어의 학습은 일정과 결함률에 영향을 주므로 익숙한 언어에 남는 것이 최선일 때가 많다. | "Often staying with a well-understood language is the best choice." | 인용 앞 문장에서 언어와 개발자의 숙련도 비용을 따진다 |
| F13-164 | 233 | Ada 외의 언어, 특히 C, assembly, Forth를 고르면 한계를 알고 coding standard를 만들어 집행하고, 검사와 분석과 시험에 더 시간을 쓰고, 개발자를 그 언어의 모범 실천과 함정에 대해 교육한다. | "especially C, assembly language, or Forth" | |
| F13-165 | 215 | 11.1.4.3절 C: C는 유연하지만 많은 오류의 길을 열고, 개발과 검증 도구의 환경과 인력 풀은 크다. 정의의 엄밀함이 안전이 중요한 용도에 모자란다. C를 고르면 코드와 data 순서의 철저한 검증과 시험의 부담이 개발자에게 있다. | "the burden is on the developer to provide a thorough verification of code" | 문장에 "dozens of dialects of C"도 있다 |
| F13-166 | 215 | C는 강한 타입 언어가 아니고 기본 형과 포인터의 암묵 변환을 허용한다. C에서는 정수 계산이 overflow하지 않음을 보이기 어렵다. 부호 없는 정수 산술은 word 길이의 modulo로 overflow 검출이 없다. | "In C it is difficult to show that any integer calculation cannot overflow" | 부호 없는 산술에 대한 서술은 같은 쪽 다음 문장이다 |
| F13-167 | 215 | C는 어느 주소를 가리킬지 제한하지 않고 포인터 산술을 허용한다. C 언어를 일부 구성으로 제한하는 것은 필요한 기능이 사라져서 실현 가능하지 않다고 지침서는 쓴다. 대신 표준의 엄격한 집행이 흔한 오류를 줄인다. | "Restricting the C language to certain constructs would not be feasible" | 2004년의 판단이다. 같은 지침서가 coding standard를 사실상의 부분집합이라 부른다 (F13-121). 두 서술이 어긋나 보인다 (기억) |
| F13-168 | 216 | C의 한계: 포인터 (배열을 넘어 stack을 깨는 오류), 배열과 문자열의 bound 검사가 없음 (검사를 감싸는 wrapper 함수를 쓸 수 있고 실행 시간이 늘어난다), void* 형 변환은 컴파일과 실행 때 검사가 없음. | "C does not provide any bounds checking on arrays and strings" | |
| F13-169 | 216 | 부동 소수점: ANSI C는 구현 방식을 정하지 않아서 컴파일러마다 구현이 다르고, 지침서의 예에서 계산 결과가 컴파일러마다 크게 다르며 모두 틀린다. | "The ANSI C standard does not mandate any particular implementation for floating point" | 예의 수식은 지침서가 거듭제곱을 인쇄하는 방식이 추출된 글자에서 깨졌으므로 옮기지 않는다 |
| F13-170 | 216 | 전역 변수는 모든 함수에 입력 인자와 같다. 변수가 100개인 프로그램에서 인자 2개인 함수는 사실상 인자 102개이므로 검증이 매우 어렵다. 다중 thread에서 여러 thread가 변수를 제어한다고 믿고 바꾸는 문제도 생긴다. | "a program with 100 global variables, actually has 102 parameters" | Toyota 전역 변수 수와 이어진다 (F13-208, F13-209) |
| F13-171 | 217 | 흔한 C의 실수 목록: = 와 == 혼동, & 와 && 혼동, 제어 구문 뒤의 세미콜론, break를 빼먹은 fall-through, 부호 있는 수와 부호 없는 수의 비교. 또 매크로와 부작용 (++)의 조합. | "Comparing signed and unsigned variables" | 항목 하나를 인용했다 |
| F13-172 | 218 | 동적 메모리를 단순히 금지하는 것이 반드시 최선은 아니다. 경고 없이 메모리 한계를 넘을 위험이 늘기 때문이다. | "prohibiting dynamic memory management is not necessarily the best course" | 앞 문장은 참고 문헌 [54]를 가리킨다. 이 쪽은 11.1.4.3의 끝이다 |
| F13-173 | 218 | C의 표준에 최소한 넣을 것: 우선순위에 괄호를 쓴다, 매크로에 괄호를 쓴다, 복잡한 매크로를 쓰지 않는다, 명시적으로 형 변환한다, void* 를 피한다, 배열 bound를 검사한다, 함수 prototype을 쓴다, 전역을 최소로 한다, switch에 default를 둔다, 재귀를 가능하면 피한다, 오류 처리와 상태 기록을 충분히 한다. | "Avoid recursion when possible." | 최소 목록이며 항목은 열한 개다 |
| F13-174 | 219 | C에서 정의되지 않았거나 구현에 따라 다른 동작의 목록을 낸 책 (Safer C 등)을 가리킨다. 지침서는 C의 일반 점검표가 부록 B에 있다고 적지만, C의 점검표는 부록 H.5와 H.8에 있다. | "lists of undefined or implementation defined behaviors" | 쪽 번호의 "Appendix B" 서술은 오기로 보인다 (기억). 부록 H.5, H.8은 F13-180 이하 |
| F13-175 | 220 | 11.1.4.4절 C++: C의 확장으로 객체지향을 더했고 C보다 강하게 형을 검사한다. 하지만 C의 많은 단점을 그대로 갖는다. 표준이 되는 안전한 부분집합은 지침서가 쓴 때 없었다. | "However, C++ suffers from many of the same drawbacks as C" | 부분집합 부재는 같은 쪽 다음 줄에 있다 (원문은 safe subset이 굽은 따옴표 안에 있다) |
| F13-176 | 221 | C++ 오류를 줄이는 실천: 다중 상속 금지, 상속 단계 최소, 포인터 최소, alias 금지, 식과 함수 호출에 부작용 금지, RTTI 금지, 전역 변수 피하기, 소멸자가 메모리를 모두 해제, 템플릿은 신중하게 (STL은 thread-safe가 아니다). | "Use templates with care, including the Standard Template Library" | 2004년경 C++의 판단이며 오늘의 C++ 표준에는 맞지 않는 항목이 있다 (기억) |
| F13-177 | 234 | 11.2절 도구: 도구는 오류를 가능한 한 많이 일찍 찾는 것이 목적이다. 도구는 표준을 기본으로 집행하고, 문서에 한계가 적혀 있어야 하고, 쓰기 쉬워야 한다. 도구가 불편하면 프로그래머가 우회한다. | "Knowing what the tool cannot do is as important as what it can do" | |
| F13-178 | 235 | 컴파일러를 고를 때 물을 것: 경고를 오류로 다룰 수 있는가 (그것이 기본 설정인가), 컴파일러 결함의 목록이 있는가, 최적화 옵션 (크기, 속도, 없음), embedded용 지원 (비트 필드, interrupt handler), run-time library의 소스가 있는가. | "Can warnings (possible problems) be treated as errors?" | |
| F13-179 | 236 | 보조 도구: lint는 컴파일러가 놓치는 문제를 찾고 표준을 벗어나면 오류로 다룬다. memory check 도구는 누수와 범위 밖 쓰기를 찾는다. | "finds problems in the code that compilers might miss" | |
| F13-180 | 366 | 부록 H.5 일반 (언어 독립) 실천: 동적 메모리를 최소로 쓰고 일찍 해제하고 할당을 추적한다, 변수를 쓰기 전에 초기화한다, 제어 흐름 복잡도를 최소로 하고 표준에 중첩 깊이 한계를 둔다, 계산의 정밀도와 정확도를 충분하게 한다, 괄호로 우선순위를 명시한다, 부작용이 있는 함수를 피한다. | "Minimize use of dynamic memory" | 출처는 NUREG/CR-6463 부록 B다 |
| F13-181 | 366 | 큰 routine에서는 진입점과 출구점을 하나로 하되, 작은 subprogram에서는 출구가 여럿이어도 더 읽기 쉬울 수 있어 허용한다. | "In larger routines, use single entry and exit points in subprograms" | 4.6절의 "only one entry and one exit point"와 다르게 조건이 붙는다 (F13-115) |
| F13-182 | 371 | 부록 H.8 C의 실천: 재귀는 아주 조심해서 쓴다 (stack overflow가 흔하다. 재귀가 유한한지 확인한다), 배열 경계 검사 함수를 쓴다, gets를 쓰지 않는다, memcpy 대신 memmove를 쓴다, switch에 default를 명시한다, 지역 변수를 초기화한다, 전역 변수는 별도 routine에서 초기화한다 (warm reboot에서 맞게 설정되도록), 함수 포인터를 피한다. | "Use recursive functions with great care. Stack overflows are common." | 항목 일부를 옮겼다 |
| F13-183 | 372 | H.8 계속: bit field 대신 bit mask를 쓴다 (bit field는 구현에 따라 다르다), 부호 있는 수와 없는 수를 섞지 않는다, 형 변환을 명시한다, 부동 소수점을 0과 비교하거나 정확한 같음을 기대하지 않는다, 형 크기 (예: int)를 가정하지 않는다. | "Do not make assumptions about the sizes of dependent types, such as int" | 정수 크기와 구현 정의 동작의 근거다 |
| F13-184 | 372 | H.8: 컴파일러 경고를 켜고 읽고, 가능하면 경고를 오류로 한다. interrupt 서비스 routine 안에서 함수를 부르지 않고, 불러야 하면 작고 재진입 가능한 함수만 쓴다. 표준 library 함수는 다중 task에서 재진입이 안 될 수 있다. | "Enable and read compiler warnings. If an option, have warnings issued as errors." | 경고 수준에 대한 이 지침서의 가장 직접적인 서술이다 |
| F13-185 | 76 | 소프트웨어 안전 기능의 예로 inhibit, trap, interlock, assertion을 든다. | "inhibits, traps, interlocks, and assertions" | assertion은 이 지침서에서 용어로 나올 뿐 방어적 프로그래밍의 기법으로 서술되지 않는다. 용어집 (298쪽)의 정의는 프로그램 상태를 지정하는 논리식이다 |

## 3. koopman-toyota-ua (Koopman, A Case Study of Toyota Unintended Acceleration and Software Safety, 2014. PDF 쪽 = slide 번호 + 0)

Koopman은 Toyota 소송에서 원고 쪽 전문가였다. 이 자료는 그 입장에서 쓴 발표이며, slide가 인용하는 근거는 NASA 보고서 부록 A와 법정 증언 (Bookout 재판)이다. 이 절의 사실은 모두 "원고 쪽 전문가의 분석"으로 읽는다.

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| F13-200 | 35 | MISRA C는 자동차용으로 개발된 C의 더 안전한 부분집합이라고 slide는 소개한다. Toyota의 infotainment 소프트웨어 자료로, coding rule 위반 30건에 "major bug" 하나가 있을 것으로 기대된다고 인용한다 (Kawana 2004). | "MISRA C is a safer subset of C programming language" | 위반 수와 결함 수의 관계는 한 자료의 수치이며 slide는 근거 자료를 인용으로만 둔다 |
| F13-201 | 36 | Toyota는 자기 coding rule이 MISRA C와 50% 겹친다고 주장했으나 Toyota의 coding rule 안에 들어 있는 MISRA C 규칙은 11개뿐이다. | "But only 11 MISRA C rules out of MISRA C in the Toyota coding rules" | |
| F13-202 | 36 | Toyota가 자기 coding rule을 항상 지키지는 않았다. 예로 switch 343개 중 105개에 default가 없다. 2002 모델 해의 코드에 MISRA를 쓰지 않은 이유는 coding rule이 1998년의 MISRA C보다 앞선다는 것이었다. | "Toyota did not always follow its own coding rules" | 근거는 NASA 부록 A 21 - 23쪽, 28쪽으로 표기된다. 부록 A는 받은 문서에 없다 |
| F13-203 | 36 | NASA의 도구가 쉽게 검사할 수 있었던 MISRA C 규칙 35개 중 14개가 위반되었고 위반이 7,134건이다 (대부분 매크로 사용과 #undef). 원고 쪽 Barr의 팀은 MISRA C 위반 80,000건을 찾았다. | "14 of 35 rules violated; 7,134 violations" | 80,000건은 원고 쪽 증언 인용이며 NASA의 수치와 세는 방법이 다르다 |
| F13-204 | 37 | NASA가 여러 정적 분석 도구를 썼다. Toyota는 이 도구들에서 경고가 없다고 주장하지 않았으나 결과는 참고가 된다고 slide가 적는다. Coverity: 선언했지만 참조하지 않은 것 97건, 재귀 포함 5건. | "Toyota did not claim warning-free on these" | 도구별 결과가 다른 항목을 센다. 도구 하나로는 전부 못 본다는 근거로 쓸 수 있다 |
| F13-205 | 37 | CodeSonar: 전역 변수가 다른 형으로 선언됨 2272건, 값을 바꾸는 cast 333건, 조건에 부작용 99건, 전역 중복 선언 64건, 초기화 안 된 변수 22건. Uno: 초기화되지 않았을 수 있는 변수 89건, 16바이트 배열에 17바이트를 초기화한 것 2건. | "global variable declared with different types" | 인용은 CodeSonar 항목의 하나다 |
| F13-206 | 38 | McCabe complexity가 50을 넘으면 "시험할 수 없다"고 본다 (slide의 판단). Toyota ETCS 코드에는 complexity가 50을 넘는 함수가 67개 있다. throttle 각도 함수는 complexity 146이고 1300줄이며 unit test 계획이 없었다. | "67 functions with complexity over 50" | 근거는 재판 증언 (Bookout 2013-10-14). 한계값 50은 Koopman의 관점이다. NASA 지침서는 10을 권한다 (F13-136) |
| F13-207 | 39 | 전역 변수는 어느 모듈에서나 읽고 쓸 수 있다. 지나친 전역 사용은 모듈성을 해치고, 한 곳의 코드 변경이 전역을 통해 다른 곳에 영향을 준다. slide는 이를 "data flow spaghetti"라 부른다. | "Excessive use of globals tends to compromise modularity" | |
| F13-208 | 40 | 쓰기 가능한 전역의 이상적인 수는 0이다. 적당한 const 값과 설정 data는 괜찮다. Toyota 코드는 read-only와 text 변수 4,720개, read/write 변수 11,253개를 갖는다. | "Ideal number of writeable globals is ZERO" | NASA 부록 A 33쪽의 수치다. 도구마다 세는 규칙이 달라 수치가 다르다는 주석이 있다 |
| F13-209 | 40 | 전역 변수는 9,273개에서 11,528개로 세어진다. 캠리 소프트웨어의 data 객체 82%가 모든 실행 task가 접근할 수 있는 무제한 범위로 선언되었다. NASA의 분석은 지역 static으로 할 수 있는 것 6,971건, 파일 static으로 할 수 있는 것 1,086건을 찾았다. | "declared with unlimited scope and accessible to all executing tasks" | 82% 문장은 NASA 부록 A의 인용이다. 범위 축소 가능 건수는 slide의 출처 표기대로 부록 A 30쪽이다 |
| F13-210 | 41 | 한 CPU에서 task들이 번갈아 쓰는 환경에서 동시성 결함은 잘못된 data 공유에서 온다. 한 가지 대책은 읽기 전에 interrupt를 막아 한 번에 한 task만 읽고 쓰게 하는 것이다. 결함은 재현이 어렵다. | "often difficult to reproduce" | 이 slide는 일반 설명이며 Toyota의 사례는 다음 쪽이다. 깨지는 짧은 예는 없다 |
| F13-211 | 42 | NASA가 구체적인 동시성 결함을 하나 찾았다. 중첩된 scheduler의 unlock, 공유 전역 변수가 모두 volatile은 아니다. 공유 전역이 interrupt를 막지 않고 접근되기도 한다. | "Shared globals not always access with interrupts masked" | slide의 원문 (access)을 그대로 옮겼다. 근거는 NASA 부록 A 33 - 34쪽이다. 결함의 구체적 내용은 이 slide에 없다 |
| F13-212 | 43 | 안전 규칙은 보통 재귀를 금한다. stack overflow의 위험이 있고, ETCS 같은 시스템에 필요한 검증 (V&V)을 불가능하게 하기 때문이다. Toyota ETCS는 재귀를 쓴다. | "Safety rules typically forbid recursion" | 근거로 NASA 부록 A 129쪽을 든다 |
| F13-213 | 43 | Toyota의 stack은 재귀를 제외하고도 94% 찼다. stack overflow를 막는 조치가 없었고, overflow가 항상 system reset을 낳는다는 잘못된 가정이 있었다. stack 바로 뒤의 메모리는 OSEK RTOS의 영역이다. | "Stack is 94% full PLUS any recursion" | 근거는 재판 증언 (Bookout 2013-10-14 PM)과 NASA 부록 A 130쪽이다 |
| F13-214 | 44 | watchdog를 올바로 쓰는 법: timer tick interrupt 서비스 routine에서 먹이를 주는 것은 대체로 나쁜 징후이고, 어느 한 task의 죽음이라도 먹이 주기를 막아야 한다. 이를 위해 먹이 주기 전에 모든 task의 liveness를 확인한다. | "Kicking from timer tick interrupt service routine usually a bad sign" | NASA 지침서 4.6절의 같은 주장 (F13-102)과 일치한다 |
| F13-215 | 45 | Toyota ETCS의 watchdog는 hardware timer 서비스 routine에서 먹이를 받고, RTOS의 오류 코드 (task 죽음)를 무시하며, throttle 각도 계산과 대부분의 failsafe를 담은 Task X의 죽음을 못 본다. 1 msec task의 죽음만 본다. | "Watchdog kicked by a hardware timer service routine" | 근거는 재판 증언이다. Toyota 쪽 주장은 이 slide에 없다 |
| F13-216 | 47 | 기타 문제로 slide가 든 것: 한 task에 throttle 계산과 failsafe가 몰려 있음, 인증받지 않은 OSEK RTOS와 80% CPU 부하 (RMA 한계 70% 초과), 75줄을 넘는 함수 200개, 비형식 검토, configuration 관리 없음, bug 추적 체계 없음, 형식 명세 없음. | "200 functions exceeded 75 lines of non-comment code" | 근거는 재판 증언과 NASA 부록 A 23쪽이다 |
| F13-217 | 55 | NASA는 worst-case 실행 시간 분석이 busy-wait loop와 간접 재귀 때문에 너무 어렵다고 보았다. 다만 deadline을 놓친 사례는 보지 못했다. | "Timing analysis too difficult for NASA" | 재귀가 시간 분석을 가로막는 구체적 사례다 |
| F13-218 | 31 | slide는 하드웨어 bit flip 하나가 task 전체를 죽일 수 있고, 잘못된 포인터가 관련 없어 보이는 함수를 망가뜨릴 수 있다고 쓴다. 한 fault containment region이 자신의 모든 고장 모드를 스스로 감시할 수 없다. | "A wild pointer can corrupt a seemingly unrelated function" | 포인터 오류가 영역 밖으로 번진다는 근거. 코딩 규칙만으로 막지 못하므로 구조에서 격리해야 한다는 주장의 바탕이다 |
| F13-219 | 48 | slide는 이 재판이 민사임을 밝힌다. 민사의 판정 기준은 "More likely than not"이고 형사의 "합리적 의심의 여지 없음"과 다르다. 제품 결함은 합리적인 주의, 곧 받아들여진 관행을 따랐는가를 본다. | "More likely than not" | 법적 맥락이다. 결함의 원인이 유일하지 않아도 그럴듯한 원인이면 된다는 서술이 같은 쪽에 있다 |
| F13-220 | 50 | 자료의 출처는 NASA와 NHTSA의 보고서 (상당 부분 가려짐), 재판 자료, Toyota 쪽 전문가의 Exponent 보고서, 원고 쪽 변호사의 시간표다. 51쪽의 감사 인사는 원고 쪽의 소스 코드 검토팀과 NASA의 검토팀을 든다. | "Bookout Trial materials" | 이 자료가 한쪽 당사자의 전문가가 만든 것이라는 근거다 |

## 4. nasa-toyota-ua-report (NASA NESC, Technical Support to NHTSA on the Reported Toyota Motor Corporation Unintended Acceleration Investigation, 2011. PDF 쪽 = 인쇄 쪽 + 0)

받은 PDF는 본 보고서 177쪽이다. Koopman이 인용하는 부록 A (소프트웨어 분석 상세)는 이 PDF에 들어 있지 않다.

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| F13-300 | 148 | 소프트웨어 분석 대상은 2005 모델 해 Camry L4의 ECM 소프트웨어다. 연구는 2010년 4월 중순에서 8월 중순까지 했다. 잠재 소프트웨어 원인을 코딩 결함, 알고리즘 결함, task 간섭 (race condition, data 손상), 결함 보호 부족의 네 범주로 나눈다. | "Coding defects (implementation)" | |
| F13-301 | 148 | 코딩 결함 범주의 서술: 소프트웨어 언어가 들어올 수 있는 결함의 종류를 어느 정도 정한다. coding standard는 구현 기법을 제한하고 코드 검사를 강화해서 결함이 들어오는 것을 줄일 수 있다. 이번 연구에서는 도구로 코드 검사를 자동화해 coding standard에 대조했다. | "by constraining the implementation techniques used and enhancing code inspections" | |
| F13-302 | 149 | 정적 분석 도구 셋: Coverity는 흔한 결함을 큰 코드에서 짧은 시간에 찾고 경고 수를 최소로 줄이는 필터를 쓴다. CodeSonar는 더 오래 걸리지만 더 깊은 경로 분석으로 미묘한 결함을 찾는다 (JPL coding standard의 검사기를 더한 판을 썼다). Uno는 연구용으로 빠르고 단순한 분석을 한다. | "can reveal more subtle types of defects and suspect coding patterns" | 도구의 분석 시간, 깊이, 경고 수 사이의 균형이 도구마다 다르다는 근거다 (F13-018) |
| F13-303 | 149 | Uno가 겨냥하는 세 가지 흔한 결함은 초기화하지 않은 변수의 사용, nil 포인터 역참조, 배열 범위 밖 접근이다. | "Nil-pointer dereferences, and out-of-bounds array indexing" | |
| F13-304 | 151 | 관찰 O-6: 이 소프트웨어는 개발 과정에서 자체 개발한 coding standard를 썼으므로, 업계 표준의 정적 분석 도구는 업계 표준 구현에 바탕을 둔 자동 검사만 한다. 그래서 코드 검사에 특별한 도구와 수작업이 필요했다. 설계 취약점으로 이어지지는 않았다고 NASA는 쓴다. | "The TMC software development process uses a proprietary developed coding standard" | 같은 내용이 관찰 목록 (173쪽)에 되풀이된다 |
| F13-305 | 152 | 발견 F-10: 정적 분석, 논리 model 시험, 재귀 시험, 최악 실행 시간 분석을 포함한 광범위한 시험과 분석을 했다. 쓴 도구들로는 단독으로 UA를 일으키는 소프트웨어 결함을 찾지 못했다. | "software defects that unilaterally cause a UA were not found" | 같은 발견이 172쪽에도 있다. 이 결론은 "소프트웨어가 안전하다"는 판정이 아니라 쓴 도구로는 그런 결함을 찾지 못했다는 것이다. Koopman slide는 같은 코드에서 규칙 위반과 복잡도를 문제로 든다 (기억, 해석) |
| F13-306 | 20 | 실행 요약: 현재 차량은 너무 복잡해서 합리적인 양의 분석이나 시험으로도 전자 장치와 소프트웨어에 오류가 없음을 증명할 수 없다. 그러므로 UA를 일으킨 증거가 없다는 것이 시스템을 무죄로 하지 않는다. | "no reasonable amount of analysis or testing can prove electronics and software have no errors" | 정적 분석 등의 결과를 해석하는 한계의 서술이다 |

## 찾지 못한 것

- Rust: 받은 문서 네 개 어디에도 없다 (pdftotext 전체 검색). Ada/SPARK는 NASA 지침서 11.1.4.1 (211 - 212쪽)과 11.1.6 (233쪽)에 있으나 2004년경의 서술이다.
- MISRA C, MISRA C++, CERT C의 규칙의 내용: 받은 문서에 없다. MISRA Compliance:2020에 예로 나오는 규칙 문장과 번호는 본문 예시용이며 F13-031, F13-066, F13-077에만 문서가 쓴 대로 옮겼다. 규칙의 뜻을 확정하는 근거로는 쓰지 않는다.
- undefined behavior 자체의 정의와 예: NASA 지침서는 "undefined by the standard", unspecified compiler behavior, 평가 순서 같은 말로만 다룬다 (F13-119, F13-157). undefined behavior의 정의와 정수 overflow의 부호 있는 경우의 서술은 없다.
- 부동 소수점의 위험: NASA 지침서의 짧은 서술 (F13-169, F13-183)뿐이다. NaN, 비교, 반올림의 체계적인 서술은 없다.
- 정수 overflow와 형 변환의 사례: 이 문서들에는 일반 서술만 있다. Ariane 501 보고서는 스캔본이라 이번에 읽지 않았다 (지시에 따름).
- assert 문과 assertion의 방어적 프로그래밍에서의 쓰임: NASA 지침서 7.4.6에 없다. 용어집과 안전 기능 목록에만 나온다 (F13-185). 실패했을 때의 안전한 값은 범위 검사의 "기본값으로 바꾸기" (F13-128)와 안전 상태로 초기화 (F13-113)로만 다룬다.
- volatile: NASA 지침서에 키워드로 없다. Koopman slide 42가 "shared globals not all volatile"이라고 적을 뿐이다 (F13-211). 컴파일러 최적화와 volatile의 관계의 서술은 없다.
- 컴파일러 경고 수준: NASA 지침서 (F13-178, F13-184)와 MISRA Compliance 2.6.4 (F13-025)의 짧은 서술이 전부다. 구체적인 경고 option의 서술은 없다.
- 정수 형의 크기: MISRA Compliance가 도구 설정의 예로 들 뿐이다 (F13-026, F13-027). NASA 지침서 H.8도 크기를 가정하지 말라고 한다 (F13-183).
- interrupt와 공유 data가 깨지는 짧은 예와 대책 (critical section, 이중 buffer): 받은 문서에 없다. NASA 지침서는 interrupt 분석의 질문과 점검 영역 (F13-143, F13-144)과 설계 data 분석의 지침 (F13-147)을 주고, Koopman은 "interrupt를 막고 읽는다"는 한 가지 대책을 말한다 (F13-210).
- 정적 분석 도구의 decidable 규칙과 undecidable 규칙의 목록: MISRA Compliance는 분류와 이유만 주고 규칙별 분류는 주지 않는다. 규칙별 분류는 MISRA C 규칙 문서에 있고 받지 않았다.
- NASA 지침서에 동적 메모리, 재귀, 전역 변수를 "금지한다"는 규칙은 없다. 최소로 쓰고 (F13-180), 조심하고 (F13-182), 단순 금지는 최선이 아니라고 (F13-172) 적는다.
- Toyota 부록 A (NASA 소프트웨어 분석의 상세): Koopman slide가 인용하는 수치의 원문이지만 받은 PDF에 없다. 수치는 Koopman slide로만 확인된다.

## 계획의 "근거 위치" 표와 어긋난 쪽

- `misra-compliance-2020` 계획표의 쪽 (10 - 19, 20 - 27, 28 - 31, 33 - 39)은 PDF 쪽으로 맞다. 단, 부록 A, B, C는 33, 34 - 36, 37쪽이고 용어집이 38 - 39쪽이다. 계획표의 "7절 준수 주장 (7.1 - 7.3)"은 실제로 7.1 - 7.4 (28 - 31쪽)이다.
- `nasa-gb-8719-13` 계획표의 "4.6, 7.4.5 - 7.4.8 (93 - 98, 146 - 152)"은 맞다. 7.4.8 복잡도는 149 - 151쪽, 8.4.1은 169 - 170쪽이고 8.5.4, 8.5.5는 174 - 175쪽이다 (표의 169 - 174와 거의 맞다). 11.1은 계획표 쪽 208 - 233과 일치한다. 인쇄 쪽은 PDF 쪽보다 1이 작다.
- 계획표의 "11.1.4 Languages"에 C++ 쪽과 Ada 쪽이 따로 있다. Ada는 211 - 212쪽, C는 215 - 219쪽, C++는 219 - 221쪽이다.
- NASA 지침서의 부록 H (365 - 372쪽 근처)는 계획표에 없으나 방어적 프로그래밍과 C 실천의 점검표가 있어 이 파일에서 뽑았다. 6.5.4절 (118쪽)과 7.5.7절 (160쪽)도 같은 이유로 더했다.
- `koopman-toyota-ua` 계획표의 "slides 35 - 43"은 맞다. slide 번호와 PDF 쪽이 같다. 계획표에 없는 slide 44 - 45 (watchdog), 47 (기타 문제), 55 (시간 분석)를 더했다.
- 계획표의 "interrupt와 공유 data의 깨지는 예: nasa-gb p94 - 97"은 4.6절의 일반 지침만 담고 깨지는 예는 아니다. 8.5.5절 interrupt 분석 (174 - 175쪽)이 더 직접적이다.
- `ariane-501-report`는 지시에 따라 읽지 않았다.
