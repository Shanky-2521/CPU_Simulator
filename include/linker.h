#ifndef LINKER_H
#define LINKER_H

#include <stdint.h>

// Define maximum sizes for symbols and instructions
#define MAX_SYMBOLS 256
#define MAX_INSTRUCTIONS 1024

// Symbol Table Entry
typedef struct {
    char name[50];        // Name of the symbol (e.g., function or variable name)
    uint32_t address;     // Address of the symbol in memory
} Symbol;

// Linker Context
typedef struct {
    Symbol symbols[MAX_SYMBOLS];    // Symbol table for resolving references
    int symbol_count;               // Number of symbols in the table
    uint32_t instructions[MAX_INSTRUCTIONS]; // Combined binary instructions
    int instruction_count;          // Total number of instructions
} Linker;

// Function Prototypes

/**
 * Initializes the linker context.
 * @param linker - Pointer to the Linker context.
 */
void init_linker(Linker *linker);

/**
 * Adds an assembly file to the linker.
 * Parses symbols and instructions, and integrates them into the linker context.
 * @param linker - Pointer to the Linker context.
 * @param filename - Name of the assembly file to process.
 */
void add_file_to_linker(Linker *linker, const char *filename);

/**
 * Resolves symbols and adjusts addresses in the linker context.
 * @param linker - Pointer to the Linker context.
 */
void resolve_symbols(Linker *linker);

/**
 * Generates the final binary file from the linker context.
 * @param linker - Pointer to the Linker context.
 * @param output_file - Name of the output binary file.
 */
void generate_binary(Linker *linker, const char *output_file);

#endif // LINKER_H
