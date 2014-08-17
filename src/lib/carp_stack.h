#ifndef CARP_STACK_H
#define CARP_STACK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "carp_types.h"

typedef struct carp_stack {
  carp_value max_height;
  carp_value *height;
  carp_value *contents;
} carp_stack;

carp_bool carp_stack_init (carp_stack *, carp_value *, carp_value);
carp_bool carp_stack_empty (carp_stack *);
static inline carp_bool carp_stack_full (carp_stack *);
carp_bool carp_stack_push (carp_stack *, carp_value);
carp_bool carp_stack_pop (carp_stack *, carp_value *);
carp_bool carp_stack_peek (carp_stack *, carp_value *);
void carp_stack_print (carp_stack *, FILE *);
void carp_stack_cleanup (carp_stack *);

#endif
