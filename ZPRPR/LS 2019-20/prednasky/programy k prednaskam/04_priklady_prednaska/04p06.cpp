// nacitanie najviac N prvych roznych slov do N-prvkoveho pola ukazovatelov na retazce
// v N-prvkovom poli celych cisel si pamatame pocty vyskytov
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 20		// maximalna dlzka slovnika
#define NSLOVA 100 	// maximalna dlzka slova
#define SUBOR "slova.txt"

int nacitaj(char *slovnik[], int pocet[]) {
	int i, n = 0;
	char *p, slovo[NSLOVA];
	FILE *f;
	
	for(i=0; i<N; i++) {
		pocet[i] = 0;
		slovnik[i] = NULL;
	}
	
	if((f = fopen(SUBOR, "r")) == NULL) {
		printf("Nepodarilo sa otvorit subor\n");
		return 0;
	}
	while(fscanf(f, "%s", slovo) == 1) {
		//printf("%s\n", slovo);
		for(i=0; i<n; i++) 
			if(!strcmp(slovnik[i], slovo)) 
				break;
		if(i < n) // slovo sa v slovniku nachadza
			pocet[i]++;
		else if(n<N){
			int len = strlen(slovo);
			p = (char *) malloc(len+1);
			strcpy(p, slovo);
			slovnik[n] = p;
			pocet[n] = 1;
			n++;
		}
	}
	fclose(f);
	for(i=n; i<N; i++) {
		slovnik[i] = NULL;
		pocet[i] = 0;
	}	
 	return n;
}

void uvolni(char *slovnik[]) {
	int i;
	for (i=0; i<N; i++)
		if (slovnik[i] != NULL) 
			free(slovnik[i]);
}

int main() {
	char *slovnik[N];
	int pocet[N];
	int i, n;
	n = nacitaj(slovnik, pocet);
	for(i=0; i<n; i++)
		printf("%s (%d)\n", slovnik[i], pocet[i]);
	uvolni(slovnik);
	return 0;
}
