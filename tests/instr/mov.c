#include "tests_instr.h"

int main () {
  carp_value val = 127;
  carp_value code[] = {CARP_I(LOADR), CARP_R0, val,
		       CARP_I(MOV), CARP_R1, CARP_R0,
		       CARP_I(HALT), EXIT_SUCCESS};

  carp_vm_init(&m, 1, 0);
  carp_vm_load(&m, code, sizeof(code)/sizeof(*code));
  carp_vm_run(&m);

  plan(NO_PLAN);

  ok(m.regs[CARP_R1] == val, "Moved register successfully.");

  done_testing();

  carp_vm_cleanup(&m);
}
