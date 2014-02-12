#ifndef GLOBALS_H
#define GLOBALS_H

#define VM_STACK_HEIGHT 100
#define definstr(x) void instr_##x (machine_state*)

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
  INSTR_PUSH ,
  INSTR_POP  ,
  INSTR_JZ   ,
  INSTR_JNZ  ,
  NUM_ITEMS
};

typedef struct machine_state {
  unsigned regs[4];
  int instr, arg1, arg2, arg3;
  int pc, running;
  stackT stack;
} machine_state;

#endif
