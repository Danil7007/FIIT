// uloha4-8.c -- Emma Macháčová, 14.10.2019 18:15

#include <stdio.h>

int main() {
    int vstup, priemer, i;
    float vstup2, sucet;

    scanf ("%d", &vstup);

    sucet = 0;
    priemer = 0;
    scanf ("%f", &vstup2);
    priemer += vstup2;
    sucet += vstup2;

    i = 0;
    
    while (i < (vstup - 1)) {
        scanf ("%f", &vstup2);

        if (vstup2 > priemer) {
            sucet += vstup2;
        }

        priemer += vstup2;
        priemer = priemer / (i + 1);

        i += 1;
    }

    printf ("%.2f", sucet);

  return 0;
}