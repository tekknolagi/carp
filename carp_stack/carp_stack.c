#include "stdio.h"
#include "stdlib.h"

#include "carp_stack.h"

void carp_stack_init(carp_stack_type* s, long max_height) {
  s->height = 0;
  s->max_height = max_height;
  long long* contents = (long long *) malloc(max_height * sizeof(long long));
  if (contents == NULL) {
    fprintf(stderr, "Not enough memory to initialize carp_stack.");
    exit(1);
  }
  s->contents = contents;
}

char carp_stack_empty(carp_stack_type* s) {
  return s->height == 0;
}

char carp_stack_full(carp_stack_type* s) {
  return s->height == s->max_height;
}

void carp_stack_push(carp_stack_type* s, long long i) {
  if (carp_stack_full(s)) {
    long long* contents = (long long *) realloc(s->contents, 5);
    if (contents == NULL) {
      fprintf(stderr, "Not enough memory to add to carp_stack.");
      exit(1);
    }
    s->contents = contents;
  }
  else {
    s->contents[s->height] = i;
    s->height++;
  }
}

long long carp_stack_pop (carp_stack_type* s) {
  if (carp_stack_empty(s)) {
    fprintf(stderr, "Carp_Stack is empty.");
    exit(1);
  }
  else {
    s->height--;
    long long i = s->contents[s->height];
    
    return i;
  }
}

void carp_stack_destroy (carp_stack_type* s) {
  free(s->contents);
  s->contents = NULL;
  s->max_height = 0;
  s->height = 0;
}
