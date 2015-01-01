#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "lib/types.h"
#include "lib/ht.h"

#include "tokenizer.h"
#include "lexer.h"
#include "machine.h"

static void carp_lex_cleanup (carp_tok *);
static void carp_lex_exit (carp_tok *, carp_ht *, int);

/*
  Assigns values to a series of tokens.
  NUM is obvious.
  REG is obvious.
  LBL is NOP instr.
  FUNC is label lookup value.
  INSTR is obvious.
*/
void carp_lex_lex (carp_machine_state *m, carp_tok *tokens) {
  assert(m != NULL);
  assert(tokens != NULL);

  long long length = -1;
  carp_tok *tmp = tokens;

  carp_ht_init(&m->labels, 10);

  while (tmp != NULL) {
    switch (tmp->type) {
    case CARP_TOK_UNDEF: {
      fprintf(stderr, "Unknown token <%s>\n", tmp->lexeme);
      carp_lex_exit(tokens, &m->labels, EXIT_FAILURE);
      break;
    }
    case CARP_TOK_NUM: {
      long long num = atoi(tmp->lexeme);
      tmp->value = num;
      break;
    }
    case CARP_TOK_REG: {
      carp_reg reg = carp_reg_lookup(tmp->lexeme);
      tmp->value = reg;
      break;
    }
    case CARP_TOK_LBL: {
      carp_bool status = carp_ht_set(&m->labels, tmp->lexeme, tmp->pos);
      if (status != 0) {
        fprintf(stderr, "Could not make label <%s>\n", tmp->lexeme);
        carp_lex_exit(tokens, &m->labels, 1);
      }

      carp_value instr = CARP_INSTR_NOP;
      tmp->value = instr;
      break;
    }
    case CARP_TOK_FUNC: {
      carp_ht_entry *res = carp_ht_get(&m->labels, tmp->lexeme);
      if (res == NULL) {
        fprintf(stderr, "Unknown label <%s>\n", tmp->lexeme);
        carp_lex_exit(tokens, &m->labels, EXIT_FAILURE);
      }

      tmp->value = res->value;
      break;
    }
    case CARP_TOK_VAR: {
      break;
    }
    case CARP_TOK_INSTR: {
      carp_value instr = carp_instr_lookup(tmp->lexeme);
      tmp->value = instr;
      break; }
    }

    #ifdef CDEBUG
    printf("[%04ld] %5s (%5s) = %4ld\n",
           tmp->pos, tmp->lexeme, carp_reverse_type[tmp->type], tmp->value);
    #endif

    tmp = tmp->next;
    length++;
  }

  carp_value code[length];
  tmp = tokens;

  while (tmp != NULL) {
    code[tmp->pos] = tmp->value;
    tmp = tmp->next;
  }

  carp_lex_cleanup(tokens);
  carp_vm_make(m);
  carp_vm_load(m, code, length);
}

/*
  Frees the carp_tok linked list.
*/
static void carp_lex_cleanup (carp_tok *tokens) {
  assert(tokens != NULL);

  carp_tok *tmp;

  while (tokens != NULL) {
    tmp = tokens->next;
    free(tokens);
    tokens = tmp;
  }
}

/*
  Exits cleanly by cleaning up first.
*/
static void carp_lex_exit (carp_tok *tokens, carp_ht *labels, int code) {
  assert(tokens != NULL);
  assert(labels != NULL);

  carp_lex_cleanup(tokens);
  carp_ht_cleanup(labels);
  exit(code);
}
