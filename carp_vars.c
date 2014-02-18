#include "carp_vars.h"

void carp_var_delete (carp_machine_state* m, char* name) {
  carp_variable* res;

  HASH_FIND_STR(m->vars, name, res);

  // does not exist
  if (res == NULL) {
    fprintf(stderr, CARP_VAR_DNE);
    carp_vm_exit(m, 1);
  }
}

void carp_var_define (carp_machine_state* m, char* name, long long value) {
  carp_variable* res;

  HASH_FIND_STR(m->vars, name, res);

  // does not exist
  if (res == NULL) {
    res = (carp_variable*) malloc(sizeof(carp_variable));
    strcpy(res->name, name);
    res->value = value;
    HASH_ADD_STR(m->vars, name, res);
  }
  // pre-existing
  else {
    HASH_DEL(m->vars, res);
    res->value = value;
    HASH_ADD_STR(m->vars, name, res);
  }
}

carp_variable carp_var_get (carp_machine_state* m, char* name) {
  carp_variable* res;

  HASH_FIND_STR(m->vars, name, res);

  // does not exist
  if (res == NULL) {
    fprintf(stderr, CARP_VAR_DNE);
    carp_vm_exit(m, 1);
  }
  else {
    return *res;
  }
}

void carp_var_cleanup (carp_machine_state* m) {
  carp_variable* vars = m->vars;
  carp_variable* current;
  carp_variable* tmp;

  HASH_ITER (hh, vars, current, tmp) {
    HASH_DEL(vars, current);
    free(current);
  }
}
