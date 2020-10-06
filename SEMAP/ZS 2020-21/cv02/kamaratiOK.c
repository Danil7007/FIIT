// uloha2-2.c -- Emma Macháčová, 24.9.2020 18:05
/* Napíšte program, ktorý zo vstupu načíta neznámy počet mien kamarátov, a následne načíta neznámy počet čísel. Pre každé číslo na vstupe vypíše meno kamaráta na príslušnom mieste v usporiadanom poradí podľa abecedy (lexikograficky). Ak sa kamarát s požadovaným číslom vo vstupe nenachádza vypíšte správu Vstup neobsahuje prvok X, kde X je požadované číslo.

Štandardný vstup obsahuje niekoľko riadkov. Najskôr budú v riadkoch mená, každé meno sa skladá so znakov anglickej abecedy, a može sa skladať z viacerých slov. Po týchto menách budú nasledovať na vstupe čísla, pričom na jednom riadku može byť jedno alebo aj viac čísel. Číslo predstavuje poradie kamaráta v usporiadanom poradí, číslovanie abecedne najmenší od 1.

Pomôcka: Načítavajte po riadkoch mená, a v prípade, že natrafíte na čísla, tak spracujte čísla podľa požiadaviek. Keďže vopred nevieme koľko mien bude na vstupe, použite na načítanie spájaný zoznam.
Ukážka vstupu:
Janko
Marienka Pekna
Adam Mily
 2  1   100
3
Výstup pre ukážkový vstup:
Janko
Adam Mily
Vstup neobsahuje prvok 100
Marienka Pekna
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct clovek {
	char meno[100];
  int poradie;
	struct clovek* dalsi;
} CLOVEK;

int main () {
  CLOVEK* head = NULL;
  CLOVEK* predchadzajuci = NULL;

  int i, x, y, pocetLudi=0;
  char meno[100];

  // clovek ---------------------------------------------------
  while (scanf ("%d", &i) <= 0) {
    fgets (meno, 100, stdin);
    //printf ("%s", meno);
    CLOVEK* temp = malloc(sizeof(struct clovek));
      temp -> dalsi = NULL;
      strcpy (temp->meno,meno);
      pocetLudi++;
      if (head == NULL) {
        head = temp;
        predchadzajuci = temp;
      }
      else {
        predchadzajuci->dalsi = temp;
        predchadzajuci = temp;
      }
  }

  // cislo --------------------------------------------------
  //printf ("%d ",i);
  int cisla[1000], pocet=1, index=0;
  cisla[index] = i; // priradenie cisla

  while (scanf ("%d", &i) > 0) {
    //printf ("%d ",i);
    pocet++;
    index++;
    // realokovanie?
    cisla[index] = i;
  }

  for (i=0; i < pocet; i++) {
    //printf ("%d\n", cisla[i]);
  }

  // pole na zoradenie ---------------------------------------------------------------
  CLOVEK* pole = (struct clovek*)calloc(pocetLudi+1, sizeof(struct clovek));
  CLOVEK* prechadzaj = head;

  //printf ("%d\n", index);

  for (x=0; x < pocetLudi; x++) { // kopirovanie
    strcpy (pole[x].meno, prechadzaj->meno);
    //printf ("%s", pole[i].meno);
    prechadzaj = prechadzaj->dalsi;
  }

  for (x = 0; x < pocetLudi; x++) { // zoradenie
    for (y = x + 1; y < pocetLudi; y++) {
      
      if ((strcmp(pole[x].meno, pole[y].meno) > 0)) {
        pole[pocetLudi+1] = pole[x];
        pole[x] = pole[y];
        pole[y] = pole[pocetLudi+1];
      }
    }
  }

  prechadzaj = head;
  for (x=0; x < pocetLudi; x++) { // pridanie poradia
    pole[x].poradie = x+1;
    prechadzaj = prechadzaj->dalsi;
  }

  int najdene=0;

  for (i=0; i <= index; i++) {
    prechadzaj = head;
    najdene = 0;
    for (x=0; x < pocetLudi; x++) { // vypis
      //printf ("%d\n", cisla[i]);
       if (pole[x].poradie == cisla[i]) {
         //printf ("%d = %d %s", cisla[i], pole[x].poradie, pole[x].meno);
         najdene = 1;
         break;
       }
      prechadzaj = prechadzaj->dalsi;
    }
    if (najdene == 1) {
      printf ("%s", pole[x].meno);
    }
    else {
      printf ("Vstup neobsahuje prvok %d\n", cisla[i]);
    }
  }

  return 0;
}