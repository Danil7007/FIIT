// pouzitie referencneho a dereferencneho operatora
#include <stdio.h>

int main() {
	int i = 7, *pointer;
	
	printf("%d\n", i);
	printf("%d\n", &i);
	printf("%d\n\n", *&i);
	
	pointer = &i;
	printf("%d\n", pointer);
	printf("%d\n", *pointer);
	printf("%d\n", &pointer);
	printf("%d\n", &*pointer);
	printf("%d\n", *&pointer);
	printf("%d\n", **&pointer);
	printf("%d\n", &*&pointer);
	
	return 0;
}
