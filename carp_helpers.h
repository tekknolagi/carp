#ifndef CARP_INSTRUCTION_HELPERS_H
#define CARP_INSTRUCTION_HELPERS_H

/*
 * structure of a word (16 bits):
 * 
 * 4 for instr name
 * 4 for arg1
 * 4 for arg2
 * 4 for arg3
 */

definstr (NEXT);
void carp_eval (carp_machine_state*);
carp_instruction carp_encode (int, long long, long long, long long);
void carp_decode (carp_instruction*, carp_machine_state*);
void carp_init_vm (carp_machine_state*);
void carp_vm_do (carp_instruction[]);

#endif
