/* C code produced by gperf version 3.0.3 */
/* Command-line: /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/gperf  */
/* Computed positions: -k'1-3' */

#if !((' ' == 32) && ('!' == 33) && ('"' == 34) && ('#' == 35) \
      && ('%' == 37) && ('&' == 38) && ('\'' == 39) && ('(' == 40) \
      && (')' == 41) && ('*' == 42) && ('+' == 43) && (',' == 44) \
      && ('-' == 45) && ('.' == 46) && ('/' == 47) && ('0' == 48) \
      && ('1' == 49) && ('2' == 50) && ('3' == 51) && ('4' == 52) \
      && ('5' == 53) && ('6' == 54) && ('7' == 55) && ('8' == 56) \
      && ('9' == 57) && (':' == 58) && (';' == 59) && ('<' == 60) \
      && ('=' == 61) && ('>' == 62) && ('?' == 63) && ('A' == 65) \
      && ('B' == 66) && ('C' == 67) && ('D' == 68) && ('E' == 69) \
      && ('F' == 70) && ('G' == 71) && ('H' == 72) && ('I' == 73) \
      && ('J' == 74) && ('K' == 75) && ('L' == 76) && ('M' == 77) \
      && ('N' == 78) && ('O' == 79) && ('P' == 80) && ('Q' == 81) \
      && ('R' == 82) && ('S' == 83) && ('T' == 84) && ('U' == 85) \
      && ('V' == 86) && ('W' == 87) && ('X' == 88) && ('Y' == 89) \
      && ('Z' == 90) && ('[' == 91) && ('\\' == 92) && (']' == 93) \
      && ('^' == 94) && ('_' == 95) && ('a' == 97) && ('b' == 98) \
      && ('c' == 99) && ('d' == 100) && ('e' == 101) && ('f' == 102) \
      && ('g' == 103) && ('h' == 104) && ('i' == 105) && ('j' == 106) \
      && ('k' == 107) && ('l' == 108) && ('m' == 109) && ('n' == 110) \
      && ('o' == 111) && ('p' == 112) && ('q' == 113) && ('r' == 114) \
      && ('s' == 115) && ('t' == 116) && ('u' == 117) && ('v' == 118) \
      && ('w' == 119) && ('x' == 120) && ('y' == 121) && ('z' == 122) \
      && ('{' == 123) && ('|' == 124) && ('}' == 125) && ('~' == 126))
/* The character set is not based on ISO-646.  */
error "gperf generated tables don't work with this execution character set. Please report a bug to <bug-gnu-gperf@gnu.org>."
#endif


#define TOTAL_KEYWORDS 36
#define MIN_WORD_LENGTH 2
#define MAX_WORD_LENGTH 5
#define MIN_HASH_VALUE 2
#define MAX_HASH_VALUE 83
/* maximum key range = 82, duplicates = 0 */

#include <string.h>
#include "instructions.h"

#ifdef __GNUC__
__inline
#else
#ifdef __cplusplus
inline
#endif
#endif
static unsigned int
hash (str, len)
     register const char *str;
     register unsigned int len;
{
  static unsigned char asso_values[] =
    {
      84, 84, 84, 84, 84, 84, 84, 84, 84, 84,
      84, 84, 84, 84, 84, 84, 84, 84, 84, 84,
      84, 84, 84, 84, 84, 84, 84, 84, 84, 84,
      84, 84, 84, 84, 84, 84, 84, 84, 84, 84,
      84, 84, 84, 84, 84, 84, 84, 84, 84, 84,
      84, 84, 84, 84, 84, 84, 84, 84, 84, 84,
      84, 84, 84, 84, 84, 84, 84, 84, 84, 84,
      84, 84, 84, 84, 84, 84, 84, 84, 84, 84,
      84, 84, 84, 84, 84, 84, 84, 84, 84, 84,
      84, 84, 84, 84, 84, 84, 84,  0, 30, 15,
      15, 15, 84, 10, 31, 55, 25, 84,  0, 20,
       0,  0,  5, 84,  5,  5,  0, 45, 55, 84,
      20, 84, 30, 84, 84, 84, 84, 84, 84, 84,
      84, 84, 84, 84, 84, 84, 84, 84, 84, 84,
      84, 84, 84, 84, 84, 84, 84, 84, 84, 84,
      84, 84, 84, 84, 84, 84, 84, 84, 84, 84,
      84, 84, 84, 84, 84, 84, 84, 84, 84, 84,
      84, 84, 84, 84, 84, 84, 84, 84, 84, 84,
      84, 84, 84, 84, 84, 84, 84, 84, 84, 84,
      84, 84, 84, 84, 84, 84, 84, 84, 84, 84,
      84, 84, 84, 84, 84, 84, 84, 84, 84, 84,
      84, 84, 84, 84, 84, 84, 84, 84, 84, 84,
      84, 84, 84, 84, 84, 84, 84, 84, 84, 84,
      84, 84, 84, 84, 84, 84, 84, 84, 84, 84,
      84, 84, 84, 84, 84, 84, 84, 84, 84, 84,
      84, 84, 84, 84, 84, 84
    };
  register int hval = (int)len;

  switch (hval)
    {
      default:
        hval += asso_values[(unsigned char)str[2]];
      /*FALLTHROUGH*/
      case 2:
        hval += asso_values[(unsigned char)str[1]];
      /*FALLTHROUGH*/
      case 1:
        hval += asso_values[(unsigned char)str[0]];
        break;
    }
  return hval;
}

