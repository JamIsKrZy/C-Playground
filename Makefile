
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

# Find all test files in Tests/
TEST_SRCS := $(shell find $(TEST_DIR) -type f -name "*.c" ! -name ".*")
TEST_BINS := $(patsubst $(TEST_DIR)/%.c, $(TEST_BIN_DIR)/%, $(TEST_SRCS))

# Default target
all: build_collection $(OBJS) build_test $(TEST_BINS)

# Ensure build directories exist before compilation
build_collection:
	mkdir -p $(BUILD_DIR)
	mkdir -p $(shell find $(SRC_DIR) -type d | sed "s|^$(SRC_DIR)|$(BUILD_DIR)|")

# Compile each .c file to corresponding .o inside build directory
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | build_collection
	$(CC) $(CFLAGS) -c $< -o $@

# Create test_bin directory and its subdirectories
build_test:
	mkdir -p $(TEST_BIN_DIR)
	mkdir -p $(shell find $(TEST_DIR) -type d | sed "s|^$(TEST_DIR)|$(TEST_BIN_DIR)|")

# Compile each test file separately, linking with object files
$(TEST_BIN_DIR)/%: $(TEST_DIR)/%.c $(OBJS) | build_test
	$(CC) $(CFLAGS) $< $(OBJS) -o $@



# Running the Test
EXE_RUNNER = ./bin/test_exe
run: clean clean_bin all build_bin
	$(EXE_RUNNER)

test: 
	$(EXE_RUNNER)



# Build bin executables 
BIN_BUILD_DIR = bin/TestRunner 
build_bin:
	$(MAKE) -C $(BIN_BUILD_DIR)


# Clean compiled files - within .target
clean:
	@rm -rf $(BUILD_DIR) $(TEST_BIN_DIR)

clean_bin:
	@$(MAKE) -C $(BIN_BUILD_DIR) clean --silent