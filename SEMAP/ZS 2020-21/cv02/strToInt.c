// uloha2-2.c -- Emma Macháčová, 24.9.2020 18:05

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  int i=0, cislo=0, dlzka, nasob=1;
  char c[100];

  fgets (c, 100, stdin);
  //printf ("%d\n", cislo);
  dlzka = strlen(c);
  //printf ("%d\n", dlzka);

  for (i=dlzka; i >= 0; i--) {
    if (c[i] >= '0' && c[i] <= '9') {
      cislo += ((c[i] - '0') * nasob);
      nasob = nasob * 10;
    }
    else if (i == 0 || c[i-1] > '0' || c[i-1] < '9') {
        printf ("%d\n", cislo);
        cislo = 0;
        nasob = 1;
    }
  }

  return 0;
}