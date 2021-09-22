// uloha1-2.c -- Emma Macháčová, 24.9.2020 20:54

#include <stdio.h>

int main(void){
    int n, i, flag, prime;
    int counter = 1;

    while (scanf("%d", &n) > 0) {

    if (n < 0) {
      return 0;
    }
    if (n == 1)
        prime = 2;
    else {
        prime = 1;
        do{
            prime += 2;
            flag = 1;
            for (i = 3; i < prime; i+=2){
                if (prime % i == 0) {
                    flag = 0;
                    break;
                }
            }
            if(flag == 1)
                counter++;
        } while (counter != n);
    }
    printf("%d\n", prime);
    counter = 1;
    }

    return 0;
}