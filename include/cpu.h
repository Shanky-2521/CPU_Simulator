#ifndef CPU_H
#define CPU_H

#include <stdint.h>
#include <stdbool.h>

#define REGISTER_COUNT 8
#define MEMORY_SIZE 4096
#define WORD_SIZE 32

// CPU Flags
typedef enum {
    // Basic Status Flags
    FLAG_ZERO = 0,           // Set when result is zero
    FLAG_NEGATIVE = 1,       // Set when result is negative
    FLAG_CARRY = 2,          // Set during unsigned overflow
    FLAG_OVERFLOW = 3,       // Set during signed overflow

    // Signed Integer Flags
    FLAG_SIGNED_POSITIVE = 4,    // Set for positive signed integers
    FLAG_SIGNED_NEGATIVE = 5,    // Set for negative signed integers
    FLAG_SIGNED_ZERO = 6,        // Set for signed zero

    // Unsigned Integer Flags
    FLAG_UNSIGNED_MAX = 7,       // Set when unsigned value reaches maximum
    FLAG_UNSIGNED_MIN = 8,       // Set when unsigned value reaches minimum

    // Comparison Flags
    FLAG_EQUAL = 9,              // Set when two values are equal
    FLAG_GREATER = 10,           // Set when first value is greater
    FLAG_LESS = 11,              // Set when first value is less

    // Arithmetic Operation Flags
    FLAG_DIV_BY_ZERO = 12,       // Set during division by zero
    FLAG_EVEN = 13,              // Set for even numbers
    FLAG_ODD = 14,               // Set for odd numbers

    // System Flags
    FLAG_INTERRUPT = 15          // Interrupt flag
} CPUFlags;

// Instruction Opcodes
typedef enum {
    // Arithmetic Operations
    OP_ADD = 0x01,
    OP_SUB = 0x02,
    OP_MUL = 0x03,
    OP_DIV = 0x04,

    // Logical Operations
    OP_AND = 0x10,
    OP_OR  = 0x11,
    OP_XOR = 0x12,
    OP_NOT = 0x13,

    // Data Movement
    OP_LOAD = 0x20,
    OP_STORE = 0x21,
    OP_MOVE = 0x22,

    // Control Flow
    OP_JUMP = 0x30,
    OP_BRANCH = 0x31,
    OP_CALL = 0x32,
    OP_RETURN = 0x33,

    // System Operations
    OP_HALT = 0xFF
} Opcodes;

// CPU Structure with Enhanced Design
typedef struct {
    // General Purpose Registers
    int32_t registers[REGISTER_COUNT];  // R0-R7 registers

    // Special Purpose Registers
    uint32_t program_counter;  // Program Counter
    uint32_t stack_pointer;    // Stack Pointer

    // Status Flags
    bool flags[16];  // Expanded flags for comprehensive condition tracking

    // Memory
    uint8_t memory[MEMORY_SIZE];  // Main memory

    // Instruction Register
    uint32_t instruction_register;

    // Halt Flag
    bool halted;

    // Integer Mode
    enum {
        MODE_SIGNED,
        MODE_UNSIGNED
    } integer_mode;
} CPU;

// Function prototypes

/**
 * Initializes the CPU structure.
 * - Clears all registers.
 * - Sets PC to the start of the code segment.
 * - Sets SP to the top of the stack segment.
 * - Sets heap_pointer to the start of the heap.
 */
void init_cpu(CPU *cpu);

/**
 * Resets the CPU state.
 * - Clears all registers.
 * - Resets PC and SP to their initial values.
 * - Clears the memory array.
 */
void reset_cpu(CPU *cpu);

/**
 * Displays the current state of the CPU.
 * - Prints registers, flags, and PC.
 */
// void display_cpu_state(const CPU *cpu);

/**
 * Executes the fetch-decode-execute loop.
 * - Fetches instructions from memory.
 * - Decodes and executes them.
 * - Handles HALT instructions gracefully.
 */
void run_cpu(CPU *cpu);


int compile_c_file(const char *c_file);


#endif // CPU_H
