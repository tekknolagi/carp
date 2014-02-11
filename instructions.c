#include "instruction_set.h"
#include "instructions.h"

void (*instructions[NUM_ITEMS]) (int, int, int)  = {
  instr_halt ,
  instr_loadi,
  instr_add  ,
  instr_incr ,
  instr_show ,
};
