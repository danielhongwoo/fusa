# 15, 16, 17장 웹 근거에서 뽑은 사실 (읽기 기록)

대상: 15장 (verification 전략), 16장 (testing), 17장 (도구와 기존 소프트웨어). 읽은 날: 2026-11-23.

- 받아 둔 문서 (references/)에 없는 주제를 공개 웹 문서에서 찾았다. "쪽" 칸에는 웹 주소를 적는다. PDF이면 주소는 절 머리에 적고 "쪽" 칸에는 PDF 파일의 몇 번째 쪽인지 적는다 (문서에 인쇄된 쪽 번호와 다를 수 있다). HTML이면 "쪽" 칸에 절 이름이나 "본문"으로 적는다.
- 직접 내려받아 글자를 대조한 것과 그렇지 못한 것을 구분한다. 대조하지 못한 것은 해당 절 머리와 "비고"에 적었다 (MathWorks 문서는 이 환경의 내려받기가 접근 거부되어 WebFetch 도구가 돌려준 문장만 있다).
- "원문의 짧은 인용"은 해당 쪽의 글자 그대로다 (열다섯 낱말 안쪽). PDF에서 뽑은 지수 (10의 몇 제곱)는 글자 추출에서 "109"처럼 보일 수 있어 비고에 적었다.
- 규격의 요구에 관한 사실은 "그 문서가 그렇게 설명한다"까지다. 규격 원문은 읽지 않았다. 회사의 글은 (2차 자료)이며, 책에 쓸 때 RULES.md 5.2절에 따라 서로 다른 회사나 기관의 것 둘 이상으로 확인한다. 비고에 같은 내용을 말하는 다른 절의 번호를 적었다.
- 규격의 판: Synopsys (2017)는 ISO 26262:2011 기준, Siemens (2022)는 ISO 26262:2018 기준이다. MathWorks와 TUV SUD의 논문 (2010경)은 ISO/DIS 26262 (2009 초안) 기준이다. 조항 번호는 이 글들이 적은 것을 비고에 옮겼으나, RULES.md 5.3절에 따라 책에는 쓰지 않는다 (원문으로 확인하지 못했다).
- 원고에 쓰기 전에 그 쪽을 직접 열어 확인한다 (RULES.md 5.2절).

## 1. Butler와 Finelli (R. W. Butler, G. B. Finelli, The Infeasibility of Quantifying the Reliability of Life-Critical Real-Time Software, IEEE Trans. Software Eng. 19(1), 1993. NASA Langley의 공개본: https://ntrs.nasa.gov/api/citations/20040139817/downloads/20040139817.pdf, 종류: 발행 기관 (NASA NTRS의 공개본. 쪽은 PDF 19쪽 중 몇 번째))

NTRS 공개본의 표지는 NASA Langley 소속과 제목만 적고, 학술지 판의 쪽 배치와 다를 수 있다. 내용 대조는 이 공개본으로만 했다.

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| W-001 | 1 | 초록은 통계 방법으로 life-critical 소프트웨어의 신뢰도를 정량화하는 것이 불가능하다고 확언한다. 표준 소프트웨어에도 fault-tolerant 소프트웨어에도 해당한다고 적는다. | "quantification of life-critical software reliability is infeasible" | B10 |
| W-002 | 1 | 고전적인 신뢰도 추정 방법을 life-critical 소프트웨어에 쓰면 터무니없이 많은 testing이 필요하다고 보인다. reliability growth model도 과도한 testing의 필요를 없애지 못한다고 초록이 적는다. | "exhorbitant amounts of testing" | B10. 원문의 철자 (exorbitant의 오기)를 그대로 옮겼다 |
| W-003 | 2 | 지금까지 초고신뢰도 요구는 1 - 10시간 임무에서 고장 확률 10의 -7제곱에서 -9제곱 정도로 옮겨져 왔다고 적는다. 같은 쪽의 용어표는 ultrareliability를 시간당 고장률 10의 -7제곱 미만으로, moderate reliability를 10의 -3제곱에서 -7제곱으로 정한다. | "ultrahigh reliability requirement has been translated into a probability of failure" | B10 |
| W-004 | 3 | 1시간 이상의 임무에서 고장 확률 10의 -7제곱에서 -9제곱을 노리는 시스템에는 life testing이 현실적이지 않다고 적는다. | "life testing is prohibitively impractical" | B10 |
| W-005 | 4 | 10시간 임무에서 고장 확률 10의 -9제곱인 시스템은 평균 고장 시간이 약 10의 10제곱 시간이다. 시험체 1개로 고장을 한 번 볼 때까지의 기대 시험 기간은 1141550년, 10개는 114155년, 10000개는 114년이다 (Table 1). 저자는 시험체를 10개 넘게 쓰기 어렵다는 경제성까지 들어 life testing은 초고신뢰 시스템에 해당 없다고 결론짓는다. | "life-testing is clearly out of the question" | B10. Table 1의 조건은 r=1 (고장 한 번)이며, 통계적 유의성을 얻으려면 더 많은 시험이 필요하다고 같은 쪽이 적는다. 인용 뒤에 "for ultrareliable systems"가 이어진다 |
| W-006 | 13 | 고장 확률을 입력당 10의 -12제곱 미만으로 보여야 하는 경우를 두고, 그 수준까지 testing하는 것은 불가능하고 적은 양의 testing에서 외삽하는 것은 위험하다고 적는다. | "extrapolation from feasible amounts of testing is dangerous" | B10 |
| W-007 | 15 | 시간당 고장률 10의 -8제곱을 정량화하려면 10의 8제곱 시간을 넘는 testing이 필요하다고 적는다. 그래서 fault-tolerant 소프트웨어의 신뢰도 model이 나왔다고 설명한다. | "life-testing of ultrareliable software is infeasible" | B10. 지수가 글자 추출에서 "108"로 보인다 |

## 2. Littlewood와 Strigini (B. Littlewood, L. Strigini, Validation of Ultrahigh Dependability for Software-Based Systems, Communications of the ACM 36(11), 1993. https://openaccess.city.ac.uk/id/eprint/1251/1/CACMnov93.pdf, 종류: 논문 (저자 소속 대학의 공개본))

공개본의 첫 쪽은 City 대학의 안내문이고 본문은 2쪽부터다. 쪽은 PDF 쪽이다.

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| W-008 | 2 | 초록은 복잡한 소프트웨어에 의존하는 시스템의 초고신뢰성을 확인하는 방법이 현재는 없다고 결론짓는다. 여러 증거를 합치면 확인 가능한 수준이 오르지만 문제를 풀 만큼은 아니라고 적는다. | "no solution exists, at present, for the validation of ultra-high dependability" | B10. W-001과 같은 취지의 독립 출처 |
| W-009 | 7 | 소프트웨어가 1000시간 동안 고장 없이 시험되었다고 하자. 이것이 운영 시험만으로 얻을 수 있는 가장 좋은 소식인데, 그 뒤의 성능과 safety-critical 용도의 적합성을 얼마나 확신할 수 있는가를 묻고 분석한다. | "tested without failure (the 'best news' it is possible to obtain" | B10 |
| W-010 | 8 | 고장 없이 시험한 기간 t0가 지났을 때 다음 고장까지 t0보다 오래 기다릴 확률이 1/2이다. 사전 믿음 없이 사후 중앙값 고장 시간을 10의 9제곱 시간으로 하려면 고장 없는 10의 9제곱 시간이 필요하다고 적는다. | "we would need to see 109 hours of failure-free working" | B10. 지수가 글자 추출에서 "109"로 보인다. 같은 쪽이 사전 분포와 관측 증거가 신뢰의 두 원천이라고 적는다 |

## 3. Yang 등 (X. Yang, Y. Chen, E. Eide, J. Regehr, Finding and Understanding Bugs in C Compilers, PLDI 2011. https://www-old.cs.utah.edu/~regehr/papers/pldi11-preprint.pdf, 종류: 논문 (저자의 대학 쪽에 공개한 preprint))

preprint의 쪽은 PDF 쪽이다.

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| W-011 | 1 | 저자들은 Csmith라는 무작위 test program 생성기를 3년 동안 써서 compiler 개발자에게 이전에 알려지지 않은 결함을 325개 넘게 보고했다. | "more than 325" | A6. 인용 뒤에 "previously unknown bugs"가 이어진다 |
| W-012 | 1 | 시험한 모든 compiler가 비정상 종료했고, 올바른 입력에 대해 조용히 틀린 code를 만들기도 했다고 적는다. | "silently generate wrong code" | A6 |
| W-013 | 1 | 방법은 differential testing이다. 생성한 C program을 여러 compiler로 번역해 실행하고 출력을 견주며, 입력 program은 191가지 정의되지 않은 동작을 하나도 실행해서는 안 된다고 적는다. | "must not execute any of the 191 kinds of undefined behavior" | A6. 원 문장은 이 인용 앞에 "program ... "이 붙고 뒤에 ", nor ..."가 이어진다 |
| W-014 | 1 | 보고한 GCC 결함 가운데 25개가 GCC가 가장 높은 우선순위 (release 차단) P1으로 분류했다. | "P1, the maximum" | A6. 앞 문장에서 숫자 25를 확인했다 |
| W-015 | 1 | 저자는 optimizing compiler의 번역 오류 (miscompilation)가 최적화의 안전 검사 부족, 부정확한 정적 분석, 잘못된 변환에서 생긴다고 설명한다. | "Miscompilations often happen because optimization safety checks are inadequate" | A6 |
| W-016 | 2 | 검증된 compiler인 CompCert에서도 증명되지 않은 부분에서 이전에 알려지지 않은 결함을 찾았다. 이 결함은 compiler가 틀린 code를 조용히 만들게 한다. | "unproved parts of CompCert" | A6. 17장에서 "검증된 compiler도 증명 범위 밖에는 결함이 있었다"의 근거 |
| W-017 | 6 | 최근판 CompCert (2011년 초 개발판)는 Csmith가 wrong-code 오류를 찾지 못한 유일한 compiler라고 적는다. 저자들은 약 6 CPU-year를 들여 시도했다. 같은 쪽에서 CompCert 1.6 for PowerPC의 한 예 (부호 있는 비교)를 들며, 이 결함과 비슷한 5개가 검증되지 않은 front-end code에 있었다고 적는다. | "the only compiler we have tested for which Csmith cannot find wrong-code errors" | A6. 원문은 "is the only compiler ..."로 시작한다. 이 문장은 2011년 초의 개발판에 대한 서술이다 |

