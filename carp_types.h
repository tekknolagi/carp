#ifndef CARP_TYPES_H
#define CARP_TYPES_H

#include "carp_globals.h"
#include "carp_uthash.h"

typedef union carp_argument {
  unsigned int i;
  carp_register r;
  long long ll;
  char s[CARP_NAME_LENGTH];
} carp_argument;

typedef struct carp_command {
  carp_instruction instr;
  carp_argument args[CARP_NUM_ARGS];
} carp_command;

typedef struct carp_variable {
  char name[CARP_NAME_LENGTH];
  long long value;

  UT_hash_handle hh;
} carp_variable;

typedef struct carp_stack_type {
  long max_height;
  long height;
  long long *contents;
} carp_stack_type;

typedef struct carp_machine_state {
  char running; // boolean
  int pc;
  carp_command c;

  long long regs[CARP_NUM_REGS];
  carp_stack_type stack;
  carp_variable *vars;
} carp_machine_state;

#endif
