#include <stdio.h>

int main () {
    int a;
    scanf ("%d", &a);

    a%2 == 0 ? printf("parne") : printf("neparne");
    return 0;
}