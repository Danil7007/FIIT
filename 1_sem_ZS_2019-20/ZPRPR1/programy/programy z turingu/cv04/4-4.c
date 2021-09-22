// uloha4-2.c -- Emma Macháčová, 14.10.2019 14:24

#include <stdio.h>

int main()
{
  int f,g,i;
  scanf("%d %d",&f,&g);
  for(i=f;i<=g;i++)
  {
    if(i % 3 == 0)
    {
      printf("%d ",i);
    }
  }
  return 0;
}