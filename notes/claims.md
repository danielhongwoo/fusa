# 근거 기록

원고에 표시 없이 쓴 사실 주장의 근거를 적는다 (RULES.md 5.5절). 확인은 Claude가 받은 문서의 해당 쪽을 직접 읽어서 한다.

## 적는 법

- ID: `C-장번호-순번`. 예: `C-06-003`. 예제의 산출물은 `C-EX-순번`으로 적는다
- 주장: 원고의 문장을 한 줄로 줄인 것
- 근거: 받은 문서의 id와 쪽. 쪽은 PDF 파일의 몇 번째 쪽인지로 적는다
- 종류: `1차` (그 문서가 직접 말하는 사실) 또는 `2차` (그 문서가 다른 규격을 설명한 것)
- 확인한 날

`2차`인 주장은 원고에서도 `(2차 자료)`로 밝힌다.

단계 2부터의 절차: 에이전트가 문서를 읽어 `notes/reading/`에 사실과 짧은 인용을 적는다. `tools/quotecheck.py`가 인용이 그 쪽에 실제로 있는지 본다. 그 뒤에 진행자가 원고에 쓴 문장의 핵심 쪽을 직접 읽는다. 직접 읽은 쪽은 근거 칸에 적었다. 적지 않은 것은 인용의 대조까지만 한 것이다.

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
| C-07-004 | 주 CPU가 계산하고 다른 CPU가 검사하는 구조는 안전 시스템의 흔한 틀이다 | koopman-toyota-ua, 32쪽 | 1차 (전문가의 발표 자료) | 2026-11-22 |
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
| C-19-004 | ISO 26262에서는 산출물을 모아 safety case를 이루고 그것으로 규격을 따랐음을 보인다. 시스템이 안전하다는 것을 증명하려 하면 확증 편향에 빠질 수 있다 (Leveson의 지적을 옮긴 것). 등급에 따라 확인 검토를 요구한다. 설계에서 독립인 검토자는 설계를 잘 몰라 위험을 찾지 못할 수 있다 | nhtsa-safety-standards-assessment, 34쪽 | 2차 (ISO 26262:2011) | 2026-11-22 |
| C-E-001 | 가속 페달 센서, 제어기, inverter의 제어부, gate drive, 전력 스위치, 모터가 하는 일 | nhtsa-etc-ev-fsa, 33-36쪽 | 1차 | 2026-11-22 |
| C-E-002 | 전기차와 내연기관 차량의 차이: 방향, creep, 페달을 놓았을 때, 멈춤 | nhtsa-etc-ev-fsa, 30-31쪽, 34쪽 | 1차 | 2026-11-22 |
| C-E-003 | AUTOSAR Classic의 층: 응용, RTE, basic software, OS, complex driver | autosar-safety-measures, 61쪽 (그림을 이미지로 확인) | 1차 | 2026-11-22 |
| C-03-011 | IEC 61508과 기계 분야의 규격은 등급마다 위험한 고장의 확률의 목표를 둔다 | iec-61508-overview-slides, 17쪽. ifa-report-2-2017e, 15-16쪽 | 2차 (IEC 61508, ISO 13849-1:2015) | 2026-11-22 |
| C-03-012 | QM은 quality management의 약어이고 등급 표에서 ASIL이 붙지 않는 결과다 | nhtsa-etc-ev-fsa, 12쪽, 55쪽 | 2차 (ISO 26262 FDIS 2011) | 2026-11-22 |
| C-06-010 | 등급 표의 구조: S3, E4, C3일 때만 D이고, 어느 하나가 한 단계 좋아질 때마다 한 단계 내려간다 | nhtsa-etc-ev-fsa, 55쪽 | 2차 (ISO 26262 FDIS 2011) | 2026-11-22 |
| C-06-011 | 보고서의 200 ms는 고장이 난 때부터 safe state로 갈 때까지의 시간이다 | nhtsa-etc-ev-fsa, 80-81쪽 | 1차 | 2026-11-22 |
| C-07-008 | 예제의 처음 설계에서 허용 토크와 정상 동작의 틈이 SG-01의 한계를 넘었다 (1.1-2.4 m/s^2). 고친 뒤의 틈은 5 Nm다 | reviews/2026-11-22-stage1/round1-fusa.md의 F-01, example/drive-torque/docs/technical-safety-concept.md 3절 | 이 책의 측정 | 2026-11-22 |
| C-12-006 | 브레이크 페달 신호의 검사를 요구사항으로 든다 | nhtsa-etc-ev-fsa, 81쪽 | 1차 | 2026-11-22 |
| C-16-006 | 변이 10개는 모두 잡았으나 검토자가 21개를 더 넣자 4개를 놓쳤다. 처음의 FI-02는 감시가 없어도 통과했다 | reviews/2026-11-22-stage1/round1-embedded.md의 E-01, E-02 | 이 책의 측정 | 2026-11-22 |
| C-01-001 | Ariane 501 조사 위원회: 소프트웨어는 기계 시스템과 같은 뜻으로 고장 나지 않는다. 옳다고 보일 때까지 틀렸다고 보라 | ariane-501-report, 10쪽 (스캔본. OCR 글자로 확인) | 1차 | 2026-11-22 |
| C-01-002 | Ariane 501: 1996-06-04, 비행 시작 약 40초 뒤에 궤도를 벗어나 부서지고 폭발했다 | ariane-501-report, 2쪽 (OCR 글자로 확인) | 1차 | 2026-11-22 |
| C-01-003 | Ariane 501의 사슬: 64-bit 부동소수점을 16-bit 정수로 바꾸다 예외. 정렬 기능이 이륙 뒤 약 40초 돌았고 그 요구는 Ariane 4의 것. 대기 장치는 앞 주기 (72 ms)에 같은 이유로 멈춤. 기술적 원인은 합리적 의심의 여지 없이 확립 | ariane-501-report, 7-8쪽 (8쪽은 쪽의 그림을 직접 읽음) | 1차 | 2026-11-22 |
| C-01-004 | Ariane 501: 변환 일곱 가운데 넷만 보호. 궤적 data를 명세에 넣지 않기로 합의. 예외가 나면 processor를 멈추는 명세. random hardware failure만 다루는 문화. 같은 소프트웨어가 두 장치에서 돈다 | ariane-501-report, 9쪽 (쪽의 그림을 직접 읽음) | 1차 | 2026-11-22 |
| C-01-005 | Ariane 501: 장치를 Ariane 5의 궤적으로 시험한 일이 없다. 앞선 사용으로 검증되었다고 보는 것은 위험했다 | ariane-501-report, 11쪽, 13쪽 (OCR 글자로 확인) | 1차 | 2026-11-22 |
| C-01-006 | Therac-25: 1985-06부터 1987-01 사이에 대량 과조사 사고 여섯 건, 사망과 중상. 저자들은 제조사의 개발 자료를 구하지 못했다 | Leveson과 Turner (1993), IEEE Computer 26(7), 18-19쪽. RIT 강의 사이트의 사본을 읽음 (웹, 2026-11-22) | 1차 (논문). 공식 조사 보고서가 아니다 | 2026-11-22 |
| C-01-007 | Therac-25: 앞선 기종은 하드웨어 안전 장치와 interlock을 유지. Therac-25는 모두 다시 넣지 않기로 함. 소프트웨어는 앞선 기종의 것에서 출발. 처음의 fault tree는 소프트웨어 오류를 넣지 않음 | Leveson과 Turner (1993), 19-21쪽 | 1차 (논문) | 2026-11-22 |
| C-01-008 | Therac-25의 두 결함: 공유 변수로 통신하는 task 사이의 경합, 1 byte 변수가 256번째마다 0이 됨. 같은 결함이 Therac-20에도 있었으나 hardware interlock이 결과를 막았다 | Leveson과 Turner (1993), 29-31쪽, 34쪽, 39쪽 | 1차 (논문) | 2026-11-22 |
| C-01-009 | Therac-25의 교훈: 소프트웨어에만 안전의 책임을 지우지 않는다. interlock 제거가 소프트웨어를 single point of failure로 만들었다. 컴퓨터 관련 사고의 대부분은 coding이 아니라 요구사항의 오류 | Leveson과 Turner (1993), 38-39쪽 | 1차 (논문). 저자들의 의견 | 2026-11-22 |
| C-01-010 | NASA의 Toyota 조사: 설계와 소스 코드에 제한 없이 접근. 가설 둘. 28만 줄 넘는 코드에서 길을 찾지 못함. 신고는 보도와 함께 늘었다 | nasa-toyota-ua-report, 13-16쪽 | 1차 | 2026-11-22 |
| C-01-011 | NASA의 결론과 스스로 적은 한계: 증거를 찾지 못한 것이 일어날 수 없다는 뜻은 아니다. 분석은 2005년식 Camry에 한정. 소프트웨어 연구는 2010-04 중순부터 08 중순. 쓴 도구로는 결함을 찾지 못함. 사건 전의 소프트웨어 상태를 남기는 수단이 없다 | nasa-toyota-ua-report, 17쪽, 148-150쪽, 170-173쪽 | 1차 | 2026-11-22 |
| C-01-012 | 원고 쪽 전문가의 주장: NASA는 시스템에 문제가 없다고 한 것이 아니다. 공유된 입력이 single point of failure. watchdog이 주요 task의 죽음을 못 잡는다. 코드 품질. 시험만으로 안전을 보일 수 없다 | koopman-toyota-ua, 9-10쪽, 19-20쪽, 33-34쪽, 36-45쪽 | 1차 (한쪽의 주장. 숫자의 출처인 NASA 부록 A와 증언 기록은 확인하지 않았다) | 2026-11-22 |
| C-01-013 | 법정의 결과: 2013년 민사 재판의 배심 평결 300만 달러, 징벌적 배상 전에 합의. 2014년 법무부와 12억 달러 합의는 바닥 매트와 페달에 한정 | koopman-toyota-ua, 12쪽, 15-17쪽 | 1차 (원고 쪽 전문가의 자료에 실린 요약) | 2026-11-22 |
| C-01-014 | 737 MAX: Lion Air 610 (2018-10-29, 189명)과 Ethiopian 302 (2019-03-10, 157명). Lion Air 사고기에서 약 6분 동안 20번 넘게 자동 trim | b737max-ntsb-asr1901, 1-3쪽 | 1차 | 2026-11-22 |
| C-01-015 | MCAS의 설계: 받음각 센서 하나의 값. trim 스위치 뒤 5초가 지나면 다시 움직임. uncommanded MCAS를 major로 분류해 FMEA와 fault tree를 하지 않음. 조종사가 3초 안에 반응한다는 가정. 기여 요인은 시간 순서 | b737max-knkt-jt610, 50-52쪽, 191-196쪽, 217쪽 | 1차 | 2026-11-22 |
| C-01-016 | 737 MAX의 hazard 평가: 시험은 꼬리 날개의 움직임만 흉내 냄. 함께 오는 경고가 평가에 없었다. 세 비행 모두 조종사의 반응이 가정과 달랐다 | b737max-ntsb-asr1901, 5-8쪽 | 1차 | 2026-11-22 |
| C-01-017 | JATR: fault tolerant한 특징이 없었다. 가정과 분석을 검증 없이 다시 씀. 요구사항 개정 뒤의 분석이 없음. 같은 팀이 설계와 안전 평가. 규정을 다 지켜도 안전이 보장되지는 않는다 | b737max-jatr, 4쪽, 50-54쪽 | 1차 | 2026-11-22 |
| C-01-018 | 하원 위원회 보고서: 생산의 압박, 10초 넘는 반응이 치명적이라는 내부 평가가 당국에 전해진 기록 없음, 2015년 엔지니어의 질문, 설계 요구사항 둘 | b737max-house-report, 19-21쪽, 114-127쪽 | 1차 (위원회 다수당 직원의 보고서. 조사 기관의 결론이 아니다) | 2026-11-22 |
| C-01-019 | 1장의 실행 예: 안전 장치가 없는 제어기는 4초 동안 13.3에서 31.1 km/h로 가속. 예제의 제어기는 11.6 km/h | example/drive-torque에서 make intro | 이 책의 측정 | 2026-11-22 |
| C-04-001 | IEC 61508은 분야를 가리지 않는 기본 규격이고 분야별, 제품별 규격의 바탕이다. IEC 62061, 61511, 61513, 61800-5-2 | iec-61508-overview-slides, 4-7쪽 | 2차 (IEC의 발표 자료) | 2026-11-22 |
| C-04-002 | ISO 26262는 IEC 61508을 도로 차량에 맞춘 규격이다. 2011년 판은 10개 Part이고 2-7이 핵심 | nhtsa-safety-standards-assessment, 14쪽 | 2차 (ISO 26262:2011) | 2026-11-22 |
| C-04-003 | 기계 규격의 계층: ISO 12100 (Type A), ISO 13849-1 (전기, 전자, 유압, 공압, 기계. 제품 규격이 거의 모두 참조). 두 규격의 요구사항을 섞지 않는다 | ifa-report-2-2017e, 11쪽, 15-17쪽 | 2차 (EN ISO 13849-1:2015) | 2026-11-22 |
| C-04-004 | DO-178C는 소프트웨어 개발을 시스템 개발의 부분으로 보고, 안전 요구사항이 위에서 주어진다고 가정한다 | nhtsa-safety-standards-assessment, 16쪽 | 2차 | 2026-11-22 |
| C-04-005 | SORA는 처방하는 요구사항이 아니라 위험에 맞춘 안전 목표를 담는다. 점검표로 쓰지 않는다. 인정된 방법으로 제안되며 당국이 바꿀 수 있다 | sora-2-5-main-body, 18-19쪽 | 1차 | 2026-11-22 |
| C-04-006 | 규격의 네 가지 방식: 과정을 정함, 방법을 나열함, 성능을 정함, 설계를 정함. 과정 규격의 약점 | nhtsa-safety-standards-assessment, 19-21쪽 (직접 읽음) | 1차 (보고서의 분석) | 2026-11-22 |
| C-04-007 | safety function의 기능은 hazard 분석에서, integrity는 risk 평가에서 나온다. lifecycle 셋. 규격을 따른다는 것의 네 요소. 규제 기관이 국제 규격을 합리적인 수준의 기준으로 쓴다 | iec-61508-overview-slides, 2쪽, 10쪽, 14쪽, 21-22쪽 | 2차 (IEC의 발표 자료) | 2026-11-22 |
| C-04-008 | ISO 13849-1은 등급을 계산하는 방법을 쓰는 사람에게 맡긴다. 제품별 규격에 없으면 safety function은 설계자가 정한다. 조화 규격과 적합 추정 | ifa-report-2-2017e, 11쪽, 16쪽, 20쪽, 29쪽 | 2차 | 2026-11-22 |
| C-04-009 | ISO 26262의 safety 정의에서 무엇이 불합리한지는 더 정의되지 않는다 | nhtsa-safety-standards-assessment, 21쪽 (직접 읽음) | 2차 (ISO 26262:2011) | 2026-11-22 |
| C-04-010 | FAA AC 20-115D: 인정된 방법이고 유일한 방법이 아니다. 의무도 규정도 아니다. 쓰면 모든 점에서 따른다 | faa-ac-20-115d, 1쪽 (직접 읽음) | 1차 | 2026-11-22 |
| C-04-011 | FMVSS는 법으로 정한 성능 요구사항이고 제조사가 스스로 인증한다. ISO 26262는 자발적인 업계 규격 | nhtsa-safety-standards-assessment, 14쪽, 16-17쪽 | 1차 (보고서) | 2026-11-22 |
| C-04-012 | shall, should, may, can, must의 뜻. normative와 informative | ISO/IEC Directives, Part 2, 9판 (2021), 3.2.1 - 3.3.8, 7절. https://www.iso.org/sites/directives/current/part2/index.xhtml (웹, 2026-11-22) | 1차 | 2026-11-22 |
| C-04-013 | GSN 표준의 Part 1만 normative. SORA는 should를 강한 의무로 정의 | gsn-standard-v3, 9쪽. sora-2-5-main-body, 29쪽 | 1차 | 2026-11-22 |
| C-04-018 | ISO의 소개 글: Part 3에 hazard analysis and risk assessment, Part 8에 형상과 변경의 관리 | https://www.iso.org/publication/PUB200262.html (웹, 2026-11-22. 에이전트가 읽음) | 1차 (발행 기관의 판매 설명) | 2026-11-23 |
| C-04-014 | ISO 26262:2018의 Part 제목, IEC 61508:2010의 Part 제목 | references/standards.md의 기록 (발행 기관의 목록에서 확인). ISO 26262-1:2018의 페이지 https://www.iso.org/standard/68383.html (웹, 2026-11-22) | 1차 (제목만) | 2026-11-22 |
| C-04-015 | DO-178C: 소프트웨어를 따로 인증하지 않는다. MIL-STD-882E는 인증 규격이 아니다. ISO 26262는 산출물을 모아 safety case로 삼고 confirmation review의 독립을 요구 | nhtsa-safety-standards-assessment, 33-34쪽 | 2차 (DO-178C와 ISO 26262:2011을 보고서가 인용) | 2026-11-22 |
| C-04-016 | ISO 26262 다음 판: Part 3, 6, 12의 초안 (DIS)이 의견을 받는 단계. Part 3의 제목이 Product development at the item level로 바뀜. 이미 개발 중인 시스템은 적용 범위에서 빠진다는 소개 글. Part 12의 초안은 2판 | https://www.iso.org/standard/90022.html, 90025.html, 90031.html (웹, 2026-11-22. 직접 읽음). 나머지 Part는 에이전트가 읽었다 | 1차 (발행 기관의 페이지) | 2026-11-22 |
| C-04-017 | IEC 61508-1의 Edition 3은 만들고 있고 발행 예정일이 2026-10-22로 적혀 있다 | https://webstore.iec.ch/en/publication/5515 (웹, 2026-11-22. 직접 읽음) | 1차 (발행 기관의 페이지) | 2026-11-22 |
| C-05-001 | HSE의 사고 34건 분석: 명세 44%, 설계와 구현 15%, 설치와 시운전 6%, 운전과 유지보수 15%, 변경 20%. 표본이 작아 통계적 의미가 낮다고 HSE가 적는다 | hse-hsg238, 30-31쪽 (직접 읽음) | 1차 | 2026-11-22 |
| C-05-002 | HSE 분석의 한계: 사고는 HSE에 알려졌거나 내부 보고서의 것. 주된 원인의 배정은 판단. 분석은 1995년 초판과 같다. 결론: 체계적인 접근으로 막을 수 있었던 결함 | hse-hsg238, 4쪽, 6쪽, 11쪽, 33쪽 | 1차 | 2026-11-22 |
| C-05-003 | 소프트웨어 문제의 대부분은 명세의 문제. 고치는 비용은 뒤로 갈수록 커진다 | nasa-gb-8719-13, 105쪽, 286쪽 | 1차 | 2026-11-22 |
| C-05-004 | safety lifecycle: 단계마다 입력, 목적, 활동, 산출물. verification과 assessment가 모든 단계에 걸친다. 앞 단계를 공식으로 다시 본다. waterfall이 아니고 조직 구조를 요구하지 않는다 | hse-hsg238, 37-38쪽 | 1차 | 2026-11-22 |
| C-05-005 | ISO 26262의 lifecycle에는 생산, 운용, 정비, 폐기가 있다 | nhtsa-safety-standards-assessment, 32쪽 | 2차 (ISO 26262:2011) | 2026-11-22 |
| C-05-006 | ISO 26262의 concept phase의 흐름 (item, hazard, risk, safety goal, safety analysis, functional safety concept, 요구사항) | nhtsa-etc-ev-fsa, 19-20쪽 (그림 1은 에이전트가 그림으로 읽음) | 2차 (ISO 26262 FDIS 2011) | 2026-11-22 |
| C-05-007 | safety plan에 들어가는 것. 따로 된 문서일 수도 다른 계획의 일부일 수도 있다 | nasa-gb-8719-13, 23쪽, 101쪽. nasa-std-8739-8b, 6쪽 | 1차 | 2026-11-22 |
| C-05-008 | 역할과 소통의 길. 관리자가 risk를 정한다. 독립된 보고의 길. 작은 팀의 겸임 | nasa-gb-8719-13, 33-34쪽 | 1차 | 2026-11-22 |
| C-05-009 | verification, audit, functional safety assessment의 풀이 | hse-hsg238, 43쪽, 52쪽. nasa-std-8739-8b, 10쪽 | 1차 | 2026-11-22 |
| C-05-010 | AUTOSAR가 제공하지 않는 것의 목록에 confirmation measure와 functional safety audit이 있다. 구현하는 쪽이 lifecycle을 보장해야 한다 | autosar-safety-measures, 45-46쪽 | 1차 (AUTOSAR의 문서). ISO 26262의 용어에 대해서는 2차 | 2026-11-22 |
| C-05-011 | ISO 26262의 confirmation review는 개발자, 프로젝트 관리, 작성자로부터의 독립을 요구한다. 독립된 검토자의 한계에 관한 보고서의 비판 | nhtsa-safety-standards-assessment, 34쪽 | 2차 (ISO 26262:2011). 비판은 보고서의 의견 | 2026-11-22 |
| C-05-012 | 독립의 세 가지: 기술, 관리, 재정. 위험이 클수록 더 독립된 검증 | nasa-std-8739-8b, 48쪽 (직접 읽음). nasa-gb-8719-13, 42쪽 | 1차 | 2026-11-22 |
| C-05-013 | JATR: 같은 팀이 설계와 안전 평가. 독립되고 권한 있는 안전 기능의 권고. hazard 평가가 정해진 설계를 문서로 만드는 데 쓰인다는 인식. 회사 자신의 지침에 맞지 않음 | b737max-jatr, 50-53쪽 | 1차 | 2026-11-22 |
| C-05-014 | 계약으로 만드는 소프트웨어에서 정해 둘 것 | nasa-gb-8719-13, 282-287쪽 | 1차 | 2026-11-22 |
| C-05-015 | tailoring: 필요한 일은 다 하고 필요한 일만. 줄일 수 없는 바닥. 줄이면 이유와 승인. 범위를 나눔. 작은 프로젝트의 주장에 관한 경고 | nasa-gb-8719-13, 43-46쪽 (46쪽은 직접 읽음), 87쪽. nasa-std-8739-8b, 56-57쪽. hse-hsg238, 33쪽 | 1차 | 2026-11-22 |
| C-05-016 | safety culture에 관한 지적들 | hse-hsg238, 7쪽, 32쪽. nasa-gb-8719-13, 265쪽. b737max-jatr, 50쪽. b737max-house-report, 19-21쪽 (위원회의 판단) | 1차 | 2026-11-22 |
| C-05-017 | ISO 26262는 safety culture와 안전 관리를 강조한다 | nhtsa-safety-standards-assessment, 15쪽 | 2차 (ISO 26262:2011) | 2026-11-22 |
| C-01-020 | Leveson과 Turner: 대부분의 사고는 시스템의 사고이고, 사고에 원인 하나를 붙이는 것은 대개 심각한 잘못이다 | Leveson과 Turner (1993), 18쪽 (직접 읽음) | 1차 (논문). 저자들의 의견 | 2026-11-23 |
| C-01-021 | NASA가 찾은 것: 신고 차량의 페달에서 두 신호 출력을 잇는 tin whisker. 두 번째 고장이 겹치면 이론적으로 가능. 고장 하나로 5도 미만, 운전자 입력과 겹쳐 15도까지 열리는 길 | nasa-toyota-ua-report, 16-17쪽 (직접 읽음) | 1차 | 2026-11-23 |
| C-01-022 | 737 MAX: 가정은 업계 지침과 맞았고 센서 하나에 기댄 설계는 모든 인증 요건을 만족했다 (기여 요인 1, 2). AOA DISAGREE 경고의 소프트웨어가 인증받은 설계와 달랐고 개발과 인증 중에 발견되지 않았다 (기여 요인 5) | b737max-knkt-jt610, 180쪽, 217쪽 (직접 읽음) | 1차 | 2026-11-23 |
| C-01-023 | 2014년의 형사 수사: 12억 달러의 벌금, 3년의 기소 유예, 사유는 두 문제를 감춘 것 | koopman-toyota-ua, 16쪽 (직접 읽음) | 1차 (원고 쪽 전문가의 자료에 실린 요약) | 2026-11-23 |
| C-05-018 | validation의 뜻. HSE는 요구사항의 명세가 옳은지를 functional safety assessment에 넣는다 | hse-hsg238, 52쪽 (직접 읽음) | 1차 | 2026-11-23 |
| C-08-001 | 연역과 귀납, 둘을 함께 써야 하는 까닭. fault tree는 모든 고장의 모델이 아니다. minimal cut set과 single failure. 같은 종류의 사건으로 된 cut set은 common cause의 신호 | nasa-fault-tree-handbook, 15-16쪽, 24-25쪽, 33-36쪽, 45쪽 | 1차 | 2026-11-23 |
| C-08-002 | FMEA 여러 개를 이어 붙여 fault tree를 만들지 않는다. FMEA로 tree를 점검할 수 있다 | nasa-fault-tree-handbook, 67쪽 | 1차 | 2026-11-23 |
| C-08-003 | common cause failure의 뜻과 네 가지 예. 독립이면 10^-9, 1%가 공통 원인이면 10^-5 (만 배) | nasa-fault-tree-handbook, 70-72쪽 (72쪽은 직접 읽음) | 1차 (숫자는 handbook의 예) | 2026-11-23 |
| C-08-004 | 소프트웨어 기능의 고장 확률을 쓰지 않는다 (MIL-STD-882E), 소프트웨어의 오류는 하드웨어의 random한 고장처럼 수로 나타낼 수 없다 (DO-178C) | nhtsa-safety-standards-assessment, 29쪽 (직접 읽음) | 2차 (보고서가 두 규격을 인용) | 2026-11-23 |
| C-08-005 | 소프트웨어 fault tree는 reliability에 관해 주장하지 않는다. 논리가 hazard를 만들지 않음을 보이는 것이고 위험한 상태가 적은 시스템에서 쓸 만하다 | nasa-gb-8719-13, 316-317쪽 | 1차 | 2026-11-23 |
| C-08-006 | 소프트웨어 FMEA: data와 사건이 틀리는 방식, interface, 찾아 주는 것과 한계 (한 번에 고장 하나) | nasa-gb-8719-13, 322-324쪽, 328쪽, 336-337쪽 | 1차 | 2026-11-23 |
| C-08-007 | HAZOP의 guide word: 규격은 열한 개를 제안, 보고서는 일곱 개를 씀. 분석의 순서 (hazard 분석 뒤에 safety analysis) | nhtsa-etc-ev-fsa, 21-22쪽 | 1차 (보고서가 한 일). ISO 26262에 관해서는 2차 | 2026-11-23 |
| C-08-008 | STPA: 고장 없이도 위험할 수 있다는 가정, Mars Polar Lander, 네 단계, control structure와 process model, unsafe control action의 네 유형, 실제 상태로 적는다, 위험한 명령의 네 가지 까닭, 앞의 명령이 실행되었다고 가정하는 잘못 | stpa-handbook, 4쪽, 7-8쪽, 14쪽, 17쪽, 22-25쪽, 35-40쪽 (36쪽은 직접 읽음), 43-46쪽 | 1차 (handbook의 방법). 다른 기법보다 낫다는 것은 저자들의 주장 | 2026-11-23 |
| C-08-009 | control structure는 물리적인 관계를 보통 담지 않는다 | stpa-handbook, 31쪽 | 1차 | 2026-11-23 |
| C-08-010 | fault propagation의 뜻. 따로 만든 소프트웨어도 정말로 독립이기 어렵다. 같은 운영 체제를 돌리는 두 processor는 독립이 아니다 (규정의 인용). independence analysis: 안전에 관련된 요소에 영향을 주는 요소는 안전에 관련된 요소가 된다 | nasa-gb-8719-13, 141-144쪽 (143-144쪽은 직접 읽음), 157-159쪽 | 1차 | 2026-11-23 |
| C-08-011 | 소프트웨어 요소 사이의 간섭 네 가지 (memory, 시간, 실행, 정보의 교환). dependent failure analysis라는 이름. AUTOSAR는 그 분석을 하지 않는다 | autosar-safety-measures, 9-10쪽, 21쪽, 46쪽 | 2차 (ISO 26262:2018을 설명) | 2026-11-23 |
| C-08-012 | FMEA, FTA는 random한 하드웨어 고장이 주된 원인이던 때의 기법이고 소프트웨어에 그대로 맞지 않는다 | nhtsa-safety-standards-assessment, 23-24쪽 | 1차 (보고서 저자의 주장) | 2026-11-23 |
| C-08-013 | NASA의 Toyota 조사: 원인을 늘어놓은 그림에는 조합의 논리가 없고 fault tree가 그것을 보인다 | nasa-toyota-ua-report, 71쪽 | 1차 | 2026-11-23 |
| C-08-014 | 예제의 분석 결과: minimal cut set 여덟 (하나짜리 일곱), FMEA 22줄, unsafe control action 11개, 독립에 기대는 곳 넷. 두 신호의 단락을 250-351 mV에서 판정하지 않는다 | example/drive-torque/docs/의 fta.md, fmea.md, stpa.md, dfa.md. 단락은 scratchpad의 시험 코드로 잼 | 이 책의 분석과 측정 | 2026-11-23 |
| C-09-001 | 컴퓨터 하나는 고장을 하나도 견디지 못한다. 위험의 원인이 processor의 고장이면 막는 것은 다른 processor에 있어야 한다 | nasa-gb-8719-13, 22쪽 (직접 읽음) | 1차 | 2026-11-23 |
| C-09-002 | permanent와 transient fault, active와 dormant, 덮는 설계는 알아채는 수단과 함께 쓴다, 같은 설계의 channel은 독립의 가정에 기댄다 | avizienis-2004-taxonomy, 5쪽, 9쪽, 24-26쪽 (25쪽은 직접 읽음) | 1차 | 2026-11-23 |
| C-09-003 | soft error: memory cell과 register의 bit 반전. Toyota 제어기의 보호 수단: memory의 검출과 정정 (1 bit 정정, 2 bit 검출), 뒤집은 사본, watchdog, 두 processor의 상호 점검, 전압 감시 | nasa-toyota-ua-report, 144-147쪽, 169-170쪽 | 1차 (NASA의 서술. 원고 쪽 전문가는 일부를 다툰다) | 2026-11-23 |
| C-09-004 | 고장률과 평균 시간, FIT, 평균이지 보장된 수명이 아니다, 위험한 쪽을 모르면 절반. diagnostic coverage의 뜻과 네 값. 시험의 간격, 찾은 뒤의 safe state, 시험하는 쪽의 독립. common cause의 몫이 10%를 넘으면 중복의 이점이 사라진다. 논리적인 두 channel | ifa-report-2-2017e, 53쪽, 55-61쪽, 285-288쪽 (53, 57-58, 286-287쪽은 직접 읽음) | 2차 (EN ISO 13849-1:2015) | 2026-11-23 |
| C-09-005 | 켤 때의 processor와 RAM 시험은 transient fault를 찾지 못한다. 자원을 혼자 써야 해서 켤 때로 몰린다. processor 안의 오류는 믿을 수 있게 보고되지 않는다. RAM 시험의 세 단계 (60, 90, 99%). memory 보호 장치는 그 core의 접근만 막는다 | autosar-safety-measures, 18쪽, 65-69쪽 (66-68쪽은 직접 읽음) | 1차 (AUTOSAR의 문서). ISO 26262에 관해서는 2차 | 2026-11-23 |
| C-09-006 | 켤 때의 시험, 프로그램 memory의 검사, watchdog에 interrupt로 신호를 보내지 않는다, 사본과 CRC, 되읽기, 하드웨어 고장의 목록을 만든다. 소프트웨어의 방벽은 하드웨어의 고장으로 무너질 수 있다 | nasa-gb-8719-13, 93-98쪽, 118쪽, 144쪽 | 1차 | 2026-11-23 |
| C-09-007 | 건강의 확인 (memory, ADC의 시험), 문제를 내고 답을 확인하는 방식, 주기적인 시험의 빈도, single-point fault와 latent fault의 지표 | nhtsa-etc-ev-fsa, 67쪽, 73-76쪽, 93쪽 | 2차 (ISO 26262 FDIS 2011). 보고서가 든 요구사항의 예 | 2026-11-23 |
| C-09-008 | bit 하나가 task 하나를 죽일 수 있다 | koopman-toyota-ua, 29-31쪽 | 1차 (원고 쪽 전문가의 발표 자료) | 2026-11-23 |
| C-06-012 | 보고서의 요구사항은 예시이고 NHTSA의 공식 입장이 아니다 | nhtsa-etc-ev-fsa, 17쪽 (직접 읽음) | 1차 | 2026-11-23 |
| C-06-013 | 안전 전략 (센서의 중복 등)은 hazard 분석과 safety analysis 단계에서 고려하지 않는다. 설계 전략이 정해지면 분석을 더 한다 | nhtsa-etc-ev-fsa, 30쪽 (직접 읽음) | 1차 | 2026-11-23 |
| C-06-014 | 경계 밖의 시스템은 속을 모르는 상자로 보고 옳게 동작한다고 가정한다. 운전자의 입력은 옳다고 가정한다 | nhtsa-etc-ev-fsa, 29쪽, 31쪽 (직접 읽음) | 1차 | 2026-11-23 |
| C-06-015 | hazard의 기준 셋 (시스템의 상태, 가장 나쁜 환경에서 손실, 막아야 할 상태). hazard와 원인을 섞는 실수. 해결책을 미리 적지 않는다 | stpa-handbook, 17-21쪽 (18-19쪽은 직접 읽음) | 1차 | 2026-11-23 |
| C-06-016 | HAZOP: guide word 일곱, 기능 19, 벗어남 132, 운전 모드 넷. STPA: 손실 둘 (충돌, 감전), control action 13, 위험한 경우 95. 두 방법의 결과가 비슷해 하나로 합쳤다 | nhtsa-etc-ev-fsa, 37쪽, 39-41쪽, 44쪽, 50쪽 (직접 읽음) | 1차 | 2026-11-23 |
| C-06-017 | brainstorming, checklist, 지난 기록에 기대는 방법은 과거의 경험에 달려 있어 역사가 짧은 기술에서 hazard를 놓칠 수 있다 | nhtsa-safety-standards-assessment, 23쪽 (직접 읽음) | 1차 (보고서의 의견) | 2026-11-23 |
| C-06-018 | 운전 상황 69개, 그 가운데 66개는 변수 10개의 조합. 전문가의 목록을 모든 조합과 견주자 상황이 더 나왔다 | nhtsa-etc-ev-fsa, 52-53쪽, 101쪽 (직접 읽음) | 1차 | 2026-11-23 |
| C-06-019 | S, E, C 등급의 이름. E4는 차를 쓰는 시간의 10%를 넘음, E2는 1%쯤, S3은 승객실이 변형될 만한 충돌 | nhtsa-etc-ev-fsa, 54-56쪽 (직접 읽음) | 2차 (ISO 26262 FDIS 2011) | 2026-11-23 |
| C-06-020 | hazard마다 가장 나쁜 운전 상황의 S, E, C. 의도하지 않은 가속과 구동력 상실의 표는 둘로 나뉘고 D는 차의 안정이 흔들리는 경우의 표에만 있다 | nhtsa-etc-ev-fsa, 57쪽, 183쪽, 186쪽, 189쪽, 192쪽, 201쪽, 210쪽, 215쪽 (직접 읽음) | 2차 (ISO 26262 FDIS 2011) | 2026-11-23 |
| C-06-021 | 규격은 평균적인 운전자의 능력으로 controllability를 평가하게 하지만 그 능력을 정의하지 않는다 | nhtsa-etc-ev-fsa, 102쪽 (직접 읽음) | 2차 (ISO 26262 FDIS 2011) | 2026-11-23 |
| C-06-022 | 사람은 드문 일의 확률을 잘 어림하지 못한다. ACC의 예 (S3, E2, C0이나 C1에서 QM). 확률이 불확실하면 가장 보수적인 평가는 severity만 쓰는 것 | nhtsa-safety-standards-assessment, 27-28쪽 (직접 읽음) | 1차 (보고서의 의견). 표의 값은 2차 (ISO 26262:2011) | 2026-11-23 |
| C-06-023 | 위험 평가가 쓰는 값의 비교 (ISO 26262, MIL-STD-882E, DO-178C). MIL-STD-882E와 DO-178C는 소프트웨어에 확률을 쓰지 않는다 | nhtsa-safety-standards-assessment, 26쪽, 29쪽 (직접 읽음) | 2차 (MIL-STD-882E, DO-178C) | 2026-11-23 |
| C-06-024 | 기계의 risk graph: 부상의 크기, 드러나는 빈도 (15분에 한 번), 피할 수 있는가. 안전 기능이 주는 위험 감소를 빼고 평가한다 | ifa-report-2-2017e, 20쪽, 32-33쪽 (33쪽은 직접 읽음) | 2차 (EN ISO 13849-1:2015) | 2026-11-23 |
| C-06-025 | safety goal의 꼴: 크기와 시간이 함께 있는 것은 하나이고 값은 모두 정하지 않았다. safe state의 세 종류와 일곱 예, hazard와의 차이 둘 | nhtsa-etc-ev-fsa, 58쪽, 67-68쪽 (직접 읽음) | 1차. safe state의 세 종류는 2차 (ISO 26262 FDIS 2011) | 2026-11-23 |
| C-06-026 | creep을 제어하지 못하는 고장은 그보다 빠른 속도에서의 고장보다 FTTI가 길 수 있다 | nhtsa-etc-ev-fsa, 80쪽 (직접 읽음) | 1차 | 2026-11-23 |
| C-EX-020 | 예제의 HARA: hazard 다섯의 등급 표, H-04의 운전 상황 다섯 줄, safety goal 둘, safe state 넷. SG-02는 보고서의 꼴 (감속의 크기와 시간)에 구동력을 잃은 상태가 경고 없이 1 s 넘게 이어지지 않는다는 구절 (값은 가정)을 더한 것이고, 그 논증은 닫히지 않는다 | example/drive-torque/docs/hara.md. 값은 nhtsa-etc-ev-fsa의 부록 F에서 빌린 가정 | 예제 | 2026-11-23 |
| C-07-009 | functional safety concept이 다루는 다섯 가지. 요구사항을 끌어내는 틀. 요구사항은 뒤의 단계에서 더 자세한 요구사항으로 내려간다 | nhtsa-etc-ev-fsa, 66쪽, 70-71쪽 (66, 71쪽은 직접 읽음) | 2차 (ISO 26262 FDIS 2011) | 2026-11-23 |
| C-07-010 | 고장과 safe state와 경고의 짝: 중복 요소 하나의 고장은 올리는 속도를 늦춘 상태와 주의 표시, 둘 다이거나 하나뿐인 요소의 고장은 낮은 속도로만 가는 상태와 경고 표시. 성능을 낮춘 상태에 들어가면 운전자에게 알린다 | nhtsa-etc-ev-fsa, 68쪽, 73-74쪽 (68, 74쪽은 직접 읽음) | 1차 | 2026-11-23 |
| C-07-011 | 소프트웨어의 safety requirement는 위에서 내려오거나 hazard 분석에서 올라온다. 올라온 것은 시스템의 명세로 먼저 올린 뒤 다시 내린다. generic과 specific의 구분 | nasa-gb-8719-13, 105쪽, 114쪽, 121쪽 (직접 읽음) | 1차 | 2026-11-23 |
| C-07-012 | must work와 must not work 기능. 앞의 것은 독립된 병렬 중복, 뒤의 것은 독립된 직렬의 막음으로 지키고, 직렬의 막음은 대개 다른 processor가 맡아야 독립이다 | nasa-gb-8719-13, 141-142쪽, 348쪽 (직접 읽음) | 1차 | 2026-11-23 |
| C-07-013 | safety strategy의 항목: 주 제어기가 멀쩡한지를 다른 processor로 확인한다 | nhtsa-etc-ev-fsa, 67쪽 (직접 읽음) | 1차 | 2026-11-23 |
| C-07-014 | 알아채는 시간과 FTTI를 따로 적는다. FTTI는 업계의 자료로 정하고 없으면 기술이 허락하는 만큼 빨리. 숫자는 200 ms 두 군데뿐이고 근거가 없다. FTTI를 정의하는 문장은 없다 | nhtsa-etc-ev-fsa, 11쪽, 71-72쪽, 80-81쪽 (71, 80쪽은 직접 읽음) | 1차 | 2026-11-23 |
| C-07-015 | time to criticality. 자동으로 대응하는 수단은 가장 긴 대응 시간과 가장 짧은 그 시간 사이에 여유가 충분할 때만 쓸모가 있다 | nasa-gb-8719-13, 117쪽 (직접 읽음) | 1차 | 2026-11-23 |
| C-07-016 | safe state를 고를 때 쓸 수 있는 정도를 가장 크게 하려 한다. 고장을 알아채면 멈추는 것이 언제나 가장 안전하다는 것은 잘못이다. 보호 수단이 새 hazard를 만들지 않는지, 서로 맞는지를 묻는다 | nhtsa-etc-ev-fsa, 67쪽. nasa-gb-8719-13, 22쪽. ifa-report-2-2017e, 27쪽 (모두 직접 읽음) | 1차. ifa는 2차 (EN ISO 12100) | 2026-11-23 |
| C-07-017 | 안전 기능을 정할 때 적을 것: 전원이 있을 때와 끊겼을 때, 고장을 알아챘을 때의 반응, 반응 시간. hardware-software interface의 명세에 ISO 26262가 요구하는 것은 받은 문서에 없다 | ifa-report-2-2017e, 30쪽 (직접 읽음). 없음은 notes/reading/ch07-facts.md의 찾지 못한 것 | 2차 (EN ISO 13849-1:2015) | 2026-11-23 |
| C-07-018 | 요구사항 하나에 등급이 둘 넘게 붙을 수 있다. 독립을 보일 수 없으면 높은 쪽을 따른다. 소프트웨어의 중복이 정말 독립인지는 설계의 처음에 확인하기 매우 어렵다 | nhtsa-etc-ev-fsa, 73쪽, 79-80쪽 (73쪽은 직접 읽음). nhtsa-safety-standards-assessment, 29쪽 (직접 읽음) | 2차 (ISO 26262 FDIS 2011). 뒤의 것은 1차 (보고서의 의견) | 2026-11-23 |
| C-EX-021 | 예제의 요구사항 62개 (safety goal 2, FSR 16, TSR 19, SWR 25) 가운데 30개가 구현 예정. 감시의 틈을 세 번 고친 경위. 오차의 예산 셋. 고장 대응의 상태 넷 | example/drive-torque/docs/requirements.yaml, technical-safety-concept.md 3절과 9절, functional-safety-concept.md 4절. make trace의 출력 | 예제 (이 책의 측정과 증명) | 2026-11-23 |
| C-06-027 | ACC의 예에 붙은 말: 규격은 가장 나쁜 운전 상황의 등급을 hazard에 주게 하므로 최종 등급은 QM보다 나쁠 수 있다. 그래도 exposure와 controllability가 등급을 낮추는 길이 된다 | nhtsa-safety-standards-assessment, 28쪽 (직접 읽음) | 1차 (보고서의 의견) | 2026-11-23 |
| C-06-028 | safe state와 hazard의 차이: safe state로 들어갈 때의 변화는 제어되어 있고, hazard의 변화는 매끄럽지도 한결같지도 않을 수 있다. 운전자가 통보받는다 | nhtsa-etc-ev-fsa, 68쪽 (직접 읽음) | 1차 | 2026-11-23 |
| C-09-009 | lockstep: 두 core가 같은 소프트웨어를 나란히 실행하고 같은 입력에서 나온 출력을 견준다 | easa-amc-20-193, 2쪽 (직접 읽음). faa-ac-20-193, 3쪽은 낱말만 | 1차 (항공의 지침. 자동차용 MCU에 대한 것이 아니다) | 2026-11-23 |
| C-EX-022 | 증명한 성질 7: 기능이 어떻게 틀려도 나가는 토크가 정상인 기능의 요구를 5 Nm 넘게 앞서지 않는다. 변이 58개. 검토자의 변이 21개 가운데 7개를 놓쳤고 (동등 3, 진짜 4), test를 더해 잡았다 | example/drive-torque/test/proof/harness.c, make check와 make mutation의 출력, reviews/2026-11-23-stage2-part2/round1-embedded.md의 E-06 | 예제 (이 책의 증명과 측정) | 2026-11-23 |
| C-10-003 | 모자란 요구사항이 소프트웨어 프로젝트 실패의 가장 큰 단일 원인이고 대개 가장 나쁜 결함의 뿌리다 | nasa-gb-8719-13, 109쪽 | 1차 | 2026-11-23 |
| C-10-004 | "빠짐없다"는 앞으로의 요구를 다 알 수 없지만 알려진 것은 모두 적는다는 뜻이다. 검증 방법은 대개 test, analysis, inspection, demonstration이다. 바깥의 동작이면 자세해도 되고 부품이나 algorithm을 정하면 설계 정보다 | nasa-gb-8719-13, 111쪽 | 1차 | 2026-11-23 |
| C-10-005 | demonstration은 소프트웨어를 그저 돌려 보는 것이고, 검증 방법은 요구사항 문서나 문서 끝의 verification matrix에 적는다 | nasa-gb-8719-13, 112쪽 | 1차 | 2026-11-23 |
| C-10-006 | 보고서의 요구사항은 한 항에 조건, FTTI, safe state, 경고를 함께 담는다 (9.2.1-4, 9.2.1-5, 9.2.3-22) | nhtsa-etc-ev-fsa, 74쪽, 80쪽 | 1차 | 2026-11-23 |
| C-10-007 | 안전에 중요한 특성은 요구사항에 드러나게 넣어야 하고 잊힌 안전 요구사항은 뒤에서 돌아온다. 요구사항에서 찾을 조건의 목록 (순서, 틀린 사건, 크기, 극성, 의도하지 않은 명령, 명령의 실패 등). 한계는 mode에 따라 다를 수 있다 | nasa-gb-8719-13, 123쪽 | 1차 | 2026-11-23 |
| C-10-008 | startup 상태에서 모든 내부 변수를 알려진 값으로 둔다 | nasa-gb-8719-13, 338쪽 | 1차 | 2026-11-23 |
| C-10-009 | 모든 상태는 모든 입력에 대해 정의된 전이를 가진다. 입력이 정한 시간 안에 없으면 time-out 같은 전이를 둔다. 범위 검사는 첫 방어선이다 | nasa-gb-8719-13, 340-341쪽 | 1차 | 2026-11-23 |
| C-10-010 | 두 lane의 문턱 문제. 모든 실시간 data는 시간의 상한과 하한을 가진다. 제어 결정은 묵은 data가 아니라 현재 상태의 data로 한다 | nasa-gb-8719-13, 342쪽 | 1차 | 2026-11-23 |
| C-10-011 | degraded mode에서 정상으로 돌아오는 조건을 명세하고, 계속 오가지 않을 만큼 구체적이어야 한다 | nasa-gb-8719-13, 343쪽 | 1차 | 2026-11-23 |
| C-10-012 | 명령에 대한 반응이 너무 느리거나 빠르거나 예상 밖인 것을 찾는 장치가 필요하다. 컴퓨터 제어 시스템은 failure 없이 hazard 상태로 가지 않는다 | nasa-gb-8719-13, 344쪽 | 1차 | 2026-11-23 |
| C-10-013 | time to criticality의 뜻과, 가장 긴 응답 시간과 가장 짧은 time to criticality 사이에 넉넉한 여유가 있어야 자동 safing이 유효하다는 것 | nasa-gb-8719-13, 117쪽 | 1차 | 2026-11-23 |
| C-10-014 | 충돌이나 HVIL 고장 뒤 연 contactor는 고전압 시스템이 온전한지 확인될 때까지 열어 둔다 (9.2.7-5) | nhtsa-etc-ev-fsa, 89쪽 | 1차 | 2026-11-23 |
| C-10-015 | unsafe control action의 정의와 네 유형. context를 반드시 적는다. 늘 위험한 명령이면 설계에 넣지 않았을 것이다. hazard로의 추적을 괄호로 적는다 | stpa-handbook, 35-36쪽 | 1차 | 2026-11-23 |
| C-10-016 | unsafe control action을 뒤집어 controller constraint를 얻는다 (C-3 "within TBD seconds after touchdown [UCA-3]"). context는 믿음이 아니라 실제 상태로 적는다 | stpa-handbook, 41쪽 | 1차 | 2026-11-23 |
| C-10-017 | 요구사항 202개 가운데 112개는 Part 3 (concept phase)의 방법으로, 90개는 STPA와 MIL-STD-882E로 얻었고, Part 4, 5, 6이 이것을 개발 단계의 요구사항으로 내린다. 예시이고 NHTSA의 공식 입장이 아니다 | nhtsa-etc-ev-fsa, 70쪽 (각주 23) | 1차 (Part 번호는 보고서가 ISO 26262를 인용한 것) | 2026-11-23 |
| C-10-018 | 9장 (70-100쪽)에서 값의 자리는 TBD이고 숫자가 나오는 곳은 200 ms를 업계 관행으로 드는 두 곳뿐이다 | nhtsa-etc-ev-fsa, 70-100쪽 (pdftotext로 TBD 35줄, 단위가 붙은 숫자 2곳을 셈), 80-81쪽 | 1차 | 2026-11-23 |
| C-10-019 | 신청자들이 시험 비행 지침을 조종사가 4초 안에 대응한다는 설계 가정으로 썼고, 그 지침을 뒷받침하는 연구를 찾지 못했다 (O2.8-C, O2.8-D) | b737max-jatr, 34쪽 | 1차 | 2026-11-23 |
| C-10-020 | 모든 요구사항이 추적되지는 않고 가정이 요구사항과 따로 관리된다 (O8.1-A b) | b737max-jatr, 57쪽 | 1차 | 2026-11-23 |
| C-10-021 | 가정을 coordination sheet에 적어 시스템 수준 요구사항에서 보이지 않았고, 가정이 계속 유효한지 확인하는 feedback loop가 분명하지 않았다 (O8.4-A) | b737max-jatr, 59쪽 | 1차 | 2026-11-23 |
| C-10-022 | 변수 일곱 가운데 넷만 보호했고, 나머지 셋은 물리적 제한이나 여유를 이유로 보호하지 않았으며 BH에서 그 추론이 틀렸다. 근거가 코드에 없었다. 궤적 data를 SRI의 요구사항과 명세에 넣지 않기로 합의했다 | ariane-501-report, 9쪽 (OCR) | 1차 | 2026-11-23 |
| C-10-023 | 권고 R5: 코드와 근거 문서가 장비가 주는 값에 대해 한 암묵적 가정을 모두 찾아 장비의 사용 제한과 견준다 | ariane-501-report, 17쪽 (OCR) | 1차 | 2026-11-23 |
| C-10-024 | 추적이 있어야 요구사항 test coverage를 온전히 얻고 여분의 동작이 없는지 확인할 수 있다. 손으로 만든 추적표는 유지하기 어렵다 | nasa-gb-8719-13, 112-113쪽 | 1차 | 2026-11-23 |
| C-10-025 | requirements criticality analysis로 안전에 닿는 요구사항을 safety-critical로 지정하고 추적 체계에 넣는다 | nasa-gb-8719-13, 122쪽 | 1차 | 2026-11-23 |
| C-11-006 | 가장 엄격하게 결함을 줄여도 모든 fault를 막지 못하므로 어느 정도의 failure tolerance가 보통 필요하다 | nasa-gb-8719-13, 141쪽 | 1차 | 2026-11-23 |
| C-11-007 | 한 FCR은 자기의 failure mode를 모두 스스로 감시할 수 없고, 구역 안의 failsafe가 그것이 찾는 fault로 망가질 수 있다. 각 FCR은 다른 FCR을 감시할 수 있지만 자기는 모든 경우에 감시하지 못한다. 공유 자원은 위험한 single point of failure이고 자체 시험만으로는 충분하지 않다. 완전한 보호에는 입력 값의 독립 관찰이 필요하다 | koopman-toyota-ua, 31-32쪽 | 1차 (전문가의 발표 자료) | 2026-11-23 |
| C-11-008 | redundant 요소는 common cause failure에 대해 검증하며, 한 요소의 전원과 통신 경로의 고장이 다른 요소의 것에 영향을 주지 않아야 한다 (보고서의 예시 요구사항) | nhtsa-etc-ev-fsa, 74쪽 | 1차 | 2026-11-23 |
| C-11-009 | ETCS-i: 두 CPU가 모두 동의해야 throttle을 열 수 있고, 센서와 CPU는 여는 쪽으로 직렬이다. 닫는 쪽으로는 redundant이고 여는 쪽으로는 아니다. CPU마다 자기 oscillator, memory 오류 검출과 정정, watchdog을 가진다 | nasa-toyota-ua-report, 67쪽 | 1차 | 2026-11-23 |
| C-11-010 | Sub-CPU는 같은 논리를 돌려 Main CPU와 견주지 않고, Main CPU와 throttle motor의 성능에 관한 진단을 한다 | nasa-toyota-ua-report, 56쪽 | 1차 | 2026-11-23 |
| C-11-011 | H-Bridge는 두 CPU 모두의 입력이 있어야 motor에 전원을 주고, CPU reset 중에는 출력이 low로 당겨져 motor 구동이 꺼진다. Sub-CPU는 H-Bridge의 독립 hardware enable을 준다 | nasa-toyota-ua-report, 144쪽 | 1차 | 2026-11-23 |
| C-11-012 | Main CPU의 heartbeat는 전원 ASIC과 Sub-CPU로, Sub-CPU의 watchdog 신호는 Main CPU로 간다. Main CPU는 Sub-CPU를, 전원 ASIC은 두 CPU를 reset할 수 있다 | nasa-toyota-ua-report, 145쪽 (그림으로 읽음), 146쪽 | 1차 | 2026-11-23 |
| C-11-013 | 두 CPU 사이의 직렬 data 전송에는 data 검사도 재시도도 없다 | nasa-toyota-ua-report, 146쪽 | 1차 | 2026-11-23 |
| C-11-014 | NASA: watchdog을 다시 거는 함수는 가장 낮은 우선순위의 task에서 실행된다. Koopman: watchdog은 하드웨어 timer 서비스 routine에서 kick되고 주요 task의 죽음을 감지하지 못한다 (두 서술을 나란히 적고 판정하지 않는다) | nasa-toyota-ua-report, 146쪽. koopman-toyota-ua, 45쪽 | 1차 (Koopman은 전문가의 주장) | 2026-11-23 |
| C-11-015 | high-assurance kernel은 주 소프트웨어와 기능이 같거나 범위가 더 좁을 수 있고 거의 틀림없이 덜 최적화된다 | nasa-gb-8719-13, 144쪽 | 1차 | 2026-11-23 |
| C-11-016 | N-version은 복잡도를 높이고 복잡도는 오류 수와 직접 관계가 있다. 한 실험 항공기 연구에서 시험 중 찾은 소프트웨어 문제는 모두 redundancy management system에서 나왔고 제어 소프트웨어는 흠 없이 동작했다 | nasa-gb-8719-13, 143-144쪽 | 1차 | 2026-11-23 |
| C-11-017 | majority voting: 3 중 2는 고장 하나, 5 중 3은 고장 둘을 견디고 홀수 개가 필요하다. 직렬 inhibit이 독립이려면 대개 서로 다른 소프트웨어를 실은 서로 다른 processor가 제어해야 한다 | nasa-gb-8719-13, 142쪽 | 1차 | 2026-11-23 |
| C-11-018 | NSTS 1700.7B에 따르면 같은 운영체제를 도는 두 processor는 서로 독립도 아니고 서로의 failure를 견디지도 못한다 | nasa-gb-8719-13, 143쪽 | 1차 | 2026-11-23 |
| C-11-019 | FCR은 하드웨어로 나누는 것이 가장 좋다. 논리적 firewall은 NASA 안에서 hazard mitigation으로 볼 뿐 hazard control로 보지 않는다. 하드웨어 고장이나 EMI/방사선이 무너뜨릴 수 있기 때문이다. 같은 processor 위의 FCR은 별도 memory chip, 같은 CPU에서 동시에 multitasking하지 않는 경우 같은 좁은 조건에서만 받아들여진다 | nasa-gb-8719-13, 144쪽 | 1차 | 2026-11-23 |
| C-11-020 | ASIL이 다른 부품: 전체를 가장 높은 ASIL로 하거나 freedom from interference를 보장한다. 방해의 묶음은 memory, timing, execution, exchange of information. 안전 수단 자체가 안전 관련이다 | autosar-safety-measures, 9쪽 | 2차 (ISO 26262:2018, 72쪽) | 2026-11-23 |
| C-11-021 | 같은 OS-Application 안에서는 memory partitioning이 방해를 막지 못한다. ASIL이 다른 부품을 같은 OS-Application에 두지 않는 편이 좋다 | autosar-safety-measures, 15쪽 | 1차 | 2026-11-23 |
| C-11-022 | memory partitioning은 MPU 같은 하드웨어를 가정하고, core 안의 MPU는 DMA나 다른 core를 제어하지 못한다. trusted OS-Application에 적용되지 않고 task 수준은 필수가 아니다 | autosar-safety-measures, 18쪽, 20-21쪽 | 1차 | 2026-11-23 |
| C-11-023 | OS의 timing 보호 셋 (execution budget, lock budget, time frame)과, 실행 시간의 강제에 하드웨어 지원이 필요하다는 것 | autosar-safety-measures, 26쪽 | 1차 | 2026-11-23 |
| C-11-024 | AUTOSAR가 하지 않는 것의 목록에 dependent failure analysis가 있다 | autosar-safety-measures, 46쪽 | 1차 | 2026-11-23 |
| C-11-025 | AUTOSAR 문서가 인용하는 ISO 26262-6 항목: 7.4.8 Coexistence, 7.4.9 Partitioning, 7.4.11 Dependent failure analysis, Annex D | autosar-safety-measures, 9쪽, 14쪽, 21쪽 | 2차 (ISO 26262:2018, 72쪽) | 2026-11-23 |
| C-11-026 | E-Gas는 AKEGAS가 표준화했고 AUTOSAR의 일부가 아니다. 감시 SW는 입출력에 직접 닿는 CDD에 둔다. 그림 3.6은 응용과 감시 SW를 한 MC 안에 그린다. 감시 SW는 SPI의 우선 접근, ADC 시험, 차단 경로 actuator의 직접 시험, ADC/DIO/PWM의 raw 값 접근이 되어야 한다 | autosar-safety-measures, 60-64쪽 (61쪽은 그림으로 읽음) | 1차 | 2026-11-23 |
| C-11-027 | 분할하는 소프트웨어는 분할 대상 가운데 가장 높은 IDAL 이상이어야 한다 | faa-ac-20-193, 5쪽 | 1차 | 2026-11-23 |
| C-11-028 | MCP의 방해는 비공개 내부 기구를 통해 일어나므로 그 simulation은 목표 MCP의 시험보다 대표성이 낮고 오류를 찾을 가능성도 낮다 | faa-ac-20-193, 10쪽 | 1차 | 2026-11-23 |
| C-11-029 | simulation으로 실패 시나리오를 시험해 볼 수 있지만 시험한 것은 simulation이고 실제 소프트웨어의 동작은 다를 수 있다 | nasa-gb-8719-13, 158쪽 | 1차 | 2026-11-23 |
| C-11-030 | 안전 소프트웨어와 같은 물리적 platform의 소프트웨어는 충분히 분할되지 않는 한 안전 소프트웨어로 본다 | nasa-gb-8719-13, 20쪽 | 1차 | 2026-11-23 |
| C-11-031 | 설계 단계에서 안전 부품에 영향을 줄 수 있는 부품은 그 자신이 안전 부품이 된다. independence analysis는 전역/공유 변수와 직접 넘기는 인자를 살핀다 | nasa-gb-8719-13, 157-158쪽 | 1차 | 2026-11-23 |
| C-11-032 | 예제의 구조, 규칙, task 넷, `monitor_output_cycle`로 묶은 일, `FI-23`과 `FI-26`의 결과, `A-10`과 `A-19`, `HA-01`, 구현하지 않은 `SWR-22`와 `SWR-23` | example/drive-torque/docs/architecture.md, dfa.md, hardware-assumptions.md, technical-safety-concept.md (4, 7, 9절), test-report.md (3, 5, 6, 8절), src/vcu/vcu.c, src/app/app.c, src/monitor/monitor.h, src/reaction/reaction.h | 예제 | 2026-11-23 |
| C-14-001 | OS와 language library처럼 널리 알려져 오류가 없다고 여겨지는 소프트웨어도 안전 시스템에서는 오류가 없다고 가정하지 않는다 | nasa-gb-8719-13, 273쪽 | 1차 | 2026-11-23 |
| C-14-002 | OS의 종류에 OS가 없는 것 (boot loader가 application을 직접 올림)과 개발자가 쓴 단순한 task scheduler가 있다 | nasa-gb-8719-13, 241쪽 | 1차 | 2026-11-23 |
| C-14-003 | RTOS의 조건에 priority inheritance가 있고, interrupt 지연, system call의 최대 시간, OS와 driver가 interrupt를 막는 최대 시간을 알아야 한다. priority inversion은 높은 task가 자원을 쥔 낮은 task에 막히고 중간 task가 돌아 낮은 task가 자원을 놓지 못하는 문제다 | nasa-gb-8719-13, 242-243쪽 | 1차 | 2026-11-23 |
| C-14-004 | 고정 우선순위 선점 OS에서 마감을 지키는지는 실행 시간, 낮은 task의 자원 잠금과 interrupt 막음으로 인한 blocking time, 활성화 간격이 정한다. AUTOSAR OS는 timing 보호로 deadline supervision을 주지 않는다 (원인 task를 가려낼 수 없어서) | autosar-safety-measures, 25쪽 (CP R25-11) | 1차 | 2026-11-23 |
| C-14-005 | memory partitioning은 OS-Application 단위로 memory를 나눠 한 partition의 코드가 다른 partition의 memory를 바꾸지 못하게 한다. MPU나 MMU를 OS가 알맞게 설정해야 하고, 위반은 하드웨어가 막고 exception을 올린다 | autosar-safety-measures, 13쪽, 20쪽 | 1차 | 2026-11-23 |
| C-14-006 | timing 보호는 Execution Budget, Lock Budget, Time Frame의 셋이고, 실행 시간 강제에는 하드웨어 지원 (예: timing enforcement interrupt)이 필요하다. Category 1 interrupt는 OS 밖에서 실행되어 감시할 수 없다 | autosar-safety-measures, 26쪽 | 1차 | 2026-11-23 |
| C-14-007 | memory partitioning은 trusted OS-Application에 적용되지 않는다. trusted는 감시와 보호를 끄고 privileged mode로 돌 수 있다. 구현 예에서 basic software 전부가 trusted/supervisor partition에 있다 | autosar-safety-measures, 13쪽, 17쪽, 20쪽 | 1차 | 2026-11-23 |
| C-14-008 | 등급이 다른 SW-C를 같은 OS-Application에 넣지 말라고 권하고, 같은 OS-Application 안은 보호하지 않는다. task 수준 partition은 OS 규격이 "may"로 적어 선택 사항이다 | autosar-safety-measures, 15-16쪽, 20-21쪽 | 1차 | 2026-11-23 |
| C-14-009 | MPU가 core 안에 있는 구현에서는 그 core의 접근만 통제하고 DMA와 다른 core는 통제하지 않는다 | autosar-safety-measures, 18쪽 | 1차 | 2026-11-23 |
| C-14-010 | AUTOSAR의 안전 mechanism은 안전에 관련되므로 그에 맞게 개발하고 통합해야 한다 | autosar-safety-measures, 9쪽 | 1차 | 2026-11-23 |
| C-14-011 | partitioning을 제공하는 소프트웨어는 나누는 소프트웨어 가운데 가장 높은 IDAL 이상이어야 한다 | faa-ac-20-193, 5쪽 | 1차 | 2026-11-23 |
| C-14-012 | NSTS 1700.7B에 따르면 같은 OS를 돌리는 두 processor는 N-version programming을 해도 독립도 고장 허용도 아니다 | nasa-gb-8719-13, 143쪽 | 1차 | 2026-11-23 |
| C-14-013 | 여러 core의 application이 공유 자원 (memory, cache, interconnect, 외부 interface)에 동시에 접근해 경쟁이 생기고, 중재 지연이 시간 간섭이 되어 혼자 돌 때보다 훨씬 오래 걸릴 수 있다. 안전 관련 application이 비결정적으로 동작하거나 시간이 모자랄 수 있다 | faa-ac-20-193, 3쪽 | 1차 | 2026-11-23 |
| C-14-014 | interference channel은 간섭을 일으킬 수 있는 플랫폼의 성질이고, MCP platform에는 OS나 hypervisor 같은 platform software가 든다 | faa-ac-20-193, 4쪽 | 1차 | 2026-11-23 |
| C-14-015 | 공유 cache, 공유 memory (lockout, race condition, data starvation, deadlock, live-lock, 지나친 data 지연), interconnect의 중재, 하드웨어 동적 기능 (주파수 조정, core 비활성화), MCP 설정 항목 | faa-ac-20-193, 7-8쪽 | 1차 | 2026-11-23 |
| C-14-016 | interconnect의 중재가 jitter, data 일관성 문제, transaction 순서 변경을 낳고 과부하될 수 있다. 공유 peripheral을 포함한 interference channel을 식별하고 완화를 검증한다. 자원 요구가 가용 자원을 넘지 않음을 검증한다 | faa-ac-20-193, 9-10쪽 | 1차 | 2026-11-23 |
| C-14-017 | WCET는 다른 core의 소프트웨어 때문에 크게 늘 수 있다. 시간 간섭 완화를 보이지 못하면 분석으로 정하고 최종 구성의 대상 MCP에서 시험으로 확인한다. MCP 내부 mechanism의 simulation은 대표성이 낮다 | faa-ac-20-193, 10-11쪽 | 1차 | 2026-11-23 |
| C-14-018 | 소프트웨어는 시작 때 core에 정적으로 배치되고 운용 중 옮기지 않는다고 가정하며, OS나 hypervisor가 동적으로 재배치하는 플랫폼은 다루지 않는다 | faa-ac-20-193, 2쪽. easa-amc-20-193, 1-2쪽 | 1차 | 2026-11-23 |
| C-14-019 | lockstep의 풀이 (같은 소프트웨어를 나란히 실행해 같은 입력의 출력을 견줌)와, lockstep core 사이에는 이 지침의 목표를 적용하지 않는다는 예외 | easa-amc-20-193, 2쪽. faa-ac-20-193, 3쪽 | 1차 | 2026-11-23 |
| C-14-020 | MCP에 의도하지 않은 기능이 있을 수 있으므로 MCP와 독립인 safety net으로 MCP 안의 고장을 찾아 장비 안에 가두는 것을 고려한다. safety net은 오동작의 원인과 독립이다 | faa-ac-20-193, 12쪽, 5쪽 | 1차 | 2026-11-23 |
| C-14-021 | watchdog을 interrupt에서 두드리지 않는다. 실제 process가 모두 막혀도 interrupt는 돌 수 있다. stack을 알려진 pattern으로 초기화하고 남은 공간을 감시한다 | nasa-gb-8719-13, 94쪽 | 1차 | 2026-11-23 |
| C-14-022 | FAA AC 20-193은 2024-01-08, 법적 구속력이 없는 acceptable means of compliance다. EASA AMC 20-193은 ED Decision 2022/001/R의 Annex I이고 따르는 것이 의무가 아니다 | faa-ac-20-193, 1쪽. easa-amc-20-193, 1쪽 | 1차 | 2026-11-23 |
| C-14-023 | AUTOSAR 문서는 ISO 26262-6의 Annex D (Freedom from interference between software elements)를 든다. 문서는 ISO 26262:2018을 참조한다 | autosar-safety-measures, 9쪽, 참고문헌 (ISO 26262:2018) | 2차 (ISO 26262:2018) | 2026-11-23 |
| C-EX (14장) | 예제의 정적 task table (task 넷, 10 ms), sim의 시간 모델 (실행 시간 0), `FI-23` - `FI-25`와 `NC-005`의 결과와 시간, `HA-01`, `HA-03`, `HA-04`, `HA-06`, `HA-14`, `A-19`, `A-24`, `A-25`의 내용, 출력 순서를 세게 한 일 | `example/drive-torque/src/vcu/vcu.c`, `sim/scenario.h`, `sim/scenario.c`, `sim/hal_sim.c`, `docs/test-report.md` 3절, 6절, 8절, `docs/hardware-assumptions.md`, `docs/technical-safety-concept.md` 4절, 9.4절, 9.5절 | 예제 | 2026-11-23 |
| C-E-004 | 페달 위치 센서는 각도를 전압으로 바꾸어 제어기에 보내며, 신호는 직결선이나 차량 bus (예: CAN)로 간다. 제어기는 전압을 토크로 바꾸고 다른 계통의 토크 요구와 조정한다 | nhtsa-etc-ev-fsa, 33쪽 | 1차 | 2026-11-23 |
| C-E-005 | inverter 제어부, gate drive, inverter/converter, 상 전류 센서와 모터 위치 센서의 역할 | nhtsa-etc-ev-fsa, 33-34쪽 | 1차 | 2026-11-23 |
| C-E-006 | 블록 그림: 제동/안정성 제어기가 브레이크 페달 위치와 차량 속도를, 다른 차량 센서가 선택된 기어를 EV PCM에 준다. EV PCM에서 gate drive board로 "Disable Motor (Traction Controller Bypass)" 선이 있다 | nhtsa-etc-ev-fsa, 32쪽 (그림 5. 쪽을 그림으로 그려 눈으로 읽었다) | 1차 | 2026-11-23 |
| C-E-007 | 차량 속도는 제동/안정성 제어 모듈이 준다고 보고서가 가정한다 | nhtsa-etc-ev-fsa, 29쪽 | 1차 | 2026-11-23 |
| C-E-008 | 기어 선택기의 위치를 transmission range sensor가 알린다 | nhtsa-etc-ev-fsa, 33쪽 | 1차 | 2026-11-23 |
| C-E-009 | 보고서의 브레이크 입력은 페달의 각도를 재는 센서 (BPPS)다 | nhtsa-etc-ev-fsa, 35쪽 | 1차 | 2026-11-23 |
| C-E-010 | 제어기는 고장을 찾으면 DTC를 기록하고 limp-home 같은 safe state로 보낼 수 있으며 계기판의 고장 표시등을 켜라고 명령한다. inverter 제어부가 고장이면 그것을 건너뛰고 gate drive와 직접 통신해 전류를 끊을 수 있다 | nhtsa-etc-ev-fsa, 35쪽. nhtsa-etc-gasoline-fsa, 34쪽 | 1차 | 2026-11-23 |
| C-E-011 | 전기차와 내연기관 차의 차이: 방향은 전류가 정하고 구동 계통이 방향을 맡는다, 페달을 놓으면 coast한다, creep은 소프트웨어로 흉내 낸다, 모터는 속도 0에서 stall하지 않지만 EPS가 갑자기 꺼지면 비슷한 상태가 된다 | nhtsa-etc-ev-fsa, 30-31쪽 | 1차 | 2026-11-23 |
| C-E-012 | 가솔린차는 흡입 공기량으로 출력을 조절하고, ECM이 PWM으로 throttle 모터를 구동한다 | nhtsa-etc-gasoline-fsa, 31쪽, 33쪽 | 1차 | 2026-11-23 |
| C-E-013 | 고장 표시등 같은 운전자 알림은 보고서의 범위 밖이다. 범위에는 차량 bus (예: CAN)의 통신이 든다 | nhtsa-etc-ev-fsa, 27-28쪽 | 1차 | 2026-11-23 |
| C-E-014 | 업계에서 흔한 경고의 예: amber (어길 확률 중간), red (높거나 이미 어김), chime | nhtsa-etc-ev-fsa, 68쪽 | 1차 | 2026-11-23 |
| C-E-015 | 그 차의 페달 센서는 VPA1, VPA2를 내고 VPA2는 같은 기울기에 0.8 V 높게 시작한다. 제어기는 두 전압을 견주어 문제를 찾는다 | nasa-toyota-ua-report, 58쪽, 96쪽 | 1차 | 2026-11-23 |
| C-E-016 | 두 센서의 견줌은 고장이 둘을 함께 유효한 전압으로 만들지 않는 한 지켜 주고, offset은 공통 원인 고장을 막으려는 것이다 | nasa-toyota-ua-report, 72쪽 | 1차 | 2026-11-23 |
| C-E-017 | 페달 센서마다 전용의 전원선과 귀선이 있다 | nasa-toyota-ua-report, 96쪽 | 1차 | 2026-11-23 |
| C-E-018 | DTC 표는 센서마다의 낮은/높은 전압과 두 센서의 상관, rationality를 별개 코드로 둔다 | nasa-toyota-ua-report, 63쪽 | 1차 | 2026-11-23 |
| C-E-019 | 페달 센서 하나가 고장으로 판정되면 limp home으로 들어가 남은 센서로 제한된 범위에서 throttle을 제어한다. limp home은 고장 뒤 낮은 속도로 계속 달리게 한다. MIL이 알리고 DTC로 저장한다 | nasa-toyota-ua-report, 49쪽, 67쪽 | 1차 | 2026-11-23 |
| C-E-020 | 고장 모드 표에 "DTC when both Brake Switch poles do not agree"라는 칸이 있다 (cruise control의 줄) | nasa-toyota-ua-report, 78쪽 (쪽을 그림으로 그려 확인) | 1차 | 2026-11-23 |
| C-E-021 | 저항성 단락 상태에서 DTC를 지우고 MIL을 끄면 다시 켜지지 않았지만 동작은 그대로였다 | nasa-toyota-ua-report, 81쪽 | 1차 | 2026-11-23 |
| C-E-022 | CAN CC의 frame: 11 또는 29 bit identifier, 값이 작을수록 높은 우선순위 (bit-wise arbitration), 0-8 byte data, CRC, ACK, 오류 검출 다섯 가지, error frame과 재전송, bus-off | CAN in Automation, "CAN CC", https://www.can-cia.org/can-knowledge/can-cc (2026-11-23에 봄. 날짜 없는 웹 페이지. scratchpad에 받아 글을 대조했다) | 1차 (표준 단체의 설명 페이지) | 2026-11-23 |
| C-E-023 | E2E가 가정하는 통신 고장 목록과, 그 원인에 transceiver 고장, EMC, ECU와 gateway 안 통신 소프트웨어 (RTE, COM, network stack)의 체계적 고장이 든다 | autosar-safety-measures, 33-34쪽 | 1차 | 2026-11-23 |
| C-E-024 | SW-C는 RTE 위에 있고 하드웨어에 독립이며 정보를 RTE로만 주고받는다. runnable은 OS task에 넣어 실행한다. partition 사이 메모리 보호. Watchdog Manager는 basic software module이다. CDD는 입출력에 직접 닿고, 감시 소프트웨어를 CDD에 두는 설계가 있다 | autosar-safety-measures, 10쪽, 11쪽, 12쪽, 23쪽, 60쪽 | 1차 | 2026-11-23 |
| C-E-025 | AUTOSAR는 완전한 safe 해법이 아니며 그것으로도 안전하지 않은 계통을 만들 수 있다 | autosar-safety-measures, 7쪽 | 1차 | 2026-11-23 |
| C-13-001 | MISRA C는 자동차를 위해 만들어진 C의 더 안전한 부분집합이다 (발표의 소개) | koopman-toyota-ua, 35쪽 | 1차 | 2026-11-23 |
| C-13-002 | MISRA Compliance의 면책: 이 문서의 요구를 지키는 것만으로 오류 없는 견고한 소프트웨어가 보장되지 않는다 | misra-compliance-2020, 4쪽 | 1차 | 2026-11-23 |
| C-13-003 | MISRA 지침은 문서화된 개발 과정 안에서 쓰도록 만들어졌고, 그 과정이 보장할 것으로 요구사항, 설계, compiler가 만든 object, test의 넷을 든다 | misra-compliance-2020, 10쪽 | 1차 | 2026-11-23 |
| C-13-004 | 예제에서 가장 무거운 결함 셋 (허용 범위의 틈, 제동 우선 상태의 기억, 방향이 바뀌는 주기의 큰 토크)은 검토와 시제품에서 찾았다 | example/drive-torque/docs/test-report.md 6절 | 1차 | 2026-11-23 |
| C-13-005 | undefined behavior와 implementation-defined behavior의 정의, 오른쪽 밀기의 예 | N1570, PDF 21-22쪽 (3.4.1, 3.4.3) | 1차 (공개 초안) | 2026-11-23 |
| C-13-006 | 구현은 부호 있는 overflow에서 값을 돌리거나, trap을 내거나, 일어나지 않는다고 가정하고 object 코드를 만들 수 있다 | SEI CERT C, INT32-C (웹) | 1차 | 2026-11-23 |
| C-13-007 | 식의 결과가 수학적으로 정의되지 않거나 형의 범위를 넘으면 undefined behavior다 | N1570, PDF 94쪽 (6.5 문단 5) | 1차 (공개 초안) | 2026-11-23 |
| C-13-008 | 부호 없는 형으로의 변환은 최댓값보다 하나 큰 수를 더하거나 빼서 정해진다 | N1570, PDF 69쪽 (6.3.1.3 문단 2) | 1차 (공개 초안) | 2026-11-23 |
| C-13-009 | int보다 작은 정수형은 int로 승격된다 (integer promotion) | N1570, PDF 69쪽 (6.3.1.1 문단 2) | 1차 (공개 초안) | 2026-11-23 |
| C-13-041 | typedef는 새 형을 만들지 않고 같은 형의 다른 이름일 뿐이다 | N1570, PDF 155쪽 (6.7.8) | 1차 (공개 초안) | 2026-11-23 |
| C-13-010 | INT32-C는 부호 있는 연산의 overflow를 막으라는 규칙이고 연산 전 검사를 보인다 | SEI CERT C, INT32-C (웹) | 1차 | 2026-11-23 |
| C-13-011 | INT31-C는 음수를 부호 없는 형으로 바꾸는 것을 결과가 정해져 있어도 위반으로 본다 | SEI CERT C, INT31-C (웹) | 1차 | 2026-11-23 |
| C-13-012 | 부분집합을 두는 이유 둘, coding standard로 만든 부분집합은 compiler가 집행하지 않는다 | nasa-gb-8719-13, 208쪽 | 1차 | 2026-11-23 |
| C-13-013 | C에서는 정수 계산이 overflow하지 않음을 보이기 어렵다. 배열과 문자열의 경계 검사가 없다. 전역 변수 100개면 인자 2개인 함수가 사실상 102개 | nasa-gb-8719-13, 215쪽, 216쪽 | 1차 | 2026-11-23 |
| C-13-014 | 가장 안전한 언어로 Ada와 SPARK를 꼽고, 익숙한 언어에 남는 것이 최선일 때가 많으며, C를 고르면 표준을 만들어 집행하고 검사와 test에 시간을 더 쓰라고 한다 | nasa-gb-8719-13, 233쪽 | 1차 | 2026-11-23 |
| C-13-015 | style 요구를 coding standard에서 떼어 둔다 (표준이 선반에 올려지는 것을 막으려고) | nasa-gb-8719-13, 147쪽 | 1차 | 2026-11-23 |
| C-13-016 | style guide는 코드의 정확성에 직접 영향이 없는 외형의 규칙이다 | misra-compliance-2020, 11쪽 | 1차 | 2026-11-23 |
| C-13-017 | 준수 주장이 뜻을 가지려면 밝혀야 할 다섯 가지 | misra-compliance-2020, 9쪽 | 1차 | 2026-11-23 |
| C-13-018 | rule과 directive의 구분 | misra-compliance-2020, 16쪽 | 1차 | 2026-11-23 |
| C-13-019 | mandatory, required, advisory의 뜻. mandatory는 바꿀 수 없고 required는 advisory나 disapplied로 낮출 수 없다 | misra-compliance-2020, 23쪽 | 1차 | 2026-11-23 |
| C-13-020 | deviation record의 내용과 적용 위치의 목록 | misra-compliance-2020, 20쪽 | 1차 | 2026-11-23 |
| C-13-021 | deviation을 받아들이면 안 되는 경우 (편의, 다른 방법이 있음, 영향을 따지지 않음) | misra-compliance-2020, 21쪽 | 1차 | 2026-11-23 |
| C-13-022 | 불변인 식과 실행될 수 없는 코드를 금하는 지침을 지키면 어떤 방어 조치를 쓸 수 없고, 그때 위반이 받아들여질 수 있다 | misra-compliance-2020, 22쪽 | 1차 | 2026-11-23 |
| C-13-023 | 이상적인 정적 분석 도구는 만들 수 없다. 도구마다 강조가 달라 둘 이상이 필요할 수 있다 | misra-compliance-2020, 13쪽 | 1차 | 2026-11-23 |
| C-13-024 | decidable, undecidable한 rule. 진단이 없다는 것이 "예"를 뜻하지 않는다. 보수적이고 방어적인 코딩으로 불확실성을 없앨 수 있다 | misra-compliance-2020, 18-19쪽 | 1차 | 2026-11-23 |
| C-13-025 | 도구 메시지의 네 분류와 조사, 기록 | misra-compliance-2020, 17-18쪽 | 1차 | 2026-11-23 |
| C-13-026 | NASA의 Toyota 조사에서 쓴 정적 분석 도구 셋의 성격 | nasa-toyota-ua-report, 149쪽 | 1차 | 2026-11-23 |
| C-13-027 | 쓴 도구로는 단독으로 UA를 일으키는 소프트웨어 결함을 찾지 못했다 | nasa-toyota-ua-report, 152쪽 | 1차 | 2026-11-23 |
| C-13-028 | 어떤 합리적인 분석이나 test로도 오류가 없음을 증명할 수 없고, 증거가 없다는 것이 무죄를 뜻하지 않는다 | nasa-toyota-ua-report, 20쪽 | 1차 | 2026-11-23 |
| C-13-029 | MISRA C 규칙 35개 중 14개 위반, read/write 변수 11,253개, 안전 규칙은 보통 재귀를 금하고 ETCS는 재귀를 쓴다 (원고 쪽 전문가의 발표, NASA 부록 A와 증언 인용) | koopman-toyota-ua, 36쪽, 40쪽, 43쪽 | 1차 (발표자의 의견) | 2026-11-23 |
| C-13-030 | defensive programming의 풀이, 결함의 출처, 범위 검사와 대응, 계속 진행은 권하지 않음, 전략의 일관성 | nasa-gb-8719-13, 147-148쪽 | 1차 | 2026-11-23 |
| C-13-031 | cyclomatic complexity가 10을 넘으면 단순화를 검토, 10보다 높은 한계는 경험과 추가 test가 있을 때만 | nasa-gb-8719-13, 96쪽, 150쪽 | 1차 | 2026-11-23 |
| C-13-032 | 지표와 한계값은 산업, 조직, 프로젝트가 정한다. 크기와 복잡도의 균형이 coverage를 얻는 시간을 줄인다 | misra-compliance-2020, 11-12쪽 | 1차 | 2026-11-23 |
| C-13-033 | complexity 50을 넘으면 test할 수 없다고 본다. Toyota 코드에 50을 넘는 함수 67개 (증언 인용) | koopman-toyota-ua, 38쪽 | 1차 (발표자의 의견) | 2026-11-23 |
| C-13-034 | interrupt 분석의 물음 (막는 구간의 길이, 쌓아 둘 수 있는가, 낮은 우선순위가 중요한 data를 바꾸는가) | nasa-gb-8719-13, 174쪽 | 1차 | 2026-11-23 |
| C-13-035 | 공유 전역이 늘 interrupt를 막은 채 접근되지는 않았다 (NASA 부록 A 인용) | koopman-toyota-ua, 42쪽 | 1차 (발표자의 인용) | 2026-11-23 |
| C-13-036 | wild pointer가 관계없는 함수를 망가뜨릴 수 있고, FCR은 자기의 고장을 모두 감시할 수 없다 | koopman-toyota-ua, 31쪽 | 1차 | 2026-11-23 |
| C-13-037 | 실행 환경의 자원 (처리 시간, stack)과 산술 overflow 같은 run-time 오류의 부재를 과정이 보이고 기록한다 | misra-compliance-2020, 15쪽 | 1차 | 2026-11-23 |
| C-13-038 | 경고를 켜고 읽고 가능하면 오류로 한다 | nasa-gb-8719-13, 372쪽 | 1차 | 2026-11-23 |
| C-13-039 | 동적 memory를 그냥 금하는 것이 반드시 최선은 아니다 | nasa-gb-8719-13, 218쪽 | 1차 | 2026-11-23 |
| C-13-040 | 일부 과정 표준 (IEC 61508, ISO 26262, DO-178)은 어떤 경우 compiler와 정적 분석 도구의 qualification을 요구한다 | misra-compliance-2020, 14쪽 (참고 문헌은 최신 판을 가리킨다고 적음, 판 표기 없음) | 2차 (ISO 26262, 판 없음) | 2026-11-23 |
| C-EX-023 | 예제의 compile option, cppcheck와 clang-tidy의 설정, CBMC의 네 검사 | example/drive-torque/Makefile, tools/prove.sh | 1차 | 2026-11-23 |
| C-EX-024 | 제품 코드에 malloc/free, 재귀, 쓰기 가능한 전역 변수, float/double이 없고, 함수 pointer는 task table 하나다. .c 11개 944줄 | example/drive-torque/src (grep, wc로 확인) | 1차 | 2026-11-23 |
| C-EX-025 | Apple clang 21에서 이 option으로 쓰지 않는 인자와 쓰지 않는 static 함수가 오류가 된다 | 작은 파일로 실험 (scratchpad) | 1차 (실험) | 2026-11-23 |
| C-EX-026 | to_permille의 signed overflow, CRC 변환 셋, clang-tidy 경고 7개, compile되지 않는 변이, 상수 이름을 쓴 test, cppcheck MISRA 7.3 거짓 경보 | example/drive-torque/docs/test-report.md 6절, 7절; notes/tool-check.md | 1차 | 2026-11-23 |
| C-EX-027 | 증명 성질 4, 8, 13, 14가 망가진 상태 값에서도 성립한다. 증명은 C 코드의 논리이고 기계어를 덮지 않는다 | example/drive-torque/docs/test-report.md 5절; test/proof/harness.c | 1차 | 2026-11-23 |
| C-EX-028 | 현재 cppcheck 지적 없음, clang-tidy 경고 0 | `make static`을 2026-11-23에 돌림 | 1차 | 2026-11-23 |
| C-12-007 | E2E 규격의 통신 고장과 주된 수단 (Table 6.1): 되풀이, 잃음, 늦음, 순서 - counter. 끼어듦, 주소가 틀림 - data ID. 둔갑 - data ID와 CRC. 손상, 받는 쪽마다 다른 정보 - CRC. 일부만 받음 - counter. 경로가 막힘 - counter (잃음이나 timeout) | autosar-e2e-protocol (R25-11), 32-33쪽 | 1차 | 2026-11-23 |
| C-12-008 | Profile 1은 지연을 counter가 아니라 정기적인 송신과 timeout의 감시에 맡긴다 (Table 6.3) | autosar-e2e-protocol, 83쪽 | 1차 | 2026-11-23 |
| C-12-009 | Profile 2는 메시지의 지연을 검출하지 않고, timeout 같은 보호는 검사 함수를 부르는 쪽이 구현해야 한다 | autosar-e2e-protocol, 107쪽 | 1차 | 2026-11-23 |
| C-12-010 | E2E 보호는 profile이 시간 표시를 넣지 않으므로 data가 지금의 것인지를 보장하지 않는다 | autosar-safety-measures (R25-11), 42쪽 | 1차 | 2026-11-23 |
| C-12-011 | Profile 1과 2는 호환성 때문에만 유지하는 legacy이고, 새 프로젝트는 Profile 11과 22를 쓴다 | autosar-e2e-protocol, 82쪽, 107쪽 | 1차 | 2026-11-23 |
| C-12-012 | Profile 1의 CRC는 CRC-8-SAE J1850의 다항식 0x1D이고 처음 값과 XOR 값은 0x00이다 | autosar-e2e-protocol, 83쪽, 86쪽 | 1차 | 2026-11-23 |
| C-12-013 | Profile 1의 data ID는 16 bit이고, dataIdMode 0, 1, 2에서는 전송하지 않고 CRC의 계산에만 넣는다 (implicit transmission) | autosar-e2e-protocol, 82쪽 | 1차 | 2026-11-23 |
| C-12-014 | Profile 1은 CRC가 맞는 첫 메시지에서 counter를 검사하지 않고 INITIAL을 알린다 | autosar-e2e-protocol, 96쪽 (그림 6.60), 103쪽 | 1차 | 2026-11-23 |
| C-12-015 | Profile 1은 검사를 부를 때마다 MaxDeltaCounter를 1 올리고 (14까지), 새 data가 없으면 허용 폭이 넓어진다. Profile 11의 MaxDeltaCounter는 정한 값이고 검사 흐름에 증가 단계가 없다 | autosar-e2e-protocol, 96쪽, 104쪽, 179쪽 (그림 6.112), 182쪽 | 1차 | 2026-11-23 |
| C-12-016 | CRC가 틀린 메시지 (ERROR, WRONGCRC)와 새 data 없음은 counter의 기준 (State->Counter, LastValidCounter)을 바꾸지 않는다 | autosar-e2e-protocol, 47쪽 (그림 6.21), 96쪽 (그림 6.60), 179쪽 (그림 6.112) | 1차 | 2026-11-23 |
| C-12-017 | CRC의 오류는 counter의 오류와 달리 거짓 경보일 가능성이 낮고, 더 엄격한 반응이 맞으며, 받는 쪽이 참는 CRC 오류의 수를 제한해야 한다 | autosar-e2e-protocol, 32쪽 | 1차 | 2026-11-23 |
| C-12-018 | FTTI = tFD + tFR이고 tFD는 E2E의 debounce 시간이다. 상태 기계의 창 크기를 FTTI에서 고르는 식을 준다 | autosar-e2e-protocol, 244쪽 | 1차 (규격의 FTTI를 설명) | 2026-11-23 |
| C-12-019 | 고른 profile의 검출 능력이 충분함을 하드웨어 고장률, bit 오류율, node 수, 반복률, gateway를 따져 사용자가 보여야 한다 | autosar-e2e-protocol, 14쪽. autosar-safety-measures, 42쪽 | 1차 | 2026-11-23 |
| C-12-020 | E2E 보호가 잡는 고장에는 아래 통신 층 (RTE, COM, network stack)의 체계적 결함이 든다. CAN과 FlexRay의 CRC는 통신 제어기의 하드웨어가 준다 | autosar-e2e-protocol, 13쪽, 86쪽 | 1차 | 2026-11-23 |
| C-12-021 | alive supervision은 너무 자주도 드물게도 실행되지 않는지, deadline supervision은 두 checkpoint 사이의 시간이 최소와 최대 안인지, logical supervision은 control flow의 오류를 본다 | autosar-safety-measures, 23-24쪽, 28쪽 | 1차 | 2026-11-23 |
| C-12-022 | checkpoint가 성글면 검출 능력이 제한된다. deadline supervision은 끝의 checkpoint가 아예 오지 않는 것을 검출하지 않는다 | autosar-safety-measures, 27쪽 | 1차 | 2026-11-23 |
| C-12-023 | AUTOSAR 개요는 시간 감시를 ISO 26262-6의 Annex D (D.2.2 Timing and execution)에 잇는다 | autosar-safety-measures, 28쪽 | 2차 (ISO 26262:2018) | 2026-11-23 |
| C-12-024 | watchdog을 interrupt로 다시 걸지 말라. 실제 process가 막혀도 interrupt는 살아 있을 수 있다 | nasa-gb-8719-13, 94쪽 | 1차 | 2026-11-23 |
| C-12-025 | 쓴 값을 다른 함수가 되읽어 확인한다 (read-back) | nasa-gb-8719-13, 95쪽 | 1차 | 2026-11-23 |
| C-12-026 | 중요한 변수를 여러 사본으로 두고 견주며, 2-out-of-3, 기본값, 묶은 변수의 CRC를 쓴다. CRC나 오류 정정 부호로 중요한 data의 손상을 찾는다 | nasa-gb-8719-13, 94쪽, 140쪽 | 1차 | 2026-11-23 |
| C-12-027 | ROM 검사는 켤 때 CPU 자가 시험 다음에 하고, 자기 프로그램을 고칠 수 있으면 주기적으로 한다 | nasa-gb-8719-13, 93쪽 | 1차 | 2026-11-23 |
| C-12-028 | Toyota의 제어기는 watchdog을 다시 거는 함수를 가장 낮은 우선순위 task에서 돌렸다 | nasa-toyota-ua-report, 146쪽 | 1차 | 2026-11-23 |
| C-12-029 | H-bridge는 main과 sub CPU 둘의 입력이 모두 있어야 동작하고, CPU reset 동안 출력이 low로 끌려 구동이 꺼진다. sub CPU는 이중 처리 경로가 아니고 독립된 하드웨어 enable을 준다 | nasa-toyota-ua-report, 144쪽, 146쪽 | 1차 | 2026-11-23 |
| C-12-030 | 특정한 저항성 단락에서 DTC 2121을 지우고 MIL을 끄면, 단락이 그대로인데 DTC와 MIL이 다시 켜지지 않고 동작은 그대로다 | nasa-toyota-ua-report, 81쪽 | 1차 | 2026-11-23 |
| C-12-031 | 두 pedal 신호를 허용 폭 안에 놓는 고장은 고장으로 검출되지 않고 유효한 명령으로 읽힌다 | nasa-toyota-ua-report, 101쪽 | 1차 | 2026-11-23 |
| C-12-032 | Toyota의 고장 표에 brake switch의 두 극이 맞지 않을 때의 DTC가 있다 | nasa-toyota-ua-report, 78쪽 (표 6.5.2.2-1) | 1차 | 2026-11-23 |
| C-12-033 | 페달 신호를 확인할 수 없으면 평소보다 느린 상승률로 토크를 허용하는 safe state를 예로 든다 | nhtsa-etc-ev-fsa, 67쪽 | 1차 | 2026-11-23 |
| C-12-034 | 한 제어기가 정한 간격으로 입력 묶음을 주고 정한 시간 안의 옳은 답으로 다른 제어기의 건전성을 확인한다 (quizzer, seed-and-key) | nhtsa-etc-ev-fsa, 74쪽 각주 24 | 1차 | 2026-11-23 |
| C-15-001 | test와 debugging은 가능한 실행의 일부만 보아 틀린 실행을 놓칠 수 있으므로 증명이 아니다 (coverage가 없는 문제) | Cousot, Abstract Interpretation in a Nutshell, 5절. https://www.di.ens.fr/~cousot/AI/IntroAbsInt.html (웹, 직접 읽음) | 1차 | 2026-11-23 |
| C-15-002 | verification은 한 단계의 산출물이 앞 단계의 요구를 만족하는지 보는 것 ("built right")이고 방법은 analysis, review, inspection, testing, auditing. validation은 "right product"를 보는 것이고 보통 주된 방법은 testing | nasa-gb-8719-13, 45쪽 | 1차 | 2026-11-23 |
| C-15-003 | NASA 표준은 IEEE 1012를 출처로 validation을 "you built the right thing", verification을 "you built it right"로 적는다 | nasa-std-8739-8b, 13쪽 | 1차 | 2026-11-23 |
| C-15-004 | Formal Inspection은 결함을 찾아 없애려는 구조화된 기술 review이고 Fagan Inspection이라고도 한다. 대상은 요구사항, 설계 노트, test 계획, source 코드 | nasa-gb-8719-13, 118쪽 (6.5.5절과 각주) | 1차 | 2026-11-23 |
| C-15-005 | Formal Inspection은 정해진 단계와 검토자의 역할이 있어 informal review나 walkthrough와 다르고, formal method가 아니다 ("Formal inspections are not formal methods!") | nasa-gb-8719-13, 119쪽 | 1차 | 2026-11-23 |
| C-15-006 | inspection은 초기, 특히 요구사항 단계에서 효과가 가장 크다. 고장과 결함의 대부분이 빠졌거나 잘못 이해된 요구사항에서 온다는 연구를 "Studies have shown"으로만 든다. 검토자의 관점, 점검 목록 | nasa-gb-8719-13, 119쪽 | 1차 | 2026-11-23 |
| C-15-007 | 코드 inspection의 점검 목록에 넣을 것 넷 (요구사항과 설계 정보, 코딩 표준, 언어와 무관한 오류, 언어별 오류). 안전 필수 부품에는 최소한 Formal Inspection을 해야 한다 (should) | nasa-gb-8719-13, 176쪽 | 1차 | 2026-11-23 |
| C-15-008 | 요구사항과 코드의 Formal Inspection의 등급은 benefit HIGH, cost MODERATE | nasa-gb-8719-13, 119쪽, 177쪽 | 1차 | 2026-11-23 |
| C-15-009 | 기법의 benefit와 cost 등급은 주관적이고 기법을 고르는 하나의 고려일 뿐이다 | nasa-gb-8719-13, 104쪽 | 1차 | 2026-11-23 |
| C-15-010 | 프로젝트 관리자는 요구사항, 계획, 설계, 코드, test 절차에 peer review나 inspection을 하고 결과를 보고해야 한다 (shall, SWE-087) | nasa-std-8739-8b, 44쪽 | 1차 (NASA 자체의 요구) | 2026-11-23 |
| C-15-011 | 실행 시간이 짧은 도구가 대체로 거짓 경보를 낼 가능성이 크고, 분석 시간과 정밀도의 균형을 고려한다 ("Broadly speaking") | misra-compliance-2020, 13쪽 | 1차 | 2026-11-23 |
| C-15-012 | undecidable rule에서 도구가 확정된 위반과 가능한 위반을 구별해 알리는 정도가 중요하다. 진단이 없다는 것이 Yes를 뜻하지 않는다 | misra-compliance-2020, 18-19쪽 | 1차 | 2026-11-23 |
| C-15-013 | Toyota 조사에서 NASA는 Coverity, CodeSonar, Uno의 세 정적 분석 도구를 썼고 성격이 서로 다르다 | nasa-toyota-ua-report, 149쪽 | 1차 | 2026-11-23 |
| C-15-014 | Koopman의 슬라이드는 도구별 경고 건수를 든다 (Coverity 선언 후 미참조 97, CodeSonar 전역 변수의 다른 형 선언 2272, Uno 초기화되지 않았을 수 있는 변수 89). Toyota는 경고 없는 상태를 주장하지 않았다. 어느 경고가 결함인지는 적지 않는다 | koopman-toyota-ua, 37쪽 | 1차 (원고 쪽 전문가의 발표. 숫자는 NASA 부록 A의 인용) | 2026-11-23 |
| C-15-015 | abstract interpretation은 실제 의미의 상위 집합을 쓰고, 그것이 안전하면 실제도 안전하다. sound는 모든 경우를 덮는다는 뜻. 경보가 없으면 올바름의 증명. 상위 집합 때문에 거짓 경보가 생긴다. sound하고 complete한 추상화는 수학적으로 있으나 계산할 수 없다 | Cousot, 같은 쪽, 7절, 9절, 11절, 13절 (웹, 직접 읽음) | 1차 | 2026-11-23 |
| C-15-016 | abstract interpretation은 분석기가 계산한 성질이 모든 실행 경로에서 성립한다는 수학적 보장을 준다 | Brat, Navas, Shi, Venet, IKOS: A Framework for Static Analysis based on Abstract Interpretation, NASA Ames, 2014, 1쪽. https://ntrs.nasa.gov/api/citations/20140012995/downloads/20140012995.pdf (웹, 직접 읽음) | 1차 | 2026-11-23 |
| C-15-017 | Astree는 C 프로그램의 run time error가 없음을 증명하려는 분석기이고, 동적 memory 할당과 재귀가 없는 프로그램을 분석하며, 가능한 오류를 모두 알리되 (sound) 때로 일어날 수 없는 오류도 알린다 | Astree 연구 팀 (ENS, INRIA), https://www.astree.ens.fr/ 본문 (웹, 직접 읽음) | 1차 (도구 개발 팀의 서술) | 2026-11-23 |
| C-15-018 | formal specification은 요구사항을 형식적인 수학 언어로 쓰는 것이고, formal verification은 결과물이 명세를 만족한다는 증명을 준다. FM은 정량적인 신뢰도를 보장하지 않고 높은 수준의 assurance를 준다고 인정된다 | nasa-gb-8719-13, 68쪽 | 1차 | 2026-11-23 |
| C-15-019 | 증명 없이 명세를 쓰는 과정만으로도 값지다. Lutz와 Ampo의 사례에서 formal specification으로 요구사항의 문제 37개를 찾았다 | nasa-gb-8719-13, 68-69쪽 | 1차 | 2026-11-23 |
| C-15-020 | model checking은 유한 상태 시스템을 검증하는 자동 방법이다. 상태 기반 모델, temporal logic, 상태 공간 탐색. 성질은 reachability, deadlock 없음, safety, liveness. 주된 어려움은 state explosion | nasa-gb-8719-13, 128-129쪽 | 1차 | 2026-11-23 |
| C-15-021 | Toyota 보고서는 SPIN을 소개하고 그 도구를 보고서 저자 한 사람이 만들었다고 적는다. 결론 F-10: 정적 분석, logic model testing 등을 했고, 쓴 도구로는 UA를 단독으로 일으키는 소프트웨어 결함을 찾지 못했다 | nasa-toyota-ua-report, 150쪽, 152쪽 | 1차 | 2026-11-23 |
| C-15-022 | CBMC의 기본 생각은 실행을 정해진 단계 수까지 모델로 만드는 것이고 반복문 펼침으로 구현한다. 한계가 작으면 깊은 경로의 결함을 놓칠 수 있다. unwinding assertion이 모두 성립하면 한계가 충분하다. 한계는 backjump로 세며 i<100 반복은 101이 필요하다 | CPROVER Manual, Understanding Loop Unwinding. https://raw.githubusercontent.com/diffblue/cbmc/develop/doc/cprover-manual/cbmc-unwinding.md (웹, 직접 읽음) | 1차 | 2026-11-23 |
| C-15-023 | 교육 자료는 --unwind 11이 반복문을 10번 펼친다고 적는다 ("10 times (not 11 times!)") | CBMC training, Loop unwinding. https://model-checking.github.io/cbmc-training/cbmc/overview/loop-unwinding.html (웹, 직접 읽음) | 1차 | 2026-11-23 |
| C-15-024 | bounded model checking은 실행의 앞부분만 보므로 늦게 나타나는 오류를 놓칠 수 있어 증명이 아니다 | Cousot, 같은 쪽, 6절 | 1차 (저자의 관점) | 2026-11-23 |
| C-15-025 | CBMC 6.11에서 열 번 도는 반복문은 --unwind 11이면 증명되고, --unwind 10이면 unwinding assertion이 실패한다. --unwinding-assertions를 주지 않아도 그렇다 | 이 책이 도구로 확인 (cbmc 6.11.0, scratchpad의 작은 예 loop.c. 2026-11-23) | 1차 (실험) | 2026-11-23 |
| C-15-026 | theorem prover는 이름의 목록만 있다 | nasa-gb-8719-13, 69쪽 | 1차 | 2026-11-23 |
| C-15-027 | FM을 쓰는 세 방식 (뒤에, 나란히, FM만으로)과 각각의 비용. FM이 널리 받아들여지지 않은 것은 주로 형식 증명의 어려움 때문이다 | nasa-gb-8719-13, 68쪽 | 1차 | 2026-11-23 |
| C-15-028 | 가장 엄격한 Design Logic Analysis는 FM을 쓴다. 비용이 높아 대상의 비용이나 위험이 낮으면 더 단순한 DLA를 쓴다 | nasa-gb-8719-13, 160쪽 | 1차 | 2026-11-23 |
| C-15-029 | Table 3-5: software category와 hazard severity로 safety effort (Full, Moderate, Minimum, None)를 정한다. 기법마다 수준별 권장 코드가 있고, Highly Recommended를 넣지 않으면 안전이 해쳐지지 않음을 보여야 한다 (should) | nasa-gb-8719-13, 42-43쪽 | 1차 | 2026-11-23 |
| C-15-030 | 위험이 큰 부품은 설계와 코딩의 모든 단계에서 inspection하고 작은 부품은 코드 inspection만 할 수 있다 (may) | nasa-gb-8719-13, 156쪽 | 1차 | 2026-11-23 |
| C-15-031 | AC 20-115D는 ED-216/DO-333 Formal Methods Supplement를 인정하는 문서로 든다 | faa-ac-20-115d, 1쪽 | 1차 | 2026-11-23 |
| C-15-032 | IKOS 논문은 DO-333이 abstract interpretation을 인증 크레딧을 얻는 한 방법으로 든다고 적는다 | Brat 외, 2014, 1쪽 (위 주소) | 2차 (DO-178C/DO-333, 판은 논문이 적은 대로) | 2026-11-23 |
| C-15-033 | `static`은 cppcheck (warning, style, performance, portability)와 clang-tidy (bugprone-*, cert-*, clang-analyzer-*)를 돌린다. cppcheck는 `--error-exitcode=1`로 멈추고, clang-tidy는 실패를 `true`로 덮고 경고 수만 찍는다. 지금 둘 다 지적 없음 | example/drive-torque/Makefile 131-147행, `make static` 실행 결과 | 1차 | 2026-11-23 |
| C-15-034 | 성질 7의 단언과 가정 (코드 인용), 전제 넷 | example/drive-torque/test/proof/harness.c 342-409행 | 1차 | 2026-11-23 |
| C-15-035 | prove.sh는 성질 14개를 --signed-overflow-check --div-by-zero-check --conversion-check --bounds-check --unwind 101 --unwinding-assertions로 돌리고, 가장 긴 반복이 100번이다. 증명 전에 tool_check.c로 도구를 확인한다. 지금 14개 모두 증명됨 | example/drive-torque/tools/prove.sh, 실행 결과 | 1차 | 2026-11-23 |
| C-15-036 | 증명과 정적 분석이 찾은 것 (signed overflow, CRC 변환 셋, SWR-24의 반례 둘, clang-tidy 둘, cppcheck MISRA 거짓 경보) | example/drive-torque/docs/test-report.md 6절 | 1차 | 2026-11-23 |
| C-15-037 | 성질 14가 구조체 안 배열의 한 칸 넘는 쓰기를 놓쳤고, 그 뒤에 tool_check.c, proof_mutation.py (9개 모두 잡음), _Static_assert를 더했다 | docs/test-report.md 5절, 6절; docs/tools.md 3절; src/flow/flow.c 12행 | 1차 | 2026-11-23 |
| C-15-038 | "틈이 5 Nm라는 것을 증명했다"가 증명보다 넓었다 (F-04, 성질 7 추가). 성질 7을 한 주기의 증분으로 읽어 "쌓인다"고 적은 것이 틀렸다 (F-21, F-29) | reviews/2026-11-23-stage2-part2/README.md, reviews/2026-11-23-stage2-part3/README.md의 "검토가 찾은 것의 성격" | 1차 | 2026-11-23 |
| C-15-039 | review는 역할을 받은 에이전트 둘이 했고, 1차에서는 서로의 의견을 보지 않았고, 같은 계열의 모델이며, 사람의 검토를 받지 않았다 | docs/safety-plan.md 40-55행; reviews/2026-11-23-stage2-part3/README.md (참가자, 확인하지 못한 것) | 1차 | 2026-11-23 |
| C-15-040 | review가 찾은 것: safety goal을 근거에 맞춰 좁힘, 남는 것의 목록이 좁음, 동등한 변이의 이유가 틀림, fault를 빼도 통과하는 test 둘 | 위 두 README의 "검토가 찾은 것의 성격"; docs/tools.md 3절 | 1차 | 2026-11-23 |
| C-16-007 | 응용의 모든 면, 사건의 모든 조합을 test하는 일은 드물게만 가능하고, test를 모을 곳은 위험의 분석으로 정하는 것이 알맞다 | nasa-gb-8719-13, 189쪽 | 1차 | 2026-11-23 |
| C-16-008 | 차량 수준의 test는 쓸모 있고 중요하지만 조건, 시간 순서, 간헐적 고장의 조합이 너무 많아 모든 것을 test할 수 없다. slide 20의 test 양 숫자에는 발표자의 어림 ("perhaps 1-2 hours")이 섞여 있다 | koopman-toyota-ua, 19쪽, 20쪽 | 1차 (원고 쪽 전문가의 발표) | 2026-11-23 |
| C-16-009 | 시간당 10^-8의 고장률을 정량화하려면 10^8시간이 넘는 test가 필요하다. 10시간 임무에 고장 확률 10^-9이면 시험체 10개로 고장 한 번까지 기대 시험 기간 114155년. r=1은 가장 짧은 경우이고 통계적 유의성에는 더 많은 test가 든다 | Butler와 Finelli, The Infeasibility of Quantifying the Reliability of Life-Critical Real-Time Software, 1993, NASA NTRS 공개본 https://ntrs.nasa.gov/api/citations/20040139817/downloads/20040139817.pdf, 4쪽 (Table 1), 15쪽 | 1차 (웹, 저자 공개본) | 2026-11-23 |
| C-16-010 | requirements coverage는 요구사항에 따른 test가 구현을 얼마나 확인했는지, structural coverage는 그 test가 코드 구조를 얼마나 실행했는지를 본다. 앞의 분석이 먼저다. coverage는 척도이지 방법이나 test가 아니다 | nasa-mcdc-tutorial, 10쪽 | 1차 | 2026-11-23 |
| C-16-011 | 요구사항에 따른 test는 사용자의 관점에서 하고, 요구사항이 유한하고 완료 기준이 있으면 exhaustive test와 달리 실행할 수 있다 | nasa-mcdc-tutorial, 11쪽 | 1차 | 2026-11-23 |
| C-16-012 | "requirements-based test 중에 실행되었다"는 코드의 동작이 그것이 이어진 요구사항과 견주어졌다는 뜻이기도 하다 (DO-248A FAQ #43의 Note 1) | nasa-mcdc-tutorial, 12쪽 | 2차 (DO-248A를 인용) | 2026-11-23 |
| C-16-013 | 코드에서 출발한 test는 구현되지 않은 요구사항을 찾을 수 없고, 코드의 출력을 기댓값으로 여기는 경향이 생긴다. 기댓값을 요구사항에서 정하면 이 치우침이 없다 | nasa-mcdc-tutorial, 16쪽 (DO-248A FAQ #44 인용) | 2차 (DO-248A를 인용) | 2026-11-23 |
| C-16-014 | equivalence class와 boundary value 분석은 test 계획 항목에 이름으로 나온다 | nasa-gb-8719-13, 187쪽 | 1차 | 2026-11-23 |
| C-16-015 | 경계와 성능 요구사항은 정한 한계에서, 아래에서, 위에서 test하는 것이 좋고 (should), 가정한 운용 한계 밖의 동작도 볼 필요가 있다. software fault injection은 test 시작 전에 코드에 fault를 넣고 반응을 보는 특별한 안전 test 기법의 예다 | nasa-gb-8719-13, 179쪽 | 1차 | 2026-11-23 |
| C-16-016 | 비교 하나의 MC/DC는 test 둘로 채워지지만, 비교점과 관계 연산자를 확인하려면 약간 위, 약간 아래, 같은 값의 셋이 든다. altitude > 2500의 예 (25와 32000은 MC/DC만, 2500, 2499, 2501이 전환점 확인) | nasa-mcdc-tutorial, 24-25쪽 | 1차 | 2026-11-23 |
| C-16-017 | negative test는 소프트웨어가 의도한 기능만 하고 불필요한 기능은 하지 않음을 보인다. 안전 test는 어느 수준에 넣어도 되지만 모든 안전 기능의 확인과 다른 요소가 방해하지 못함을 보이는 것이 필수다 (vital) | nasa-gb-8719-13, 194쪽 | 1차 | 2026-11-23 |
| C-16-018 | statement coverage의 예 (and를 or로 잘못 써도 못 찾음), decision coverage는 (A or B)에서 B의 효과를 보지 않음, condition coverage는 (TF), (FT)가 판단을 한쪽으로만 보냄 | nasa-mcdc-tutorial, 14-15쪽 | 1차 | 2026-11-23 |
| C-16-019 | MC/DC는 입력이 n개인 판단에 일반적으로 최소 n+1개의 test. multiple condition coverage는 2^n이고, 각주는 n이 조건이 아니라 입력의 수라고 적는다 ((A and B) or (A and C)는 입력 셋, 조건 넷) | nasa-mcdc-tutorial, 15쪽 | 1차 | 2026-11-23 |
| C-16-020 | 최소 test 묶음은 exhaustive가 아니어서 모든 오류를 찾지 못한다 (or 자리의 xor). unique-cause와 masking의 정의 | nasa-mcdc-tutorial, 79쪽 | 1차 (CAST에 낸 백서, 78쪽에서 규제 지침이 아니라고 밝힘) | 2026-11-23 |
| C-16-021 | unique-cause는 판단의 논리 분석이 필요 없고, 되풀이되거나 강하게 묶인 조건의 판단에는 쓸 수 없다 | nasa-mcdc-tutorial, 19쪽 | 1차 | 2026-11-23 |
| C-16-022 | 연산자가 한 종류인 판단에서 두 방식은 같다. unique-cause를 채우면 masking도 채운다. test 수는 일반적으로 같다. masking은 논리 분석이 필요하고 묶인 조건에도 쓸 수 있다 | nasa-mcdc-tutorial, 82쪽 | 1차 (백서) | 2026-11-23 |
| C-16-023 | 단락 평가 식은 MC/DC에서 보통의 and, or처럼 다룰 수 있고 don't-care로 최소 test를 줄일 수 있다. 그 최소 test는 compiler가 최적화할 때에도 옳게 동작할 때에만 유효하다 | nasa-mcdc-tutorial, 49-51쪽 | 1차 | 2026-11-23 |
| C-16-024 | 실행되지 않은 코드는 test case나 절차의 부족, 소프트웨어 요구사항의 불충분, dead code, deactivated code에서 나올 수 있고 (DO-178B 6.4.4.3을 따라), 분석이 source의 오류도 찾을 수 있다 | nasa-mcdc-tutorial, 53쪽 | 2차 (DO-178B를 설명) | 2026-11-23 |
| C-16-025 | dead code는 지우는 것이 좋고, 의도하지 않은 기능과 deactivated code는 설명하고 다룬다. MC/DC를 채우려고 더한 test도 요구사항과 맞아야 한다 (should) | nasa-mcdc-tutorial, 67-68쪽 | 1차 | 2026-11-23 |
| C-16-026 | 예제 11: A 대신 B를 쓴 코드에서 승인된 test의 출력은 기댓값과 맞아 test만으로는 오류를 못 잡지만, MC/DC가 모자라다. 코드가 옳았다면 같은 test가 MC/DC를 준다 | nasa-mcdc-tutorial, 54-55쪽 | 1차 | 2026-11-23 |
| C-16-027 | coverage를 채우면 의도하지 않은 기능이 없음을 확인하는 데 도움이 되지만 모든 요구사항을 test했음은 확인하지 않는다. 오해의 예: 입력을 모두 source에서 끌어냄, MC/DC를 test 방법으로 씀 | nasa-mcdc-tutorial, 61쪽 | 1차 | 2026-11-23 |
| C-16-028 | source 수준 coverage는 object 수준과 다를 수 있다. Beizer: source에서 statement 100%인 test 묶음이 object에서 75% 이하일 수 있다 | nasa-mcdc-tutorial, 17쪽 | 1차 (Beizer를 인용) | 2026-11-23 |
| C-16-029 | instrumentation은 코드를 바꾸므로 오류를 숨기거나 만들지 않음을 보이는 것이 필수이고, 보통 원래 코드와 같은 test로 견준다. 도구는 probe를 넣은 코드를 확인하고 넣지 않은 코드는 가정이다 | nasa-mcdc-tutorial, 56쪽 | 1차 | 2026-11-23 |
| C-16-030 | probe가 compiler의 함수 호출 순서를 바꾼 예. probe를 넣은 코드는 compiler, linker, target이 다를 수 있어 충실도를 평가하는 것이 좋다 (should) | nasa-mcdc-tutorial, 59-60쪽 | 1차 | 2026-11-23 |
| C-16-031 | 도구마다 독립 효과를 정하는 algorithm이 다르고, 조건 수의 한계가 있어 큰 식이 무시되거나 일부만 감시될 수 있다 | nasa-mcdc-tutorial, 58쪽 | 1차 | 2026-11-23 |
| C-16-032 | unit test와 integration test의 뜻, stub과 driver | nasa-gb-8719-13, 185쪽, 190쪽 | 1차 | 2026-11-23 |
| C-16-033 | fault injection은 오류에 대한 반응을 보는 test 갈래에 들고 안전에 중요한 부품에 Highly Recommended다. 전통적으로 source를 고쳐 fault를 만들었으나 이제는 부품 사이 interface에 넣고 source 없이도 쓴다 | nasa-gb-8719-13, 191-192쪽, 281쪽 | 1차 | 2026-11-23 |
| C-16-034 | MC/DC의 목적은 요구사항에 따른 test가 코드 구조를 실행하기에 충분한지 정하는 것이지 오류를 찾는 것이 아니다 | nasa-mcdc-tutorial, 83쪽 (백서, 78쪽) | 1차 (백서) | 2026-11-23 |
| C-16-035 | mutation testing의 뜻 (변이를 만들어 test 묶음이 가려내는지 보고, 비율이 test 묶음의 질을 나타냄), 두 가설 (competent programmer, coupling effect), equivalent mutant와 그 자동 검출이 불가능함 (프로그램 동치가 결정 불가능) | Jia와 Harman, An Analysis and Survey of the Development of Mutation Testing, IEEE TSE 게재 논문의 저자 원고 (PDF 생성 2010-04), https://web.eecs.umich.edu/~weimerw/2020-481F/readings/mutation-testing.pdf, 1쪽, 3쪽, 4쪽 | 1차 (웹, 논문의 공개 사본) | 2026-11-23 |
| C-16-036 | software-in-the-loop, processor-in-the-loop, hardware-in-the-loop의 설명 (MIL은 정의하지 않음) | MathWorks, Model Development Processes, https://www.mathworks.com/help/simulink/slref/simulink-concepts-model-development-processes.html (WebFetch가 돌려준 문장, 원문 글자 대조 못 함) | 2차 (회사의 설명서) | 2026-11-23 |
| C-16-037 | MiL, SiL, PiL, HiL의 검증 단계. SiL까지 target에 매이지 않고 PiL부터 실제 target에서 수치 정확도와 실행 시간을 본다 | Synopsys, Model-Based Design and Virtual ECUs Enable Early Testing for Electric Vehicle Controls, 2025-01, https://www.synopsys.com/content/dam/synopsys/verification/white-papers/model-based-design-and-vecu-wp.pdf, 2쪽 | 2차 (회사의 백서) | 2026-11-23 |
| C-16-038 | virtual PiL, SiL (PC용으로 compile한 C 코드), MiL (C 코드를 만드는 model)의 구분 | Jordan 외, Full Virtualization of Renault's Engine Management Software, arXiv:1802.06841, https://arxiv.org/pdf/1802.06841, 5쪽 | 1차 (웹, 논문) | 2026-11-23 |
| C-16-039 | back-to-back test (equivalence test)는 생성한 코드가 model 시뮬레이션과 같은 결과를 내는지 시험한다. 다른 회사의 출처는 찾지 못했다 | MathWorks, Back-to-Back Equivalence Testing, https://www.mathworks.com/help/sltest/ug/back-to-back-equivalence-testing.html (WebFetch가 돌려준 문장) | 2차 (회사의 설명서 하나뿐) | 2026-11-23 |
| C-16-040 | simulator의 충실도를 물을 것. 안전 test는 최종 시스템 (하드웨어와 소프트웨어)에서 해야 한다 (must). 형상 관리가 system test 매체의 유일한 배포자가 되는 것이 좋고, 반복 가능성은 알려진 고정된 출처에서만 보장된다 | nasa-gb-8719-13, 190쪽 | 1차 | 2026-11-23 |
| C-16-041 | Ariane 5: SRI는 장비 수준에서 엄격히 시험했으나 Ariane 5의 카운트다운, 비행 순서, 궤적에서의 동작은 시험하지 않았다. 모의 가속도 신호를 넣는 지상 test가 가능했고 했다면 메커니즘이 드러났을 것 | ariane-501-report, 11쪽 (OCR) | 1차 | 2026-11-23 |
| C-16-042 | ISF 폐루프 시험에서 두 SRI는 소프트웨어 모듈로 모의. 1992년에 SRI를 loop에 넣지 않기로 바꿈 (이유 넷). 위원회는 이유가 기술적으로 타당했으나 이미 확인되었다고 가정한 데에 분명한 위험이 있었다고 봄. simulator로 바꾸는 것은 앞선 수준이 범위를 완전히 덮었는지 확인한 뒤에만 | ariane-501-report, 12-13쪽 (OCR) | 1차 | 2026-11-23 |
| C-16-043 | DO-178B Table A-7: statement coverage는 level A-C, decision coverage는 A-B, MC/DC는 A | nasa-mcdc-tutorial, 14쪽 | 2차 (DO-178B를 설명) | 2026-11-23 |
| C-16-044 | 예제의 수: test 71개 (`TC-` 63, `FT-` 3, `NC-` 5), 요구사항 63개 (구현 예정 5), coverage 11개 파일 100% (GCC, masking MC/DC, `-O0`), 변이 221개 (손 172, 상수 49; test 217, build 4; 따로 둔 2), fault 33가지 | example/drive-torque/docs/test-report.md 1-4절, 7절; test 코드의 ID를 grep으로 셈; build/reports/coverage.txt | 이 책의 측정 | 2026-11-23 |
| C-16-045 | `FI-01` 29 ms (30), 88 ms (92), `FI-02` 49 ms (50), 108 ms (111). 주입 시각을 주기 안에서 0-9 ms로 옮김 | test/test_scenario.c `TC-102`, test/test_fault_app.c `TC-201`, build/reports/variant-O0.txt, docs/test-report.md 3절 | 이 책의 측정 | 2026-11-23 |
| C-16-046 | 만드는 동안의 발견: input.c MC/DC 42%와 `TC-107`, 변이를 놓친 네 번, `NC-001`과 `NC-002`가 수단을 더하자 실패, `TC-113`과 `TC-208`이 fault 없이도 통과, 따로 둔 변이의 이유가 두 번 틀림, 배열 바로 뒤 변이가 우연에 기대어 잡힘, build가 잡는 변이 넷 | example/drive-torque/docs/test-report.md 3절, 6절, 7절 | 이 책의 측정 | 2026-11-23 |
| C-16-047 | 같은 test 묶음에서 줄은 100%, MC/DC는 GCC 43% (14개 가운데), LLVM 20% (5개 가운데). 세는 단위가 다르다 | notes/tool-check.md | 이 책의 측정 | 2026-11-23 |
| C-16-048 | `make variants`: `-O2`, `-Os`, sanitizer (`-O1 -fsanitize=address,undefined`) build에서 test가 통과하고 출력이 `-O0`과 같다. AddressSanitizer는 같은 stack 변수 안의 이웃에 떨어진 한 칸 넘는 쓰기를 알리지 않았다 | example/drive-torque/tools/variants.sh, build/reports/variant-*.txt (cmp로 같음 확인), docs/test-report.md 1절, docs/tools.md 2절 | 이 책의 측정 | 2026-11-23 |
| C-16-049 | `TC-009`의 코드 (현재 저장소의 것) | example/drive-torque/test/test_unit.c 876-899행 | 이 책의 산출물 | 2026-11-23 |
| C-17-001 | 일부 과정 표준 (IEC 61508, ISO 26262, DO-178)은 어떤 경우 compiler와 정적 분석 도구의 qualification을 요구한다. 그 경우가 무엇인지는 이 문서에 없다 | misra-compliance-2020, 14쪽 | 2차 (판 없음. C-13-040과 같다) | 2026-11-23 |
| C-17-002 | DO-178B에서 development tool은 오류를 넣을 수 있고 verification tool은 놓칠 수만 있다. 그래서 두 과정이 함께 모자라야 오류가 남고, 두 종류에 다른 엄격함을 요구한다 | FAA Order 8110.49 Chg 2 (2017)의 9장 (2003-06-03 판), PDF 37-38쪽 (인쇄 50-51쪽). https://www.faa.gov/documentLibrary/media/Order/FAA_Order_8110_49_w-chg_2.pdf | 2차 (DO-178B, 발행 기관) | 2026-11-23 |
| C-17-003 | verification 중에 쓰는 도구가 모두 verification tool은 아니다 (감시 코드를 넣었다 걷어 내는 도구). 분류는 최종 제품에 미치는 영향으로 정한다 | 같은 문서, PDF 37쪽 | 2차 (DO-178B, 발행 기관) | 2026-11-23 |
| C-17-004 | 도구의 결과를 다른 verification 활동이 확인하면 qualification할 필요가 없다. 세 물음에 모두 "예"이면 qualification한다 | 같은 문서, PDF 37-38쪽 (9-2.a, 9-3.a) | 2차 (DO-178B, 발행 기관) | 2026-11-23 |
| C-17-005 | DO-330/DO-178C는 기준 셋 (1: 출력이 항공 소프트웨어가 되어 오류를 넣음, 2: verification을 자동화하고 다른 과정을 줄이는 근거, 3: 의도한 범위에서 오류를 놓침)과 level로 TQL 다섯을 정하고, 번호가 낮을수록 엄격하다 | AFuzion (연도 미표기) https://afuzion.com/?p=358 . LDRA, DO-330 Test Tool Qualification Technical Briefing v2.0 (2021), 3쪽 https://ldra.com/wp-content/uploads/ldra/DO-330-Test-Tool-Qualification-Technical-Briefing-v2.0.pdf . Rapita Systems (연도 미표기) https://www.rapitasystems.com/do-330 | 2차 (DO-330, 회사 글 셋) | 2026-11-23 |
| C-17-006 | DO-178B로 qualification한 development tool은 기준 1, verification tool은 기준 2 또는 3에 대응한다 (Table 2) | faa-ac-20-115d, 11쪽 | 2차 (DO-178C/DO-330, 항공) | 2026-11-23 |
| C-17-007 | ISO 26262의 TCL은 TI와 TD로 정한다. TCL1은 더 qualification이 필요 없고 TCL2, 3은 qualification 방법이 필요하다. 방법은 넷이고 ASIL마다 맞는 정도가 다르다 | Synopsys, Understanding How to Assess Tool Confidence Levels for ISO 26262 (2017-10), 1-2쪽, 4-5쪽 https://www.synopsys.com/content/dam/synopsys/solutions/documents/automotive-tool-confidence-iso-26262-wp.pdf . Siemens, Clearing the fog of ISO 26262 tool qualification (2022-04-13) https://blogs.sw.siemens.com/verificationhorizons/2022/04/13/clearing-the-fog-of-iso-26262-tool-qualification/ | 2차 (ISO 26262:2011 / ISO 26262:2018, 회사 글 둘) | 2026-11-23 |
| C-17-008 | TCL은 따내는 등급이 아니라 쓰임에 대한 분류다 (Siemens). 모든 도구를 TCL1로 만드는 것이 목표라는 생각은 오해다 (Synopsys) | Siemens (2022), 본문. Synopsys (2017), 4쪽 | 2차 (ISO 26262:2018 / 2011) | 2026-11-23 |
| C-17-009 | TCL 판정의 책임은 쓰는 쪽에 있고, 미리 정한 TCL도 쓰는 쪽이 확인한다. 한 도구의 출력을 다른 도구로 따로 비교해 확신을 높이는 예 (합성 도구) | Synopsys (2017), 3쪽 | 2차 (ISO 26262:2011, 회사 글 하나. 원고에서 Synopsys의 말로 적었다) | 2026-11-23 |
| C-17-010 | IEC 61508의 off-line 지원 도구는 T1, T2, T3로 나뉘고 (예: 편집기, coverage 측정, 최적화 compiler), T3에는 명세에 맞는다는 증거가 필요하며, 새 판마다 qualification한다 | Conrad, Munier, Rauch, Qualifying Software Tools According to ISO 26262 (2010경), 3쪽 https://fr.mathworks.com/content/dam/mathworks/tag-team/Objects/m/61793_CMR10-16.pdf (IEC 61508 2판 초안 기준). El-Sayed (UL), IEC 61508 Why Tool Qualification (2024-11), 10-11쪽 https://61508.org/wp-content/uploads/2024/11/09B-IEC-61508-Why-tool-qualification_V2_cut.pdf (2판 기준). AbsInt, Relation to safety standards (연도 미표기) https://www.absint.com/qualification/iec.htm (판 표기 없음) | 2차 (IEC 61508, 회사 글 셋) | 2026-11-23 |
| C-17-011 | MISRA Compliance에서 compiler는 linker, library manager, 실행 파일 형식 변환 도구를 포함한다 | misra-compliance-2020, 12쪽 | 1차 | 2026-11-23 |
| C-17-012 | 공급자에게서 확신을 얻기 어려우면 책임이 개발자에게 있다. 확신을 얻는 길 셋. validation test는 제품과 같은 compiler option, linker option, library 판으로 해야 한다 ("must") | misra-compliance-2020, 13쪽 | 1차 | 2026-11-23 |
| C-17-013 | 알려진 결함의 목록 (공급자 또는 자체). 더 공격적인 최적화는 compiler 결함이 드러날 위험을 높일 수 있다 ("may") | misra-compliance-2020, 14쪽 | 1차 | 2026-11-23 |
| C-17-014 | compiler를 고를 때 결함 목록, 최적화를 끄는 선택, runtime library의 source를 묻는다 | nasa-gb-8719-13, 235쪽 | 1차 | 2026-11-23 |
| C-17-015 | Csmith로 3년 동안 알려지지 않은 결함 325개 넘게 보고. 시험한 모든 compiler가 조용히 틀린 코드를 만들기도 했다. GCC의 한 결함은 모든 최적화 수준에서 틀린 값을 냈다 (Figure 1) | Yang, Chen, Eide, Regehr, Finding and Understanding Bugs in C Compilers (PLDI 2011), 1쪽 https://www-old.cs.utah.edu/~regehr/papers/pldi11-preprint.pdf | 1차 (논문) | 2026-11-23 |
| C-17-016 | CompCert의 증명되지 않은 부분에서 틀린 코드를 만드는 결함을 찾았다 | 같은 논문, 2쪽 | 1차 (논문) | 2026-11-23 |
| C-17-017 | 정의되지 않은 동작에 기대는 코드를 최적화가 지워 버리고, 결과가 잘못된 동작부터 빠진 보안 검사까지 이른다 | Wang, Zeldovich, Kaashoek, Solar-Lezama, Towards Optimization-Safe Systems (SOSP 2013), 1쪽 https://pdos.csail.mit.edu/papers/stack%3Asosp13.pdf | 1차 (논문) | 2026-11-23 |
| C-17-018 | probe를 넣자 compiler가 A, B의 호출 순서를 바꾼 예. 감시 코드가 오류를 숨기거나 넣지 않음을 보이는 것이 필수이고 보통 같은 test로 견준다 | nasa-mcdc-tutorial, 59-60쪽, 56쪽 | 1차 (항공의 맥락) | 2026-11-23 |
| C-17-019 | 자동 생성은 사람의 번역 오류를 없애지만 도구의 오류는 남고, 안전 관련이면 옳은 번역을 확인해야 한다 | nasa-gb-8719-13, 238쪽 | 1차 | 2026-11-23 |
| C-17-020 | compiler도 object code에 오류를 낸다. 안전 관련이면 생성 코드도 손으로 쓴 코드와 같은 inspection, 분석, test를 받는 것이 좋다 ("should") | nasa-gb-8719-13, 240쪽 | 1차 | 2026-11-23 |
| C-17-021 | 자동 생성의 접근: 생성 도구의 V&V, 도구와 입력의 형상 관리, 생성 코드를 손으로 쓴 코드와 같은 과정으로 확인 (SWE-146) | nasa-std-8739-8b, 29쪽 | 1차 (NASA의 요구) | 2026-11-23 |
| C-17-022 | OTS는 사 온 것과 다시 쓰는 것을 함께 가리키고, SOUP라는 이름이 문제를 앞에 내세워 낫다. 문서의 부족, source가 없으면 어떤 안전 분석은 못 한다 | nasa-gb-8719-13, 271쪽 | 1차 | 2026-11-23 |
| C-17-023 | 꺼도 다시 compile하지 않으면 코드가 남는다 | nasa-gb-8719-13, 272쪽 | 1차 | 2026-11-23 |
| C-17-024 | dormant code를 찾으려면 source가 필요하다 | nasa-gb-8719-13, 278쪽 | 1차 | 2026-11-23 |
| C-17-025 | 잘 알려진 OS나 library도 오류가 없다고 가정하지 말라 | nasa-gb-8719-13, 273쪽 | 1차 | 2026-11-23 |
| C-17-026 | wrapper: 입력을 막거나 출력을 검사. 문서 밖의 출력은 빠져나가고, OTS만큼 커질 수 있다 | nasa-gb-8719-13, 276쪽 | 1차 | 2026-11-23 |
| C-17-027 | OTS의 안전에 확신을 주는 일은 아직 "black art"에 가깝다 | nasa-gb-8719-13, 280쪽 | 1차 | 2026-11-23 |
| C-17-028 | COTS, OSS, 다시 쓰는 component를 직접 개발한 것과 같은 수준으로 확인하고, 공급자의 결함을 주기적으로 평가한다 (SWE-027 e, f, SWE-211) | nasa-std-8739-8b, 20-21쪽, 40쪽 | 1차 (NASA의 요구) | 2026-11-23 |
| C-17-029 | adopted code의 출처. 영향을 간과하거나 무해하다고 가정해서는 안 된다 ("must never"). 두 물음은 같지 않고, 준수는 필요조건도 충분조건도 아니다 | misra-compliance-2020, 25쪽 | 1차 | 2026-11-23 |
| C-17-030 | binary로만 받으면 준수와 품질을 확인할 범위가 좁아진다 | misra-compliance-2020, 26쪽 | 1차 | 2026-11-23 |
| C-17-031 | 정렬 기능의 요구사항은 Ariane 4를 위한 것이고 Ariane 5에는 해당하지 않았으며, 공통성 때문에 남았다. 위원회는 "presumably" 바꾸지 않는 것이 현명하다는 생각 때문이라고 적는다 | ariane-501-report, PDF 10쪽 (보고서 6쪽, OCR) | 1차 | 2026-11-23 |
| C-17-032 | 명세가 구현에서 나오는 운용의 제약을 밝히지 않았다. 한계의 선언이 모든 임무 중요 장치에 의무여야 한다 ("should be mandatory") | ariane-501-report, PDF 11쪽 (보고서 7쪽, OCR) | 1차 | 2026-11-23 |
| C-17-033 | 다시 쓰기의 가장 큰 문제는 심리적인 것이다. Ariane 5의 팀이 그렇게 생각했다 | nasa-gb-8719-13, 279쪽 | 1차 | 2026-11-23 |
| C-17-034 | proven in use 논증은 사용 이력이 있는 제품을 다른 환경에서 쓸 때 필요하다. 꼭 갖춰야 할 조건 (전형적인 환경, 비슷한 부품, 결함을 고친 부품은 보통 다른 부품, 모든 고장과 사용 시간의 기록). Ariane 4의 예에서 환경이 바뀌면 논증이 무효가 된다 | Schabe, Braband, Basic requirements for proven-in-use arguments (arXiv:1511.01839, 2015), 1쪽, 6쪽, 7쪽 https://arxiv.org/pdf/1511.01839 | 1차 (논문. Ariane의 서술은 논문의 해석) | 2026-11-23 |
| C-17-035 | IEC 61508의 proven in use는 하드웨어의 무작위 고장률을 위한 것이고 체계적 능력의 요구를 대신하지 않는다 | Intertek, Exploring the IEC 61508 Proven-In-Use Concept (2026-01-22) https://www.intertek.com/blog/2026/01-22-exploring-the-iec-61508-proven-in-use-concept/ | 2차 (IEC 61508, 판 표기 없음, 회사 글 하나. 원고에서 Intertek의 말로 적었다) | 2026-11-23 |
| C-17-036 | ISO 26262에 proven in use 논증의 절이 있다 (기준의 수치는 원고에 쓰지 않았다) | Schildbach, On the Application of ISO 26262 in Control Design for Automated Vehicles (arXiv:1804.04349, 2018), 6쪽 https://arxiv.org/pdf/1804.04349 | 2차 (ISO 26262, 판 표기 없음, 하나뿐. 원고에 "이 문서 하나로만 확인했다"를 붙였다) | 2026-11-23 |
| C-17-037 | SEooC는 맥락을 가정해 개발하고, 통합할 때 가정을 확인하며, 맞지 않으면 영향 분석을 한다. ISO 26262 Part 10이 SEooC의 안내를 담는다 | Embitel, What is Safety Element out of Context (SEooC) ... (2019-08-27) https://www.embitel.com/blog/embedded-blog/what-is-safety-element-out-of-context-seooc-in-automotive-functional-safety (판 표기 없음). Guo (Renesas), Functional Safety Support for Automotive (3) (2021-10-04) https://www.renesas.com/en/blogs/renesas-functional-safety-support-automotive-3-applying-iso-26262-standard-seooc-software (ISO 26262:2018 기준) | 2차 (회사 글 둘) | 2026-11-23 |
| C-17-038 | MCAL과 OS가 SEooC 소프트웨어의 흔한 예이고, 가정을 모두 확인하는 데 시간과 지식이 든다 | Guo (Renesas, 2021), 본문 | 2차 (ISO 26262:2018, 원고에서 Renesas의 말로 적었다) | 2026-11-23 |
| C-17-039 | AUTOSAR 명세는 SEooC를 정의하지 않는다 | autosar-safety-measures, 46쪽 | 1차 | 2026-11-23 |
| C-17-040 | 안전 관련 코드와 같은 platform의 OTS는 영향을 줄 수 없음을 분석으로 확인해야 한다 | nasa-gb-8719-13, 272-273쪽 | 1차 | 2026-11-23 |
| C-17-041 | OSS를 COTS와 함께 다루고, 사용 조건에 GNU GPL 같은 재배포 조건을 포함한다 | nasa-std-8739-8b, 20-21쪽 (SWE-027 c) | 1차 (NASA의 요구) | 2026-11-23 |
| C-17-042 | IV&V는 프로젝트가 쓰는 open source를 모두 찾았는지, 보안 위험을 찾고 줄였는지 확인한다 | nasa-std-8739-8b, 54쪽 (4.4.2.34) | 1차 (NASA의 요구) | 2026-11-23 |
| C-EX-029 | 예제의 도구 목록, 어느 도구도 qualification되지 않음, 결함을 넣는 것은 compiler 하나, 다른 compiler (GCC)와 `make variants`로 확인, 실제로 있었던 일 일곱 가운데 넷은 검토자가 결함을 넣거나 빼서 드러남, 하지 않은 것, 밖에서 온 소프트웨어 (표준 헤더 셋, library 함수 호출 없음, 시작 코드와 runtime) | `example/drive-torque/docs/tools.md` 1-5절. 헤더는 `src/`의 `#include`로 확인 | 예제 | 2026-11-23 |
