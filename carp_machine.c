#include "carp_machine.h"

void carp_vm_init (carp_machine_state* m) {
  // set instruction pointer to 0
  for (int i = 0; i < CARP_NUM_REGS; i++) {
    m->regs[i] = 0;
  }

  // "turn VM on"
  m->running = CARP_FLAG_TRUE;

  // initialize stack
  carp_stack_init(m, CARP_STACK_HEIGHT);

  // initialize variable hash table
  m->vars = NULL;
}

void carp_vm_do (carp_machine_state* m, carp_command program[]) {
  while(m->running) {
    carp_command c = program[m->regs[CARP_EIP]];
    // decode the instruction and set state
    carp_decode(&c, m);

    carp_eval(m);
  }

  carp_vm_exit(m, 0);
}

void carp_vm_cleanup (carp_machine_state* m) {
  carp_stack_destroy(m);
  carp_var_cleanup(m);
}

void carp_vm_exit (carp_machine_state* m, int code) {
  carp_vm_cleanup(m);
  exit(code);
}
