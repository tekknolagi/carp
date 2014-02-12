#include "stdio.h"
#include "stdlib.h"
#include "stack/stack.h"
#include "globals.h"

#include "stack/stack.c"
#include "instructions.c"
#include "instruction_helpers.c"

int main (int argc, char **argv) {
  machine_state mstate;
  mstate.pc = 0;
  mstate.running = 1;
  StackInit(&mstate.stack, VM_STACK_HEIGHT);

  unsigned program[] = {
    encode(INSTR_LOADI,  0, 12,  0), // loadi r0 12
    encode(INSTR_PUSH ,  11, 0,  0), // push 11
    encode(INSTR_POP  ,  1,  0,  0), // pop r1
    encode(INSTR_INCR ,  1,  0,  0), // incr r1
    encode(INSTR_ADD  ,  0,  1,  2), // add r0 r1 r2
    encode(INSTR_DECR ,  2,  0,  0), // decr r2
    encode(INSTR_SHOW ,  2,  0,  0), // show r2
    encode(INSTR_HALT ,  0,  0,  0), // halt 0
  };

  for (mstate.pc = 0; mstate.running; mstate.pc++) {
    printf("i: "); printbits(program[mstate.pc]);
    decode(program[mstate.pc], &mstate);
    eval(&mstate);
  }
}
