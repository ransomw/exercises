#include <u.h>
#include <libc.h>
#include <stdio.h>

int power(int, int);

/**
 * call by value demonstration
 */
void
main(void)
{
	int i;

	for(i = 0; i < 10; ++i)
		/* the value of the variable i doesn't change
		 * as a result of the calls to power() ... */
		printf("%d %d %d\n", i, power(2, i), power(-3, i));

	exits(0);
}

int
power(int base, int n)
{
	int p;

	/* ... despite the decrement that occurs here */
	for(p = 1; n > 0; --n)
		p *= base;

	return p;
}

