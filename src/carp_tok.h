#ifndef CARP_TOK_H
#define CARP_TOK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "carp_machine.h"

#define CARP_TOK_WORD_LENGTH 10

typedef enum {
  CARP_TOK_UNDEF,
  CARP_TOK_NUM,
  CARP_TOK_LBL,
  CARP_TOK_INSTR,
  CARP_TOK_FUNC,
} carp_id;

typedef struct carp_tok_s {
  char lexeme[CARP_TOK_WORD_LENGTH];
  carp_id type;

  struct carp_tok_s *next;
} carp_tok;

#endif
