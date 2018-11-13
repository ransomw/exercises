/* expressions use one or more operators or function calls */
x == 0
x++
printf("%d", x)

/* a *statement* is an expression followed by a semicolon */
x == 0;
x++;
printf("%d", x);

/* {braces} group
 *	- declarations
 *		and
 *	- statements
 * together into a *block* or compound statement.
 */

if(x == 0) {
	x++;
	printf("%d", x);
}

void
my_fun(int x)
{
	x++;
	printf("%d", x);
}

/* both control flow and function calls are examples.
 * syntactically (e.g. in a yacc grammar), blocks are
 * equivalent to (i.e. or'd in the same production rule as)
 * a single statement.
 */
