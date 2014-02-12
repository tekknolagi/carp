#include "instructions.h"

void instr_halt (machine_state *m) {
  StackDestroy(&m->stack);
  exit(m->arg1); // exit code
}

void instr_loadi (machine_state *m) {
  m->regs[m->arg1] = m->arg2;
}

void instr_mov (machine_state *m) {
  m->regs[m->arg1] = m->regs[m->arg2];
}

void instr_add (machine_state *m) {
  m->regs[m->arg3] = m->regs[m->arg1] + m->regs[m->arg2]; // end = 1 + 2
}

void instr_sub (machine_state *m) {
  m->regs[m->arg3] = m->regs[m->arg1] - m->regs[m->arg2]; // end = 1 - 2
}

void instr_mul (machine_state *m) {
  m->regs[m->arg3] = m->regs[m->arg1] * m->regs[m->arg2]; // end = 1 * 2
}

void instr_div (machine_state *m) {
  m->regs[m->arg3] = m->regs[m->arg1] / m->regs[m->arg2]; // end = 1 / 2
}

void instr_incr (machine_state *m) {
  m->regs[m->arg1]++;
}

void instr_decr (machine_state *m) {
  m->regs[m->arg1]--;
}

void instr_show (machine_state *m) {
  printf("r: %d\n", m->regs[m->arg1]);
}

void instr_push (machine_state *m) {
  StackPush(&m->stack, m->arg1); // push 1
}

void instr_pop (machine_state *m) {
  m->regs[m->arg1] = StackPop(&m->stack); // pop top into 1
}

void instr_jz (machine_state *m) {
  // TODO
}

void instr_jnz (machine_state *m) {
  // TODO
}
