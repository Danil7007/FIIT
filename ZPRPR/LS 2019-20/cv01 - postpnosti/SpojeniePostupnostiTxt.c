// V suboroch cisla1.txt a cisla2.txt sa nachazaju usporiadane postupnosti celych cisiel
// oddelenych medzerami. Napiste prog., kt. spoji tieto dve postupnosti do jednej do suboru vysledok.txt
// tak, aby bola usporiadana

#include <stdio.h>
#include <algorithm>

int main (){
    FILE *subor1, *subor2, *subor3;
    int i = 0, j = 0, s1, s2, s3, *pole[100];

    subor1 = fopen("cisla1.txt", "r");
    subor2 = fopen("cisla2.txt", "r");
    subor3 = fopen("vysledny.txt", "w");

    s1 = getc(subor1);
    s2 = getc(subor2);
    s3 = getc(subor3);
	
    while (s1 != EOF){
        *(pole + i) = s1;
        s1 = getc(subor2);
        i++;
    }

    while (s2 != EOF){
        *(pole + i) = s2;
        s2 = getc(subor2); 
        i++;
    }

    // ZORADIT POLE, VYMAZAT DUPLIKATY 
    // std::sort(std::begin(pole), std::end(pole));

    while (j < i){
        fprintf (s3, "%d", *(pole + j));
        j++;
    }

    fclose (s1);
    fclose (s2);
    fclose (s3);

    return 0;
}
