// uloha7-2.c -- Emma Macháčová, 31.3.2020 15:40

/*
Definujte štruktúru DATUM pre dátum (deň, mesiac, rok) a napíšte funkciu pocetDni(), ktorá dostane 2 dátumy a vráti počet dní medzi týmito dátumami. Neuvažujte priestupné roky. Funkciu použite v programe, ktorý načíta 2 dátumy a vypíše počet dní medzi prvým a druhým dátumom. Ak je druhý dátum nižší ako prvý, program vypíše správu Vymente datumy.

Ukážka vstupu:
1.4.2020
5.4.2020
Výstup pre ukážkový vstup:
4

*/

#include <stdio.h>

struct DATUM {
    int den;
    int mesiac;
    int rok;
};

int main() {
  struct DATUM datum1;
  struct DATUM datum2;
  char bodka;
  int riesenie=0, i;

  scanf("%d %c %d %c %d", &datum1.den, &bodka, &datum1.mesiac, &bodka, &datum1.rok);
  scanf("%d %c %d %c %d", &datum2.den, &bodka, &datum2.mesiac, &bodka, &datum2.rok);

  // korektny vstup
  if ( (datum2.rok < datum1.rok) || (datum2.rok == datum1.rok && datum2.mesiac < datum1.mesiac) || (datum2.rok == datum1.rok && datum2.mesiac == datum1.mesiac && datum2.den < datum1.den)){
    printf("Vymente datumy\n");
    return 0;
  } 

  // rozdiel iba v dnoch
  if (datum2.rok == datum1.rok && datum2.mesiac == datum1.mesiac){
      for (i = datum1.den; i < datum2.den; i++){
        riesenie++;
      }
  }
  // rozdiel v mesiacoh
  else if (datum2.rok == datum1.rok && datum2.mesiac != datum1.mesiac){
    // mesiace
    for (i = datum1.mesiac; i < datum2.mesiac; i++){
      if (i == 2){
        riesenie += 29;
      }
      else if (i == 1 || i == 3 || i == 5 || i == 7 || i == 8 || i == 10 || i == 12){
        riesenie += 31;
      }
      else {
        riesenie += 30;
      }
    }
    // dni
    for (i = datum1.den; i < datum2.den; i++){
        riesenie++;
      }
  }
  // rozdiel v rokoch
  else {
    // roky
    riesenie += (datum2.rok - datum1.rok) * 365;
    // mesiace
    for (i = datum1.mesiac; i < datum2.mesiac; i++){
      if (i == 2){
        riesenie += 29;
      }
      else if (i == 1 || i == 3 || i == 5 || i == 7 || i == 8 || i == 10 || i == 12){
        riesenie += 31;
      }
      else {
        riesenie += 30;
      }
    }
    // dni
    for (i = datum1.den; i < datum2.den; i++){
      riesenie++;
    }
  }

  printf("%d\n", riesenie);
  return 0;
}