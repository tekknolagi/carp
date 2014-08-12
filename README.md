# CarpVM
This is a project I've been slowly working on for about half a year now. The goal is to try and build a small (and decently reliable) VM from the ground up, learning more and more C as I go.

Right now there are instructions, registers, a stack, data memory, and the most basic of gotos.

CONSIDER THIS PRE-ALPHA SOFTWARE. Things change more than they do in Rust!

## Installation

### Getting Carp

**If you already have a local copy (cloned before submodule was added)**

* `git fetch`
* `git rebase`
* `git submodule init`
* `git submodule update`

**If you don't already have a local copy**

* `git clone --recursive`

NOTE: If `git submodule status` doesn't return a SHA1 hash and repository name, you have a problem.

### Building Carp

1. `make`
2. `make install`

## Use

NOTE: See `carp -h` for help with command-line options.

### Interpreter

1. Write a Carp file - see [SYNTAX.md](http://github.com/tekknolagi/carp/tree/master/SYNTAX.md). More formal spec coming.
2. Run `./carp.out -f your_file.carp`.

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
* MOD (): Pops the two top integers from the stack and pushes lower % upper.
* NOT (reg): Computes bitwise NOT of reg and stores in reg.
* XOR (): Pops the top two integers from the stack and XORs them.
* OR (): Pops the top two integers from the stack and ORs them.
* AND (): Pops the top two integers from the stack and ANDs them.
* INCR (reg): Increments value in given register.
* DECR (reg): Decrements value in given register.
* INC (): Increments the value at the top of the stack.
* DEC (): Decrements the value at the top of the stack.
* PUSHR (reg): Pushes value in given register.
* PUSH (val): Pushes given value.
* POP (reg): Pops an integer from the stack and dumps it into given register.
* CMP (): Pops the top two integers from the stack and checks if equal. 0 means equal. Result will be pushed onto the stack.
* MOV (rega, regb): Move value in rega to regb.
* JZ (addr): Jumps to given absolute address if top of the stack is 0.
* RJZ (diff): Adds differential to current IP (relative jump) if top of the stack is 0.
* JNZ (addr): Jumps to given absolute address if top of the stack is not 0.
* RJNZ (diff): Adds differential to current IP (relative jump) if top of the stack is not 0.
* JMP (addr): Jumps to given absolute address.
* RJMP (diff): Adds differential to current IP (relative jump).
* DBS (key, val): Sets data memory at key (string pointer) to given value.
* DBG (key, reg): Gets value from data memory at key (string pointer) and dumps it into given register.
* CALL (key, nargs): Save state and set IP to value in data memory at key.
* RET (val): Push return value and load state.
* PREG (reg): Prints contents of given register.
* PTOP (): Peeks top of stack and prints top value.

## Registers

* R0 ... R9: General purpose.
* AX, BX, CX, DX, RX: Used for ... something in the future. Just taking up space for now.
* IP: Instruction pointer. Used for keeping place in code, gotos, calling, etc.
* SP: Stack pointer. Now working! :D
* GBG: Garbage register mainly used for popping.

## How to contribute

One way:

1. Check out the TODO.md file to see if anything needs doing.
2. Write some code (following existing implicit style) and submit a pull request.

Another way:

1. Write some code for a feature you want to exist and submit a pull request.

## License

GPLv3. See [LICENSE.txt](http://github.com/tekknolagi/carp/tree/master/LICENSE.txt).

## Badges and Things

![](https://ga-beacon.appspot.com/UA-47678422-4/tekknolagi/carp)
