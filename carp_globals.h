#ifndef CARP_GLOBALS_H
#define CARP_GLOBALS_H

// shortcut so I don't have to keep copy/pasting declarations & definitions
#define definstr(x) void carp_instr_##x (carp_machine_state* m)

#define CARP_NUM_ARGS 3
#define CARP_NAME_LENGTH 10

// max stack height of VM (initial)
#define CARP_STACK_HEIGHT 100

typedef enum {
  CARP_TOK_INSTR, // instruction name
  CARP_TOK_PERC , // percent symbol
  CARP_TOK_DOLL , // dollar symbol
  CARP_TOK_LONG , // long int number
} carp_token;

typedef enum {
  CARP_FLAG_FALSE,
  CARP_FLAG_TRUE ,
} carp_bool;

typedef enum {
  CARP_EX_OK   ,
  CARP_EX_USAGE,
  CARP_EX_MEM  ,
} carp_exit_code;

// make instruction numbers easier on the eyes
typedef enum {
  CARP_INSTR_HALT ,
  CARP_INSTR_NOP  ,
  CARP_INSTR_NEXT ,
  CARP_INSTR_LOADI,
  CARP_INSTR_MOV  ,
  CARP_INSTR_ADD  ,
  CARP_INSTR_SUB  ,
  CARP_INSTR_MUL  ,
  CARP_INSTR_DIV  ,
  CARP_INSTR_INCR ,
  CARP_INSTR_DECR ,
  CARP_INSTR_SHOW ,
  CARP_INSTR_PUSH ,
  CARP_INSTR_POP  ,
  CARP_INSTR_CMP  ,
  CARP_INSTR_JZ   ,
  CARP_INSTR_RJZ  ,
  CARP_INSTR_JNZ  ,
  CARP_INSTR_RJNZ ,
  CARP_INSTR_JMP  ,
  CARP_INSTR_RJMP ,
  CARP_INSTR_DBS  ,
  CARP_INSTR_DBG  ,
  CARP_INSTR_LBL  ,
  CARP_INSTR_CALL ,
  CARP_NUM_INSTRS ,
} carp_instruction;

// make register numbers easier on the eyes
typedef enum {
  // regs 0 through 14 for general use
  CARP_REG0 ,
  CARP_REG1 ,
  CARP_REG2 ,
  CARP_REG3 ,
  CARP_REG4 ,
  CARP_REG5 ,
  CARP_REG6 ,
  CARP_REG7 ,
  CARP_REG8 ,
  CARP_REG9 ,
  CARP_REG10,
  CARP_REG11,
  CARP_REG12,
  CARP_REG13,
  CARP_REG14,

  // regs used for cmp, et al
  CARP_EAX  ,
  CARP_EDX  ,

  // instruction pointer
  CARP_EIP  ,

  CARP_NUM_REGS,
} carp_register;

#endif
