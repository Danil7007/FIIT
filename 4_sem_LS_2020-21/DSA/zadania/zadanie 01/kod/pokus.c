// Zadanie 1 - Správca pamäti -- Emma Macháčová, 17.2.2021 14:26

// keďže pracujeme s pamäťou priamo budú nastávať konverzie o ktorých si kompiler bude myslieť že niesu správne, ale do pola vkladáme diagnostické informácie ktoré potrebujeme čítať, meníme veci ktoré nie su kompatibilné tak, aby to kompatibilné bolo na niektorých miestach je použité #pragma GCC diagnostic ignored "-Wincompatible-pointer-types"

#include <stdio.h>
#include <stdint.h> // na uint16_t
#include <string.h> // pre memset do memory_init
#include <stdlib.h> // pre random do testov
#include <time.h> 

// pseudo-enum
#define EMPTY 0
#define FULL 1
#define FREED 2
#define DEAD 3

// format
#define HLAVICKA 3
#define MEMORY_HLAVICKA 2

// globálny ukazovateľ na pamať pre memory_init
char *GLOB_MEM;

// deklarácie funkcií
void *memory_alloc (unsigned int size); // služby analogické malloc
int memory_free (void *valid_ptr); // uvoľnenie vyhradeného bloku pamäti
int memory_check (void *ptr); // skontrolovanie je ukazovateľ platný 
void memory_init (void *ptr, unsigned int size); // inicializácia pamäte

void vypis (); // pomocna funkcia
void test (int key, int uvolnovanie);

// inicializácia pamäte - DONE
void memory_init (void *ptr, unsigned int size) {
  // pokial nie je možné ani zapísať veľkosť pola, alebo by sa po zapísaní nezmestilo už nič iné
  if (size <= (MEMORY_HLAVICKA + HLAVICKA)) {return;} 

  GLOB_MEM = ptr; // priradenie vyhradenej pamäte a globálneho ukazovateľa

  // vynulovanie pamäte; +2 lebo na začiatok pôjde informácia o veľkosti poľa
  memset((GLOB_MEM + MEMORY_HLAVICKA), 0, size); 

  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wincompatible-pointer-types"
  uint16_t *pomocny_pointer = GLOB_MEM; // pomocný pointer, na pretypovanie GLOB
  #pragma GCC diagnostic pop
  *pomocny_pointer = (uint16_t) size; // veľkosť pamäte v prekonvertovanom tvare

  return;
}

