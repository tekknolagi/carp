#ifndef CARP_VARS_H
#define CARP_VARS_H

#include "stdlib.h"

#include "carp_uthash.h"
#include "carp_globals.h"
#include "carp_machine.h"

void carp_label_delete (carp_machine_state*, char*);
void carp_label_define (carp_machine_state*, char*, long long);
carp_label carp_label_get (carp_machine_state*, char*);
void carp_label_cleanup (carp_machine_state*);

#endif

