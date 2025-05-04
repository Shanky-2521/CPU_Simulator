#ifndef ALU_H
#define ALU_H

#include <stdint.h>
#include <stdbool.h>
#include "cpu.h" // Include CPU structure for flag updates

// ALU Function Prototypes

/**
 * Performs addition and updates the CPU flags.
 * @param cpu - Pointer to the CPU structure.
 * @param a - First operand.
 * @param b - Second operand.
 * @return Result of addition.
 */
int32_t alu_add(CPU *cpu, int32_t a, int32_t b);

/**
 * Performs subtraction and updates the CPU flags.
 * @param cpu - Pointer to the CPU structure.
 * @param a - First operand.
 * @param b - Second operand.
 * @return Result of subtraction.
 */
int32_t alu_subtract(CPU *cpu, int32_t a, int32_t b);

/**
 * Performs multiplication and updates the CPU flags.
 * @param cpu - Pointer to the CPU structure.
 * @param a - First operand.
 * @param b - Second operand.
 * @return Result of multiplication.
 */
int32_t alu_mul(CPU *cpu, int32_t a, int32_t b);

/**
 * Performs division and updates the CPU flags.
 * @param cpu - Pointer to the CPU structure.
 * @param a - Dividend.
 * @param b - Divisor.
 * @return Result of division.
 */
int32_t alu_div(CPU *cpu, int32_t a, int32_t b);

/**
 * Performs bitwise AND operation and updates the CPU flags.
 * @param cpu - Pointer to the CPU structure.
 * @param a - First operand.
 * @param b - Second operand.
 * @return Result of bitwise AND.
 */
int32_t alu_and(CPU *cpu, int32_t a, int32_t b);

/**
 * Performs bitwise OR operation and updates the CPU flags.
 * @param cpu - Pointer to the CPU structure.
 * @param a - First operand.
 * @param b - Second operand.
 * @return Result of bitwise OR.
 */
int32_t alu_or(CPU *cpu, int32_t a, int32_t b);

/**
 * Performs bitwise XOR operation and updates the CPU flags.
 * @param cpu - Pointer to the CPU structure.
 * @param a - First operand.
 * @param b - Second operand.
 * @return Result of bitwise XOR.
 */
int32_t alu_xor(CPU *cpu, int32_t a, int32_t b);

/**
 * Performs bitwise NOT operation and updates the CPU flags.
 * @param cpu - Pointer to the CPU structure.
 * @param a - Operand.
 * @return Result of bitwise NOT.
 */
int32_t alu_not(CPU *cpu, int32_t a);

/**
 * Performs left shift operation and updates the CPU flags.
 * @param cpu - Pointer to the CPU structure.
 * @param a - Operand.
 * @param shift - Number of positions to shift.
 * @return Result of left shift.
 */
int32_t alu_shl(CPU *cpu, int32_t a, int32_t shift);

/**
 * Performs right shift operation and updates the CPU flags.
 * @param cpu - Pointer to the CPU structure.
 * @param a - Operand.
 * @param shift - Number of positions to shift.
 * @return Result of right shift.
 */
int32_t alu_shr(CPU *cpu, int32_t a, int32_t shift);

/**
 * Compares two values for equality and updates the CPU flags.
 * @param cpu - Pointer to the CPU structure.
 * @param a - First operand.
 * @param b - Second operand.
 * @return 1 if equal, 0 otherwise.
 */
int32_t alu_eq(CPU *cpu, int32_t a, int32_t b);

/**
 * Compares two values for inequality and updates the CPU flags.
 * @param cpu - Pointer to the CPU structure.
 * @param a - First operand.
 * @param b - Second operand.
 * @return 1 if not equal, 0 otherwise.
 */
int32_t alu_neq(CPU *cpu, int32_t a, int32_t b);

/**
 * Checks if the first operand is greater than the second.
 * @param cpu - Pointer to the CPU structure.
 * @param a - First operand.
 * @param b - Second operand.
 * @return 1 if a > b, 0 otherwise.
 */
