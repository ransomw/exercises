#include <u.h>
#include <libc.h>
#include <stdio.h>

/**
 * print Fahrenheit-Celsisus table
 * (integer version)
 */
void
main (void)
{
	int fahr, cel;
	int lo = 0, hi = 300, step = 20;

	fahr = lo;
// style: Plan 9 system uses no spaces around brackets
	while(fahr <= hi){
		// ((int) 5) / ((int) 9) = 0
		cel = 5 * (fahr-32) / 9;
		// printf("%d\t%d\n", fahr, cel);
		// %<n>d prints <n> digits wide (leading space)
		printf("%3d %6d\n", fahr, cel);
		fahr += step;
	}
	exits(0);
}

/* other built-in types include.
float
char
short
long
double
*/
