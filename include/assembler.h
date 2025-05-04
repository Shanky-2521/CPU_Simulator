// Custom Assembly Language Specification

#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <stdint.h>

#include "cpu.h"

// Instruction Structure
typedef struct {
    Opcodes opcode;      // Operation to perform
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
