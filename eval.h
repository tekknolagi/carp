#ifndef EVAL_H
#define EVAL_H

void eval (int instr, int arg1, int arg2, int arg3) {
  switch (instr) {
  case INSTR_HALT:
    exit(arg1);
    break;

  case INSTR_LOADI:
    regs[arg1] = arg2;
    break;

  case INSTR_ADD:
    regs[arg3] = regs[arg1] + regs[arg2];
    break;

  case INSTR_INCR:
    regs[arg1]++;
    break;

  case INSTR_SHOW:
    printf("r: %d\n", regs[arg1]);
    break;
  }
}

#endif
