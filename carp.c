#include "carp.h"

int main (int argc, char** argv) {
  carp_machine_state mstate;
  carp_vm_init(&mstate);

  carp_command program[] = {}; // something
  carp_vm_do(&mstate, program);
}
