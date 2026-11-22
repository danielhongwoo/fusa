# 단계 2 묶음 4 검토, 1회차: functional safety 전문가

- 역할: functional safety 전문가. 모델: Claude Opus 5.5 (에이전트). 날짜: 2026-11-23. 기준 commit 1a059b5. 다른 검토자의 의견은 보지 않았다.
- 대상: ch15 (새 초고), ch16 (깊은 수정), ch17 (새 초고). 부록 A에 더한 스물아홉 항목 (1a059b5의 diff). example/drive-torque/docs/tools.md, test-report.md 1절과 6절.
- 읽은 것: 위 원고 전부, tools.md 전부, test-report.md의 요약과 바뀐 줄, 부록 A의 diff, Makefile의 `static`과 `skipped`, notes/tool-check.md의 MC/DC 줄, notes/claims.md에서 웹 주소. 읽기 메모 (ch15 - ch17-facts.md, ch15-17-web-facts.md)는 웹 출처의 판과 주소를 찾는 데만 썼다. 판정은 문서를 직접 열어 했다.
- 대조한 것: 받은 문서의 쪽 (nasa-gb-8719-13 31쪽, nasa-mcdc-tutorial 7쪽, nasa-std-8739-8b 7쪽, Ariane 501 보고서 PDF 10 - 13쪽은 tesseract로 OCR). 진행자가 열지 않았다는 웹 출처를 먼저 열었다: AFuzion, LDRA (PDF를 받아 pdftotext), Rapita Systems, AbsInt, Conrad 외 (MathWorks의 PDF를 받아 pdftotext), Schildbach (arXiv PDF를 받아 pdftotext). 진행자가 연 것 가운데 Intertek은 내용이 걸려서 다시 열었다. Cousot, Astree, IKOS, CPROVER, Butler와 Finelli, Jia와 Harman, MathWorks, Synopsys, Jordan, FAA Order 8110.49, Yang, Wang, Siemens, Embitel, Renesas, Schabe와 Braband, UL은 열지 않았다.
- 돌린 것: 없다. Makefile을 읽었다.
- `(실무)`가 붙은 것은 받은 문서가 아니라 내 실무 지식에서 나온 것이다. 규격의 내용에 닿는 것은 `(확인 필요)`다.

## 지적

### A 등급

F-01 [A] 16장 129행의 "충분히 test했다"의 뜻: "정한 세 물음에 답했고, 남은 것을 적었다."
- 문제 1, 적는 것과 받아들이는 것이 다르다: 남은 것을 적었다는 것만으로는 충분하지 않다. 남은 것마다 그것을 맡는 다른 수단이 있거나 받아들일 수 있다는 논증이 있어야 한다. 바로 뒤 문장 ("남은 것은 test가 아닌 수단과 설계의 수단이 맡는다")이 그 뜻을 품고 있지만, 정의 자체에는 없다. 독자는 "빈 곳을 목록으로 적었으니 충분히 test했다"를 배운다. 이 책의 예제가 실제로 그렇게 읽힐 위험이 있다. 예제의 test는 모두 host의 실행 파일이고, 그것을 "남은 것"에 적었다.
- 문제 2, 환경의 물음이 빠졌다: 세 물음은 무엇을 test했는가와 test가 얼마나 좋은가를 묻는다. 그 test가 내보내는 것에 대해 말하는가는 묻지 않는다. 같은 장이 NASA 지침서를 들어 안전 test는 하드웨어와 소프트웨어를 모두 갖춘 최종 시스템에서 해야 한다 ("must")고 옮기고 (113행, nasa-gb 190쪽), coverage를 잰 실행 파일과 내보내는 실행 파일이 다를 수 있다고 적는다 (117 - 119행). 그런데 결론의 정의에는 이 물음이 없다. 결론만 읽으면 host에서 세 물음에 답한 test가 "충분한" test가 된다.
- 근거: nasa-gb-8719-13 190쪽 ("Safety testing must be performed on the final system, both hardware and software"), 194쪽. (실무) 자동차에서도 test 환경이 target을 얼마나 대표하는지는 test 계획의 일부로 정당화한다 `(확인 필요)`.
- 고칠 방법: 129행을 이렇게 쓴다. "이 책은 '충분히 test했다'를 네 물음에 답한 것으로 쓴다. 요구사항을 모두 test했는가, 코드를 빠짐없이 실행했는가, test가 결함을 잡는가, 그 test가 내보내는 것 (target의 build와 하드웨어)에 대해 말하는가. 그리고 답이 '아니다'인 곳마다 그것을 맡는 다른 수단이나 받아들이는 까닭을 적었다. 적어 두기만 한 빈 곳은 충분하다는 근거가 아니다." 예제 표 (137행)에 넷째 줄을 더한다: "test가 내보내는 것에 대해 말하는가 | 아니다. host의 실행 파일뿐이다 | 남은 것: target의 compiler, 실행 시간 (17장, tools.md 4절)".

