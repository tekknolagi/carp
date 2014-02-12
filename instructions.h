#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

// this is where the declaration/definition macro comes in handy
definstr (halt);
definstr (nop);

definstr (loadi);
definstr (mov);

definstr (add);
definstr (sub);
definstr (mul);
definstr (div);

definstr (incr);
definstr (decr);

definstr (show);

definstr (push);
definstr (pop);

definstr (cmp);

definstr (jz);
definstr (jnz);

definstr (rjz);
definstr (rjnz);

// create an array of function pointers to the instructions --
// this is useful in `eval`
void (*instructions[NUM_INSTRS]) (machine_state*)  = {
  [INSTR_HALT]  = instr_halt ,
  [INSTR_NOP]   = instr_nop  ,
  [INSTR_LOADI] = instr_loadi,
  [INSTR_MOV]   = instr_mov  ,
  [INSTR_ADD]   = instr_add  ,
  [INSTR_SUB]   = instr_sub  ,
  [INSTR_MUL]   = instr_mul  ,
  [INSTR_DIV]   = instr_div  ,
  [INSTR_INCR]  = instr_incr ,
  [INSTR_DECR]  = instr_decr ,
  [INSTR_SHOW]  = instr_show ,
  [INSTR_PUSH]  = instr_push ,
  [INSTR_POP]   = instr_pop  ,
  [INSTR_CMP]   = instr_cmp  ,
  [INSTR_JZ]    = instr_jz   ,
  [INSTR_JNZ]   = instr_jnz  ,
  [INSTR_RJZ]   = instr_rjz  ,
  [INSTR_RJNZ]  = instr_rjnz ,
};

#endif
