#ifndef GLOBALS_H
#define GLOBALS_H

enum instruction_enum {
  INSTR_HALT ,
  INSTR_LOADI,
  INSTR_ADD  ,
  INSTR_INCR ,
  INSTR_SHOW ,
  NUM_ITEMS
};

unsigned regs[4];

void instr_halt  (int, int, int);
void instr_loadi (int, int, int);
void instr_add   (int, int, int);
void instr_incr  (int, int, int);
void instr_show  (int, int, int);

void (*instructions[NUM_ITEMS]) (int, int, int)  = {
  instr_halt ,
  instr_loadi,
  instr_add  ,
  instr_incr ,
  instr_show ,
};

#endif