### B 등급

F-02 [B] 도구가 없으면 `make check`가 통과한다 (Makefile의 `static`, `coverage`, `prove`, `skipped`. 15장 80행, 17장 87행, tools.md 3절의 마지막 줄).
- 문제: 15장은 "검사 단계가 있다는 것과 그 단계가 실패를 알린다는 것은 다른 일"을 교훈으로 적고, clang-tidy의 경고를 실패로 바꾼 일을 든다. 그런데 같은 모양이 남아 있다. cppcheck, clang-tidy, GCC 14 이상, cbmc가 없으면 그 단계를 "건너뜀"으로 적고 지나가고, `skipped`는 `STRICT=1`일 때만 실패한다. 그리고 `STRICT=1`은 구현 예정 요구사항 때문에 늘 실패하므로 아무도 쓰지 않는다. 곧 CBMC가 없는 컴퓨터에서 `make check`는 증명 없이 통과한다. clang-tidy 쪽도 명령의 종료 상태를 `|| true`로 버리고 출력의 "warning:", "error:"만 센다. 도구가 그런 말 없이 죽으면 "경고 0개"가 된다.
- 근거: Makefile 40, 130 - 148, 178 - 180행.
- 고칠 방법: 건너뛴 단계를 구현 예정과 따로 다루어, 도구가 하나라도 없으면 `make check`가 실패하게 한다 (예: `SKIP_OK=1`을 줄 때만 지나간다). clang-tidy의 종료 상태도 본다. 그렇게 하지 않으면 15장 80행에 "도구가 없으면 그 단계는 건너뛰고 `make check`는 통과한다"를 한 줄 적고, tools.md 4절의 표에 넣는다.

F-03 [B] 15장 67 - 74행 방법의 표: "보장하는 것" 칸이 도구와 증명의 전제를 빼고 적혀 있다.
- 문제: 이 장은 82 - 116행에서 가정 (`__CPROVER_assume`)이 증명이 보는 상태를 좁힌다는 것을 공들여 보이고, sim의 표 (140행)에는 "(전제 아래에서)"를 붙였다. 그런데 결론의 표에서 bounded model checking은 "펼친 한계 안의 모든 입력에서 단언이 성립한다", abstract interpretation은 "검사하는 종류의 오류가 모든 실행에서 없다"로만 적혀 있다. (실무) sound한 분석기의 "모든 실행"은 분석기에 준 설정 (target의 형 크기와 ABI, 입력이나 volatile 변수의 값 범위, 알 수 없는 함수의 stub) 아래의 모든 실행이다 `(확인 필요)`. 표만 읽는 독자는 이 전제를 놓친다.
- 고칠 방법: 두 줄의 "보장하는 것"을 "harness가 만든 환경과 가정 (assume) 아래에서, 펼친 한계 안의 모든 입력에서 ...", "분석기에 준 설정 (target, 입력의 범위) 아래에서 모든 실행에서 ..."로 쓰고, "보장하지 못하는 것"에 "가정과 설정이 실제와 맞는다는 것"을 더한다.

