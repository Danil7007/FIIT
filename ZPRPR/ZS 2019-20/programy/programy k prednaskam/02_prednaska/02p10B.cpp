// vypis znaku s mensim ordinalnym cislom
// nacitanie d vo vnutri putchar
#include <stdio.h>

int main() {
	int c, d;
	
	c = getchar(); // aj c sa da nacitat v putchar()
	
	putchar(c < (d = getchar()) ? c : d);	
	return 0;
}
