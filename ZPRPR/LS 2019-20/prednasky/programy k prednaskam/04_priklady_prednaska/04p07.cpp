// argumenty programu (argumenty funkcie main())
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
  if(argc == 2 && !strcmp(argv[1], "-h"))	// ak prvy argument je rovny -h
    printf("help\n");		// vypise "help"
  else
    printf("program\n");	// vypise "program"
  return 0;
}

