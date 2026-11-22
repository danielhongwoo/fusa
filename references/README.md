# 참고 문서

책을 쓰는 데 쓰는 문서를 실제로 볼 수 있는지에 따라 나눈 목록이다. 주소와 상태는 2026-11-22에 확인했다.

- 등급의 뜻과 문장에 근거를 표시하는 방법은 [RULES.md](../RULES.md) 5절에 있다.
- 규격의 정식 명칭과 판은 [standards.md](standards.md)에 있다.
- 받은 문서 파일은 git에 넣지 않는다. `sh references/fetch.sh`로 다시 받을 수 있다.
- 받은 파일의 SHA-256 값은 [SHA256SUMS](SHA256SUMS)에 있다. `references/`에서 `shasum -a 256 -c SHA256SUMS`로 확인한다.

## 요약

| 등급 | 뜻 | 수 | 해당 문서 |
|---|---|---|---|
| A | 무료로 받을 수 있다 | 33개 받음, 11개는 직접 받아야 함 | 사고 조사 보고서, NASA와 FAA와 EASA의 문서, SORA, AUTOSAR 공개 규격, 저자가 공개한 책과 논문 |
| B | 온라인에서 볼 수만 있다 | 8개 | ISO와 IEC의 미리보기, KS 열람, 공개 autopilot 문서 |
| C | 유료이거나 볼 수 없다 | 규격 대부분과 책 | ISO 26262, IEC 61508, 로봇 규격, 항공 규격, MISRA C |

가장 중요한 사실: ISO 26262:2018의 본문은 C 등급이고 사지 않기로 했다. 이 책은 그 원문을 보지 않고 쓴다. 요구사항의 전문을 볼 수 있는 규격은 한국어 번역본으로 열람할 수 있는 IEC 61508뿐이다 (B 등급).

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

### 관통 예제와 같은 주제를 다룬 미국 정부 보고서

| id | 문서 | 올린 곳 | 쓰는 장 | 쪽 | 크기 |
|---|---|---|---|---|---|
| nhtsa-etc-ev-fsa | Functional Safety Assessment of a Generic Accelerator Control System With Electronic Throttle Control in Electric Vehicles, DOT HS 812 656 (2020) | 미국 교통부 저장소 | 6, 7, 8 | 444 | 3.6 |
| nhtsa-safety-standards-assessment | Assessment of Safety Standards for Automotive Electronic Control Systems, DOT HS 812 285 (2016) | 미국 교통부 저장소 | 4, 22 | 49 | 0.6 |
| nasa-toyota-ua-report | NASA Engineering and Safety Center, Toyota unintended acceleration 조사 보고서 (2011) | NHTSA | 1 | 177 | - |

nhtsa-etc-ev-fsa는 이 책의 관통 예제와 같은 시스템 (전기차의 가속 제어)에 ISO 26262의 concept phase를 적용한 보고서다. 시스템 정의, hazard 분석 (HAZOP, STPA), ASIL 평가, safety goal, FMEA, functional safety concept, functional safety requirement를 담고 있다. ISO 26262의 요구사항에 관한 이 책의 주된 2차 자료다.

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

### 단계 0에서 더한 문서

