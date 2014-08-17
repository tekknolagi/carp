#ifndef CARP_REGISTERS_H
#define CARP_REGISTERS_H

#include <stdlib.h>
#include <assert.h>

#include "lib/carp_types.h"

// make register numbers easier on the eyes
typedef enum {
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

  // regs used for cmp, et al
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

static char carp_reverse_reg[][5] = {
  "r0","r1","r2","r3","r4","r5","r6","r7","r8","r9",
  "ax","bx","cx","dx","rx",
  "ip","sp","fp","gbg","run","ext","undef"
};

carp_value *carp_reg_get (carp_value [], carp_reg);
carp_bool carp_reg_set (carp_value [], carp_reg, carp_value);
carp_bool carp_reg_add (carp_value [], carp_reg, carp_value);
carp_bool carp_reg_sub (carp_value [], carp_reg, carp_value);
carp_bool carp_reg_inc (carp_value [], carp_reg);
carp_bool carp_reg_dec (carp_value [], carp_reg);
void carp_reg_init(carp_value []);

#endif
