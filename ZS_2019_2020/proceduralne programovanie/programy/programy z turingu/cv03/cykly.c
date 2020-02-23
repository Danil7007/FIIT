#include <stdio.h>

int main () {
   int a, i ;
   nacitanie:
   printf ("Zadaj cislo 1-10 : ") ;
   scanf ("%d", &a) ;
   if ((a > 10) || (a < 1)) {
       printf ("Nespravna hodnota vstupu\n") ;
       goto nacitanie;
   }
   for (i = 1; i <= 2*a; i++) {
       printf ("Veta %d\n", i) ;
   }

    return 0;
}