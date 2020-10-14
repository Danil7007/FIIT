#include <stdio.h> 
  
// FAKTORIAL
unsigned long int factorial(unsigned int n) { 
  unsigned long int res = 1; 
  
  for (int i = 1; i <= n; ++i) { 
    res *= i; 
  } 
  
  return res; 
} 
  
unsigned long int binomialCoeff(unsigned int n, unsigned int k) { 
  unsigned long int res = 1; 
  
  // C(n, k) = C(n, n-k) 
  if (k > n - k) 
    k = n - k; 
  
  // [n*(n-1)*---*(n-k+1)] / [k*(k-1)*---*1] 
  for (int i = 0; i < k; ++i) { 
    res *= (n - i); 
    res /= (i + 1); 
  } 
  
  return res; 
} 
  
// A Binomial coefficient based function to find nth catalan 
// number in O(n) time 
unsigned long int catalan(unsigned int n) { 
  // Calculate value of 2nCn 
  unsigned long int c = binomialCoeff(2*n, n); 
  
  // return 2nCn/(n+1) 
  return c/(n+1); 
} 
  
// A function to count number of BST with n nodes  
// using catalan 
unsigned long int pocetStromov(unsigned int n) { 
  // find nth catalan number 
  unsigned long int count = catalan(n); 
  
  // return nth catalan number 
  return count; 
} 
  
// A function to count number of binary trees with n nodes  
unsigned long int countBT(unsigned int n) { 
  // find count of BST with n numbers 
  unsigned long int count = catalan(n); 
  
  // return count * n! 
  return count * factorial(n); 
} 
  

int main() { 
  int pocet, n; 
  
  while (scanf ("%d", &n) > 0) {
    
    if (n > 0) {
      pocet = pocetStromov(n);
      printf ("%d\n", pocet);
    }
    else {
      printf ("0\n");
    }  
  }
  
  
  return 0; 
}