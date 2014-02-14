#include <myvm/myvm.h>

int main (int argc, char **argv) {
  instruction program[] = {
    // compute 5 factorial
    encode(INSTR_LOADI,  REG0,    1,    0), // loadi r0 1
    encode(INSTR_LOADI,  REG1,    5,    0), // loadi r1 5
    encode(INSTR_LOADI,  REG2,    1,    0), // loadi r2 0
    encode(INSTR_MUL  ,  REG0, REG1, REG0), // mul r0 r1 r0
    encode(INSTR_DECR ,  REG1,    0,    0), // decr r1
    encode(INSTR_CMP  ,  REG1, REG2,    0), // cmp r1 r2
    encode(INSTR_RJZ  ,     2,    0,    0), // rjz 2 (jump forward +2 if eax is 0)
    encode(INSTR_JMP  ,     3,    0,    0), // jmp to more multiplication
    encode(INSTR_SHOW ,  REG0,    0,    0), // show r0
    encode(INSTR_HALT ,     0,    0,    0), // halt 0
  };

  vm_do(program);
}
