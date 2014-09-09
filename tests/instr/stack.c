#include "tests_instr.h"

int main () {
  carp_value val0 = 127;
  carp_value val1 = 32;
  carp_value reg0 = CARP_R0;
  carp_value reg1 = CARP_R1;
  carp_value code[] = {CARP_I(PUSH), val0,
		       CARP_I(PUSH), val1,
		       CARP_I(ADD),

		       CARP_I(PUSH), val0,
		       CARP_I(PUSH), val1,
		       CARP_I(SUB),

		       CARP_I(PUSH), val0,
		       CARP_I(PUSH), val1,
		       CARP_I(MUL),

		       CARP_I(PUSH), val0,
		       CARP_I(PUSH), val1,
		       CARP_I(MOD),

		       CARP_I(PUSH), val0,
		       CARP_I(PUSH), val1,
		       CARP_I(SHR),

		       CARP_I(PUSH), val0,
		       CARP_I(PUSH), val1,
		       CARP_I(SHL),

		       CARP_I(PUSH), val0,
		       CARP_I(NOT),

		       CARP_I(PUSH), val0,
		       CARP_I(PUSH), val1,
		       CARP_I(XOR),

		       CARP_I(PUSH), val0,
		       CARP_I(PUSH), val1,
		       CARP_I(OR),

		       CARP_I(PUSH), val0,
		       CARP_I(PUSH), val1,
		       CARP_I(AND),

		       CARP_I(PUSH), val0,
		       CARP_I(INC),

		       CARP_I(PUSH), val0,
		       CARP_I(DEC),

		       CARP_I(LOADR), reg0, val0,
		       CARP_I(PUSHR), reg0,

		       CARP_I(PUSH), val0,

		       CARP_I(PUSH), val0,
		       CARP_I(POP), reg1,

		       CARP_I(PUSH), val0,
		       CARP_I(PUSH), val1,
		       CARP_I(CMP),

		       CARP_I(PUSH), val0,
		       CARP_I(PUSH), val0,
		       CARP_I(CMP),

		       CARP_I(PUSH), 1,
		       CARP_I(PUSH), 2,
		       CARP_I(LT),

		       CARP_I(PUSH), 2,
		       CARP_I(PUSH), 1,
		       CARP_I(LT),

		       CARP_I(PUSH), 2,
		       CARP_I(PUSH), 1,
		       CARP_I(GT),

		       CARP_I(PUSH), 1,
		       CARP_I(PUSH), 2,
		       CARP_I(GT),

		       CARP_I(HALT), EXIT_SUCCESS};

  carp_vm_init(&m, 1, 0);
  carp_vm_load(&m, code, sizeof(code)/sizeof(*code));
  carp_vm_run(&m);

  plan(NO_PLAN);

  ok(m.stack.contents[0] == val0 + val1,  "Stack ADD successful.");
  ok(m.stack.contents[1] == val0 - val1,  "Stack SUB successful.");
  ok(m.stack.contents[2] == val0 * val1,  "Stack MUL successful.");
  ok(m.stack.contents[3] == val0 % val1,  "Stack MOD successful.");
  ok(m.stack.contents[4] == val0 >> val1, "Stack SHR successful.");
  ok(m.stack.contents[5] == val0 << val1, "Stack SHL successful.");
  ok(m.stack.contents[6] == ~val0,        "Stack NOT successful.");
  ok(m.stack.contents[7] == (val0 ^ val1),"Stack XOR successful.");
  ok(m.stack.contents[8] == (val0 | val1),"Stack OR  successful.");
  ok(m.stack.contents[9] == (val0 & val1),"Stack AND successful.");
  ok(m.stack.contents[10] == val0 + 1,    "Stack INC successful.");
  ok(m.stack.contents[11] == val0 - 1,    "Stack DEC successful.");
  ok(m.stack.contents[12] == val0,        "Stack PUSHR successful.");
  ok(m.stack.contents[13] == val0,        "Stack PUSH successful.");
  ok(m.regs[reg1] == val0,                "Stack POP successful.");
  ok(m.stack.contents[14] != 0,           "Stack CMP != 0 successful.");
  ok(m.stack.contents[15] == 0,           "Stack CMP == 0 successful.");
  ok(m.stack.contents[16] == 1,           "Stack LT true successful.");
  ok(m.stack.contents[17] == 0,           "Stack LT false successful.");
  ok(m.stack.contents[18] == 1,           "Stack GT true successful.");
  ok(m.stack.contents[19] == 0,           "Stack GT false successful.");

  done_testing();

  carp_vm_cleanup(&m);
}
