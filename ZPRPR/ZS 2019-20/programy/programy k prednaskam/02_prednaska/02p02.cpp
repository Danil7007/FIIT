// realne konstanty: prevod cm na inch
#include <stdio.h>

int main()
{
	int vyska_cm = 0xAA;
	double vyska_inch;
	
	vyska_inch = vyska_cm * .393701;
	
	printf("vyska: %d cm = %f inch\n", vyska_cm, vyska_inch);
	printf("vyska: %f mikrometrov\n\n", vyska_cm * 1e4);

	return 0;
}
