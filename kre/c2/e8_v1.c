#include <u.h>
#include <libc.h>
#include <stdio.h>

int get_num_bits(void);
unsigned rightrot(unsigned x, int n);

void
main(void)
{

	printf("%x %x %x %x\n",
		rightrot(0xABC, 4),
		rightrot(0xABC, 8),
		rightrot(0x1E1, 1),
		rightrot(0x3C3, 2));

	exits(0);
}

/* find the number of bits in an unsigned */
int
get_num_bits(void)
{
	int i;
	unsigned x;

	x = 1;
	for(i = 0; x != 0 && i < 65; ++i)
		x = x << 1;

	return i;
}

// todo: try to avoid get_num_bits, sizeof, or similar
//   two's compliment trick, perhaps?
/* rotate x to the right by n positions */
unsigned
rightrot(unsigned x, int n)
{
	int num_bits = get_num_bits();

	return (x >> n) |
		(x & ~(~0 << n)) << (num_bits - n);
}