## 4. Wang 등 (X. Wang, N. Zeldovich, M. F. Kaashoek, A. Solar-Lezama, Towards Optimization-Safe Systems: Analyzing the Impact of Undefined Behavior, SOSP 2013. https://pdos.csail.mit.edu/papers/stack%3Asosp13.pdf, 종류: 논문 (저자 연구실의 공개본))

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| W-018 | 1 | 이 논문은 정의되지 않은 동작 때문에 compiler 최적화가 뜻밖에 지워 버리는 code를 "optimization-unstable code"라 부르고 연구한다. 이런 code가 Linux kernel과 Postgres database에도 있고, 결과가 잘못된 동작에서 빠진 보안 검사까지 이른다고 초록이 적는다. | "unexpectedly discarded by compiler optimizations" | A6 |
| W-019 | 1 | 저자들이 만든 정적 검사기 Stack을 널리 쓰이는 시스템에 적용해 개발자가 확인하고 고친 새 결함 160개를 찾았다. | "uncovered 160 new bugs" | A6. 이어서 확장판 (TOCS)은 161개로 적는다고 검색 결과가 알렸으나 그 논문은 이 기록에서 읽지 않았다 |
| W-020 | 1 | Debian Wheezy의 C/C++ package 8,575개 가운데 40%에 unstable code가 있다고 추정한다. 또한 compiler가 정의되지 않은 동작을 최적화에 점점 더 활용한다고 적는다. | "exists in 40% of the 8,575 Debian Wheezy packages" | A6. 원문의 인용 앞에 "We estimate that unstable code"가 있다. "추정"임에 주의 |
| W-021 | 1 | Figure 1: 포인터에 길이를 더해 넘침을 검사하는 흔한 code (buf + len < buf)에서 gcc가 두 번째 if를 최적화로 없애 취약해진다. | "gcc optimizes away the second if statement" | A6. 원문은 이 code를 여러 code base에서 발견했다고 적는다 |
| W-022 | 2 | Figure 2: Linux kernel의 CVE-2009-1897에서, 포인터 tun을 역참조한 뒤에 null 검사를 하는 순서여서 gcc가 null 검사를 없애고 공격할 수 있게 되었다. | "gcc optimizes away the null pointer check" | A6. 원문의 CVE 표기는 "CVE-20091897"로 글자가 이어져 있다 |

## 5. Jia와 Harman (Y. Jia, M. Harman, An Analysis and Survey of the Development of Mutation Testing, IEEE Trans. Software Eng., 2011 판의 저자 공개본. https://web.eecs.umich.edu/~weimerw/2020-481F/readings/mutation-testing.pdf, 종류: 논문 (대학 강의 자료로 공개된 survey 본문))

이 복사본은 TSE 서식의 31쪽이다. 학술지의 호와 쪽은 이 복사본에 적혀 있지 않았다. 원 출판 연도는 이 기록에서 확인하지 못했다 (참고 문헌에 2009년 TSE 논문이 있다. survey 자체는 2011년 판으로 알려져 있으나 이 복사본의 글자로는 확인하지 못했다).

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| W-023 | 1 | mutation testing은 fault-based testing 기법이며, "mutation adequacy score"라는 검사 기준을 준다. 이 점수로 test 집합이 결함을 얼마나 잘 찾아내는지를 잴 수 있다. | "fault-based testing technique" | B9 |
| W-024 | 3 | mutation testing은 두 가설에 기댄다. competent programmer hypothesis (DeMillo 등 1978이 처음 제안)는 프로그래머가 올바른 판에 가까운 program을 짠다고 가정한다. coupling effect는 단순한 결함을 모두 찾는 test가 복잡한 결함도 높은 비율로 찾는다는 가설이다 (Offutt의 서술을 인용). | "complex faults are coupled to simple faults" | B9. 가설이므로 책에서도 "가설"로 쓴다. 고전 원문 (DeMillo 등 1978)은 직접 읽지 않았고 이 survey의 설명이다 |
| W-025 | 4 | 어떤 mutant는 원래 program과 항상 같은 출력을 내므로 죽일 수 없다. 이것을 equivalent mutant라 한다. 구문은 다르지만 기능은 같다. | "syntactically different but functionally equivalent" | B9 |
| W-026 | 4 | 모든 equivalent mutant를 자동으로 찾는 것은 program의 동치 판정이 결정 불가능하기 때문에 불가능하다. 이 문제가 mutation testing의 널리 쓰임을 막는 장벽이라고 적는다. | "program equivalence is undecidable" | B9. 8쪽에서 Budd와 Angluin의 증명을 근거로 든다. 이 survey의 설명이며 원 논문은 읽지 않았다 |
| W-027 | 4 | mutation score는 죽인 mutant의 수를 equivalent가 아닌 mutant의 총수로 나눈 비율이다. 목표는 점수를 1로 올리는 것이다. | "total number of non-equivalent mutants" | B9. 앞 구절은 "killed mutants over the" |

## 6. CBMC 논문 (D. Kroening, P. Schrammel, M. Tautschnig, CBMC: The C Bounded Model Checker, arXiv:2302.02384, 2023. https://arxiv.org/pdf/2302.02384, 종류: 논문 (도구 저자의 공개본))

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| W-028 | 1 | CBMC는 C program에서 assertion의 위반을 보이거나, 주어진 한계 (bound) 안에서 assertion이 안전함을 증명한다. 주석을 단 C program을 bit 단위로 정확하게 formula로 옮기며, 반복문은 주어진 깊이까지 펼친다. formula가 만족 가능하면 assertion을 위반하는 실행이 있다. | "proves safety of the assertions under a given bound" | C12. 같은 내용: W-030 |
| W-029 | 7 | --unwinding-assertions를 주면 CBMC가 펼친 횟수가 충분한지도 검사한다. 이것은 실행 횟수의 한계를 증명하는 것이다. 더 작은 한계에서는 반복이 더 가능함을 보이는 실행이 있으므로 CBMC가 unwinding assertion이 실패했다고 보고한다. | "checks that sufficient unwinding is done" | C12 |
| W-030 | 8 | unwinding assertion이 없으면, 또는 --depth 옵션을 쓰면 CBMC는 program이 옳음을 꼭 증명하지는 않는다. 그래도 결함을 찾는 데는 도움이 된다. 예제에서 펼침 한계 1에서는 결함이 안 보이고 2에서 위반하는 실행이 나온다. | "does not necessarily prove the program correct" | C12. 이 쪽이 반복 펼침을 제한하는 두 방법 (--unwind, --depth)도 적는다 |

## 7. CPROVER Manual의 loop unwinding 절과 CBMC 문서 (Diffblue/CPROVER 프로젝트, cbmc-unwinding 절의 원본 Markdown: https://raw.githubusercontent.com/diffblue/cbmc/develop/doc/cprover-manual/cbmc-unwinding.md, 문서 첫 쪽: https://diffblue.github.io/cbmc/, 종류: 공식 문서)

