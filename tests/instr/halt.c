#include "tests_instr.h"

int main () {
  carp_value code0[] = {CARP_I(HALT), EXIT_SUCCESS};
  carp_value code1[] = {CARP_I(HALT), EXIT_FAILURE};

  carp_machine_state m1;
  carp_value status1;

  carp_vm_init(&m, 1, 0);
  carp_vm_load(&m, code0, sizeof(code0)/sizeof(*code0));
  status = carp_vm_run(&m);
  carp_vm_cleanup(&m);

  carp_vm_init(&m1, 1, 0);
  carp_vm_load(&m1, code1, sizeof(code1)/sizeof(*code1));
  status1 = carp_vm_run(&m1);
  carp_vm_cleanup(&m1);

  plan(NO_PLAN);

  ok(status == EXIT_SUCCESS, "Machine exits with no failures.");
  ok(status1 == EXIT_FAILURE, "Machine exits with failure.");

  done_testing();
}
