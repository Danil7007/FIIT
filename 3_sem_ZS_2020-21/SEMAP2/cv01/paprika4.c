// uloha1-1.c -- Emma Macháčová, 23.9.2020 23:46

#include <stdio.h>

int pocetDni, varianty;

int maxZisk () {
    int a=0, b=0, c=0, sken=2, zisk=0, i;
    scanf ("%d", &pocetDni);

    //printf ("pocet dni %d\n", pocetDni);
    if (pocetDni < 2) {
        printf ("0\n");
        for (i=0; i < pocetDni; i++) {
            scanf("%d", &b);
        }
        return 0;
    }

    scanf ("%d %d", &a, &b);
    // od dva lebo dve hodnoty boli uz nacitane
    while (sken < pocetDni) {

        //printf ("a %d b %d c %d\n", a, b, c);

        // klesanie
            if (a > b) {
                // nebol vrch
                if (b > c) {
                    a = b;
                    scanf ("%d", &b);
                    sken++;
                }
                // bol vrch
                else if (b < c) {
                    zisk += c - a;
                    a = b;
                    scanf ("%d", &b);
                    sken++;
                    c = 0;
                }
                
            }

        // stupanie
            else if (a < b) {
                // za peakom
                if (b <= c) {
                    zisk += c - a;
                    a = b;
                    scanf ("%d", &b);
                    sken++;
                    c = 0;
                    //printf ("aktualny zisk %d\n", zisk);
                }
                // stale stupa
                else if (b > c) {
                    c = b;
                    scanf ("%d", &b);
                    sken++;
                }
            }

        // konst
            else if (a == b) {
                // oba spodky kopca su rovnako vysoko ale uz mam stred
                if (c > b) {
                    zisk += c - a;
                    a = b;
                    scanf ("%d", &b);
                    sken++;
                    c = 0;
                    //printf ("aktualny zisk %d\n", zisk);
                }

                // rovinka pri stupani / klesani
                if (b >= c) {
                    a = b;
                    scanf ("%d", &b);
                    sken++;
                }
            }
    }
    //printf ("%d %d %d\n", a, b, c);

    // kopec na uplnom konci ktory sa inak nezarata
    if ((c > a) || (b > a)) {
        if (c > b) {
            zisk += c - a;
        }
        else {
            zisk += b - a;
        }
        //printf ("aktualny zisk %d\n", zisk);
    }

    printf ("%d\n", zisk);
    return 0;
}

int main () {
    int i;
    scanf ("%d", &varianty);
    for (i=0; i<varianty; i++) {
        maxZisk();
        //printf ("\n");
    }
    return 0;
}