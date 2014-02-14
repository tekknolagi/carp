#ifndef CARP_STACK_H
#define CARP_STACK_H

typedef struct carp_stack_type {
  long max_height;
  long height;
  long long *contents;
} carp_stack_type;

void carp_stack_init (carp_stack_type*, long);
char carp_stack_empty (carp_stack_type*);
char carp_stack_full (carp_stack_type*);
void carp_stack_push (carp_stack_type*, long long);
long long carp_stack_pop (carp_stack_type*);
void carp_stack_destroy (carp_stack_type*);

#endif