| id | 문서 | 올린 곳 | 쓰는 장 | 쪽 |
|---|---|---|---|---|
| nasa-std-8739-8b | NASA-STD-8739.8B, Software Assurance and Software Safety Standard | NASA | 5, 10-17 | 65 |
| nasa-fault-tree-handbook | Fault Tree Handbook with Aerospace Applications (2002) | NASA | 8 | 218 |
| nasa-system-safety-handbook-v1 | NASA System Safety Handbook Volume 1, NASA/SP-2010-580 (2011) | NASA NTRS | 3, 5, 19 | 120 |
| hse-hsg238 | UK HSE, Out of control: Why control systems go wrong and how to prevent failure (HSG238) | HSE | 1, 10 | 53 |
| nhtsa-etc-gasoline-fsa | Functional Safety Assessment of a Generic Accelerator Control System With Electronic Throttle Control in Gasoline-Fueled Vehicles, DOT HS 812 557 (2018) | 미국 교통부 저장소 | 6, 7 | 404 |
| easa-amc-20-193 | EASA AMC 20-193, Use of multi-core processors (2022) | EASA | 14 | 14 |

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
| NASA의 Toyota 조사 보고서의 부록 A (소프트웨어) | https://www.nhtsa.gov/staticfiles/nvs/pdf/NASA_FR_Appendix_A_Software.pdf | 자동 요청이 거부됨 |
| UN Regulation No. 155, No. 156 | https://unece.org 에서 검색 | 자동 요청이 거부됨 |
| NUREG-0492, Fault Tree Handbook (1981) | https://www.nrc.gov/reading-rm/doc-collections/nuregs/staff/sr0492/index.html | 자동 요청이 거부됨 |
| JARUS SORA 2.5의 Annex A, B, E, F, H, I | jarus-rpas.org | 아래 설명 참고 |

### E-Gas monitoring concept에 대하여

관통 예제의 감시 구조는 이 문서에 바탕을 둔다. 그런데 확인한 결과는 다음과 같다.

- 최신으로 알려진 v6.0의 공식 배포처를 찾지 못했다. 문서 공유 사이트의 사본만 있었고, 그런 사본은 쓰지 않는다.
- v4.0 (2007-01-30)의 사본이 미국 NHTSA의 공개 문서철에 있다. 자동으로는 받지 못했다.
- 따라서 이 문서는 구할 때까지 C 등급으로 다룬다. 이 문서에 관한 문장은 모두 `(확인 필요)`이다.
- 받은 문서 가운데 autosar-safety-measures의 3.7.2절이 이 감시 구조를 AUTOSAR 구조 안에서 구현하는 방법을 그림과 함께 설명한다. 원문을 구하기 전에는 이것을 2차 자료로 쓴다.

### JARUS 사이트에 대하여

- 주소를 확인하던 중에 jarus-rpas.org가 예상하지 못한 서버로 연결되고 첫 페이지가 열리지 않는 것을 보았다.
- 그래서 그 도메인에서는 받지 않았다. 본문은 체코 항공 당국의 사본을 받았고, EU가 채택한 내용은 EASA의 문서로 받았다.
- 부록이 필요하면 사이트의 상태를 직접 확인한 뒤에 받는다.

## B. 온라인에서 볼 수만 있는 문서

