// uloha5-1.c -- Emma Macháčová, 14.10.2020 14:38

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* qsort C-string comparison function */ 
int cstring_cmp (const void *a, const void *b) { 
	const char **ia = (const char **)a;
	const char **ib = (const char **)b;
	return strcmp(*ia, *ib);
} 

int porovnaj (char *a[], int n) {
	int akt=0, porovn=0;
	int dupl=0;

	for (akt = 0, porovn = akt+1; akt < n-1; akt++, porovn++) {

		if (strcmp (a[akt], a[porovn]) == 0) {
			//printf ("duplikat\n");
			dupl++;
		}

	}

	return dupl;
}

// spracuje cisla OP: vrati pocet najdenych duplikatov.
int vyhadzovac(char *a[], int n) {
 
    qsort(a, n, sizeof(char *), cstring_cmp);

	/*for (int i=0; i<n; i++) {
		printf ("%s\n", a[i]);
	}*/

	printf ("Pocet duplikatov: %d\n", porovnaj (a, n));

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

	vyhadzovac(a, n);

	return 0;
}