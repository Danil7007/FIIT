// histogram
#include<stdio.h>
#include<ctype.h>

#define SUBOR "pismena.txt"
#define N 'Z' - 'A' + 1    /* pocet pismen abecedy */

int main()
{
   int c, i, hist[N];
   FILE *fr;

   if((fr = fopen(SUBOR, "r")) == NULL) {
      printf("Subor sa nepodarilo otvorit.\n");
      return 1;
   }

   for (i=0; i<N; i++) 
      hist[i] = 0;

   while ((c = toupper(getc(fr))) != EOF) {
      if(c >= 'A' && c <= 'Z') 
          hist[c - 'A']++;
   }
   for (i=0; i<N; i++) 
      if (hist[i] != 0) 
         printf("%c: %2d\n", 'A' + i, hist[i]);

   if(fclose(fr) == EOF) {
      printf("Subor sa nepodarilo zatvorit.\n");
      return 1;
   }

   return 0;
}

