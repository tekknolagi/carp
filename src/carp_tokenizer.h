#ifndef CARP_TOK_H
#define CARP_TOK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#include "lib/carp_types.h"
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
  carp_value pos;
  carp_value value;

  struct carp_tok_s *next;
} carp_tok;

carp_tok *carp_lex_tokenize (const char *);
void carp_lex_cleanup (carp_tok *);
char *file_read (const char *);

carp_bool is_sign (char);
carp_bool is_num (const char *);
carp_bool is_reg (const char *);
carp_bool is_label (const char *);
carp_bool is_func (const char *);
carp_bool is_var (const char *);
carp_bool is_instr (const char *);

carp_bool carp_reg_lookup (const char *);
carp_bool carp_instr_lookup (const char *);

#endif
