#include "carp_stack.h"

int carp_stack_init (carp_stack *s, long max_height) {
  s->max_height = max_height;
  s->height = 0;

  long long *contents = malloc(max_height * sizeof(long long));
  if (contents == NULL)
    return -1;

  s->contents = contents;
  return 0;
}

// boolean
int carp_stack_empty (carp_stack *s) {
  return s->height == 0;
}

// boolean
int carp_stack_full (carp_stack *s) {
  return s->height == s->max_height;
}

int carp_stack_push (carp_stack *s, long long i) {
  if (carp_stack_full(s)) {
    long long *contents = realloc(s->contents, s->height + 5);
    if (contents == NULL)
      return -1;

    s->contents = contents;
  }
  else {
    s->contents[s->height] = i;
    s->height++;
  }

  return 0;
}

long long carp_stack_pop (carp_stack *s) {
  if (carp_stack_empty(s))
    return (int) NULL;
  else {
    s->height--;
    return s->contents[s->height];
  }
}

long long carp_stack_peek (carp_stack *s) {
  if (carp_stack_empty(s)) 
    return (int) NULL;
  else
    return s->contents[s->height - 1];
}

void carp_stack_destroy (carp_stack *s) {
  free(s->contents);
  s->contents = NULL;
  s->max_height = 0;
  s->height = 0;
}
