# 14장. 플랫폼: RTOS, OS, multicore

## 핵심 질문

내 코드 아래에 있는 소프트웨어와 프로세서는 믿을 수 있는가?

## 내 코드 아래에 있는 것

앞의 장들은 내가 쓴 코드를 다뤘다. 그런데 그 코드 아래에는 OS나 scheduler, driver와 library, 그리고 프로세서가 있다. 대개 내가 쓰지도 만들지도 않은 것들이지만, 이것들이 틀리면 내 코드가 옳아도 결과가 틀린다. 그래서 이것들도 item의 일부로 분석한다. NASA의 지침서는 OS와 language library처럼 널리 쓰여 오류가 없다고 여겨지는 소프트웨어도 안전 시스템에서는 오류가 없다고 가정하지 말라고 한다 (NASA, 2004, 273쪽). 기성품 소프트웨어 일반은 17장, 구조로 나누는 일은 11장, 실행을 감시하는 mechanism은 12장에서 다룬다. 이 장은 실행을 맡는 것, 곧 OS와 프로세서를 본다.

기대는 문서는 셋이다. AUTOSAR의 안전 수단 개요 (Classic Platform R25-11)는 OS가 주는 보호와 그 한계를 적는다. 미국 FAA의 AC 20-193 (2024)과 유럽 EASA의 AMC 20-193 (2022)은 multicore 프로세서에 관한 항공의 지침이다. 자동차에 그대로 적용되는 문서가 아니지만, 이 책이 받은 문서 가운데 multicore의 간섭을 가장 자세히 공개한 것이어서 소개한다. NASA의 지침서는 2004년의 문서이므로 그때의 지침으로 읽는다.

## OS 없이: 표 하나, thread 하나

가장 단순한 플랫폼은 OS가 없는 것이다. NASA의 지침서도 OS의 종류에 OS가 없는 것과 개발자가 직접 쓴 단순한 task scheduler를 넣는다 (NASA, 2004, 241쪽). 이 책의 예제가 그렇다. 정해 둔 표 (정적 task table)에 task 넷을 적고 10 ms마다 표의 순서대로 부른다. thread는 하나이고, 한 task가 다른 task를 중간에 끊는 일 (선점)이 없다.

이 꼴에서 얻는 것은 셋이다. 입력, 기능, 감시와 출력이 늘 같은 차례로 실행된다. task가 서로를 끊지 않으므로 함께 쓰는 data를 두 task가 동시에 만지는 경합이 없다. 실행의 모양이 하나뿐이어서 test와 증명이 그 하나만 다루면 된다. 그 대신 긴 계산 하나가 뒤의 모든 task를 늦춘다. 급한 일이 생겨도 앞의 task가 끝나기를 기다려야 한다. 그리고 보호가 없다. 모든 task가 같은 memory를 쓰므로 한 task의 잘못된 pointer가 감시의 변수를 덮어쓸 수 있다. 이것을 막는 것은 하드웨어의 memory 보호뿐이고, 그 설정과 관리는 보통 OS가 맡는다.

## OS가 들어오면

### 선점이 데려오는 것

OS를 쓰면 급한 task가 덜 급한 task를 끊고 먼저 돌 수 있다. 그 대신 OS가 없던 꼴이 저절로 주던 것을 잃는다. 함께 쓰는 data는 쓰는 도중에 끊길 수 있어서 보호가 필요해진다. 보호에 lock을 쓰면 우선순위의 뒤집힘 (priority inversion)이 생길 수 있다. 낮은 task가 자원을 쥔 채 중간 task에 밀리는 동안, 그 자원을 기다리는 높은 task도 함께 멈추는 것이다. NASA의 지침서는 RTOS의 조건에 이것을 푸는 priority inheritance를 넣고, interrupt 지연과 OS와 driver가 interrupt를 막는 최대 시간을 알아야 한다고 적는다 (NASA, 2004, 242-243쪽).

마감도 새 문제가 된다. AUTOSAR의 문서는 고정된 우선순위로 선점하는 OS에서 task가 마감을 지키는지를 세 가지가 정한다고 적는다. 그 task의 실행 시간, 낮은 task가 자원을 잠그거나 interrupt를 막아서 생기는 막힘의 시간, 그리고 task가 활성화되는 간격이다 (AUTOSAR, 2025, 25쪽). 실행 시간만 재서는 마감을 말할 수 없다.

### OS가 주는 보호와 그 한계

