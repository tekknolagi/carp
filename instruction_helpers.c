#include "instructions.h"
#include "instruction_helpers.h"

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

// increment instruction pointer
definstr (next) {
  m->regs[EIP]++;
}

// get and execute the instruction
void eval (machine_state *m) {
  instructions[m->instr](m);
}

// "encode" the instruction & 3 args into a 16 bit integer
unsigned encode (int instr, int arg1, int arg2, int arg3) {
  unsigned encoded = 0;
  encoded += (instr & 0xF) << 12;
  encoded += (arg1  & 0xF) << 8;
  encoded += (arg2  & 0xF) << 4;
  encoded += (arg3  & 0xF);
  return encoded;
}

// "decode" the instruction & 3 args into machine state
void decode (unsigned encoded, machine_state *m) {
  m->instr = (encoded & 0xF000) >> 12;
  m->arg1  = (encoded & 0x0F00) >>  8;
  m->arg2  = (encoded & 0x00F0) >>  4;
  m->arg3  = (encoded & 0x000F);
}
