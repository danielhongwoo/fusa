# 5장 근거 문서에서 뽑은 사실 (읽기 기록)

대상: 5장 "Safety lifecycle과 safety management" (plans/ch05-safety-lifecycle.md). 읽은 날: 2026-11-22.

- 쪽 칸은 PDF 파일의 몇 번째 쪽이다. 문서에 인쇄된 쪽 번호가 다르면 절 머리에 차이를 적는다.
- 인용은 줄바꿈을 합치고 따옴표와 줄표를 ASCII로 바꿨다. 그 밖에는 원문 그대로다.
- `(기억)`은 문서에서 확인하지 못한 내용이다. 원고의 근거로 쓰지 않는다.
- 원고에 쓰기 전에 그 쪽을 직접 열어 확인한다 (RULES.md 5.2절).

## 1. iec-61508-overview-slides (슬라이드 자료, 2022년 7월 파일, IEC 61508의 해설 자료이며 규격 원문이 아니다)

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| F05-001 | 19 | HSE "Out of control" 연구는 제어 시스템이 관련된 사고 34건을 다뤘다. 범위는 화학/석유 플랜트와 기계이고, 사고를 "원인이 시작된 lifecycle 단계"로 분류했다. | Incidents characterized by originating lifecycle phase | 출처 책은 hse-hsg238 절과 대조 |
| F05-002 | 20 | 제어 시스템의 위험 고장의 주된 원인을 safety lifecycle 단계별로 제시: Specification 44%, Changes after Commissioning 20%, Design & Implementation 15%, Operation & Maintenance 15%, Installation & Commissioning 6%. 60% 넘는 고장이 투입 전에 이미 시스템에 들어 있었다고 적는다. | More than 60% of failures were "built into the safety-related systems" before taken into service. | 숫자는 HSE 표 2와 같다 (F05-011). 44+15+6=65%가 "투입 전" |
| F05-003 | 21 | IEC 61508에는 safety lifecycle이 셋 있다: Overall, E/E/PE system, Software. 각 단계가 그 단계의 요구사항을 정하며, 그 요구사항은 기술 요구사항에 관한 것이라고 적는다. 그림은 Concept, Specification, Design, Installation & Commissioning, Operation & Maintenance, Validation, Modification의 매우 단순화한 Overall lifecycle이다. | The requirements specified in each phase relate to the technical requirements. | 슬라이드는 "very simplified"라고 밝힌다 |
| F05-004 | 22 | 규격 준수는 네 덩어리로 그려진다: Management of Functional Safety, Competence, Technical Requirements, Functional Safety Assurance Measures. 이 조항들이 safety lifecycle의 각 해당 단계에 적용된다. | These clauses applied to each relevant phase of the Safety Lifecycles | 기술 요구사항 외에 관리, 역량, 보증 조치가 따로 있다는 구도 |
| F05-005 | 2 | 시장 환경 슬라이드: safety culture, 기능 안전 관리, 조직의 역량과 개인의 역량의 공식화가 늘고 있다고 적는다. | Increasing formality of safety culture, management of functional safety, competence of the organisation and personal competence | 지정 범위 밖(2쪽). 추세에 관한 진술이며 근거 없음 |

