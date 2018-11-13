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

unsigned
rightrot_one(unsigned x)
{
	unsigned left_one = ~((unsigned) ~0 >> 1);

	if(x & 1)
		return left_one | (x >> 1);
	else
		return x >> 1;
}

/* rotate x to the right by n positions */
unsigned
rightrot(unsigned x, int n)
{
	for(; n > 0; --n)
		x = rightrot_one(x);

	return x;
}
