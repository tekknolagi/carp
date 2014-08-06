#ifndef CARP_HASH_H
#define CARP_HASH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define CARP_HT_KEY_LENGTH 10

typedef struct carp_ht_entry_s {
  short int used;
  char key[CARP_HT_KEY_LENGTH];
  long long value;
} carp_ht_entry;

typedef struct carp_ht_s {
  long size;
  carp_ht_entry *buckets;
} carp_ht;

unsigned long carp_ht_hash (const char *, long);

short int carp_ht_init (carp_ht *, long);
short int carp_ht_del (carp_ht *, const char *);
short int carp_ht_set (carp_ht *, const char *, long long);
carp_ht_entry *carp_ht_get (carp_ht *, const char *);
void carp_ht_print (carp_ht *);
void carp_ht_cleanup (carp_ht *);

#endif
