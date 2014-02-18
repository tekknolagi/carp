#include "carp/carp.h"

int main (int argc, char** argv) {
  carp_machine_state mstate;
  carp_init_vm(&mstate);

  // array of structs
  carp_instruction program[] = {
    // sum numbers from 1 to 100
    {CARP_INSTR_LOADI, {CARP_REG0, 0}}, // loadi r0 0
    {CARP_INSTR_LOADI, {CARP_REG1, 100}}, // loadi r1 100
    {CARP_INSTR_LOADI, {CARP_REG2, 0}}, // loadi r2 0
    {CARP_INSTR_ADD, {CARP_REG0, CARP_REG1, CARP_REG0}}, // add r0 r1 r0
    {CARP_INSTR_DECR, {CARP_REG1}}, // decr r1
    {CARP_INSTR_CMP, {CARP_REG1, CARP_REG2}}, // cmp r1 r2
    {CARP_INSTR_RJZ, {2}}, // rjz 2 (jump forward +2 if eax is 0)
                           // that is, to the halt instruction
    {CARP_INSTR_JMP, {3}}, // jmp to more addition
    {CARP_INSTR_SHOW, {CARP_REG0}}, // show r0
    {CARP_INSTR_HALT, {0}}, // halt 0
  };

  carp_vm_do(&mstate, program);
}
