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

	return 
		/* blank out dest bits */
		(x & ~(~(~0 << n) << (p+1-n)))
		| /* and fill in the blank */
		((y & ~(~0 << n)) << (p+1-n))
	;
}
