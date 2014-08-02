#include "carp_lexer.h"

int main (int argc, char **argv) {
  char *fn = argv[1];
  carp_tok *tokens = carp_lex_tokenize(fn);
  carp_tok *tmp = tokens;
  //carp_ht labels;

  while (tmp != NULL) {
    switch (tmp->type) {
    case ct(UNDEF): {
      fprintf(stderr, "Unknown token <%s>\n", tmp->lexeme);
      carp_lex_cleanup(tokens);
      exit(1);
      break; }

    case ct(NUM): {
      long long num = atoi(tmp->lexeme);
      tmp->val = num;
      break; }

    case ct(REG): {
      carp_reg reg = carp_reg_lookup(tmp->lexeme);
      tmp->val = reg;
      break; }

    case ct(LBL): {
      //carp_ht_insert(&labels, tmp->lexeme, );
      break; }

    case ct(INSTR): {
      carp_instr instr = carp_instr_lookup(tmp->lexeme);
      tmp->val = instr;
      break; }
      
    case ct(FUNC): {
      //long long addr = ;
      break; }
    }

    //printf("%s (%s)\n", tmp->lexeme, carp_reverse_type[tmp->type]);
    tmp = tmp->next;
  }

  carp_lex_cleanup(tokens);
  return 0;
}

carp_reg carp_reg_lookup (char *s) {
  assert(s != NULL);

  for (int i = 0; i < CARP_NUM_REGS; i++)
    if (!strcmp(carp_reverse_reg[i], s))
      return i;

  return -1;
}

carp_instr carp_instr_lookup (char *s) {
  assert(s != NULL);

  for (int i = 0; i < CARP_NUM_INSTRS; i++)
    if (!strcmp(carp_reverse_instr[i], s))
      return i;

  return -1;
}
