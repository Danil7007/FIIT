/*Jakubko sa nudí na hodine programovania a tak si začal na papier čmárať binárne vyhľadávacie stromy. Zapačíli sa mu a chcel by zistiť koľko rôznych binárnych vyhľadávacích stromov existuje pre daný počet prvkov. Napíšte program, ktorý pre daný počet prvkov N zistí, koľko je rôznych binárnych vyhľadávacích stromov, ktoré možno z N rôznych prvkov zostrojiť.

Špecifikácia vstupu: Na vstupe je niekoľko čísel veľkosťou do 32. Čísla sú oddelené medzerou alebo novým riadkom.

Špecifikácia výstupu: Pre každé číslo i na vstupe vypíšte jedno číslo -- počet rôznych binárnych vyhľadávacích stromov, ktoré možno zostrojiť z i rôznych prvkov.

Ukážka vstupu:
1
2
3
Výstup pre ukážkový vstup:
1
2
5*/

#include <stdio.h>
#include <string.h>

long unsigned pole[35];

//catalanovo cislo
unsigned long int catalan(unsigned int n) {
   // zakladny case
   if (n <= 1) return 1;
   // catalan(n) == sum  catalan(i)*catalan(n-i-1)
   unsigned long int vysledok = 0;
   for (int i=0; i<n; i++) {
     if (pole[i] != 0 && pole[n-i-1] != 0) {
       vysledok += pole[i] * pole[n-i-1];
     }
     else {
      //vysledok += catalan(i)*catalan(n-i-1);
      pole[i] = catalan(i);
      pole[n-i-1] = catalan(n-i-1);
      vysledok += pole[i] * pole[n-i-1];
     }
     
   }
      
   pole[n] = vysledok;
   return vysledok;
}


int main() {
  int n;
  
  memset (pole, 0, 34);

  while (scanf ("%d", &n) > 0 ) {
    if (pole[n] != 0) {
      printf("%ld\n", pole[n]);
    }
    else {
      printf("%ld\n", catalan(n));
    } 
  }

  //printf("pre vstup 5: %ld, \n", pole[5]);

   return 0;
}