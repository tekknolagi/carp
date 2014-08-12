#include "tests.h"
#include "../src/lib/carp_stack.h"

int main (int argc, char **argv) {
  int status;
  carp_stack s;
  long long esp;
  long long val;
  long long to_push = 1;

  plan(NO_PLAN);

  status = carp_stack_init(&s, &esp, 10);
  ok(status == 0, "Made stack.");

  status = carp_stack_empty(&s);
  ok(status == 1, "Stack is empty by default.");

  status = carp_stack_pop(&s, &val);
  ok(status == -1, "Error popping empty stack.");

  status = carp_stack_full(&s);
  ok(status == 0, "Stack is not full by default.");

  status = carp_stack_push(&s, to_push);
  ok(status == 0, "Pushed successfully.");

  status = carp_stack_pop(&s, &val);
  ok(status == 0, "Popped value successfully.");
  ok(val == to_push, "Popped same value as pushed.");

  carp_stack_cleanup(&s);
  ok(s.contents == NULL, "Contents are NULL.");

  done_testing();
}
