#include "carp_machine.h"

CARP_IDEF (HALT) {
  carp_vm_exit(m, carp_vm_next(m));
}

CARP_IDEF (NOP) {
  ;
}

CARP_IDEF (LOAD) {
  carp_value reg = carp_vm_next(m),
    val = carp_vm_next(m);
  carp_reg_set(m->regs, reg, val);
}

CARP_IDEF (GLOAD) {
  carp_value reladdr = carp_vm_next(m),
    fp = m->regs[CARP_FP],
    val = m->stack.contents[fp + reladdr];
  CARP_SPUSH(val);
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

CARP_IDEF (NOT) {
  carp_value reg = carp_vm_next(m);
  carp_reg_set(m->regs, reg, ~m->regs[reg]);
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

  carp_reg_set(m->regs, CARP_AX, a - b);
}

CARP_BINOP (LT, <)

CARP_BINOP (GT, >)

CARP_IDEF (JZ) {
  carp_value a;
  CARP_SPOP(a);
  // zero
  if (!a)
    carp_reg_set(m->regs, CARP_IP, carp_vm_next(m));
}

CARP_IDEF (RJZ) {
  carp_value a;
  CARP_SPOP(a);
  // zero
  if (!a)
    carp_reg_add(m->regs, CARP_IP, m->code[m->regs[CARP_IP] + 1]);
}

CARP_IDEF (JNZ) {
  carp_value a;
  CARP_SPOP(a);
  // not zero
  if (a)
    carp_reg_set(m->regs, CARP_IP, carp_vm_next(m));
}

CARP_IDEF (RJNZ) {
  carp_value a;
  CARP_SPOP(a);
  // not zero
  if (a)
    carp_reg_add(m->regs, CARP_IP, m->code[m->regs[CARP_IP] + 1]);
}

CARP_IDEF (JMP) {
  carp_reg_set(m->regs, CARP_IP, carp_vm_next(m));
}

CARP_IDEF (RJMP) {
  carp_reg_add(m->regs, CARP_IP, m->code[m->regs[CARP_IP] + 1]);
}

CARP_IDEF (DBS) {
  char *key = (char *) carp_vm_next(m);
  carp_value val = carp_vm_next(m);

  carp_ht *res = carp_ht_set(&m->vars, key, val);
  if (res == NULL)
    carp_vm_err(m, CARP_HT_NO_MEM);
}

CARP_IDEF (DBG) {
  char *key = (char *) carp_vm_next(m);
  carp_value reg = carp_vm_next(m);

  carp_ht *res = carp_ht_get(&m->vars, key);
  if (res == NULL)
    carp_vm_err(m, CARP_HT_DNE);

  carp_reg_set(m->regs, reg, res->value);
}

CARP_IDEF (CALL) {
  carp_value addr = carp_vm_next(m);
  carp_value nargs = carp_vm_next(m);

  CARP_SPUSH(nargs);
  CARP_SPUSH(m->regs[CARP_FP]);
  CARP_SPUSH(m->regs[CARP_IP]);

  carp_reg_set(m->regs, CARP_FP, m->regs[CARP_SP]);
  carp_reg_set(m->regs, CARP_IP, addr - 1);
}

CARP_IDEF (RET) {
  carp_value rvalue;
  CARP_SPOP(rvalue);

  carp_value state;

  carp_reg_set(m->regs, CARP_SP, m->regs[CARP_FP]);

  CARP_SPOP(state);

  carp_reg_set(m->regs, CARP_IP, state);

  CARP_SPOP(state);

  carp_reg_set(m->regs, CARP_FP, state);

  CARP_SPOP(state);

  carp_value nargs = state;
  carp_reg_sub(m->regs, CARP_SP, nargs);

  CARP_SPUSH(rvalue);
}

CARP_IDEF (PREG) {
  printf("%lld\n", *carp_reg_get(m->regs, carp_vm_next(m)));
}

CARP_IDEF (PTOP) {
  carp_value val;

  if (carp_stack_peek(&m->stack, &val) == 1)
    carp_vm_err(m, CARP_STACK_EMPTY);

  printf("%lld\n", val);
}

CARP_IDEF (PVARS) {
  carp_ht_print(&m->vars, stdout);
}
