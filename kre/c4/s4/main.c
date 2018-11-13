#include <u.h>
#include <libc.h>
#include <stdio.h>

void push(double f);
double pop(void);

void
main(void)
{
	push(1.23);
	push(3.21);
	printf("%g %g\n", pop(), pop());
	
	exits(0);
}
