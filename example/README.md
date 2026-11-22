# 예제

책에서 쓰는 예제의 산출물과 코드를 둔다. 여기에 있는 것이 원본이고, 원고는 이것을 가리키거나 필요한 부분만 옮겨 싣는다 (RULES.md 1.1절).

예제의 등급과 수치는 설명을 위한 가정이다. 실제 제품에 쓸 수 없다. 예제의 산출물은 ISO 26262의 용어와 흐름을 따르지만, 규격의 요구사항을 만족하는지 확인한 것이 아니다.

## 폴더

```
example/
  drive-torque/          관통 예제: 전기차의 구동 토크 제어
    docs/                산출물 문서
      scope.md           예제의 범위: item의 경계, E/E 구성도, hazard, 가정, ID 체계
      item-definition.md
      hara.md
      safety-goals.md
      functional-safety-concept.md
      technical-safety-concept.md
      requirements.yaml  software safety requirement (ID, 문장, 위로 가는 추적)
      safety-case.md
    src/
      app/               기능: 페달에서 토크 요구를 만든다
      monitor/           감시: 토크 요구가 허용 범위 안인지 본다
      hal/               하드웨어 추상화 계층의 interface와 시뮬레이션용 구현
    sim/                 plant model, 운전 시나리오, fault injection
    test/                unit test, 요구사항에 따른 test, fault injection test
    tools/               추적 검사, 보고서를 만드는 스크립트
    Makefile             `make check`로 빌드, test, coverage, 정적 분석을 돌린다
  robot-field-switch/    보조 예제 (20장): 이동 로봇의 속도에 따른 보호 영역 전환
  drone-failsafe/        보조 예제 (21장): 소형 드론의 link 상실, geofence 이탈, 위치 상실 대응
```

- `docs/scope.md`는 단계 0에서 쓴다. 나머지 문서와 코드는 단계 0.5와 단계 1에서 만든다.
- 응용과 감시의 코드는 `hal/`의 interface만 부른다. fault는 `hal/`의 뒤에서만 넣는다.
- 도구의 선택과 확인 결과는 `notes/tool-check.md`에 있다.

## ID 체계

| 접두어 | 뜻 | 예 |
|---|---|---|
| `H-` | hazard | `H-01` |
| `SG-` | safety goal | `SG-01` |
| `FSR-` | functional safety requirement | `FSR-01` |
| `TSR-` | technical safety requirement | `TSR-01` |
| `SWR-` | software safety requirement | `SWR-01` |
| `A-` | 가정 (assumption) | `A-01` |
| `TC-` | test case | `TC-01` |

아래 단계의 항목은 위 단계의 ID를 가리킨다. 코드와 test에는 `SWR-`과 `TC-`를 주석으로 적어, 스크립트가 빠진 것을 찾을 수 있게 한다.
