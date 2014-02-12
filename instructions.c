#include "instructions.h"

definstr (halt) {
  StackDestroy(&m->stack);
  exit(m->arg1); // exit code
}

definstr (loadi) {
  m->regs[m->arg1] = m->arg2;
  instr_next(m);
}

definstr (mov) {
  m->regs[m->arg1] = m->regs[m->arg2];
  instr_next(m);
}

definstr (add) {
  m->regs[m->arg3] = m->regs[m->arg1] + m->regs[m->arg2]; // end = 1 + 2
  instr_next(m);
}

definstr (sub) {
  m->regs[m->arg3] = m->regs[m->arg1] - m->regs[m->arg2]; // end = 1 - 2
  instr_next(m);
}

definstr (mul) {
  m->regs[m->arg3] = m->regs[m->arg1] * m->regs[m->arg2]; // end = 1 * 2
  instr_next(m);
}

definstr (div) {
  m->regs[m->arg3] = m->regs[m->arg1] / m->regs[m->arg2]; // end = 1 / 2
  instr_next(m);
}

definstr (incr) {
  m->regs[m->arg1]++;
  instr_next(m);
}

definstr (decr) {
  m->regs[m->arg1]--;
  instr_next(m);
}

definstr (show) {
  printf("r: %d\n", m->regs[m->arg1]);
  instr_next(m);
}

definstr (push) {
  StackPush(&m->stack, m->arg1); // push 1
  instr_next(m);
}

definstr (pop) {
  m->regs[m->arg1] = StackPop(&m->stack); // pop top into 1
  instr_next(m);
}

definstr (cmp) {
  m->regs[EAX] = m->regs[m->arg1] - m->regs[m->arg2];
}

definstr (jz) {
  // TODO
  if (!m->regs[EAX]) {

  }
  else {

  }
}

definstr (jnz) {
  // TODO
  if (m->regs[EAX]) {

  }
  else {

  }
}
