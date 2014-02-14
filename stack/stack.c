#include "stdlib.h"
#include "stack.h"

void stack_init(stack_type* s, long max_height) {
  s->height = 0;
  s->max_height = max_height;
  s->contents = (long long *) malloc(max_height * sizeof(long long));
}

void stack_push(stack_type* s, long long i) {
  if (s->height == s->max_height) {
    s->contents = (long long *) realloc(s->contents, 5);
  }
  else {
    s->height++;
    s->contents[s->height] = i;
  }
}

long long stack_pop (stack_type* s) {
  long long i = s->contents[s->height];
  s->height--;

  return i;
}

void stack_destroy (stack_type* s) {
  free(s->contents);
  s->contents = NULL;
  s->max_height = 0;
  s->height = 0;
}
