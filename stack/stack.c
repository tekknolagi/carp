#include "stdio.h"
#include "stdlib.h"

#include "stack.h"

void stack_init(stack_type* s, long max_height) {
  s->height = 0;
  s->max_height = max_height;
  long long* contents = (long long *) malloc(max_height * sizeof(long long));
  if (contents == NULL) {
    fprintf(stderr, "Not enough memory to initialize stack.");
    exit(1);
  }
  s->contents = contents;
}

char stack_empty(stack_type* s) {
  return s->height == 0;
}

char stack_full(stack_type* s) {
  return s->height == s->max_height;
}

void stack_push(stack_type* s, long long i) {
  if (stack_full(s)) {
    long long* contents = (long long *) realloc(s->contents, 5);
    if (contents == NULL) {
      fprintf(stderr, "Not enough memory to add to stack.");
      exit(1);
    }
    s->contents = contents;
  }
  else {
    s->contents[s->height] = i;
    s->height++;
  }
}

long long stack_pop (stack_type* s) {
  if (stack_empty(s)) {
    fprintf(stderr, "Stack is empty.");
    exit(1);
  }
  else {
    s->height--;
    long long i = s->contents[s->height];
    
    return i;
  }
}

void stack_destroy (stack_type* s) {
  free(s->contents);
  s->contents = NULL;
  s->max_height = 0;
  s->height = 0;
}
