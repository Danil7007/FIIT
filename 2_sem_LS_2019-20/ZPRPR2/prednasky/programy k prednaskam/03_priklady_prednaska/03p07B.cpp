#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int porovnaj_vzost (const void *a, const void *b) {
   return (*(int*)a - *(int*)b);
}

int main() {
   int *a, *b, na, nb, ia, ib, i, n;
   srand(time(NULL));

   printf("Zadajte pocet prvkov prveho pola: ");
   scanf("%d", &na);
   if((a = (int *) malloc(na * sizeof(int))) == NULL)
      exit(1);
   for(i = 0; i < na; i++)
      a[i] = rand() % 100;   /* pomocou indexov */
   qsort(a, na, sizeof(int), porovnaj_vzost);

   printf("Zadajte pocet prvkov druheho pola: ");
   scanf("%d", &nb);
   if((b = (int *) malloc(nb * sizeof(int))) == NULL)
      exit(1);
   for(i = 0; i < nb; i++)
      *(b + i) = rand() % 100; /* pomocou ukazovatelov */
   qsort(b, nb, sizeof(int), porovnaj_vzost);

   printf("Pole a: \n");
   for(i=0; i < na; i++)
      printf("%d, ", *(a + i)); /* pomocou ukazovatelov */
   printf("\n");
  
   printf("Pole b: \n");
   for(i=0; i < nb; i++)
      printf("%d, ", b[i]);     /* pomocou indexov */
   printf("\n");

   a = (int *) realloc(a, (na+nb) * sizeof(int));

   ia = na-1;
   ib = nb-1;
   for(n = na+nb-1; n>=0; n--) 
	  	if(ia >= 0 && ib >= 0)
			if(a[ia] >= b[ib])
         		a[n] = a[ia--];
      		else
         		a[n] = b[ib--];
		else if (ib >= 0)
			a[n] = b[ib--];

   n = na+nb;
   printf("Pole a (spojene): \n");
   for(i=0; i<n; i++)
      printf("%d, ", a[i]);

   return 0;
}  

