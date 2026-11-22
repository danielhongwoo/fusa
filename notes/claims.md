# 근거 기록

원고에 표시 없이 쓴 사실 주장의 근거를 적는다 (RULES.md 5.5절). 확인은 Claude가 받은 문서의 해당 쪽을 직접 읽어서 한다.

## 적는 법

- ID: `C-장번호-순번`. 예: `C-06-003`. 예제의 산출물은 `C-EX-순번`으로 적는다
- 주장: 원고의 문장을 한 줄로 줄인 것
- 근거: 받은 문서의 id와 쪽. 쪽은 PDF 파일의 몇 번째 쪽인지로 적는다
- 종류: `1차` (그 문서가 직접 말하는 사실) 또는 `2차` (그 문서가 다른 규격을 설명한 것)
- 확인한 날

`2차`인 주장은 원고에서도 `(2차 자료)`로 밝힌다.

용어집 (부록 A)은 항목마다 근거를 적으므로 여기에 다시 적지 않는다. 2026-11-22의 초안 37개 항목은 근거 쪽을 직접 읽어 확인했다.

## 기록

| ID | 주장 | 근거 | 종류 | 확인한 날 |
|---|---|---|---|---|
| C-EX-001 | 보고서의 범위 안은 페달부터 inverter와 그 센서까지, 그리고 제동 우선 기능이다. 범위 밖은 모터의 토크 생성, 회생 제동을 포함한 제동 시스템의 오동작, 고전압 시스템, 운전자의 실수, 둘 이상의 고장이 겹치는 경우다 | nhtsa-etc-ev-fsa, 27-28쪽 | 1차 | 2026-11-22 |
| C-EX-002 | 보고서의 요구사항은 예시이고 NHTSA의 공식 입장이 아니다 | nhtsa-etc-ev-fsa, 13쪽, 17쪽 | 1차 | 2026-11-22 |
| C-EX-003 | 전기차는 creep을 소프트웨어로 흉내 내고, 모터 토크의 방향은 전류가 정한다 | nhtsa-etc-ev-fsa, 30-31쪽, 34쪽 | 1차 | 2026-11-22 |
| C-EX-004 | 제동 우선 상태에서 제어기는 가속 페달의 토크 요구를 따르지 않고 전류를 낮춘다. 두 페달의 충돌이 남아 있으면 이 상태를 끝내지 않는다 | nhtsa-etc-ev-fsa, 34-35쪽 | 1차 | 2026-11-22 |
| C-EX-005 | inverter의 제어부가 고장 나면 제어기가 그것을 거치지 않고 gate drive board로 모터 전류를 끊을 수 있다 | nhtsa-etc-ev-fsa, 35쪽, 32쪽 (그림 5, 이미지로 확인) | 1차 | 2026-11-22 |
| C-EX-006 | 회생 제동은 보고서의 범위 밖이다 | nhtsa-etc-ev-fsa, 28쪽, 36쪽 | 1차 | 2026-11-22 |
| C-EX-007 | H1은 의도하지 않은 가속과 같은 뜻이고, hazard는 운전자의 행동과 차량의 반응의 짝으로 정의한다 | nhtsa-etc-ev-fsa, 37쪽 | 1차 | 2026-11-22 |
| C-EX-008 | hazard별 ASIL: H1 D, H1.a B, H2 C, H3 C, H4 D, H5 C, H6 D, H7 B. H1.a의 B는 차량 속도가 0일 때만 동작하는 기능에 대한 것이다. H2와 H5의 등급은 분석자마다 달랐다 | nhtsa-etc-ev-fsa, 57쪽 | 2차 (ISO 26262 FDIS 2011) | 2026-11-22 |
| C-EX-009 | safety goal은 hazard마다 하나씩 있고 hazard의 ASIL을 받는다. 수치는 정해지지 않았다 | nhtsa-etc-ev-fsa, 58쪽 | 2차 (ISO 26262 FDIS 2011) | 2026-11-22 |
| C-EX-010 | 보고서는 safe state를 일곱 가지로 들고, 토크 0은 다른 상태를 보장할 수 없을 때의 상태로 적는다. safe state와 hazard의 차이는 변화가 제어된다는 것과 운전자가 안다는 것이다 | nhtsa-etc-ev-fsa, 68쪽 | 1차 | 2026-11-22 |
| C-EX-011 | 보고서에서 시간 값이 나오는 곳은 두 군데이고, 둘 다 업계의 관행으로 200 ms를 든다 | nhtsa-etc-ev-fsa, 80-81쪽 | 1차 | 2026-11-22 |
| C-EX-012 | 보고서가 따른 규격은 ISO 26262의 2011년 최종 초안 (FDIS)이다 | nhtsa-etc-ev-fsa, 107쪽 | 1차 | 2026-11-22 |
| C-EX-013 | E-Gas monitoring concept은 엔진 제어에 쓰는 safety concept이고 AUTOSAR 규격의 일부가 아니다. 감시 소프트웨어를 입출력에 직접 닿는 Complex Driver에 두는 설계를 보인다. 세 단계가 무엇인지는 이 문서의 글에 없다 | autosar-safety-measures, 60-61쪽 | 1차 | 2026-11-22 |
| C-02-001 | availability, reliability, safety, security의 구분 | avizienis-2004-taxonomy, 6쪽 | 1차 | 2026-11-22 |
| C-02-002 | fault가 error를 만들고 error가 밖으로 드러나면 failure다 | avizienis-2004-taxonomy, 5쪽 | 1차 | 2026-11-22 |
| C-02-003 | 부품이 하나도 고장 나지 않아도 부품 사이의 상호 작용으로 사고가 날 수 있다 | stpa-handbook, 4쪽 | 1차 | 2026-11-22 |
| C-02-004 | 위험한 failure는 random hardware failure와 systematic failure로 나뉜다 | iec-61508-overview-slides, 12-13쪽 | 2차 (IEC 61508) | 2026-11-22 |
| C-02-005 | functional safety는 safety 가운데 시스템이 입력에 맞게 올바르게 동작하는 데 달린 부분이다 | iec-61508-overview-slides, 8쪽 | 2차 (IEC 61508) | 2026-11-22 |
| C-02-006 | 자동차의 functional safety는 E/E 시스템의 오동작이 만드는 hazard에서 오는 불합리한 risk가 없는 것이다 | nhtsa-safety-standards-assessment, 14쪽 | 2차 (ISO 26262:2011) | 2026-11-22 |
| C-02-007 | safe state는 정상 동작, 성능을 낮춘 동작, 꺼진 상태일 수 있다 | nhtsa-etc-ev-fsa, 67쪽 | 2차 (ISO 26262 FDIS 2011) | 2026-11-22 |
| C-02-008 | 하드웨어의 bit가 뒤집히면 소프트웨어의 틀린 동작으로 나타나고, bit 하나가 task 하나를 멈출 수 있다 | koopman-toyota-ua, 29쪽, 31쪽 | 1차 (전문가의 발표 자료) | 2026-11-22 |
| C-03-001 | risk는 빈도와 심각도의 조합이다 | iec-61508-overview-slides, 11쪽. sora-2-5-main-body, 21쪽 | 1차 | 2026-11-22 |
| C-03-002 | 받아들일 수 있는 risk는 사회가 그 맥락에서 받아들이는 수준이다 | iec-61508-overview-slides, 11쪽 | 2차 (IEC 61508) | 2026-11-22 |
| C-03-003 | safety function에는 기능과 safety integrity의 두 면이 있다 | iec-61508-overview-slides, 10쪽 | 2차 (IEC 61508) | 2026-11-22 |
| C-03-004 | SIL은 1-4이고 safety function의 속성이다 | iec-61508-overview-slides, 14-16쪽 | 2차 (IEC 61508) | 2026-11-22 |
| C-03-005 | ASIL은 S, E, C로 정하고 가장 나쁜 상황의 값을 hazard에 준다 | nhtsa-etc-ev-fsa, 52쪽, 55쪽 | 2차 (ISO 26262 FDIS 2011) | 2026-11-22 |
| C-03-006 | PL은 a-e이고 risk graph로 정하며, SIL과 같은 척도 위에서 대응시킬 수 있다 | ifa-report-2-2017e, 15-16쪽, 32-33쪽 | 2차 (ISO 13849-1:2015) | 2026-11-22 |
| C-03-007 | SAIL은 운용의 등급이고 정량적인 값이 아니다 | sora-2-5-main-body, 47-48쪽 | 1차 | 2026-11-22 |
| C-03-008 | DAL은 개발 보증 활동의 엄격함의 수준이고, 기능에 주는 것과 item에 주는 것이 있다 | easa-moc-light-uas-2510, 5쪽. easa-moc-light-uas-high-risk-2510, 5-6쪽 | 1차 | 2026-11-22 |
| C-03-009 | DO-178B는 statement coverage를 level A-C, decision coverage를 A-B, MC/DC를 A에 요구한다 | nasa-mcdc-tutorial, 14쪽 | 2차 (DO-178B) | 2026-11-22 |
| C-03-010 | 등급을 정하고 그 등급에 맞는 개발 과정, 기술적 기법, 검증 방법을 따른다 | koopman-toyota-ua, 21-23쪽 | 1차 (전문가의 발표 자료) | 2026-11-22 |
| C-06-001 | 보고서의 순서: 시스템 정의, hazard 분석, 등급, safety goal | nhtsa-etc-ev-fsa, 21쪽 | 1차 | 2026-11-22 |
| C-06-002 | 보고서는 가정마다 그것이 깨지면 무엇을 더 분석해야 하는지 적는다 | nhtsa-etc-ev-fsa, 28쪽 | 1차 | 2026-11-22 |
| C-06-003 | HAZOP의 guide word 일곱 개 | nhtsa-etc-ev-fsa, 22쪽 | 1차 | 2026-11-22 |
| C-06-004 | hazard를 운전자의 행동과 차량의 반응의 짝으로 정의하고, 두 방법의 결과를 합쳤다 | nhtsa-etc-ev-fsa, 37쪽 | 1차 | 2026-11-22 |
| C-06-005 | S, E, C의 뜻과 예 (후륜 C3, 전륜 C2) | nhtsa-etc-ev-fsa, 54-56쪽 | 2차 (ISO 26262 FDIS 2011) | 2026-11-22 |
| C-06-006 | 분석자마다 exposure와 controllability의 평가가 달랐다. 사람은 드문 일의 빈도를 잘 어림하지 못한다 | nhtsa-etc-ev-fsa, 57쪽, 102쪽 | 1차 | 2026-11-22 |
| C-06-007 | 차가 서 있을 때만 동작하는 기능이라면 등급을 B로 볼 수 있다 | nhtsa-etc-ev-fsa, 57쪽, 101쪽 | 1차 | 2026-11-22 |
| C-06-008 | safe state에 도달하는 시간은 업계의 자료로 정하고, 없으면 기술이 허락하는 만큼 빨리 간다 | nhtsa-etc-ev-fsa, 71쪽 | 1차 | 2026-11-22 |
| C-06-009 | HARA 표의 운전 상황 다섯 개와 S, E, C의 값 | nhtsa-etc-ev-fsa, 55-56쪽, 176쪽, 178쪽, 196쪽 | 2차 (ISO 26262 FDIS 2011) | 2026-11-22 |
| C-07-001 | functional safety concept은 safety goal에서 요구사항을 끌어내어 요소에 나눠 준다 | nhtsa-etc-ev-fsa, 66쪽 | 2차 (ISO 26262 FDIS 2011) | 2026-11-22 |
| C-07-002 | 요구사항을 끌어내는 틀: 막거나 알아챈다, 정해진 시간 안에 safe state로 간다, 운전자에게 알린다 | nhtsa-etc-ev-fsa, 71쪽 | 1차 | 2026-11-22 |
| C-07-003 | 운전자 경고를 단계로 나눈 예 | nhtsa-etc-ev-fsa, 68쪽 | 1차 | 2026-11-22 |
| C-07-004 | 주 연산과 그것을 검사하는 연산을 나누는 구조는 안전 시스템의 흔한 틀이다 | koopman-toyota-ua, 32쪽 | 1차 (전문가의 발표 자료) | 2026-11-22 |
| C-07-005 | FTTI는 보통 고장을 알아채는 시간과 대응하는 시간의 합으로 본다 | autosar-e2e-protocol, 244쪽 | 2차 (ISO 26262:2018) | 2026-11-22 |
| C-07-006 | 구현 사이의 독립을 보일 수 있으면 다른 등급으로 구현할 수 있다 | nhtsa-etc-ev-fsa, 73쪽, 80쪽 | 2차 (ISO 26262 FDIS 2011) | 2026-11-22 |
| C-07-007 | 등급이 다른 소프트웨어를 함께 실으면 전체를 가장 높은 등급으로 개발하거나 freedom from interference를 보인다. 방해의 종류는 넷이다 | autosar-safety-measures, 9쪽, 72쪽 | 2차 (ISO 26262:2018) | 2026-11-22 |
| C-10-001 | 요구사항의 속성: 모호하지 않다, 빠짐없다, 서로 어긋나지 않는다, 추적할 수 있다, 검증할 수 있다 | nasa-gb-8719-13, 109-111쪽 | 1차 | 2026-11-22 |
| C-10-002 | 고장이 난 때부터 위험한 상태에 이를 때까지의 시간이 자동 대응의 필요를 정한다 | nasa-gb-8719-13, 117쪽 | 1차 | 2026-11-22 |
| C-11-001 | fault containment region의 뜻. 한 구역은 자기 고장을 다 잡지 못한다. 함께 쓰는 자원은 단일 고장점이다 | koopman-toyota-ua, 31-32쪽 | 1차 (전문가의 발표 자료) | 2026-11-22 |
| C-11-002 | 안전 시스템의 두 가지 구조: 여러 채널, 기능과 감시 | koopman-toyota-ua, 32쪽 | 1차 (전문가의 발표 자료) | 2026-11-22 |
| C-11-003 | 주 제어기의 건전성을 보조 processor로 확인한다 | nhtsa-etc-ev-fsa, 67쪽 | 1차 | 2026-11-22 |
| C-11-004 | 메모리 방해의 예 (내용의 손상, 일관되지 않은 data, stack의 넘침)와 메모리를 나누는 수단 | autosar-safety-measures, 9-10쪽 | 1차 | 2026-11-22 |
| C-11-005 | 실행 시간의 상한을 OS가 감시하고, 강제하려면 하드웨어의 도움이 필요하다. 실행 방해의 예 | autosar-safety-measures, 22쪽, 25-26쪽 | 1차 | 2026-11-22 |
| C-12-001 | 실행의 감시 세 가지: alive, deadline, logical supervision | autosar-safety-measures, 22-23쪽 | 1차 | 2026-11-22 |
| C-12-002 | 통신의 고장과 그것을 잡는 수단 (CRC, counter, data ID, timeout) | autosar-e2e-protocol, 32-33쪽 | 1차 | 2026-11-22 |
| C-12-003 | E2E 보호는 알려 줄 뿐이고 대응은 받는 쪽이 정한다 | autosar-e2e-protocol, 13-14쪽 | 1차 | 2026-11-22 |
| C-12-004 | 한 제어기가 다른 제어기에 답이 정해진 문제를 내어 건전성을 확인하는 기법 | nhtsa-etc-ev-fsa, 74쪽 | 1차 | 2026-11-22 |
| C-12-005 | 켤 때의 자가 시험과 주기적인 검사, 대응에 따르는 경고와 고장 기록 | nhtsa-etc-ev-fsa, 67쪽, 77쪽, 80쪽 | 1차 | 2026-11-22 |
| C-16-001 | 차량 수준의 test로 가능한 조건과 고장의 조합을 다 해 볼 수는 없다 | koopman-toyota-ua, 19쪽 | 1차 (전문가의 발표 자료) | 2026-11-22 |
| C-16-002 | structural coverage 분석은 요구사항에 따른 test가 코드의 구조를 얼마나 실행했는지를 본다 | nasa-mcdc-tutorial, 10-12쪽 | 1차 | 2026-11-22 |
| C-16-003 | statement coverage, decision coverage, MC/DC의 뜻. 조건이 n개면 보통 적어도 n+1개의 test | nasa-mcdc-tutorial, 13-17쪽 | 1차 | 2026-11-22 |
| C-16-004 | MC/DC의 두 방식: unique-cause와 masking | nasa-mcdc-tutorial, 19쪽, 79-82쪽 | 1차 | 2026-11-22 |
| C-16-005 | 예제의 측정값 (coverage, 시간, 변이 검사, CBMC와 coverage가 찾은 것) | example/drive-torque/docs/test-report.md, notes/tool-check.md | 이 책의 측정 | 2026-11-22 |
| C-19-001 | assurance case의 정의 | gsn-standard-v3, 10쪽 | 1차 | 2026-11-22 |
| C-19-002 | GSN의 요소와 위에서 아래로 만드는 여섯 걸음 | gsn-standard-v3, 11-13쪽, 59-61쪽 | 1차 | 2026-11-22 |
| C-19-003 | 흔한 잘못: 상자 속의 글, 모호함, 뭉뚱그림, 건너뛰기, 믿음의 도약 | gsn-standard-v3, 80-87쪽 | 1차 | 2026-11-22 |
| C-19-004 | ISO 26262에서는 산출물을 모아 safety case를 이룬다. 이 쓰임은 확증 편향으로 이끌 수 있다. 등급에 따라 확인 검토를 요구한다 | nhtsa-safety-standards-assessment, 33-34쪽 | 2차 (ISO 26262:2011) | 2026-11-22 |
| C-E-001 | 가속 페달 센서, 제어기, inverter의 제어부, gate drive, 전력 스위치, 모터가 하는 일 | nhtsa-etc-ev-fsa, 33-36쪽 | 1차 | 2026-11-22 |
| C-E-002 | 전기차와 내연기관 차량의 차이: 방향, creep, 페달을 놓았을 때, 멈춤 | nhtsa-etc-ev-fsa, 30-31쪽, 34쪽 | 1차 | 2026-11-22 |
| C-E-003 | AUTOSAR Classic의 층: 응용, RTE, basic software, OS, complex driver | autosar-safety-measures, 61쪽 (그림을 이미지로 확인) | 1차 | 2026-11-22 |
