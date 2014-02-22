#ifndef CARP_H
#define CARP_H

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

// dependency-less
#include "carp_messages.h"
#include "carp_uthash.h"
#include "carp_globals.h"

#include "carp_vars.h"
#include "carp_machine.h"
#include "carp_stack.h"
#include "carp_instructions.h"

// needs globals, uthash
#include "carp_vars.c"

// needs globals, stack, vars
#include "carp_machine.c"

// needds helpers
#include "carp_stack.c"

// needs globals, stack, vars
#include "carp_instructions.c"


#endif