F-04 [B] 17장 60행과 부록 A의 proven in use: "IEC 61508의 proven in use는 하드웨어의 무작위 고장률을 운용 이력으로 정당화하는 길이고 체계적 능력의 요구를 대신하지 않는다" (Intertek).
- 문제: Intertek의 글이 그렇게 적는 것은 맞다 (다시 열어 확인했다). 그러나 그 글이 다루는 것은 하드웨어의 Route 2H이고, 같은 글이 체계적 능력은 "Route 1S/2S"로 보여야 한다고 적는다. (실무) IEC 61508에서 Route 2S는 체계적 능력을 proven in use로 보이는 길이라고 알고 있다 `(확인 필요)`. 원고의 문장을 IEC 61508 전체에 대한 말로 읽으면, 독자는 "61508에서 사용 이력은 체계적 고장에 대해 아무것도 말하지 못한다"를 배운다. 출처 하나를 그 출처가 다룬 범위보다 넓게 옮긴 것이다.
- 근거: Intertek, "Exploring the IEC 61508 proven-in-use concept" (2026-01-22, 2026-11-23에 열어 봄): Route 2H, "Systematic capability ... must still be demonstrated via Route 1S/2S".
- 고칠 방법: "시험 인증 회사 Intertek의 글은 IEC 61508의 하드웨어 쪽 proven in use (Route 2H)를 설명하면서, 그것은 무작위 고장률을 운용 이력으로 정당화하는 길이고 체계적 능력은 따로 보여야 한다고 적는다 `(2차 자료)`. 체계적 능력 쪽에도 사용 이력에 기대는 길 (Route 2S)이 있다고 같은 글이 이름만 든다. 이 책은 그 조건을 확인하지 못했다." 부록 A의 proven in use 항목도 같게 고친다.

F-05 [B] 15장 17행과 129 - 132행: review가 요구사항 자체를 의심하게 해 주는 유일한 수단처럼 적혀 있다. 그런데 그 review를 한 예제의 기록이 보이는 것은 같은 계열의 모델 둘이다.
- 문제: 표 (69행)는 review가 "요구사항 자체를 의심할 수 있다"를 보장한다고 적는다. 132행이 한계를 밝히지만, 표에는 그 조건 (검토자가 만든 쪽과 독립이고, 그 분야의 지식이 있을 때)이 없다. (실무) 자동차의 확인 검토 (confirmation review)와 감사에서는 검토자의 독립의 정도가 등급에 따라 정해진다고 알고 있다 `(확인 필요)`. review의 보장은 누가 읽었는가에 달려 있다는 것을 표에서 말하지 않으면, 독자는 "review를 했다"를 근거로 쓴다.
- 고칠 방법: 표의 review 줄 "보장하는 것"을 "다른 눈이 읽었다는 것. 읽은 사람이 만든 쪽과 독립이고 그 분야를 알면, 요구사항 자체를 의심할 수 있다"로 고친다.

### C 등급

F-06 [C] 17장 17행 "뒤집어 읽으면, 도구가 낸 결과를 다른 활동이 확인하는 쓰임에서는 그 도구의 qualification이 필요하지 않다." 그리고 부록 A tool qualification 항목. 이 말은 FAA Order 8110.49의 세 물음 (DO-178B)에서 나온다. 그 기준에서는 맞다. 다만 "다른 활동"이 그 도구가 낼 수 있는 오류를 잡을 수 있어야 한다는 조건이 빠지면, 아무 확인이나 붙여 qualification을 피하는 것으로 읽힌다. "그 확인이 도구의 오류를 잡을 수 있는 것이라면"을 붙인다. 23행의 TD (오동작을 잡을 확신)도 같은 조건이다.

F-07 [C] 17장 60행. Schildbach의 글을 "판을 밝히지 않음"이라고 적었다. 그 글의 서론은 "2011년에 ISO 26262 [3]이 나왔다"고 적고, proven in use의 근거를 "[3, part 8.14]"로 든다. ISO 26262:2011을 가리킨다. "ISO 26262:2011을 가리킴"으로 고친다.

F-08 [C] Ariane 501 보고서의 쪽 표기. 16장 123 - 125행은 "11쪽", "12-13쪽", "12쪽"이고, 17장 58행은 "PDF 10쪽", "PDF 11쪽"이다. OCR로 대조해 보니 둘 다 PDF의 쪽이다 (보고서 자체의 쪽은 PDF 쪽에서 4를 뺀다). 한 가지로 맞추고, 10장 74행 (9쪽, 17쪽)도 같은 표기인지 맞춘다.

F-09 [C] 17장 25행 "T3에는 ... 증거가 필요하고, 도구의 새 판마다 qualification한다고 설명한다." AbsInt의 쪽에서 "Each new version of the off-line support tool has to be qualified"는 부류를 가리지 않고 적혀 있다. T3에만 걸리는 말로 읽히지 않게 문장을 나눈다.