## 2. hse-hsg238 (HSE, Out of control, 2nd edition, 53쪽. 인쇄 쪽 번호 = PDF 쪽)

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| F05-006 | 4 | 2판의 서문: 사고 분석은 1995년 1판과 같고, 기술은 달라졌어도 전체 결론과 세부 교훈은 유효하다고 HSE가 적는다. | remains unchanged from the first edition published in 1995 | 자료의 시기는 1995년 이전 |
| F05-007 | 6 | 사고 사례는 HSE에 보고되었거나 HSE 내부 조사 보고서에서 가져왔다. | The details of the incidents were either advised to HSE, or taken from its own internal investigation reports. | 무작위 표본이 아님. 선정 기준은 이 쪽에 없음 |
| F05-008 | 11 | 분류 방식은 사고의 근본 원인이 시작된 단계에 오류를 배정한다. 예: 유지보수 중의 고장이 명세 단계의 실수로 거슬러 올라갈 수 있다. 5개 단계를 8개 범주로 나눈다. | allocates errors and failures to the phase where the root causes of the incident originated | HSE의 분류 체계 |
| F05-009 | 11 | 대부분의 사고는 여러 단계의 오류 때문이어서, 어느 단계가 지배적인지는 판단이 필요하고 다른 사람은 다르게 볼 수 있다고 HSE가 적는다. 합계에는 주된 원인만 센다. | Others may have differing views. | 분류가 저자의 판단이라는 한계 |
| F05-010 | 12 | 분류표(표 1)의 단계: 1 안전 요구사항 명세(기능, 안전 무결성), 2 설계와 구현, 3 설치와 시운전, 4 운전과 유지보수(운전자 행동, 유지보수 활동), 5 시운전 후 변경(수정과 개조, 폐기). | Safety integrity requirements specification | 사고 분류의 단계 정의 |
| F05-011 | 30 | 사고 34건에서 원인 56개가 확인되었다. 표 2의 주된 원인(건수 및 %): 기능 요구사항 명세 4(12), 안전 무결성 요구사항 명세 11(32), 명세 합계 15(44); 설계와 구현 5(15); 설치와 시운전 2(6); 운전 1(3)과 유지보수 4(12), 합계 5(15); 변경 7(20), 폐기 0. | Total inadequate specification | 건수를 합하면 15+5+2+5+7=34. 슬라이드의 44/15/6/15/20과 일치 |
| F05-012 | 31 | 표본이 작아 통계적 유의성이 낮으므로, 모든 제어 시스템 고장으로 일반화할 때는 주의해야 한다고 HSE가 직접 적는다. 그래도 사례에서 얻는 교훈은 많다고 한다. | because of the small sample size the results of the analysis have low statistical significance | 표본 크기 34건. 표본 한계의 직접 근거 |
| F05-013 | 31 | 분석은 대부분의 제어 시스템 고장의 뿌리가 부적절한 명세에 있을 수 있음을 시사한다. 이유로 EUC(제어 대상 장비)의 위험 분석 부족, 제어 시스템의 치명적 고장 모드가 명세에 미치는 영향을 평가하지 않음을 든다. | most control system failures may have their root cause in an inadequate specification | "suggests"(시사)라는 표현 |
| F05-014 | 31 | 소프트웨어 개발의 여러 연구가 명세 단계의 오류가 대부분의 소프트웨어 결함과 고장을 차지함을 보였다고 적는다 (각주 29-31). | errors made during specification account for most software faults and failures | 각주의 연구 자체는 읽지 않음 |
| F05-015 | 4 | 요약: 설계 후반에 위험을 늦게 발견하면 그에 따른 변경을 반영하기가 어렵고, 시스템 수명 후반일수록 더 어렵고 비싸다. | more difficult (and expensive) to make such changes later in the life of the control system | HSE의 주장 |
| F05-016 | 4 | 설계에서 우려되는 점으로 단일 채널 시스템의 안전 무결성에 대한 지나친 낙관, 소프트웨어를 충분히 검증하지 않음, 인간 요인에 대한 고려 부족을 든다. | failure to adequately verify software | 사고 분석에서 나온 지적 |
| F05-017 | 5 | 유지보수와 수정: 잘 설계된 시스템의 안전 무결성도 부적절한 절차로 크게 손상될 수 있다. 교육 부족, 부적절한 안전 분석, 부적절한 시험, 절차에 대한 관리 통제 부족이 운전 단계 고장의 반복 주제다. | inadequate management control of procedures are recurring themes of operational failures | 슬라이드의 "Changes after Commissioning 20%"와 같은 맥락 |
| F05-018 | 5 | 안전에서는 인적 요인과 관리 요인도 매우 중요하다고 적고, HSE의 일반 사고 비용 연구(각주 4)에서 오류를 고치는 비용이 처음부터 체계적으로 했을 때의 비용을 훨씬 넘었다고 한다. 그림 1은 보험 비용 1에 비보험 비용 8-36으로 표시한다. | costs of error rectification far exceeded those that would have been incurred | 제어 시스템 전용 자료가 아니라 일반 사고 비용 연구. 그림 1의 비율 읽기는 그림 레이블 기준 |
| F05-019 | 7 | 10항: 제어 시스템 고장은 기술 요소만의 문제가 아니며, 상충하는 경영 우선순위와 인센티브, 안전 공학 교육 부족, safety culture의 부재, 부실한 계약 절차가 기술 원인의 고장에 크게 기여할 수 있다고 적는다. | absence of a 'safety culture' and poor contract procedures etc may contribute significantly | 5절(관리 책임)의 예고 |
| F05-020 | 32 | 관리 책임: 고용주는 위험 평가를 해야 하고(규정 3), 조직 체계와 절차가 시스템 수명의 모든 단계에서 안전을 다뤄야 한다(규정 5). 경영진은 안전 방침을 만들고 모든 조직 수준에서 safety culture의 발전을 키울 책임이 있다. | foster the development of a safety culture throughout all levels of the organisation | 영국 Management of Health and Safety at Work Regulations 1999. 법적 틀은 영국 |
| F05-021 | 32 | 안전 책임은 여러 분야 팀이 장비 수명의 모든 단계에서 나눠 진다. 따라서 팀 사이의 의사소통이 중요하며, 보고 절차를 만들고 감시하는 것이 경영진의 책임이다. | vital that communication between these groups is effective | 79항 |
| F05-022 | 32 | 운전과 유지보수 절차는 이해하기 쉽고 모호하지 않고 문서화되어 감사 추적(audit trail)이 가능해야 한다. 종사자의 자격, 교육, 경험은 한 번으로 끝나지 않고 지속적인 성과 평가와 교육 약속이 필요하다. | adequately qualified, trained, and experienced | 80-81항 |
| F05-023 | 33 | 결론: 사고 대부분은 제어 시스템의 미묘한 고장 모드가 아니라 lifecycle 전체에 걸친 체계적 접근으로 막을 수 있었던 결함이 원인이다. 특히 명세 단계의 세부 주의 부족과 기술 사항의 관리 부족이 근본 원인이다. | defects that were preventable if a systematic approach had been adopted throughout its lifecycle | 83항. HSE의 결론 |
| F05-024 | 33 | tailoring에 해당하는 서술: 고장의 결과가 사람이나 환경에 위험이 작거나 설계가 단순하면 경험과 체크리스트에 기초한 체계적 접근으로 충분할 수 있다. 위험이 크거나 복잡하면 HAZOP(위험 식별), FMEA(설계 분석) 같은 정형 기법을 권고한다. | a systematic approach based on experience and checklists may be adequate to identify hazards | 86-87항. 리스크와 복잡도가 엄밀성을 정하는 근거 |
| F05-025 | 37 | safety lifecycle 정의와 구조: 각 단계는 입력, 정해진 목적, 안전 활동, 산출물을 갖고 한 단계의 산출물이 다음 단계의 입력이 된다. 모든 단계를 가로질러 verification과 assessment 활동이 있다. 이 모델은 IEC 61508에서 왔고 사고 분류에 맞게 조금 바꿨다. | Running across all the lifecycle phases are verification and assessment activities. | 3-5항 |
| F05-026 | 38 | 프로젝트 모델과 safety lifecycle의 근본 차이는 결과의 assessment와 verification에 정형 절차를 쓰는 것이다. 이미 한 활동을 이후 결정이 뒤집지 않는지 상류 활동을 공식적으로 다시 검토해야 하며, 이로써 반복적 성격이 생긴다. | formally review 'upstream' activities | 6-7항. 많은 사고가 전체 안전 요구사항에서 고려하지 않은 장비 고장 때문이었다고 적는다 |
| F05-027 | 38 | 단순하고 위험이 잘 알려진 프로젝트는 모든 단계와 활동이 필요 없을 수 있어 문제에 맞춘 tailoring이 기대된다. safety lifecycle은 특정 조직 구조를 요구하지 않으며, 한 활동을 끝내야 다음을 시작하는 것도 아니다 (concurrent design 가능). | tailoring to the problem in hand will be required | 9-11항 |
| F05-028 | 38 | lifecycle 모델의 장점으로 전체 문제의 조망, 모든 관계자의 기준점, 단계 안에 갇히는 "isolationist" 문화(하청이 있을 때 특히)의 위험 감소, 문서화 필요의 식별을 든다. | minimises the risk of an 'isolationist' culture within each phase | 12항 |
| F05-029 | 43 | verification: 한 활동의 산출물이 입력을 만족하는지 다음 단계로 가기 전에 확인하는 것. 엄밀성은 목표 safety integrity level과 복잡도에 따라 다르다. | Checking that the outputs satisfy the inputs before moving on to the next safety lifecycle phase | 31-32항. 복잡한 소프트웨어는 최종 인수 시험만으로 설계 결함을 찾을 수 없다고 적는다 |
| F05-030 | 43 | functional safety assessment: 프로젝트 팀과 독립된 사람이 수행하는 기술적 평가로, 근거에 기초해 기능 안전이 달성되었는지 결정한다. 용어집은 "근거에 기초한 조사로 달성된 기능 안전을 판단하는 것"이라 정의한다 (50쪽). | carried out by personnel who are independent of the project team | 33항. 독립의 정도(사람, 부서, 조직)는 이 쪽에 없음. ISO 26262가 아니라 HSE의 설명 |
| F05-031 | 52 | 용어집: validation 정의의 주석 2는 안전 요구사항 명세가 사용자의 안전 필요를 충분히 정확히 담았는지의 고려를 functional safety assessment의 일부로 본다고 적는다. verification은 객관적 증거로 요구사항 충족을 확인하는 것이며, 문서 검토, 설계 검토, 성능 시험이 예다. | Examples include document reviews, design reviews, and performance tests. | 용어집. HSE의 정의 |

