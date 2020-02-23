// uloha4-3.c -- Emma Macháčová, 14.10.2019 17:08

#include <stdio.h>
#include <string.h>

int main() {

  int male, velke, dlzka, i;
  char vstup [90];

  scanf("%s", &vstup[0]);
  dlzka = strlen(vstup);

  for (i = 0; i < dlzka; i++) {
    if ('a' <= vstup[i] && vstup[i] <= 'z') {
      male += 1;
    }
    if ('A' <= vstup[i] && vstup[i] <= 'Z') {
      velke += 1;
    }
  }
 
  printf ("%d %d", male, velke);
  return(0);
}