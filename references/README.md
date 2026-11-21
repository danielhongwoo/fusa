# 참고 문서

책을 쓰는 데 쓰는 문서를 실제로 볼 수 있는지에 따라 나눈 목록이다. 주소와 상태는 2026-11-22에 확인했다.

- 등급의 뜻과 문장에 근거를 표시하는 방법은 [RULES.md](../RULES.md) 5절에 있다.
- 규격의 정식 명칭과 판은 [standards.md](standards.md)에 있다.
- 받은 문서 파일은 git에 넣지 않는다. `sh references/fetch.sh`로 다시 받을 수 있다.
- 받은 파일의 SHA-256 값은 [SHA256SUMS](SHA256SUMS)에 있다. `references/`에서 `shasum -a 256 -c SHA256SUMS`로 확인한다.

## 요약

| 등급 | 뜻 | 수 | 해당 문서 |
|---|---|---|---|
| A | 무료로 받을 수 있다 | 24개 받음, 7개는 직접 받아야 함 | 사고 조사 보고서, NASA와 FAA와 EASA의 문서, SORA, AUTOSAR 공개 규격, 저자가 공개한 책과 논문 |
| B | 온라인에서 볼 수만 있다 | 8개 | ISO와 IEC의 미리보기, KS 열람, 공개 autopilot 문서 |
| C | 유료이거나 볼 수 없다 | 규격 대부분과 책 | ISO 26262, IEC 61508, 로봇 규격, 항공 규격, MISRA C |

가장 중요한 사실: 이 책의 중심 근거인 ISO 26262와 IEC 61508의 본문은 C 등급이다. 받을 수 있는 것은 주변 자료이고, 규격 본문의 내용은 원문을 구하기 전에는 확정할 수 없다.

## A. 받은 문서

폴더 이름이 문서의 id다. 크기 단위는 MB다.

### 사고 사례

| id | 문서 | 올린 곳 | 쓰는 장 | 쪽 | 크기 |
|---|---|---|---|---|---|
| ariane-501-report | Ariane 501 Inquiry Board Report (1996-07-19) | ESA | 1 | 60 | 2.2 |
| b737max-jatr | Joint Authorities Technical Review, Boeing 737 MAX Flight Control System (2019-10) | FAA | 1 | 71 | 0.6 |
| b737max-ntsb-asr1901 | NTSB Safety Recommendation Report ASR-19-01 | NTSB | 1 | 13 | 0.1 |
| b737max-knkt-jt610 | KNKT 최종 보고서, Lion Air JT610 | KNKT (인도네시아) | 1 | 322 | 12.9 |
| b737max-house-report | 미국 하원 교통인프라위원회 최종 보고서 (2020-09) | 미국 하원 | 1 | 245 | 3.5 |
| koopman-toyota-ua | Koopman, A Case Study of Toyota Unintended Acceleration and Software Safety (2014) | 저자의 CMU 페이지 | 1 | 55 | 5.9 |

### 개념과 분석 기법

| id | 문서 | 올린 곳 | 쓰는 장 | 쪽 | 크기 |
|---|---|---|---|---|---|
| avizienis-2004-taxonomy | Avizienis, Laprie, Randell, Landwehr, Basic Concepts and Taxonomy of Dependable and Secure Computing (2004) | 메릴랜드 대학 저장소 | 2 | 37 | 0.3 |
| stpa-handbook | Leveson, Thomas, STPA Handbook (2018) | MIT PSAS (저자 연구실) | 8 | 188 | 5.6 |
| gsn-standard-v3 | GSN Community Standard Version 3 (2021) | SCSC | 19 | 130 | 1.6 |
| iec-61508-overview-slides | IEC 61508 & Functional Safety (2022, 발표 자료) | IEC | 3, 4 | 24 | 1.2 |

### 소프트웨어 안전과 verification

| id | 문서 | 올린 곳 | 쓰는 장 | 쪽 | 크기 |
|---|---|---|---|---|---|
| nasa-gb-8719-13 | NASA Software Safety Guidebook, NASA-GB-8719.13 (2004) | NASA | 10-16 | 389 | 2.6 |
| nasa-mcdc-tutorial | Hayhurst 외, A Practical Tutorial on Modified Condition/Decision Coverage, NASA/TM-2001-210876 | NASA NTRS | 16 | 85 | 4.1 |
| misra-compliance-2020 | MISRA Compliance:2020 | MISRA | 13 | 39 | 0.7 |
| autosar-e2e-protocol | AUTOSAR E2E Protocol Specification (R25-11) | AUTOSAR | 12 | 314 | 3.5 |
| autosar-safety-measures | AUTOSAR Overview of Functional Safety Measures in AUTOSAR (R25-11) | AUTOSAR | 11, 12, 14 | 72 | 12.3 |
| faa-ac-20-115d | FAA AC 20-115D, Airborne Software Development Assurance Using EUROCAE ED-12( ) and RTCA DO-178( ) (2017) | FAA | 21, 22 | 15 | 0.5 |
| faa-ac-20-193 | FAA AC 20-193, Use of Multi-Core Processors (2024) | FAA | 14 | 18 | 0.7 |

