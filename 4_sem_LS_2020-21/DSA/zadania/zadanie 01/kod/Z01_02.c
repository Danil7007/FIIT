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

// globálny ukazovateľ na pamať pre memory_init
char *GLOB_MEM;

// deklarácie funkcií
void *memory_alloc (unsigned int size); // služby analogické malloc
int memory_free (void *valid_ptr); // uvoľnenie vyhradeného bloku pamäti
int memory_check (void *ptr); // skontrolovanie je ukazovateľ platný 
void memory_init (void *ptr, unsigned int size); // inicializácia pamäte

// inicializácia pamäte
void memory_init (void *ptr, unsigned int size) {
  if (size < 2) {return;} // pokial nie je možné ani zapísať veľkosť pola

  GLOB_MEM = ptr; // priradenie vyhradenej pamäte a globálneho ukazovateľa

  // vynulovanie pamäte; +2 lebo na začiatok pôjde informácia o veľkosti poľa
  memset((GLOB_MEM + 2), 0, size); 

  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wincompatible-pointer-types"
  uint16_t *pomocny_pointer = GLOB_MEM; // pomocný pointer, na pretypovanie GLOB
  #pragma GCC diagnostic pop
  *pomocny_pointer = (uint16_t) size; // veľkosť pamäte v prekonvertovanom tvare

  return;
}

// alokácia
void *memory_alloc (unsigned int size) {
  if (GLOB_MEM == NULL) { // ak nie je inicializovaná pamäť
    printf ("Pamäť nebola inicializovaná\n");
    fprintf (stderr, "Pamäť nebola inicializovaná\n");
    return NULL;
  }

  // získanie veľkosti pamate
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wincompatible-pointer-types"
  uint16_t *velkost_pamate = GLOB_MEM; // pomocný pointer, na pretypovanie GLOB
  #pragma GCC diagnostic pop

  // aktualne miesto v pamati; 2 lebo na zaciatku mame hlavicku celeho pola
  uint16_t volna_pamat = *(velkost_pamate) - 2;
  int pozicia = 2; // od indexu 2 začína pamäť
  char *fuga = NULL;
  int velkost_fugy = 0;
  int hlavicky_fug = 0;

  // kym je v pamati priestor pre uzivatelske info; - 3 pre hlavicku novej info
  while ( 0 < (volna_pamat - 3) && (volna_pamat - 3) >= size ) { 

    //printf ("volna pamat %d size %d\n", (volna_pamat-3), size);

    // case A - narazíme na nepoužitú voľnú pamäť - EMPTY --------------------------
    if (GLOB_MEM[pozicia] == EMPTY) { 
      
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
      volna_pamat -= (*tmp + 3); 
      printf ("\tzostávajúca pamäť %d bitov\n\n", volna_pamat);
      
      return (GLOB_MEM+pozicia+3); // pointer na prvý slot volnej pamäte ---- RETURN no. 1
    }

    // case B - narazíme na už zabraný blok pamäte - FULL --------------------------
    else if (GLOB_MEM[pozicia] == FULL) {
      // odpočítame od pamäte veľkosť zabratého bloku, tento údaj je na [pozicia+1]
      // a odpocitame aj miesto co zabera hlavicka
      #pragma GCC diagnostic push
      #pragma GCC diagnostic ignored "-Wincompatible-pointer-types"
      uint16_t* tmp = (GLOB_MEM + pozicia + 1);
      volna_pamat -= (*tmp + 3); // 3 pre hlavičku ----------------- PAMAT !!!
      //printf (" -> na pozicii %d sa nachádza blok veľkosti %d;\n", pozicia, *tmp);
      pozicia += (*tmp + 3); // skočíme za zabranú časť pamäte
      //printf (" -> presúvam sa na pozíciu %d\n", pozicia);
      #pragma GCC diagnostic pop
    }

    // case C - narazíme na uvolnený blok pamäte - FREED ---------------------------
    else if (GLOB_MEM[pozicia] == FREED) {
      #pragma GCC diagnostic push
      #pragma GCC diagnostic ignored "-Wincompatible-pointer-types"
      uint16_t* tmp = (GLOB_MEM + pozicia + 1); // velkost bloku
      #pragma GCC diagnostic pop

      // ak sa využije celý blok
      if (*tmp + velkost_fugy == size){
        GLOB_MEM[pozicia] = FULL;
        // informácia o velkosti bloku sa nemení
        printf ("ALOKÁCIA (2) PREBEHLA ÚSPEŠNE, \n\talokovaných %d bitov od pozície %d\n\n", size, pozicia);
        return (GLOB_MEM+pozicia+3); // ------------------------------- RETURN no. 2
      }

      // ak je viac pamate ako je treba užívateľovi
      else if (*tmp + velkost_fugy > size) {
        int rozdiel = (*tmp + velkost_fugy) - size; // zbytočných slotov

        if (fuga == NULL) {
          GLOB_MEM[pozicia] = FULL; // zmena typu
          // zmena informácie o veľkosti zabraného bloku pamäte
          #pragma GCC diagnostic push
          #pragma GCC diagnostic ignored "-Wincompatible-pointer-types"
          uint16_t *tmp2 = (GLOB_MEM + pozicia + 1); // priradenie
          #pragma GCC diagnostic pop
          *tmp2 = (uint16_t) size; //GLOB_MEM[pozicia+1] = (uint16_t) size; 
        }
        else {
          *fuga = FULL; // zmena typu
          // informácia o velkosti bloku 
          #pragma GCC diagnostic push
          #pragma GCC diagnostic ignored "-Wincompatible-pointer-types"
          uint16_t *tmp2 = (fuga + 1); // priradenie
          #pragma GCC diagnostic pop
          *tmp2 = (uint16_t) size; //GLOB_MEM[pozicia+1] = (uint16_t) size; 

          // vynulovanie a prepis na DEAD
          int j = (*tmp + velkost_fugy + hlavicky_fug);
          printf ("%d\n", j);
          for (int i = 0; i < j; i++) {
            *(fuga+3+i) = DEAD;
            
          }

        }

        //for (int i = 0; i < rozdiel; i++) {
          // GLOB_MEM[pozicia] je zaciatok hlavicky
          // GLOB_MEM[pozicia+3] je zaciatok uzivatelskej info (hlavicka = 3 sloty)
          // GLOB_MEM[pozicia+3+size] je prvy nepotrebny slot, je ich +0 az rozdiel
          //GLOB_MEM[pozicia+3+size+i] = DEAD;
        //}

        printf ("ALOKÁCIA (3) PREBEHLA ÚSPEŠNE, \n\talokovaných %d bitov od pozície %d\n\n", size, pozicia);
        return (GLOB_MEM+pozicia+3); // ------------------------------- RETURN no. 3
      }

      // ak sa sem užívatelova požiadavka nezmestí
      else if (*tmp + velkost_fugy < size) {
        if (fuga == NULL) {
          fuga = (GLOB_MEM + pozicia); // fuga ukazuje na hlavicku FREED bloku
          velkost_fugy += *tmp; // velkost prvej fugy
          hlavicky_fug = 3;
        }
        else {
          hlavicky_fug += 3;
        }
        
        //printf("\n%d\n", velkost_fugy);

        // tak ako v case B
        volna_pamat -= (*tmp + 3); // 3 pre hlavičku ----------------- PAMAT !!!
        pozicia += (*tmp + 3); // skočíme za túto časť pamäte
        //printf (" -> presúvam sa na pozíciu %d\n", pozicia);
      }

      
    }

  }

  /*
  printf ("%u\n", *velkost_pamate);
  printf ("%u\n", volna_pamat);
  break;
  */

  // ak prejdeme pole a nenájde sa dosť miesta pre novu informáciu
  printf ("NEPODARILO SA ALOKOVAŤ PAMAŤ\n");
  printf ("\tchýba %d bitov zo %d\n", (size - volna_pamat + 3), size);
  fprintf (stderr, "Nepodarilo sa alokovať pamäť\n");
  return NULL;
}

