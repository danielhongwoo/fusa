# 9장. 소프트웨어 엔지니어가 알아야 할 하드웨어 - 장 계획

원고: [chapters/ch09-hardware-for-software-engineers.md](../chapters/ch09-hardware-for-software-engineers.md)

| 항목 | 내용 |
|---|---|
| Part | II. Hazard에서 소프트웨어 요구사항까지 |
| 쓰는 단계 | 단계 2 (살 붙이기) |
| 상태 | 미착수 |

독자는 임베디드 개발 경험이 있다 (2026-11-22 결정). 이 장에서 임베디드의 기초는 다시 설명하지 않고, 같은 주제를 안전의 관점에서만 다룬다.

## 핵심 질문

하드웨어는 어떻게 고장 나고, 그중 무엇이 소프트웨어의 일이 되는가?

## 다룰 내용

- 하드웨어 고장의 종류: permanent, transient, latent. random과 systematic의 구분 다시 보기
- 하드웨어가 잡아 주는 것과 소프트웨어의 몫: lockstep core, ECC, 전압과 clock 감시
- MCU safety manual에서 찾는 것: assumption of use, 소프트웨어가 해야 하는 진단, 고장률과 diagnostic coverage 표의 위치
- 소프트웨어가 하는 진단: startup test, 주기적 self test (RAM, flash의 CRC, ADC 기준 전압, clock, watchdog 점검)
- 지표 읽는 법: SPFM, LFM, PMHF (ISO 26262), HFT, SFF, PFD, PFH (IEC 61508)

## 검토에서 더한 항목 (2026-11-22)

괄호 안은 지적 번호이고, 검토 기록은 `reviews/2026-11-22-plan/`에 있다. 규격의 내용에 관한 항목은 쓰기 전에 확인한다 (RULES.md 5절).

- 지표의 계산은 하지 않는다. 읽는 법만 2-3쪽으로 다룬다 (E-03, F-27)
- demand mode와 등급의 뜻은 3장에서 다룬다 (F-13)
- 차량 E/E의 기초는 부록 E에서 다룬다. MCU의 기초는 독자가 안다고 본다 (E-01, F-24)

## 예제 산출물

예제 MCU에 대한 가정 목록, 소프트웨어가 수행할 진단 목록

## 관련 규격과 자료

ISO 26262-5, -11; IEC 61508-1, -2, -6

## 근거 위치 (2026-11-22)

받은 문서에서 이 장을 뒷받침하는 곳이다. 쪽은 PDF 파일의 몇 번째 쪽인지다. 에이전트가 문서를 읽어 뽑은 것이므로, 원고에 쓰기 전에 그 쪽을 직접 읽어 확인한다 (RULES.md 5.2절).

| 문서 | 절 | 쪽 | 뒷받침하는 내용 |
|---|---|---|---|
| `autosar-safety-measures` | 4 Hardware Diagnostics (4.1 Core Test, 4.2 RAM Test) | 65-69 | 소프트웨어가 수행하는 core test와 RAM test의 fault model, 감지와 반응, 한계 |
| `nasa-gb-8719-13` | 4.6 Good Programming Practices for Safety (CPU/ROM/memory tests, watchdog, power-up checks) | 93-98 | startup 시 self test, ROM 검사, watchdog 사용 요령 |
| `nasa-toyota-ua-report` | 6.7.2 System Integrity and Fail Safe Modes (Heartbeat, Watch Dog Timer, Hardware Data Checks, Software Data Checks) / 6.9 External Theories (single event effects 설명) | 144-147, 169-170 | 실제 ECU의 EDAC, data mirroring, watchdog, 두 processor의 상호 감시, single event effect 방어 |
| `koopman-toyota-ua` | slides 29-30 (Random HW Faults, How Often Do Random Faults Happen?) | 29-30 | random hardware fault 빈도의 감각 (chip당 수만 시간에 한 번 등, 발표자의 추정치) |
| `iec-61508-overview-slides` | slides 12-13 Failure Categories | 12-13 | random hardware failure와 systematic failure 구분 다시 보기 |
| `avizienis-2004-taxonomy` | 3.2.1 A Taxonomy of Faults (permanent/transient), 5.2 Fault Tolerance | 8-10, 24-27 | fault의 지속성 분류와 error detection/recovery |

### 받은 문서에 근거가 없는 항목

이 항목은 다른 공개 문서를 찾거나, `(2차 자료)`로 밝히거나, 쓰지 않는다.

- SPFM, LFM, PMHF, HFT, SFF, PFD, PFH, lockstep, ECC, MCU safety manual - 받은 문서에 없다
- 전압, clock 감시, ADC 기준 전압 self test - autosar 4(core test, RAM test)만 있다
