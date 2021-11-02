/*
   This simple application demonstrates standard text input and output[1]
   handling in a C application. Direct user interaction with the application can
   be done using a terminal[2] that provides the appropriate command line
   interface.

   Compile:
   gcc 1_echo.c -o 1_echo

   Use:
   ./1_echo arg1 arg2 - This will print out the passed arguments into standard
   error output and wait for user input. Any entered lines will be duplicated on
   the output stream. Once user closes the stream (CTRL+D) the EXIT message will
   be printed out on the standard error output.
   ./1_echo > file.txt - This will only print out the arguments and EXIT message
   as the standart text output is forwarded into a file. Any lines entered will
   be stored in file.txt until the stream ends (CTRL+D).

   Links:
   [1] https://en.wikipedia.org/wiki/Stdout
   [2] https://en.wikipedia.org/wiki/Text_terminal
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  int i;
  char c;
  
  // Print out all arguments passed to the application on the commandline
  for (i = 0; i < argc; i++) {
    fprintf(stderr, "Argument[%d]: %s\n", i, argv[i]);
  }

  // Copy any input character until the stream is closed
  while ((c = getchar()) != EOF) {
    putchar(c);
    fflush(stdout);
  }

  // Use the standard error output to print EXIT
  fprintf(stderr, "EXIT\n");
  return EXIT_SUCCESS;
}
