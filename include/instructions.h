#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include <stdint.h>
#include "cpu.h"
#include "alu.h"
#include "memory.h"

// Define opcodes for the instruction set
typedef enum {
    ADD,       // 0x00
    SUB,       // 0x01
    MUL,       // 0x02
    DIV,       // 0x03
    AND,       // 0x04
    OR,        // 0x05
    XOR,       // 0x06
    NOT,       // 0x07
    SHL,       // 0x08
    SHR,       // 0x09
    EQ,        // 0x0A
    NEQ,       // 0x0B
    GT,        // 0x0C
    LT,        // 0x0D
    GE,        // 0x0E
    LE,        // 0x0F
    LOAD,      // 0x10
    STORE,     // 0x11
    JUMP,      // 0x12
    JZ,        // 0x13
    JNZ,       // 0x14
    CALL,      // 0x15
    RET,       // 0x16
    PUSH,      // 0x17
    POP,       // 0x18
    HALT       // 0x19
} Opcode;

// Define instruction structure
typedef struct {
    Opcode opcode;        // Operation code
    uint32_t operands[3]; // Up to 3 operands
} Instruction;

// Function Prototypes

/**
 * Decodes a 32-bit binary instruction into an Instruction struct.
 * @param raw - The 32-bit binary instruction.
 * @return Decoded instruction.
 */
// Removed function declaration

/**
 * Executes a given instruction on the CPU.
 * @param cpu - Pointer to the CPU structure.
 * @param instruction - Instruction to execute.
 */
// Removed function declaration

/**
 * Displays the decoded instruction for debugging purposes.
 * @param instruction - Instruction to display.
 */
// Removed function declaration

#endif // INSTRUCTIONS_H
