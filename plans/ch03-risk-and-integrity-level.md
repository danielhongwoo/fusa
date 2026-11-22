# 3장. Risk와 integrity level - 장 계획

원고: [chapters/ch03-risk-and-integrity-level.md](../chapters/ch03-risk-and-integrity-level.md)

| 항목 | 내용 |
|---|---|
| Part | I. 사고방식과 기본 개념 |
| 쓰는 단계 | 단계 1 (뼈대). 단계 2에서 깊게 고친다 |
| 상태 | 미착수 |

## 핵심 질문

얼마나 안전해야 충분한가? 그 답이 어떻게 개발 방법의 엄격함으로 바뀌는가?

## 다룰 내용

- risk는 severity와 발생 가능성의 조합
- tolerable risk, ALARP, risk reduction, safety function
- SIL, ASIL, PL, SAIL, DAL: 분야마다 다른 등급 체계
- 하드웨어에는 수치 목표를, 소프트웨어에는 방법과 엄격함을 요구하는 이유
- integrity level에 대한 흔한 오해
- 로봇과 드론에서는 (단계 3에서 채운다)

## 검토에서 더한 항목 (2026-11-22)

괄호 안은 지적 번호이고, 검토 기록은 `reviews/2026-11-22-plan/`에 있다. 규격의 내용에 관한 항목은 쓰기 전에 확인한다 (RULES.md 5절).

- demand mode (low demand, high demand, continuous)와 PFD, PFH가 둘인 이유 (F-13)
- 등급은 제품이 아니라 safety function과 요구사항의 속성이라는 점. QM의 뜻 (F-13)
- systematic capability (F-13)
- 흔한 오해: SAIL을 제품의 등급으로 읽는 것 (F-07)

## 책의 성격에 따른 조정 (2026-11-22)

이 책은 ISO 26262:2018의 원문을 보지 않고 쓴다 (RULES.md 5.6절).

- 등급이 높을수록 개발 방법이 엄격해지는 까닭을 원리로 설명한다. 등급별 방법 표의 내용은 싣지 않는다.

## 예제 산출물

없음 (6장에서 실제 등급을 정한다)

## 관련 규격과 자료

IEC 61508-1, -5; ISO 26262-3

받은 문서: iec-61508-overview-slides

## 근거 위치 (2026-11-22)

받은 문서에서 이 장을 뒷받침하는 곳이다. 쪽은 PDF 파일의 몇 번째 쪽인지다. 에이전트가 문서를 읽어 뽑은 것이므로, 원고에 쓰기 전에 그 쪽을 직접 읽어 확인한다 (RULES.md 5.2절).

