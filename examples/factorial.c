#include "carp.h"

int main (int argc, char **argv) {
  carp_instruction program[] = {
    // compute 5 factorial
    {CARP_INSTR_LOADI, {CARP_REG0, 1}}, // loadi r0 1
    {CARP_INSTR_LOADI, {CARP_REG1, 5}}, // loadi r1 5
    {CARP_INSTR_LOADI, {CARP_REG2, 1}}, // loadi r2 1
    {CARP_INSTR_MUL, {CARP_REG0, CARP_REG1, CARP_REG0}}, // mul r0 r1 r0
    {CARP_INSTR_DECR, {CARP_REG1}}, // decr r1
    {CARP_INSTR_CMP, {CARP_REG1, CARP_REG2}}, // cmp r1 r2
    {CARP_INSTR_RJZ, {2}}, // rjz 2 (jump forward +2 if eax is 0)
    {CARP_INSTR_JMP, {3}}, // jmp to more multiplication
    {CARP_INSTR_SHOW, {CARP_REG0}}, // show r0
    {CARP_INSTR_HALT, {0}} // halt 0
  };

  carp_vm_do(program);
}
