//#include <stdio.h>

// int main()
//{
//  int a,i,count;
//  scanf("%d",&a);
//  int p[a];
//  for(i=0;i<a;i++)
//  {
//    scanf("%d",&p[i]);
//    p[i] > 0 && p[i] <= 100 ? count++ : (count=count);  
//  }
//  printf("%d",count);
//  return 0;
//}

// uloha4-2.c -- Emma Macháčová, 14.10.2019 14:24

#include <stdio.h>

int main() {
  int n, i, sucet;
  scanf ("%d", &n);
  int pole[n];

  for (i = 0; i < n; i++) {
    scanf ("%d", &pole[i]);
  }

  for (i = 0; i < n; i++) {
    if (0 < pole[i] && pole[i] <= 100) {
      sucet += 1;
    }
  }

  printf ("%d", sucet);

  return 0;
}