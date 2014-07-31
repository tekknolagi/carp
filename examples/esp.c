#include <carp/carp.h>

int main (int argc, char **argv) {
  long long code[] = {
    CARP_INSTR_PUSHI, 5,
    CARP_INSTR_PREG,  CARP_ESP,

    CARP_INSTR_HALT, 0
  };

  carp_machine_state m;
  carp_vm_init(&m, 10);
  carp_vm_load(&m, code);
  carp_vm_run(&m);
}
