#include "alu.h"
#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <stddef.h>

// Helper function to update CPU flags for comprehensive integer handling
static void update_flags(CPU *cpu, int32_t result, bool overflow) {
    // Reset all flags
    for (int i = 0; i < 16; i++) {
        cpu->flags[i] = false;
    }

    // Basic Status Flags
    if (result == 0) {
        cpu->flags[FLAG_ZERO] = true;
        cpu->flags[FLAG_SIGNED_ZERO] = true;
    }

    if (result < 0) {
        cpu->flags[FLAG_NEGATIVE] = true;
        cpu->flags[FLAG_SIGNED_NEGATIVE] = true;
    } else if (result > 0) {
        cpu->flags[FLAG_SIGNED_POSITIVE] = true;
    }

    // Overflow and Carry Flags
    if (overflow) {
        cpu->flags[FLAG_OVERFLOW] = true;
        cpu->flags[FLAG_CARRY] = true;
    }

    // Even/Odd Flag
    if (result % 2 == 0) {
        cpu->flags[FLAG_EVEN] = true;
    } else {
        cpu->flags[FLAG_ODD] = true;
    }

    // Unsigned Flags (for 32-bit unsigned representation)
    if ((uint32_t)result == UINT32_MAX) {
        cpu->flags[FLAG_UNSIGNED_MAX] = true;
    }
    if (result == 0) {
        cpu->flags[FLAG_UNSIGNED_MIN] = true;
    }
}

// Arithmetic Operations
int32_t alu_add(CPU *cpu, int32_t a, int32_t b) {
    int32_t result = a + b;
    
    // Check for signed overflow
    bool overflow = ((a > 0 && b > 0 && result <= 0) || 
                     (a < 0 && b < 0 && result >= 0));

    update_flags(cpu, result, overflow);

    return result;
}

// Subtraction, Multiplication, Division, Logical, and Shift Operations are defined above

// Atomic Bit-Level Operations

// Half Adder: Adds two bits without carry-in
void half_adder(bool a, bool b, bool *sum, bool *carry) {
    *sum = a ^ b;     // XOR for sum
    *carry = a & b;   // AND for carry
}

// Full Adder: Adds two bits with carry-in
void full_adder(bool a, bool b, bool carry_in, bool *sum, bool *carry_out) {
    bool half_sum, half_carry1, half_carry2;

    // First half adder
    half_adder(a, b, &half_sum, &half_carry1);

    // Second half adder with carry-in
    half_adder(half_sum, carry_in, sum, &half_carry2);

    // Compute final carry-out
    *carry_out = half_carry1 | half_carry2;
}

// N-bit Ripple Carry Adder
bool ripple_carry_adder(const bool *a, const bool *b, bool *result, size_t size) {
    bool carry = false;
    bool current_carry;

    for (size_t i = 0; i < size; i++) {
        full_adder(a[i], b[i], carry, &result[i], &current_carry);
        carry = current_carry;
    }

    return carry;  // Final carry-out
}

// Additional Primitive Functions

// Count leading zeros in a 32-bit integer
uint8_t count_leading_zeros(uint32_t x) {
    uint8_t count = 0;
    if (x == 0) return 32;
    
    while (!(x & 0x80000000)) {
        count++;
        x <<= 1;
    }
    
    return count;
}

// Perform bit reversal of a 32-bit integer
uint32_t bit_reverse(uint32_t x) {
    x = ((x & 0xffff0000) >> 16) | ((x & 0x0000ffff) << 16);
    x = ((x & 0xff00ff00) >> 8) | ((x & 0x00ff00ff) << 8);
    x = ((x & 0xf0f0f0f0) >> 4) | ((x & 0x0f0f0f0f) << 4);
    x = ((x & 0xcccccccc) >> 2) | ((x & 0x33333333) << 2);
    x = ((x & 0xaaaaaaaa) >> 1) | ((x & 0x55555555) << 1);
    return x;
}

// Check if a number is a power of 2
bool is_power_of_two(uint32_t x) {
    return x && !(x & (x - 1));
}

