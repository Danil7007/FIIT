// uloha8-2.c -- Emma Macháčová, 4.11.2020 12:35

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct bod {
  int x;
  int y;
  double vzdialenost;
} BOD;

double vektor (double x1, int x2, double y1, int y2) {
  double vekt=0;
  double a, b;

  a = x1 - x2;
  a *= a;
  b = y1 - y2;
  b *= b;

  vekt = sqrt(a + b);

  return vekt;
}

int compare (const void * a, const void * b) {
  BOD *bodA = (BOD *)a;
  BOD *bodB = (BOD *)b;

  return ( bodA->x - bodB->x );
}

int plot (int n) {
  int i;
  int loX, hiX;
  int loY, hiY;
  double stredX=0, stredY=0;
  double maxVzdialenost=0;

  BOD* pole;
  pole = (struct bod*)calloc(n, sizeof(struct bod));
  BOD* pole2;
  pole2 = (struct bod*)calloc(n, sizeof(struct bod));

  // aspon jeden bod to predsa musi mat
  scanf ("%d %d", &pole[0].x, &pole[0].y);
  loX = hiX = pole[0].x;
  loY = hiY = pole[0].y;

  for (i=1; i<n; i++) {
    scanf ("%d %d", &pole[i].x, &pole[i].y);
    if (pole[i].x < loX) // najdenie extremov
      loX = pole[i].x;
    if (pole[i].y < loY)
      loY = pole[i].y;
    if (pole[i].x > hiX)
      hiX = pole[i].x;
    if (pole[i].y > hiY)
      hiY = pole[i].y;
  }

  stredX = (hiX + loX) / 2; // najdenie stredu
  stredY = (hiY + loY) / 2;

  for (i=0; i<n; i++) { // vypocitanie vzdialenosti
    pole[i].vzdialenost = vektor(stredX, pole[i].x, stredY, pole[i].y);
    //if (pole[i].vzdialenost > maxVzdialenost) 
      //maxVzdialenost = pole[i].vzdialenost;
  }

  qsort (pole, n, sizeof(BOD), compare); // zoradenie

  /*for (i=0; i<n; i++) {
    printf ("%d %d\n", pole[i].x, pole[i].y);
  }
  printf("---\n");*/

  int j=0;
  for (i=0; i<n; i++) { // zoradenie 2
    if (pole[i].y >= stredY) {
      pole2[j] = pole[i];
      j++;
    }
  }
  for (i=n-1; i>=0; i--) {
    if (pole[i].y < stredY) {
      pole2[j] = pole[i];
      j++;
    }
  }

  free (pole);

  for (i=0; i<n; i++) { //vypis
    printf ("%d %d\n", pole2[i].x, pole2[i].y);
  }

  return 0;
}

int main() {
  int n;

  scanf ("%d", &n);
  plot (n);

  return 0;
}