## 3. nasa-gb-8719-13 (NASA Software Safety Guidebook, 2004-03-31. 인쇄 쪽 번호 = PDF 쪽 - 1)

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| F05-032 | 33 | 3장 첫머리: 예비 위험 분석(PHA)이 소프트웨어가 안전 필수임을 보이면 소프트웨어 안전 프로세스를 시작해야 한다. 안전 노력의 양은 시스템과 소프트웨어의 위험 수준에 맞춰 조정(tailoring)한다. | If the Preliminary Hazard Analysis (PHA) reveals that any software is safety-critical, a software safety process must be initiated. | 가이드북이며 요구 문서가 아님 |
| F05-033 | 33 | 안전 프로세스 참여자 그림: 프로젝트 관리자, 시스템 엔지니어, 시스템 안전 엔지니어, 소프트웨어 안전 엔지니어, 소프트웨어 보증 엔지니어, 소프트웨어 개발자. 이들 사이의 의사소통선을 만들고 유지하는 것이 매우 중요하다고 적는다. | It is VERY important that these lines are established and maintained. | 그림의 글 |
| F05-034 | 33 | 프로젝트 관리자는 전체 개요를 유지하고, 분석 기법이 필요한지 의문이 생기면 대개 최종 권한자다. 프로젝트가 감수할 위험의 양과 종류도 관리자가 정한다. 한편 SMA와 IV&V는 안전 분석, 설계, 검증이 적절히 이루어지는지 확인하는 독립된 보고 경로를 제공한다. | SMA and IV&V provide an independent reporting path | SMA = Safety and Mission Assurance(NASA의 안전 보증 조직). 관리자 권한과 독립 보고 경로의 병존 |
| F05-035 | 34 | 역할 설명: 시스템 엔지니어는 하드웨어와 소프트웨어 분할을 맡고, 시스템 안전 엔지니어는 위험한 구성요소를 정한다. 소프트웨어 안전 엔지니어는 안전 요구사항이 있고 설계에 반영되는지 검증하고 분석과 시험을 한다. 개발자는 설계와 방어적 프로그래밍으로 영향을 준다. 소프트웨어 보증 엔지니어는 프로세스를 감시하고 추적성을 보증하며 "외부의 시각"을 준다. | provide an "outside view" of both the software process and products | 역할 정의는 NASA 프로젝트 기준 |
| F05-036 | 34 | 작은 팀에서는 별도의 소프트웨어 안전 엔지니어가 없을 수 있고, 소프트웨어 보증, 시스템 안전, 시스템 개발자, 개발팀 구성원이 그 역할을 맡거나 여럿이 나눠 맡을 수 있다. | In a small team, there may not be a separate software safety engineer. | 역할의 겸임 허용 |
| F05-037 | 34 | IV&V: 모든 NPG 7120.5 프로젝트와 안전 필수 프로젝트에서 프로젝트 관리자가 자체 평가를 해 NASA IV&V 시설과 지역 SMA에 보고한다. IV&V는 소프트웨어 보증과 소프트웨어 안전에 더해지는 것이며 이를 대체하지 않는다. | IV&V is in addition to software assurance and software safety and not a replacement for those roles. | NASA 내부 정책에 기댄 서술 |
| F05-038 | 35 | 소프트웨어 보증의 목표: 결함 줄이기, 결함을 더 일찍(고치는 비용이 적은 시점에) 찾기, 소프트웨어 안전을 보증하기, 예산과 일정 유지, 위험 줄이기. 단계(개념, 요구사항, 설계, 구현, 검증, 유지보수)의 구분은 waterfall을 뜻하지 않는다. | Find the defects earlier in the lifecycle, when they are less costly to correct. | 35쪽 |
| F05-039 | 105 | 소프트웨어 요구사항 장 첫머리: 소프트웨어 결함을 고치는 비용은 개발 lifecycle이 진행될수록 급격히 늘어나므로 처음부터 올바른 요구사항을 만드는 것이 중요하다. 모든 오류를 없애기는 대개 불가능하다고도 적는다. | The cost of correcting software faults and errors escalates dramatically as the development life cycle progresses | 지정 범위 밖(105쪽). 수치 없음 |
| F05-040 | 35 | 안전 노력의 범위 정하기 세 단계: 안전 필수 소프트웨어 식별, 그 중요도 결정, 개발 노력과 감독의 정도 결정. 수치와 표는 출발점일 뿐이며 시스템 위험 지수와 소프트웨어의 통제 정도, 복잡도, 개발 환경을 합치는 것은 "정확한 과학이 아니다". | Merging these two aspects is not an exact science | 3.1절 |
| F05-041 | 36-37 | 소프트웨어 신뢰도는 정량화하기 어렵고(대개 정성적), 중대형(4-5만 줄 이상) 소프트웨어는 모든 상태를 시험할 수 없다고 적는다. 그래서 노력의 수준은 시스템의 다른 특성으로 정한다: 통제의 정도(Degree of Control), 복잡도, 시간 임계성. | usually impossible to establish reliability values and prove correctness of design by testing all possible states | 36쪽. 시험으로 증명 불가 서술 |
| F05-042 | 38-40 | MIL-STD-882C의 소프트웨어 통제 범주(IA, IIA, IIB, IIIA, IIIB, IV)와 시스템 위험 지수(2-5)를 소프트웨어 위험 행렬(표 3-3)로 합쳐 소프트웨어 위험 지수(1-5)를 얻는다. 낮은 번호는 설계가 허용 불가라는 뜻이 아니라 분석과 시험에 더 많은 자원이 필요하다는 뜻이다. | a low index number from the Software Risk Matrix does not mean that a design is unacceptable | 38-40쪽. MIL-STD-882C는 882D 이후 폐기되었다고 가이드북이 적음 |
| F05-043 | 41-42 | 소프트웨어 위험 지수 1은 Full, 2와 3은 Moderate, 4와 5는 Minimum 노력에 대응한다 (높은 2는 Full 쪽, 높은 4는 Moderate). 표 3-5에서 심각도와 범주에 따라 Full, Moderate, Minimum, None으로 나뉜다. | Software Risk Index 1 = full effort, Software Risk Index 2 and 3 = moderate effort | 41-42쪽 |
| F05-044 | 40 | 줄일 수 없는 것: 표 3-3의 주석은 안전 필수 시스템의 모든 소프트웨어를 평가해야 하며, 시스템 안전 요소를 훼손할 가능성이 있으면 안전 필수로 다뤄야 한다고 적는다. 통제 범주 IV도 치명적/위험 사건에서는 최소 노력이 필요할 수 있다 (41쪽). | All software in a safety-critical system must be evaluated. | 40쪽 주석 |
| F05-045 | 42 | 요구사항은 시스템 설계가 진행되며 바뀐다. 하드웨어였던 항목이 소프트웨어로 옮겨가면 소프트웨어 안전 노력의 결정을 다시 해야 한다. | As system elements are redistributed, it is vital to revisit the software safety effort determination. | 경고 상자 |
| F05-046 | 42 | 감독의 정도(표 3-6): 소프트웨어 위험 지수 1(시스템 위험 지수 2)은 완전히 독립된 IV&V 조직과 사내 SA(software assurance), 지수 2는 사내 SA와 독립 평가(IA)의 가능성, 지수 3은 사내 SA, 지수 4-5는 최소한의 사내 SA. 필요한 감독은 임무 성공과 안전 중 더 큰 쪽이다. | Fully independent IV & V1 organization, as well as in-house SA | 42쪽(표), 43쪽(큰 쪽 규칙). NASA 기관 요건에 기댐 |
| F05-047 | 43 | 3.2 tailoring: 안전 활동은 소프트웨어 개발 노력에 맞아야 하되 시스템이 안전함을 보장해야 한다. 어떤 수준에서도 최소한 명세, 설계, 구현, 시험, 변경 요청, 문제 보고서를 검토해 위험이 들어갔는지 봐야 한다. | At the very minimum, a project must review all pertinent specifications, designs, implementations, tests | 줄일 수 없는 최소선 |
| F05-048 | 43 | 소프트웨어 보증 활동은 항상 안전 요구사항이 특정 설계 요소, 프로그램 단위, 시험으로 추적되는지 검증해야 한다. 모든 NASA 프로젝트는 안전 필수 정도와 관계없이 시작 때와 큰 변경 때 IV&V 평가를 해야 한다고 적는다. | must perform an IV&V evaluation at the beginning of the project, and whenever the project changes significantly | 같은 쪽 내용. 286쪽(PDF)은 이를 IV&V 또는 IA의 필요성 평가로 부른다 |
| F05-049 | 43 | 기법별 권고 표시: Mandatory, Highly Recommended, Recommended, Not Recommended. Highly Recommended를 넣지 않으면 안전이 훼손되지 않음을 보여야 한다. 목록에 없는 기법은 비슷한 결과를 낼 수 있음을 보이면 쓸 수 있다 (44쪽). | If not included, it should be shown that safety is not compromised. | 각주 2. tailoring에 근거 제시가 필요하다는 서술 |
| F05-050 | 44-45 | 조정할 수 있는 활동: 개발(안전 기능), 분석, 검사(inspection), 검토(review)의 수와 시점, verification과 validation의 시험 수와 커버리지, 소프트웨어 보증과 안전 감사(audit)의 빈도와 대상 수. 범주 분류와 선택한 활동은 프로젝트 관리, 개발, 소프트웨어 품질 보증, 소프트웨어 시스템 안전이 함께 협상해 승인한다. | must be negotiated and approved by project management, software development, software quality assurance, and software systems safety | 44쪽(협상), 45쪽(감사 빈도 등) |
| F05-051 | 45 | Full 노력은 위험한 사건이 짧은 시간에 확대되는 시스템(생명 유지, 화재 감지, 추진, 전원, 화약 등)에 해당한다. Moderate는 위험 가능성이 제한적이거나 사람이 대응할 시간이 있는 시스템이다. 독립 평가(IA)는 IV&V보다 범위가 좁은 일회성 검토로, 외부 감사에 가깝다. | In many ways, IA is an outside audit of the project's development process and products | 45쪽. IA의 정의는 NASA 내부 용어 |
| F05-052 | 46 | Minimum은 위험 가능성이 낮거나 비소프트웨어 수단(하드웨어 인터록 등)으로 통제하는 경우다. 정식 안전 프로그램이 필요 없어도 좋은 개발 관행과 SA는 항상 필요하다고 적는다. | Of course, good development practices and SA are always necessary. | 줄일 수 없는 것 |
| F05-053 | 46 | 혼합 수준: 소프트웨어 모든 부분을 같게 다룰 필요가 없다. 안전 필수 소프트웨어를 분리하면 안전 노력을 그 부분에만 적용할 수 있다. 작은 프로젝트가 "안전 필수 소프트웨어 없음"을 주장하는 것은 일이 늘어나는 것이 걱정되기 때문인 경우가 많다고 적는다. | Partitioning the safety-critical software from code that is not safety-critical allows the safety effort to be applied only to that safety-critical portion. | 분리(partitioning)를 근거로 한 범위 축소 |
| F05-054 | 53 | 장 4: 개념, 요구사항, 설계, 구현, 시험, 운영 단계는 모든 lifecycle에 적용되는 개념이며 엄격한 waterfall을 뜻하지 않는다. lifecycle 선택은 초기 결정 중 하나이며, 소프트웨어, 시스템, 안전 엔지니어가 함께 정해야 한다. | this does not imply a strict adherence to the waterfall lifecycle | 53쪽. 이 가이드북은 특정 모델을 권하지 않는다 (54쪽) |
| F05-055 | 54-55 | waterfall: 단계마다 정해진 활동과 산출물이 있고 다음 단계로 가기 전에 승인해야 한다. 문제로 요구사항을 미리 명세할 수 있다는 가정, 변경이 적다는 가정, 문서 외 산출물이 늦게 나옴, 선행 작업을 기다리는 팀 막힘을 든다. 시스템 waterfall 아래에 소프트웨어 waterfall이 놓이는 그림이 있다 (V-model 그림은 없음). | must be approved prior to moving into the next phase | 54쪽(그림, 정의), 55쪽(문제) |
| F05-056 | 55-60 | 그 밖의 lifecycle 모델: rapid prototyping(프로토타입을 제품으로 쓰는 위험), spiral(반복마다 위험 관리를 명시), incremental(단일 인도, 증분 인도), evolutionary(요구사항을 증분에서 구체화). 각 모델의 장단점을 적는다. | Time apparently gained on the front end of a project because of early releases may be lost later | 56-60쪽. 모델별 서술 |
| F05-057 | 87 | 4.4 프로세스 tailoring: 목표는 필요한 일을 모두 하되 필요한 것만 하는 것이다. tailoring에 영향을 주는 요인: 안전/임무 중요도, 규모와 복잡도, 요구 규격(IEEE 12207 등), 비용과 일정 위험, 혁신과 기술 위험. 무거운 프로세스는 줄이고(tailor down) 가벼운 것은 늘린다(tailor up). | The goal is to do all the necessary work, but only what is necessary. | 87쪽(인쇄 86) |
| F05-058 | 23 | 시스템 안전 프로그램 계획(System Safety Program Plan)은 안전 필수 소프트웨어의 개발과 분석의 전제 조건이다. 조직 구조, 인터페이스, 분석, 보고, 평가, 자료 보존의 기준을 정하고, 분석의 일정, 결과 전달 방법, 모든 활동의 승인 절차를 다룬다. 조직(프로그램) 수준의 계획이 있고, 프로젝트 수준의 안전 계획은 프로그램 계획의 요건과 프로젝트 고유 요건을 어떻게 반영할지 기술한다. | outlines the organizational structure, interfaces, and the required criteria for analysis, reporting, evaluation, and data retention | 지정 범위 밖(23쪽). safety plan의 내용에 관한 주된 근거 |
| F05-059 | 101 | 개념 단계 작업(표 5-1): 소프트웨어 안전 계획을 만들고, 그 안에서 안전 노력을 계획하고 tailoring한다. 계획은 독립 문서일 수도, 시스템 안전 계획의 일부일 수도 있다. 소프트웨어 보증/IV&V는 이 계획을 검토한다. 같은 표에서 위험 추적과 문제 해결 프로세스, 위험 검증 행렬, make-or-buy 결정 참여, 계약 입력도 개념 단계 작업으로 든다. | The plan can be an independent document or part of the system Safety Plan. | 지정 범위 밖(101쪽) |
| F05-060 | 102 | 개념 단계 문서(표 5-2): 시스템 안전 계획은 소프트웨어를 하위 시스템으로 포함하고 작업(분석, 요구사항 추적)과 인원을 식별한다. 소프트웨어 관리 계획, 위험 관리 계획, 형상 관리 계획, V&V 계획, 품질 보증 계획에도 각각 소프트웨어 안전에 관한 항목이 들어간다. 99쪽은 개념 단계의 계획으로 Software Management, Development, Assurance, Safety Plan을 든다. | Include software as a subsystem. | 지정 범위 밖(99, 102쪽). 계획 목록은 NASA 기준 |
| F05-061 | 103 | 5.4 IV&V: 위험이 높은 소프트웨어의 고가 시스템에서 쓴다. IV&V는 개발 조직과 기술적으로, 관리적으로, 재정적으로 독립한 조직이 수행한다. 사내 소프트웨어 품질/제품 보증을 대체하지 않고 보완한다. 사용 여부와 수준은 개념 단계에서 정한다. | IV&V is performed by an organization that is technically, managerially, and financially independent of the development organization. | 103쪽(인쇄 102). 정의는 NASA 기준 |
| F05-062 | 103 | 안전 노력 수준별 개념 단계 기법(표 5-3, 그림으로 확인): 예비 위험 분석, 소프트웨어 하위 시스템 위험 분석, 소프트웨어 안전 요구사항은 Min, Mod, Full 모두 Mandatory이다. 체크리스트와 교차 참조는 Min과 Mod에서 Highly Recommended, Full에서 Mandatory이다. | Software Safety Requirements | 표의 기호는 텍스트로 안 읽혀 그림으로 확인했다. 줄일 수 없는 것의 예 |
| F05-063 | 265 | 11.9.1.3 프로세스 문제: 관리자는 사고의 맥락을 만들 수 있고 안전에 해로운 개발 환경을 만들거나 유지할 수 있다. 관리자 교육과 정책, 결정, 프로세스, 산출물에 대한 독립 평가가 필요하다고 적는다. 원인 유형으로 시스템 목표가 안전과 양립하지 않음, 일정 압박과 규칙 무시 압박, 의사소통 실패, 교육 부족, "safety culture 부족. 안전이 우선순위를 못 받음"을 든다. | Lack of safety culture. Safety is not given priority. | 지정 범위 밖(265쪽, 인쇄 264). safety culture의 정의가 아니라 문제 유형의 나열 |
| F05-064 | 282 | 12.2 계약자 개발 소프트웨어: 성과 기반 계약에서는 개발 방식을 명세하기 어렵고 결과가 기준이지만, 안전 필수 소프트웨어에서는 "어떻게"가 매우 중요하다. 고객은 계약자의 개발 프로세스를 들여다볼 수 있어야 한다 (문제를 일찍 찾고 최종 시스템에 신뢰를 주기 위해). | with safety-critical software and systems, the how is very important | 282쪽(인쇄 281). NASA 계약 맥락 |
| F05-065 | 282 | 12.2.1 계약자 선정: 기술 전문성, 개발 프로세스, 과거 실적이 요소이며 SW-CMM, ISO-9000 같은 역량 틀은 한 방법이다. 프로세스 외에 팀원의 전문성, 팀의 기능, 프로세스를 실제로 따르는 정도도 중요하다. 과거 실적은 실제로 만들 팀의 것이 회사의 다른 부서에 대해 정한 역량 수준보다 높게 평가해야 한다. | factors beyond the process are also important, such as the expertise of team members | 282쪽. 내부 평가인지 외부 평가인지, 어느 부서가 평가되었는지를 묻는다 |
| F05-066 | 283 | 12.2.2 계약에 넣을 항목(NPG 8715.3): 안전 요구사항, 임무 성공 요구사항, 위험 관리 요구사항, 계약자의 안전 방침과 프로젝트 안전 계획과 위험 관리 계획의 제출과 평가, 사고와 아찔한 사례(close call)와 교훈 보고, NASA의 감시(surveillance), 하청에 대한 안전 요구사항 전달. | require that the safety requirements are passed on to sub-contractors | 283쪽. 성과 기반 계약에도 감시 요구가 있다고 적는다 |
| F05-067 | 283 | 안전 요구사항은 명세에 명확히 적어야 하며, 요구사항 변경은 대개 계약자에게 더 많은 돈을 주는 것이므로 시스템 안전을 미리 생각해 시스템 명세에 쓰라고 한다. 안전 검증 절차(Safety Compliance Data Package와 단계별 3단계 심사)를 누가 준비하고 발표할지 계약에 명시해야 한다. | specify in the contract who has responsibility for preparing and presenting the Safety Compliance Data Package | 283쪽. 심사 단계는 NASA JSC 절차 |
| F05-068 | 284 | 분석과 시험: 안전과 임무 보증에 필요한 분석, 특별 시험, 누가 하고 누가 결과를 보는지를 계약에 명시해야 한다. 성과 기반 계약에서는 대개 계약자가 분석까지 모두 한다. | the tests and analyses should be spelled out, as well as the responsible party | 284쪽 |
| F05-069 | 284 | 소프트웨어 보증: 성과 기반 계약에서는 계약 회사 내부의 관리적으로 독립된 그룹이 맡는 것이 보통이다. 다른 계약에서는 NASA의 SA 인원이 맡을 수 있다. 누가 하든 SA 기능의 요구를 계약에 넣어야 하며, 세부 역할 대신 인정된 규격을 요구하거나 NASA 프로젝트 관리자가 승인하는 SA 계획을 지정해도 충분하다. | the SA role is usually handled by a managerially independent group within the contracting company | 284쪽 |
| F05-070 | 284-285 | 계약자 감시(12.2.2.4): 요구사항을 부과할 때 준수 감시 방법도 함께 넣어야 한다 (지표, 인증 같은 확인 자료 제출). 인도물(12.2.2.5)에는 운영 소프트웨어 외에 관리, 개발, 보증, V&V, 시험, 형상 관리 계획, 설계 문서, 소스 코드, 개발 도구, 설정 파일, 시뮬레이터, 시험 소프트웨어, SA 보고서와 감사 결과, 검사 보고서, 시험 절차와 보고서가 들어간다. | what happens after the system is delivered and the contractor is no longer part of the project | 인도 후 계약자가 없어져도 고객이 유지보수해야 한다는 이유 |
| F05-071 | 286 | IV&V 또는 IA의 필요 평가는 계약 수여 전에 완료하고 합의해야 한다. 변경 프로세스는 계약에 넣고, 변경 통제 위원회에 개발, 소프트웨어 보증, 시스템, 안전, 관리의 대표를 두며 NASA 고객 대표가 위원회에 참여하거나 결정을 검토해야 한다. | A NASA/customer representative should be part of the change board, or at least review the board decisions. | 286쪽 |
| F05-072 | 286 | 요구사항 명세는 고객이 공식 검사(formal inspection)로 완전하고 모호하지 않음을 확인해야 한다. 대부분의 소프트웨어 문제는 사실 명세 문제이며 소프트웨어가 진행될수록 수정이 점점 비싸진다. 계약자와 고객 사이에 해석 차이를 일찍 잡는 소통 장치도 필요하다. | Most software problems are actually specification problems | 286쪽. HSE의 명세 단계 44%와 같은 방향의 서술(NASA는 수치 없음) |
| F05-073 | 286-287 | 감시 방식 두 가지: oversight(NASA 인력이 계약자 팀의 일원처럼 같이 일하며 SA, 감사, 시험 입회, 안전 분석을 수행)와 insight(손을 떼는 방식, 계약자가 SA 기능을 모두 수행하고 NASA는 SA 기록을 검토하고 개발과 SA 프로세스를 표본 감사하고 주요 검토에 참여). 방식과 구체 내용은 감시 계획(surveillance plan)에 적는다. | Oversight is an in-line approach, where NASA personnel work with the contractor as a team member. | 286쪽(oversight, insight 시작), 287쪽(감시 계획, 누가/무엇을) |
| F05-074 | 287 | 시험 환경이 바뀌었거나 NASA가 안전 검증 시험을 입회하지 않았으면, 위험의 중요도에 따라 시험을 다시 해야 한다. 인수 시험은 기능 시험 이상이어야 하며 "반드시 동작", "절대 동작 금지" 기능과 오류 처리를 모두 검증한다. | those tests should be rerun (depending on the criticality of the hazards) | 287쪽 |

