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

  // initialize label hash table
  m->labels = NULL;
}

void carp_vm_load (carp_command* c, carp_machine_state* m) {
  // copy command into machine state
  memcpy(&m->c, c, sizeof(carp_command));
}

void carp_vm_eval (carp_machine_state* m) {
  // get and execute the instruction
  carp_instructions[m->c.instr](m);
}

void carp_vm_do (carp_machine_state* m, carp_command program[]) {
  while(m->running) {
    carp_vm_load(&program[m->regs[CARP_EIP]], m);
    carp_vm_eval(m);
  }

  carp_vm_exit(m, CARP_EX_OK);
}

void carp_vm_cleanup (carp_machine_state* m) {
  carp_stack_destroy(m);
  carp_var_cleanup(m);
  carp_label_cleanup(m);
}

void carp_vm_exit (carp_machine_state* m, int code) {
  carp_vm_cleanup(m);
  exit(code);
}
