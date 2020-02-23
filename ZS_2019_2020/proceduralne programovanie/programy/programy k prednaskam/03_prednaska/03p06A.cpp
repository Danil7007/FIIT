// vypis znaku s najmensim ordinalnym cislom
#include <stdio.h>

int main() {
	int c, d, e;
	
	c = getchar();
	d = getchar();
	e = getchar();
	
	putchar(c < d ? (c < e ? c : e) : (d < e ? d : e));	
	return 0;
}
