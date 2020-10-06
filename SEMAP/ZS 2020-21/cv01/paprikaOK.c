/*Jakubko dostal vreckové. Namiesto toho, aby ho len tak minul, však dostal geniálny nápad. Čo keby začal podnikať?

Na trhu predávajú papriku. Jakubko si všimol, že cena papriky sa každý deň mení. Zároveň sa mu podarilo vypočítať odhad cien papriky pre nasledovných N dní. Teraz už len potrebuje zistiť, ktoré dni má papriku kúpiť a ktoré ju predá. Keďže ešte nevie, či jeho odhad je správny, povedal si, že vždy bude mať nakúpenú najviac jednu papriku, teda pred tým než kúpi ďalšiu papriku, musí tú predchádajúcu predať.

Vstup: Na prvom riadku vstupu je celé číslo T, ktoré vyjadruje počet scenárov. Pre každý scenár nasleduje samostatný riadok. Na každom z týchto riadkov je najprv uvedené celé číslo N a potom N čísel, ktoré vyjadrujú odhad cien papriky na nasledovných N dní.

Výstup: Pre každý scenár vypočítajte maximálny zisk, ktorý Jakubko dokáže dosiahnuť. Môžete predpokladať, že počiatočné vreckové bude stačiť na nákup akejkoľvek drahej papriky. Toto vreckové sa do výsledku nezapočítava.

Ukážka vstupu:
1
2 1 3
Výstup pre ukážkový vstup:
2
*/

#include <stdio.h>
#include <stdlib.h>

int zisk;

int paprika () {
    int* cisla;
    int pocet=0, a=0, b=0, i=0;
    zisk=0;

    scanf ("%d", &pocet);
    cisla = (int*)calloc(pocet, sizeof(int));

    if (pocet <= 1) { // ak je len jeden den alebo ziaden
        // max zisk = 0
        for (i=0; i < pocet; i++) { // vycerpanie nepotrebneho vstupu
            scanf ("%d", &a);
        }
        printf ("%d\n", zisk);
        return 0;
    }

    if (pocet == 2) { // ak su dva
        scanf ("%d", &a);
        scanf ("%d", &b);
        if (b > a) {
            zisk = (b - a);
        }
        printf ("%d\n", zisk);
        return 0;
    }

    for (i=0; i < pocet; i++) { // nacitanie
        scanf ("%d", &a);
        cisla[i] = a;
    }
    a = 0; // bude vyuzite na nieco ine

    for (i=0; i < (pocet-1); i++) {
        a = cisla[i];
        b = cisla[i+1];

        //printf ("a: %d b: %d\n", a, b);

        if (b > a) {
            zisk += (b - a);
        }
    }

    free (cisla);
    printf ("%d\n", zisk);
    return 0;
}

int main () {
    int i, j;

    scanf ("%d", &i);

    for (j=0; j < i; j++) {
        paprika ();
    }


    return 0;
}