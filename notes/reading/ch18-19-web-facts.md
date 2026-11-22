# 18, 19장 웹 근거에서 뽑은 사실 (읽기 기록)

대상: 18장 (변경, 형상, 릴리스 이후), 19장 (safety case). 읽은 날: 2026-11-23.

- 받아 둔 문서 (references/)에 없는 주제를 공개 웹 문서에서 찾았다. "쪽" 칸에는 HTML이면 웹 쪽의 절 이름이나 소제목을 적고, PDF이면 PDF 파일의 몇 번째 쪽인지를 적는다 (문서에 인쇄된 쪽 번호와 다를 수 있으며, 다른 경우는 "비고"에 인쇄 쪽을 적었다). 슬라이드 자료의 "쪽"은 슬라이드 번호다.
- 이 기록의 절 1 - 23은 모두 PDF나 HTML의 글자를 직접 대조했다 (절 1, 8, 18은 WebFetch 도구가 저장한 PDF 사본을 읽었다. 맨 끝의 "읽지 못한 쪽" 참조). 대조는 "원문의 짧은 인용"이 해당 쪽의 글자 층에 있는지를 도구로 확인한 것이다 (공백, 줄바꿈, 곡선 따옴표의 차이는 무시). 인용에 든 곡선 따옴표와 줄표는 ASCII로 바꾸었다. 쪽 칸이 절 이름인 HTML 절은 문서 전체에서 찾았다. "사실" 칸의 풀이가 옳은지는 도구가 보지 않으며 사람이 읽고 확인했다.
- 규격의 요구에 관한 사실은 "그 문서가 그렇게 설명한다"까지다. ISO 26262, ISO 24089, UL 4600, UN Regulation 156과 157의 원문은 읽지 못했다. 회사와 협회의 글은 (2차 자료)이며, 책에 쓸 때 RULES.md 5.2절에 따라 서로 다른 회사나 기관의 것 둘 이상으로 확인한다. 비고에 같은 내용을 말하는 다른 절의 번호를 적었다.
- 규격의 판: Synopsys와 ZVEI의 글은 ISO 26262의 판을 문서에서 확인하지 못했다 (절 17, 18의 머리). 이 글들이 쓴 조항 번호는 비고에 옮기지 않았거나 책에 쓰지 않는다 (RULES.md 5.3절).
- 이 환경의 내려받기가 접근 거부 (403)를 받은 곳은 쓰지 않았다. 목록은 맨 끝의 "읽지 못한 쪽 (막힌 출처)"에 있다.
- 원고에 쓰기 전에 그 쪽을 직접 열어 확인한다 (RULES.md 5.2절).

## 1. UN Regulation 156 (R156)의 요약 발표 (K. F. Zastrow, UN Regulation 156 Software Update & Software Updates Management System, UNECE/ITU Future Networked Car Symposium 2021 발표 자료, 2021. https://fnc.itu.int/wp-content/uploads/2021/03/Kai-Frederik-ZASTROW-STELLANTIS-V2.pdf, 종류: 회사의 설명 글 (발표자는 OICA 기술위원회 의장이자 Stellantis 소속. 규정 본문이 아니다))

(2차 자료) UNECE의 규정 본문 (unece.org)은 이 환경의 내려받기가 접근 거부 (403)를 돌려주어 읽지 못했다 (아래 "읽지 못한 쪽"). 이 발표는 규정의 요지를 슬라이드로 옮긴 것이다. "쪽" 칸은 PDF 쪽 (슬라이드 한 장이 한 쪽)이다. 슬라이드 9 - 10은 "Examples of requirements"라고 적어 규정의 모든 요구를 나열한 것이 아님을 밝힌다.

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| V-001 | 9 | SUMS (software update management system)에서 제조사는 형식 승인된 차종마다 적용한 갱신 하나하나에 대해 정보를 기록하고 보관해야 한다. 기록 항목은 갱신의 목적, 영향받는 차량 시스템이나 기능, 형식 승인된 시스템의 요구에 영향을 주는지, 실행 방법과 조건, 적절한 verification과 validation을 거쳤다는 확인이다. | "Confirmation that the software update has undergone adequate" | A1. 같은 내용: 절 2 (UL). |
| V-002 | 10 | OTA 갱신을 하는 차량 형식에 대한 요구의 예: 갱신이 실패했을 때 시스템을 이전 버전으로 되돌릴 수 있어야 한다. | "restore systems to their previous version in case of a failed update" | A1. 같은 내용: 절 2 (UL, "restore it to the previous state"). |
| V-003 | 10 | 갱신은 차량에 갱신을 끝낼 만큼 전력이 있을 때만 실행할 수 있어야 한다. | "enough power to complete the update" | A1. |
| V-004 | 10 | 갱신 전에 사용자에게 알릴 수 있어야 하는 것: 갱신의 목적, 차량 기능의 변화, 예상 소요 시간, 갱신 중 쓸 수 없는 기능, 안전하게 실행하도록 돕는 지시. 갱신 뒤에는 성공 여부를 알릴 수 있어야 한다. | "Any vehicle functionalities which may not be available during the execution" | A1. |
| V-005 | 10 | 갱신을 운전 중에 실행하는 것이 안전하지 않을 수 있는 경우에는 갱신 동안 차를 운전할 수 없게 해야 하고, 운전자가 차의 안전이나 갱신의 성공에 영향을 주는 기능을 쓰지 못하게 해야 한다. | "Ensure the vehicle cannot be driven during the execution of the update" | A1. 이 슬라이드는 조건을 "운전 중의 갱신이 안전하지 않을 수 있는 경우"로 달았다. 운전 중의 갱신을 일률로 금지한다는 서술이 아니다. |
| V-006 | 11 | RxSWIN (Regulation x Software Identification Number)은 규정 x와 관련하여 형식 승인에 중요한 소프트웨어의 정보를 나타내는 식별자다. 새 소프트웨어가 규정 적합성에 영향을 주면 형식 승인의 확장이나 새 승인이 필요하다고 그림으로 설명한다. | "dedicated identifier representing information about the software that is type approval relevant" | A1. 같은 내용: 절 2 (UL). |

## 2. UL Solutions의 R156 설명 (UL Solutions, Software update management systems according to UNECE R156, 날짜 불명 (쪽 아래에 2026 저작권 표시), https://www.ul.com/sis/insights/software-update-management-systems-according-unece-r156, 종류: 회사의 설명 글 (검사 인증 회사의 글))

(2차 자료) 규정 본문이 아니고 회사가 R156과 ISO 24089를 요약한 글이다. "쪽" 칸은 글 안의 소제목이다. 직접 내려받아 대조했다.

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| V-007 | 본문, SUMS의 정의 | SUMS는 소프트웨어 갱신이 안전하고, 기능을 하고, 추적 가능하고, 규정에 맞게 이뤄지도록 하는 것이라고 설명한다. "규정에 맞는다"는 차량 소프트웨어가 해당 형식 승인에 계속 적합함을 뜻한다고 적는다. | "software updates are carried out in a safe, functional, traceable and compliant manner" | A1. 같은 내용: 절 1 (Zastrow). |
| V-008 | 본문, SUMS의 범위 | 갱신은 변경이므로 유효한 형식 승인에 영향을 줄 수 있고, SUMS가 갱신이 형식 승인의 범위에 주는 영향을 식별한다고 적는다. 갱신이 차량 전체 구성과 맞는지 (compatibility)를 확인하는 단계가 있다고 적는다. | "can have an influence on the valid type approval" | A1. 같은 내용: 절 1 (갱신이 형식 승인의 요구에 영향을 주는지 기록). |
| V-009 | 본문, RXSWIN 단락 | 갱신이 실패하거나 중단되면 이전 상태로 되돌릴 수 있어야 한다고 적는다. 이 문장은 RXSWIN을 소프트웨어 버전마다 고유하게 정해야 한다는 단락 안에 있다. | "you must be able to restore it to the previous state" | A1. 같은 내용: 절 1 (Zastrow). |
| V-010 | 본문, RXSWIN 단락 | 형상 관리가 핵심이고, 차량의 현재 소프트웨어 구성 상태 (부품 포함)를 정하는 식별자가 필요하다고 적는다. RXSWIN은 당국이 요구하고 제조사가 정한다. | "Configuration management is key." | A1, A5. 같은 내용: 절 1 (Zastrow). |
| V-011 | 본문, 도전 과제 | ISO 24089는 2023년 초에 발행되었고 SUMS에 대한 더 자세한 안내를 준다고 적는다. UN R156은 필요한 활동만 말하고 실제 구현 방법은 ISO 24089가 설명한다고 적는다. | "UN R156 only states the required activities" | A1. 규정과 ISO 24089의 관계에 관한 (2차 자료)의 서술이다. |
| V-012 | 본문, 맺음 | UNECE 규정은 요구사항을 명시하나 어떻게 충족할지는 제조사에게 맡기며, SUMS는 중립 기관의 감사와 인증이 필요하다고 적는다. | "leaves it up to manufacturers to determine how they meet those requirements" | A1. |

## 3. NIST SP 800-193 (A. Regenscheid, Platform Firmware Resiliency Guidelines, 2018-05. https://nvlpubs.nist.gov/nistpubs/SpecialPublications/NIST.SP.800-193.pdf, 종류: 발행 기관 (미국 NIST의 지침))

