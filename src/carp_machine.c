#include "carp_machine.h"

void carp_vm_init (carp_machine_state *m, long stack_height, long long main) {
  assert(m != NULL);
  assert(stack_height > 0);

  /* set all registers to 0, including:
   * - EIP
   * - ESP
   */
  for (int i = 0; i < CARP_NUM_REGS; i++)
    m->regs[i] = 0;

  // defined entrypoint (main)
  // -1 because EIP is incremented before each instr
  m->regs[CARP_EIP] = main - 1;

  // "turn VM on"
  m->running = 1;

  // initialize stack
  // give pointer to ESP
  int status = carp_stack_init(&m->stack, &m->regs[CARP_ESP], stack_height);
  if (status == -1)
    carp_vm_err(m, CARP_STACK_NO_MEM);

  // initialize variable hash table
  carp_ht_init(&m->vars);

  // initialize label hash table
  carp_ht_init(&m->labels);
}

void carp_vm_make (carp_machine_state *m) {
  for (int i = 0; i < CARP_NUM_REGS; i++)
    m->regs[i] = 0;

  carp_ht *res = carp_ht_get(m->labels, "main");
  if (res == NULL)
    carp_vm_err(m, CARP_VM_NO_MAIN);

  m->regs[CARP_EIP] = res->value - 1;

  m->running = 1;

  int status = carp_stack_init(m->stack, m->regs[CARP_ESP], 1);
  if (status == -1)
    carp_vm_err(m, CARP_STACK_NO_MEM);

  carp_ht_init(&m->vars);
}

void carp_vm_load (carp_machine_state *m, long long code[], carp_ht labels) {
  assert(m != NULL);

  m->code = code;
}

void carp_vm_eval (carp_machine_state *m) {
  assert(m != NULL);

  m->regs[CARP_EIP]++;

  //printf("instr: %s\n", carp_reverse_instr[m->code[m->regs[CARP_EIP]]]);

  // fetch instruction
  int instr = m->code[m->regs[CARP_EIP]];
  // decode, execute
  carp_instructions[instr](m);

  //carp_stack_print(&m->stack);
}

void carp_vm_run (carp_machine_state *m) {
  assert(m != NULL);

  while (m->running)
    carp_vm_eval(m);

  carp_vm_exit(m, 0);
}

long long carp_vm_next (carp_machine_state *m) {
  assert(m != NULL);

  return m->code[++m->regs[CARP_EIP]];
}

void carp_vm_err (carp_machine_state *m, char *e) {
  fprintf(stderr, e);
  puts("");
  carp_vm_exit(m, 1);
}

void carp_vm_cleanup (carp_machine_state *m) {
  assert(m != NULL);

  carp_stack_cleanup(&m->stack);
  carp_ht_cleanup(&m->vars);
  carp_ht_cleanup(&m->labels);
}

void carp_vm_exit (carp_machine_state *m, int code) {
  assert(m != NULL);

  m->running = 0;
  carp_vm_cleanup(m);
  exit(code);
}
