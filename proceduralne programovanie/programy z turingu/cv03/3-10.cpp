// Napíšte program, ktorý vypíše počet dní v mesiaci, pričom budete uvažovať
// nepriestupný rok. Vstupom je celé číslo m určujúce mesiac v roku. Výstupom je
// správa Mesiac cislo m ma x dni, kde m je načítané poradové číslo mesiaca
// a x je počet dní v tomto mesiaci. Ak m nie je platné poradové číslo mesiaca,
// program vypíše správu Neplatne cislo mesiaca. Správa na výstupe je
// ukončená znakom konca riadku.
// Ukážkový vstup:
// 5
// Ukážkový výstup:
// Mesiac cislo 5 ma 31 dni


#include <stdio.h>

int main () {

    float w, h, i, bmi ;
    printf ("Zadaj vysku(cm) a hmotnost(kg):\n") ;
    scanf ("%f %f", &h, &w) ;

    printf ("Na zaklade tvojej vysky %.1f a vahy %.1f je ", h, w) ;
    h = h/100 ;
    i = h*h ;
    bmi = w/i ;
    printf ("\ntvoje BMI: %.3f\n", bmi) ;

    if (bmi <= 18.5) {
        printf ("\nMas podvahu") ;
    }

    if ((18.5 < bmi) && (bmi < 25)) {
        printf ("\nMas normalnu vahu") ;
    }

    if ((25 <= bmi) && (bmi < 30)) {
        printf ("\nMas nadvahu") ;
    }

    if (bmi >= 30) {
        printf ("\nSi obezny") ;
    }

    return 0 ;
}