#include <u.h>
#include <libc.h>
#include <stdio.h>

/* bitwise operators are
 *   & and
 *   | or
 *   ^ exclusive or
 *   << left shift
 *   >> right shift
 *   ~ one's compliment
 * they apply to integers (char, short, int, long) only
 */

unsigned getbits(unsigned x, int p, int n);

void
main(void)
{
	/* & masks bits, | turns bits on.
	 *
	 * this occurs with in file permissions, which are
	 * described by 9 bits:  3 bits each for root, group, user.
	 * those bits describing read, write, execute.
	 *
	 * the following has root read, write and group read 
	 * permissions.
	 */
	short perms = 0640;
	printf("%o %o\n",
		/* remove write permissions for all */
		perms & 0555,
		/* add read permissions for all */
		perms | 0444);

	/* the exclusive or operator, sometimes called nor,
	 * returns 0 when bits are the same and 1 when different.
	 * in binary: 1100 ^ 1010 = 0110
	 */
	printf("%x\n", 0xC ^ 0xA);

	/* the shift operators move bits a specified number
	 * of positions to the right or left.
	 * i.e. 1 << 1 == 10 and 10 >> 1 == 1
	 *
	 * left shifting always fills with zero.
	 * right shifting fills unsigned variables with zero,
	 * while the sign bit is changed in a machine-dependent
	 * manner.
	 */
	printf("%x %o\n",
		3 << 2,
		0640 >> 3);

	/* ~ is unary.  it flips each bit in its operand,
	 * and is particularly useful for masking
	 * in a portable (length-independent) manner.
	 */
	printf("%o\n", 0111 & ~07);
  
	printf("%x\n", getbits(0x30, 5, 4));

	exits(0);
}

/* get n bits starting at position p */
unsigned
getbits(unsigned x, int p, int n)
{
	/* shift the desired bits to the right.
	 * add one since position is indexed from zero.
	 */
	return (x >> (p+1-n)) &
		/* produces n ones on the right.
		 * mask lops off any undesired bits to the left.
		 */
			~(~0 << n);
}
