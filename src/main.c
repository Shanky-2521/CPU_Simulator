#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cpu.h"
#include "alu.h"
#include "assembler.h"

// Recursive Factorial in C (for comparison)
int factorial_c(int n) {
    static int recursive_calls = 0;
    recursive_calls++;
    printf("Recursive call count (C): %d\n", recursive_calls);
    
    if (n <= 1) return 1;
    return n * factorial_c(n - 1);
}

// Function prototypes for external functions
int generate_factorial_assembly(const char *source_file);
int demonstrate_fetch_decode_execute(CPU *cpu);
// Function signatures match assembler.h
void execute_program(CPU *cpu);
void load_program_to_memory(CPU *cpu, const char *object_file);

int main() {
    // Create a new CPU instance
    CPU cpu;
    init_cpu(&cpu);

    // Demonstrate Recursive Factorial
    printf("Recursive Factorial Demonstration:\n");
    
    // C Implementation
    printf("\nC Implementation:\n");
    int c_result = factorial_c(5);
    printf("Factorial of 5 (C): %d\n", c_result);

    // Generate Assembly Program
    const char *source_file = "/Users/shashankcuppala/Downloads/CPU_Simulator/factorial.asm";
    const char *object_file = "/Users/shashankcuppala/Downloads/CPU_Simulator/factorial.obj";
    
    generate_factorial_assembly(source_file);
    
    // Assemble the program
    if (assemble_program(source_file, object_file) != 0) {
        fprintf(stderr, "Assembly failed\n");
        return EXIT_FAILURE;
    }

    // Load program to memory
    load_program_to_memory(&cpu, object_file);

    // Demonstrate Fetch-Decode-Execute Cycle
    demonstrate_fetch_decode_execute(&cpu);

    // Execute the program
    printf("\nExecuting Factorial Program:\n");
    execute_program(&cpu);

    return EXIT_SUCCESS;
}
