#include <u.h>
#include <libc.h>
#include <stdio.h>

/**
 * cp input to output
 */
void
main(void)
{
	/* use int rather than char to ensure enough bits for EOF */
	int c;

	/* assignment expressions have a value:
	 * the left-hand side of the assignment.
	 * since test operators have higher precedence than assignment,
	 * the extra parens are necessary.  the following are equivalent
	 * a = b == c
	 * a = (b == c) */
	while((c = getchar()) != EOF)
		putchar(c); // result of operation not used

	exits(0);
}
