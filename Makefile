


# Compiler
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -ICollections

# Directories
SRC_DIR := Collections
BUILD_DIR := build

# Find all .c files recursively
SRCS := $(shell find $(SRC_DIR) -type f -name "*.c")
OBJS := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

# Default target
all: create_bin $(OBJS)

# Create necessary bin subdirectories
create_bin:
	mkdir -p $(shell find $(SRC_DIR) -type d | sed "s|^$(SRC_DIR)|$(BUILD_DIR)|")

# Compile each .c file to corresponding .o inside bin
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	-$(CC) $(CFLAGS) -c $< -o $@

compile_one:
	$(eval SRC_FILE := $(wildcard $(SRC_DIR)/**/$(file)))  # Find the file path
	$(if $(SRC_FILE), \
		$(CC) $(CFLAGS) -c $(SRC_FILE) -o $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC_FILE)), \
		$(error File '$(file)' not found in $(SRC_DIR)) \
	)







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
	rm -rf $(BUILD_DIR)
	$(MAKE) -C $(BIN_BUILD_DIR) clean