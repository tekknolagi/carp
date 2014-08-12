#ifndef TESTS_H
#define TESTS_H

#include "../src/carp.h"
#include "libtap/tap.h"

#define AC_RED     "\x1b[31m"
#define AC_GREEN   "\x1b[32m"
#define AC_YELLOW  "\x1b[33m"
#define AC_BLUE    "\x1b[34m"
#define AC_MAGENTA "\x1b[35m"
#define AC_CYAN    "\x1b[36m"
#define AC_RESET   "\x1b[0m"

#define AC_CLR(color, text) (AC_##color text AC_RESET)
#define AC_OK(text) AC_CLR(GREEN, text)
#define AC_BAD(text) AC_CLR(RED, text)

#endif
