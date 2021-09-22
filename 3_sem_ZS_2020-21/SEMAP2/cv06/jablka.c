// uloha6-2.c -- Emma Macháčová, 21.10.2020 14:30

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef struct bod {
  double x;
  double y;
  double cas;
} BOD;

// qsort
int compare (const void * a, const void * b) {

  BOD *bodA = (BOD *)a;
  BOD *bodB = (BOD *)b;

  return (bodA->cas - bodB->cas);
}

// stiha / nestiha
int porovnaj (BOD a, BOD b, double rychlost) {
  double vzdialenostX, vzdialenostY, rozdielCas;

  /*a.x - b.x < 0 ? (vzdialenostX = a.x - b.x * -1) : (vzdialenostX = a.x - b.x);
  a.y - b.y < 0 ? (vzdialenostY = a.y - b.y * -1) : (vzdialenostY = a.y - b.y);*/

  vzdialenostX = a.x - b.x;
  vzdialenostY = a.y - b.y;
  rozdielCas = a.cas - b.cas;

  /*printf ("rozdiel x: %lf\n", vzdialenostX);
  printf ("rozdiel y: %lf\n", vzdialenostY);
  printf ("vzdialennost: %lf\n", sqrt(vzdialenostX*vzdialenostX + vzdialenostY*vzdialenostY));
  printf ("rozdiel cas: %lf\n", rozdielCas);*/

  // a*a + b*b = c*c
  if (vzdialenostX*vzdialenostX + vzdialenostY*vzdialenostY <= rychlost*rozdielCas*rychlost*rozdielCas) {
    //printf ("stiha\n");
    return 1;
  }
  else {
    //printf ("nestiha\n");
    return 0;
  }
}


int recPocet (BOD* pole, int start, int nasl, int koniec, double rychlost, int nestihnuty, int *max, int aktMax) {
  int i, pom;

  if (nasl > koniec && start < koniec) {
    start = 0;
    nasl = nestihnuty;
    nestihnuty = 0;
    if (aktMax > *max) {
      *max = aktMax;
      aktMax = 0;
    }
    aktMax = 0;
  }

  if (start == koniec) {
    if (aktMax > *max) {
      *max = aktMax;
      aktMax = 0;
    }
    aktMax = 0;
    return 0;
  }

  
  if (porovnaj (pole[start], pole[nasl], rychlost) == 1) { // stihol
    aktMax++;
    printf ("%c %c stihol, max %d\n", start+65, nasl+65, aktMax);
    return recPocet(pole, nasl, nasl+1, koniec, rychlost, nestihnuty, max, aktMax);
  }

  if (porovnaj (pole[start], pole[nasl], rychlost) == 0) { // nestihol
    printf ("%c %c nestihol \n", start+65, nasl+65);
    if (nestihnuty == 0) {
      nestihnuty = nasl;
    }
    return recPocet(pole, start, nasl+1, koniec, rychlost, nestihnuty, max, aktMax);
  }


}


int main() {
  int pocet, i, max=0;
  BOD* body;
  BOD novy;
  double rychlost;
  BOD start;
  start.x = 0;
  start.y = 0;
  start.cas = 0;

  while (scanf ("%d", &pocet) > 0 ) {  // nacitanie
    max=0;
    scanf ("%lf", &rychlost);

    // pole bodov
    body = (struct bod*)calloc(pocet+1, sizeof(struct bod)); 

    for (i=0; i<pocet; i++) { // nacitanie bodov

      scanf ("%lf", &novy.x);
      scanf ("%lf", &novy.y);
      scanf ("%lf", &novy.cas);

      body[i] = novy; // vlozenie do pola
    }
    novy.x = 0;
    novy.y = 0;
    novy.cas = 0;
    body[i] = novy; // vychodiskovy bod

    /*for (i=0; i<=pocet; i++) { // vypis
      printf ("%c: %.2lf ", i+65, body[i].x);
      printf ("%.2lf ", body[i].y);
      printf ("%.2lf\n", body[i].cas);
    }
    printf ("\n");*/

    // zoradenie
    qsort (body, pocet+1, sizeof(struct bod), compare);

    for (i=0; i<=pocet; i++) { // vypis
      printf ("%c: %.2lf ", i+65, body[i].x);
      printf ("%.2lf ", body[i].y);
      printf ("%.2lf\n", body[i].cas);
    }
    printf ("\n");

    recPocet(body, 0, 1, pocet, rychlost, 0, &max, 0);
    printf ("%d\n", max);

    //porovnaj (body[1], body[2], rychlost);
  }
  
  return 0;
}