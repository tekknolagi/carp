#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lib/carp_types.h"
#include "carp_tokenizer.h"
#include "carp_bytecode.h"

int is_ignore (char c) {
  return (c == ' ') || (c == '\t') || (c == '\n') || (c == ',');
}

int read_word (FILE *fp, char *buf, carp_value *linenum) {
  if (fp == NULL) return CARP_B(NOFILE);
  if (buf == NULL) return CARP_B(NOBUF);

  char c = -1;
  int i = 0;

  while ((c = fgetc(fp)) != EOF && !is_ignore(c)) {
    if (i >= CARP_TOK_WORD_LENGTH) return CARP_B(NOSPACE);
    buf[i++] = c;
  }

  buf[i] = 0;
  if (c == EOF) return CARP_B(EOF);

  while (c != EOF && is_ignore(c)) {
    printf("%u\n", c);
    if (c == '\n') (*linenum)++;
    c = fgetc(fp);
  }

  if (c == EOF) return CARP_B(EOF);

  ungetc(c, fp);

  return CARP_B(OK);
}

int main (int argc, char **argv) {
  if (argc < 2)
    return 1;

  FILE *fp = fopen(argv[1], "rb");
  if (fp == NULL)
    return 1;

  carp_value linenum = 1;

  int status = CARP_B(OK);
  char c;

  printf("%lld: ", linenum);
  while (status == CARP_B(OK)) {
  getchar:
    c = fgetc(fp);
    if (c == EOF) {
      status = CARP_B(EOF);
      break;
    }

    printf("%c", c);
    if (c == '\n') {
      linenum++;
      printf("%lld: ", linenum);
    }
    if (c == '\t' || c == ' ') goto getchar;
  }
  putchar('\n');

  fclose(fp);
  //  free(parsed);
}
