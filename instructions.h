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

definstr (jz);
definstr (jnz);

definstr (je);
definstr (jne);

definstr (cmp);

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
  instr_jz   ,
  instr_jnz  ,
  instr_je   ,
  instr_jne  ,
  instr_cmp  ,
};

#endif
