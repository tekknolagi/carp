# Syntax

The syntax looks like most ASM with instructions and arguments and whatnot.

Subject to change:

1. Function definitions are defined with a colon at the end of the name, like so: `main:`.
2. Function calls are prefixed with an at sign, like so: `@main`.
3. Registers are not prefixed with %, like so: `ax`.
4. Instruction arguments are separated by commas (thuogh actually they don't have to be).
5. All words must be shorter than 10 characters long.

Example:

```asm
add:
	gload -5
	gload -4
	add
	ret

main:
	push 7
	push 9
	call @add, 2
	ptop
	halt 0
```

Would print `16`.