AUTOSAR의 문서는 OS가 주는 보호 두 가지를 설명한다. memory partitioning은 OS-Application이라고 부르는 묶음 (task와 interrupt 처리 루틴 등)마다 memory 영역을 나눠, 한 partition의 코드가 다른 partition의 memory를 바꾸지 못하게 한다. 실제로 접근을 막는 것은 MPU나 MMU 같은 하드웨어이고, 그것을 알맞게 설정하는 것이 OS의 일이다. timing 보호는 앞의 세 요인에 하나씩 대응하는 한계를 감시한다. task의 실행 시간의 상한 (Execution Budget), 자원과 interrupt를 잠그는 시간의 상한 (Lock Budget), 활성화 사이의 최소 간격 (Time Frame)이다. 실행 시간을 강제하려면 시간을 재는 interrupt 같은 하드웨어의 도움이 필요하다 (AUTOSAR, 2025, 13쪽, 20쪽, 26쪽).

같은 문서는 이 보호가 닿지 않는 곳을 함께 적는다 (13쪽, 15-18쪽, 20-22쪽, 26쪽).

| 한계 | 문서가 적은 것 |
|---|---|
| trusted 쪽에는 걸리지 않는다 | trusted OS-Application은 감시와 보호를 끄고 privileged mode로 돌 수 있다. 문서가 드는 구현 예에서는 basic software 전부가 이 쪽에 있다 |
| 같은 OS-Application 안은 나누지 않는다 | 등급이 다른 component를 같은 OS-Application에 넣지 말라고 권한다. task 수준의 partition은 OS 규격이 "may"로 적어서 구현에 따라 없을 수 있다 |
| 다른 bus master는 막지 못할 수 있다 | MPU가 core 안에 있는 구현에서는 그 core의 접근만 막는다. DMA와 다른 core는 통제 밖이다 |
| OS 밖의 interrupt는 감시하지 못한다 | Category 1 interrupt는 OS 밖에서 실행된다 |
| OS는 마감을 직접 보지 않는다 | 마감 위반은 관계없는 task의 간섭으로도 생겨서 원인 task를 가려낼 수 없기 때문이다 |

budget의 값을 얻는 방법은 이 문서에 없다. OS는 정해 준 budget을 지키게 할 뿐이고, 값이 옳은지는 쓰는 쪽이 보여야 한다.

### 보호하는 것은 누가 믿어 주는가

보호를 OS가 주면 OS 자신이 안전에 관련된 소프트웨어가 된다. AUTOSAR의 문서는 자기의 안전 mechanism도 안전에 관련되므로 그에 맞게 개발하고 통합해야 한다고 적는다 (AUTOSAR, 2025, 9쪽). 항공의 multicore 지침은 더 분명하다. partitioning을 제공하는 소프트웨어는 그것이 나누는 소프트웨어 가운데 가장 높은 등급 이상이어야 한다 (FAA, 2024, 5쪽). 그리고 OS는 여러 요소가 함께 기대는 것이다. NASA의 지침서는 같은 OS를 돌리는 두 processor는 application을 아무리 따로 만들어도 서로 독립이 아니라는 우주 왕복선의 규정을 옮긴다 (NASA, 2004, 143쪽).

특정 RTOS 제품의 인증이 무엇을 보증하는지, ISO 26262가 OS에 무엇을 요구하는지는 이 책이 받은 문서에 없어서 다루지 못했다. hypervisor, Linux 같은 범용 OS, AUTOSAR Adaptive Platform도 마찬가지다.

## multicore: 함께 쓰는 것이 간섭의 길이 된다

core가 둘 넘으면 data를 주고받지 않는 application 사이에도 결합이 생긴다. FAA의 지침은 여러 core의 application이 memory, cache, core를 잇는 interconnect 같은 공유 자원에 동시에 접근하려 해 경쟁이 생기고, 중재의 지연 때문에 혼자 돌 때보다 훨씬 오래 걸릴 수 있다고 적는다. 그러면 안전에 관련된 application이 기능을 끝낼 시간이 모자랄 수 있다 (FAA, 2024, 3쪽). 지침은 이런 간섭을 일으킬 수 있는 플랫폼의 성질을 interference channel (간섭의 길)이라고 부르고, 플랫폼에 OS나 hypervisor도 넣는다 (4쪽). 지침이 드는 길은 이렇다 (7-10쪽).

