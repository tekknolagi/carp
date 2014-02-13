#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stack/stack.h"
#include "globals.h"

#include "stack/stack.c"
#include "instruction_helpers.c"
#include "instructions.c"
#include "init.c"

int main (int argc, char **argv) {
  machine_state mstate;
  init_vm(&mstate);

  instruction program[] = {
    encode(INSTR_LOADI,  REG0,    12,     0), // loadi r0 12
    encode(INSTR_PUSH ,    11,     0,     0), // push 11
    encode(INSTR_POP  ,  REG1,     0,     0), // pop r1
    encode(INSTR_INCR ,  REG1,     0,     0), // incr r1
    encode(INSTR_ADD  ,  REG2,  REG0,  REG1), // add r2 r0 r1
    encode(INSTR_DECR ,  REG2,     0,     0), // decr r2
    encode(INSTR_SHOW ,  REG2,     0,     0), // show r2
    encode(INSTR_CMP  ,  REG0,  REG0,     0), // cmp r0 r0
    encode(INSTR_RJZ  ,     2,     0,     0), // rjnz 1 (jump forward +1 if
                                              // eax is 0
    encode(INSTR_SHOW ,  REG2,     0,     0), // see if skipped
    encode(INSTR_HALT ,     0,     0,     0), // halt 0
  };

  while(mstate.running) {
    instruction i = program[mstate.regs[EIP]];
    // decode the instruction and set state
    decode(&i, &mstate);

    // print the "encoded" groups of 16 bits
    // print_instr(&i, &mstate);

    eval(&mstate);
  }
}
