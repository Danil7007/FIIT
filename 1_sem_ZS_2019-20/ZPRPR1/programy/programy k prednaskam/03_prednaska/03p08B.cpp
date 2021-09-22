// do-while: opisovanie znakov pokym sa nenacita * (vratane)
#include <stdio.h>

int main() 
{
	int c;

	do {
		if ((c = getchar()) != ' ')
			putchar(c);
	} while (c != '*');
	return 0;
}