PC급 platform firmware를 대상으로 한 보안 지침이다. 차량 ECU를 직접 다루지 않는다. "쪽" 칸은 PDF 쪽이고, 문서에 인쇄된 쪽은 비고에 적었다. 이 지침의 "shall"은 이 지침을 따르려는 구현에 대한 것이며 자동차 규격의 요구가 아니다.

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| V-013 | 28 | 갱신에 쓰는 신뢰 뿌리 (RTU) 또는 신뢰 사슬 (CTU)이 변경 가능하면, 인증된 갱신으로만 바꾸고, 그 갱신 도중 예기치 않은 중대 사건이 있어도 항상 동작하거나 다음 재시작 때 복구 가능해야 한다고 적는다. 예로 flash를 쓰는 중의 전원 상실을 든다. | "power loss in the middle of a flash write operation" | A2. 인쇄 쪽 20 (4.1.2 항목 2). 갱신 장치 자체를 갱신하는 경우의 요구다. |
| V-014 | 23 | 자동 복구 (automatic recovery)의 설명: 시스템이 firmware 이미지의 손상을 감지하면, 손상된 이미지와 떨어진 곳 (예: 두 번째 flash chip, 보호된 영역)에 둔 백업 이미지로 복구하는 것이다. | "recover from a backup firmware image stored in a location" | A2. 인쇄 쪽 15 (3.5.2). 두 자리의 이미지를 두는 설계를 설명하는 문장이다. |
| V-015 | 23 | 인증된 갱신이 버전 번호를 확인하는 구현에서는 이전 버전으로 되돌리는 (rollback) 별도 절차를 둘 수 있고, 그 절차가 물리적 현장 확인을 요구할 수 있다고 적는다. 목적은 알려진 취약점이 있는 옛 firmware를 공격자가 설치하는 것을 막는 것이다. | "special update process for rolling back the installed firmware" | A2. 인쇄 쪽 15 (3.5.2 항목 3). |
| V-016 | 31 | 되돌리기 (rollback)는 제대로 동작하지 않는 갱신에서 복구하는 수단이 될 수 있지만, 권한 없는 rollback은 공격자가 취약한 이미지를 되살리게 할 수 있다고 적는다. rollback을 지원하는 장치는 이를 막는 보안 통제가 있어야 한다고 적는다. | "unauthorized rollback could allow an attacker to restore a vulnerable firmware image" | A2. 인쇄 쪽 23 (4.2.1.3의 주). 안전을 위한 되돌리기와 보안을 위한 되돌리기 금지가 맞서는 점을 보인다. |
| V-017 | 35 | firmware 복구는 지역에 저장한 백업이나 다른 곳에서 받은 복구 이미지로 하며, 어느 경우든 복구 전에 인증된 갱신 메커니즘으로 이미지의 무결성과 진짜임을 확인하도록 지침이 정한다고 적는다. | "locally-stored backup or to a recovery image downloaded from another source" | A2. 인쇄 쪽 27 (4.4.1). |

## 4. MCUboot 설계 문서 (MCUboot 프로젝트, MCUboot design, 최신판 (판과 날짜는 쪽에 없음). https://docs.mcuboot.com/design.html, 종류: 공식 문서 (오픈 소스 bootloader의 공식 설계 문서))

"쪽" 칸은 문서 안의 소제목이다. 직접 내려받아 글자를 대조했다. 이 문서는 MCU용 secure bootloader의 설계를 설명하며, 안전 규격의 요구가 아니다.

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| V-018 | Image slots | flash를 이미지 영역으로 나누고 각 영역에 primary slot과 secondary slot 둘을 둔다. 보통 primary slot의 이미지만 실행하며, secondary의 이미지를 실행하려면 두 이미지를 맞바꾸거나 primary에 덮어써서 옮긴다. 빌드할 때 swap 방식과 덮어쓰기 방식 중 하나를 고른다. | "must be configured at build time to choose" | A2. |
| V-019 | Boot swap types | 갱신은 두 단계로 할 수 있다. 먼저 "test" swap으로 새 이미지를 부팅하고, 새 이미지가 스스로 flash에 "OK"를 표시하면 그 swap이 영구가 된다. 표시하지 않으면 다음 부팅 때 원래 이미지로 되돌리는 "revert" swap을 한다. | "make test swaps permanent only after performing a self-test" | A2. 갱신 뒤 확인을 거쳐야 확정하는 설계의 공식 설명. |
| V-020 | Boot swap types | test swap의 목적은 나쁜 firmware 때문에 장치를 못 쓰게 되는 것 ("bricked")을 막는 것이다. 새 이미지가 부팅 직후 죽으면 다음 reset에서 이전의 동작하는 이미지로 되돌린다고 적는다. | "rather than booting the bad image again" | A2. |
| V-021 | Image slots (swap 방식의 설명 끝) | 덮어쓰기와 direct-XIP 방식이 swap 방식보다 구현이 훨씬 단순하다고 적는다. swap 방식에서는 bootloader가 이미지를 맞바꾸는 도중에 reset이 와도 제대로 동작해야 하기 때문이다. | "must work properly even when it is reset during the middle of an image swap" | A2. 갱신 중의 전원 상실에 대한 설계 비용의 설명. |
| V-022 | Image trailer | bootloader는 flash 영역 끝의 metadata (image trailer)로 현재 상태를 판단한다. trailer의 swap status는 이미지 swap의 진행을 기록한다. swap 동안 이 metadata의 일부를 scratch 영역으로 옮겼다 되돌린다. | "records the progress of an image swap" | A2. |
| V-023 | Swap using scratch | scratch 영역을 쓰는 swap은 flash의 지울 수 있는 횟수 (erase cycle)에 따라 갱신 가능 횟수가 제한된다. 문서는 갱신 횟수를 erase cycle 수 나누기 (이미지 크기 나누기 scratch 크기)로 어림하는 식을 준다. | "number of erase cycles supported by the flash hardware" | A2. 갱신 횟수의 flash 수명 제약. |

## 5. Uptane Standard 2.0.0 (Uptane 프로젝트, Uptane Standard for Design and Implementation, 2.0.0판. https://uptane.org/docs/2.0.0/standard/uptane-standard, 종류: 공식 문서 (표준 문서의 공개판))

자동차 ECU의 software update를 보안 쪽에서 다루는 표준이다. 이 페이지는 최신판 (2.1.0)이 따로 있다고 안내한다. "쪽" 칸은 절 번호다 (이 문서의 번호이며, 규격 조항이 아니다). 읽은 범위에서 갱신 도중의 전원 차단이나 쓰기의 원자성을 다루는 문장은 찾지 못했다 ("power" 낱말이 갱신 전력의 한 곳뿐).

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| V-024 | 4.3.3 Interfere with ECU functionality | 공격 유형 중 rollback attack을 ECU가 이전에 유효했던, 현재 설치된 것보다 낮은 소프트웨어 버전을 설치하게 하는 것으로 정의한다. | "install a previously valid software revision that is older than" | A2. 같은 내용: 절 3의 rollback 설명 (보안 쪽). |
| V-025 | 4.3.3 Interfere with ECU functionality | mix-and-match attack을 이미지 각각은 유효해도 서로 호환되지 않는 묶음을 설치하게 하는 것으로 정의한다. 유효한 버전 중에 서로 호환되지 않는 것이 있을 때 가능하다고 적는다. | "some of the updates do not interoperate properly" | A2. 변경 조합의 정합성 문제 (A1, A5와도 닿는다). |
| V-026 | 5.2.3.1.1 Custom metadata about images | 이미지마다 release counter (새 버전을 낼 때마다 증가)와 호환되는 ECU 모델의 hardware identifier를 두라고 권한다. counter는 Director가 침해돼도 rollback을 막는 데 쓸 수 있고, hardware ID는 호환되지 않는 이미지의 설치를 막는다. 이 항목은 "SHOULD" 수준이다. | "A release counter, to be incremented each time a new version" | A2, A5. 호환성과 버전 정보를 갱신 metadata에 넣는 설계. |
| V-027 | 5.4.2.1.2 ECU version report | ECU는 갱신 서버에 version report를 보내며, report에는 ECU의 고유 식별자와 현재 설치된 이미지의 파일 이름, 길이, hash가 들어간다고 정한다. | "The filename, length, and hashes of its currently installed image" | A2, A6. 현장의 차량이 무슨 버전을 가졌는지 서버가 아는 방법. |
| V-028 | 5.4 In-vehicle implementation requirements | Primary ECU는 이미지 metadata를 설치하기 전에 완전 검증 (full verification)을 해야 하고 (SHALL), Secondary ECU는 가능하면 완전 검증을, 못 하면 최소한 부분 검증을 해야 한다. | "A Primary ECU SHALL perform full verification" | A2. |

## 6. FAA AC 00-69 (FAA, Best Practices for Airborne Software Development Assurance Using EUROCAE ED-12( ) and RTCA DO-178( ), 2017-07-21. https://www.faa.gov/documentLibrary/media/Advisory_Circular/AC_00-69.pdf, 종류: 발행 기관 (FAA의 advisory circular))

이 AC는 지침이 아니라 "best practices"를 보완 정보로 준다고 스스로 밝힌다. "쪽" 칸은 PDF 쪽이다 (인쇄 쪽과 같다). 직접 내려받아 대조했다. 받아 둔 문서 faa-ac-20-115d (references/)와 같은 날짜의 짝이다.

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| V-029 | 1 | 이 AC는 DO-178C와 AC 20-115D에 대한 "best practices"를 담으며 지침이 아니라 보완 정보라고 밝힌다. | "not intended as guidance but rather as complementary information" | A3. |
| V-030 | 1 | software change impact analysis (CIA)는 제안한 소프트웨어가 바탕으로 삼는 출시된 소프트웨어 baseline을 식별하고, 변경과 영향의 요약, 이번 변경에서 고칠 문제 보고서 (problem report)와 변경 요청의 목록, 새로 활성화하거나 구현할 기능의 목록을 준다고 적는다. | "identifies the released software baseline upon which the proposed software" | A3. |
| V-031 | 2 | CIA가 다루는 변경 항목의 목록: software level, 개발과 verification 환경, 소프트웨어 process, tool (새 버전이나 쓰임의 변경), processor와 하드웨어 부품과 interface, configuration data (특히 기능을 켜고 끌 때), 소프트웨어 interface와 입출력 요구, 요구와 설계와 구조와 code 요소 (수정된 것뿐 아니라 영향받는 것까지). | "Configuration data, especially when activating or deactivating functions;" | A3, A5. 같은 내용: 절 7. |
| V-032 | 2 | CIA는 해당하는 항목마다 결과로 생기는 영향을 서술하고, DO-178C 등을 계속 만족하고 안전한 운용의 요구를 계속 만족하기 위해 할 활동을 식별한다고 적는다. | "identifies the activities to be performed" | A3. |

## 7. FAA AC 20-115D (FAA, Airborne Software Development Assurance Using EUROCAE ED-12( ) and RTCA DO-178( ), 2017-07-21. https://www.faa.gov/documentLibrary/media/Advisory_Circular/AC_20-115D.pdf, 종류: 발행 기관 (FAA의 advisory circular))

