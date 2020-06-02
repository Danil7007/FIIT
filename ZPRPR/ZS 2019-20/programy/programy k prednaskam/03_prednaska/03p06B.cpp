// vypis znaku s mensim ordinalnym cislom
// nacitanie d vo vnutri putchar
#include <stdio.h>

int main() {
	int c, d, e;
	
	c = getchar(); 
	d = getchar();	// aj c, d sa daju nacitat v putchar()
	
	putchar(c < d ? (c < (e = getchar()) ? c : e) : (d < e ? d : e));	
	
	return 0;
}
