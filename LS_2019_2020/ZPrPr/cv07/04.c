// uloha7-4.c -- Emma Macháčová, 31.3.2020 16:49

/*

Uvažujte záznamy cestovnej kancelárie o predaných zájazdoch, kde sa uchovávajú položky: identifikačné číslo záznamu, meno zákazníka, názov destinácie, rok nástupu na pobyt a dĺžku pobytu v dňoch. Nepredpokladajte prácu s reťazcami dlhšími ako 100 znakov.

Definujte typ ZAJAZD ako štruktúru pre záznamy o predaných zájazdoch.
Definujte statické pole záznamov o zájazdoch zajazdy s najviac 100 záznamami.
Napíšte funkciu nacitaj, ktorá načíta záznamy, pokým nie je zadané záporné identifikačné číslo. Každá položka je na vstupe oddelená znakom konca riadku. Ošetrite možnosť presiahnutia dĺžky poľa. Zvoľte vhodné argumenty tak, aby ste vo funkcii nevyužívali žiadne globálne premenné.
Napíšte funkciu vypis, ktorá vypíše všetky záznamy, každý záznam v jednom riadku, pričom položky sú v riadku oddelené vždy jednou medzerou. Posledný riadok výstupu je nasledovaný znakom konca riadku. Zvoľte vhodné argumenty tak, aby ste vo funkcii nevyužívali žiadne globálne premenné.
Napíšte funkciu najnovsie, ktorá bude pracovať s poľom záznamov. Vypíše najväčšiu dĺžku zájazdov z posledného roka, pre ktorý boli zájazdy predané, a počet všetkých zájazdov z posledného roka. Posledný rok, pre ktorý boli zájazdy predané, je potrebné zistiť, nie je to nutne rok 2020. Výpis predstavuje jeden riadok ukončený znakom konca riadku a obsahujúci 2 celé čísla oddelené jednou medzerou. Zvoľte vhodné argumenty tak, aby ste vo funkcii nevyužívali žiadne globálne premenné.
Napíšte program, v ktorom použijete definície a funkcie podľa predchádzajúcich bodov. Program pomocou funkcií najprv načíta záznamy, vypíše záznamy a nakoniec vypíše najväčšiu dĺžku zájazdov z posledného roka, pre ktorý boli zájazdy predané, a počet všetkých zájazdov z posledného roka.
Ukážka vstupu:
1
Lojzo
Rim
2012
7
2
Ferko
Madeira
2010
12
3
Anicka
Kreta
2012
10
-1
Výstup pre ukážkový vstup:
1 Lojzo Rim 2012 7
2 Ferko Madeira 2010 12
3 Anicka Kreta 2012 10
10 2

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int id;
  char meno[30];
  char dest[30];
  int rok;
  int trvanie;
} ZAJAZD;

void nacitaj(ZAJAZD zazn[]){
  int n=0;
  while (n < 100 && scanf("%d", &zazn[n].id) != -1){
    scanf("%s", zazn[n].meno);
    scanf("%s", zazn[n].dest);
    scanf("%d", &zazn[n].rok);
    scanf("%d", &zazn[n].trvanie);
    n++;
  }
}

void vypis (ZAJAZD zazn[]){
  int n=0;
  while (n < 100 && zazn[n].id != -1){
    printf("%d %s %s %d %d\n", zazn[n].id, zazn[n].meno, zazn[n].dest, zazn[n].rok, zazn[n].trvanie);
    n++;
  }
}

void najnovsie (ZAJAZD zazn[]){
  int najdlhsi=0, pocet=0, maxRok=0, n=0;
  while (n < 100 && zazn[n].id != -1){
    if (zazn[n].rok > maxRok){
      maxRok = zazn[n].rok;
    }
    n++;
  }
  n=0;
  while (n < 100 && zazn[n].id != -1){
    if (zazn[n].rok == maxRok){
      pocet++;
      if (zazn[n].trvanie > najdlhsi){
        najdlhsi = zazn[n].trvanie;
      }
    }
    n++;
  }
  printf("%d %d\n", najdlhsi, pocet);
}

int main() {
  ZAJAZD zazn[100];

  nacitaj(zazn);
  vypis (zazn);
  najnovsie(zazn);

  return 0;
}