받아 둔 문서 faa-ac-20-115d (references/)와 같은 문서다. 웹에서 다시 내려받아 아래 쪽의 글자를 대조했다. 이 AC는 수락 가능한 한 가지 방법이며 의무가 아니고, 이 방법을 쓰면 해당하는 모든 점에서 따라야 한다고 1쪽이 적는다. "쪽" 칸은 PDF 쪽이다 (인쇄 쪽과 같다). 파일을 책에서 인용할 때는 references/의 사본으로 쪽을 다시 확인한다.

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| V-033 | 9 | 기존 (legacy) 소프트웨어를 수정해야 하면 software change impact analysis (CIA)로 수정의 범위, 수정의 영향, 수정된 소프트웨어가 의도한 기능을 하고 인정받은 compliance 수단을 계속 만족함을 보이는 데 필요한 verification을 정하라고 적는다. | "conduct a software change impact analysis (CIA) to determine the extent of the modifications" | A3. 9.b.(4)는 이 AC의 항 번호다 (규격 조항이 아니다). |
| V-034 | 9 | CIA의 절차: 포함할 소프트웨어 변경을 식별하고 DO-178C의 12.1이 말하는 분석을 한다. CIA가 가리키는 verification을 한다. CIA의 결과를 PSAC (Plan for Software Aspects of Certification)나 SAS (Software Accomplishment Summary)에 요약한다. | "Summarize the results of the CIA in the Plan for Software Aspects of" | A3. |
| V-035 | 10 | configuration data를 쓴다면 (DO-178C의 "Parameter Data Item"이 뜻하는 것), 그 data의 process가 이전 인증 프로젝트에서 FAA에게 평가받아 수락된 것이어야 한다. 그런 process가 없으면 DO-178C에 맞게 parameter data item을 쓰는 새 process를 세우라고 적는다. | "In the absence of processes for using configuration data" | A5. 9.b.(8)(b). 같은 취지가 3쪽 5.a.(4)에도 있다. |
| V-036 | 3 | 새 소프트웨어를 이전 승인된 process로 개발할 수 있는 조건의 하나로, configuration data를 쓰면 그 process가 이전 인증 프로젝트에서 평가받은 것이어야 한다고 적는다. | "If using configuration data, as defined under" | A5. 5.a.(4). |
| V-037 | 12 | tool이나 tool의 운용 환경이 바뀌면 DO-330의 해당 절에 따라 tool change impact analysis를 하라고 적는다. | "tool change impact analysis" | A3. tool 쪽의 변경 영향 분석. |

## 8. FDA 안내서 (FDA, Deciding When to Submit a 510(k) for a Software Change to an Existing Device: Guidance for Industry and FDA Staff, 2017-10-25. https://www.fda.gov/media/99785/download, 종류: 발행 기관 (미국 FDA의 비구속 안내서))

의료기기의 소프트웨어 변경에 관한 안내서이며 "Contains Nonbinding Recommendations"라고 표시한다. 자동차에 직접 적용되지 않는다. 이 환경의 내려받기 (curl)는 이 주소에서 404를 받았고, WebFetch 도구가 저장한 PDF 사본으로 읽었다. 쪽은 PDF 쪽이며 인쇄 쪽은 6, 7, 8이다 (표지 포함 PDF 쪽에서 4를 뺀다). 첫 쪽의 안내는 21 CFR 820이 2026-02-02에 QMSR로 바뀌었고 이 안내서는 그 전에 나왔다고 적는다.

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| V-038 | 10 | 변경이 기기의 안전이나 효과에 크게 영향을 줄 수 있는지 먼저 위험 기반 평가 (risk-based assessment)를 하라고 한다. 이 평가는 변경으로 생기는 새 위험과 바뀌는 기존 위험을 모두 식별하고 분석해야 한다. | "should first conduct a risk-based assessment" | A3. 인쇄 쪽 6. |
| V-039 | 10 | 변경이 의도하지 않은 결과를 낼 수 있음을 따로 평가하라고 한다. 예로 의도한 OS 갱신이 device driver와 기기 안의 code에 의도하지 않은 영향을 주거나, 호환을 위해 다른 구성요소의 갱신을 요구할 수 있다고 든다. | "may trigger unintended effects in device drivers and software code" | A3. 인쇄 쪽 6. |
| V-040 | 11 | 소프트웨어의 고장은 체계적 (systematic)이라 발생 확률을 통계 방법으로 정할 수 없으므로, 해로움의 발생 확률 전체를 어림할 수 없으면 위험의 어림은 해로움의 심각도만으로 하라고 적는다. | "the estimation of risk should be based on the severity of harm alone" | A3. 인쇄 쪽 7. 의료기기 맥락의 서술이다. |
| V-041 | 11 | 위험 평가로 새 510(k)가 필요 없다고 판단했다면 그 판단을 정상적인 verification과 validation의 성공으로 확인해야 한다. 예상 밖의 결과가 나오면 판단을 다시 따져야 한다. 반대로 위험 평가가 크게 영향을 줄 수 있다고 하면 test가 성공해도 새 제출이 필요하다. | "this decision should be confirmed by successful, routine verification and validation" | A3. 인쇄 쪽 7. 회귀 test의 역할을 "판단의 확인"으로 설명하는 서술이다. |
| V-042 | 11 | 동시에 여러 변경을 고려할 때는 각 변경을 따로, 그리고 합쳐서 평가하라고 한다. 소프트웨어에서는 code의 줄 하나하나의 변경이 기기의 하나하나의 변경이 아닐 수 있다고 적는다. | "each change should be assessed separately, as well as in aggregate" | A3. 인쇄 쪽 7. |
| V-043 | 12 | 누적 효과가 제출 기준을 넘으면 새 510(k)를 내야 하고, 넘지 않으면 제조사가 변경을 문서화해야 한다. 소프트웨어 변경도 품질 시스템 (QS 규정)에 따라 문서화해야 한다고 적는다. | "When the cumulative effect of individual changes triggers the regulatory" | A3. 인쇄 쪽 8. |

## 9. RTCA와 EUROCAE의 FAS topic paper (FAS 사용자 그룹, FTP1034 Rev 3, DO-178C/ED-12C and DO-278A/ED-109A Annex A Table A-5 Objectives #8, 9 Differences, 2022-09-21. https://rtca.org/wp-content/uploads/2024/06/FTP1034_3-PUBLICATION.pdf, 종류: 공식 문서 (RTCA의 공개 문서이나 "공식 정책이나 입장이 아니며 지침으로 읽지 말라"고 스스로 밝힌다))

FAS (Forum for Aeronautical Software)는 DO-178C 사용자 그룹이며 이 문서는 그 그룹의 의견이다. 문서 자신이 "not to be construed as guidance"라고 적는다. "쪽" 칸은 PDF 쪽이다 (문서 안의 쪽 번호와 같다). DO-178C의 절 번호 (6.6a, 6.6b, Table A-5, A-7)는 이 문서가 적은 것이며 책에는 쓰지 않는다.

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| V-044 | 3 | DO-178C에는 parameter data item (PDI)에 관한 새 목표 둘이 있다. Annex A Table A-5의 목표 8은 "PDI 파일이 맞고 완전하다", 목표 9는 "PDI 파일의 verification이 이뤄졌다"이다. 목표 8은 Level D에도 적용되나 목표 9는 아니다. | "Parameter Data Item File is correct and complete." | A5. |
| V-045 | 4 | 목표 8의 전체 문장은 PDI 파일이 상위 요구가 정한 구조를 따르는지 verify하라고 한다. 상위 요구가 정의하지 않은 요소가 없어야 하고, 각 data 요소가 올바른 값을 가지며 다른 요소와 일관되고 속성을 지킴을 보여야 한다. | "should also be shown to have the correct value" | A5. |
| V-046 | 4 | 목표 9는 PDI 파일이 크고 복잡할 수 있으므로 verification이 관련 있고 완전하다는 확신을 더하려고 추가되었다. 파일의 모든 요소가 verification에서 다뤄졌다는 증거가 필요하며, code의 structural coverage 목표와 어느 정도 같다고 적는다. | "every single element of the Parameter Data Item File has been covered" | A5. 증거의 한 방법으로 PDI의 요소와 verification case, procedure, 결과를 잇는 trace를 예로 든다 (유일한 방법이 아니라고 적는다). |
| V-047 | 4 | 목표 9는 Level A, B, C에 적용되고 Level A와 B에서는 독립성이 있다고 적는다. | "applying to Levels A, B, and C" | A5. DO-178C의 수준 (Level)은 항공의 것이며 ASIL과 대응하지 않는다. |

## 10. Myklebust 등 (T. Myklebust, T. Stalhane, G. K. Hanssen, T. Wien, B. Haugset, Scrum, documentation and the IEC 61508-3:2010 software standard, PSAM 12 학회 논문 (연도는 파일 이름과 학회 이름으로 추정한 2014년경이며 문서 안에서 확인하지 못함). https://www.sintef.no/globalassets/_div.-opprydding-2023/ec-61508-documentation-and-safescrum-psam12.pdf, 종류: 논문 (연구 기관 SINTEF의 공개본))

IEC 61508 (산업 일반의 기능 안전)을 대상으로 한 논문이며 ISO 26262에 관한 것이 아니다. 저자 중 한 사람은 ABB 소속이다. "쪽" 칸은 PDF 쪽이다. 저자들 자신의 견해와 경험을 적은 부분이 있다 ("In our opinion").

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| V-048 | 1 | 저자들은 IEC 61508과 관련 규격이 계획을 포함한 문서화를 강하게 요구하고, agile은 문서를 줄이고 동작하는 소프트웨어를 만들고 유지하는 것을 목표의 하나로 삼아 서로 어긋난다고 적는다. 안전 규격 준수의 평가는 agile 방법의 범위 밖이라고도 적는다. | "Assessment of compliance with standards like IEC 61508 is outside the scope of agile methods." | A4. |
| V-049 | 1 | 안전 관련 소프트웨어의 문서가 일부 경우 전체 프로젝트 자원의 최대 50%를 쓴다고 인용 [5]를 달아 적는다. 문서 부담은 agile만의 문제가 아니라 안전 관련 개발 전반의 문제라고 적는다. | "up to 50% of all project resources has been spent on activities" | A4. 인용 [5]의 근거는 읽지 않았다. |
| V-050 | 3 | SafeScrum은 기능 product backlog와 안전 product backlog 둘을 두고, 기능 항목이 어느 안전 요구에 영향을 주는지를 계속 추적한다. 반복마다 추적 정보의 기록과 유지를 별도의 활동으로 넣는다. | "a separate activity in each sprint" | A4. |
| V-051 | 3 | 각 Scrum 반복을 작은 waterfall이나 V-model로 볼 수 있다고 적는다. 추적은 지원 도구 없이는 효율적으로 하기 어렵다고 적는다. test를 먼저 쓰는 방식 (TDD)은 회귀 test를 가능하게 하고 code의 문서가 된다고 적는다. | "Each Scrum iteration can be considered as a mini waterfall project" | A4. 같은 내용 (조건으로서의 추적과 test): 절 11. |
| V-052 | 3 | IEC 61508에 맞추려면 각 반복의 끝에서 기능 요구의 validation과 함께 RAMS (신뢰성, 가용성, 유지보수성, 안전) validation을 하고, 필요하면 assessor가 이 validation과 반복 후 회고에 참여할 수 있다고 제안한다. 모든 반복이 끝난 뒤에 최종 RAMS validation을 따로 한다. | "an assessor may take part in this validation for each sprint" | A4. 제안이다. 규격의 요구로 서술한 것이 아니다. |

