#include "carp_registers.h"
#include "carp_instructions.h"
#include "carp_tokenizer.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <errno.h>

char carp_reverse_type[][6] = {
  "undef",
  "num",
  "reg",
  "lbl",
  "func",
  "var",
  "instr"
};

static char *file_read(const char *);
static bool is_sign(char);
static bool is_num(const char *);
static bool is_reg(const char *);
static bool is_label(const char *);
static bool is_var(const char *);
static bool is_instr(const char *);

/* Reads a whole file into memory (really should change to
 * line-by-line), then goes through and copies lexemes, types, and
 * program positions in.
 */
carp_tok *carp_lex_tokenize (const char *fn) {
  assert(fn != NULL);

  char *str = file_read(fn);

  assert(str != NULL);

  const char *delim = " ,\t\n";
  char *toks = strtok(str, delim);

  /* empty file, so skip the pain and halt with success there must be
   * a cleaner way to do this
   */
  if (toks == NULL) {
    exit(EXIT_SUCCESS);
  }

  int toks_len = 0;

  carp_id type;
  carp_tok *parsed = malloc(sizeof *parsed);
  carp_tok *head = parsed;
  carp_tok *lookbehind = NULL;
  carp_value i = 0;

  if (parsed == NULL) {
    fprintf(stderr, "Could not allocate memory for token.\n");
    return NULL;
  }

  while (toks != NULL) {
    toks_len = strlen(toks);

    if (is_num(toks)) {
      type = CARP_TOK_NUM;
    } else if (is_reg(toks)) {
      type = CARP_TOK_REG;
    } else if (is_label(toks)) {
      type = CARP_TOK_LBL;
    } else if (lookbehind != NULL && strcmp(lookbehind->lexeme, "call") == 0) {
      type = CARP_TOK_FUNC;
    } else if (is_var(toks)) {
      type = CARP_TOK_VAR;
    } else if (is_instr(toks)) {
      type = CARP_TOK_INSTR;
    } else {
      type = CARP_TOK_UNDEF;
    }

    if (type == CARP_TOK_LBL) {
      /* don't copy colon at end */
      memcpy(parsed->lexeme, toks, toks_len - 1);
      parsed->lexeme[toks_len - 1] = 0;
    } else if (type == CARP_TOK_VAR) {
      /* don't copy proposed $ at start */
      memcpy(parsed->lexeme, toks + 1, toks_len - 1);
      parsed->lexeme[toks_len - 1] = 0;
    } else {
      /* nothing to avoid */
      memcpy(parsed->lexeme, toks, toks_len);
      parsed->lexeme[toks_len] = 0;
    }

    parsed->type = type;
    parsed->pos = i++;
    parsed->next = NULL;

    toks = strtok(NULL, delim);

    if (toks != NULL) {
      parsed->next = malloc(sizeof *parsed->next);
      lookbehind = parsed;
      parsed = parsed->next;
    }
  }

  free(str);

  return head;
}

/* Reads a whole file and returns a pointer to its contents. */
char *file_read (const char *fn) {
  assert(fn != NULL);

  char *contents;
  size_t fsize;
  size_t nread;
  FILE *fp;

  if ((fp = fopen(fn, "r")) == NULL) {
    fprintf(stderr, "Could not open file `%s' for reading: %s\n",
            fn, strerror(errno));
    exit(EXIT_FAILURE);
  }

  /* Figure out file size */
  fseek(fp, 0, SEEK_END);
  fsize = ftell(fp);
  fseek(fp, 0, SEEK_SET);

  /* File size in bytes */
  fsize *= sizeof(*contents);

  if ((contents = malloc(fsize)) == NULL) {
    fprintf(stderr, "Could not allocate %lu bytes for file contents: %s\n",
            fsize, strerror(errno));
    exit(EXIT_FAILURE);
  }

  if ((nread = fread(contents, sizeof *contents, fsize, fp)) != fsize) {
    fprintf(stderr, "WARNING: Something was wonky when reading this file: %s\n",
            strerror(errno));
  }

  fclose(fp);

  return contents;
}

/* Returns true if the character is a numeric sign. */
bool is_sign (char c) {
  return c == '+' || c == '-';
}

/* Returns true if the string contains all numbers (can start with a sign). */
bool is_num (const char *s) {
  assert(s != NULL);

  if (!(is_sign(s[0]) || isdigit((unsigned char) s[0]))) return 0;

  for (size_t i = 1; i < strlen(s); i++)
    if (!isdigit((unsigned char) s[i])) return 0;

  return 1;
}

/* Returns true if the string is in the registers list. */
bool is_reg (const char *s) {
  assert(s != NULL);

  return carp_reg_lookup(s) != CARP_REG_UNDEF;
}

/* Returns true if the string has a : in it. */
bool is_label (const char *s) {
  assert(s != NULL);

  return strchr(s, ':') != NULL;
}

/* Returns true if the string has a $ in it. */
bool is_var (const char *s) {
  assert(s != NULL);

  return strchr(s, '$') != NULL;
}

/* Returns true if the string is in the instructions list. */
bool is_instr (const char *s) {
  assert(s != NULL);

  return carp_instr_lookup(s) != CARP_INSTR_UNDEF;
}

/* Uses strcmp to look up regs. Could probably use a hashtable. */
carp_reg carp_reg_lookup (const char *s) {
  assert(s != NULL);

  for (int i = 0; i < CARP_NUM_REGS; i++)
    if (!strcmp(carp_reverse_reg[i], s))
      return i;

  return CARP_REG_UNDEF;
}

/* Uses strcmp to look up instrs. Could probably use a hashtable. */
carp_instr carp_instr_lookup (const char *s) {
  assert(s != NULL);

  for (int i = 0; i < CARP_NUM_INSTRS; i++)
    if (!strcmp(carp_reverse_instr[i], s))
      return i;

  return CARP_INSTR_UNDEF;
}
