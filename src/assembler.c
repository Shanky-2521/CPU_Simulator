#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "assembler.h"
#include "cpu.h"
#include "alu.h"

// Simple Assembler Implementation
int assemble_program(const char *source_file, const char *output_file) {
    FILE *src = fopen(source_file, "r");
    FILE *obj = fopen(output_file, "wb");
    
    if (!src || !obj) {
        perror("Error opening files");
        return -1;
    }

    char line[256];
    while (fgets(line, sizeof(line), src)) {
        Instruction instr;
        char opcode_str[10];
        
        // Basic parsing (simplified for demonstration)
        if (sscanf(line, "%s R%hhu, R%hhu, R%hhu", 
                   opcode_str, 
                   &instr.dest_reg, 
                   &instr.src_reg1, 
                   &instr.src_reg2) == 4) {
            
            // Map string to opcode
            if (strcmp(opcode_str, "ADD") == 0) instr.opcode = OP_ADD;
            else if (strcmp(opcode_str, "SUB") == 0) instr.opcode = OP_SUB;
            // Add more mappings as needed
            
            // Write instruction to object file
            fwrite(&instr, sizeof(Instruction), 1, obj);
        }
    }

    fclose(src);
    fclose(obj);
    return 0;
}

void load_program_to_memory(CPU *cpu, const char *object_file) {
    FILE *obj = fopen(object_file, "rb");
    if (!obj) {
        perror("Error opening object file");
        return;
    }

    // Reset memory and program counter
    memset(cpu->memory, 0, MEMORY_SIZE);
    cpu->program_counter = 0;

    // Read instructions into memory
    Instruction instr;
    size_t offset = 0;
    while (fread(&instr, sizeof(Instruction), 1, obj) == 1) {
        memcpy(&cpu->memory[offset], &instr, sizeof(Instruction));
        offset += sizeof(Instruction);
    }

    fclose(obj);
}

void execute_program(CPU *cpu) {
    while (!cpu->halted) {
        // Fetch instruction
        Instruction *current_instr = (Instruction*)&cpu->memory[cpu->program_counter];
        
        // Decode instruction
        switch (current_instr->opcode) {
            case OP_ADD:
                cpu->registers[current_instr->dest_reg] = 
                    alu_add(cpu, 
                            cpu->registers[current_instr->src_reg1], 
                            cpu->registers[current_instr->src_reg2]);
                break;
            
            case OP_SUB:
                cpu->registers[current_instr->dest_reg] = 
                    alu_subtract(cpu, 
                            cpu->registers[current_instr->src_reg1], 
                            cpu->registers[current_instr->src_reg2]);
                break;
            
            // Add more instruction implementations
            
            case OP_HALT:
                cpu->halted = true;
                break;
            
            default:
                printf("Unknown opcode: 0x%02X\n", current_instr->opcode);
                cpu->halted = true;
                break;
        }
        
        // Move to next instruction
        cpu->program_counter += sizeof(Instruction);
    }
}

// Recursive Factorial Example
void generate_factorial_assembly(const char *output_file) {
    FILE *f = fopen(output_file, "w");
    if (!f) {
        perror("Error creating assembly file");
        return;
    }

    // Simplified factorial assembly pseudocode
    fprintf(f, "# Factorial Recursive Program\n");
    fprintf(f, "LOAD R1, 5    # Input number\n");
    fprintf(f, "CALL factorial\n");
    fprintf(f, "HALT\n\n");
    
    fprintf(f, "factorial:\n");
    fprintf(f, "  CMP R1, 1    # Compare input with 1\n");
    fprintf(f, "  JZ base_case # Jump if zero\n");
    fprintf(f, "  PUSH R1      # Save current number\n");
    fprintf(f, "  SUB R1, R1, 1 # Decrement number\n");
    fprintf(f, "  CALL factorial # Recursive call\n");
    fprintf(f, "  POP R2       # Restore previous number\n");
    fprintf(f, "  MUL R1, R1, R2 # Multiply result\n");
    fprintf(f, "  RET\n\n");
    
    fprintf(f, "base_case:\n");
    fprintf(f, "  MOV R1, 1    # Base case: return 1\n");
    fprintf(f, "  RET\n");

    fclose(f);
}

// Demonstration of Fetch-Decode-Execute Cycle
void demonstrate_fetch_decode_execute(CPU *cpu) {
    printf("Fetch-Decode-Execute Cycle Demonstration:\n");
    
    // Load instruction
    Instruction *current_instr = (Instruction*)&cpu->memory[cpu->program_counter];
    
    // Fetch Stage
    printf("FETCH Stage:\n");
    printf("  Program Counter: 0x%04X\n", cpu->program_counter);
    printf("  Fetched Instruction: Opcode 0x%02X\n", current_instr->opcode);
    
    // Decode Stage
    printf("\nDECODE Stage:\n");
    printf("  Destination Register: R%d\n", current_instr->dest_reg);
    printf("  Source Register 1: R%d\n", current_instr->src_reg1);
    printf("  Source Register 2: R%d\n", current_instr->src_reg2);
    
    // Execute Stage
    printf("\nEXECUTE Stage:\n");
    switch (current_instr->opcode) {
        case OP_ADD:
            printf("  Performing Addition\n");
            cpu->registers[current_instr->dest_reg] = 
                alu_add(cpu, 
                        cpu->registers[current_instr->src_reg1], 
                        cpu->registers[current_instr->src_reg2]);
            break;
        case OP_SUB:
            printf("  Performing Subtraction\n");
            cpu->registers[current_instr->dest_reg] = 
                alu_subtract(cpu, 
                        cpu->registers[current_instr->src_reg1], 
                        cpu->registers[current_instr->src_reg2]);
            break;
        case OP_MUL:
            printf("  Performing Multiplication\n");
            cpu->registers[current_instr->dest_reg] = 
                alu_mul(cpu, 
                        cpu->registers[current_instr->src_reg1], 
                        cpu->registers[current_instr->src_reg2]);
            break;
        case OP_DIV:
            printf("  Performing Division\n");
            cpu->registers[current_instr->dest_reg] = 
                alu_div(cpu, 
                        cpu->registers[current_instr->src_reg1], 
                        cpu->registers[current_instr->src_reg2]);
            break;
        case OP_HALT:
            printf("  Halting Execution\n");
            cpu->halted = true;
            break;
        default:
            printf("  Unhandled Opcode: %d\n", current_instr->opcode);
            break;
    }
    
    // Memory/Register State
    printf("\nMEMORY/REGISTER State:\n");
    for (int i = 0; i < 8; i++) {
        printf("  R%d: %d\n", i, cpu->registers[i]);
    }
}
