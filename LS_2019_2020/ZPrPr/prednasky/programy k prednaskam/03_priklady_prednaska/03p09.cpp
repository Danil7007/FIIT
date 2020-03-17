// vypisy (hodnoty pola, dvojnasobky a druhe mocniny)
// a charakteristiky hodnot pola (maximum, minimum, priemer)
// ukazka ukazovatelov vo funkciach
#include <stdio.h>
#include <stdlib.h>

int *alokuj(int pocet);
void nacitaj(int *pole, int pocet);
float priemer(int *pole, int pocet);
int *maximum(int pole[], int pocet);
void minimum(int pole[], int pocet, int *min);
void vypis(int pole[], int pocet, int (*p_f)(int x));

int identita(int x);
int mocnina(int x);
int dvojnasobok(int x);

int main()
{
   int *pole, n, min;

   printf("Zadajte pocet cisel: ");
   scanf("%d", &n);
   if ((pole = alokuj(n)) == NULL) {
      printf("Nepodarilo sa alokovat pole.\n");
      return 1;
   }
   nacitaj(pole, n); 
   printf("Nacitane pole: \n");
   vypis(pole, n, identita);
   printf("Dvojnasobky pola: \n");
   vypis(pole, n, dvojnasobok);
   printf("Druhe mocniny pola: \n");
   vypis(pole, n, mocnina);
   printf("Priemer je %.3f.\n", priemer(pole, n));
   printf("Maximum je %d.\n", *maximum(pole, n));
   minimum(pole, n, &min);
   printf("Minimum je %d.\n", min);

   free(pole);
   return 0;
}

int *alokuj(int pocet) {
   return (int *) malloc(pocet * sizeof(int));
}

void nacitaj(int *pole, int pocet) {
   int i;
   for(i = 0; i < pocet; i++) {
      printf("%d-te cislo: ", i);
      scanf("%d", pole + i);
   }
}

float priemer(int *pole, int pocet) {
   int i, suma = 0;
   for(i = 0; i < pocet; i++)
      suma += *(pole + i);
   return (float) suma / (float) pocet;
}

int *maximum(int pole[], int pocet) {
   int *p = pole, i;
   for(i = 1; i < pocet; i++) 
      if(*p < pole[i]) 
         p = pole + i;
   return p;
}

void minimum(int pole[], int pocet, int *min) {
   int i;
   *min = pole[0];
   for(i = 1; i < pocet; i++) 
      if(*min > pole[i]) 
         *min = pole[i];
}

void vypis(int pole[], int pocet, int (*p_f)(int x)) {
   int i;
   printf("* ");
   for(i = 0; i < pocet; i++)
      printf("%d * ", (*p_f)(pole[i]));
   printf("\n");
}

int identita(int x) {
   return x;
}

int mocnina(int x) {
   return x*x;
}

int dvojnasobok(int x) {
   return 2*x;
} 

