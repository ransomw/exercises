#include <u.h>
#include <libc.h>
#include <stdio.h>

unsigned invert(unsigned x, int p, int n);

void
main(void)
{

	printf("%x %x\n",
		/* bc0 = 1011.1100.0000 -> 1011.0011.1100 = b3c */
		invert(0xBC0, 7, 6),
		/* FA0 = 1111.1010.0000 -> 1100.0110.0000 = C60 */
		invert(0xFA0, 9, 4));

	exits(0);
}

/* invert (0->1, 1->0) n bits that begin at p */
unsigned
invert(unsigned x, int p, int n)
{
	unsigned bit_mask = ~(~0 << n) << (p+1-n);
	unsigned to_invert = x & bit_mask;

	return (x & ~bit_mask) | (~to_invert & bit_mask);
}
