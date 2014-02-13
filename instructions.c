#include "instructions.h"

definstr (halt) {
  puts("halting...");
  StackDestroy(&m->stack);
  exit((int) m->args[0]); // exit code
}

definstr (nop) {
  ;
  instr_next(m);
}

definstr (loadi) {
  m->regs[(int) m->args[0]] = m->args[1];
  instr_next(m);
}

definstr (mov) {
  m->regs[(int) m->args[0]] = m->regs[(int) m->args[1]];
  instr_next(m);
}

definstr (add) {
  m->regs[(int) m->args[0]] = m->regs[(int) m->args[1]] + m->regs[(int) m->args[2]]; // end = 1 + 2
  instr_next(m);
}

definstr (sub) {
  m->regs[(int) m->args[0]] = m->regs[(int) m->args[1]] - m->regs[(int) m->args[2]]; // end = 1 - 2
  instr_next(m);
}

definstr (mul) {
  m->regs[(int) m->args[0]] = m->regs[(int) m->args[1]] * m->regs[(int) m->args[12]]; // end = 1 * 2
  instr_next(m);
}

definstr (div) {
  m->regs[(int) m->args[0]] = m->regs[(int) m->args[1]] / m->regs[(int) m->args[2]]; // end = 1 / 2
  instr_next(m);
}

definstr (incr) {
  m->regs[(int) m->args[0]]++;
  instr_next(m);
}

definstr (decr) {
  m->regs[(int) m->args[0]]--;
  instr_next(m);
}

definstr (show) {
  printf("r%d: %lld\n", (int) m->args[0], m->regs[(int) m->args[0]]);
  instr_next(m);
}

definstr (push) {
  StackPush(&m->stack, m->args[0]); // push 1
  instr_next(m);
}

definstr (pop) {
  m->regs[(int) m->args[0]] = StackPop(&m->stack); // pop top into 1
  instr_next(m);
}

definstr (cmp) {
  m->regs[EAX] = m->regs[(int) m->args[0]] - m->regs[(int) m->args[1]];
  instr_next(m);
}

definstr (jz) {
  // zero
  if (!m->regs[EAX]) {
    m->regs[EIP] = m->args[0];
  }
  else {
    instr_nop(m);
  }
}

definstr (jnz) {
  // not zero
  if (m->regs[EAX]) {
    m->regs[EIP] = m->args[0];
  }
  else {
    instr_nop(m);
  }
}

definstr (rjz) {
  // zero
  if (!m->regs[EAX]) {
    m->regs[EIP] += m->args[0];
  }
  else {
    instr_nop(m);
  }
}

definstr (rjnz) {
  // not zero
  if (m->regs[EAX]) {
    m->regs[EIP] += m->args[0];
  }
  else {
    instr_nop(m);
  }
}
