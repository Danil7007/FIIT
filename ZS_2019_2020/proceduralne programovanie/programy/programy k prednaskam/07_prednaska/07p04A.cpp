// pouzitie referencneho a dereferencneho operatora - co vypise program?
#include <stdio.h>

int main() 
{
   int i = 100; 
   i = *&*&*&*&i;
   printf("hodnota i je %d\n", i);       
   return (0); 
} 

