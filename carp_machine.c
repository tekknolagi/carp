#include "carp_machine.h"

void carp_vm_init (carp_machine_state *m, long stack_height) {
  // set instruction pointer to 0
  for (int i = 0; i < CARP_NUM_REGS; i++) {
    m->regs[i] = 0;
  }

  // "turn VM on"
  m->running = 1;

  // initialize stack
  int status = carp_stack_init(&m->stack, stack_height);
  if (status == -1) {
    fprintf(stderr, CARP_STACK_NO_MEM);
    carp_vm_exit(m, status);
  }

  // initialize variable hash table
  carp_ht_init(&m->vars);

  // initialize label hash table
  carp_ht_init(&m->labels);
}

void carp_vm_load (carp_machine_state *m, long long code[]) {
  m->code = code;
}

void carp_vm_eval (carp_machine_state *m) {
  // get and execute the instruction
  int instr = m->code[m->regs[CARP_EIP]];
  //  printf("ip: %d\ninstr: %d\n\n", m->regs[CARP_EIP], instr);
  carp_instructions[instr](m);
  m->regs[CARP_EIP]++;
}

void carp_vm_run (carp_machine_state *m) {
  while (m->running)
    carp_vm_eval(m);

  carp_vm_exit(m, 0);
}

void carp_vm_cleanup (carp_machine_state *m) {
  m->running = 0;

  carp_stack_destroy(&m->stack);
  carp_ht_cleanup(&m->vars);
  carp_ht_cleanup(&m->labels);
}

void carp_vm_exit (carp_machine_state *m, int code) {
  carp_vm_cleanup(m);
  exit(code);
}
