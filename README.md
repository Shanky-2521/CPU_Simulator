### **Team Members**
- **Shashank Cuppala**
  - Student ID: 017415216
  - Role: Developer

- **Venkat Gowtham Bhupalam**
  - Student ID: 017510714
  - Role: Co-Developer

- **Pavan Charith DevaraPalli**
  - Student ID: TBD
  - Role: Co-Developer

- **Sai Mouna Bogireddy**
  - Student ID: TBD
  - Role: Co-Developer

### **1. Folder and File Structure Setup**
- We created the folder structure for a modular CPU simulator project:
  ```
  CPU_Simulator/
  ├── include/        # Header files (e.g., cpu.h, alu.h, memory.h, etc.)
  ├── src/            # Source files (e.g., cpu.c, alu.c, memory.c, etc.)
  ├── programs/       # Sample programs in assembly and binary
  ├── build/          # Compiled binaries
  ├── Makefile        # Build automation
  ```

---

### **2. Core Modules Implemented**

#### **a. CPU Module**
- Designed the `CPU` structure in `cpu.h`:
  - Includes general-purpose registers (`R0`–`R3`), special-purpose registers (PC, SP), flags (`Z`, `N`, `O`), and memory.
- Implemented CPU initialization and `run_cpu` (fetch-decode-execute loop) in `cpu.c`:
  - Fetches instructions from memory, decodes them, executes them, and updates the Program Counter (PC).

---

#### **b. Memory Module**
- Implemented a 1024-byte memory, divided into segments:
  - **Code**: 0x000–0x0FF
  - **Data**: 0x100–0x1FF
  - **Stack**: 0x200–0x2FF
  - **Heap**: 0x300–0x3FF
- Functions in `memory.c`:
  - `read_memory`: Reads data from memory.
  - `write_memory`: Writes data to memory with bounds checking.
  - `load_program`: Loads a program into the code segment of memory.

---

#### **c. Instruction Set Architecture (ISA)**
- Defined an `Opcode` enum in `instructions.h` for all instructions:
  ```c
  typedef enum {
      ADD, SUB, MUL, DIV, AND, OR, XOR, NOT,
      SHL, SHR, EQ, NEQ, GT, LT, GE, LE,
      LOAD, STORE, JUMP, JZ, JNZ, CALL, RET,
      PUSH, POP, HALT
  } Opcode;
  ```
- Designed the `Instruction` structure:
  - `opcode` (operation code) and `operands` (up to 3).

- Implemented:
  - `decode_instruction`: Converts a 32-bit binary into an `Instruction` structure.
  - `execute_instruction`: Executes instructions using the CPU and ALU.

---

#### **d. Arithmetic and Logical Unit (ALU)**
- Implemented ALU operations in `alu.c`:
  - Arithmetic (`ADD`, `SUB`, `MUL`, `DIV`).
  - Logical (`AND`, `OR`, `XOR`, `NOT`).
  - Bitwise shifts (`SHL`, `SHR`).
  - Comparisons (`EQ`, `NEQ`, `GT`, `LT`, `GE`, `LE`).

---

#### **e. Debug Utilities**
- Added functions in `debug.c` to monitor the CPU and memory state:
  - `display_cpu_state`: Prints the state of registers, flags, and halted status.
  - `display_memory_state`: Prints memory contents in ASCII/Hex format.

---

### **3. Program Execution**

#### **a. Binary Program**
- Created a sample binary program (`test1.bin`):
  ```asm
  LOAD 0 256    ; Load value at address 256 into R0
  LOAD 1 260    ; Load value at address 260 into R1
  ADD 2 0 1     ; R2 = R0 + R1
  STORE 2 264   ; Store R2 at address 264
  HALT          ; Stop execution
  ```

#### **b. Issues Faced and Fixes**

1. **PC Out of Bounds**:
   - Added bounds checking in `fetch_instruction`.
   - Prevented PC from incrementing after the `HALT` instruction in `run_cpu`.

2. **HALT Not Stopping Execution**:
   - Ensured `HALT` sets `cpu->halted = true` in `execute_instruction`.

3. **Instruction Decoding and Execution**:
   - Confirmed `HALT` and other opcodes are decoded and executed correctly.
   - Fixed logical bugs in `run_cpu` to handle halted CPU state properly.

4. **Debug Logs**:
   - Added logs to trace:
     - Loaded memory addresses (`load_program`).
     - Fetched instructions (`fetch_instruction`).
     - Decoded and executed instructions (`execute_instruction`).

---

### **4. Current Status**

1. **Simulation Core Working**:
   - The fetch-decode-execute loop runs.
   - Instructions are fetched, decoded, executed, and halted correctly.
   - Memory and CPU state are displayed for debugging.

2. **Issues Resolved**:
   - `HALT` now stops execution.
   - PC no longer exceeds memory bounds.

---

### **5. Next Steps**
1. **Validation**:
   - Test the simulator with more complex programs to ensure all instructions work correctly.

2. **High-Level Language (HLL)**:
   - Define a simple HLL for writing programs.
   - Implement a translator to convert HLL to ISA assembly.

3. **Linker**:
   - Combine multiple assembly programs into a single binary.

4. **Advanced Features**:
   - Add stack support for function calls.
   - Implement recursion and dynamic memory allocation.

-