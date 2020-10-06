/*
Napíšte algoritmus, ktorý nájde K-te (1 <= K <= 100 000) prvočíslo v poradí od najmenších (pozn. prvé je 2).

Štandardný vstup obsahuje niekoľko riadkov, na každom z nich bude jedno číslo K. Pre každý riadok na vstupe vypíšte na štandardný výstup práve jedno číslo -- K-te prvočíslo.

Ukážka vstupu:
1
2
3
4
10
Výstup pre ukážkový vstup:

    
2
3
5
7
29*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void eratosten (int *cisla, int *prvocisla, int max) {
  int i, j;
  int indexPrvocisla = 0;
  
  for (i = 2; i < max; i++) { // nacitanie celych cisiel
    cisla[i] = i;
  }

  for (i=2; (i*i) < max; i++) { // eratostenovo sito
    if (cisla[i]) {
      for (j=2; j < max; j++) {
        if (cisla[i] * j > max) {
          break;
        }
        else {
          cisla[cisla[i] * j] = 0;
        }
      }
    }
  }

  for (i=0; i < max; i++) { // prepis do zvlast pola
    if (cisla[i]) {
      prvocisla[indexPrvocisla] = cisla[i];
      indexPrvocisla++;
    }
  }

  free(cisla);
  return;
}


int main () {
  int *cisla;
  int *prvocisla;
  int max = 1300000, i;

  cisla = (int*)calloc(max, sizeof(int));
  prvocisla = (int*)calloc(110000, sizeof(int));

  eratosten (cisla, prvocisla, max);

  while (scanf ("%d", &i) > 0) { // vypis
    printf ("%d\n", prvocisla[i-1]);
  }

  free(prvocisla);
  return 0;
}