## 4. nhtsa-safety-standards-assessment (DOT HS 812 285, 2016-06, ISO 26262:2011 기준. 인쇄 쪽 번호 = PDF 쪽 - 10)

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| F05-075 | 32 | 3.9: ISO 26262, MIL-STD-882E, DO-178C는 모두 lifecycle 고려를 담지만, 어떻게 lifecycle 안전 요구사항을 만들지에 대한 논의는 모두 매우 높은 수준이고 지침이 제한적이라고 보고서가 평가한다. ISO 26262의 lifecycle에는 생산, 운영, 서비스(유지보수와 수리), 폐기가 있다 (Part 7). | the discussions regarding how to generate lifecycle safety requirements are very high level | 보고서 저자의 평가. 2011 판 기준 |
| F05-076 | 32 | 제조 공정이 안전에 미치는 영향을 ISO 26262는 다루지만(MIL-STD-882E는 아님), 제조 공정 관리에서 안전 필수 매개변수를 찾는 지침은 없다. 업계에서 흔한 방법으로 Process FMEA를 든다. | provides no guidance on how to identify important safety-critical parameters for manufacturing process control | 2011 판 기준 평가 |
| F05-077 | 33 | 3.11: MIL-STD-882E는 인증 규격이 아니며 검토, audit, 위원회 지원의 세부는 프로그램 관리자와 계약자에게 맡긴다. DO-178C는 소프트웨어를 단독으로 인증하지 않고, 시스템에 포함되어 lifecycle 산출물의 검토로 승인한다. | software approval is based on the documents produced to support the software lifecycle | 항공 규격 설명(원문을 보고서가 인용) |
| F05-078 | 34 | ISO 26262도 DO-178C와 비슷하게 작업 산출물을 모아 "safety case"를 만들고, 그것으로 ISO 26262 프로세스의 준수를 보인다고 보고서가 설명한다. 보고서는 이 용어가 안전 공학 일반의 safety case와 달라 혼동될 수 있다고 지적한다. | The safety case is then used to demonstrate the adherence to the ISO 26262 process. | 2011 판 기준. 용어 지적은 보고서 저자의 의견 |
| F05-079 | 34 | ISO 26262 Part 2 표 1이 ASIL별로 요구하는 confirmation review는 "개발자, 프로젝트 관리, 작업 산출물 저자에 대한 독립"을 요구한다고 보고서가 인용한다. | independence with regard to the developers of the item, project management and the authors of the work product | 2011 판 Part 2 Table 1(보고서가 인용한 것을 옮김). ASIL별 구분 내용은 이 쪽에 없음. 이 문서에 functional safety audit, assessment는 나오지 않음 |
| F05-080 | 34 | 보고서의 비판: 독립 검토자는 시스템 설계를 잘 모를 수 있고, 개발팀은 확증 편향 때문에 안전 목표가 달성되었다는 강한 증거를 제시한다. 그러면 기술에 깊이 들어 있지 않은 독립 검토자는 모르는 위험(unknown-unknowns)을 찾지 못할 수 있다. 회사에 분야별 전문가가 많지 않아 진짜 독립한 검토자를 찾기 어렵다. | A truly independent reviewer may be hard to find. | 보고서 저자(Volpe 연구 팀)의 의견이며 ISO 26262의 주장이 아님 |
| F05-081 | 34 | 보고서가 제안한 대안: 개발팀이 설계의 모든 단계(위험 분석, 위험 평가, 요구사항 정의 등)에서 견실한 시스템 공학 모범 사례를 쓰도록 하는 것이 더 효과적일 수 있다. | let the engineering team ensure that solid systems engineering best practices are used in all stages | 저자 의견. 독립성 요구를 대체하는 것이 아니라 대안으로 제시 |
| F05-082 | 15 | ISO 26262가 safety culture를 키우는 것과 안전 공학 관리를 구현하는 것의 중요성을 강조한다고 보고서가 적는다. | It also emphasizes the importance of fostering a safety culture and implementing safety engineering management. | 지정 범위 밖(15쪽). 2011 판 기준 |

