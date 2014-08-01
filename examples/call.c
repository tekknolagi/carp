#include <carp/carp.h>

int main (int argc, char **argv) {
  long long code[] = {
    CARP_INSTR_GLOADI, -5, CARP_EAX,
    CARP_INSTR_PUSHR, CARP_EAX,
    CARP_INSTR_GLOADI, -4, CARP_EAX,
    CARP_INSTR_PUSHR, CARP_EAX,
    CARP_INSTR_ADDI,
    CARP_INSTR_RET,

    CARP_INSTR_PUSHI, 7,
    CARP_INSTR_PUSHI, 9,
    CARP_INSTR_CALL, 0, 2,

    CARP_INSTR_PTOP,

    CARP_INSTR_HALT, 0
  };

  carp_machine_state m;
  carp_vm_init(&m, 10, 12);
  carp_vm_load(&m, code);
  carp_vm_run(&m);
}
