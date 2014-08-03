#include "carp.h"
#include "carp_lexer.h"

int main (int argc, char **argv) {
  char *fn = argv[1];
  if (fn == NULL) {
    fprintf(stderr, "No filename given.\n");
    exit(1);
  }

  carp_tok *tokens = carp_lex_tokenize(fn);
  if (tokens == NULL) {
    fprintf(stderr, "Something went wrong with tokenization.\n");
    exit(1);
  }

  carp_machine_state m;
  carp_lex_lex(&m, tokens);
  carp_vm_run(&m);
  carp_vm_cleanup(&m);

  return 0;
}
