#include "instructions.h"
#include "instruction_helpers.h"

// increment instruction pointer
definstr (NEXT) {
  m->regs[EIP]++;
}

void print_args (long long args[]) {
  printf("[ %lld, %lld, %lld ]",
	 args[0],
	 args[1],
	 args[2]);
}

void print_instr (instruction* i, machine_state* m) {
  printf("|- \n"
	 "| i: %d\n"
	 "| args: ", i->instr);
  print_args(i->args);
  printf("\n"
	 "| state: ");
  print_args(m->args);
  printf("\n"
	 "|-\n");
}

void printbits_num (long long num) {
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

// get and execute the instruction
void eval (machine_state *m) {
  instructions[m->instr](m);
}

// "encode" the instruction & 3 args into a 16 bit integer
instruction encode (int instr, long long arg1, long long arg2, long long arg3) {
  instruction i;
  i.instr = instr;
  memcpy(i.args,
	 ((long long[NUM_ARGS]){arg1, arg2, arg3}), // need extra parentheses otherwise memcpy macro barfs
	 sizeof(long long[NUM_ARGS]));

  return i;
}

// "decode" the instruction & 3 args into machine state
void decode (instruction* i, machine_state* m) {
  m->instr = i->instr;
  memcpy(m->args, i->args, sizeof(long long[NUM_ARGS]));
}
