#!/usr/bin/env python3
"""요구사항의 추적을 검사한다.

    tools/trace.py            검사하고 표를 찍는다
    tools/trace.py --quiet    문제만 찍는다
    tools/trace.py --strict   구현 예정인 요구사항이 하나라도 있으면 실패한다

보는 것
    1. docs/requirements.yaml의 ID가 겹치지 않고, 위로 가는 추적 (parents)이 있는 ID를 가리킨다
    2. safety goal이 아닌 요구사항은 모두 위 단계의 요구사항에 이어진다
    3. software safety requirement (SWR-)는 src/의 코드에 ID가 적혀 있다
    4. software safety requirement는 test case (TC-)가 하나 넘게 있고, 그 TC가 test/의 코드에 있다
    5. test/의 코드에 적힌 TC는 요구사항 파일에도 있다
    6. 증명 함수 (proved_by)는 test/proof/harness.c에 있다
    7. 구현 예정 (status: planned)인 요구사항은 3과 4를 보지 않는다. 그 수와 ID를 늘 찍는다.
       구현 예정이라고 적었는데 코드나 test가 이미 있으면 문제다 (표시를 지우지 않은 것이다).
       위 단계의 요구사항이 구현 예정인데 그 아래가 모두 구현되어 있어도 문제다.
       거꾸로, 위 단계가 구현한 것으로 적혀 있는데 그 아래가 모두 구현 예정이어도 문제다.
       --strict에서는 구현 예정이 0이어야 한다

요구사항 파일은 YAML의 작은 부분만 쓴다. 바깥의 library를 받지 않으려고 직접 읽는다.
    requirements:
      - id: SWR-01
        text: "한 줄 문장"
        parents: [TSR-01]
        verified_by: [TC-001]
        proved_by: [prove_something]
        status: planned
이 도구는 qualification되지 않았다.
"""
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
REQ_FILE = os.path.join(ROOT, "docs", "requirements.yaml")
ORDER = ["SG", "FSR", "TSR", "SWR"]
problems = []


def problem(msg):
    problems.append(msg)


def parse_value(raw):
    raw = raw.strip()
    if raw.startswith("[") and raw.endswith("]"):
        inner = raw[1:-1].strip()
        return [x.strip().strip('"') for x in inner.split(",")] if inner else []
    if len(raw) >= 2 and raw[0] == '"' and raw[-1] == '"':
        return raw[1:-1]
    return raw


def load_requirements(path):
    items, current = [], None
    with open(path, encoding="utf-8") as f:
        for n, line in enumerate(f, 1):
            text = line.rstrip("\n")
            if not text.strip() or text.lstrip().startswith("#"):
                continue
            if re.match(r"^requirements:\s*(\[\])?\s*$", text):
                continue
            m = re.match(r"^\s*-\s+(\w+):\s*(.*)$", text)
            if m:
                current = {m.group(1): parse_value(m.group(2))}
                items.append(current)
                continue
            m = re.match(r"^\s+(\w+):\s*(.*)$", text)
            if m and current is not None:
                current[m.group(1)] = parse_value(m.group(2))
                continue
            problem("%s:%d: 읽을 수 없는 줄이다" % (os.path.basename(path), n))
    return items


def scan(folder, pattern):
    """폴더의 C 파일에서 pattern에 맞는 ID를 찾아 {ID: [파일, ...]}로 돌려준다."""
    found = {}
    base = os.path.join(ROOT, folder)
    for dirpath, _, names in os.walk(base):
        for name in sorted(names):
            if not name.endswith((".c", ".h")):
                continue
            path = os.path.join(dirpath, name)
            with open(path, encoding="utf-8") as f:
                for ident in set(re.findall(pattern, f.read())):
                    found.setdefault(ident, []).append(os.path.relpath(path, ROOT))
    return found


