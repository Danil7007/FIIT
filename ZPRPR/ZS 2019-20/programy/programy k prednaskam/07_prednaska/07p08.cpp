// vypocet obvodu a obsahu kruhu: vratenie hodnoty cez argumenty
#include <stdio.h>

#define PI 3.14

void kruh(int r, float *o, float *s)
{
   *o = 2 * PI * r;
   *s = PI * r*r;
}

int main() 
{
   int polomer;
   float obvod, obsah;

   printf("Zadaj polomer kruhu: ");
   scanf("%d", &polomer);

   kruh(polomer, &obvod, &obsah);
   printf("obvod: %.2f, obsah: %.2f\n", obvod, obsah);
   return 0;
}