F-10 [C] 17장 75행 "자동차의 규격이 기존 소프트웨어 component를 받아들이는 절차를 따로 두는지 ... 확인하지 못했다." (실무) ISO 26262-8에는 소프트웨어 component의 qualification과 proven in use 논증을 다루는 절이 있다고 알고 있다 `(확인 필요)`. 원고가 이미 인용한 Schildbach의 글이 그 가운데 하나를 "part 8.14"로 가리킨다. "Schildbach의 글은 그 Part의 한 절을 proven in use로 가리킨다 (ISO 26262:2011). 받아들이는 절차의 내용은 확인하지 못했다" 정도로 이으면, 네 갈래 길의 표가 규격의 어디와 닿는지 독자가 찾을 수 있다.

F-11 [C] 16장 9행과 11행. Koopman의 발표를 차량 test의 일반론에 쓴 곳 (19쪽)은 발표자를 밝혔고, 20쪽의 숫자는 "일반론의 예로만 본다"고 낮췄다. 맞다. 다만 19쪽의 말은 NASA의 지침서 (189쪽)와 Butler와 Finelli로 이미 받쳐지므로, 소송의 한쪽 전문가의 발표를 셋째 근거로 둘 까닭이 약하다. 빼도 논지가 서지 않는지 저자가 정할 일이다.

## ISO 26262, IEC 61508, DO-178C, DO-330의 요구를 단정한 곳

규격이 무엇을 요구한다고 단정한 문장은 찾지 못했다. 조항 번호나 표의 값을 옮긴 곳도 없다. 셋은 RULES 5.2절의 경계에 있다.

| 곳 | 문장 | 판단 |
|---|---|---|
| 16장 226행 | DO-178B는 statement를 A-C, decision을 A-B, MC/DC를 A에 목표로 둔다 | NASA의 tutorial 14쪽이 DO-178B Table A-7을 들어 적은 그대로다. 정부 기관의 문서 하나로 옮겼고, DO-178C에서의 변화는 확인하지 못했다고 밝혔다. 받아들일 수 있다 |
| 17장 21행 | DO-330의 기준 셋과 TQL 다섯 | `(2차 자료)`, 회사 셋. AFuzion, LDRA, Rapita를 열어 기준 셋의 문장과 TQL의 순서를 확인했다. 세 회사 모두 도구를 파는 쪽이지만 서로 다른 회사다 |
| 17장 23행 | ISO 26262의 TI, TD, TCL, 네 방법 | `(2차 자료)`, 회사 둘 (Synopsys 2011 판 기준, Siemens 2018 판 기준). 내가 열지 않았다. 내용은 (실무) 내가 아는 것과 맞다 |
| 17장 25행 | IEC 61508의 T1, T2, T3 | `(2차 자료)`, 셋 가운데 둘 (Conrad 외, AbsInt)이 거의 같은 문장이라고 원고가 스스로 밝혔다. Conrad 외는 "IEC 61508 Ed. 2.0 (초안)"을 기준으로 적고 (pdftotext로 확인), AbsInt는 판을 적지 않는다. 맞다 |
| 17장 60행 | IEC 61508의 proven in use | F-04 |

## 근거를 대조한 문장

52개를 대조했다. 어긋나거나 넓게 옮긴 것이 4개다 (F-04, F-07, F-08, F-09). 숫자와 인용의 세기 (should, must, Highly Recommended)는 대조한 곳에서 모두 맞았다.

