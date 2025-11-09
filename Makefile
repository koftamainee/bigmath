# === CONFIGURATION ===
TARGET := libbigmath.a

BUILD_TYPE ?= Release
GENERATOR ?= Ninja
BUILD_DIR := build
TARGET_DIR := target
CMAKE_CMD := cmake
DEBUGGER_CMD := pwndbg
ARGS := # Extra args for example/test runs

EXAMPLE := factorial
TEST := test_basic

ifeq ($(V),1)
	Q :=
else
	Q := @
endif

.PHONY: all configure build clean cleanbuild debug release examples run_example tests run_tests pwn valgrind analyze analyze_fix help

# === DEFAULT TARGET ===
all: build

# === CMAKE CONFIGURATION ===
configure:
	$(Q)echo "Configuring project for $(BUILD_TYPE) build [$(GENERATOR)]..."
	$(Q)mkdir -p "$(BUILD_DIR)/$(BUILD_TYPE)"
	$(Q)$(CMAKE_CMD) -S . -B "$(BUILD_DIR)/$(BUILD_TYPE)" \
		-G "$(GENERATOR)" \
		-DCMAKE_BUILD_TYPE=$(BUILD_TYPE) \
		-DCMAKE_EXPORT_COMPILE_COMMANDS=ON \
		-DCMAKE_ARCHIVE_OUTPUT_DIRECTORY=$(abspath $(TARGET_DIR)) \
		-DCMAKE_LIBRARY_OUTPUT_DIRECTORY=$(abspath $(TARGET_DIR)) \
		-DCMAKE_RUNTIME_OUTPUT_DIRECTORY=$(abspath $(TARGET_DIR))
	$(Q)ln -sf "$(BUILD_DIR)/$(BUILD_TYPE)/compile_commands.json" compile_commands.json

# === BUILD TARGETS ===
build: configure
	$(Q)echo "Building project ($(BUILD_TYPE))..."
	$(Q)$(CMAKE_CMD) --build "$(BUILD_DIR)/$(BUILD_TYPE)"

examples: build
	$(Q)$(CMAKE_CMD) --build "$(BUILD_DIR)/$(BUILD_TYPE)" --target $(EXAMPLE)

tests: build
	$(Q)$(CMAKE_CMD) --build "$(BUILD_DIR)/$(BUILD_TYPE)" --target $(TEST)

# === CLEAN ===
clean:
	$(Q)echo "Cleaning build artifacts..."
	$(Q)rm -rf "$(BUILD_DIR)" "$(TARGET_DIR)" compile_commands.json

cleanbuild: clean build

# === BUILD VARIANTS ===
debug:
	$(Q)$(MAKE) BUILD_TYPE=Debug build

release:
	$(Q)$(MAKE) BUILD_TYPE=Release build

# === RUNNING ===
run_example: debug
	$(Q)echo "Running example: $(EXAMPLE)"
	$(Q)echo "--------------------------------"
	$(Q)"$(TARGET_DIR)/$(EXAMPLE)" $(ARGS)

run_tests: debug
	$(Q)echo "Running tests..."
	$(Q)echo "--------------------------------"
	$(Q)"$(TARGET_DIR)/$(TEST)" $(ARGS)

# === DEBUGGING ===
pwn: debug
	$(Q)echo "Starting pwndbg session..."
	$(Q)echo "--------------------------------"
	$(Q)$(DEBUGGER_CMD) "$(TARGET_DIR)/$(EXAMPLE)"

valgrind: debug
	$(Q)echo "Running under Valgrind..."
	$(Q)echo "--------------------------------"
	$(Q)valgrind --leak-check=full --show-leak-kinds=all \
		--track-origins=yes --error-exitcode=1 \
		"$(TARGET_DIR)/$(EXAMPLE)" $(ARGS)

# === STATIC ANALYSIS ===
analyze: build
	$(Q)echo "Running clang-tidy analysis..."
	$(Q)find src include -type f \( -name '*.c' -o -name '*.h' \) \
		| xargs clang-tidy -p "$(BUILD_DIR)/$(BUILD_TYPE)"

analyze_fix: build
	$(Q)echo "Running clang-tidy with auto-fix..."
	$(Q)find src include -type f \( -name '*.c' -o -name '*.h' \) \
		| xargs clang-tidy -p "$(BUILD_DIR)/$(BUILD_TYPE)" --fix

# === HELP ===
help:
	$(Q)echo "bigmath Build System"
	$(Q)echo "Targets:"
	$(Q)echo "  all           - Default build (Release)"
	$(Q)echo "  build         - Build project (BUILD_TYPE=Release)"
	$(Q)echo "  debug         - Build Debug version"
	$(Q)echo "  release       - Build Release version"
	$(Q)echo "  examples      - Build example programs"
	$(Q)echo "  run_example   - Run example binary (ARGS=...)"
	$(Q)echo "  tests         - Build test binaries"
	$(Q)echo "  run_tests     - Run tests"
	$(Q)echo "  pwn           - Debug example with pwndbg"
	$(Q)echo "  valgrind      - Run example under Valgrind"
	$(Q)echo "  analyze       - Static analysis with clang-tidy"
	$(Q)echo "  analyze_fix   - clang-tidy auto-fix mode"
	$(Q)echo "  clean         - Remove build artifacts"
	$(Q)echo "  cleanbuild    - Clean then rebuild"
	$(Q)echo "  help          - Show this message"
	$(Q)echo ""
	$(Q)echo "Variables:"
	$(Q)echo "  BUILD_TYPE    - Debug/Release (default: Release)"
	$(Q)echo "  GENERATOR     - CMake generator (default: Ninja)"
	$(Q)echo "  V=1           - Verbose output"
	$(Q)echo "  ARGS          - Arguments for example/test run"
