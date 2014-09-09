#include <carp/carp_machine.h>

int main (int argc, char **argv) {
  carp_value code[] = {
    CARP_INSTR_LOAD, -4, // 1st arg
    CARP_INSTR_LOAD, -3, // 2nd arg
    CARP_INSTR_ADD,
    CARP_INSTR_POP, CARP_REG_AX,
    CARP_INSTR_RET,

    CARP_INSTR_PUSH, 7, // 1st arg
    CARP_INSTR_PUSH, 9, // 2nd arg
    CARP_INSTR_CALL, 0,

    CARP_INSTR_PREG, CARP_REG_AX,

    CARP_INSTR_HALT, 0
  };

  carp_machine_state m;
  carp_vm_init(&m, 1, 6);
  carp_vm_load(&m, code, sizeof(code)/sizeof(*code));
  carp_value ecode = carp_vm_run(&m);
  carp_vm_cleanup(&m);
  return ecode;
}