| 문서 | 주소 | 볼 수 있는 범위 | 확인 |
|---|---|---|---|
| ISO Online Browsing Platform | https://www.iso.org/obp | ISO 규격의 서문, 소개, 범위, 인용 규격, 용어와 정의. 본문은 볼 수 없다 | ISO의 도움말로 확인. 이용 약관에 동의해야 들어갈 수 있어 직접 열어 보지는 않았다 |
| IEC webstore의 미리보기 | https://webstore.iec.ch | IEC 규격의 목차와 앞부분 | 직접 열어 보지 않았다 |
| e-나라표준인증의 KS 열람 | https://standard.go.kr | 한국어 번역본. IEC 규격을 옮긴 KS (예: KS C IEC 61508)는 로그인하면 무료로 볼 수 있다. 보기만 할 수 있다 | KS C IEC 61508-1 - -7이 모두 열리는 것을 저자가 로그인해 확인했다 (2026-11-22). ISO 규격을 옮긴 KS (예: KS R ISO 26262)가 열리는지는 확인하지 못했다 |
| UL 4600 | https://www.shopulstandards.com | UL의 무료 열람 서비스가 있다 (가입 필요, 보기 전용) | UL 4600이 대상인지 확인하지 못했다 |
| SEI CERT C (웹판) | https://wiki.sei.cmu.edu | 최신 규칙 전체 | 확인 |
| Therac-25 논문 (다시 실은 판) | https://web.mit.edu/6.033/2004/wwwdocs/papers/Therac_1.html | 논문 전체, 5부로 나뉨 | 확인 |
| Therac-25 논문 (IEEE Computer에 실린 모양의 사본) | https://www.se.rit.edu/~swen-342/resources/ 아래의 PDF | 논문 전체, 24쪽 | 2026-11-22에 읽음. 1장의 근거. 저자의 페이지 (sunnyday.mit.edu)는 연결되지 않았다 |
| ISO/IEC Directives, Part 2 (9판, 2021) | https://www.iso.org/sites/directives/current/part2/index.xhtml | 전체. ISO와 IEC의 문서를 쓰는 규칙 | 2026-11-22에 읽음. 4장의 근거 |
| ISO의 규격별 페이지 | https://www.iso.org/standard/68383.html (ISO 26262-1:2018), 90020.html - 90031.html (다음 판의 초안) | 판, 단계, 소개 글 | 2026-11-22에 읽음. curl로는 열리지 않아 브라우저로 읽었다 |
| IEC의 판매 페이지 | https://webstore.iec.ch/en/publication/5515 (IEC 61508-1) | 판, 다음 판의 단계와 발행 예정일 | 2026-11-22에 읽음 |
| PX4 safety 설정 문서 | https://docs.px4.io/main/en/config/safety.html | failsafe의 종류와 동작 | 확인 |
| ArduPilot Copter failsafe 문서 | https://ardupilot.org/copter/docs/failsafe-landing-page.html | failsafe의 종류 | 확인 |

ISO와 IEC의 미리보기로는 조항과 Annex의 제목, 용어의 정의를 확인할 수 있다. 본문의 요구사항은 확인할 수 없다.

## C. 유료이거나 볼 수 없는 문서

규격의 목록은 [standards.md](standards.md)에 있다. 거기 있는 규격은 위의 A, B에 적힌 것을 빼면 모두 C 등급이다.

### 확인한 가격

ISO 26262와 IEC 61508의 가격은 아래 "원문을 구하는 방법"에 있다.

| 문서 | 가격 | 파는 곳 | 확인 |
|---|---|---|---|
| MISRA C:2025 | 15 파운드 안팎 | https://misra.org.uk/product/misra-c2025/ | 한 사람용 PDF. 화면 보기 전용. 결제 화면까지는 확인하지 못했다. 사지 않기로 정했다 (2026-11-22) |

### 책

| 책 | 쓰는 장 |
|---|---|
| Hobbs, Embedded Software Development for Safety-Critical Systems | 10-17 |
| Smith, Simpson, The Safety Critical Systems Handbook | 3, 9 |
| Rierson, Developing Safety-Critical Software | 22 |
| Koopman, Better Embedded System Software | 11-14 |
| Koopman, How Safe Is Safe Enough? | 23 |

## 규격 원문

2026-11-22에 조사했다. 가격은 판매처의 화면에서 본 값이다. 사기 직전에 다시 확인한다.

### 결론

- ISO 26262:2018의 원문 전체를 합법적으로 무료로 볼 수 있는 길은 찾지 못했다. 보려면 사야 한다.
- 한국어 번역본 (KS R ISO 26262)은 싸지만, 소프트웨어를 다루는 Part 6을 비롯해 대부분이 2011년 판을 옮긴 것이다. 이 책이 기준으로 삼는 2018년 판의 근거로 쓸 수 없다.
- IEC 61508은 지금 살 필요가 없다. 한국어 번역본 (KS C IEC 61508, Edition 2와 같은 내용)을 e-나라표준인증에서 로그인하면 무료로 볼 수 있고, Edition 3이 곧 나온다.

### ISO 26262:2018 영문 원문의 가격

