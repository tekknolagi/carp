#ifndef CARP_STACK_H
#define CARP_STACK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct carp_stack {
  long long max_height;
  long long *height;
  long long *contents;
} carp_stack;

short int carp_stack_init (carp_stack *, long long *, long long);
short int carp_stack_empty (carp_stack *);
short int carp_stack_full (carp_stack *);
short int carp_stack_push (carp_stack *, long long);
short int carp_stack_pop (carp_stack *, long long *);
short int carp_stack_peek (carp_stack *, long long *);
void carp_stack_print (carp_stack *);
void carp_stack_cleanup (carp_stack *);

#endif
