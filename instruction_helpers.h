#ifndef INSTRUCTION_HELPERS_H
#define INSTRUCTION_HELPERS_H

/*
 * structure of a word (16 bits):
 * 
 * 4 for instr name
 * 4 for arg1
 * 4 for arg2
 * 4 for arg3
 */

definstr (next);
void print_args      (long long []);
void print_instr     (instruction*, machine_state*);
void printbits_num   (long long);
void eval            (machine_state*);
instruction encode   (int, long long, long long, long long);
void decode          (instruction*, machine_state*);

#endif