## 11. Ribeiro 등 (J. E. F. Ribeiro, M. Zenha-Rela, J. G. Silva, From Waterfallish Aerospace Certification onto Agile Certifiable Iterations, arXiv:2503.04265, 2025-03. https://arxiv.org/pdf/2503.04265, 종류: 논문 (저자가 arXiv에 공개한 preprint. 동료 심사를 거쳤는지는 문서에서 확인하지 못함))

항공 (DO-178C)을 대상으로 한 논문이다. "쪽" 칸은 PDF 쪽이다. 도구의 효과 (업계 전문가와 함께 설계하고 검증했다는 주장)는 저자의 주장이며 이 기록에서 확인하지 않았다.

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| V-053 | 1 | 초록은 agile이 요구 변경을 수용하는 능력 때문에 항공 업계에서 인기를 얻지만, 안전 필수 분야는 DO-178C 같은 규정이 요구하는 철저한 문서화를 요구한다고 적는다. 어려움의 핵심은 문서의 내용이 아니라 시스템 요구에서 모든 test와 verification 증거까지의 포괄적인 추적성이라고 적는다. | "comprehensive traceability from system-level requirements to all sorts of testing" | A4. |
| V-054 | 1 | 추적성의 작업이 현재는 대부분 수작업이며 프로젝트의 끝에 하므로 agile화를 막는다고 적는다. 해법으로 반복마다 DO-178C 문서를 만들어 앞서 만든 문서와 합치는 "continuous certification"의 전략과 도구를 제안한다. | "blocks efforts to agilize the development of software for aerospace" | A4. |
| V-055 | 2 | DO-178C 같은 규격은 특정한 개발 모델을 정하지 않으며, 해당 안전 수준의 목표를 충족한다는 증거가 충분하면 다른 방법을 쓸 수 있다고 적는다 (논문의 서론에서 인용 [1,2,3,4]를 달아). | "do not dictate a specific" | A4. 규격의 요구에 관한 서술이며 이 논문의 서술 하나뿐이다. 책에 쓰려면 별도 확인한다. |
| V-056 | 2 | 저자들은 agile을 쓰려는 안전 필수 분야에서 문서가 수작업에 크게 의존해 관리되는 것을 걱정거리로 든다. 인증 당국이 광범위한 문서화와 추적성을 요구한다고 서술한다. | "extensive documentation and traceability are mandated by certification authorities" | A4. 저자의 서술이다 (인용 [8] 뒤의 문장). |

## 12. 49 CFR Part 573 (미국 연방규정집 제49편 제573부, Defect and Noncompliance Responsibility and Reports, 2022-10-01판. https://www.govinfo.gov/content/pkg/CFR-2022-title49-vol7-part573.pdf, 종류: 발행 기관 (미국 정부 간행물))

NHTSA의 recall 보고 의무를 정한 연방 규정이다. 이 환경의 내려받기가 NHTSA의 웹 사이트 (nhtsa.gov)에서 접근 거부 (403)를 받아, 제도의 설명 쪽은 읽지 못했고 규정 본문만 읽었다. "쪽" 칸은 PDF 쪽 (PDF에서 글자 층을 단 구분 없이 뽑은 쪽)이다.

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| V-057 | 3 | 제조사는 자기나 NHTSA 청장이 자동차 안전에 관련된다고 판단한 결함마다 NHTSA에 보고서를 내야 한다. | "determines to be related to motor vehicle safety" | A6. 573.6(a). |
| V-058 | 3 | 보고서는 결함이 안전 관련으로 판단된 뒤 5 근무일 안에 내야 한다. 첫 보고서에는 최소한 (c)(1), (2), (5)의 정보를 넣고, 그 기간에 얻지 못한 나머지는 정확함을 확인한 뒤 5 근무일 안에 낸다. 이미 낸 정보가 새 정보로 바뀌면 5 근무일 안에 고쳐 낸다. | "not more than 5 working days after a" | A6. 573.6(b). |
| V-059 | 5 | 보고서에는 결함과 합리적으로 관련된 안전 위험의 서술, 판단의 근거가 된 주요 사건의 연대기 (chronology), 결함을 바로잡는 제조사의 계획 (소유자의 수리 비용 상환 계획 포함)을 넣는다. | "a chronology of all principal events that were" | A6. 573.6(c)의 항목들. |
| V-060 | 7 | recall 캠페인을 하는 제조사는 캠페인 시작 분기부터 연속 여섯 분기 동안 분기 보고서를 내야 한다. 보고 항목에는 알림을 시작하고 끝낸 날짜, 대상 차량 수, 점검하고 수리한 차량 수가 있다. | "for each of six consecutive quarters" | A6. 573.7. 현장 조치의 진행을 감독하는 보고다. |

## 13. Part 573 Safety Recall Report 23V-838 (Tesla, Inc.가 NHTSA에 낸 보고서, 2023-12-12. https://static.nhtsa.gov/odi/rcl/2023/RCLRPT-23V838-8276.PDF, 종류: 발행 기관 (NHTSA의 공개 recall 자료실에 있는 제조사 제출 문서. 내용은 제조사의 서술))

NHTSA가 공개하는 recall 보고서이며, 글은 제조사가 쓴 것이다. 제조사는 NHTSA의 분석에 동의하지 않는다고 같은 보고서에 적었다. 여기서는 소프트웨어 결함 recall의 절차 (조사 -> 자발적 recall -> OTA 수정)를 보이는 용도로만 쓴다. 결함의 원인은 "NR" (보고하지 않음)이다. "쪽" 칸은 PDF 쪽이다.

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| V-061 | 1 | 대상 차량은 2,031,220대이며 제조사가 추정한 결함 비율은 100%다. | "Number of potentially involved : 2,031,220" | A6. |
| V-062 | 4 | 연대기는 NHTSA가 2021-08-13에 Preliminary Evaluation (PE21-020)을 열어 11건의 사고를 조사하고, 2022-06-08에 Engineering Analysis (EA22-002)로 올렸으며, 제조사가 2023-12-05에 자발적 recall을 하기로 했다고 적는다. | "NHTSA opened a Preliminary Evaluation (PE21-020)" | A6. 현장의 사고 보고에서 시작해 조사 단계 둘을 거쳐 recall에 이르는 한 사례의 경과. |
| V-063 | 4 | 제조사는 NHTSA의 분석에 동의하지 않지만 조사를 마무리하려고 자발적으로 recall을 하기로 했다고 적는다. | "While not concurring with the agency" | A6. 제조사의 서술이다. |
| V-064 | 4 | 관련 구성요소란에 "Vehicle Software"를 적고, 설명은 recall 수정을 담은 버전 이전의 모든 Autosteer 버전이다. | "Component Name 1 : Vehicle Software" | A6. recall 보고서가 소프트웨어를 구성요소로 적는 사례. |
| V-065 | 5 | 수정은 고객 비용 없이 over-the-air (OTA) 소프트웨어로 하며, 소프트웨어 버전 2023.44.30으로 2023-12-12 무렵 일부 차량부터 배포를 시작하고 나머지는 나중에 배포한다고 적는다. | "affected vehicles will receive an over-the-air" | A6, A1. 같은 내용 (OTA 수정이 recall의 해결책이 됨): 이 보고서뿐. |

## 14. Haddon-Cave (C. Haddon-Cave QC, The Nimrod Review: An independent review into the broader issues surrounding the loss of the RAF Nimrod MR2 Aircraft XV230 in Afghanistan in 2006, HC 1025, 2009-10. https://assets.publishing.service.gov.uk/government/uploads/system/uploads/attachment_data/file/229037/1025.pdf, 종류: 발행 기관 (영국 정부가 의회에 낸 독립 조사 보고서))

