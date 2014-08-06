#ifndef CARP_HT_H
#define CARP_HT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define CARP_HT_KEY_LENGTH 10

typedef struct carp_ht_s {
  char key[CARP_HT_KEY_LENGTH];
  long long value;

  struct carp_ht_s *next;
} carp_ht;

void carp_ht_init (carp_ht *);
int carp_ht_del (carp_ht *, const char *);
carp_ht *carp_ht_tail (carp_ht *);
carp_ht *carp_ht_set (carp_ht *, const char *, long long);
carp_ht *carp_ht_get (carp_ht *, const char *);
void carp_ht_cleanup (carp_ht *);
void carp_ht_print (carp_ht *);

#endif

