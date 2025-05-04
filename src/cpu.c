#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cpu.h"
#include "alu.h"

// Define memory boundaries
#define CODE_START 0x100
#define CODE_END (MEMORY_SIZE - 1)
#define STACK_END (MEMORY_SIZE - 1)
#define HEAP_START 0x200

// Initialize the CPU
void init_cpu(CPU *cpu) {
    // Clear all registers
    memset(cpu->registers, 0, sizeof(cpu->registers));

    // Clear flags
    for (int i = 0; i < 16; i++) {
        cpu->flags[i] = false;
    }

    // Set Program Counter to start of code segment
    cpu->program_counter = CODE_START;

    // Set Stack Pointer to end of memory
    cpu->stack_pointer = STACK_END;

    // Clear entire memory
    memset(cpu->memory, 0, MEMORY_SIZE);

    // Clear instruction register
    cpu->instruction_register = 0;

    // Ensure CPU is not halted
    cpu->halted = false;

    // Set default integer mode to signed
    cpu->integer_mode = MODE_SIGNED;

    printf("CPU Initialized:\n");
    printf("  Registers cleared\n");
    printf("  Flags reset\n");
    printf("  Memory zeroed\n");
    printf("  Integer Mode: Signed\n");
}

// Reset the CPU to its initial state
void reset_cpu(CPU *cpu) {
    init_cpu(cpu);
}

// Display current CPU state
static void display_cpu_state(const CPU *cpu) {
    printf("\n--- CPU State ---\n");
    
    // Print Registers
    printf("Registers:\n");
    for (int i = 0; i < REGISTER_COUNT; i++) {
        printf("  R%d: 0x%08X\n", i, cpu->registers[i]);
    }

    // Print Special Registers
    printf("Program Counter: 0x%08X\n", cpu->program_counter);
    printf("Stack Pointer:   0x%08X\n", cpu->stack_pointer);

    // Print Flags
    printf("Flags:\n");
    const char *flag_names[] = {"Zero", "Negative", "Overflow", "Carry", "Interrupt"};
    for (int i = 0; i < 5; i++) {
        printf("  %s: %s\n", flag_names[i], cpu->flags[i] ? "SET" : "CLEAR");
    }

    // Print Halted State
    printf("Halted: %s\n", cpu->halted ? "YES" : "NO");
}

// Fetch next instruction
uint32_t fetch_instruction(CPU *cpu) {
    if (cpu->program_counter < CODE_START || cpu->program_counter > CODE_END) {
        fprintf(stderr, "Error: Program Counter out of memory bounds at %08X.\n", cpu->program_counter);
        cpu->halted = true;
        return 0;
    }

    // Fetch 32-bit instruction
    uint32_t instruction = *((uint32_t*)(cpu->memory + cpu->program_counter));
    cpu->instruction_register = instruction;
    cpu->program_counter += sizeof(uint32_t);

    return instruction;
}

// Decode instruction
static Opcodes decode_instruction(uint32_t instruction) {
    // Extract opcode (assuming first byte represents opcode)
    return (Opcodes)(instruction & 0xFF);
}

// Execute instruction
static void execute_instruction(CPU *cpu, Opcodes opcode) {
    switch (opcode) {
        case OP_HALT:
            cpu->halted = true;
            printf("CPU Halted\n");
            break;

        case OP_ADD:
            // Placeholder for ADD instruction
            printf("ADD instruction\n");
            break;

        case OP_SUB:
            // Placeholder for SUB instruction
            printf("SUB instruction\n");
            break;

        // Add more instruction implementations here
        default:
            fprintf(stderr, "Unknown opcode: 0x%02X\n", opcode);
            cpu->halted = true;
            break;
    }
}

// Main CPU run loop
void run_cpu(CPU *cpu) {
    while (!cpu->halted) {
        // Fetch instruction
        uint32_t instruction = fetch_instruction(cpu);
        
        // Decode instruction
        Opcodes opcode = decode_instruction(instruction);
        
        // Execute instruction
        execute_instruction(cpu, opcode);
    }

    // Display final CPU state when halted
    display_cpu_state(cpu);
}
