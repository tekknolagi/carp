#ifndef STACK_H
#define STACK_H

typedef struct stack_type {
  long max_height;
  long height;
  long long *contents;
} stack_type;

void stack_init (stack_type*, long);
void stack_push (stack_type*, long long);
long long stack_pop (stack_type*);
void stack_destroy (stack_type*);

#endif
