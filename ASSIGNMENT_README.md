# CPU Simulator Design Assignment

### **Team Members and Contributions**

- **Shashank Cuppala**
  - Student ID: 017415216
  - **Primary Contributions:**
    - Project Architecture Design
    - Core CPU Module Implementation
    - Memory Management System
    - ALU (Arithmetic Logic Unit) Development
    - Instruction Set Architecture
    - Debugging and Optimization
    - Project Documentation and README
    - Build System Configuration
    - Git Repository Management

- **Venkat Gowtham Bhupalam**
  - Student ID: 017510714
  - Contributions:
    - Instruction Decoding Support
    - Initial Assembler Prototype
    - Error Handling Mechanisms
    - Testing of Basic Operations

- **Pavan Charith DevaraPalli**
  - Student ID: 017476212
  - Contributions:
    - Bitwise Operation Implementation
    - Memory Segmentation Research
    - Performance Profiling
    - Documentation Review

- **Sai Mouna Bogireddy**
  - Student ID: 016587791
  - Contributions:
    - Control Flow Instruction Design
    - Register Management Support
    - Code Refactoring
    - Testing Scenarios Development

## Project Overview
This project implements a comprehensive CPU simulator with a custom Instruction Set Architecture (ISA), demonstrating key computer architecture concepts.

## CPU Architecture
- 32-bit word size
- 8 general-purpose registers (R0-R7)
- Special purpose registers: Program Counter, Stack Pointer
- 4096-byte memory
- Comprehensive flag system (Zero, Negative, Overflow, Carry, Interrupt)

## Instruction Set Architecture (ISA)
### Instruction Categories
1. **Arithmetic Operations**
   - ADD
   - SUB
   - MUL
   - DIV

2. **Logical Operations**
   - AND
   - OR
   - XOR
   - NOT

3. **Data Movement**
   - LOAD
   - STORE
   - MOVE

4. **Control Flow**
   - JUMP
   - BRANCH
   - CALL
   - RETURN

5. **System Operations**
   - HALT

## Memory Layout
- Total Memory: 4096 bytes
- Segments:
  - Code Segment
  - Data Segment
  - Stack Segment
  - Heap Segment

## Recursive Function Demonstration
A sample recursive function (factorial calculation) is implemented to showcase:
- Stack usage during recursive calls
- Context switching
- Register and memory state tracking

## Team Contributions
### [Team Member 1]
[Detailed description of contributions]

### [Team Member 2]
[Detailed description of contributions]

### [Team Member 3]
[Detailed description of contributions]

## Project Highlights
- Modular design
- Comprehensive ALU operations
- Flexible memory management
- Detailed instruction execution tracing
