#ifndef GLOBALS_H
#define GLOBALS_H

// max height of VM (initial)
#define VM_STACK_HEIGHT 100

// shortcut so I don't have to keep copy/pasting declarations & definitions
#define definstr(x) void instr_##x (machine_state* m)

// make instruction numbers easier on the eyes
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
  NUM_INSTRS ,
};

// make register numbers easier on the eyes
enum register_enum {
  // instruction pointer
  EIP  ,
  // regs 0 through 14 used... normally?
  REG0 ,
  REG1 ,
  REG2 ,
  REG3 ,
  REG4 ,
  REG5 ,
  REG6 ,
  REG7 ,
  REG8 ,
  REG9 ,
  REG10,
  REG11,
  REG12,
  REG13,
  REG14,
  NUM_REGS,
};

typedef struct machine_state {
  unsigned regs[NUM_REGS];
  int instr, arg1, arg2, arg3;
  int pc, running;
  stackT stack;
} machine_state;

#endif
