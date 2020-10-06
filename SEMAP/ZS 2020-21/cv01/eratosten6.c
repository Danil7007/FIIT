#include <stdio.h>
#include <string.h>

int main () {
  int i, max, p;
  // bool pole prvocisla 0 1 podla indexu == prvocislo 
  int prvocislaBool[1300000]; 
  int prvocisla[100000]; // hodnoty prvocisiel
  memset (prvocislaBool, 1, sizeof(prvocisla)); // nast. hodnoty na true

  max = 1300000; // 100.000-ce prvocislo cca
  for (p = 2; p*p <= max; p++) {
    if (prvocislaBool[p] == 1) {
      for (i = p*p; i <= max; i += p) {
        prvocislaBool[i] = 0; // vymazanie vsetkych nasobkov p
      }
    }
  } // index 2 == 1, 3 == 1, 4 == 0....

  p = 0;
  for (i=2; i < max; i++) {
    if (prvocislaBool[i]) {
      prvocisla[p] = i; // priradenie prvocisiel do pola
      p++;
    }
  }

  while (scanf ("%d", &i) > 0) { // vstup - poradia prvocisiel
    printf ("%d\n", prvocisla[i-1]);
  }

  return 0;
}