// vypisat posledny a 1. riadok suboru

#include <stdio.h>

int main() {
	FILE *fr;
	int c;
	long pozicia;

	if ((fr = fopen("lyrics.txt", "r")) == NULL) {
		printf("Subor sa nepodarilo otvorit.\n");
		return 0;
	}

	while((c = getc(fr)) != EOF) {
		if(c == '\n')
			pozicia = ftell(fr); // zapamata si poziciu zaciatku riadku
	}
	
	fseek(fr, pozicia, SEEK_SET);	// nastavi sa na zaciatok posledneho riadku
	while((c = getc(fr)) != EOF) 	// vypis posledneho riadku
		putchar(c);
	putchar('\n');
	
	rewind(fr);
	while((c = getc(fr)) != '\n') 	// vypis 1. riadku
		putchar(c);	
	putchar(c);

	if (fclose(fr) == EOF) 
		printf("Subor sa nepodarilo zatvorit\n");
	return 0;
}

