# compiler and flags
# -I specifies the path for the header files
CC = gcc
CFLAGS = -Wall -Werror -Iinclude

# automatically detect all source and object files
SRC = $(wildcard src/*.c)
OBJ = $(SRC:src/%.c=build/%.o)

# output binary
TARGET = build/lox

# Rule syntax
# target: dependecy
# <tab> command

# default target
all: $(TARGET)

# Pattern rule to compile .c file to .o files
# $@ refers to current target
# $< refers to first dependecy
# $^ refers to all dependencies
build/%.o: src/%.c
	mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

# build target
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

# run the compiler
run: $(TARGET)
	./$(TARGET)

# clean up the generated files
clean:
	rm -rf build

.PHONY: all clean run
