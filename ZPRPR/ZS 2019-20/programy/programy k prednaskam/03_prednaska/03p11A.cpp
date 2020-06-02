// hadanie magickeho cisla
#include <stdio.h>
#include <stdlib.h> 
#include <time.h> 

int main(void) 
{
	int magicke, tip; 
	srand(time(0));
	magicke = rand() % 10 + 1;  

	printf("Vas tip na magicke cislo: ");
	scanf("%d", &tip); 

	while (tip != magicke && tip != -1) {
		if (tip > magicke) 
			printf("\ntip je prilis vysoky, zadajte dalsi: "); 
		else printf("\ntip je prilis nizky, zadajte dalsi:\n");
		scanf("%d", &tip);
	}
	
	if (tip == magicke) {
		printf("*** BINGO! ***");
		printf(" %d je magicke cislo.\n", magicke);
	}
	else 
		printf("Skus nabuduce.\n");
	
	return 0;
}

