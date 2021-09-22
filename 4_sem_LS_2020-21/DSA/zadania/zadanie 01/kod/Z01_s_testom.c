// Zadanie 1 - Správca pamäti -- Emma Macháčová, 17.2.2021 14:26

// keďže pracujeme s pamäťou priamo budú nastávať konverzie o ktorých si kompiler bude myslieť že niesu správne, ale do pola vkladáme diagnostické informácie ktoré potrebujeme čítať, meníme veci ktoré nie su kompatibilné tak, aby to kompatibilné bolo na niektorých miestach je použité #pragma GCC diagnostic ignored "-Wincompatible-pointer-types"

#include <stdio.h>
#include <stdint.h> // na uint16_t
#include <string.h> // pre memset do memory_init

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

// inicializácia pamäte - DONE
void memory_init (void *ptr, unsigned int size) {
  if (size < MEMORY_HLAVICKA) {return;} // pokial nie je možné ani zapísať veľkosť pola

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
    printf ("CHYBA - PAMAŤ NEBOLA INICIALIZOVANÁ\n\n");
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
  char *free_prt = NULL; // pointer na prvú medzeru
  int pocet_free = 0; // pocet medzier
  int velkost_free = 0; // velkost pamate medzier

  // kym je v pamati priestor pre uzivatelske info; - 3 pre hlavicku novej info
  while ( 0 < (volna_pamat - HLAVICKA) && (volna_pamat - HLAVICKA) >= size ) { 

    //printf ("volna pamat %d size %d\n", (volna_pamat-3), size);

    // case A - narazíme na nepoužitú voľnú pamäť - EMPTY ---------------------------
    if (GLOB_MEM[pozicia] == EMPTY) { 
      
      // ak nepredchádza blok uvolnenenj pamate
      if (free_prt == NULL) {
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

        printf ("ALOKÁCIA (1) PREBEHLA ÚSPEŠNE, \n\talokovaných %d bitov od pozície %d\n", size, pozicia);

        // minus size informacie (tmp) a 3 pre head
        volna_pamat -= (*tmp + HLAVICKA); 
        //printf ("\tzostávajúca pamäť %d bitov\n\n", volna_pamat);
        
        return (GLOB_MEM + pozicia + HLAVICKA); // pointer na prvý slot volnej pamäte ---- RETURN no. 1
      }

      // ak je predtým medzera
      else {
        *free_prt = FULL;

        // informácia o velkosti bloku 
          #pragma GCC diagnostic push
          #pragma GCC diagnostic ignored "-Wincompatible-pointer-types"
          uint16_t *tmp2 = (free_prt + 1); // priradenie
          #pragma GCC diagnostic pop
          *tmp2 = (uint16_t) size; //GLOB_MEM[pozicia+1] = (uint16_t) size; 

        // vynulovanie
        // NIE JE NUTNE, robi to ze uzivatelovi pride uplne prazdny blok pamate, dalo by sa to uplne vypustit z kodu
        //printf ("\n%d\n", (velkost_free + 3));
        // i zacina od 3 aby sa neprepisala hlavicka
        // prepise sa cela medzera v pamati, x slotov posunutych o prvu hlavicku
        for (int i = HLAVICKA; i < (velkost_free + HLAVICKA); i++) {
          *(free_prt + i) = EMPTY;
        }

        printf ("ALOKÁCIA (2) PREBEHLA ÚSPEŠNE, \n\talokovaných %d bitov \n\n", size);
        
        //printf ("%d\n", *(free_prt + HLAVICKA));
        return (free_prt + HLAVICKA);
        //return (GLOB_MEM + pozicia + HLAVICKA); // ------------------------------- RETURN no. 2
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
      free_prt = NULL;
      pocet_free = 0;
      velkost_free = 0;
    }

    // case C - narazíme na uvolnený blok pamäte - FREED ----------------------------
    else if (GLOB_MEM[pozicia] == FREED) {
      #pragma GCC diagnostic push
      #pragma GCC diagnostic ignored "-Wincompatible-pointer-types"
      uint16_t *tmp = (GLOB_MEM + pozicia + 1); // velkost bloku medery
      #pragma GCC diagnostic pop

      // ak je to prvá medzera
      if (free_prt == NULL) {
        free_prt = (GLOB_MEM + pozicia);
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
        *free_prt = FULL;

        // informácia o velkosti bloku 
          #pragma GCC diagnostic push
          #pragma GCC diagnostic ignored "-Wincompatible-pointer-types"
          uint16_t *tmp2 = (free_prt + 1); // priradenie
          #pragma GCC diagnostic pop
          *tmp2 = (uint16_t) size; //GLOB_MEM[pozicia+1] = (uint16_t) size; 

        // vynulovanie
        // NIE JE NUTNE, robi to ze uzivatelovi pride uplne prazdny blok pamate, dalo by sa to uplne vypustit z kodu
        //printf ("\n%d\n", (velkost_free + 3));
        // i zacina od 3 aby sa neprepisala hlavicka
        // prepise sa cela medzera v pamati, x slotov posunutych o prvu hlavicku
        for (int i = HLAVICKA; i < (velkost_free + HLAVICKA); i++) {
          *(free_prt + i) = EMPTY;
        }

        printf ("ALOKÁCIA (3) PREBEHLA ÚSPEŠNE, \n\talokovaných %d bitov od pozície %d\n\n", size, pozicia);
        
        return (free_prt + HLAVICKA);
        //return (GLOB_MEM + pozicia + HLAVICKA); // ------------------------------- RETURN no. 3
      }

      // ak je miesta viac
      else if (velkost_free > size) {
        *free_prt = FULL; // zmena typu

        // informácia o velkosti bloku 
          #pragma GCC diagnostic push
          #pragma GCC diagnostic ignored "-Wincompatible-pointer-types"
          uint16_t *tmp2 = (free_prt + 1); // priradenie
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
            *(free_prt + i) = EMPTY;
          }
          // sloty ktore si nevyziadal
          else {
            *(free_prt + i) = DEAD; // sloty navyse
          }
          
        }

        printf ("ALOKÁCIA (4) PREBEHLA ÚSPEŠNE, \n\talokovaných %d bitov od pozície %d\n\n", size, pozicia);

        return (free_prt + HLAVICKA);
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
      if (free_prt == NULL) {
        free_prt = (GLOB_MEM + pozicia); // priradenie pointra
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
        *free_prt = FULL;

        // informácia o velkosti bloku 
          #pragma GCC diagnostic push
          #pragma GCC diagnostic ignored "-Wincompatible-pointer-types"
          uint16_t *tmp2 = (free_prt + 1); // priradenie
          #pragma GCC diagnostic pop
          *tmp2 = (uint16_t) size; //GLOB_MEM[pozicia+1] = (uint16_t) size; 

        // vynulovanie
        // NIE JE NUTNE, robi to ze uzivatelovi pride uplne prazdny blok pamate, dalo by sa to uplne vypustit z kodu
        //printf ("\n%d\n", (velkost_free + 3));
        // i zacina od 3 aby sa neprepisala hlavicka
        // prepise sa cela medzera v pamati, x slotov posunutych o prvu hlavicku
        for (int i = HLAVICKA; i < (velkost_free + HLAVICKA); i++) {
          *(free_prt + i) = EMPTY;
        }

        printf ("ALOKÁCIA (5) PREBEHLA ÚSPEŠNE, \n\talokovaných %d bitov\n\n", size);
        
        return (free_prt + HLAVICKA);
        //return (GLOB_MEM + pozicia + HLAVICKA); // ------------------------------- RETURN no. 5
      }

      // ak je miesta malo
      else {
        // ako case B
        //#pragma GCC diagnostic push
        //#pragma GCC diagnostic ignored "-Wincompatible-pointer-types"
        //uint16_t* tmp = (GLOB_MEM + pozicia + 1);
        //#pragma GCC diagnostic pop

        volna_pamat --; // pri DEAD je to vzdy iba jeden slot !!
        pozicia ++; // skočíme za zabranú časť pamäte o jeden slot
      }

    }
  }

  /*
  printf ("%u\n", *velkost_pamate);
  printf ("%u\n", volna_pamat);
  break;
  */

  // ak prejdeme pole a nenájde sa dosť miesta pre novu informáciu
  printf ("CHYBA - NEPODARILO SA ALOKOVAŤ PAMAŤ\n");
  printf ("\tchýba %d bitov / %d \n\n", (size - volna_pamat + HLAVICKA), size);
  //fprintf (stderr, "Nepodarilo sa alokovať pamäť\n");
  return NULL;
}

