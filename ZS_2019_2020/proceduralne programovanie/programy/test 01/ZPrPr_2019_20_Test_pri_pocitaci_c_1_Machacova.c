// test1.c -- Emma Macháčová, 28.10.2019 17:02

#include <stdio.h>

int main(){
  int a, b, v, o, i, j, k, l, p;

  scanf("%d", &p);
  if (p<= 100 && p>=1){
    for (l=1; l<=p; l++){
    scanf("%d %d", &v, &o);
    if (o<=7 && o>=1 && v<=11 && v>=3 && v%2!=0){
      a = v / 2 + 1;
      b = v / 2 + 1;
      for (i=1; i<=v; i++){
        for (k=1; k<= o ; k++){
          for (j=1; j<=v; j++){
            if (j==a || i==b){
              printf("*"); 
            }
            else{
              printf("."); 
            }
          }
        }
        printf("\n");
        if (i>=b){
          a--;
        }
        else{
          a++;
        }
      }
      }
      else{
        printf("Nespravny vstup\n");
        break;
      }
    }
  }
  else{
    printf("Nespravny vstup");
  }

  return 0;
}