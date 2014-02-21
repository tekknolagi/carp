#include "carp_stack.h"

void carp_stack_init (carp_machine_state* m, long max_height) {
  carp_stack_type* s = &m->stack;

  s->height = 0;
  s->max_height = max_height;
  long long* contents = malloc(max_height * sizeof(long long));
  if (contents == NULL) {
    fprintf(stderr, CARP_NO_MEM);
    carp_vm_exit(m, CARP_EX_MEM);
  }
  s->contents = contents;
}

char carp_stack_empty (carp_machine_state* m) {
  carp_stack_type* s = &m->stack;

  return s->height == 0;
}

char carp_stack_full (carp_machine_state* m) {
  carp_stack_type* s = &m->stack;

  return s->height == s->max_height;
}

void carp_stack_push (carp_machine_state* m, long long i) {
  carp_stack_type* s = &m->stack;

  if (carp_stack_full(m)) {
    long long* contents = realloc(s->contents, 5);
    if (contents == NULL) {
      fprintf(stderr, CARP_NO_MEM);
      carp_vm_exit(m, CARP_EX_MEM);
    }
    s->contents = contents;
  }
  else {
    s->contents[s->height] = i;
    s->height++;
  }
}

long long carp_stack_pop (carp_machine_state* m) {
  carp_stack_type* s = &m->stack;

  if (carp_stack_empty(m)) {
    fprintf(stderr, CARP_STACK_EMPTY);
    carp_vm_exit(m, CARP_EX_USAGE);
  }
  else {
    s->height--;
    long long i = s->contents[s->height];
    
    return i;
  }
  return CARP_EX_USAGE; // does not get here
}

void carp_stack_destroy (carp_machine_state* m) {
  carp_stack_type* s = &m->stack;

  free(s->contents);
  s->contents = NULL;
  s->max_height = 0;
  s->height = 0;
}