// alokácia - ASI DONE (?)
void *memory_alloc (unsigned int size) {
  if (GLOB_MEM == NULL) { // ak nie je inicializovaná pamäť
    printf ("CHYBA - PAMAT NEBOLA INICIALIZOVANA\n\n");
    fprintf (stderr, "Pamäť nebola inicializovaná\n");
    return NULL;
  }

  // získanie veľkosti pamate
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wincompatible-pointer-types"
  uint16_t *velkost_pamate = GLOB_MEM; // pomocný pointer, na pretypovanie GLOB
  #pragma GCC diagnostic pop

  // aktualne miesto v pamati; 2 lebo na zaciatku mame hlavicku celeho pola
  uint16_t volna_pamat = *(velkost_pamate) - MEMORY_HLAVICKA;
  int pozicia = MEMORY_HLAVICKA; // od indexu 2 začína pamäť

  // pre využívanie fragmentov volnej pamäte
  char *free_ptr = NULL; // pointer na prvú medzeru
  int pocet_free = 0; // pocet medzier
  int velkost_free = 0; // velkost pamate medzier

  // ked nebude dost pamate
  if ((size + HLAVICKA) > (volna_pamat)) {
    printf ("Pamat nie je dostatocne velka\n\n");
    return NULL;
  }

  // while ( 0 <= (volna_pamat + velkost_free - HLAVICKA) && (volna_pamat + velkost_free - HLAVICKA) >= size ) { 
  // kym nie sme na konci pamate
  while ( 0 <= (volna_pamat + velkost_free) && (volna_pamat + velkost_free) >= size ) { 

    // case A - narazíme na nepoužitú voľnú pamäť - EMPTY ---------------------------
    if (GLOB_MEM[pozicia] == EMPTY) { 
      
      // aby na konci pamate neprislo k leaku - treba kontrolovat
      if ( 0 > (volna_pamat + velkost_free - HLAVICKA) || (volna_pamat + velkost_free - HLAVICKA) < size ) {
        printf ("Koniec pola\n\n");
        return NULL;
      }

      // ak nepredchádza blok uvolnenenj pamate
      if (free_ptr == NULL) {
        GLOB_MEM[pozicia] = FULL; // zmena stavu bloku pamate
        // uloženie informácie o veľkosti zabraného bloku pamäte
        #pragma GCC diagnostic push
        #pragma GCC diagnostic ignored "-Wincompatible-pointer-types"
        uint16_t *tmp = (GLOB_MEM + pozicia + 1); // priradenie
        #pragma GCC diagnostic pop
        *tmp = (uint16_t) size; //GLOB_MEM[pozicia+1] = (uint16_t) size; 
        // na GLOB_MEM[pozicia] je typ bloku
        // na GLOB_MEM[pozicia+1] a GLOB_MEM[pozicia+2] je velkost bloku
        // od GLOB_MEM[pozicia+3] zacina uzivatelska pamat

        printf ("ALOKACIA (1) PREBEHLA USPESNE, \n\talokovanych %d bitov od pozicie %d\n", size, pozicia);

        // minus size informacie (tmp) a 3 pre head
        //volna_pamat -= (*tmp + HLAVICKA);
        volna_pamat = volna_pamat - (size + HLAVICKA); 
        //printf ("\tzostávajúca pamäť %d bitov\n\n", volna_pamat);
        
        return (GLOB_MEM + pozicia + HLAVICKA); // pointer na prvý slot volnej pamäte ---- RETURN no. 1
      }

      // ak je predtým medzera
      else {
        *free_ptr = FULL;

        // informácia o velkosti bloku 
          #pragma GCC diagnostic push
          #pragma GCC diagnostic ignored "-Wincompatible-pointer-types"
          uint16_t *tmp2 = (free_ptr + 1); // priradenie
          #pragma GCC diagnostic pop
          *tmp2 = (uint16_t) size; //GLOB_MEM[pozicia+1] = (uint16_t) size; 

        // vynulovanie
        // NIE JE NUTNE, robi to ze uzivatelovi pride uplne prazdny blok pamate, dalo by sa to uplne vypustit z kodu
        //printf ("\n%d\n", (velkost_free + 3));
        // i zacina od 3 aby sa neprepisala hlavicka
        // prepise sa cela medzera v pamati, x slotov posunutych o prvu hlavicku
        for (int i = HLAVICKA; i < (velkost_free + HLAVICKA); i++) {
          *(free_ptr + i) = EMPTY;
        }

        printf ("ALOKACIA (2) PREBEHLA USPESNE, \n\talokovaných %d bitov \n", size);
        
        return (free_ptr + HLAVICKA); // ------------------------------- RETURN no. 2
      }
    }

    // case B - narazíme na už zabraný blok pamäte - FULL ---------------------------
    else if (GLOB_MEM[pozicia] == FULL) {
      // odpočítame od pamäte veľkosť zabratého bloku, tento údaj je na [pozicia+1]
      // a odpocitame aj miesto co zabera hlavicka
      #pragma GCC diagnostic push
      #pragma GCC diagnostic ignored "-Wincompatible-pointer-types"
      uint16_t* tmp = (GLOB_MEM + pozicia + 1);
      volna_pamat -= (*tmp + HLAVICKA); // 3 pre hlavičku ----------------- PAMAT !!!
      //printf (" -> na pozicii %d sa nachádza blok veľkosti %d;\n", pozicia, *tmp);
      pozicia += (*tmp + HLAVICKA); // skočíme za zabranú časť pamäte
      //printf (" -> presúvam sa na pozíciu %d\n", pozicia);
      #pragma GCC diagnostic pop

      // ak doteraz boli nejaké medzery tak neboli dosť veľké, lebo sa tam pamať nepriradila
      free_ptr = NULL;
      pocet_free = 0;
      velkost_free = 0;

      //printf("zostava %d\n", volna_pamat);
    }

    // case C - narazíme na uvolnený blok pamäte - FREED ----------------------------
    else if (GLOB_MEM[pozicia] == FREED) {
      #pragma GCC diagnostic push
      #pragma GCC diagnostic ignored "-Wincompatible-pointer-types"
      uint16_t *tmp = (GLOB_MEM + pozicia + 1); // velkost bloku medery
      #pragma GCC diagnostic pop

      // ak je to prvá medzera
      if (free_ptr == NULL) {
        free_ptr = (GLOB_MEM + pozicia);
        // pri prvej medzere neratame hlavicku lebo sa vyuzije ako je
        velkost_free += *tmp; 
        pocet_free++;
      }
      else {
        // pri dalsich mezerach sa rataju aj hlavicky lebo sa prepisu informaciami
        velkost_free += *tmp;
        velkost_free += HLAVICKA;
        pocet_free++;
      }
      
      //printf ("tmp %d,velkost medzeri %d\n", *tmp, velkost_free);
      
      // ak sa zmesti presne
      if ((velkost_free) == size){
        *free_ptr = FULL;

        // informácia o velkosti bloku 
          #pragma GCC diagnostic push
          #pragma GCC diagnostic ignored "-Wincompatible-pointer-types"
          uint16_t *tmp2 = (free_ptr + 1); // priradenie
          #pragma GCC diagnostic pop
          *tmp2 = (uint16_t) size; //GLOB_MEM[pozicia+1] = (uint16_t) size; 

        // vynulovanie
        // NIE JE NUTNE, robi to ze uzivatelovi pride uplne prazdny blok pamate, dalo by sa to uplne vypustit z kodu
        // i zacina od 3 aby sa neprepisala hlavicka
        // prepise sa cela medzera v pamati, x slotov posunutych o prvu hlavicku
        for (int i = HLAVICKA; i < (velkost_free + HLAVICKA); i++) {
          *(free_ptr + i) = EMPTY;
        } 

        printf ("ALOKACIA (3) PREBEHLA USPESNE, \n\talokovanych %d bitov od pozicie %d\n", size, pozicia);
        
        return (free_ptr + HLAVICKA);
        //return (GLOB_MEM + pozicia + HLAVICKA); // ------------------------------- RETURN no. 3
      }

      // ak je miesta viac
      else if (velkost_free > size) {
        *free_ptr = FULL; // zmena typu

        // informácia o velkosti bloku 
          #pragma GCC diagnostic push
          #pragma GCC diagnostic ignored "-Wincompatible-pointer-types"
          uint16_t *tmp2 = (free_ptr + 1); // priradenie
          #pragma GCC diagnostic pop
          *tmp2 = (uint16_t) size; //GLOB_MEM[pozicia+1] = (uint16_t) size; 

        // vynulovanie
        // NIE JE NUTNE, robi to ze uzivatelovi pride uplne prazdny blok pamate, dalo by sa to uplne vypustit z kodu
        //printf ("\n%d\n", (velkost_free + 3));
        // i zacina od 3 aby sa neprepisala hlavicka
        // prepise sa cela medzera v pamati, x slotov posunutych o prvu hlavicku
        for (int i = HLAVICKA; i < (velkost_free + HLAVICKA); i++) {
          // kym je prepisany pocet slotov kolko chce uzivatel
          if (i < size + HLAVICKA) {
            *(free_ptr + i) = EMPTY;
          }
          // sloty ktore si nevyziadal
          else {
            *(free_ptr + i) = DEAD; // sloty navyse
          }
        }

        printf ("ALOKACIA (4) PREBEHLA USPESNE, \n\talokovanych %d bitov od pozicie %d\n", size, pozicia);

        return (free_ptr + HLAVICKA);
        //return (GLOB_MEM + pozicia + HLAVICKA); // ------------------------------- RETURN no. 4
      }

      // ak je miesta malo
      else if (velkost_free < size) {
        // ako case B
        #pragma GCC diagnostic push
        #pragma GCC diagnostic ignored "-Wincompatible-pointer-types"
        uint16_t* tmp = (GLOB_MEM + pozicia + 1);
        volna_pamat -= (*tmp + HLAVICKA); // 3 pre hlavičku ----------------- PAMAT !!!
        pozicia += (*tmp + HLAVICKA); // skočíme za zabranú časť pamäte
        #pragma GCC diagnostic pop
      }
    }

    // case D - ak narazíme na malé mŕtve sloty - DEAD ------------------------------
    else if (GLOB_MEM[pozicia] == DEAD) {

      // ak je to prvá medzera
      if (free_ptr == NULL) {
        free_ptr = (GLOB_MEM + pozicia); // priradenie pointra
        // ak pred DEAD slotmi nebol FREED blok, chyba miesto na hlavicku, ktore sa pri FREED zachovava, lebo DEAD je iba jeden slot, teda pri prvom chybaju sloty na hlavicku
        velkost_free -= HLAVICKA; 
        velkost_free ++; // za aktualny slot
      }
      else {
        // pri DEAD blokoch nie su hlavicky
        velkost_free ++;
      }

      // NEMALO BY SA STAT ZE BUDE VIAC MIESTA LEBO PRIBUDA PO JEDNOM, case ze je viac miesta ako treba sa riesi v casti o FREED
      // ak sa zmesti presne
      if ((velkost_free) == size){
        *free_ptr = FULL;

        // informácia o velkosti bloku 
          #pragma GCC diagnostic push
          #pragma GCC diagnostic ignored "-Wincompatible-pointer-types"
          uint16_t *tmp2 = (free_ptr + 1); // priradenie
          #pragma GCC diagnostic pop
          *tmp2 = (uint16_t) size; //GLOB_MEM[pozicia+1] = (uint16_t) size; 

        // vynulovanie
        // NIE JE NUTNE, robi to ze uzivatelovi pride uplne prazdny blok pamate, dalo by sa to uplne vypustit z kodu
        // i zacina od 3 aby sa neprepisala hlavicka
        // prepise sa cela medzera v pamati, x slotov posunutych o prvu hlavicku
        for (int i = HLAVICKA; i < (velkost_free + HLAVICKA); i++) {
          *(free_ptr + i) = EMPTY;
        }

        printf ("ALOKACIA (5) PREBEHLA USPESNE, \n\talokovanych %d bitov\n", size);
        
        return (free_ptr + HLAVICKA); // ------------------------------- RETURN no. 5
      }

      // ak je miesta malo
      else {
        // ako case B
        volna_pamat --; // pri DEAD je to vzdy iba jeden slot !!
        pozicia ++; // skočíme za zabranú časť pamäte o jeden slot
      }
      //printf ("DEAD, zostava %d, free %d / %d\n", volna_pamat, velkost_free, size);

    }
  }

  // ak prejdeme pole a nenájde sa dosť miesta pre novu informáciu
  printf ("CHYBA - NEPODARILO SA ALOKOVAT PAMAT\n");
  if (free_ptr != NULL){
    printf ("\tchyba %d bitov / %d \n\n", (size - volna_pamat - velkost_free), size + HLAVICKA);
  }
  else {
    printf ("\tchyba %d bitov / %d \n\n", (size - volna_pamat + HLAVICKA), size + HLAVICKA);
  }
  fprintf (stderr, "Nepodarilo sa alokovat pamat\n");
  return NULL;
}

