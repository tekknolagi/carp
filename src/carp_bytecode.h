#ifndef CARP_BYTECODE_H
#define CARP_BYTECODE_H

#define CARP_TOK_WORD_LENGTH 15

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
  char *lexeme;
  carp_id type;
  carp_value line;
  carp_value value;

  struct carp_tok_s *prev;
  struct carp_tok_s *next;
} carp_tok;

carp_reg carp_reg_lookup (const char *);
carp_instr carp_instr_lookup (const char *);

carp_tok *carp_tok_tokenize (FILE *);

#endif
