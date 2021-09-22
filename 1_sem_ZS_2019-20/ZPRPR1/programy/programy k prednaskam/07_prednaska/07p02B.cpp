// klasicka premenna a ukzovate s priradenim adresy - vypis adries a hodnot
#include <stdio.h>

int main() {
	int i = 1, j = 2, *p;
	
	printf("adresy  - i: %p, p: %p\n", &i, &p);
	printf("hodnoty - i: %d, p: %p\n\n", i, p);
	//printf("hodnoty - i: %d, p: %p, *p: %d\n\n", i, p, *p);
	
	p = &i;
	//p = 125;
	printf("adresy  - i: %p, p: %p\n", &i, &p);
	printf("hodnoty - i: %d, p: %p, *p: %d\n\n", i, p, *p);	
	
	return 0;
}
