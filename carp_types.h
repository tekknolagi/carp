#ifndef CARP_TYPES_H
#define CARP_TYPES_H

#include "carp_globals.h"
#include "carp_uthash.h"

typedef struct carp_char_list {
  char val;
  struct carp_char_list* next;
} carp_char_list;

union carp_argument {
  char* s;
  long long ll;
  carp_register_e r;
} carp_argument;

typedef struct carp_command {
  carp_instruction_e instr;
  union carp_argument args[CARP_NUM_ARGS];
} carp_command;

typedef struct carp_variable {
  char name[CARP_NAME_LENGTH];
  long long value;

  UT_hash_handle hh;
} carp_variable;

typedef struct carp_variable carp_label;

typedef struct carp_stack_type {
  long max_height;
  long height;
  long long* contents;
} carp_stack_type;

typedef struct carp_machine_state {
  carp_bool_e running;
  int pc;
  carp_command c;

  long long regs[CARP_NUM_REGS];
  carp_stack_type stack;
  carp_variable* vars;
  carp_variable* labels;
} carp_machine_state;

typedef struct carp_token {
  carp_token_e type;
  char* value;
  struct carp_token* next;
} carp_token;

#endif
