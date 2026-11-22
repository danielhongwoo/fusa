# 책의 예제다. 실제 제품에 쓸 수 없다.
#
#   make check     빌드, test, 추적 검사, 정적 분석, coverage, 증명을 차례로 돌린다
#   make test      빌드와 test만
#   make intro     1장의 실행 예: 안전 장치가 없는 제어기와 예제의 제어기를 같은 고장에서 견준다
#   make mutation  제품 코드에 결함을 하나씩 넣어 test가 잡는지 본다
#   make clean     build 폴더를 지운다
#
# 도구가 없으면 그 단계를 건너뛰고 "건너뜀"이라고 찍는다.
# make check STRICT=1 로 돌리면 건너뛴 단계가 있을 때 실패한다.
# 구현 예정 (status: planned)인 요구사항이 남아 있을 때도 실패한다.
# 이 도구들은 어느 것도 qualification되지 않았다.

CC      ?= cc
CFLAGS  := -std=c11 -Wall -Wextra -Werror -pedantic -O0 -g
INC     := -Isrc/common -Isrc/hal -Isrc/input -Isrc/app -Isrc/monitor -Isrc/reaction -Isrc/com -Isrc/flow -Isrc/vcu -Isim -Itest -Itest/faulty

# 제품 코드 (item의 소프트웨어)
# 하드웨어를 부르지 않는 부분과 부르는 부분을 나눈다. unit test는 앞의 것만 link한다
SRC_LOGIC  := src/input/pedal_check.c src/input/brake_check.c src/input/gear_check.c src/monitor/monitor.c src/monitor/inverter_check.c src/reaction/reaction.c src/com/e2e.c src/flow/flow.c
SRC_IO     := src/input/input.c src/vcu/vcu.c
SRC_SAFETY := $(SRC_LOGIC) $(SRC_IO)
SRC_APP    := src/app/app.c
SRC        := $(SRC_SAFETY) $(SRC_APP)
# 시뮬레이션 (item의 밖)
SIM        := sim/plant.c sim/frame_sim.c sim/hal_sim.c sim/scenario.c
TESTLIB    := test/test_run.c

# MC/DC를 재려면 GCC 14 이상이 필요하다
GCC  := $(shell for c in gcc-16 gcc-15 gcc-14; do if command -v $$c >/dev/null 2>&1; then echo $$c; break; fi; done)
GCOV := $(subst gcc,gcov,$(GCC))
CPPCHECK   := $(shell command -v cppcheck 2>/dev/null)
CLANG_TIDY := $(shell command -v clang-tidy 2>/dev/null || ls /opt/homebrew/opt/llvm/bin/clang-tidy 2>/dev/null)
CBMC       := $(shell command -v cbmc 2>/dev/null)

.PHONY: check test intro intro-figure trace static coverage prove mutation clean dirs skipped

check: test intro trace static coverage prove skipped
	@echo "make check: 끝"

dirs:
	@mkdir -p build/out build/reports build/cov
	@: > build/skipped

# ---- 빌드와 test ----

build/test_unit: $(SRC_LOGIC) $(SRC_APP) $(TESTLIB) test/test_unit.c | dirs
	$(CC) $(CFLAGS) $(INC) -o $@ $^ -lm

build/test_scenario: $(SRC) $(SIM) $(TESTLIB) test/test_scenario.c | dirs
	$(CC) $(CFLAGS) $(INC) -o $@ $^ -lm

# 기능 모듈을 결함이 있는 것으로 바꿔 끼운다.
# 정상인 기능은 소스를 고치지 않고 함수 이름만 바꿔 compile한다.
build/app_good.o: $(SRC_APP) | dirs
	$(CC) $(CFLAGS) $(INC) -Dapp_init=app_good_init -Dapp_step=app_good_step -c -o $@ $<

build/test_fault_app: $(SRC_SAFETY) build/app_good.o test/faulty/app_fault.c $(SIM) $(TESTLIB) test/test_fault_app.c | dirs
	$(CC) $(CFLAGS) $(INC) -o $@ $^ -lm

# 대조: 감시와 출력 단계를 아무것도 하지 않는 모듈로 바꿔 끼운다
build/test_no_monitor: src/input/pedal_check.c src/input/brake_check.c src/input/gear_check.c src/input/input.c src/monitor/inverter_check.c src/reaction/reaction.c src/com/e2e.c src/flow/flow.c src/vcu/vcu.c build/app_good.o test/faulty/app_fault.c test/faulty/monitor_none.c $(SIM) $(TESTLIB) test/test_no_monitor.c | dirs
	$(CC) $(CFLAGS) $(INC) -o $@ $^ -lm

# 대조: 방향의 판정을 하지 않는 모듈로 바꿔 끼운다
build/test_no_gear_check: $(filter-out src/input/gear_check.c,$(SRC)) test/faulty/gear_none.c $(SIM) $(TESTLIB) test/test_no_gear_check.c | dirs
	$(CC) $(CFLAGS) $(INC) -o $@ $^ -lm

# 대조: inverter가 알린 토크를 검사하지 않는 모듈로 바꿔 끼운다
build/test_no_inverter_check: $(filter-out src/monitor/inverter_check.c,$(SRC)) test/faulty/inverter_check_none.c $(SIM) $(TESTLIB) test/test_no_inverter_check.c | dirs
	$(CC) $(CFLAGS) $(INC) -o $@ $^ -lm