// free - DONE
int memory_free (void *valid_ptr) {
  // kvoli testom
  if (valid_ptr == NULL) {
    printf ("CHYBA - CHYBNY POINTER\n\n");
    fprintf (stderr, "Chybný pointer\n");
    return 0;
  }
  
  if (GLOB_MEM == NULL) { // ak nie je inicializovaná pamäť
    printf ("CHYBA - PAMAT NEBOLA INICIALIZOVANA\n\n");
    fprintf (stderr, "Pamäť nebola inicializovaná\n");
    return 0;
  }

  char *tmp = valid_ptr; // pretypovanie na pointer typu char
  if (*(tmp - HLAVICKA) == FREED) {
    printf ("CHYBA - PAMAT UZ BOLA UVOLNENA\n\n");
    fprintf (stderr, "Pamäť už bola uvoľnená\n");
    return 0;
  }

  *(tmp - HLAVICKA) = FREED; // zmena typu bloku na FREED v hlavicke (-3)

  // pocet slotov uzivatelskej pamate
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wincompatible-pointer-types"     
  uint16_t *tmp2 = (tmp-2);
  #pragma GCC diagnostic pop
  uint16_t pocet = *tmp2;
  
  // vynulovanie užívatelských informacií
  for (int i = 0; i < pocet; i++) {
    *(tmp+i) = EMPTY; 
    // prva informacia uzivatela zacina na (tmp+0) 
    // posledna je na (tmp+pocet-1)
  }

  printf ("Pamat uvolnena uspesne\n\n");
  return 1;
}

