#include "instructions.h"
#include <stdio.h>

// Decode a 32-bit binary instruction into an Instruction struct
Instruction decode_instruction(uint32_t raw) {
    Instruction instr;
    instr.opcode = (Opcode)((raw >> 24) & 0xFF); // Extract opcode (upper 8 bits)
    instr.operands[0] = (raw >> 16) & 0xFF;      // Extract first operand (next 8 bits)
    instr.operands[1] = (raw >> 8) & 0xFF;       // Extract second operand (next 8 bits)
    instr.operands[2] = raw & 0xFF;              // Extract third operand (lowest 8 bits)
    return instr;
}

// Display the decoded instruction for debugging
void display_instruction(Instruction instruction) {
    printf("Opcode: %02X\n", instruction.opcode);
    printf("Operands: %u, %u, %u\n",
           instruction.operands[0],
           instruction.operands[1],
           instruction.operands[2]);
}

// Execute a given instruction on the CPU
void execute_instruction(CPU *cpu, Instruction instruction) {
    printf("Executing instruction: Opcode=%02X Operands=%u, %u, %u\n",
           instruction.opcode,
           instruction.operands[0],
           instruction.operands[1],
           instruction.operands[2]);

    uint32_t *reg = cpu->registers; // Shortcut to registers
    uint32_t result;

    switch (instruction.opcode) {
        // Arithmetic Operations
        case ADD:
            reg[instruction.operands[0]] = alu_add(cpu, reg[instruction.operands[1]], reg[instruction.operands[2]]);
            break;
        case SUB:
            reg[instruction.operands[0]] = alu_sub(cpu, reg[instruction.operands[1]], reg[instruction.operands[2]]);
            break;
        case MUL:
            reg[instruction.operands[0]] = alu_mul(cpu, reg[instruction.operands[1]], reg[instruction.operands[2]]);
            break;
        case DIV:
            reg[instruction.operands[0]] = alu_div(cpu, reg[instruction.operands[1]], reg[instruction.operands[2]]);
            break;

        // Logical Operations
        case AND:
            reg[instruction.operands[0]] = alu_and(cpu, reg[instruction.operands[1]], reg[instruction.operands[2]]);
            break;
        case OR:
            reg[instruction.operands[0]] = alu_or(cpu, reg[instruction.operands[1]], reg[instruction.operands[2]]);
            break;
        case XOR:
            reg[instruction.operands[0]] = alu_xor(cpu, reg[instruction.operands[1]], reg[instruction.operands[2]]);
            break;
        case NOT:
            reg[instruction.operands[0]] = alu_not(cpu, reg[instruction.operands[1]]);
            break;

        // Shift Operations
        case SHL:
            reg[instruction.operands[0]] = alu_shl(cpu, reg[instruction.operands[1]], instruction.operands[2]);
            break;
        case SHR:
            reg[instruction.operands[0]] = alu_shr(cpu, reg[instruction.operands[1]], instruction.operands[2]);
            break;

        // Comparison Operations
        case EQ:
            result = alu_eq(cpu, reg[instruction.operands[1]], reg[instruction.operands[2]]);
            reg[instruction.operands[0]] = result;
            break;
        case NEQ:
            result = alu_neq(cpu, reg[instruction.operands[1]], reg[instruction.operands[2]]);
            reg[instruction.operands[0]] = result;
            break;
        case GT:
            result = alu_gt(cpu, reg[instruction.operands[1]], reg[instruction.operands[2]]);
            reg[instruction.operands[0]] = result;
            break;
        case LT:
            result = alu_lt(cpu, reg[instruction.operands[1]], reg[instruction.operands[2]]);
            reg[instruction.operands[0]] = result;
            break;
        case GE:
            result = alu_ge(cpu, reg[instruction.operands[1]], reg[instruction.operands[2]]);
            reg[instruction.operands[0]] = result;
            break;
        case LE:
            result = alu_le(cpu, reg[instruction.operands[1]], reg[instruction.operands[2]]);
            reg[instruction.operands[0]] = result;
            break;

        // Memory Operations
        case LOAD: {
            uint32_t reg = instruction.operands[0];
            uint32_t address = instruction.operands[1];
            if (address >= MEMORY_SIZE) {
                fprintf(stderr, "Error: Memory read out of bounds at address 0x%08X.\n", address);
                cpu->halted = true;
            } else {
                cpu->registers[reg] = read_memory(cpu->memory, address);
            }
            break;
        }

        case STORE: {
            uint32_t reg_value = cpu->registers[instruction.operands[0]];
            uint32_t address = instruction.operands[1];
            if (address >= MEMORY_SIZE) {
                fprintf(stderr, "Error: Memory write out of bounds at address 0x%08X.\n", address);
                cpu->halted = true;
            } else {
                write_memory(cpu->memory, address, reg_value);
            }
            break;
        }


        // Control Flow
        case JUMP:
            cpu->pc = reg[instruction.operands[0]]; // Jump to address in register
            break;
        case JZ:
            if (cpu->flags & 0x1) // Zero flag is set
                cpu->pc = reg[instruction.operands[0]];
            break;
        case JNZ:
            if (!(cpu->flags & 0x1)) // Zero flag is not set
                cpu->pc = reg[instruction.operands[0]];
            break;
        case CALL:
            cpu->sp -= 4; // Push current PC onto the stack
            write_memory(cpu->memory, cpu->sp, cpu->pc);
            cpu->pc = reg[instruction.operands[0]]; // Jump to address in register
            break;
        case RET:
            cpu->pc = read_memory(cpu->memory, cpu->sp); // Pop return address from the stack
            cpu->sp += 4;
            break;

        // Stack Operations
        case PUSH:
            cpu->sp -= 4;
            write_memory(cpu->memory, cpu->sp, reg[instruction.operands[0]]);
            break;
        case POP:
            reg[instruction.operands[0]] = read_memory(cpu->memory, cpu->sp);
            cpu->sp += 4;
            break;

        // System Operations
        case HALT:
            printf("HALT instruction executed. Stopping CPU.\n");
            cpu->halted = true;
            break;

        default:
            fprintf(stderr, "Error: Invalid opcode %02X\n", instruction.opcode);
            cpu->halted = true;
            break;
    }
}
