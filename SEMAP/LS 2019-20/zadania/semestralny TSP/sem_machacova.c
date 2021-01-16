#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// mapa = vstupna matica; navstivene hovori o tom, kde uz jakubko bol (0 albo 1);
// n = pocet domov; mincas je minimalny cas, ktory potrebuje k prechodu  
int mapa[20][20], navstivene[20], n, mincas = 2000000000;
// funkcie
int nacitaj();
void najdi_min(int dom, int cas);

// funkcia na nacitanie vstupu
int nacitaj() {
    int i, j; // indexy

    // nacitaj pocet miest - ak je co citat vrati na konci 1
    if (scanf("%d", &n) > 0) {

        // nacitaj maticu
        for (i = 0; i < n; i++) { // stlpce
            // riadky
            for (j = 0; j < n; j++) {
                scanf("%d", &mapa[i][j]);
            }
            navstivene[i] = 0; // vynulovanie pola - nikde este nebol
        }

        // kebyze si chcem nacitanu maticu vypisat
        /*
        for (i = 0; i < n; i++) {
            printf("\n\n");
            for (j = 0; j < n; j++)
                printf("\t%d", mapa[i][j]);
        }
        */
        return 1;
    }
    else {
        return 0; // ak uz nie je co nacitat
    }

}

// hladanie minimalneho casu
void najdi_min (int dom, int cas) {
    // sum sluzi na zistenie, ci sme boli vo vsetkych domoch
    int i, sum = 0;
    // nastavenie navstivenia domu
    navstivene[dom] = 1;
    // prichod -->

    // zistenie sum
    for (i = 0; i < n; i++) {
        sum += navstivene[i];
    }
    // ak sme boli vsade
    if (sum == n) {
        if (cas + mapa[dom][0] < mincas) // ak je najmensi cas zatial
            mincas = cas + mapa[dom][0]; // min cas je cas zatial + navrat domov
        navstivene[dom] = 0; // musime nastavit na 0 ked odideme pre dalsie varianty
            return;
    }

    // pre pocet domov
    for (i = 0; i < n; i++) {
        // ak este nebol navstiveny a ak sa tam vobec oplati chodit (ak uz mam lepsie riessenie tak nie)
        if (navstivene[i] == 0 && cas + mapa[dom][i] < mincas) {
            najdi_min (i, cas + mapa[dom][i]); // pre dany dom, plus cas pre danu vzdialenost
            // navrat <--
        }
    }

    // pri odchode musime nastavit navstivene na 0
    navstivene[dom] = 0;
    return;
}

// taka pomcna funkcia na vypisanie vyslednej casovej hodnoty
void vypis() {
    //printf("\n\nMinimum :");
    printf("\n%d\n", mincas);
}

// main funkcia
int main () {

    // kym ma funkcia nacitaj co citat zo vstupu vracia 1
    while (nacitaj () > 0) {
        mincas = 2000000000;
        najdi_min (0, 0); // vychodiskovy dom a cas
        vypis ();
    }

    return 0;
}
