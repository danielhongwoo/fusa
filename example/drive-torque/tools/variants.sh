#!/bin/sh
# 책의 예제다. 실제 제품에 쓸 수 없다.
# 같은 test를 다른 compile option으로 다시 돌려, 출력이 -O0의 것과 한 줄도 다르지 않은지 본다.
#   O2, Os     최적화를 켜도 동작이 같은가. host의 compiler에 대해서만 말해 준다.
#              target의 compiler와 그 최적화는 보지 않는다
#   sanitizer  실행 중의 memory 오류와 정의되지 않은 동작이 없는가. test가 지나간 길에 대해서만 말해 준다.
#              배열 밖의 접근은 AddressSanitizer가 본다 (UndefinedBehaviorSanitizer는 구조체의 끝에 있는
#              배열을 넘는 것을 이 설정에서 알리지 않는다). 초기화하지 않은 변수를 읽는 것은 둘 다 알리지
#              않는다. 그것은 값으로 보는 test (TC-023, TC-133)가 맡는다
#   gcc        다른 compiler (GCC)의 -O0과 -O2에서도 출력이 같은가. GCC가 있을 때에만 돌린다
# 사용법: sh tools/variants.sh <cc> [gcc]   (example/drive-torque 폴더에서)
#
# 변형마다 소스를 build/variants/<이름>/에 복사해 거기에서 make test를 돌린다.
# 이 도구는 qualification되지 않았다.
set -u

CC=${1:-cc}
GCC=${2:-}
BASE="-std=c11 -Wall -Wextra -Werror -pedantic -g"
SAN="-O1 -fsanitize=address,undefined -fno-sanitize-recover=all -fno-omit-frame-pointer"
REPORTS=build/reports
REF=$REPORTS/variant-O0.txt
fail=0

mkdir -p "$REPORTS" build/variants
if ! make -s test CC="$CC" > "$REF" 2>&1; then
    echo "변형: 기준 (-O0)의 test가 실패했다"
    exit 1
fi

run_variant() {
    name=$1
    flags=$2
    cc=${3:-$CC}
    dir=build/variants/$name
    out=$REPORTS/variant-$name.txt
    rm -rf "$dir"
    mkdir -p "$dir"
    cp -R src sim test intro tools Makefile "$dir/"
    if ! (cd "$dir" && make -s test CC="$cc" CFLAGS="$BASE $flags") > "$out" 2>&1; then
        echo "변형 $name: test가 실패했다 (보고서: $out)"
        fail=1
        return
    fi
    if cmp -s "$REF" "$out"; then
        echo "변형 $name: test의 출력이 -O0과 한 줄도 다르지 않다"
    else
        echo "변형 $name: test는 통과했지만 출력이 -O0과 다르다 (보고서: $out)"
        fail=1
    fi
}

run_variant O2 "-O2"
run_variant Os "-Os"

# 다른 compiler. coverage를 재는 GCC를 여기에서도 쓴다
if [ -n "$GCC" ]; then
    run_variant gcc-O0 "-O0" "$GCC"
    run_variant gcc-O2 "-O2" "$GCC"
else
    echo "건너뜀: GCC의 변형 (GCC 14 이상이 없다)"
    echo "GCC의 변형" >> build/skipped
fi

# sanitizer가 이 compiler에 있는지 작은 프로그램으로 먼저 본다
probe=build/variants/probe
printf 'int main(void) { return 0; }\n' > "$probe.c"
if "$CC" $SAN -o "$probe" "$probe.c" > /dev/null 2>&1 && "$probe"; then
    run_variant sanitizer "$SAN"
else
    echo "건너뜀: sanitizer (이 compiler에는 없다)"
    echo "sanitizer" >> build/skipped
fi

exit "$fail"
