// hviezdickovanie: oramovana sachovnica - opakovanie pod seba
#include <stdio.h>

int main() {
	int i, j, n, k, o;

	printf("Zadajte velkost stvorca: ");
	scanf("%d", &n);
	printf("Zadajte pocet opakovani pod seba: ");
	scanf("%d", &o);

	for(k=1; k<=o; k++) 
		for(i=1; i<=n; i++) {
			for(j=1; j<=n; j++) 
				if(i==1 || i==n || j==1 || j== n) putchar('*');
				else if(i%2==1 && j%2==1 || i%2==0 && j%2==0) 
					putchar('x');
					else putchar('o');				
			putchar('\n');
		}
	
	return 0;
}