| 장 | 요지 | 문서와 쪽 | 판정 |
|---|---|---|---|
| 15 | Highly Recommended는 진지하게 따지고, 넣지 않으면 안전이 해쳐지지 않음을 보이는 것이 좋다 (should) | nasa-gb 43 | 맞음 |
| 15 | Fagan Inspection, formal inspection은 formal method가 아니다 | nasa-gb 118-119 | 맞음 |
| 15 | inspection의 점검 목록, 안전 필수 부품에는 inspection (should) | nasa-gb 176 | 맞음 |
| 15 | 등급이 주관적이라는 말 | nasa-gb 104 | 맞음 |
| 15 | FM은 정량적 신뢰도를 보장하지 않는다, 개발자 훈련 | nasa-gb 68 | 맞음 |
| 15 | formal specification으로 문제 37개 | nasa-gb 69 | 맞음 |
| 15 | 위험이 큰 부품은 모든 단계에서, 작은 부품은 코드만 inspection | nasa-gb 156 | 맞음 (may) |
| 15 | 위험이 낮으면 단순한 방법 | nasa-gb 160 | 맞음 |
| 15 | model checking과 state explosion | nasa-gb 128-129 | 맞음 |
| 15 | verification은 "you built it right" (IEEE 1012) | nasa-std-8739-8b 13 | 맞음 |
| 15 | peer review나 inspection (shall) | nasa-std-8739-8b 44 | 맞음 |
| 16 | 모든 것을 test하는 일은 드물다, 위험 분석으로 모은다 | nasa-gb 189 | 맞음 |
| 16 | coverage는 척도이지 방법이 아니다, "MC/DC testing"은 해가 될 수 있다 | nasa-mcdc-tutorial 10 | 맞음 |
| 16 | DO-178B Table A-7의 coverage와 level | nasa-mcdc-tutorial 14 | 맞음 |
| 16 | n+1개, (TF)(FT)(FF), 2^n, 입력과 조건의 수 | nasa-mcdc-tutorial 15 | 맞음 |
| 16 | source 100%가 object code에서 75% 이하 | nasa-mcdc-tutorial 17 | 맞음 |
| 16 | instrumentation이 오류를 숨기거나 넣지 않음을 보인다 | nasa-mcdc-tutorial 56 | 맞음 (essential) |
| 16 | MC/DC를 오해하는 예 | nasa-mcdc-tutorial 61 | 맞음 |
| 16 | 한계에서, 아래에서, 위에서 test하라 (should), fault injection의 예 | nasa-gb 179 | 맞음 |
| 16 | unit test는 가장 작은 규모, 프로그래머 | nasa-gb 185 | 맞음 |
| 16 | equivalence와 boundary는 test 계획의 항목 | nasa-gb 187 | 맞음 |
| 16 | simulator의 충실도, 안전 test는 최종 시스템에서 (must), 형상 관리가 유일한 배포자 (should) | nasa-gb 190 | 맞음 |
| 16 | fault injection은 Highly Recommended | nasa-gb 192 | 맞음 |
| 16 | 안전 test는 어느 수준에도 넣을 수 있지만 모든 안전 기능을 확인하는 것이 필수 (vital), negative test | nasa-gb 194 | 맞음 |
| 16 | fault injection은 이제 interface에, source 없이도 | nasa-gb 281 | 맞음 |
| 16 | SRI를 Ariane 5의 카운트다운, 비행 순서, 궤적으로 시험하지 않았다. 지상 test를 했다면 메커니즘이 드러났을 것 | ariane-501-report PDF 11 (OCR) | 맞음 (쪽 표기는 F-08) |
| 16 | 1992년에 SRI를 loop에서 뺐다, 이유, "definite risk" | ariane-501-report PDF 12-13 (OCR) | 맞음 |
| 16 | 앞선 수준이 범위를 완전히 덮었는지 확인한 뒤에만 simulator | ariane-501-report PDF 12 (OCR) | 맞음 |
| 17 | 정렬 기능을 공통성 때문에 남겼다, "not wise to make changes" | ariane-501-report PDF 10 (OCR) | 맞음 |
| 17 | 한계의 선언은 모든 임무 필수 장치에 의무여야 한다 ("should be mandatory") | ariane-501-report PDF 11 (OCR) | 맞음 |
| 17 | compiler의 결함 목록, 최적화를 끌 수 있는가, runtime의 source | nasa-gb 235 | 맞음 |
| 17 | 자동 생성의 옳은 번역을 확인해야 한다 (must) | nasa-gb 238 | 맞음 |
| 17 | 생성된 코드에 같은 inspection (should) | nasa-gb 240 | 맞음 (should) |
| 17 | OTS, source가 없으면 어떤 안전 분석은 할 수 없다 | nasa-gb 271 | 맞음 |
| 17 | 꺼도 다시 compile하지 않으면 코드가 남는다, 같은 platform의 OTS | nasa-gb 272 | 맞음 |
| 17 | wrapper, 문서가 말하지 않은 출력, OTS만큼 커진다 | nasa-gb 276 | 맞음 |
| 17 | dormant code | nasa-gb 278 | 맞음 |
| 17 | 다시 쓰기의 가장 큰 문제는 심리, Ariane 5 | nasa-gb 279 | 맞음 |
| 17 | OTS의 안전은 "black art" | nasa-gb 280 | 맞음 |
| 17 | COTS, OSS, 재사용 component, GPL의 조건 | nasa-std-8739-8b 20-21 | 맞음 |
| 17 | 생성 도구의 V&V, 형상 관리 | nasa-std-8739-8b 29 | 맞음 |
| 17 | COTS를 직접 개발한 것과 같은 수준으로 test | nasa-std-8739-8b 40 | 맞음 |
| 17 | IV&V가 open source를 찾았는지 | nasa-std-8739-8b 54 | 맞음 |
| 17 | DO-330 기준 1, 2, 3 | AFuzion (웹) | 맞음. 연도는 쪽에 없다 |
| 17 | 기준 셋, TQL 표 | LDRA (PDF, pdftotext) | 맞음. 참고 문헌에 2021년의 날짜 |
| 17 | 기준 셋, TQL 다섯, 낮을수록 엄격 | Rapita Systems (웹) | 맞음. 날짜 없음 |
| 17 | T1, T2, T3, T3에는 명세에 맞는다는 증거 | Conrad 외 (PDF, pdftotext) | 맞음. IEC 61508 Ed. 2.0 초안 기준 |
| 17 | T1, T2, T3, 새 판마다 qualification | AbsInt (웹) | 맞음. 새 판의 말이 T3에만 걸리지 않음 (F-09) |
| 17, A | IEC 61508의 proven in use는 하드웨어의 무작위 고장률 | Intertek (웹) | 문서와는 맞음. 그 글의 범위 (Route 2H)보다 넓게 옮김 (F-04) |
| 17 | ISO 26262의 proven in use 절 | Schildbach (arXiv PDF, pdftotext) | 맞음. 판은 2011 (F-07) |
| 15, 16, 17 | 예제의 숫자: clang-tidy가 찾은 것 둘, 거짓 경보 하나, TC 63, FT 3, NC 5, 변이 221개 (172 + 49) 가운데 217개와 4개, 네 번의 놓침, 90개 가운데 일곱, 도구의 틀림 여덟 | test-report.md 1, 6, 7절, tools.md 3절 | 맞음 |
| 16 | MC/DC 43%와 20% | notes/tool-check.md | 맞음 |