### 로봇

| id | 문서 | 올린 곳 | 쓰는 장 | 쪽 | 크기 |
|---|---|---|---|---|---|
| ifa-report-2-2017e | IFA Report 2/2017e, Functional safety of machine controls - Application of EN ISO 13849 | DGUV IFA | 20 | 324 | 18.8 |

### 드론

| id | 문서 | 올린 곳 | 쓰는 장 | 쪽 | 크기 |
|---|---|---|---|---|---|
| sora-2-5-main-body | JARUS SORA 2.5 Main Body (JAR doc 25, 2024) | 체코 항공 당국의 사본 | 21 | 57 | 1.3 |
| easa-ed-2025-018-r-annex | Annex to ED Decision 2025/018/R (SORA 2.5를 EU 규정의 AMC와 GM으로 채택) | EASA | 21 | 204 | 3.4 |
| easa-ear-uas | Easy Access Rules for Unmanned Aircraft Systems (2026-06 개정) | EASA | 21 | 617 | 9.0 |
| easa-sc-light-uas-medium-risk | Special Condition Light-UAS Medium Risk, Issue 01 (2020) | EASA | 21 | 25 | 0.5 |
| easa-moc-light-uas-2510 | MoC Light-UAS.2510-01, Issue 1 (2024, SAIL IV) | EASA | 21 | 11 | 0.4 |
| easa-moc-light-uas-high-risk-2510 | MoC Light-UAS High Risk.2510-01 (2025, SAIL V와 VI) | EASA | 21 | 16 | 0.4 |

### 받은 문서를 쓸 때 주의할 점

- avizienis-2004-taxonomy: 학술지에 실린 판이 아니라 기술 보고서 (TR 2004-47) 판이다. 인용할 때 구분한다.
- ifa-report-2-2017e: EN ISO 13849-1의 2015년 판을 기준으로 쓴 보고서다. 책이 기준으로 삼는 2023년 판과 다르다. 2023년 판을 반영한 보고서 (IFA Report 1/2025)는 독일어판만 확인했다.
- sora-2-5-main-body: 발행 기관인 JARUS의 사이트가 아니라 체코 항공 당국의 사본이다. 크기는 JARUS 사이트의 파일과 같았다.
- easa-ear-uas: EASA가 만든 통합본이고 법적 효력이 없다. 법 조문을 인용할 때는 EUR-Lex의 원문을 쓴다.
- easa-moc-light-uas-2510과 easa-moc-light-uas-high-risk-2510: 번호가 같아 보이지만 다른 문서다. 앞의 것은 SAIL IV, 뒤의 것은 SAIL V와 VI에 쓴다.
- b737max-knkt-jt610: 파일 이름의 번호와 보고서 표지의 번호가 다르다는 보고가 있다. 인용할 때 표지의 번호를 확인한다.
- 재배포 조건: koopman-toyota-ua에는 CC BY 4.0 표시가 있고, nasa-mcdc-tutorial에는 공개 사용을 허용한다는 표시가 있다. 나머지는 조건을 찾지 못했으므로 재배포할 수 없다고 보고 다룬다.

## A. 무료지만 직접 받아야 하는 문서

자동으로 받을 수 없었다. 사람 확인 화면이나 등록 양식이 있는 곳은 우회하지 않았다.

| 문서 | 받는 곳 | 받지 못한 이유 |
|---|---|---|
| Leveson, Engineering a Safer World (MIT Press, open access) | https://mitpress.mit.edu/9780262533690/engineering-a-safer-world/ 의 open access 링크 | 사람 확인 화면 |
| Leveson, Turner, An Investigation of the Therac-25 Accidents (1993) | http://sunnyday.mit.edu/papers/therac.pdf (저자 페이지, 주소 미확인) | 연결되지 않음. 대신 볼 수 있는 곳은 B 목록에 있다 |
| MIL-STD-882E, Change 1 (2023) | https://assist.dla.mil 에서 검색 | 검색 화면을 거쳐야 함 |
| UK HSE, Reducing risks, protecting people (2001) | https://webarchive.nationalarchives.gov.uk/ukgwa/20230703113731/https:/www.hse.gov.uk/enforce/expert/r2p2.htm | 사람 확인 화면. HSE의 원래 페이지는 없어졌다 |
| SEI CERT C Coding Standard (2016 Edition) | https://www.sei.cmu.edu/forms/secure-coding-form/ | 이름과 이메일을 넣는 등록이 필요 |
| Standardized E-Gas Monitoring Concept | v4.0 (2007): https://downloads.regulations.gov/NHTSA-2014-0108-0021/attachment_1.pdf | 접근 거부. 아래 설명 참고 |
| JARUS SORA 2.5의 Annex A, B, E, F, H, I | jarus-rpas.org | 아래 설명 참고 |

### E-Gas monitoring concept에 대하여

관통 예제의 감시 구조는 이 문서에 바탕을 둔다. 그런데 확인한 결과는 다음과 같다.

