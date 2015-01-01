#include <stdlib.h>
#include <inttypes.h>
#include <assert.h>

#include "registers.h"

char carp_reverse_reg[][5] = {
  "r0",
  "r1",
  "r2",
  "r3",
  "r4",
  "r5",
  "r6",
  "r7",
  "r8",
  "r9",
  "ax",
  "bx",
  "cx",
  "dx",
  "rx",
  "ip",
  "sp",
  "fp",
  "gbg",
  "run",
  "ext",
  "undef",
};

/*
  Returns a pointer to a register.
*/
carp_value *carp_reg_get (carp_value regs[], carp_reg reg) {
  assert(regs != NULL);

  if (reg >= CARP_NUM_REGS)
    return NULL;

  return &regs[reg];
}

/*
  Set the value in a given register. Fails if register is outside bounds.
*/
carp_bool carp_reg_set (carp_value regs[], carp_reg reg, carp_value value) {
  assert(regs != NULL);

  carp_value *res = carp_reg_get(regs, reg);
  if (res == NULL)
    return 1;

  *res = value;
  return 0;
}

/*
  Adds a value to a register.
*/
carp_bool carp_reg_add (carp_value regs[], carp_reg reg, carp_value value) {
  assert(regs != NULL);

  carp_value *res = carp_reg_get(regs, reg);
  if (res == NULL)
    return 1;

  *res += value;
  return 0;
}

/*
  Subtracts a value from a register.
*/
carp_bool carp_reg_sub (carp_value regs[], carp_reg reg, carp_value value) {
  assert(regs != NULL);

  carp_value *res = carp_reg_get(regs, reg);
  if (res == NULL)
    return 1;

  *res -= value;
  return 0;
}

/*
  Increments a register.
*/
carp_bool carp_reg_inc (carp_value regs[], carp_reg reg) {
  assert(regs != NULL);

  assert(regs != NULL);

  carp_value *res = carp_reg_get(regs, reg);
  if (res == NULL)
    return 1;

  carp_reg_add(regs, reg, 1);
  return 0;
}

/*
  Decrements a register.
*/
carp_bool carp_reg_dec (carp_value regs[], carp_reg reg) {
  assert(regs != NULL);

  assert(regs != NULL);

  carp_value *res = carp_reg_get(regs, reg);
  if (res == NULL)
    return 1;

  carp_reg_sub(regs, reg, 1);
  return 0;
}

void carp_reg_print (carp_value regs[], FILE *fp) {
  assert(regs != NULL);

  if (fp == NULL)
    fp = stdout;

  fprintf(fp, "{\n");

  for (int i = 0; i < CARP_NUM_REGS; i++)
    fprintf(fp, "%s: %" PRId64 ",\n", carp_reverse_reg[i], regs[i]);

  fprintf(fp, "}\n");
}

/*
  Initialize all the registers to value 0.
*/
void carp_reg_init (carp_value regs[]) {
  assert(regs != NULL);

  for (int i = 0; i < CARP_NUM_REGS; i++)
    carp_reg_set(regs, i, 0);
}
