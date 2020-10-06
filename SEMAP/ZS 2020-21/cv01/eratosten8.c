#include <stdio.h>
#include <string.h>

#define MAX 1300000
#define MIN 110000


int main () {
  int i, j;
  int prvocisla[MAX];
  int pole_poradi[MIN];
  int i_vstup = 0;

  while (scanf ("%d", &pole_poradi[i_vstup++]) > 0);

  for (i = 2; i < MAX; i++) {
    prvocisla[i] = i;
  }

  i = 2;
  while ((i*i) < MAX) {
    if (prvocisla[i]) {
      for (j=2; j < MAX; j++) {
        if (prvocisla[i] * j > MAX) {
          break;
        }
        else {
          prvocisla[prvocisla[i] * j] = 0;
        }
      }
    }
    i++;
  }

  int maly_index = 0;
  int mensie_pole[MIN];

  for (i=0; i < MAX; i++) {
    if (prvocisla[i]) {
      mensie_pole[maly_index] = prvocisla[i];
      maly_index++;
    }
  }

  for (i=0; i < i_vstup-1; i++) {
    printf ("%d\n", mensie_pole[pole_poradi[i]-1]);
  }




  return 0;
}