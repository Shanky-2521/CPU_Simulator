
#include "memory.h"
#include "../include/cpu.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdint.h>


// Read a 32-bit value from memory
uint32_t read_memory(const uint8_t *memory, uint32_t address) {
    if (address + 4 > MEMORY_SIZE) {
        fprintf(stderr, "Error: Memory read out of bounds at address 0x%08X.\n", address);
        exit(EXIT_FAILURE);
    }
    return *((uint32_t *)&memory[address]); // Read 4 bytes as a single 32-bit value
}

// Write a 32-bit value to memory
void write_memory(uint8_t *memory, uint32_t address, uint32_t value) {
    if (address + 4 > MEMORY_SIZE) {
        fprintf(stderr, "Error: Memory write out of bounds at address 0x%08X.\n", address);
        exit(EXIT_FAILURE);
    }
    *((uint32_t *)&memory[address]) = value; // Write 4 bytes as a single 32-bit value
}

// Load a program into the code segment
int load_program(uint8_t *memory, const uint32_t *program, uint32_t size) {
    if (memory == NULL || program == NULL) {
        fprintf(stderr, "Error: NULL pointer passed to load_program.\n");
        return -1; // Failure
    }
    if (size > (CODE_END - CODE_START + 1) / sizeof(uint32_t)) {
        fprintf(stderr, "Error: Program size exceeds code segment bounds.\n");
        return -1; // Failure
    }
    for (uint32_t i = 0; i < size; i++) {
        uint32_t address = CODE_START + i * sizeof(uint32_t);
        write_memory(memory, address, program[i]);
        printf("Loaded instruction %08X at address %08X\n", program[i], address); // Debug log
    }
    return 0; // Success
}


// Display memory contents
void display_memory(const uint8_t *memory, uint32_t start, uint32_t end, char format) {
    if (start >= MEMORY_SIZE || end >= MEMORY_SIZE || start > end) {
        fprintf(stderr, "Error: Invalid memory range for display.\n");
        return;
    }

    printf("\nMemory Contents (from 0x%08X to 0x%08X):\n", start, end);
    for (uint32_t address = start; address <= end; address += 4) {
        if ((address - start) % 32 == 0) {
            printf("\n0x%08X: ", address); // Print the address every 32 bytes
        }

        if (format == 'H') { // Hexadecimal format
            printf("%08X ", read_memory((uint8_t *)memory, address));
        } else if (format == 'A') { // ASCII format
            for (int i = 0; i < 4; i++) {
                char c = memory[address + i];
                printf("%c", isprint(c) ? c : '.'); // Printable or a dot for non-printables
            }
            printf(" ");
        } else {
            fprintf(stderr, "Error: Unsupported display format '%c'.\n", format);
            return;
        }
    }
    printf("\n");
}
