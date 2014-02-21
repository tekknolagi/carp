#include "carp/carp.h"

int main (int argc, char** argv) {
  carp_machine_state mstate;
  carp_vm_init(&mstate);

  // array of structs
  carp_command program[] = {
    // store 10 in test_name
    {CARP_INSTR_DBS, {{.s="test_name"}, {.ll=10}}},
    {CARP_INSTR_DBG, {{.s="test_name"}}},
    {CARP_INSTR_SHOW, {{.r=CARP_EAX}}},
    {CARP_INSTR_HALT, {{.ll=0}}},
  };

  carp_vm_do(&mstate, program);
}
