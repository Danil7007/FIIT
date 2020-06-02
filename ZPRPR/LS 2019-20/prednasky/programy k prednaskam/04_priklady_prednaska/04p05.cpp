// pole ukazovatelov na retazce
// rozne vypisy - pomocou pomocnych ukazovatelov
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

	char *p_text[4];

	p_text[0] = "prvy";		// ukazuje na konstantu
	p_text[1] = "druhy";	// ukazuje na konstantu
	p_text[2] = (char *) malloc(10);	// ukazuje na alokovane pole znakov
	strcpy(p_text[2], "treti");
	p_text[3] = (char *) malloc(10);	// ukazuje na alokovane pole znakov
	strcpy(p_text[3], "stvrty");

	printf("Vypis pomocou char c pre znak: \n");
	char c, *p;
	c = p_text[0][0];
	printf("p_text[0][0]: %c\n", c);
	
	printf("Vypis pomocou char *q pre jednotlive retazce: \n");
	p = &p_text[0][0];
	while (*p != '\0')
	    putchar(*p++);
	putchar('\n');
	
	printf("%s \n", p_text[1]);
	puts(p_text[2]);

	printf("Vypis pomocou char **q (++*q): \n");
	char **q;
	q = p_text;
	puts(++*q);
	
	printf("Vypis pomocou char **q (*++q): \n");
	q = p_text;
	puts(*++q);
	
	printf("Vypis pomocou char **q (vypis celeho pola retazcov): \n");
	int i;
	q = p_text;
	for (i = 0; i < 4; i++) 
	    puts(*q++);

	free(p_text[2]);
	free(p_text[3]);
	return 0;
}

