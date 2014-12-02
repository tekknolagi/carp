#ifndef CARP_INSTRUCTIONS_H
#define CARP_INSTRUCTIONS_H

#define CARP_I(x) CARP_INSTR_##x

// make instruction numbers easier on the eyes
typedef enum {
  CARP_I(UNDEF) = -1,

  CARP_I(HALT) ,
  CARP_I(NOP)  ,
  CARP_I(LOADR),
  CARP_I(LOAD) ,
  CARP_I(STORE),
  CARP_I(MOV)  ,
  CARP_I(ADD)  ,
  CARP_I(SUB)  ,
  CARP_I(MUL)  ,
  CARP_I(MOD)  ,
  CARP_I(SHR)  ,
  CARP_I(SHL)  ,
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
  CARP_I(CALL) ,
  CARP_I(RET)  ,
  CARP_I(PREG) ,
  CARP_I(PTOP) ,

  CARP_NUM_INSTRS,
} carp_instr;

extern char carp_reverse_instr[][6];

#endif
