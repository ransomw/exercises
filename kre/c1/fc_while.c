#include <u.h>
#include <libc.h>
#include <stdio.h>

/**
 * print Fahrenheit-Celsisus table
 * (floating-point version)
 */
void
main (void)
{
	float fahr, cel;
	float lo = 0, hi = 300, step = 20;

	fahr = lo;
	while(fahr <= hi){
		/* if an arimetic op has one int and one float
		 * as operands, the int is cast to float,
		 * as in fahr-32 */
		cel = (5.0/9.0) * (fahr-32);
		/* example line out
		 *   0  -17.8
		 * so %6.1f means 6 chars, incl decimal and sign,
		 * and one digit precision */
		printf("%3.0f %6.1f\n", fahr, cel);
		fahr += step;
	}
	exits(0);
}

/* other printf formatting examples, notes
%6f - at least 6 chars wide
%.2f - two chars after the decimal
%o - octal
%x - hex
%c - char
%s - str
%% - the '%' char itself
*/
