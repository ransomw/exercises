#include <u.h>
#include <libc.h>
#include <stdio.h>

int lower(int c);

void
main(void)
{
	print("%c%c\n", lower('X'), lower('x'));
}

int
lower(int c)
{
	/* parens unnecessary b/c of low precedence of ? */
	return c >= 'A' && c <= 'Z' ?
		c + 'a' - 'A' : c;
}
