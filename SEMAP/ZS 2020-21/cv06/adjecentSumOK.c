// uloha6-1.c -- Emma Macháčová, 21.10.2020 14:24
/*
Farmár nedávno kúpil novú stodolu. V stodole je predinštalovaných N prístrojov na dojenie kráv. Prístroje sú očíslované postupne číslami 1, 2, ..., N, pričom i-ty prístroj je schopný vydojiť M_i litrov mlieka za deň. Naneštastie, prístroje sú tak blízko seba, že ak dojíme kravu v i-tom prístroji, tak dva jeho susedné prístroje (i-1 a i+1) nemôžu byť používané súčasne. Prvý a posledný prístroj majú samozrejme len jeden susedný prístroj. Farmár teraz rozmýšľa, ktoré prístroje použije na dojenie kráv tak, aby maximalizoval množstvo mlieka, ktoré môže vydojiť za jeden deň.

Špecifikácia vstupu: Na vstupe je opísaných niekoľko stodolí, čítajte do konca vstupu. Pre každú stodolu je dané prirodzené číslo N (najviac 10 000), a N prirodzených čísel M_i (každé najviac 100 000), kde M_i je množstvo mlieka, ktoré vydojí i-ty prístroj za jeden deň.

Špecifikácia výstupu: Pre každú stodolu na vstupe vypíšte jedno číslo -- koľko najviac môže v stodole farmár vydojiť mlieka za deň.

Ukážka vstupu:
5
1 2 3 4 5
5
1 5 3 4 5
Výstup pre ukážkový vstup:
9
10
*/

#include <stdio.h>
#include <stdlib.h>


int FindMaxSum(int arr[], int n) { 
  int incl = arr[0]; 
  int excl = 0; 
  int excl_new; 
  int i; 
  
  for (i = 1; i < n; i++) { 
     /* aktualne maximum bez i */
     excl_new = (incl > excl)? incl: excl; 
  
     /* aktualne maximum aj s i */
     incl = excl + arr[i]; 
     excl = excl_new; 
  } 
  
   /* vacsi z incl alebo excl */
   return ((incl > excl)? incl : excl); 
} 
  

int main() {
  int n, scan, i;
  int* arr;

  while (scanf ("%d", &n) > 0) {
    arr = (int*)calloc(n, sizeof(int));

    for (i=0; i<n; i++) {
      scanf ("%d", &scan);
      arr[i] = scan;
    }

    //printf ("%d %d\n", arr[0], arr[4]);

    printf("%d \n", FindMaxSum(arr, n)); 
  }

  return 0; 
}