int32_t alu_gt(CPU *cpu, int32_t a, int32_t b);

/**
 * Checks if the first operand is less than the second.
 * @param cpu - Pointer to the CPU structure.
 * @param a - First operand.
 * @param b - Second operand.
 * @return 1 if a < b, 0 otherwise.
 */
int32_t alu_lt(CPU *cpu, int32_t a, int32_t b);

/**
 * Checks if the first operand is greater than or equal to the second.
 * @param cpu - Pointer to the CPU structure.
 * @param a - First operand.
 * @param b - Second operand.
 * @return 1 if a >= b, 0 otherwise.
 */
int32_t alu_ge(CPU *cpu, int32_t a, int32_t b);

/**
 * Checks if the first operand is less than or equal to the second.
 * @param cpu - Pointer to the CPU structure.
 * @param a - First operand.
 * @param b - Second operand.
 * @return 1 if a <= b, 0 otherwise.
 */
int32_t alu_le(CPU *cpu, int32_t a, int32_t b);

/**
 * Performs right shift operation and updates the CPU flags.
 * @param cpu - Pointer to the CPU structure.
 * @param a - Operand.
 * @param shift - Number of positions to shift.
 * @return Result of right shift.
 */
int32_t alu_right_shift(CPU *cpu, int32_t a, uint8_t shift);

// Atomic Bit-Level Operations

/**
 * N-bit Half Adder: Adds two bits without considering carry-in
 * @param a - First bit
 * @param b - Second bit
 * @param sum - Pointer to store sum bit
 * @param carry - Pointer to store carry bit
 */
void half_adder(bool a, bool b, bool *sum, bool *carry);

/**
 * N-bit Full Adder: Adds two bits with carry-in
 * @param a - First bit
 * @param b - Second bit
 * @param carry_in - Incoming carry bit
 * @param sum - Pointer to store sum bit
 * @param carry_out - Pointer to store carry-out bit
 */
void full_adder(bool a, bool b, bool carry_in, bool *sum, bool *carry_out);

/**
 * N-bit Ripple Carry Adder
 * @param a - First N-bit number
 * @param b - Second N-bit number
 * @param result - Pointer to store result
 * @param size - Number of bits
 * @return Carry out of most significant bit
 */
bool ripple_carry_adder(const bool *a, const bool *b, bool *result, size_t size);

// Additional Primitive Functions

/**
 * Count leading zeros in a 32-bit integer
 * @param x - Input number
 * @return Number of leading zero bits
 */
uint8_t count_leading_zeros(uint32_t x);

/**
 * Perform bit reversal of a 32-bit integer
 * @param x - Input number
 * @return Number with bits in reverse order
 */
uint32_t bit_reverse(uint32_t x);

/**
 * Check if a number is a power of 2
 * @param x - Input number
 * @return true if x is a power of 2, false otherwise
 */
bool is_power_of_two(uint32_t x);

/**
 * Extract a bit field from a number
 * @param x - Input number
 * @param start - Starting bit position (0-based)
 * @param length - Number of bits to extract
 * @return Extracted bit field
 */
uint32_t extract_bits(uint32_t x, uint8_t start, uint8_t length);

/**
 * Insert a bit field into a number
 * @param original - Original number
 * @param field - Bit field to insert
 * @param start - Starting bit position (0-based)
 * @param length - Number of bits to insert
 * @return Modified number
 */
uint32_t insert_bits(uint32_t original, uint32_t field, uint8_t start, uint8_t length);

/**
 * Rotate bits left
 * @param x - Input number
 * @param n - Number of positions to rotate
 * @return Number after left rotation
 */
uint32_t rotate_left(uint32_t x, uint8_t n);

/**
 * Rotate bits right
 * @param x - Input number
 * @param n - Number of positions to rotate
 * @return Number after right rotation
 */
uint32_t rotate_right(uint32_t x, uint8_t n);

#endif // ALU_H
