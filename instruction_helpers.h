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

void printbits (unsigned num) {
  unsigned int mask = 32768;   //mask = [1000 0000 0000 0000]
  int n = 0;
  
  while(mask > 0) {
    if (n > 0 && n%4 == 0) printf(" ");
    if((num & mask) == 0 )
      printf("0");
    else
      printf("1");
    mask = mask >> 1 ;  // Right Shift
    n++;
  }
  printf("\n");
}

void eval (int instr, int arg1, int arg2, int arg3) {
  instructions[instr](arg1, arg2, arg3);
}

unsigned encode (int instr, int arg1, int arg2, int arg3) {
  unsigned encoded = 0;
  encoded += (instr << 12) & 0xF000;
  encoded += (arg1  <<  8) & 0xF00;
  encoded += (arg2  <<  4) & 0xF0;
  encoded += arg3;
  printf("i: "); printbits(encoded);
  return encoded;
}

void decode (unsigned encoded, int *instr, int *arg1, int *arg2, int *arg3) {
  *instr = (encoded & 0xF000) >> 12;
  *arg1  = (encoded & 0x0F00) >>  8;
  *arg2  = (encoded & 0x00F0) >>  4;
  *arg3  = (encoded & 0x000F);
}

#endif
