// spocitanie vsetkych cisel v subore bez urcenej struktury
// vyuzitie ungetc
#include <stdio.h>

int main() {
	FILE *fr;
	int c;
	double x, sum = 0.0;

	if ((fr = fopen("data.txt", "r")) == NULL) {
		printf("Subor sa nepodarilo otvorit.\n");
		return 0;
	}
	
	while((c = getc(fr)) != EOF) {
		if(c >= '0' && c <= '9') {
			ungetc(c, fr);
			fscanf(fr, "%lf", &x);
			printf("%10.4f\n", x);
			sum += x;
		}
	}
	printf("Sucet cisel v subore: %f", sum);
	if (fclose(fr) == EOF) 
		printf("Subor sa nepodarilo zatvorit\n");
	return 0;
}

