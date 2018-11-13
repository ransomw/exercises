#include <u.h>
#include <libc.h>
#include <stdio.h>
#include "calc.h"
#define MAXVAL	100 /* max stack depth */

int sp = 0; /* next free stack position */
double val[MAXVAL]; /* stack of values */

void
push(double f)
{
	if(sp < MAXVAL)
		val[sp++] = f;
	else {
		printf("error: stack full, cant push %g\n", f);
		exits("stack full");
	}
}

double
pop(void)
{
	if(sp > 0)
		return val[--sp];
	else {
		exits("stack empty");
		return 0.0;
	}
}
