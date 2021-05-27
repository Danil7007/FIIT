#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define log2(x) (log(x) / log(2))

typedef struct binaryDecisionDiagram {
    int pocetPremennych;
    int pocetUzlov;
    struct diagramNode* koren;
} BDD;

// funkcia
typedef struct binaryFunction {
    char vektor[20];
    int pocetPremennych;
} BF;

// uzol
typedef struct diagramNode {
    BF funkcia;
    struct diagramNode* false;
    struct  diagramNode* true;
} node;

BDD *BDD_create(BF *bfunkcia); // vytvorenie binarneho diagramu
char BDD_use(BDD *bdd, char *vstupy); // vyuzitie binarneho diagramu

int getPocetPremennych(BF bfunkcia); // pomocne funkcie
void rozdel(node *uzol, BDD *diagram);
char* leftHalf(char* vektor);
char* rightHalf(char* vektor);
void printOut(node *uzol);

// vytvorenie diagramu (DONE)
BDD *BDD_create(BF *bfunkcia) {
    node *root = (struct diagramNode*)malloc(sizeof(struct diagramNode));
    BDD *diagram = (struct binaryDecisionDiagram*)malloc(sizeof(struct binaryDecisionDiagram));

    root->funkcia = *bfunkcia; // vstupny vektor
    diagram->pocetPremennych = getPocetPremennych(root->funkcia); // pocet premennych
    diagram->pocetUzlov = 0; // pociatocny pocet uzlov (ak ratame aj root tak 1)
    diagram->koren = root; // koren


    rozdel(root, diagram);

    return diagram;
}

// use
char BDD_use(BDD *bdd, char *vstupy) {
    int velkostVstupu = strlen(vstupy);
    char vysledok;

    node* temp = bdd->koren;

    // prejdenie diagramu
    for (int i=0; i < velkostVstupu; i++) {
        if (vstupy[i] == 0) {
            temp = temp->false;
        }
        else {
            temp = temp->true;
        }
    }

    if (temp->funkcia.vektor == 0) {
        vysledok = 0;
    }
    else {
        vysledok = 1;
    }

    return vysledok;
}

// rekurzivna funkcia na rozvetvenie
void rozdel(node *uzol, BDD *diagram) {
    char* vektor = uzol->funkcia.vektor;

    // ak sa da rozdelit
    if (strlen(vektor) % 2 == 0) {

        // vytvorenie uzlov
        node *leftChild = (node *) malloc(sizeof(node));
        node *rightChild = (node *) malloc(sizeof(node));
        diagram->pocetUzlov += 2;

        // rozdelenie vektora
        char* tempL = leftHalf(vektor);
        char* tempR = rightHalf(vektor);

        // priradenie vektorov uzlom
        strcpy(leftChild->funkcia.vektor, tempL);
        strcpy(rightChild->funkcia.vektor, tempR);
        //printf("%s\n", leftChild->funkcia.vektor);
        //printf("%s\n", rightChild->funkcia.vektor);

        // priradenie uzlov k rodicovi
        uzol->false = leftChild;
        uzol->true = rightChild;

        // dalsie delenie
        rozdel(leftChild, diagram);
        rozdel(rightChild, diagram);
    }
}

// ziska lavu polku vektora
char* leftHalf(char* vektor) {
    int velkost = (strlen(vektor) / 2);
    //printf("velkost: %d\n", velkost);

    char* temp = (char*)calloc(velkost+1, sizeof(char));

    for (int i = 0; i < velkost; i++) {
        temp[i] = vektor[i];
    }

    //printf("Left: %s\n", temp);

    return temp;
}

// ziska pravu polku vekora
char* rightHalf(char* vektor) {
    int velkost = (strlen(vektor) / 2);
    //printf("velkost: %d\n", velkost);

    char* temp = (char*)calloc(velkost+1, sizeof(char));

    int j = 0;
    for (int i = velkost; i < (strlen(vektor)); i++) {
        temp[j] = vektor[i];
        j++;
    }

    //printf("Right: %s\n", temp);

    return temp;
}

// zisti pocet premennych vektora
int getPocetPremennych(BF bfunkcia) {
    //logaritmus so zakladom dva z poctu outputov
    int pocetOutputov = strlen(bfunkcia.vektor);
    float vysledok = log2(pocetOutputov);

    //printf("Pocet outputov: %d\n", pocetOutputov);
    //printf("Log: %.0lf\n", vysledok);

    return (int)vysledok;
}

// vypis
void printOut(node* uzol) {
    char* vektor = uzol->funkcia.vektor;

    // ak sa da rozdelit
    if (strlen(vektor) % 2 == 0 || strlen(vektor) == 1) {

        // vypis
        if (strlen(vektor) == 1) {
            printf("%s ", uzol->funkcia.vektor);
        }

        // priradenie
        node *leftChild = uzol->false;
        node *rightChild = uzol->true;

        // dalej
        if (strlen(vektor) / 2 != 0) {
            printOut(leftChild);
            printOut(rightChild);
        }
    }

}

int main() {

    // root funkcia
    BF *funkcia = (struct binaryFunction*) malloc (sizeof (struct binaryFunction));
    strcpy(funkcia->vektor, "01011100");

    // diagram
    BDD *diagram = BDD_create(funkcia);

    printOut(diagram->koren);

    return 0;
}