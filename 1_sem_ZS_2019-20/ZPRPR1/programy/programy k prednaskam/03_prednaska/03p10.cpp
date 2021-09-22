// break a continue vo while cykle
// opisovanie znakov na obrazovku (okrem medzier), skonci po precitni '*'
#include <stdio.h>

int main() {
	int c;

	while (1) {
		if ((c = getchar()) == ' ')
			continue;
		if (c == '*')		// co ak tu tento if nebude?
		   break;
		putchar(c);
	}
	return 0;
}
