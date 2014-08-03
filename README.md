# CarpVM
This is a project I've been slowly working on for about half a year now. The goal is to try and build a small (and decently reliable) VM from the ground up, learning more and more C as I go.

Right now there are instructions, registers, a stack, data memory, and the most basic of gotos.

## Installation

1. `make`
2. `make install`

## Use

### Interpreter

1. Write a Carp file - see [SYNTAX.md](http://github.com/tekknolagi/carp/tree/master/SYNTAX.md). More formal spec coming.
2. Run `carp your_file.carp`.

### API

1. Include `carp/carp.h` in your program.
2. Run `gcc program.c /usr/local/lib/libcarp.a -o program.out`.

## Instruction set

Defined as such: NAME (args): Description

* HALT (code): Halts and attempts to clean up stack, data memory, and label memory before exiting with given exit code.
* NOP (): Does nothing. Seriously.
* LOAD (reg, val): Loads given integer value into given register.
* MOV (dst, src): Copies contents of src register into dst register.
* ADD (): Pops the top two integers from the stack and pushes their sum.
* SUB (): Pops the top two integers from the stack and pushes the difference (lower minus upper).
* MUL (): Pops the top two integers from the stack and pushes their product.
* MOD (rega, regb): Computes rega % regb and stores in ERX.
* REM (reg): Stores ERX in given register.
* NOT (reg): Computes bitwise NOT of reg and stores in reg.
* XOR (rega, regb): Computes rega ^ regb and stores in rega.
* OR (rega, regb): Computes rega | regb and stores in rega.
* AND (rega, regb): Computes rega & regb and stores in rega.
* INCR (reg): Increments value in given register.
* DECR (reg): Decrements value in given register.
* INC (): Increments the value at the top of the stack.
* DEC (): Decrements the value at the top of the stack.
* PUSHR (reg): Pushes value in given register.
* PUSH (val): Pushes given value.
* POP (val): Pops an integer from the stack and dumps it into GBG.
* JZ (addr): Jumps to given absolute address if value in EAX is 0.
* RJZ (diff): Adds differential to current EIP (relative jump) if value in EAX is 0.
* JNZ (addr): Jumps to given absolute address if value in EAX is not 0.
* RJNZ (diff): Adds differential to current EIP (relative jump) if value in EAX is not 0.
* JMP (addr): Jumps to given absolute address.
* RJMP (diff): Adds differential to current EIP (relative jump).
* DBS (key, val): Sets data memory at key (string pointer) to given value.
* DBG (key, reg): Gets value from data memory at key (string pointer) and dumps it into given register.
* CALL (key, nargs): Save state and set EIP to value in data memory at key.
* RET (val): Push return value and load state.
* PREG (reg): Prints contents of given register.
* PTOP (): Peeks top of stack and prints top value.

## Registers

* REG0 ... REG9: General purpose.
* EAX, EBX, ECX, EDX: Used for cmp, et al.
* ERX: Used for remainder/mod.
* EIP: Instruction pointer. Used for keeping place in code, gotos, calling, etc.
* ESP: Stack pointer. Not currently in use; stack implementation is separate.
* GBG: Garbage register mainly used for popping.

## How to contribute

One way:

1. Check out the TODO.md file to see if anything needs doing.
2. Write some code (following existing implicit style) and submit a pull request.

Another way:

1. Write some code for a feauture you want to exist and submit a pull request.

## License

Not sure yet. Probably GPL. For now assume Creative Commons Attribution NonCommercial (whatever license is on my blog, http://bernsteinbear.com).