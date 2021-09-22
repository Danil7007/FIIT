#include <stdio.h>
#include <string.h>

long unsigned pole[35];

// using recursive approach to find the catalan number
unsigned long int catalan(unsigned int n) {
   // Base case
   if (n <= 1) return 1;
   // catalan(n) is sum of catalan(i)*catalan(n-i-1)
   unsigned long int res = 0;
   for (int i=0; i<n; i++)
      res += catalan(i)*catalan(n-i-1);
   
   pole[n] = res;
   return res;
}


int main() {
  int n, i;
  
  memset (pole, 0, 34);


  while (scanf ("%d", &n) > 0 ) {
    if (pole[n] != 0) {
      printf("%ld\n", pole[n]);
    }
    else {
      printf("%ld\n", catalan(n));
    } 
  }

   return 0;
}