def main():
    quiet = "--quiet" in sys.argv
    strict = "--strict" in sys.argv
    reqs = load_requirements(REQ_FILE)
    by_id = {}
    for r in reqs:
        rid = r.get("id", "")
        if not re.match(r"^(SG|FSR|TSR|SWR)-\d+$", rid):
            problem("ID의 형식이 틀렸다: %r" % rid)
            continue
        if rid in by_id:
            problem("%s: ID가 겹친다" % rid)
        by_id[rid] = r
        if not r.get("text"):
            problem("%s: 문장 (text)이 없다" % rid)
        if r.get("status", "planned") != "planned":
            problem("%s: status에는 planned만 쓸 수 있다. 구현한 요구사항에는 status를 적지 않는다" % rid)
    planned = sorted(rid for rid, r in by_id.items() if r.get("status") == "planned")

    for rid, r in by_id.items():
        kind = rid.split("-")[0]
        parents = r.get("parents", [])
        if kind != "SG" and not parents:
            problem("%s: 위로 가는 추적 (parents)이 없다" % rid)
        for p in parents:
            if p not in by_id:
                problem("%s: 없는 ID를 가리킨다: %s" % (rid, p))
            elif ORDER.index(p.split("-")[0]) >= ORDER.index(kind):
                problem("%s: 위 단계가 아닌 것을 가리킨다: %s" % (rid, p))

    in_src = scan("src", r"\bSWR-\d+\b")
    in_test = scan("test", r"\bTC-\d+\b")
    listed_tc = set()
    for rid, r in sorted(by_id.items()):
        tcs = r.get("verified_by", [])
        listed_tc.update(tcs)
        if not rid.startswith("SWR-"):
            continue
        if rid in planned:
            if rid in in_src:
                problem("%s: 구현 예정이라고 적었는데 코드에 ID가 있다 (%s)" % (rid, in_src[rid][0]))
            for tc in tcs:
                if tc in in_test:
                    problem("%s: 구현 예정이라고 적었는데 %s가 test/의 코드에 있다" % (rid, tc))
            continue
        if rid not in in_src:
            problem("%s: src/의 코드에 ID가 없다" % rid)
        if not tcs:
            problem("%s: test case (verified_by)가 없다" % rid)
        for tc in tcs:
            if tc not in in_test:
                problem("%s: %s가 test/의 코드에 없다" % (rid, tc))
    harness = os.path.join(ROOT, "test", "proof", "harness.c")
    harness_text = open(harness, encoding="utf-8").read() if os.path.exists(harness) else ""
    for rid, r in sorted(by_id.items()):
        for name in r.get("proved_by", []):
            if not re.search(r"\bvoid %s\(void\)" % re.escape(name), harness_text):
                problem("%s: 증명 함수 %s가 test/proof/harness.c에 없다" % (rid, name))
    for rid in planned:
        if rid.startswith("SWR-"):
            continue
        children = [c for c, r in by_id.items() if rid in r.get("parents", [])]
        if children and not any(c in planned for c in children):
            problem("%s: 구현 예정이라고 적었는데 그 아래의 요구사항 (%s)이 모두 구현되어 있다"
                    % (rid, ", ".join(sorted(children))))
    for rid in sorted(by_id):
        if rid.startswith("SWR-") or rid in planned:
            continue
        children = [c for c, r in by_id.items() if rid in r.get("parents", [])]
        if children and all(c in planned for c in children):
            problem("%s: 구현한 것으로 적혀 있는데 그 아래의 요구사항 (%s)이 모두 구현 예정이다"
                    % (rid, ", ".join(sorted(children))))
    if strict and planned:
        problem("구현 예정인 요구사항이 %d개 있다 (--strict)" % len(planned))
    for sid in sorted(in_src):
        if sid not in by_id:
            problem("%s: 코드에 있지만 요구사항 파일에 없다 (%s)" % (sid, in_src[sid][0]))
    for tc in sorted(in_test):
        if tc not in listed_tc:
            problem("%s: test 코드에 있지만 어느 요구사항에도 이어지지 않는다 (%s)" % (tc, in_test[tc][0]))

    if not quiet:
        def chain(rid):
            ps = by_id[rid].get("parents", [])
            return rid if not ps else "%s <- %s" % (rid, ", ".join(chain(p) for p in ps))
        print("요구사항 %d개" % len(by_id))
        for rid in sorted(by_id, key=lambda x: (ORDER.index(x.split("-")[0]), x)):
            if rid.startswith("SWR-"):
                r = by_id[rid]
                if rid in planned:
                    print("  %s | 구현 예정" % chain(rid))
                    continue
                print("  %s | 코드: %s | test: %s" % (
                    chain(rid),
                    ", ".join(in_src.get(rid, ["없음"])),
                    ", ".join(r.get("verified_by", [])) or "없음"))
    print("구현 예정: %d개%s" % (len(planned), (" (" + ", ".join(planned) + ")") if planned else ""))
    for p in problems:
        print("문제  " + p)
    print("추적 검사: 문제 %d개" % len(problems))
    return 1 if problems else 0


if __name__ == "__main__":
    sys.exit(main())
