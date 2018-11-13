#include <u.h>
#include <libc.h>
#include <stdio.h>

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

/* rotate x to the right by n positions */
unsigned
rightrot(unsigned x, int n)
{
	unsigned left_one = ~((unsigned) ~0 >> 1);

	for(; n > 0; --n)
		if(x & 1)
			x = left_one | (x >> 1);
		else
			x = x >> 1;

	return x;
}