| 함께 쓰는 것 | 지침이 드는 효과 |
|---|---|
| cache | cache miss 등으로 생기는 시간 간섭 |
| memory | 시간 간섭, 그리고 lockout, race condition, data 기아, deadlock, livelock, 지나친 data 지연 |
| interconnect | 접근의 중재로 생기는 시간 간섭. data가 닿는 시각의 jitter, transaction의 순서가 바뀜, 과부하 |
| 주변 장치 | 공유하는 peripheral도 간섭의 길로 식별한다 |
| 하드웨어의 동적 기능 | 주파수를 바꾸거나 core를 끄는 절전 기능이 실행 중에 동작을 바꾼다 |

지침의 목표는 이 길을 다루는 순서로 읽힌다. 프로세서의 설정 (켠 core, 주파수, interconnect의 우선순위, 공유 memory와 cache의 할당)을 정해 문서로 남기고, 간섭의 길을 식별해 고른 완화 수단을 검증하고, 모든 소프트웨어가 함께 돌 때 자원의 요구가 가용 자원을 넘지 않음을 검증한다. 한 task의 worst-case execution time (WCET, 가장 나쁜 경우의 실행 시간)은 다른 core에서 다른 소프트웨어가 돌 때 크게 늘 수 있다. 그래서 시간 간섭을 완화했음을 보이지 못하면 WCET를 분석으로 정하고, 모든 소프트웨어가 최종 구성으로 도는 실제 프로세서에서 시험으로 확인한다. 프로세서 안의 비공개 mechanism에서 생기는 간섭은 simulation이 대표하기 어렵다는 이유도 든다 (FAA, 2024, 10-11쪽).

FAA와 EASA의 두 문서는 모두 소프트웨어를 시작할 때 core에 정적으로 배치하고 운용 중에는 옮기지 않는다고 가정하며, OS나 hypervisor가 task를 core 사이에서 옮기는 플랫폼은 다루지 않는다 (FAA, 2024, 2쪽. EASA, 2022, 1-2쪽). 실행의 모양을 미리 정해 두어야 검증할 수 있다는 점에서 정적 task table과 같은 생각이라고 이 책은 읽는다.

## 프로세서 자신

소프트웨어와 OS가 모두 옳아도 프로세서가 고장 나면 계산이 틀린다. 그리고 고장 난 프로세서는 자기 고장을 믿을 만하게 알리지 못한다 (9장). 9장에 하나만 더한다. 두 core가 같은 소프트웨어를 나란히 실행하고 같은 입력에서 나온 출력을 견주는 방식을 lockstep이라고 한다 (EASA, 2022, 2쪽). 항공의 두 지침은 lockstep으로 묶인 core 사이에는 간섭에 관한 목표를 적용하지 않는다. 자동차용 MCU가 lockstep을 어떻게 쓰는지는 이 책이 확인하지 못했다.

FAA의 지침은 프로세서에 의도하지 않은 기능이 있을 수 있으므로, 프로세서와 독립인 safety net (오동작의 원인과 상관없이 동작하는 바깥의 수단)으로 그 안의 고장을 찾아 가두는 것을 고려하라고 적는다 (FAA, 2024, 5쪽, 12쪽). 예제의 외부 watchdog이 이 자리에 있다.

## 믿는다는 것

이 장의 질문에 대한 이 책의 답은 이렇다. 아래에 있는 것을 믿는다는 것은 그것이 옳다고 보이는 것이 아니라, 무엇에 기대는지를 가정으로 적고 그 가정이 깨졌을 때 드러나게 하는 것이다. 적어 둔 가정은 실제 플랫폼으로 옮길 때 다시 볼 목록이 된다. 그리고 드러나게 하는 수단은 기대는 것과 따로 서야 한다. NASA의 지침서가 watchdog을 interrupt에서 두드리지 말라고 하는 까닭도 실제 일을 하는 process가 모두 막혀도 interrupt는 돌 수 있기 때문이다 (NASA, 2004, 94쪽).

## 관통 예제에 적용

### 예제의 플랫폼

예제에는 OS가 없다. task 넷을 `example/drive-torque/src/vcu/vcu.c`의 표에 적었다.

```c
const vcu_task_t vcu_task_table[] = {
    { "input", CYCLE_MS, task_input },
    { "app", CYCLE_MS, task_app },
    { "monitor_output", CYCLE_MS, task_monitor_output },
    { "flow", CYCLE_MS, task_flow },
};
```

