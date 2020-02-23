#include <stdio.h>

#include <stdio.h>

int main(){
    int a[1][5], i, max,j;
    double sum1 = 0, sum2 = 0;
    for (i=0; i<5; i++){
        a[0][i] = 0;
    }
    scanf("%d %d %d %d %d", &a[0][0], &a[0][1], &a[0][2], &a[0][3], &a[0][4]);
    max = 0;
    for (i=4; i>=0; i--){
        if (max<a[0][i]){
            max = a[0][i];
        }
    }
    for (i=0; i<5; i++){
        a[1][i] = a[0][i]*max;
        sum1 += a[0][i];
        sum2 += a[1][i];
    }
    printf("\nPole 1:\n");
    for (i=4; i>=0; i--){
        printf("%d ",a[0][i]);
    }
    printf("\nMaximum pola 1: %d", max);
    printf("\nPole 2:\n");
    for (i=4; i>=0; i--){
        printf("%d ",a[1][i]);
    }
    printf("\nAP pola 1: %.2f a AP pola 2: %.2f\n", sum1/5, sum2/5);
    for(j=0;j<=1;j++){
        for(i=0;i<=4;i++){
            printf("%2d ",a[j][i]);
        }
        printf("\n");
    }
    return 0;
}