CPROVER Manual의 완성된 쪽 (https://www.cprover.org/cprover-manual/cbmc/unwinding/)은 이 환경에서 본문이 JavaScript로 그려져 글자를 얻지 못했다. 같은 내용의 원본 Markdown을 읽었다. 쪽은 "절 이름"으로 적는다.

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| W-031 | cbmc-unwinding.md, Understanding Loop Unwinding | CBMC의 기본 생각은 program 실행을 유한한 단계 수까지 모형으로 만드는 것이다. 이것은 반복문을 펼치는 (unwinding) 과정으로 구현된다. 반복 5회까지의 결함을 찾는 BMC instance는 반복문 본문의 복사본 5개를 담는다. | "to model a program's execution up to a bounded number of steps" | C12 |
| W-032 | 같은 절 | 반복 횟수가 자료에 크게 좌우되거나 너무 크거나 끝이 없으면 한계를 --unwind B로 주어야 한다. 횟수는 backjump의 개수로 센다. 예: i<100 조건은 반복이 끝나기까지 101번 평가되므로 한계는 100이 아니라 101이다. | "requires a limit of 101, and not 100" | C12. 같은 절이 CBMC가 반복 한계를 스스로 알아내는 때도 있다고 적는다. W-036은 교육 자료가 센 방식을 다르게 적는다 (비고 참조) |
| W-033 | 같은 절 | 펼침 횟수가 너무 작으면 더 깊은 경로가 필요한 결함을 놓칠 수 있다. 이를 막으려고 주어진 한계가 충분히 큰지 검사하는 unwinding assertion을 옵션 --unwinding-assertions로 넣을 수 있다. | "bugs that require paths that are deeper may be missed" | C12. 인용 앞 문장은 "What if the number of unwindings specified is too small?" |
| W-034 | 같은 절 | unwinding assertion은 마지막 복사본 안에서 반복 조건이 거짓임을 assert하는 꼴 (assert(!cond))이다. 모두 성립함이 증명되면 주어진 반복 한계는 그 program에 충분하다. 문서는 이를 worst-case 실행 시간의 높은 수준 상한과 연결해 설명한다. | "the given loop bounds are sufficient for the program" | C12 |
| W-035 | diffblue.github.io/cbmc/, 첫 쪽 | CBMC는 모든 경로와 모든 입력을 탐색해 assertion이 모두 참인지 검사한다. 그러나 bounded model checker여서 입력을 어떤 크기 이하로 제한해야 할 수 있다. 결과는 그런 입력들에 대해 기대대로 동작한다는 보증이다. | "using CBMC may require restricting inputs to inputs of some bounded size" | C12. 이 쪽이 buffer overflow, 부호 있는 정수 넘침 같은 정의되지 않은 동작의 검사도 적는다 |

## 8. CBMC training (model-checking 프로젝트의 교육 자료. https://model-checking.github.io/cbmc-training/cbmc/overview/loop-unwinding.html, 종류: 공식 문서 (CBMC 사용자 교육 자료. 도구 저자 본인의 문서는 아니고 오픈소스 CBMC 사용 사례 모음의 일부))

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| W-036 | Loop unwinding | --unwind 11을 주면 모든 반복문을 11번이 아니라 10번 펼친다. 반복 한계가 필요하면 --unwind로 정한다. | "10 times (not 11 times!)" | C12. W-032의 "limit of 101" 설명과 세는 방식이 달라 보인다. 한계를 쓰는 방식 (한계 N이면 반복 N-1회까지)을 책에 쓸 때는 도구의 현재 판으로 직접 시험해 확인한다 |
| W-037 | Loop unwinding assertions | 펼침 한계 안에서 assertion이 모두 성립해도 그 한계가 충분한지는 모른다. 11번째 반복에 결함이 있으면 놓친다. 이를 위해 --unwinding-assertions가 있다. | "how do we know that 10 iterations is enough?" | C12. 인용은 "But how do we know"의 뒤쪽 |
| W-038 | Loop unwinding assertions | --unwinding-assertions를 주면 CBMC는 반복문을 완전히 펼쳤는지 검사한다. 한계가 충분한 첫 예는 성공하고, 반복 횟수가 변수인 둘째 예는 unwinding assertion 실패로 검증이 실패한다. | "CBMC will check that it has completely unrolled the loop" | C12 |

## 9. Cousot, "Abstract Interpretation in a Nutshell" (P. Cousot, 연도 미표기. https://www.di.ens.fr/~cousot/AI/IntroAbsInt.html, 종류: 공식 문서 (abstract interpretation 창시자의 대학 쪽 소개 글))

쪽은 글의 번호 매긴 절이다.

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| W-039 | 절 5 | 시험과 debugging은 가능한 실행의 일부만 다루므로 증명이 아니다. 틀린 실행 경로를 놓칠 수 있다. 이를 coverage 부재의 문제라 부른다. | "Testing/debugging is not a proof" | B10 보조, C11 |
| W-040 | 절 6 | bounded model checking은 가능한 실행의 앞부분만 탐색하므로 증명이 아니다. 늦게 나타나는 오류를 놓칠 수 있다. | "late errors can be missed" | C12의 한계. 절 10도 BMC가 앞부분만 보므로 "incorrect"로 간주되어야 한다는 저자의 강한 의견을 적는다. 의견이므로 책에서는 "Cousot의 관점"으로 쓴다 |
| W-041 | 절 7 | abstract interpretation은 실제 의미의 상위 집합인 abstract semantics를 쓴다. 상위 집합이 안전하면 실제도 안전하다. | "abstract semantics covers all possible cases" | C11 |
| W-042 | 절 9 | 추상화가 sound (correct)하다는 것은 abstract semantics가 실제 의미의 모든 경우를 덮는다는 뜻이다. 모든 formal method는 sound한 추상화를 써야 한다. 시험과 달리 formal method는 전체를 덮는다. | "if a potential error is not signaled" | C11. 인용 뒤에 "that it should be definitely impossible"가 이어진다 |
| W-043 | 절 11 | 상위 집합으로 근사하므로 실제로는 없는 실행도 다루게 되어 false alarm (false positive)이 생긴다. 경보가 없으면 올바름의 증명이 된다. | "In absence of alarms, this yields a corectness proof." | C11. 원문의 철자 (correctness의 오기) 그대로 |
| W-044 | 절 12 | 자동 formal method는 모두 불완전하다 (incomplete). 실제로는 불가능한 오류에 경보를 내는 program이 무한히 많다. 모든 질문이 결정 불가능하므로 이런 false alarm은 피할 수 없고, 더 정밀한 추상화로 줄일 수 있으나 계산 비용이 늘어난다. | "Such false alarms are inevitable" | C11 |
| W-045 | 절 13 | 시험은 일부 실행만 보아 오류를 놓치고, abstract interpretation은 상위 집합을 보아 없는 오류를 만든다. 둘 다 없는 (sound하고 complete한) 추상화는 수학적으로 존재하지만 계산할 수 없다. | "it is impossible to compute" | C11 |

## 10. Astree 프로젝트 쪽 (ENS와 INRIA의 Astree 연구 팀, 연도 미표기. https://www.astree.ens.fr/, 종류: 공식 문서 (도구 개발 연구 팀의 쪽))

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| W-046 | 본문, Objectives | Astree는 C program에서 run time error (RTE)가 없음을 증명하려는 정적 분석기다. 구조적인 C program을 분석하며 동적 memory 할당과 재귀는 다루지 않는다. 임베디드 응용 (교통, 원자력, 의료, 항공우주)을 겨냥한다. | "without dynamic memory allocation and recursion" | C11. 도구의 적용 범위 한계 |
| W-047 | 본문, 수학적 불가능성 이후 | 설계 선택은 abstract interpretation 기반 정적 분석기가 가능한 오류를 모두 알리되 (sound), 때로는 실제로 일어날 수 없는 오류도 알리는 (false alarm) 것이다. 목표는 false alarm을 줄이는 것이다. | "occasionally signal errors that cannot really happen" | C11. 같은 문장이 sound함을 괄호로 단언한다 (인용에서 제외: 악센트 글자 포함) |
| W-048 | 본문, 정밀도 | 일반성의 대가로 정밀도가 낮을 수 있다. false alarm의 전형적 비율은 C 기본 연산의 10%에서 20%라고 적고, 특화한 정적 분석기는 10% 미만의 더 나은 정밀도를 얻는다고도 적는다. 이 비율은 이 쪽의 서술이며 어느 program에서 잰 것인지는 이 기록에서 확인하지 못했다. | "Typical rates of false alarms" | C11. 인용 뒤에 "are from 10% to 20% of the C basic operations"가 이어진다. 웹 쪽이라 갱신될 수 있다 |
| W-049 | 본문, Industrial Applications | 2003년 11월에 Airbus A340 fly-by-wire의 주 비행 제어 소프트웨어 (C 132,000줄)에서 RTE가 없음을 자동으로 증명했다고 적는다. | "absence of any RTE in the primary flight control software" | C11. 사례의 자기 보고 (연구 팀의 서술) |

## 11. IKOS 도구 논문과 저장소 (G. Brat, J. A. Navas, N. Shi, A. Venet, IKOS: A Framework for Static Analysis based on Abstract Interpretation (Tool Paper), NASA Ames, 2014. https://ntrs.nasa.gov/api/citations/20140012995/downloads/20140012995.pdf, 종류: 발행 기관 (NASA NTRS). 저장소: https://github.com/NASA-SW-VnV/ikos, 종류: 공식 문서)

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| W-050 | 1 | 이 논문은 DO-178C의 확장 DO-333이 정적 분석을 인증에 쓰는 방법을 설명한다고 소개하며, 1절이 DO-333이 abstract interpretation을 인증 크레딧을 얻는 한 방법으로 든다고 적는다. | "describes how developers can use static analysis" | C11, A3 주변. 규격의 서술이 아니라 NASA 논문의 서술이다. 원고에서 "DO-333이 요구한다"로 쓰지 않는다 |
| W-051 | 1 | abstract interpretation은 sound한 정적 분석을 만드는 방법론을 주는 이론이다. 분석기가 계산한 성질이 가능한 모든 실행 경로에서 성립한다는 수학적 보장을 준다. | "mathematical guarantee that all properties computed by the analyzer hold" | C11 |
| W-052 | 1 | 변수가 가질 수 있는 값을 구간 같은 간결한 집합으로 근사한다. 그 결과 실제로는 불가능한 값 할당도 포함되어 false alarm (실제로는 안전한 문장에 경보)이 생길 수 있다. 그러나 문장이 안전하다고 판정되면 오류를 낼 수 없다. 이 성질을 인증의 핵심으로 본다. | "when a statement is deemed safe, it can never cause an error" | C11. 인용은 문장 앞 접속사 뒤에서 시작한다 |
| W-053 | 저장소 README | IKOS는 abstract interpretation 이론에 기반한 C/C++ 정적 분석기다. 처음에는 sound한 정적 분석기를 만드는 C++ 라이브러리로 시작했다. C와 C++ program의 run time 오류를 찾고 없음을 증명하는 분석을 구현한다고 적는다. | "detecting and proving the absence of runtime errors" | C11 |

## 12. FDA, General Principles of Software Validation (Final Guidance for Industry and FDA Staff, 2002 (판 2.0). https://www.fda.gov/media/73141/download?attachment, 종류: 발행 기관 (미국 FDA). 쪽은 PDF 48쪽 중 몇 번째, 본 기록은 WebFetch가 저장한 PDF 사본을 직접 읽어 확인)

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| W-054 | 11 (절 3.1.2) | Quality System regulation은 ISO 8402:1994와 맞춰져 "verification"과 "validation"을 서로 다른 용어로 본다. 그러나 소프트웨어 공학 문헌 가운데는 두 말을 섞어 쓰거나 "VV&T"를 하나의 개념처럼 쓰는 것이 많다고 적는다. | "as separate and distinct terms" | C13. 앞 구절은 "treats" 뒤에 두 용어가 따옴표로 묶여 있다 |
| W-055 | 11 | software verification은 소프트웨어 생애주기의 한 단계의 산출물이 그 단계의 명시된 요구를 모두 충족한다는 객관적 증거를 준다. 일관성, 완전성, 정확성을 찾는다. | "objective evidence that the design outputs of a particular phase" | C13. 인용 뒤에 "of the software development life cycle meet all of the specified requirements"가 이어진다 |
| W-056 | 11 | testing은 많은 verification 활동 가운데 하나다. 다른 활동으로 정적 분석과 동적 분석, code와 문서의 inspection, walkthrough를 든다. | "Software testing is one of many verification activities" | C13, B 전반 |
| W-057 | 11 | FDA는 software validation을 소프트웨어 명세가 사용자 요구와 의도한 용도에 맞고, 소프트웨어로 구현한 요구를 일관되게 충족할 수 있다는 객관적 증거로 본다. 이 정의는 따옴표 안의 문장으로 적혀 있다. | "confirmation by examination and provision of objective evidence" | C13. 원문의 정의가 ISO의 정의를 따온 것인지는 이 쪽에서 확인하지 못했다. 이 책의 NASA-STD-8739.8B 정의와 견주는 용도 |
| W-058 | 11 | validation 활동은 생애주기 중에도, 끝에도 일어날 수 있다. 소프트웨어는 대개 더 큰 하드웨어 시스템의 일부이므로 소프트웨어의 validation에는 모든 소프트웨어 요구가 올바르고 완전하게 구현되어 시스템 요구로 추적된다는 증거가 포함된다. | "validation activities may occur both during, as well as at the end" | C13 |

## 13. Synopsys, Understanding How to Assess Tool Confidence Levels for ISO 26262 (Synopsys, 2017년 10월. https://www.synopsys.com/content/dam/synopsys/solutions/documents/automotive-tool-confidence-iso-26262-wp.pdf, 종류: 회사의 설명 글 (EDA 도구 회사, 7쪽). ISO 26262:2011 기준)

(2차 자료)

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| W-059 | 1 | 이 글은 ISO 26262 Part 8의 "Confidence in the Use of Software Tools"에 해당하는 절 (2011판 11절)이 소프트웨어 tool 분류와 qualification의 방법을 준다고 설명한다. 절의 목적은 필요한 신뢰 수준을 정하는 기준과, 필요하면 tool을 qualification하는 수단을 주는 것이다. | "software tool classification and qualification" | A1. 같은 내용: W-063. 2011판 조항 번호 11.4.5를 이 글이 적는다 (책에 쓰지 않는다) |
| W-060 | 1 | tool confidence level (TCL)은 두 기준으로 정한다. Tool Impact (TI)는 tool이 개발 중인 설계에 직접 안전 관련 영향을 주는가이고, TI1은 직접 영향 없음 (예: 표 계산 프로그램), TI2는 직접 영향 있음 (예: 합성 도구)이다. | "Two criteria are used to determine TCL" | A1. 같은 내용: W-063 |
| W-061 | 1 | Tool Error Detection (TD)은 tool의 오작동을 막거나 찾는 수단이 있다는 확신의 정도다. TD1은 높은 확신, TD2는 중간, TD3은 낮은 확신이다. | "TD1 means a high degree of confidence" | A1. 같은 내용: W-063 |
| W-062 | 2 | TCL을 정하는 표 (Table 3): TI1이면 TD와 관계없이 TCL1이다. TI2이면 TD1은 TCL1, TD2는 TCL2, TD3은 TCL3이다. TCL1은 추가 qualification이 필요 없다. TCL2나 TCL3이면 추가 qualification이 필요하다. | "TCL1 means that no further qualification is required" | A1. 같은 내용: W-063 |
| W-063 | 4 | 모든 tool을 TCL1로 만드는 것이 목표라는 것은 오해이며, 목표는 tool이 오류를 넣거나 놓치지 않는다는 높은 확신이 있는 개발 흐름을 만들고 설명하는 것이라고 적는다. TCL2나 TCL3의 tool은 추가 qualification을 하면 쓸 수 있다. 방법은 TCL2와 TCL3에서 같고 ASIL마다 권장 정도가 다르다. | "The methods are the same for either a TCL2 or a TCL3 assessment" | A1. 같은 내용: W-064 |
| W-064 | 4, 5 | 방법 네 가지: (1a) 사용을 통한 신뢰 증가, (1b) tool 개발 과정의 평가, (1c) tool의 validation, (1d) 안전 규격에 따른 개발. 이 글은 대부분의 EDA tool에 1c를 권한다. 1a는 같은 목적, 비슷한 사용 사례, 비슷한 환경과 설정에서 쓰였고, tool 명세가 바뀌지 않았으며, 이전 개발에서 얻은 오작동과 잘못된 출력을 체계적으로 기록했다는 증거가 필요하다고 적는다. | "Method 1a requires evidence that the tool has been used for the same purpose" | A1. 같은 내용: W-067 (네 방법의 존재). 1a 조건은 이 글만의 서술이다 |
| W-065 | 3 | tool을 쓰는 쪽이 TCL을 판정할 책임이 있다. tool 공급자가 미리 정한 TCL이 있어도 사용자가 자기 사용 사례에 맞는지 확인해야 한다. 사용자가 공급자와 의견이 다를 수 있고, 그러면 추가 qualification이 필요할 수 있다. | "The user of the software tool is responsible for the TCL value assessment" | A1. 같은 내용: W-066 |
| W-066 | 3 | 한 tool만으로 TCL을 평가하기 어려우면 tool chain으로 평가할 수 있다. 예: 합성 tool의 출력은 TCL2나 TCL3이지만, 입력과 출력 netlist를 독립적인 formal 비교로 확인하면 합성 tool chain의 출력을 TCL1로 올릴 수 있다. tool chain은 사용 사례로 문서화해야 한다. | "increase the confidence level that the synthesis tool output is correct" | A1. tool 출력을 다른 도구로 확인해 TD를 높이는 설계의 예 |

## 14. Siemens, Clearing the fog of ISO 26262 tool qualification (Siemens EDA, Verification Horizons 블로그, 2022-04-13. https://blogs.sw.siemens.com/verificationhorizons/2022/04/13/clearing-the-fog-of-iso-26262-tool-qualification/, 종류: 회사의 설명 글 (EDA 도구 회사). ISO 26262:2018 기준)

(2차 자료)

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| W-067 | 본문, Background | ISO 26262는 안전 관련 전자 장치를 개발할 때 쓰는 tool을 평가하도록 하며 세 용어를 정의한다고 설명한다. TI는 tool이 오류를 넣거나 놓칠 가능성의 평가다. TI1은 그럴 가능성이 없다는 논거가 있을 때 고르고, 나머지는 TI2다. | "introduce or fail to detect errors" | A1. 같은 내용: W-060 |
| W-068 | 같은 곳 | TD는 tool의 오작동을 막을 수 있다는 확신의 평가다. TD1은 오작동이 막히거나 발견된다는 높은 확신, TD2는 중간 확신, TD3은 그 밖의 경우다. TCL은 TI와 TD로 정해지며, TCL1은 높은 신뢰로 추가 qualification이 필요 없고, TCL2와 TCL3은 추가 qualification 방법이 필요하다. | "No further qualification methods are required" | A1. 같은 내용: W-061, W-062. 인용은 TCL1의 설명 문장의 끝부분 |
| W-069 | 같은 곳 | TCL은 tool만으로 정해지지 않고, 최종 제품의 공정 단계에서 tool을 쓰는 맥락으로 정해진다. 구입한 tool과 내부에서 만든 tool 모두에 TCL을 정해야 한다. | "not based only on the tool but also on its use in the context" | A1. 같은 내용: W-065. 인용은 "TCL determination is not based only on the tool but..." 에서 따옴 |
| W-070 | 같은 곳 | 2018판에는 tool qualification 방법이 네 가지 있고, ASIL 목표에 따라 적합도가 다르다고 적는다. TCL은 "달성"하는 것이 아니라 분류이며, "TCL2가 TCL1보다 낫다"는 것은 오해라고 지적한다. 구입한 tool은 방법과 그 방법이 ASIL 목표에 권장되는지를 보라고 권한다. | "TCL is not something that is achieved" | A1. 같은 내용: W-064 (네 방법). 2018판의 조항 번호를 이 글이 적었으나 쓰지 않는다 |

## 15. MathWorks와 TUV SUD, Qualifying Software Tools According to ISO 26262 (M. Conrad, P. Munier, F. Rauch, 2010경. https://fr.mathworks.com/content/dam/mathworks/tag-team/Objects/m/61793_CMR10-16.pdf, 종류: 회사의 설명 글 (도구 회사 MathWorks와 인증 기관 TUV SUD의 공저, 논문 꼴). ISO/DIS 26262 (2009 초안)와 IEC 61508 개정판 초안 기준)

(2차 자료) 초안 기준이므로 판 사이의 차이가 크다. 개념 설명으로만 쓴다.

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| W-071 | 3 | IEC 61508은 off-line 소프트웨어 지원 tool을 세 부류로 나눈다고 설명한다 (개정 2판 초안의 정의 절 기준). T1은 실행 code에 직접이든 간접이든 기여할 수 없는 tool. T2는 설계나 실행 code의 verification이나 test를 돕는 tool이며 이 tool의 오류는 결함을 못 찾게 만들 수 있다. T3은 실행 code에 직접이든 간접이든 기여할 수 있는 출력을 만드는 tool. | "tools supporting verification or test of the design or the executable code" | A2. 같은 내용: W-074, W-075 |
| W-072 | 3 | T3 off-line tool에는 tool이 명세나 매뉴얼에 맞는다는 증거가 필요하다. 이 증거는 사용을 통한 신뢰나 특정 응용에 독립한 validation에서 올 수 있다. 증거가 없으면 응용마다 tool의 오류를 찾는 조치 (예: back-to-back testing)를 둘 수 있다. off-line tool의 새 판마다 qualification해야 한다. | "Each new version of an off-line support tool shall be qualified" | A2, A7 (back-to-back의 용도). 같은 내용: W-074, W-075 |
| W-073 | 3 | ISO/DIS 26262-8의 tool qualification은 tool의 사용 사례를 문서로 만들고 분석하는 것에서 시작한다. tool이나 그 잘못된 출력이 안전 요구의 위반으로 이어질 수 있는지 평가하고, 그 오류를 막거나 찾을 확률도 평가해 필요한 TCL을 정한다. 필요한 TCL과 ASIL이 qualification 방법의 선택을 이끈다. | "a required tool confidence level (TCL) is determined" | A1. 초안 기준 서술. 같은 내용: W-060 - W-062 |

## 16. UL (IEC 61508 Why Tool Qualification, H. El-Sayed, UL Solutions, 2024년 11월, 61508 협회 사이트의 발표 자료. https://61508.org/wp-content/uploads/2024/11/09B-IEC-61508-Why-tool-qualification_V2_cut.pdf, 종류: 회사의 설명 글 (시험 인증 회사의 발표 자료, 23쪽, 쪽은 PDF 쪽))

(2차 자료) 발표자의 의견과 규격의 서술이 섞여 있다. 쪽 13의 "deficiency" 서술은 발표자의 평가다.

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| W-074 | 10 | IEC 61508 Part 3 (2판)의 off-line 지원 tool은 세 부류다. T1은 안전 관련 시스템의 실행 code (data 포함)에 직접이든 간접이든 기여하는 출력이 없다 (예: text editor, 설정 관리 tool). T2는 설계나 실행 code의 test나 verification을 돕고 오류가 결함을 못 찾게 할 수 있지만 실행 소프트웨어에 직접 오류를 만들 수 없다 (예: test harness 생성기, coverage 측정, 정적 분석). T3은 실행 code에 기여하는 출력을 만든다 (예: 최적화 compiler). | "T1 generates no outputs which can directly or indirectly contribute" | A2. 같은 내용: W-071, W-075. 원문 인용은 한 부류만 담는다 |
| W-075 | 11 | 발표자가 요약한 요구: T1, T2, T3 tool의 선택을 정당화해야 한다. T3 tool에는 tool이 명세나 문서에 맞는다는 증거가 있어야 한다. T2, T3 tool이 설정 baseline의 항목을 만들면 tool 정보를 baseline에 기록해야 한다. off-line tool의 새 판마다 qualification해야 한다. | "Each new version of off-line support tool shall be qualified." | A2. 같은 내용: W-072, W-076 |
| W-076 | 13 | 발표자는 IEC 61508이 SIL에 비례한 T2, T3 qualification 요구를 주지 않으며, tool의 위험 분석도 요구하지 않는다고 평가한다. 그래서 tool 오류가 안전에 직접 영향을 줄 때도 완화 조치가 없을 수 있다고 적는다. | "does not ask for a tool risk assessment analysis" | A2. 발표자의 평가이며 규격의 서술로 쓰지 않는다. ISO 26262가 TI와 TD로 분석하는 것과 대비되는 점 |
| W-077 | 8 | 발표자는 소프트웨어의 failure rate를 지수 분포로 모델링하고, 고장이 없어야 하는 SIL 1 소프트웨어가 10의 6제곱 시간에 95% 신뢰를 보이려면 약 3 x 10의 6제곱 시간이 필요하다고 계산해 보인다. 99% 신뢰에서는 최소 4.6M 시간이 필요하다고 적고 Part 7 Annex D의 표 D1을 가리킨다. | "For 99% confidence, we need at least 4.6M hrs" | A5 (proven in use의 통계적 증거). 같은 방향: W-084. 이 쪽은 발표자의 계산이며 지수 분포 가정이 붙는다 |

## 17. AbsInt, IEC 61508 qualification (AbsInt GmbH. https://www.AbsInt.com/qualificaiton/iec.htm, 종류: 회사의 설명 글 (정적 분석 도구와 compiler 회사). 연도 미표기)

(2차 자료)

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| W-078 | 본문 | IEC 61508은 off-line 지원 tool을 세 부류로 정의한다고 설명한다. T1은 실행 code에 기여하지 않는 tool, T2는 설계나 실행 code의 verification이나 test를 돕는 tool (오류가 결함을 못 찾게 할 수 있음), T3은 실행 code에 직접 또는 간접으로 기여하는 출력을 만드는 tool이다. | "tools supporting verification or test of the design or the executable code" | A2. 같은 내용: W-071, W-074. 이 문장은 W-071과 같다 (같은 부류 정의를 두 곳이 같은 말로 쓴다. 규격 원문의 표현을 따랐을 가능성) |
| W-079 | 본문 | T2, T3 tool에는 tool의 동작과 사용 조건을 정한 명세가 있어야 하고, T3 tool에는 명세를 충족한다는 증거가 있어야 한다. 이 증거는 사용을 통한 신뢰나 tool validation에서 올 수 있고, T3에 든 증거를 T2에도 쓸 수 있다. | "evidence has to be provided that the tool meets its specification" | A2. 같은 내용: W-072, W-075 |

## 18. AFuzion, DO-330 Introduction - Tool Qualification (AFuzion, 연도 미표기. https://afuzion.com/?p=358, 종류: 회사의 설명 글 (항공 소프트웨어 컨설팅과 교육 회사))

(2차 자료)

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| W-080 | 본문 | DO-330은 tool의 영향이 tool의 범주와 적용되는 DAL로 정해지므로 tool qualification 활동을 그 영향에 맞춘다. 그래서 세 가지 tool 기준에 따라 다섯 TQL (tool qualification level)을 도입한다. | "five Tool Qualification Levels (TQLs) based upon three Tool Criteria" | A3. 같은 내용: W-082, W-085 |
| W-081 | 본문 | Criteria 1: 출력이 항공 소프트웨어의 일부가 되어 오류를 넣을 수 있는 tool (예: model에서 source code를 자동 생성하는 code 생성 tool). Criteria 2: verification 과정을 자동화해 오류를 놓칠 수 있고, 그 출력이 다른 verification 과정이나 항공 소프트웨어에 영향을 줄 수 있는 개발 과정의 생략이나 축소를 정당화하는 데 쓰이는 tool (예: 완전성 검증과 coverage 검사를 함께 하는 model checking tool). Criteria 3: 의도한 사용 범위에서 오류를 놓칠 수 있는 tool (예: 구조 coverage tool). | "whose output is part of the airborne software" | A3. 같은 내용: W-082, W-083, W-085 |

## 19. LDRA, DO-330 Test Tool Qualification Technical Briefing (LDRA Ltd, v2.0, PDF 생성일 2021-11. https://ldra.com/wp-content/uploads/ldra/DO-330-Test-Tool-Qualification-Technical-Briefing-v2.0.pdf, 종류: 회사의 설명 글 (소프트웨어 test와 정적 분석 도구 회사))

(2차 자료)

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| W-082 | 3 | DO-330은 세 기준을 바탕으로 TQL 개념을 도입한다고 적고, 세 기준을 번호 매겨 적는다: 1) 출력이 항공 소프트웨어의 일부가 되는 tool, 2) verification을 자동화하며 그 출력이 다른 verification이나 개발 과정의 생략이나 축소를 정당화하는 데 쓰이는 tool, 3) 의도한 사용 범위에서 오류를 놓칠 수 있는 tool. | "within the scope of its intended use, could fail to detect an error" | A3. 같은 내용: W-081, W-083 |
| W-083 | 3 | DAL (소프트웨어 level)과 기준의 조합이 TQL을 정하는 표 (Figure 1): 기준 1은 A에서 D 순서로 TQL-1, -2, -3, -4. 기준 2는 A, B에서 TQL-4, C, D에서 TQL-5. 기준 3은 모든 level에서 TQL-5. 이 회사는 자사의 test 도구를 기준 3의 도구로 보고 level과 관계없이 TQL-5라고 적는다. | "always assigned Tool Qualification Level 5" | A3. 같은 내용: W-084 (같은 표). 표의 칸을 쪽 3의 그림에서 읽었다. 받은 문서 faa-ac-20-115d의 대응표와 견주어 확인한다 |