carp_instr
in_instr_set (str)
     register const char *str;
{
  register unsigned int len = strlen(str);
  static const char * wordlist[] =
    {
      "", "", "lt",
      "not", "load", "loadr",
      "", "or", "nop",
      "ptop", "store", "",
      "gt", "pop", "",
      "", "", "",
      "and", "call", "",
      "", "", "ret",
      "", "", "",
      "", "xor", "preg",
      "", "", "",
      "add", "rjnz", "halt",
      "", "", "mod",
      "shl",
      "", "", "",
      "cmp", "shr",
      "", "", "",
      "dec", "decr",
      "", "", "",
      "jmp", "rjmp", "",
      "", "jz", "jnz",
      "push", "pushr", "",
      "", "rjz", "",
      "", "", "",
      "mul", "", "",
      "", "", "inc",
      "incr",
      "", "", "",
      "mov",
      "", "", "",
      "", "sub"
    };

  static const carp_instr instrs[] =
    {
      CARP_I(UNDEF), CARP_I(UNDEF), CARP_I(LT),
      CARP_I(NOT), CARP_I(LOAD), CARP_I(LOADR),
      CARP_I(UNDEF), CARP_I(OR), CARP_I(NOP),
      CARP_I(PTOP), CARP_I(STORE), CARP_I(UNDEF),
      CARP_I(GT), CARP_I(POP), CARP_I(UNDEF),
      CARP_I(UNDEF), CARP_I(UNDEF), CARP_I(UNDEF),
      CARP_I(AND), CARP_I(CALL), CARP_I(UNDEF),
      CARP_I(UNDEF), CARP_I(UNDEF), CARP_I(RET),
      CARP_I(UNDEF), CARP_I(UNDEF), CARP_I(UNDEF),
      CARP_I(UNDEF), CARP_I(XOR), CARP_I(PREG),
      CARP_I(UNDEF), CARP_I(UNDEF), CARP_I(UNDEF),
      CARP_I(ADD), CARP_I(RJNZ), CARP_I(HALT),
      CARP_I(UNDEF), CARP_I(UNDEF), CARP_I(MOD),
      CARP_I(SHL),
      CARP_I(UNDEF), CARP_I(UNDEF), CARP_I(UNDEF),
      CARP_I(CMP), CARP_I(SHR),
      CARP_I(UNDEF), CARP_I(UNDEF), CARP_I(UNDEF),
      CARP_I(DEC), CARP_I(DECR),
      CARP_I(UNDEF), CARP_I(UNDEF), CARP_I(UNDEF),
      CARP_I(JMP), CARP_I(RJMP), CARP_I(UNDEF),
      CARP_I(UNDEF), CARP_I(JZ), CARP_I(JNZ),
      CARP_I(PUSH), CARP_I(PUSHR), CARP_I(UNDEF),
      CARP_I(UNDEF), CARP_I(RJZ), CARP_I(UNDEF),
      CARP_I(UNDEF), CARP_I(UNDEF), CARP_I(UNDEF),
      CARP_I(MUL), CARP_I(UNDEF), CARP_I(UNDEF),
      CARP_I(UNDEF), CARP_I(UNDEF), CARP_I(INC),
      CARP_I(INCR),
      CARP_I(UNDEF), CARP_I(UNDEF), CARP_I(UNDEF),
      CARP_I(MOV),
      CARP_I(UNDEF), CARP_I(UNDEF), CARP_I(UNDEF),
      CARP_I(UNDEF), CARP_I(SUB)
    };

  if (len <= MAX_WORD_LENGTH && len >= MIN_WORD_LENGTH)
    {
      register int key = hash (str, len);

      if (key <= MAX_HASH_VALUE && key >= 0)
        {
          register const char *s = wordlist[key];

          if (*str == *s && !strcmp (str + 1, s + 1))
	    return instrs[key];
        }
    }
  return CARP_I(UNDEF);
}
