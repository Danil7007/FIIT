#include <stdio.h>

int GenNthPrime(int n)
{
    int i,j,count=0,flag=0;

    for(i=2; i>0; i++)
    {
        flag=0;
        for(j=2; j<i; j++)
        {
            if(i%j==0)
            {
                flag=1;
                break;
            }
        }
        if(flag==0)
        {
            count++;

        }
        if(count==n)
        {
            printf("%d\n",i);
            break;
        }

    }
  return 0;
}

int main()
{
    int n;

    while (scanf("%d",&n) > 0 ) {
      GenNthPrime(n);///call the function
    }

    return 0;
}