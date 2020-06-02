// Napiste program, kt. nacita cele cislo n nasledovane znakom konca riadku. 
// Potom nacita postupnost n celych cisiel, kazde nasledovane znakom konca riadku. 
// Program urci, ci naciana postupnost cisiel je spravna.
// Postupnost je spravna ak....

#include <stdio.h>

int main () { 
    int k = 0, m, n, i, postupnost = 1;

    scanf("%d", &n);
    
    if (!(n >= 0 && n <= 10)){
    return 0;
    }

    for (i=1; i <= n; i++){
        scanf ("%d", &m);

        if (i>1){
            if (!((k*2 > m) && (m > k/2))){
                printf ("Nespravna");
                return 0;
            }
        }
        k = m;
    }
    printf ("Spravna");
    
    return 0;
        
}