## 5. nhtsa-etc-ev-fsa (DOT HS 812 656, 2020-03, Volpe, EV 가속 제어 시스템의 기능 안전 평가. 인쇄 쪽 번호 = PDF 쪽 - 16)

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| F05-083 | 19 | 이 연구는 ISO 26262 프로세스를 따라 개념 수준에서 기능의 무결성 요구사항을 찾는다. ISO 26262가 IEC 61508을 바탕으로 한 기능 안전 규격이며, Part 3이 시스템 공학의 concept phase에서 규격을 적용하는 단계를 기술한다고 설명한다. | Part 3 of ISO 26262 describes the steps for applying the standard during the concept phase of the system engineering process. | 판 표기는 이 쪽에 없고 참고문헌은 "FDIS 2011"이다 (ISO 26262 Final Draft 2011) |
| F05-084 | 20 | 그림 1(안전 분석과 요구사항 개발 프로세스, concept phase 기준) 순서: Item Definition(시스템 범위와 정의, 블록 다이어그램) -> Vehicle Level Hazard Analysis(HAZOP, STPA 1단계) -> Vehicle Level Hazards -> Risk Assessment(ASIL) -> Vehicle Level Safety Goals with ASIL -> Safety Analysis(기능 FMEA, STPA 2단계) -> Functional Safety Concept(1 고장 검출과 완화, 2 safe state, 3 운전자 경고와 degradation 전략, 4 시스템 요소에 할당) -> Functional Safety Requirements. | Safety Analysis and Requirements Development Process | 그림은 텍스트가 아닌 이미지이며 눈으로 읽었다. 그림은 Part 3을 따르되 이전 연구의 경험으로 일부 수정했다고 19쪽이 적는다 |
| F05-085 | 20 | 그림 1 아래 주석: ISO 26262는 특정 위험/안전 분석 방법을 권하거나 지정하지 않으며, 다른 타당한 방법을 분석가 재량으로 쓸 수 있다. | ISO 26262 does not recommend or endorse a particular method for hazard and safety analyses. | 이 보고서가 쓴 HAZOP, STPA, FMEA는 그림의 예 |
| F05-086 | 13 | 요약: 이 보고서는 구현 전략까지 다루지 않고, 일반 EV의 ACS/ETC(가속 제어/전자 스로틀 제어)에 대해 위험 분석 후 요구사항의 예를 낸다. 요구사항은 NHTSA의 공식 입장이 아니라고 각주가 밝힌다. | not intended to represent NHTSA's official position | 각주 1. 보고서의 문서 제목에 "functional safety assessment"가 들어가지만 ISO 26262의 assessment 활동이 아니라 연구 과제명이다 |

