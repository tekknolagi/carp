#include "tests.h"
#include "../src/lib/carp_ht.h"

int main () {
  carp_bool status;
  carp_ht h;
  carp_ht *res;
  char *key = "mykey";
  char *badkey = "badkey";
  carp_value value = 17;

  plan(NO_PLAN);

  carp_ht_init(&h);

  status = carp_ht_del(&h, key);
  ok(status == 1, "Delete fails with empty table.");

  res = carp_ht_tail(&h);
  ok(res == &h, "Tail == head in empty table.");

  res = carp_ht_set(&h, key, value);
  ok(res->value == value && !strcmp(key, res->key), \
     "Set returns struct with correct information.");

  res = carp_ht_tail(&h);
  ok(res != &h, "Tail != head after adding key.");
  ok(res->value == value && !strcmp(key, res->key), \
     "Tail has correct information.");

  res = carp_ht_get(&h, key);
  ok(res->value == value && !strcmp(key, res->key), \
     "Gets correct struct back.");

  res = carp_ht_get(&h, badkey);
  ok(res == NULL, "Bad key gives null response.");

  carp_ht_cleanup(&h);

  done_testing();
}
