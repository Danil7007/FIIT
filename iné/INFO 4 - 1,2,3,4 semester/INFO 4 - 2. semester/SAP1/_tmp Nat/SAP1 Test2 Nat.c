#include <stdio.h>
#include <string.h>
#include <stdlib.h>


//Byte Printf
#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
  (byte & 0x80 ? '1' : '0'), \
  (byte & 0x40 ? '1' : '0'), \
  (byte & 0x20 ? '1' : '0'), \
  (byte & 0x10 ? '1' : '0'), \
  (byte & 0x08 ? '1' : '0'), \
  (byte & 0x04 ? '1' : '0'), \
  (byte & 0x02 ? '1' : '0'), \
  (byte & 0x01 ? '1' : '0') 


// uloha 4
#define VYTVORIT_CISLO(i) (1<<(i))

// uloha 1
typedef struct {
  char meno[50];
  int vek;
  float plat;
} TOsoba;




void uloha1() {
  TOsoba s;
  TOsoba *p = &s;
  
printf("======\n");
printf("Uloha1\n\n");  
  
//  *p.vek = 1; // ERROR
  printf("A: %d\n", s.vek);
  
  (*p).vek = 2;
  printf("B: %d\n", s.vek);
  
  p ->vek = 3;
  printf("C: %d\n", s.vek);
  
  s.vek = 4;
  printf("D: %d\n\n", s.vek);
}

void uloha2() {
  int i, j, k, *p1, *p2 = &j;
  
  printf("======\n");
  printf("Uloha2\n\n");  
  
  p1 = &i;
  scanf("%d", &i);
  scanf("%d", p2);
  *p1 = 22; // ---

  printf("%p %p %d\n", &p1, p1, *p1)    ;
  printf("%p %d\n", &j, j);
  p2 = p1; // ---
  
  k = *p2 + 1;  // ---
//  printf("i: %d\nj: %d\nk: %d\np1 val: %d\np2 val: %d\n\n", i, j, k, *p1, *p2); // PRINT
  
  p1 = NULL; // ---  
}


void uloha4() {
  char x1, x2, x3, x4, x5;
//  char x1, x2, x3, x4, x5 = 255;

  printf("======\n");
  printf("Uloha4\n\n");  
  
  // PRINT MASKS
  printf("MASKS:\n");
  
  x1 = ( (~VYTVORIT_CISLO(1)) & (~VYTVORIT_CISLO(2)) & ~1);
  x2 = (VYTVORIT_CISLO(1) | VYTVORIT_CISLO(2));
  x3 = ( (~VYTVORIT_CISLO(0)) & (~VYTVORIT_CISLO(1)) & (~VYTVORIT_CISLO(2)) );
  x4 = ( ~VYTVORIT_CISLO(3) );
  x5 = ~( (~VYTVORIT_CISLO(1)) & (~VYTVORIT_CISLO(2)) & ~1);

  printf("A: "BYTE_TO_BINARY_PATTERN"\n", BYTE_TO_BINARY(x1));
  printf("B: "BYTE_TO_BINARY_PATTERN"\n", BYTE_TO_BINARY(x2));
  printf("C: "BYTE_TO_BINARY_PATTERN"\n", BYTE_TO_BINARY(x3));
  printf("D: "BYTE_TO_BINARY_PATTERN"\n", BYTE_TO_BINARY(x4));
  
  printf("\n5: "BYTE_TO_BINARY_PATTERN"\n", BYTE_TO_BINARY(x5));
  
  x1 = x2 = x3 = x4 = x5 = 255;
  printf("\nCALCULATIONS:\n");
  // CALCULATE
  
  x1 &= ( (~VYTVORIT_CISLO(1)) & (~VYTVORIT_CISLO(2)) & ~1);
  x2 &= (VYTVORIT_CISLO(1) | VYTVORIT_CISLO(2));
  x3 |= ( (~VYTVORIT_CISLO(0)) & (~VYTVORIT_CISLO(1)) & (~VYTVORIT_CISLO(2)) );
  x4 |= ( ~VYTVORIT_CISLO(3) );
  x5 &= ~( (~VYTVORIT_CISLO(1)) & (~VYTVORIT_CISLO(2)) & ~1);

  printf("A: "BYTE_TO_BINARY_PATTERN"\n", BYTE_TO_BINARY(x1));
  printf("B: "BYTE_TO_BINARY_PATTERN"\n", BYTE_TO_BINARY(x2));
  printf("C: "BYTE_TO_BINARY_PATTERN"\n", BYTE_TO_BINARY(x3));
  printf("D: "BYTE_TO_BINARY_PATTERN"\n", BYTE_TO_BINARY(x4));
  
  printf("\n5: "BYTE_TO_BINARY_PATTERN"\n", BYTE_TO_BINARY(x5));
}


void uloha6() {
  // Koskova - 6. prednaska
  
  int a[2][3] = {
    {11, 12, 13},
    {21, 22, 23}
  };
  
  int i = 1;
  int j = 2;
  
  printf("======\n");
  printf("Uloha6\n\n");  
                                                             // ADDRESS:
  printf("%p - val: %d\n", &a[i][j], a[i][j]);               // &a[i][j]
  printf("%p - val: %d\n", a[i]+j, *(a[i]+j));               // a[i]+j
  printf("%p - val: %d\n", *(a + i) + j, *(*(a + i) + j));   // *(x + i) + j
}

void uloha7() {
  printf("======\n");
  printf("Uloha7\n\n");  
  
  int x[10], *p_x;
  p_x = (int*) malloc(10*sizeof(int));
  
  printf("sizeof x: %d\n",sizeof(x));
  printf("sizeof p_x: %d\n",sizeof(p_x));
}


int main() {
//  uloha1();
//  uloha2();
  uloha4();
//  uloha6();
//  uloha7();
}