#include "linker.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Initialize the linker context
void init_linker(Linker *linker) {
    linker->symbol_count = 0;
    linker->instruction_count = 0;
}

// Add an assembly file to the linker
void add_file_to_linker(Linker *linker, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error: Cannot open file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        if (line[0] == ':') {
            // Symbol definition (e.g., ":label_name 100")
            Symbol symbol;
            sscanf(line, ":%s %u", symbol.name, &symbol.address);
            symbol.address += linker->instruction_count; // Adjust relative to current instruction count
            linker->symbols[linker->symbol_count++] = symbol;
        } else {
            // Instruction line
            uint32_t instruction;
            sscanf(line, "%x", &instruction);
            linker->instructions[linker->instruction_count++] = instruction;
        }
    }
    fclose(file);
}

// Resolve symbols and adjust addresses
void resolve_symbols(Linker *linker) {
    for (int i = 0; i < linker->instruction_count; i++) {
        uint32_t instruction = linker->instructions[i];
        uint8_t opcode = (instruction >> 24) & 0xFF;

        if (opcode == 0x12 || opcode == 0x15) { // JUMP or CALL instructions
            char symbol_name[50];
            sscanf((char *)&instruction + 4, "%s", symbol_name); // Extract the symbol name

            // Search for the symbol in the table
            int found = 0;
            for (int j = 0; j < linker->symbol_count; j++) {
                if (strcmp(linker->symbols[j].name, symbol_name) == 0) {
                    // Replace the symbol reference with its resolved address
                    linker->instructions[i] = (instruction & 0xFF000000) |
                                              linker->symbols[j].address;
                    found = 1;
                    break;
                }
            }
            if (!found) {
                fprintf(stderr, "Error: Undefined symbol %s\n", symbol_name);
                exit(EXIT_FAILURE);
            }
        }
    }
}

// Generate the final binary file
void generate_binary(Linker *linker, const char *output_file) {
    FILE *file = fopen(output_file, "wb");
    if (!file) {
        fprintf(stderr, "Error: Cannot create output file %s\n", output_file);
        exit(EXIT_FAILURE);
    }

    fwrite(linker->instructions, sizeof(uint32_t), linker->instruction_count, file);
    fclose(file);
    printf("Binary generated: %s\n", output_file);
}
