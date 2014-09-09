#include <carp/carp_machine.h>

int main (int argc, char **argv) {
  char data[][CARP_HT_KEY_LENGTH] = {
    "hello",
    "world"
  };

  // I wish there was a better way to do this.
  carp_value hellop = (carp_value) &data[0];

  carp_value code[] = {
    // 3 + 9 + 7 == 19?
    CARP_INSTR_LOADR,  CARP_R0, 7,
    CARP_INSTR_PREG,  CARP_R0,
    CARP_INSTR_PUSH,  3,
    CARP_INSTR_PUSH,  9,
    CARP_INSTR_ADD,
    CARP_INSTR_PTOP,

    CARP_INSTR_PUSHR, CARP_R0,
    CARP_INSTR_ADD,
    CARP_INSTR_PTOP,

    CARP_INSTR_PUSH,  19,
    CARP_INSTR_CMP,
    CARP_INSTR_PREG,  CARP_AX,

    // set & get 20
    CARP_INSTR_DBS,   hellop, 20,
    CARP_INSTR_DBG,   hellop, CARP_AX,
    CARP_INSTR_PREG,  CARP_AX,
    
    // should be in $?
    CARP_INSTR_HALT, 1
  };

  carp_machine_state m;
  carp_vm_init(&m, 10, 0);
  carp_vm_load(&m, code, sizeof(code)/sizeof(*code));
  carp_value ecode = carp_vm_run(&m);
  carp_vm_cleanup(&m);
  return ecode;
}
