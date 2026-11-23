#!/usr/bin/env python3
"""원고에서 쓰지 않기로 한 표현을 찾는다 (RULES.md 1절).

사용법: tools/stylecheck.py [파일 ...]   파일을 주지 않으면 chapters/의 모든 원고를 본다.
        tools/stylecheck.py --count      장마다 수만 적는다 (tools/lint가 쓴다).
목록은 tools/style-words.tsv에 있다. 찾은 것은 주의이고 오류가 아니다:
인용문이나 그 말이 맞는 경우가 있으므로 사람이 (또는 검토자가) 보고 판단한다.
"""
import glob
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


def rules():
    out = []
    with open(os.path.join(ROOT, "tools", "style-words.tsv"), encoding="utf-8") as f:
        for line in f:
            line = line.rstrip("\n")
            if not line or line.startswith("#"):
                continue
            pat, msg = line.split("\t", 1)
            out.append((re.compile(pat), msg))
    return out


def scan(path, rs):
    found = []
    with open(path, encoding="utf-8") as f:
        for n, line in enumerate(f, 1):
            for pat, msg in rs:
                for m in pat.finditer(line):
                    a = max(0, m.start() - 15)
                    found.append((n, line[a:m.end() + 10].strip(), msg))
    return found


def main():
    args = [a for a in sys.argv[1:] if a != "--count"]
    count_only = "--count" in sys.argv[1:]
    files = args or sorted(glob.glob(os.path.join(ROOT, "chapters", "*.md")))
    rs = rules()
    total = 0
    for p in files:
        found = scan(p, rs)
        total += len(found)
        name = os.path.relpath(p, ROOT)
        if count_only:
            if found:
                print("%4d  %s" % (len(found), name))
            continue
        for n, text, msg in found:
            print("%s:%d: %s  ->  %s" % (name, n, text, msg))
    print("쓰지 않기로 한 표현: %d곳" % total)
    return 0


if __name__ == "__main__":
    sys.exit(main())
