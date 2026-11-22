# 8장. Safety analysis 기법 - 장 계획

원고: [chapters/ch08-safety-analysis.md](../chapters/ch08-safety-analysis.md)

| 항목 | 내용 |
|---|---|
| Part | II. Hazard에서 소프트웨어 요구사항까지 |
| 쓰는 단계 | 단계 2 (살 붙이기) |
| 상태 | 미착수 |

## 핵심 질문

설계가 safety goal을 위반할 수 있는 경로를 어떻게 찾는가?

## 다룰 내용

- 원인에서 결과로 (FMEA), 결과에서 원인으로 (FTA)
- HAZOP과 guide word
- STPA: 제어 구조 관점의 분석
- dependent failure analysis: common cause failure와 cascading failure
- 분석 기법을 소프트웨어 아키텍처에 적용하는 법과 한계

## 검토에서 더한 항목 (2026-11-22)

괄호 안은 지적 번호이고, 검토 기록은 `reviews/2026-11-22-plan/`에 있다. 규격의 내용에 관한 항목은 쓰기 전에 확인한다 (RULES.md 5절).

- FTA와 FMEA는 충분히, STPA는 2-3쪽, HAZOP은 소개만 한다 (E-14)
- dependent failure analysis를 11장의 freedom from interference 주장과 잇는다 (F-06)
- 단계 1에서는 이 장의 원고 없이 예제 산출물 (FTA 1개, 독립성 주장 목록)만 먼저 만든다 (F-06)

## 예제 산출물

FTA 1개, 소프트웨어 수준 FMEA 1개, STPA control structure

## 관련 규격과 자료

ISO 26262-9, ISO 26262-6 Annex E; IEC 61508-7; STPA Handbook

받은 문서: stpa-handbook

받은 문서 (추가): nhtsa-etc-ev-fsa (HAZOP, STPA, FMEA를 같은 시스템에 적용한 예)

## 근거 위치 (2026-11-22)

받은 문서에서 이 장을 뒷받침하는 곳이다. 쪽은 PDF 파일의 몇 번째 쪽인지다. 에이전트가 문서를 읽어 뽑은 것이므로, 원고에 쓰기 전에 그 쪽을 직접 읽어 확인한다 (RULES.md 5.2절).

| 문서 | 절 | 쪽 | 뒷받침하는 내용 |
|---|---|---|---|
| `stpa-handbook` | Ch.2 How to Do a Basic STPA Analysis (Step 2 control structure, Step 3 UCA, Step 4 loss scenarios) | 24-52 | STPA의 단계: 제어 구조 모델, unsafe control action 4가지 형태, loss scenario |
| `stpa-handbook` | Ch.1 Introduction / Ch.3 Integrating STPA into the System Engineering Process | 4-13, 54-71 | FTA, FMEA, HAZOP과 대비한 STPA의 위치, 설계 단계별 적용 |
| `nhtsa-etc-ev-fsa` | 2.2 Hazard and Safety Analysis Methods (HAZOP, Functional FMEA, STPA) / 7.1 Functional FMEA / 7.2 STPA Step 2 | 21-26, 59-65 | 같은 시스템(전기차 가속 제어)에 HAZOP, FMEA, STPA를 적용한 예와 결과 수 비교 |
| `nasa-gb-8719-13` | 6.6.7 Software Fault Tree Analysis / Appendix C SFTA / Appendix D SFMEA (D.4 Process) | 131, 315-337 | 소프트웨어 FTA와 FMEA의 목적, 절차, 한계 |
| `nasa-gb-8719-13` | 7.4.2 Designing around Faults and Failures (7.4.2.2 Fault Containment Regions) / 7.5.3 Independence Analysis | 141-145, 158-159 | 독립성 주장과 fault propagation 방지, 독립성 분석 |
| `nasa-toyota-ua-report` | 6.5.2 System Failures (High Level Functional Fault Tree) | 68-80 | 실제 시스템에 대한 functional fault tree와 failure mitigation 대응 |
| `koopman-toyota-ua` | slides 31-34 (Fault Containment Regions, Redundancy, Split Input Sources, VPA1/VPA2) | 31-34 | 단일 고장점과 독립적인 fault containment region의 필요 (dependent failure 논의 예) |
| `b737max-jatr` | R6.8, R6.9 (single and multiple failure analysis) | 53-54 | 단일 최악 시나리오만 분석하면 안 됨, cascading effects 분석 요구 |

### 받은 문서에 근거가 없는 항목

이 항목은 다른 공개 문서를 찾거나, `(2차 자료)`로 밝히거나, 쓰지 않는다.

- HAZOP guide word의 일반 정의, dependent failure analysis (CCF, cascading)의 규격 정의 - nhtsa-etc의 HAZOP 적용 예와 koopman FCR 슬라이드가 간접 근거
