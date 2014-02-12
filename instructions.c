#include "instructions.h"

void instr_halt (int exitcode, int arg2, int arg3) {
  exit(exitcode);
}

void instr_loadi (int regnum, int val, int arg3) {
  regs[regnum] = val;
}

void instr_mov (int reg1, int reg2, int arg3) {
  regs[reg2] = regs[reg1];
}

void instr_add (int reg1, int reg2, int endreg) {
  regs[endreg] = regs[reg1] + regs[reg2];
}

void instr_sub (int reg1, int reg2, int endreg) {
  regs[endreg] = regs[reg1] - regs[reg2];
}

void instr_mul (int reg1, int reg2, int endreg) {
  regs[endreg] = regs[reg1] * regs[reg2];
}

void instr_div (int reg1, int reg2, int endreg) {
  regs[endreg] = regs[reg1] / regs[reg2];
}

void instr_incr (int regnum, int arg2, int arg3) {
  regs[regnum]++;
}

void instr_decr (int regnum, int arg2, int arg3) {
  regs[regnum]--;
}

void instr_show (int regnum, int arg2, int arg3) {
  printf("r: %d\n", regs[regnum]);
}
