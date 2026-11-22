# 6장 근거 문서에서 뽑은 사실 (읽기 기록)

대상: 6장 "Hazard analysis and risk assessment" (plans/ch06-hara.md). 읽은 날: 2026-11-23.

- 쪽 칸은 PDF 파일의 몇 번째 쪽이다. 문서에 인쇄된 쪽 번호가 다르면 절 머리에 차이를 적는다.
- 인용은 줄바꿈을 합치고 따옴표와 줄표를 ASCII로 바꿨다. 그 밖에는 원문 그대로다.
- 이 장의 규격 문서 (ISO 26262, IEC 61508)는 받지 못했다. ISO 26262의 용어는 2차 자료가 적은 대로만 옮겼다. 보고서가 따른 규격은 ISO 26262의 2011년 최종 초안 (FDIS)이다.
- `(기억)`은 문서에서 확인하지 못한 내용이다. 원고의 근거로 쓰지 않는다.
- 원고에 쓰기 전에 그 쪽을 직접 열어 확인한다 (RULES.md 5.2절).

## 1. nhtsa-etc-ev-fsa (NHTSA/Volpe, Functional Safety Assessment of a Generic Accelerator Control System With Electronic Throttle Control in Electric Vehicles, DOT HS 812 656, 2020. PDF 쪽 = 인쇄 쪽 + 16)

