# CarpVM
This is a project I've been slowly working on for about half a year now. The goal is to try and build a small (and decently reliable) VM from the ground up, learning more and more C as I go.

Right now there are instructions, registers, a stack, data memory, and the most basic of gotos.

## Installation

1. `make`
2. `make install`

To compile anything:

1. Include `carp/carp.h` in your program
2. `gcc program.c /usr/local/lib/carp/libcarp.a -o program.out`

## Instructions

Defined as such: NAME (args): Description

* HALT (code): Halts and attempts to clean up stack, data memory, and label memory before exiting with given exit code.
* NOP (): Does nothing. Not sure why you'd use it, but I've seen it included. It might go away at some point.
* LOADI (reg, val): Loads given integer value into given register.
* MOV (dst, src): Copies contents of src register into dst register.
* ADDI (): Pops the top two integers from the stack and pushes their sum.
* SUBI (): Pops the top two integers from the stack and pushes the difference (lower minus upper).
* MULI (): Pops the top two integers from the stack and pushes their product.
* INCR (): Increments the value at the top of the stack.
* DECR (): Decrements the value at the top of the stack.
* PUSHR (reg): Pushes value in given register.
* PUSHI (val): Pushes given value.
* POPI (val): Pops an integer from the stack and dumps it into GBG.
* JZ (addr): Jumps to given absolute address if value in EAX is 0.
* RJZ (diff): Adds differential to current EIP (relative jump) if value in EAX is 0.
* JNZ (addr): Jumps to given absolute address if value in EAX is not 0.
* RJNZ (diff): Adds differential to current EIP (relative jump) if value in EAX is not 0.
* JMP (addr): Jumps to given absolute address.
* RJMP (diff): Adds differential to current EIP (relative jump).
* DBS (key, val): Sets data memory at key (string pointer) to given value.
* DBG (key): Gets value from data memory at key (string pointer) and dumps it into EAX.
* LBL (key): Sets data memory at key (string pointer) to EIP.
* PREG (reg): Prints contents of given register.
* PTOP (): Peeks top of stack and prints top value.

## Registers

* REG0 ... REG9: General purpose.
* EAX, EDX: Used for cmp, et al.
* EIP: Instruction pointer. Used for keeping place in code, gotos, calling, etc.
* ESP: Stack pointer. Not currently in use; stack implementation is separate.
* GBG: Garbage register mainly used for popping.