#ifndef CARP_REGISTERS_H
#define CARP_REGISTERS_H

#include <stdio.h>

#include "lib/types.h"

// make register numbers easier on the eyes
typedef enum {
  CARP_REG_UNDEF = -1,

  // regs 0 through 9 for general use
  CARP_R0 ,
  CARP_R1 ,
  CARP_R2 ,
  CARP_R3 ,
  CARP_R4 ,
  CARP_R5 ,
  CARP_R6 ,
  CARP_R7 ,
  CARP_R8 ,
  CARP_R9 ,

  // regs used for cmp, et al... possibly
  CARP_AX  ,
  CARP_BX  ,
  CARP_CX  ,
  CARP_DX  ,
  CARP_RX  , // <- remainder

  // instruction pointer
  CARP_IP  ,

  // stack pointer
  CARP_SP  ,

  // frame pointer
  CARP_FP  ,

  // garbage reg for pop
  CARP_GBG  ,

  // is machine running?
  CARP_RUN  ,

  // exit code
  CARP_EXT  ,

  CARP_NUM_REGS,
} carp_reg;

extern char carp_reverse_reg[][5];

carp_value *carp_reg_get (carp_value [], carp_reg);
carp_bool carp_reg_set (carp_value [], carp_reg, carp_value);
carp_bool carp_reg_add (carp_value [], carp_reg, carp_value);
carp_bool carp_reg_sub (carp_value [], carp_reg, carp_value);
carp_bool carp_reg_inc (carp_value [], carp_reg);
carp_bool carp_reg_dec (carp_value [], carp_reg);
void carp_reg_print (carp_value [], FILE *);
void carp_reg_init(carp_value []);

#endif
