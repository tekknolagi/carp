#ifndef CARP_LEXER_H
#define CARP_LEXER_H

#include "carp_tokenizer.h"
#include "carp_machine.h"

void carp_lex_lex (carp_machine_state *, carp_tok *);
void carp_lex_cleanup (carp_tok *);
void carp_lex_exit (carp_tok *, carp_ht *, int);

#endif