## 20. Rapita Systems, DO-330 (Rapita Systems, 연도 미표기. https://www.rapitasystems.com/do-330, 종류: 회사의 설명 글 (임베디드 소프트웨어 verification 도구 회사))

(2차 자료)

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| W-084 | 본문, Tool qualification levels | DO-178C가 세 가지 tool 평가 기준을 정하고, 이 기준과 소프트웨어의 DAL을 조합해 다섯 TQL 가운데 하나로 tool을 분류한다. 표는 W-083과 같다 (기준 1: TQL-1에서 TQL-4, 기준 2: TQL-4, TQL-4, TQL-5, TQL-5, 기준 3: 모두 TQL-5). | "3 sets of tool assessment criteria" | A3. 같은 내용: W-083, W-080 |
| W-085 | 같은 곳 | 예시: 구조 설명을 package나 class 구조로 바꾸는 code 생성 tool은 기준 1이다. verification tool은 보통 기준 3이어서 TQL-5다. 기준 2는 주로 model 기반 testing에서 검증된 code 생성기와 함께 쓸 때 해당하는데, 생성된 code의 verification이 model의 testing으로 대신되기 때문이다. TQL의 번호가 낮을수록 더 엄격하게 test해야 한다. | "Tools with a lower numbered TQL" | A3. 같은 내용: W-081. 인용 뒤에 "(e.g. 1) must be tested more rigorously"가 이어진다 |

