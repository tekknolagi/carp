#include <getopt.h>

#include "machine.h"

#define CARP_VERSION 0.3

static void carp_print_version ();
static void carp_print_license ();
static void carp_print_warranty ();
static void carp_print_conditions ();
static void carp_print_help ();

/*
  Main Carp interpreter.
*/
int main (int argc, char **argv) {
  static struct option long_options[] = {
    {"version", 0, 0, 'v'},
    {"license", 0, 0, 'l'},
    {"warranty", 0, 0, 'w'},
    {"conditions", 0, 0, 'c'},
    {"file", 1, 0, 'f'},
    {"help", 0, 0, 'h'},
    {NULL, 0, NULL, 0},
  };

  int c;
  int option_index = 0;
  while ((c = getopt_long(argc, argv, "vlwcf:h", long_options, &option_index)) != -1) {
    switch (c) {
    case 0:
      printf("option %s", long_options[option_index].name);

      if (optarg) {
        printf(" with arg %s", optarg);
      }

      putchar('\n');
      break;

    case 'v':
      // version
      carp_print_version();
      break;

    case 'l':
      // license
      carp_print_license();
      break;

    case 'w':
      // warranty
      carp_print_warranty();
      break;

    case 'c':
      // conditions
      carp_print_conditions();
      break;

    case 'f':
      // file
      carp_run_program(optarg);
      break;

    case 'h':
      // help
      carp_print_help();
      break;

    default:
      puts("For usage, run `carp -h' or `carp --help'.");
      break;
    }
  }

  return EXIT_SUCCESS;
}

/*
  Print Carp software version.
*/
void carp_print_version () {
  printf("carp %1.1f\n", CARP_VERSION);
}

/*
  Print part of the license and directions to find full license.
 */
void carp_print_license () {
  puts("carp  Copyright (C) 2014  Maxwell Bernstein\n\
    This program comes with ABSOLUTELY NO WARRANTY; for details type `carp -w'.\n\
    This is free software, and you are welcome to redistribute it\n\
    under certain conditions; type `carp -c' for details.");
  puts("See LICENSE.txt or http://www.gnu.org/licenses/gpl-3.0.txt");
}

/*
  Print warranty.
*/
void carp_print_warranty () {
  puts("THERE IS NO WARRANTY FOR THE PROGRAM, TO THE EXTENT PERMITTED BY APPLICABLE LAW. EXCEPT WHEN OTHERWISE STATED IN WRITING THE COPYRIGHT HOLDERS AND/OR OTHER PARTIES PROVIDE THE PROGRAM “AS IS” WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE PROGRAM IS WITH YOU. SHOULD THE PROGRAM PROVE DEFECTIVE, YOU ASSUME THE COST OF ALL NECESSARY SERVICING, REPAIR OR CORRECTION.");
}

/*
  Print conditions.
*/
void carp_print_conditions () {
  puts("See LICENSE.txt or http://www.gnu.org/licenses/gpl-3.0.txt");
}

/*
  Print the help message.
*/
void carp_print_help () {
  puts("Usage:");
  puts("-v, --version\n\tsee version number");
  puts("-l, --license:\n\tsee licensing information");
  puts("-w, --warranty:\n\tsee warranty information");
  puts("-c, --conditions:\n\tsee licensing conditions");
  puts("-f, --file [filename]:\n\tinterpret [filename]. Argument not optional.");
  puts("-h, --help:\n\tget this message");
}
