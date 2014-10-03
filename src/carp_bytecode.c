#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#include "lib/carp_types.h"
#include "carp_registers.h"
#include "carp_instructions.h"
#include "carp_bytecode.h"

#define is_white(c) ((c) == '\n' || (c) == '\t' || (c) == ' ')
#define fail_if(x) if (x) return EXIT_FAILURE

static carp_bool is_sign (char);
static carp_bool is_num (const char *);
static carp_bool is_reg (const char *);
static carp_bool is_label (const char *);
static carp_bool is_var (const char *);
static carp_bool is_instr (const char *);
static carp_tok *carp_tok_create (int);
static carp_id carp_tok_classify (carp_tok *, char []);
static void carp_tok_cleanup (carp_tok *);

int main (int argc, char **argv) {
  fail_if (argc < 2);
  
  FILE *fp = fopen(argv[1], "rb");
  fail_if (fp == NULL);

  carp_tok *tokens = carp_tok_tokenize(fp);
  fail_if (tokens == NULL);

  carp_tok_cleanup(tokens);
  fclose(fp);
}

/*
  Returns true if the character is a numeric sign.
*/
carp_bool is_sign (char c) {
  return c == '+' || c == '-';
}

/*
  Returns true if the string contains all numbers (can start with a sign).
*/
carp_bool is_num (const char *s) {
  assert(s != NULL);

  if (!(is_sign(s[0]) || isdigit((int) s[0]))) return 0;

  for (int i = 1; i < strlen(s); i++)
    if (!isdigit((int) s[i])) return 0;

  return 1;
}

/*
  Returns true if the string is in the registers list.
*/
carp_bool is_reg (const char *s) {
  assert(s != NULL);

  return carp_reg_lookup(s) != CARP_REG_UNDEF;
}

/*
  Returns true if the string has a : in it.
*/
carp_bool is_label (const char *s) {
  assert(s != NULL);

  return strchr(s, ':') != NULL;
}

/*
  Returns true if the string has a $ in it.
*/
carp_bool is_var (const char *s) {
  assert(s != NULL);

  return strchr(s, '$') != NULL;
}

/*
  Returns true if the string is in the instructions list.
*/
carp_bool is_instr (const char *s) {
  assert(s != NULL);

  return carp_instr_lookup(s) != CARP_INSTR_UNDEF;
}

/*
  Uses strcmp to look up regs. Could probably use a hashtable.
*/
carp_reg carp_reg_lookup (const char *s) {
  assert(s != NULL);

  for (int i = 0; i < CARP_NUM_REGS; i++)
    if (!strcmp(carp_reverse_reg[i], s))
      return i;

  return CARP_REG_UNDEF;
}

/*
  Uses strcmp to look up instrs. Could probably use a hashtable.
*/
carp_instr carp_instr_lookup (const char *s) {
  assert(s != NULL);

  for (int i = 0; i < CARP_NUM_INSTRS; i++)
    if (!strcmp(carp_reverse_instr[i], s))
      return i;

  return CARP_INSTR_UNDEF;
}

/*
  Frees the carp_tok linked list.
*/
static void carp_tok_cleanup (carp_tok *tokens) {
  assert(tokens != NULL);

  carp_tok *tmp;

  while (tokens) {
    tmp = tokens->next;
    free(tokens->lexeme);
    free(tokens);
    tokens = tmp;
  }
}

carp_bool fread_word (FILE *fp, carp_tok *tok, int *lines) {
  if (fp == NULL) return 1;
  if (lines == NULL) return 2;

  int ok = 1;
  char c = EOF;
  int i = 0;

  int buf_len = 20;
  char buf[buf_len];

  while (ok) {
    c = fgetc(fp);

    if (i >= buf_len) {
      ok = 0;
      break;
    }

    if (c == EOF) {
      ok = 0;
      break;
    }

    if (is_white(c))
      break;

    buf[i++] = c;
  }

  if (c == EOF && i > 0) ok = 1;

  if (!ok) return 3;

  while (is_white(c)) {
    if (c == '\n') (*lines)++;
    c = fgetc(fp);
  }
  ungetc(c, fp);

  buf[i++] = 0;

  //printf("buf: `%s' of length %d\n", buf, i);
  if (tok->prev) printf("prev: `%s'\n", tok->prev->lexeme);
  tok->type = carp_tok_classify(tok, buf);

  // do not copy ending colon
  if (tok->type == CARP_T(LBL)) {
    strncpy(tok->lexeme, buf, i - 1);
    tok->lexeme[i - 1] = 0;
  }
  // do not copy beginning $ (if applicable)
  else if (tok->type == CARP_T(VAR)) {
    strncpy(tok->lexeme, buf + 1, i - 1);
    tok->lexeme[i - 1] = 0;
  }
  // just copy the dang thing
  else {
    strncpy(tok->lexeme, buf, i);
  }

  tok->line = *lines;
  tok->next = NULL;

  return 1;
}

static carp_tok *carp_tok_create (int slen) {
  assert(slen > 0);

  carp_tok *tok = calloc(1, sizeof *tok);
  if (tok == NULL) return NULL;

  tok->lexeme = calloc(slen, sizeof *tok->lexeme);
  if (tok->lexeme == NULL) return NULL;

  return tok;
}

static carp_id carp_tok_classify (carp_tok *tok, char buf[]) {
  assert(tok != NULL);
  assert(buf != NULL);

  if (is_num(buf))
    return CARP_T(NUM);

  if (is_reg(buf))
    return CARP_T(REG);

  if (is_label(buf))
    return CARP_T(LBL);

  if (tok->prev && !strcmp(tok->prev->lexeme, "call"))
    return CARP_T(FUNC);

  if (is_var(buf))
    return CARP_T(VAR);

  if (is_instr(buf))
    return CARP_T(INSTR);

  return CARP_T(UNDEF);
}

carp_tok *carp_tok_tokenize (FILE *fp) {
  assert(fp != NULL);

  carp_bool status = 0;
  carp_tok *head = NULL;
  carp_tok *cur = NULL;
  int lines = 1;
  int reading = 1;
  
  /* head = carp_tok_create(CARP_TOK_WORD_LENGTH); */
  /* if (head == NULL) { */
  /*   puts("Could not allocate memory."); */
  /*   exit(1); */
  /* } */

  /* status = fread_word(fp, head, &lines); */
  /* if (status != 0) return NULL; */

  head->prev = NULL;
  cur = head;
 
  while (reading) {
    //cur->value = 

    cur = carp_tok_create(CARP_TOK_WORD_LENGTH);
    if (cur == NULL) {
      puts("Could not allocate memory.");
      exit(1);
    }

    printf("%s: %s\n", carp_reverse_type[cur->type], cur->lexeme);

    status = fread_word(fp, cur, &lines);
    if (status != 0) return head;

    cur->next->prev = cur;
    cur = cur->next;

    if (cur == NULL) reading = 0;
  }

  return head;
}