## 21. FAA Order 8110.49 Chg 2 (FAA, Software Approval Guidelines, Change 2, 2017-04-10 (장 9는 2003 원판). https://www.faa.gov/documentLibrary/media/Order/FAA_Order_8110_49_w-chg_2.pdf, 종류: 발행 기관 (미국 FAA). 쪽은 PDF 84쪽 중 몇 번째)

이 문서의 tool 장 (9장)은 DO-178B 기준이고, DO-178C의 criteria 1, 2, 3을 쓰지 않는다. 2018년의 8110.49A (19쪽)는 이 장을 담고 있지 않았다. DO-330 / DO-178C의 기준 셋의 뜻을 발행 기관의 문서로 찾지 못했고, 이 절은 DO-178B 시대의 같은 취지의 서술이다. 책에서 쓰면 "DO-178B 시대의 FAA 정책"으로 밝힌다.

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| W-086 | 37 (인쇄 쪽 50) | DO-178B는 development tool을 출력이 항공 소프트웨어의 일부가 되어 오류를 넣을 수 있는 tool로 정의한다고 적는다. 검증 중에 쓰는 tool이 모두 verification tool인 것은 아니다. 코드를 test용으로 instrumentation했다가 test 뒤에 제거하는 tool은 출력이 더 이상 verify되지 않으면 원래 code를 알 수 없는 방식으로 바꿀 수 있다. | "tools used during verification are not necessarily" | A3 (criteria 1과 3의 구분의 배경). 인용 뒤에 "verification tools"가 이어진다 |
| W-087 | 38 (인쇄 쪽 51) | development tool은 오류를 시스템에 직접 넣을 수 있다. verification tool은 제품에 이미 있는 오류를 놓칠 수만 있다. 그래서 항공 소프트웨어에 오류가 들어가려면 두 과정 (개발이 오류를 넣고 verification이 못 찾는 것)이 모두 부족해야 하고, DO-178B가 두 tool에 서로 다른 엄격함을 요구하는 이유다. | "only fail to detect an error that already exists in the product" | A3 |
| W-088 | 38 (인쇄 쪽 51) | tool qualification 여부를 정하는 세 질문: (1) tool이 오류를 넣거나 기존 오류를 놓칠 수 있는가, (2) tool의 출력이 다른 verification 활동으로 확인되지 않는가, (3) tool 사용으로 DO-178B의 과정이 생략, 축소, 자동화되는가. 세 질문 모두 "예"이면 qualification해야 한다. | "Can the tool insert an error into the airborne software" | A3. DO-178B 기준이고 criteria 1-3의 3 질문과는 다르다. 인용은 첫 질문의 앞부분 |

