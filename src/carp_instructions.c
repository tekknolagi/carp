#include "carp_machine.h"

definstr (HALT) {
  carp_vm_exit(m, carp_vm_next(m));
}

definstr (NOP) {
  ;
}

definstr (LOAD) {
  long long reg = carp_vm_next(m),
    val = carp_vm_next(m);
  m->regs[reg] = val;
}

definstr (GLOAD) {
  long long reladdr = carp_vm_next(m),
    fp = m->regs[CARP_EFP],
    val = m->stack.contents[fp + reladdr];
  CARP_SPUSH(val);
}

definstr (MOV) {
  long long dst = carp_vm_next(m),
    src = carp_vm_next(m);
  m->regs[dst] = m->regs[src];
}

CARP_BINOP (ADD, +)

CARP_BINOP (SUB, -)

CARP_BINOP (MUL, *)

definstr (MOD) {
  long long a = m->regs[carp_vm_next(m)],
    b = m->regs[carp_vm_next(m)];

  m->regs[CARP_ERX] = a % b;
}

definstr (REM) {
  long long reg = carp_vm_next(m);
  m->regs[reg] = m->regs[CARP_ERX];
}

definstr (NOT) {
  long long *reg = &m->regs[carp_vm_next(m)];

  *reg = ~(*reg);
}

CARP_BINOP (XOR, ^)

CARP_BINOP (OR, |)

CARP_BINOP (AND, &)

definstr (INCR) {
  long long reg = carp_vm_next(m);
  m->regs[reg]++;
}

definstr (DECR) {
  long long reg = carp_vm_next(m);
  m->regs[reg]--;
}

definstr (INC) {
  long long a;
  CARP_SPOP(a);
  CARP_SPUSH(a + 1);
}

definstr (DEC) {
  long long a;
  CARP_SPOP(a);
  CARP_SPUSH(a - 1);
}

definstr (PUSHR) {
  long long reg = carp_vm_next(m),
    a = m->regs[reg];
  CARP_SPUSH(a);
}

definstr (PUSH) {
  long long a = carp_vm_next(m);
  CARP_SPUSH(a);
}

definstr (POP) {
  long long val;
  CARP_SPOP(val);
  m->regs[CARP_GBG] = val;
}

definstr (CMP) {
  carp_instr_POP(m);
  long long b = m->regs[CARP_GBG];
  carp_instr_POP(m);
  long long a = m->regs[CARP_GBG];

  m->regs[CARP_EAX] = a - b;
}

definstr (JZ) {
  // zero
  if (!m->regs[CARP_EAX])
    m->regs[CARP_EIP] = carp_vm_next(m);
}

definstr (RJZ) {
  // zero
  if (!m->regs[CARP_EAX])
    m->regs[CARP_EIP] += m->code[m->regs[CARP_EIP] + 1];
}

definstr (JNZ) {
  // not zero
  if (m->regs[CARP_EAX])
    m->regs[CARP_EIP] = carp_vm_next(m);
}

definstr (RJNZ) {
  // not zero
  if (m->regs[CARP_EAX])
    m->regs[CARP_EIP] += m->code[m->regs[CARP_EIP] + 1];
}

definstr (JMP) {
  m->regs[CARP_EIP] = carp_vm_next(m);
}

definstr (RJMP) {
  m->regs[CARP_EIP] += m->code[m->regs[CARP_EIP] + 1];
}

definstr (DBS) {
  char *key = (char *) carp_vm_next(m);
  long long val = carp_vm_next(m);

  carp_ht *res = carp_ht_set(&m->vars, key, val);
  if (res == NULL)
    carp_vm_err(m, CARP_HT_NO_MEM);
}

definstr (DBG) {
  char *key = (char *) carp_vm_next(m);
  long long reg = carp_vm_next(m);

  carp_ht *res = carp_ht_get(&m->vars, key);
  if (res == NULL)
    carp_vm_err(m, CARP_HT_DNE);

  m->regs[reg] = res->value;
}

definstr (CALL) {
  long long addr = carp_vm_next(m);
  long long nargs = carp_vm_next(m);

  CARP_SPUSH(nargs);
  CARP_SPUSH(m->regs[CARP_EFP]);
  CARP_SPUSH(m->regs[CARP_EIP]);

  m->regs[CARP_EFP] = m->regs[CARP_ESP];
  m->regs[CARP_EIP] = addr - 1;
}

definstr (RET) {
  long long rvalue;
  CARP_SPOP(rvalue);

  long long state;

  m->regs[CARP_ESP] = m->regs[CARP_EFP];

  CARP_SPOP(state);

  m->regs[CARP_EIP] = state;

  CARP_SPOP(state);

  m->regs[CARP_EFP] = state;

  CARP_SPOP(state);

  long long nargs = state;
  m->regs[CARP_ESP] -= nargs;

  CARP_SPUSH(rvalue);
}

definstr (PREG) {
  int reg = carp_vm_next(m);
  printf("%lld\n", m->regs[reg]);
}

definstr (PTOP) {
  long long val;

  if (carp_stack_peek(&m->stack, &val) == -1)
    carp_vm_err(m, CARP_STACK_EMPTY);

  printf("%lld\n", val);
}
