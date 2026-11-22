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

## 지금 어디까지 왔는가 (2026-11-22)

- 단계 0 (준비), 단계 0.5 (예제 골격), 단계 1 (뼈대)을 마쳤다. 단계 검토를 세 번 받아 통과했다 ([reviews/2026-11-22-stage1/](reviews/2026-11-22-stage1/README.md)).
- 쓴 원고: 2, 3, 6, 7, 10, 11, 12, 16, 19장과 부록 A, E의 뼈대. 장마다 1-3쪽이다.
- 예제: safety goal 하나가 요구사항, 코드, test, safety case까지 이어진다. safety case는 닫히지 않았고, 열린 가지를 그대로 적었다.
- 사람의 검토는 받지 않았다. ISO 26262 원문과도 대조하지 않았다.

읽는 순서 (저자용)

1. [example/drive-torque/docs/scope.md](example/drive-torque/docs/scope.md): 예제가 무엇을 다루고 무엇을 뺐는가
2. [chapters/ch06-hara.md](chapters/ch06-hara.md), [chapters/ch07-safety-concept.md](chapters/ch07-safety-concept.md): hazard에서 safety goal, 구조, 시간 예산까지
3. [example/drive-torque/docs/technical-safety-concept.md](example/drive-torque/docs/technical-safety-concept.md): 3절 "허용 토크와 정상 동작 사이의 틈"이 이 예제의 핵심이다
4. [chapters/ch10-software-safety-requirements.md](chapters/ch10-software-safety-requirements.md), [chapters/ch11-software-architecture.md](chapters/ch11-software-architecture.md), [chapters/ch12-safety-mechanisms.md](chapters/ch12-safety-mechanisms.md): 요구사항, 구조, 기법
5. [chapters/ch16-testing.md](chapters/ch16-testing.md)과 [example/drive-torque/docs/test-report.md](example/drive-torque/docs/test-report.md): 6절 "만드는 동안 찾은 것"
6. [chapters/ch19-safety-case.md](chapters/ch19-safety-case.md)과 [example/drive-torque/docs/safety-case.md](example/drive-torque/docs/safety-case.md)
7. 나머지: [2장](chapters/ch02-concepts-and-terms.md), [3장](chapters/ch03-risk-and-integrity-level.md), [부록 E](chapters/appendix-e-vehicle-ee-basics.md), [부록 A](chapters/appendix-a-glossary.md)

예제를 돌리려면 `example/drive-torque/`에서 `make check`와 `make mutation`을 실행한다.

저자가 정해야 하는 것

- [notes/disputes.md](notes/disputes.md): 에이전트의 토론에서 합의되지 않은 것 (1건)
- [PLAN.md](PLAN.md)의 12절 "정해야 할 것"
- [notes/questions.md](notes/questions.md): 받은 문서로 풀지 못한 질문
