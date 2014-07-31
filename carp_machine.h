#ifndef CARP_MACHINE_H
#define CARP_MACHINE_H

#include <stdlib.h>
#include <assert.h>

#include "lib/carp_stack.h"
#include "lib/carp_ht.h"

#define CARP_EXIT_STACK_FAILED "Could not initialize stack.\n"
#define CARP_STACK_NO_MEM  "Not enough memory.\n"
#define CARP_STACK_EMPTY "Carp stack is empty.\n"

#define CARP_HT_DNE "Variable not defined.\n"
#define CARP_HT_NO_MEM "Not enough memory.\n"
#define CARP_HT_CONTENTS_NULL "Could not get. Contents NULL.\n"

// make register numbers easier on the eyes
enum {
  // regs 0 through 9 for general use
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

  // regs used for cmp, et al
  CARP_EAX  ,
  CARP_EDX  ,

  // instruction pointer
  CARP_EIP  ,

  // stack pointer
  CARP_ESP  ,

  // frame pointer
  CARP_EFP  ,

  // garbage reg for pop
  CARP_GBG  ,

  CARP_NUM_REGS,
};

// make instruction numbers easier on the eyes
enum {
  CARP_INSTR_HALT ,
  CARP_INSTR_NOP  ,
  CARP_INSTR_LOADI,
  CARP_INSTR_MOV  ,
  CARP_INSTR_ADDI ,
  CARP_INSTR_SUBI ,
  CARP_INSTR_MULI ,
  CARP_INSTR_INCR ,
  CARP_INSTR_DECR ,
  CARP_INSTR_PUSHR,
  CARP_INSTR_PUSHI,
  CARP_INSTR_POPI ,
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
  CARP_INSTR_RET  ,
  CARP_INSTR_PREG ,
  CARP_INSTR_PTOP ,

  CARP_NUM_INSTRS ,
};

typedef struct carp_machine_state {
  long long regs[CARP_NUM_REGS];
  carp_stack stack;
  carp_ht vars;
  carp_ht labels;

  // bool
  int running;
  long long *code;
} carp_machine_state;

void carp_vm_init (carp_machine_state *, long);
void carp_vm_load (carp_machine_state *, long long []);
void carp_vm_eval (carp_machine_state *);
void carp_vm_run (carp_machine_state *);
void carp_vm_cleanup (carp_machine_state *);
void carp_vm_exit (carp_machine_state *, int);

// shortcut so I don't have to keep copy/pasting declarations & definitions
#define definstr(x) void carp_instr_##x (carp_machine_state *m)

// this is where the declaration/definition macro comes in handy
definstr(HALT);
definstr(NOP);
definstr(LOADI);
definstr(MOV);
definstr(ADDI); definstr(SUBI); definstr(MULI);
definstr(INCR); definstr(DECR);
definstr(PUSHR);
definstr(PUSHI); definstr(POPI);
definstr(CMP);
definstr(JZ); definstr(RJZ);
definstr(JNZ); definstr(RJNZ);
definstr(JMP); definstr(RJMP);
definstr(DBS); definstr(DBG);
definstr(LBL); definstr(CALL); definstr(RET);
definstr(PREG); definstr(PTOP);

// shortcut so I don't have to keep copy/pasting array indices & whatnot
#define assigninstr(x) [CARP_INSTR_##x] = carp_instr_##x

// create an array of function pointers to the instructions --
// this is useful in `eval`
static void (*carp_instructions[]) (carp_machine_state *) = {
  assigninstr(HALT),
  assigninstr(NOP),
  assigninstr(LOADI),
  assigninstr(MOV),
  assigninstr(ADDI), assigninstr(SUBI), assigninstr(MULI),
  assigninstr(INCR), assigninstr(DECR),
  assigninstr(PUSHR),
  assigninstr(PUSHI), assigninstr(POPI),
  assigninstr(CMP),
  assigninstr(JZ), assigninstr(RJZ),
  assigninstr(JNZ), assigninstr(RJNZ),
  assigninstr(JMP), assigninstr(RJMP),
  assigninstr(DBS), assigninstr(DBG),
  assigninstr(LBL), assigninstr(CALL), assigninstr(RET),
  assigninstr(PREG), assigninstr(PTOP),
};

#endif