## 6. b737max-jatr (Joint Authorities Technical Review, 2019-10. 인쇄 쪽 번호 = PDF 쪽 - 20)

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| F05-087 | 50 | 권고 R6: FAA가 safety culture를 장려해 인증 요건 준수에 앞서 안전한 제품을 만드는 데 주된 초점을 두게 해야 한다. 기능은 단편이 아니라 항공기 수준에서 전체적으로 평가하고, 안전 분석 프로세스를 개발 보증 프로세스와 통합하며, 안전 분석의 가정을 의심해야 한다. | promote a safety culture that drives a primary focus on the creation of safe products | JATR(여러 항공당국 합동 검토)이 FAA에 하는 권고. 항공 규격 맥락 |
| F05-088 | 50, 52 | 설계 조직과 독립된 system safety 기능을 갖고, 항공기/시스템 설계 세부에 영향을 줄 권한을 가지며, 독립적으로 안전을 평가하도록 신청자에게 권장해야 한다. 안전 관리 체계(safety management system)가 그 방법 중 하나다. | have a system safety function that is independent from the design organization | R6와 R6.7. 의무가 아니라 "encourage" |
| F05-089 | 52 | R6.7은 설계 변경이 항공기 안전 운용에 영향을 줄 때마다 포괄적이고 통합된 위험, 고장, 안전 분석이 수행되게 하는 것이 그 독립 기능의 일이라고 적는다. | Such system safety function should ensure that comprehensive and integrated risk, failure, and safety analyses are performed | R6.7 |
| F05-090 | 53 | 관찰 O6.7-A: 보잉에 독립된 안전 그룹이 시스템 안전 분석을 조율하는지 확인하지 못했다. 각 시스템 팀이 설계와 관련 안전 평가를 모두 한다. 시험 비행 조종사가 핵심 설계 결정을 검증하는 데 자주 쓰이는 것은 엔지니어가 견실한 정보를 갖는 한 문제가 아니라고 적는다. | Each system team conducts both the design and related safety assessments. | 관찰(observation)이며 확정 판단이 아님. "could not identify" |
| F05-091 | 52 | 발견 F6.6-A: FHA 보고서가 설계를 이끄는 도구가 아니라 이미 정의된 설계를 문서화하는 데 쓰인다는 인식이 있다. STS와 FCC의 FHA는 B737 NG 보고서를 갱신한 것이며 MCAS의 새 위험을 찾아 설계 완화를 이끈 것으로 보이지 않았다. | they did not appear to be used as tools to identify new hazards related to MCAS and drive design mitigations | JATR의 평가. 안전 분석이 설계에 후행한 사례 |
| F05-092 | 52 | 발견 F6.5-A: MCAS를 하나의 완전한 기능으로 보는 통합 SSA가 수행되지 않았다. 안전 분석이 여러 문서에 흩어져 있었고 B737 NG의 SSA 일부를 충분한 평가 없이 B737 MAX에 재사용했다. | parts of the SSA from the B737 NG were reused in the B737 MAX without sufficient evaluation | 변경 관리와 재사용 분석의 사례 |
| F05-093 | 51 | 발견 F6.4-A: MCAS 도입으로 항공기 수준의 조종사 응답 가정이 무효가 되었으나, 완전한 작업량 평가는 수행되지 않았고 가정이 이전 프로그램에서 공식 검증 없이 이어졌다. | The same assumptions for flight crew responses to erroneous AOA were carried over from previous programs without formal validation. | F6.4-A |
| F05-094 | 51 | 발견 F6.1-B: 위험을 없애거나 설계 특징이나 경고로 완화하기 전에 조종사 조치를 주된 완화 수단으로 쓴 것은 안전한 설계를 위한 보잉 자체의 프로세스 지침에 맞지 않는다. | is not in accordance with Boeing's process instructions for safe design | 조직이 자체 규정을 따르지 않은 사례 |

