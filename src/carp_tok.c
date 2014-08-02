#include "carp_tok.h"

carp_tok *carp_lex_tokenize (char *);
void *file_read (char *);
char *is_label (char *);
char *is_func (char *);
int is_instr (char *);
int is_sign (char);
int is_num (char *);

int main (int argc, char **argv) {
  carp_tok *tokens = carp_lex_tokenize(argv[1]);
  carp_tok *tmp;

  while (tokens != NULL) {
    printf("<%s>\n", tokens->lexeme);
    tmp = tokens->next;
    free(tokens);
    tokens = tmp;
  }

  return 0;
}

carp_tok *carp_lex_tokenize (char *fn) {
  if (fn == NULL) {
    fprintf(stderr, "No filename given.\n");
    exit(1);
  }

  char *str = file_read(fn);
  char *delim = " ,\t\n";
  char *toks = strtok(str, delim);

  carp_id type;
  carp_tok *parsed = malloc(sizeof(carp_tok));
  carp_tok *head = parsed;

  while (toks != NULL) {
    if (is_num(toks))
      type = CARP_TOK_NUM;
    else if (is_label(toks))
      type = CARP_TOK_LBL;
    else if (is_instr(toks))
      type = CARP_TOK_INSTR;
    else if (is_func(toks))
      type = CARP_TOK_FUNC;
    else
      type = CARP_TOK_UNDEF;

    parsed->type = type;
    memcpy(parsed->lexeme, toks, strlen(toks));
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

void *file_read (char *fn) {
  char *contents;
  long long fsize;

  FILE *fp = fopen(fn, "rb");
  if (!fp) {
    fprintf(stderr, "Could not fopen file.\n");
    exit(1);
  }

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

char *is_label (char *s) {
  return strchr(s, ':');
}

char *is_func (char *s) {
  return strchr(s, '@');
}

int is_instr (char *s) {
  for (int i = 0; i < CARP_NUM_INSTRS; i++)
    if (!strcmp(carp_reverse_instr[i], s))
      return 1;

  return 0;
}

int is_sign (char c) {
  return c == '+' || c == '-';
}

int is_num (char *s) {
  if (!(is_sign(s[0]) || isdigit(s[0]))) return 0;

  for (int i = 1; i < strlen(s); i++)
    if (!isdigit(s[i])) return 0;

  return 1;
}
