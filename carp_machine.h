#ifndef CARP_MACHINE_H
#define CARP_MACHINE_H

#include "stdlib.h"

#include "carp_types.h"

void carp_vm_init (carp_machine_state*);
void carp_vm_do (carp_instruction c[]);
void carp_vm_cleanup (carp_machine_state*);
void carp_vm_exit (carp_machine_state*, int);

#endif
