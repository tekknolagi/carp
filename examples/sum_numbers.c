#include <myvm/myvm.h>

int main (int argc, char **argv) {
  instruction program[] = {
    // sum numbers from 1 to 100
    encode(INSTR_LOADI,  REG0,     0,     0), // loadi r0 0
    encode(INSTR_LOADI,  REG1,   100,     0), // loadi r1 100
    encode(INSTR_LOADI,  REG2,     0,     0), // loadi r2 0
    encode(INSTR_ADD  ,  REG0,  REG1,  REG0), // add r0 r1 r0
    encode(INSTR_DECR ,  REG1,     0,     0), // decr r1
    encode(INSTR_CMP  ,  REG1,  REG2,     0), // cmp r0 r0
    encode(INSTR_RJZ  ,     2,     0,     0), // rjz 1 (jump forward +2 if eax is 0)
                                              // that is, to the halt instruction
    encode(INSTR_JMP  ,     3,     0,     0), // jmp to more addition
    encode(INSTR_SHOW ,  REG0,     0,     0), // show r0
    encode(INSTR_HALT ,     0,     0,     0), // halt 0
  };

  vm_do(program);
}
