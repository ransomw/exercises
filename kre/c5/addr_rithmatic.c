#include <u.h>
#include <libc.h>
#include <stdio.h>

/* much of this section is in alloc_and_free.c */

int mystrlen(char *s);

void
main(void)
{

	printf("%d\n", mystrlen("asdf"));

	exits(0);
}

int
mystrlen(char *s)
{
	char *p = s;

	while(*p != '\0')
		p++;
	/* pointer subtraction is explicity mentioned
	 * for the first time in this section.  specifically,
	 * for pointers p, q with p < q (i.e. with p
	 * occuring before q in the linearly ordered
	 * space of memory addresses),
		q - p + 1
	 * is the number of elements from p to q, inclusive.
	 *
	 * so as usual, this string length function returns
	 * the number of characters in the string other than
	 * the null character, '\0'.
	 */
	return p - s;
}
