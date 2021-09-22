// uloha5-4.c -- Emma Macháčová, 21.10.2019 18:22

#include <stdio.h>

int main() {
  
  int vstup, pocet_a, pocet_b, i, j, k, l, m, n;

  scanf ("%d", &vstup);
  
  
  if (vstup < 1 || vstup > 15 && || vstup % 2 == 0) {
    printf ("Zly vstup");
    
  }
  else {
    pocet_a = 1;
    pocet_b = vstup - pocet_a;

    for (i=0; i < vstup; i++) {

      for (j=0; j < pocet_a; j++) {
        printf ("*");
      }
      for (k=0; k < pocet_b; k++) {
        printf (" ");
      }

      pocet_a += 1;
      pocet_b = vstup - pocet_a;

      printf ("\n"); 
    }

    pocet_b = 1;
    pocet_a = vstup - pocet_b;

    for (l=0; l < vstup - 1; l++) {

      for (m=0; m < pocet_a; m++) {
        printf ("*");
      }
      for (n=0; n < pocet_b; n++) {
        printf (" ");
      }

      pocet_b += 1;
      pocet_a = vstup - pocet_b;

      if (pocet_a >= 1) {
        printf ("\n"); 
      }
      
    }
  }
  }
  
  return 0;
