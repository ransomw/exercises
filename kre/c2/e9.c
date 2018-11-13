#include <u.h>
#include <libc.h>
#include <stdio.h>

int bitcount(unsigned x);

void
main(void)
{
	printf("%d %d %d\n",
		bitcount(04),
		bitcount(05),
		bitcount(07));

	exits(0);
}

/* count 1 bits in x */
int
bitcount(unsigned x)
{
	int n;

	for(n = 0; x != 0; ++n)
		/* in any two's compliment number system, x - 1
		 * 1. toggles the rightmost one bit of x
		 * 2. toggles all lower bits
		 * hence, x & (x - 1)
		 * 1. deletes the rightmost one bit of x
		 * 2. leaves all lower bits set to zero
		 *	since 0 & 1 == 1 & 0 == 0
		 */
		x &= x - 1;

	return n;
}