## 7. b737max-house-report (미 하원 교통 인프라 위원회 최종 보고서, 2020-09. 인쇄 쪽 번호 = PDF 쪽 - 7)

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| F05-095 | 19 | 요약의 다섯 가지 주제(theme)가 설계, 개발, 인증과 FAA 감독에 영향을 줬다고 위원회가 적는다: 생산 압박, 결함 있는 설계 및 성능 가정, 은폐 문화, 이해 상충 대표, FAA 감독 구조에 대한 보잉의 영향. | five central themes that affected the design, development, and certification of the 737 MAX | 위원회(의회) 보고서이며 위원회의 판단이다. 다른 쪽의 사실 조사 결과와 구분해서 인용한다 |
| F05-096 | 19 | 1) 생산 압박: Airbus A320neo와 경쟁하기 위한 재정 압박이 비용 절감, 일정 유지, 생산 라인 지연 회피 노력으로 이어졌고, 목표가 공공의 안전을 위협한 사례가 있다고 한다 (20쪽에 이어짐). | There was tremendous financial pressure on Boeing and the 737 MAX program to compete with Airbus' new A320neo aircraft. | 위원회의 주장 |
| F05-097 | 20 | 2) 결함 있는 설계 및 성능 가정: MCAS를 단일 AOA 센서 입력으로 작동하게 허용했고 조종사가 오작동을 완화할 것으로 기대했다. 또 MCAS를 안전 필수(safety-critical) 시스템으로 분류하지 않아 FAA의 더 큰 정밀 검토를 피했고, MCAS의 동작이 보잉 자체 설계 지침도 위반했다고 한다. | Boeing also failed to classify MCAS as a safety-critical system | 위원회의 주장. 분류가 후속 감독 강도를 정한다는 서술 |
| F05-098 | 20-21 | 3) 은폐 문화: 보잉이 FAA, 고객, 조종사에게 중요한 정보를 숨긴 사례로 MCAS의 존재를 조종사에게 알리지 않음, AOA Disagree 경고가 대부분의 기체에서 작동하지 않는다는 것을 알리지 않음, 시뮬레이터에서 시험 조종사가 반응하는 데 10초 넘게 걸린 내부 시험 자료를 숨김을 든다. | Boeing withheld crucial information from the FAA, its customers, and 737 MAX pilots. | 위원회의 표현("Culture of Concealment") |
| F05-099 | 21 | 4) 이해 상충 대표: FAA의 감독 구조에서 보잉 직원인 Authorized Representative(AR)가 FAA를 대신해 적합성을 확인하는데, AR이 FAA에 중요한 정보를 알리지 않은 사례가 있다. 한 AR이 2016년에 내부적으로 우려를 제기했으나 FAA에 전달되지 않았고 설계 변경으로 이어지지 않았다. | creates inherent conflicts of interest that have jeopardized the safety of the flying public | 위원회의 주장. 제3자 독립성 상실의 사례 |
| F05-100 | 21 | 5) 보잉의 FAA 감독에 대한 영향: FAA 관리가 보잉의 요구로 FAA 자체 기술 전문가의 판단을 뒤집은 사례가 있고, FAA의 내부 safety culture 설문(초안, MITRE 작성, 2020-02-28)은 고위 간부가 업계의 사업적 결과에 지나치게 신경 쓴다고 보는 사람이 많다고 적는다. | overly concerned with achieving the business-oriented outcomes of industry stakeholders | 설문은 초안이며 위원회가 소장한 문서를 인용한 것. FAA 기술 전문가의 사기 저하도 언급 |

## 8. koopman-toyota-ua (Koopman, CMU, 2014-09-18 슬라이드. 저자는 이 사건의 원고 쪽 전문가 증인)

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| F05-101 | 2 | 저자 자신이 원고 쪽 전문가 증인으로 증언했다고 슬라이드가 밝힌다. 이 슬라이드의 모든 주장은 원고 쪽 전문가의 주장이다. | I testified as a Plaintiff expert witness | 지정 범위 밖(2쪽). 아래 모든 행에 적용 |
| F05-102 | 26 | 미국 차에는 인증 요건이 없고, 연방 자동차 안전 기준(FMVSS)은 소프트웨어 안전의 전형적인 주제를 다루지 않는다. 자동차 제조사는 MISRA 지침을 따를 의무가 없었으나 따를 수는 있었다. | Auto makers not required to follow MISRA guidelines | 2014년 시점의 미국. 슬라이드의 법 서술(원고 쪽 전문가) |
| F05-103 | 27 | Toyota는 MISRA 지침을 따랐다고 주장하지 않는다. 슬라이드는 NASA(의 조사 보고)가 감사 가능한 소프트웨어 프로세스 계획과 Toyota의 문서화된 safety argument를 공개하지 않았다고 적는다. Toyota 쪽 전문가의 의견은 현실적인 ETCS 결함이 없고 fail-safe가 막는다는 것이다. | NASA did not disclose an auditable software process plan | 원고 쪽 전문가의 주장. 슬라이드의 NASA가 무엇을 가리키는지는 문장에 없어 해석이 필요하다. 재판 증언 기록(Bookout)을 출처로 단다 |
| F05-104 | 46 | Safety Culture 슬라이드: V 프로세스의 일부(예: module inspection)에 대해 Toyota에 "아는 사람이 없었다". 점검하지 못했거나 안 한 부분에 대한 독립된 인증이 없었다. | No independent certification for parts they couldn't/didn't check | 원고 쪽 전문가의 주장(Bookout 증언 2013-10-11 인용) |
| F05-105 | 46 | 슬라이드가 인용하는 Toyota 직원 진술은 fail-safe가 있으므로 소프트웨어 이상은 급발진 주장과 관련이 없다는 것이다. 2007년 내부 이메일은 fail-safe 같은 기술이 엔지니어링 부서의 "DNA"에 없다고 적는다. | technology such as failsafe is not part of the Toyota's engineering division's DNA | 재판 증거에서 인용된 문장. 해석은 저자의 것 |
| F05-106 | 23 | 저자가 제시하는 안전 필수 소프트웨어의 "받아들여지는 관행"(SIL 접근)에는 SIL에 맞는 개발, 기술, 검증 방법, 프로세스가 실제로 작동하는지 확인(SQA), 좋은 아키텍처, 좋은 safety culture가 포함된다. | Good safety culture | 지정 범위 밖(23쪽). 저자의 목록 |

## 9. autosar-safety-measures (AUTOSAR CP R25-11, 문서 664. 인쇄 쪽 번호 = PDF 쪽, "45 of 72")

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| F05-107 | 45 | 3.3: AUTOSAR 표준은 정해진 lifecycle을 따르며 변경 관리로 강제하고, 정해진 AUTOSAR 버전을 쓰면 명세, 인터페이스, 동작이 명확해져 개발 중 systematic fault를 줄인다. AUTOSAR 명세 개발에는 여러 당사자의 검토가 있고 마일스톤과 검토 조건은 AUTOSAR Quality Management가 정한다. 작업 패키지에 사람을 배정하는 정의가 있다. | are defined by AUTOSAR Quality Management | AUTOSAR가 자기 명세 개발에 대해 하는 서술 |
| F05-108 | 45-46 | 3.4: 안전 관련 응용을 개발하는 구현자는 안전 개발 lifecycle이 적절한지 스스로 보장해야 한다. AUTOSAR가 강제하지도 제공하지도 않는 조치의 예(완전하지 않다고 밝힘): SEooC 정의, HARA/HAZOP, 전체 안전 개념, ASIL 식별, 종속 고장 분석, AUTOSAR safety case, confirmation measures, functional safety audits, conformance test, 구현 기법(낮은 복잡도, 방어적 프로그래밍, 코딩 규칙), 구현으로의 추적, 소프트웨어 통합 시험, AUTOSAR 명세에 대한 V&V, 구현에 대한 결함 보고. | must ensure that the safety development life cycle is adequate | 이 문서가 ISO 26262:2018을 참조하며(참고문헌 [1]) 용어 confirmation measures와 functional safety audits가 나오지만 정의는 없다. (기억) ISO 26262의 confirmation measure에는 confirmation review, functional safety audit, functional safety assessment가 있다 - 문서에서 확인 못함 |
| F05-109 | 46 | 공급자(AUTOSAR)가 주지 않는 항목 중 "confirmation measures"와 "functional safety audits"가 각각 한 줄로 나열된다. 쓰는 쪽에 남는 책임이라는 취지다. | No functional safety audits | 사실은 "제공하지 않음"의 목록이며 누가 해야 하는지의 독립성 수준은 없음 |
| F05-110 | 46 | 3.5: Safety Extensions 문서는 AUTOSAR 모델에 기능 안전 정보를 넣는 방법을 정해, 시스템의 기술 안전 개념 중 실현에 관련된 부분을 표준 템플릿으로 기술하고 교환하며, 안전 요구사항과 AUTOSAR 모델 요소 사이의 추적성을 제공할 수 있다. | Describe and exchange the part of a (technical) safety concept of a system which is relevant for the realization | 공급망에서 안전 정보를 주고받는 수단의 예. development interface agreement라는 말은 없음 |

