#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

void instr_halt  (int, int, int);
void instr_loadi (int, int, int);
void instr_mov   (int, int, int);
void instr_add   (int, int, int);
void instr_sub   (int, int, int);
void instr_mul   (int, int, int);
void instr_div   (int, int, int);
void instr_incr  (int, int, int);
void instr_decr  (int, int, int);
void instr_show  (int, int, int);

void (*instructions[NUM_ITEMS]) (int, int, int)  = {
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
