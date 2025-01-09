# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -g

# Automatically detect all source and object files
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

# Ouput Binary
TARGET = lox

# Default target
all = $(TARGET)

# Rule syntax
# target: dependecy
# <tab> command

# Build target
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)
	rm -f $(OBJS)

# Pattern rule to compile .c file to .o files
# $@ refers to current target
# $< refers to first dependecy
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Run the program
run: $(TARGET)
	./$(TARGET)

# Clean up the generated files
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean run