#include "carp_tokenizer.h"

carp_tok *carp_lex_tokenize (char *fn) {
  assert(fn != NULL);

  char *str = file_read(fn);
  char *delim = " ,\t\n";
  char *toks = strtok(str, delim);

  carp_id type;
  carp_tok *parsed = malloc(sizeof(carp_tok));
  carp_tok *head = parsed;
  long long i = 0;

  while (toks != NULL) {
    if (is_num(toks))
      type = ct(NUM);
    else if (is_reg(toks))
      type = ct(REG);
    else if (is_label(toks))
      type = ct(LBL);
    else if (is_instr(toks))
      type = ct(INSTR);
    else if (is_func(toks))
      type = ct(FUNC);
    else
      type = ct(UNDEF);

    // don't copy colon
    if (type == ct(LBL))
      memcpy(parsed->lexeme, toks, strlen(toks) - 1);
    // don't copy @
    else if (type == ct(FUNC) || type == ct(REG))
      memcpy(parsed->lexeme, toks + 1, strlen(toks) - 1);
    // nothing to avoid
    else
      memcpy(parsed->lexeme, toks, strlen(toks));

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

void carp_lex_cleanup (carp_tok *tokens) {
  assert(tokens != NULL);

  carp_tok *tmp;

  while (tokens != NULL) {
    tmp = tokens->next;
    free(tokens);
    tokens = tmp;
  }
}

void *file_read (char *fn) {
  assert(fn != NULL);

  char *contents;
  long long fsize;

  FILE *fp = fopen(fn, "rb");
  assert(fp != NULL);

  fseek(fp, 0, SEEK_END); // go to end
  fsize = ftell(fp);
  fseek(fp, 0, SEEK_SET); // go to beginning

  contents = malloc(fsize * sizeof(char));
  if (contents == NULL) {
    fprintf(stderr, "Could not malloc space for file contents.\n");
    exit(1);
  }

  fread(contents, sizeof(char), fsize, fp);
  fclose(fp);

  return contents;
}

int is_sign (char c) {
  return c == '+' || c == '-';
}

int is_num (char *s) {
  assert(s != NULL);

  if (!(is_sign(s[0]) || isdigit(s[0]))) return 0;

  for (int i = 1; i < strlen(s); i++)
    if (!isdigit(s[i])) return 0;

  return 1;
}

char *is_reg (char *s) {
  assert(s != NULL);

  return strchr(s, '%');
}

char *is_label (char *s) {
  assert(s != NULL);

  return strchr(s, ':');
}

int is_instr (char *s) {
  assert(s != NULL);

  for (int i = 0; i < CARP_NUM_INSTRS; i++)
    if (!strcmp(carp_reverse_instr[i], s))
      return 1;

  return 0;
}

char *is_func (char *s) {
  assert(s != NULL);

  return strchr(s, '@');
}
