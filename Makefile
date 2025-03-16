
# Compiler
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -I$(SRC_DIR) -ITest
AR = ar
ARFLAGS = rcs

# Directories
SRC_DIR := Collections
BUILD_DIR := .target/build
TEST_DIR := Tests
TEST_BIN_DIR := .target/test_bin

# Static Library Name
LIB_NAME := libcollections.a
LIB_PATH := $(BUILD_DIR)/$(LIB_NAME)

# Source Files
SRCS := $(shell find $(SRC_DIR) -type f -name "*.c" ! -path '*/.*')
OBJS := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

# Test Files
TEST_SRCS := $(shell find $(TEST_DIR) -type f -name "*.c" ! -path '*/.*')
TEST_BINS := $(patsubst $(TEST_DIR)/%.c, $(TEST_BIN_DIR)/%, $(TEST_SRCS))

# Default target
all: build_collection build_test
	@echo "✅ Build Completed Successfully!"

# Compile and archive static library
build_collection: $(LIB_PATH)

$(LIB_PATH): $(OBJS)
	@echo "🔧 Archiving static library..."
	@$(AR) $(ARFLAGS) $@ $^ && echo "✅ Library archived successfully!" || (echo "❌ Library archiving failed!" && exit 1)

# Compile source files to object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | build_dirs
	@$(CC) $(CFLAGS) -c $< -o $@ && echo "✔️  Compiled $<" || (echo "❌ Compilation failed: $<" && exit 1)

# Create build directories
build_dirs:
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(shell find $(SRC_DIR) -type d ! -path '*/.*' | sed "s|^$(SRC_DIR)|$(BUILD_DIR)|")

# Compile tests and link with static library
build_test: $(TEST_BINS)

$(TEST_BIN_DIR)/%: $(TEST_DIR)/%.c $(LIB_PATH) | test_dirs
	@$(CC) $(CFLAGS) $< -L$(BUILD_DIR) -lcollections -o $@ && echo "✔️  Built test: $@" || (echo "❌ Test build failed: $@" && exit 1) 

# Create test directories
test_dirs:
	@mkdir -p $(TEST_BIN_DIR)
	@mkdir -p $(shell find $(TEST_DIR) -type d ! -path '*/.*' | sed "s|^$(TEST_DIR)|$(TEST_BIN_DIR)|")



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
	@rm -rf $(BUILD_DIR) $(TEST_BIN_DIR) && echo "🧹 Cleaned build files!"

clean_bin:
	@$(MAKE) -C $(BIN_BUILD_DIR) clean --silent