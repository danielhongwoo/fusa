# 17장. Tool과 기존 소프트웨어 - 장 계획

원고: [chapters/ch17-tools-and-existing-software.md](../chapters/ch17-tools-and-existing-software.md)

| 항목 | 내용 |
|---|---|
| Part | IV. 안전함을 보이고 유지하기 |
| 쓰는 단계 | 단계 2 (살 붙이기) |
| 상태 | 초고 (2026-11-23, 단계 2의 묶음 4). 에이전트 검토 세 번을 거쳤다 (`reviews/2026-11-23-stage2-part4/`). 사람의 검토는 받지 않았다 |

## 핵심 질문

내가 만들지 않은 것 (compiler, code generator, library, open source)을 어떻게 믿는가?

## 다룰 내용

- tool이 안전에 미치는 영향, tool confidence level, tool qualification
- compiler와 code generator, model-based development
- 기존 software component의 qualification, proven in use
- 맥락 없이 개발된 요소 (SEooC: safety element out of context)와 가정의 검증
- open source 사용

## 검토에서 더한 항목 (2026-11-22)

괄호 안은 지적 번호이고, 검토 기록은 `reviews/2026-11-22-plan/`에 있다. 규격의 내용에 관한 항목은 쓰기 전에 확인한다 (RULES.md 5절).

- 기존 소프트웨어를 쓰는 네 갈래 길: SEooC로 개발, component qualification, proven in use, 등급 없이 쓰고 격리 (F-15)
- ISO 26262의 tool confidence level과 IEC 61508의 tool 분류를 나란히 비교한다 (F-15)
- code generator의 tool confidence level (F-25)
- compiler가 안전 관련 코드를 바꾸는 사례 1개 (E-09)
- 예제 toolchain의 분류표에 qualification되지 않았음을 밝힌다 (E-17)

## 책의 성격에 따른 조정 (2026-11-22)

이 책은 ISO 26262:2018의 원문을 보지 않고 쓴다 (RULES.md 5.6절).

- tool confidence level, component qualification, proven in use의 세부 절차는 개념 수준으로 다룬다 (2차 자료).

## 예제 산출물

예제 toolchain의 tool 분류표, 외부 component 하나의 사용 근거

## 관련 규격과 자료

ISO 26262-8, -10; IEC 61508-3; DO-330

## 근거 위치 (2026-11-22)

받은 문서에서 이 장을 뒷받침하는 곳이다. 쪽은 PDF 파일의 몇 번째 쪽인지다. 에이전트가 문서를 읽어 뽑은 것이므로, 원고에 쓰기 전에 그 쪽을 직접 읽어 확인한다 (RULES.md 5.2절).

| 문서 | 절 | 쪽 | 뒷받침하는 내용 |
|---|---|---|---|
| `faa-ac-20-115d` | 10. Tool Qualification (Table 2, 11-12 TQL correlation) | 10-12 | DO-330 기반 tool qualification level, DO-178B tool 분류와 TQL의 대응 (항공) |
| `faa-ac-20-115d` | 9. Modifying and Re-using Software Approved using older versions (legacy software, Figure 1) | 5-10 | 기존 소프트웨어 재사용의 절차: 사용 이력, service difficulty 평가 |
| `nasa-gb-8719-13` | 12.1 Off-the-Shelf Software (12.1.1-12.1.5 Special Problems with Reused Software) | 270-282 | OTS/COTS와 재사용 소프트웨어의 평가, 통합, 추천 분석과 테스트 |
| `nasa-gb-8719-13` | 11.2 Compilers, Editors, Debuggers / 11.3 CASE tools and Automatic Code Generation | 233-240 | tool과 code generator의 위험, 선택 기준 |
| `misra-compliance-2020` | 2.6 Tool management (2.6.1-2.6.6) | 12-15 | compiler와 정적 분석 tool의 선택, 검증, 설정 |
| `nasa-mcdc-tutorial` | 4.1.2 Factors to Consider in Selecting or Qualifying a Tool | 56-59 | coverage tool의 qualification 요소 |
| `ariane-501-report` | 2.2 (Ariane 4 소프트웨어의 재사용) | 9-11 | 검증 없는 재사용이 사고로 이어진 사례 (OCR본) |
| `autosar-safety-measures` | 3.4 Functional Safety Measures not delivered by AUTOSAR | 46 | AUTOSAR가 SEooC, ASIL 식별, dependent failure analysis, safety case, confirmation measure를 제공하지 않는다는 목록 (SEooC의 정의 자체는 없음) |

### 받은 문서에 근거가 없는 항목

이 항목은 다른 공개 문서를 찾거나, `(2차 자료)`로 밝히거나, 쓰지 않는다.

- tool confidence level, ISO 26262의 tool 분류, IEC 61508 tool 분류, SEooC 정의, proven in use - 받은 문서에 없다 (TQL은 faa-ac-20-115d만, 항공)
- compiler가 안전 코드를 바꾸는 사례, code generator의 TCL - 없음 (nasa-gb 11.3 일반 서술만)
- open source 사용 - nasa-gb p245 RTEMS 한 줄뿐
