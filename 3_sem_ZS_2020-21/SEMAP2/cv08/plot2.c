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

BOD p[1000];
BOD o[2000];
int np, no;

void insert (int i);
void hulk();
int obal (BOD a, BOD b, BOD c);

int compare (const void * a, const void * b) {
  BOD *bodA = (BOD *)a;
  BOD *bodB = (BOD *)b;

  return ( bodA->x - bodB->x );
}

void insert (int i) {
  while (no >= 2 && obal(o[no-2], o[no-1], p[i]) < 0) {
    no--;
  }
  o[no++] = p[i];
}

void hulk() {
  int i;
  o[0] = p[0];
  o[1] = p[1];
  no=2;
  for (i=2; i<np; i++) {
    insert(i);
  }
  for (i=np-2; i>=0; i--) {
    insert(i);
  }
}

int obal (BOD a, BOD b, BOD c) {
  return (c.x - a.x) * (c.y - b.y) - (c.x - b.x) * (c.y - a.y);
}



int main() {
  int n;
  
  scanf ("%d", &n);
  for (int i = 0; i<n; i++) {
    scanf ("%d", &p[i].x);
    scanf ("%d", &p[i].y);
  }

  qsort (p, n, sizeof(BOD), compare);

  hulk(n);

  for (int i=0; i<no; i++) {
    printf ("%d ", o[i].x);
    printf ("%d\n", o[i].y);
  }

  return 0;
}