// free - DONE
int memory_free (void *valid_ptr) {
  if (GLOB_MEM == NULL) { // ak nie je inicializovaná pamäť
    //printf ("CHYBA - PAMAŤ NEBOLA INICIALIZOVANÁ\n\n");
    //fprintf (stderr, "Pamäť nebola inicializovaná\n");
    return 0;
  }

  char *tmp = valid_ptr; // pretypovanie na pointer typu char
  if (*(tmp - HLAVICKA) == FREED) {
    //printf ("CHYBA - PAMAŤ UŽ BOLA UVOĽNENÁ\n\n");
    //fprintf (stderr, "Pamäť už bola uvoľnená\n");
    return 0;
  }

  *(tmp - HLAVICKA) = FREED; // zmena typu bloku na FREED v hlavicke (-3)
  int pocet = *(tmp - 2); // pocet slotov uzivatelskej pamate
  
  // vynulovanie užívatelských informacií
  for (int i = 0; i < pocet; i++) {
    *(tmp+i) = 0; 
    // prva informacia uzivatela zacina na (tmp+0) 
    // posledna je na (tmp+pocet-1)
  }

  //printf ("%d\n", *(tmp-3));
  //printf ("Pamäť uvolnená úspešne\n\n");
  return 1;
}

int memory_check (void *ptr) {
  if (GLOB_MEM == NULL) { // ak nie je inicializovaná pamäť
    //printf ("CHYBA - PAMAŤ NEBOLA INICIALIZOVANÁ\n\n");
    //fprintf (stderr, "Pamäť nebola inicializovaná\n");
    return 0;
  }

  char *kontrolovany = ptr; // pretypovanie na pointer typu char
  int pozicia_bloku = MEMORY_HLAVICKA;
  int size = GLOB_MEM[0];

  //printf ("%d\n", GLOB_MEM[pozicia_bloku + 1]);

  while ((pozicia_bloku + HLAVICKA) <= size) {

    // ak je FULL a je to ten isty
    if ( (&GLOB_MEM[pozicia_bloku + HLAVICKA] == kontrolovany) && (GLOB_MEM[pozicia_bloku] == FULL) ) {
      //printf ("Pointer je valídny\n\n");
      return 1;
    }
    // ak je to ten pointer ale nieje FULL
    else if ((GLOB_MEM[pozicia_bloku] != FULL) && (&GLOB_MEM[pozicia_bloku + HLAVICKA] == kontrolovany)) {
      //printf ("Pointer NIE JE valídny\n\n");
      return 0;
    }

    else {
      // posun 
      //pozicia_bloku += (GLOB_MEM[pozicia_bloku + 1] + HLAVICKA);
      pozicia_bloku++;
    }
  }

  //printf ("Pointer NIE JE valídny\n\n");
  return 0;
}

