#include "tests.h"

int main (int argc, char **argv) {
  int status;
  carp_stack s;
  long long esp;

  plan(NO_PLAN);

  status = carp_stack_init(&s, &esp, 10);
  ok(status == 0, AC_OK("Made stack."));

  status = carp_stack_empty(&s);
  ok(status == 1, AC_OK("Stack is empty by default."));

  status = carp_stack_full(&s);
  ok(status == 0, AC_OK("Stack is not full by default."));

  carp_stack_cleanup(&s);

  done_testing();
}
