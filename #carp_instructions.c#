#include "carp_instructions.h"

definstr (HALT) {
  puts("halting...");
  carp_stack_destroy(&m->stack);
  exit((int) m->args[0]); // exit code
}

definstr (NOP) {
  carp_instr_NEXT(m);
}

definstr (LOADI) {
  m->regs[(int) m->args[0]] = m->args[1];
  carp_instr_NEXT(m);
}

definstr (MOV) {
  m->regs[(int) m->args[0]] = m->regs[(int) m->args[1]];
  carp_instr_NEXT(m);
}

definstr (ADD) {
  m->regs[(int) m->args[0]] = m->regs[(int) m->args[1]] + m->regs[(int) m->args[2]]; // end = 1 + 2
  carp_instr_NEXT(m);
}

definstr (SUB) {
  m->regs[(int) m->args[0]] = m->regs[(int) m->args[1]] - m->regs[(int) m->args[2]]; // end = 1 - 2
  carp_instr_NEXT(m);
}

definstr (MUL) {
  m->regs[(int) m->args[0]] = m->regs[(int) m->args[1]] * m->regs[(int) m->args[12]]; // end = 1 * 2
  carp_instr_NEXT(m);
}

definstr (DIV) {
  m->regs[(int) m->args[0]] = m->regs[(int) m->args[1]] / m->regs[(int) m->args[2]]; // end = 1 / 2
  carp_instr_NEXT(m);
}

definstr (INCR) {
  m->regs[(int) m->args[0]]++;
  carp_instr_NEXT(m);
}

definstr (DECR) {
  m->regs[(int) m->args[0]]--;
  carp_instr_NEXT(m);
}

definstr (SHOW) {
  printf("r%d: %lld\n", (int) m->args[0], m->regs[(int) m->args[0]]);
  carp_instr_NEXT(m);
}

definstr (PUSH) {
  carp_stack_push(&m->stack, m->args[0]); // push 1
  carp_instr_NEXT(m);
}

definstr (POP) {
  m->regs[(int) m->args[0]] = carp_stack_pop(&m->stack); // pop top into 1
  carp_instr_NEXT(m);
}

definstr (CMP) {
  m->regs[CARP_EAX] = m->regs[(int) m->args[0]] - m->regs[(int) m->args[1]];
  carp_instr_NEXT(m);
}

definstr (JZ) {
  // zero
  if (!m->regs[CARP_EAX]) {
    m->regs[CARP_EIP] = m->args[0];
  }
  else {
    carp_instr_NOP(m);
  }
}

definstr (RJZ) {
  // zero
  if (!m->regs[CARP_EAX]) {
    m->regs[CARP_EIP] += m->args[0];
  }
  else {
    carp_instr_NOP(m);
  }
}

definstr (JNZ) {
  // not zero
  if (m->regs[CARP_EAX]) {
    m->regs[CARP_EIP] = m->args[0];
  }
  else {
    carp_instr_NOP(m);
  }
}

definstr (RJNZ) {
  // not zero
  if (m->regs[CARP_EAX]) {
    m->regs[CARP_EIP] += m->args[0];
  }
  else {
    carp_instr_NOP(m);
  }
}

definstr (JMP) {
  m->regs[CARP_EIP] = m->args[0];
}

definstr (RJMP) {
  m->regs[CARP_EIP] += m->args[0];
}
