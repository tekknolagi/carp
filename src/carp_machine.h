#ifndef CARP_MACHINE_H
#define CARP_MACHINE_H

#include "lib/carp_types.h"
#include "lib/carp_stack.h"
#include "lib/carp_ht.h"

#include "carp_registers.h"
#include "carp_instructions.h"

typedef struct carp_machine_state_s {
  carp_value regs[CARP_NUM_REGS];
  carp_stack stack;
  carp_ht vars;
  carp_ht labels;

  carp_value *code;
} carp_machine_state;

void carp_vm_init(carp_machine_state *, long, carp_value);
void carp_vm_make(carp_machine_state *);
void carp_vm_load(carp_machine_state *, carp_value [], carp_value);
void carp_vm_eval(carp_machine_state *);
carp_value carp_vm_run(carp_machine_state *);
carp_value carp_vm_next(carp_machine_state *);
void carp_vm_err(carp_machine_state *, const char *);
void carp_vm_cleanup(carp_machine_state *);
void carp_vm_exit(carp_machine_state *, int);

carp_value carp_run_program (const char *);

// shortcut so I don't have to keep copy/pasting declarations & definitions
#define CARP_IDEF(x) void carp_instr_##x \
  (__attribute__((unused)) carp_machine_state *m)
// #define CARP_IDECL(x) void carp_instr_##x (carp_machine_state *)

// this is where the declaration/definition macro comes in handy
CARP_IDEF(HALT);
CARP_IDEF(NOP);
CARP_IDEF(LOADR); CARP_IDEF(LOAD); CARP_IDEF(STORE);
CARP_IDEF(MOV);
CARP_IDEF(ADD); CARP_IDEF(SUB); CARP_IDEF(MUL);
CARP_IDEF(MOD);
CARP_IDEF(SHR); CARP_IDEF(SHL);
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

// pointer to carp_instruction function
typedef void (*carp_instruction_f) (carp_machine_state *);

// create an array of function pointers to the instructions --
// this is useful in `eval`
carp_instruction_f carp_instructions[CARP_NUM_INSTRS];

#endif
