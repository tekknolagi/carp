#include "tests.h"
#include "../src/lib/carp_ht.h"

int main () {
  carp_bool status;
  carp_ht h;
  carp_ht_entry *res;
  const char *key = "mykey";
  const char *badkey = "badkey";
  carp_value value = 17;

  plan(NO_PLAN);

  carp_ht_init(&h, 10);

  status = carp_ht_del(&h, key);
  ok(status == 1, "Delete fails with empty table.");

  status = carp_ht_set(&h, key, value);
  ok(status == 0, "Set returns successfully.");

  res = carp_ht_get(&h, key);
  ok(res->value == value && !strcmp(key, res->key), \
     "Gets correct struct back.");

  res = carp_ht_get(&h, badkey);
  ok(res == NULL, "Bad key gives null response.");

  carp_ht_cleanup(&h);

  done_testing();
}
