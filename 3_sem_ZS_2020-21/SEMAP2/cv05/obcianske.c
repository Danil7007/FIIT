// uloha5-1.c -- Emma Macháčová, 14.10.2020 14:38

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// spracuje cisla OP: vrati pocet najdenych duplikatov.
int vyhadzovac(char *a[], int n) {
	
	// sem napis svoje riesenie

	return 0;
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

	//printf("Pocet duplikatov: %d\n", vyhadzovac(a, n));

	return 0;
}