## 22. Embitel, What is Safety Element out of Context (SEooC) in Automotive Functional Safety (ISO 26262) (Embitel, 2019-08-27. https://www.embitel.com/blog/embedded-blog/what-is-safety-element-out-of-context-seooc-in-automotive-functional-safety, 종류: 회사의 설명 글 (임베디드 소프트웨어 서비스 회사의 블로그))

(2차 자료)

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| W-089 | 본문 | SEooC는 특정 차량에서의 적용 맥락을 고려하지 않고 개발한 소프트웨어나 하드웨어 부품이다. 구체적인 요구가 아니라 가정에 기대어 개발하며, 특정 차량이나 OEM이 아니라 가정한 맥락을 위해 개발한다. | "developed for an assumed context and not for a specific vehicle" | A4. 같은 내용: W-092 |
| W-090 | 본문 | SEooC의 개발은 가정으로 시작한다. 가정에는 적용 영역과 의도한 기능, 시스템의 기술 구조 개요, 기능 안전 요구와 기술 안전 요구, 시스템에 할당된 ASIL이 들어간다. HARA가 아니라 가정이 안전 목표와 ASIL을 정한다. | "Development of a safety element out of context starts with assumptions." | A4. 같은 내용: W-092 |
| W-091 | 본문 | SEooC를 시스템에 통합하기 전에 가정을 확인한다. 통합 단계에서 item의 안전 요구와 SEooC가 가정한 안전 요구를 맞춰 보고, 차이가 있으면 Part 8의 변경 관리를 시작해 영향 분석을 한다. 차이가 안전 목표에 비춰 받아들일 만하면 조치가 없고, 아니면 item 정의나 기능 안전 개념이나 SEooC 부품을 바꾼다. | "a change management activity is initiated" | A4. 같은 내용: W-093, W-094 |

## 23. Renesas, Functional Safety Support for Automotive (3) - Applying the ISO 26262 Standard to SEooC Software (S. Guo, Renesas, 2021-10-04. https://www.renesas.com/en/blogs/renesas-functional-safety-support-automotive-3-applying-iso-26262-standard-seooc-software, 종류: 회사의 설명 글 (반도체와 소프트웨어 공급 회사의 블로그))

(2차 자료)

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| W-092 | 본문 | SEooC는 ISO 26262에서 특정 item의 맥락에서 개발하지 않은 것을 뜻한다고 이 글이 설명한다. 가정에 기대어 개발하고, 통합할 때 가정의 유효성을 확인할 수 있는 여러 item에 쓰이도록 만든다. SEooC는 시스템, subsystem, 소프트웨어 부품, 하드웨어 부품일 수 있다. 예: AUTOSAR MCAL. | "validity of its assumptions can be established during integration" | A4. 같은 내용: W-089, W-090, W-094 |
| W-093 | 본문 | SEooC 소프트웨어가 고객에게 이르면 고객이 가정을 확인하고 자기 시스템에 통합해야 한다. 가정을 모두 확인하는 것은 시간이 걸리고 소프트웨어를 충분히 알아야 한다. 가정이 맞지 않으면 SEooC 부품이나 시스템 안전 요구를 바꿔야 할 수 있다. | "validate the assumptions and integrate it into their system" | A4. 같은 내용: W-091 |
| W-094 | 본문 | 이 글은 설정 가능한 SEooC 소프트웨어의 시험을 두 가지 생애주기 선택으로 설명한다. 1) 설정을 적용한 소프트웨어를 verify한다 (Simplified Lifecycle I). 2) 허용 설정 값의 범위로 설정 가능한 소프트웨어를 verify하고 고객의 설정이 그 범위에 든다고 보인다 (Simplified Lifecycle II). 이 회사는 사용의 가정을 Safety Application Note에 공개한다고 적는다. | "verify the configurable software with a range of admissible configuration data" | A4. 이 선택은 Part 8의 간소화된 생애주기에 관한 이 회사의 설명이다 |

## 24. Cinque, De Simone, Marchetta (Certify the Uncertified: Towards Assessment of Virtualization for Mixed-criticality in the Automotive Domain, arXiv:2205.12596, 2022. https://arxiv.org/pdf/2205.12596, 종류: 논문 (대학 연구진의 공개본))

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| W-095 | 2 | 이 논문은 ISO 26262에서 SEooC를 설명하는 문장을 인용한다: SEooC는 가정에 기대어 ISO 26262에 맞게 개발한 소프트웨어일 수 있고, 통합 때 가정의 유효성을 확인할 수 있는 여러 item에 쓰이도록 만든다. 가정이 새 맥락에 맞지 않으면 영향 분석을 시작해야 한다고 덧붙인다. | "validity of its assumptions can be established during integration" | A4. 규격의 문장을 논문이 옮긴 것이므로 (2차 자료), W-092와 같은 문장이다. 확인 시점은 통합 때다. 영향 분석은 이 논문의 서술 |

