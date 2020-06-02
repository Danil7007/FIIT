// uloha4-8.c -- Emma Macháčová, 14.10.2019 18:15

#include <stdio.h>

int main() {
  int vstup, priemer, priemer2, i;
  float sucet;

  scanf ("%d", &vstup);
  int  pole[vstup];

  priemer2 = vstup;
  sucet = vstup;

  for (i = 1; i <= vstup; i++) {
    scanf ("%d", &pole[i]);

    priemer += pole[i];
    priemer /= i;

    if (priemer > priemer2) {
      sucet += pole[i];
    }

    priemer2 = priemer;
  }

  printf ("%.2f", sucet);

  return 0;
}