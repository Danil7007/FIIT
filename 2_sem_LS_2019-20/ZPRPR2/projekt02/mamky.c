//Napiste program ktorý na vstupe nacita 2 cele cisla n a m. 
//Nasledne vytvorí n struktur typu mama a m struktur typu babo.
//Vytvorí spájaný zoznam struktur babo pre kazdu mamu tak aby kazda mama mala rovnaký pocet deti. 
//Cislo m musí byť párne a tak isto aj n ak nie program vypíše "Grmanovej to zasa jebe"

#include <stdio.h>
#include <stdlib.h>

typedef struct babo {
    int vek;
    int cisielko;
    struct babo *dalsie;
} BABO; 

typedef struct mamka {
    int plat;
    BABO *dzetci;
} MAMKA;

int main() {
    int n, m;
    struct mamka *pole_mamiek,*stepmamka;
    
    scanf ("%d %d", &n, &m);
    if (n % 2 != 0 || m % 2 != 0) {
        printf ("Grmanovej to zasa jebe :) \n");
        return 0;
    }
    
    pole_mamiek = (struct mamka*)calloc(n, sizeof(struct mamka));
   
    
    for (int i = 0; i<n; i++) {
        
        
        BABO *stepdecko = (struct babo*)malloc(sizeof(struct babo));
        pole_mamiek[i].dzetci = stepdecko;
    
        for (int j=0; j < (m/n) - 1; j++) {
            BABO *falosne_stepdecko = (struct babo*)malloc(sizeof(struct babo));
            stepdecko->dalsie = falosne_stepdecko;
            stepdecko = falosne_stepdecko;
        }
        
        
    
    }
    
    
    return 0;
}
