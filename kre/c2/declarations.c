#include <u.h>
#include <libc.h>
#include <stdio.h>

int my_strlen(const char[]);

void
main(void)
{
	/* variables must be declared before use,
	 * one or more name for each type,
	 * and optionally initialized
	 */
	int a, b = 2;
	int x;
	int y = 2;

	a = x = 1;
	printf("%d %d %d %d\n",
		a, b, x, y);

	/* variable declarations needn't all appear
	 * at the beginning of a function
	 *
	 * and arrays of any type are declared as follows
	 */
	char astr[10] = "asdf";
	/* or the size of the array can be inferred
	 * by initializing to a constant
	 */
	char bstr[] = "qwer";

	printf("%s\n", astr);
	printf("%s\n", bstr);

	/* the const qualifier specifies that a variable's value
	 * will not change
	 */
	const unsigned int z = 3;
	const char cstr[] = "zxcv";

	printf("%d %s\n",
		z, cstr);

	/* results about what happens when a const is changed
	 * are impl-dependent.   8c passes over with a warning.
	 */
	z = 2;
	printf("%d\n", z);
	
	printf("%d ", my_strlen(astr));
	printf("%s\n", astr);

	exits(0);
}

/* the const qualifier can also be used in function definitions
 * and prototypes.  again, 8c only warns by default.
 */
int
my_strlen(const char s[])
{
	int i;

	while(s[i] != '\0')
		++i;
	s[i-1] = 'z';
	return i;
}
