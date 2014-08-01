# Syntax

The syntax looks like most ASM with instructions and arguments and whatnot.

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
call add, 2
ptop

halt 0
```

Would print `16`.