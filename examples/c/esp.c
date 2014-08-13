#include <carp/carp.h>

int main (int argc, char **argv) {
  carp_value code[] = {
    CARP_INSTR_PUSH, 5,
    CARP_INSTR_PUSH, 6,
    CARP_INSTR_PREG,  CARP_SP,

    CARP_INSTR_DECR, CARP_SP,
    CARP_INSTR_POP,
    CARP_INSTR_PREG, CARP_GBG,

    CARP_INSTR_HALT, 0
  };

  carp_machine_state m;
  carp_vm_init(&m, 10, 0);
  carp_vm_load(&m, code, sizeof(code));
  carp_vm_run(&m);
}
