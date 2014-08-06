#include "carp_hash.h"

int main () {
  carp_ht h;
  int status;
  const char *key = "Maxwell";

  status = carp_ht_init(&h, 10);
  if (status == 1) {
    fprintf(stderr, "Memory could not be allocated.\n");
    exit(1);
  }

  status = carp_ht_set(&h, key, 17);
  if (status == 1) {
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

  carp_ht_print(&h);

  carp_ht_cleanup(&h);
}

// djb2
unsigned long carp_ht_hash (const char *str, long size) {
  assert(str != NULL);

  unsigned long hash = 5381;
  int c;

  while ((c = *str++))
    hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

  return hash % size;
}

short int carp_ht_init (carp_ht *h, long size) {
  assert(h != NULL);
  assert(size > 0);

  h->size = size;
  h->buckets = malloc(size * sizeof(h->buckets));
  if (h->buckets == NULL)
    return 1;

  for (long i = 0; i < h->size; i++)
    h->buckets[i].used = 0;

  return 0;
}

short int carp_ht_del (carp_ht *h, const char *key) {
  assert(h != NULL);
  assert(key != NULL);

  unsigned long hash = carp_ht_hash(key, h->size);

  // different key, same hash! collision!
  if (!strcmp(h->buckets[hash].key, key))
    return 1;

  // unused bucket
  if (!h->buckets[hash].used)
    return 2;

  h->buckets[hash].used = 0;
  h->buckets[hash].key[0] = 0; // NUL-terminate
  h->buckets[hash].value = 0;

  return 0;
}

short int carp_ht_set (carp_ht *h, const char *key, long long value) {
  assert(h != NULL);
  assert(key != NULL);

  unsigned long hash = carp_ht_hash(key, h->size);

  // different key, same hash! collision!
  // TODO: linear probing!
  if (!strcmp(h->buckets[hash].key, key))
    return 1;

  if (!h->buckets[hash].used) {
    strncpy(h->buckets[hash].key, key, strlen(key));
    h->buckets[hash].used = 1;
  }

  h->buckets[hash].value = value;

  return 0;
}

carp_ht_entry *carp_ht_get (carp_ht *h, const char *key) {
  assert(h != NULL);
  assert(key != NULL);

  unsigned long hash = carp_ht_hash(key, h->size);

  return &h->buckets[hash];
}

short int carp_ht_resize (carp_ht *h, long newsize) {
  assert(h != NULL);
  assert(newsize > 0);

  carp_ht_entry *newbuckets = malloc(newsize * sizeof h->buckets);
  //h->buckets = realloc(h->buckets, newsize * sizeof h->buckets);
  if (newbuckets == NULL)
    return 1;

  for (long i = 0; i < h->size; i++)
    if (h->buckets[i].used) {
      int status = carp_ht_set(newbuckets, h->buckets[i].key, h->buckets[i].value);
      // collision?!
      if (status == 1) {
	// ???
      }
    }

  h->size = newsize;
}

void carp_ht_print (carp_ht *h) {
  assert(h != NULL);

  puts("{");

  for (long int i = 0; i < h->size; i++)
    if (h->buckets[i].used)
      printf("  %s: %lld,\n", h->buckets[i].key, h->buckets[i].value);

  puts("}");
}

void carp_ht_cleanup (carp_ht *h) {
  assert(h != NULL);

  free(h->buckets);
}
