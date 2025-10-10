# === TARGETS ===
LIB_NAME := bigmath
BUILD_DIR := build
TARGET_DIR := target
EXAMPLES_DIR := examples
TESTS_DIR := tests

CC := gcc
CFLAGS := -O3 -Wall -Wextra -Iinclude -march=native
LDFLAGS :=

# Recursively collect all .c files
SRC := $(shell find src -name '*.c')
OBJ := $(patsubst src/%.c,$(BUILD_DIR)/%.o,$(SRC))

.PHONY: all clean build lib examples tests run_example help

# === DEFAULT TARGET ===
all: build

# === BUILD LIBRARY ===
build: $(BUILD_DIR)/lib$(LIB_NAME).a

$(BUILD_DIR)/lib$(LIB_NAME).a: $(OBJ)
	@mkdir -p $(TARGET_DIR)
	ar rcs $@ $^

# Compile each .c file to corresponding build/.o preserving subdirs
$(BUILD_DIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# === EXAMPLES ===
examples: $(EXAMPLES_DIR)/factorial

$(EXAMPLES_DIR)/factorial: $(EXAMPLES_DIR)/factorial.c $(BUILD_DIR)/lib$(LIB_NAME).a
	@mkdir -p $(TARGET_DIR)
	$(CC) $(CFLAGS) $< $(BUILD_DIR)/lib$(LIB_NAME).a -o $(TARGET_DIR)/factorial

run_example: examples
	@echo "Running factorial example..."
	$(TARGET_DIR)/factorial

# === TESTS ===
tests: $(TESTS_DIR)/test_basic

$(TESTS_DIR)/test_basic: $(TESTS_DIR)/test_basic.c $(BUILD_DIR)/lib$(LIB_NAME).a
	@mkdir -p $(TARGET_DIR)
	$(CC) $(CFLAGS) $< $(BUILD_DIR)/lib$(LIB_NAME).a -o $(TARGET_DIR)/test_basic

run_tests: tests
	@echo "Running tests..."
	$(TARGET_DIR)/test_basic

# === CLEAN ===
clean:
	rm -rf $(BUILD_DIR) $(TARGET_DIR)

# === HELP ===
help:
	@echo "bigmath Makefile"
	@echo "Targets:"
	@echo "  all           - Build library and examples"
	@echo "  build         - Build lib$(LIB_NAME).a"
	@echo "  examples      - Build example programs"
	@echo "  run_example   - Run factorial example"
	@echo "  tests         - Build tests"
	@echo "  run_tests     - Run all tests"
	@echo "  clean         - Remove build artifacts"
