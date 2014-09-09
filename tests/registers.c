#include "tests.h"
#include "../src/carp_registers.h"

int main () {
  carp_bool status = 0;
  carp_value regs[CARP_NUM_REGS];
  carp_value reg = 7;
  carp_value value = 19;
  carp_value *res = NULL;
  carp_value adder = 23;

  plan(NO_PLAN);

  carp_reg_init(regs);
  for (int i = 0; i < CARP_NUM_REGS; i++)
    status += regs[i];
  ok(status == 0, "All the registers are set to 0.");

  status = carp_reg_set(regs, reg, value);
  ok(status == 0, "Set reports no errors.");
  ok(regs[reg] == value, "Set is successful.");

  res = carp_reg_get(regs, reg);
  ok(res != NULL, "Get reports no errors.");
  ok(*res == value, "Get is successful.");

  status = carp_reg_add(regs, reg, adder);
  ok(status == 0, "Add reports no errors.");
  ok(regs[reg] == value + adder, "Add is successful.");

  status = carp_reg_sub(regs, reg, adder);
  ok(status == 0, "Sub reports no errors.");
  ok(regs[reg] == value, "Sub is successful.");

  status = carp_reg_inc(regs, reg);
  ok(status == 0, "Inc reports no errors.");
  ok(regs[reg] == value + 1, "Inc is successful.");

  status = carp_reg_dec(regs, reg);
  ok(status == 0, "Dec reports no errors.");
  ok(regs[reg] == value, "Dec is successful.");

  done_testing();
}