## 10. nasa-std-8739-8b (NASA-STD-8739.8B, 2022-09-08, 65쪽. 인쇄 쪽 번호 = PDF 쪽. 8719.13 표준을 흡수한 판)

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| F05-111 | 2 | 문서 이력: A판(2020)이 NASA 소프트웨어 보증 표준(8739.8)과 소프트웨어 안전 표준(8719.13)을 합쳤고 8719.13 표준을 취소했다. B판(2022)은 NPR 7150.2D에 맞춘 개정이다. | cancels the NASA-STD-8719.13 standard | 이 책의 nasa-gb-8719-13은 2004년 가이드북으로, 표준이 아니다. 두 문서를 구분해서 적는다 |
| F05-112 | 6 | 소프트웨어 보증과 소프트웨어 안전 계획(SA 계획 등)은 독립 문서일 수도, 소프트웨어 관리/개발 계획이나 프로젝트 SMA 계획의 일부일 수도 있다. 계획은 SA/안전 조직과 프로젝트 관리자가 만들고, SMA 조직이 소프트웨어 계획과 문서에 서명 권한이 있다. | can be standalone documents or incorporated within other documents | 1.3절. 계획의 형식은 프로젝트가 정한다 |
| F05-113 | 6 | 1.4: 이 표준의 tailoring은 프로그램/프로젝트 요건의 일부로 문서화하며, 담당 센터 기술 권한(TA)이 승인한다. | Tailoring of this standard for application to a specific program or project is documented | 6쪽 |
| F05-114 | 15 | 4.1: 소프트웨어 보증이 효과가 있으려면 관리자가 보증 기능을 이해하고, 숙련된 자원을 제공하고, 보증 기능이 준 정보를 받아 행동해야 한다. 표준은 인수자와 공급자 양쪽 역할에 적용되며, 한 조직이 자체로 쓸 수도 있고 여러 조직이 쓸 수도 있다. | Management receives and acts upon information provided by the software assurance function | 15쪽 |
| F05-115 | 15-16 | 4.2: 소프트웨어는 위험 상황을 일으키거나 기여함, 통제나 완화를 제공함, 안전 필수 기능을 통제함, 사고 시 피해를 줄임, 위험 상태를 검출하고 보고하고 시정함 중 하나 이상이면 안전 필수로 분류한다. 위험 분석에서 결정되고 추적 가능해야 한다. | Software is classified as safety-critical if it meets at least one of the following criteria | 15-16쪽 |
| F05-116 | 16 | 4.3: 프로젝트 관리자가 표 1의 소프트웨어 보증/안전 활동을 수행해야 한다. 역할과 책임은 프로젝트의 범위와 규모에 맞게 프로젝트 안에서 위임할 수 있다. 센터 SMA 책임자가 SMA 기술 권한을 지정한다. | roles and responsibilities for completing these requirements may be delegated within the project | 16쪽 |
| F05-117 | 10 | 용어 정의(IEEE 정의 인용): audit은 감사 증거를 얻고 객관적으로 평가해 감사 기준이 충족된 정도를 정하는 체계적이고 독립적이며 문서화된 프로세스다. 내부(1자) 또는 외부(2자, 3자) audit이 있다. assess는 계획이나 작업물 요구사항에 비춰 결과를 판단하는 것이며 시정 조치를 독립적으로 추적해 종결하는 것을 포함한다. | systematic, independent, and documented process for obtaining audit evidence | 10쪽. audit 정의의 주석 |
| F05-118 | 17-19 | 표 1의 소프트웨어 보증 과업: 소프트웨어 보증 계획을 NASA-HDBK-2203의 내용에 따라 만들고 안전을 포함한다(17쪽). 검토와 audit 마일스톤이 정의되었는지 확인한다(18쪽). 개발 프로세스와 관행의 audit을 최소 2년에 한 번 수행한다(19쪽). 이슈, 발견, 위험이 종결까지 추적되는지 확인한다. | Perform audits on software development processes and practices at least once every two years. | 계획의 구체 내용은 NASA-HDBK-2203에 있고 이 문서에 없음 |
| F05-119 | 48 | 4.4.1.2: IV&V의 독립성은 세 가지 매개변수로 정의된다. 기술적 독립(분석 수행 인원이 시스템 또는 그 요소의 개발에 참여하지 않음), 관리적 독립(개발 및 프로그램 관리 팀과 다른 조직에 속하고, 분석 대상, 방법, 일정을 자체 결정하며, 결과를 제출할 때 개발 조직의 승인이 필요하지 않음), 재정적 독립(IV&V 예산의 통제권이 개발 조직과 독립한 그룹에 있음). | Three parameters define the independence of IV&V: technical independence, managerial independence, and financial independence. | 48쪽. 독립성을 항목으로 나눈 가장 명시적인 서술 |
| F05-120 | 49-50 | IV&V는 lifecycle 전체에 걸쳐 일찍 시작하고, "appropriate assurance" 원칙에 따라 위험과 자원을 맞춰 프로젝트별 IV&V를 정하며, 그 tailoring을 IV&V 프로젝트 실행 계획에 문서화한다. 독립적이지만 IV&V 제공자는 프로젝트의 전체 안전과 위험 완화 보증 전략의 일부이며 결과는 전체 보증 평가에 합친다. | While independent, the IV&V Provider is still a part of a project's overall safety and risk mitigation software assurance strategy. | 49쪽(원칙), 50쪽(주석) |
| F05-121 | 56 | IV&V 제공자는 위험 사건과 원인 또는 완화 기법으로 추적되는 각 소프트웨어 요구사항을 독립 시험으로 검증하고, 프로젝트의 NASA 품질 audit, 평가, 검토에 모두 참여한다 (4.4.2.46, 4.4.2.48). | verify through independent testing each of the software requirements that trace to a hazardous event | 56쪽 |
| F05-122 | 56-57 | 4.5 tailoring: 프로젝트의 SMA TA가 tailoring한 요구사항을 검토하고 동의해야 한다. 3단계: 소프트웨어 분류 결정, 요구사항 매핑 행렬, SA TA의 tailoring. 완화 요청에는 근거, 위험 평가, 정당화 자료가 들어가야 하며 영향받는 다른 조직(안전, 품질, 보안, 건강)과 협의하고 동의를 받는다. 분류가 바뀌면 계획을 갱신한다. | The request for relief from a requirement includes the rationale, a risk evaluation, and reference to all material that justifies supporting acceptance. | 56-57쪽. 줄이는 데 근거와 승인이 필요하다는 직접 서술 |

## 장 계획이 기대했지만 문서에 없던 것

- ISO 26262의 역할 정의, 독립성 수준, confirmation review, functional safety audit, functional safety assessment의 정의, development interface agreement: 받은 문서에 없다. 유일한 흔적은 NHTSA 평가 보고서 34쪽의 confirmation review 독립성 인용 한 줄(2011 판 Part 2 Table 1)과 AUTOSAR 46쪽의 용어 목록이다.
- ISO 26262가 safety plan에 요구하는 항목: 문서에 없다. NASA(F05-058~060, F05-112, F05-118)가 일반적인 안전 계획 서술을 준다.
- 자동차 쪽 tailoring 서술: 없다. 자동차 규격의 tailoring은 이 문서들에서 확인하지 못했다. NASA(F05-043~053, F05-122)와 HSE(F05-024, F05-027)만 있다.
- V-model: 받은 문서에 V-model 그림이나 서술이 없다. NASA 가이드북은 waterfall 등 모델을, 슬라이드와 HSE는 safety lifecycle(순환형 그림)을 보여 준다.
- safety culture의 정의: 없다. HSE(F05-020), NASA 가이드북(F05-063), JATR(F05-087), 하원 보고서(F05-095~100)가 사례와 지적만 준다.
- 공급망 책임 분담의 자동차 사례: development interface agreement가 없다. AUTOSAR 46쪽(제공하지 않는 항목)과 NASA 12.2절(계약)이 예다.
- HSE 표본(34건)의 선정 기준과 모집단: 6쪽은 HSE에 알려졌거나 내부 보고서에서 왔다고만 적고 선정 기준은 적지 않는다.
