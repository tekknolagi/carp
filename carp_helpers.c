#include "carp_instructions.h"
#include "carp_helpers.h"

// increment instruction pointer
definstr (NEXT) {
  m->regs[CARP_EIP]++;
}

// get and execute the instruction
void carp_eval (carp_machine_state *m) {
  carp_instructions[m->instr](m);
}

// "encode" the instruction & 3 args into a 16 bit integer
carp_instruction carp_encode (int instr, long long arg1, long long arg2, long long arg3) {
  carp_instruction i;
  i.instr = instr;
  memcpy(i.args,
	 ((long long[CARP_NUM_ARGS]){arg1, arg2, arg3}), // need extra parentheses otherwise memcpy macro barfs
	 sizeof(long long[CARP_NUM_ARGS]));

  return i;
}

// "decode" the instruction & 3 args into machine state
void carp_decode (carp_instruction* i, carp_machine_state* m) {
  m->instr = i->instr;
  memcpy(m->args, i->args, sizeof(long long[CARP_NUM_ARGS]));
}

void carp_init_vm (carp_machine_state *m) {
  // set instruction pointer to 0
  for (int i = 0; i < CARP_NUM_REGS; i++) {
    m->regs[i] = 0;
  }

  // "turn VM on"
  m->running = CARP_FLAG_TRUE;

  // initialize stack
  carp_stack_init(&m->stack, CARP_STACK_HEIGHT);
}

void carp_vm_do (carp_instruction program[]) {
  carp_machine_state mstate;
  carp_init_vm(&mstate);

  while(mstate.running) {
    carp_instruction i = program[mstate.regs[CARP_EIP]];
    // decode the instruction and set state
    carp_decode(&i, &mstate);

    carp_eval(&mstate);
  }
}
