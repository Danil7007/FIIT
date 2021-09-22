// uloha3-1.c -- Emma Macháčová, 30.9.2020 12:38
/*Daná je vzostupne usporiadaná postupnosť čísel, napíšte funkciu, ktorá pre dané číslo X nájde jeho pozíciu v tejto postupnosti. Ak sa číslo X v postupnosti nenachádza, funckia vráti -1.

Naprogramujte funkciu v nasledovnom tvare:

// vrati index cisla x vo vzostupne usporiadanej postupnosti cisel. Vrati -1 ak sa x v postupnosti nenachadza.
int search(int cisla[], int n, int x)
{
  // ...
}
Príklad postupnosti:

    N = 3
    10 20 30
Hľadané prvky:

30
25
20
Výstup:

2
-1
1*/

#include <stdio.h>
#include <stdlib.h>

int search (int cisla[], int n, int x) {
  int start_index = 0;
  int end_index = n - 1;
  int element = x;
  int middle;

  while (start_index <= end_index){
    // vypocitanie stredu
    middle = start_index + (end_index - start_index ) / 2; 
    // ak sme nasli
    if (cisla[middle] == element)
      return middle;
    // ak mame hladat v pravej polke pola
    if (cisla[middle] < element)
      start_index = middle + 1;
    else
      end_index = middle - 1;
  }
  // ak sme nenasli
  return -1;
}



// ukazkovy test (spracovanie vstupu)
int main(void) {
  int *a, n, i;

  // nacitanie n cisel do pola a
  scanf("%d", &n);
  a = malloc(n * sizeof(int));
  for (i = 0; i < n; i++)
    scanf("%d", &a[i]);

  // nacitanie cisel do konca vstupu
  while (scanf("%d", &i) > 0)
    printf("%d\n", search(a, n, i));
  return 0;
}