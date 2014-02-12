#include "stdio.h"
#include "stdlib.h"
#include "stack/stack.h"
#include "globals.h"

#include "stack/stack.c"
#include "instruction_helpers.c"
#include "instructions.c"
#include "init.c"

int main (int argc, char **argv) {
  machine_state mstate;
  init_vm(&mstate);

  unsigned program[] = {
    encode(INSTR_LOADI,  REG0,    12,     0), // loadi r0 12
    encode(INSTR_PUSH ,  11  ,     0,     0), // push 11
    encode(INSTR_POP  ,  REG1,     0,     0), // pop r1
    encode(INSTR_INCR ,  REG1,     0,     0), // incr r1
    encode(INSTR_ADD  ,  REG0,  REG1,  REG2), // add r0 r1 r2
    encode(INSTR_DECR ,  REG2,     0,     0), // decr r2
    encode(INSTR_SHOW ,  REG2,     0,     0), // show r2
    encode(INSTR_HALT ,     0,     0,     0), // halt 0
  };

  for (; mstate.running ;) {
    // print the "encoded" groups of 4 bits
    printf("i: "); printbits(program[mstate.regs[EIP]]);

    // decode the instruction and set state
    decode(program[mstate.regs[EIP]], &mstate);

    eval(&mstate);
  }
}
