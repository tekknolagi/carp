#include "carp_instructions.h"

definstr (HALT) {
  puts("halting...");
  carp_vm_exit(m, (int) m->c.args[0].ll);
}

definstr (NOP) {
  carp_instr_NEXT(m);
}

definstr (NEXT) {
  m->regs[CARP_EIP]++;
}

definstr (LOADI) {
  m->regs[m->c.args[0].r] = m->c.args[1].ll;
  carp_instr_NEXT(m);
}

definstr (MOV) {
  m->regs[m->c.args[0].r] = m->regs[m->c.args[1].r];
  carp_instr_NEXT(m);
}

definstr (ADD) {
  m->regs[m->c.args[0].r] = m->regs[m->c.args[1].r] + m->regs[m->c.args[2].r]; // end = 1 + 2
  carp_instr_NEXT(m);
}

definstr (SUB) {
  m->regs[m->c.args[0].r] = m->regs[m->c.args[1].r] - m->regs[m->c.args[2].r]; // end = 1 - 2
  carp_instr_NEXT(m);
}

definstr (MUL) {
  m->regs[m->c.args[0].r] = m->regs[m->c.args[1].r] * m->regs[m->c.args[2].r]; // end = 1 * 2
  carp_instr_NEXT(m);
}

definstr (DIV) {
  m->regs[m->c.args[0].r] = m->regs[m->c.args[1].r] / m->regs[m->c.args[2].r]; // end = 1 / 2
  carp_instr_NEXT(m);
}

definstr (INCR) {
  m->regs[m->c.args[0].r]++;
  carp_instr_NEXT(m);
}

definstr (DECR) {
  m->regs[m->c.args[0].r]--;
  carp_instr_NEXT(m);
}

definstr (SHOW) {
  printf("r%d: %lld\n", m->c.args[0].r, m->regs[m->c.args[0].r]);
  carp_instr_NEXT(m);
}

definstr (PUSH) {
  carp_stack_push(m, m->c.args[0].ll); // push 1
  carp_instr_NEXT(m);
}

definstr (POP) {
  m->regs[m->c.args[0].r] = carp_stack_pop(m); // pop top into 1
  carp_instr_NEXT(m);
}

definstr (CMP) {
  m->regs[CARP_EAX] = m->regs[m->c.args[0].r] - m->regs[m->c.args[1].r];
  carp_instr_NEXT(m);
}

definstr (JZ) {
  // zero
  if (!m->regs[CARP_EAX]) {
    m->regs[CARP_EIP] = m->c.args[0].ll;
  }
  else {
    carp_instr_NOP(m);
  }
}

definstr (RJZ) {
  // zero
  if (!m->regs[CARP_EAX]) {
    m->regs[CARP_EIP] += m->c.args[0].ll;
  }
  else {
    carp_instr_NOP(m);
  }
}

definstr (JNZ) {
  // not zero
  if (m->regs[CARP_EAX]) {
    m->regs[CARP_EIP] = m->c.args[0].ll;
  }
  else {
    carp_instr_NOP(m);
  }
}

definstr (RJNZ) {
  // not zero
  if (m->regs[CARP_EAX]) {
    m->regs[CARP_EIP] += m->c.args[0].ll;
  }
  else {
    carp_instr_NOP(m);
  }
}

definstr (JMP) {
  m->regs[CARP_EIP] = m->c.args[0].ll;
}

definstr (RJMP) {
  m->regs[CARP_EIP] += m->c.args[0].ll;
}

definstr (DBS) {
  carp_var_define(m, m->c.args[0].s, m->c.args[1].ll);
  carp_instr_NEXT(m);
}

definstr (DBG) {
  m->regs[CARP_EAX] = carp_var_get(m, m->c.args[0].s).value;
  carp_instr_NEXT(m);
}
