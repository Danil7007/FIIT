#include <stdio.h>
#include <string.h>

int main () {
  int cisla[1300000];
  int prvocisla[100000];
  int i, j, n;

  // nacitanie celych cisiel
  for (i=2; i < 1300000; i++) {
    cisla[i] = i;
  }

  // vytriedenie prvocisiel
  for (i=2; i*i < 1300000; i++) {
    for (j=2; j < 130000; j++) {
      if (cisla[i] * j > 1300000) {
        break;
      }
      else {
        cisla[cisla[i] * j] = 0;
      }
    }
  }

  n = 0;
  for (i=0; i < 1300000; i++) {
    if (cisla[i]) {
      prvocisla[n] = cisla[i];
      n++;
    }
  }

  while (scanf ("%d", &i) > 0) {
    printf ("%d\n", prvocisla[i-1]);
  }








  return 0;
}