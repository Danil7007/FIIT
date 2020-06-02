// Vypis suboru - rekurzivna funkcia
#include <stdio.h>

void vypis_iter(FILE *fr);
void vypis_rek(FILE *fr);

int main(void) {
	FILE *fr;
	
	if((fr = fopen("lyrics.txt", "r")) == NULL) {
		printf("Subor sa nepodarilo otvorit\n");
		return 0;
	}
	
	vypis_iter(fr);
	//vypis_rek(fr);
	
	if(fclose(fr) == EOF)
		printf("Subor sa nepodarilo zatvorit\n");
	return 0;
}

void vypis_iter(FILE *fr) {
	int c;
	
	while((c=getc(fr)) != EOF) 
		putchar(c);
}

void vypis_rek(FILE *fr) {
	int c;
	
	if((c=getc(fr)) != EOF) {
		putchar(c);		// co sa stane, ked vymenenime poradie prikazov v tele if?
		vypis_rek(fr);
	}   
}
