# 4장. 규격 지도와 규격 읽는 법 - 장 계획

원고: [chapters/ch04-standards-map.md](../chapters/ch04-standards-map.md)

| 항목 | 내용 |
|---|---|
| Part | I. 사고방식과 기본 개념 |
| 쓰는 단계 | 단계 2 (살 붙이기) |
| 상태 | 미착수 |

## 핵심 질문

규격은 왜 이렇게 많고 서로 어떤 관계인가? 규격 문장은 어떻게 읽어야 하는가?

## 다룰 내용

- IEC 61508과 분야별 규격: ISO 26262, IEC 61511, IEC 62061, ISO 13849, EN 50716, IEC 62304
- 별도 계보인 항공: DO-178C
- 로봇: 기계류 안전 규격 (ISO 12100, ISO 13849-1) 위에 로봇 규격이 얹히는 구조
- 드론: 규격보다 규제와 운용 위험 평가 (SORA)가 중심인 구조
- 규격의 구조: part, clause, normative와 informative, shall과 should, work product, 방법 표의 추천 등급
- 규격이 정해 주는 것과 개발자 판단에 맡기는 것
- compliance, assessment, certification의 차이

## 검토에서 더한 항목 (2026-11-22)

괄호 안은 지적 번호이고, 검토 기록은 `reviews/2026-11-22-plan/`에 있다. 규격의 내용에 관한 항목은 쓰기 전에 확인한다 (RULES.md 5절).

- 규격 지도를 세 묶음으로 그린다: IEC 61508을 분야에 맞춘 규격, IEC 61508을 참조하는 규격, 계보가 다른 규격 (F-10)
- Part마다 요구사항 (normative)인지 해설 (informative)인지 표로 보인다 (F-18)

## 책의 성격에 따른 조정 (2026-11-22)

이 책은 ISO 26262:2018의 원문을 보지 않고 쓴다 (RULES.md 5.6절).

- 규격의 구성과 서로의 관계는 받은 문서 (iec-61508-overview-slides, nhtsa-safety-standards-assessment)를 근거로 소개한다.
- ISO 26262는 Part의 구성과, 미리보기로 확인한 조항 제목 수준으로 소개한다.

## 예제 산출물

부록 B (규격 구조 대응표)의 틀

## 관련 규격과 자료

IEC 61508-1; ISO 26262-1, -2, -10

받은 문서: iec-61508-overview-slides, nhtsa-safety-standards-assessment (ISO 26262, MIL-STD-882E, DO-178C 등을 견준 미국 정부 보고서)

## 근거 위치 (2026-11-22)

받은 문서에서 이 장을 뒷받침하는 곳이다. 쪽은 PDF 파일의 몇 번째 쪽인지다. 에이전트가 문서를 읽어 뽑은 것이므로, 원고에 쓰기 전에 그 쪽을 직접 읽어 확인한다 (RULES.md 5.2절).

| 문서 | 절 | 쪽 | 뒷받침하는 내용 |
|---|---|---|---|
| `iec-61508-overview-slides` | slides 4-7 (Objectives, Typical examples, Standalone & sector/product standards) | 4-7 | IEC 61508이 기본 규격이고 IEC 62061, 61511, 61513, 61800-5-2가 분야별 구현이라는 구조 |
| `iec-61508-overview-slides` | slides 21-22 (Safety Lifecycle, Compliance to IEC 61508) | 21-22 | 규격의 구성: 기능 안전 관리, 3개 lifecycle, 기술 요구, assurance 측정 |
| `nhtsa-safety-standards-assessment` | 2 Description of Relevant Safety Standards (2.1-2.6) | 14-19 | ISO 26262가 IEC 61508을 도로 차량에 맞춘 규격이고 10개 Part 중 2-7이 핵심이라는 구성 (2011 판), MIL-STD-882E, DO-178C, AUTOSAR, MISRA C 소개 |
| `nhtsa-safety-standards-assessment` | 3.1 Type of Standard (3.1.1-3.1.4) | 19-21 | 규격의 유형: 프로세스 규정, 방법 나열, 성능 기반, 설계 규정 (규격이 정해 주는 것과 판단에 맡기는 것) |
| `nhtsa-safety-standards-assessment` | 3.11 Review, Audit, and Certification | 33-34 | compliance와 approval/certification의 차이 (DO-178C의 approval, ISO 26262의 safety case) |
| `gsn-standard-v3` | Introduction to the Standard (Part 0 informative / Part 1 normative / Part 2 informative) | 9 | normative와 informative 구분의 실제 예 |
| `faa-ac-20-115d` | 6. Using ED-12C/DO-178C / 8. Guidance applicable to ED-12B or ED-12C | 3-5 | 규제 기관이 DO-178C를 "acceptable means of compliance"로 인정하는 구조 (항공 계보) |

### 받은 문서에 근거가 없는 항목

이 항목은 다른 공개 문서를 찾거나, `(2차 자료)`로 밝히거나, 쓰지 않는다.

- EN 50716, IEC 61511, IEC 62061, ISO 13849, IEC 62304의 구조 - 슬라이드가 이름만 언급 (IEC 62304는 misra 문서에 이름만)
- Part별 normative/informative 표, shall/should 읽는 법 - ISO 26262 구조 원문이 없다 (nhtsa-std p14는 Part 구성만)
- 로봇 규격의 계층 (ISO 12100, ISO 13849-1)과 SORA의 구조는 20장과 21장의 근거 위치를 쓴다 (`ifa-report-2-2017e`, `sora-2-5-main-body`). 로봇 전용 규격 (ISO 10218 등)은 받은 문서가 없다
