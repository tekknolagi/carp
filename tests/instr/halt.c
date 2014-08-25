#include "tests_instr.h"

int main () {
  carp_value code[] = {CARP_I(HALT), EXIT_SUCCESS};

  carp_vm_init(&m, 1, 0);
  carp_vm_load(&m, code, sizeof(code)/sizeof(*code));
  status = carp_vm_run(&m);

  plan(NO_PLAN);

  ok(status == EXIT_SUCCESS, "Machine exits with no failures.");

  done_testing();

  carp_vm_cleanup(&m);
}
