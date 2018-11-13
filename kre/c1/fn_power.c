#include <u.h>
#include <libc.h>
#include <stdio.h>

/* this is a sort of declaration, like variable declarations
 * at the beginning of functions, called a 'function prototype'.
 * it must agree with the function definition and all uses of
 * the function.
 * note that parameter names need not agree with the function
 * definition.  indeed, parameter names are optional.
 * int power(int, int);
 * is equivalent. */
int power(int m, int n);

void
main(void)
{
	int i;

	for(i = 0; i < 10; ++i)
		printf("%d %d %d\n", i, power(2, i), power(-3, i));

	/* Plan 9 uses strings rather than integers to represent
	 * exit status. */
	exits(0);
}

/* power: raise base to n-th power; n >= 0 */
int
power(int base, int n)
{
	int i, p;

	p = 1;
	for(i = 1; i <= n; ++i)
		p *= base;
	/* return is followed by an arbitrary expression.
	 * functions may also return; without an expression
	 * or omit return, in which case there's an implicit return;
	 * before the closing right brace } */
	return p;
}

/* fn definition syntax
```pseudocode
return-type
function-name(parameter declarations, si presente)
{
	declarations
	statements
}
```
*/
