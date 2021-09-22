// uloha9-2.c -- Emma Macháčová, 11.11.2020 00:25
/*
Jakubkovi sa opäť podarilo nadviazať komunikáciu s mimozemskou civilizáciou Palindromiánov. Ako už isto vieme, každá ich správa je palindróm (reťazec znakov, ktorý sa spredu číta rovnako ako odzadu, napr. abba). Do správ sa primiešalo aj vysielanie iných civilizácií a preto by potreboval v zachytených signáloch nájsť najdlhšie úseky správ, ktoré sú palindrómom. Pomôžte Jakubkovi a napíšte program, ktorý pre každú zachytenú správu určí dĺžku najdlhšej súvislej podpostupnosti, ktorá je palindrómom.

Špecifikácia vstupu: Na vstupe je zadaných niekoľko správ, čítajte do konca vstupu. Každá správa je reťazec malých písmen anglickej abecedy dlhý najviac 50000 znakov.

Špecifikácia výstupu: Pre každú správu na vstupe vypíšte jedno číslo na samostatný riadok -- dĺžku najdlhšej súvislej podpostupnosti, ktorá je palindrómom. Konkrétne umiestnenie palindrómu nie je potrebné určovať.

Ukážka vstupu:
abecedazjedladeda
povedalanamedveda
abbabaabaabbaabab
Výstup pre ukážkový vstup:
5
3
10
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// funkcia na hladanie palindromovych substringov
void palindrom (char *slovo){
   // palindrom s dlzkou 0 neexistuje, 1 pismenko uz je palindrom
   int maxDlzka=1, indexy[2][50000], pocet=1;
   int s=0, i=0, n = strlen(slovo);

   // indexy palindromov
   // prve pismenko je palindrom dlzky 1
   indexy[0][0] = 0;
   indexy[1][0] = 0;

   // podmienka - ked je slovo nulovej dlzky
   if (n <= 0){
        printf("0\n");
        return;
   }

   // -------------------- moznost 1: ----------------------------------------------------- stred palindromu je pismenko

   //printf("%d %d, pocet %d dzlka %d\n", s, i, pocet, maxDlzka);
   for (s=1; s<n; s++){
        // kym sa nedostane mimo pola a ma zhodu
        for (i=0; ((s-i-1) >= 0) && ((s+i+1) < n) && (slovo[s-i-1] == slovo[s+i+1]); i++){
            // nerobi nic, iba inkrementuje i
        }

        // novy najdlhsi palindrom
        if (2*i+1 > maxDlzka){
            maxDlzka = 2*i+1;
            pocet = 1;
            // prepise uz zapisany palindrom, ak je ich zapisanych viac z predchadzajucej najvacsej dlzky
            // nevadi, lebo na to je ukladany pocet
            indexy[0][0] = (s-i);
            indexy[1][0] = (s+i);
        }
        // dalsi rovnako dlhy palindrom
        else if (2*i+1 == maxDlzka){
            pocet++;
            indexy[0][pocet-1] = (s-i);
            indexy[1][pocet-1] = (s+i);
        }
        //printf("1: %d %d, pocet %d dzlka %d\n", s, i, pocet, maxDlzka);
   }
   //printf("\n");

   // -------------------- moznost 2: ------------------------------------------ stred palindromu je medzi pismenkami

   for (s=1; s<n; s++){

       // ak sa nezhoduju stredove pismenka
       if (slovo[s-1] != slovo[s]){
           continue;
       }

        for (i=0; ((s-i-2) >= 0) && ((s+i+1) < n) && (slovo[s-i-2] == slovo[s+i+1]); i++){
            // inkrementovanie i
        }

        // novy najdlhsi palindrom
        if (2*i+2 > maxDlzka){
            maxDlzka = 2*i+2;
            pocet = 1;
            indexy[0][0] = (s-i-1);
            indexy[1][0] = (s+i);
        }
        // dalsi rovnako dlhy palindrom
        else if (2*i+2 == maxDlzka){
            pocet++;
            indexy[0][pocet-1] = (s-i-1);
            indexy[1][pocet-1] = (s+i);
        }
        //printf("2: %d %d, pocet %d dzlka %d\n", s, i, pocet, maxDlzka);
   }

   // vypis
   printf ("%d ", maxDlzka);
   // podla poctu
   for (i=0; i<pocet; i++){
       for (s = indexy[0][i]; s <= indexy[1][i]; s++){
           //printf("%c", slovo[s]);
       }
       printf(" ");
   }
   printf("\n");

   //printf("-------------------------------------------\n\n");
}

int main(){
    char slovo[50000];

    while (scanf("%s", slovo) > 0){
        palindrom(slovo);
    }

    return 0;
}