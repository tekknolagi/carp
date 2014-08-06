#ifndef CARP_HASH_H
#define CARP_HASH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define CARP_HT_KEY_LENGTH 10

typedef struct carp_ht_entry_s {
  char key[CARP_HT_KEY_LENGTH];
  long long value;
} carp_ht_entry;

typedef struct carp_ht_s {
  long size;
  carp_ht_entry *contents;
} carp_ht;

int carp_ht_init (carp_ht *, long);
unsigned long carp_ht_hash (unsigned char [], long);
int carp_ht_set (carp_ht *, unsigned char [], long long);
carp_ht_entry *carp_ht_get (carp_ht *, unsigned char []);
void carp_ht_cleanup (carp_ht *);

#endif
