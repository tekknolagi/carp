#ifndef CARP_H
#define CARP_H

#include "carp_machine.h"

#define CARP_VERSION 0.1

typedef struct carp_option_s {
  short int version;
  short int license;
  short int warranty;
  short int conditions;
  char *file;
} carp_option;

void carp_print_version ();
void carp_print_license ();
void carp_print_warranty ();
void carp_print_conditions ();
void carp_run_program (char *);

#endif
