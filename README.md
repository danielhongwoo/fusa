# 소프트웨어 엔지니어를 위한 기능 안전 (Functional Safety)

Functional safety를 공부하며 쓰는 책의 원고 저장소다. 책은 functional safety의 사고방식과 소프트웨어 기법을 다루고, ISO 26262는 구조와 용어 수준으로 소개한다. 독자는 임베디드 시스템 개발 경험이 있는 소프트웨어 엔지니어이고, 주 분야는 자동차 (ISO 26262), 보조 분야는 로봇과 드론이다.

## 문서 안내

| 위치 | 내용 |
|---|---|
| [OUTLINE.md](OUTLINE.md) | 무엇을 쓰는가: 독자, 범위, 예제, 목차 |
| [PLAN.md](PLAN.md) | 어떻게 쓰는가: 단계, 절차, 일정, 위험, 정한 것과 정해야 할 것 |
| [RULES.md](RULES.md) | 쓸 때 지키는 규칙: 형식, 근거 표시, 저작권, commit |
| [chapters/](chapters/) | 원고. 장마다 파일 하나이고, 책에 실릴 내용만 둔다 |
| [plans/](plans/) | 장 계획. 원고와 같은 이름의 파일에 핵심 질문, 다룰 내용, 예제 산출물, 근거, 상태를 적는다 |
| [references/](references/README.md) | 참고 문서 목록과 접근 등급, 규격 목록, 받은 문서 |
| [figures/](figures/) | SVG 그림 |
| [reviews/](reviews/) | 검토 기록 |
| [example/](example/README.md) | 예제의 산출물 문서, 코드, test. `make check`로 돌린다 |
| [notes/](notes/) | 근거 기록 (`claims.md`), 저자에게 알릴 쟁점 (`disputes.md`), 풀리지 않은 질문 (`questions.md`), 도구 확인 기록 |
| [tools/](tools/) | 문서 검사 도구 (`tools/lint`) |

## 지금 어디까지 왔는가 (2026-11-23)

- 단계 0 (준비), 단계 0.5 (예제 골격), 단계 1 (뼈대)을 마쳤다 ([reviews/2026-11-22-stage1/](reviews/2026-11-22-stage1/README.md)).
- 단계 2 (살 붙이기)의 다섯 묶음 가운데 둘을 마쳤다.
  - 묶음 1: 1, 4, 5장의 초고. 검토 두 번, 통과 ([reviews/2026-11-22-stage2-part1/](reviews/2026-11-22-stage2-part1/README.md)).
  - 묶음 2: 8, 9장의 초고와 6, 7장의 깊은 수정. 검토 세 번, 통과 ([reviews/2026-11-23-stage2-part2/](reviews/2026-11-23-stage2-part2/README.md)).
- 남은 묶음: 13, 14장과 10, 11, 12장, 부록 E / 15, 17장과 16장 / 18장과 19장.
- 예제: safety goal이 둘이 되었다 (의도하지 않은 가속, 구동력의 상실과 감속). 단계 1의 설계를 네 가지 기법으로 분석했고, 찾은 것을 요구사항으로 올렸다. 요구사항 62개 가운데 30개는 "구현 예정"이다. 요구사항만 있고 코드가 없다. 다음 묶음에서 구현한다.
- safety case는 닫히지 않았고, 단계 2가 끝나도 닫히지 않는다. 열린 가지를 그대로 적었다.
- 사람의 검토는 받지 않았다. ISO 26262 원문과도 대조하지 않았다.

읽는 순서 (저자용. 단계 2에서 새로 쓰거나 깊게 고친 것)

1. [chapters/ch01-accidents.md](chapters/ch01-accidents.md): 사고 사례 넷과 관통 예제의 소개
2. [chapters/ch04-standards-map.md](chapters/ch04-standards-map.md), [chapters/ch05-safety-lifecycle.md](chapters/ch05-safety-lifecycle.md): 규격의 지도와 일하는 틀
3. [chapters/ch06-hara.md](chapters/ch06-hara.md): hazard에서 safety goal까지. "safety goal 둘"에 `SG-02`를 두 번 고친 경위가 있다
4. [chapters/ch07-safety-concept.md](chapters/ch07-safety-concept.md): "감시의 틈: 세 번 고친 이야기"가 이 예제의 핵심이다
5. [chapters/ch08-safety-analysis.md](chapters/ch08-safety-analysis.md): 네 가지 분석 기법과, 예제에서 분석이 찾은 것과 놓친 것
6. [chapters/ch09-hardware-for-software-engineers.md](chapters/ch09-hardware-for-software-engineers.md)
7. 예제의 문서: [hara.md](example/drive-torque/docs/hara.md), [functional-safety-concept.md](example/drive-torque/docs/functional-safety-concept.md), [technical-safety-concept.md](example/drive-torque/docs/technical-safety-concept.md) (3절과 9절), [test-report.md](example/drive-torque/docs/test-report.md) (6절 "만드는 동안 찾은 것")

단계 1의 뼈대로 남아 있는 장: 2, 3, 10, 11, 12, 16, 19장과 부록 E. 숫자와 문장 몇 개만 지금의 예제에 맞췄다.

예제를 돌리려면 `example/drive-torque/`에서 `make check`와 `make mutation`을 실행한다.

저자가 정해야 하는 것

- [notes/disputes.md](notes/disputes.md): 에이전트의 토론에서 합의되지 않은 것 (1건. 저자가 정했고 구현했다)
- [PLAN.md](PLAN.md)의 12절 "정해야 할 것"
- [notes/questions.md](notes/questions.md): 받은 문서로 풀지 못한 질문
