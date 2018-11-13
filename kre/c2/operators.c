#include <u.h>
#include <libc.h>
#include <stdio.h>

void
main(void)
{
	/* arithmetic: +, -, *, /, %
	 *
	 * precedence: [+, -](binary) < [*, /, %] < [+, -](unary)
	 *
	 * apply to all numbers, except %, the modulus operator,
	 * which computes remainders, only applies to integers
	 */
	printf("%d\n", 1 + 20 % 7); /* 1 + (20 % 7) */
	printf("%d\n", -(2 - 3));
	// ??? unary + does nothing?
	printf("%d\n", +(2 - 3));

	/* relational: >, >=, <, <= [all same precedence]
	 * equality: ==, != [all same precedence]
	 * logical: &&, ||
	 * unary negation: ! --- non-zero to zero, zero to one
	 *
	 * precendence: (relational) > (equality) > && > ||
	 *
	 */

	exits(0);
}
