// znakove konstanty 
#include <stdio.h>

int main()
{
	char znak = 'A';  
	
	printf("%c", znak);		// vypisat ako %d
	znak = znak + 1;
	printf("%c%c", znak, znak + 1);
	znak = '\n';
	printf("%c", znak);
	
//	znak = '*';
//	printf("\007 Znak %c ma ASCII kod %d", znak, znak);  

	return 0;
}
