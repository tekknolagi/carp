#ifndef CARP_REGISTERS_H
#define CARP_REGISTERS_H

// make register numbers easier on the eyes
typedef enum {
  // regs 0 through 9 for general use
  CARP_REG0 ,
  CARP_REG1 ,
  CARP_REG2 ,
  CARP_REG3 ,
  CARP_REG4 ,
  CARP_REG5 ,
  CARP_REG6 ,
  CARP_REG7 ,
  CARP_REG8 ,
  CARP_REG9 ,

  // regs used for cmp, et al
  CARP_EAX  ,
  CARP_EBX  ,
  CARP_ECX  ,
  CARP_EDX  ,
  CARP_ERX  , // <- remainder

  // instruction pointer
  CARP_EIP  ,

  // stack pointer
  CARP_ESP  ,

  // frame pointer
  CARP_EFP  ,

  // garbage reg for pop
  CARP_GBG  ,

  CARP_NUM_REGS,
} carp_reg;

static char carp_reverse_reg[][5] = {
  "reg0","reg1","reg2","reg3","reg4","reg5","reg6","reg7","reg8","reg9",
  "eax","ebx","ecx","edx","erx",
  "eip","esp","efp","gbg","undef"
};

#endif