// free
int memory_free (void *valid_ptr) {
  if (GLOB_MEM == NULL) { // ak nie je inicializovaná pamäť
    printf ("Pamäť nebola inicializovaná\n");
    fprintf (stderr, "Pamäť nebola inicializovaná\n");
    return 0;
  }

  char *tmp = valid_ptr; // pretypovanie na pointer typu char
  *(tmp-3) = FREED; // zmena typu bloku na FREED v hlavicke (-3)

  int pocet = *(tmp-2); // pocet slotov uzivatelskej pamate
  
  // vynulovanie užívatelských informacií
  for (int i = 0; i < pocet; i++) {
    *(tmp+i) = 0; 
    // prva informacia uzivatela zacina na (tmp+0) 
    // posledna je na (tmp+pocet-1)
  }

  //printf ("%d\n", *(tmp-3));
  printf ("Pamäť uvolnená úspešne\n\n");
  return 1;
}


int main()
{
  char memory[25]; // celkový blok pamäte 
  
  memory_init (memory, 25); // inicializácia
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wincompatible-pointer-types"
  uint16_t *tmp = GLOB_MEM; // pomocný pointer, na pretypovanie GLOB
  #pragma GCC diagnostic pop


  // test
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wunused-variable"

  char *pointer = (char *) memory_alloc(2); // alokovanie bloku veľkosti 10
  char *pointer2 = (char *) memory_alloc(1); 
  char *pointer3 = (char *) memory_alloc(5); 
  char *pointer4 = (char *) memory_alloc(3); 
  //char *pointer5 = (char *) memory_alloc(19000); 
  //char *pointer6 = (char *) memory_alloc(700); 

  memory_free (pointer);
  memory_free (pointer2);
  memory_free (pointer3);
  //printf ("po uvolneni: %d\n", *(pointer3-3));

  char *pointer7 = (char *) memory_alloc(5); 

  //pointer = (char *) memory_alloc(3);

  

  
  //printf ("%u\n", *tmp);

  for (int i=0; i<25; i++) {
    printf ("%d ", memory[i]);
  }

  return 0;
}