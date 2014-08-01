#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

int is_ident (char *s) {
  for (int i = 0; i < strlen(s); i++)
    if (!isalpha(s[i])) return 0;

  return 1;
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

int main (int argc, char **argv) {
  if (argv[1] == NULL) {
    fprintf(stderr, "No filename given.\n");
    exit(1);
  }

  char *fn = argv[1];
  char *str = file_read(fn);
  char *delim = " ,\t\n";
  char *toks = strtok(str, delim);

  while (toks != NULL) {
    if (is_label(toks)) {
      printf("label: ");
    }
    else if (is_ident(toks)) {
      printf("ident: ");
    }
    else if (is_num(toks)) {
      printf("num: ");
    }

    printf("<%s>\n", toks);
    toks = strtok(NULL, delim);
  }

  free(str);

  return 0;
}
