# 예제

책에서 쓰는 예제의 산출물과 코드를 둔다. 여기에 있는 것이 원본이고, 원고는 이것을 가리키거나 필요한 부분만 옮겨 싣는다 (RULES.md 1.1절).

예제의 등급과 수치는 설명을 위한 가정이다. 실제 제품에 쓸 수 없다. 예제의 산출물은 ISO 26262의 용어와 흐름을 따르지만, 규격의 요구사항을 만족하는지 확인한 것이 아니다.

## 폴더

```
example/
  drive-torque/          관통 예제: 전기차의 구동 토크 제어
    docs/                산출물 문서
      scope.md           예제의 범위: item의 기능과 경계, hazard, 가정
      item-definition.md
      hara.md            HARA와 safety goal
      functional-safety-concept.md
      technical-safety-concept.md   구조, 시간 예산, 가정, 독립성에 관한 주장
      fta.md             safety goal 하나의 fault tree
      fmea.md            소프트웨어 수준의 FMEA
      stpa.md            control structure와 unsafe control action
      dfa.md             dependent failure analysis
      hardware-assumptions.md   하드웨어에 대한 가정과 진단의 목록
      hsi.md             hardware-software interface: 신호마다 단위, 켠 직후의 값, 고장일 때의 모습
      safety-plan.md     활동, 역할, 확인, 줄인 것
      fault-table.md     fault, error, failure, hazard의 정리
      requirements.yaml  safety goal에서 software safety requirement까지 (ID, 문장, 추적)
      architecture.md    소프트웨어의 정적 view와 동적 view
      test-report.md     test와 fault injection의 결과
      tools.md           도구의 목록, 틀리면 어떻게 되는가, 실제로 있었던 일
      change-impact.md   변경 요청 하나 (CR-001)의 영향 분석
      safety-case.md     두 safety goal의 논증 (GSN), 근거의 한계, 가정, 열린 가지
    src/
      common/            공통 형과 단위
      hal/               하드웨어 추상화 계층의 interface
      input/             입력 읽기와 입력 검사 (가속 페달의 두 채널)
      app/               기능: 토크 요구를 만든다
      monitor/           감시 (허용 토크), 출력 단계 (깎기), inverter가 알린 토크의 검사
      reaction/          고장 대응의 상태 기계
      com/               메시지의 보호와 검사
      flow/              실행의 확인 (외부 watchdog에 보낼 답)
      vcu/               주기 실행: task table
    intro/               1장의 실행 예: 안전 장치가 없는 제어기와 견준다
    sim/                 시뮬레이션용 HAL, plant model, 시나리오 실행기
    test/                unit test, 시나리오 test, 결함 모듈 (faulty/), 증명할 성질 (proof/)
    tools/               추적 검사, coverage, 증명, 변이 검사, 다른 compile option의 test, 단계의 확인
    Makefile             `make check`로 빌드, test, 다른 compile option의 test, 추적, 정적 분석, coverage, 증명을 돌린다
  robot-field-switch/    보조 예제 (20장): 이동 로봇의 속도에 따른 보호 영역 전환
  drone-failsafe/        보조 예제 (21장): 소형 드론의 link 상실, geofence 이탈, 위치 상실 대응
```

- 기능과 감시의 코드는 `hal/`의 interface로만 하드웨어를 만난다.
- fault는 `sim/`의 HAL 구현 뒤에서 넣거나, 모듈 전체를 link할 때 바꿔 끼워서 넣는다. `src/`의 코드에는 test용 코드가 없다.
- 시뮬레이션은 VCU를 HAL로 나온 것 (토크 요구, 구동 허용 신호, 경고 요청, 진단 메시지)으로만 본다.
- 도구의 선택과 확인 결과는 `notes/tool-check.md`에 있다.

## 돌리는 법

```
cd example/drive-torque
make check           # 빌드, test, 다른 compile option의 test, 추적 검사, 정적 분석, coverage, 증명
make mutation        # 제품 코드에 결함을 하나씩 넣어 test가 잡는지 본다 (10분쯤)
make proof-mutation  # 제품 코드에 결함을 하나씩 넣어 증명이 잡는지 본다
make step-check      # 단계마다 알려진 결함을 넣어 그 단계가 실패를 알리는지 본다
```

필요한 도구: C compiler, Python 3, GCC 14 이상 (coverage와 다른 compiler의 test), cppcheck, clang-tidy, CBMC. 도구가 없으면 그 단계를 건너뛰고 "건너뜀"이라고 찍고, `make check`는 끝에서 실패한다. 돌리지 못한 검사가 있는데 통과했다고 말하지 않으려는 것이다 (`make check SKIP_OK=1`을 주면 지나간다). 어느 도구도 qualification되지 않았다 (`drive-torque/docs/tools.md`).

## ID 체계

| 접두어 | 뜻 | 예 |
|---|---|---|
| `H-` | hazard | `H-01` |
| `SG-` | safety goal | `SG-01` |
| `FSR-` | functional safety requirement | `FSR-01` |
| `TSR-` | technical safety requirement | `TSR-01` |
| `SWR-` | software safety requirement | `SWR-01` |
| `A-` | 가정 (assumption) | `A-01` |
| `TC-` | 요구사항에 따른 test case | `TC-001` |
| `FI-` | fault injection의 종류 | `FI-01` |
| `FT-`, `RT-` | 기능의 test, robustness test. 안전 요구사항의 추적에 넣지 않는다 | `FT-001` |

아래 단계의 항목은 위 단계의 ID를 가리킨다. 코드에는 `SWR-`을, test에는 `TC-`를 주석으로 적는다. `tools/trace.py`가 빠진 것을 찾는다.
