#ifndef CARP_STACK_H
#define CARP_STACK_H

#include "stdio.h"
#include "stdlib.h"
#include "carp_machine.h"
#include "carp_types.h"

void carp_stack_init (carp_machine_state*, long);
carp_bool_e carp_stack_empty (carp_machine_state*);
carp_bool_e carp_stack_full (carp_machine_state*);
void carp_stack_push (carp_machine_state*, long long);
long long carp_stack_pop (carp_machine_state*);
void carp_stack_destroy (carp_machine_state*);

#endif
