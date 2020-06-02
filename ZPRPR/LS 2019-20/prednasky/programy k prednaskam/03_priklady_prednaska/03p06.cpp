// na zaklade volby od pouzivatela sa voli funkcia, ktora sa spusti
// vypis bud spravy "Ahoj" alebo "Cau"
// pouzitie ukazovatela na funkciu
#include <stdio.h>
#include <ctype.h>

void ahoj() {
	printf("Ahoj\n");
}

void cau() {
	printf("Cau\n");
}

int main() {
   int c;
   void (* p_fnc)();    /* definicia ukazovatela na funkciu */

   printf("Ahoj / Cau / Koniec\n");
   while((c = toupper(getchar())) != 'K') {
      if (c == 'A') p_fnc = ahoj;
      else if (c == 'C') p_fnc = cau;
	else continue;

	(*p_fnc)();
   }
   return 0;
}

