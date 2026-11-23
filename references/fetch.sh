#!/bin/sh
# 받을 수 있는 참고 문서 (접근 등급 A)를 references/<id>/ 아래에 받는다.
# 사용법: sh references/fetch.sh
# - 이미 있는 파일은 다시 받지 않는다.
# - 공식 출처 (발행 기관, 저자의 페이지, 정부 기관)의 주소만 쓴다.
# - 받은 파일은 git에 넣지 않는다 (.gitignore).
# 목록과 SHA-256 값은 references/README.md에 있다.

set -u
cd "$(dirname "$0")" || exit 1

ok=0
fail=0

fetch() {
    id=$1
    file=$2
    url=$3
    mkdir -p "$id"
    if [ -s "$id/$file" ]; then
        echo "있음  $id/$file"
        ok=$((ok + 1))
        return 0
    fi
    if curl -fsSL --retry 2 --connect-timeout 20 --max-time 900 -o "$id/$file.part" "$url"; then
        if [ "$(head -c 4 "$id/$file.part")" = "%PDF" ]; then
            mv "$id/$file.part" "$id/$file"
            echo "받음  $id/$file"
            ok=$((ok + 1))
            return 0
        fi
        rm -f "$id/$file.part"
        echo "실패  $id/$file (PDF가 아니다)"
    else
        rm -f "$id/$file.part"
        echo "실패  $id/$file (요청 실패)"
    fi
    fail=$((fail + 1))
    return 1
}

# 사고 사례 (1장)
fetch ariane-501-report esa-x-1819eng.pdf \
    "https://esamultimedia.esa.int/docs/esa-x-1819eng.pdf"
fetch b737max-jatr Final_JATR_Submittal_to_FAA_Oct_2019.pdf \
    "https://www.faa.gov/sites/faa.gov/files/2021-08/Final_JATR_Submittal_to_FAA_Oct_2019.pdf"
fetch b737max-ntsb-asr1901 ASR1901.pdf \
    "https://www.ntsb.gov/investigations/AccidentReports/Reports/ASR1901.pdf"
fetch b737max-knkt-jt610 KNKT.18.10.33.04-Final-Report.pdf \
    "https://knkt.go.id/Repo/Files/Laporan/Penerbangan/2018/KNKT.18.10.33.04-Final-Report.pdf"
fetch b737max-eaib-et302 ET_302__B737-8MAX_ACCIDENT_FINAL_REPORT.pdf \
    "https://bea.aero/fileadmin/user_upload/ET_302__B737-8MAX_ACCIDENT_FINAL_REPORT.pdf"
fetch b737max-ntsb-et302-comments US-comments-ET302-Report-March-2022.pdf \
    "https://www.ntsb.gov/investigations/Documents/US%20comments%20ET302%20Report%20March%202022.pdf"
fetch b737max-ntsb-et302-comments Response-to-EAIB-final-report.pdf \
    "https://www.ntsb.gov/investigations/Documents/Response%20to%20EAIB%20final%20report.pdf"
fetch b737max-house-report 2020.09.15-FINAL-737-MAX-Report.pdf \
    "https://democrats-transportation.house.gov/imo/media/doc/2020.09.15%20FINAL%20737%20MAX%20Report%20for%20Public%20Release.pdf"
fetch koopman-toyota-ua koopman14_toyota_ua_slides.pdf \
    "https://users.ece.cmu.edu/~koopman/pubs/koopman14_toyota_ua_slides.pdf"

# 주요 예제와 같은 주제를 다룬 미국 정부 보고서 (1, 6, 7장)
fetch nhtsa-etc-ev-fsa dot_44158_DS1.pdf \
    "https://rosap.ntl.bts.gov/view/dot/44158/dot_44158_DS1.pdf"
fetch nhtsa-safety-standards-assessment dot_12302_DS1.pdf \
    "https://rosap.ntl.bts.gov/view/dot/12302/dot_12302_DS1.pdf"
fetch nasa-toyota-ua-report INRP-DP14003-61483.pdf \
    "https://static.nhtsa.gov/odi/inv/2014/INRP-DP14003-61483.pdf"

# 개념과 분석 기법 (2, 8, 19장)
fetch avizienis-2004-taxonomy TR_2004-47.pdf \
    "https://drum.lib.umd.edu/bitstreams/ed07fa96-1e50-4309-afdd-43d3d779ac99/download"
fetch stpa-handbook STPA_handbook.pdf \
    "http://psas.scripts.mit.edu/home/get_file.php?name=STPA_handbook.pdf"
fetch gsn-standard-v3 GSN_Community_Standard_v3.pdf \
    "https://scsc.uk/r1386.pdf?ref=1386&stream=1"
