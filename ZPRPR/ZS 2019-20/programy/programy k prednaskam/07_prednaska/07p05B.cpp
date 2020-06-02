// pouzitie 2 smernikov
#include <stdio.h>

int main() 
{
   int i = 5, j = 7; 
   int *p, *q;
   
   p = &i;
   q = &j;
   printf("hodnoty - *p: %d, *q: %d\n\n", *p, *q);
   
   p = q;
   printf("Priradenie adresy:\n");
   printf("hodnoty - *p: %d, *q: %d\n", *p, *q);
   printf("adresy  - p: %p, q: %p\n", p, q);
          
   return (0); 
} 
