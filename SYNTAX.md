# Syntax

The syntax looks like most ASM with instructions and arguments and whatnot.

Subject to change:

1. Function definitions are defined with a colon at the end of the name, like so: `main:`.
2. Function calls are prefixed with an at sign, like so: `@main`.
3. Instruction arguments are separated by commas (thuogh actually they don't have to be).
4. All words must be shorter than 10 characters long.

Example:

```asm
add:
gloadi -5
gloadi -4
addi
ret

main:
pushi 7
pushi 9
call @add, 2
ptop

halt 0
```

Would print `16`.