/*int main()
{
  char memory[50]; // celkový blok pamäte 

  memory_init (memory, 50); // inicializácia

  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wincompatible-pointer-types"
  uint16_t *tmp = GLOB_MEM; // pomocný pointer, na pretypovanie GLOB
  #pragma GCC diagnostic pop


  // test
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wunused-variable"

  char *pointer = (char *) memory_alloc(10); // alokovanie bloku veľkosti x

  memory_check (pointer);

  //char *pointer2 = (char *) memory_alloc(10); 

  //char *pointer3 = (char *) memory_alloc(5); 

  //char *pointer4 = (char *) memory_alloc(3); 
  //char *pointer5 = (char *) memory_alloc(10); 

  //char *pointer6 = (char *) memory_alloc(700); 

  memory_free (pointer);
  
  //memory_free (pointer4);
  //memory_free (pointer5);

  //printf ("po uvolneni: %d\n", *(pointer3-3));

  char *pointer7 = (char *) memory_alloc(10); 

  memory_check(pointer7);

  memory_free (pointer7);

  memory_check(pointer7);

  char *pointer30 = NULL;

  memory_check (pointer30);

  pointer = (char *) memory_alloc(16);
  memory_check (pointer);


  char *pointer8 = (char *) memory_alloc(1);
  char *pointer9 = (char *) memory_alloc(6);

  //memory_free (pointer2);
  char *pointer10 = (char *) memory_alloc(6);
  pointer = (char *) memory_alloc(8);
  
  //printf ("%u\n", *tmp);

  for (int i=0; i<50; i++) {
    printf ("%d ", memory[i]);
  }

  return 0;
}*/

