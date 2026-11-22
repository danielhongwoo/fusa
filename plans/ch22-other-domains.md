# 22장. 그 밖의 분야의 소프트웨어 안전 규격 - 장 계획

원고: [chapters/ch22-other-domains.md](../chapters/ch22-other-domains.md)

| 항목 | 내용 |
|---|---|
| Part | V. 넓히기 |
| 쓰는 단계 | 단계 3 (넓히기) |
| 상태 | 미착수 |

## 핵심 질문

같은 문제를 다른 분야는 어떻게 다르게 푸는가?

## 다룰 내용

- 항공: DO-178C (objective 기반, DAL)
- 철도: EN 50716
- 의료기기: IEC 62304, ISO 14971
- 공정: IEC 61511
- 비교 관점: 등급을 정하는 법, 방법 지정 대 목표 제시, independence 요구, tool qualification

## 검토에서 더한 항목 (2026-11-22)

괄호 안은 지적 번호이고, 검토 기록은 `reviews/2026-11-22-plan/`에 있다. 규격의 내용에 관한 항목은 쓰기 전에 확인한다 (RULES.md 5절).

- 비교표를 중심으로 쓴다 (E-14)
- IEC 62304 2판에서 달라지는 점 (F-18)
- 기계 분야는 20장에서 다뤘으므로 표의 한 열로만 둔다

## 예제 산출물

자동차, 로봇, 드론을 포함한 분야별 비교표

## 관련 규격과 자료

쓰는 시점에 정한다

받은 문서: nhtsa-safety-standards-assessment, faa-ac-20-115d

## 근거 위치 (2026-11-22)

받은 문서에서 이 장을 뒷받침하는 곳이다. 쪽은 PDF 파일의 몇 번째 쪽인지다. 에이전트가 문서를 읽어 뽑은 것이므로, 원고에 쓰기 전에 그 쪽을 직접 읽어 확인한다 (RULES.md 5.2절).

| 문서 | 절 | 쪽 | 뒷받침하는 내용 |
|---|---|---|---|
| `nhtsa-safety-standards-assessment` | 2.2 MIL-STD-882E / 2.3 DO-178C / 3.1 Type of Standard / 3.6 Risk Assessment / 3.8 Software Safety | 15-16, 19-21, 26-32 | 항공(DO-178C), 군용(MIL-STD-882E), 자동차 규격을 같은 11개 차원으로 비교 (등급, 방법 지정 대 목표 제시 포함) |
| `faa-ac-20-115d` | 5-6 Using DO-178B/C, 9 Legacy software, 10 Tool Qualification | 2-12 | DO-178C 적용 방식, tool qualification, 재사용 (항공 규제 문서) |
| `nasa-mcdc-tutorial` | 1.1 Scope / 2.1 Verification Process (DO-178B level A의 MC/DC 목표) | 7-10 | DO-178B 소프트웨어 level별 구조 coverage 요구의 한 항목 |
| `faa-ac-20-193` | 2.2-2.3 Applicability / 5.8 Applicability of the MCP objectives according to IDALs | 1-2, 13 | 항공 IDAL 등급에 따라 multicore 목표가 달라지는 방식 |
| `koopman-toyota-ua` | slide 22 (Safety Integrity Level Approaches Are Common) | 22 | 분야별 등급 체계 비교 표 (철도 EN 50128, 의료 FDA, 항공 DO-178B, 군용 MIL-STD-882D 등, 2014 자료) |
| `iec-61508-overview-slides` | slides 5-7 (examples, sector standards) | 5-7 | 기계류(IEC 62061), 공정(IEC 61511), 원자력(IEC 61513), 전력 구동(IEC 61800-5-2)이 IEC 61508 계열이라는 점 |
| `nasa-gb-8719-13` | 3.1-3.2 Software Safety Planning, 4.4 Tailoring | 35-46, 87 | NASA의 위험 기반 노력 수준 결정 (우주 분야 예) |

### 받은 문서에 근거가 없는 항목

이 항목은 다른 공개 문서를 찾거나, `(2차 자료)`로 밝히거나, 쓰지 않는다.

- EN 50716, IEC 62304 2판, ISO 14971, IEC 61511 상세 - 이름과 표 한 줄 수준
- 철도, 의료, 공정의 독립성 요구, tool qualification 비교 - 없음 (koopman p22 한 표만)
