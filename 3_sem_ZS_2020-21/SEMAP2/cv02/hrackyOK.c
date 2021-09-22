// uloha2-1.c -- Emma Macháčová, 24.9.2020 15:54
/* Jakubko ma veľmi rád plyšové zvieratka: tigre, drakov aj mackov. Už ich má celkom dosť a chcel by v nich mať poriadok. Kúpil si pre ne drevenú poličku, no na poličke chce mať len tie, s ktorými sa skutočne aj hráva.

Zo začiatku teda nechá poličku prázdnu a zvieratká bude na poličku umiestnovať tak, že keď sa so zvieratkom dohrá, umiestni ho na ľavý okraj poličky. Jakubko sa môže hrať aj so zvieratkami, ktoré už sú na poličke, vtedy zvieratko z poličky vyberie a po dohraní ho dá taktiež na začiatok poličky.

Na vstupe je zadané kladné celé číslo N, ktorú určuje koľko krát sa Jakubko hral. Nasleduje N čisel identifikujúcich jednotlivé zvieratká, s ktorými sa v danom momente hral. Vypište obsah poličky po tom, ako sa Jakubko dohrá s posledným zvieratkom.

Ukážka vstupu:
4
3 2 1 3
Výstup pre ukážkový vstup:
3 1 2
*/

#include <stdio.h>
#include <stdlib.h>

int main() {
  int pocet, i, max=-100, pomocna;
  int* pole;
  int* pole2;

  scanf ("%d", &pocet);
  pole = (int*) calloc(pocet, sizeof(int));

  //printf ("pole: ");
  for (i=0; i<pocet; i++) {
    scanf ("%d", &pole[i]);
    //printf ("%d ", pole[i]);
    if (pole[i] > max) {
      max = pole[i];
    }
  }
  //printf ("\n");
  //printf ("max: %d\nprvkov: %d\n", max, pocet);

  pole2 = (int*) calloc(max, sizeof(int));

  for (i=pocet-1; i >=0; i--) {
    pomocna = pole[i];
    //printf ("%d %d %d\n", pole[i], pomocna, pole2[pomocna]);
    if (pole2[pomocna] == 0) {
      printf ("%d ", pole[i]);
      pole2[pomocna]++;
    }
  }

  return 0;
}