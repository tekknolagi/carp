#include <inttypes.h>
#include "stack.h"

static bool carp_stack_full (carp_stack *);

/*
  Initialize the stack with pointer to the height and initial height.
*/
bool carp_stack_init (carp_stack *s, carp_value *height, carp_value max_height) {
  assert(s != NULL);
  assert(height != NULL);
  assert(max_height > 0);

  s->max_height = max_height;
  s->height = height;

  carp_value *contents = calloc(max_height, sizeof *contents);
  if (contents == NULL)
    return 1;

  s->contents = contents;
  return 0;
}

/*
  Return true if the height is 0 (meaning the stack is empty).
*/
bool carp_stack_empty (carp_stack *s) {
  assert(s != NULL);

  return (*s->height) == 0;
}

/*
  Return true if the height is the max height (meaning the stack is full).
*/
static bool carp_stack_full (carp_stack *s) {
  assert(s != NULL);

  return (*s->height) == s->max_height;
}

/*
  Push value onto the stack. Return 0 if stack push succeeds.
*/
bool carp_stack_push (carp_stack *s, carp_value i) {
  assert(s != NULL);

  if (carp_stack_full(s)) {
    // give stack 2n + 1 its existing space, hopefully more efficiently allocating
    carp_value new_height = 2*s->max_height + 1;
    carp_value *new_contents = realloc(s->contents, new_height * sizeof *new_contents);
    if (new_contents == NULL)
      return 1;

    // if all is well, update pointer and capacity
    s->max_height = new_height;
    s->contents = new_contents;
  }

  assert(!carp_stack_full(s));
  // push the value and increase the height
  s->contents[(*s->height)] = i;
  (*s->height)++;

  return 0;
}

/*
  Pop the top of the stack into v. Return 0 if stack pop succeeds.
*/
bool carp_stack_pop (carp_stack *s, carp_value *v) {
  assert(s != NULL);

  if (carp_stack_empty(s))
    return 1;
  else {
    (*s->height)--;
    *v = s->contents[(*s->height)];
    return 0;
  }
}

/*
  Peek the top of the stack into v. Return 0 if the peek succeeds.
*/
bool carp_stack_peek (carp_stack *s, carp_value *v) {
  assert(s != NULL);

  if (carp_stack_empty(s)) 
    return 1;
  else
    *v = s->contents[(*s->height) - 1];

  return 0;
}

/*
  Print the contents of the stack onto stdout.
*/
void carp_stack_print (carp_stack *s, FILE *fp) {
  assert(s != NULL);

  if (fp == NULL)
    fp = stdout;

  fprintf(fp, "[ ");

  for (carp_value i = 0; i < (*s->height); i++)
    fprintf(fp, "%" PRId64 " ", s->contents[i]);

  fprintf(fp, "]\n");
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