| 문서 | 절 | 쪽 | 뒷받침하는 내용 |
|---|---|---|---|
| `iec-61508-overview-slides` | slides 9-10 (Safety Integrity, Safety Function: Functionality & Safety Integrity) | 9-10 | safety function의 기능과 integrity를 나눔, integrity는 random과 systematic failure를 모두 포함 |
| `iec-61508-overview-slides` | slides 11, 14-17 (Risk, SIL, SILs & Risk Reduction, Target Failure Measure) | 11, 14-17 | risk = 빈도 x 심각도, tolerable risk, SIL은 safety function의 속성 (제품이 아님), SIL별 risk reduction 범위 |
| `koopman-toyota-ua` | slides 21-23 (SIL Approach, SIL Approaches Are Common, Accepted Practice) | 21-23 | 분야마다 다른 등급 체계 비교표 (SIL, ASIL, DO-178B level 등)와 "등급 -> 개발 방법의 엄격함" 흐름 |
| `nasa-gb-8719-13` | 3.1.2 Determine Software Safety-Criticality (3.1.2.1 Control Categories, 3.1.2.2 Risk Matrix) | 37-41 | 소프트웨어의 통제 범주와 risk matrix로 노력 수준을 정하는 NASA 방식 (등급 체계의 다른 예) |
| `nasa-gb-8719-13` | 2.3.2 Risk Levels | 27-29 | 위험 수준 정의와 hazard 제거/통제 정책 |
| `nhtsa-safety-standards-assessment` | 3.6 Risk Assessment Approach (3.6.1-3.6.4) | 26-29 | ISO 26262 (ISO 26262:2011 기준)의 severity/exposure/controllability, MIL-STD-882E의 소프트웨어 통제 범주, 소프트웨어에 ASIL을 주는 방식과 한계 |
| `nhtsa-etc-ev-fsa` | 5.1 ASIL Assessment Steps / 5.2 ASIL Assignment for Each Hazard (목차 수준) | 52-57 | ASIL이 hazard별로 정해지고 가장 높은 값을 택하는 예 (ISO 26262:2011 기준) |
| `ifa-report-2-2017e` | 3 Generic standards concerning the functional safety of machinery control systems | 15-16 | SIL과 PL이 모두 PFHD 구간으로 정의되는 등급이고 PL a는 SIL과 대응 없음. low demand(PFDavg)와 high demand/continuous(PFHD)의 구분과 기계류에서 후자만 쓰인다는 점(3장의 demand mode 항목) |
| `ifa-report-2-2017e` | 5.2.1 Risk estimation / 5.2.2 Risk evaluation | 27 | risk를 피해의 심각도와 발생 확률(노출, 위험 사건, 회피 가능성)로 보는 정의, 위험 평가의 판단 기준(가능한 한 낮은 수준까지 감소) |
| `ifa-report-2-2017e` | 5.2 Risk reduction strategy (Fig 5.3) | 27-28 | 허용 위험, 필요한 최소 위험 감소, 실제 위험 감소, 잔여 위험의 관계를 보인 그림 (tolerable risk, risk reduction, safety function 항목) |
| `ifa-report-2-2017e` | 4.1 Identification of safety functions and their properties | 20 | 같은 하드웨어가 여러 safety function에 쓰이고 safety function마다 요구 위험 감소가 다르다는 서술 (등급이 safety function의 속성이라는 항목) |
| `ifa-report-2-2017e` | 6.3.6 Structure of the normative requirements | 67-68 | 소프트웨어는 체계적 원인의 고장이라 방법의 엄격함을 PLr에 맞춰 키운다는 서술 (하드웨어는 수치 목표, 소프트웨어는 방법이라는 항목) |
| `sora-2-5-main-body` | 2.1 Risk in the context of SORA | 21 | risk를 발생 빈도와 심각도의 조합으로 정의 |
| `sora-2-5-main-body` | 4.7 Step #7 - Specific Assurance and Integrity Levels (SAIL) determination (4.7.1, 4.7.4) | 47-48 | SAIL이 최종 GRC와 잔여 ARC에서 정해지는 운용의 등급이고 정량값이 아니라 OSO robustness 수준을 가리킨다는 서술 (SAIL을 제품의 등급으로 읽는 오해 항목) |
| `sora-2-5-main-body` | 2.2 Semantic model in the context of SORA, (c) | 22 | SAIL이 높을수록 허용 loss of control 비율이 낮아진다는 서술 |
| `easa-moc-light-uas-high-risk-2510` | 8.1 Safety Objectives per SAIL and failure condition classification (Table 1) | 9 | SAIL V, VI에서 failure condition 심각도(major, hazardous, catastrophic)별 확률 목표와 FDAL(D, C, B)의 대응. DAL이 safety 평가에서 정해지는 등급이라는 근거 |
| `easa-moc-light-uas-2510` | Definitions (c) Development Assurance Level | 5 | DAL이 개발 보증 작업의 엄격함 수준이고 system safety assessment가 정한다는 정의 설명 |
| `faa-ac-20-115d` | 9. Modifying and Re-using Software ... (9.b(2)) | 8 | system safety process가 failure condition의 심각도에 따라 최소 개발 보증 수준(소프트웨어 level)을 정한다는 서술 |

### 받은 문서에 근거가 없는 항목

이 항목은 다른 공개 문서를 찾거나, `(2차 자료)`로 밝히거나, 쓰지 않는다.

- ALARP, tolerable risk의 상세 - 슬라이드는 tolerable risk 정의만 있고 ALARP 단어가 어느 문서에도 없다
- demand mode(low/high/continuous), PFD, PFH, systematic capability - 받은 문서 어디에도 없다
- ISO 26262의 QM 의미 - nhtsa-etc가 ASIL QM을 쓰는 예만 있고 설명은 없다
- ALARP 등 tolerable risk의 정식 기준 - 받은 문서에 ALARP를 다룬 곳이 없다. IFA는 허용 위험과 최소 위험 감소의 관계를 그림(p28)으로만 보이고, iec-61508-overview-slides는 이번 범위 밖이라 보지 않았다
- systematic capability - 받은 로봇, 드론 문서는 정의를 주지 않는다. IFA p72에 IEC 61508-2의 "required systematic capability"를 언급하는 한 구절만 있다
- PFD와 PFH가 둘인 이유의 자세한 설명 - IFA p15는 low demand와 high demand 구분과 기계류에서 후자가 쓰인다는 점만 짧게 적는다
