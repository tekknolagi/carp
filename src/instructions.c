#include <inttypes.h>
#include "lib/messages.h"

#include "instructions.h"
#include "machine.h"

char carp_reverse_instr[][6] = {
  "halt",
  "nop",
  "loadr",
  "load",
  "store",
  "mov",
  "add",
  "sub",
  "mul",
  "mod",
  "shr",
  "shl",
  "not",
  "xor",
  "or",
  "and",
  "incr",
  "decr",
  "inc",
  "dec",
  "pushr",
  "push",
  "pop",
  "cmp",
  "lt",
  "gt",
  "jz",
  "rjz",
  "jnz",
  "rjnz",
  "jmp",
  "rjmp",
  "call",
  "ret",
  "preg",
  "ptop",
  "undef",
};

// yay macros

#define CARP_SPOP(NAME) if (carp_stack_pop(&m->stack, &NAME) == 1) \
    carp_vm_err(m, CARP_STACK_EMPTY)

#define CARP_SPUSH(NAME) if (carp_stack_push(&m->stack, NAME) == 1) \
    carp_vm_err(m, CARP_STACK_NO_MEM)

#define CARP_BINOP(NAME, F) CARP_IDEF (NAME) { \
  carp_value b, a; \
  CARP_SPOP(b);	\
  CARP_SPOP(a); \
  CARP_SPUSH(a F b); }


CARP_IDEF (HALT) {
  carp_vm_exit(m, carp_vm_next(m));
}

CARP_IDEF (NOP) {
  ;
}

CARP_IDEF (LOADR) {
  carp_value reg = carp_vm_next(m),
    val = carp_vm_next(m);
  carp_reg_set(m->regs, reg, val);
}

CARP_IDEF (LOAD) {
  carp_value reladdr = carp_vm_next(m),
    fp = m->regs[CARP_FP],
    val = m->stack.contents[fp + reladdr];
  CARP_SPUSH(val);
}

CARP_IDEF (STORE) {
  carp_value reladdr = carp_vm_next(m),
    val = carp_vm_next(m),
    fp = m->regs[CARP_FP];
  m->stack.contents[fp + reladdr] = val;
}

CARP_IDEF (MOV) {
  carp_value dst = carp_vm_next(m),
    src = carp_vm_next(m);
  carp_reg_set(m->regs, dst, m->regs[src]);
}

CARP_BINOP (ADD, +)

CARP_BINOP (SUB, -)

CARP_BINOP (MUL, *)

CARP_BINOP (MOD, %)

CARP_BINOP (SHR, >>)

CARP_BINOP (SHL, <<)

CARP_IDEF (NOT) {
  carp_value val;
  CARP_SPOP(val);
  CARP_SPUSH(~val);
}

CARP_BINOP (XOR, ^)

CARP_BINOP (OR, |)

CARP_BINOP (AND, &)

CARP_IDEF (INCR) {
  carp_reg_inc(m->regs, carp_vm_next(m));
}

CARP_IDEF (DECR) {
  carp_reg_dec(m->regs, carp_vm_next(m));
}

CARP_IDEF (INC) {
  carp_value a;
  CARP_SPOP(a);
  CARP_SPUSH(a + 1);
}

CARP_IDEF (DEC) {
  carp_value a;
  CARP_SPOP(a);
  CARP_SPUSH(a - 1);
}

CARP_IDEF (PUSHR) {
  CARP_SPUSH(*carp_reg_get(m->regs, carp_vm_next(m)));
}

CARP_IDEF (PUSH) {
  carp_value a = carp_vm_next(m);
  CARP_SPUSH(a);
}

CARP_IDEF (POP) {
  carp_value val;
  CARP_SPOP(val);
  carp_reg_set(m->regs, carp_vm_next(m), val);
}

CARP_IDEF (CMP) {
  carp_value b, a;
  CARP_SPOP(b);
  CARP_SPOP(a);
  CARP_SPUSH(a - b);
}

CARP_BINOP (LT, <)

CARP_BINOP (GT, >)

CARP_IDEF (JZ) {
  carp_value a;
  CARP_SPOP(a);
  // zero
  if (!a)
    carp_reg_set(m->regs, CARP_IP, carp_vm_next(m));
  else
    // do not take the next arg as an instruction
    carp_vm_next(m);
}

CARP_IDEF (RJZ) {
  carp_value a;
  CARP_SPOP(a);
  // zero
  if (!a)
    carp_reg_add(m->regs, CARP_IP, m->code[m->regs[CARP_IP] + 1]);
  else
    // do not take the next arg as an instruction
    carp_vm_next(m);
}

CARP_IDEF (JNZ) {
  carp_value a;
  CARP_SPOP(a);
  // not zero
  if (a)
    carp_reg_set(m->regs, CARP_IP, carp_vm_next(m));
  else
    // do not take the next arg as an instruction
    carp_vm_next(m);
}

CARP_IDEF (RJNZ) {
  carp_value a;
  CARP_SPOP(a);
  // not zero
  if (a)
    carp_reg_add(m->regs, CARP_IP, m->code[m->regs[CARP_IP] + 1]);
  else
    // do not take the next arg as an instruction
    carp_vm_next(m);
}

CARP_IDEF (JMP) {
  carp_reg_set(m->regs, CARP_IP, carp_vm_next(m));
}

CARP_IDEF (RJMP) {
  carp_reg_add(m->regs, CARP_IP, m->code[m->regs[CARP_IP] + 1]);
}

CARP_IDEF (CALL) {
  carp_value addr = carp_vm_next(m);

  CARP_SPUSH(m->regs[CARP_FP]);
  CARP_SPUSH(m->regs[CARP_IP]);

  carp_reg_set(m->regs, CARP_FP, m->regs[CARP_SP]);
  carp_reg_set(m->regs, CARP_IP, addr - 1);
}

CARP_IDEF (RET) {
  carp_value state;

  carp_reg_set(m->regs, CARP_SP, m->regs[CARP_FP]);

  CARP_SPOP(state);
  carp_reg_set(m->regs, CARP_IP, state);

  CARP_SPOP(state);
  carp_reg_set(m->regs, CARP_FP, state);
}

CARP_IDEF (PREG) {
  printf("%" PRId64 "\n", *carp_reg_get(m->regs, carp_vm_next(m)));
}

CARP_IDEF (PTOP) {
  carp_value val;

  if (carp_stack_peek(&m->stack, &val) == 1)
    carp_vm_err(m, CARP_STACK_EMPTY);

  printf("%" PRId64 "\n", val);
}
