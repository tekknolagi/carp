#ifndef CARP_BYTECODE_H
#define CARP_BYTECODE_H

#define CARP_B(x) CARP_BYTECODE_##x

typedef enum {
  CARP_B(OK),
  CARP_B(NOFILE),
  CARP_B(NOBUF),
  CARP_B(NOSPACE),
  CARP_B(EOF),

  CARP_NUM_BYTECODE_ECODES
} carp_bytecode_ecode;

#endif
