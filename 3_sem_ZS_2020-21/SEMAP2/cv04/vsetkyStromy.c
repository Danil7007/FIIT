// uloha4-2.c -- Emma Macháčová, 7.10.2020 11:53

#include <stdio.h>

int factorial(int n) {
  int i, fact=1;
  
  for (i=1; i <= n; ++i) {
    fact *= i;
  }

  return fact;
}

int combination(int n, int r) {
  int comb;

  comb = (factorial(n)) / (factorial(r) * (factorial(n-r)));

  return comb;
}

int binaryTreesPossible (int n) {
  int btn, citatel, menovatel, podiel, intercon;

  citatel = combination(2*n,n);
  menovatel = (n+1); 
  podiel = citatel / menovatel;
  btn = podiel * factorial(n);

  intercon = btn / factorial(n);

  printf ("cit: %d\n", citatel);
  printf ("men: %d\n", menovatel);
  printf ("pod: %d\n", podiel);
  printf ("btn: %d\n", btn);

  return intercon;
}


int main()
{
  int n;

  while (scanf ("%d", &n) > 0) {
    printf ("%d\n", binaryTreesPossible (n));
  }

  

  return 0;
}