#ifndef CARP_STACK_H
#define CARP_STACK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#include "types.h"

typedef struct carp_stack {
  carp_value max_height;
  carp_value *height;
  carp_value *contents;
} carp_stack;

bool carp_stack_init (carp_stack *, carp_value *, carp_value);
bool carp_stack_empty (carp_stack *);
bool carp_stack_push (carp_stack *, carp_value);
bool carp_stack_pop (carp_stack *, carp_value *);
bool carp_stack_peek (carp_stack *, carp_value *);
void carp_stack_print (carp_stack *, FILE *);
void carp_stack_cleanup (carp_stack *);

#endif
