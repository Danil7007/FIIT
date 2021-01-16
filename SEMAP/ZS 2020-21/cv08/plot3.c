// uloha8-2.c -- Emma Macháčová, 4.11.2020 12:35

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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

float uhol (BOD bodA, BOD bodB) {
  float deltaX, deltaY;
  float uhol;
  
  deltaX = bodA.x - bodB.x;
  deltaY = bodA.y - bodB.y;
  //printf ("\nROZDIEL %lf %lf\n", deltaX, deltaY);

  uhol = (deltaY / deltaX);
  uhol = atan(uhol);

  







  printf ("UHOL %lf\n", uhol);
  return uhol;
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

float maxUhol(int akt, int n, BOD* pole, int* next) {
  int i, pocet=0, saveIndex;
  float temp, max=-1000;
  
  while (pocet < n) { // kym neprejdeme vsetky prvky pola

    for (i=0; i<n; i++) {

      if (akt != i) { // nech neporovnavame ten isty bod so sebou
        temp = uhol (pole[akt], pole[i]);
        printf (" %d ? %d  : %lf\n", akt, i, temp);

        if (temp > max) { // najdene maximum
          max = temp;  
          saveIndex = i;
          *next = saveIndex;
        }

      } 

      pocet++; 
    }
  }

  printf ("%d -> %d :  %lf\n", akt, *next, max);
  return max;
}


int main () {
  int n, next, akt;
  BOD* pole;
  
  scanf ("%d", &n);
  pole = (struct bod*)calloc(n, sizeof(struct bod));
  
  nacitaj(n, pole);

  uhol (pole[0], pole[1]);

  //qsort (pole, n, sizeof(BOD), porovnaj);
  //vypis(n, pole);

  /*next = 0;
  akt = 0;
  do {
    maxUhol(akt, n, pole, &next);
    akt = next;
  } while (next != 0);*/

  return 0;
}