void z1_testovac(char *region, char **pointer, int minBlock, int maxBlock, int minMemory, int maxMemory, int testFragDefrag) {
    unsigned int allocated = 0;
    unsigned int mallocated = 0;
    unsigned int allocated_count = 0;
    unsigned int mallocated_count = 0;
    unsigned int i = 0;
    int random_memory = 0;
    int random = 0;
    memset(region, 0, 100000);
    random_memory = (rand() % (maxMemory-minMemory+1)) + minMemory;
    memory_init(region + 500, random_memory);
    if (testFragDefrag) {
        do {
            pointer[i] = memory_alloc(8);
            if (pointer[i])
                i++;
        } while (pointer[i]);
        for (int j = 0; j < i; j++) {
            if (memory_check(pointer[j])) {
                memory_free(pointer[j]);
            }
            else {
                printf("Error: Wrong memory check (1).\n");
            }
        }
    }
    i = 0;
    while (allocated <= random_memory-minBlock) {
        random = (rand() % (maxBlock-minBlock+1)) + minBlock;
        if (allocated + random > random_memory)
            continue;
        allocated += random;
        allocated_count++;
        pointer[i] = memory_alloc(random);
        if (!(memory_check(pointer[i]))) {
          printf("Error: Wrong memory check (2).\n\n");
        }
        if (pointer[i]) {
            i++;
            mallocated_count++;
            mallocated += random;
        }
    }
    /*for (int j = 0; j < i; j++) {
        if (memory_check(pointer[j])) {
            memory_free(pointer[j]);
        }
        else {
            printf("Error: Wrong memory check (2).\n");
        }
    }*/
    memset(region + 500, 0, random_memory);
    for (int j = 0; j < 100000; j++) {
        if (region[j] != 0) {
            region[j] = 0;
            printf("Error: Modified memory outside the managed region. index: %d\n",j-500);
        }
    }
    float result = ((float)mallocated_count / allocated_count) * 100;
    float result_bytes = ((float)mallocated / allocated) * 100;
    printf("Memory size of %d bytes: allocated %.2f%% blocks (%.2f%% bytes).\n\n", random_memory, result, result_bytes);
}

int main() {
    char region[100000];
    char* pointer[13000];
    z1_testovac(region, pointer, 8, 24, 50, 100, 1);
    z1_testovac(region, pointer, 8, 1000, 10000, 20000, 0);
    z1_testovac(region, pointer, 8, 35000, 50000, 99000, 0);
    return 0;
}
