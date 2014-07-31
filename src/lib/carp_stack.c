#include "carp_stack.h"

int carp_stack_init (carp_stack *s, long long *height, long max_height) {
  assert(s != NULL);
  assert(height != NULL);
  assert(max_height > 0);

  s->max_height = max_height;
  s->height = height;

  long long *contents = calloc(max_height, sizeof(*contents));
  if (contents == NULL)
    return -1;

  s->contents = contents;
  return 0;
}

// boolean
int carp_stack_empty (carp_stack *s) {
  assert(s != NULL);

  return (*s->height) == 0;
}

// boolean
int carp_stack_full (carp_stack *s) {
  assert(s != NULL);

  return (*s->height) == s->max_height;
}

int carp_stack_push (carp_stack *s, long long i) {
  assert(s != NULL);

  if (carp_stack_full(s)) {
    long long *contents = realloc(s->contents, (2*(*s->height) + 1) * sizeof(*contents));
    if (contents == NULL) {
      return -1;
    }

    s->max_height *= 2;
    s->max_height++;
    s->contents = contents;
  }

  s->contents[(*s->height)] = i;
  (*s->height)++;

  return 0;
}

long long carp_stack_pop (carp_stack *s) {
  assert(s != NULL);

  if (carp_stack_empty(s))
    return (int) NULL;
  else {
    (*s->height)--;
    return s->contents[(*s->height)];
  }
}

long long carp_stack_peek (carp_stack *s) {
  assert(s != NULL);

  if (carp_stack_empty(s)) 
    return (int) NULL;
  else
    return s->contents[(*s->height) - 1];
}

void carp_stack_destroy (carp_stack *s) {
  assert(s != NULL);

  free(s->contents);
  s->contents = NULL;
  s->max_height = 0;
  (*s->height) = 0;
}
