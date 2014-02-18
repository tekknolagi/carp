#ifndef CARP_VARS_H
#define CARP_VARS_H

#include "stdlib.h"

#include "carp_uthash.h"
#include "carp_globals.h"
#include "carp_machine.h"

void carp_var_delete (carp_machine_state*, char*);
void carp_var_define (carp_machine_state*, char*, long long);
carp_variable carp_var_get (carp_machine_state*, char*);
void carp_var_cleanup (carp_machine_state*);

#endif