// check - DONE
int memory_check (void *ptr) {
  if (GLOB_MEM == NULL) { // ak nie je inicializovaná pamäť
    printf ("CHYBA - PAMAŤ NEBOLA INICIALIZOVANÁ\n\n");
    fprintf (stderr, "Pamäť nebola inicializovaná\n");
    return 0;
  }

  char *kontrolovany = ptr; // pretypovanie na pointer typu char
  unsigned int pozicia_bloku = MEMORY_HLAVICKA;

  // získanie veľkosti pamate
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wincompatible-pointer-types"
  uint16_t *velkost_pola = GLOB_MEM; // pomocný pointer, na pretypovanie GLOB
  #pragma GCC diagnostic pop

  while (pozicia_bloku < *velkost_pola) {

    // ak je FULL a je to ten isty
    if ((GLOB_MEM[pozicia_bloku] == FULL) && (&GLOB_MEM[pozicia_bloku + HLAVICKA] == kontrolovany)) {
      printf ("Pointer je aktívny\n\n");
      return 1;
    }
    // ak je to ten pointer ale nieje FULL
    else if ((GLOB_MEM[pozicia_bloku] != FULL) && (&GLOB_MEM[pozicia_bloku + HLAVICKA] == kontrolovany)) {
      printf ("Pointer nie je aktívny\n");
      return 0;
    }
    // ak narazi na DEAD
    else if (GLOB_MEM[pozicia_bloku] == DEAD) {
      pozicia_bloku++;
    }
    else {
      #pragma GCC diagnostic push
      #pragma GCC diagnostic ignored "-Wincompatible-pointer-types"     
      uint16_t *tmp = (GLOB_MEM + pozicia_bloku + 1);
      #pragma GCC diagnostic pop
      uint16_t velkost_bloku = *tmp;

      // posun o celu velkost bloku
      pozicia_bloku += (velkost_bloku + HLAVICKA);
    }
  }

  printf ("Pointer nie je aktívny\n");
  return 0;
}

