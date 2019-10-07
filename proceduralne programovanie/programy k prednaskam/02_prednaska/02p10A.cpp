// vypis znaku s mensim ordinalnym cislom
#include <stdio.h>

int main() {
	int c, d;
	
	c = getchar();
	d = getchar();
	
	putchar(c < d ? c : d);	
	return 0;
}
