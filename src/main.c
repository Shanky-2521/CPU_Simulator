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
    // Step 2: Run the compiled binary
    if (run_binary() != 0) {
        return EXIT_FAILURE; // Stop if execution fails
    }

    // Step 3: Translate C to Assembly (Optional)
    char asm_file[256];
    snprintf(asm_file, sizeof(asm_file), "%s.asm", c_file);
    if (translate_c_to_asm(c_file, asm_file) != 0) {
        return EXIT_FAILURE; // Stop if translation fails
    }

    return EXIT_SUCCESS;
}




int compile_c_file(const char *c_file) {
    printf("Compiling %s...\n", c_file);
    char command[256];
    snprintf(command, sizeof(command), "gcc %s -o a.out", c_file);
    int status = system(command);
    if (status != 0) {
        fprintf(stderr, "Error: Compilation failed for %s\n", c_file);
        return -1;
    }
    printf("Compilation successful. Binary: a.out\n");
    return 0;
}

int run_binary() {
    printf("Running a.out...\n");
    int status = system("./a.out");
    if (status != 0) {
        fprintf(stderr, "Error: Execution of a.out failed.\n");
        return -1;
    }
    printf("Execution completed.\n");
    return 0;
}
