// matice: vypis s ukazovatelom
// nacitanie vypis 3 matic
// vypis cez ukazovatel na 2D pole organizovane po N stlpcov
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define N 3
#define SUBOR "matice.txt"

void nacitaj(int m1[][N], int m2[][N], int m3[][N]);
void vypis(int m1[][N], int m2[][N], int m3[][N]);


int main()
{
   	int c, m1[N][N], m2[N][N], m3[N][N];
   	char f_meno[50];

   	nacitaj(m1, m2, m3);
   	vypis(m1, m2, m3); 
	return 0;
}

int nacitaj_pom(int m[][N], FILE *f) 
{
   int i, j;

   for (i=0; i<N; i++) 
      for (j=0; j<N; j++)
         if (fscanf(f, "%d", &m[i][j]) != 1) 
            return 1;
   return 0;
}  

void nacitaj(int m1[][N], int m2[][N], int m3[][N])
{
   FILE *f;

   if ((f = fopen(SUBOR, "r")) == NULL) {
      printf("Subor %s sa nepodarilo otvorit.\n", SUBOR);
      exit(1);
   }

   if(nacitaj_pom(m1, f) || nacitaj_pom(m2, f) || 
      nacitaj_pom(m3, f)) {
      printf("Nepodarilo sa nacitat matice.\n");
	exit(1);
   }

   if (fclose(f) == EOF) 
      printf("Subor sa nepodarilo zatvorit.\n");
}
   


void vypis(int m1[][N], int m2[][N], int m3[][N]) {
   int i, j, k, (*m)[N];	// vyuzitie ukazovatela m na 2D pole organizovane do N stlpcov

   	for (k=0; k<3; k++) {
      	switch (k) {
      		case 0: m = m1; break;
      		case 1: m = m2; break;
      	case 2: m = m3; break;
    	}
    
	   	printf("Matica c.%d:\n", k+1);
	    for (i=0; i<N; i++) {
	       	for (j=0; j<N; j++)
	           	printf("%d ", m[i][j]);
	       	putchar('\n');
      	}
    	printf("\n");
   }
}

