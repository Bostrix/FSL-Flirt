// globalvariables.h

extern int globalopts;
extern int verbose;
extern int help;
extern void print_usage(int argc, char **argv);
extern void parse_command_line(int argc, char **argv);
// Declare other global variables and functions as needed
#ifndef GLOBAL_VARIABLES_H
#define GLOBAL_VARIABLES_H

#include "globaloptions.h"

extern globaloptions globalopts; // Assuming globaloptions is the class name

// Other declarations...

#endif

