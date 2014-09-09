#include <carp/carp_machine.h>

int main (int argc, char **argv) {
  char data[][CARP_HT_KEY_LENGTH] = {
    "max"
  };

  carp_value strp = (carp_value) &data[0];

  carp_value code[] = {
    CARP_INSTR_DBS, strp, 10,
    CARP_INSTR_DBG, strp, CARP_R0,
    CARP_INSTR_PREG, CARP_R0,
    CARP_INSTR_HALT, 0
  };

  carp_machine_state m;
  carp_vm_init(&m, 1, 0);
  carp_vm_load(&m, code, sizeof(code)/sizeof(*code));
  carp_value ecode = carp_vm_run(&m);
  carp_vm_cleanup(&m);
  return ecode;
}
