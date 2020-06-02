#include <stdio.h>
 
int main()
{
  int n, i,  c, a = 1;
 
  scanf("%d", &n);

  if (0>n>11) {
  
    for (i = 1; i <= n; i++)
    {
      for (c = 1; c <= i; c++)
      {
        printf("%d ",a);
        a++;
      }
      printf("\n");
    }
  }
  else {
    printf ("Nespravny vstup");
  }

  return 0;
}