#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

void instr_halt (int exitcode, int arg2, int arg3) {
  exit(exitcode);
}

void instr_loadi (int regnum, int val, int arg3) {
  regs[regnum] = val;
}

void instr_add (int reg1, int reg2, int endreg) {
  regs[endreg] = regs[reg1] + regs[reg2];
}

void instr_incr (int regnum, int arg2, int arg3) {
  regs[regnum]++;
}

void instr_show (int regnum, int arg2, int arg3) {
  printf("r: %d\n", regs[regnum]);
}

#endif
