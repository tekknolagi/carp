#ifndef CARP_INSTRUCTIONS_H
#define CARP_INSTRUCTIONS_H

#define CARP_I(x) CARP_INSTR_##x

// make instruction numbers easier on the eyes
typedef enum {
  CARP_I(HALT) ,
  CARP_I(NOP)  ,
  CARP_I(LOAD) ,
  CARP_I(GLOAD),
  CARP_I(MOV)  ,
  CARP_I(ADD)  ,
  CARP_I(SUB)  ,
  CARP_I(MUL)  ,
  CARP_I(MOD)  ,
  CARP_I(NOT)  ,
  CARP_I(XOR)  ,
  CARP_I(OR)   ,
  CARP_I(AND)  ,
  CARP_I(INCR) ,
  CARP_I(DECR) ,
  CARP_I(INC)  ,
  CARP_I(DEC)  ,
  CARP_I(PUSHR),
  CARP_I(PUSH) ,
  CARP_I(POP)  ,
  CARP_I(CMP)  ,
  CARP_I(LT)   ,
  CARP_I(GT)   ,
  CARP_I(JZ)   ,
  CARP_I(RJZ)  ,
  CARP_I(JNZ)  ,
  CARP_I(RJNZ) ,
  CARP_I(JMP)  ,
  CARP_I(RJMP) ,
  CARP_I(DBS)  ,
  CARP_I(DBG)  ,
  CARP_I(CALL) ,
  CARP_I(RET)  ,
  CARP_I(PREG) ,
  CARP_I(PTOP) ,

  CARP_NUM_INSTRS,
} carp_instr;

static char carp_reverse_instr[][6] = {
  "halt","nop","load","gload","mov","add","sub","mul","mod","not","xor","or",
  "amd","incr","decr","inc","dec","pushr","push","pop","cmp","lt","gt","jz",
  "rjz","jnz","rjnz","jmp","rjmp","dbs","dbg","call","ret","preg","ptop","undef"
};

#define CARP_BINOP(NAME, F) CARP_IDEF (NAME) { \
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
