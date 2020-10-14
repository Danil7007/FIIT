// uloha5-1.c -- Emma Macháčová, 14.10.2020 14:38

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// spracuje cisla OP: vrati pocet najdenych duplikatov.
int vyhadzovac(char *a[], int n) {
	int pocet=0, t=0, p=0, operacii=0;
	int* zhodne;
	zhodne = (int*)calloc(n, sizeof(int));

	//printf ("operacii: %d \n", operacii);

	while (t < n) { // od prveho

		p = t + 1; // porovnavam s dalsim

		if (zhodne[t] == 0) {
			while (p < n) { // kym dalsie neprejde na koniec zoznamu
		
				if (zhodne[p] != -1) {
					//printf ("%d - %d\n", t,  p);
					if (strcmp (a[t], a[p]) == 0) {
						pocet++;
						zhodne[p] = -1;
					}
					operacii++;
				}
				p++;
			}
		}
		t++;
	}	

	//printf ("operacii: %d \n", operacii);
	return pocet;
}

// ukazkovy test
int main(void)
{
	char **a = NULL, buf[100];
	int n = 0, len = 0;

	// nacitanie retazcov
	while (scanf("%s", buf) > 0)
	{
		if (n == len)
		{
			len = len + len + (len == 0);
			a = (char**)realloc(a, len * sizeof(char*));
		}
		a[n++] = strdup(buf); 
		// na konci bude v n pocet nacitanych obcianskych
	}

	printf("Pocet duplikatov: %d\n", vyhadzovac(a, n));

	//vyhadzovac(a, n);

	return 0;
}