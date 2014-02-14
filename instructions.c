#include "instructions.h"

definstr (HALT) {
  puts("halting...");
  stack_destroy(&m->stack);
  exit((int) m->args[0]); // exit code
}

definstr (NOP) {
  instr_NEXT(m);
}

definstr (LOADI) {
  m->regs[(int) m->args[0]] = m->args[1];
  instr_NEXT(m);
}

definstr (MOV) {
  m->regs[(int) m->args[0]] = m->regs[(int) m->args[1]];
  instr_NEXT(m);
}

definstr (ADD) {
  m->regs[(int) m->args[0]] = m->regs[(int) m->args[1]] + m->regs[(int) m->args[2]]; // end = 1 + 2
  instr_NEXT(m);
}

definstr (SUB) {
  m->regs[(int) m->args[0]] = m->regs[(int) m->args[1]] - m->regs[(int) m->args[2]]; // end = 1 - 2
  instr_NEXT(m);
}

definstr (MUL) {
  m->regs[(int) m->args[0]] = m->regs[(int) m->args[1]] * m->regs[(int) m->args[12]]; // end = 1 * 2
  instr_NEXT(m);
}

definstr (DIV) {
  m->regs[(int) m->args[0]] = m->regs[(int) m->args[1]] / m->regs[(int) m->args[2]]; // end = 1 / 2
  instr_NEXT(m);
}

definstr (INCR) {
  m->regs[(int) m->args[0]]++;
  instr_NEXT(m);
}

definstr (DECR) {
  m->regs[(int) m->args[0]]--;
  instr_NEXT(m);
}

definstr (SHOW) {
  printf("r%d: %lld\n", (int) m->args[0], m->regs[(int) m->args[0]]);
  instr_NEXT(m);
}

definstr (PUSH) {
  stack_push(&m->stack, m->args[0]); // push 1
  instr_NEXT(m);
}

definstr (POP) {
  m->regs[(int) m->args[0]] = stack_pop(&m->stack); // pop top into 1
  instr_NEXT(m);
}

definstr (CMP) {
  m->regs[EAX] = m->regs[(int) m->args[0]] - m->regs[(int) m->args[1]];
  instr_NEXT(m);
}

definstr (JZ) {
  // zero
  if (!m->regs[EAX]) {
    m->regs[EIP] = m->args[0];
  }
  else {
    instr_NOP(m);
  }
}

definstr (RJZ) {
  // zero
  if (!m->regs[EAX]) {
    m->regs[EIP] += m->args[0];
  }
  else {
    instr_NOP(m);
  }
}

definstr (JNZ) {
  // not zero
  if (m->regs[EAX]) {
    m->regs[EIP] = m->args[0];
  }
  else {
    instr_NOP(m);
  }
}

definstr (RJNZ) {
  // not zero
  if (m->regs[EAX]) {
    m->regs[EIP] += m->args[0];
  }
  else {
    instr_NOP(m);
  }
}

definstr (JMP) {
  m->regs[EIP] = m->args[0];
}

definstr (RJMP) {
  m->regs[EIP] += m->args[0];
}
