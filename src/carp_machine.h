#ifndef CARP_MACHINE_H
#define CARP_MACHINE_H

#include <stdlib.h>
#include <assert.h>

#include "carp_registers.h"
#include "carp_instructions.h"
#include "lib/carp_stack.h"
#include "lib/carp_ht.h"

#define CARP_VM_NO_MAIN "Could not find main."

#define CARP_EXIT_STACK_FAILED "Could not initialize stack."
#define CARP_STACK_NO_MEM  "Not enough memory."
#define CARP_STACK_EMPTY "Carp stack is empty."

#define CARP_HT_DNE "Variable not defined."
#define CARP_HT_NO_MEM "Not enough memory."
#define CARP_HT_CONTENTS_NULL "Could not get. Contents NULL."

typedef struct carp_machine_state_s {
  long long regs[CARP_NUM_REGS];
  carp_stack stack;
  carp_ht vars;
  carp_ht labels;

  // bool
  int running;
  long long *code;
} carp_machine_state;

void carp_vm_init (carp_machine_state *, long, long long);
void carp_vm_make (carp_machine_state *);
void carp_vm_load (carp_machine_state *, long long []);
void carp_vm_eval (carp_machine_state *);
void carp_vm_run (carp_machine_state *);
long long carp_vm_next (carp_machine_state *);
void carp_vm_err (carp_machine_state *, char *);
void carp_vm_cleanup (carp_machine_state *);
void carp_vm_exit (carp_machine_state *, int);

// shortcut so I don't have to keep copy/pasting declarations & definitions
#define definstr(x) void carp_instr_##x (carp_machine_state *m)

// this is where the declaration/definition macro comes in handy
definstr(HALT);
definstr(NOP);
definstr(LOAD); definstr(GLOAD);
definstr(MOV);
definstr(ADD); definstr(SUB); definstr(MUL);
definstr(MOD); definstr(REM);
definstr(NOT); definstr(XOR); definstr(OR); definstr(AND);
definstr(INCR); definstr(DECR);
definstr(INC); definstr(DEC);
definstr(PUSHR);
definstr(PUSH); definstr(POP);
definstr(CMP);
definstr(JZ); definstr(RJZ);
definstr(JNZ); definstr(RJNZ);
definstr(JMP); definstr(RJMP);
definstr(DBS); definstr(DBG);
definstr(CALL); definstr(RET);
definstr(PREG); definstr(PTOP);

// shortcut so I don't have to keep copy/pasting array indices & whatnot
#define assigninstr(x) [CARP_INSTR_##x] = carp_instr_##x

// create an array of function pointers to the instructions --
// this is useful in `eval`
static void (*carp_instructions[]) (carp_machine_state *) = {
  assigninstr(HALT),
  assigninstr(NOP),
  assigninstr(LOAD), assigninstr(GLOAD),
  assigninstr(MOV),
  assigninstr(ADD), assigninstr(SUB), assigninstr(MUL),
  assigninstr(MOD), assigninstr(REM),
  assigninstr(NOT), assigninstr(XOR), assigninstr(OR), assigninstr(AND),
  assigninstr(INCR), assigninstr(DECR),
  assigninstr(INC), assigninstr(DEC),
  assigninstr(PUSHR),
  assigninstr(PUSH), assigninstr(POP),
  assigninstr(CMP),
  assigninstr(JZ), assigninstr(RJZ),
  assigninstr(JNZ), assigninstr(RJNZ),
  assigninstr(JMP), assigninstr(RJMP),
  assigninstr(DBS), assigninstr(DBG),
  assigninstr(CALL), assigninstr(RET),
  assigninstr(PREG), assigninstr(PTOP),
};

#endif
