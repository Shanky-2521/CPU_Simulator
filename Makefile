# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -I./include -g
LDFLAGS =

SRC_DIR = src
BUILD_DIR = build
INCLUDE_DIR = include
PROGRAMS_DIR = programs

SRCS = $(wildcard $(SRC_DIR)/*.c)
ASMS = $(wildcard $(SRC_DIR)/*.s)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
ASMOBJS = $(ASMS:$(SRC_DIR)/%.s=$(BUILD_DIR)/%.o)

TARGET = cpu_simulator

# Main simulator target
all: $(BUILD_DIR)/$(TARGET)

# Sample programs
SAMPLE_PROGRAMS = factorial_recursive

# Simulator executable
$(BUILD_DIR)/$(TARGET): $(OBJS) $(ASMOBJS)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(LDFLAGS) -o $@ $^

# Object file compilation rule
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Assembler file compilation rule
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.s
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Sample program compilation
$(PROGRAMS_DIR)/%.out: $(PROGRAMS_DIR)/%.c
	$(CC) $(CFLAGS) $< -o $@

# Compile all sample programs
programs: $(SAMPLE_PROGRAMS:%=$(PROGRAMS_DIR)/%.out)

# Run simulator
run: $(BUILD_DIR)/$(TARGET)
	./$(BUILD_DIR)/$(TARGET)

# Run sample programs
run_factorial: $(PROGRAMS_DIR)/factorial_recursive.out
	./$(PROGRAMS_DIR)/factorial_recursive.out

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR) $(PROGRAMS_DIR)/*.out

# Phony targets
.PHONY: all clean run programs run_factorial

# Test target (optional)
test:
	$(CC) $(CFLAGS) -o $(BUILD_DIR)/test_runner test/*.c $(SRCS)
	$(BUILD_DIR)/test_runner

# Debugging build
debug: CFLAGS += -DDEBUG -fsanitize=address
debug: all

# Run target for convenience
run: $(BIN)
	$(BIN) programs/bin/sample_program.bin