영국 군용기 사고의 조사 보고서이며, 안전 사례 (safety case) 제도에 대한 22장의 평가가 B7의 근거다. 이 보고서가 평가하는 safety case는 영국 국방부의 제도 (Def Stan 00-56)이며 자동차나 ISO 26262의 것이 아니다. "쪽" 칸은 PDF 쪽이다. 인쇄된 쪽 번호는 PDF 쪽에서 1을 뺀 값이다 (22장은 인쇄 쪽 533 - 545). 직접 내려받아 대조했다. 인용문에 든 따옴표는 원문의 곡선 따옴표를 ASCII로 바꾸었다.

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| V-066 | 534 | 22장의 요약은 safety case 제도가 길을 잃었고, 진짜 안전을 희생해 "paper safety" 문화를 낳았으며, 비용 대비 가치가 없다고 결론짓는다. | "Safety Case regime has lost its way" | B7. 인쇄 쪽 533 (22장 요약 1). |
| V-067 | 534 | 군 환경의 safety case의 결함으로 관료적 길이, 모호한 언어, 사소한 위험과 중대한 위험에 같은 주의, 과거 서류를 파헤치는 작업, 업체에 맡김, 운용자의 입력 부족, 비례하지 않음, 준수만을 위한 작업, 과정만 보는 audit, 안전하다는 선입견과 서가에 꽂아 둠을 든다. | "audits of process only" | B7. 인쇄 쪽 533 (22장 요약 2). |
| V-068 | 534 | safety case는 위험을 생각하는 데 돕도록 의도했으나 그 자체가 목적이 되었다고 요약한다. 민간 항공과 미국, 캐나다, 호주 공군은 safety case를 쓰지 않고 감항성을 다르게 관리한다고 적는다. | "an aid to thinking about risk but have become an end" | B7. 인쇄 쪽 533 (요약 4와 5). 이 서술은 2009년 영국 군용기의 맥락이다. |
| V-069 | 535 | 일부 safety case가 사람들에게 위험을 서류의 "금고"에 넣어 두고 잊어도 된다는 거짓 안전감을 준다고 적는다. safety case가 있다는 사실만으로 그 platform이 안전하다는 인식이 퍼져 있다고 적는다. | "a false sense of security that a Safety Case is some sort of" | B7. 인쇄 쪽 534 (22.3). |
| V-070 | 535 | 서류를 많이 만드는 것은 쉽고, 핵심 위험에 집중해 생각하는 것이 더 어렵다고 적는다. safety case의 성장이 platform 자체에 대한 점검, 정비, 개선에 쓸 시간과 돈과 인력을 다른 데로 돌렸다고 우려한다. | "It is easy to produce vast quantities of paper" | B7. 인쇄 쪽 534 (22.5, 22.6). |
| V-071 | 535 | 결함 (1): safety case와 보고서가 너무 길고 관료적이며 반복적이고 세부로 막혀 있어, 때로 청구서 정당화와 "thud factor"를 위한 것이라고 적는다. | "too long, bureaucratic, repetitive and comprise impenetrable detail" | B7. 인쇄 쪽 534 (22.7(1)). |
| V-072 | 535 | 결함 (3): 사소한 위험과 대재앙 수준의 위험에 같은 주의를 주고 주된 위험을 부각하지 못한다고 적는다. | "giving equal attention and treatment to minor irrelevant hazards" | B7. 인쇄 쪽 534 (22.7(3)). |
| V-073 | 535 | 결함 (6): 운용자와 정비사의 입력이 없거나 부족하다고 적고, 한 사례로 RAF Kinloss의 운용자들이 원래 Nimrod safety case가 있는 줄도 몰랐다고 적는다. | "input from operators and maintainers" | B7. 인쇄 쪽 534 (22.7(5), (6)). 업체에 외주하는 문제도 같은 항에 있다. |
| V-074 | 536 | 결함 (9): 준수만을 위해 쓴 safety case는 기계적인 같은 틀을 따르고, 고객이나 설계자가 원하는 답, 곧 platform이 안전하다는 답을 내는 경향이 있다고 적는다. | "the answer which the customer or designer wants" | B7. 인쇄 쪽 535 (22.7(9)). |
| V-075 | 536 | 결함 (11): safety case가 platform이 "안전하다"고 주장하며, 왜 위험이 platform을 안전하지 않게 만들 수 있는지를 따지지 않아 자기충족적 예언에 그친다고 적는다. 각주 6은 GSN의 최상위 목표 "platform이 수용할 만큼 안전하다고 간주된다"가 이미 가정한 결론을 이끌 수 있다고 적는다. | "can drive a conclusion that is already assumed" | B7. 인쇄 쪽 535 (22.7(11)과 각주 6). 결론을 먼저 정해 놓은 논증에 대한 서술이다. |
| V-076 | 536 | 결함 (10): safety case의 audit은 실질보다 과정을 보는 경향이 있다고 적는다. 결함 (12): safety case는 한 번 쓰면 서가에서 잠자며 위험을 따라가는 살아 있는 문서가 아니라고 적는다. | "tend to look at the process rather than the substance" | B7. 인쇄 쪽 535 (22.7(10), (12)). |
| V-077 | 536 | 결함 (7): safety case의 비용이 다루는 문제, 위험, 변경에 비해 터무니없이 크다고 적는다. | "out of proportion to the issues, risks or modifications" | B7, A3. 인쇄 쪽 535 (22.7(7)). 변경 (modification)에 대한 safety case의 비례성. |
| V-078 | 537 | Ladbroke Grove 조사에서 증인의 말을 인용해, audit이 현장에서 일어나야 할 일이 일어나는지를 확인하지 않고 서류의 흔적을 쫓았다고 적는다. safety case 자체가 상황에 적절한지라는 핵심 질문은 좀처럼 묻지 않는다고 인용한다. | "chase paper trails rather than check" | B7. 인쇄 쪽 536 (22.13). Cullen 보고서에 있는 증인의 말을 이 보고서가 인용한 것이다. |
| V-079 | 537 | Nimrod의 Safety Case 1은 위 결함들의 "유감스러운 본보기"이고, Safety Case 2도 크기가 커졌으나 명료성은 나아지지 않아 "읽기 어렵고 반복되는 문서"라고 적는다. | "an impenetrable and repetitious document" | B7. 인쇄 쪽 536 (22.14). |
| V-080 | 542 | Cullen 경이 이 보고서의 저자에게 safety case는 "위험을 생각하는 데 돕는 것이지 그 자체가 목적이 아니다"라고 강조했다고 적는다. | "not an end in themselves" | B7. 인쇄 쪽 541 (22.24). |
| V-081 | 544 | Nimrod Safety Case 2의 업체 청구액이 300만 파운드를 넘고 표준 단가로 75,000 man hour에 해당한다고 적는다. 보고서는 이 제도가 국방부의 지출에 비해 감항성에 이득을 주는 가치가 없다고 평가한다. | "75,000 man hours" | B7. 인쇄 쪽 543 (22.34). |
| V-082 | 544 | Def Stan 00-56의 safety case 정의 ("체계적인 논증과 증거"로 "시스템이 안전하다"를 보임)가 번거롭고 문서 중심인 논증을 부추겨 자기충족적 예언으로 이끈다고 평가한다. | "document-heavy" | B7. 인쇄 쪽 543 (22.36). |
| V-083 | 545 | 권고 22.2와 22.6: safety case를 "Risk Case"로 이름을 바꿔 안전을 가정하지 않고 위험을 관리하는 것임을 강조하고, 정의를 "위험이 ALARP로 관리되고 있다는 합리적 확인"으로 바꾼다. 원칙은 간결, 자체 제작, 접근성, 비례, 이해 용이, 문서 최소 (SHAPED)다. | "reasonable confirmation that risks are managed to ALARP" | B7. 인쇄 쪽 544 (권고 22.2 - 22.6). |
| V-084 | 546 | 단순한 변경에는 Risk Case가 몇 줄이거나 핵심 추가 위험과 완화를 적은 몇 쪽이면 된다고 적고, 복잡한 변경에는 더 길 수 있다고 적는다. | "no additional material risks are anticipated" | B7, A3. 인쇄 쪽 545 (22.40). 변경에 따른 safety case 갱신의 규모에 대한 한 서술이다. |

## 15. Bloomfield와 Rushby (R. Bloomfield, J. Rushby, Assurance 2.0: A Manifesto, arXiv:2004.10474v3, 2021-01. https://arxiv.org/pdf/2004.10474, 종류: 논문 (저자가 공개한 preprint))

assurance case의 약한 곳을 찾는 방법을 제안하는 논문이며, 저자들의 제안이다 (규제 기관의 지침이 아니다). "쪽" 칸은 PDF 쪽이다 (위 두 단으로 된 쪽을 글자 층에서 단 순서로 뽑은 쪽). "assurance deficit"라는 낱말은 이 논문에서 찾지 못했다.

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| V-085 | 2 | 확증 편향 (confirmation bias)은 assurance case를 쓸 때 자연스러운 우려라고 적는다. 사례를 만드는 쪽이 시스템을 지지하는 사례를 짓고 있기 때문이다. 유능한 외부 검토자가 좋은 방어이지만 보통 주기적으로, 사례를 쓰는 끝 무렵에야 참여한다고 적는다. | "Competent and diligent external reviewers are good defenses against confirmation bias" | B8. |
| V-086 | 2 | 저자들은 assurance 2.0의 혁신이 사례를 쓰는 모든 단계에서 확증 편향을 체계적으로 줄이려는 것이라고 적는다. 과도한 보수로 "만약을 위한" 증거가 장황하게 붙는 일 없이 이를 하겠다고 적는다. | "systematic mitigations against confirmation bias at every step" | B8. |
| V-087 | 2 | 믿음이 정당하려면 확인된 모든 의심과 반론이 처리되고 결론을 바꿀 만한 믿을 만한 의심이 남지 않아야 한다 (indefeasibility). 잔여 의심은 늘 있으나, 우리가 알고, 검토하고, 의식적으로 결정했을 때 사례가 반박 불가능해진다고 적는다. 모르는 의심이 있거나, 알고도 처리하지 않은 의심이 있으면 이 성질을 잃는다. | "no credible doubts remain that would change the conclusion" | B8. |
| V-088 | 2 | 의심과 반론은 defeater로 나타나므로, 이 기준을 적용하려면 논증의 defeater를 포괄적으로 찾아야 한다. defeater를 찾으면 그것이 defeater가 아님을 보이거나 시스템이나 사례를 고쳐 없애야 한다. | "the search for defeaters" | B8. |
| V-089 | 3 | 잘 짜인 assurance case가 반박되는 (defeated) 길은 둘이라고 적는다. 하나는 증거가 필요한 확신을 정당화하기에 부족한 것 (undercutting defeat, 증거가 모자라거나 주장과의 관계에 간극이나 결함이 있는 경우)이고, 다른 하나는 주장에 모순되는 증거 (rebutting defeater)다. assurance case의 defeater는 중요 시스템의 hazard와 같고, hazard 탐색이 안전 공학의 핵심이듯 defeater 탐색이 assurance case 평가의 핵심이라고 적는다. | "Defeaters for an assurance case are rather like hazards for a critical system" | B8. |
| V-090 | 1 | 저자들은 논증의 단계가 "가능한 한 연역적이고 꼭 필요한 만큼만 귀납적"이어야 한다고 제안한다. 연역적 단계는 의심이 숨을 곳을 없애 약한 곳을 드러내고, 연역할 수 없는 곳은 간극으로 인정해 특별히 주목해야 한다고 적는다. | "as deductive as possible and inductive only as strictly necessary" | B8. 저자의 제안이다. |

## 16. Graydon과 Holloway (P. J. Graydon, C. M. Holloway, An Investigation of Proposed Techniques for Quantifying Confidence in Assurance Arguments, NASA/TM-2016-219195, 2016-05. https://ntrs.nasa.gov/api/citations/20160006526/downloads/20160006526.pdf, 종류: 발행 기관 (NASA Langley의 기술 메모))

"쪽" 칸은 PDF 쪽이다 (96쪽). 이 메모의 주제는 assurance argument의 신뢰를 숫자로 계산하는 제안들을 평가하는 것이다.

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| V-091 | 5 | 초록은 제안된 어떤 기법도 안전 실무자가 쓸 때 믿을 만한 결과를 낸다는 증거가 거의 없고, 제안자들은 통제 실험이나 이력 연구 대신 그럴듯한 결과가 나오는 한 예로 효과를 보인다고 적는다. 일부 경우에 기법이 비현실적인 결과를 낼 수 있음을 보이고, 정량적 신뢰 기법은 중요한 시스템의 출시를 정당화하는 근거로 권하기 전에 더 검증해야 한다고 결론짓는다. | "quantitative confidence techniques require further validation" | B8. |
| V-092 | 18 | 검토한 기법 중 하나의 논문이 평가자에게 증거가 충분한지와 불충분한지를 모두 물으면 확증 편향을 상쇄한다고 가설을 세운다고 적는다. 메모는 이를 제안자의 주장으로 보고하며 효과가 입증되었다고 하지 않는다. | "counteract confirmation bias" | B8. 원문의 "will counteract confirmation bias"는 인용한 논문의 가설이다. |

## 17. Synopsys 백서 (S. Chonnad, V. Litovtchenko, V. Sargsyan, The Role of Confirmation Measures in ISO 26262 Functional Safety Automotive Products, Synopsys, 연도 불명. https://www.synopsys.com/content/dam/synopsys/automotive/white-papers/automotive-iso26262-confirmation-measures.pdf, 종류: 회사의 설명 글 (EDA와 IP 회사의 백서))

(2차 자료) 반도체와 IP 개발의 맥락에서 쓴 글이다. 기준 판은 문서에 적혀 있지 않다. 글이 인용하는 조항 번호 (6.4.9 - 6.4.12 등)는 ISO 26262:2018의 번호로 보이나 원문으로 확인하지 않았고, 책에는 쓰지 않는다 (RULES.md 5.3절). "쪽" 칸은 PDF 쪽이다. 다른 회사의 같은 주제의 글은 절 18.

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| V-093 | 2 | confirmation measures는 confirmation review, functional safety audit, functional safety assessment를 포함한다. 적용되는 ASIL에 따라 자원, 관리, 출시 권한에서 충분히 독립적으로 수행한다고 적는다. | "independence regarding resources, management, and release authority" | B9. 같은 내용: 절 18 (ZVEI). |
| V-094 | 2 | 독립성의 수준은 safety plan에 ASIL에 따라 정한다. confirmation measure의 일정은 safety manager가 잡고, 세부는 그 measure를 맡은 담당자가 계획한다고 적는다. | "specified in the safety plan based on the ASIL" | B9. |
| V-095 | 2 | confirmation review의 대상은 safety plan, technical safety concept, 안전 분석 (DFA, FMEDA 등), safety case 같은 특정 work product다. 검토자는 work product의 정확성, 완전성, 일관성, 적절성, 내용을 해당 요구와 견주고, 결과로 검토 보고서를 낸다고 적는다. | "confirmation reviews are performed for specific work products" | B9. 같은 내용: 절 18의 confirmation review 대상. |
| V-096 | 3 | functional safety audit은 안전에 필요한 process가 실제로 구현되었는지, 조직이 자기 정책과 process를 따르는지를 검토하는 것이다. safety case의 confirmation review는 safety case의 논증이 충분히 설득력이 있는지를 판단한다고 적는다. | "evaluates the argument provided in the safety case" | B9. 같은 내용: 절 18. |
| V-097 | 3 | functional safety assessment (FSA)는 item이 기능 안전을 달성했는지를 판단하는 것이다. 공급자의 FSA는 범위가 제한되며 다음 통합 수준의 FSA의 입력이 된다. 최종 고객인 vehicle manufacturer가 사람을 지정해 전체 FSA를 하고, 판단에는 수용, 조건부 수용, 거부의 권고가 들어간다고 적는다. | "recommendation for acceptance, conditional acceptance, or rejection" | B9. 같은 내용: 절 18 (assessor는 수용을 권고). |
| V-098 | 3 | 이 글의 "독립"은 조직의 독립을 뜻한다. ASIL에 따라 work product를 만든 사람과 다른 사람이, 같은 직속 상사에게 보고하지 않거나 같은 부서가 아닌 사람이 수행해야 한다고 예를 든다. | "not reporting to the same direct supervisor or from the same department" | B9. ASIL별 독립 수준 (I0 - I3)의 표는 이 글에 없다. |

## 18. ZVEI 지침 (ZVEI (독일 전기전자 산업 협회), Best Practice Guideline: Software for Safety-Related Automotive Systems, 2020-12. https://www.zvei.org/fileadmin/user_upload/Presse_und_Medien/Publikationen/2020/Dezember/Best_Practice_Guideline_Software_for_Safety-Related_Automotive_Systems/Best-Practice-Guideline-Software-for-Safety-Related-Automotive-Systems.pdf, 종류: 회사의 설명 글 (업계 협회의 지침. 규격 본문이 아니다))

(2차 자료) 기준 판은 문서의 본문에서 확인하지 못했으나 2018판에 대한 지침으로 보인다. 이 환경의 내려받기는 처음에 429 (요청 과다)를 돌려주었고, WebFetch 도구가 저장한 PDF 사본으로 읽었다. "쪽" 칸은 PDF 쪽이다 (문서 안의 쪽 번호 6, 7과 같다). 단이 둘이라 글자 층의 순서가 섞여 있어 인용을 단 순서로 뽑은 글자와 대조했다.

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| V-099 | 6 | ISO 26262는 안전 필수 자동차의 인정된 규격이지만 조화 규격 (harmonized standard)이 아니고 EU나 UNECE의 지침이나 규정이 아니어서 차량의 형식 승인의 전제 조건이 아니라고 적는다. 그럼에도 계약이나 제조물 책임 때문에 준수가 필요하다고 이 지침은 논한다. | "no prerequisite for vehicle homologation" | B9, B11. 지침의 서술이다. B11의 규제 쪽 문서 (절 21, 절 23)에서 safety case를 요구하는 것은 ISO 26262가 아니라 형식 승인 쪽의 규정이다. |
| V-100 | 6 | 준수 여부를 세 단계로 본다. 검토자 (reviewer)는 보통 저자가 아닌 프로젝트 구성원이고, 감사자 (auditor)는 기능 안전 자격을 가진 품질 부서 사람이며, 마지막으로 안전 평가자 (safety assessor)가 안전 계획, process, 조치, 목표, safety case를 보고 기능 안전이 달성되었는지 판단한다. 평가자는 보통 audit과 검토의 결과에 기댄다. | "typically project members other than the author" | B9. 같은 내용: 절 17. |
| V-101 | 6 | 안전 평가자는 개발팀으로부터 ASIL에 따라 정해지는 충분한 독립성이 있어야 한다. 평가자의 자격 제도가 없고 업계는 평가자의 경험과 평판에 의존하며, 평가 회사의 인증 제도도 OEM이 기대하지 않는다고 적는다. 평가자를 프로젝트 초기에 참여시키는 것을 모범 사례로 든다. | "no assessor qualification scheme" | B9. |
| V-102 | 6 | 준수의 결정은 확신을 뒷받침하는 증거에 기반하며 "말로 하는 진술은 충분하지 않다"고 적는다. 받아들여진 safety case와, 높은 ASIL에서는 독립성이 ASIL로 등급화된 functional safety assessment에 기댄다. 이 assessment는 confirmation review와 functional safety audit을 포함해야 한다고 적는다. | "Verbal statements are not enough" | B9. 같은 내용: 절 17. |
| V-103 | 7 | 평가자는 기능 안전이 달성되었다고 확신할 때만 제품 개발의 수용을 권고한다. 규격의 목표가 모두 충족되었다는 확신을 주려면 safety case에 명확하고 이해할 수 있고 설득력 있는 논증의 사슬을 문서화하라고 한다. | "clear, understandable and convincing chain of argumentation" | B9. 이 지침의 권고다. |

## 19. Koopman (P. Koopman, UL 4600: What to Include in an Autonomous Vehicle Safety Case, IEEE Computer, 2023-05, 쪽 101 - 104. https://users.ece.cmu.edu/~koopman/pubs/Koopman2023_UL4600_Safety_Case.pdf, 종류: 논문 (UL 4600의 주 저자가 자기 대학 사이트에 공개한 논문))

UL 4600의 저자가 규격을 소개한 글이다. 규격 본문이 아니며 저자의 관점이 들어 있다. UL 4600의 판은 글에서 2020-04 발행이라고만 적고 어느 판을 설명하는지 밝히지 않는다. "쪽" 칸은 PDF 쪽이며, 잡지의 인쇄 쪽은 PDF 쪽에 100을 더한 값이다 (PDF 1쪽 = 인쇄 101쪽).

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| V-104 | 3 | UL 4600은 AV 자체를 어떻게 만드는지나 공학 방법론을 표준화하지 않고, 특정 AV에서 안전이 왜 수용 가능한지의 설명이 포괄적이고 일관되고 설득력 있도록 하는 방법을 표준화한다고 적는다. | "is comprehensive, consistent, and compelling" | B10. 인쇄 쪽 103. 같은 내용: 절 20. |
| V-105 | 3 | UL 4600의 중심은 "instrumented safety case"이며, safety case는 AV가 배치되기에 충분히 안전한 이유를 증거로 뒷받침해 추론한 논증이다. safety case가 답해야 할 질문 (예: 확인된 모든 hazard가 완화되었다는 증거가 있는가)과 논증의 타당성에 대한 위협 (예: 설계팀이 고려해야 할 hazard를 빠뜨리지 않았는가)을 함께 적게 한다. | "A safety case is a reasoned argument, supported by evidence" | B10. 인쇄 쪽 103. |
| V-106 | 3 | safety performance indicator (SPI)는 safety case 안의 어느 주장이든 설계, 시뮬레이션, test, 배치 중에 반증되는지를 감지하는 계측이다. 예로 배치 중의 phantom braking이 논증이 가정한 비율의 두 배로 나타나면 그 지표를 모으고 safety case를 다시 따지라고 한다. | "instrumentation to detect whether any claim within the safety case is falsified" | B10, A6. 인쇄 쪽 103. 현장 감시를 safety case의 주장과 묶는 설계. 같은 내용: 절 20. |
| V-107 | 3 | UL 4600이 safety case의 맥락에서 다루도록 요구하는 주제에는 소프트웨어와 시스템 공학 process, 검증과 validation과 test, 도구와 legacy code의 qualification, lifecycle (제조로의 출시, 공급망, 운용, 폐기), 유지보수, SPI가 있다. 시험 실패와 "뜻밖의 일"마다 corrective action이 촉발되어야 한다고 적는다. | "UL 4600 requires addressing the following high-level topics in the context of the" | B10, A6. 인쇄 쪽 103 - 104 (주제 목록이 쪽 사이에 걸쳐 있다). |
| V-108 | 4 | 규격 적합성의 평가: 팀의 안전 엔지니어가 safety case를 만들고 스스로 평가한 뒤, 독립 평가자가 safety case의 형식과 실질이 좋은지 확인한다. 독립 평가자가 반드시 외부 사람일 필요는 없으나 설계팀과 독립된 arms-length 관계가 있어야 한다고 적는다. | "an independent arms-length relationship with the design team" | B10, B9. 인쇄 쪽 104. 같은 내용: 절 20. |
| V-109 | 2 | UL 4600은 "shall"의 긴 목록 대신, 요구마다 적당한 수의 항을 두고 항마다 "고려하라"는 prompt를 달아 합리적인 엔지니어가 놓치기 쉬운 것을 떠올리게 한다고 설명한다. 해결책을 정하지 않고 올바른 질문을 했는지 확인하게 한다고 적는다. | "The standard does not require" | B10. 인쇄 쪽 102 - 103 (문장이 쪽 사이에 걸쳐 있다). |

## 20. Koopman의 강의 자료 (P. Koopman, Key Ideas: UL 4600 Safety Standard for Autonomous Vehicles, 카네기멜런 대학 ECE 642 강의 L109, 2022-07. https://users.ece.cmu.edu/~koopman/lectures/ece642/L109_UL4600.pdf, 종류: 논문 (저자가 공개한 강의 자료이며 동료 심사를 거친 글이 아니다))