| Part | ISO store | 한국표준정보망 (KSSN) |
|---|---|---|
| 1 Vocabulary | CHF 67 | 106,700원 |
| 2 Management of functional safety | CHF 196 | 312,200원 |
| 3 Concept phase | CHF 179 | 285,100원 |
| 4 Product development at the system level | CHF 179 | 285,100원 |
| 6 Product development at the software level | CHF 225 | 358,300원 |
| 8 Supporting processes | CHF 225 | 확인하지 못함 |
| 9 ASIL-oriented and safety-oriented analyses | CHF 179 | 285,100원 |
| Part 1-10 묶음 | CHF 1,561 | - |

- Part 3, 6, 9를 사면 ISO store에서 CHF 583, KSSN에서 928,500원이다.
- 위 일곱 Part를 낱개로 사면 ISO store에서 CHF 1,250이다. 묶음은 Part 5, 7, 10까지 필요할 때만 이득이다.
- PDF는 한 사람만 쓸 수 있는 조건이다. 인쇄할 수 있는지는 확인하지 못했다.
- 다른 나라 표준 기관의 가격도 비슷하다. ISO 26262-6을 기준으로 아일랜드는 217유로, 독일은 241유로다 (부가세 제외). 더 싼 합법적 경로는 찾지 못했다.
- 가격을 본 곳: https://committee.iso.org/standard/68388.html (ISO), https://www.kssn.net (KSSN)

### 한국어 번역본 (KS)

| 번역본 | 옮긴 판 | KSSN 가격 |
|---|---|---|
| KS R ISO 26262-1, -2, -3, -4, -6, -7, -8, -9 | 2011년 판 | -1 39,600원, -2 48,700원, -3 34,600원, -6 55,000원, -9 34,600원 |
| KS R ISO 26262-10 | 2012년 판 | 확인하지 못함 |
| KS R ISO 26262-5, -11, -12 | 2018년 판 | -5 90,000원, -11 170,200원, -12 45,600원 |
| KS C IEC 61508-1 - -7 | Edition 2 (2010) | -3 103,900원. e-나라표준인증에서 로그인하면 무료로 볼 수 있다 (저자가 확인) |
| KS C IEC 61508-0 | 시리즈를 소개하는 기술 보고서 (IEC TR 61508-0:2005)의 번역본으로 보인다. 요구사항은 없다 | 저자가 사이트에서 보았다. 옮긴 판은 확인하지 못했다 |

- 어느 판을 옮겼는지는 e-나라표준인증의 각 규격 페이지에 적힌 "대응 국제표준"으로 확인했다.
- KS R ISO 26262를 e-나라표준인증에서 무료로 볼 수 있는지는 확인하지 못했다. 로그인해야 알 수 있다.
- e-나라표준인증의 열람은 보기만 할 수 있다. 인쇄, 복사, 내려받기, AI에 넣는 것이 금지되어 있다.

### ISO 26262 3판의 초안

- Part 1, 2, 3, 4, 6, 8, 9의 초안 (DIS)을 ISO store에서 Part마다 CHF 67에 판다.
- Part 3의 초안 투표가 2026-10에 시작되었다는 기록이 있다. 발행일은 정해지지 않았고 2027년 이후로 보인다.
- 영국 표준 기관 (BSI)은 2026-10-14에 Part 1-11의 초안을 의견 수렴용으로 냈다. 재판매처에서는 Part마다 20유로대에 판다.
- 초안은 바뀔 수 있어서 책의 근거로 삼을 수 없다. "새 판에서 달라지는 점"을 미리 살피는 데에는 쓸 수 있다.

### 결정과 그 영향 (2026-11-22)

ISO 26262:2018의 원문은 사지 않는다. 그래서 다음을 할 수 없다.

- 조항 번호를 달고 "규격이 이렇게 요구한다"고 설명하는 것
- 요구사항 수준의 대응표. 부록 B는 조항과 Annex의 제목 수준까지만 만든다
- ASIL에 따른 방법 표의 내용을 확인하는 것
- 원고를 원문과 대조했다고 말하는 것

