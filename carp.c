#include "carp_machine.h"

int main (int argc, char **argv) {
  char data[][CARP_HT_KEY_LENGTH] = {
    "hello",
    "world"
  };

  long long code[] = {
    // 3 + 9 + 7 == 19?
    CARP_INSTR_LOADI, CARP_REG0, 7,
    CARP_INSTR_PREG, CARP_REG0,
    CARP_INSTR_PUSHI, 3,
    CARP_INSTR_PUSHI, 9,
    CARP_INSTR_ADDI,
    CARP_INSTR_PTOP,

    CARP_INSTR_PUSHR, CARP_REG0,
    CARP_INSTR_ADDI,
    CARP_INSTR_PTOP,

    CARP_INSTR_PUSHI, 19,
    CARP_INSTR_CMP,
    CARP_INSTR_PREG, CARP_EAX,

    // set & get 20
    CARP_INSTR_DBS, &data[0], 20,
    CARP_INSTR_DBG, &data[0],
    CARP_INSTR_PREG, CARP_EAX,
    
    // should be in $?
    CARP_INSTR_HALT, 1
  };

  carp_machine_state m;
  carp_vm_init(&m, 10);
  carp_vm_load(&m, code);
  carp_vm_run(&m);
}
