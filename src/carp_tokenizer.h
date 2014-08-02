#ifndef CARP_TOK_H
#define CARP_TOK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#include "carp_registers.h"
#include "carp_instructions.h"

#define CARP_TOK_WORD_LENGTH 10

// shortcut
#define ct(x) CARP_TOK_##x

typedef enum {
  ct(UNDEF),
  ct(NUM),
  ct(REG),
  ct(LBL),
  ct(INSTR),
  ct(FUNC),
} carp_id;

static char carp_reverse_type[][6] = {
  "undef","num","reg","lbl","instr","func"
};

typedef struct carp_tok_s {
  char lexeme[CARP_TOK_WORD_LENGTH];
  carp_id type;
  long long pos;
  long long val;

  struct carp_tok_s *next;
} carp_tok;

carp_tok *carp_lex_tokenize (char *);
void carp_lex_cleanup (carp_tok *);
void *file_read (char *);
int is_sign (char);
int is_num (char *);
char *is_reg (char *);
char *is_label (char *);
int is_instr (char *);
char *is_func (char *);


#endif