sim의 실행기 (`sim/scenario.c`)는 1 ms마다 주기가 된 task를 표의 순서대로 부르고, task의 실행 시간은 0이다 (`sim/scenario.h`). 네 task는 모두 `vcu_t` 하나를 pointer로 받아 함께 쓴다. 지금은 선점이 없어 경합이 없지만, RTOS로 옮겨 task마다 우선순위를 주면 이 구조체가 그대로 함께 쓰는 data가 된다.

### 실행이 틀려지는 것을 넣어 보다

실행기는 task를 부르는 자리에서 실행의 고장을 넣는다 (`docs/test-report.md` 3절).

| fault | 결과 | 잰 시간 |
|---|---|---|
| `FI-23`: 입력의 task가 멈추고, 100 ms 뒤에 운전자가 페달을 놓음 | VCU는 지난 입력으로 75 Nm를 계속 보냈다. 실행의 확인 (`SWR-20`)이 답하지 않아 외부 watchdog이 구동 허용 신호를 끊었다. VCU는 끊긴 것을 몰랐고 경고도 없었다 | 끊을 때까지 15 ms, 모터 토크가 5% 아래로 73 ms (예산 76) |
| `FI-24`: 기능, 감시와 출력, 확인의 task가 하나씩 빠짐, 모두 멈춤 | 넷 모두 watchdog이 끊었다. 출력의 task가 빠졌거나 모두 멈추면 경고가 없었다 | 6 ms |
| `FI-25`: task의 주기가 두 배로 늘어남 (clock의 고장) | 답이 창보다 늦게 가서 watchdog이 끊었다 | 16 ms |

`FI-23`에서 실행의 확인을 뺀 대조 (`NC-005`)는 가속의 차이가 1.36 m/s^2로 `SG-01`을 어겼다.

`FI-25`가 이 장의 질문에 가장 가깝다. clock이 느려지면 주기가 늘지만, 소프트웨어가 재는 시간도 같은 clock에서 나오므로 소프트웨어 안에서는 아무것도 틀려 보이지 않는다. 이것을 잡은 것은 MCU와 clock을 함께 쓰지 않는다고 가정한 외부 watchdog (`HA-01`)이었다. 그런데 sim의 watchdog은 제품과 같은 process에서 도는 model이고, 따로 된 clock을 가진 것처럼 보이는 것은 실행기가 task의 주기만 늘리기 때문이다. 실제 부품이 따로 된 clock과 전원으로 그렇게 동작하는지는 sim이 보이지 못한다.

### 플랫폼에 대한 가정

예제가 플랫폼에 기대는 것은 가정으로 적혀 있다 (`docs/hardware-assumptions.md`, `docs/technical-safety-concept.md` 4절과 9.5절).

| 가정 | 내용 | 예제에서 |
|---|---|---|
| `HA-01`, `A-24` | clock을 함께 쓰지 않는 외부 watchdog이 창 안에 옳은 답이 없으면 구동 허용 신호를 끊는다 | 소프트웨어의 몫 (`SWR-20`)만 구현했다 |
| `HA-03`, `A-19` | memory 보호가 기능의 영역과 감시의 영역을 나눈다 | 가정이다. sim에 memory 보호가 없다 |
| `HA-04` | task의 실행 시간을 감시한다 | 가정이다. sim의 실행 시간은 0이다 |
| `HA-06` | MCU의 clock을 감시한다 | 가정이다. 이것이 없을 때 외부 watchdog이 잡는 것을 `FI-25`가 보였다 |
| `HA-14` | CAN의 송신 함수는 바로 돌아오고 주기를 막지 않는다 | 가정이다. 구동 허용 신호를 CAN보다 먼저 쓰는 순서만 지켰다 |
| `A-25` | 비휘발성 memory에 쓰기를 요청하는 함수는 바로 돌아오고 주기를 막지 않는다 | 가정이다. 그 함수를 쓰는 고장 기록 (`SWR-23`)은 구현하지 않았다 |

`HA-14`의 순서는 처음에 test가 보지 못했다. sim의 HAL에는 CAN의 지연이 없어서 순서를 되돌려도 결과가 같았기 때문이다. 검토자가 이것을 찾은 뒤, sim의 HAL이 순서를 어긴 횟수를 세고 test가 그 수가 0인지 보게 했다 (`docs/test-report.md` 6절). sim이 플랫폼을 흉내 내지 못해도 가정이 기대는 순서는 세어 볼 수 있다.

