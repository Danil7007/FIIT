#include <stdio.h>
#include <string.h>

typedef struct meno {
    char krstne[20];
    char priezv[20];
} MENO;

typedef struct herec {
    MENO meno_herca;
    int rok_nar;
    struct herec *dalsi;
} HEREC;

typedef struct film {
    char nazov[20];
    char rezis[20];
    int rok;
    HEREC *herci;
} FILM;

int main() {
    HEREC pokus;
    char c;
    int i;
    
    HEREC *prvy = NULL;
    HEREC *dalsi = NULL;
    
    i=0;
    scanf("%c", &c);
    if (c == '*') {
        // medzera pred menom
        scanf("%c", &c);
        // prve pismeno mena
        scanf("%c", &c);
        
        // krstne
        while (c != ' ') {
            pokus.meno_herca.krstne[i] = c;
            // medzera za menom skonci tu
            scanf("%c", &c);
            i++;
        } 
        
        i=0;
        scanf("%c", &c);
        // priezv
        while (c != ' ') {
            pokus.meno_herca.priezv[i] = c;
            // medzera za menom skonci tu
            scanf("%c", &c);
            i++;
        } 
        
        scanf("%d", &pokus.rok_nar);
        
        // ak je herec novy uzol
        if (prvy == NULL) {
            prvy = pokus;
        }
        // ak uz boli herci pridani
        else {
            p_h = head_h;
            while (p_h->dalsi_h != NULL) {
                p_h = p_h->dalsi_h;
            }
            p_h->dalsi_h = temp_h;
        }
    }
    
    
    printf("%s %s %d", pokus.meno_herca.krstne, pokus.meno_herca.priezv, pokus.rok_nar);

    return 0;
}
