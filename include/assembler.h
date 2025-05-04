// Custom Assembly Language Specification

#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <stdint.h>

// Instruction Opcodes
typedef enum {
    // Arithmetic Operations
    OP_ADD = 0x01,      // Add two registers
    OP_SUB = 0x02,      // Subtract two registers
    OP_MUL = 0x03,      // Multiply two registers
    OP_DIV = 0x04,      // Divide two registers

    // Logical Operations
    OP_AND = 0x10,      // Bitwise AND
    OP_OR  = 0x11,      // Bitwise OR
    OP_XOR = 0x12,      // Bitwise XOR
    OP_NOT = 0x13,      // Bitwise NOT

    // Data Movement
    OP_MOV = 0x20,      // Move value between registers
    OP_LOAD = 0x21,     // Load value from memory
    OP_STORE = 0x22,    // Store value to memory

    // Control Flow
    OP_JMP = 0x30,      // Unconditional jump
    OP_JZ = 0x31,       // Jump if zero
    OP_JNZ = 0x32,      // Jump if not zero
    OP_CALL = 0x33,     // Function call
    OP_RET = 0x34,      // Return from function

    // Stack Operations
    OP_PUSH = 0x40,     // Push to stack
    OP_POP = 0x41,      // Pop from stack

    // Comparison
    OP_CMP = 0x50,      // Compare two registers

    // Halt
    OP_HALT = 0xFF      // Halt execution
} Opcode;

// Instruction Structure
typedef struct {
    Opcode opcode;      // Operation to perform
    uint8_t dest_reg;   // Destination register
    uint8_t src_reg1;   // First source register
    uint8_t src_reg2;   // Second source register or immediate value
    int32_t immediate;  // Immediate value for certain instructions
} Instruction;

// Assembler Function Prototypes
int assemble_program(const char *source_file, const char *output_file);
void load_program_to_memory(CPU *cpu, const char *object_file);
void execute_program(CPU *cpu);

#endif // ASSEMBLER_H