UL 4600의 저자의 슬라이드다. "쪽" 칸은 슬라이드 (PDF 쪽) 번호다. 슬라이드는 UL 4600 version 2 (2022-03-15 발행)를 설명한다고 적는다. 슬라이드의 말은 저자의 요약이며 규격 본문이 아니다.

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| V-110 | 3 | UL 4600은 목표 기반 (goal based)이다. 안전 규격이 보통 "안전을 어떻게 하는지" (process, work product)를 정하는 것과 달리, "safety case가 다뤄야 할 것"을 말하고 특정 공학 방법을 정하지 않으며, 다른 안전 규격을 safety case의 맥락 안에서 쓴다. safety case를 평가하는 방법 (최소 범위, 잘 짜인 safety case의 성질, 객관적 평가 기준)의 표준이라고 적는다. | "Standard for how to assess a safety case" | B10. 같은 내용: 절 19. |
| V-111 | 7 | UL 4600의 safety case 범위를 "안전을 독립적으로 평가하는 데 필요한 모든 것"이라고 적는다. | "Everything needed to independently assess safety" | B10. |
| V-112 | 9 | SPI는 KPI와 같되 안전에 특화한 것이며 "safety case의 타당성"에 대한 지표를 준다. 안전 관련 행동의 지표, safety case 안의 가정의 타당성 (예: 차선 표시 끊김을 최대 X 미터까지 견딘다는 가정), 그 밖에 safety case를 확인하는 모든 지표를 든다. | "Provides metrics on safety case validity" | B10, A6. 같은 내용: 절 19. |
| V-113 | 13 | "Other Key Points": 자기 인증 (self-certification)이 허용되고, 내부 평가자가 허용되며 외부 "certificate"의 요구는 없다. "Continuous Maintenance process"가 규격의 갱신을 제공한다고 적는다. | "Internal assessor permitted; no external" | B10, B9. 슬라이드 13. 이 서술은 version 1과 2의 것인지 슬라이드에서 구분하지 않는다. |
| V-114 | 14 | version 2의 평가 용어와 역할: 자기 평가 (self-assessment)에서는 개발팀이 safety case를 점검하고, 독립 평가 (independent assessment)의 범위에는 safety case의 독립적인 기술적 실질이 들어간다고 적는다. | "Independent assessment" | B10, B9. 슬라이드 14. 같은 내용: 절 19. |

## 21. 영국 교통부 (Department for Transport, Automated vehicles: statement of safety principles consultation, 2026-06-17 발행. https://www.gov.uk/government/consultations/automated-vehicles-statement-of-safety-principles/automated-vehicles-statement-of-safety-principles-consultation, 종류: 발행 기관 (영국 정부의 의견 수렴 문서))

영국 Automated Vehicles Act 2024에 따른 안전 원칙 선언 (statement of safety principles, SoSP)의 초안과 의견 수렴 문서다. 문서가 UNECE의 ADS 규정 (자율 주행 시스템 규정)을 서술하는 부분이 근거이며, 그 규정은 "if adopted"로 적혀 있어 채택 전 초안일 수 있다. 읽은 날 (2026-11-23)에 의견 수렴은 2026-09-09에 마감된 상태다. "쪽" 칸은 웹 쪽의 소제목이다. 직접 내려받아 대조했다.

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| V-115 | The UNECE automated driving systems (ADS) regulation | UNECE의 ADS 규정은 형식 승인에서 차량의 기능뿐 아니라 제조사의 안전 process와 문화를 더 넓게 본다고 적는다. 조직 수준의 의무로 (1) 현장 감시와 보고를 포함한 safety management system, (2) 시험 방법 (시뮬레이션, 트랙, 실도로)의 평가, (3) claims, arguments, evidence를 갖춘 구조화된 safety case를 든다. | "a structured safety case with claims, arguments and evidence" | B11, A6. 영국 정부의 서술이며 UNECE 규정의 본문은 읽지 못했다. 같은 내용: 절 22 (같은 부처의 이전 문서). |
| V-116 | The UNECE automated driving systems (ADS) regulation | 이 조치들은 ADS가 "unreasonable risk가 없음"을 보이는 것을 목표로 하며, 규정이 채택되면 2027년 초에 시행될 것으로 기대한다고 적는다. | "If adopted, the ADS regulation is expected to come into force in early 2027." | B11. |
| V-117 | The UNECE automated driving systems (ADS) regulation | 규정은 ADS가 유능하고 조심스러운 인간 운전자와 적어도 같은 수준의 안전을 내야 한다는 일반 개념을 담는다고 적는다. | "at least equivalent to that of a competent and careful human driver" | B11. 영국 정부가 인용한 규정의 한 문장이다. 이 문서에서 직접 읽은 것은 인용문뿐이다. |
| V-118 | The purpose of the SoSP | 초안 SoSP의 목적에 대한 의견 수렴에서 일부 응답자는 안전 원칙의 범위를 공급망과 소프트웨어 갱신 요구 같은 지속적 안전으로 넓히자고 제안했다고 적는다. 정부는 많은 쟁점을 SoSP보다 안전 체계의 다른 부분에서 다루는 것이 낫다고 본다고 적는다. | "such as requiring software updates" | B11, A1. 정부의 입장은 SoSP에서 갱신을 다루지 않는다는 쪽이다. |

## 22. 영국 교통부 (Department for Transport, Automated vehicles: statement of safety principles, call for evidence, 2025-06-10 - 2025-09-01. https://www.gov.uk/government/calls-for-evidence/automated-vehicles-statement-of-safety-principles/automated-vehicles-statement-of-safety-principles, 종류: 발행 기관 (영국 정부의 의견 수집 문서))

위 문서의 앞 단계 문서다 (쪽 아래에 "Updated 17 June 2026"이 있어 닫힌 뒤의 갱신본이다). "쪽" 칸은 소제목이다. 직접 내려받아 대조했다.

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| V-119 | Using the statement of safety principles during pre-deployment | 형식 승인과 authorisation에서의 안전 평가를 뒷받침하려고 제조사가 safety case를 제시하게 된다고 적는다. 형식 승인되는 자동 주행 차량에서는 safety case가 ADS에 "unreasonable risk가 없음"을 보이는 증거를 담을 것으로 기대한다. | "the manufacturer will outline their safety case" | B11. |
| V-120 | Definition of a safety case | 이 문서는 safety case를 "ADS가 규정의 요구를 어떻게 만족하고 unreasonable risk가 없는지의 추론을 적은 문서"로 정의하고, 제조사가 ADS가 안전하다고 보는 근거의 증거 기반을 적는다고 한다. 의도한 사용, 안전을 확인한 시험, 시스템의 안전을 수명 동안 유지할 process의 설명을 담을 수 있다고 적는다. | "A safety case is the documentation that sets out the reasoning for how" | B11. 정의는 이 문서의 것이며 UL 4600의 정의 (절 19)와 말이 다르다. |
| V-121 | Post-deployment | 배치 뒤의 in-use 규제 기관은 차량이 authorisation의 조건을 계속 지키는지 보고, 차량이 안전하고 합법적으로 달리지 않음을 보이는 사고를 식별하고 조사한다고 적는다. 한 차량의 사건이나 한 ADS 기능을 쓰는 차량군의 반복된 위반이 대상이 될 수 있다고 적는다. | "identify and investigate incidents that indicate a vehicle may not be driving safely" | B11, A6. 제조사의 현장 감시가 아니라 규제 기관의 감시를 서술한다. |

## 23. 영국 정부의 ALKS 평가 (Department for Transport 등, Annex B: Revised monitoring and control tests and assessment of ALKS against those tests, 2021-01. https://assets.publishing.service.gov.uk/media/60804515e90e076ab07a6cec/annex-b-revised-monitoring-and-control-tests-and-assessment-of-alks-against-those-tests.pdf, 종류: 발행 기관 (영국 정부 문서가 UN Regulation No. 157 (ALKS)의 채택된 본문을 인용))

UN R157 (자동 차선 유지 시스템)의 규정 본문을 영국 정부가 법적 검토를 위해 인용한 표다 ("Paragraph numbers relate to the paragraph in the ALKS adopted text"). 규정 자체 (unece.org)는 접근 거부로 읽지 못했다. 이 인용은 2021-01의 채택본이며 이후의 개정을 반영하지 않을 수 있다. 읽은 범위에서 "safety case"라는 낱말은 이 문서에 없다. "쪽" 칸은 PDF 쪽이다 (글자 층을 단 순서로 뽑은 쪽).

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| V-122 | 1 | R157의 부록 항 3.5.1은 시스템의 소프트웨어와 하드웨어에 대해 제조사가 형식 승인 당국에 safety management system으로, 안전과 지속적 적합성을 lifecycle 전체 (설계, 개발, 생산, 운용, 폐기)에 걸쳐 관리하는 효과적인 process, 방법론, 도구가 마련되고 최신이며 지켜지고 있음을 보여야 한다고 정한다 (영국 정부의 인용). | "effective processes, methodologies and tools are in place" | B11, A6. 같은 내용: 절 21 (ADS 규정의 safety management system). 인용의 항 번호는 책에 쓰지 않는다. |
| V-123 | 1 | 형식 승인의 증거 방법으로 안전 문서 audit (Annex 4), 제조사의 선언, 실도로 시연 주행 (Annex 5)을 나열한다. | "Audit of safety documentation" | B11. 인용된 R157의 구조에 대한 영국 정부의 표. |
| V-124 | 2 | R157의 Annex 4는 "unreasonable risk"를 수동으로 능숙하게 조심스럽게 운전한 차량에 견줘 운전자와 탑승자와 다른 도로 이용자의 전체 위험 수준이 높아진 것으로 정의한다고 인용한다. | "means the overall level of risk for the" | B11. 영국 정부의 인용이다. |

---

## 찾지 못한 것

"발행 기관"은 정부, 표준화 기구, 도구 저자의 공식 문서 또는 저자가 공개한 논문이다. "2차 자료 둘 이상"은 서로 다른 회사나 기관의 설명 글 둘 이상이다. 아래의 "근거의 세기"는 그 주제의 사실이 어느 정도 받쳐지는지를 뜻하며, 어느 것도 ISO 26262나 R156, R157, UL 4600의 원문을 읽은 것이 아니다.

