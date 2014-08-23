#ifndef CARP_INSTRUCTIONS_H
#define CARP_INSTRUCTIONS_H

#define CARP_I(x) CARP_INSTR_##x

// make instruction numbers easier on the eyes
typedef enum {
  CARP_I(UNDEF) = -1,

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
  CARP_I(PVARS),

  CARP_NUM_INSTRS,
} carp_instr;

static char carp_reverse_instr[][6] = {
  "halt","nop","load","gload","mov","add","sub","mul","mod","not","xor","or",
  "amd","incr","decr","inc","dec","pushr","push","pop","cmp","lt","gt","jz",
  "rjz","jnz","rjnz","jmp","rjmp","dbs","dbg","call","ret","preg","ptop","pvars",
  "undef",
};

#endif
