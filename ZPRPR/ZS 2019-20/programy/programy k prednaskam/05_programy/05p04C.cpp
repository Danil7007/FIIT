// vypisat predposledny *neprazdny* riadok suboru

#include <stdio.h>

int main() {
	FILE *fr;
	int c;
	long pozicia = 0, pred;

	if ((fr = fopen("lyrics.txt", "r")) == NULL) {
		printf("Subor sa nepodarilo otvorit.\n");
		return 0;
	}
	
	while((c = getc(fr)) != EOF) {
		if(c == '\n') {
			pred = pozicia;
			pozicia = ftell(fr); // zapamata si poziciu zaciatku riadku
		}
	}
	if(pozicia == ftell(fr)) {
		printf("Posledny riadok je prazdny\n", pred, pozicia);
		pozicia = pred;	
	}
			
	fseek(fr, pozicia, SEEK_SET);	// nastavi sa na zaciatok posledneho neprazdneho riadku
	while((c = getc(fr)) != EOF) 	// vypis posledneho riadku
		putchar(c);
	putchar('\n');

	if (fclose(fr) == EOF) 
		printf("Subor sa nepodarilo zatvorit\n");
	return 0;
}

