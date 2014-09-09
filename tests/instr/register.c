#include "tests_instr.h"

int main () {
  carp_value val = 127;
  carp_value code[] = {CARP_I(LOADR), CARP_R0, val,

		       CARP_I(MOV), CARP_R1, CARP_R0,

		       CARP_I(MOV), CARP_R2, CARP_R0,
		       CARP_I(INCR), CARP_R2,

		       CARP_I(MOV), CARP_R3, CARP_R0,
		       CARP_I(DECR), CARP_R3,

		       CARP_I(HALT), EXIT_SUCCESS};

  carp_vm_init(&m, 1, 0);
  carp_vm_load(&m, code, sizeof(code)/sizeof(*code));
  carp_vm_run(&m);
  carp_vm_cleanup(&m);

  plan(NO_PLAN);

  ok(m.regs[CARP_R0] == val, "Set register successfully.");
  ok(m.regs[CARP_R1] == val, "Moved register successfully.");
  ok(m.regs[CARP_R2] == val + 1, "Incremented register successfully.");
  ok(m.regs[CARP_R3] == val - 1, "Decremented register successfully.");

  done_testing();
}
