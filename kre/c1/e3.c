#include <u.h>
#include <libc.h>
#include <stdio.h>

#define	HORIZ "----------" /* 10 chars */
//            "Fahrenheit"

// fc.c, more prettily printed
// todo: less uglily coded (hint: %s)
void
main (void)
{
	float fahr, cel;
	float lo = 0, hi = 300, step = 20;
	char horiz[] = HORIZ;
	
	fahr = lo;


	printf("+"); printf(HORIZ); printf("-"); printf(horiz); printf("+");
	printf("\n");
	printf("|");
	printf("Fahrenheit");
	printf("|");
	printf(" Celsisus ");
	printf("|");
	printf("\n");

	while(fahr <= hi){
		cel = (5.0/9.0) * (fahr-32);
		printf("%3.0f %6.1f\n", fahr, cel);
		fahr += step;
	}
	exits(0);
}
