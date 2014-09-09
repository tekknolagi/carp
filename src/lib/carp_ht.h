#ifndef CARP_HASH_H
#define CARP_HASH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "carp_types.h"

#define CARP_HT_KEY_LENGTH 15

typedef struct carp_ht_entry_s {
  char key[CARP_HT_KEY_LENGTH];
  long long value;
  struct carp_ht_entry_s *next;
} carp_ht_entry;

typedef struct carp_ht_s {
  long size;
  carp_ht_entry **buckets;
} carp_ht;

void carp_ht_init (carp_ht *);
carp_bool carp_ht_del (carp_ht *, char *);
carp_ht_entry *carp_ht_tail (carp_ht *);
carp_ht_entry *carp_ht_set (carp_ht *, char *, carp_value);
carp_ht_entry *carp_ht_get (carp_ht *, char *);
void carp_ht_print (carp_ht *, FILE *);
void carp_ht_cleanup (carp_ht *);

#endif
