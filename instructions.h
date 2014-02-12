#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

void instr_halt  (machine_state*);
void instr_loadi (machine_state*);
void instr_mov   (machine_state*);
void instr_add   (machine_state*);
void instr_sub   (machine_state*);
void instr_mul   (machine_state*);
void instr_div   (machine_state*);
void instr_incr  (machine_state*);
void instr_decr  (machine_state*);
void instr_show  (machine_state*);

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
};

#endif
