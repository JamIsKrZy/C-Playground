


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







OS := $(shell uname -s)

# Determine executable extension
ifeq ($(OS),Windows_NT)
    EXE_EXT := .exe
else
    EXE_EXT :=  # No extension for Unix-based systems (Linux, macOS)
endif


# Location to put executable
EXE_DIR = ./bin/
TESTRUNNER = test$(EXE_EXT) 


exe:
	gcc -o $(EXE_DIR)$(TESTRUNNER) ./bin/TestRunner/fildir.c







# Clean compiled files
clean:
	rm -rf $(BUILD_DIR)