#include "carp_helpers.h"

// get and execute the instruction
void carp_eval (carp_machine_state* m) {
  carp_instructions[m->c.instr](m);
}

// "decode" the instruction & 3 args into machine state
void carp_decode (carp_command* c, carp_machine_state* m) {
  m->c = *c;
  memcpy(m->c.args, c->args, sizeof(carp_argument[CARP_NUM_ARGS]));
}
