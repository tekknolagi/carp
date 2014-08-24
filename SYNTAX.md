# Syntax

The syntax looks like most ASM with instructions and arguments and whatnot.

Subject to change:

1. Function definitions are defined with a colon at the end of the name, like so: `add:`.
2. Function calls are simple: `call add, 2`.
3. Registers are not prefixed with %, like so: `ax`.
4. Instruction arguments are separated by commas (thuogh actually they don't have to be).
5. All words must be shorter than 10 characters long.
6. All Carp files must end with a blank line.

Example:

```asm
add:
	load -5
	load -4
	add
	ret

main:
	push 7
	push 9
	call add
	ptop
	halt 0
```

Would print `16`.
