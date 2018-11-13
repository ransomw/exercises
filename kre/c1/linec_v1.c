#include <u.h>
#include <libc.h>
#include <stdio.h>

/**
 * count lines
 */
void
main(void)
{
	inc c, nl;

	nl = 0;
	while((c = getchar()) != EOF)
		/* single quotes for char literals
		 * build to integer constants */
		// todo: tables for plan9 charset
		if(c == '\n')
			++nl;

	printf("%d\n", nl);

	exits(0);
}
