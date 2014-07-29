#include "lib/carp_ht.h"

int httest_main (int argc, char **argv) {
  int status;
  carp_ht h;
  char *name = "maxwell";

  carp_ht_init(&h);

  carp_ht *res = carp_ht_set(&h, "maxwell", 17);
  if (res == NULL) {
    fprintf(stderr, "could not add maxwell\n");
    carp_ht_cleanup(&h);
    exit(1);
  }

  carp_ht_set(&h, "sophie", 18);
  carp_ht_print(&h);
  carp_ht_del(&h, "sophie");
  carp_ht_print(&h);

  res = carp_ht_get(&h, "maxwell");
  if (res == NULL) {
    fprintf(stderr, "could not find maxwell\n");
    carp_ht_cleanup(&h);
    exit(1);
  }

  carp_ht_cleanup(&h);

  return 0;
}
