#include "carp_hash.h"

int main () {
  carp_ht h;
  int status;
  unsigned char key[] = "Maxwell";

  status = carp_ht_init(&h, 10);
  if (status == -1) {
    fprintf(stderr, "Memory could not be allocated.\n");
    exit(1);
  }

  status = carp_ht_set(&h, key, 17);
  if (status == -1) {
    fprintf(stderr, "Collision! Gotta figure out how to handle this.\n");
    carp_ht_cleanup(&h);
    exit(1);
  }

  carp_ht_entry *res;
  res = carp_ht_get(&h, key);
  if (res == NULL) {
    fprintf(stderr, "Something went horribly wrong.\n");
    carp_ht_cleanup(&h);
    exit(1);
  }

  printf("value: %lld\n", res->value);

  carp_ht_cleanup(&h);
}

int carp_ht_init (carp_ht *h, long size) {
  assert(h != NULL);
  assert(size > 0);

  h->size = size;
  h->contents = malloc(size * sizeof(h->contents));
  if (h->contents == NULL)
    return -1;

  return 0;
}

// djb2
unsigned long carp_ht_hash (unsigned char str[], long size) {
  assert(str != NULL);

  unsigned long hash = 5381;
  int c;

  while ((c = *str++))
    hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

  return hash % size;
}

int carp_ht_set (carp_ht *h, unsigned char key[], long long value) {
  assert(h != NULL);
  assert(key != NULL);

  unsigned long hash = carp_ht_hash(key, h->size);
  // different key, same hash! collision!
  if (!strcmp(h->contents[hash].key, key))
    return -1;

  strncpy(h->contents[hash].key, key, strlen(key));
  h->contents[hash].value = value;

  return 0;
}

carp_ht_entry *carp_ht_get (carp_ht *h, unsigned char key[]) {
  assert(h != NULL);
  assert(key != NULL);

  unsigned long hash = carp_ht_hash(key, h->size);

  return &h->contents[hash];
}

void carp_ht_cleanup (carp_ht *h) {
  assert(h != NULL);

  free(h->contents);
}
