#include "carp_labels.h"

void carp_label_delete (carp_machine_state* m, char* name) {
  carp_label* res;

  HASH_FIND_STR(m->labels, name, res);

  // does not exist
  if (res == NULL) {
    fprintf(stderr, CARP_LABEL_DNE);
    carp_vm_exit(m, CARP_EX_USAGE);
  }
}

void carp_label_define (carp_machine_state* m, char* name, long long value) {
  carp_label* res;

  HASH_FIND_STR(m->labels, name, res);

  // does not exist
  if (res == NULL) {
    res = malloc(sizeof(carp_label));
    strcpy(res->name, name);
    res->value = value;
    HASH_ADD_STR(m->labels, name, res);
  }
  // pre-existing
  else {
    HASH_DEL(m->labels, res);
    res->value = value;
    HASH_ADD_STR(m->labels, name, res);
  }
}

carp_label carp_label_get (carp_machine_state* m, char* name) {
  carp_label* res;

  HASH_FIND_STR(m->labels, name, res);

  // does not exist
  if (res == NULL) {
    fprintf(stderr, CARP_LABEL_DNE);
    carp_vm_exit(m, CARP_EX_USAGE);
    return *res; // never gets here, but squashes warning
  }
  else {
    return *res;
  }
}

void carp_label_cleanup (carp_machine_state* m) {
  carp_label* labels = m->labels;
  carp_label* current;
  carp_label* tmp;

  HASH_ITER (hh, labels, current, tmp) {
    HASH_DEL(labels, current);
    free(current);
  }
}
