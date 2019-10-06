#include <stdio.h>
// najdenie maxima z 3 cisel
int main() 
{
   double x, y, z, max;

   printf("Zadaj tri realne cisla: ");
   scanf("%lf %lf %lf", &x, &y, &z);

   if (x > y) {
      if (x > z)
         max = x;
      else
         max = z;
   }
   else {
      if (y > z)
         max = y;
      else
         max = z;
   }

   printf("Najvacsie cislo je %f \n", max);
   return 0;
}

