
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -ICollections
MAIN = runner.c

# Gather source files from dep/
SRC := $(wildcard dep/*.c)

# Convert source files to object files inside ./bin/
OBJS := $(patsubst dep/%.c, bin/%.o, $(SRC))

OS := $(shell uname -s)

# Determine executable extension
ifeq ($(OS),Windows_NT)
    EXE_EXT := .exe
else
    EXE_EXT :=  # No extension for Unix-based systems (Linux, macOS)
endif

# Target: Build everything
all: bin test_exe

# Create bin directory if it doesn't exist
bin:
	mkdir -p bin

# Compile object files and place them in ./bin/
bin/%.o: dep/%.c | bin
	$(CC) $(CFLAGS) -c $< -o $@

# Link the final executable
test_exe: $(OBJS)
	$(CC) $(CFLAGS) -o ../test_exe$(EXE_EXT) $(OBJS) $(MAIN)





# Clean generated files
clean:
	@rm -rf bin
	@rm -f ../test_exe

print:
	@echo $(FILES)




