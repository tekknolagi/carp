#ifndef CARP_TYPES_H
#define CARP_TYPES_H

#include "carp_globals.h"
#include "carp_uthash.h"

typedef struct carp_instruction {
  int instr;
  long long args[CARP_NUM_ARGS];
  char string_args[CARP_NUM_STRING_ARGS][CARP_NAME_LENGTH];
} carp_instruction;

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
  int instr, pc;
  long long args[CARP_NUM_ARGS];
  char string_args[CARP_NUM_STRING_ARGS][CARP_NAME_LENGTH];

  long long regs[CARP_NUM_REGS];
  carp_stack_type stack;
  carp_variable *vars;
} carp_machine_state;

#endif