### 원문 없이 쓰는 방법

책의 근거는 Claude가 직접 읽을 수 있는 문서로 한정한다 (RULES.md 5.1절). 저자가 대조하지 않아도 되게 하기 위해서다.

Claude가 읽을 수 있는 것 (책의 근거로 쓴다)

| 필요한 것 | 근거로 쓰는 문서 |
|---|---|
| ISO 26262의 concept phase가 실제로 적용된 모습 (hazard 분석, ASIL 평가, safety goal, functional safety concept) | nhtsa-etc-ev-fsa |
| 규격들의 구성과 서로의 관계 | nhtsa-safety-standards-assessment, iec-61508-overview-slides |
| 소프트웨어 안전의 기법 (요구사항, 설계, 코딩, test) | nasa-gb-8719-13, nasa-mcdc-tutorial, misra-compliance-2020 |
| safety mechanism과 감시 구조 | autosar-safety-measures, autosar-e2e-protocol |
| 분석 기법 | stpa-handbook, nhtsa-etc-ev-fsa |
| safety case | gsn-standard-v3 |
| 사고 사례 | 사고 조사 보고서들, nasa-toyota-ua-report, koopman-toyota-ua |
| 로봇 | ifa-report-2-2017e (2015년 판 기준) |
| 드론 | SORA와 EASA의 문서들 |

저자만 볼 수 있는 것 (책의 근거로 쓰지 않는다. 저자가 원할 때 읽는 참고 자료다)

| 문서 | 볼 수 있는 곳 | 확인 |
|---|---|---|
| KS C IEC 61508-0 - -7 (Edition 2의 한국어 번역본) | e-나라표준인증, 로그인 필요 | Part 1-7이 모두 열리는 것을 저자가 확인했다 (2026-11-22) |
| KS R ISO 26262 (대부분 2011년 판) | 같은 곳 | 열리는지 확인하지 못했다 |
| ISO 26262-1:2018의 용어와 정의 | ISO Online Browsing Platform, 이용 약관 동의 필요 | ISO의 도움말로 확인. 직접 열어 보지는 않았다 |
| ISO 26262 3판의 초안 | 영국 표준 기관이 2026-10-14부터 의견을 받고 있다 | 초안을 무료로 읽을 수 있는지는 확인하지 못했다 |

- e-나라표준인증의 열람은 보기만 할 수 있고 AI에 넣는 것이 금지되어 있다. 그래서 Claude는 이 문서들을 읽지 않는다.
- KS C IEC 61508을 읽는다면 순서는 Part 0 (소개) -> Part 4 (용어) -> Part 1 (일반 요구사항) -> Part 3 (소프트웨어) -> Part 7 (기법의 설명)을 권한다.
- 초안은 바뀔 수 있어서 책의 근거로 삼지 않는다.
- 3판이 발행되면 그때 살지를 다시 정한다. 원고가 끝나는 시점에는 3판이 현행일 수 있다.
- 직접 받아야 하는 문서 (위의 "무료지만 직접 받아야 하는 문서")를 받아 두면 Claude가 읽을 수 있는 근거가 늘어난다.

### 산 문서를 쓸 때 주의할 점

- 산 PDF는 한 사람용이다. git에 넣지 않고 다른 사람에게 주지 않는다.
- Claude가 그 파일을 읽어도 되는지는 사용 조건을 확인한 뒤에 정한다. 정하기 전에는 저자가 원문과 대조하고, Claude는 받은 문서와 저자가 알려 준 내용으로만 확인한다.

### 확인하지 못한 것

- 도서관 (국회도서관, 국립중앙도서관, 대학 도서관)에서 방문해서 볼 수 있는지
- 환율을 넣은 ISO store와 KSSN의 가격 비교
- ISO가 파는 PDF의 인쇄 조건
- KS R ISO 26262-4, -7, -8, -10의 가격
