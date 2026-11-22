#!/usr/bin/env python3
"""1장의 그림을 만든다: 페달 센서가 고착된 뒤의 차량 속도와 토크 요구.

    tools/plot_intro.py <naive.csv> <vcu.csv> <출력.svg>

두 CSV는 `make intro`가 만든다. 바깥의 library를 쓰지 않고 SVG를 글자로 쓴다.
"""
import csv
import sys

W, H = 760, 520
LEFT, RIGHT = 70, 20
PANELS = [  # (제목, CSV의 열, 단위를 바꾸는 곱, y의 최댓값, y 눈금 간격, 위쪽 y, 높이)
    ("차량 속도 (km/h)", "speed_mps", 3.6, 35.0, 5.0, 50, 200),
    ("토크 요구 (Nm)", "torque_out", 0.1, 100.0, 25.0, 300, 150),
]
T_MAX = 8000
EVENTS = [(1000, "페달 30%"), (3000, "센서 고착"), (4000, "페달 놓음")]
SERIES = [  # (이름, 색, 점선)
    ("안전 장치가 없는 제어기", "#c0392b", ""),
    ("예제의 제어기", "#1f5fa8", "6 4"),
]


def read(path, column, scale):
    points = []
    with open(path, encoding="utf-8") as f:
        for row in csv.DictReader(f):
            t = int(row["t_ms"])
            if t % 20 == 0:
                points.append((t, float(row[column]) * scale))
    return points


def main():
    if len(sys.argv) != 4:
        print(__doc__)
        return 2
    paths = [sys.argv[1], sys.argv[2]]
    plot_w = W - LEFT - RIGHT
    out = []
    out.append('<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 %d %d" width="%d" height="%d" '
               'font-family="Helvetica, Arial, \'Apple SD Gothic Neo\', \'Malgun Gothic\', sans-serif" '
               'font-size="13">' % (W, H, W, H))
    out.append('  <title>페달 센서가 고착된 뒤의 차량 속도와 토크 요구</title>')
    out.append('  <rect x="0" y="0" width="%d" height="%d" fill="#ffffff"/>' % (W, H))

    def x_of(t):
        return LEFT + plot_w * t / T_MAX

    for title, column, scale, y_max, y_step, top, height in PANELS:
        def y_of(v):
            return top + height - height * v / y_max

        out.append('  <text x="%d" y="%d" font-weight="bold">%s</text>' % (LEFT, top - 12, title))
        # 눈금과 격자
        v = 0.0
        while v <= y_max + 1e-9:
            y = y_of(v)
            out.append('  <line x1="%d" y1="%.1f" x2="%d" y2="%.1f" stroke="#dddddd"/>'
                       % (LEFT, y, W - RIGHT, y))
            out.append('  <text x="%d" y="%.1f" text-anchor="end" fill="#444444">%g</text>'
                       % (LEFT - 8, y + 4, v))
            v += y_step
        for t in range(0, T_MAX + 1, 1000):
            x = x_of(t)
            out.append('  <text x="%.1f" y="%d" text-anchor="middle" fill="#444444">%d</text>'
                       % (x, top + height + 18, t // 1000))
        out.append('  <rect x="%d" y="%d" width="%d" height="%d" fill="none" stroke="#444444"/>'
                   % (LEFT, top, plot_w, height))
        # 사건을 세로선으로
        for t, label in EVENTS:
            x = x_of(t)
            out.append('  <line x1="%.1f" y1="%d" x2="%.1f" y2="%d" stroke="#888888" '
                       'stroke-dasharray="2 3"/>' % (x, top, x, top + height))
            if column == "speed_mps":
                out.append('  <text x="%.1f" y="%d" fill="#444444">%s</text>' % (x + 4, top + 14, label))
        # 선
        for (name, color, dash), path in zip(SERIES, paths):
            pts = " ".join("%.1f,%.1f" % (x_of(t), y_of(min(v, y_max))) for t, v in read(path, column, scale))
            extra = ' stroke-dasharray="%s"' % dash if dash else ""
            out.append('  <polyline points="%s" fill="none" stroke="%s" stroke-width="2.5"%s/>'
                       % (pts, color, extra))

    # x축 이름과 범례
    last_top, last_h = PANELS[-1][5], PANELS[-1][6]
    out.append('  <text x="%d" y="%d" text-anchor="middle" fill="#444444">시간 (초)</text>'
               % (LEFT + plot_w // 2, last_top + last_h + 38))
    lx = LEFT + 435
    ly = PANELS[0][5] + 149  # 5와 10 km/h의 격자선 사이, 점선의 아래. 선과 겹치지 않는 곳
    for i, (name, color, dash) in enumerate(SERIES):
        y = ly + i * 15
        extra = ' stroke-dasharray="%s"' % dash if dash else ""
        out.append('  <line x1="%d" y1="%d" x2="%d" y2="%d" stroke="%s" stroke-width="2.5"%s/>'
                   % (lx, y, lx + 36, y, color, extra))
        out.append('  <text x="%d" y="%d">%s</text>' % (lx + 44, y + 4, name))
    out.append('</svg>')

    with open(sys.argv[3], "w", encoding="utf-8") as f:
        f.write("\n".join(out) + "\n")
    print("그림을 썼다: %s" % sys.argv[3])
    return 0


if __name__ == "__main__":
    sys.exit(main())
