# 1장. 소프트웨어가 사람을 다치게 할 때 - 장 계획

원고: [chapters/ch01-accidents.md](../chapters/ch01-accidents.md)

| 항목 | 내용 |
|---|---|
| Part | I. 사고방식과 기본 개념 |
| 쓰는 단계 | 단계 2 (살 붙이기) |
| 상태 | 미착수 |

## 핵심 질문

소프트웨어는 닳지도 부러지지도 않는데 어떻게 사고를 일으키는가?

## 다룰 내용

- 사례: Therac-25 방사선 치료기, Ariane 5 Flight 501, Toyota unintended acceleration, Boeing 737 MAX MCAS
- 사례에서 반복되는 패턴: 요구사항의 결함, 검증 없는 재사용, 단일 입력에 대한 의존, 사라진 hardware interlock, 조직 요인
- "버그 없는 코드"와 "안전한 시스템"이 다른 이유

## 검토에서 더한 항목 (2026-11-22)

괄호 안은 지적 번호이고, 검토 기록은 `reviews/2026-11-22-plan/`에 있다. 규격의 내용에 관한 항목은 쓰기 전에 확인한다 (RULES.md 5절).

- 사례의 깊이를 나눈다: Toyota와 737 MAX는 깊게, Therac-25와 Ariane 5는 짧게 (E-14)
- 사례마다 공식 조사의 결론과 다툼이 있는 부분을 나눠 적는다 (F-17)
- 장 끝에서 안전 장치가 없는 토크 제어기 (약 100줄)를 실행해, 센서 값이 고착되면 차가 계속 가속하는 그래프를 보인다 (E-04)

## 예제 산출물

관통 예제 소개

## 관련 규격과 자료

각 사고의 조사 보고서 원문

받은 문서: ariane-501-report, b737max-jatr, b737max-ntsb-asr1901, b737max-knkt-jt610, b737max-house-report, koopman-toyota-ua

받은 문서 (추가): nasa-toyota-ua-report (NASA의 Toyota 조사 보고서, 2011)

## 근거 위치 (2026-11-22)

받은 문서에서 이 장을 뒷받침하는 곳이다. 쪽은 PDF 파일의 몇 번째 쪽인지다. 에이전트가 문서를 읽어 뽑은 것이므로, 원고에 쓰기 전에 그 쪽을 직접 읽어 확인한다 (RULES.md 5.2절).

| 문서 | 절 | 쪽 | 뒷받침하는 내용 |
|---|---|---|---|
| `ariane-501-report` | 2.1 Chain of technical events / 2.2 Comments on the failure scenario | 7-10 | 정렬 함수의 64비트 float -> 16비트 정수 변환에서 operand error, 보호되지 않은 변환, Ariane 4 요구의 재사용. 스캔본(텍스트 층 없음)이라 OCR로 확인. 보고서 자체 쪽 = PDF 쪽 - 4 |
| `ariane-501-report` | 2.3 The testing and qualification procedures / 4 Recommendations | 11-13, 17-18 | SRI를 loop에 넣지 않은 system test, 재사용 장비의 가정을 새 환경에서 검증하지 않음, 가정 목록 검토 권고 |
| `nasa-toyota-ua-report` | 4.0 Executive Summary / 7.1 Findings (F-1..F-6) / 7.2 Observations | 13-17, 170-173 | NASA 조사의 결론: 재현 가능한 대형 throttle 열림 UA를 찾지 못함, 다중 fail-safe 존재, pedal 이중 고장 시나리오. 공식 조사의 결론 부분 |
| `nasa-toyota-ua-report` | 6.7.3 Software Study and Results (6.7.3.1-6.7.3.5) | 147-151 | 소프트웨어 검토 범위: 정적 분석 tool, SPIN model checking, 코딩 결함, task 간섭, 불충분한 fault protection 4분류 |
| `koopman-toyota-ua` | slides 9-16 (NASA Conclusions .. US Criminal Investigation) | 9-16 | NASA 조사의 한계 주장, Bookout 재판의 결과, 형사 조사: 공식 조사와 재판의 결론이 갈리는 부분 (원고 측 전문가의 견해임을 밝혀야 함) |
| `koopman-toyota-ua` | slides 17-20, 31-47 | 17-20, 31-47 | 테스트만으로 안전을 보일 수 없다는 주장, 단일 고장점, 전역 변수, 동시성, 재귀, watchdog, 안전 문화 지적 (전문가 증언 자료) |
| `b737max-knkt-jt610` | 1.6.5 Aircraft System information (Speed Trim System/MCAS) / 2.5.1.2 FHA for MCAS Related Failures / 3.2 Contributing Factors | 50-52, 191-196, 217-218 | MCAS가 AOA 센서 하나에 의존, FHA의 조종사 반응 가정, 기여 요인 목록 (인도네시아 KNKT 최종 보고서) |
| `b737max-jatr` | R6 Holistic, integrated aircraft-level approach (F6.1-A..F6.9) / Executive Summary | 4, 50-54 | 조종사 조치를 주된 완화책으로 삼음, 센서 voting 없음, SSA 분절과 재사용, 규정 준수가 곧 안전은 아님 |

### 받은 문서에 근거가 없는 항목

이 항목은 다른 공개 문서를 찾거나, `(2차 자료)`로 밝히거나, 쓰지 않는다.

- Therac-25 사고 서술 - 받은 문서에 사례 보고서가 없다 (nasa-gb-8719-13 p37에 한 문장 언급뿐)
- 장 끝의 센서 고착 토크 제어기 실행 예 - 문서 근거가 필요한 내용이 아니라 저자의 코드이나, 원리 근거는 nasa-toyota 6.6.2 (pedal 고장)로만 간접 뒷받침
