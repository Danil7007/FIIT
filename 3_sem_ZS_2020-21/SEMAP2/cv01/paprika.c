// uloha1-1.c -- Emma Macháčová, 23.9.2020 23:46

#include <stdio.h>

int vyhodne (int cena[], int zac, int kon) {

  int pom_zisk = 0, pom_zisk2 = 0, i, j;

  if (kon <= zac) {
    return 0;
  }

  for (i=zac; i<kon; i++) {

    for (j=i+1; j<=kon; j++) {
      if (cena[j] > cena[i]) {
        pom_zisk2 = cena[j] - cena[i] + vyhodne (cena, zac, i-1) + vyhodne (cena, j+1, kon);
        if (pom_zisk > pom_zisk2) {
          pom_zisk += pom_zisk;
        }
        else {
          pom_zisk += pom_zisk2;
        }
      }
    }
  }

  return pom_zisk;
}

int main() {
  // nechce sa mi alokovat pole dynamicky
  int odhad[100];
  // t je pocet scenarov
  int t, n, i, j, zisk;

  scanf ("%d", &t);

  // sken pocet scenarov
  for (i=0; i<t; i++) {
    for (j=0; j<100; j++) {
      odhad[j] = 0;
    }
    scanf ("%d", &n);
    // sken odhady cien
    for (j=0; j<n; j++) {
      scanf ("%d", &odhad[j]);
    }
    zisk = vyhodne (odhad, 0, j-1);
    printf ("%d\n", zisk);
    zisk = 0;
  }


  return 0;
}