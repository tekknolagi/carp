#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

// this is where the declaration/definition macro comes in handy
definstr (HALT);
definstr (HALT);
definstr (NOP);
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

// create an array of function pointers to the instructions --
// this is useful in `eval`
void (*instructions[NUM_INSTRS]) (machine_state*)  = {
  [INSTR_HALT]  = instr_HALT ,
  [INSTR_NOP]   = instr_NOP  ,
  [INSTR_LOADI] = instr_LOADI,
  [INSTR_MOV]   = instr_MOV  ,
  [INSTR_ADD]   = instr_ADD  ,
  [INSTR_SUB]   = instr_SUB  ,
  [INSTR_MUL]   = instr_MUL  ,
  [INSTR_DIV]   = instr_DIV  ,
  [INSTR_INCR]  = instr_INCR ,
  [INSTR_DECR]  = instr_DECR ,
  [INSTR_SHOW]  = instr_SHOW ,
  [INSTR_PUSH]  = instr_PUSH ,
  [INSTR_POP]   = instr_POP  ,
  [INSTR_CMP]   = instr_CMP  ,
  [INSTR_JZ]    = instr_JZ   ,
  [INSTR_RJZ]   = instr_RJZ  ,
  [INSTR_JNZ]   = instr_JNZ  ,
  [INSTR_RJNZ]  = instr_RJNZ ,
  [INSTR_JMP]   = instr_JMP  ,
  [INSTR_RJMP]  = instr_RJMP ,
};

#endif
