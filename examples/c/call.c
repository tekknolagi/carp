#include <carp/carp.h>

int main (int argc, char **argv) {
  carp_value code[] = {
    CARP_INSTR_GLOAD, -5, // 1st arg
    CARP_INSTR_GLOAD, -4, // 2nd arg
    CARP_INSTR_ADD,
    CARP_INSTR_RET,

    CARP_INSTR_PUSH, 7, // 1st arg
    CARP_INSTR_PUSH, 9, // 2nd arg
    CARP_INSTR_CALL, 0, 2,

    CARP_INSTR_PTOP,

    CARP_INSTR_HALT, 0
  };

  carp_machine_state m;
  carp_vm_init(&m, 1, 6);
  carp_vm_load(&m, code, sizeof(code));
  return carp_vm_run(&m);
}
