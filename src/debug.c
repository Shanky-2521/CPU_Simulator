#include "debug.h"
#include <ctype.h> // For isprint()
#include <stdio.h>
#include "cpu.h"  // Include your CPU structure definitions

// Display the contents of all registers
void display_registers(const CPU *cpu) {
    printf("\n=== Registers ===\n");
    for (int i = 0; i < 4; i++) {
        printf("R%d: %08X\n", i, cpu->registers[i]);
    }
    printf("PC: %08X\n", cpu->program_counter);
    printf("SP: %08X\n", cpu->stack_pointer);
}

// Display the current state of memory in a specified range
void display_memory_state(const CPU *cpu, uint32_t start, uint32_t end, char format) {
    printf("=== Memory State (from 0x%08X to 0x%08X) ===\n", start, end);
    for (uint32_t addr = start; addr <= end; addr += 4) {
        uint32_t value = read_memory(cpu->memory, addr);
        if (format == 'h') {
            printf("0x%08X: %08X\n", addr, value); // Hexadecimal format
        } else if (format == 'a') {
            printf("0x%08X: %c%c%c%c\n", addr,
                   (value >> 24) & 0xFF,
                   (value >> 16) & 0xFF,
                   (value >> 8) & 0xFF,
                   value & 0xFF); // ASCII format
        } else {
            fprintf(stderr, "Error: Unsupported display format '%c'.\n", format);
            return;
        }
    }
}


// Display the current state of the CPU
static void display_cpu_state(const CPU *cpu) {
    printf("\n=== CPU State ===\n");
    display_registers(cpu);

    printf("\nFlags: ");
    printf("Z=%d ", cpu->flags[FLAG_ZERO]); // Zero flag
    printf("N=%d ", cpu->flags[FLAG_NEGATIVE]); // Negative flag
    printf("O=%d\n", cpu->flags[FLAG_OVERFLOW]); // Overflow flag

    printf("Halted: %s\n", cpu->halted ? "Yes" : "No");
}

// Display the decoded instruction for debugging purposes
void display_instruction_debug(const Instruction *instruction) {
    printf("\n=== Decoded Instruction ===\n");
    printf("Opcode: %02X\n", instruction->opcode);
    printf("Operands: %u, %u, %u\n",
           instruction->operands[0],
           instruction->operands[1],
           instruction->operands[2]);
}




