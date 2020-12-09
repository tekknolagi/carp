#include <stdlib.h>
#include <assert.h>

#include "lib/messages.h"
#include "lexer.h"
#include "machine.h"

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

  // initialize label hash table
  carp_ht_init(&m->labels, 10);
}

/* VM initialization for parsed code (since the labels will have
 * already been generated).  Would like to rename this at some
 * point.
 */
void carp_vm_make (carp_machine_state *m) {
  assert(m != NULL);
  assert(&m->labels != NULL);

  carp_reg_init(m->regs);

  carp_ht_entry *res = carp_ht_get(&m->labels, "main");
  if (!res) {
    carp_vm_err(m, CARP_VM_NO_MAIN);
  }
  else {
    carp_reg_set(m->regs, CARP_IP, res->value - 1);
    m->regs[CARP_RUN] = 1;
  }

  bool carp_stack_err = carp_stack_init(&m->stack, &m->regs[CARP_SP], 1);
  if (carp_stack_err == 1) {
    carp_vm_err(m, CARP_STACK_NO_MEM);
  }
}

/*
  Allocate space for the code, then load it.
*/
void carp_vm_load (carp_machine_state *m, carp_value code[], carp_value length) {
  assert(m != NULL);

  m->code = calloc(length, sizeof *code);
  if (m->code == NULL)
    carp_vm_err(m, CARP_CODE_NO_MEM);

  memcpy(m->code, code, length * sizeof *code);
}

/*
  Get the next instruction and execute it.
*/
void carp_vm_eval (carp_machine_state *m) {
  assert(m != NULL);

  carp_reg_inc(m->regs, CARP_IP);

  // fetch instruction
  carp_value instr = m->code[m->regs[CARP_IP]];

  // decode, execute
  carp_instructions[instr](m);
}

/*
  Start the fetch, decode, execute loop, then exit when done.
*/
carp_value carp_vm_run (carp_machine_state *m) {
  assert(m != NULL);

  while (m->regs[CARP_RUN]) {
    #ifdef CDEBUG
    carp_value instr = m->code[m->regs[CARP_IP]+1];
    printf("i: %s\n", carp_reverse_instr[instr]);
    #endif
    carp_vm_eval(m);
  }

  return m->regs[CARP_EXT];
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
void carp_vm_err (carp_machine_state *m, const char *e) {
  fprintf(stderr, "%s", e);
  putchar('\n');
  carp_vm_exit(m, EXIT_FAILURE);
}

/*
  Free the code, stack, variable table, and label table.
*/
void carp_vm_cleanup (carp_machine_state *m) {
  assert(m != NULL);

  free(m->code);
  carp_stack_cleanup(&m->stack);
  carp_ht_cleanup(&m->labels);
}

/*
  Change the machine state to OFF, clean up, and exit.
*/
void carp_vm_exit (carp_machine_state *m, int code) {
  assert(m != NULL);

  m->regs[CARP_RUN] = 0;
  m->regs[CARP_EXT] = code;
}

/*
  Read, tokenize, lex, and execute the contents of a Carp file.
*/
carp_value carp_run_program (const char *fn) {
  carp_machine_state m;
  carp_tok *tokens = carp_lex_tokenize(fn);

  if (tokens == NULL) {
    fprintf(stderr, "Something went wrong with tokenization.\n");
    exit(EXIT_FAILURE);
  }

  carp_lex_lex(&m, tokens);
  return carp_vm_run(&m);
}

// shortcut so I don't have to keep copy/pasting array indices & whatnot
#define CARP_IASSN(x) [CARP_INSTR_##x] = carp_instr_##x

static const carp_instruction_f carp_instructions[] = {
  CARP_IASSN(HALT),
  CARP_IASSN(NOP),
  CARP_IASSN(LOADR),
  CARP_IASSN(LOAD),
  CARP_IASSN(STORE),
  CARP_IASSN(MOV),
  CARP_IASSN(ADD),
  CARP_IASSN(SUB),
  CARP_IASSN(MUL),
  CARP_IASSN(MOD),
  CARP_IASSN(SHR),
  CARP_IASSN(SHL),
  CARP_IASSN(NOT),
  CARP_IASSN(XOR),
  CARP_IASSN(OR),
  CARP_IASSN(AND),
  CARP_IASSN(INCR),
  CARP_IASSN(DECR),
  CARP_IASSN(INC),
  CARP_IASSN(DEC),
  CARP_IASSN(PUSHR),
  CARP_IASSN(PUSH),
  CARP_IASSN(POP),
  CARP_IASSN(CMP),
  CARP_IASSN(LT),
  CARP_IASSN(GT),
  CARP_IASSN(JZ),
  CARP_IASSN(RJZ),
  CARP_IASSN(JNZ),
  CARP_IASSN(RJNZ),
  CARP_IASSN(JMP),
  CARP_IASSN(RJMP),
  CARP_IASSN(CALL),
  CARP_IASSN(RET),
  CARP_IASSN(PREG),
  CARP_IASSN(PTOP),
};
