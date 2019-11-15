// pouztie 2 smernikov - vypisy hodnot
#include <stdio.h>

int main() {
	int i, *p, *q;
	
	i = 5;
	printf("i: %d\n", i);
	//printf("i: %d, *p: %d, *q: %d\n", i, *p, *q);
	p  = &i;
	printf("i: %d, *p: %d\n", i, *p);
	*p = 6;
	printf("i: %d, *p: %d\n", i, *p);
	q = &i;
	printf("i: %d, *p: %d, *q: %d\n", i, *p, *q);
	*q = 7;
	printf("i: %d, *p: %d, *q: %d\n", i, *p, *q);	
	
	return 0;
}
