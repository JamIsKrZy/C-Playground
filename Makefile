


# Compiler
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -ICollections -ITest

# Directories
SRC_DIR := Collections
BUILD_DIR := .target/build
TEST_DIR := Tests
TEST_BIN_DIR := .target/test_bin

# Find all .c files recursively in Collections (excluding test files)
SRCS := $(shell find $(SRC_DIR) -type f -name "*.c")
OBJS := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

# Find all test files in Test/
TEST_SRCS := $(shell find $(TEST_DIR) -type f -name "*.c" ! -name ".*")
TEST_BINS := $(patsubst $(TEST_DIR)/%.c, $(TEST_BIN_DIR)/%, $(TEST_SRCS))

# Default target
all: create_bin $(OBJS) create_test_bin $(TEST_BINS)




# Create necessary bin subdirectories
create_bin:
	mkdir -p $(shell find $(SRC_DIR) -type d | sed "s|^$(SRC_DIR)|$(BUILD_DIR)|")

# Compile each .c file to corresponding .o inside build directory
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	-$(CC) $(CFLAGS) -c $< -o $@

# Create test_bin directory and its subdirectories
create_test_bin:
	mkdir -p $(shell find $(TEST_DIR) -type d | sed "s|^$(TEST_DIR)|$(TEST_BIN_DIR)|")

# Compile each test file separately, linking with object files
$(TEST_BIN_DIR)/%: $(TEST_DIR)/%.c $(OBJS) | create_test_bin
	$(CC) $(CFLAGS) $< $(OBJS) -o $@








# Build bin executables 
BIN_BUILD_DIR = bin/TestRunner 
build_bin:
	$(MAKE) -C $(BIN_BUILD_DIR)




# Running the Test
EXE_RUNNER = ./bin/test_exe
run:
	$(EXE_RUNNER)

# Clean compiled files
clean:
	rm -rf $(BUILD_DIR) $(TEST_BIN_DIR)
	$(MAKE) -C $(BIN_BUILD_DIR) clean