## 25. Schabe와 Braband (H. Schabe, J. Braband, Basic requirements for proven-in-use arguments, arXiv:1511.01839, 2015. https://arxiv.org/pdf/1511.01839, 종류: 논문 (TUV Rheinland와 Siemens 저자의 preprint))

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| W-096 | 1 | proven-in-use 논증은 사용 이력이 있는 미리 개발된 제품을 원래와 다른 환경에서 쓰려 할 때 필요하다. 예: 안전 맥락에 쓰는 COTS 부품, 다른 규격으로 인증된 제품, 낮은 무결성 수준으로 인증된 제품을 더 높은 수준에 쓰는 경우. 제품은 소프트웨어 모듈을 포함할 수 있다. | "Proven-in-use arguments are needed when pre-developed products" | A5 |
| W-097 | 1 | IEC 61508-7의 Annex D는 단순한 통계 model로 소프트웨어 신뢰도를 평가하자고 제안한다. 이 Annex는 논란이 많고 개정 중이라고 적는다. 철도 규격 EN 50129는 SIL 3, 4에 100만 시간의 운영, 서로 다른 장비로 2년 이상의 경험을 권한다. | "discussed quite controversially" | A5. 같은 방향: W-077. 원문 인용의 앞은 "this annex is". 숫자는 철도 규격의 것이다 |
| W-098 | 7 | 이 방법을 쓰려고 반드시 충족해야 하는 조건: 환경의 무작위 영향이 대표적이어야 한다. 비교하는 부품이 서로 비슷해야 하고 "결함을 고치면 보통 다른 부품으로 보아야 한다". 모든 고장을 기록하고 관찰할 수 있어야 한다. 모든 수명과 사용 시간을 기록해야 한다. 이 조건은 좋은 통계 표본의 요건과 같다고 적는다. | "if bugs are fixed, the component has usually to be regarded as a different component" | A5. 인용은 열네 낱말. 소프트웨어에 특정한 조건으로, 결함을 고친 판은 다른 부품이라는 점이 중요하다 |
| W-099 | 6 | Ariane 4의 관성 기준 장치 소프트웨어를 Ariane 5에 그대로 재사용했고, 질적인 proven-in-use 논증의 결과로 test와 validation의 양을 줄였다. 저자들은 이 부품이 116번의 임무에서 오류가 없었다고 가정해도, 운영 환경이 바뀌면 운영 경험에 기댄 논증이 무효가 된다고 적는다. 부품이 다른 시스템에 통합되는 것도 충분히 비슷함을 논증해야 한다. | "the change in operational environment would have invalidated any argument" | A5. Ariane 501 보고서 (references/ariane-501-report)와 견줄 사례. 이 논문의 서술이며 보고서의 결론이 아니다 |

## 26. Schildbach, On the Application of ISO 26262 in Control Design for Automated Vehicles (G. Schildbach, Lubeck 대학, arXiv:1804.04349, 2018. https://arxiv.org/pdf/1804.04349, 종류: 논문 (대학 연구자의 공개본))

(2차 자료) ISO 26262의 판은 이 글에서 확인하지 못했다. 인용한 조항은 "part 8.14"로 적혀 있다.

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| W-100 | 6 | ISO 26262의 개발 과정 전체를 건너뛰는 것은 예외적인 경우에만 허용된다. 흔한 방법은 proven-in-use 논증을 세우는 것이다. 후보는 다른 차종이나 다른 안전 관련 산업에서 쓰였거나 자동차용으로 만들지 않은 COTS여야 한다. 논증은 관측한 사고율이 ASIL마다 정한 수준보다 낮음을 보여야 한다 (저자의 서술: ASIL D 1 fit, C 10 fit, B 100 fit, A 1,000 fit). | "Bypassing the entire ISO 26262 development process altogether is permitted only in exceptional cases." | A5. 수치는 이 논문만의 서술이므로 원문 확인 전에는 쓰지 않는다. 같은 쪽이 소프트웨어는 하드웨어만큼 철저히 test할 수 없다는 취지의 서술도 한다 |

## 27. Intertek, Exploring the IEC 61508 Proven-In-Use Concept (Intertek, 2026-01-22. https://www.intertek.com/blog/2026/01-22-exploring-the-iec-61508-proven-in-use-concept/, 종류: 회사의 설명 글 (시험 인증 회사의 블로그))

(2차 자료) 이 글은 하드웨어의 무작위 고장률 (Route 2H)을 다룬다. 소프트웨어의 체계적 결함에 대한 서술이 아니다.

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| W-101 | 본문 | IEC 61508의 proven-in-use는 하드웨어의 무작위 고장률을 이전의 운영 이력으로 정당화하는 길이다. 유효하려면 문서화된 안정한 운영 이력, 의도한 응용과 같은 운영 환경, 관찰 기간의 중대한 설계 변경 없음, 현장 고장의 기록과 분류와 조사가 필요하다고 적는다. | "PIU is not an alternative to systematic capability requirements" | A5. 체계적 능력의 요구는 proven-in-use로 대신할 수 없다는 점. 이 글의 조항 번호 (Part 2의 7.4.10)는 책에 쓰지 않는다 |
| W-102 | 본문 | 증거의 최소 요건으로 충분한 설치 수 (보통 100대 이상), SIL 목표에 맞는 운영 시간 (10의 6제곱에서 10의 8제곱 시간 이상), 환경의 비교 가능성, 완전한 변경 관리, 모든 모드의 고장 기록을 든다. 통계적으로는 chi-square 방법을 쓴다고 적는다. | "statistically significant operational history" | A5. 수치는 이 글의 서술이다 |

## 28. MathWorks 문서 (MathWorks, Simulink Test 문서. https://www.mathworks.com/help/sltest/ug/back-to-back-equivalence-testing.html, https://www.mathworks.com/help/sltest/sil-pil-and-hil-tests.html, https://www.mathworks.com/help/simulink/slref/simulink-concepts-model-development-processes.html, 종류: 회사의 설명 글 (도구 회사의 공식 사용 설명서))

(2차 자료) 이 환경의 내려받기 (curl)는 이 사이트가 접근을 막아 글자를 얻지 못했다. 우회하지 않고 WebFetch 도구의 답을 썼다. 아래 인용은 도구가 돌려준 문장이며 원문 글자와의 대조를 못 했다. 원고에 쓰기 전에 쪽을 직접 연다.

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| W-103 | back-to-back-equivalence-testing | back-to-back testing (equivalence testing)은 생성한 code가 model 시뮬레이션과 같은 결과를 내는지 시험한다. 일반 모드 시뮬레이션과 SIL 시뮬레이션의 결과를 견주고, 예에서는 Outport 신호를 두 모드에서 그려 견준다. | "tests whether the generated code produces the same results as the model simulation" | B7. 같은 내용을 말하는 다른 회사의 출처를 찾지 못했다 (MathWorks 문서와 W-072의 한 줄 언급뿐). 도구가 돌려준 문장 |
| W-104 | sil-pil-and-hil-tests | 이 쪽은 equivalence test를 back-to-back test라고도 부른다고 적고, 요약에서 SIL, PIL, 실시간 HIL의 equivalence test를 다룬다고 한다. | "Equivalence tests are sometimes referred to as back-to-back tests." | B7, B8. 도구가 돌려준 문장 |
| W-105 | simulink-concepts-model-development-processes | SIL은 개발 컴퓨터에서 compile한 source code를 별도 process로 실행하는 개발 과정이다. PIL은 source code를 cross-compile해 만든 object code를 target processor에서 실행하는 개발 과정이다. HIL은 제어기의 하드웨어와 소프트웨어 같은 실제 부품을 짝지어 쓰는 개발 과정이라고 적는다 (도구가 돌려준 문장이 여기서 끊겨 있어 나머지 부분을 확인하지 못했다). 이 쪽은 MIL을 정의하지 않았다. | "cross-compiles source code and runs the resulting object code on a target processor" | B8. 같은 내용: W-106, W-107. 도구가 돌려준 문장이며 HIL의 정의 문장은 끝이 잘려 있다 |

## 29. Synopsys, Model-Based Design and Virtual ECUs Enable Early Testing for Electric Vehicle Controls (Synopsys, 2025-01. https://www.synopsys.com/content/dam/synopsys/verification/white-papers/model-based-design-and-vecu-wp.pdf, 종류: 회사의 설명 글 (EDA 도구 회사의 백서, 8쪽))

(2차 자료)

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| W-106 | 2 | model 기반 설계에서 verification은 각 단계의 설계 상세 수준에 맞는 시뮬레이션으로 닫힌 루프에서 이뤄진다. 단계는 MiL, SiL, PiL, HiL이다. 개발 흐름은 SiL까지 목표 하드웨어에 의존하지 않고, PiL부터는 최소한 개발 보드 하나에 의존하여 cross-compile한 알고리즘을 실제 목표에서 실행해 수치 정확도와 실행 시간과 기능 정확성을 확인한다. | "These verification stages include Model-in-the-Loop" | B8. 같은 내용: W-105, W-107. 인용은 단계 이름을 든 문장의 일부 |

## 30. Jordan 등 (Y. Jordan, D. von Wissel, A. Dolha, J. Mauss, Full Virtualization of Renault's Engine Management Software and Application to System Development, arXiv:1802.06841, 2018경. https://arxiv.org/pdf/1802.06841, 종류: 논문 (자동차 회사와 도구 회사의 공동 저자, 공개본))

쪽은 PDF 9쪽 중 몇 번째다. 발표 연도는 이 복사본에서 확인하지 못했다 (arXiv 번호로 2018년 2월).

