#include "carp_ht.h"

static unsigned long carp_ht_rhash (const char *, long);
static unsigned long carp_ht_hash (const char *, long);
static short int carp_ht_used (carp_ht *);

int main () {
  carp_ht h;
  int status;

  status = carp_ht_init(&h, 10);
  if (status == 1) {
    fprintf(stderr, "Memory could not be allocated.\n");
    exit(1);
  }
  carp_ht_print(&h);

  status = carp_ht_set(&h, "Maxwell\0", 17);
  if (status == 1) {
    fprintf(stderr, "Collision! Gotta figure out how to handle this.\n");
    carp_ht_cleanup(&h);
    exit(1);
  }
  carp_ht_print(&h);

  status = carp_ht_set(&h, "llewxaM\0", 18);
  if (status == 1) {
    fprintf(stderr, "llewxaM == Maxwell\n");
    carp_ht_cleanup(&h);
    exit(1);
  }
  carp_ht_print(&h);

  status = carp_ht_set(&h, "axwellM\0", 19);
  if (status == 1) {
    fprintf(stderr, "llewxaM == Maxwell\n");
    carp_ht_cleanup(&h);
    exit(1);
  }
  carp_ht_print(&h);

  status = carp_ht_set(&h, "xwellMa\0", 20);
  if (status == 1) {
    fprintf(stderr, "llewxaM == Maxwell\n");
    carp_ht_cleanup(&h);
    exit(1);
  }
  carp_ht_print(&h);

  status = carp_ht_set(&h, "wellMax\0", 21);
  if (status == 1) {
    fprintf(stderr, "llewxaM == Maxwell\n");
    carp_ht_cleanup(&h);
    exit(1);
  }
  carp_ht_print(&h);

  status = carp_ht_set(&h, "ellMaxw\0", 22);
  if (status == 1) {
    fprintf(stderr, "llewxaM == Maxwell\n");
    carp_ht_cleanup(&h);
    exit(1);
  }
  carp_ht_print(&h);

  status = carp_ht_set(&h, "llMaxwe\0", 23);
  if (status == 1) {
    fprintf(stderr, "llewxaM == Maxwell\n");
    carp_ht_cleanup(&h);
    exit(1);
  }
  carp_ht_print(&h);

  status = carp_ht_set(&h, "lMaxwel\0", 24);
  if (status == 1) {
    fprintf(stderr, "llewxaM == Maxwell\n");
    carp_ht_cleanup(&h);
    exit(1);
  }
  carp_ht_print(&h);

  status = carp_ht_set(&h, "!\"axwell\0", 25);
  if (status == 1) {
    fprintf(stderr, "llewxaM == Maxwell\n");
    carp_ht_cleanup(&h);
    exit(1);
  }
  carp_ht_print(&h);

  status = carp_ht_set(&h, "%(xwell\0", 25);
  if (status == 1) {
    fprintf(stderr, "llewxaM == Maxwell\n");
    carp_ht_cleanup(&h);
    exit(1);
  }
  carp_ht_print(&h);

  status = carp_ht_set(&h, "(%xwell\0", 25);
  if (status == 1) {
    fprintf(stderr, "llewxaM == Maxwell\n");
    carp_ht_cleanup(&h);
    exit(1);
  }
  carp_ht_print(&h);

  carp_ht_cleanup(&h);
}

// djb2 raw hash
static unsigned long carp_ht_rhash (const char *str, long size) {
  assert(str != NULL);

  unsigned long hash = 5381;
  int c;

  while ((c = *str++))
    hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

  return hash;
}

static unsigned long carp_ht_hash (const char *str, long size) {
  assert(str != NULL);

  return carp_ht_rhash(str, size) % size;
}

static short int carp_ht_used (carp_ht *h) {
  long in_use = 0;

  for (long i = 0; i < h->size; i++)
    if (h->buckets[i].used) in_use++;

  return in_use * 100 / h->size;
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

  unsigned long rhash = carp_ht_rhash(key, h->size);
  unsigned long hash = rhash % h->size;

  // different key, same hash! collision!
  // TODO: linear probing!
  while (h->buckets[hash].used != 0 && strcmp(h->buckets[hash].key, key) != 0) {
    // resize? o.O
    if (hash >= h->size || carp_ht_used(h) > 60) {
      if (carp_ht_resize(h) == 1) {
	fprintf(stderr, "Could not resize.\n");
	return 1;
      }
      else
	carp_ht_set(h, key, value);
    }

    hash = ++rhash % h->size;
  }

  h->buckets[hash].used = 1;
  strncpy(h->buckets[hash].key, key, strlen(key));
  h->buckets[hash].value = value;

  return 0;
}

carp_ht_entry *carp_ht_get (carp_ht *h, const char *key) {
  assert(h != NULL);
  assert(key != NULL);

  unsigned long rhash = carp_ht_rhash(key, h->size);
  unsigned long hash = rhash % h->size;

  while (h->buckets[hash].used && strcmp(h->buckets[hash].key, key) != 0) {
    if (hash >= h->size) return NULL; // not found

    hash = ++rhash % h->size;
  }

  return &h->buckets[hash];
}

short int carp_ht_resize (carp_ht *h) {
  assert(h != NULL);

  long newsize = 2 * h->size + 1;
  carp_ht newh = {newsize, NULL};
  newh.buckets = malloc(newsize * sizeof *h->buckets);
  if (newh.buckets == NULL)
    return 1;

  for (long i = 0; i < newsize; i++) {
    newh.buckets[i].used = 0;
    newh.buckets[i].key[0] = 0;
    newh.buckets[i].value = 0;
  }

  for (long i = 0; i < h->size; i++)
    if (h->buckets[i].used) {
      const char *key = h->buckets[i].key;
      unsigned long hash = carp_ht_hash(key, h->size);
      printf("adding [%ld] %s\n", hash, key);

      /* newh.buckets[hash].used = 1; */
      /* strncpy(newh.buckets[hash].key, key, strlen(key)); */
      /* newh.buckets[hash].value = h->buckets[i].value; */
      carp_ht_set(&newh, key, h->buckets[i].value);
    }

  free(h->buckets);
  h->size = newsize;
  h->buckets = newh.buckets;
  return 0;
}

void carp_ht_print (carp_ht *h) {
  assert(h != NULL);

  printf("{ %d%% full (size %ld)\n", carp_ht_used(h), h->size);;

  for (long int i = 0; i < h->size; i++)
    if (h->buckets[i].used)
      printf("  \"%s\": %lld,\n", h->buckets[i].key, h->buckets[i].value);

  printf("}\n\n");
}

void carp_ht_cleanup (carp_ht *h) {
  assert(h != NULL);

  free(h->buckets);
}
