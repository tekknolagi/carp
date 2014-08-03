#ifndef CARP_LEX_H
#define CARP_LEX_H

#include "lib/carp_ht.h"
#include "carp_tokenizer.h"
#include "carp_machine.h"

void carp_lex_lex (carp_machine_state *, carp_tok *);
void carp_lex_exit (carp_tok *, carp_ht *, int);
carp_reg carp_reg_lookup (char *);
carp_instr carp_instr_lookup (char *);

#endif
