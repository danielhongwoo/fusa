#!/usr/bin/env python3
"""책의 예제다. 실제 제품에 쓸 수 없다.

검사 단계가 실패를 알리는지 본다.

    python3 tools/step_check.py      (example/drive-torque 폴더에서. make step-check)

단계마다 알려진 결함을 하나 넣은 복사본에서 그 단계만 돌려, 종료 상태가 0이 아닌지를 확인한다.
검사 단계가 있다는 것과 그 단계가 실패를 알린다는 것은 다른 일이다. 이 예제에서 단계가 실패를 덮은 일이
세 번 있었다 (docs/test-report.md 6절): 정적 분석 단계가 clang-tidy의 경고를 넘겼고, coverage 단계가
100%에 못 미친 것을 넘겼고, 도구가 없으면 그 단계를 건너뛰고 통과했다. 셋 모두 다른 사람이 찾았다.

변이 검사 (tools/mutation_check.py)가 "test가 결함을 잡는가"를 묻는다면, 이 도구는 한 단계 위에서
"단계가 실패를 밖으로 알리는가"를 묻는다. 넣어 본 결함에 대해서만 말해 준다.

단계가 실패한 까닭도 본다. 종료 상태가 0이 아니라는 것만 보면, 넣은 결함과 상관없는 까닭 (compile 오류,
시간 초과)으로 실패해도 "알림"으로 센다 (검토자가 짚었다). 그래서 경우마다 단계의 출력에 있어야 할 글을
정규식으로 적어 두고, 그 글이 있을 때에만 "알림"으로 센다. 결함을 넣지 않은 복사본에서는 여기에서 쓰는
단계가 모두 통과하는지를 먼저 본다.
이 도구는 qualification되지 않았다.
"""
import os
import re
import shutil
import signal
import subprocess
import sys
import tempfile

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
TIMEOUT_S = 600

# 결함을 넣지 않은 복사본에서 통과해야 하는 단계. 아래의 경우들이 쓰는 단계를 모두 넣는다
BASE_STEPS = [["test"], ["variants"], ["trace"], ["static", "skipped"], ["coverage", "skipped"], ["prove", "skipped"]]

# (설명, make에 줄 인자, 단계의 출력에 있어야 할 글 (정규식), 바꿀 곳 [(파일, 원래 글, 바꾼 글)])
CASES = [
    ("test: 제품 코드의 결함 (알 수 없는 기어 값을 D로 본다)",
     ["test"], r"^실패  TC-107 ",
     [("src/input/input.c", "in->gear = GEAR_N; /* 알 수 없는 값은 N으로 본다 */", "in->gear = GEAR_D;")]),
    ("variants: 최적화를 켰을 때에만 드러나는 결함",
     ["variants"], r"변형 O2: test가 실패했다",
     [("src/app/app.c", "    if (target > limit) {\n        target = limit;\n    }\n",
       "#ifdef __OPTIMIZE__\n    target = target / 2;\n#endif\n    if (target > limit) {\n        target = limit;\n    }\n")]),
    ("trace: 요구사항 파일에 없는 ID가 코드에 있다",
     ["trace"], r"문제  SWR-99: 코드에 있지만 요구사항 파일에 없다",
     [("src/app/app.c", " * 기능의 구현.\n", " * 기능의 구현. SWR-99\n")]),
    ("static: cppcheck가 지적하는 코드 (늘 거짓인 조건)",
     ["static"], r"knownConditionTrueFalse",
     [("src/app/app.c", "    if (p < 0) {\n        p = 0;\n    }\n",
       "    if (p < 0) {\n        p = 0;\n    } else if (p < -5) {\n        p = 0;\n    } else {\n        /* 그대로 */\n    }\n")]),
    ("static: clang-tidy만 경고하는 코드 (넓히기 전에 넘치는 곱셈)",
     ["static"], r"clang-tidy: 경고 1 개",
     [("src/app/app.c", "    if (p < 0) {\n        p = 0;\n    }\n",
       "    if (p < 0) {\n        p = 0;\n    }\n    {\n        long long wide = (long long)(p * 1000);\n        (void)wide;\n    }\n")]),
    ("static: clang-tidy가 아무 말 없이 죽는다",
     ["static", "CLANG_TIDY=false"], r"clang-tidy: 경고 0 개[^\n]*\nclang-tidy: 실패 \(종료 상태 1\)", []),
    ("coverage: test가 실행하지 않는 문장",
     ["coverage"], r"100%에 못 미친다: src/vcu/vcu\.c",
     [("src/vcu/vcu.c", "    if (ok) {\n        hal_watchdog_write(",
       "    if (vcu->torque_out == 1234567) {\n        ok = false;\n    }\n    if (ok) {\n        hal_watchdog_write(")]),
    ("prove: 배열의 바로 뒤에 쓰는 결함",
     ["prove", "PROPS=prove_flow"], r"실패    prove_flow\n\[flow_mark\.array_bounds",
     [("src/flow/flow.c", "    if (f->count < FLOW_TASK_COUNT) {\n        f->marks[f->count] = mark;",
       "    if (f->count <= FLOW_TASK_COUNT) {\n        f->marks[f->count] = mark;")]),
    ("도구가 없다: cbmc", ["prove", "skipped", "CBMC="], r"건너뜀: cbmc가 없다\nmake check: 실패", []),
    ("도구가 없다: GCC (coverage)", ["coverage", "skipped", "GCC="], r"건너뜀: GCC 14 이상이 없다\nmake check: 실패", []),
    ("도구가 없다: cppcheck", ["static", "skipped", "CPPCHECK="], r"건너뜀: cppcheck가 없다\nmake check: 실패", []),
    ("도구가 없다: clang-tidy", ["static", "skipped", "CLANG_TIDY="], r"건너뜀: clang-tidy가 없다\nmake check: 실패", []),
]


