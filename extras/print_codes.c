#include <stdio.h>

#include "../src/carp_instructions.h"

int main () {
  for (int i = 0; i < CARP_NUM_INSTRS; i++)
    printf("%d\t%s\n", i, carp_reverse_instr[i]);
}