# 대조: 실행의 순서를 보지 않고 늘 옳은 답을 내는 모듈로 바꿔 끼운다
build/test_no_flow_check: $(filter-out src/flow/flow.c,$(SRC)) test/faulty/flow_none.c $(SIM) $(TESTLIB) test/test_no_flow_check.c | dirs
	$(CC) $(CFLAGS) $(INC) -o $@ $^ -lm

test: build/test_unit build/test_scenario build/test_fault_app build/test_no_monitor build/test_no_gear_check build/test_no_inverter_check build/test_no_flow_check
	@echo "== unit test"
	@build/test_unit
	@echo "== 시나리오 test (fault는 HAL의 뒤에서 넣는다)"
	@build/test_scenario
	@echo "== 기능의 고장을 넣는 test (모듈을 바꿔 끼운다)"
	@build/test_fault_app
	@echo "== 대조 test (감시를 뺀다)"
	@build/test_no_monitor
	@echo "== 대조 test (방향의 판정을 뺀다)"
	@build/test_no_gear_check
	@echo "== 대조 test (inverter가 알린 토크의 검사를 뺀다)"
	@build/test_no_inverter_check
	@echo "== 대조 test (실행의 확인을 뺀다)"
	@build/test_no_flow_check

# ---- 1장의 실행 예 ----
# 같은 시나리오를 안전 장치가 없는 제어기와 예제의 제어기로 돌린다.
# 어느 제어기인지는 link할 때 정해진다

# 단순한 제어기는 보호가 없는 토크 요구를 보낸다. 그 함수는 제품의 HAL에 없고 sim의 header에만 있다.
# 그 제어기의 소스 (1장에 실린 그대로)를 고치지 않으려고 header를 compiler의 option으로 넣는다
build/intro_naive: intro/naive_vcu.c $(SIM) intro/demo.c | dirs
	$(CC) $(CFLAGS) $(INC) -include sim/hal_sim.h -o $@ $^ -lm

build/intro_vcu: $(SRC) $(SIM) intro/demo.c | dirs
	$(CC) $(CFLAGS) $(INC) -o $@ $^ -lm

intro: build/intro_naive build/intro_vcu
	@echo "== 1장의 실행 예 (페달 센서의 고착)"
	@build/intro_naive naive build/out/intro-naive.csv
	@build/intro_vcu vcu build/out/intro-vcu.csv

# 책의 그림을 다시 만든다 (figures/ch01-stuck-pedal.svg)
intro-figure: intro
	@python3 tools/plot_intro.py build/out/intro-naive.csv build/out/intro-vcu.csv ../../figures/ch01-stuck-pedal.svg

# ---- 추적 ----

trace: | dirs
	@echo "== 추적 검사"
	@python3 tools/trace.py $(if $(filter 1,$(STRICT)),--strict) > build/reports/trace.txt; status=$$?; cat build/reports/trace.txt; exit $$status

# ---- 정적 분석 ----

static: | dirs
	@echo "== 정적 분석"
ifneq ($(CPPCHECK),)
	@$(CPPCHECK) --std=c11 --enable=warning,style,performance,portability --inline-suppr \
		--suppress=missingIncludeSystem --error-exitcode=1 -q $(INC) src > build/reports/cppcheck.txt 2>&1; \
		status=$$?; cat build/reports/cppcheck.txt; \
		if [ $$status -ne 0 ]; then exit $$status; fi; echo "cppcheck: 지적 없음"
else
	@echo "건너뜀: cppcheck가 없다" | tee -a build/skipped
endif
ifneq ($(CLANG_TIDY),)
	@$(CLANG_TIDY) $(SRC) --quiet --checks='-*,bugprone-*,cert-*,clang-analyzer-*,-bugprone-easily-swappable-parameters' \
		-- $(CFLAGS) $(INC) > build/reports/clang-tidy.txt 2>&1 || true
	@echo "clang-tidy: 경고 $$(grep -c 'warning:' build/reports/clang-tidy.txt) 개 (보고서: build/reports/clang-tidy.txt)"
else
	@echo "건너뜀: clang-tidy가 없다" | tee -a build/skipped
endif

# ---- coverage ----

coverage: | dirs
	@echo "== coverage (statement, branch, MC/DC)"
ifneq ($(GCC),)
	@sh tools/coverage.sh "$(GCC)" "$(GCOV)" "$(CFLAGS)"
else
	@echo "건너뜀: GCC 14 이상이 없다" | tee -a build/skipped
endif

# ---- 증명 ----

prove: | dirs
	@echo "== 증명 (CBMC)"
ifneq ($(CBMC),)
	@sh tools/prove.sh
else
	@echo "건너뜀: cbmc가 없다" | tee -a build/skipped
endif

# test가 결함을 잡는지 본다. 시간이 걸려서 check에는 넣지 않았다
mutation:
	@python3 tools/mutation_check.py

skipped:
	@if [ -s build/skipped ]; then echo "건너뛴 단계가 있다:"; cat build/skipped; \
		if [ "$(STRICT)" = "1" ]; then exit 1; fi; fi

clean:
	rm -rf build