(52줄은 문장 단위로 세면 60개쯤이다.)

## 잘된 것

- 세 장이 같은 태도로 쓰였다. 수단마다 "보장하는 것과 못 하는 것"을 적고, 도구마다 "틀리면 무엇이 잡는가"를 적는다. tools.md 2절의 오른쪽 칸 (알려진 결함을 넣어 보고 도구가 알리는지 본다)은 실무의 도구 신뢰 논증과 같은 생각을 작은 예제에서 보인다.
- 근거의 세기를 지켰다. should, must, Highly Recommended, "may"를 원문대로 옮겼고, 회사의 글은 회사의 글이라고, 판이 없으면 없다고 적었다. 받은 문서가 정의를 싣지 않은 말 (dead code, deactivated code, equivalence class)은 이 책의 풀이라고 밝혔다.
- 16장 6절의 Ariane 501 대목은 공식 조사의 말 (12쪽의 조건부 허용, 13쪽의 "definite risk")을 정확히 옮겼다. 17장은 Schabe와 Braband의 해석을 조사 보고서의 결론과 나눠 적었다.
- 15장의 성질 7 해설은 지난 묶음의 잘못 (증분으로 읽음)을 정확히 고쳤고, "증명의 결과를 옮긴 문장은 review의 대상이다"로 일반화했다.

## 판정

조건부 통과. F-01을 고치면 통과로 본다. 근거 대조는 좋다. 받은 문서의 쪽과 세기는 대조한 곳에서 모두 맞았고, 웹 출처 일곱 곳도 원고가 옮긴 대로였다. 넓게 옮긴 곳 (F-04) 하나와 판의 표기 (F-07) 하나가 있다. 고칠 것은 결론을 짓는 문장에 몰려 있다. 16장의 "충분히"의 정의 (F-01)와 15장의 방법의 표 (F-03, F-05)가 그 장의 본문이 이미 적은 조건을 결론에서 빼고 있다. F-02는 15장의 교훈과 같은 모양의 구멍이 예제에 남아 있다는 것이어서, 고치거나 적어 두기를 권한다.

## 저자가 정할 것

1. 16장의 "충분히"에 환경의 물음을 넷째로 넣을 것인가, 셋을 두고 "남은 것"의 기준을 강하게 할 것인가 (F-01).
2. 도구가 없을 때 `make check`를 실패하게 할 것인가 (F-02). 그러면 도구를 다 갖추지 않은 독자는 `make check`를 통과시킬 수 없다.
3. 16장 9행의 Koopman 인용을 남길 것인가 (F-11).