// pomocna funkcia
void vypis () {
  if (GLOB_MEM == NULL) { // ak nie je inicializovaná pamäť
    printf ("CHYBA - PAMAŤ NEBOLA INICIALIZOVANÁ\n\n");
    fprintf (stderr, "Pamäť nebola inicializovaná\n");
    return;
  }

  // získanie veľkosti pamate
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wincompatible-pointer-types"
  uint16_t *velkost_pola = GLOB_MEM; // pomocný pointer, na pretypovanie GLOB
  #pragma GCC diagnostic pop

  for (int i=0; i < *velkost_pola; i++) {
    printf ("%u ", GLOB_MEM[i]);
  }

  return;
}

void test (int key, int uvolnovanie) {
  
  // získanie veľkosti pamate
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wincompatible-pointer-types"
  uint16_t *velkost_pamate = GLOB_MEM; 
  #pragma GCC diagnostic pop

  unsigned long pamat_pokus = 0;
  unsigned long pamat_ok = 0;

  int alokovanych_pokus = 0;
  int alokovanych_ok = 0;
  int uvolnenych = 0;

  // viac sa nezmesti blokov do 50 000 pola
  char *pole[7000] = {NULL};
  int i = 0;
  uint16_t size;
  uint16_t random_index;
  float percenta;

  while ( pamat_pokus < (*velkost_pamate - MEMORY_HLAVICKA) ) {

    // podla testu velkost blokov
    if (key == 1) {
      size = 23;
    }
    else if (key == 2) {
      size = (rand() % (24 - 8 + 1)) + 8;
    }
    else if (key == 3) {
      size = (rand() % (5000 - 500 + 1)) + 500;
    }
    else {
      size = (rand() % (50000 - 8 + 1)) + 8;
    }

    printf ("Skusana velkost bloku je %d -------\n\n", size);

    // pokus o alokaciu
    if (!(memory_check(pole[i]))) {
      pole[i] = (char *) memory_alloc(size);
      pamat_pokus += (size + HLAVICKA);
      alokovanych_pokus ++;
    }
    

    // kontrola uspesnosti
    if ( memory_check(pole[i]) ) {
      //printf ("%lu + %u\n", pamat_ok, size);
      pamat_ok += size;
      //printf ("%lu + %d\n", pamat_ok, HLAVICKA);
      pamat_ok += HLAVICKA;
      alokovanych_ok ++;
      //printf ("%lu\n", pamat_ok);
    }

    //printf ("alokovanych %d blokov z %d, (%d bytov z %d)\n\n", alokovanych_ok, alokovanych_pokus, pamat_ok, pamat_pokus);

    random_index = (rand() % (((i+1) - 1) - 0 + 1));
    //printf ("rand %d\n", random_index);

    if ( (uvolnovanie == 1) && (i != 0) && (i % 3 == 0) && (memory_free (pole[random_index]) ) ) {
      uvolnenych++;
    }


    if (i == 7000) { i = 0;}
    else { i++; }
  }

  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wformat="

  percenta = (float) alokovanych_ok / (float) alokovanych_pokus * 100;

  printf ("\nPocet alokovanych blokov: %d z %d (%.2lf%)\n", alokovanych_ok, alokovanych_pokus, percenta);

  percenta = (float) pamat_ok / (float) pamat_pokus * 100;

  printf ("Velkost alokovanej pamate %u bytov zo skusaných %u bytov (%.2lf%), \nv pamati o velkosti %u\n", pamat_ok, pamat_pokus, percenta, (*velkost_pamate - MEMORY_HLAVICKA));

  printf ("Pocet uvolnenych blokov: %d\n\n", uvolnenych);

  percenta = (float) pamat_ok / (float) (*velkost_pamate - MEMORY_HLAVICKA) * 100;

  printf ("USPESNOST %.2lf%\n\n ", percenta);

  #pragma GCC diagnostic pop
}

int main()
{
  char memory[40000]; // celkový blok pamäte 

  memory_init (memory, 40000); // inicializácia

  //#pragma GCC diagnostic push
  //#pragma GCC diagnostic ignored "-Wincompatible-pointer-types"
  //uint16_t *tmp = GLOB_MEM; // pomocný pointer, na pretypovanie GLOB
  //#pragma GCC diagnostic pop
  

  /*/ test

  char *pointer1 = (char *) memory_alloc(5);
  memory_check(pointer1);
  char *pointer2 = (char *) memory_alloc(2);
  memory_check(pointer2);

  memory_free(pointer1);
  pointer1 = (char *) memory_alloc(2);

  memory_free(pointer2);
  pointer2 = (char *) memory_alloc(4);

  memory_free(pointer2);
  memory_free(pointer1);

  pointer1 = (char *) memory_alloc(6);
  pointer2 = (char *) memory_alloc(1);

  memory_free(pointer2);
  memory_free(pointer1);
  
  pointer1 = (char *) memory_alloc(7); */

  test(3, 1);
  
  //vypis();


  
  return 0;
}