| 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
|---|---|---|---|---|
| W-107 | 5 | 가상 ECU (virtual ECU)를 PC에서 실행하는 방법으로 세 가지를 구분한다. virtual PiL은 목표 processor용으로 compile한 hex file을 chip을 시뮬레이션해 실행한다. SiL은 PC용으로 compile한 C code다. MiL은 C code를 생성하는 model을 쓴다. | "SiL: C code compiled for PC" | B8. 같은 내용: W-105, W-106. 이 논문의 한 쪽에서 세 구분을 한꺼번에 적는다. 정의라기보다 이 논문이 쓰는 구분이다 |

---

## 찾지 못한 것

"발행 기관"은 정부, 표준화 기구, 도구 저자의 공식 문서 또는 저자가 공개한 논문이다. "2차 자료 둘 이상"은 서로 다른 회사나 기관의 설명 글 둘 이상이다.

| 주제 | 근거의 세기 | 어디서 | 못 찾은 것과 주의 |
|---|---|---|---|
| A1. ISO 26262의 tool 신뢰 (TI, TD, TCL, qualification 방법) | 2차 자료 둘 이상 | W-059 - W-066 (Synopsys, 2011판 기준), W-067 - W-070 (Siemens, 2018판 기준), W-073 (MathWorks와 TUV SUD, 2009 초안) | 발행 기관의 자료는 없다. 두 회사는 서로 독립이다. TCL 표와 네 방법에 대해 둘이 일치한다. 2011판과 2018판의 조항 번호 차이가 있어 번호는 쓰지 않는다. Part 8의 qualification 방법별 ASIL 권장 정도의 표는 Synopsys의 Figure 4에 있으나 2011판이며, 2018판과 같은지 확인하지 못했다 |
| A2. IEC 61508 도구 분류 T1, T2, T3 | 2차 자료 둘 이상 | W-071 (MathWorks와 TUV SUD), W-074 - W-076 (UL), W-078 - W-079 (AbsInt) | 발행 기관의 자료는 없다. 세 곳이 같은 분류를 적는다. 두 곳 (W-071, W-078)이 문장을 거의 같게 적는다. 규격 원문의 문장을 따랐을 수 있어 독립성은 약하다. 2판의 정의는 개정 중 초안이었다는 서술도 있어 판을 확인해야 한다 |
| A3. DO-330과 DO-178C의 tool qualification criteria 1, 2, 3의 뜻 | 2차 자료 둘 이상 | W-080 - W-085 (AFuzion, LDRA, Rapita) | 발행 기관의 자료는 못 찾았다. FAA Order 8110.49A (2018)는 이 장을 담지 않고, 8110.49 Chg 2는 DO-178B 시대의 서술이다 (W-086 - W-088). 받은 문서 faa-ac-20-115d의 대응표와 TQL 표 (W-083, W-084)가 맞는지 책에서 견주어야 한다. 세 회사의 서술이 일치한다. 기준 2의 문구는 회사마다 조금 다르다 |
| A4. SEooC와 가정의 확인 | 2차 자료 둘 이상 | W-089 - W-091 (Embitel), W-092 - W-094 (Renesas), W-095 (대학 논문이 ISO 문장을 인용) | 발행 기관의 자료는 못 찾았다. ISO 26262 Part 10을 SEooC의 안내 문서로 가리키는 것은 Embitel뿐이다. 통합할 때 쓰는 쪽이 가정을 확인한다는 점은 세 곳이 일치한다. 확인의 주체를 "누가"로 더 구체적으로 (OEM인가 tier 1인가) 적은 곳은 없다 |
| A5. proven in use 논증, 기존 소프트웨어 qualification | 2차 자료 둘 이상 (일반 조건), 하나뿐 (ISO 26262의 수치) | 조건: W-096 - W-099 (논문), W-077 (UL), W-101 - W-102 (Intertek, 하드웨어). ISO 26262: W-100 | 발행 기관의 자료는 없다. 일반 조건 (같은 환경, 변경 없음, 고장 기록, 통계 표본)은 W-098, W-101이 서로 비슷하게 말한다. ISO 26262 Part 8의 proven in use 절의 요구 (ASIL별 사고율, 시간)는 W-100 하나뿐이고 판을 확인하지 못했다. IEC 61508의 소프트웨어 proven in use 기준 (Part 7 Annex D)은 논란이 있고 개정 중이라고 W-097이 적는다. ISO 26262 Part 10의 proven in use 사례는 목차만 보였고 본문을 읽지 못했다. 기존 소프트웨어 부품의 qualification을 정면으로 다룬 공개 자료 (예: ISO 26262의 소프트웨어 부품 qualification 절의 설명)는 찾지 못했다 |
| A6. compiler 결함과 최적화가 뜻을 바꾼 사례 | 발행 기관 (저자 공개 논문 둘) | W-011 - W-017 (Yang 등 2011), W-018 - W-022 (Wang 등 2013) | 충분하다. 두 연구의 결과를 그대로 쓴다 (결함 325개 보고, unstable code 160개 확인). 이 책의 개념과 직접 이어지는 부분: CompCert의 증명 밖에서도 결함이 있었다 (W-016) |
| B7. back-to-back test | 하나뿐 | W-103, W-104, W-072 (MathWorks 문서, MathWorks와 TUV SUD의 논문) | 같은 회사의 문서뿐이다. MathWorks 문서의 글자는 WebFetch로만 읽어 대조하지 못했다. 다른 회사나 기관의 설명을 찾지 못했다. "ISO 26262가 back-to-back을 권한다"는 서술은 이 기록의 어떤 쪽에서도 확인하지 못했다 |
| B8. MIL, SIL, PIL, HIL의 구분 | 2차 자료 둘 이상 | W-105 (MathWorks, MIL 정의는 없음), W-106 (Synopsys), W-107 (논문, MiL/SiL/virtual PiL) | HIL의 정의를 직접 서술한 곳은 W-105뿐이다 (잘린 문장). 네 단계 이름을 나열하는 곳은 W-106이다. MIL의 정의는 W-107의 한 줄 (MiL: C code를 생성하는 model)뿐이다. 서로 다른 출처에서 구분이 일치하나, 발행 기관의 자료는 없다 |
| B9. mutation testing의 정의와 한계 | 논문 하나 (공개 survey) | W-023 - W-027 (Jia와 Harman) | 발행 기관 수준의 survey이나 하나뿐이다. 고전 원문 (DeMillo, Lipton, Sayward 1978)과 Budd와 Angluin의 결정 불가능성 증명은 직접 읽지 않았고 이 survey의 설명이다. 이 복사본의 학술지 서지 (호, 쪽)를 확인하지 못했다 |
| B10. test로는 매우 낮은 고장률을 보일 수 없다는 논증 | 발행 기관 + 저자 공개본 | W-001 - W-007 (Butler와 Finelli, NASA NTRS), W-008 - W-010 (Littlewood와 Strigini, City 대학), W-039 (Cousot) | 충분하다. 두 논문이 같은 결론을 서로 독립으로 낸다. NTRS 본은 NASA 보고서 꼴의 공개본이라 학술지판과 쪽이 다를 수 있다 |
| C11. abstract interpretation 기반 정적 분석의 보장과 한계 | 발행 기관 (도구 저자의 공개 자료) | W-039 - W-045 (Cousot), W-046 - W-049 (Astree 팀), W-050 - W-053 (IKOS와 NASA) | 충분하다. sound함의 뜻과 false alarm의 필연성을 Cousot, Astree 팀, NASA 세 곳이 같게 말한다. Astree의 false alarm 비율 (W-048)은 연구 팀의 서술이며 어느 program인지 확인하지 못했다 |
| C12. bounded model checking, unwinding, unwinding assertion | 발행 기관 (도구의 공식 문서) | W-028 - W-038 (CBMC 논문, CPROVER Manual의 원본, CBMC 문서와 교육 자료), W-040 (Cousot) | 충분하다. 다만 CPROVER Manual의 완성 쪽과 교육 자료가 한계의 센 방식을 다르게 적는다 (W-032 대 W-036). 책에 --unwind의 뜻을 쓰기 전에 도구로 직접 확인한다. diffblue.github.io의 문서 쪽은 첫 쪽만 읽었다 |
| C13. verification과 validation 구별의 다른 분야 정의 | 발행 기관 | W-054 - W-058 (FDA, 의료기기 소프트웨어, 2002) | 충분하다. FDA 안내서는 ISO 8402:1994와 맞춘다고 적는다. 안내서가 2026년의 QMSR 시행 전에 나왔음을 안내문이 밝힌다. 정의 문장은 의료기기 규제의 맥락이다 |

## 읽지 못한 쪽 (막힌 출처)

- TUV SUD의 webinar 자료 (tuvsud.com의 PDF)는 사람 확인 화면 (Cloudflare)이 나와 버렸다.
- MathWorks 문서 (mathworks.com)와 HHS 사이트의 FDA 안내서 복사본은 접근 거부를 돌려주었다. MathWorks는 WebFetch 도구의 답만 있다 (절 28). FDA 안내서는 fda.gov의 PDF를 WebFetch가 저장한 사본으로 읽었다 (절 12).
- Analog Devices의 블로그와 ISO의 온라인 열람 쪽 (OBP)은 내려받지 못했다. ISO 규격의 공개 미리보기는 읽지 못했다.
- 이 환경의 내려받기가 접근 거부를 받은 곳에서 요청 머리글을 바꿔 다시 시도하는 일은 하지 않았다.
