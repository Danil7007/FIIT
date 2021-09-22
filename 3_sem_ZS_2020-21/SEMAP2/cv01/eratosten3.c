#include <stdio.h>

int prvocisla[100000], hladam[100000], pocet=0;

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
            prvocisla[count] = i;
            //printf("%d\n",i);
            count++;

        }
        if(count==n)
        {
            //printf("%d\n",i);
            break;
        }

    }
  return 0;
}

int main()
{
    int n, max=0, i, index;

    while (scanf("%d",&n) > 0 ) {
      hladam[pocet] = n;
      pocet++;
    }

    for (i=0; i < pocet; i++) {
      if (hladam[i] > max) {
        max = hladam[i];
      }
    }

    GenNthPrime(max);

    for (i=0; i < pocet; i++) {
      index = hladam[i] - 1;
      printf ("%d\n", prvocisla[index]);
    }

    return 0;
}