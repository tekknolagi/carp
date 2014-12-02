#include "carp_machine.h"
#include <getopt.h>

#define CARP_VERSION 0.3

static void carp_print_version(void);
static void carp_print_license(void);
static void carp_print_warranty(void);
static void carp_print_conditions(void);
static void carp_print_help(void);

int main(int argc, char **argv) {
  static struct option long_options[] = {
    {"version",    0, 0, 'v'},
    {"license",    0, 0, 'l'},
    {"warranty",   0, 0, 'w'},
    {"conditions", 0, 0, 'c'},
    {"file",       1, 0, 'f'},
    {"help",       0, 0, 'h'},
    {NULL,         0, NULL, 0},
  };

  int c;
  int option_index = 0;

  while ((c = getopt_long(argc, argv, "vlwcf:h",
                          long_options, &option_index)) != -1) {
    switch (c) {
    case 0:
      printf("option %s", long_options[option_index].name);

      if (optarg) {
        printf(" with arg %s", optarg);
      }

      putchar('\n');
      break;
    case 'v':
      carp_print_version();
      break;
    case 'l':
      carp_print_license();
      break;
    case 'w':
      carp_print_warranty();
      break;
    case 'c':
      carp_print_conditions();
      break;
    case 'f':
      carp_run_program(optarg);
      break;
    case 'h':
      carp_print_help();
      break;
    default:
      puts("For usage, run `carp -h' or `carp --help'.");
      break;
    }
  }

  return EXIT_SUCCESS;
}

void carp_print_version() {
  printf("carp %1.1f\n", CARP_VERSION);
}

void carp_print_license() {
  puts("carp  Copyright (C) 2014  Maxwell Bernstein\n"
       "This program comes with ABSOLUTELY NO WARRANTY;\n"
       "for details, type `carp -w'.\n"
       "This is free software, and you are welcome to\n"
       "redistribute it under certain conditions;\n"
       "type `carp -c' for details.\n");
  carp_print_conditions();
}

void carp_print_warranty() {
  puts("THERE IS NO WARRANTY FOR THE PROGRAM, TO THE EXTENT PERMITTED\n"
       "BY APPLICABLE LAW. EXCEPT WHEN OTHERWISE STATED IN WRITING THE\n"
       "COPYRIGHT HOLDERS AND/OR OTHER PARTIES PROVIDE THE PROGRAM\n"
       "“AS IS” WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED,\n"
       "INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF\n"
       "MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. THE ENTIRE\n"
       "RISK AS TO THE QUALITY AND PERFORMANCE OF THE PROGRAM IS WITH YOU.\n"
       "SHOULD THE PROGRAM PROVE DEFECTIVE, YOU ASSUME THE COST OF ALL\n"
       "NECESSARY SERVICING, REPAIR OR CORRECTION.");
}

void carp_print_conditions() {
  puts("See LICENSE.txt or http://www.gnu.org/licenses/gpl-3.0.txt");
}

void carp_print_help() {
  puts("Usage:\n"
       "-v, --version\n\tsee version number\n"
       "-l, --license:\n\tsee licensing information\n"
       "-w, --warranty:\n\tsee warranty information\n"
       "-c, --conditions:\n\tsee licensing conditions\n"
       "-f, --file [filename]:\n"
       "\tinterpret [filename]. Argument not optional.\n"
       "-h, --help:\n\tget this message");
}
