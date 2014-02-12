#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

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

void (*instructions[NUM_ITEMS]) (machine_state*)  = {
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
};

#endif
