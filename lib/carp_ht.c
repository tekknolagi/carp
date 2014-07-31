#include "carp_ht.h"

void carp_ht_init (carp_ht *h) {
  h->next = NULL;
}

int carp_ht_del (carp_ht *h, char *key) {
  carp_ht *res = carp_ht_get(h, key);
  carp_ht *prev = h;

  // not found
  if (res == NULL)
    return -1;

  while (prev->next != res)
    prev = prev->next;

  prev->next = res->next;
  free(res);

  return 0;
}

carp_ht *carp_ht_tail (carp_ht *h) {
  carp_ht *tail = h;

  while (tail->next != NULL)
    tail = tail->next;

  return tail;
}

carp_ht *carp_ht_set (carp_ht *h, char *key, long long value) {
  carp_ht *res = carp_ht_get(h, key);

  // exists
  if (res != NULL) {
    res->value = value;

    return res;
  }
  // does not exist
  else {
    carp_ht *tail = carp_ht_tail(h);
    tail->next = malloc(sizeof(*tail->next));
    if (tail->next == NULL)
      return NULL;	

    tail = tail->next;

    tail->value = value;
    tail->next = NULL;
    strncpy(tail->key, key, CARP_HT_KEY_LENGTH);

    return tail;
  }
}

carp_ht *carp_ht_get (carp_ht *h, char *key) {
  carp_ht *res = h;

  while (strcmp(res->key, key) != 0) {
    if (res->next == NULL)
      return NULL;
    
    res = res->next;
  }

  return res;
}

void carp_ht_cleanup (carp_ht *h) {
  carp_ht *tmp = h;
  carp_ht *cur;

  while (tmp != NULL) {
    cur = tmp->next;
    if (tmp != h)
      free(tmp);

    tmp = cur;
  }
}

void carp_ht_print (carp_ht *h) {
  carp_ht *tmp = h;

  puts("{");

  while (tmp != NULL) {
    if (tmp != h)
      printf("%s: %lld,\n", tmp->key, tmp->value);

    tmp = tmp->next;
  }

  puts("}");
}
