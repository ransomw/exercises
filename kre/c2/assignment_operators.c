#include <u.h>
#include <libc.h>
#include <stdio.h>

/* the binary operators
 * + - * / % << >> & ^ |
 * have corresponding assignment operators --- i.e.
 *   <expr>_1 <op>= <expr>_2
 * is equivalent to
 *   <expr>_1 = (<expr>_1) <op> (<expr>_2)
 * for each of these,
 * except <expr>_1 is only computed once in the former case.
 */

int bitcount(unsigned x);

void
main(void)
{
	int x = 2;

	/* notice implicit parens: x is 8, not 6, in the following */
	x *= 2 + 2;
	printf("%d\n", x);

	printf("%d %d %d\n",
		bitcount(04),
		bitcount(05),
		bitcount(07));

	x = 1;
	if((x += 1) == 2)
		printf("asdf\n");

	exits(0);
}

/* count 1 bits in x */
int
bitcount(unsigned x)
{
	int b;

	for(b = 0; x != 0; x >>= 1)
		if(x & 01)
			b++;

	return b;
}
