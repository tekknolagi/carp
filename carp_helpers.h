#ifndef CARP_INSTRUCTION_HELPERS_H
#define CARP_INSTRUCTION_HELPERS_H

#include "stdio.h"
#include "string.h"
#include "stdlib.h"

#include "carp_globals.h"
#include "carp_types.h"
#include "carp_instructions.h"

definstr (NEXT);
void carp_eval (carp_machine_state*);
void carp_decode (carp_command*, carp_machine_state*);

#endif
