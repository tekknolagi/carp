#include "carp.h"

int main (int argc, char **argv) {
  carp_instruction program[] = {
    // sum numbers from 1 to 100
    carp_encode(CARP_INSTR_LOADI,  CARP_REG0,     0,     0), // loadi r0 0
    carp_encode(CARP_INSTR_LOADI,  CARP_REG1,   100,     0), // loadi r1 100
    carp_encode(CARP_INSTR_LOADI,  CARP_REG2,     0,     0), // loadi r2 0
    carp_encode(CARP_INSTR_ADD  ,  CARP_REG0,  CARP_REG1,  CARP_REG0), // add r0 r1 r0
    carp_encode(CARP_INSTR_DECR ,  CARP_REG1,     0,     0), // decr r1
    carp_encode(CARP_INSTR_CMP  ,  CARP_REG1,  CARP_REG2,     0), // cmp r0 r0
    carp_encode(CARP_INSTR_RJZ  ,     2,     0,     0), // rjz 1 (jump forward +2 if eax is 0)
                                              // that is, to the halt instruction
    carp_encode(CARP_INSTR_JMP  ,     3,     0,     0), // jmp to more addition
    carp_encode(CARP_INSTR_SHOW ,  CARP_REG0,     0,     0), // show r0
    carp_encode(CARP_INSTR_HALT ,     0,     0,     0), // halt 0
  };

  carp_vm_do(program);
}
