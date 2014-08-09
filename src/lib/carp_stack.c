#include "carp_stack.h"

/*
  Initialize the stack with pointer to the height and initial height.
*/
short int carp_stack_init (carp_stack *s, long long *height, long long max_height) {
  assert(s != NULL);
  assert(height != NULL);
  assert(max_height > 0);

  s->max_height = max_height;
  s->height = height;

  long long *contents = calloc(max_height, sizeof *contents);
  if (contents == NULL)
    return -1;

  s->contents = contents;
  return 0;
}

/*
  Return true if the height is 0 (meaning the stack is empty).
*/
short int carp_stack_empty (carp_stack *s) {
  assert(s != NULL);

  return (*s->height) == 0;
}

/*
  Return true if the height is the max height (meaning the stack is full).
*/
short int carp_stack_full (carp_stack *s) {
  assert(s != NULL);

  return (*s->height) == s->max_height;
}

/*
  Push value onto the stack. Return 0 if stack push succeeds.
*/
short int carp_stack_push (carp_stack *s, long long i) {
  assert(s != NULL);

  if (carp_stack_full(s)) {
    // give stack 2n + 1 its existing space, hopefully more efficiently allocating
    long long *contents = realloc(s->contents, (2*(*s->height) + 1) * sizeof *contents);
    if (contents == NULL)
      return -1;

    // and of course update max_height
    s->max_height *= 2;
    s->max_height++;

    // and update the pointer
    s->contents = contents;
  }

  // in either case, push a value and increase the height
  s->contents[(*s->height)] = i;
  (*s->height)++;

  return 0;
}

/*
  Pop the top of the stack into v. Return 0 if stack pop succeeds.
*/
short int carp_stack_pop (carp_stack *s, long long *v) {
  assert(s != NULL);

  if (carp_stack_empty(s))
    return -1;
  else {
    (*s->height)--;
    *v = s->contents[(*s->height)];
    return 0;
  }
}

/*
  Peek the top of the stack into v. Return 0 if the peek succeeds.
*/
short int carp_stack_peek (carp_stack *s, long long *v) {
  assert(s != NULL);

  if (carp_stack_empty(s)) 
    return -1;
  else
    *v = s->contents[(*s->height) - 1];

  return 0;
}

/*
  Print the contents of the stack onto stdout.
*/
void carp_stack_print (carp_stack *s) {
  printf("[ ");

  for (long long i = 0; i < (*s->height); i++)
    printf("%lld ", s->contents[i]);

  printf("]\n");
}

/*
  Clean up the stack memory.
*/
void carp_stack_cleanup (carp_stack *s) {
  assert(s != NULL);

  free(s->contents);
  s->contents = NULL;
  s->max_height = 0;
  (*s->height) = 0;
}
