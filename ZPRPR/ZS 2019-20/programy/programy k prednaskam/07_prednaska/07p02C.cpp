// klasicka premenna a ukzovate s priradenim adries aj hodnot - vypis adries a hodnot
#include <stdio.h>

int main() {
	int i = 1, j = 2, *p;
	
	printf("adresy  - i: %p, p: %p\n", &i, &p);
	printf("hodnoty - i: %d, p: %p\n\n", i, p);
	//printf("hodnoty - i: %d, p: %p, *p: %d\n\n", i, p, *p);
	
	p = &i;
	printf("adresy  - i: %p, p: %p\n", &i, &p);
	printf("hodnoty - i: %d, p: %p, *p: %d\n\n", i, p, *p);	
	
	*p = 5;
	printf("adresy  - i: %p, p: %p\n", &i, &p);
	printf("hodnoty - i: %d, p: %p, *p: %d\n\n", i, p, *p);		
	
	return 0;
}
