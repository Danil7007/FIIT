// while: opisovanie znakov pokym sa nenacita *
#include <stdio.h>

int main() 
{
	int c;

	while ((c = getchar()) != '*') {
		if (c != ' ')
			putchar(c);
	}
	return 0;
}

