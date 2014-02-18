#include "carp_helpers.h"

// get and execute the instruction
void carp_eval (carp_machine_state *m) {
  carp_instructions[m->instr](m);
}

// "decode" the instruction & 3 args into machine state
void carp_decode (carp_instruction* i, carp_machine_state* m) {
  m->instr = i->instr;
  memcpy(m->args, i->args, sizeof(long long[CARP_NUM_ARGS]));
}
