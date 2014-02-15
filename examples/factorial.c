#include "carp.h"

int main (int argc, char **argv) {
  carp_instruction program[] = {
    // compute 5 factorial
    carp_encode(CARP_INSTR_LOADI,  CARP_REG0,    1,    0), // loadi r0 1
    carp_encode(CARP_INSTR_LOADI,  CARP_REG1,    5,    0), // loadi r1 5
    carp_encode(CARP_INSTR_LOADI,  CARP_REG2,    1,    0), // loadi r2 0
    carp_encode(CARP_INSTR_MUL  ,  CARP_REG0, CARP_REG1, CARP_REG0), // mul r0 r1 r0
    carp_encode(CARP_INSTR_DECR ,  CARP_REG1,    0,    0), // decr r1
    carp_encode(CARP_INSTR_CMP  ,  CARP_REG1, CARP_REG2,    0), // cmp r1 r2
    carp_encode(CARP_INSTR_RJZ  ,     2,    0,    0), // rjz 2 (jump forward +2 if eax is 0)
    carp_encode(CARP_INSTR_JMP  ,     3,    0,    0), // jmp to more multiplication
    carp_encode(CARP_INSTR_SHOW ,  CARP_REG0,    0,    0), // show r0
    carp_encode(CARP_INSTR_HALT ,     0,    0,    0), // halt 0
  };

  carp_vm_do(program);
}
