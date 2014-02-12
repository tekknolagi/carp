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

void printbits     (unsigned);
void eval          (int, int, int, int);
unsigned encode    (int, int, int, int);
void decode        (unsigned, int*, int*, int*, int*);

#endif
