#include "carp/carp.h"

int main (int argc, char** argv) {
  carp_machine_state mstate;
  carp_vm_init(&mstate);

  // array of structs
  carp_command program[] = {
    // sum numbers from 1 to 100
    {CARP_INSTR_LOADI, {{.r=CARP_REG0}, {.ll=0}}}, // loadi r0 0
    {CARP_INSTR_LOADI, {{.r=CARP_REG1}, {.ll=100}}}, // loadi r1 100
    {CARP_INSTR_LOADI, {{.r=CARP_REG2}, {.ll=0}}}, // loadi r2 0
    {CARP_INSTR_ADD, {{.r=CARP_REG0}, {.r=CARP_REG1}, {.r=CARP_REG0}}}, // add r0 r1 r0
    {CARP_INSTR_DECR, {{.r=CARP_REG1}}}, // decr r1
    {CARP_INSTR_CMP, {{.r=CARP_REG1}, {.r=CARP_REG2}}}, // cmp r1 r2
    {CARP_INSTR_RJZ, {{.ll=2}}}, // rjz 2 (jump forward +2 if eax is 0)
                           // that is, to the halt instruction
    {CARP_INSTR_JMP, {{.ll=3}}}, // jmp to more addition
    {CARP_INSTR_SHOW, {{.r=CARP_REG0}}}, // show r0
    {CARP_INSTR_HALT, {{.ll=0}}}, // halt 0
  };

  carp_vm_do(&mstate, program);
}
