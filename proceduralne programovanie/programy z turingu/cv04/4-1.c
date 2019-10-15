// uloha4-2.c -- Emma Macháčová, 14.10.2019 14:24

#include <stdio.h>

int main() {
  int a;
  scanf ("%d", &a);
  a <=0 ? printf ("Mrzne\n") : a >= 100 ? printf ("Vrie\n") : printf ("Normalna teplota");
  return 0;
}