약어: ACS/ETC = accelerator control system with electronic throttle control, EV PCM = 전기차 powertrain control module, AP = 가속 페달, BP = 브레이크 페달, BTO = brake throttle override.

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| F06-001 | 37 | 보고서의 표 1은 vehicle-level hazard를 운전자의 행동, 차량의 반응, hazard의 세 열로 적는다. 가속 쪽 (H1, H1.a, H2, H3), 감속 쪽 (H4, H5), 둘 다에 걸치는 것 (H6), 움직임과 무관한 것 (H7)으로 묶는다. | "Vehicle-Level Hazards and Definitions" | 표의 머리글. H1.a를 빼면 hazard는 일곱 개다. 지금 원고와 scope.md는 다섯 개만 쓴다 |
| F06-002 | 37 | H1 (Potential Uncontrolled Vehicle Propulsion)은 운전자가 가속을 요구하지 않았거나 준 것보다 적게 요구했는데 운전자가 고른 방향으로 가속하는 것이다. 보고서는 이것이 unintended acceleration과 같은 뜻이라고 한다. H1.a는 같은 hazard가 차량 속도 0에서 일어나는 경우다. | "Potential Uncontrolled Vehicle Propulsion When the Vehicle Speed is Zero" | H1의 정의 문장은 같은 쪽에서 "any vehicle acceleration that the driver did not purposely cause to occur"를 인용한다 |
| F06-003 | 37 | H2 (Potential Insufficient Vehicle Propulsion)는 차가 운전자가 요구한 수준이나 요구한 비율로 가속하지 않는 경우다. | "does not accelerate to the level commanded by the driver" | 운전자가 가속을 요구한 상황이 전제다 |
| F06-004 | 37 | H3 (Potential Vehicle Movement in an Unintended Direction)은 운전자의 명령에 따라 가속은 하지만 운전자가 고른 방향과 다른 방향으로 가속하는 경우다. | "Potential Vehicle Movement in an Unintended Direction" | 지금 원고의 "잘못된 방향"에 해당한다 |
| F06-005 | 37 | H4 (Potential Propulsion Power Reduction/Loss or vehicle stalling)는 운전자가 일부러 일으키지 않은 모든 정도의 감속이다. | "incidents where there is any degree of" | 지금 원고의 "구동력의 감소나 상실"에 해당한다 |
| F06-006 | 37 | H5 (Potential Insufficient Vehicle Deceleration)는 운전자가 가속 페달의 각도를 줄였을 때 차가 요구한 수준이나 비율로 감속하지 않는 경우다. | "or at the rate commanded by the driver when the" | 지금 원고의 "감속 부족"에 해당한다 |
| F06-007 | 37 | H6 (Potentially Allowing Driver's Command to Override Active Safety Systems)는 설계상 ACS/ETC가 능동 안전 시스템의 토크 요구를 따라야 하는데 운전자의 입력을 따르는 경우다. 각주는 운전자의 명령이 모든 능동 안전 시스템보다 우선하게 설계된 시스템에는 이 hazard가 해당하지 않을 수 있다고 한다. | "designed to give driver's command priority over all active safety systems" | 예제에는 그런 시스템이 없어 scope.md가 뺀다 |
| F06-008 | 38 | H7 (Potential Electric Shock)은 움직임과 무관한데도 hazard로 넣었다. ACS/ETC의 기능에서 직접 나오므로 ISO 26262 Part 3 Clause 1에 따라 범위 안이라고 한다. | "even though it is not related to vehicle motion" | 보고서가 ISO 26262를 이렇게 읽었다는 서술이다 |
| F06-009 | 57 | 표 23은 hazard별 ASIL을 준다. H1 D, H1.a B, H2 C, H3 C, H4 D, H5 C, H6 D, H7 B. | "Table 23. Vehicle-Level Hazards and Corresponding ASIL" | 표의 제목. 표의 숫자만 있는 줄이므로 제목을 인용한다 |
| F06-010 | 57 | H1.a의 B는 차량 속도가 0일 때만 동작하는 기능 (예: 언덕에서 뒤로 밀리지 않게 하는 hill-holder)에 대한 등급이다. 낮은 속도의 충돌이어서 severity가 낮아진 것이 이유라고 적는다. | "features that only operate when vehicle speed is zero" | C-06-007과 겹친다 |
| F06-011 | 57 | H2와 H5의 C에는 각주가 붙는다. 이 hazard의 ASIL 평가는 객관적인 자료가 없어 분석자마다 달랐다. 보고서는 severity, exposure, controllability 세 평가 모두에 객관적인 자료가 쉽게 구해지지 않는다고 한다. | "varied among safety analysts in the absence of objective data" | C-06-006과 겹친다. H1, H3, H4에는 이 각주가 없다 |
| F06-012 | 57 | H6은 자기 평가를 따로 하지 않는다. H6의 영향은 H1, H2, H4, H5에 들어 있으므로, 그 넷 가운데 가장 엄격한 등급을 받는다. | "The effects of H6 are contained in H1, H2, H4, and H5." | 그래서 H6은 D이고, 별도의 Appendix F 표가 없다 |
| F06-013 | 56 | ISO 26262는 운전 상황마다 매긴 등급 가운데 hazard마다 가장 엄격한 것을 고르라고 요구한다고 보고서가 적는다. | "ISO 26262 requires the most severe ASIL be chosen for each hazard." | |
| F06-014 | 175 | Appendix F는 hazard 일곱을 아홉 개의 표로 나눈다. H1은 destabilization이 없는 경우 (F-1)와 있는 경우 (F-2), H4도 없는 경우 (F-3)와 있는 경우 (F-4)로 나뉜다. H1.a는 F-5, H2는 F-6, H5는 F-7, H3은 F-8, H7은 F-9다. | "Table F-2: Potential Uncontrolled Vehicle Propulsion With Destabilization" | destabilization의 정의는 본문에서 찾지 못했다 (끝의 "찾지 못한 것") |
| F06-015 | 178 | H1에서 destabilization이 없는 경우 (표 F-1)의 가장 나쁜 줄은 중속 (40-100 kph) 시골길, 교통량 많음이나 적음, 시야와 노면 좋음, 충돌 시나리오는 다른 차나 장벽과 부딪치는 것, E4 S3 C2로 ASIL C다. 이 표에는 C3인 줄이 없다. | "Uncontrolled Propulsion Without Destabilization" | 지금 원고의 표 2번 줄이다. 표 제목의 쪽은 176쪽이다 |
| F06-016 | 183 | H1에서 destabilization이 있는 경우의 가장 나쁜 줄은 고속 (100-130 kph), 교통량 많음이나 적음, 시야와 노면 좋음, 앞차나 장벽과 충돌, E4 S3 C3로 ASIL D다. 시야 나쁨과 미끄러운 노면은 E3으로 C다. | "Table F-2: Potential Uncontrolled Vehicle Propulsion With Destabilization" | 지금 원고의 표 1번 줄 (S3 E4 C3 D)이 이 줄이다. 원고에는 destabilization의 구분이 없다 |
| F06-017 | 176 | H1의 주차장 출발 줄은 E4 S2 C2로 ASIL B다. 보행자가 적고 시야가 좋은 상황이고, 충돌 시나리오는 낮은 속도로 보행자와 부딪치는 것이다. | "The vehicle runs into a pedestrian at low speed." | 지금 원고의 표 3번 줄이다 |
| F06-018 | 196 | H1.a의 표에서 가장 높은 줄은 B다. 기어 D나 R, 브레이크를 밟은 채 정지, 보행자 많음, 고장이 크리프 토크에 맞선 제동 토크를 이길 만큼의 토크를 만든다는 가정, E4 S2 C2다. 같은 조건에 보행자가 적으면 C1로 A다. | "Table F-5: Potential Uncontrolled Vehicle Propulsion When the Vehicle Speed Is Zero" | P나 N 기어는 충돌 시나리오가 "None"이다. 지금 원고의 표 4번 줄 (C1, A)이 이 표의 한 줄이다 |
| F06-019 | 197 | H1.a 표에서 언덕 정지 (hill-hold) 중 브레이크 없이 D 기어일 때 구동 토크가 줄어 차가 뒤로 구르는 줄은 E2 S1 C0이고 ASIL이 없다 (None). 신호 대기 중 교통량이 많은 줄은 E4 S1 C2로 A다. | "The vehicle rolls back." | |
| F06-020 | 201 | H2에서 가장 높은 줄은 C다. 고속 (100-130 kph) 추월, 시골길, 시야와 노면 좋음, 요구한 속도에 이르지 못해 다른 차가 정면으로 들이받는 시나리오, E3 S3 C3다. 사고 가능성이 없는 줄은 C0이고 ASIL이 None이다. | "another vehicle runs into the vehicle head on" | 사고로 이어지지 않는 상황이 표의 많은 줄을 차지한다 (198쪽) |
| F06-021 | 210 | H5에서 가장 높은 줄은 C다. 전제는 BTO 상태이고, ACS/ETC가 정상이고, AP와 BP를 함께 밟았고, 속도가 줄긴 하지만 요구한 비율로는 줄지 않는 것이다. 고속, 교통량 많음이나 적음, 시야와 노면 좋음, E4 S3 C2다. | "The driver responds to traffic conditions by reducing speed" | 차가 앞차나 장벽과 부딪치는 시나리오다. 주차장 출발 줄은 E4 S2 C1로 A다 (204쪽) |
| F06-022 | 215 | H3의 표에서 줄들은 모두 C3이다 (EPS가 틀린 방향의 토크를 만든다는 가정). 가장 높은 줄은 C이고, 주차장 출발에 보행자 적음 (E4 S2 C3), 보행자 많음 (E3 S3 C3), 시내 정체 구간에 보행자 있음 (E3 S3 C3)이 그것이다. | "EPS faults and produces torque in the wrong direction" | 216쪽에 보행자 없는 시내 줄 (E4 S1 C3 B, E3 S1 C3 A)이 이어진다. C3인 까닭은 이 표에 적혀 있지 않다 |
| F06-023 | 192 | H4에서 destabilization이 있는 경우의 가장 나쁜 줄은 D다. 후륜 구동 차량이라는 가정, 고속 (100-130 kph), 교통량 많음이나 적음, 시야와 노면 좋음, 가속을 잃어 뒤차가 들이받는 시나리오, E4 S3 C3다. | "associated with rear-wheel drive vehicles" | 지금 원고의 "구동력 상실은 D"의 근거다. 원고에 후륜 구동 가정은 없다 |
| F06-024 | 189 | H4에서 destabilization이 없는 경우 (표 F-3)의 가장 높은 줄은 C다. 고속 (100-130 kph) 시골길 교통량 많음이나 적음에 시야와 노면 좋음은 E4 S3 C2, 고속 추월은 E3 S3 C3이고, 가속을 잃어 뒤차나 마주 오는 차가 들이받는 시나리오다. | "Propulsion Power Reduction/Loss or Vehicle Stalling Without Destabilization" | 같은 hazard가 destabilization 여부로 C와 D로 갈린다. 표 제목의 쪽은 186쪽이다 |
| F06-025 | 217 | H7의 표는 세 상황을 든다. 고전압 전선을 만지는 중이면 E2 S3 C3로 B, 충돌로 고전압이 드러났으면 E1 S3 C3로 A, 주행 중 safe state 때문에 버스 방전이 필요한 상황은 E0이고 ASIL이 없다. | "Exposure to high voltage in this scenario is almost impossible" | 인용은 E0 줄의 충돌 시나리오 칸이다. 이 hazard는 S, E, C 변수 표 (표 17)를 쓰지 않고 상황 세 개를 따로 만들었다 (53쪽) |
| F06-026 | 52 | ASIL 평가의 절차: (1) 운전 상황을 찾는다, (2) hazard마다 exposure 평가, 충돌 시나리오 찾기, severity 평가, controllability 평가, ASIL 찾기, (3) hazard에 가장 나쁜 ASIL을 준다. | "Assign the worst-case ASIL to the hazard." | 원고의 3장과 같은 순서다 |
| F06-027 | 52 | 보고서는 운전 상황 69개를 만들었고 부록 E에 적었다. 그 가운데 66개는 변수 10개와 그 상태로 설명된다. | "This study generates 69 vehicle operational situations" | 나머지 3개는 감전 hazard의 상황 (53쪽)이다 |
| F06-028 | 53 | 운전 상황의 변수 10개와 상태 수는 이렇다. 속도 7 (매우 높음, 높음, 중간, 시내, 시내 매우 낮음, 주차장 V=0, 신호 정지 V=0), 교통량 2, 시야 2, 보행자 3, 시골길 여부 2, 철도 건널목 3, 노면 2, 운전 동작 4 (정체 반복, 추월, 회피, 직진이거나 정지), 브레이크 페달 2, 기어 5 (P, R, N, D, hill hold가 켜진 D). | "Variables and States for Description of Vehicle Operational Situations" | 변수의 조합을 다 열거하면 상황은 훨씬 많아진다. 69개는 그 일부다. 변수 표는 "현재의 산업 관행"을 따랐다고 같은 쪽 앞에서 적는다 (52쪽) |
| F06-029 | 52 | 운전 상황의 예: 고속 (100 kph 초과, 130 kph 미만), 교통량 많음, 시야와 노면 좋음. 시내, 교통량 많고 보행자 있음, 16 kph 넘는 정체 반복, 시야 나쁨, 노면 미끄러움. | "Driving at high speeds (100 kph < V < 130 kph), heavy traffic, good visibility" | 지금 원고의 표 1번과 같은 상황이다 |
| F06-030 | 174 | 부록 E의 일부 상황은 변수의 두 상태를 슬래시로 묶어 한 줄로 적는다. 예: 고속, 교통량 많음이나 적음, 시야 좋음이나 나쁨, 노면 좋음이나 미끄러움. | "light/heavy traffic, good/low visibility, and good/slippery road conditions" | 묶인 줄의 S, E, C는 한 값만 적힌다. 묶음 안에서 가장 나쁜 값인지는 적혀 있지 않다 |
| F06-031 | 53 | 감전 hazard에는 위 변수 표를 쓰지 않았다. 상황 세 개를 따로 만들었다. 고전압 전선을 만지는 중, 충돌로 고전압이 드러난 상태, 주행 중 safe state가 버스 방전을 요구하는 상황. | "Therefore, the variables in Table 17 were not used" | 감전은 차량 운동 hazard와 상황이 달라서라고 적는다 |
| F06-032 | 101 | 운전 상황은 처음에는 안전 전문가의 경험과 알려진 주행 사이클로 만들었다. 그 뒤에 변수 표 (표 17)를 만들고, 변수와 상태의 가능한 조합을 모두 열거해 전문가가 만든 목록과 견주었더니 상황이 더 나왔다. 그 상황을 평가해 더했다. | "The comparison found additional operational situations." | 상황 만들기의 방법에 관한 가장 직접적인 서술이다 |
| F06-033 | 102 | 보고서는 NHTSA의 충돌 자료의 변수와 코드, 자연주행 (naturalistic driving) 자료를 써서 변수 목록을 넓히면 상황이 더 완전해지고, 상황을 충돌 자료에 연결해 severity와 exposure를 정량으로 볼 수 있다고 제안한다. 조합이 너무 길어지므로 상황을 효율적으로 살피는 방법이 필요하다고도 적는다. | "Develop a comprehensive variable list describing the vehicle operational situations" | 제안일 뿐 이 보고서가 한 것이 아니다 |
| F06-034 | 21 | 보고서는 두 방법으로 hazard를 찾고, 결과는 vehicle-level hazard 목록 하나다. 등급을 매기고, 그 ASIL을 safety goal에 그대로 옮기는 것은 뒤 단계다. | "The output of the hazard analysis is a list of vehicle-level hazards." | C-06-001과 겹친다 |
| F06-035 | 21 | 각주: ISO 26262는 hazard나 safety 분석의 특정 방법을 권하거나 보증하지 않는다. 비슷하고 타당한 방법을 분석자의 재량으로 써도 된다. | "ISO 26262 does not recommend or endorse specific methods" | |
| F06-036 | 21 | 각주: HAZOP과 기능 FMEA와 달리 STPA는 표준 접근이 정의되어 공개된 적이 없어서, 보고서가 STPA를 더 자세히 설명한다. | "a standard approach has not been defined and published for STPA" | |
| F06-037 | 22 | HAZOP은 네 단계다. 시스템과 범위를 정하고, 시스템이 하는 기능을 모두 나열하고, 기능마다 guide word를 대어 설계 의도에서 벗어나는 방식을 적고, 그 벗어남이 차량 수준의 hazard가 될 수 있는지 평가한다. IEC 61882가 guide word 11개를 제안하지만 시스템에 맞게 고칠 수 있고, 이 보고서는 일곱 개를 썼다. | "the guidewords can be tailored to the particular system being analyzed" | guide word 일곱 개는 C-06-003에 있다 |
| F06-038 | 39 | HAZOP은 전기차 ACS/ETC의 기능 19개를 찾았다. 기능 17 (고장 감지와 완화), 18 (데이터 저장), 19 (모터 전류 값 제공)는 완전성을 위해 넣었다. | "The HAZOP study identifies 19 system functions for the EV ACS/ETC." | 기능 18에서 나오는 malfunction은 차량 수준 hazard가 되지 않는다고 40쪽이 적는다 |
| F06-039 | 40 | guide word 일곱 개를 기능 19개에 적용해 malfunction 132개가 나왔다. 각 malfunction이 차량 수준 hazard 하나 이상으로 이어질 수 있는지 평가했다. | "results in a list of 132 malfunctions" | 기능마다 6, 7, 9개다 (42쪽 표 3) |
| F06-040 | 41 | HAZOP 결과 표는 기능, guide word, malfunction, 운전 모드 (ON; D; Moving, ON; R; Moving, ON; D; Stopped, ON; R; Stopped 네 가지), 가능한 hazard의 열로 되어 있다. 같은 malfunction이 운전 모드에 따라 다른 hazard가 된다. 예: 가속 페달 위치를 전달하지 않는 것은 네 모드에서 H1과 H4와 H2, 앞의 두 모드에서 H5와 H3, 뒤의 두 모드에서 H1.a가 된다. | "ON: Engine on; D: Drive; R: Reverse" | "Not requested"는 hazard "None"이다. 올바른 정보가 의도하지 않게 오는 경우라서다 |
| F06-041 | 44 | STPA에서 손실 (loss)은 차량 충돌과 감전 둘이다. 처음의 hazard 목록은 문헌 조사와 엔지니어링 경험에서 만들고, STPA Step 1에서 UCA를 찾으며 고친다. | "The vehicle-level losses relevant to this study are a vehicle crash and electrocution." | 손실이 둘이고, hazard는 일곱이다 |
| F06-042 | 24 | 보고서가 인용한 STPA의 정의: 손실은 사람의 사망이나 부상, 재산 피해, 환경 오염 등을 낳는 원치 않고 계획하지 않은 사건이다. hazard는 최악의 환경 조건과 함께 시스템 수준의 손실로 이어지는 시스템 상태나 조건이다. | "a system state or set of conditions that, together with a particular set of worst-case" | 정의는 STPA 쪽 원문 (Leveson)을 보고서가 옮긴 것이다. 아래 4절의 handbook과 견준다 |
| F06-043 | 25 | STPA Step 1은 controller마다 control action을 모두 나열하고, control action마다 context variable (제어 입력과 환경 중 안전에 영향을 주는 것)을 정하고, 그 상태의 조합을 열거해 가능한 상태의 목록을 만든다. 보고서는 설계를 모르는 단계여서 process model variable 대신 context variable을 쓴다. | "The combinations of context variable states are enumerated to create an exhaustive list" | 운전 상황을 변수 조합으로 열거하는 방법이 HARA의 운전 상황 만들기와 닮았다 (기억) |
| F06-044 | 25 | UCA guide word 여섯 개를 control action과 context variable 조합마다 대어 hazard가 되는지 보고, 새로운 hazard가 나오면 vehicle-level hazard 목록에 더한다. 그 뒤 Quine-McCluskey 알고리즘으로 UCA 문장의 수를 줄인다. | "If new hazards are identified, add these hazards to the vehicle-level hazard list" | |
| F06-045 | 44 | STPA는 control action 13개를 다룬다. EV PCM이 11개 (BTO 모드 진입과 복귀, 토크 증감, 전진과 후진 토크, 냉각 켬과 끔, 고전압 버스 방전, 접촉기 열기, 직류 전력 요청)를 내고 TICM이 2개 (모터 전류 증감)를 낸다. | "This study identifies 11 control actions issued by the EV PCM" | 위 11개의 열거는 44쪽에서 시작해 47쪽까지 이어진다 |
| F06-046 | 48 | UCA guide word 여섯 개를 control action 13개의 context variable 상태 조합마다 대고, 그 control action이 차량 수준 hazard가 되는지 평가한다. | "The six UCA guidewords (Figure 4) are applied to each combination of context variable states" | UCA 표의 칸은 "Hazardous if Provided"이거나 N/A이거나 hazard 번호 (H4 등)다 (49쪽) |
| F06-047 | 50 | STPA Step 1은 UCA 95개를 찾았다. control action별로는 2개에서 24개까지다 (토크 감소 24개가 가장 많다). | "Overall, STPA Step 1 identifies a total of 95 UCAs" | 표 13 |
| F06-048 | 51 | UCA 문장의 예: "EV PCM이 가속 페달을 놓았는데 토크 증가 명령을 낸다" (H1), "EV PCM이 P, N, D를 골랐는데 후진 토크를 낸다" (H3과 H1). | "Increase Torque command when the driver reduces or maintains the angular position" | UCA의 꼴은 control action과 context와 hazard의 짝이다 |
| F06-049 | 37 | 보고서는 두 방법이 비슷한 vehicle-level hazard를 찾았고, 그것을 하나의 일관된 목록으로 합쳤다고 적는다. | "HAZOP and STPA identify similar vehicle-level hazards." | C-06-004와 겹친다. 어느 hazard를 어느 방법이 먼저 찾았는지는 적혀 있지 않다 |
| F06-050 | 14 | 요약: HAZOP은 기능 19개에서 malfunction 132개, STPA는 control action 13개에서 UCA 95개를 찾았고, 둘을 합쳐 hazard 일곱을 얻었다. | "The STPA method identifies 95 unsafe control actions from analysis of the 13" | 요약의 쪽 번호는 인쇄 쪽 xiii이다 |
| F06-051 | 23 | 기능 FMEA는 concept phase에서 하므로 특정 설계를 가정하지 않고, 통제나 완화 수단이 있다고 보지도 않는다. 절차의 앞 네 단계만 한다. | "the analysis is not based on a specific design" | 7장에서 쓸 사실이지만 HARA 단계의 전제로도 쓴다 |
| F06-052 | 58 | 표 24는 safety goal 여덟 개를 ASIL과 함께 적는다. SG1 D, SG1a B, SG2 C, SG3 C, SG4 D, SG5 C, SG6 D, SG7 B. 각 safety goal은 표 23의 hazard 하나에 대응한다. | "Table 24. Safety Goals with ASIL" | SG6만 H6에 해당하고 나머지는 hazard 이름과 같은 말이다 |
| F06-053 | 58 | SG1은 가속이 TBD m/s^2를 TBD초보다 오래 넘는 것을 막는다는 꼴이다. 이 꼴 (크기와 시간)은 SG1 하나이고, SG1a와 SG4는 크기만 TBD로 두고, SG2와 SG5는 각주에서 TBD sigma를 쓰며, SG3, SG6, SG7에는 수치 자리가 없다. | "for a period greater than TBD seconds" | 숫자는 하나도 정해져 있지 않다. 지금 원고의 "값은 정하지 않고 남겼다"와 맞다 |
| F06-054 | 58 | safety goal의 문장은 모두 "hazard가 일어나는 것을 식별된 ASIL에 맞게 완화한다"는 꼴이다. 해결 수단은 적지 않는다. | "is to be mitigated in accordance with the identified ASIL" | SG6만 다른 꼴이다 |
| F06-055 | 58 | SG2와 SG5의 각주: 추진력이나 감속이 부족하다는 것은 차가 올바르게 동작하는 속도 증가나 감소 곡선에서 어떤 운전 조건에서든 TBD sigma보다 많이 벗어나는 것이다. 운전자가 가속 페달의 각도를 늘리거나 줄인 결과로 생기는 속도 변화에 한정된다. | "deviating from the correctly functioning speed increase/decrease profile" | 부족을 통계의 편차 (sigma)로 정의한다. 값은 TBD다 |
| F06-056 | 58 | SG6은 ACS/ETC의 제어 알고리즘이 안전을 위해 가장 우선순위가 높은 토크 명령을 고르는 것이다. ASIL D다. | "to choose the torque command that has the highest priority for safety" | H6에서 나온 goal이다 |
| F06-057 | 70 | 9.1절은 같은 safety goal을 다시 적는데 SG1의 문장에 시간이 없다 ("TBD m/s^2보다 큰 가속"). SG4는 "운전자의 의도를 TBD m/s^2 넘는 감속"으로 적는다. 표 24의 SG4는 "TBD m/s^2보다 큰 감속"이다. | "SG 1: Potential uncontrolled vehicle propulsion resulting in vehicle acceleration" | 같은 보고서 안에서 safety goal의 문장이 쪽마다 조금씩 다르다 (70-71쪽) |
| F06-058 | 54 | exposure는 고장 모드와 겹치면 위험해질 수 있는 운전 상황에 놓여 있는 상태다. 등급은 E0 (incredible), E1 (very low), E2 (low), E3 (medium), E4 (high probability)다. 보고서는 표 18이 ISO 26262 Part 3 Table 2를 그대로 옮겼다고 한다. | "Table 18. Exposure (E) Assessment" | 2차 자료 (ISO 26262 FDIS 2011) |
| F06-059 | 54 | severity는 위험한 상황에서 한 사람 이상에게 생길 수 있는 피해의 정도의 추정이다. S0 무상해, S1 가볍거나 중간의 부상, S2 심각하고 생명을 위협하는 부상 (생존 가능성 높음), S3 생명을 위협하는 부상 (생존 불확실)이나 사망이다. | "Table 19. Severity (S) Assessment" | 2차 자료 |
| F06-060 | 54 | 표 20은 severity를 AIS (Abbreviated Injury Scale)로 정하는 수용 가능한 방법이다. S1은 AIS 1-6이 될 확률이 10%를 넘는 것 (S2, S3 제외), S2는 AIS 3-6, S3은 AIS 5-6이 될 확률이 10%를 넘는 것이다. S0은 AIS 0이거나 AIS 1-6의 확률이 10% 미만, 또는 안전과 무관한 손상이다. | "Table 20. Acceptable Approach to Assess Severity (S)" | 2차 자료. 지금 원고에 AIS가 없다 |
| F06-061 | 54 | controllability는 관련된 사람들이 때맞춰 반응해 특정 피해를 피하는 능력이다. 관련된 사람에는 운전자, 승객, 차 바깥 가까이에 있는 사람이 들어간다. | "ability to avoid a specified harm or damage through the timely reactions" | 2차 자료. 각주 19에 사람의 범위가 있다 |
| F06-062 | 55 | controllability 등급은 C0 (일반적으로 제어 가능), C1 (쉽게 제어 가능), C2 (보통 제어 가능), C3 (제어하기 어렵거나 제어 불가능)이다. | "Table 21. Controllability (C) Assessment" | 2차 자료. C-06-005와 겹친다 |
| F06-063 | 55 | 표 22는 E1, E2, E3, E4와 C1, C2, C3와 S1, S2, S3로 ASIL을 찾는다. 이 표에는 E0, S0, C0이 없다. E1 줄은 S1과 S2에서 모두 QM이고 S3에서만 C3이 A다. S3, E4, C3이 D다. | "Table 22. ASIL Assessment" | 2차 자료. 이 쪽의 표를 읽은 것이다. 책은 표를 옮기지 않는다 (plans) |
| F06-064 | 55 | 예 1 (H1, 고속 100-130 kph, 교통량 많음): E4는 이 운전 상황이 차의 평균 운전 시간의 10%를 넘게 일어난다는 뜻이다. 충돌은 앞차를 추돌하거나 도로를 벗어나 물체와 부딪치는 것이다. | "This operational situation occurs often, > 10 percent of the vehicle average operating time." | 2차 자료. E4의 수치 기준이 여기에 있다 |
| F06-065 | 56 | 예 1의 S3은 승객실이 변형되는 정면이나 후면 충돌이고 AIS 5-6일 확률이 10%를 넘는다. C3은 후륜 구동 차량의 경우이고, 전륜 구동이면 C2이며, 후륜 구동이 더 엄격한 평가여서 그것을 골랐다. ASIL D다. | "The rear-wheel drive vehicles represent the more severe ASIL assessment." | C-06-005, 009와 겹친다 |
| F06-066 | 56 | 예 2 (H4, 매우 높은 속도 130 kph 초과, 교통량 많음, 시야 나쁨, 노면 미끄러움): E2는 이 상황이 운전 시간의 약 1%에 일어난다는 뜻이다. 차가 가속을 잃고 뒤차가 들이받으며, S3, C3이고 ASIL B다. C3의 이유는 운전자가 차를 차선 밖으로 빼며 필요하면 더 제동하는 것이 어렵다는 것이다. | "Operational situation occurs about 1 percent of the operating time of the vehicle." | 2차 자료. 같은 hazard (H4)가 다른 상황에서는 D까지 간다 (192쪽) |
| F06-067 | 54 | 정의의 근거: exposure와 severity와 controllability의 정의를 보고서는 ISO 26262 Part 1의 조항 (1.37, 1.120, 1.19)에서 옮겼다고 적는다. | "Exposure is defined as the state of being in an operational situation" | 2차 자료 |
| F06-068 | 102 | 프로젝트 팀의 분석자 모두가 exposure와 controllability에 같은 평가를 하지는 않았다. 객관적인 자료가 흔히 없어 전문가의 의견을 쓰기 때문이며, 보고서는 이것이 ISO 26262에 대한 이전의 평가들 ([17] [18])과 맞는다고 적는다. | "not all safety analysts on the project team agreed to the same assessment" | C-06-006과 겹친다 |
| F06-069 | 102 | ISO 26262는 객관적인 자료가 없으면 전문가의 입력을 쓰라고 권한다. 이것이 평가를 끝내게 해 주지만 단점이 있고, 누가 옳은지 정하기 어렵다고 보고서는 적는다. | "ISO 26262 recommends the use of expert inputs when objective data are not available." | |
| F06-070 | 102 | ISO 26262는 controllability를 평균적이거나 다수인 운전자의 능력에 근거해 평가하지만, 표준이 평균적이거나 다수인 운전자의 능력을 정의하지 않는다고 보고서는 지적한다. | "the standard provides no definition on the ability of the average/majority driver" | |
| F06-071 | 102-103 | 개선안: severity는 NHTSA의 충돌 통계로 뒷받침할 수 있고, exposure는 자연주행 자료에서 통계를 낼 수 있다. controllability의 통계는 공개되어 있지 않아 더 연구해야 한다. | "Statistics are not publicly available for the assessment of controllability." | |
| F06-072 | 101 | ISO 26262의 방식으로는 hazard가 모든 운전 상황 가운데 가장 엄격한 ASIL을 받으므로, 일부 상황에서만 쓰이는 기능에는 등급이 지나치게 엄격할 수 있다. 보고서는 두 단계를 제안한다. 먼저 차를 설계와 기능에 대한 가정 없는 black box로 보고 hazard마다 가장 엄격한 ASIL을 고르고, 기능을 설계할 때는 그 기능이 동작하는 상황의 부분집합에서 가장 엄격한 ASIL을 고른다. | "Treat the vehicle as a black box with no assumptions about its designs and features." | C-06-007과 겹친다. 이 두 단계는 새 내용이다 |
| F06-073 | 18 | 보고서의 2장, 10장, 11장은 같은 프로젝트의 가솔린 차 보고서와 본질적으로 같고, 단독으로 읽을 수 있게 다시 실었다. | "Sections two, ten, and eleven of this report are essentially unchanged" | 관찰 (10장)이 가솔린 보고서와 같은 말이다 |
| F06-074 | 66 | 보고서가 ISO 26262 Part 3 Clause 8.2를 옮긴 것: functional safety concept는 고장 감지와 완화, safe state로의 전환, 고장 허용 메커니즘, 위험 노출 시간을 허용되는 구간으로 줄이기 위한 고장 감지와 운전자 경고 (예: 엔진 경고등), 여러 요청 사이의 중재 논리를 다룬다. | "Fault detection and driver warning to reduce the risk exposure time to an acceptable interval" | 2차 자료 (보고서가 규격을 옮겨 적은 것) |
| F06-075 | 67 | safe state는 의도한 동작 모드, 성능이 낮아진 동작 모드, 꺼진 모드 중 하나일 수 있다 (ISO 26262 Part 1 Clause 1.102). functional safety concept를 만드는 쪽은 차의 안전을 지키면서 item의 가용성을 최대로 하려 한다. | "A safe state may be the intended operating mode, a degraded operating mode" | 2차 자료. 원고의 safe state 서술과 맞는다 |
| F06-076 | 67 | EV ACS/ETC의 safe state는 전체 토크를 쓰는 정상 동작, 성능 저하 동작 (0 < 토크 < 전체), 꺼진 모드 (토크 0) 중 하나다. 예: 가속 페달 신호가 좋지만 확인할 수 없으면 토크는 허용하되 올리는 속도를 평소보다 늦춘다. | "the safe state may allow full torque but at a ramp rate slower than normal" | |
| F06-077 | 68 | safe state 일곱: 1 다른 시스템의 입력 차단, 2 고장 직전의 토크로 상한, 3 토크 상승 속도를 늦춤, 4 가속 페달 입력 없이 속도 제한 (> creep)으로 토크, 5 가속 페달 0에서의 토크 맵 값, 6 토크 0, 7 고전압 버스 차단. 6은 1-5를 보장하지 못할 때의 예다. | "Safe State 6: Zero torque output" | 지금 원고와 같다 (68쪽). 고장 예: 6은 "system is unable to mitigate the hazards or ensure Safe States 1-5" |
| F06-078 | 71 | 요구사항의 틀로, 보고서는 hazard가 될 수 있는 고장이 나면 ACS/ETC가 fault tolerant time interval (FTTI) 안에 safe state로 가고, safe state는 고장에 맞아야 하며, 운전자에게 경고하고 운전자가 해야 할 일을 알려야 한다고 적는다. | "the ACS/ETC is to transition into a safe state within the fault tolerant time interval" | C-06-008과 겹친다. 경고 요구는 새 내용이다 |
| F06-079 | 80 | 크리프 속도를 흉내 내는 구조에서는, 크리프 토크를 제어하지 못하는 고장의 FTTI가 크리프 속도보다 빠르게 달리는 때의 FTTI보다 길 수 있다. | "may have a longer FTTI than the FTTI for operating speeds above the idle" | 같은 고장이라도 운전 상황에 따라 허용 시간이 다를 수 있다는 서술이다. 200 ms는 C-06-011 |
| F06-080 | 72 | 표 30: 단일 고장의 하드웨어 고장은 "고장 감지 시간 안에 감지하고 FTTI 안에 완화"해야 하고 (ASIL B/C/D), 고장이 나면 해당 safe state로 간다. 감지 시간과 FTTI가 따로 있는 두 시간으로 적혀 있다. | "detected within the fault detection time and mitigated within the FTTI" | 7장에서 시간 구간을 나눌 때의 근거. 값은 TBD다 |
| F06-081 | 74 | 주기적 시험의 빈도는 FTTI와 fault reaction time interval에 따라 고른다. safe state로 가는 시간은 TBD ms이거나 TBD초다. | "The frequency of the periodic tests is to be selected based on the FTTI" | |
| F06-082 | 11 | 약어표가 FTTI를 fault tolerant time interval이라고 풀어 쓴다. 본문에 FTTI의 정의 문장은 없다. | "fault tolerant time interval" | 정의 원문은 이 보고서에 없다 (끝의 "찾지 못한 것") |
| F06-083 | 19 | 이 연구는 ISO 26262의 과정을 따라 개념 수준에서 기능의 integrity 요구를 찾는다. 구현의 차이와 무관하게 한다. | "independent of implementation variations" | HARA가 설계를 모를 때 하는 일이라는 근거 |
| F06-084 | 27 | 범위 안은 가속 페달부터 모터까지 고전압 전원 연결까지의 모든 구성요소와 그 연결, BTO 기능, 다른 시스템에서 오는 토크 요구, 고전압 배터리 (RESS)와 냉각 시스템과의 인터페이스, 속도와 브레이크 페달과 방향 센서다. | "this analysis assumes that these other vehicle systems correctly issue torque requests" | 다른 시스템 (cruise control 등)의 토크 요구가 틀리는 것은 범위 밖이다 |
| F06-085 | 28 | 범위 밖의 것: 모터의 토크 생성과 그 뒤의 전달, 전자 제어 때문이 아닌 hazard (화재 등), 제동 시스템의 고장 (회생 제동 포함), 다른 시스템의 잘못된 토크 요구, 고전압 시스템의 고장, 운전자에게 알리는 것, 운전자 오류, 정비 불량, 다중 고장. | "Driver errors, such as incorrect pedal application or gear selection" | 예제의 A-12 (운전자의 입력은 옳다)와 같은 가정이다 |
| F06-086 | 29 | 운전자의 가속과 감속 의도는 가속 페달과 브레이크 페달로만 전달된다고 보고, 운전자의 입력이 옳다고 가정한다. 운전자가 왜 틀리게 밟는지는 분석하지 않는다. | "this analysis assumes the driver input is correct" | 가정이 깨지면 더 분석해야 한다고 같은 쪽이 적는다 |
| F06-087 | 29 | BTO에서 빠져나와 다시 가속하려면 운전자가 페달 충돌을 없애는 것에 더해 가속 페달의 각도를 명시적으로 늘려야 한다고 가정한다. Toyota가 공개한 brake override 흐름도에 근거한다. | "the driver needs to not only remove the pedal conflict" | 다른 제조사는 전략이 다를 수 있어 별도의 분석이 필요하다고 한다 |
| F06-088 | 30 | 중복 센서 같은 안전 전략은 hazard 분석과 safety 분석 단계에서 고려하지 않는다. 구체적인 설계 전략이 정해지면 분석을 다시 해야 한다. | "Safety strategies, such as redundant sensors, are not considered" | HARA는 안전 수단이 없다고 보고 한다는 근거다 |
| F06-089 | 31 | 전기차의 모터는 양방향으로 돌 수 있어, 방향은 ACS/ETC가 모터에 보내는 전류로 정해진다. 그래서 ACS/ETC가 차의 움직임의 방향을 제어할 책임을 진다. 내연기관 차는 변속기가 방향을 바꾼다. | "The EV ACS/ETC is responsible for controlling the direction of vehicle motion." | 전기차 보고서에만 H3 (잘못된 방향)이 있는 까닭이다 |
| F06-090 | 31 | 구성도에서 회색으로 그린 다른 차량 시스템은 ACS/ETC에 대해 black box로 보고 올바르게 동작한다고 가정한다. | "are treated as black boxes with respect to the EV ACS/ETC" | item의 경계에서 밖의 것에 가정을 적는 예 |
| F06-091 | 13 | 각주: 이 보고서의 hazard는 일반적인 전기차의 ACS/ETC 기준이다. 운전자 보조 기능이 통합된 더 복잡한 시스템은 hazard와 요구가 더 나올 수 있다. | "may result in additional hazards and functional safety requirements" | |
| F06-092 | 17 | 보고서의 요구사항은 예시이고 NHTSA의 공식 입장이나 요구가 아니다. | "not intended to represent NHTSA's official position" | 각주 4 |

## 2. nhtsa-etc-gasoline-fsa (NHTSA/Volpe, Functional Safety Assessment of a Generic Accelerator Control System With Electronic Throttle Control in Gasoline-Fueled Vehicles, DOT HS 812 557, 2018. PDF 쪽 = 인쇄 쪽 + 18)

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| F06-093 | 36 | 가솔린 보고서의 hazard는 H1, H1.a, H2, H3 (구동력 감소나 상실, stalling), H4 (감속 부족), H5 (운전자의 명령이 능동 안전 시스템을 이김)다. 전기차 보고서의 H3 (잘못된 방향)과 H7 (감전)이 없다. | "Potential Propulsion Power Reduction/Loss or Vehicle Stalling" | 번호가 하나씩 당겨진다. 가솔린의 H3은 전기차의 H4, 가솔린의 H4는 전기차의 H5, 가솔린의 H5는 전기차의 H6이다 |
| F06-094 | 36 | 가솔린 보고서의 가속 쪽 vehicle response는 "운전자가 고른 방향 (전진이나 후진)으로 가속"이다. 전기차의 "운전자가 지정한 것과 다른 방향으로 가속"에 해당하는 줄이 없다. | "direction chosen by driver (forward or reverse)" | 내연기관은 방향을 변속기가 정한다 (전기차 31쪽) |
| F06-095 | 51 | 가솔린 보고서가 hazard에 준 등급은 H1 D, H1.a B, H2 C, H3 (구동력 감소나 상실) D, H4 (감속 부족) C, H5 D다. 전기차 보고서와 같은 hazard는 같은 등급이다. | "Table 16. Vehicle-Level Hazards and Corresponding ASIL" | 같은 각주도 있다: H1.a의 B는 속도 0에서만 동작하는 기능, H2와 H4는 분석자마다 달랐다 |
| F06-096 | 51 | 가솔린 보고서도 H2와 H4 (감속 부족)의 ASIL이 객관적인 자료가 없어 분석자마다 달랐다고 적는다. | "varied among safety analysts in the absence of objective data" | 전기차 보고서의 H2와 H5에 해당 |
| F06-097 | 52 | 가솔린 보고서의 safety goal은 SG1 D (가속이 TBD m/s^2를 TBD초 넘게), SG1a B, SG2 C, SG3 D (감속이 TBD m/s^2를 넘거나 stalling), SG4 C, SG5 D다. 전기차 보고서의 SG3 (방향)과 SG7 (감전)이 없다. | "Table 17. Safety Goals With ASIL" | 값은 모두 TBD다. SG1의 꼴과 TBD가 전기차와 같다 |
| F06-098 | 52 | 가솔린의 SG5는 제어 알고리즘이 안전을 위해 가장 우선순위가 높은 throttle 명령을 고르는 것이다. 전기차의 SG6은 torque 명령이다. | "to choose the throttle command that has the highest priority for safety" | |
| F06-099 | 47 | 가솔린 보고서도 운전 상황을 69개 만들었다. 전기차 보고서의 수와 같다. | "This study generates 69 vehicle operational situations" | 변수 표 (표 10)도 전기차의 표 17과 같다 (48쪽) |
| F06-100 | 50 | 가솔린 보고서의 예 1 (H1, 고속, 교통량 많음)도 E4 S3 C3 ASIL D이고, C3은 후륜 구동의 경우이며 전륜 구동이면 C2다. | "The rear-wheel drive vehicles represent the more severe ASIL assessment." | 전기차의 55-56쪽과 같은 서술이다 |
| F06-101 | 165 | 가솔린 보고서의 부록 F도 H1을 destabilization이 없는 경우 (ASIL C)와 있는 경우 (ASIL D)로 나누고, 표 제목에 등급을 적는다. 있는 경우의 첫 줄은 고속, 교통량 많음, 시야와 노면 좋음, E4 S3 C3이다. | "Table F-2: Unintended Vehicle Propulsion with Destabilization" | 전기차의 183쪽과 같은 값이다 |
| F06-102 | 168 | 가솔린의 H1.a 표 (ASIL B)도 주차장 D나 R에서 브레이크를 밟고 정지, 보행자 많음, E4 S2 C2가 가장 높고, 같은 조건에 보행자가 적으면 C1로 A다. | "Table F-3: Unintended Vehicle Propulsion With Zero Starting Speed" | 전기차의 196쪽과 같은 값이다 |
| F06-103 | 38 | 가솔린 보고서의 HAZOP은 기능 15개에 guide word를 적용해 malfunction 103개를 얻었다. | "They generate a list of 103 malfunctions." | 전기차는 기능 19개, malfunction 132개다 |
| F06-104 | 45 | 가솔린 보고서의 STPA는 control action 4개에서 UCA 48개를 찾았다. | "Overall, STPA Step 1 identifies a total of 48 UCAs" | 전기차는 control action 13개, UCA 95개다. 두 보고서 모두 hazard 목록은 같은 꼴 (가속, 감속, 방향, 우선순위)이다 |

## 3. nhtsa-safety-standards-assessment (NHTSA/Volpe, Assessment of Safety Standards for Automotive Electronic Control Systems, DOT HS 812 285, 2016. PDF 쪽 = 인쇄 쪽 + 10)

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| F06-105 | 21 | 표 1은 안전과 hazard의 정의를 견준다. ISO 26262: 안전은 부당한 위험이 없는 것, hazard는 item의 malfunctioning behavior가 낳는 피해의 잠재적 원인이다. MIL-STD-882E: hazard는 사망, 부상, 직업병, 장비나 재산의 손상, 환경 피해를 낳는 사건 (mishap)으로 이어질 수 있는 실제나 잠재적 조건이다. DO-178C는 hazard의 정의가 없다. | "Table 1: Definition of Safety and Hazard" | 표의 제목. 보고서가 ISO 26262의 정의를 옮겨 적은 것이다 |
| F06-106 | 22 | ISO 26262의 hazard는 item이 설계 의도를 만족하지 못하는 경우의 결과로 한정된다. 그러면 어느 시스템이나 부품도 의도한 기능을 하지 못하지 않았는데 시스템 사이의 위험한 상호작용으로 생기는 안전 문제를 놓칠 수 있다고 보고서가 지적한다. | "may not address safety issues arising from unsafe interactions between systems" | 문장이 21쪽 끝에서 시작해 22쪽으로 이어진다 |
| F06-107 | 22-23 | MIL-STD-882E는 Functional Hazard Analysis (Task 208)를 요구한다. 시스템이 정해진 기능을 하지 못했을 때의 안전 영향을 평가하며, 설계 초기의 높은 수준의 정의로 할 수 있다. 다만 모든 기능이 이미 나와 있다고 가정하고 빠진 기능이나 요구를 찾도록 이끌지 않는다. | "this method assumes all functions are already identified" | |
| F06-108 | 23 | ISO 26262는 item 수준의 hazard 분석 방법으로 brainstorming, checklist, quality history, FMEA, field study를 든다 (Part 3 Clause 7.4.2.2). 그 아래 단계의 safety 분석으로는 FMEA, FTA, ETA, HAZOP 등을 든다 (Part 9 Clause 8). | "The listed hazard analysis methods include brainstorming, checklists, quality history, FMEA, and field studies." | 보고서가 규격을 옮겨 적은 것 |
| F06-109 | 23 | brainstorming, checklist, quality history, field study는 과거의 경험에 기댄다. 역사가 짧고 빨리 바뀌는 기술에서는 hazard를 놓칠 수 있다고 보고서는 지적한다. | "these techniques may miss potential hazards" | HARA가 떠올리는 것에 의존한다는 한계다. 원고의 "틀이 필요하다"의 근거 |
| F06-110 | 24 | HAZOP은 원래 공정 산업에서 나왔고 주로 정성 분석이다. guide word와 실제 과정의 모델링이 부품 고장과 시스템 상호작용을 함께 보게 한다. 그러나 자동차 전자 제어에 적용하려면 수정과 시험이 필요하고, ISO 26262는 자동차 시스템에 어떻게 적용하는지 지침을 주지 않는다. | "ISO 26262 does not provide guidance on how to apply this method to automotive systems" | |
| F06-111 | 25 | STPA는 안전을 제어 문제로 보고, hazard와 causal factor를 찾도록 이끈다. 설계 초기에 높은 수준의 개념만 있을 때도 쓸 수 있다. 자동차에서의 적용은 아직 적다. | "STPA can also be easily used in the early stage of the design" | |
| F06-112 | 26 | 위험 평가의 세 방식: ISO 26262는 ASIL을 S, E, C의 표 조합으로 정한다. MIL-STD-882E는 하드웨어에는 severity와 사고 발생 확률로 risk index를 만들고, 소프트웨어에는 severity와 software control category를 쓴다. DO-178C는 소프트웨어의 level을 severity만으로 정한다. | "DO-178 specifies software levels only based on the impact" | 표 2가 이 비교를 요약한다 |
| F06-113 | 26 | 표 2: severity는 세 규격 모두의 차원이다. 운전 상황의 확률 (exposure)과 controllability는 ISO 26262만, 사고 발생 확률은 MIL-STD-882E의 하드웨어만, software control category는 MIL-STD-882E의 소프트웨어만의 차원이다. | "Table 2: Comparison of Risk Assessment Approaches" | 표의 제목. 표의 체크 표시를 읽은 것이다 |
| F06-114 | 27 | 통계적으로 타당한 확률 자료가 없으면 전문가가 주관적으로 추정하며, ISO 26262와 MIL-STD-882E 모두 이것을 권한다. 그러나 사람은 드문 사건의 확률을 잘 맞히지 못한다. 확률이 불확실하면 보수적으로 평가하라는 것이 보고서의 의견이고, 가장 보수적인 확률은 100%다 (severity만 쓰는 것). | "humans are not good at predicting truly random events, especially rare events" | C-06-006과 같은 내용이다 |
| F06-115 | 27 | controllability는 ISO 26262에만 있는 차원이라고 보고서가 적는다. Part 3 Clause 7.4.3.7을 인용해, controllability 평가는 운전자나 위험에 놓인 사람이 위험한 사건을 충분히 제어해 특정 피해를 피할 확률의 추정이라고 한다. | "Controllability is a risk assessment dimension unique to ISO 26262" | 2차 자료 (보고서가 규격을 옮겨 적은 것) |
| F06-116 | 28 | controllability 평가에는 통계적으로 타당한 표본의 시험 자료가 필요하다. 어려움은 둘이다. 새 차 설계마다 human factors 시험에 자원과 시간이 많이 든다. 시험이 사용자가 시스템과 어떻게 상호작용하고 위험한 상태를 어떻게 아는지의 설계 구현을 반영해야 하는데, ASIL을 평가하는 설계 초기에는 그런 세부가 보통 없다. | "Such details about the design are usually not available during early phase" | 28쪽 |
| F06-117 | 28 | ACC 예: 곡선 출구 램프에서 ACC가 속도를 줄이지 못해 앞차를 추돌하는 hazard는 S3이다. 출구 램프 상황은 E2이다. "운전 보조 시스템을 쓸 수 없음"의 controllability는 C0이나 C1이다. 그 조합으로 ASIL이 QM이 되어 높은 severity가 안전과 무관한 문제로 내려간다. | "a high-severity hazard is reduced to a non-safety-critical issue" | 보고서는 C0이나 C1이라는 증거가 불분명하다고 지적한다. 또 모든 운전 상황 중 최악을 hazard의 ASIL로 하므로 최종 등급은 QM보다 나쁠 수 있다고 덧붙인다 |
| F06-118 | 28 | exposure와 controllability를 쓰면 severity가 높은 hazard의 위험 척도를 낮출 수 있다고 보고서는 적는다. 유효한 통계와 엄밀한 시험 없이 분석자가 제한된 정보로 평가해야 하는 경우가 있고, 그렇지 않으면 가장 보수적인 방법은 severity만 쓰는 것이다. | "effectively provides an opportunity to reduce the risk measure for a high severity hazard" | 원고의 "상황을 잘게 나누면" 오해 항목과 다른 논점이다. 같은 쪽 끝에 비용에 관한 논쟁이 있다 |
| F06-119 | 29 | 소프트웨어의 위험 평가: ISO 26262는 소프트웨어 요구사항에 ASIL decomposition으로 ASIL을 주고, safety goal과 같거나 낮을 수 있다. MIL-STD-882E는 소프트웨어의 고장 확률이 과거 자료로 정할 수 없다고 보고 software control category를 쓴다. DO-178C는 소프트웨어의 오류 가능성이 하드웨어의 무작위 고장처럼 정량화될 수 없다고 하며 severity만 쓴다. | "the likelihood that the software contains an error cannot be quantified" | 소프트웨어 level의 정의는 DO-178C의 원문 인용이 아니라 이 보고서의 요약이다 |
| F06-120 | 29 | 보고서는 DO-178C가 소프트웨어 위험 평가에 가장 보수적인 방식, 곧 severity만 쓴다고 평가한다. | "DO-178C presents the most conservative approach to software risk assessment" | |
| F06-121 | 45 | 부록의 요약표: ISO 26262는 세 차원 (severity, exposure, controllability)으로 ASIL을 만들고, "acceptable risk"라는 말을 쓰지만 정의가 충분히 정밀하지 않으며, 정성과 정량의 확률 평가를 모두 받아들이고, 모든 하드웨어와 소프트웨어에 ASIL decomposition을 제안한다. | "Uses three dimensions" | 인용은 표의 ISO 26262 칸이다 |

## 4. stpa-handbook (Leveson, Thomas, STPA Handbook, 2018. PDF 쪽 = 인쇄 쪽 + 0)

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| F06-122 | 15 | 분석의 목적을 정하는 첫 단계는 넷이다. 손실을 찾고, 시스템 수준의 hazard를 찾고, 시스템 수준의 constraint를 찾고, hazard를 고친다 (선택). | "Defining the purpose of the analysis has four parts" | |
| F06-123 | 16 | 손실 (loss)의 정의: 이해관계자에게 가치 있는 것이 관련된 것이다. 사람의 생명이나 부상, 재산 피해, 환경 오염, 임무, 평판, 정보 유출 등 이해관계자가 받아들일 수 없는 것이다. 업계마다 사고, mishap, 부작용 등 다른 말을 쓰므로 이 장은 "losses"로 통일한다. | "A loss involves something of value to stakeholders." | |
| F06-124 | 17 | 손실의 작성 요령: 손실에 개별 부품이나 구체적 원인 ("human error", "brake failure")을 적지 않는다. 시스템 설계자가 직접 제어하지 못하는 환경의 일이 손실에 들어갈 수 있다. 특별히 제외한 손실이나 가정을 적는다. | "Losses should not reference individual components or specific causes" | |
| F06-125 | 17 | hazard의 정의: 시스템 상태나 조건의 집합으로, 최악의 환경 조건과 함께 손실로 이어진다. 시스템 경계는 설계자가 어느 정도 통제하는 부분을 포함하도록 긋는 것이 가장 유용하다. 그것이 hazard와 손실을 구별하는 까닭이다. | "system state or set of conditions that, together with a particular set of worst-case" | 원문은 "worst-case environmental conditions, will lead to a loss"로 이어진다 |
| F06-126 | 18 | 시스템 수준 hazard의 기준 셋: hazard는 시스템의 상태나 조건이다 (부품 수준의 원인이나 환경 상태가 아니다). 최악의 환경에서 손실로 이어진다. 막아야 할 상태나 조건을 적는다. | "Hazards are system states or conditions (not component-level causes or environmental states)" | 원고의 "hazard는 차량 수준으로 적는다"와 맞는다 |
| F06-127 | 18 | 예: 원자력 발전소에서 바람의 방향과 도시와의 거리는 통제할 수 없지만, 방사성 물질의 방출은 설계로 통제할 수 있어 hazard는 방출이다. 비행 중인 항공기는 손실로 이어질 수 있지만 막아야 할 조건이 아니므로 hazard가 아니다. | "Hazards should be states to be prevented" | hazard에는 시스템이 정상적으로 있어야 하는 상태를 적지 않는다 |
| F06-128 | 19 | 흔한 실수 첫째는 hazard를 hazard의 원인과 혼동하는 것이다. "brake failure", "operator is distracted", "hydraulic leak"은 원인이다. hazard는 <시스템> & <안전하지 않은 조건> & <손실과의 연결>을 포함해야 한다. | "<Hazard specification> = <System> & <Unsafe Condition> & <Link to Losses>" | 원고의 "토크 계산이 틀린다가 아니라 차가 가속한다"와 같은 논점이다 |
| F06-129 | 19 | hazard의 수는 대략 7-10개를 넘으면 묶거나 합치는 것을 고려하라고 한다. 처음에는 더 추상적인 목록으로 시작해 나중에 sub-hazard로 고친다. | "more than about seven to ten system-level hazards" | 전기차 보고서는 H1.a를 빼면 hazard가 일곱 개다 |
| F06-130 | 19 | hazard에 "unsafe"라는 말을 쓰지 않는다. 쓰면 재귀적인 정의가 된다. 어떤 시스템 상태나 조건이 위험한지를 구체적으로 적는다. | "A common mistake is to use the word" | 인용은 "unsafe"의 앞부분이다. 아래 20쪽의 요약에는 "unintended"와 "accidental"도 들어 있다 |
| F06-131 | 19 | STPA의 hazard는 기술적 기능의 이탈이나 부품 고장이 아니라, 원인과 무관하게 본래 안전하지 않은 시스템 상태다. 정해진 기능이 안전하고 옳다고, 운전자가 기대대로 행동한다고 가정하지 않기 위해서다. | "regardless of the cause" | 원문: "inherently unsafe-regardless of the cause" |
| F06-132 | 20 | hazard를 검토할 때 볼 것: 개별 부품을 가리키지 않는다. 시스템과 시스템의 상태를 가리킨다. 설계자와 운용자가 통제하거나 관리할 수 있는 요인을 가리킨다. 막아야 할 시스템 수준의 조건을 적는다. 수는 대개 7-10개를 넘지 않는다. "unsafe", "unintended", "accidental" 같은 모호하거나 재귀적인 말을 쓰지 않는다. | "Tips to prevent common mistakes when identifying hazards" | 해석: 전기차 보고서의 "Unintended Direction" (H3)은 이 기준에서 보면 피해야 할 낱말을 쓴다 |
| F06-133 | 20 | system-level constraint는 hazard를 막기 위해 만족해야 하는 시스템의 조건이나 동작이다. hazard의 조건을 뒤집어 적는다. 꼴: <시스템> & <지킬 조건> & <hazard와의 연결>. 하나의 constraint가 hazard 여럿에 걸치거나 hazard 하나에 constraint 여럿이 있을 수 있다. | "simply invert the condition" | safety goal과 닮았지만 STPA는 ASIL을 붙이지 않는다 (기억) |
| F06-134 | 20 | constraint는 hazard가 일어난 뒤 손실을 줄이는 방법도 정할 수 있다. "hazard가 일어나면, 손실을 막거나 줄이기 위해 할 일은 ...". 예: SC-3 항공기가 최소 간격을 어기면 이를 감지하고 충돌을 막는 조치를 한다. | "If aircraft do violate minimum separation" | |
| F06-135 | 20-21 | constraint는 특정 해결책이나 구현을 정하지 않는다. 이 단계에서 해결책을 정하면 더 나은 해결책을 놓칠 수 있다. 예: 충돌 회피 시스템을 설치한다고 적지 않는다. | "Specifying a particular solution is usually premature at this early stage" | 원고의 "safety goal은 해결 방법을 적지 않는다"와 맞는다 |
| F06-136 | 21 | hazard는 필요하면 sub-hazard로 고친다. 방법은 "hazard를 막으려면 무엇을 통제해야 하는가"를 묻는 것이다. 예: H-4 (항공기가 지상의 다른 물체에 너무 가까워짐)에서 감속, 가속, 조향 세 가지를 통제해야 하므로 H-4.1 감속이 부족함 ... H-4.10 조향이 항공기를 경로 밖으로 보냄까지 열 개의 sub-hazard를 얻는다. | "One way to derive sub-hazards is to ask" | 전기차 보고서의 hazard (가속, 감속, 방향)가 이 handbook의 sub-hazard와 같은 꼴이다 (기억) |
| F06-137 | 57 | PHA 표에서 hazard의 확률이나 가능성은 초기 개념 단계에서 알 수 없고, 소프트웨어가 많은 시스템에서는 상세 설계 뒤에도 알 수 없다. 과거 자료는 시스템이 크게 다르면 쓸모없다. 실제 프로젝트에서 타당한 시나리오가 있는 hazard가 초기에 "marginal"이거나 매우 일어나기 어렵다고 잘못 기각되는 일이 많다고 적는다. | "humans are very bad at estimating probability or likelihood of unusual events" | HARA의 exposure에 대한 비판과 이어진다 |
| F06-138 | 57 | 항공 업계에서는 확률 요구 (예: 바퀴 제동을 모두 잃는 일이 이륙 때 비행당 5E-7 미만)를 쓰지만, 소프트웨어가 많은 시스템에서는 이런 요구가 만족되는지 보장할 수 없다고 한다. | "Loss of all wheel braking during landing or rejected take off" | 인용은 SAE ARP 4761의 예를 handbook이 옮긴 것이다 |

## 5. ifa-report-2-2017e (IFA, Functional safety of machine controls - Application of EN ISO 13849, IFA Report 2/2017e, 2019년 7월 판. PDF 쪽 = 인쇄 쪽 + 0)

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| F06-139 | 20 | 기계의 안전 기능이 요구하는 위험 감소의 질은 performance level (PL)로 정의한다. 위험 평가의 결과가 PL의 필요한 값 (required performance level, PLr)을 정한다. | "the required Performance Level, PLr" | 20쪽 |
| F06-140 | 20 | PLr은 간단한 결정 나무인 risk graph로 정한다. 세 질문이다. 부상이 되돌릴 수 없는가 (사망, 사지 상실)나 되돌릴 수 있는가 (치유되는 압궤상). 운전자가 위험 구역에 자주 오래 있는가 (15분에 한 번보다 자주)나 드물고 짧은가. 운전자가 사고를 피할 수 있는가 (예: 기계가 천천히 움직임). | "a simple decision tree, the" | 인용은 "risk graph"에 이어지는 구절의 앞이다 |
| F06-141 | 32 | 각 안전 기능에 필요한 PLr을 정해야 한다. 요구는 필요한 위험 감소에서 나온다. EN ISO 13849-1은 ISO/TR 14121-2의 방법 가운데 risk graph를 쓴다. | "A required Performance Level PLr" | |
| F06-142 | 32 | 그림 5.9의 risk graph는 시작점에서 S1 (경미), S2 (중대)로 가르고, 각각 F1 (드묾), F2 (잦음)으로, 다시 P1 (특정 조건에서 가능), P2 (거의 불가능)로 가른다. 여덟 경로가 PLr a, b, c, d, e에 이른다. S1-F1-P1이 a, S1-F1-P2와 S1-F2-P1이 b, S1-F2-P2와 S2-F1-P1이 c, S2-F1-P2와 S2-F2-P1이 d, S2-F2-P2가 e다. | "Risk graph for determining the PLr for each safety function" | 경로와 등급의 짝은 그림 (쪽의 그림을 렌더링해 읽음)에서 읽은 것이다. 위쪽이 낮은 위험, 아래쪽이 높은 위험이다 |
| F06-143 | 33 | 위험 매개변수는 S (부상의 심각도), F (위험에 노출되는 빈도나 시간), P (위험을 피하거나 피해를 제한할 가능성)다. 분석은 각 안전 기능마다, 그 기능이 주는 위험 감소를 고려하지 않고 한다. 제어 시스템과 무관하게 구현된 다른 기술적 수단 (기계적 방호 등)은 효과가 있다고 볼 수 있다. | "S - severity of injury" | 분석에서 위험 감소를 빼는 것은 HARA에서 안전 수단이 없다고 보는 것과 같다 |
| F06-144 | 33 | S1은 경미한 (보통 되돌릴 수 있는) 부상이고 S2는 심각한 (보통 되돌릴 수 없는) 부상이나 사망이다. 사고의 통상적인 결과와 치유 과정을 따져 S1과 S2를 가른다. | "S1 - slight (normally reversible injury)" | 심각도가 두 단계뿐이다. 자동차의 S0-S3은 네 단계 |
| F06-145 | 33 | F1은 드물거나 덜 자주, 노출 시간이 짧은 것이고, F2는 잦거나 계속, 노출 시간이 긴 것이다. 규격은 운전자의 개입이 15분에 한 번보다 자주 일어나면 F2를 고르고, 그렇지 않고 노출 시간이 기계 전체 사용 시간의 1/20을 넘지 않으면 F1을 고르라는 수치 기준을 준다. | "operator interventions occur more frequently than once every 15 minutes" | 노출의 수치 기준이 있다. 자동차의 E0-E4는 운전 시간의 비율 (E4 10% 초과, 보고서의 55쪽)이다 |
| F06-146 | 33 | P1은 특정 조건에서 위험을 알아채고 피할 수 있다, P2는 거의 불가능하다. 기계의 물리적 특성, 운전자의 자격, 반응 가능성을 본다. 위험을 줄이는 것은 물리적으로 가능한 수단만 고려하고 제어 구성요소로 줄이는 것은 고려하지 않는다. 제어 구성요소가 고장 날 수 있기 때문이다. | "scarcely possible" | P의 판단에서 제어 시스템을 믿지 않는다는 서술은 자동차 controllability의 가정과 견줄 만하다 |
| F06-147 | 34 | 위험한 사건이 일어날 확률을 "낮음"으로 볼 근거 (신뢰성 자료, 비슷한 기계의 사고 이력)가 있으면 PLr을 한 단계 낮출 수 있지만 PL a 아래로는 내릴 수 없다. 낮춘 PLr은 비교한 기계의 것보다 낮아서는 안 된다. | "it must however not drop below" | 인용은 "PL a"의 앞부분이다 |
| F06-148 | 34 | 위험한 사건의 확률을 낮게 보려면, 사건을 일으킬 수 있는 요인 (일반 PLC의 오동작, 새 부품의 경험 부족, 전자기 간섭, 온도 등)을 따져야 한다. 소프트웨어의 오류도 위험한 사건을 일으킬 수 있다고 적는다. | "errors in the software, which of course may also give rise to hazardous events" | |
| F06-149 | 16 | IEC 61508과 IEC 62061의 SIL은 안전 관련 신뢰성의 지표이고 각 값은 목표 고장 척도로 10배 구간이다. PL은 시간당 위험한 고장 확률 (PFHD)로 a (10^-4 쪽)에서 e (10^-8 쪽)까지다. 그림 3.2는 PFHD의 구간으로 PL a에는 SIL이 대응하지 않고, PL b와 c가 SIL 1, d가 SIL 2, e가 SIL 3에 대응하며 SIL 4는 괄호로 적힌 것을 보인다. | "Level (PL) and Safety Integrity Level (SIL)" | 대응은 그림을 읽은 것이다. 쪽의 글에서 정확한 경계는 읽기 어렵다 |
| F06-150 | 15 | IEC 61508은 안전 기능을 두 가지 운용 방식으로 가른다. low demand mode (요구가 1년에 한 번 이하)는 평균 요구 시 고장 확률 PFDavg, high demand 또는 continuous mode는 시간당 위험한 고장 확률 PFHD로 잰다. | "Safety functions in low demand mode" | IEC 61508 규격의 원문이 아니라 IFA가 요약한 것이다 |
| F06-151 | 27 | 위험 추정 (risk estimation)의 요소: 피해의 심각도와, 피해가 일어날 확률. 확률은 사람이 위험에 노출되는 것, 위험한 사건이 일어나는 것, 피하거나 줄이는 기술적이고 인적인 가능성의 함수다. | "Probability of this harm occurring as a function of" | 자동차의 S, E, C와 같은 세 요소다 (기억) |

## 찾지 못한 것

- ISO 26262 Part 3의 원문. S, E, C 표와 ASIL 표는 전기차 보고서 54-55쪽이 옮긴 것 (2011년 판)만 있다. 원고가 쓰는 2018년 판의 표나 정의는 확인하지 못했다.
- destabilization의 정의. 전기차 보고서의 Appendix F 표 제목 (F-1과 F-2, F-3과 F-4)에만 나오고, 본문 1-103쪽에서 이 낱말을 정의한 곳을 찾지 못했다. 표의 "Hazard occurs with destabilization"이 차의 안정을 잃는 경우라는 것은 (기억)이다.
- FTTI의 정의 문장. 전기차 보고서에는 약어표 (11쪽)와 쓰임만 있다. 값은 거의 모두 TBD이고, 200 ms가 나오는 곳은 80-81쪽 둘뿐이다.
- 전기차 보고서에서 어느 hazard를 HAZOP이 먼저 찾았고 어느 hazard를 STPA가 먼저 찾았는지. 보고서는 두 방법이 "비슷한" hazard를 찾았고 하나로 합쳤다고만 적는다 (37쪽). H6과 H7이 어느 방법에서 나왔는지는 적혀 있지 않다.
- hazard마다 가장 나쁜 운전 상황의 S, E, C를 모은 요약표. 보고서의 표 23은 ASIL만 있다. 이 파일의 hazard별 S, E, C는 Appendix F (176-217쪽)에서 직접 읽어 옮겼다.
- 통계의 근거. 보고서는 severity는 NHTSA 충돌 통계로 뒷받침할 수 있고 exposure는 자연주행 자료에서 낼 수 있다고 하지만 (102-103쪽), 이 보고서의 평가가 그런 통계를 썼다는 서술은 없다.
- MIL-STD-882E의 severity와 probability 표 (categories와 risk assessment matrix). nhtsa-safety-standards-assessment에는 "severity와 probability가 risk index를 만든다"는 문장만 있고 (26쪽), 표는 없다. nasa-gb-8719-13 38-39쪽과 mil-std 범주가 plans에 언급되어 있으나 이 읽기에서는 받은 PDF 다섯 개만 보았다.
- IEC 61508의 HARA 방식 (risk graph, risk matrix, SIL의 결정). nhtsa-safety-standards-assessment는 IEC 61508을 ISO 26262의 원형으로 한 줄 언급할 뿐이다 (14쪽). ifa-report는 SIL을 PFH의 구간으로 소개할 뿐 (15-16쪽) 위험 그래프로 SIL을 정하는 방법은 없다.
- DO-178C의 software level A-E의 정의 (catastrophic, hazardous 등). nhtsa-safety-standards-assessment는 "severity만으로 level을 정한다"고 요약할 뿐이다 (26, 29쪽).
- STPA handbook에서 hazard의 심각도나 등급을 매기는 방법. handbook은 hazard에 등급을 붙이지 않고, 대신 확률 판단을 초기에 하지 말라고 한다 (57쪽).
- 전기차 보고서에서 H4의 C3과 D의 이유 (후륜 구동의 가정 말고). 56쪽의 예 2는 H4의 B를 설명하지만, D인 줄의 이유는 192쪽 표에 가정 칸 ("rear-wheel drive vehicles") 하나로만 적혀 있다.

## 지금 원고와 예제 문서와 어긋나 보이는 곳

- chapters/ch06-hara.md의 "hazard 다섯 개"와 plans의 "hazard 5개". 전기차 보고서의 hazard는 H1.a를 빼도 일곱 개 (H1-H7)다. scope.md가 보고서의 H6, H7을 뺐다고 밝혔으므로 어긋남은 아니지만, plans의 "7개 vehicle-level hazard" (근거 위치 표의 4.1 행)와 "hazard 5개" (검토 항목)가 같은 문서에 같이 있다.
- 원고의 "같은 hazard가 QM부터 D까지 갈린다"의 표 1번 줄 (S3 E4 C3 D)은 보고서의 Table F-2 (destabilization이 있는 경우)의 줄이다. destabilization이 없는 경우 (F-1)의 최고는 C다. 원고와 hara.md는 이 구분을 쓰지 않는다. hara.md의 2번 줄 (178쪽, C)은 F-1의 줄이다.
- hara.md의 4번 줄 (S2 E4 C1 A, 196쪽)과 3번 줄 (176쪽), 5번 줄 (178쪽)의 값과 쪽은 보고서와 맞다. 4번의 C1 이유를 "보고서는 적지 않았다"고 한 것도 맞다. 196쪽 표는 C1 (보행자 적음)과 C2 (보행자 많음)의 줄만 있고 이유를 적지 않는다.
- 원고의 "보고서의 safety goal은 '가속이 얼마를 넘는 상태가 얼마보다 오래'라는 꼴이고, 값은 정하지 않고 남겼다"는 표 24의 SG1에만 맞는다. SG1a와 SG4는 크기만, 나머지는 수치 자리가 없다. 70쪽 9.1절의 SG1 문장에는 시간이 없다.
- 원고의 "두 방법의 결과는 비슷했고"는 보고서의 "similar"와 맞는다 (37쪽). 다만 가솔린 보고서와 비교하면 전기차에서만 H3 (잘못된 방향)과 H7이 있다. 원고가 H3을 쓰는 까닭 (전기차 모터가 양방향)을 31쪽에서 뒷받침할 수 있다.
- plans의 "근거 위치" 표의 쪽 (nhtsa-etc-ev-fsa 27-30, 34, 37-42, 52-57, 58, 67-68, 101-103)은 모두 읽은 내용과 맞다. 다만 hazard 수는 plans 안에서 "7개" (근거 위치 표)와 "5개" (검토 항목)가 같이 있다.
- STPA handbook의 hazard 기준은 "unintended", "accidental" 같은 말을 피하라고 한다 (20쪽). 전기차 보고서의 H3 (Unintended Direction)이 그렇고, 원고와 scope.md의 "의도하지 않은 가속" (H-01)도 같은 낱말을 쓴다. 보고서는 H1을 "uncontrolled propulsion"이라고 부르고 unintended acceleration과 같다고 한다 (37쪽).
