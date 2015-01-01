#ifndef CARP_TOKENIZER_H
#define CARP_TOKENIZER_H

#include "lib/types.h"

#include "registers.h"
#include "instructions.h"

#define CARP_TOK_WORD_LENGTH 10

typedef enum {
  CARP_TOK_UNDEF,
  CARP_TOK_NUM,
  CARP_TOK_REG,
  CARP_TOK_LBL,
  CARP_TOK_FUNC,
  CARP_TOK_VAR,
  CARP_TOK_INSTR,
} carp_id;

extern char carp_reverse_type[][6];

typedef struct carp_tok_s {
  char lexeme[CARP_TOK_WORD_LENGTH];
  carp_id type;
  carp_value pos;
  carp_value value;

  struct carp_tok_s *next;
} carp_tok;

carp_tok *carp_lex_tokenize (const char *);
carp_reg carp_reg_lookup (const char *);
carp_instr carp_instr_lookup (const char *);

#endif
