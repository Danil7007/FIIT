#include <stdio.h>

int prvocisla[100000];
int pocetPrvocisiel=0;
int posledne;

int prime (int n) {

  if (n <= pocetPrvocisiel) { // ak uz sme ho nasli nemusime dalej hladat
    //printf ("uz mam\n");
    //printf ("%d\n", prvocisla[n-1]);
    return 0;
  }

  int i, j, flag;

  if (pocetPrvocisiel == 0) { // ked este nemam najdene ziadne prvocislo
    posledne = 2;
  }
  else {
    posledne = prvocisla[pocetPrvocisiel-1]; // nastavi sa na posledne najdene prvocislo
  }

  for (i=posledne; i>0; i++) {
    flag = 0;
    for (j=0; j < pocetPrvocisiel; j++) {
      if (i % prvocisla[j] == 0) {
        flag = 1;
        break;
      }
    }
    if (flag == 0) {
      prvocisla[pocetPrvocisiel] = i;
      pocetPrvocisiel++;
    }
    if (pocetPrvocisiel == n) { // ak uz sme ho nasli
    //printf ("%d\n", prvocisla[n-1]);
    break;
    }
  }

  return 0;
}

int main () {
  int n;

  while (scanf ("%d", &n) > 0) {
    prime(n);
    printf ("%d\n", prvocisla[n-1]);
  }
  
  return 0;
}