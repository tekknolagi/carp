#ifndef EVAL_H
#define EVAL_H

void eval (int instr, int arg1, int arg2, int arg3) {
  instructions[instr](arg1, arg2, arg3);
}

#endif
