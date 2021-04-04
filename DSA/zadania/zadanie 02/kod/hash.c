// Zadanie 2 - Vyhladavanie v dynamickych mnozinah -- Emma Macháčová, 22.3.2021 17:25

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// struktura zvierata
typedef struct node {
    int pocetNoh;
    int pocetOci;
    char nazovZvierata[20]; // hlavny key

    long long hash;
    long long ind;

} ZVIERA;

struct node *hashArray[100000];
int SIZE = 100000;

long long hash (char *str);
void insert(char *key, int data, int data2);
void print();


void insert(char *key, int data, int data2) {

    struct node *item;
    item = (struct node *) malloc(sizeof(struct node));
    strcpy(item->nazovZvierata, key);
    item->pocetNoh = data;
    item->pocetOci = data2;

    //get the hash
    long long hashIndex = hash(key);
    item->hash = hashIndex;


    // realloc
    if (hashIndex >= SIZE) {
        SIZE += hashIndex;
        SIZE += 1000;
        *hashArray = (struct node*)realloc(*hashArray, (SIZE * sizeof(struct node)));
    }


    // hladanie miesta pre informaciu
    while(hashArray[hashIndex] != NULL) {
        // "linear probing"
        hashIndex = (hashIndex + 1) % sizeof(hashArray) / sizeof(struct node);
    }

    item->ind = hashIndex;
    hashArray[hashIndex] = item;
}

void print() {
    int i = 0, j = SIZE, k;

    for(i = 0, k = 0; i<j; i++) {

        if(hashArray[i] != NULL) {
            //printf(" (%s, %lld, %lld, %d, %d)",hashArray[i]->nazovZvierata, hashArray[i]->hash, hashArray[i]->ind, hashArray[i]->pocetNoh,hashArray[i]->pocetOci);
            printf(" (%s, %lld, %lld)",hashArray[i]->nazovZvierata, hashArray[i]->hash, hashArray[i]->ind);
            k++;
            if (k%5 == 0) {
                printf("\n");
            }
        }
        else {
            //printf(" ~~ ");
        }

    }

    printf("\n");
}

// polynomialne hashovanie z prednasky (miesto 31 -> 3)
long long hash (char *str) {
    int i, len = strlen(str), h = 0;
    for (i = 0; i < len; i++) {
        h = h*3 + str[i]*3 + str[i];
        //h += str[i]*17*i;
    }
    return h;
}

int main () {


    insert("pes", 10, 20);
    insert("los", 20,30);
    insert("losos", 10, 15);
    insert("los", 20,30);
    insert("opica", 20,30);

    insert("pes", 10, 20);
    insert("opica", 20,30);
    insert("los", 20,30);
    insert("losos", 10, 15);
    insert("los", 20,30);



    print();
}