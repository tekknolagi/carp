#ifndef _CARP_STACK_H_
#define _CARP_STACK_H_

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define CARP_STACK_NO_MEM  "Not enough memory.\n"
#define CARP_STACK_EMPTY "Carp stack is empty.\n"

typedef struct carp_stack {
  long max_height;
  long height;
  long long *contents;
} carp_stack;

int carp_stack_init (carp_stack *, long);
int carp_stack_empty (carp_stack *);
int carp_stack_full (carp_stack *);
int carp_stack_push (carp_stack *, long long);
long long carp_stack_pop (carp_stack *);
long long carp_stack_peek (carp_stack *);
void carp_stack_destroy (carp_stack *);

#endif
