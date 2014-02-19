#include "carp/carp.h"

int main (int argc, char** argv) {
  carp_machine_state mstate;
  carp_vm_init(&mstate);

  // array of structs
  carp_command program[] = {
    {CARP_INSTR_DBS, {"test_name", 10}},
    {CARP_INSTR_DBG, {"test_name"}},
    {CARP_INSTR_SHOW, {CARP_EAX}},
    {CARP_INSTR_HALT, {0}}
  };

  carp_vm_do(&mstate, program);
}
