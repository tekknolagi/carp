#include "carp/carp.h"

int main (int argc, char** argv) {
  carp_machine_state mstate;
  carp_vm_init(&mstate);

  carp_command program[] = {
    {CARP_INSTR_LOADI, {{.r=CARP_REG0}, {.ll='A'}}},
    {CARP_INSTR_LOADI, {{.r=CARP_REG1}, {.ll='\n'}}},
    {CARP_INSTR_PRNT, {{.r=CARP_REG0}}},
    {CARP_INSTR_PRNT, {{.r=CARP_REG1}}},
    {CARP_INSTR_PSTR, {{.s="hello\n"}}},
    {CARP_INSTR_HALT, {{.ll=0}}},
  };

  carp_vm_do(&mstate, program);
}
