#ifndef CARP_INSTRUCTIONS_H
#define CARP_INSTRUCTIONS_H

#define ci(x) CARP_INSTR_##x

// make instruction numbers easier on the eyes
typedef enum {
  ci(HALT) ,
  ci(NOP)  ,
  ci(LOAD) ,
  ci(GLOAD),
  ci(MOV)  ,
  ci(ADD)  ,
  ci(SUB)  ,
  ci(MUL)  ,
  ci(MOD)  ,
  ci(REM)  ,
  ci(NOT)  ,
  ci(XOR)  ,
  ci(OR)   ,
  ci(AND)  ,
  ci(INCR) ,
  ci(DECR) ,
  ci(INC)  ,
  ci(DEC)  ,
  ci(PUSHR),
  ci(PUSH) ,
  ci(POP)  ,
  ci(CMP)  ,
  ci(JZ)   ,
  ci(RJZ)  ,
  ci(JNZ)  ,
  ci(RJNZ) ,
  ci(JMP)  ,
  ci(RJMP) ,
  ci(DBS)  ,
  ci(DBG)  ,
  ci(CALL) ,
  ci(RET)  ,
  ci(PREG) ,
  ci(PTOP) ,

  CARP_NUM_INSTRS,
} carp_instr;

static char carp_reverse_instr[][6] = {
  "halt","nop","load","gload","mov","add","sub","mul","mod","rem","not","xor","or",
  "amd","incr","decr","inc","dec","pushr","push","pop","cmp","jz","rjz","jnz",
  "rjnz","jmp","rjmp","dbs","dbg","call","ret","preg","ptop","undef"
};

#define CARP_BINOP(NAME, F) definstr (NAME) { \
  long long b, a; \
  if (carp_stack_pop(&m->stack, &b) == -1)\
    carp_vm_err(m, CARP_STACK_EMPTY);\
  if (carp_stack_pop(&m->stack, &a) == -1)\
    carp_vm_err(m, CARP_STACK_EMPTY);\
  carp_stack_push(&m->stack, a F b);}

#define CARP_SPOP(NAME) if (carp_stack_pop(&m->stack, &NAME) == -1) \
    carp_vm_err(m, CARP_STACK_EMPTY)

#define CARP_SPUSH(NAME) if (carp_stack_push(&m->stack, NAME) == -1) \
    carp_vm_err(m, CARP_STACK_NO_MEM)

#endif
