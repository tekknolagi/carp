#include "carp_ht.h"

static unsigned long carp_ht_rhash (const char *, long);
static unsigned long carp_ht_hash (const char *, long);
static short int carp_ht_used (carp_ht *);

int main () {
  carp_ht h;
  int status;
  printf("jesus\n");
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

  for (long i = 0; i < h->size; i++) {
    carp_ht_entry *base = h->buckets[i];
    while (base) {
	in_use++;
	base = base->next;
    }
  }

  return in_use * 100 / h->size;
}

short int carp_ht_init (carp_ht *h, long size) {
  assert(h != NULL);
  assert(size > 0);

  h->size = size;
  h->buckets = malloc(size * sizeof(carp_ht_entry *));
  if (h->buckets == NULL)
    return 1;

  for (long i = 0; i < h->size; i++)
    h->buckets[i] = 0;

  return 0;
}

short int carp_ht_del (carp_ht *h, const char *key) {
  assert(h != NULL);
  assert(key != NULL);

  unsigned long hash = carp_ht_hash(key, h->size);
  if (h->buckets[hash] == NULL) return 0;

  // different key, same hash! collision!
  if (!strcmp(h->buckets[hash]->key, key)) {
    carp_ht_entry *base = h->buckets[hash];
    while (!strcmp(base->next->key, key)) { //possible issue if key is empty string?
      if (base->next == NULL) return 0;
      base = base->next;
    }
    carp_ht_entry *next = base->next;
    base->next = base->next->next;
    free(next);
  }
  // unused bucket
  if (!h->buckets[hash])
    return 2;

  carp_ht_entry *next = h->buckets[hash]->next;
  h->buckets[hash]->next = h->buckets[hash]->next->next;
  free(next);

  return 0;
}

short int carp_ht_set (carp_ht *h, const char *key, long long value) {
  assert(h != NULL);
  assert(key != NULL);

  carp_ht_entry *new = calloc(1, sizeof(carp_ht_entry));

  unsigned long rhash = carp_ht_rhash(key, h->size);
  unsigned long hash = rhash % h->size;

  if (h->buckets[hash] == NULL) {
    strncpy(new->key, key, strlen(key));
    new->value = value;
    h->buckets[hash] = new;
    return 0;
  }

  // different key, same hash! collision!
  // TODO: linear probing!
  carp_ht_entry *base = h->buckets[hash];
  while (base->next != NULL && strcmp(base->next->key, key) != 0) {
    // resize? o.O
    if (hash >= h->size || carp_ht_used(h) > 60) {
      if (carp_ht_resize(h) == 1) {
	fprintf(stderr, "Could not resize.\n");
	return 1;
      }
      else {
	carp_ht_set(h, key, value);
	return 0;
      }
    }

    base = base->next;
  }

  base->next = new;
  strncpy(new->key, key, strlen(key));
  new->value = value;

  return 0;
}

carp_ht_entry *carp_ht_get (carp_ht *h, const char *key) {
  assert(h != NULL);
  assert(key != NULL);

  unsigned long rhash = carp_ht_rhash(key, h->size);
  unsigned long hash = rhash % h->size;

  carp_ht_entry *base = h->buckets[hash];
  while (base && strcmp(base->key, key) != 0) {
    if (hash >= h->size) return NULL; // not found

    base = base->next;
  }

  return base;
}

short int carp_ht_resize (carp_ht *h) {
  //TODO: This probably still leaks memory, did not try to free entry lists...
  assert(h != NULL);

  long newsize = 2 * h->size + 1;
  carp_ht newh = {newsize, NULL};
  newh.buckets = calloc(newsize, sizeof(carp_ht_entry *));
  if (newh.buckets == NULL)
    return 1;

  for (long i = 0; i < h->size; i++)
    if (h->buckets[i]) {
      carp_ht_entry *base = h->buckets[i];
      while (base) {
	const char *key = base->key;
	unsigned long hash = carp_ht_hash(key, h->size);
	printf("adding [%ld] %s, ", hash, key);
	carp_ht_set(&newh, base->key, base->value);
	carp_ht_entry *next = base->next;
	free(base);
	base = next;
      }
      printf("\n");
    }

  free(h->buckets);
  h->size = newsize;
  h->buckets = newh.buckets;
  return 0;
}

void carp_ht_print (carp_ht *h) {
  assert(h != NULL);

  printf("{ %d%% full (size %ld)\n", carp_ht_used(h), h->size);;

  //TODO: Does not print along collision lists.
  for (long int i = 0; i < h->size; i++)
    if (h->buckets[i]) {
      carp_ht_entry *base = h->buckets[i];
      do {
	printf("  \"%s\": %lld,", base->key, base->value);
      } while ((base = base->next));
      printf("\n");
    }

  printf("}\n\n");
}

void carp_ht_cleanup (carp_ht *h) {

  //TODO: Definitely leaks memory.
  assert(h != NULL);
  for (long i = 0; i < h->size; i++)
    if (h->buckets[i]) {
      carp_ht_entry *base = h->buckets[i];
      while (base) {
	carp_ht_entry *next = base->next;
	free(base);
        base = next;
      }
    }
  free(h->buckets);
}
