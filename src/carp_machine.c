#include <stdlib.h>
#include <assert.h>

#include "lib/carp_messages.h"
#include "carp_machine.h"

/*
  Initialize the VM - this includes lots of allocation.
*/
void carp_vm_init (carp_machine_state *m, long stack_height, carp_value main_addr) {
  assert(m != NULL);
  assert(stack_height > 0);

  /* set all registers to 0, including:
   * - IP
   * - SP
   */
  carp_reg_init(m->regs);

  // defined entrypoint (main)
  // -1 because IP is incremented before each instr
  carp_reg_set(m->regs, CARP_IP, main_addr - 1);

  // "turn VM on"
  m->regs[CARP_RUN] = 1;

  // initialize stack
  // give pointer to SP
  int status = carp_stack_init(&m->stack, &m->regs[CARP_SP], stack_height);
  if (status == 1)
    carp_vm_err(m, CARP_STACK_NO_MEM);

  // initialize variable hash table
  carp_ht_init(&m->vars);

  // initialize label hash table
  carp_ht_init(&m->labels);
}

/*
  VM initialization for parsed code (since the labels will have already been generated).
  Would like to rename this at some point.
*/
void carp_vm_make (carp_machine_state *m) {
  assert(m != NULL);
  assert(&m->labels != NULL);

  carp_reg_init(m->regs);

  carp_ht *res = carp_ht_get(&m->labels, "main");
  if (res == NULL)
    carp_vm_err(m, CARP_VM_NO_MAIN);

  carp_reg_set(m->regs, CARP_IP, res->value - 1);

  m->regs[CARP_RUN] = 1;

  int status = carp_stack_init(&m->stack, &m->regs[CARP_SP], 1);
  if (status == 1)
    carp_vm_err(m, CARP_STACK_NO_MEM);

  carp_ht_init(&m->vars);
}

/*
  Allocate space for the code, then load it.
*/
void carp_vm_load (carp_machine_state *m, carp_value code[], carp_value length) {
  assert(m != NULL);

  m->code = calloc(length, sizeof *code);
  if (m->code == NULL)
    carp_vm_err(m, "Could not allocate memory for code.");

  memcpy(m->code, code, length * sizeof *code);
}

/*
  Get the next instruction and execute it.
*/
void carp_vm_eval (carp_machine_state *m) {
  assert(m != NULL);

  carp_reg_inc(m->regs, CARP_IP);

  // fetch instruction
  int instr = m->code[m->regs[CARP_IP]];

  // decode, execute
  carp_instructions[instr](m);
}

/*
  Start the fetch, decode, execute loop, then exit when done.
*/
carp_value carp_vm_run (carp_machine_state *m) {
  assert(m != NULL);

  while (m->regs[CARP_RUN])
    carp_vm_eval(m);

  return m->regs[CARP_EXT];
  //carp_vm_exit(m, EXIT_SUCCESS);
}

/*
  Increment the instruction pointer and return the next value in the code.
*/
carp_value carp_vm_next (carp_machine_state *m) {
  assert(m != NULL);

  return m->code[++m->regs[CARP_IP]];
}

/*
  Writes an error message to stderr, then signals for the machine
  to cleanly exit.
*/
void carp_vm_err (carp_machine_state *m, char *e) {
  fprintf(stderr, e);
  putchar('\n');
  carp_vm_exit(m, EXIT_FAILURE);
}

/*
  Free the code, stack, varible table, and label table.
*/
void carp_vm_cleanup (carp_machine_state *m) {
  assert(m != NULL);

  free(m->code);
  carp_stack_cleanup(&m->stack);
  carp_ht_cleanup(&m->vars);
  carp_ht_cleanup(&m->labels);
}

/*
  Change the machine state to OFF, clean up, and exit.
*/
void carp_vm_exit (carp_machine_state *m, int code) {
  assert(m != NULL);

  m->regs[CARP_RUN] = 0;
  m->regs[CARP_EXT] = code;
  carp_vm_cleanup(m);
}