### 실제 MCU와 RTOS로 옮긴다면

이 책은 예제를 실제 MCU에 올리지 않았다. 올린다면 적어도 아래를 다시 보여야 한다고 이 책은 판단한다.

| 다시 보일 것 | 까닭 |
|---|---|
| 실행 시간과 마감 | 시간 예산 (`technical-safety-concept.md` 9.4절)에는 실행 시간의 칸이 없고, watchdog의 창은 sim에 둔 임시 값이다 |
| stack의 사용량 | NASA의 지침서는 stack을 알려진 pattern으로 채우고 남은 공간을 감시하라고 권한다 (NASA, 2004, 94쪽) |
| memory 보호의 설정 | `HA-03`은 설정이 맞아야 성립하고, trusted 쪽, 같은 partition 안, DMA에는 닿지 않는다 |
| interrupt와 함께 쓰는 data | 입력을 interrupt로 받거나 task를 나누면 `vcu_t`가 함께 쓰는 data가 된다 |
| compiler가 만든 코드 | 예제의 증명과 coverage는 PC에서 본 source 코드의 논리에 대한 것이다 |
| core가 둘 넘는 MCU | 기능과 감시를 다른 core에 두면 공유 자원이 간섭의 길이 된다 |

## sim이 보이는 것과 못 보이는 것

| 보이는 것 | 못 보이는 것 |
|---|---|
| task가 빠지거나 멈추거나 주기가 늘어지면 소프트웨어가 답하지 않고 watchdog의 model이 끊는다 | 실제 외부 watchdog이 따로 된 clock과 전원으로 동작하는 것 |
| 정한 순서로 실행될 때의 논리 | 실행 시간, jitter, 마감 초과 |
| 출력을 쓰는 순서 (어긴 횟수를 세어서) | 선점과 interrupt가 만드는 data의 경합 |
| | stack의 넘침, memory 보호의 동작, multicore의 간섭, 프로세서의 고장 |
| | 주기가 짧아지거나 순서가 바뀌는 실행. unit test (`TC-021`)로만 보았다 |

## 규격에서의 위치

- ISO 26262-6 (Product development at the software level): 받은 AUTOSAR 문서는 등급이 다른 소프트웨어가 함께 있을 때의 간섭에 대해 이 Part의 Annex D (Freedom from interference between software elements)를 든다 `(2차 자료)` (AUTOSAR, 2025, 9쪽. ISO 26262:2018을 설명)
- FAA AC 20-193, EASA AMC 20-193: 항공의 multicore 지침이다. 자동차의 문서가 아니다

## 흔한 오해

- "인증받은 RTOS를 쓰면 플랫폼은 끝났다." 받은 문서가 적는 것은 OS의 보호가 하드웨어와 설정과 budget의 값에 달렸고 닿지 않는 곳이 있다는 것이다.
- "OS가 timing 보호를 하니 마감은 지켜진다." OS는 정해 준 budget을 지키게 할 뿐이다. 마감 자체는 보지 않고, budget의 값은 쓰는 쪽이 정한다.
- "MPU를 켰으니 memory가 나뉘었다." core 안에 있는 MPU는 그 core의 접근만 막는다. DMA와 다른 core는 따로 다뤄야 한다.
- "watchdog이 있으니 clock의 고장도 잡는다." 소프트웨어와 같은 clock을 쓰는 감시는 clock이 느려진 것을 모른다 (`FI-25`).

## 확인 문제

1. 예제의 `app` task만 20 ms 주기로 바꾸고 RTOS에서 우선순위를 낮게 준다고 하자. `vcu_t`의 어느 필드가 함께 쓰는 data가 되는가? `SWR-20`의 확인은 어떻게 바뀌어야 하는가?
2. `FI-24`에서 출력의 task가 빠진 경우에는 경고가 나가지 않았다. 왜 그런가? 운전자에게 알리려면 VCU 밖에 무엇이 있어야 하는가?
3. AUTOSAR OS의 Execution Budget을 쓰려면 task마다 값을 정해야 한다. `monitor_output` task의 값을 정하려면 무엇을 재거나 분석해야 하는가? 값이 너무 작으면 어느 hazard에 다가가는가?
4. 기능과 감시를 core가 둘인 MCU의 두 core에 나눠 싣는다면, 예제에서 따질 간섭의 길을 셋 들어 보라.
