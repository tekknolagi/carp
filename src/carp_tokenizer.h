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
  ct(FUNC),
  ct(VAR),
  ct(INSTR),
} carp_id;

static char carp_reverse_type[][6] = {
  "undef","num","reg","lbl","func","var","instr"
};

typedef struct carp_tok_s {
  char lexeme[CARP_TOK_WORD_LENGTH];
  carp_id type;
  long long pos;
  long long value;

  struct carp_tok_s *next;
} carp_tok;

carp_tok *carp_lex_tokenize (char *);
void carp_lex_cleanup (carp_tok *);
char *file_read (const char *);
short int is_sign (char);
short int is_num (char *);
short int is_reg (char *);
short int is_label (char *);
short int is_func (char *);
short int is_var (char *);
short int is_instr (char *);


#endif