// Extract a bit field from a number
uint32_t extract_bits(uint32_t x, uint8_t start, uint8_t length) {
    uint32_t mask = ((1U << length) - 1) << start;
    return (x & mask) >> start;
}

// Insert a bit field into a number
uint32_t insert_bits(uint32_t original, uint32_t field, uint8_t start, uint8_t length) {
    uint32_t mask = ((1U << length) - 1) << start;
    return (original & ~mask) | ((field << start) & mask);
}

// Rotate bits left
uint32_t rotate_left(uint32_t x, uint8_t n) {
    n %= 32;  // Ensure rotation is within 32-bit range
    return (x << n) | (x >> (32 - n));
}

// Rotate bits right
uint32_t rotate_right(uint32_t x, uint8_t n) {
    n %= 32;  // Ensure rotation is within 32-bit range
    return (x >> n) | (x << (32 - n));
}

int32_t alu_subtract(CPU *cpu, int32_t a, int32_t b) {
    int32_t result = a - b;
    update_flags(cpu, result, false);

    // Detect signed overflow
    if ((a > 0 && b < 0 && result < 0) || (a < 0 && b > 0 && result > 0)) {
        cpu->flags[FLAG_OVERFLOW] = true; // Set Overflow flag
    }
    return result;
}

int32_t alu_mul(CPU *cpu, int32_t a, int32_t b) {
    int32_t result = a * b;
    update_flags(cpu, result, false);
    return result; // Overflow detection is typically not included for multiplication in simple ALUs
}

int32_t alu_div(CPU *cpu, int32_t a, int32_t b) {
    if (b == 0) {
        fprintf(stderr, "Error: Division by zero.\n");
        cpu->halted = true; // Halt the CPU on division by zero
        return 0;
    }
    int32_t result = a / b;
    update_flags(cpu, result, false);
    return result;
}

// Logical Operations
int32_t alu_and(CPU *cpu, int32_t a, int32_t b) {
    int32_t result = a & b;
    update_flags(cpu, result, false);
    return result;
}

int32_t alu_or(CPU *cpu, int32_t a, int32_t b) {
    int32_t result = a | b;
    update_flags(cpu, result, false);
    return result;
}

int32_t alu_xor(CPU *cpu, int32_t a, int32_t b) {
    int32_t result = a ^ b;
    update_flags(cpu, result, false);
    return result;
}

int32_t alu_not(CPU *cpu, int32_t a) {
    int32_t result = ~a;
    update_flags(cpu, result, false);
    return result;
}

// Shift Operations
int32_t alu_shl(CPU *cpu, int32_t a, int32_t shift) {
    int32_t result = a << shift;
    update_flags(cpu, result, false);
    return result;
}

int32_t alu_shr(CPU *cpu, int32_t a, int32_t shift) {
    int32_t result = (int32_t)((uint32_t)a >> shift); // Perform logical right shift
    update_flags(cpu, result, false);
    return result;
}

// Comparison Operations
int32_t alu_eq(CPU *cpu, int32_t a, int32_t b) {
    int32_t result = (a == b) ? 1 : 0;
    update_flags(cpu, result, false);
    return result;
}

int32_t alu_neq(CPU *cpu, int32_t a, int32_t b) {
    int32_t result = (a != b) ? 1 : 0;
    update_flags(cpu, result, false);
    return result;
}

int32_t alu_gt(CPU *cpu, int32_t a, int32_t b) {
    int32_t result = (a > b) ? 1 : 0;
    update_flags(cpu, result, false);
    return result;
}

int32_t alu_lt(CPU *cpu, int32_t a, int32_t b) {
    int32_t result = (a < b) ? 1 : 0;
    update_flags(cpu, result, false);
    return result;
}

int32_t alu_ge(CPU *cpu, int32_t a, int32_t b) {
    int32_t result = (a >= b) ? 1 : 0;
    update_flags(cpu, result, false);
    return result;
}

int32_t alu_le(CPU *cpu, int32_t a, int32_t b) {
    int32_t result = (a <= b) ? 1 : 0;
    update_flags(cpu, result, false);
    return result;
}
