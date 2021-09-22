// uloha1-1.c -- Emma Macháčová, 23.9.2020 23:46

#include <stdio.h>
#include <stdlib.h>

int analyzuj () {
    int* cisla;
    int* cislaUpravene;

    int i, x, pocet;

    scanf ("%d", &pocet);

    cisla = (int*)calloc(pocet, sizeof(int));
    cislaUpravene = (int*)calloc(pocet, sizeof(int));

    printf ("(1) ");
    for (i=0; i < pocet; i++) { // skenovanie
        scanf ("%d", &cisla[i]);
        printf ("%d ", cisla[i]);
    }

    
    x = 0;
    i = 0;
    for (i=0; i < pocet; i++) { // odstranenie roviniek

        if (i > 0 && cisla[i-1] != cisla[i]) {
            //printf ("%d ", cisla[i-1]);
            cislaUpravene[x] = cisla[i-1];
            x++;
        }
    }

    //printf ("\n(2) ");
    for (i=0; i < x; i++) { // vypis
        //printf ("%d ", cislaUpravene[i]);
    }

    for (i=2; i < x; i++) { // odstranenie spojov
        // v klesani
        if (cislaUpravene[i-2] > cislaUpravene[i-1] && cislaUpravene[i-1] > cislaUpravene[i]) {
            cislaUpravene[i-1] = cislaUpravene[i-2];
        }
        // v stupani
        if (cislaUpravene[i-2] < cislaUpravene[i-1] && cislaUpravene[i-1] < cislaUpravene[i]) {
            cislaUpravene[i-1] = cislaUpravene[i-2];
        }
    }

    //printf ("\n(3) ");
    for (i=0; i < x; i++) { // vypis
        //printf ("%d ", cislaUpravene[i]);
    }

    pocet = 0;
    for (i=0; i < x; i++) { // odstranenie roviniek

        if (cislaUpravene[i-1] != cislaUpravene[i]) {
            cisla[pocet] = cislaUpravene[i];
            pocet++;
        }
    }

    free (cislaUpravene);

    //printf ("\n(4) ");
    for (i=0; i < pocet; i++) { // vypis
        //printf ("%d ", cisla[i]);
    }
    
    int aktZisk=0, zisk=0;

    for (i=0; i < pocet-1; i++) {
        aktZisk = (cisla[i+1] - cisla[i]);
        if (aktZisk > 0) {
            //printf ("\n%d ", aktZisk);
            zisk += aktZisk;
        }
    }
    
    printf ("%d\n", zisk);

    free (cisla);
    return 0;
}

int main () {
    int prep;
    scanf ("%d", &prep);

    while (prep > 0) {
        analyzuj ();
        prep--;
    }
    
    
    return 0;
}