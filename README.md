# THIS PROJECT IS UNSTABLE AND DEPRECATED

I have since started slow work on a more stable, better thought-out project
called [RabbitVM](https://github.com/rabbitvm/rabbit). It doesn't quite have the
same level of documentation but it should work much better.

# CarpVM
This is a project I've been slowly working on for about half a year now. The goal is to try and build a small (and decently reliable) VM from the ground up, learning more and more C as I go.

Right now there are instructions, registers, a stack, data memory, and calls. Not sure if recursion works... it should in theory. Haven't tested.

CONSIDER THIS PRE-ALPHA SOFTWARE. Things change more than they do in Rust!

[![Build Status](https://travis-ci.org/tekknolagi/carp.svg?branch=master)](https://travis-ci.org/tekknolagi/carp) &nbsp;
![](https://ga-beacon.appspot.com/UA-47678422-4/tekknolagi/carp) &nbsp;
[![Flattr this](http://api.flattr.com/button/flattr-badge-large.png)](http://flattr.com/thing/3268893/tekknolagicarp-on-GitHub)

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
NOTE: Recursive clone is for testing library. If not included, tests will not build.

### Building Carp

1. `make`
2. `make test` (optional)
3. `make install`
4. `make clean` (optional)

#### Tested Machines

Arch (bit) | OS (with version, name) | Compiler (with version)
---------- | ----------------------- | -----------------------
64-bit     | Ubuntu 12.04 (precise)  | gcc 4.6.3
64-bit     | Ubuntu 14.04 (trusty)   | gcc 4.8.2
32-bit     | Ubuntu 14.04 (trusty)   | gcc 4.8.2
64-bit     | OS X 10.9.4 (Mavericks) | clang 3.2
32-bit     | OS X 10.9.4 (Mavericks) | gcc 4.2.1
64-bit     | Arch Linux 3.13.6-1     | clang 3.4.2
64-bit?    | Arch Linux 3.13.6-1     | gcc 4.9.0 20140604

## Use

NOTE: See `carp -h` for help with command-line options.

### Interpreter

1. Write a Carp file - see [SYNTAX.md](http://github.com/tekknolagi/carp/tree/master/SYNTAX.md). More formal spec coming.
2. Run `./carp.out -f your_file.carp`.

### API

1. Include `carp/carp_machine.h` in your program.
2. Run `gcc program.c /usr/local/lib/libcarp.a -o program.out`.

## Instruction set

Opcode | Arguments | Description
------ | --------- | -----------
HALT   | exit code | Sets `ext` to given code, halts, and attempts to clean up stack, data memory, and label memory.
NOP    |           | Does nothing. Seriously.
LOADR  | reg, val  | Loads given integer value into given register.
LOAD   | diff      | Loads value at location `fp` + diff in the stack.
STORE  | diff, val | Stores value at location `fp` + diff.
MOV    | dst, src  | Copies contents of src register into dst register.
ADD    |           | Pops the top two integers from the stack and pushes their sum.
SUB    |           | Pops the top two integers from the stack and pushes the difference (lower minus upper).
MUL    |           | Pops the top two integers from the stack and pushes their product.
MOD    |           | Pops the top two integers from the stack and pushes lower % upper.
SHR    |           | Pops the top two integers from the stack and pushes lower >> upper.
SHL    |           | Pops the top two integers from the stack and pushes lower << upper.
NOT    |           | Pops top integer from stack and pushes bitwise NOT of that integer.
XOR    |           | Pops the top two integers from the stack and pushes bitwise XOR..
OR     |           | Pops the top two integers from the stack and pushes bitwise OR.
AND    |           | Pops the top two integers from the stack and pushes bitwise AND.
INCR   | reg       | Increments value in given register.
DECR   | reg       | Decrements value in given register.
INC    |           | Increments the value at the top of the stack.
DEC    |           | Decrements the value at the top of the stack.
PUSHR  | reg       | Pushes value in given register.
PUSH   | val       | Pushes given value.
POP    | reg       | Pops an integer from the stack and dumps it into given register.
CMP    |           | Pops the top two integers from the stack and checks if equal. 0 means equal. Pushes result.
LT     |           | Pops the top two integers from the stack and checks if lower < upper. Pushes result.
GT     |           | Pops the top two integers from the stack and checks if lower > upper. Pushes result.
JZ     | addr      | Jumps to given absolute address if top of the stack is 0.
RJZ    | diff      | Adds differential to `ip` (relative jump) if top of the stack is 0.
JNZ    | addr      | Jumps to given absolute address if top of the stack is not 0.
RJNZ   | diff      | Adds differential to `ip` (relative jump) if top of the stack is not 0.
JMP    | addr      | Jumps to given absolute address unconditionally.
RJMP   | diff      | Adds differential to `ip` (relative jump) unconditionally.
CALL   | key/addr  | Save state and set IP to value in data memory at key. Function may return value in `ax`.
RET    |           | Put top of the stack into `ax` and load previous state.
PREG   | reg       | Prints contents of given register.
PTOP   |           | Peeks top of stack and prints top value.

## Registers

Name | Purpose
---- | -------
`r0` ... `r9` | General purpose.
`ax` | Return value for user-defined function.
`bx`, `cx`, `dx`, `rx` | ... something in the future. Just taking up space for now.
`ip` | Instruction pointer. Used for keeping place in code, gotos, calling, etc.
`sp` | Stack pointer.
`fp` | Frame pointer. Used to keep state for function calls.
`gbg` | Garbage register mainly used for popping.
`run` | Boolean - is machine running?
`ext` | Exit code.

## How to contribute

One way:

1. Check out the TODO.md file to see if anything needs doing.
2. Write some code (following existing implicit style) and submit a pull request.

Another way:

1. Write some code for a feature you want to exist and submit a pull request.

## License

GPLv3. See [LICENSE.txt](http://github.com/tekknolagi/carp/tree/master/LICENSE.txt).
