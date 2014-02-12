#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

// this is where the declaration/definition macro comes in handy
definstr (halt);

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

// create an array of function pointers to the instructions --
// this is useful in `eval`
void (*instructions[NUM_INSTRS]) (machine_state*)  = {
  instr_halt ,
  instr_loadi,
  instr_mov  ,
  instr_add  ,
  instr_sub  ,
  instr_mul  ,
  instr_div  ,
  instr_incr ,
  instr_decr ,
  instr_show ,
  instr_push ,
  instr_pop  ,
  instr_cmp  ,
  instr_jz   ,
  instr_jnz  ,
};

#endif
