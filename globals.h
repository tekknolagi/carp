#ifndef GLOBALS_H
#define GLOBALS_H

// shortcut so I don't have to keep copy/pasting declarations & definitions
#define definstr(x) void instr_##x (machine_state* m)

#define NUM_ARGS 3

// max height of VM (initial)
#define VM_STACK_HEIGHT 100

typedef char bool;
enum bools {
  FLAG_FALSE, FLAG_TRUE,
};

// make instruction numbers easier on the eyes
enum instruction_enum {
  INSTR_HALT ,
  INSTR_NOP  ,
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
  INSTR_CMP  ,
  INSTR_JZ   ,
  INSTR_RJZ  ,
  INSTR_JNZ  ,
  INSTR_RJNZ ,
  INSTR_JMP  ,
  INSTR_RJMP ,
  NUM_INSTRS ,
};

// make register numbers easier on the eyes
enum register_enum {
  // regs 0 through 14 for general use
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

  // regs used for cmp, et al
  EAX  ,
  EDX  ,

  // instruction pointer
  EIP  ,

  NUM_REGS,
};

typedef struct instruction {
  int instr;
  long long args[NUM_ARGS];
} instruction;

typedef struct machine_state {
  bool running;
  int instr, pc;
  long long args[NUM_ARGS];

  long long regs[NUM_REGS];
  stackT stack;
} machine_state;

#endif
