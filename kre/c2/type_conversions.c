#include <u.h>
#include <libc.h>
#include <stdio.h>
/* charset-indep tests and conversions */
#include <ctype.h>

/* when operators get [two] operands of different types,
 * the operands can be automatically converted to a common type
 * in some situations, usually by converting the type with fewer
 * bits to the "wider" type as in an_int + a_float resulting in a float.
 * the assignment operator can legally lose bits, as in an_int = a_float.
 *
 * sec. 6 of appendix A describes formal rules.  informally,
 * - if either operand is long double, double, or float (resp.)
 *   convert the other to that type, in that order of precedence
 * - convert both char and short to int
 * afterward, if either operand is long, convert the other to long
 * ... some complications arise (e.g -1L < 1U while -1L > 1UL)
 *     in the additional case of unsigned numbers.
 */

int atoi(char s[]);
int lower(int c);

void
main(void)
{

	print("%d\n", atoi("123"));
	print("%c%c\n", lower('X'), lower('x'));
	/* from ctypes */
	print("%c%c\n", tolower('X'), tolower('x'));

	/* printable chars are always positive.
	 * however, when storing arbitrary bits in a char,
	 * whether type-conversion to an integer treats the value
	 * as signed (e.g. two's-compliment) or unsigned is mach-dep.
	 *
	 * so when storing bit sequences in a char,
	 * always specify signed or unsigned.
	 */
	char c;
	signed char sc;
	unsigned char uc;
	c = sc = uc = '\200';
	printf("%d %d %d\n", c + 1, sc + 1, uc + 1);

	/* the assignment operator always converts LHS to RHS.
	 * in the case of integers, bits are added, possibly
	 * via "sign extension" as in `sc + 1` above,
	 * or bits are dropped as in the following example
	 */
	long int li = 0xF000;
	c = li;
	printf("%d %d\n", li, c);

	/* conversion to wider integers and back is always
	 * non-lossy, whether there's sign extension or not
	 */
	int i = sc = '\200';
	signed char sc2 = i;
	printf("%d %d %d\n", sc, i, sc2);
	/* similar conversions occur on function calls
	 * according to *prototype* (not declaration).
	 * in the abscence of a prototype,
	 * - `char` and `short` become `int`
	 * - `float` becomes `double`
	 */

	/* a 'cast' of the form
	 *	(type name) expression
	 * can be used to explicitly convert an expression
	 * to a given type.  it converts using the same
	 * rules as the assignment operator.
	 */
	printf("%.1f\n", ((int) 2.5) + 2.5);
}

/* for example, since a char is a small integer, the arithmetic
 * operators automatically convert a_char + an_int to an integer
 *
 * the following converts a string of digits to an integer
 * using automatic type conversion
 */
int
atoi(char s[])
{
	int i, n;

	n = 0;
	for(i = 0;
		isdigit(s[i]);
		/* ^ ctype.h charset-independent version of
		 * the following check for charsets with contiguous
		 * digits
		 * s[i] >= '0' && s[i] <= '9';
		 * the two are not exactly equivalent, however:
		 * using relational expressions and boolean operators
		 * always results in 0 or 1, while truthy functions
		 * like isdigit may use any non-zero value instead of 1
		 */
		++i)
		/* this conversion still relies on assumptions
		 * about the charset, tho */
		n = 10 * n + (s[i] - '0');
	return n;
}

/* another example of the same: convert upper-case to lower-case,
 * _provided_ (1) upper- and lower-case chars are a fixed distance
 * apart and (2) the upper-chase chars start with 'A' and end with 'Z'
 */
int
lower(int c)
{
	/* (1) */
	if (c >= 'A' && c <= 'Z')
		/* (2) */
		return c + 'a' - 'A';
	else
		return c;
}