fetch iec-61508-overview-slides IEC_61508_and_Functional_Safety_2022.pdf \
    "https://assets.iec.ch/public/acos/IEC%2061508%20&%20Functional%20Safety-2022.pdf?2023040501"

# 소프트웨어 안전과 verification (10-17장)
fetch nasa-gb-8719-13 nasa-gb-8719.13.pdf \
    "https://s3vi.ndc.nasa.gov/ssri-kb/static/resources/nasa-gb-8719.13.pdf"
fetch nasa-mcdc-tutorial 20010057789.pdf \
    "https://ntrs.nasa.gov/api/citations/20010057789/downloads/20010057789.pdf"
fetch misra-compliance-2020 MISRA-Compliance-2020.pdf \
    "https://misra.org.uk/app/uploads/2021/06/MISRA-Compliance-2020.pdf"
fetch autosar-e2e-protocol AUTOSAR_FO_PRS_E2EProtocol.pdf \
    "https://www.autosar.org/fileadmin/standards/R25-11/FO/AUTOSAR_FO_PRS_E2EProtocol.pdf"
fetch autosar-safety-measures AUTOSAR_CP_EXP_FunctionalSafetyMeasures.pdf \
    "https://www.autosar.org/fileadmin/standards/R25-11/CP/AUTOSAR_CP_EXP_FunctionalSafetyMeasures.pdf"
fetch faa-ac-20-115d AC_20-115D.pdf \
    "https://www.faa.gov/documentLibrary/media/Advisory_Circular/AC_20-115D.pdf"
fetch faa-ac-20-193 AC_20-193.pdf \
    "https://www.faa.gov/documentLibrary/media/Advisory_Circular/AC_20-193.pdf"

# 2026-11-22에 더한 문서
fetch nasa-std-8739-8b NASA-STD-8739.8B.pdf \
    "https://standards.nasa.gov/system/files/tmp/NASA-STD-87398%20REV%20B.pdf"
fetch nasa-fault-tree-handbook Fault_Tree_Handbook_with_Aerospace_Applications_2002.pdf \
    "https://extapps.ksc.nasa.gov/reliability/Documents/Fault_Tree_Handbook_with_Aerospace_Applications_August_2002.pdf"
fetch nasa-system-safety-handbook-v1 20120003291.pdf \
    "https://ntrs.nasa.gov/api/citations/20120003291/downloads/20120003291.pdf"
fetch hse-hsg238 hsg238.pdf \
    "https://www.hse.gov.uk/pubns/priced/hsg238.pdf"
fetch nhtsa-etc-gasoline-fsa dot_36888_DS1.pdf \
    "https://rosap.ntl.bts.gov/view/dot/36888/dot_36888_DS1.pdf"
fetch easa-amc-20-193 amc_20-193_use_of_multi-core_processors.pdf \
    "https://easa.europa.eu/sites/default/files/dfu/annex_i_to_ed_decision_2022-001-r_amc_20-193_use_of_multi-core_processors_mcps.pdf"

# 로봇 (20장)
fetch ifa-report-2-2017e rep0217e.pdf \
    "https://www.dguv.de/medien/ifa/en/pub/rep/pdf/reports-2019/report0217e/rep0217e.pdf"

# 드론 (21장)
fetch sora-2-5-main-body SORA-v2.5-Main-Body-Release-JAR_doc_25.pdf \
    "https://www.caa.cz/wp-content/uploads/2024/12/SORA-v2.5-Main-Body-Release-JAR_doc_25.pdf"
fetch easa-ed-2025-018-r-annex annex_to_ed_decision_2025-018-r_1_2.pdf \
    "https://www.easa.europa.eu/sites/default/files/dfu/annex_to_ed_decision_2025-018-r_1_2.pdf"
fetch easa-ear-uas EAR-for-Unmanned-Aircraft-Systems.pdf \
    "https://www.easa.europa.eu/en/downloads/110913/en"
fetch easa-sc-light-uas-medium-risk special_condition_sc_light-uas_medium_risk_01.pdf \
    "https://www.easa.europa.eu/sites/default/files/dfu/special_condition_sc_light-uas_medium_risk_01.pdf"
fetch easa-moc-light-uas-2510 moc_light-uas_2510-01_final.pdf \
    "https://www.easa.europa.eu/en/downloads/139355/en"
fetch easa-moc-light-uas-high-risk-2510 final_moc_light-uas_2510-01_sail_v_and_vi.pdf \
    "https://www.easa.europa.eu/sites/default/files/dfu/final_moc_light-uas_2510-01_sail_v_and_vi.pdf"

echo "받았거나 이미 있음: $ok, 실패: $fail"
