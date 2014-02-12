#ifndef GLOBALS_H
#define GLOBALS_H

enum instruction_enum {
  INSTR_HALT ,
  INSTR_LOADI,
  INSTR_MOV  ,
  INSTR_ADD  ,
  INSTR_SUB  ,
  INSTR_MUL  ,
  INSTR_DIV  ,
  INSTR_INCR ,
  INSTR_DECR ,
  INSTR_SHOW ,
  NUM_ITEMS
};

typedef struct machine_state {
  unsigned regs[4];
  int instr, arg1, arg2, arg3;
  int pc;
  int running;
} machine_state;

#endif
