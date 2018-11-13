#include <u.h>
#include <libc.h>
#include <stdio.h>

unsigned setbits(unsigned x, int p, int n, unsigned y);

void
main(void)
{

	printf("%x\n",
		setbits(0xBC0, 7, 4, 0xA));

	exits(0);
}

/* x with the bits that being at p
 * set to the rightmost n bits of y
 */
unsigned
setbits(unsigned x, int p, int n, unsigned y)
{
	unsigned n_ones = ~(~0 << n);
	int left_shift = (p+1-n);
	unsigned bit_set = (y & n_ones) << left_shift;
	unsigned bit_mask = ~(n_ones << left_shift);

	return (x & bit_mask) | bit_set;
}
