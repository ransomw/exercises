#include <u.h>
#include <libc.h>
#include <stdio.h>

/**
 * print Celsisus-Fahrenheit table
 * (floating-point version)
 */
void
main (void)
{
	float fahr, cel;
	float lo = 0, hi = 300, step = 20;

	fahr = lo;
	while(fahr <= hi){
		cel = (5.0/9.0) * (fahr-32);
		printf("%6.1f %3.0f\n", cel, fahr);
		fahr += step;
	}
	exits(0);
}
