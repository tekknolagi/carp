#include "instructions.h"

definstr (halt) {
  StackDestroy(&m->stack);
  exit(m->arg1); // exit code
}

definstr (loadi) {
  m->regs[m->arg1] = m->arg2;
}

definstr (mov) {
  m->regs[m->arg1] = m->regs[m->arg2];
}

definstr (add) {
  m->regs[m->arg3] = m->regs[m->arg1] + m->regs[m->arg2]; // end = 1 + 2
}

definstr (sub) {
  m->regs[m->arg3] = m->regs[m->arg1] - m->regs[m->arg2]; // end = 1 - 2
}

definstr (mul) {
  m->regs[m->arg3] = m->regs[m->arg1] * m->regs[m->arg2]; // end = 1 * 2
}

definstr (div) {
  m->regs[m->arg3] = m->regs[m->arg1] / m->regs[m->arg2]; // end = 1 / 2
}

definstr (incr) {
  m->regs[m->arg1]++;
}

definstr (decr) {
  m->regs[m->arg1]--;
}

definstr (show) {
  printf("r: %d\n", m->regs[m->arg1]);
}

definstr (push) {
  StackPush(&m->stack, m->arg1); // push 1
}

definstr (pop) {
  m->regs[m->arg1] = StackPop(&m->stack); // pop top into 1
}

definstr (jz) {
  // TODO
  // need to implement instruction pointers and whatnot
}

definstr (jnz) {
  // TODO
}
