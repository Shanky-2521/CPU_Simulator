# Factorial Recursive Program
LOAD R1, 5    # Input number
CALL factorial
HALT

factorial:
  CMP R1, 1    # Compare input with 1
  JZ base_case # Jump if zero
  PUSH R1      # Save current number
  SUB R1, R1, 1 # Decrement number
  CALL factorial # Recursive call
  POP R2       # Restore previous number
  MUL R1, R1, R2 # Multiply result
  RET

base_case:
  MOV R1, 1    # Base case: return 1
  RET
