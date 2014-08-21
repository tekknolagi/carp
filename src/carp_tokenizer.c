#include "carp_tokenizer.h"

/*
  Reads a whole file into memory (really should change to line-by-line), then goes through and
  copies lexemes, types, and program positions in.
*/
carp_tok *carp_lex_tokenize (const char *fn) {
  assert(fn != NULL);

  char *str = file_read(fn);

  assert(str != NULL);

  char *delim = " ,\t\n";
  char *toks = strtok(str, delim);

  // empty file, so create main and halt.
  if (toks == NULL) {
    carp_tok *parsed = malloc(sizeof *parsed);
    if (parsed == NULL) {
      fprintf(stderr, "Could not allocate memory for token.\n");
      return NULL;
    }

    carp_tok *next;

    const char *mainl = "main";
    const char *halti = "halt";

    parsed->type = CARP_T(LBL);
    parsed->pos = 0;
    memcpy(parsed->lexeme, mainl, strlen(mainl));

    parsed->next = malloc(sizeof *parsed->next);
    if (parsed->next == NULL) {
      fprintf(stderr, "Could not allocate memory for token.\n");
      return NULL;
    }

    next = parsed->next;
    next->type = CARP_T(INSTR);
    next->pos = 1;
    next->next = NULL;
    memcpy(next->lexeme, halti, strlen(halti));

    return parsed;
  }

  int toks_len = 0;

  carp_id type;
  carp_tok *parsed = malloc(sizeof *parsed);
  carp_tok *head = parsed;
  carp_tok *lookbehind;
  carp_value i = 0;

  const char *call = "call\0";

  if (parsed == NULL) {
    fprintf(stderr, "Could not allocate memory for token.\n");
    return NULL;
  }

  while (toks != NULL) {
    toks_len = strlen(toks);

    if (is_num(toks))
      type = CARP_T(NUM);

    else if (is_reg(toks))
      type = CARP_T(REG);

    else if (is_label(toks))
      type = CARP_T(LBL);

    else if (strcmp(lookbehind->lexeme, "call") == 0) //is_func(toks))
      type = CARP_T(FUNC);

    else if (is_var(toks))
      type = CARP_T(VAR);

    else if (is_instr(toks))
      type = CARP_T(INSTR);

    else
      type = CARP_T(UNDEF);

    // don't copy colon
    if (type == CARP_T(LBL)) {
      memcpy(parsed->lexeme, toks, toks_len - 1);
      parsed->lexeme[toks_len - 1] = 0;
    }

    // don't copy @ or proposed $
    else if (/*type == CARP_T(FUNC) || */type == CARP_T(VAR)) {
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
      parsed->next = malloc(sizeof *parsed->next);
      lookbehind = parsed;
      parsed = parsed->next;
    }
  }

  free(str);

  return head;
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
carp_bool is_sign (char c) {
  return c == '+' || c == '-';
}

/*
  Returns true if the string contains all numbers (can start with a sign).
*/
carp_bool is_num (const char *s) {
  assert(s != NULL);

  if (!(is_sign(s[0]) || isdigit(s[0]))) return 0;

  for (int i = 1; i < strlen(s); i++)
    if (!isdigit(s[i])) return 0;

  return 1;
}

/*
  Returns true if the string is in the registers list.
*/
carp_bool is_reg (const char *s) {
  assert(s != NULL);

  return carp_reg_lookup(s) != -1;
}

/*
  Returns true if the string has a : in it.
*/
carp_bool is_label (const char *s) {
  assert(s != NULL);

  return strchr(s, ':') != NULL;
}

/*
  Returns true if the string has a @ in it.
*/
carp_bool is_func (const char *s) {
  assert(s != NULL);

  return strchr(s, '@') != NULL;
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

  return carp_instr_lookup(s) != -1;
}

/*
  Uses strcmp to look up regs. Could probably use a hashtable.
*/
carp_bool carp_reg_lookup (const char *s) {
  assert(s != NULL);

  for (int i = 0; i < CARP_NUM_REGS; i++)
    if (!strcmp(carp_reverse_reg[i], s))
      return i;

  return -1;
}

/*
  Uses strcmp to look up instrs. Could probably use a hashtable.
*/
carp_bool carp_instr_lookup (const char *s) {
  assert(s != NULL);

  for (int i = 0; i < CARP_NUM_INSTRS; i++)
    if (!strcmp(carp_reverse_instr[i], s))
      return i;

  return -1;
}
