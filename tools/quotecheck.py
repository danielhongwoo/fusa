#!/usr/bin/env python3
"""읽기 메모의 인용이 받은 문서의 그 쪽에 실제로 있는지 본다.

    tools/quotecheck.py notes/reading/ch04-facts.md [...]

읽기 메모 (notes/reading/)는 문서마다 절 하나와 표 하나로 되어 있다.
    ## 1. <문서 id> (...)
    | 번호 | 쪽 | 사실 | 원문의 짧은 인용 | 비고 |
이 도구는 표의 줄마다 references/<문서 id>/ 의 PDF에서 그 쪽의 글자를 뽑아 인용이 들어 있는지 찾는다.

보는 것은 "인용한 글자가 그 쪽에 있다"까지다. "사실" 칸의 풀이가 옳은지는 보지 않는다.
쪽이 숫자가 아닌 줄 (웹 주소, 조항 번호)과 인용이 없는 줄은 건너뛰고 그 수를 알린다.
스캔본처럼 글자 층이 없는 문서는 찾지 못한 것으로 나온다.
받은 문서는 git에 없으므로, 문서를 받아 둔 컴퓨터에서만 돌릴 수 있다.
"""
import glob
import os
import re
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
HEADING = re.compile(r"^#{2,3}\s+(?:[\d.]+\s+)?([a-z0-9][a-z0-9-]+)\b")
PAGES = re.compile(r"^\s*(?:slides?\s*)?(\d+)(?:\s*-\s*(\d+))?\s*$")


# PDF에서 나오는 글자 가운데 ASCII로 바꿔 견줄 것: 굽은 따옴표, 긴 줄표, 합자
REPLACE = {0x2018: "'", 0x2019: "'", 0x201C: '"', 0x201D: '"', 0x2013: "-", 0x2014: "-",
           0xFB01: "fi", 0xFB02: "fl", 0x00AD: ""}


def normalize(text):
    """글자와 숫자만 남긴다. 줄바꿈, 붙임표, 띄어쓰기의 차이로 어긋나지 않게 하기 위해서다"""
    return re.sub(r"[^a-z0-9]+", "", text.translate(REPLACE).lower())


def page_text(pdf, first, last, cache={}):
    key = (pdf, first, last)
    if key not in cache:
        result = subprocess.run(["pdftotext", "-q", "-f", str(first), "-l", str(last), pdf, "-"],
                                capture_output=True, text=True)
        cache[key] = normalize(result.stdout)
    return cache[key]


def page_ranges(cell):
    """ '10, 14' -> [(10, 10), (14, 14)], '19-20' -> [(19, 20)] """
    ranges = []
    for part in cell.split(","):
        m = PAGES.match(part)
        if not m:
            return []
        first = int(m.group(1))
        last = int(m.group(2)) if m.group(2) else first
        ranges.append((first, last))
    return ranges


def check_file(path):
    doc = None
    found = missing = skipped = 0
    for line in open(path, encoding="utf-8"):
        if line.startswith("#"):
            # 문서 id로 시작하지 않는 절 (예: 웹에서 읽은 것)은 대조하지 않는다
            m = HEADING.match(line)
            doc = m.group(1) if m and os.path.isdir(os.path.join(ROOT, "references", m.group(1))) else None
            continue
        if not line.startswith("| F"):
            continue
        cells = [c.strip() for c in line.strip().strip("|").split("|")]
        if len(cells) < 4:
            continue
        number, pages, quote = cells[0], cells[1], cells[3]
        quotes = re.findall(r'"([^"]{8,})"', quote)
        if not quotes and len(quote) >= 8 and quote.isascii() and not quote.startswith("("):
            quotes = [quote]  # 따옴표 없이 적은 인용
        ranges = page_ranges(pages)
        pdfs = glob.glob(os.path.join(ROOT, "references", doc or "", "*.pdf")) if doc else []
        if not quotes or not ranges or not pdfs:
            skipped += 1
            continue
        ok = False
        for pdf in pdfs:
            for first, last in ranges:
                # 쪽 번호가 한 쪽 어긋난 것은 받아들이지 않는다. 그 쪽만 본다
                text = page_text(pdf, first, last)
                if all(normalize(q) in text for q in quotes if normalize(q)):
                    ok = True
        if ok:
            found += 1
        else:
            missing += 1
            print("없음  %s  %s %s쪽: %s" % (number, doc, pages, quotes[0][:70]))
    print("%s: 찾음 %d, 없음 %d, 건너뜀 %d" % (os.path.relpath(path, ROOT), found, missing, skipped))
    return missing


def main():
    if len(sys.argv) < 2:
        print(__doc__)
        return 2
    missing = sum(check_file(p) for p in sys.argv[1:])
    return 1 if missing else 0


if __name__ == "__main__":
    sys.exit(main())
