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
#define CARP_T(x) CARP_TOK_##x

typedef enum {
  CARP_T(UNDEF),
  CARP_T(NUM),
  CARP_T(REG),
  CARP_T(LBL),
  CARP_T(FUNC),
  CARP_T(VAR),
  CARP_T(INSTR),
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

carp_tok *carp_lex_tokenize (const char *);
void carp_lex_cleanup (carp_tok *);
char *file_read (const char *);

short int is_sign (char);
short int is_num (const char *);
short int is_reg (const char *);
short int is_label (const char *);
short int is_func (const char *);
short int is_var (const char *);
short int is_instr (const char *);

short int carp_reg_lookup (const char *);
short int carp_instr_lookup (const char *);

#endif
