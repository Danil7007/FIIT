// uloha5-1.c -- Emma Macháčová, 14.10.2020 14:38

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// hash
unsigned long hash (char *str) {
    unsigned long hash = 5381;
    char c=0;

    while (c = *str++) {
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
	}

    return hash;
}

// find dup
int countDup (unsigned long *arr, int size) {
	int i, j, count=0;

	for(i=0; i<size; i++) {
        for(j=i+1; j<size; j++) {
            if(arr[i] == arr[j]) {
                count++;
                break;
            }
        }
    }

	//printf ("%d\n", count);
	return count;
}


// spracuje cisla OP: vrati pocet najdenych duplikatov.
int vyhadzovac(char *a[], int n) {
	int i;
	unsigned long* pole;
	pole = (unsigned long*)calloc(n, sizeof(unsigned long));

	for (i=0; i<n; i++) {
		//printf ("%ld\n", hash (a[i]));
		pole[i] = hash(a[i]);
	}
	
	printf ("Pocet duplikatov: %d\n", countDup (pole, n));

	return 0;
}

// ukazkovy test
int main(void) {
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