| 주제 | 근거의 세기 | 어디서 | 못 찾은 것과 주의 |
|---|---|---|---|
| A1. UN R156의 요지 | 2차 자료 둘 이상 (발행 기관의 본문은 못 읽음) | 절 1 (V-001 - V-006, 업계 대표의 발표), 절 2 (V-007 - V-012, UL), 절 21 (영국 정부의 한 줄) | 규정 본문 (unece.org)이 접근 거부라 발행 기관의 근거가 없다. 갱신 실패 시 이전 상태로 복구는 두 곳이 일치한다 (V-002, V-009의 "restore" 문장). 갱신 전의 전력 조건, 운전 중 갱신의 제한, 사용자에게 알림은 발표 자료 (절 1) 한 곳뿐이다. 발표자는 이 항목들을 "examples of requirements"라고 적어 전부가 아님을 밝힌다. 규정의 항 번호는 어디서도 얻지 못했다 |
| A2. 갱신 중 전원 차단과 되돌리기의 설계 | 발행 기관 (공식 문서 포함) | 절 3 (V-013 - V-017, NIST), 절 4 (V-018 - V-023, MCUboot), 절 5 (V-024 - V-028, Uptane) | 충분하다. 다만 NIST는 PC platform firmware의 보안 지침이고, MCUboot는 MCU bootloader의 설계 문서이며, Uptane는 보안 표준이다. 셋 다 안전 규격이 아니다. 갱신 중 전원 차단에 정면으로 답하는 것은 NIST의 한 항 (RTU와 CTU)과 MCUboot의 swap 설계이며, Uptane는 읽은 범위에서 이 문제를 다루지 않는다. 자동차 ECU의 flash 갱신에 쓰는 AUTOSAR나 UDS의 설명은 찾지 않았다 |
| A3. 변경 영향 분석과 회귀 test | 발행 기관 (항공과 의료기기) | 절 6 (V-029 - V-032, FAA AC 00-69), 절 7 (V-033 - V-037, FAA AC 20-115D), 절 8 (V-038 - V-043, FDA) | 충분하나 자동차의 것이 아니다. FAA의 Order 8110.49A (2018)를 내려받아 본문에서 "impact analysis"를 찾았으나 한 곳도 없었다 (이 지침이 AC 00-69와 AC 20-115D로 옮겨 간 것으로 보이나 이 기록에서는 확인하지 못했다). 회귀 test에 관한 FAA의 직접 서술은 찾지 못했다. FDA의 서술은 검증과 validation의 성공으로 "새 제출이 필요 없다는 판단"을 확인한다는 것이다 (V-041). ISO 26262의 변경 관리 (Part 8)에 관한 공개 문서는 이번에 찾지 않았다 |
| A4. CI와 agile을 안전 관련 개발과 함께 쓰는 조건 | 논문 둘 (규제 기관의 문서는 없음) | 절 10 (V-048 - V-052, SINTEF 등, IEC 61508), 절 11 (V-053 - V-056, 항공) | 규제 기관이나 표준화 기구의 공개 문서는 찾지 못했다. 두 논문은 조건으로 같은 것을 든다: 문서와 추적성의 지속적 생성, 회귀 test, 평가자의 참여. "continuous integration" 자체를 조건으로 든 문서는 찾지 못했고, Ribeiro 등의 "continuous certification"이 가장 가깝다. 두 논문 모두 저자의 제안과 경험이다. 효과의 검증 (적용 사례)은 읽지 않았다 |
| A5. calibration data와 설정 data (parameter data item) | 발행 기관 (항공, 일부) | 절 7 (V-033 - V-037), 절 6 (CIA의 configuration data), 절 9 (V-044 - V-047, RTCA FAS topic paper) | FAA의 AC는 parameter data item의 process를 FAA가 평가한 것이어야 한다고만 적고 내용을 자세히 설명하지 않는다. 목표 (PDI 파일의 correct and complete, 모든 요소의 verification)의 설명은 RTCA 사용자 그룹의 의견 (FTP1034)이며 공식 지침이 아니라고 문서가 밝힌다. NASA의 문서는 찾지 못했다. 자동차의 calibration data에 관한 공개 문서는 찾지 못했다. 항공의 PDI는 자동차의 calibration data와 같은 개념이 아닐 수 있어 책에서 대응을 단정하지 않는다 |
| A6. 현장의 감시와 recall | 발행 기관 (법령과 사례 하나) | 절 12 (V-057 - V-060, 49 CFR 573), 절 13 (V-061 - V-065, NHTSA 자료실의 recall 보고서), 절 22, 절 21 (영국 정부), 절 19 (SPI) | NHTSA의 recall 제도 설명 쪽과 ODI의 조사 절차 문서는 접근 거부라 읽지 못했다. 규정 본문과 한 사례의 연대기만 읽었다. 소프트웨어 결함 recall의 공개 통계는 찾지 못했다. 사례 하나는 제조사가 쓴 서술이고 제조사는 NHTSA의 분석에 동의하지 않는다고 적었다. 사고 보고서의 "소프트웨어 결함이 원인"이라는 결론의 근거를 이 보고서는 담지 않는다 (원인란이 "NR") |
| B7. Nimrod Review의 safety case 비판 | 발행 기관 | 절 14 (V-066 - V-084) | 충분하다. 쪽과 항 번호를 함께 기록했다. 이 비판은 2009년 영국 군용기의 맥락이며 자동차에 직접 적용되지 않는다. 보고서는 "safety case" 개념 자체를 버리지 않고 이름과 방식을 바꾸라고 권한다 (V-083). "결론을 먼저 정해 놓은 논증"에 해당하는 서술은 22.7(9)와 22.7(11)과 각주 6이다 |
| B8. assurance case의 평가와 약한 곳 | 발행 기관 (저자 공개 논문과 NASA 기술 메모, 논증은 일부) | 절 15 (V-085 - V-090, Bloomfield와 Rushby), 절 16 (V-091 - V-092, NASA) | defeater와 confirmation bias는 절 15가 직접 다룬다. "assurance deficit"라는 낱말은 읽은 문서에 없었다 (Hawkins 등의 논문은 읽지 않았다). SEI의 assurance case 자료는 찾지 않았다. NASA 메모는 평가가 아니라 신뢰를 숫자로 계산하는 제안의 한계를 다룬다. 두 문서는 저자의 의견과 제안이며 규제 지침이 아니다 |
| B9. ISO 26262의 confirmation measure와 독립성 | 2차 자료 둘 이상 | 절 17 (V-093 - V-098, Synopsys), 절 18 (V-099 - V-103, ZVEI 협회), 절 19 (UL 4600의 평가자와 비교) | 발행 기관 (ISO)의 자료는 없다. 두 글은 서로 다른 기관이고 세 가지 measure의 구분, 독립성이 ASIL에 따른다는 점, assessor가 audit과 review의 결과에 기댄다는 점에서 일치한다. 독립성 수준 (I0 - I3)의 표와 ASIL별 요구는 두 글 어디에도 없다. Kugler Maag (kuglermaag.com)의 설명은 인증서가 맞지 않아 읽지 못했다. DNV의 쪽은 읽었으나 독립성의 수준을 서술하지 않아 쓰지 않았다. 판을 확정한 글이 없다 |
| B10. UL 4600의 safety case 요구 | 하나뿐 (저자 한 사람의 자료 둘) | 절 19 (V-104 - V-109), 절 20 (V-110 - V-114) | UL이나 규격 본문의 공개 자료는 읽지 못했다 (UL의 열람 쪽은 로그인이나 약관이 있을 수 있어 시도하지 않았다. ulse.org의 한 주소는 404). 두 자료는 같은 저자의 것이라 서로 독립이 아니다. 책에 쓸 때는 "UL 4600의 저자가 이렇게 설명한다"까지다. 규격의 판 (version 1, 2, 3)에 따른 차이는 슬라이드 13, 14가 version 2에서 평가 용어가 바뀌었다고만 적는다 |
| B11. 자동차 safety case를 요구하거나 권하는 규제 문서 | 발행 기관 (영국 정부의 서술, 규정 본문은 못 읽음) | 절 21 (V-115 - V-118), 절 22 (V-119 - V-121), 절 23 (V-122 - V-124), 절 18 (ISO 26262는 형식 승인의 전제 조건이 아님) | UNECE의 R157 본문 (Annex 4의 audit)과 새 ADS 규정의 본문은 접근 거부로 읽지 못했다. 영국 정부는 새 ADS 규정이 "structured safety case"를 요구한다고 적지만 그 규정은 "if adopted"의 초안이다. R157에 대해서는 영국 정부가 인용한 항이 safety management system의 process audit을 정할 뿐 "safety case"라는 낱말은 읽은 범위에 없다. NHTSA의 자율 주행 지침 (nhtsa.gov)은 접근 거부로 읽지 못했다. EU의 형식 승인 문서 (EUR-Lex)는 사람 확인 화면이 나와 읽지 못했다 |

## 읽지 못한 쪽 (막힌 출처)

- unece.org: UN Regulation 156과 157의 본문 (PDF 둘)과 R156의 해석 문서가 접근 거부 (403)를 돌려주었다. WebFetch 도구도 같았다. 그래서 A1과 B11의 규정 본문을 읽지 못했다. 이 환경의 내려받기가 접근 거부를 받은 곳에서 요청 머리글을 바꿔 다시 시도하는 일은 하지 않았다.
- nhtsa.gov: recall 제도의 설명 쪽, Motor Vehicle Safety Defects and Recalls 안내서 (PDF), ODI 조사 절차 문서, 자율 주행 지침이 접근 거부 (403)를 돌려주었다. static.nhtsa.gov의 recall 보고서는 읽을 수 있었다 (절 13).
- eur-lex.europa.eu: R156과 R157의 EU 공보 사본 (2021/388, 2021/389)이 내용 없는 202 응답을 돌려주었다 (사람 확인 화면으로 보여 우회하지 않았다). WebFetch 도구도 빈 내용을 받았다.
- volpe.dot.gov의 ISO 26262 평가 보고서와 rtca.org의 다른 쪽 (FTP1000, 호스트 azurewebsites)이 접근 거부 (403)를 돌려주었다.
- vehicle-certification-agency.gov.uk (영국 형식 승인 기관)의 쪽은 curl이 403을 받았다. WebFetch 도구는 내용을 돌려주었으나 직접 대조하지 못해 이 기록에 쓰지 않았다.
- kuglermaag.com은 TLS 인증서의 호스트 이름이 맞지 않아 읽지 못했다.
- 이 기록에 쓴 PDF 중 ZVEI (절 18)와 FDA (절 8)와 Zastrow의 발표 (절 1)는 curl이 429 (ZVEI)나 404 (FDA)를 받거나 WebFetch가 글자가 아닌 PDF 내용을 돌려주어, WebFetch 도구가 저장한 PDF 사본을 pdftotext로 읽었다. 글자는 직접 대조했다.
- FAA 문서 (AC 00-69, AC 20-115D, Order 8110.49A)를 내려받을 때 curl 요청에 브라우저 형태의 User-Agent 머리글을 붙였다. 접근 거부를 받은 뒤에 바꾼 것이 아니라 그 사이트의 첫 요청부터였고, 요청은 모두 성공했다. 그 뒤의 요청에는 붙이지 않았다.
- ulse.org (UL Standards and Engagement)의 UL 4600 쪽은 한 주소가 404였고, Rushby의 SRI 논문 한 주소도 404였다. 다른 주소를 더 찾지 않았다.
