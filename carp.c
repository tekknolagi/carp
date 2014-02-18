#include "carp.h"

int main (int argc, char** argv) {
  carp_machine_state mstate;
  carp_init_vm(&mstate);

  carp_instruction program[] = {}; // something
  carp_vm_do(&mstate, program);
}
