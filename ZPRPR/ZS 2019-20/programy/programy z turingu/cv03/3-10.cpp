// Napíšte program, ktorý vypíše počet dní v mesiaci, pričom budete uvažovať
// nepriestupný rok. Vstupom je celé číslo m určujúce mesiac v roku. Výstupom je
// správa Mesiac cislo m ma x dni, kde m je načítané poradové číslo mesiaca
// a x je počet dní v tomto mesiaci. Ak m nie je platné poradové číslo mesiaca,
// program vypíše správu Neplatne cislo mesiaca. Správa na výstupe je
// ukončená znakom konca riadku.
// Ukážkový vstup:
// 5
// Ukážkový výstup:
// Mesiac cislo 5 ma 31 dni


#include <stdio.h>

int main () {

    int m ;

    printf ("Zadaj cislo mesiaca (1-12) : \n") ;
    scanf ("%d", &m) ;

    if (m == 1) {
        printf ("\nMesiac %d ma 31 dni", m) ;
    }

    if (m == 2) {
        printf ("\nMesiac %d ma 28 dni", m) ;
    }

    if (m == 3) {
        printf ("\nMesiac %d ma 31 dni", m) ;
    }

    if (m == 4) {
        printf ("\nMesiac %d ma 30 dni", m) ;
    }

    if (m == 5) {
        printf ("\nMesiac %d ma 31 dni", m) ;
    }

    if (m == 6) {
        printf ("\nMesiac %d ma 30 dni", m) ;
    }

    if (m == 7) {
        printf ("\nMesiac %d ma 31 dni", m) ;
    }

    if (m == 8) {
        printf ("\nMesiac %d ma 31 dni", m) ;
    }

    if (m == 9) {
        printf ("\nMesiac %d ma 30 dni", m) ;
    }

    if (m == 10) {
        printf ("\nMesiac %d ma 31 dni", m) ;
    }

    if (m == 11) {
        printf ("\nMesiac %d ma 30 dni", m) ;
    }

    if (m == 12) {
        printf ("\nMesiac %d ma 31 dni", m) ;
    }

    if (m < 12) {
        printf ("\nNeplatny mesiac") ;
    }

    if (m <= 0) {
        printf ("\nNeplatny mesiac") ;
    }

    return 0 ;
}