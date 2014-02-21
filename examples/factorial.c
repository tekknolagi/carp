#include "carp/carp.h"

int main (int argc, char** argv) {
  carp_machine_state mstate;
  carp_vm_init(&mstate);

  // array of structs
  carp_command program[] = {
    // compute 5 factorial
    {CARP_INSTR_LOADI, {{.r=CARP_REG0}, {.ll=1}}}, // loadi r0 1
    {CARP_INSTR_LOADI, {{.r=CARP_REG1}, {.ll=5}}}, // loadi r1 5
    {CARP_INSTR_LOADI, {{.r=CARP_REG2}, {.ll=1}}}, // loadi r2 1
    {CARP_INSTR_MUL, {{.r=CARP_REG0}, {.r=CARP_REG1}, {.r=CARP_REG0}}}, // mul r0 r1 r0
    {CARP_INSTR_DECR, {{.r=CARP_REG1}}}, // decr r1
    {CARP_INSTR_CMP, {{.r=CARP_REG1}, {.r=CARP_REG2}}}, // cmp r1 r2
    {CARP_INSTR_RJZ, {{.ll=2}}}, // rjz 2 (jump forward +2 if eax is 0)
    {CARP_INSTR_JMP, {{.ll=3}}}, // jmp to more multiplication
    {CARP_INSTR_SHOW, {{.r=CARP_REG0}}}, // show r0
    {CARP_INSTR_HALT, {{.i=0}}}, // halt 0
  };

  carp_vm_do(&mstate, program);
}