- 최신으로 알려진 v6.0의 공식 배포처를 찾지 못했다. 문서 공유 사이트의 사본만 있었고, 그런 사본은 쓰지 않는다.
- v4.0 (2007-01-30)의 사본이 미국 NHTSA의 공개 문서철에 있다. 자동으로는 받지 못했다.
- 따라서 이 문서는 구할 때까지 C 등급으로 다룬다. 이 문서에 관한 문장은 모두 `(확인 필요)`이다.

### JARUS 사이트에 대하여

- 주소를 확인하던 중에 jarus-rpas.org가 예상하지 못한 서버로 연결되고 첫 페이지가 열리지 않는 것을 보았다.
- 그래서 그 도메인에서는 받지 않았다. 본문은 체코 항공 당국의 사본을 받았고, EU가 채택한 내용은 EASA의 문서로 받았다.
- 부록이 필요하면 사이트의 상태를 직접 확인한 뒤에 받는다.

## B. 온라인에서 볼 수만 있는 문서

| 문서 | 주소 | 볼 수 있는 범위 | 확인 |
|---|---|---|---|
| ISO Online Browsing Platform | https://www.iso.org/obp | ISO 규격의 서문, 소개, 범위, 인용 규격, 용어와 정의. 본문은 볼 수 없다 | ISO의 도움말로 확인. 이용 약관에 동의해야 들어갈 수 있어 직접 열어 보지는 않았다 |
| IEC webstore의 미리보기 | https://webstore.iec.ch | IEC 규격의 목차와 앞부분 | 직접 열어 보지 않았다 |
| e-나라표준인증의 KS 열람 | https://standard.go.kr | KS R ISO 26262, KS C IEC 61508, KS B ISO 13849-1, KS B ISO 10218의 상세 페이지가 있다. 열람은 로그인이 필요하고 열람 전용이다 | 실제로 본문이 열리는지, 무료인지는 확인하지 못했다 |
| UL 4600 | https://www.shopulstandards.com | UL의 무료 열람 서비스가 있다 (가입 필요, 보기 전용) | UL 4600이 대상인지 확인하지 못했다 |
| SEI CERT C (웹판) | https://wiki.sei.cmu.edu | 최신 규칙 전체 | 확인 |
| Therac-25 논문 (다시 실은 판) | https://web.mit.edu/6.033/2004/wwwdocs/papers/Therac_1.html | 논문 전체, 5부로 나뉨 | 확인 |
| PX4 safety 설정 문서 | https://docs.px4.io/main/en/config/safety.html | failsafe의 종류와 동작 | 확인 |
| ArduPilot Copter failsafe 문서 | https://ardupilot.org/copter/docs/failsafe-landing-page.html | failsafe의 종류 | 확인 |

ISO와 IEC의 미리보기로는 조항과 Annex의 제목, 용어의 정의를 확인할 수 있다. 본문의 요구사항은 확인할 수 없다.

## C. 유료이거나 볼 수 없는 문서

규격의 목록은 [standards.md](standards.md)에 있다. 거기 있는 규격은 위의 A, B에 적힌 것을 빼면 모두 C 등급이다.

### 확인한 가격

| 문서 | 가격 | 파는 곳 | 확인 |
|---|---|---|---|
| ISO 26262-6:2018 | CHF 225 | https://www.iso.org/standard/68388.html | 확인 |
| IEC 61508-3:2010 | CHF 405 | https://webstore.iec.ch/publication/5517 | 화면에 보인 기본 가격. 구입 조건은 확인하지 못했다 |
| MISRA C:2025 | 15 파운드 안팎 | https://misra.org.uk/product/misra-c2025/ | 한 사람용 PDF. 화면 보기 전용. 결제 화면까지는 확인하지 못했다 |
| KS 번역본 | 확인하지 못함 | https://www.kssn.net | - |

### 책

| 책 | 쓰는 장 |
|---|---|
| Hobbs, Embedded Software Development for Safety-Critical Systems | 10-17 |
| Smith, Simpson, The Safety Critical Systems Handbook | 3, 9 |
| Rierson, Developing Safety-Critical Software | 22 |
| Koopman, Better Embedded System Software | 11-14 |
| Koopman, How Safe Is Safe Enough? | 23 |

## 원문을 구한다면

소프트웨어 엔지니어가 독자인 책이므로, 아래 순서로 필요하다. 이것은 제안이고 구입 여부는 정하지 않았다 ([PLAN.md](../PLAN.md) 12절).

1. ISO 26262-6 (소프트웨어). 10-16장의 근거다.
2. ISO 26262-3 (concept phase)과 ISO 26262-9 (분석). 6, 7, 8장의 근거다.
3. ISO 26262-1 (용어). 용어와 정의는 ISO Online Browsing Platform에서 볼 수 있으므로 먼저 그것으로 확인한다.
4. ISO 26262-8, -4, -2. 지원 프로세스, 시스템 수준, 관리.
5. IEC 61508-3. 비교의 근거다. Edition 3이 곧 발행될 예정이므로 발행을 기다리는 것이 낫다.
