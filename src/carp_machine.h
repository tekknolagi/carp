#ifndef CARP_MACHINE_H
#define CARP_MACHINE_H

#include <stdlib.h>
#include <assert.h>

#include "lib/carp_types.h"
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
  carp_value regs[CARP_NUM_REGS];
  carp_stack stack;
  carp_ht vars;
  carp_ht labels;

  carp_value *code;
} carp_machine_state;

void carp_vm_init (carp_machine_state *, long, carp_value);
void carp_vm_make (carp_machine_state *);
void carp_vm_load (carp_machine_state *, carp_value [], carp_value);
void carp_vm_eval (carp_machine_state *);
carp_value carp_vm_run (carp_machine_state *);
carp_value carp_vm_next (carp_machine_state *);
void carp_vm_err (carp_machine_state *, char *);
void carp_vm_cleanup (carp_machine_state *);
void carp_vm_exit (carp_machine_state *, int);

// shortcut so I don't have to keep copy/pasting declarations & definitions
#define CARP_IDEF(x) void carp_instr_##x (carp_machine_state *m)

// this is where the declaration/definition macro comes in handy
CARP_IDEF(HALT);
CARP_IDEF(NOP);
CARP_IDEF(LOAD); CARP_IDEF(GLOAD);
CARP_IDEF(MOV);
CARP_IDEF(ADD); CARP_IDEF(SUB); CARP_IDEF(MUL);
CARP_IDEF(MOD);
CARP_IDEF(NOT); CARP_IDEF(XOR); CARP_IDEF(OR); CARP_IDEF(AND);
CARP_IDEF(INCR); CARP_IDEF(DECR);
CARP_IDEF(INC); CARP_IDEF(DEC);
CARP_IDEF(PUSHR);
CARP_IDEF(PUSH); CARP_IDEF(POP);
CARP_IDEF(CMP); CARP_IDEF(LT); CARP_IDEF(GT);
CARP_IDEF(JZ); CARP_IDEF(RJZ);
CARP_IDEF(JNZ); CARP_IDEF(RJNZ);
CARP_IDEF(JMP); CARP_IDEF(RJMP);
CARP_IDEF(DBS); CARP_IDEF(DBG);
CARP_IDEF(CALL); CARP_IDEF(RET);
CARP_IDEF(PREG); CARP_IDEF(PTOP); CARP_IDEF(PVARS);

// shortcut so I don't have to keep copy/pasting array indices & whatnot
#define CARP_IASSN(x) [CARP_INSTR_##x] = carp_instr_##x

// create an array of function pointers to the instructions --
// this is useful in `eval`
static void (*carp_instructions[]) (carp_machine_state *) = {
  CARP_IASSN(HALT),
  CARP_IASSN(NOP),
  CARP_IASSN(LOAD), CARP_IASSN(GLOAD),
  CARP_IASSN(MOV),
  CARP_IASSN(ADD), CARP_IASSN(SUB), CARP_IASSN(MUL),
  CARP_IASSN(MOD),
  CARP_IASSN(NOT), CARP_IASSN(XOR), CARP_IASSN(OR), CARP_IASSN(AND),
  CARP_IASSN(INCR), CARP_IASSN(DECR),
  CARP_IASSN(INC), CARP_IASSN(DEC),
  CARP_IASSN(PUSHR),
  CARP_IASSN(PUSH), CARP_IASSN(POP),
  CARP_IASSN(CMP), CARP_IASSN(LT), CARP_IASSN(GT),
  CARP_IASSN(JZ), CARP_IASSN(RJZ),
  CARP_IASSN(JNZ), CARP_IASSN(RJNZ),
  CARP_IASSN(JMP), CARP_IASSN(RJMP),
  CARP_IASSN(DBS), CARP_IASSN(DBG),
  CARP_IASSN(CALL), CARP_IASSN(RET),
  CARP_IASSN(PREG), CARP_IASSN(PTOP), CARP_IASSN(PVARS),
};

#endif
