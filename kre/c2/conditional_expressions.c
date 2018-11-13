#include <u.h>
#include <libc.h>
#include <stdio.h>

void
main(void)
{
	/* consider two methods of computing the maximum of a and b */
	int a = 1, b = 2, z, zz;

	if(a > b)
		z = a;
	else
		z = b;

	/* this is a *conditional expression*, i.e. an expression that
	 * uses the ternary operator `?:` generally of the form
	 *	<expr>_1 ? <expr>_2 : <expr>_3
	 * `?:` evalues <expr>_1 first, then
	 * if <expr>_1 is non-zero, <expr>_2 is evaluated,
	 * and that is the result of the expression, while
	 * if <expr>_1 is zero, <expr>_3 is evaluated,
	 * and that is the result.
	 *
	 * while only one of <expr>_2 and <expr>_3 are evaluated,
	 * the type of the result is still determined by applying
	 * the type conversion rules to both expressions.
	 */
	 */
	zz = (a > b) ? a : b;

	printf("%d %d\n", z, zz);



	exits(0);
}