def run(copy, args):
    """단계를 돌려 (종료 상태, 출력)을 돌려준다. 끝나지 않으면 종료 상태 대신 None이다."""
    out_path = os.path.join(copy, "step-check-output.txt")
    with open(out_path, "wb") as out:
        # 끝나지 않으면 make와 그 아래의 프로세스를 모두 끝낸다 (make만 끝내면 test 실행 파일이 남는다)
        proc = subprocess.Popen(["make", "-s"] + args, cwd=copy, stdout=out, stderr=subprocess.STDOUT,
                                start_new_session=True)
        try:
            status = proc.wait(timeout=TIMEOUT_S)
        except subprocess.TimeoutExpired:
            os.killpg(proc.pid, signal.SIGKILL)
            proc.wait()
            status = None
    return status, open(out_path, encoding="utf-8", errors="replace").read()


def main():
    hidden = 0
    work = tempfile.mkdtemp(prefix="step-check-")
    try:
        # 기준: 결함을 넣지 않은 복사본에서는 단계가 통과해야 한다. 그래야 아래의 실패가 결함 때문이다
        base = os.path.join(work, "base")
        shutil.copytree(ROOT, base, ignore=shutil.ignore_patterns("build"))
        for args in BASE_STEPS:
            status, _ = run(base, args)
            if status != 0:
                print("오류  결함을 넣지 않았는데 단계가 실패한다 (make %s)" % " ".join(args))
                return 1
        for i, (what, args, expect, edits) in enumerate(CASES):
            copy = os.path.join(work, "c%02d" % i)
            shutil.copytree(ROOT, copy, ignore=shutil.ignore_patterns("build"))
            broken = False
            for path, old, new in edits:
                target = os.path.join(copy, path)
                text = open(target, encoding="utf-8").read()
                if text.count(old) != 1:
                    print("오류  %s: 바꿀 곳을 찾지 못했다 (%s)" % (path, what))
                    broken = True
                    break
                open(target, "w", encoding="utf-8").write(text.replace(old, new))
            if broken:
                hidden += 1
                continue
            status, output = run(copy, args)
            if status is None:
                print("오류  %s: 단계가 끝나지 않았다" % what)
                hidden += 1
            elif status == 0:
                print("덮음  %s" % what)
                hidden += 1
            elif re.search(expect, output, re.MULTILINE) is None:
                # 실패하기는 했지만 넣은 결함 때문이라는 글이 없다 (예: compile 오류)
                print("오류  %s: 단계가 실패했지만 기대한 글이 출력에 없다 (%s)" % (what, expect))
                if os.environ.get("STEP_CHECK_DEBUG"):
                    print(output[-1500:])
                hidden += 1
            else:
                print("알림  %s" % what)
    finally:
        shutil.rmtree(work, ignore_errors=True)
    print("단계의 확인: %d가지 가운데 %d가지에서 단계가 실패를 알렸다" % (len(CASES), len(CASES) - hidden))
    return 1 if hidden else 0


if __name__ == "__main__":
    sys.exit(main())
