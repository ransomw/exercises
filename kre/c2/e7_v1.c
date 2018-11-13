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
		/* FA = 1111.1010 -> 1100.0110 = C6 */
		invert(0xFA0, 9, 4));

	exits(0);
}

/* invert (0->1, 1->0) n bits that begin at p */
unsigned
invert(unsigned x, int p, int n)
{
	unsigned n_ones = ~(~0 << n);
	int left_shift = (p+1-n);
	unsigned bit_mask = ~(n_ones << left_shift);
	unsigned inverted_bits = ~((x & ~bit_mask) >> left_shift)
					& n_ones;

	return (x & bit_mask) | inverted_bits << left_shift;
}
