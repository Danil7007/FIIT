#include <stdio.h>

int prvocisla[100000];
int hladam[100000];
int pocetPrvocisiel=0, pocetHladani=0;

int prime (int n) {

  if (n <= pocetPrvocisiel) { // ak uz sme ho nasli
    //printf ("uz mam\n");
    //printf ("%d\n", prvocisla[n-1]);
    return 0;
  }

  int i, j, flag;

  for (i=2; i>0; i++) {
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
  int n, i, max=0;

  while (scanf ("%d", &n) > 0) {
    hladam[pocetHladani] = n;
    pocetHladani++;
    if (n > max) {
      max = n;
    }
  }

  //n = hladam[pocetHladani-1]; // najvacsi prvok
  prime(max);

  for (i=0; i<pocetHladani; i++) {
    n = hladam[i];
    //prime(n);
    printf ("%d\n", prvocisla[n-1]);
  }
  
  

  return 0;
}