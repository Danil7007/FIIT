// uloha8-2.c -- Emma Macháčová, 4.11.2020 12:35

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define PI 3.14159265358

typedef struct bod {
  int x;
  int y;
  int kvadrant;
  double vzdialenost;
} BOD;

void nacitaj (int n, BOD* pole) {
  for (int i=0; i<n; i++) {
    scanf ("%d", &pole[i].x);
    scanf ("%d", &pole[i].y);
    //printf ("%d %d\n", pole[i].x, pole[i].y);
  }
}

void vypis (int n, BOD* pole) {
  for (int i=0; i<n; i++) {
    printf ("%d ", pole[i].x);
    printf ("%d\n", pole[i].y);
  }
}

int porovnaj (const void * a, const void * b) {
  BOD *bodA = (BOD *)a;
  BOD *bodB = (BOD *)b;

  if (bodA->x != bodB->x) 
    return ( bodA->x - bodB->x );
  else
    return (bodA->y - bodB->y);
}

float vzdialenost (BOD bodA, BOD bodB) {
  float vzdial=0;
  float a, b;

  a = bodA.x - bodB.x;
  a *= a;
  b = bodA.y - bodB.y;
  b *= b;

  vzdial = sqrt(a + b);

  return vzdial;
}

float uhol (BOD bodA, BOD bodB) {
  float dX, dY, uhol=0;

  dX = bodA.x - bodB.x;
  dY = bodA.y - bodB.y;

  if (dX == 0 && dY > 0)
    uhol = 0;
  else if (dY == 0 && dX < 0)
    uhol = PI / 4;
  else if (dX == 0 && dY < 0)
    uhol = PI / 2;
  else if (dY == 0 && dX > 0)
    uhol = (PI / 4) * (-1);
  // --------------------------------------------------------- 
  else if (bodB.y < bodA.y && bodB.x > bodA.x) { // a
    uhol = atan (dX / dY) * (-1);
  }
  else if (bodB.y > bodA.y && bodB.x > bodA.x) { // b
    uhol = atan (dY / dX) + (PI / 2);
  } 
  // --------------------------------------------------------- 
  else if (bodB.y > bodA.y && bodB.x < bodA.x) { // c
    uhol = atan (dY / dX) - (PI / 2);
  } 
  else if (bodB.y < bodA.y && bodB.x < bodA.x) { // d
    uhol = atan (dX / dY) * (-1);
  } 
  // --------------------------------------------------------- 

  return uhol;
}

float maxUhol (int start, int n, BOD* pole, int* pouzite, int* dalsiIndex, float* plot) {
  float max = -500, temp = -500;
  int akt=0, index;

  for (akt=0; akt<n; akt++) {
    if (akt != start && pouzite[akt] == 0) {
      temp = uhol (pole[start], pole[akt]);
      if (temp >= max) {
        max = temp;
        index = akt;
        printf ("  %d -> %d : %lf\n", start, akt, max);
      }
    }
  }

  *dalsiIndex = index;
  printf ("%d -> %d : %.2lf°\n", start, index, max);

  *plot += vzdialenost(pole[start], pole[index]);

  pouzite[index] = 1;
  return max;
}

int main () {
  int n, dalsiIndex=0;
  float plot=0;
  BOD* pole;
  int* pouzite;
  
  scanf ("%d", &n);

  pole = (struct bod*)calloc(n, sizeof(struct bod));
  pouzite = (int*)calloc(n, sizeof(int));
  nacitaj(n, pole);
  qsort (pole, n, sizeof(BOD), porovnaj);
  //vypis(n, pole);

  // trasa
  do {
    maxUhol (dalsiIndex, n, pole, pouzite, &dalsiIndex, &plot);
  } while (dalsiIndex != 0);
  
  printf ("%.3lf\n", plot);

  return 0;
}