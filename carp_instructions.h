#ifndef CARP_INSTRUCTIONS_H
#define CARP_INSTRUCTIONS_H

#include "stdio.h"

#include "carp_globals.h"
#include "carp_types.h"
#include "carp_machine.h"
#include "carp_stack.h"

// this is where the declaration/definition macro comes in handy
definstr (HALT);
definstr (NOP);
definstr (NEXT);
definstr (LOADI);
definstr (MOV);
definstr (ADD);
definstr (SUB);
definstr (MUL);
definstr (DIV);
definstr (INCR);
definstr (DECR);
definstr (SHOW);
definstr (PUSH);
definstr (POP);
definstr (CMP);
definstr (JZ);
definstr (RJZ);
definstr (JNZ);
definstr (RJNZ);
definstr (JMP);
definstr (RJMP);
definstr (DBS);
definstr (DBG);
definstr (LBL);
definstr (CALL);

// create an array of function pointers to the instructions --
// this is useful in `eval`
void (*carp_instructions[CARP_NUM_INSTRS]) (carp_machine_state*)  = {
  [CARP_INSTR_HALT]  = carp_instr_HALT ,
  [CARP_INSTR_NOP]   = carp_instr_NOP  ,
  [CARP_INSTR_NEXT]  = carp_instr_NEXT ,
  [CARP_INSTR_LOADI] = carp_instr_LOADI,
  [CARP_INSTR_MOV]   = carp_instr_MOV  ,
  [CARP_INSTR_ADD]   = carp_instr_ADD  ,
  [CARP_INSTR_SUB]   = carp_instr_SUB  ,
  [CARP_INSTR_MUL]   = carp_instr_MUL  ,
  [CARP_INSTR_DIV]   = carp_instr_DIV  ,
  [CARP_INSTR_INCR]  = carp_instr_INCR ,
  [CARP_INSTR_DECR]  = carp_instr_DECR ,
  [CARP_INSTR_SHOW]  = carp_instr_SHOW ,
  [CARP_INSTR_PUSH]  = carp_instr_PUSH ,
  [CARP_INSTR_POP]   = carp_instr_POP  ,
  [CARP_INSTR_CMP]   = carp_instr_CMP  ,
  [CARP_INSTR_JZ]    = carp_instr_JZ   ,
  [CARP_INSTR_RJZ]   = carp_instr_RJZ  ,
  [CARP_INSTR_JNZ]   = carp_instr_JNZ  ,
  [CARP_INSTR_RJNZ]  = carp_instr_RJNZ ,
  [CARP_INSTR_JMP]   = carp_instr_JMP  ,
  [CARP_INSTR_RJMP]  = carp_instr_RJMP ,
  [CARP_INSTR_DBS]   = carp_instr_DBS  ,
  [CARP_INSTR_DBG]   = carp_instr_DBG  ,
  [CARP_INSTR_LBL]   = carp_instr_LBL  ,
  [CARP_INSTR_CALL]  = carp_instr_CALL ,
};

#endif
