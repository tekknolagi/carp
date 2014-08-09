#include "carp_tokenizer.h"

/*
  Reads a whole file into memory (really should change to line-by-line), then goes through and
  copies lexemes, types, and program positions in.
*/
carp_tok *carp_lex_tokenize (char *fn) {
  assert(fn != NULL);

  char *str = file_read(fn);

  assert(str != NULL);

  char *delim = " ,\t\n";
  char *toks = strtok(str, delim);

  // empty file, so create main and halt.
  if (toks == NULL) {
    carp_tok *parsed = malloc(sizeof(carp_tok));
    carp_tok *next;

    const char *mainl = "main";
    const char *halti = "halt";

    parsed->type = ct(LBL);
    parsed->pos = 0;
    memcpy(parsed->lexeme, mainl, strlen(mainl));

    parsed->next = malloc(sizeof(carp_tok));
    next = parsed->next;

    next->type = ct(INSTR);
    next->pos = 1;
    next->next = NULL;
    memcpy(next->lexeme, halti, strlen(halti));

    return parsed;
  }

  int toks_len = 0;

  carp_id type;
  carp_tok *parsed = malloc(sizeof(carp_tok));
  carp_tok *head = parsed;
  long long i = 0;

  while (toks != NULL) {
    toks_len = strlen(toks);
    if (is_num(toks))
      type = ct(NUM);
    else if (is_reg(toks))
      type = ct(REG);
    else if (is_label(toks))
      type = ct(LBL);
    else if (is_func(toks))
      type = ct(FUNC);
    else if (is_var(toks))
      type = ct(VAR);
    else if (is_instr(toks))
      type = ct(INSTR);
    else
      type = ct(UNDEF);

    // don't copy colon
    if (type == ct(LBL)) {
      memcpy(parsed->lexeme, toks, toks_len - 1);
      parsed->lexeme[toks_len - 1] = 0;
    }
    // don't copy @
    else if (type == ct(FUNC) || type == ct(VAR)) {
      memcpy(parsed->lexeme, toks + 1, toks_len - 1);
      parsed->lexeme[toks_len - 1] = 0;
    }
    // nothing to avoid
    else {
      memcpy(parsed->lexeme, toks, toks_len);
      parsed->lexeme[toks_len] = 0;
    }

    parsed->type = type;
    parsed->pos = i++;
    parsed->next = NULL;

    toks = strtok(NULL, delim);
    if (toks != NULL) {
      parsed->next = malloc(sizeof(carp_tok));
      parsed = parsed->next;
    }
  }

  free(str);

  return head;
}

/*
  Frees the carp_tok linked list.
*/
void carp_lex_cleanup (carp_tok *tokens) {
  assert(tokens != NULL);

  carp_tok *tmp;

  while (tokens != NULL) {
    tmp = tokens->next;
    free(tokens);
    tokens = tmp;
  }
}

/*
  Reads a whole file and returns a pointer to its contents.
*/
char *file_read (const char *fn) {
  assert(fn != NULL);

  char *contents;
  long long fsize;

  FILE *fp = fopen(fn, "r");
  if (fp == NULL) {
    fprintf(stderr, "Could not open file `%s' for reading.\n", fn);
    exit(1);
  }

  fseek(fp, 0, SEEK_END); // go to end
  fsize = ftell(fp);
  fseek(fp, 0, SEEK_SET); // go to beginning

  contents = malloc(fsize * sizeof *contents);
  if (contents == NULL) {
    fprintf(stderr, "Could not malloc space for file contents.\n");
    exit(1);
  }

  size_t nread = fread(contents, sizeof *contents, fsize, fp);
  if (nread != fsize) {
    fprintf(stderr, "WARNING: Something was wonky while reading this file.\n");
  }

  fclose(fp);

  return contents;
}

/*
  Returns true if the character is a numeric sign.
*/
short int is_sign (char c) {
  return c == '+' || c == '-';
}

/*
  Returns true if the string contains all numbers (can start with a sign).
*/
short int is_num (const char *s) {
  assert(s != NULL);

  if (!(is_sign(s[0]) || isdigit(s[0]))) return 0;

  for (int i = 1; i < strlen(s); i++)
    if (!isdigit(s[i])) return 0;

  return 1;
}

/*
  Returns true if the string is in the registers list.
*/
short int is_reg (const char *s) {
  assert(s != NULL);

  return carp_reg_lookup(s) != -1;
}

/*
  Returns true if the string has a : in it.
*/
short int is_label (const char *s) {
  assert(s != NULL);

  return strchr(s, ':') != NULL;
}

/*
  Returns true if the string has a @ in it.
*/
short int is_func (const char *s) {
  assert(s != NULL);

  return strchr(s, '@') != NULL;
}

/*
  Returns true if the string has a $ in it.
*/
short int is_var (const char *s) {
  assert(s != NULL);

  return strchr(s, '$') != NULL;
}

/*
  Returns true if the string is in the instructions list.
*/
short int is_instr (const char *s) {
  assert(s != NULL);

  return carp_instr_lookup(s) != -1;
}

/*
  Uses strcmp to look up regs. Could probably use a hashtable.
*/
short int carp_reg_lookup (const char *s) {
  assert(s != NULL);

  for (int i = 0; i < CARP_NUM_REGS; i++)
    if (!strcmp(carp_reverse_reg[i], s))
      return i;

  return -1;
}

/*
  Uses strcmp to look up instrs. Could probably use a hashtable.
*/
short int carp_instr_lookup (const char *s) {
  assert(s != NULL);

  for (int i = 0; i < CARP_NUM_INSTRS; i++)
    if (!strcmp(carp_reverse_instr[i], s))
      return i;

  return -1;
}
