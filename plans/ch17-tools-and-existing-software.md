# 17장. Tool과 기존 소프트웨어 - 장 계획

원고: [chapters/ch17-tools-and-existing-software.md](../chapters/ch17-tools-and-existing-software.md)

| 항목 | 내용 |
|---|---|
| Part | IV. 안전함을 보이고 유지하기 |
| 쓰는 단계 | 단계 2 (살 붙이기) |
| 상태 | 미착수 |

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
