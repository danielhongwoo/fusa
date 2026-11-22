#!/usr/bin/env python3
"""gcov의 출력을 파일마다 한 줄로 줄인다.

    tools/coverage_summary.py build/cov/gcov.txt

안전 요구사항을 받는 파일 (입력 검사, 감시, 출력 단계, 주기 실행)은
statement와 MC/DC가 100%가 아니면 실패한다. 기능의 파일은 숫자만 보인다.
이 도구는 qualification되지 않았다.
"""
import re
import sys

SAFETY = ("src/input/", "src/monitor/", "src/reaction/", "src/vcu/")


def main():
    text = open(sys.argv[1], encoding="utf-8", errors="replace").read()
    rows = []
    for block in re.split(r"\n(?=File ')", text):
        m = re.match(r"File '([^']+)'", block)
        if not m or not m.group(1).startswith("../../src/"):
            continue
        name = m.group(1).replace("../../", "")

        def pick(label):
            mm = re.search(label + r":\s*([\d.]+)% of (\d+)", block)
            return (float(mm.group(1)), int(mm.group(2))) if mm else None

        rows.append((name, pick("Lines executed"), pick("Taken at least once"),
                     pick("Condition outcomes covered")))

    def show(v):
        return "%6.2f%% (%d)" % v if v else "해당 없음"

    failed = []
    print("%-28s %-16s %-16s %-16s" % ("파일", "statement", "branch", "MC/DC"))
    for name, lines, branches, conds in sorted(rows):
        print("%-28s %-16s %-16s %-16s" % (name, show(lines), show(branches), show(conds)))
        if name.startswith(SAFETY):
            if (lines and lines[0] < 100.0) or (conds and conds[0] < 100.0):
                failed.append(name)
    print("괄호 안은 세는 단위의 수다. MC/DC는 GCC가 센 조건 결과의 수다.")
    if not rows:
        print("coverage: gcov의 출력에서 src/의 파일을 찾지 못했다")
        return 1
    if failed:
        print("coverage: 안전 요구사항을 받는 파일이 100%에 못 미친다: " + ", ".join(failed))
        return 1
    print("coverage: 안전 요구사항을 받는 파일은 statement와 MC/DC가 100%다")
    return 0


if __name__ == "__main__":
    sys.exit(main())
