# 20장. 로봇: 기계류 안전의 방식 - 장 계획

원고: [chapters/ch20-robots.md](../chapters/ch20-robots.md)

| 항목 | 내용 |
|---|---|
| Part | V. 넓히기 |
| 쓰는 단계 | 단계 3 (넓히기) |
| 상태 | 미착수 |

## 핵심 질문

사람 옆에서 움직이는 기계의 안전은 자동차와 무엇이 같고 무엇이 다른가?

## 다룰 내용

- 기계류 안전의 틀: ISO 12100 risk assessment와 3단계 위험 감소 (본질적 안전 설계, 보호 장치, 사용 정보)
- safety function과 required performance level. PL과 SIL의 관계
- ISO 13849-1의 구조 요구: Category, 부품 신뢰도, diagnostic coverage, common cause failure
- ISO 13849-1의 소프트웨어 요구: embedded software와 application software의 구분, ISO 26262-6과의 깊이 차이
- 로봇 규격이 정하는 safety function: protective stop, emergency stop, 속도와 위치 제한, speed and separation monitoring, power and force limiting
- 로봇 종류별 규격: 산업용 로봇 (ISO 10218-1, -2), 서비스 로봇 (ISO 13482), 이동 로봇 (ISO 3691-4)
- 흔한 구조: 안전 등급을 받은 controller와 일반 소프트웨어 (예: ROS 2)의 분리
- 정지가 safe state인 시스템의 설계와 그 한계

## 검토에서 더한 항목 (2026-11-22)

괄호 안은 지적 번호이고, 검토 기록은 `reviews/2026-11-22-plan/`에 있다. 규격의 내용에 관한 항목은 쓰기 전에 확인한다 (RULES.md 5절).

- 안전 기능은 인증된 보호 장치 (safety laser scanner)와 safety controller가 수행한다. 일반 소프트웨어 (예: ROS 2)는 안전 장치가 아니다 (E-21)
- ISO 13849-1:2023의 소프트웨어 요구: embedded software와 application software, 제한된 언어와 범용 언어의 구분 (F-21)
- risk graph로 요구 등급을 정하는 법 (F-21)
- ISO 10218:2025에서 달라진 점은 1쪽 상자로 쓴다. 협동 작업은 표 한 칸으로 줄인다 (F-20, E-22)
- EU Machinery Regulation 2023/1230 (2027-01-20 적용) (F-19)
- 정지에도 거리, 시간, 짐, 경사가 걸린다는 점 (F-09)

## 예제 산출물

자율 이동 로봇의 속도에 따른 보호 영역 전환과 정지: 안전 기능의 정의, risk graph로 정한 요구 등급, Category 구조, 정지 거리 예산 (응답 시간 + 제동 거리 <= 감지 거리), 일반 소프트웨어와 safety controller의 경계 그림. 관통 예제와의 비교표

## 관련 규격과 자료

ISO 12100; ISO 13849-1, -2; IEC 62061; ISO 10218-1, -2; ISO 13482; ISO 3691-4

받은 문서: ifa-report-2-2017e (ISO 13849-1의 2015년 판 기준)
