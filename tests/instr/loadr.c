#include "tests_instr.h"

int main () {
  carp_reg reg = CARP_R0;
  carp_value val = 127;
  carp_value code[] = {CARP_I(LOADR), reg, val,
		       CARP_I(HALT), EXIT_SUCCESS};

  carp_vm_init(&m, 1, 0);
  carp_vm_load(&m, code, sizeof code);
  carp_vm_run(&m);

  plan(NO_PLAN);

  ok(m.regs[reg] == val, "Set register successfully.");

  done_testing();
}
