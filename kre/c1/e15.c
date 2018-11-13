#include <u.h>
#include <libc.h>
#include <stdio.h>

#define LOWER	0
#define UPPER	300
#define STEP	20

float fahr_2_cel(int);

void
main (void)
{
	int fahr;

	for(fahr = LOWER; fahr <= UPPER; fahr += STEP){
		printf("%3d %6.1f\n", fahr, fahr_2_cel(fahr));
	}

	exits(0);
}

float
fahr_2_cel(int fahr)
{
	return (5.0/9.0) * (fahr-32);
}
