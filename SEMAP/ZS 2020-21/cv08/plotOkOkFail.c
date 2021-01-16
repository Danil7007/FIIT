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

// pomocna funkcia
void vypis (int n, BOD* pole) {
  for (int i=0; i<n; i++) {
    printf ("%d ", pole[i].x);
    printf ("%d\n", pole[i].y);
  }
}

// na zoradenie
int porovnaj (const void * a, const void * b) {
  BOD *bodA = (BOD *)a;
  BOD *bodB = (BOD *)b;

  if (bodA->x != bodB->x) 
    return ( bodA->x - bodB->x );
  else
    return (bodA->y - bodB->y);
}

// vypocet velkosti vektora AB
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

// pocita uhol, tak ze
// SEVER = 180
// JUH = 0
// VYCHOD = 90
// ZAPAD = -90
float uhol (BOD bodA, BOD bodB) {
  float dX, dY, uhol=0;

  dX = bodA.x - bodB.x; // delta X a delta Y
  dY = bodA.y - bodB.y;

  // pre 4 svetove strany ked su presne
  if (dX == 0 && dY > 0) // dole
    uhol = 0;
  else if (dY == 0 && dX < 0) // 90°
    uhol = PI / 2;
  else if (dX == 0 && dY < 0) // 180°
    uhol = PI;
  else if (dY == 0 && dX > 0) // -90°
    uhol = (PI / 2) * (-1);
  // ----------- ked je to niekde medzi ----------- kladne uhly
  else if (bodB.y < bodA.y && bodB.x > bodA.x) { // JV
    uhol = atan (dX / dY) * (-1);
  }
  else if (bodB.y > bodA.y && bodB.x > bodA.x) { // SV
    uhol = atan (dY / dX) + (PI / 2);
  } 
  // -------------------------------------------- zaporne uhly 
  else if (bodB.y > bodA.y && bodB.x < bodA.x) { // SZ
    uhol = atan (dY / dX) - (PI / 2);
  } 
  else if (bodB.y < bodA.y && bodB.x < bodA.x) { // JZ
    uhol = atan (dX / dY) * (-1);
  } 
  // --------------------------------------------------------- 

  return uhol;
}

float maxUhol (int start, int n, BOD* pole, int* pouzite, int* dalsiIndex, float* plot) {
  float max = -500, temp = -500; 
  // max uhol a temporary uhol na porovnanie
  int akt=0, index;
  // aktualny index s ktorym sa porovnava a index co ukladame

  // pole[start] sa porovna so vsetkymi bodmi v poli
  // okrem sam so sebou a uz pouzitymi prvkami, 
  // (podla pola pouzite)
  // a zisti sa najvacsi uhol
  // prvok s najvacsim uhlom pouzijeme v plote (pole pouzite)

  for (akt=0; akt<n; akt++) {
    if (akt != start && pouzite[akt] == 0) {
      temp = uhol (pole[start], pole[akt]);
      //printf ("  %d -> %d : %lf\n", start, akt, temp);
      if (temp >= max) {
        max = temp;
        index = akt; // index prvku ktory pouzijeme v plote
        //printf ("  max %lf\n", max);
      }
    }
  }

  // kedze je to zoradene mozeme preskocit rovno vsetky prvky
  // medzi startom a tymto indexom
  *dalsiIndex = index;
  //printf ("%d -> %d : %.2lf°\n", start, index, max);

  // vypocet vzdialenosti
  *plot += vzdialenost(pole[start], pole[index]);

  // prvok co sme pouzili oznacime ako pouzity
  pouzite[index] = 1;
  return max;
}

int main () {
  int n, dalsiIndex=0;
  float plot=0;
  BOD* pole;
  int* pouzite;
  
  scanf ("%d", &n);

  // pole bodov
  pole = (struct bod*)calloc(n, sizeof(struct bod)); 
  // ktore body su v plote
  pouzite = (int*)calloc(n, sizeof(int));
  nacitaj(n, pole); // nacitanie vstupu
  // zoradi podla x, ak x==x podla y
  qsort (pole, n, sizeof(BOD), porovnaj); 
  //vypis(n, pole);

  // trasa
  do {
    maxUhol (dalsiIndex, n, pole, pouzite, &dalsiIndex, &plot);
  } while (dalsiIndex != 0);
  // je nula na zaciatku a na konci ked sa plot uzavrie
  
  printf ("%.3lf\n", plot);

  return 0;
}